#ifndef __CPU_H__
#define __CPU_H__
#include "Vtop.h"
#include "Vtop__Dpi.h"
#include "svdpi.h"
#include <common.h>

#define SIM_BEGIN 5
#define FIRST_INST_EXECUTION 7

typedef struct {
  uint64_t gpr[32];
  uint64_t pc;
  uint64_t mepc;
  uint64_t mstatus;
  uint64_t mcause;
  uint64_t mtvec;
} riscv64_NPC_CPU_state;

extern riscv64_NPC_CPU_state cpu;
#endif
