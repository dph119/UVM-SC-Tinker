#ifndef TINYALU_DRIVER_H_
#define TINYALU_DRIVER_H_

// driver to drive the dut
// is also the bfm
#include <uvm>
#include "pkg.h"

#include "Vtinyalu.h"
#include "verilated_vcd_sc.h"   // Tracing

using namespace sc_core;
using namespace uvm;

template <typename REQ = uvm::uvm_sequence_item, typename RSP = REQ>
class driver : public uvm::uvm_driver<REQ, RSP> {
 public:
 driver(uvm::uvm_component_name name) : uvm::uvm_driver<REQ, RSP>(name) {}

 Vtinyalu* dut;
 
 UVM_COMPONENT_PARAM_UTILS(driver<REQ, RSP>);

 // Define interface signals to communicate to DUT
 // You need to check the verilated header file to see
 // just what kind of data types were generated
 sc_signal<uint32_t > A;
 sc_signal<uint32_t > B;
 sc_signal<uint32_t > op;  
 sc_signal<bool> start;
 sc_signal<bool> reset_n;
 sc_signal<bool> done;  
 sc_signal<uint32_t > result;
 // For some reason attempting to instantiate sc_clock caused
 // UVM to hang at the end reporting stats at end of test
 // TODO: Try calling dut->final() at the end?
 sc_signal<bool> clk;
      
 void elaboration_phase(uvm::uvm_phase& phase) {
   // Set up the DUT and clock
   UVM_INFO("driver", "Creating/connecting DUT.", uvm::UVM_INFO);

   // Note we can only instantiate during the elaboration phase
   // SystemC will barf if it sees you try to do it later
   dut = new Vtinyalu("dut");

   dut->clk(clk);
   dut->reset_n(reset_n);
   dut->A(A);
   dut->B(B);
   dut->op(op);
   dut->start(start);
   dut->done(done);
   dut->result(result);
 }

 void final_phase(uvm::uvm_phase& phase) {
   // Stop the clock and delete the dut
   UVM_INFO("driver", "Stopping the clock.", uvm::UVM_INFO);         
   UVM_INFO("driver", "Obliterating DUT.", uvm::UVM_INFO);      
   delete dut;
   
   // check remaining objections because why not
   phase.get_objection()->display_objections();
 }

 void run_phase(uvm::uvm_phase& phase) {
   REQ req;

   UVM_INFO("driver", "Starting the clock.", uvm::UVM_INFO);

   reset_n = 0;

   clk = 0;
   sc_core::wait(1, SC_NS);
   clk = 1;
   
   UVM_INFO("driver", "Enabling waves...", uvm::UVM_INFO);
   Verilated::traceEverOn(true);   
   VerilatedVcdSc* tfp = new VerilatedVcdSc;
   dut->trace(tfp, 99);
   tfp->open("vlt_dump.vcd");   
   
   // Separate into own clk driver since sc_clock doesn't seem to be working?
   for(int i = 0; i < 10000; i++) {
     clk = ~clk;
     sc_core::wait(1, SC_NS);     
   }

   if (tfp) tfp->close();
   
   while(true) {
     this->seq_item_port->get(req);

     // extract data from the request, drive the port
   }
 }
};

#endif
