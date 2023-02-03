#include <memory.h>
#include <device.h>

static uint8_t pmem[CONFIG_MSIZE] = {};
uint8_t *guest_to_host(uint64_t paddr) { return pmem + paddr - CONFIG_MBASE; }
extern uint64_t get_time();

static inline uint64_t host_read(void *addr, int len) {
  switch (len) {
  case 1:
    return *(uint8_t *)addr;
  case 2:
    return *(uint16_t *)addr; case 4:
    return *(uint32_t *)addr;
  case 8:
    return *(uint64_t *)addr;
  default:
    return 0;
  }
}

static inline void host_write(void *addr, int len, uint64_t data) {
  switch (len) {
  case 1:
    *(uint8_t *)addr = data;
    return;
  case 2:
    *(uint16_t *)addr = data;
    return;
  case 4:
    *(uint32_t *)addr = data;
    return;
  case 8:
    *(uint64_t *)addr = data;
    return;
  default:
    return;
  }
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

extern "C" void pmem_read(long long raddr, long long *rdata) {
    /* always read from "raddr & ~0x7ull" 8 bytes to rdata */
#ifdef CONFIG_MTRACE
    printf("MEM READ: addr: %#016llx, data: %#016llx\n", raddr, *rdata);
#endif
    if ((uint64_t)raddr == RTC_BASE) {
        *rdata = get_time();
    } else {
        *rdata = pmem_read(raddr & ~0x7ull, 8);
    }
}

extern "C" void pmem_write(long long waddr, long long wdata, char wmask) {
    /* write to "waddr & ~0x7ull" 8 bytes wdata according to wmask */
    int len = 0;
    int loc = 0;
    unsigned char wmask_u = (unsigned char) wmask;
    uint64_t padd_waddr = waddr & ~0x7ull;
#ifdef CONFIG_MTRACE
    printf("MEM WRITE: addr: %#016llx, len: %d, data: %#016llx\n", waddr + loc, len, wdata);
#endif
    if ((uint64_t)waddr == SERIAL_BASE) {
        putchar((int)wdata);
    } else {
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
        pmem_write(padd_waddr + loc, len, wdata);
    }
}
