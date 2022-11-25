#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtop.h"

#define CONFIG_MBASE 0x80000000
#define CONFIG_MSIZE 0x8000000

#define SIM_END_TIME 100
vluint64_t sim_time = 0;
static uint8_t pmem[CONFIG_MSIZE] = {};
uint8_t* guest_to_host(uint64_t paddr) { return pmem + paddr - CONFIG_MBASE; }

static inline uint64_t host_read(void *addr, int len) {
  switch (len) {
    case 1: return *(uint8_t  *)addr;
    case 2: return *(uint16_t *)addr;
    case 4: return *(uint32_t *)addr;
    case 8: return *(uint64_t *)addr;
    default: return 0;
  }
}

static inline void host_write(void *addr, int len, uint64_t data) {
  switch (len) {
    case 1: *(uint8_t  *)addr = data; return;
    case 2: *(uint16_t *)addr = data; return;
    case 4: *(uint32_t *)addr = data; return;
    case 8: *(uint64_t *)addr = data; return;
    default: return;
  }
}

static uint64_t pmem_read(uint64_t addr, int len) {
  uint64_t ret = host_read(guest_to_host(addr), len);
  return ret;
}

static void pmem_write(uint64_t addr, int len, uint64_t data) {
  host_write(guest_to_host(addr), len, data);
}

void init_mem() {
    pmem_write(0x80000004, 4, 0x00108113); // immi = 1, rs1 = 1, rd = 2 addi 
    pmem_write(0x80000008, 4, 0x00208113); // immi = 1, rs1 = 1, rd = 2 addi 
    pmem_write(0x8000000c, 4, 0x00308113); // immi = 1, rs1 = 1, rd = 2 addi 
}

void pc_reset (Vtop *dut, vluint64_t &sim_time) {
    dut -> rst = 0;
    if (sim_time <= 4) {
        dut -> rst = 1;
    }
}


int main() {
    Vtop *dut = new Vtop;
    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    init_mem();
    while (sim_time < SIM_END_TIME) {
        pc_reset(dut, sim_time);

        dut -> clk ^= 1;
        dut -> eval();

        if (dut->clk == 1 && sim_time >= 5) {
            dut -> inst = pmem_read(dut -> pc_val, 4);
        }

        m_trace -> dump(sim_time);
        sim_time++;
    }
    m_trace -> close();
    delete dut;
    exit(EXIT_SUCCESS);
}
