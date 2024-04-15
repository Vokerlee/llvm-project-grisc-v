//===-- GRISCVTargetStreamer.h - griscv Target Streamer ----------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_GRISCV_MCTARGETDESC_GRISCVTARGETSTREAMER_H
#define LLVM_LIB_TARGET_GRISCV_MCTARGETDESC_GRISCVTARGETSTREAMER_H

#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"

namespace llvm {

class formatted_raw_ostream;

class GRISCVTargetStreamer : public MCTargetStreamer {
public:
  GRISCVTargetStreamer(MCStreamer &S);
  void finish() override;

  virtual void emitDirectiveOptionPush();
  virtual void emitDirectiveOptionPop();
  virtual void emitDirectiveOptionPIC();
  virtual void emitDirectiveOptionNoPIC();
  virtual void emitDirectiveOptionRelax();
  virtual void emitDirectiveOptionNoRelax();

  virtual void emitAttribute(unsigned Attribute, unsigned Value);
  virtual void finishAttributeSection();
  virtual void emitTextAttribute(unsigned Attribute, StringRef String);
  virtual void emitIntTextAttribute(unsigned Attribute, unsigned IntValue,
                                    StringRef StringValue);

  void emitTargetAttributes(const MCSubtargetInfo &STI);
};

// This part is for ascii assembly output
class GRISCVTargetAsmStreamer : public GRISCVTargetStreamer {
  formatted_raw_ostream &OS;

  void finishAttributeSection() override;
  void emitAttribute(unsigned Attribute, unsigned Value) override;
  void emitTextAttribute(unsigned Attribute, StringRef String) override;
  void emitIntTextAttribute(unsigned Attribute, unsigned IntValue,
                            StringRef StringValue) override;

public:
  GRISCVTargetAsmStreamer(MCStreamer &S, formatted_raw_ostream &OS);

  void emitDirectiveOptionPush() override;
  void emitDirectiveOptionPop() override;
  void emitDirectiveOptionPIC() override;
  void emitDirectiveOptionNoPIC() override;
  void emitDirectiveOptionRelax() override;
  void emitDirectiveOptionNoRelax() override;
};

}

#endif // LLVM_LIB_TARGET_GRISCV_MCTARGETDESC_GRISCVTARGETSTREAMER_H
