#include <systemc>
#include <uvm>

using namespace uvm;

class tinyalu_base_test : public uvm_test {
 public:
  tinyalu_base_test(uvm_component_name name): uvm_test(name) {}
  
  UVM_COMPONENT_UTILS(tinyalu_base_test);

  void run_phase(uvm_phase& phase) {
    sc_time drain_time = sc_time(12.5, SC_US);

    uvm_report_info("drain",
      "Setting drain time of " + drain_time.to_string(), UVM_NONE);

    phase.get_objection()->set_drain_time(this, drain_time);
    
    phase.raise_objection(this);
    UVM_INFO(get_name(), "Sup world.", uvm::UVM_INFO);
    sc_core::wait(100, SC_US);
    UVM_INFO(get_name(), "Time is passing, right?", uvm::UVM_INFO);    
    phase.drop_objection(this);
  }

  void main_phase(uvm_phase& phase) {
    UVM_INFO(get_name(), "This is the main phase.", uvm::UVM_INFO);        
  }
  
  void pre_shutdown_phase(uvm_phase& phase) {
    UVM_INFO(get_name(), "This is the PRE shutdown phase.", uvm::UVM_INFO);
  }
  
  void shutdown_phase(uvm_phase& phase) {
    UVM_INFO(get_name(), "This is the shutdown phase.", uvm::UVM_INFO);
  }

  void report_phase(uvm_phase& phase) {
    UVM_INFO(get_name(), "This is the report phase.", uvm::UVM_INFO);
  }
  
  void final_phase(uvm_phase& phase) {
    UVM_INFO(get_name(), "Time is the final phase.", uvm::UVM_INFO);
    //    phase.drop_objection(this);    
    //    sc_stop();
  }

  // Use an objection callback do something when objections are raised or
  // dropped (or all dropped). This example prints some information on each
  // drop.
  virtual void dropped( uvm_objection* objection,
      uvm_object* source_obj,
      const std::string& description,
      int count )
  {
    std::ostringstream str;
    str << count
        << " objection(s) dropped from "
        << source_obj->get_full_name()
        << ", total count is now "
        << objection->get_objection_total(this)
        << " top: " << objection->get_objection_total(uvm_root::get());

    uvm_report_info("dropped", str.str(), UVM_NONE);
  }

  virtual void raised( uvm_objection* objection,
      uvm_object* source_obj,
      const std::string& description,
      int count )
  {
    std::ostringstream str;
    str << count
        << " objection(s) raised from "
        << source_obj->get_full_name()
        << ", total count is now "
        << objection->get_objection_total(this)
        << " top: " << objection->get_objection_total(uvm_root::get());

    uvm_report_info("raised", str.str(), UVM_NONE);
  }
  
};
