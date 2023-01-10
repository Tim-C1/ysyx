// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___settle__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___settle__TOP__0\n"); );
    // Body
    if ((0x40U & vlSelf->inst)) {
        if ((0x20U & vlSelf->inst)) {
            if ((0x10U & vlSelf->inst)) {
                vlSelf->top__DOT__immi_sext = 0ULL;
                vlSelf->top__DOT__rs1 = (0x1fU & 0U);
                vlSelf->top__DOT__rd = (0x1fU & 0U);
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
                vlSelf->top__DOT__rd = (0x1fU & ((4U 
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
                                                  : 0U));
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
                        vlSelf->top__DOT__rd = (0x1fU 
                                                & (vlSelf->inst 
                                                   >> 7U));
                    } else {
                        vlSelf->top__DOT__immi_sext = 0ULL;
                        vlSelf->top__DOT__rs1 = (0x1fU 
                                                 & 0U);
                        vlSelf->top__DOT__rd = (0x1fU 
                                                & 0U);
                    }
                } else {
                    vlSelf->top__DOT__immi_sext = 0ULL;
                    vlSelf->top__DOT__rs1 = (0x1fU 
                                             & 0U);
                    vlSelf->top__DOT__rd = (0x1fU & 0U);
                }
            } else {
                vlSelf->top__DOT__immi_sext = 0ULL;
                vlSelf->top__DOT__rs1 = (0x1fU & 0U);
                vlSelf->top__DOT__rd = (0x1fU & 0U);
            }
        } else {
            vlSelf->top__DOT__immi_sext = 0ULL;
            vlSelf->top__DOT__rs1 = (0x1fU & 0U);
            vlSelf->top__DOT__rd = (0x1fU & 0U);
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
        vlSelf->top__DOT__rd = (0x1fU & ((0x10U & vlSelf->inst)
                                          ? ((8U & vlSelf->inst)
                                              ? 0U : 
                                             ((4U & vlSelf->inst)
                                               ? ((2U 
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
                                          : 0U));
    } else if ((0x10U & vlSelf->inst)) {
        if ((8U & vlSelf->inst)) {
            vlSelf->top__DOT__immi_sext = 0ULL;
            vlSelf->top__DOT__rs1 = (0x1fU & 0U);
            vlSelf->top__DOT__rd = (0x1fU & 0U);
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
            vlSelf->top__DOT__rd = (0x1fU & ((2U & vlSelf->inst)
                                              ? ((1U 
                                                  & vlSelf->inst)
                                                  ? 
                                                 (vlSelf->inst 
                                                  >> 7U)
                                                  : 0U)
                                              : 0U));
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
                vlSelf->top__DOT__rd = (0x1fU & (vlSelf->inst 
                                                 >> 7U));
            } else {
                vlSelf->top__DOT__immi_sext = 0ULL;
                vlSelf->top__DOT__rs1 = (0x1fU & 0U);
                vlSelf->top__DOT__rd = (0x1fU & 0U);
            }
        } else {
            vlSelf->top__DOT__immi_sext = 0ULL;
            vlSelf->top__DOT__rs1 = (0x1fU & 0U);
            vlSelf->top__DOT__rd = (0x1fU & 0U);
        }
    } else {
        vlSelf->top__DOT__immi_sext = 0ULL;
        vlSelf->top__DOT__rs1 = (0x1fU & 0U);
        vlSelf->top__DOT__rd = (0x1fU & 0U);
    }
    vlSelf->rs1_reg = vlSelf->top__DOT__gpr__DOT__rf
        [1U];
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

void Vtop___024root____Vdpiimwrap_top__DOT__gpr__DOT__set_gpr_ptr__Vdpioc2_TOP(const VlUnpacked<QData/*63:0*/, 32> &a);

VL_ATTR_COLD void Vtop___024root___initial__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___initial__TOP__0\n"); );
    // Body
    Vtop___024root____Vdpiimwrap_top__DOT__gpr__DOT__set_gpr_ptr__Vdpioc2_TOP(vlSelf->top__DOT__gpr__DOT__rf);
}

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
    Vtop___024root___initial__TOP__0(vlSelf);
}

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    // Body
    Vtop___024root___settle__TOP__0(vlSelf);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
}

VL_ATTR_COLD void Vtop___024root___final(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___final\n"); );
}

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->inst = VL_RAND_RESET_I(32);
    vlSelf->pc_val = VL_RAND_RESET_Q(64);
    vlSelf->result = VL_RAND_RESET_Q(64);
    vlSelf->rs1_reg = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__immi_sext = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__rs1 = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__rd = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__npc = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__rs1_val = VL_RAND_RESET_Q(64);
    for (int __Vi0=0; __Vi0<32; ++__Vi0) {
        vlSelf->top__DOT__gpr__DOT__rf[__Vi0] = VL_RAND_RESET_Q(64);
    }
    for (int __Vi0=0; __Vi0<3; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }
}
