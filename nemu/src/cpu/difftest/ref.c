#include <isa.h>
#include <cpu/cpu.h>
#include <difftest-def.h>
#include <memory/paddr.h>

/* DUT buf, REF addr */
void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) {
    if (direction == DIFFTEST_TO_REF) {
        memcpy(guest_to_host(addr), buf, n);
    } else {
        memcpy(buf, guest_to_host(addr), n); 
    }
}

void difftest_regcpy(void *dut, bool direction) {
    CPU_state *dut_r = (CPU_state *)dut;
    if (direction == DIFFTEST_TO_REF) {
        for (int i = 0; i < 32; i ++) {
            cpu.gpr[i] = dut_r->gpr[i];
        }
        cpu.pc = dut_r->pc;
        cpu.mepc = dut_r->mepc;
        cpu.mstatus = dut_r->mstatus;
        cpu.mcause = dut_r->mcause;
        cpu.mtvec = dut_r->mtvec;
    } else {
        for (int i = 0; i < 32; i++) {
            dut_r->gpr[i] = cpu.gpr[i];
        }     
        dut_r->pc = cpu.pc;
        dut_r->mepc = cpu.mepc;
        dut_r->mstatus = cpu.mstatus;
        dut_r->mcause = cpu.mcause;
        dut_r->mtvec = cpu.mtvec;
    }
}

void difftest_exec(uint64_t n) {
    cpu_exec(n);
}

void difftest_raise_intr(word_t NO) {
  assert(0);
}

void difftest_init(int port) {
  /* Perform ISA dependent initialization. */
  init_isa();
}
