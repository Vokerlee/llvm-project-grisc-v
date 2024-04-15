//===----------------------------------------------------------------------===//
//
// Implements the info about GRISC-V target spec.
//
//===----------------------------------------------------------------------===//

#include "GRISCVTargetMachine.h"
#include "GRISCVMachineFunctionInfo.h"
#include "TargetInfo/GRISCVTargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"

#define DEBUG_TYPE "sim"

using namespace llvm;

static Reloc::Model getRelocModel(std::optional<Reloc::Model> RM,
                                  Reloc::Model Default) {
  if (RM) {
    return *RM;
  }
  return Default;
}

/// simTargetMachine ctor - Create an LP64 Architecture model
GRISCVTargetMachine::GRISCVTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         std::optional<Reloc::Model> RM,
                                         std::optional<CodeModel::Model> CM,
                                         CodeGenOptLevel OL, bool JIT)
    : LLVMTargetMachine(T,
                        "e-m:e-p:64:64-i64:64-i128:128-n32:64-S128",
                        TT, CPU, FS, Options, getRelocModel(RM, Reloc::Static),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

GRISCVTargetMachine::~GRISCVTargetMachine() = default;

MachineFunctionInfo *GRISCVTargetMachine::createMachineFunctionInfo(
    BumpPtrAllocator &Allocator, const Function &F,
    const TargetSubtargetInfo *STI) const {
  return GRISCVFunctionInfo::create<GRISCVFunctionInfo>(Allocator, F, STI);
}

namespace {

class GRISCVPassConfig : public TargetPassConfig {
public:
  GRISCVPassConfig(GRISCVTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  GRISCVTargetMachine &getGRISCVTargetMachine() const {
    return getTM<GRISCVTargetMachine>();
  }

  bool addInstSelector() override;
};

} // anonymous namespace

TargetPassConfig *GRISCVTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new GRISCVPassConfig(*this, PM);
}

bool GRISCVPassConfig::addInstSelector() {
  addPass(createGRISCVISelDag(getGRISCVTargetMachine(), getOptLevel()));
  return false;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeGRISCVTarget() {
  RegisterTargetMachine<GRISCVTargetMachine> X(getTheGRISCVTarget());
}
