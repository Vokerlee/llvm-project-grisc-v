#ifndef __LLVM_LIB_TARGET_SIM_SIMTARGETMACHINE_H__
#define __LLVM_LIB_TARGET_SIM_SIMTARGETMACHINE_H__

#include "GRISCVSubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class GRISCVTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  GRISCVSubtarget Subtarget;

public:
  GRISCVTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                    CodeGenOpt::Level OL, bool JIT);
  ~GRISCVTargetMachine() override;

  const GRISCVSubtarget *getSubtargetImpl() const { return &Subtarget; }
  const GRISCVSubtarget *getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
} // end namespace llvm

#endif // __LLVM_LIB_TARGET_SIM_SIMTARGETMACHINE_H__