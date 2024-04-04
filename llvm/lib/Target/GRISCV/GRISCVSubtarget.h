#ifndef __LLVM_LIB_TARGET_GRISCV_GRISCVSUBTARGET_H__
#define __LLVM_LIB_TARGET_GRISCV_GRISCVSUBTARGET_H__

#include "MCTargetDesc/GRISCVInfo.h"
#include "GRISCVRegisterInfo.h"
// #include "GRISCVFrameLowering.h"
// #include "GRISCVISelLowering.h"
// #include "GRISCVInstrInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include <string>

#define GET_SUBTARGETINFO_HEADER
#include "GRISCVGenSubtargetInfo.inc"

namespace llvm {

class TargetMachine;

class GRISCVSubtarget : public GRISCVGenSubtargetInfo {
  virtual void anchor();

  GRISCVRegisterInfo RegInfo;
  // GRISCVInstrInfo InstrInfo;
  // GRISCVFrameLowering FrameLowering;
  // GRISCVTargetLowering TLInfo;
  // SelectionDAGTargetInfo TSInfo;
  griscvABI::ABI TargetABI = griscvABI::ABI_LP64;
  MVT XLenVT = MVT::i64;
  unsigned XLen = 64;

public:
  GRISCVSubtarget(const Triple &TT, const std::string &CPU, const std::string &FS,
                  const TargetMachine &TM);

  // const griscvInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  // const griscvFrameLowering *getFrameLowering() const override {
  //   return &FrameLowering;
  // }
  // const griscvTargetLowering *getTargetLowering() const override {
  //   return &TLInfo;
  // }
  const GRISCVRegisterInfo *getRegisterInfo() const override { return &RegInfo; }
  // const SelectionDAGTargetInfo *getSelectionDAGInfo() const override {
  //   return &TSInfo;
  // }

  auto getTargetABI() const { return TargetABI; }
  auto getXLenVT() const { return XLenVT; }
  auto getXLen() const { return XLen; }
};

} // end namespace llvm

#endif // __LLVM_LIB_TARGET_GRISCV_GRISCVSUBTARGET_H__
