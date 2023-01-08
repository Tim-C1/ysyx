module top ( 
    input clk,
    input rst,
    input [31:0] inst,
    output reg [63:0] pc_val,
    output [63:0] result,
    output [63:0] rs1_reg
);

// ebreak
wire [31:0] ebreak = 32'b00000000000100000000000001110011;

// signal from idu
wire [63:0] immi_sext;
wire [6:0] opcode;
wire [4:0] rs1;
wire [4:0] rd;

// signal from pc

// signal from exu
wire wen_reg;
wire wen_pc;
wire [63:0] npc;

// signal from gpr
wire [63:0] rs1_val;

// signal from register file
wire [63:0] a0_val;

idu idu (.inst(inst), .opcode(opcode), .immi_sext(immi_sext), .rs1(rs1), .rd(rd));
exu exu (.rs1_val(rs1_val), .immi_sext(immi_sext), .pc(pc_val), .opcode(opcode), .result(result), .npc(npc), .wen_reg(wen_reg), .wen_pc(wen_pc));
RegisterFile #(5, 64) gpr (.clk(clk), .wdata(result), .waddr(rd), .raddr(rs1), .wen(wen_reg), .rdata(rs1_val), .rs1_reg(rs1_reg), .r10_val(a0_val));
pc pc(.clk(clk), .rst(rst), .wdata(npc), .wen(wen_pc), .pc_val(pc_val));

export "DPI-C" task ebreak_detect;
export "DPI-C" task trap;

task ebreak_detect;
    output is_ebreak;
    begin
        assign is_ebreak = (inst == ebreak);
    end
endtask

task trap;
    output trap_state;
    begin
        assign trap_state = (a0_val != 64'b0);
    end
endtask

endmodule

