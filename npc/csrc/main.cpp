#include <cstdio>
#include <verilator.h>
#include "Vtop.h"
#include "Vtop__Dpi.h"

vluint64_t sim_time = 0;
svLogic is_ebreak = 0;
svLogic trap_state = 2;

Vtop *dut = new Vtop;
VerilatedVcdC *m_trace = new VerilatedVcdC;

void init_npc_monitor(char *img, char *elf);
void npc_sdb_mainloop(void);

const char *log_path = "/home/ctr/ysyx-workbench/npc/npc-log.txt";
FILE *fp = fopen(log_path, "w");

int main(int argc, char *argv[]) {
    Verilated::traceEverOn(true);
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    const svScope scope = svGetScopeFromName("TOP.top");
    assert(scope);
    svSetScope(scope);
    init_npc_monitor(argv[1], argv[2]);
    npc_sdb_mainloop();
    fclose(fp); 
    m_trace -> close();
    delete dut;
}
