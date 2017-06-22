#ifndef TINYALU_SEQUENCEA_H_
#define TINYALU_SEQUENCEA_H_

#include <systemc>
#include <uvm>

template <typename REQ = uvm::uvm_sequence_item, typename RSP = REQ>
class sequenceA : public uvm::uvm_sequence<REQ,RSP> {
  public:
    sequenceA(const std::string& name_) : uvm::uvm_sequence<REQ, RSP>(name_) {}
  
    UVM_COMPONENT_PARAM_UTILS(sequenceA<REQ, RSP>);

    void body() {
         UVM_INFO(this->get_name(), "Starting sequence BOI", uvm::UVM_INFO);
         UVM_INFO(this->get_name(), "Starting sequence BOI", uvm::UVM_INFO);
         UVM_INFO(this->get_name(), "Starting sequence BOI", uvm::UVM_INFO);
         UVM_INFO(this->get_name(), "Starting sequence BOI", uvm::UVM_INFO);
    }
};

#endif
