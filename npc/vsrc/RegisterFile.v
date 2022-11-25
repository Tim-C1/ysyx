/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */
module RegisterFile #(ADDR_WIDTH = 1, DATA_WIDTH = 1) (
  input clk,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input [ADDR_WIDTH-1:0] raddr,
  input wen,
  output [DATA_WIDTH-1:0] r1,
  output [DATA_WIDTH-1:0] r2,
  output [DATA_WIDTH-1:0] rdata
);
  reg [DATA_WIDTH-1:0] rf [ADDR_WIDTH-1:0];
  always @(posedge clk) begin
    if (wen) rf[waddr] <= wdata;
  end
//always @(*) begin
//  if (raddr == 0) rdata = 0;
//  else rdata = rf[raddr];
//end
  assign rdata = rf[raddr];
  assign r1 = rf[5'd1];
  assign r2 = rf[5'd2];
endmodule
/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */

    
