/* verilator lint_off UNUSED */
module idu (
    input [31:0] inst,
    output reg [4:0] rs1,
    output reg [4:0] rs2,
    output reg [4:0] rd,
    output reg [63:0] imm,
    output [6:0] opcode,
    output reg [2:0] op_type,
    output reg shtype,
    output reg add
);
    assign opcode = inst[6:0];

    always @(*) begin
        case (opcode)
            7'b0010011: begin // Integer Register-Immediate Instructions
                rs1 = inst[19:15];
                rs2 = 5'b0;
                rd = inst[11:7];
                imm = {{52{inst[31]}}, inst[31:20]}; // immI
                op_type = inst[14:12];
                shtype = (inst[31:25] == 7'b0000000) ? 0: 1; // 0: Logic shift; 1: arithmetic shift
                add = 0;
            end

            7'b0011011: begin // RV64I IW
                rs1 = inst[19:15];
                rs2 = 5'b0;
                rd = inst[11:7];
                imm = {{52{inst[31]}}, inst[31:20]}; // immI
                op_type = inst[14:12];
                shtype = (inst[31:25] == 7'b0000000) ? 0: 1; // 0: Logic shift; 1: arithmetic shift
                add = 1'b0;
            end
           
            7'b0111011: begin // RV64I W
                rs1 = inst[19:15];
                rs2 = inst[24:20];
                rd = inst[11:7];
                imm = 64'b0;
                op_type = inst[14:12];
                shtype = (inst[31:25] == 7'b0000000) ? 0: 1;
                add = (inst[31:25] == 7'b0000000) ? 0: 1;
            end

            7'b0110011: begin // Integer Register-Register Instructions
                rs1 = inst[19:15];
                rs2 = inst[24:20];
                rd = inst[11:7];
                imm = 64'b0;
                op_type = inst[14:12];
                shtype = (inst[31:25] == 7'b0000000) ? 0: 1;
                add = (inst[31:25] == 7'b0000000) ? 0: 1;
            end

            7'b1100011: begin // Branch
                rs1 = inst[19:15];
                rs2 = inst[24:20];
                rd = 5'b0;
                imm = {{52{inst[31]}}, inst[7], inst[30:25], inst[11:8], 1'b0}; // immB 
                op_type = 3'b000;
                shtype = 0;
                add = 0;
            end

            7'b0110111, 7'b0010111: begin // LUI, AUIPC
                rs1 = 5'b0;
                rs2 = 5'b0;
                rd = inst[11:7];
                imm = {{32{inst[31]}}, inst[31:12], 12'b0};
                op_type = 3'b000;
                shtype = 1'b0;
                add = 1'b0;
            end

            7'b1101111: begin // JAL
                rs1 = 5'b0;
                rs2 = 5'b0;
                rd = inst[11:7];
                imm = {{44{inst[31]}}, inst[19:12], inst[20], inst[30:25], inst[24:21], 1'b0};
                op_type = 3'b000;
                shtype = 1'b0;
                add = 1'b0;
            end

            7'b1100111: begin // JALR
                rs1 = inst[19:15];
                rs2 = 5'b0;
                rd = inst[11:7];
                imm = {{52{inst[31]}}, inst[31:20]};
                op_type = 3'b000;
                shtype = 1'b0;
                add = 1'b0;
            end

            7'b0000011: begin // Load
                rs1 = inst[19:15];
                rs2 = 5'b0;
                rd = inst[11:7];
                imm = {{52{inst[31]}}, inst[31:20]}; // immI
                op_type = 3'b000;
                shtype = 1'b0;
                add = 1'b0;
            end
            
            7'b0100011: begin // Store
                rs1 = inst[19:15];
                rs2 = inst[24:20];
                rd = 5'b0;
                imm = {{52{inst[31]}}, inst[31:25], inst[11:8], inst[7]}; // immS
                op_type = 3'b000;
                shtype = 1'b0;
                add = 1'b0;
            end

            default: begin
                rs1 = 5'b0;
                rs2 = 5'b0;
                rd = 5'b0;
                imm = 64'b0;
                op_type = 3'b0;
                shtype = 1'b0;
                add = 1'b0;
            end

        endcase
    end
endmodule
/* verilator lint_off UNUSED */
