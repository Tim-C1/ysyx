// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vtop__Syms.h"
#include "Vtop___024root.h"

void Vtop___024root____Vdpiexp_top__DOT__ebreak_detect_TOP(Vtop__Syms* __restrict vlSymsp, CData/*0:0*/ &is_ebreak) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root____Vdpiexp_top__DOT__ebreak_detect_TOP\n"); );
    // Init
    // Body
    is_ebreak = (0x100073U == vlSymsp->TOP.inst);
}
