// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+11,"clk", false,-1);
    tracep->declBit(c+12,"rst", false,-1);
    tracep->declBus(c+13,"inst", false,-1, 31,0);
    tracep->declQuad(c+14,"r1", false,-1, 63,0);
    tracep->declQuad(c+16,"r2", false,-1, 63,0);
    tracep->declQuad(c+18,"pc_val", false,-1, 63,0);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+11,"clk", false,-1);
    tracep->declBit(c+12,"rst", false,-1);
    tracep->declBus(c+13,"inst", false,-1, 31,0);
    tracep->declQuad(c+14,"r1", false,-1, 63,0);
    tracep->declQuad(c+16,"r2", false,-1, 63,0);
    tracep->declQuad(c+18,"pc_val", false,-1, 63,0);
    tracep->declQuad(c+20,"immi_sext", false,-1, 63,0);
    tracep->declBus(c+22,"rs1", false,-1, 4,0);
    tracep->declBus(c+23,"rd", false,-1, 4,0);
    tracep->declBit(c+28,"wen", false,-1);
    tracep->declQuad(c+24,"result", false,-1, 63,0);
    tracep->declQuad(c+26,"rs1_val", false,-1, 63,0);
    tracep->pushNamePrefix("exu ");
    tracep->declQuad(c+26,"rs1_val", false,-1, 63,0);
    tracep->declQuad(c+20,"immi_sext", false,-1, 63,0);
    tracep->declQuad(c+24,"result", false,-1, 63,0);
    tracep->declBit(c+28,"wen", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("gpr ");
    tracep->declBus(c+29,"ADDR_WIDTH", false,-1, 31,0);
    tracep->declBus(c+30,"DATA_WIDTH", false,-1, 31,0);
    tracep->declBit(c+11,"clk", false,-1);
    tracep->declQuad(c+24,"wdata", false,-1, 63,0);
    tracep->declBus(c+23,"waddr", false,-1, 4,0);
    tracep->declBus(c+22,"raddr", false,-1, 4,0);
    tracep->declBit(c+28,"wen", false,-1);
    tracep->declQuad(c+14,"r1", false,-1, 63,0);
    tracep->declQuad(c+16,"r2", false,-1, 63,0);
    tracep->declQuad(c+26,"rdata", false,-1, 63,0);
    for (int i = 0; i < 5; ++i) {
        tracep->declQuad(c+1+i*2,"rf", true,(i+0), 63,0);
    }
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("idu ");
    tracep->declBus(c+13,"inst", false,-1, 31,0);
    tracep->declQuad(c+20,"immi_sext", false,-1, 63,0);
    tracep->declBus(c+22,"rs1", false,-1, 4,0);
    tracep->declBus(c+23,"rd", false,-1, 4,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("pc ");
    tracep->declBit(c+11,"clk", false,-1);
    tracep->declBit(c+12,"rst", false,-1);
    tracep->declQuad(c+31,"wdata", false,-1, 63,0);
    tracep->declBit(c+33,"wen", false,-1);
    tracep->declQuad(c+18,"pc_val", false,-1, 63,0);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd* tracep);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd* tracep);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    vluint32_t* const oldp VL_ATTR_UNUSED = tracep->oldp(vlSymsp->__Vm_baseCode);
    // Body
    tracep->fullQData(oldp+1,(vlSelf->top__DOT__gpr__DOT__rf[0]),64);
    tracep->fullQData(oldp+3,(vlSelf->top__DOT__gpr__DOT__rf[1]),64);
    tracep->fullQData(oldp+5,(vlSelf->top__DOT__gpr__DOT__rf[2]),64);
    tracep->fullQData(oldp+7,(vlSelf->top__DOT__gpr__DOT__rf[3]),64);
    tracep->fullQData(oldp+9,(vlSelf->top__DOT__gpr__DOT__rf[4]),64);
    tracep->fullBit(oldp+11,(vlSelf->clk));
    tracep->fullBit(oldp+12,(vlSelf->rst));
    tracep->fullIData(oldp+13,(vlSelf->inst),32);
    tracep->fullQData(oldp+14,(vlSelf->r1),64);
    tracep->fullQData(oldp+16,(vlSelf->r2),64);
    tracep->fullQData(oldp+18,(vlSelf->pc_val),64);
    tracep->fullQData(oldp+20,((((- (QData)((IData)(
                                                    (vlSelf->inst 
                                                     >> 0x1fU)))) 
                                 << 0xcU) | (QData)((IData)(
                                                            (vlSelf->inst 
                                                             >> 0x14U))))),64);
    tracep->fullCData(oldp+22,((0x1fU & (vlSelf->inst 
                                         >> 0xfU))),5);
    tracep->fullCData(oldp+23,((0x1fU & (vlSelf->inst 
                                         >> 7U))),5);
    tracep->fullQData(oldp+24,((((4U >= (7U & (vlSelf->inst 
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
                                                                >> 0x14U)))))),64);
    tracep->fullQData(oldp+26,(((4U >= (7U & (vlSelf->inst 
                                              >> 0xfU)))
                                 ? vlSelf->top__DOT__gpr__DOT__rf
                                [(7U & (vlSelf->inst 
                                        >> 0xfU))] : 0ULL)),64);
    tracep->fullBit(oldp+28,(1U));
    tracep->fullIData(oldp+29,(5U),32);
    tracep->fullIData(oldp+30,(0x40U),32);
    tracep->fullQData(oldp+31,(0ULL),64);
    tracep->fullBit(oldp+33,(0U));
}
