#include <cassert>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtop.h"
#include "Vtop__Dpi.h"
#include "svdpi.h"

#define CONFIG_MBASE 0x80000000
#define CONFIG_MSIZE 0x8000000
#define RESET_VECTOR CONFIG_MBASE

#define ASNI_FG_RED     "\33[1;31m"
#define ASNI_FG_GREEN   "\33[1;32m"
#define ASNI_NONE       "\33[0m"
#define ASNI_FMT(str, fmt) fmt str ASNI_NONE

#define SIM_END_TIME 1000
vluint64_t sim_time = 0;
svLogic is_ebreak = 0;
svLogic trap_state = 2;
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
    pmem_write(0x80000008, 4, 0x00208113); // immi = 2, rs1 = 1, rd = 2 addi 
    pmem_write(0x8000000c, 4, 0x00308113); // immi = 3, rs1 = 1, rd = 2 addi 
    pmem_write(0x80000010, 4, 0x00408113); // immi = 4, rs1 = 1, rd = 2 addi 
    pmem_write(0x80000014, 4, 0x00100073); // ebreak
}

void load_img(char *img_path){
    if (img_path == NULL) {
        printf("no img is given\n");
        assert(0);
    }
    FILE *fp = fopen(img_path, "rb");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    fseek(fp, 0 , SEEK_SET);
    int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
    assert(ret == 1);

    pmem_write(CONFIG_MBASE + size, 4, 0x00100073);

    fclose(fp);
}

void pc_reset (Vtop *dut, vluint64_t &sim_time) {
    dut -> rst = 0;
    if (sim_time <= 2) {
        dut -> rst = 1;
    }
}

void npc_trap (svLogic *trap_state, uint32_t pc) {
    if (*trap_state == 0) {
        printf("%s, AT PC = 0x%08x\n", ASNI_FMT("Hit Good Trap", ASNI_FG_GREEN), pc);
        exit(EXIT_SUCCESS);
    } else if (*trap_state == 1) {
        printf("%s, AT PC = 0x%08x\n", ASNI_FMT("Hit bad Trap", ASNI_FG_RED), pc);
        exit(EXIT_SUCCESS);
    } else {
        printf("Program is still running, check trap functions \n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    Vtop *dut = new Vtop;
    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    const svScope scope = svGetScopeFromName("TOP.top");
    assert(scope);  // Check for nullptr if scope not found
    svSetScope(scope);
    load_img(argv[1]); // $(IMG)
    while (sim_time < SIM_END_TIME) {
        dut -> clk ^= 1;
        dut -> eval();
        ebreak_detect(&is_ebreak);
        if (is_ebreak == 1) {
            trap(&trap_state);
            npc_trap(&trap_state, dut -> pc_val);
        }
        pc_reset(dut, sim_time);

        if (dut->clk == 1 && sim_time >= 2) {
            dut -> inst = pmem_read(dut -> pc_val, 4);
        }
        m_trace -> dump(sim_time);
        sim_time++;
    }
    m_trace -> close();
    delete dut;
}