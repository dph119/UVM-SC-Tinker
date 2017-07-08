#ifndef TINYALU_DRIVER_H_
#define TINYALU_DRIVER_H_

/*****

  uvmprimver uses uvm_driver as a pass-through, sending a given transaction
  to a BFM. In that case, the BFM is responsible for handling the low-level
  interface protocols.

  When I look into the purpose of uvm_driver, though, I find that it is
  responsible for handling what the BFM did in uvmprimer. So, I'll let this driver
  be responsible for all the low-level details around communicating to the DUT.

*****/

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
 VerilatedVcdSc* tfp;
 
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
 sc_clock clk;

 void setup_waves() {
   UVM_INFO("driver", "Enabling waves...", uvm::UVM_INFO);
   Verilated::traceEverOn(true);   
   tfp = new VerilatedVcdSc;
   dut->trace(tfp, 99);
   tfp->open("vlt_dump.vcd");   
 }
 
 // Blunder: you can't instantiate during end_of_elaboration(), as SystemC
 // considers this, well, after the elaboration phase. But that doesn't
 // mean there's an actual "elaboration_phase" in UVM.
 // It's annoying if you get your phases mixed up or have a typo in the name, because
 // you'll just never actually execute the method.
 // Is there a way to check for this aside from asserts in later phases?
 void connect_phase(uvm::uvm_phase& phase) {
   // Set up the DUT
   UVM_INFO("driver", "Creating/connecting DUT.", uvm::UVM_INFO);
   
   dut = new Vtinyalu("dut");

   dut->clk(clk);
   dut->reset_n(reset_n);
   dut->A(A);
   dut->B(B);
   dut->op(op);
   dut->start(start);
   dut->done(done);
   dut->result(result);

   UVM_INFO("driver", "Ending connect_phase()", uvm::UVM_INFO);

   // TODO_dhullih: Use command-line arg/flag to figure out whether to call this method
   setup_waves();
 }
 
 void final_phase(uvm::uvm_phase& phase) {
   if (tfp) {
     UVM_INFO("driver", "Dumping/closing waves.", uvm::UVM_INFO);      
     tfp->flush();
     tfp->close();
   }
   
   // check remaining objections because why not. BOZO_dhullih - remove?
   phase.get_objection()->display_objections();
   dut->final();
 }

 void reset_dut() {
   // Routine to reset the DUT
   reset_n = 0;
   // wait 2 clocks
   sc_core::wait(2);
   reset_n = 1;
   start = 1;
 }

 void run_phase(uvm::uvm_phase& phase) {
   REQ req;

   assert(dut && "DUT cannot be NULL at this point.");

   // Always begin by putting the DUT through reset
   reset_dut();
   
   while(true) {
     this->seq_item_port->get(req);

     // extract data from the request, drive the port

     // should check for whether the transaction is a reset in itself
     
   }
 }
};

#endif
