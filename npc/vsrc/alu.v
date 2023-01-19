module alu (
    input [63:0] op1,
    input [63:0] op2,
    input [2:0] op_type,
    input [5:0] shamt,
    input shtype,
    input add,
    output reg [63:0] rst,
    output reg eq,
    output reg lt,
    output reg lt_s
);
    always @(*) begin
        eq = op1 == op2;
        lt = op1 < op2;
        lt_s = $signed(op1) < $signed(op2);
        case (op_type)
            3'b000: begin rst = (add == 0) ? op1 + op2: op1 - op2; end
            3'b001: begin rst = op1 << shamt; end
            3'b010: begin rst = ($signed(op1) < $signed(op2)) ? 1: 0; end
            3'b011: begin rst = (op1 < op2) ? 1: 0; end
            3'b100: begin rst = op1 ^ op2; end
            3'b101: begin rst = (shtype == 0) ? op1 >> shamt: $signed(op1) >>> shamt; end
            3'b110: begin rst = op1 | op2; end
            3'b111: begin rst = op1 & op2; end
        endcase
    end
endmodule
