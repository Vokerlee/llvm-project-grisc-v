#include "MCTargetDesc/GRISCVInfo.h"
#include "GRISCVRegisterInfo.h"
#include "GRISCVInstrsInfo.h"
#include "GRISCVSubtarget.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "GRISCVGenRegisterInfo.inc"

GRISCVRegisterInfo::GRISCVRegisterInfo() : GRISCVGenRegisterInfo(griscv::X1) {}

const MCPhysReg *GRISCVRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  if (MF->getFunction().getCallingConv() == CallingConv::GHC)
    return CSR_NoRegs_SaveList;
  if (MF->getFunction().hasFnAttribute("interrupt"))
    return CSR_Interrupt_SaveList;

  return CSR_ILP32_LP64_SaveList;
}

BitVector GRISCVRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  markSuperRegs(Reserved, griscv::X0); // zero
  markSuperRegs(Reserved, griscv::X2); // sp
  markSuperRegs(Reserved, griscv::X3); // gp
  markSuperRegs(Reserved, griscv::X4); // tp
  return Reserved;
}

bool GRISCVRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return false;
}

bool GRISCVRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                             int SPAdj, unsigned FIOperandNum,
                                             RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected non-zero SPAdj value");

  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  Register FrameReg;
  int Offset = getFrameLowering(MF)
                   ->getFrameIndexReference(MF, FrameIndex, FrameReg)
                   .getFixed();
  Offset += MI.getOperand(FIOperandNum + 1).getImm();

  if (!isInt<16>(Offset)) {
    llvm_unreachable("");
  }

  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false, false, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);

  return false;
}

Register GRISCVRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? griscv::X8 : griscv::X2;
}

const uint32_t *GRISCVRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                                         CallingConv::ID CC) const {
  auto &Subtarget = MF.getSubtarget<GRISCVSubtarget>();

  if (CC == CallingConv::GHC)
    return CSR_NoRegs_RegMask;

  switch (Subtarget.getTargetABI()) {
  default:
    llvm_unreachable("Unrecognized ABI");
  case griscvABI::ABI_LP64:
    return CSR_ILP32_LP64_RegMask;
  }
}
