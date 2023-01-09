#include <memory.h>

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

uint64_t pmem_read(uint64_t addr, int len) {
  uint64_t ret = host_read(guest_to_host(addr), len);
  return ret;
}

void pmem_write(uint64_t addr, int len, uint64_t data) {
  host_write(guest_to_host(addr), len, data);
}

void init_mem() {
    pmem_write(0x80000004, 4, 0x00108113); // immi = 1, rs1 = 1, rd = 2 addi 
    pmem_write(0x80000008, 4, 0x00208113); // immi = 2, rs1 = 1, rd = 2 addi 
    pmem_write(0x8000000c, 4, 0x00308113); // immi = 3, rs1 = 1, rd = 2 addi 
    pmem_write(0x80000010, 4, 0x00408113); // immi = 4, rs1 = 1, rd = 2 addi 
    pmem_write(0x80000014, 4, 0x00100073); // ebreak
}
