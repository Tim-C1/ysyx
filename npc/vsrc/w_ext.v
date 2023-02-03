/* verilator lint_off UNUSED */
module w_ext(
    input [63:0] op,
    output [63:0] rst
);
    assign rst = {{32{op[31]}}, op[31:0]};
endmodule
/* verilator lint_off UNUSED */
