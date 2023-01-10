// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"

class Vtop__Syms;
VL_MODULE(Vtop___024root) {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    CData/*4:0*/ top__DOT__rs1;
    CData/*4:0*/ top__DOT__rd;
    CData/*0:0*/ __Vclklast__TOP__clk;
    VL_IN(inst,31,0);
    VL_OUT64(pc_val,63,0);
    VL_OUT64(result,63,0);
    VL_OUT64(rs1_reg,63,0);
    QData/*63:0*/ top__DOT__immi_sext;
    QData/*63:0*/ top__DOT__npc;
    QData/*63:0*/ top__DOT__rs1_val;
    VlUnpacked<QData/*63:0*/, 32> top__DOT__gpr__DOT__rf;
    VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;

    // INTERNAL VARIABLES
    Vtop__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
    Vtop___024root(const char* name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(Vtop__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
