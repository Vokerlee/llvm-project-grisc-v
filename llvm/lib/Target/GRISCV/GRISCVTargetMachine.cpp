//===----------------------------------------------------------------------===//
//
// Implements the info about GRISC-V target spec.
//
//===----------------------------------------------------------------------===//

#include "GRISCVTargetMachine.h"
#include "TargetInfo/GRISCVTargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"

#define DEBUG_TYPE "sim"

using namespace llvm;

static Reloc::Model getRelocModel(Optional<Reloc::Model> RM) {
  return RM.getValueOr(Reloc::Static);
}

/// simTargetMachine ctor - Create an LP64 Architecture model
GRISCVTargetMachine::GRISCVTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         Optional<Reloc::Model> RM,
                                         Optional<CodeModel::Model> CM,
                                         CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T,
                        "e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i32:32:32-"
                        "f32:32:32-i64:32-f64:32-a:0:32-n32",
                        TT, CPU, FS, Options, getRelocModel(RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

GRISCVTargetMachine::~GRISCVTargetMachine() = default;

namespace {

class GRISCVPassConfig : public TargetPassConfig {
public:
  GRISCVPassConfig(GRISCVTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  GRISCVTargetMachine &getGRISCVTargetMachine() const {
    return getTM<GRISCVTargetMachine>();
  }

  // bool addInstSelector() override;
};

} // anonymous namespace

TargetPassConfig *GRISCVTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new GRISCVPassConfig(*this, PM);
}

bool GRISCVPassConfig::addInstSelector() {
  // addPass(createGRISCVISelDag(getGRISCVTargetMachine(), getOptLevel()));
  return false;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeGRISCVTarget() {
  RegisterTargetMachine<GRISCVTargetMachine> X(getTheGRISCVTarget());
}
