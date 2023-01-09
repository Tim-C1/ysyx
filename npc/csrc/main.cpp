#include <verilator.h>
#include "Vtop.h"
#include "Vtop__Dpi.h"
#include "svdpi.h"

vluint64_t sim_time = 0;
svLogic is_ebreak = 0;
svLogic trap_state = 2;

Vtop *dut = new Vtop;
VerilatedVcdC *m_trace = new VerilatedVcdC;

void init_npc_monitor(char *img);
void npc_sdb_mainloop(void);

int main(int argc, char *argv[]) {
    Verilated::traceEverOn(true);
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    const svScope scope = svGetScopeFromName("TOP.top");
    assert(scope);
    svSetScope(scope);
    init_npc_monitor(argv[1]);
    npc_sdb_mainloop();
    m_trace -> close();
    delete dut;
}
