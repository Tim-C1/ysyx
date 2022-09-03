#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"
#include "nvboard.h"

static TOP_NAME dut;

void nvboard_bind_all_pins(Vtop* top);

VerilatedContext* contextp = new VerilatedContext;

VerilatedVcdC* tfp = new VerilatedVcdC;

Vtop* top = new Vtop;

contextp->traceEverOn(true);
top->trace(tfp, 0);
tfp->open("build/waves/Vtop.vcd");

int cnt = 1;

int main() {
  nvboard_bind_all_pins(&dut);
  nvboard_init();

	while (cnt <= 20) {
	  int a = rand() & 1;
	  int b = rand() & 1;
	  top->a = a;
	  top->b = b;
	  top->eval();
	  contextp->timeInc(1);
	  tfp->dump(contextp->time());
  	  nvboard_update();
	  printf("a = %d, b = %d, f = %d\n", a, b, top->f);
	  assert(top->f == a ^ b);
	}
}
