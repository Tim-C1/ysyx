#ifndef __MEMORY_H__
#define __MEMORY_H__
#include <common.h>

#define CONFIG_MBASE 0x80000000
#define CONFIG_MSIZE 0x8000000
#define RESET_VECTOR CONFIG_MBASE

uint8_t* guest_to_host(uint64_t paddr);
uint64_t pmem_read(uint64_t addr, int len); 
void pmem_write(uint64_t addr, int len, uint64_t data); 
#endif
