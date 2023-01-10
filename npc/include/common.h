#ifndef __COMMON_H__
#define __COMMON_H__
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>

/* terminal color */
#define ASNI_FG_RED     "\33[1;31m"
#define ASNI_FG_GREEN   "\33[1;32m"
#define ASNI_NONE       "\33[0m"
#define ASNI_FMT(str, fmt) fmt str ASNI_NONE
#endif

