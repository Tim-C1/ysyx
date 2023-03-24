module csr (
    input clk,
    input [63:0] mepc_data,
    input [63:0] mstatus_data,
    input [63:0] mcause_data,
    input [63:0] mtvec_data,
    input mepc_wen,
    input mstatus_wen,
    input mcause_wen,
    input mtvec_wen,
    input [63:0] csr_num,
    output [63:0] mepc_val,
    output [63:0] mstatus_val,
    output [63:0] mcause_val,
    output [63:0] mtvec_val,
    output [63:0] csr_rst
);

    reg [63:0] mepc;
    reg [63:0] mstatus = 64'ha00018000;
    reg [63:0] mcause;
    reg [63:0] mtvec;

    always@(posedge clk) begin
        if (mepc_wen) mepc <= mepc_data;
        if (mstatus_wen) mstatus <= mstatus_data;
        if (mcause_wen) mcause <= mcause_data;
        if (mtvec_wen) mtvec <= mtvec_data;
    end
    
    assign mepc_val = mepc;
    assign mstatus_val = mstatus;
    assign mcause_val = mcause;
    assign mtvec_val = mtvec;
    assign csr_rst = csr_num == 64'h300 ? mstatus :
                     csr_num == 64'h305 ? mtvec : 
                     csr_num == 64'h341 ? mepc : 
                     csr_num == 64'h342 ? mcause : 64'h0; 
 endmodule
