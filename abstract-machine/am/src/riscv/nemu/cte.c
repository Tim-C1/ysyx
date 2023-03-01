#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
      case (0xb):
          if (c->gpr[17] == -1) {
              ev.event = EVENT_YIELD;
          } else if (c->gpr[17] == 1 ||
                     c->gpr[17] == 0 ||
                     c->gpr[17] == 4 ||
                     c->gpr[17] == 9 ||
                     c->gpr[17] == 2 ||
                     c->gpr[17] == 3 ||
                     c->gpr[17] == 4 ||
                     c->gpr[17] == 7 ||
                     c->gpr[17] == 8 ||
                     c->gpr[17] == 19) {
              ev.event = EVENT_SYSCALL;
          } else {
              printf("Please handle me, a7=%d\n", c->gpr[17]);
          }
          c->mepc = c->mepc + 4;
          break;
      default:
          printf("%s\t0x%d\n", "mcause", c->mcause);
          // printf("%s\t0x%d\n", "mepc", c->mepc);
          ev.event = EVENT_ERROR; break;
    }

    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  return NULL;
}

void yield() {
  asm volatile("li a7, -1; ecall");
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
