#include <bits/types/FILE.h>
#include <cpu.h>
#include <cstdint>
#include <decode.h>
#include <memory.h>
#include <common.h>
#include <verilator.h>
#include "Vtop.h"

extern svLogic is_ebreak;
extern svLogic trap_state;
extern Vtop *dut;
extern vluint64_t sim_time;
extern VerilatedVcdC *m_trace;
extern FILE *log_fp;
uint64_t *cpu_gpr = NULL;
extern "C" void set_gpr_ptr(const svOpenArrayHandle r) {
  cpu_gpr = (uint64_t *)(((VerilatedDpiOpenVar*)r)->datap());
}
extern void difftest_step(uint64_t pc);
extern void difftest_skip_ref();

extern void device_update();
extern NPC_state npc_state;

static char log_buf[128];
static uint64_t pc_p = 0x80000000; // save previous pc value for difftest to show the wrong instruction position
static uint64_t immI(uint32_t i) { return SEXT(BITS(i, 31, 20), 12); }
static uint64_t immU(uint32_t i) { return SEXT(BITS(i, 31, 12), 20) << 12; }
static uint64_t immS(uint32_t i) { return (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); }
static uint64_t immJ(uint32_t i) { return (SEXT(BITS(i, 31, 31), 1) << 20) | (BITS(i, 19, 12) << 12) | (BITS(i, 20, 20) << 11) | (BITS(i, 30, 25) << 5) | (BITS(i, 24, 21) << 1); }
static uint64_t immB(uint32_t i) { return (SEXT(BITS(i, 31, 31), 1) << 12) | (BITS(i, 7, 7) << 11) | (BITS(i, 30, 25) << 5) | (BITS(i, 11, 8) << 1); }

NPC_CPU_state cpu = {};
void reg_display(void) {
  int i;
  assert(cpu_gpr);
  for (i = 0; i < 32; i++) {
    printf("gpr[%d] = 0x%lx\n", i, cpu_gpr[i]);
  }
}

/* wrap around code for ftrace */
#ifdef CONFIG_FTRACE
extern char *get_func_symbol_by_address(uint64_t addr, int type);
typedef struct ftrace_info {
    uint64_t jump_addr;
    int jump_type; // 1 CALL; 2 RETURN
    char* func_name;
} ftrace_info;

ftrace_info ftrace_buf[102400]; // store ftrace info
int ftrace_info_cnt = 0;
static int is_ret(uint32_t s) { return (s == 0x8067); } // RET
static int is_jump(uint32_t s) {
    if (BITS(s, 6, 0) == (uint32_t)0b1101111) {
        return 1; // JAL
    } else if (BITS(s, 6, 0) == (uint32_t)0b1100111) {
        return 2; // JALR
    } else {
        return -1; // NOT JUMP
    }
}

static void save_ftrace_info(uint32_t inst, uint32_t pc) {
  if (is_ret(inst)) {
      ftrace_buf[ftrace_info_cnt].jump_addr = pc;
      ftrace_buf[ftrace_info_cnt].jump_type = 2;
      char *sym_name = get_func_symbol_by_address(ftrace_buf[ftrace_info_cnt].jump_addr, 2);
      ftrace_buf[ftrace_info_cnt].func_name = sym_name;
      ftrace_info_cnt++;
      return;
  }
  if (is_jump(inst) == 1) {
      ftrace_buf[ftrace_info_cnt].jump_addr = (uint64_t)(pc + immJ(inst));
      ftrace_buf[ftrace_info_cnt].jump_type = 1;
      char *sym_name = get_func_symbol_by_address(ftrace_buf[ftrace_info_cnt].jump_addr, 1);
      ftrace_buf[ftrace_info_cnt].func_name = sym_name;
      ftrace_info_cnt++;
  } else if (is_jump(inst) == 2) {
      ftrace_buf[ftrace_info_cnt].jump_addr = (uint64_t)((R(BITS(inst, 19, 15)) + immI(inst)) & ~(1ull));
      ftrace_buf[ftrace_info_cnt].jump_type = 1;
      char *sym_name = get_func_symbol_by_address(ftrace_buf[ftrace_info_cnt].jump_addr, 1);
      ftrace_buf[ftrace_info_cnt].func_name = sym_name;
      ftrace_info_cnt++;
  } else {
  }
  return;
}
#endif
/* wrap around code for ftrace */

static void save_reg(uint64_t pc, uint64_t mepc, uint64_t mtvec, uint64_t mstatus, uint64_t mcause) {
    for (int i = 0; i < 32; i++) {
        cpu.gpr[i] = cpu_gpr[i];
    }
    cpu.pc = pc;
    cpu.mepc = mepc;
    cpu.mtvec = mtvec;
    cpu.mstatus = mstatus;
    cpu.mcause = mcause;
}

static void pc_reset (Vtop *dut, vluint64_t &sim_time) {
    dut -> rst = 0;
    if (sim_time < SIM_BEGIN) {
        dut -> rst = 1;
    }
}

void exec(uint32_t num) {
    int i = 0;
    while (i < num) {
        dut -> clk ^= 1;
        dut -> eval();
        if (dut->clk == 1 && sim_time >= 8) { // finish executing one instruction
            save_reg(dut->pc_val, dut->mepc_value, dut->mtvec_value, dut->mstatus_value, dut->mcause_value);
            difftest_step(pc_p);
            pc_p = cpu.pc;
        }
        ebreak_detect(&is_ebreak);
        if (is_ebreak == 1) {
            trap(&trap_state);
            npc_state.state = NPC_END;
            npc_state.halt_ret = trap_state;
            npc_state.halt_pc = dut->pc_val;
            break;
        }
        pc_reset(dut, sim_time);

        if (dut->clk == 1 && sim_time >= SIM_BEGIN) {
            uint32_t instruction = pmem_read(cpu.pc, 4);
            i++;
#ifdef CONFIG_ITRACE
            char *p = log_buf;
            uint8_t *inst = (uint8_t *)&(instruction);
            for (int i = 0; i < 4; i++) {
                p += sprintf(p, " %02x", inst[i]);
            }
            memset(p, ' ', 1);
            p++;
            void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
            disassemble(p, log_buf + sizeof(log_buf) - p, dut -> pc_val, (uint8_t *)&instruction, 4);
            fprintf(log_fp, "cpu.pc: 0x%lx, %s\n", dut->pc_val, log_buf);
#endif
#ifdef CONFIG_FTRACE
            save_ftrace_info(instruction, dut->pc_val);
#endif
        }
        // m_trace -> dump(sim_time);
        sim_time++;
    }
}

void execute(uint32_t num) {
    for (;num > 0; num --) {
        exec(1);
        if (npc_state.state != NPC_RUNNING) {
            break;
        }
        device_update();
    }
}

void npc_exec(uint32_t num) {
    switch (npc_state.state) {
        case NPC_END: case NPC_ABORT:
          printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
          return;
        default: npc_state.state = NPC_RUNNING;
    }
    execute(num);
#ifdef CONFIG_FTRACE
    for (int i = 0; i < ftrace_info_cnt; i++) {
        ftrace_info ftrace_info = ftrace_buf[i];
        if (ftrace_info.func_name != NULL) {
            switch (ftrace_info.jump_type) {
                case 1: printf("CALL (%s@%#8lx)\n", ftrace_info.func_name, ftrace_info.jump_addr); break;
                case 2: printf("RET (%s@%#8lx)\n", ftrace_info.func_name, ftrace_info.jump_addr); break;
                default: break;
            }
        }
    }
#endif
    switch (npc_state.state) {
        case NPC_RUNNING: npc_state.state = NPC_STOP; break;
        case NPC_ABORT: printf("npc %s at pc: 0x%016lx\n", ASNI_FMT("ABORT", ASNI_FG_RED), npc_state.halt_pc); break;
        case NPC_END: printf("npc %s at pc: 0x%016lx\n", ASNI_FMT("HIT GOOD TRAP", ASNI_FG_GREEN), npc_state.halt_pc);
    }
}
