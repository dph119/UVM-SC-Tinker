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
 // For some reason attempting to instantiate sc_clock caused
 // UVM to hang at the end reporting stats at end of test
 // TODO: Try calling dut->final() at the end?
 // sc_signal<bool> clk;
 sc_clock clk;
 
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

   UVM_INFO("driver", "Connecting clock.", uvm::UVM_INFO);   
   
   dut->clk(clk);

   UVM_INFO("driver", "DONE connecting clock.", uvm::UVM_INFO);
   
   dut->reset_n(reset_n);
   dut->A(A);
   dut->B(B);
   dut->op(op);
   dut->start(start);
   dut->done(done);
   dut->result(result);

   UVM_INFO("driver", "Ending connect_phase()", uvm::UVM_INFO);   
 }

 void final_phase(uvm::uvm_phase& phase) {
   // Stop the clock and delete the dut
  
   UVM_INFO("driver", "Stopping the clock.", uvm::UVM_INFO);         
   //   UVM_INFO("driver", "Obliterating DUT.", uvm::UVM_INFO);      
   //   delete dut;

   if (tfp) {
     UVM_INFO("driver", "Dumping/closing waves.", uvm::UVM_INFO);      
     tfp->flush();
     tfp->close();
   }
   
   // check remaining objections because why not
   phase.get_objection()->display_objections();

   dut->final();
 }

 void run_phase(uvm::uvm_phase& phase) {
   REQ req;

   assert(dut && "DUT cannot be NULL at this point.");

   UVM_INFO("driver", "Begin run_phase()", uvm::UVM_INFO);
   
   reset_n = 0;

   /*   clk = 0;
   sc_core::wait(1, SC_NS);
   clk = 1;
   */
   UVM_INFO("driver", "Enabling waves...", uvm::UVM_INFO);
   Verilated::traceEverOn(true);   
   tfp = new VerilatedVcdSc;
   dut->trace(tfp, 99);
   tfp->open("vlt_dump.vcd");   

   /*
   // Separate into own clk driver since sc_clock doesn't seem to be working?
   for(int i = 0; i < 10000; i++) {
     clk = clk == 0;
     sc_core::wait(1, SC_NS);
     std::cout << i << " " << clk << endl; 
   }
   */
   while(true) {
     this->seq_item_port->get(req);

     // extract data from the request, drive the port
   }
 }
};

#endif
