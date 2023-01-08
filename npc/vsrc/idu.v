/* verilator lint_off UNUSED */
module idu (
    input [31:0] inst,
    output reg [6:0] opcode,
    output reg [63:0] immi_sext,
    output reg [4:0] rs1,
    output reg [4:0] rd
);
assign opcode = inst[6:0];

always @(*) begin
    case(opcode)
        7'b0010011: begin
                        immi_sext = {{52{inst[31]}}, inst[31:20]}; //ADDI
                        rs1 = inst[19:15];
                        rd = inst[11:7];
                    end
        7'b0110111: begin 
                        immi_sext = {{32{inst[31]}}, inst[31:12], 12'b0}; //LUI
                        rs1 = 5'b0;
                        rd = inst[11:7];
                    end
        7'b0010111: begin
                        immi_sext = {{32{inst[31]}}, inst[31:12], 12'b0}; //AUIPC
                        rs1 = 5'b0;
                        rd = inst[11:7];
                    end
        7'b1101111: begin
                        immi_sext = {{44{inst[31]}}, inst[19:12], inst[20], inst[30:25], inst[24:21], 1'b0}; //JAL
                        rs1 = 5'b0;
                        rd = inst[11:7];
                    end
        7'b1100111: begin
                        immi_sext = {{52{inst[31]}}, inst[31:20]}; //JALR
                        rs1 = inst[19:15];
                        rd = inst[11:7];
                    end
        default: begin
                        immi_sext = 64'b0; // NOT IMPLEMENTED
                        rs1 = 5'b0;
                        rd = 5'b0;
                end
    endcase
end

endmodule
/* verilator lint_off UNUSED */
