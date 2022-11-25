/* verilator lint_off UNUSED */
module idu (
    input [31:0] inst,
    output [63:0] immi_sext,
    output [4:0] rs1,
    output [4:0] rd
);

// ADDI
assign immi_sext = {{52{inst[31]}}, inst[31:20]};
assign rs1 = inst[19:15];
assign rd = inst[11:7];

endmodule
/* verilator lint_off UNUSED */
