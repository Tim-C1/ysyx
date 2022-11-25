module exu (
    input [63:0] rs1_val,
    input [63:0] immi_sext,
    output [63:0] result,
    output wen
);

assign wen = 1'b1;
assign result = rs1_val + immi_sext;

endmodule
