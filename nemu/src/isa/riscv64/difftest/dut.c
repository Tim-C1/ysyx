#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  bool gpr_chk = true;
  bool pc_chk = true;
  bool mtvec_chk = true;
  for (int i = 0; i < 32; i++) {
      if (cpu.gpr[i] != ref_r->gpr[i]) {
          Log("different at GPR[%d]\n", i);
          gpr_chk = false;
      }
  }
  if (cpu.pc != ref_r->pc) {
      Log("different at pc\n");
      pc_chk = false;
  }
  if (cpu.mtvec != ref_r->mtvec) {
      Log("different at MTVEC");
      mtvec_chk = false;
  }
  return gpr_chk && pc_chk && mtvec_chk;
}

void isa_difftest_attach() {
}
