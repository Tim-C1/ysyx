module exu (
    input [63:0] rs1_val,
    input [63:0] immi_sext,
    input [63:0] pc,
    input [6:0] opcode,
    output reg [63:0] result,
    output reg [63:0] npc,
    output wen_reg,
    output reg wen_pc
);

always @(*) begin
    case (opcode)
        7'b0010011: begin result = rs1_val + immi_sext; npc = pc + 4; wen_pc = 1'b0; end // ADDI
        7'b0110111: begin result = immi_sext; npc = pc + 4; wen_pc = 1'b0; end // LUI
        7'b0010111: begin result = pc + immi_sext; npc = pc + 4; wen_pc = 1'b0; end // AUIPC
        7'b1101111: begin result = pc + 4; npc = pc + immi_sext; wen_pc = 1'b1; end // JAL
        7'b1100111: begin result = pc + 4 ; npc = (immi_sext + rs1_val) & (~ 64'b1); wen_pc = 1'b1; end // JALR
        default: begin result = 64'b0; npc = pc + 4; wen_pc = 1'b0; end
    endcase
end
assign wen_reg = 1'b1;

endmodule
