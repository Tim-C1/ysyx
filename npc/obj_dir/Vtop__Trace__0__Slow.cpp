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
    tracep->declBit(c+75,"clk", false,-1);
    tracep->declBit(c+76,"rst", false,-1);
    tracep->declBus(c+77,"inst", false,-1, 31,0);
    tracep->declQuad(c+78,"pc_val", false,-1, 63,0);
    tracep->declQuad(c+80,"result", false,-1, 63,0);
    tracep->declQuad(c+82,"rs1_reg", false,-1, 63,0);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+75,"clk", false,-1);
    tracep->declBit(c+76,"rst", false,-1);
    tracep->declBus(c+77,"inst", false,-1, 31,0);
    tracep->declQuad(c+78,"pc_val", false,-1, 63,0);
    tracep->declQuad(c+80,"result", false,-1, 63,0);
    tracep->declQuad(c+82,"rs1_reg", false,-1, 63,0);
    tracep->declBus(c+86,"ebreak", false,-1, 31,0);
    tracep->declQuad(c+1,"immi_sext", false,-1, 63,0);
    tracep->declBus(c+84,"opcode", false,-1, 6,0);
    tracep->declBus(c+3,"rs1", false,-1, 4,0);
    tracep->declBus(c+4,"rd", false,-1, 4,0);
    tracep->declBit(c+87,"wen_reg", false,-1);
    tracep->declBit(c+85,"wen_pc", false,-1);
    tracep->declQuad(c+5,"npc", false,-1, 63,0);
    tracep->declQuad(c+7,"rs1_val", false,-1, 63,0);
    tracep->declQuad(c+9,"a0_val", false,-1, 63,0);
    tracep->pushNamePrefix("exu ");
    tracep->declQuad(c+7,"rs1_val", false,-1, 63,0);
    tracep->declQuad(c+1,"immi_sext", false,-1, 63,0);
    tracep->declQuad(c+78,"pc", false,-1, 63,0);
    tracep->declBus(c+84,"opcode", false,-1, 6,0);
    tracep->declQuad(c+80,"result", false,-1, 63,0);
    tracep->declQuad(c+5,"npc", false,-1, 63,0);
    tracep->declBit(c+87,"wen_reg", false,-1);
    tracep->declBit(c+85,"wen_pc", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("gpr ");
    tracep->declBus(c+88,"ADDR_WIDTH", false,-1, 31,0);
    tracep->declBus(c+89,"DATA_WIDTH", false,-1, 31,0);
    tracep->declBit(c+75,"clk", false,-1);
    tracep->declQuad(c+80,"wdata", false,-1, 63,0);
    tracep->declBus(c+4,"waddr", false,-1, 4,0);
    tracep->declBus(c+3,"raddr", false,-1, 4,0);
    tracep->declBit(c+87,"wen", false,-1);
    tracep->declQuad(c+7,"rdata", false,-1, 63,0);
    tracep->declQuad(c+82,"rs1_reg", false,-1, 63,0);
    tracep->declQuad(c+9,"r10_val", false,-1, 63,0);
    for (int i = 0; i < 32; ++i) {
        tracep->declQuad(c+11+i*2,"rf", true,(i+0), 63,0);
    }
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("idu ");
    tracep->declBus(c+77,"inst", false,-1, 31,0);
    tracep->declBus(c+84,"opcode", false,-1, 6,0);
    tracep->declQuad(c+1,"immi_sext", false,-1, 63,0);
    tracep->declBus(c+3,"rs1", false,-1, 4,0);
    tracep->declBus(c+4,"rd", false,-1, 4,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("pc ");
    tracep->declBit(c+75,"clk", false,-1);
    tracep->declBit(c+76,"rst", false,-1);
    tracep->declQuad(c+5,"wdata", false,-1, 63,0);
    tracep->declBit(c+85,"wen", false,-1);
    tracep->declQuad(c+78,"pc_val", false,-1, 63,0);
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
    tracep->fullQData(oldp+1,(vlSelf->top__DOT__immi_sext),64);
    tracep->fullCData(oldp+3,(vlSelf->top__DOT__rs1),5);
    tracep->fullCData(oldp+4,(vlSelf->top__DOT__rd),5);
    tracep->fullQData(oldp+5,(vlSelf->top__DOT__npc),64);
    tracep->fullQData(oldp+7,(vlSelf->top__DOT__rs1_val),64);
    tracep->fullQData(oldp+9,(vlSelf->top__DOT__gpr__DOT__rf
                              [0xaU]),64);
    tracep->fullQData(oldp+11,(vlSelf->top__DOT__gpr__DOT__rf[0]),64);
    tracep->fullQData(oldp+13,(vlSelf->top__DOT__gpr__DOT__rf[1]),64);
    tracep->fullQData(oldp+15,(vlSelf->top__DOT__gpr__DOT__rf[2]),64);
    tracep->fullQData(oldp+17,(vlSelf->top__DOT__gpr__DOT__rf[3]),64);
    tracep->fullQData(oldp+19,(vlSelf->top__DOT__gpr__DOT__rf[4]),64);
    tracep->fullQData(oldp+21,(vlSelf->top__DOT__gpr__DOT__rf[5]),64);
    tracep->fullQData(oldp+23,(vlSelf->top__DOT__gpr__DOT__rf[6]),64);
    tracep->fullQData(oldp+25,(vlSelf->top__DOT__gpr__DOT__rf[7]),64);
    tracep->fullQData(oldp+27,(vlSelf->top__DOT__gpr__DOT__rf[8]),64);
    tracep->fullQData(oldp+29,(vlSelf->top__DOT__gpr__DOT__rf[9]),64);
    tracep->fullQData(oldp+31,(vlSelf->top__DOT__gpr__DOT__rf[10]),64);
    tracep->fullQData(oldp+33,(vlSelf->top__DOT__gpr__DOT__rf[11]),64);
    tracep->fullQData(oldp+35,(vlSelf->top__DOT__gpr__DOT__rf[12]),64);
    tracep->fullQData(oldp+37,(vlSelf->top__DOT__gpr__DOT__rf[13]),64);
    tracep->fullQData(oldp+39,(vlSelf->top__DOT__gpr__DOT__rf[14]),64);
    tracep->fullQData(oldp+41,(vlSelf->top__DOT__gpr__DOT__rf[15]),64);
    tracep->fullQData(oldp+43,(vlSelf->top__DOT__gpr__DOT__rf[16]),64);
    tracep->fullQData(oldp+45,(vlSelf->top__DOT__gpr__DOT__rf[17]),64);
    tracep->fullQData(oldp+47,(vlSelf->top__DOT__gpr__DOT__rf[18]),64);
    tracep->fullQData(oldp+49,(vlSelf->top__DOT__gpr__DOT__rf[19]),64);
    tracep->fullQData(oldp+51,(vlSelf->top__DOT__gpr__DOT__rf[20]),64);
    tracep->fullQData(oldp+53,(vlSelf->top__DOT__gpr__DOT__rf[21]),64);
    tracep->fullQData(oldp+55,(vlSelf->top__DOT__gpr__DOT__rf[22]),64);
    tracep->fullQData(oldp+57,(vlSelf->top__DOT__gpr__DOT__rf[23]),64);
    tracep->fullQData(oldp+59,(vlSelf->top__DOT__gpr__DOT__rf[24]),64);
    tracep->fullQData(oldp+61,(vlSelf->top__DOT__gpr__DOT__rf[25]),64);
    tracep->fullQData(oldp+63,(vlSelf->top__DOT__gpr__DOT__rf[26]),64);
    tracep->fullQData(oldp+65,(vlSelf->top__DOT__gpr__DOT__rf[27]),64);
    tracep->fullQData(oldp+67,(vlSelf->top__DOT__gpr__DOT__rf[28]),64);
    tracep->fullQData(oldp+69,(vlSelf->top__DOT__gpr__DOT__rf[29]),64);
    tracep->fullQData(oldp+71,(vlSelf->top__DOT__gpr__DOT__rf[30]),64);
    tracep->fullQData(oldp+73,(vlSelf->top__DOT__gpr__DOT__rf[31]),64);
    tracep->fullBit(oldp+75,(vlSelf->clk));
    tracep->fullBit(oldp+76,(vlSelf->rst));
    tracep->fullIData(oldp+77,(vlSelf->inst),32);
    tracep->fullQData(oldp+78,(vlSelf->pc_val),64);
    tracep->fullQData(oldp+80,(vlSelf->result),64);
    tracep->fullQData(oldp+82,(vlSelf->rs1_reg),64);
    tracep->fullCData(oldp+84,((0x7fU & vlSelf->inst)),7);
    tracep->fullBit(oldp+85,((1U & (IData)(((0x60U 
                                             == (0x70U 
                                                 & vlSelf->inst)) 
                                            & ((8U 
                                                & vlSelf->inst)
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
    tracep->fullIData(oldp+86,(0x100073U),32);
    tracep->fullBit(oldp+87,(1U));
    tracep->fullIData(oldp+88,(5U),32);
    tracep->fullIData(oldp+89,(0x40U),32);
}
