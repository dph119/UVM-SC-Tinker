#ifndef TINYALU_BASE_TEST_H_
#define TINYALU_BASE_TEST_H_

#include <systemc>
#include <uvm>

#include "sequenceA.h"
#include "env.h"

using namespace sc_core;
using namespace uvm;

class base_test : public uvm_test {
 public:
  env* env_h;
  sequencer<sequence_item, rsp>* sequencer_h;
  sequenceA<sequence_item, rsp>* sequence_a;
    
  base_test(uvm_component_name name): uvm_test(name) {}
  
  UVM_COMPONENT_UTILS(base_test);

  void build_phase(uvm_phase& phase) {
    env_h = env::type_id::create("env_h", this);
  }

  void end_of_elaboration_phase(uvm_phase& phase) {
    sequencer_h = env_h->sequencer_h;
  }
  
  void run_phase(uvm_phase& phase) {
    // Instantiate an instance to use
    sequence_a = new sequenceA<sequence_item, rsp>("some_rando_sequence_name");
    
    sc_time drain_time = sc_time(12.5, SC_US);

    uvm_report_info("drain",
      "Setting drain time of " + drain_time.to_string(), UVM_NONE);

    phase.get_objection()->set_drain_time(this, drain_time);
    
    phase.raise_objection(this);
    UVM_INFO(get_name(), "Sup world.", uvm::UVM_INFO);
    sc_core::wait(1000, SC_US);

    // create some arbitrary sequence item to pass to the driver
    SC_FORK
      sc_core::sc_spawn(sc_bind(&base_test::start_sequence, this))
    SC_JOIN
    
    UVM_INFO(get_name(), "Time is passing, right?", uvm::UVM_INFO);    
    phase.drop_objection(this);
  }

  void start_sequence() {
    sequence_a->start(sequencer_h, NULL);
  }
};

#endif
