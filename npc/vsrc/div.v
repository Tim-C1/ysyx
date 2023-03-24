module div(
    input [63:0] op1,
    input [63:0] op2,
    input [1:0] div_type,
    output reg [63:0] rst
);
    wire [31:0] op1_hf = op1[31:0];
    wire [31:0] op2_hf = op2[31:0];
    reg [31:0] rst_32;
    always @(*) begin
        case (div_type)
            2'b00: begin rst = $signed(op1) / $signed(op2); rst_32 = 0; end
            2'b01: begin rst = op1 / op2; rst_32 = 0; end
            2'b10: begin rst_32 = $signed(op1_hf) / $signed(op2_hf); rst = {{32{rst_32[31]}}, rst_32[31:0]}; end
            2'b11: begin rst_32 = op1_hf / op2_hf; rst = {{32{rst_32[31]}}, rst_32[31:0]}; end
        endcase
    end
endmodule

