/* verilator lint_off UNUSED */
module sext(
    input [2:0] imm_type,
    input [31:0] imm_src,
    output reg [63:0] imm_sext
);
    always @(*) begin
        case(imm_type)
            3'b001: imm_sext = {{52{imm_src[31]}}, imm_src[31:20]}; // immI
            3'b011: imm_sext = {{52{imm_src[31]}}, imm_src[7], imm_src[30:25], imm_src[11:8], 1'b0}; // immB
            3'b101: imm_sext = {{44{imm_src[31]}}, imm_src[19:12], imm_src[20], imm_src[30:25], imm_src[24:21], 1'b0}; // immJ
            3'b010: imm_sext = {{52{imm_src[31]}}, imm_src[31:25], imm_src[11:8], imm_src[7]}; // immS
            3'b100: imm_sext = {{32{imm_src[31]}}, imm_src[31:12], 12'b0}; // immU
            default: imm_sext = 64'b0;
        endcase
    end
endmodule
/* verilator lint_off UNUSED */
