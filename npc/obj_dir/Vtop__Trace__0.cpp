// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedVcd* tracep);

void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_sub_0((&vlSymsp->TOP), tracep);
}

void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_sub_0\n"); );
    // Init
    vluint32_t* const oldp VL_ATTR_UNUSED = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        tracep->chgQData(oldp+0,(vlSelf->top__DOT__gpr__DOT__rf[0]),64);
        tracep->chgQData(oldp+2,(vlSelf->top__DOT__gpr__DOT__rf[1]),64);
        tracep->chgQData(oldp+4,(vlSelf->top__DOT__gpr__DOT__rf[2]),64);
        tracep->chgQData(oldp+6,(vlSelf->top__DOT__gpr__DOT__rf[3]),64);
        tracep->chgQData(oldp+8,(vlSelf->top__DOT__gpr__DOT__rf[4]),64);
    }
    tracep->chgBit(oldp+10,(vlSelf->clk));
    tracep->chgBit(oldp+11,(vlSelf->rst));
    tracep->chgIData(oldp+12,(vlSelf->inst),32);
    tracep->chgQData(oldp+13,(vlSelf->r1),64);
    tracep->chgQData(oldp+15,(vlSelf->r2),64);
    tracep->chgQData(oldp+17,(vlSelf->pc_val),64);
    tracep->chgQData(oldp+19,(vlSelf->result),64);
    tracep->chgQData(oldp+21,((((- (QData)((IData)(
                                                   (vlSelf->inst 
                                                    >> 0x1fU)))) 
                                << 0xcU) | (QData)((IData)(
                                                           (vlSelf->inst 
                                                            >> 0x14U))))),64);
    tracep->chgCData(oldp+23,((0x1fU & (vlSelf->inst 
                                        >> 0xfU))),5);
    tracep->chgCData(oldp+24,((0x1fU & (vlSelf->inst 
                                        >> 7U))),5);
    tracep->chgQData(oldp+25,(((0U == (0x1fU & (vlSelf->inst 
                                                >> 0xfU)))
                                ? 0ULL : ((4U >= (7U 
                                                  & (vlSelf->inst 
                                                     >> 0xfU)))
                                           ? vlSelf->top__DOT__gpr__DOT__rf
                                          [(7U & (vlSelf->inst 
                                                  >> 0xfU))]
                                           : 0ULL))),64);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
