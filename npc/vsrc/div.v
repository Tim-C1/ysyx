module div(
    input [63:0] op1,
    input [63:0] op2,
    input div_type,
    output reg [63:0] rst
);
    always @(*) begin
        case (div_type)
            1'b0: rst = $signed(op1) / $signed(op2);
            1'b1: rst = op1 / op2;
        endcase
    end
endmodule

