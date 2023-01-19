/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */
module RegisterFile #(ADDR_WIDTH = 1, DATA_WIDTH = 1) (
  input clk,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input [ADDR_WIDTH-1:0] raddr_1,
  input [ADDR_WIDTH-1:0] raddr_2,
  input wen,
  output [DATA_WIDTH-1:0] rdata_1,
  output [DATA_WIDTH-1:0] rdata_2,
  output [DATA_WIDTH-1:0] r10_val
);
 // reg [DATA_WIDTH-1:0] rf [ADDR_WIDTH-1:0];
  reg [DATA_WIDTH-1:0] rf [31:0];
  always @(posedge clk) begin
      if (wen) begin
          rf[waddr] <= wdata;
          rf[0] <= 0;
      end
  end
  assign rdata_1 = (raddr_1 == 0) ? 0: rf[raddr_1];
  assign rdata_2 = (raddr_2 == 0) ? 0: rf[raddr_2];
  assign r10_val = rf[5'b01010];

  import "DPI-C" function void set_gpr_ptr(input logic [63:0] a []);
  initial set_gpr_ptr(rf);

endmodule
/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */

    
