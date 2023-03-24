/* verilator lint_off UNUSED */
/* verilator lint_off DECLFILENAME */
`include "memory.v"

module top (
    input clk,
    input rst,
    output reg [63:0] pc_val,
    output [63:0] mepc_value,
    output [63:0] mcause_value,
    output [63:0] mtvec_value,
    output [63:0] mstatus_value,
    output [63:0] mtvec_data,
    output [63:0] mcause_data_test,
    output  mcause_wen_test,
    output [3:0] rst_ctl
);
    wire [63:0] wdata_pc;
    wire [63:0] pc_branch = pc_val + imm_sext;
    assign wdata_pc = npc_ctl == 3'b010 ?
                      pc_branch :
                      npc_ctl == 3'b001 ?
                      alu_rst : 
                      npc_ctl == 3'b011 ?
                      mtvec_val :
                      npc_ctl == 3'b100 ?
                      mepc_val : pc_val + 4;

    wire wen_pc = 1'b1;
    pc npc_pc (
        .clk(clk),
        .rst(rst),
        .wdata(wdata_pc),
        .wen(wen_pc),
        .pc_val(pc_val)
    );

    wire [31:0] inst;
    inst_mem npc_inst_mem (
        .pc(pc_val),
        .inst(inst)
    );

    wire eq;
    wire lt;
    wire ltu;
    wire [2:0] npc_ctl;
    wire wen_mem;
    wire ren_mem;
    wire wen_reg;
    wire [1:0] div_type;
    wire rem_type;
    wire [1:0] mul_type;
    wire [2:0] imm_type;
    wire [2:0] mem_type;
    wire [3:0] op_type;
    wire [1:0] op1_ctl;
    wire [1:0] op2_ctl;
    // csr signals
    wire [1:0] mepc_ctl;
    wire [1:0] mcause_ctl;
    wire mstatus_ctl;
    wire mtvec_ctl;
    wire mtvec_wen;
    wire mcause_wen;
    wire mstatus_wen;
    wire mepc_wen;
//    wire [3:0] rst_ctl;
    decoder npc_decoder (
        .opcode(inst[6:0]),
        .func3(inst[14:12]),
        .func7(inst[31:25]),
        .eq(eq),
        .lt(lt),
        .ltu(ltu),
        .csr_num(imm_sext),
        .func12(inst[31:20]),
        .npc_ctl(npc_ctl),
        .wen_mem(wen_mem),
        .ren_mem(ren_mem),
        .wen_reg(wen_reg),
        .div_type(div_type),
        .rem_type(rem_type),
        .mul_type(mul_type),
        .imm_type(imm_type),
        .mem_type(mem_type),
        .op_type(op_type),
        .op1_ctl(op1_ctl),
        .op2_ctl(op2_ctl),
        .rst_ctl(rst_ctl),
        .mstatus_ctl(mstatus_ctl),
        .mtvec_ctl(mtvec_ctl),
        .mepc_ctl(mepc_ctl),
        .mcause_ctl(mcause_ctl),
        .mtvec_wen(mtvec_wen),
        .mcause_wen(mcause_wen),
        .mstatus_wen(mstatus_wen),
        .mepc_wen(mepc_wen)
    );

    wire [63:0] imm_sext;
    sext npc_sext (
        .imm_type(imm_type),
        .imm_src(inst),
        .imm_sext(imm_sext)
    );

    wire [63:0] wdata_reg;
    wire [63:0] rd1_reg;
    wire [63:0] rd2_reg;
    wire [63:0] r10_val_reg;
    RegisterFile #(5, 64) npc_gprs (
        .clk(clk),
        .wdata(wdata_reg),
        .waddr(inst[11:7]),
        .raddr_1(inst[19:15]),
        .raddr_2(inst[24:20]),
        .wen(wen_reg),
        .rdata_1(rd1_reg),
        .rdata_2(rd2_reg),
        .r10_val(r10_val_reg)
    );

    wire [63:0] mepc_data = mepc_ctl == 2'b00 ? pc_val : 
                            mepc_ctl == 2'b01 ? rd1_reg : 
                            alu_rst; 

    wire [63:0] mcause_data = mcause_ctl == 2'b00 ? 64'hb : 
                              mcause_ctl == 2'b01 ? rd1_reg :
                              alu_rst;
    assign mcause_data_test = mcause_data;
    assign mcause_wen_test = mcause_wen;
    wire [63:0] mstatus_data = mstatus_ctl ? rd1_reg : alu_rst;
    /* wire [63:0] mtvec_data = mtvec_ctl ? rd1_reg : alu_rst; */
    assign mtvec_data = mtvec_ctl ? rd1_reg : alu_rst;
    wire [63:0] mepc_val;
    wire [63:0] mstatus_val;
    wire [63:0] mcause_val;
    wire [63:0] mtvec_val;
    wire [63:0] csr_rst;
    csr npc_csrs (
        .clk(clk),
        .mstatus_data(mstatus_data),
        .mtvec_data(mtvec_data),
        .mepc_data(mepc_data),
        .mcause_data(mcause_data),
        .mepc_wen(mepc_wen),
        .mstatus_wen(mstatus_wen),
        .mcause_wen(mcause_wen),
        .mtvec_wen(mtvec_wen),
        .csr_num(imm_sext),
        .mepc_val(mepc_val),
        .mstatus_val(mstatus_val),
        .mcause_val(mcause_val),
        .mtvec_val(mtvec_val),
        .csr_rst(csr_rst)
    );
    assign mstatus_value = mstatus_val;
    assign mtvec_value = mtvec_val;
    assign mcause_value = mcause_val;
    assign mepc_value = mepc_val;

    wire [63:0] op1_alu = op1_ctl == 2'b00 ?
                          pc_val :
                          op1_ctl == 2'b01 ?
                          64'b0 : rd1_reg;
    wire [63:0] op2_alu = op2_ctl == 2'b00 ?
                          rd2_reg :
                          op2_ctl == 2'b01 ?
                          imm_sext :
                          op2_ctl == 2'b11 ? 
                          csr_rst :
                          {58'b0, inst[25:20]};
    wire [63:0] alu_rst;
    alu npc_alu (
        .op1(op1_alu),
        .op2(op2_alu),
        .op_type(op_type),
        .rst(alu_rst),
        .eq(eq),
        .lt(ltu),
        .lt_s(lt)
    );

    wire [63:0] rd_mem;
    data_mem npc_data_mem (
        .wen(wen_mem),
        .ren(ren_mem),
        .mem_type(mem_type),
        .addr(alu_rst),
        .wdata(rd2_reg),
        .rdata(rd_mem)
    );

    // MUL, DIV, REM result
    wire [63:0] mul_rst;
    mul npc_mul (
        .op1(rd1_reg),
        .op2(rd2_reg),
        .mul_type(mul_type),
        .rst(mul_rst)
    );

    wire [63:0] div_rst;
    div npc_div (
        .op1(rd1_reg),
        .op2(rd2_reg),
        .div_type(div_type),
        .rst(div_rst)
    );

    wire [63:0] rem_rst;
    rem npc_rem (
        .op1(rd1_reg),
        .op2(rd2_reg),
        .rem_type(rem_type),
        .rst(rem_rst)
    );

    // W instrunction
    wire [63:0] alu_rst_w;
    w_ext npc_w_ext_alu (
        .op(alu_rst),
        .rst(alu_rst_w)
    );

    wire [63:0] mul_rst_w;
    w_ext npc_w_ext_mul (
        .op(mul_rst),
        .rst(mul_rst_w)
    );

    /* wire [63:0] div_rst_w; */
    /* w_ext npc_w_ext_div ( */
    /*     .op(div_rst), */
    /*     .rst(div_rst_w) */
    /* ); */

    wire [63:0] rem_rst_w;
    w_ext npc_w_ext_rem (
        .op(rem_rst),
        .rst(rem_rst_w)
    );

    assign wdata_reg = rst_ctl == 4'b0000 ?
                    alu_rst :
                    rst_ctl == 4'b0001 ?
                    alu_rst_w :
                    rst_ctl == 4'b0010 ?
                    pc_val + 4 :
                    rst_ctl == 4'b0011 ?
                    rd_mem :
                    rst_ctl == 4'b0100 ?
                    mul_rst :
                    rst_ctl == 4'b0101 ?
                    mul_rst_w :
                    rst_ctl == 4'b0110 ?
                    div_rst :
                    /* rst_ctl == 4'b0111 ? */
                    /* div_rst_w : */
                    rst_ctl == 4'b1000 ?
                    rem_rst : 
                    rst_ctl == 4'b1010 ?
                    csr_rst : rem_rst_w;

    export "DPI-C" task ebreak_detect;
    export "DPI-C" task trap;
    export "DPI-C" task dnpc;

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
            assign trap_state = (r10_val_reg != 64'b0);
        end
    endtask

    task dnpc;
        output [63:0] dnpc_val;
        begin
            assign dnpc_val = wdata_pc;
        end
    endtask
endmodule
/* verilator lint_off UNUSED */
/* verilator lint_off DECLFILENAME */

