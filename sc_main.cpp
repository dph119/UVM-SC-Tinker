#include <systemc>
#include <uvm>

#include "Vtinyalu.h"
#include "tinyalu_base_test.h"

using namespace uvm;

int sc_main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);

  std::cout << "About to start the test..." << std::endl;
  uvm::run_test("tinyalu_base_test");
  std::cout << "... test ended." << std::endl;
  
  //  while (!Verilated::gotFinish()) { sc_start(1, SC_NS); }
  
  //  delete top;
  exit(0);
}
