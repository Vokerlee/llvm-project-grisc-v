#ifndef __LLVM_LIB_TARGET_GRISCV_GRISCVREGISTERINFO_H__
#define __LLVM_LIB_TARGET_GRISCV_GRISCVREGISTERINFO_H__

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_ENUM
#define GET_REGINFO_HEADER
#include "GRISCVGenRegisterInfo.inc"

namespace llvm {

class TargetInstrInfo;
class GRISCVSubtarget;

struct GRISCVRegisterInfo : public GRISCVGenRegisterInfo {
public:
  GRISCVRegisterInfo();

  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;

  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const override;

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  bool requiresRegisterScavenging(const MachineFunction &MF) const override;

  bool eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;

  // Debug information queries.
  Register getFrameRegister(const MachineFunction &MF) const override;
};

} // end namespace llvm

#endif // __LLVM_LIB_TARGET_GRISCV_GRISCVREGISTERINFO_H__