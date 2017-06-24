#ifndef TINYALU_SEQUENCE_ITEM_H_
#define TINYALU_SEQUENCE_ITEM_H_

#include <systemc>
#include <uvm>

// define transactions

#include "pkg.h"

class sequence_item : public uvm::uvm_sequence_item {
 public:
  uint32_t A;
  uint32_t B;
  int op;
  uint32_t result;
  
  sequence_item(const std::string& name = "sequence_item") : uvm::uvm_sequence_item(name) {}

  ~sequence_item() {}

  UVM_OBJECT_UTILS(sequence_item);

  void do_print(const::uvm::uvm_printer& printer) const {
    printer.print_string("op", op2str(op));
    printer.print_field_int("A", A);
    printer.print_field_int("B", B);
    printer.print_field_int("result", result);          
  }
};

class rsp : public sequence_item {
 public:
 rsp(const std::string& name = "random_rsp_item") : sequence_item(name) {}

  ~rsp() {}

  UVM_OBJECT_UTILS(rsp);
};

#endif
