module mul (
    input [63:0] op1,
    input [63:0] op2,
    input [1:0] mul_type,
    output reg [63:0] rst
);
    always @(*) begin
        case(mul_type)
            2'b00: rst = op1 * op2;
            2'b01: rst = ($signed(op1) * $signed(op2)) >> 64;
            2'b10: rst = ($signed(op1) * op2) >> 64;
            2'b11: rst = (op1 * op2) >> 64;
        endcase
    end

endmodule




