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
        tracep->chgQData(oldp+0,(vlSelf->top__DOT__immi_sext),64);
        tracep->chgCData(oldp+2,(vlSelf->top__DOT__rs1),5);
        tracep->chgCData(oldp+3,(vlSelf->top__DOT__rd),5);
        tracep->chgQData(oldp+4,(vlSelf->top__DOT__npc),64);
        tracep->chgQData(oldp+6,(vlSelf->top__DOT__rs1_val),64);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        tracep->chgQData(oldp+8,(vlSelf->top__DOT__gpr__DOT__rf
                                 [0xaU]),64);
        tracep->chgQData(oldp+10,(vlSelf->top__DOT__gpr__DOT__rf[0]),64);
        tracep->chgQData(oldp+12,(vlSelf->top__DOT__gpr__DOT__rf[1]),64);
        tracep->chgQData(oldp+14,(vlSelf->top__DOT__gpr__DOT__rf[2]),64);
        tracep->chgQData(oldp+16,(vlSelf->top__DOT__gpr__DOT__rf[3]),64);
        tracep->chgQData(oldp+18,(vlSelf->top__DOT__gpr__DOT__rf[4]),64);
        tracep->chgQData(oldp+20,(vlSelf->top__DOT__gpr__DOT__rf[5]),64);
        tracep->chgQData(oldp+22,(vlSelf->top__DOT__gpr__DOT__rf[6]),64);
        tracep->chgQData(oldp+24,(vlSelf->top__DOT__gpr__DOT__rf[7]),64);
        tracep->chgQData(oldp+26,(vlSelf->top__DOT__gpr__DOT__rf[8]),64);
        tracep->chgQData(oldp+28,(vlSelf->top__DOT__gpr__DOT__rf[9]),64);
        tracep->chgQData(oldp+30,(vlSelf->top__DOT__gpr__DOT__rf[10]),64);
        tracep->chgQData(oldp+32,(vlSelf->top__DOT__gpr__DOT__rf[11]),64);
        tracep->chgQData(oldp+34,(vlSelf->top__DOT__gpr__DOT__rf[12]),64);
        tracep->chgQData(oldp+36,(vlSelf->top__DOT__gpr__DOT__rf[13]),64);
        tracep->chgQData(oldp+38,(vlSelf->top__DOT__gpr__DOT__rf[14]),64);
        tracep->chgQData(oldp+40,(vlSelf->top__DOT__gpr__DOT__rf[15]),64);
        tracep->chgQData(oldp+42,(vlSelf->top__DOT__gpr__DOT__rf[16]),64);
        tracep->chgQData(oldp+44,(vlSelf->top__DOT__gpr__DOT__rf[17]),64);
        tracep->chgQData(oldp+46,(vlSelf->top__DOT__gpr__DOT__rf[18]),64);
        tracep->chgQData(oldp+48,(vlSelf->top__DOT__gpr__DOT__rf[19]),64);
        tracep->chgQData(oldp+50,(vlSelf->top__DOT__gpr__DOT__rf[20]),64);
        tracep->chgQData(oldp+52,(vlSelf->top__DOT__gpr__DOT__rf[21]),64);
        tracep->chgQData(oldp+54,(vlSelf->top__DOT__gpr__DOT__rf[22]),64);
        tracep->chgQData(oldp+56,(vlSelf->top__DOT__gpr__DOT__rf[23]),64);
        tracep->chgQData(oldp+58,(vlSelf->top__DOT__gpr__DOT__rf[24]),64);
        tracep->chgQData(oldp+60,(vlSelf->top__DOT__gpr__DOT__rf[25]),64);
        tracep->chgQData(oldp+62,(vlSelf->top__DOT__gpr__DOT__rf[26]),64);
        tracep->chgQData(oldp+64,(vlSelf->top__DOT__gpr__DOT__rf[27]),64);
        tracep->chgQData(oldp+66,(vlSelf->top__DOT__gpr__DOT__rf[28]),64);
        tracep->chgQData(oldp+68,(vlSelf->top__DOT__gpr__DOT__rf[29]),64);
        tracep->chgQData(oldp+70,(vlSelf->top__DOT__gpr__DOT__rf[30]),64);
        tracep->chgQData(oldp+72,(vlSelf->top__DOT__gpr__DOT__rf[31]),64);
    }
    tracep->chgBit(oldp+74,(vlSelf->clk));
    tracep->chgBit(oldp+75,(vlSelf->rst));
    tracep->chgIData(oldp+76,(vlSelf->inst),32);
    tracep->chgQData(oldp+77,(vlSelf->pc_val),64);
    tracep->chgQData(oldp+79,(vlSelf->result),64);
    tracep->chgQData(oldp+81,(vlSelf->rs1_reg),64);
    tracep->chgCData(oldp+83,((0x7fU & vlSelf->inst)),7);
    tracep->chgBit(oldp+84,((1U & (IData)(((0x60U == 
                                            (0x70U 
                                             & vlSelf->inst)) 
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
                                                           & vlSelf->inst)))))))));
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
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
