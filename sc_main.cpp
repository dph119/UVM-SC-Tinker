#include <systemc>
#include <uvm>

#include "verilated.h"
#include "base_test.h"

int sc_main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);

  uvm::run_test("base_test");

  // JFC. What's SUPPOSED to happen is UVM calls sc_start() and ticks away until either
  // 1. timeout is reached or 2. no activity is seen by the scheduler. However, the sheer existence
  // of an instantiated sc_clock ticking away causes sc_start() to never return.
  // I can't find anything about "stopping" an instance of sc_clock. It seems that in SystemC you'd just
  // eventually call sc_stop() and go home, but uvm_root::run_test() literally has code
  // to call sc_stop() after sc_start(). As far as I can tell, you end up with a livelock.
  // I'm just going to call sc_pause/sc_stop at the end of final_phase() in my env.
  // But this rips us out of UVM world, bypassing any post-test running routines, such
  // as the summary generated by the report server. I might also need to synchronize between
  // all components if they are actually trying to do stuff in final_phase (I'll probably just avoid that).
  //
  // SO, to make the test look like everything is running as expected, retrieve the report server
  // ourselves and explicitly tell it to create the summary.
  // 
  // The OTHER way around this is to simply not use sc_clock, but that's the whole point of the class.
  uvm_report_server* l_rs = uvm_report_server::get_server();
  l_rs->summarize();
    
  std::cout << "\n==========================================";
  std::cout << "\n|               END OF TEST              |";
  std::cout << "\n==========================================\n";

  exit(0);
}
