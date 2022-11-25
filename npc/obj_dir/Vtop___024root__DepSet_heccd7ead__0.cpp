// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_INLINE_OPT void Vtop___024root___sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___sequent__TOP__0\n"); );
    // Init
    QData/*63:0*/ top__DOT__gpr__DOT____Vlvbound_h40260bdd__0;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__gpr__DOT__rf__v0;
    QData/*63:0*/ __Vdlyvval__top__DOT__gpr__DOT__rf__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__gpr__DOT__rf__v0;
    // Body
    __Vdlyvset__top__DOT__gpr__DOT__rf__v0 = 0U;
    vlSelf->pc_val = ((IData)(vlSelf->rst) ? 0x80000000ULL
                       : (4ULL + vlSelf->pc_val));
    vlSelf->r1 = vlSelf->top__DOT__gpr__DOT__rf[1U];
    vlSelf->r2 = vlSelf->top__DOT__gpr__DOT__rf[2U];
    top__DOT__gpr__DOT____Vlvbound_h40260bdd__0 = vlSelf->top__DOT__result;
    if ((4U >= (7U & (vlSelf->inst >> 7U)))) {
        __Vdlyvval__top__DOT__gpr__DOT__rf__v0 = top__DOT__gpr__DOT____Vlvbound_h40260bdd__0;
        __Vdlyvset__top__DOT__gpr__DOT__rf__v0 = 1U;
        __Vdlyvdim0__top__DOT__gpr__DOT__rf__v0 = (7U 
                                                   & (vlSelf->inst 
                                                      >> 7U));
    }
    if (__Vdlyvset__top__DOT__gpr__DOT__rf__v0) {
        vlSelf->top__DOT__gpr__DOT__rf[__Vdlyvdim0__top__DOT__gpr__DOT__rf__v0] 
            = __Vdlyvval__top__DOT__gpr__DOT__rf__v0;
    }
}

VL_INLINE_OPT void Vtop___024root___combo__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___combo__TOP__0\n"); );
    // Body
    vlSelf->top__DOT__result = (((4U >= (7U & (vlSelf->inst 
                                               >> 0xfU)))
                                  ? vlSelf->top__DOT__gpr__DOT__rf
                                 [(7U & (vlSelf->inst 
                                         >> 0xfU))]
                                  : 0ULL) + (((- (QData)((IData)(
                                                                 (vlSelf->inst 
                                                                  >> 0x1fU)))) 
                                              << 0xcU) 
                                             | (QData)((IData)(
                                                               (vlSelf->inst 
                                                                >> 0x14U)))));
}

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        Vtop___024root___sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
    Vtop___024root___combo__TOP__0(vlSelf);
    // Final
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
