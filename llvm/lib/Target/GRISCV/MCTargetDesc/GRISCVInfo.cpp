#include "GRISCVInfo.h"

#define GET_REGINFO_ENUM
#include "GRISCVGenRegisterInfo.inc"

namespace llvm {
  namespace griscvABI {
    MCRegister getBPReg() { return griscv::X9; }
    MCRegister getSCSPReg() { return griscv::X18; }
  } // namespace griscvABI
} // namespace llvm
