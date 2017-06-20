#include <systemc>
#include <uvm>
#include "Vtinyalu.h"

int sc_main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  
  sc_clock clk ("clk",10, 0.5, 3, true);

  // You need to check the verilated header file to see
  // just what kind of data types were generated
  sc_signal<uint32_t > A;
  sc_signal<uint32_t > B;
  sc_signal<uint32_t > op;  
  sc_signal<bool> start;
  sc_signal<bool> reset_n;
  sc_signal<bool> done;  
  sc_signal<uint32_t > result;  
  
  Vtinyalu* top = new Vtinyalu("top");   // SP_CELL (top, Vtinyalu);

  top->clk(clk);               // SP_PIN  (top, clk, clk);
  top->A(A);
  top->B(B);
  top->op(op);
  top->start(start);
  top->reset_n(reset_n);
  top->done(done);  
  top->result(result);
  
  while (!Verilated::gotFinish()) { sc_start(1, SC_NS); }
  delete top;
  exit(0);
}
