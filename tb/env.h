#ifndef TINYALU_ENV_H_
#define TINYALU_ENV_H_

#include <systemc>
#include <uvm>

#include "sequence_item.h"
#include "tinyalu_driver.h"
#include "sequencer.h"

class env: public uvm::uvm_env {
 public:
  sequencer<sequence_item, rsp>* sequencer_h;
  tinyalu_driver<sequence_item, rsp>* tinyalu_driver_h;

  UVM_COMPONENT_UTILS(env);
  
  env(uvm::uvm_component_name name) : uvm::uvm_env(name), sequencer_h(0), tinyalu_driver_h(0) {}

  void build_phase(uvm::uvm_phase& phase) {
    uvm::uvm_env::build_phase(phase);

    // Create the sequencer, tinyalu_driver, and sequence to be used
    sequencer_h = sequencer<sequence_item, rsp>::type_id::create("sequence_controller", this);
    tinyalu_driver_h = tinyalu_driver<sequence_item, rsp>::type_id::create("slave", this);
  }

  void connect_phase(uvm::uvm_phase& phase) {
    // Connect the sequencer to the tinyalu_driver
    // Note: ports connect to exports
    tinyalu_driver_h->seq_item_port(sequencer_h->seq_item_export);
  }
};

#endif
