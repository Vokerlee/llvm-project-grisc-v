#include "GRISCVRegisterInfo.h"
// #include "GRISCVInstrInfo.h"
// #include "GRISCVMachineFunctionInfo.h"
// #include "GRISCVSubtarget.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define DEBUG_TYPE "GRISCV-reg-info"
#define GET_REGINFO_TARGET_DESC

GRISCVRegisterInfo::GRISCVRegisterInfo() : GRISCVGenRegisterInfo(GRISCV::R1) {}

// const MCPhysReg *
// GRISCVRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
//   return CSR_GRISCV_SaveList;
// }

// TODO: check calling conv
BitVector GRISCVRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  Reserved.set(GRISCV::R0);
  Reserved.set(GRISCV::R1);
  Reserved.set(GRISCV::R2);
  Reserved.set(GRISCV::R3);
  return Reserved;
}

bool GRISCVRegisterInfo::requiresRegisterScavenging(
    const MachineFunction &MF) const {
  return false; // TODO: what for?
}

