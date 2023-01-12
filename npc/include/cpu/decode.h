#ifndef __DECODE_H__
#define __DECODE_H__
#define BITMASK(bits) ((1ull << (bits)) - 1)
#define BITS(x, hi, lo) (((x) >> (lo)) & BITMASK((hi) - (lo) + 1)) // similar to x[hi:lo] in verilog
#define SEXT(x, len) ({ struct { int64_t n : len; } __x = { .n = static_cast<int64_t>(x) }; (uint64_t)__x.n; })
#define R(i) cpu_gpr[i]
#endif
