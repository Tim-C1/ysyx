#include <bits/types/FILE.h>
#include <cpu.h>
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

uint64_t *cpu_gpr = NULL;
extern "C" void set_gpr_ptr(const svOpenArrayHandle r) {
  cpu_gpr = (uint64_t *)(((VerilatedDpiOpenVar*)r)->datap());
}

static char log_buf[128];
extern FILE *fp;

static uint64_t immI(uint32_t i) { return SEXT(BITS(i, 31, 20), 12); }
static uint64_t immU(uint32_t i) { return SEXT(BITS(i, 31, 12), 20) << 12; }
static uint64_t immS(uint32_t i) { return (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); }
static uint64_t immJ(uint32_t i) { return (SEXT(BITS(i, 31, 31), 1) << 20) | (BITS(i, 19, 12) << 12) | (BITS(i, 20, 20) << 11) | (BITS(i, 30, 25) << 5) | (BITS(i, 24, 21) << 1); }
static uint64_t immB(uint32_t i) { return (SEXT(BITS(i, 31, 31), 1) << 12) | (BITS(i, 7, 7) << 11) | (BITS(i, 30, 25) << 5) | (BITS(i, 11, 8) << 1); }

/* wrap around code for ftrace */
#ifdef CONFIG_FTRACE
extern char *get_func_symbol_by_address(uint64_t addr, int type);
typedef struct ftrace_info {
    uint64_t jump_addr;
    int jump_type; // 1 CALL; 2 RETURN
    char* func_name;
} ftrace_info; 

ftrace_info ftrace_buf[1024]; // store ftrace info
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

static int npc_trap (svLogic *trap_state, uint32_t pc) {
    if (*trap_state == 0) {
        printf("%s, AT PC = 0x%08x\n", ASNI_FMT("Hit Good Trap", ASNI_FG_GREEN), pc);
        return 0;
    } else if (*trap_state == 1) {
        printf("%s, AT PC = 0x%08x\n", ASNI_FMT("Hit bad Trap", ASNI_FG_RED), pc);
        return 1;
    } else {
        printf("Program is still running, check trap functions \n");
        return 1;
    }
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
        ebreak_detect(&is_ebreak);
        if (is_ebreak == 1) {
            trap(&trap_state);
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
            int trap_flag = npc_trap(&trap_state, dut -> pc_val);
            if (trap_flag == 0) {
                break;
            } else {
                exit(EXIT_FAILURE);
            }
        }
        pc_reset(dut, sim_time);

        if (dut->clk == 1 && sim_time >= SIM_BEGIN) {
            dut -> inst = pmem_read(dut -> pc_val, 4);
            i++;
#ifdef CONFIG_ITRACE
            char *p = log_buf;
            uint8_t *inst = (uint8_t *)&(dut -> inst);
            for (int i = 0; i < 4; i++) {
                p += sprintf(p, " %02x", inst[i]);
            }
            memset(p, ' ', 1);
            p++;
            void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
            disassemble(p, log_buf + sizeof(log_buf) - p, dut -> pc_val, (uint8_t *)&dut->inst, 4);
            fprintf(fp, "%s\n", log_buf);
#endif
#ifdef CONFIG_FTRACE
            save_ftrace_info(dut->inst, dut->pc_val);
#endif
        }
        m_trace -> dump(sim_time);
        sim_time++;
    }
}
