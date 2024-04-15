#ifndef __LLVM_LIB_TARGET_SIM_SIMTARGETMACHINE_H__
#define __LLVM_LIB_TARGET_SIM_SIMTARGETMACHINE_H__

#include "GRISCVSubtarget.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/CodeGen.h"

namespace llvm {

class GRISCVTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  GRISCVSubtarget Subtarget;

public:
  GRISCVTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    std::optional<Reloc::Model> RM, std::optional<CodeModel::Model> CM,
                    CodeGenOptLevel OL, bool JIT);
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

  MachineFunctionInfo *
  createMachineFunctionInfo(BumpPtrAllocator &Allocator, const Function &F,
                            const TargetSubtargetInfo *STI) const override;
};

FunctionPass *createGRISCVISelDag(GRISCVTargetMachine &TM,
                                  CodeGenOptLevel OptLevel);

} // end namespace llvm

#endif // __LLVM_LIB_TARGET_SIM_SIMTARGETMACHINE_H__
