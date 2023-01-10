// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Implementation of DPI export functions.
//
#include "Vtop.h"
#include "Vtop__Syms.h"
#include "verilated_dpi.h"


void Vtop::ebreak_detect(svLogic* is_ebreak) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root::ebreak_detect\n"); );
    // Init
    CData/*0:0*/ is_ebreak__Vcvt;
    // Body
    static int __Vfuncnum = -1;
    if (VL_UNLIKELY(__Vfuncnum == -1)) __Vfuncnum = Verilated::exportFuncNum("ebreak_detect");
    const VerilatedScope* __Vscopep = Verilated::dpiScope();
    Vtop__Vcb_ebreak_detect_t __Vcb = (Vtop__Vcb_ebreak_detect_t)(VerilatedScope::exportFind(__Vscopep, __Vfuncnum));
    (*__Vcb)((Vtop__Syms*)(__Vscopep->symsp()), is_ebreak__Vcvt);
    for (size_t is_ebreak__Vidx = 0; is_ebreak__Vidx < 1; ++is_ebreak__Vidx) *is_ebreak = is_ebreak__Vcvt;
}

void Vtop::trap(svLogic* trap_state) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root::trap\n"); );
    // Init
    CData/*0:0*/ trap_state__Vcvt;
    // Body
    static int __Vfuncnum = -1;
    if (VL_UNLIKELY(__Vfuncnum == -1)) __Vfuncnum = Verilated::exportFuncNum("trap");
    const VerilatedScope* __Vscopep = Verilated::dpiScope();
    Vtop__Vcb_trap_t __Vcb = (Vtop__Vcb_trap_t)(VerilatedScope::exportFind(__Vscopep, __Vfuncnum));
    (*__Vcb)((Vtop__Syms*)(__Vscopep->symsp()), trap_state__Vcvt);
    for (size_t trap_state__Vidx = 0; trap_state__Vidx < 1; ++trap_state__Vidx) *trap_state = trap_state__Vcvt;
}
