// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vtop___024root.h"

VL_INLINE_OPT void Vtop___024root___combo__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___combo__TOP__0\n"); );
    // Body
    if ((0x40U & vlSelf->inst)) {
        if ((0x20U & vlSelf->inst)) {
            if ((0x10U & vlSelf->inst)) {
                vlSelf->top__DOT__immi_sext = 0ULL;
                vlSelf->top__DOT__rs1 = (0x1fU & 0U);
            } else if ((8U & vlSelf->inst)) {
                vlSelf->top__DOT__immi_sext = ((4U 
                                                & vlSelf->inst)
                                                ? (
                                                   (2U 
                                                    & vlSelf->inst)
                                                    ? 
                                                   ((1U 
                                                     & vlSelf->inst)
                                                     ? 
                                                    (((- (QData)((IData)(
                                                                         (vlSelf->inst 
                                                                          >> 0x1fU)))) 
                                                      << 0x14U) 
                                                     | (QData)((IData)(
                                                                       ((0xff000U 
                                                                         & vlSelf->inst) 
                                                                        | ((0x800U 
                                                                            & (vlSelf->inst 
                                                                               >> 9U)) 
                                                                           | ((0x7e0U 
                                                                               & (vlSelf->inst 
                                                                                >> 0x14U)) 
                                                                              | (0x1eU 
                                                                                & (vlSelf->inst 
                                                                                >> 0x14U))))))))
                                                     : 0ULL)
                                                    : 0ULL)
                                                : 0ULL);
                vlSelf->top__DOT__rs1 = (0x1fU & 0U);
            } else if ((4U & vlSelf->inst)) {
                if ((2U & vlSelf->inst)) {
                    if ((1U & vlSelf->inst)) {
                        vlSelf->top__DOT__immi_sext 
                            = (((- (QData)((IData)(
                                                   (vlSelf->inst 
                                                    >> 0x1fU)))) 
                                << 0xcU) | (QData)((IData)(
                                                           (vlSelf->inst 
                                                            >> 0x14U))));
                        vlSelf->top__DOT__rs1 = (0x1fU 
                                                 & (vlSelf->inst 
                                                    >> 0xfU));
                    } else {
                        vlSelf->top__DOT__immi_sext = 0ULL;
                        vlSelf->top__DOT__rs1 = (0x1fU 
                                                 & 0U);
                    }
                } else {
                    vlSelf->top__DOT__immi_sext = 0ULL;
                    vlSelf->top__DOT__rs1 = (0x1fU 
                                             & 0U);
                }
            } else {
                vlSelf->top__DOT__immi_sext = 0ULL;
                vlSelf->top__DOT__rs1 = (0x1fU & 0U);
            }
        } else {
            vlSelf->top__DOT__immi_sext = 0ULL;
            vlSelf->top__DOT__rs1 = (0x1fU & 0U);
        }
    } else if ((0x20U & vlSelf->inst)) {
        vlSelf->top__DOT__immi_sext = ((0x10U & vlSelf->inst)
                                        ? ((8U & vlSelf->inst)
                                            ? 0ULL : 
                                           ((4U & vlSelf->inst)
                                             ? ((2U 
                                                 & vlSelf->inst)
                                                 ? 
                                                ((1U 
                                                  & vlSelf->inst)
                                                  ? 
                                                 (((QData)((IData)(
                                                                   (- (IData)(
                                                                              (vlSelf->inst 
                                                                               >> 0x1fU))))) 
                                                   << 0x20U) 
                                                  | (QData)((IData)(
                                                                    (0xfffff000U 
                                                                     & vlSelf->inst))))
                                                  : 0ULL)
                                                 : 0ULL)
                                             : 0ULL))
                                        : 0ULL);
        vlSelf->top__DOT__rs1 = (0x1fU & 0U);
    } else if ((0x10U & vlSelf->inst)) {
        if ((8U & vlSelf->inst)) {
            vlSelf->top__DOT__immi_sext = 0ULL;
            vlSelf->top__DOT__rs1 = (0x1fU & 0U);
        } else if ((4U & vlSelf->inst)) {
            vlSelf->top__DOT__immi_sext = ((2U & vlSelf->inst)
                                            ? ((1U 
                                                & vlSelf->inst)
                                                ? (
                                                   ((QData)((IData)(
                                                                    (- (IData)(
                                                                               (vlSelf->inst 
                                                                                >> 0x1fU))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     (0xfffff000U 
                                                                      & vlSelf->inst))))
                                                : 0ULL)
                                            : 0ULL);
            vlSelf->top__DOT__rs1 = (0x1fU & 0U);
        } else if ((2U & vlSelf->inst)) {
            if ((1U & vlSelf->inst)) {
                vlSelf->top__DOT__immi_sext = (((- (QData)((IData)(
                                                                   (vlSelf->inst 
                                                                    >> 0x1fU)))) 
                                                << 0xcU) 
                                               | (QData)((IData)(
                                                                 (vlSelf->inst 
                                                                  >> 0x14U))));
                vlSelf->top__DOT__rs1 = (0x1fU & (vlSelf->inst 
                                                  >> 0xfU));
            } else {
                vlSelf->top__DOT__immi_sext = 0ULL;
                vlSelf->top__DOT__rs1 = (0x1fU & 0U);
            }
        } else {
            vlSelf->top__DOT__immi_sext = 0ULL;
            vlSelf->top__DOT__rs1 = (0x1fU & 0U);
        }
    } else {
        vlSelf->top__DOT__immi_sext = 0ULL;
        vlSelf->top__DOT__rs1 = (0x1fU & 0U);
    }
}

VL_INLINE_OPT void Vtop___024root___sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___sequent__TOP__0\n"); );
    // Init
    CData/*4:0*/ __Vdlyvdim0__top__DOT__gpr__DOT__rf__v0;
    QData/*63:0*/ __Vdlyvval__top__DOT__gpr__DOT__rf__v0;
    // Body
    vlSelf->pc_val = ((IData)(vlSelf->rst) ? 0x7ffffffcULL
                       : ((1U & (IData)(((0x60U == 
                                          (0x70U & vlSelf->inst)) 
                                         & ((8U & vlSelf->inst)
                                             ? (IData)(
                                                       (7U 
                                                        == 
                                                        (7U 
                                                         & vlSelf->inst)))
                                             : (IData)(
                                                       (7U 
                                                        == 
                                                        (7U 
                                                         & vlSelf->inst)))))))
                           ? vlSelf->top__DOT__npc : 
                          (4ULL + vlSelf->pc_val)));
    __Vdlyvval__top__DOT__gpr__DOT__rf__v0 = vlSelf->result;
    __Vdlyvdim0__top__DOT__gpr__DOT__rf__v0 = vlSelf->top__DOT__rd;
    vlSelf->top__DOT__gpr__DOT__rf[__Vdlyvdim0__top__DOT__gpr__DOT__rf__v0] 
        = __Vdlyvval__top__DOT__gpr__DOT__rf__v0;
    vlSelf->rs1_reg = vlSelf->top__DOT__gpr__DOT__rf
        [1U];
}

VL_INLINE_OPT void Vtop___024root___combo__TOP__1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___combo__TOP__1\n"); );
    // Body
    vlSelf->top__DOT__rd = (0x1fU & ((0x40U & vlSelf->inst)
                                      ? ((0x20U & vlSelf->inst)
                                          ? ((0x10U 
                                              & vlSelf->inst)
                                              ? 0U : 
                                             ((8U & vlSelf->inst)
                                               ? ((4U 
                                                   & vlSelf->inst)
                                                   ? 
                                                  ((2U 
                                                    & vlSelf->inst)
                                                    ? 
                                                   ((1U 
                                                     & vlSelf->inst)
                                                     ? 
                                                    (vlSelf->inst 
                                                     >> 7U)
                                                     : 0U)
                                                    : 0U)
                                                   : 0U)
                                               : ((4U 
                                                   & vlSelf->inst)
                                                   ? 
                                                  ((2U 
                                                    & vlSelf->inst)
                                                    ? 
                                                   ((1U 
                                                     & vlSelf->inst)
                                                     ? 
                                                    (vlSelf->inst 
                                                     >> 7U)
                                                     : 0U)
                                                    : 0U)
                                                   : 0U)))
                                          : 0U) : (
                                                   (0x20U 
                                                    & vlSelf->inst)
                                                    ? 
                                                   ((0x10U 
                                                     & vlSelf->inst)
                                                     ? 
                                                    ((8U 
                                                      & vlSelf->inst)
                                                      ? 0U
                                                      : 
                                                     ((4U 
                                                       & vlSelf->inst)
                                                       ? 
                                                      ((2U 
                                                        & vlSelf->inst)
                                                        ? 
                                                       ((1U 
                                                         & vlSelf->inst)
                                                         ? 
                                                        (vlSelf->inst 
                                                         >> 7U)
                                                         : 0U)
                                                        : 0U)
                                                       : 0U))
                                                     : 0U)
                                                    : 
                                                   ((0x10U 
                                                     & vlSelf->inst)
                                                     ? 
                                                    ((8U 
                                                      & vlSelf->inst)
                                                      ? 0U
                                                      : 
                                                     ((4U 
                                                       & vlSelf->inst)
                                                       ? 
                                                      ((2U 
                                                        & vlSelf->inst)
                                                        ? 
                                                       ((1U 
                                                         & vlSelf->inst)
                                                         ? 
                                                        (vlSelf->inst 
                                                         >> 7U)
                                                         : 0U)
                                                        : 0U)
                                                       : 
                                                      ((2U 
                                                        & vlSelf->inst)
                                                        ? 
                                                       ((1U 
                                                         & vlSelf->inst)
                                                         ? 
                                                        (vlSelf->inst 
                                                         >> 7U)
                                                         : 0U)
                                                        : 0U)))
                                                     : 0U))));
    vlSelf->top__DOT__rs1_val = ((0U == (IData)(vlSelf->top__DOT__rs1))
                                  ? 0ULL : vlSelf->top__DOT__gpr__DOT__rf
                                 [vlSelf->top__DOT__rs1]);
    if ((0x40U & vlSelf->inst)) {
        if ((0x20U & vlSelf->inst)) {
            if ((0x10U & vlSelf->inst)) {
                vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                vlSelf->result = 0ULL;
            } else if ((8U & vlSelf->inst)) {
                if ((4U & vlSelf->inst)) {
                    if ((2U & vlSelf->inst)) {
                        if ((1U & vlSelf->inst)) {
                            vlSelf->top__DOT__npc = 
                                (vlSelf->pc_val + vlSelf->top__DOT__immi_sext);
                            vlSelf->result = (4ULL 
                                              + vlSelf->pc_val);
                        } else {
                            vlSelf->top__DOT__npc = 
                                (4ULL + vlSelf->pc_val);
                            vlSelf->result = 0ULL;
                        }
                    } else {
                        vlSelf->top__DOT__npc = (4ULL 
                                                 + vlSelf->pc_val);
                        vlSelf->result = 0ULL;
                    }
                } else {
                    vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                    vlSelf->result = 0ULL;
                }
            } else if ((4U & vlSelf->inst)) {
                if ((2U & vlSelf->inst)) {
                    if ((1U & vlSelf->inst)) {
                        vlSelf->top__DOT__npc = (0xfffffffffffffffeULL 
                                                 & (vlSelf->top__DOT__immi_sext 
                                                    + vlSelf->top__DOT__rs1_val));
                        vlSelf->result = (4ULL + vlSelf->pc_val);
                    } else {
                        vlSelf->top__DOT__npc = (4ULL 
                                                 + vlSelf->pc_val);
                        vlSelf->result = 0ULL;
                    }
                } else {
                    vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                    vlSelf->result = 0ULL;
                }
            } else {
                vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                vlSelf->result = 0ULL;
            }
        } else {
            vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
            vlSelf->result = 0ULL;
        }
    } else if ((0x20U & vlSelf->inst)) {
        if ((0x10U & vlSelf->inst)) {
            if ((8U & vlSelf->inst)) {
                vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                vlSelf->result = 0ULL;
            } else if ((4U & vlSelf->inst)) {
                if ((2U & vlSelf->inst)) {
                    if ((1U & vlSelf->inst)) {
                        vlSelf->top__DOT__npc = (4ULL 
                                                 + vlSelf->pc_val);
                        vlSelf->result = vlSelf->top__DOT__immi_sext;
                    } else {
                        vlSelf->top__DOT__npc = (4ULL 
                                                 + vlSelf->pc_val);
                        vlSelf->result = 0ULL;
                    }
                } else {
                    vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                    vlSelf->result = 0ULL;
                }
            } else {
                vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                vlSelf->result = 0ULL;
            }
        } else {
            vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
            vlSelf->result = 0ULL;
        }
    } else if ((0x10U & vlSelf->inst)) {
        if ((8U & vlSelf->inst)) {
            vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
            vlSelf->result = 0ULL;
        } else if ((4U & vlSelf->inst)) {
            if ((2U & vlSelf->inst)) {
                if ((1U & vlSelf->inst)) {
                    vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                    vlSelf->result = (vlSelf->pc_val 
                                      + vlSelf->top__DOT__immi_sext);
                } else {
                    vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                    vlSelf->result = 0ULL;
                }
            } else {
                vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                vlSelf->result = 0ULL;
            }
        } else if ((2U & vlSelf->inst)) {
            if ((1U & vlSelf->inst)) {
                vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                vlSelf->result = (vlSelf->top__DOT__rs1_val 
                                  + vlSelf->top__DOT__immi_sext);
            } else {
                vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
                vlSelf->result = 0ULL;
            }
        } else {
            vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
            vlSelf->result = 0ULL;
        }
    } else {
        vlSelf->top__DOT__npc = (4ULL + vlSelf->pc_val);
        vlSelf->result = 0ULL;
    }
}

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Body
    Vtop___024root___combo__TOP__0(vlSelf);
    vlSelf->__Vm_traceActivity[1U] = 1U;
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        Vtop___024root___sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    Vtop___024root___combo__TOP__1(vlSelf);
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
