#include "GRISCVSubtarget.h"
#include "GRISCV.h"

using namespace llvm;

#define DEBUG_TYPE "griscv-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "GRISCVGenSubtargetInfo.inc"

void GRISCVSubtarget::anchor() {}

// GRISCVSubtarget::GRISCVSubtarget(const Triple &TT, const std::string &CPU,
//                              const std::string &FS, const TargetMachine &TM)
//     : GRISCVGenSubtargetInfo(TT, CPU, /*TuneCPU=*/CPU, FS), InstrInfo(*this),
//       FrameLowering(*this), TLInfo(TM, *this) {}

GRISCVSubtarget::GRISCVSubtarget(const Triple &TT, const std::string &CPU,
                                 const std::string &FS, const TargetMachine &TM)
    : GRISCVGenSubtargetInfo(TT, CPU, /*TuneCPU=*/CPU, FS) {}
