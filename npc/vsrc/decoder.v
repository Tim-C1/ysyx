module decoder(
    input [6:0] opcode,
    input [2:0] func3,
    input [6:0] func7,
    input eq,
    input lt,
    input ltu,
    output [1:0] npc_ctl,
    output wen_mem,
    output ren_mem,
    output wen_reg,
    output div_type,
    output rem_type,
    output [1:0] mul_type,
    output [2:0] imm_type,
    output [2:0] mem_type,
    output [3:0] op_type,
    output [1:0] op1_ctl,
    output [1:0] op2_ctl,
    output [3:0] rst_ctl
);
    // op1_ctl: 00 -- pc, 01 -- 0, 10 -- rd1
    assign op1_ctl = (opcode == 7'b0110111) ? // LUI
                      2'b01 :
                     (opcode == 7'b0010111 || // AUIPC
                      opcode == 7'b1101111) ?  // JAL
                      2'b00 : 2'b10;

    // op2_ctl: 00 -- rd2, 01 -- imm_sext, 10 -- shamt
    //assign op2_ctl = (opcode == 7'b0110011 || // ADD, SUB ...
    //                  opcode == 7'b1100011 || // Branch ...
    //                  opcode == 7'b0111011) ?  // ADDW, SUBW ...
    //                  1'b0: 1'b1;

    assign op2_ctl = ((opcode == 7'b0010011 && func3 == 3'b001) ||
                      (opcode == 7'b0010011 && func3 == 3'b101) ||
                      (opcode == 7'b0011011 && func3 == 3'b001) ||
                      (opcode == 7'b0011011 && func3 == 3'b101)) ?
                      2'b10 :
                      (opcode == 7'b0110011 ||
                       opcode == 7'b1100011 ||
                       opcode == 7'b0111011) ?
                      2'b00 : 2'b01;

   // imm_type: 000 -- R, 001 -- I, 010 -- S, 011 -- B, 100 -- U, 101 -- J
    assign imm_type = (opcode == 7'b0110111 || // LUI
                       opcode == 7'b0010111) ? // AUIPC
                       3'b100 :
                      (opcode == 7'b1101111) ? // JAL
                       3'b101 :
                      (opcode == 7'b1100111 || // JALR
                       opcode == 7'b0000011 || // Load
                       opcode == 7'b0010011 || // ADDI ...
                       opcode == 7'b0011011) ? // ADDIW ...
                       3'b001 :
                      (opcode == 7'b1100011) ? // Branch
                       3'b011 :
                      (opcode == 7'b0100011) ? // Store
                       3'b010 : 3'b000;

    // op_type: 0000: +, 1000: -, 0001: <<, 0010: slt, 0011: sltu, 0100: ^, 0101: >>, 1101: >>>, 0110: |, 0111: &, 1001: srliw, 1010: sraiw, 1011: srlw, 1100: sraw
    assign op_type = (opcode == 7'b0110111 || // LUI
                      opcode == 7'b0010111 || // AUIPC
                      opcode == 7'b1101111 || // JAL
                      opcode == 7'b1100111 || // JALR
                      opcode == 7'b0000011 || // Load
                      opcode == 7'b0100011 || // Store
                      opcode == 7'b1100011 || // Branch
                     (opcode == 7'b0010011 && func3 == 3'b000) || // ADDI
                     (opcode == 7'b0110011 && func3 == 3'b000 && func7 == 7'b0000000) || // ADD
                     (opcode == 7'b0011011 && func3 == 3'b000) || // ADDIW
                     (opcode == 7'b0111011 && func3 == 3'b000 && func7 == 7'b0000000)) ? // ADDW
                      4'b0000 :
                     ((opcode == 7'b0110011 && func3 == 3'b000 && func7 == 7'b0100000) || // SUB
                      (opcode == 7'b0111011 && func3 == 3'b000 && func7 == 7'b0100000)) ? // SUBW
                      4'b1000 :
                     ((opcode == 7'b0010011 && func3 == 3'b001) || // SLLI
                      (opcode == 7'b0110011 && func3 == 3'b001) || // SLL
                      (opcode == 7'b0011011 && func3 == 3'b001) || // SLLIW
                      (opcode == 7'b0111011 && func3 == 3'b001)) ? // SLLW
                      4'b0001 :
                     ((opcode == 7'b0010011 && func3 == 3'b010) || // SLTI
                      (opcode == 7'b0110011 && func3 == 3'b010)) ? // SLT
                      4'b0010 :
                     ((opcode == 7'b0010011 && func3 == 3'b011) || // SLTIU
                      (opcode == 7'b0110011 && func3 == 3'b011)) ? // SLTU
                      4'b0011 :
                     ((opcode == 7'b0110011 && func3 == 3'b100) || // XOR
                      (opcode == 7'b0010011 && func3 == 3'b100)) ? // XORI
                      4'b0100 :
                     ((opcode == 7'b0010011 && func3 == 3'b101 && func7[5] == 1'b0) || // SRLI
                      (opcode == 7'b0110011 && func3 == 3'b101 && func7[5] == 1'b0)) ? // SRL
                      4'b0101 :
                     ((opcode == 7'b0010011 && func3 == 3'b101 && func7[5] == 1'b1) || // SRAI
                      (opcode == 7'b0110011 && func3 == 3'b101 && func7[5] == 1'b1)) ? // SRA
                      4'b1101 :
                     ((opcode == 7'b0010011 && func3 == 3'b110) || // ORI
                      (opcode == 7'b0110011 && func3 == 3'b110)) ? // OR
                      4'b0110 :
                     ((opcode == 7'b0010011 && func3 == 3'b111) || // ANDI
                      (opcode == 7'b0110011 && func3 == 3'b111)) ? // AND
                      4'b0111 :
                     ((opcode == 7'b0011011 && func3 == 3'b101 && func7[5] == 1'b0) || // SRLIW
                      (opcode == 7'b0111011 && func3 == 3'b101 && func7[5] == 1'b0)) ? // SRLW
                      4'b1001 : 4'b1010;

    // mem_type:
    assign mem_type = func3;

    // wen_mem
    assign wen_mem = (opcode == 7'b0100011);

    // ren_mem
    assign ren_mem = (opcode == 7'b0000011);

    // npc_ctl: 00 -- pc + 4, 01 -- alu_rst, 10 -- pc_branch
    assign npc_ctl = (opcode == 7'b1101111 || // JAL
                      opcode == 7'b1100111) ? // JALR
                      2'b01 :
                      ((opcode == 7'b1100011 && func3 == 3'b000 && eq == 1'b1) || // BEQ
                      (opcode == 7'b1100011 && func3 == 3'b001 && eq == 1'b0) || // BNE
                      (opcode == 7'b1100011 && func3 == 3'b100 && lt == 1'b1) || // BLT
                      (opcode == 7'b1100011 && func3 == 3'b101 && lt == 1'b0) || // BGE
                      (opcode == 7'b1100011 && func3 == 3'b110 && ltu == 1'b1) || // BLTU
                      (opcode == 7'b1100011 && func3 == 3'b111 && ltu == 1'b0)) ? // BGEU
                      2'b10 : 2'b00;

    // rst_type:
    // 0000: alu_result
    // 0001: alu_result_W
    // 0010: pc + 4
    // 0011: data_mem
    // 0100: mul
    // 0101: mul_w
    // 0110: div
    // 0111: div_w
    // 1000: rem
    // 1001: rem_w
    assign rst_ctl = (opcode == 7'b0110111 || // LUI
                       opcode == 7'b0010111 || // AUIPC
                       opcode == 7'b0010011 || // ADDI ...
                      (opcode == 7'b0110011 && func7[0] == 1'b0)) ? // ADD ...
                       4'b0000 :
                      (opcode == 7'b0011011 || // ADDIW ...
                      (opcode == 7'b0111011 &&
                       func7[0] == 1'b0)) ? // ADDW ...
                       4'b0001 :
                      (opcode == 7'b1101111 || // JAL
                       opcode == 7'b1100111) ? // JALR
                       4'b0010 :
                      (opcode == 7'b0000011) ? // LOAD
                       4'b0011 :
                      (opcode == 7'b0110011 && (func3 == 3'b000 || func3 == 3'b001 || func3 == 3'b010 || func3 == 3'b011)) ? // MUL
                       4'b0100 :
                      (opcode == 7'b0111011 && func3 == 3'b000 && func7[0] == 1'b1) ? // MULW
                       4'b0101 :
                      (opcode == 7'b0110011 && (func3 == 3'b100 || func3 == 3'b101)) ? // DIV, DIVU
                       4'b0110 :
                      (opcode == 7'b0111011 && (func3 == 3'b100 || func3 == 3'b101)) ? // DIVW, DIVUW
                       4'b0111 :
                      (opcode == 7'b0110011 && (func3 == 3'b110 || func3 == 3'b111)) ? // REM, REMU
                       4'b1000 : 4'b1001;

    // wen_reg
    assign wen_reg = (opcode == 7'b0110111 || // LUI
                      opcode == 7'b0010111 || // AUIPC
                      opcode == 7'b1101111 || // JAL
                      opcode == 7'b1100111 || // JALR
                      opcode == 7'b0000011 || // LOAD
                      opcode == 7'b0010011 || // ADDI ...
                      opcode == 7'b0110011 || // ADD ...
                      opcode == 7'b0011011 || // ADDIW ...
                      opcode == 7'b0111011 || // ADDW
                      opcode == 7'b0110011 || // MUL ...
                      opcode == 7'b0111011) ?  // MULW ...
                      1'b1 : 1'b0;

    // mul_type
    // 00 MUL
    // 01 MULH
    // 10 MULHSU
    // 11 MULHU
    assign mul_type = ((opcode == 7'b0110011 && func3 == 3'b000) || // MUL
                       (opcode == 7'b0111011 && func3 == 3'b000)) ? // MULW
                       2'b00 :
                      (opcode == 7'b0110011 && func3 == 3'b001) ? // MULH
                       2'b01 :
                      (opcode == 7'b0110011 && func3 == 3'b010) ? // MULHSU
                       2'b10 : 2'b11;

    assign div_type = (opcode == 7'b0110011 && func3 == 3'b100) ? 1'b0 : 1'b1;

    assign rem_type = (opcode == 7'b0110011 && func3 == 3'b110) ? 1'b0 : 1'b1;
endmodule
