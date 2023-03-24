#include <memory.h>
#include <common.h>
#include <cpu.h>
#include <device/mmio.h>
#include <device.h>

static uint8_t pmem[CONFIG_MSIZE] = {};
uint8_t *guest_to_host(uint64_t paddr) { return pmem + paddr - CONFIG_MBASE; }
static void out_of_bound(paddr_t addr) {
  panic("address = " FMT_PADDR " is out of bound of pmem [" FMT_PADDR ", " FMT_PADDR ") at pc = " FMT_WORD,
      addr, CONFIG_MBASE, CONFIG_MBASE + CONFIG_MSIZE, cpu.pc);
}

uint64_t pmem_read(uint64_t addr, int len) {
  uint64_t ret = host_read(guest_to_host(addr), len);
  return ret;
}

void pmem_write(uint64_t addr, int len, uint64_t data) {
  host_write(guest_to_host(addr), len, data);
}

/* only use when IMG reading function not work for initializing the npc memory
 */
void init_mem() {
  pmem_write(0x80000004, 4, 0x00108113); // immi = 1, rs1 = 1, rd = 2 addi
  pmem_write(0x80000008, 4, 0x00208113); // immi = 2, rs1 = 1, rd = 2 addi
  pmem_write(0x8000000c, 4, 0x00308113); // immi = 3, rs1 = 1, rd = 2 addi
  pmem_write(0x80000010, 4, 0x00408113); // immi = 4, rs1 = 1, rd = 2 addi
  pmem_write(0x80000014, 4, 0x00100073); // ebreak
}

void scan_mem(char *args) {
  int length;
  uint64_t addr;
  char *arg1 = strtok(NULL, " ");
  char *arg2 = strtok(NULL, " ");

  sscanf(arg1, "%d", &length);
  sscanf(arg2, "%lx", &addr);

  for (int i = 0; i < length; i++) {
      printf("start: %#016lx, word: %#016lx\n", addr + 4*i, pmem_read(addr + 4*i, 4));
  }
}

word_t paddr_read(paddr_t addr, int len) {
  uint64_t data;
  if (likely(in_pmem(addr))) {
    data = pmem_read(addr, len);
    // printf("read address: " FMT_PADDR ", len: %d, at pc: 0x%lx, data: 0x%lx\n", addr, len, cpu.pc, data);
    return data;
  }
  return mmio_read(addr, len);
  out_of_bound(addr);
  return 0;
}

void paddr_write(paddr_t addr, int len, word_t data) {
  // printf("write address: " FMT_PADDR ", len: %d, data: %ld at pc: 0x%lx\n", addr, len, data, cpu.pc);
  if (likely(in_pmem(addr))) { pmem_write(addr, len, data); return; }
  mmio_write(addr, len, data); return;
  out_of_bound(addr);
}

extern "C" void pmem_read(long long raddr, long long *rdata) {
    /* always read from "raddr & ~0x7ull" 8 bytes to rdata */
    *rdata = paddr_read(raddr & ~0x7ull, 8);
}

extern "C" void pmem_write(long long waddr, long long wdata, char wmask) {
    /* write to "waddr & ~0x7ull" 8 bytes wdata according to wmask */
    int len = 0;
    int loc = 0;
    unsigned char wmask_u = (unsigned char) wmask;
    uint64_t padd_waddr = waddr & ~0x7ull;
    while (loc < 8) {
        bool shift_bit = wmask_u & (unsigned char) 1;
        if (shift_bit) {
            while (1) {
                if (wmask_u == 0) break;
                wmask_u = wmask_u >> 1;
                len++;
            }
            break;
        }     // find the byte location to store data;
        wmask_u >>= 1;
        loc++;
    }
    paddr_write(padd_waddr + loc, len, wdata);
}
