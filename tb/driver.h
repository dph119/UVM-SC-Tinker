#ifndef TINYALU_DRIVER_H_
#define TINYALU_DRIVER_H_

// driver to drive the dut
// is also the bfm
#include <uvm>
#include "pkg.h"

using namespace sc_core;
using namespace uvm;

template <typename REQ = uvm::uvm_sequence_item, typename RSP = REQ>
class driver : public uvm::uvm_driver<REQ, RSP> {
 public:
 driver(uvm::uvm_component_name name) : uvm::uvm_driver<REQ, RSP>(name) {}

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
 
 void run_phase(uvm::uvm_phase& phase) {
   REQ req;

   while(true) {
     this->seq_item_port->get(req);

     // extract data from the request, drive the port
   }
 }
};

#endif
