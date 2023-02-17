#include <isa.h>
#include "local-include/reg.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
  int i;
  for (i = 0; i < 32; i++) {
    printf("%s\t0x%016lx\n", regs[i], cpu.gpr[i]);    
  }
  printf("%s\t0x%016lx\n", "pc", cpu.pc);
  printf("%s\t0x%016lx\n", "mcause", cpu.mcause);
  printf("%s\t0x%016lx\n", "mepc", cpu.mepc);
  printf("%s\t0x%016lx\n", "mstatus", cpu.mstatus);
  printf("%s\t0x%016lx\n", "mtvec", cpu.mtvec);
}


word_t isa_reg_str2val(const char *s, bool *success) {
  for (int i = 0; i < 32; i++) {
      if (strcmp(regs[i], s) == 0) {
          return cpu.gpr[i];
      }
  }
  if (strcmp(s, "pc") == 0) {
      return cpu.pc;
  }
  printf("wrong register name: %s\n", s);
  return 0;
}
