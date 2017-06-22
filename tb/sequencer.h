#ifndef TINYALU_SEQUENCER_H_
#define TINYALU_SEQUENCE_H_

#include <systemc>
#include <uvm>

template <typename REQ = uvm::uvm_sequence_item, typename RSP = REQ>
  class sequencer : public uvm::uvm_sequencer<REQ, RSP> {
 public:
 sequencer(uvm::uvm_component_name name) : uvm::uvm_sequencer<REQ, RSP>(name) {}

 UVM_COMPONENT_PARAM_UTILS(sequencer<REQ, RSP>);
};

#endif
