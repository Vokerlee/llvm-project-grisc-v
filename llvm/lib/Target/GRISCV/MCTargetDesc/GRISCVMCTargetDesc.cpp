//===-- GRISCVMCTargetDesc.cpp - GRISCV Target Descriptions -------------------===//
//
//                     The LLVM Compiler Infrastructure
//
//===----------------------------------------------------------------------===//
//
// This file provides GRISC-V specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "GRISCVInfo.h"
#include "GRISCVMCTargetDesc.h"
#include "TargetInfo/GRISCVTargetInfo.h"
#include "GRISCVInstPrinter.h"
#include "GRISCVElfStreamer.h"
#include "GRISCVObjectFileInfo.h"
#include "GRISCVMCAsmInfo.h"
#include "GRISCVTargetStreamer.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_REGINFO_ENUM
#define GET_REGINFO_MC_DESC
#include "GRISCVGenRegisterInfo.inc"

#define ENABLE_INSTR_PREDICATE_VERIFIER
#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_DESC
#include "GRISCVGenInstrsInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "GRISCVGenSubtargetInfo.inc"

static MCInstrInfo *createGRISCVMCInstrInfo() {
  auto *X = new MCInstrInfo();
  InitGRISCVMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createGRISCVMCRegisterInfo(const Triple &TT) {
  auto *X = new MCRegisterInfo();
  InitGRISCVMCRegisterInfo(X, griscv::X1);
  return X;
}

static MCSubtargetInfo *createGRISCVMCSubtargetInfo(const Triple &TT,
                                                    StringRef CPU, StringRef FS) {
  return createGRISCVMCSubtargetInfoImpl(TT, CPU, /*TuneCPU=*/CPU, FS);
}

static MCAsmInfo *createGRISCVMCAsmInfo(const MCRegisterInfo &MRI,
                                        const Triple &TT,
                                        const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new GRISCVMCAsmInfo(TT);
  MCRegister SP = MRI.getDwarfRegNum(griscv::X2, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createGRISCVMCInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
  return new GRISCVInstPrinter(MAI, MII, MRI);
}

static MCTargetStreamer *createGRISCVTargetAsmStreamer(MCStreamer &S,
                                                       formatted_raw_ostream &OS,
                                                       MCInstPrinter *InstPrint,
                                                       bool isVerboseAsm) {
  return new GRISCVTargetStreamer(S);
}

static MCObjectFileInfo *
createGRISCVMCObjectFileInfo(MCContext &Ctx, bool PIC,
                             bool LargeCodeModel = false) {
  MCObjectFileInfo *MOFI = new GRISCVMCObjectFileInfo();
  MOFI->initMCObjectFileInfo(Ctx, PIC, LargeCodeModel);
  return MOFI;
}

static MCTargetStreamer *
createGRISCVObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI) {
  const Triple &TT = STI.getTargetTriple();
  if (TT.isOSBinFormatELF())
    return new GRISCVTargetELFStreamer(S, STI);
  return nullptr;
}

class GRISCVMCInstrAnalysis : public MCInstrAnalysis {
public:
  explicit GRISCVMCInstrAnalysis(const MCInstrInfo *Info)
      : MCInstrAnalysis(Info) {}

  bool evaluateBranch(const MCInst &Inst, uint64_t Addr, uint64_t Size,
                      uint64_t &Target) const override {
    if (isConditionalBranch(Inst)) {
      int64_t Imm;
      if (Size == 2)
        Imm = Inst.getOperand(1).getImm();
      else
        Imm = Inst.getOperand(2).getImm();
      Target = Addr + Imm;
      return true;
    }

    if (Inst.getOpcode() == griscv::JAL) {
      Target = Addr + Inst.getOperand(1).getImm();
      return true;
    }

    return false;
  }
};

static MCInstrAnalysis *createGRISCVInstrAnalysis(const MCInstrInfo *Info) {
  return new GRISCVMCInstrAnalysis(Info);
}

static MCTargetStreamer *createGRISCVNullTargetStreamer(MCStreamer &S) {
  return new GRISCVTargetStreamer(S);
}

namespace {
MCStreamer *createGRISCVELFStreamer(const Triple &T, MCContext &Context,
                                    std::unique_ptr<MCAsmBackend> &&MAB,
                                    std::unique_ptr<MCObjectWriter> &&MOW,
                                    std::unique_ptr<MCCodeEmitter> &&MCE,
                                    bool RelaxAll) {
  return createGRISCVELFStreamer(Context, std::move(MAB), std::move(MOW),
                                 std::move(MCE), RelaxAll);
}
} // end anonymous namespace

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeGRISCVTargetMC() {
  // Register the MC asm info.
  Target &TheGRISCVTarget = getTheGRISCVTarget();
  RegisterMCAsmInfoFn X(TheGRISCVTarget, createGRISCVMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCObjectFileInfo(TheGRISCVTarget, createGRISCVMCObjectFileInfo);
  TargetRegistry::RegisterMCInstrInfo(TheGRISCVTarget, createGRISCVMCInstrInfo);
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheGRISCVTarget, createGRISCVMCRegisterInfo);

  TargetRegistry::RegisterMCAsmBackend(TheGRISCVTarget, createGRISCVAsmBackend);
  TargetRegistry::RegisterMCCodeEmitter(TheGRISCVTarget, createGRISCVMCCodeEmitter);
  TargetRegistry::RegisterMCInstPrinter(TheGRISCVTarget, createGRISCVMCInstPrinter);
  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheGRISCVTarget,
                                          createGRISCVMCSubtargetInfo);
  TargetRegistry::RegisterELFStreamer(TheGRISCVTarget, createGRISCVELFStreamer);
  TargetRegistry::RegisterObjectTargetStreamer(TheGRISCVTarget,
                                               createGRISCVObjectTargetStreamer);
  TargetRegistry::RegisterMCInstrAnalysis(TheGRISCVTarget, createGRISCVInstrAnalysis);
  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheGRISCVTarget, createGRISCVMCInstPrinter);

  TargetRegistry::RegisterAsmTargetStreamer(TheGRISCVTarget,
                                            createGRISCVTargetAsmStreamer);

  TargetRegistry::RegisterNullTargetStreamer(TheGRISCVTarget,
                                               createGRISCVNullTargetStreamer);
}
