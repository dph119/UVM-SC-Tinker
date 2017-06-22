#ifndef TINYALU_PKG_H_
#define TINYALU_PKG_H_

#include <string>

enum operation_t {
  no_op,
  add_op,
  and_op,
  xor_op,
  mul_op,
  rst_op
};

std::string op2str(int op) {
  switch(op) {
  case no_op: return "no_op";
  case and_op: return "and_op";
  case xor_op: return "xor_op";
  case mul_op: return "mul_op";
  case rst_op: return "rst_op";
  }
}

#endif
