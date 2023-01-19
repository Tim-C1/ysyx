#include <cstdio>
#include <verilator.h>
#include <cpu.h>
#include "Vtop.h"
#include "Vtop__Dpi.h"

vluint64_t sim_time = 0;
svLogic is_ebreak = 0;
svLogic trap_state = 2;

Vtop *dut = new Vtop;
VerilatedVcdC *m_trace = new VerilatedVcdC;

NPC_state npc_state = {.state = NPC_STOP};
void init_npc_monitor(char *img, char *elf, char *ref_so_file);
void npc_sdb_mainloop(void);

const char *log_path = "/home/ctr/ysyx-workbench/npc/npc-log.txt";
FILE *log_fp = fopen(log_path, "w");

int is_npc_exit_bad(void) {
    int good = (npc_state.state == NPC_END && (npc_state.halt_ret == 0));
    return !good;
}
int is_batch_mode = 0;

int main(int argc, char *argv[]) {
    Verilated::traceEverOn(true);
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    const svScope scope = svGetScopeFromName("TOP.top");
    assert(scope);
    svSetScope(scope);
    init_npc_monitor(argv[1], argv[2], argv[3]);
    if (strcmp(argv[4], "batch") == 0) {
        is_batch_mode = 1;
    }
    npc_sdb_mainloop();
    fclose(log_fp);
    m_trace -> close();
    delete dut;
    return is_npc_exit_bad();
}
