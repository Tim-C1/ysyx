#include <bits/types/FILE.h>
#include <cpu.h>
#include <cstdio>
#include <memory.h>
#include <common.h>
#include <verilator.h>
#include "Vtop.h"

extern svLogic is_ebreak;
extern svLogic trap_state;

extern Vtop *dut;
extern vluint64_t sim_time;
extern VerilatedVcdC *m_trace;

static char log_buf[128];
extern FILE *fp;
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
            printf("%s\n", log_buf);
            fprintf(fp, "%s\n", log_buf);
#endif
        }
        m_trace -> dump(sim_time);
        sim_time++;
    }
}
