#ifndef __DIFFTEST_H__
#define __DIFFTEST_H__
#include <common.h>
void difftest_skip_ref();
void difftest_step(vaddr_t pc, vaddr_t npc);
#endif
