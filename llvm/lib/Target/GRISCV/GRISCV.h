#ifndef __LLVM_LIB_TARGET_GRISCV_GRISCV_H__
#define __LLVM_LIB_TARGET_GRISCV_GRISCV_H__

#include "GRISCVRegisterInfo.h"
#include "MCTargetDesc/GRISCVMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class GRISCVTargetMachine;
class GRISCVSubtarget;

namespace GRISCV {
enum {
  GP = R0,
  RA = R1,
  SP = R2,
  FP = R3,
  BP = R4,
};
} // namespace GRISCV

} // namespace llvm

#endif // __LLVM_LIB_TARGET_GRISCV_GRISCV_H__
