/* verilator lint_off WIDTH */
module alu (
    input [63:0] op1,
    input [63:0] op2,
    input [3:0] op_type,
    output reg [63:0] rst,
    output reg eq,
    output reg lt,
    output reg lt_s
);
    wire [31:0] op1_low = op1[31:0];
    always @(*) begin
        eq = op1 == op2;
        lt = op1 < op2;
        lt_s = $signed(op1) < $signed(op2);
        case (op_type)
            4'b0000: begin rst = op1 + op2; end
            4'b1000: begin rst = op1 - op2; end
            4'b0001: begin rst = op1 << op2[5:0]; end
            4'b0010: begin rst = ($signed(op1) < $signed(op2)) ? 1: 0; end
            4'b0011: begin rst = (op1 < op2) ? 1: 0; end
            4'b0100: begin rst = op1 ^ op2; end
            4'b0101: begin rst = op1 >> op2[5:0]; end
            4'b1101: begin rst = $signed(op1) >>> op2[5:0]; end
            4'b0110: begin rst = op1 | op2; end
            4'b0111: begin rst = op1 & op2; end
            4'b1001: begin rst = op1_low >> op2[4:0]; end
            4'b1010: begin rst = $signed(op1_low) >>> op2[4:0]; rst[63:32] = {{32{op1_low[31]}}}; end
            default: rst = 64'hffffffffffffffff;
        endcase
    end
endmodule
/* verilator lint_off WIDTH */
