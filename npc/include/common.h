#ifndef __COMMON_H__
#define __COMMON_H__
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include <conf.h>
#include <macro.h>

typedef uint64_t paddr_t;
typedef uint64_t vaddr_t;
typedef uint64_t word_t;
typedef uint16_t ioaddr_t;

#define FMT_WORD "0x%016lx"
#define FMT_PADDR "0x%016lx"

#include <debug.h>
#endif

