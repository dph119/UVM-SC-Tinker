#ifndef TINYALU_ENV_H_
#define TINYALU_ENV_H_

#include <systemc>
#include <uvm>

#include "sequence_item.h"
#include "driver.h"
#include "sequencer.h"

class env: public uvm::uvm_env {
 public:
  sequencer<sequence_item, rsp>* sequencer_h;
  driver<sequence_item, rsp>* driver_h;

  UVM_COMPONENT_UTILS(env);
  
  env(uvm::uvm_component_name name) : uvm::uvm_env(name), sequencer_h(0), driver_h(0) {}

  void build_phase(uvm::uvm_phase& phase) {
    uvm::uvm_env::build_phase(phase);

    // Create the sequencer, driver, and sequence to be used
    sequencer_h = sequencer<sequence_item, rsp>::type_id::create("sequence_controller", this);
    driver_h = driver<sequence_item, rsp>::type_id::create("slave", this);
  }

  void connect_phase(uvm::uvm_phase& phase) {
    // Connect the sequencer to the driver
    // Note: ports connect to exports
    driver_h->seq_item_port(sequencer_h->seq_item_export);
  }
};

#endif
