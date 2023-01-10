/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */
module RegisterFile #(ADDR_WIDTH = 1, DATA_WIDTH = 1) (
  input clk,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input [ADDR_WIDTH-1:0] raddr,
  input wen,
  output [DATA_WIDTH-1:0] rdata,
  output [DATA_WIDTH-1:0] rs1_reg,
  output [DATA_WIDTH-1:0] r10_val
);
 // reg [DATA_WIDTH-1:0] rf [ADDR_WIDTH-1:0];
  reg [DATA_WIDTH-1:0] rf [31:0];
  always @(posedge clk) begin
    if (wen) rf[waddr] <= wdata;
  end
  assign rdata = (raddr == 0) ? 0: rf[raddr];
  assign rs1_reg = rf[5'b00001];
  assign r10_val = rf[5'b01010];

  import "DPI-C" function void set_gpr_ptr(input logic [63:0] a []);
  initial set_gpr_ptr(rf);

endmodule
/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */

    
