#include <dlfcn.h>
#include <common.h>
#include <memory.h>
#include <cpu.h>
#include "difftest.h"
void (*ref_difftest_memcpy)(uint64_t addr, void *buf, size_t n, bool direction) = NULL;
void (*ref_difftest_regcpy)(void *dut, bool direction) = NULL;
void (*ref_difftest_exec)(uint64_t n) = NULL;
void (*ref_difftest_raise_intr)(uint64_t NO) = NULL;

extern svLogic trap_state;
extern NPC_state npc_state;

static bool is_skip_ref = false;
static int skip_dut_nr_inst = 0;

// this is used to let ref skip instructions which
// can not produce consistent behavior with NEMU
void difftest_skip_ref() {
  is_skip_ref = true;
  // If such an instruction is one of the instruction packing in QEMU
  // (see below), we end the process of catching up with QEMU's pc to
  // keep the consistent behavior in our best.
  // Note that this is still not perfect: if the packed instructions
  // already write some memory, and the incoming instruction in NEMU
  // will load that memory, we will encounter false negative. But such
  // situation is infrequent.
  skip_dut_nr_inst = 0;
}

static void show_ref_and_dut_regs(NPC_CPU_state *ref) {
    for (int i = 0; i < 32; i++) {
        printf("npc: gpr[%d] = 0x%0lx\tnemu: gpr[%d] = 0x%0lx\n", i, cpu.gpr[i], i, ref->gpr[i]);
    }
    printf("npc: pc = 0x%lx\tnemu: pc = 0x%lx\n", cpu.pc, ref->pc);
}

static void checkregs(NPC_CPU_state *ref, uint64_t pc) {
    int same = 1;
    for (int i = 0; i < 32; i++) {
        if (ref->gpr[i] != cpu.gpr[i]) {
            trap_state = 1;
            same = 0;
        }
    }
    if (ref->pc != cpu.pc) {
        trap_state = 1;
        same = 0;
    }
    if (!same) {
        npc_state.state= NPC_ABORT;
        npc_state.halt_pc = pc;
        show_ref_and_dut_regs(ref);
    }
}

void init_difftest(char *ref_so_file, long img_size, int port) {
  assert(ref_so_file != NULL);

  void *handle;
  handle = dlopen(ref_so_file, RTLD_LAZY);
  if (!handle) {
      printf("error: %s\n", dlerror());
  }
  assert(handle);

  ref_difftest_memcpy = dlsym(handle, "difftest_memcpy");
  assert(ref_difftest_memcpy);

  ref_difftest_regcpy = dlsym(handle, "difftest_regcpy");
  assert(ref_difftest_regcpy);

  ref_difftest_exec = dlsym(handle, "difftest_exec");
  assert(ref_difftest_exec);

  ref_difftest_raise_intr = dlsym(handle, "difftest_raise_intr");
  assert(ref_difftest_raise_intr);

  void (*ref_difftest_init)(int) = dlsym(handle, "difftest_init");
  assert(ref_difftest_init);

  printf("Differential testing: %s\n", ASNI_FMT("ON", ASNI_FG_GREEN));

  ref_difftest_init(port);
  ref_difftest_memcpy(RESET_VECTOR, guest_to_host(RESET_VECTOR), img_size, DIFFTEST_TO_REF);
  cpu.pc = 0x80000000;
  ref_difftest_regcpy(&cpu, DIFFTEST_TO_REF);
}

void difftest_step(uint64_t pc) {
  NPC_CPU_state ref_r;

  if (is_skip_ref) {
    // to skip the checking of an instruction, just copy the reg state to reference design
    ref_difftest_regcpy(&cpu, DIFFTEST_TO_REF);
    is_skip_ref = false;
    return;
  }

  ref_difftest_exec(1);
  ref_difftest_regcpy(&ref_r, DIFFTEST_TO_DUT);

  checkregs(&ref_r, pc);
}
