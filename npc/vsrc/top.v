/* verilator lint_off UNUSED */
module top ( 
    input clk,
    input rst,
    output reg [63:0] pc_val
);
    reg [31:0] inst;
    reg [63:0] inst_bus;
    always @(*) begin
        if (pc_val >= 64'h80000000) begin
            pmem_read(pc_val, inst_bus);
            if (pc_val[2] == 1'b0) begin // read the first 4 bytes of inst_bus
                inst = inst_bus[31:0];
            end
            else begin
                inst = inst_bus[63:32];
            end
        end
        else begin
            inst_bus = 64'b0;
            inst = 32'b0;
        end
    end

    // idu signals
    reg [4:0] rs1_idu;
    reg [4:0] rs2_idu;
    reg [4:0] rd_idu;
    reg [63:0] imm_idu;
    wire [6:0] opcode_idu;
    reg [2:0] op_type_idu;
    reg shtype_idu;
    reg add_idu;
    idu idu(
        .inst(inst),
        .rs1(rs1_idu),
        .rs2(rs2_idu),
        .rd(rd_idu),
        .imm(imm_idu),
        .opcode(opcode_idu),
        .op_type(op_type_idu),
        .shtype(shtype_idu),
        .add(add_idu)
    );
    
    // alu signals
    wire [63:0] op1_alu;
    wire [63:0] op2_alu;
    wire [5:0] shamt_alu;
    wire [63:0] rst_alu;
    wire [63:0] rst_alu_std;
    wire [63:0] rst_alu_tmp;
    reg eq_alu;
    reg lt_alu;
    reg lt_s_alu;

    assign op1_alu = (opcode_idu == 7'b0010111 || // AUIPC
                      opcode_idu == 7'b1101111 || // JAL
                      opcode_idu == 7'b1100011    // BRANCH
                     ) ? pc_val:
                         ((opcode_idu == 7'b0011011 || opcode_idu == 7'b0111011) && op_type_idu == 3'b101 && shtype_idu == 0)
                          ? {32'b0, op1_val[31:0]}:
                                ((opcode_idu == 7'b001011 || opcode_idu == 7'b0111011) && op_type_idu == 3'b101 && shtype_idu == 1)
                                    ? {{32{op1_val[31]}}, op1_val[31:0]}:
                                         op1_val; // read rs1 from gprs or current pc
    
    assign op2_alu = (opcode_idu == 7'b0110011 || opcode_idu == 7'b0111011) // IRRI RV64IW
                      ? op2_val: imm_idu; // read rs2 from gprs or imm

    assign shamt_alu = (opcode_idu == 7'b0010011 ||
                        opcode_idu == 7'b0011011 
                       ) ? inst[25:20]: op2_val[5:0];

    alu alu(
        .op1(op1_alu),
        .op2(op2_alu),
        .op_type(op_type_idu),
        .shamt(shamt_alu),
        .shtype(shtype_idu),
        .add(add_idu),
        .rst(rst_alu_std),
        .eq(eq_alu),
        .lt(lt_alu),
        .lt_s(lt_s_alu)
    );
   
    // RV64 M Extentions
    reg [63:0] rst_mext;
    always @(*) begin
        case(op_type_idu)
            3'b000: rst_mext = op1_val * op2_val;
            3'b001: rst_mext = ($signed(op1_val) * $signed(op2_val)) >> 64;
            3'b010: rst_mext = ($signed(op1_val) * op2_val) >> 64;
            3'b011: rst_mext = (op1_val * op2_val) >> 64;
            3'b100: rst_mext = $signed(op1_val) / $signed(op2_val);
            3'b101: rst_mext = op1_val / op2_val; 
            3'b110: rst_mext = $signed(op1_val) % $signed(op2_val);
            3'b111: rst_mext = op1_val % op2_val;
        endcase
    end

    assign rst_alu_tmp = ((opcode_idu == 7'b0110011 && inst[31:25] == 7'b0000001) || (opcode_idu == 7'b0111011 && inst[31:25] == 7'b0000001)) ? rst_mext: rst_alu_std; 

    assign rst_alu = (opcode_idu == 7'b1100111) ? {rst_alu_tmp[63:1], 1'b0}: // JALR set the least bit 0
                     ((opcode_idu == 7'b0011011 || opcode_idu == 7'b0111011) ? {{32{rst_alu_tmp[31]}}, rst_alu_tmp[31:0]}:
                     rst_alu_tmp);

    // gprs signals
    wire wen_gpr;
    wire [63:0] wdata_gpr;
    wire [63:0] op1_val; 
    wire [63:0] op2_val;
    wire [63:0] r10_val_gpr;

    assign wen_gpr = (opcode_idu == 7'b0010011 || // IRII
               opcode_idu == 7'b0110011 || // IRRI
               opcode_idu == 7'b0110111 || // LUI
               opcode_idu == 7'b0010111 || // AUIPC
               opcode_idu == 7'b1101111 || // JAL
               opcode_idu == 7'b1100111 || // JALR
               opcode_idu == 7'b0000011 || // LD
               opcode_idu == 7'b0011011 || // RV64 IW
               opcode_idu == 7'b0111011    // RV64 W
              );

    assign wdata_gpr = (opcode_idu == 7'b1101111 || opcode_idu == 7'b1100111) ? // JAL, JALR
                       pc_val + 64'h4 :
                       ((opcode_idu == 7'b0000011) ? // Load
                       rdata_mem : 
                       rst_alu);

    RegisterFile #(5, 64) gpr (
        .clk(clk),
        .raddr_1(rs1_idu),
        .raddr_2(rs2_idu),
        .waddr(rd_idu),
        .wen(wen_gpr),
        .wdata(wdata_gpr),
        .rdata_1(op1_val),
        .rdata_2(op2_val),
        .r10_val(r10_val_gpr)
    );

    // pc signals
    reg [63:0] wdata_pc;
    wire [2:0] branch_type;
    reg wen_pc;
    
    assign branch_type = inst[14:12]; 
    always @(*) begin
        if (opcode_idu == 7'b1100011) begin
            case(branch_type)
                3'b000: begin
                    wdata_pc = (op1_val == op2_val) ? rst_alu: 64'b0;
                    wen_pc = (op1_val == op2_val);
                end
                3'b001: begin
                    wdata_pc = (op1_val != op2_val) ? rst_alu: 64'b0;
                    wen_pc = (op1_val != op2_val);
                end
                3'b100: begin
                    wdata_pc = ($signed(op1_val) < $signed(op2_val)) ? rst_alu: 64'b0;
                    wen_pc = ($signed(op1_val) < $signed(op2_val));
                end
                3'b101: begin
                    wdata_pc = ($signed(op1_val) >= $signed(op2_val)) ? rst_alu: 64'b0;
                    wen_pc = ($signed(op1_val) >= $signed(op2_val));
                end
                3'b110: begin
                    wdata_pc = (op1_val < op2_val) ? rst_alu: 64'b0;
                    wen_pc = (op1_val < op2_val);
                end
                3'b111: begin
                    wdata_pc = (op1_val >= op2_val) ? rst_alu: 64'b0;
                    wen_pc = (op1_val >= op2_val);
                end
                default: begin
                    wdata_pc = 64'b0;
                    wen_pc = 1'b0;
                end
            endcase
        end
        else if (opcode_idu == 7'b1101111 || opcode_idu == 7'b1100111) begin
            wdata_pc = rst_alu;
            wen_pc = 1'b1;
        end
        else begin
            wdata_pc = 64'b0;
            wen_pc = 1'b0;
        end
    end

    pc pc (
        .clk(clk),
        .rst(rst),
        .wdata(wdata_pc),
        .wen(wen_pc),
        .pc_val(pc_val)
    );
    
    // load
    reg [63:0] raddr_mem;
    reg [63:0] rdata_bus;
    wire [2:0] ld_type;
    wire rena_mem;
    wire [63:0] rmem_offset;
    reg [63:0] rdata_mem;

    assign raddr_mem = rst_alu;
    assign ld_type = inst[14:12];
    assign rena_mem = opcode_idu == 7'b0000011;
    assign rmem_offset = raddr_mem - (raddr_mem & ~64'h7);

    always @(*) begin
        if (rena_mem) begin
            pmem_read(raddr_mem, rdata_bus); 
            case (ld_type)
                3'b000: begin
                    case (rmem_offset)
                        64'h0: begin rdata_mem = {{56{rdata_bus[7]}}, rdata_bus[7:0]}; end
                        64'h1: begin rdata_mem = {{56{rdata_bus[15]}}, rdata_bus[15:8]}; end
                        64'h2: begin rdata_mem = {{56{rdata_bus[23]}}, rdata_bus[23:16]}; end
                        64'h3: begin rdata_mem = {{56{rdata_bus[31]}}, rdata_bus[31:24]}; end
                        64'h4: begin rdata_mem = {{56{rdata_bus[39]}}, rdata_bus[39:32]}; end
                        64'h5: begin rdata_mem = {{56{rdata_bus[47]}}, rdata_bus[47:40]}; end
                        64'h6: begin rdata_mem = {{56{rdata_bus[55]}}, rdata_bus[55:48]}; end
                        64'h7: begin rdata_mem = {{56{rdata_bus[63]}}, rdata_bus[63:56]}; end
                        default: begin rdata_mem = 64'hffffffffffffffff; end
                    endcase
                end

                3'b001: begin
                    case(rmem_offset)
                        64'h0: begin rdata_mem = {{48{rdata_bus[15]}}, rdata_bus[15:0]}; end
                        64'h1: begin rdata_mem = {{48{rdata_bus[23]}}, rdata_bus[23:8]}; end
                        64'h2: begin rdata_mem = {{48{rdata_bus[31]}}, rdata_bus[31:16]}; end
                        64'h3: begin rdata_mem = {{48{rdata_bus[39]}}, rdata_bus[39:24]}; end
                        64'h4: begin rdata_mem = {{48{rdata_bus[47]}}, rdata_bus[47:32]}; end
                        64'h5: begin rdata_mem = {{48{rdata_bus[55]}}, rdata_bus[55:40]}; end
                        64'h6: begin rdata_mem = {{48{rdata_bus[63]}}, rdata_bus[63:48]}; end
                        default: begin rdata_mem = 64'hffffffffffffffff; end
                    endcase
                end

                3'b010: begin
                    case(rmem_offset)
                        64'h0: begin rdata_mem = {{32{rdata_bus[31]}}, rdata_bus[31:0]}; end
                        64'h1: begin rdata_mem = {{32{rdata_bus[39]}}, rdata_bus[39:8]}; end
                        64'h2: begin rdata_mem = {{32{rdata_bus[47]}}, rdata_bus[47:16]}; end
                        64'h3: begin rdata_mem = {{32{rdata_bus[55]}}, rdata_bus[55:24]}; end
                        64'h4: begin rdata_mem = {{32{rdata_bus[63]}}, rdata_bus[63:32]}; end
                        default: begin rdata_mem = 64'hffffffffffffffff; end
                    endcase
                end

                3'b011: begin
                    case(rmem_offset)
                        64'h0: begin rdata_mem = rdata_bus; end
                        default: begin rdata_mem = 64'hffffffffffffffff; end
                    endcase
                end

                3'b100: begin
                    case (rmem_offset)
                        64'h0: begin rdata_mem = {56'b0, rdata_bus[7:0]}; end
                        64'h1: begin rdata_mem = {56'b0, rdata_bus[15:8]}; end
                        64'h2: begin rdata_mem = {56'b0, rdata_bus[23:16]}; end
                        64'h3: begin rdata_mem = {56'b0, rdata_bus[31:24]}; end
                        64'h4: begin rdata_mem = {56'b0, rdata_bus[39:32]}; end
                        64'h5: begin rdata_mem = {56'b0, rdata_bus[47:40]}; end
                        64'h6: begin rdata_mem = {56'b0, rdata_bus[55:48]}; end
                        64'h7: begin rdata_mem = {56'b0, rdata_bus[63:56]}; end
                        default: begin rdata_mem = 64'hffffffffffffffff; end
                    endcase
                end

                3'b101: begin
                    case(rmem_offset)
                        64'h0: begin rdata_mem = {48'b0, rdata_bus[15:0]}; end
                        64'h1: begin rdata_mem = {48'b0, rdata_bus[23:8]}; end
                        64'h2: begin rdata_mem = {48'b0, rdata_bus[31:16]}; end
                        64'h3: begin rdata_mem = {48'b0, rdata_bus[39:24]}; end
                        64'h4: begin rdata_mem = {48'b0, rdata_bus[47:32]}; end
                        64'h5: begin rdata_mem = {48'b0, rdata_bus[55:40]}; end
                        64'h6: begin rdata_mem = {48'b0, rdata_bus[63:48]}; end
                        default: begin rdata_mem = 64'hffffffffffffffff; end
                    endcase
                end

                3'b110: begin
                    case(rmem_offset)
                        64'h0: begin rdata_mem = {32'b0, rdata_bus[31:0]}; end
                        64'h1: begin rdata_mem = {32'b0, rdata_bus[39:8]}; end
                        64'h2: begin rdata_mem = {32'b0, rdata_bus[47:16]}; end
                        64'h3: begin rdata_mem = {32'b0, rdata_bus[55:24]}; end
                        64'h4: begin rdata_mem = {32'b0, rdata_bus[63:32]}; end
                        default: begin rdata_mem = 64'hffffffffffffffff; end
                    endcase
                end
                default: begin rdata_mem = 64'hffffffffffffffff; end
            endcase
        end
        else begin
            rdata_bus = 64'b0;
            rdata_mem = 64'hffffffffffffffff;
        end
    end
    
    // store
    wire [63:0] waddr_mem;
    wire [63:0] wdata_mem;
    wire [63:0] waddr_offset;
    reg [7:0] wmask_mem;
    wire [2:0] st_type;
    wire wen_mem;

    assign st_type = inst[14:12];
    assign waddr_mem = rst_alu;
    assign wdata_mem = op2_val;
    assign waddr_offset = waddr_mem - (waddr_mem & ~64'h7);
    assign wmask_mem = (st_type == 3'b000) ? 8'b00000001 :
                       (st_type == 3'b001) ? 8'b00000011 :
                       (st_type == 3'b010) ? 8'b00001111 :
                       (st_type == 3'b011) ? 8'b11111111 :
                                             8'b00000000;
    always @(*) begin
        case (st_type)
            3'b000: begin
                case (waddr_offset)
                    64'h0: begin wmask_mem = 8'b00000001; end
                    64'h1: begin wmask_mem = 8'b00000010; end
                    64'h2: begin wmask_mem = 8'b00000100; end
                    64'h3: begin wmask_mem = 8'b00001000; end
                    64'h4: begin wmask_mem = 8'b00010000; end
                    64'h5: begin wmask_mem = 8'b00100000; end
                    64'h6: begin wmask_mem = 8'b01000000; end
                    64'h7: begin wmask_mem = 8'b10000000; end
                    default: begin wmask_mem = 8'b00000000; end
                endcase
            end

            3'b001: begin
                case (waddr_offset)
                    64'h0: begin wmask_mem = 8'b00000011; end
                    64'h1: begin wmask_mem = 8'b00000110; end
                    64'h2: begin wmask_mem = 8'b00001100; end
                    64'h3: begin wmask_mem = 8'b00011000; end
                    64'h4: begin wmask_mem = 8'b00110000; end
                    64'h5: begin wmask_mem = 8'b01100000; end
                    64'h6: begin wmask_mem = 8'b11000000; end
                    default: begin wmask_mem = 8'b00000000; end
                endcase
            end

            3'b010: begin
                case (waddr_offset)
                    64'h0: begin wmask_mem = 8'b00001111; end
                    64'h1: begin wmask_mem = 8'b00011110; end
                    64'h2: begin wmask_mem = 8'b00111100; end
                    64'h3: begin wmask_mem = 8'b01111000; end
                    64'h4: begin wmask_mem = 8'b11110000; end
                    default: begin wmask_mem = 8'b00000000; end
                endcase
            end

            3'b011: begin
                case (waddr_offset)
                    64'h0: begin wmask_mem = 8'b11111111; end
                    default: begin wmask_mem = 8'b00000000; end
                endcase
            end

            default: begin wmask_mem = 8'b00000000; end
        endcase
    end

    assign wen_mem = opcode_idu == 7'b0100011;
    always @(*) begin
        if (wen_mem) begin
            pmem_write(waddr_mem, wdata_mem, wmask_mem);
        end
    end
                                             
    import "DPI-C" function void pmem_read(
        input longint raddr, output longint rdata);

    import "DPI-C" function void pmem_write(
      input longint waddr, input longint wdata, input byte wmask);

    export "DPI-C" task ebreak_detect;
    export "DPI-C" task trap;

    wire [31:0] ebreak = 32'b00000000000100000000000001110011;
    task ebreak_detect;
        output is_ebreak;
        begin
            assign is_ebreak = (inst == ebreak);
        end
    endtask

    task trap;
        output trap_state;
        begin
            assign trap_state = (r10_val_gpr != 64'b0);
        end
    endtask

endmodule
/* verilator lint_off UNUSED */
