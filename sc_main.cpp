#include <systemc>
#include <uvm>

#include "verilated.h"
#include "base_test.h"

int sc_main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);

  uvm::run_test("base_test");
  
  std::cout << "==========================================" << endl;
  std::cout << "               END OF TEST                " << endl;
  std::cout << "==========================================" << endl;  

  exit(0);
}
