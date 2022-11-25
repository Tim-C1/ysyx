module pc(
    input clk,
    input rst,
    input [63:0] wdata,
    input wen,
    output reg [63:0] pc_val
);

always @(posedge clk) begin
    if (rst) pc_val <= 64'h80000000;
    else begin
        if (wen) pc_val <= wdata;
        else pc_val <= pc_val + 64'd4;
    end
end

endmodule
