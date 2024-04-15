//===-- GRISCVTargetStreamer.cpp - griscv Target Streamer Methods -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides griscv specific target streamer methods.
//
//===----------------------------------------------------------------------===//

#include "GRISCVInfo.h"
#include "GRISCVTargetStreamer.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/GRISCVAttributes.h"
#include "llvm/Support/GRISCVISAInfo.h"

using namespace llvm;

GRISCVTargetStreamer::GRISCVTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}

void GRISCVTargetStreamer::finish() { finishAttributeSection(); }

void GRISCVTargetStreamer::emitDirectiveOptionPush() {}
void GRISCVTargetStreamer::emitDirectiveOptionPop() {}
void GRISCVTargetStreamer::emitDirectiveOptionPIC() {}
void GRISCVTargetStreamer::emitDirectiveOptionNoPIC() {}
void GRISCVTargetStreamer::emitDirectiveOptionRelax() {}
void GRISCVTargetStreamer::emitDirectiveOptionNoRelax() {}
void GRISCVTargetStreamer::emitAttribute(unsigned Attribute, unsigned Value) {}
void GRISCVTargetStreamer::finishAttributeSection() {}
void GRISCVTargetStreamer::emitTextAttribute(unsigned Attribute,
                                             StringRef String) {}
void GRISCVTargetStreamer::emitIntTextAttribute(unsigned Attribute,
                                                unsigned IntValue,
                                                StringRef StringValue) {}

void GRISCVTargetStreamer::emitTargetAttributes(const MCSubtargetInfo &STI) {
  emitAttribute(GRISCVAttrs::STACK_ALIGN, GRISCVAttrs::ALIGN_16);

  unsigned XLen = 64;
  std::vector<std::string> FeatureVector;
  griscvFeatures::toFeatureVector(FeatureVector, STI.getFeatureBits());

  auto ParseResult = llvm::GRISCVISAInfo::parseFeatures(XLen, FeatureVector);
  if (!ParseResult) {
    /* Assume any error about features should handled earlier.  */
    consumeError(ParseResult.takeError());
    llvm_unreachable("Parsing feature error when emitTargetAttributes?");
  } else {
    auto &ISAInfo = *ParseResult;
    emitTextAttribute(GRISCVAttrs::ARCH, ISAInfo->toString());
  }
}

// This part is for ascii assembly output
GRISCVTargetAsmStreamer::GRISCVTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS)
    : GRISCVTargetStreamer(S), OS(OS) {}

void GRISCVTargetAsmStreamer::emitDirectiveOptionPush() {
  OS << "\t.option\tpush\n";
}

void GRISCVTargetAsmStreamer::emitDirectiveOptionPop() {
  OS << "\t.option\tpop\n";
}

void GRISCVTargetAsmStreamer::emitDirectiveOptionPIC() {
  OS << "\t.option\tpic\n";
}

void GRISCVTargetAsmStreamer::emitDirectiveOptionNoPIC() {
  OS << "\t.option\tnopic\n";
}

void GRISCVTargetAsmStreamer::emitDirectiveOptionRelax() {
  OS << "\t.option\trelax\n";
}

void GRISCVTargetAsmStreamer::emitDirectiveOptionNoRelax() {
  OS << "\t.option\tnorelax\n";
}

void GRISCVTargetAsmStreamer::emitAttribute(unsigned Attribute, unsigned Value) {
  OS << "\t.attribute\t" << Attribute << ", " << Twine(Value) << "\n";
}

void GRISCVTargetAsmStreamer::emitTextAttribute(unsigned Attribute,
                                                StringRef String) {
  OS << "\t.attribute\t" << Attribute << ", \"" << String << "\"\n";
}

void GRISCVTargetAsmStreamer::emitIntTextAttribute(unsigned Attribute,
                                                   unsigned IntValue,
                                                   StringRef StringValue) {}

void GRISCVTargetAsmStreamer::finishAttributeSection() {}
