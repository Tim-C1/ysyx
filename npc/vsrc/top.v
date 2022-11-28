module top ( 
    input clk,
    input rst,
    input [31:0] inst,
    output reg [63:0] r1,
    output reg [63:0] r2,
    output reg [63:0] pc_val,
    output [63:0] result
);

// signal from idu
wire [63:0] immi_sext;
wire [4:0] rs1;
wire [4:0] rd;

// signal from exu
wire wen;
//wire [63:0] result;

// signal from gpr
wire [63:0] rs1_val;

idu idu (.inst(inst), .immi_sext(immi_sext), .rs1(rs1), .rd(rd));
exu exu (.rs1_val(rs1_val), .immi_sext(immi_sext), .result(result), .wen(wen));
RegisterFile #(5, 64) gpr (.clk(clk), .wdata(result), .waddr(rd), .raddr(rs1), .wen(wen), .rdata(rs1_val), .r1(r1), .r2(r2));
pc pc(.clk(clk), .rst(rst), .wdata(0), .wen(0), .pc_val(pc_val));

export "DPI-C" task ebreak_detect;

task ebreak_detect;
    output is_ebreak;
    begin
        assign is_ebreak = inst == 32'b00000000000100000000000001110011;
    end
endtask

endmodule
