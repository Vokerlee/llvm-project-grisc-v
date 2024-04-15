//===-- GRISCVELFStreamer.cpp - GRISCV ELF Target Streamer Methods ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides GRISCV specific target streamer methods.
//
//===----------------------------------------------------------------------===//

#include "GRISCVElfStreamer.h"
#include "GRISCVAsmBackend.h"
#include "GRISCVInfo.h"
#include "GRISCVMCTargetDesc.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCValue.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/Support/LEB128.h"
#include "llvm/Support/Casting.h"

using namespace llvm;

// This part is for ELF object output.
GRISCVTargetELFStreamer::GRISCVTargetELFStreamer(MCStreamer &S,
                                                 const MCSubtargetInfo &STI)
    : GRISCVTargetStreamer(S), CurrentVendor("GRISCV") {
  MCAssembler &MCA = getStreamer().getAssembler();
  auto &MAB = static_cast<GRISCVAsmBackend &>(MCA.getBackend());
  griscvABI::ABI ABI = MAB.getTargetABI();
  assert(ABI != griscvABI::ABI_Unknown && "Improperly initialised target ABI");

  unsigned EFlags = MCA.getELFHeaderEFlags();

  switch (ABI) {
  case griscvABI::ABI_LP64:
    break;
  case griscvABI::ABI_Unknown:
    llvm_unreachable("Improperly initialised target ABI");
  }

  MCA.setELFHeaderEFlags(EFlags);
}

MCELFStreamer &GRISCVTargetELFStreamer::getStreamer() {
  return static_cast<MCELFStreamer &>(Streamer);
}

void GRISCVTargetELFStreamer::emitDirectiveOptionPush() {}
void GRISCVTargetELFStreamer::emitDirectiveOptionPop() {}
void GRISCVTargetELFStreamer::emitDirectiveOptionPIC() {}
void GRISCVTargetELFStreamer::emitDirectiveOptionNoPIC() {}
void GRISCVTargetELFStreamer::emitDirectiveOptionRelax() {}
void GRISCVTargetELFStreamer::emitDirectiveOptionNoRelax() {}

void GRISCVTargetELFStreamer::emitAttribute(unsigned Attribute, unsigned Value) {
  setAttributeItem(Attribute, Value, /*OverwriteExisting=*/true);
}

void GRISCVTargetELFStreamer::emitTextAttribute(unsigned Attribute,
                                               StringRef String) {
  setAttributeItem(Attribute, String, /*OverwriteExisting=*/true);
}

void GRISCVTargetELFStreamer::emitIntTextAttribute(unsigned Attribute,
                                                  unsigned IntValue,
                                                  StringRef StringValue) {
  setAttributeItems(Attribute, IntValue, StringValue,
                    /*OverwriteExisting=*/true);
}

void GRISCVTargetELFStreamer::finishAttributeSection() {
  if (Contents.empty())
    return;

  if (AttributeSection) {
    Streamer.switchSection(AttributeSection);
  } else {
    MCAssembler &MCA = getStreamer().getAssembler();
    AttributeSection = MCA.getContext().getELFSection(
        ".GRISCV.attributes", ELF::SHT_GRISCV_ATTRIBUTES, 0);
    Streamer.switchSection(AttributeSection);

    Streamer.emitInt8(ELFAttrs::Format_Version);
  }

  // Vendor size + Vendor name + '\0'
  const size_t VendorHeaderSize = 4 + CurrentVendor.size() + 1;

  // Tag + Tag Size
  const size_t TagHeaderSize = 1 + 4;

  const size_t ContentsSize = calculateContentSize();

  Streamer.emitInt32(VendorHeaderSize + TagHeaderSize + ContentsSize);
  Streamer.emitBytes(CurrentVendor);
  Streamer.emitInt8(0); // '\0'

  Streamer.emitInt8(ELFAttrs::File);
  Streamer.emitInt32(TagHeaderSize + ContentsSize);

  // Size should have been accounted for already, now
  // emit each field as its type (ULEB or String).
  for (AttributeItem item : Contents) {
    Streamer.emitULEB128IntValue(item.Tag);
    switch (item.Type) {
    default:
      llvm_unreachable("Invalid attribute type");
    case AttributeType::Numeric:
      Streamer.emitULEB128IntValue(item.IntValue);
      break;
    case AttributeType::Text:
      Streamer.emitBytes(item.StringValue);
      Streamer.emitInt8(0); // '\0'
      break;
    case AttributeType::NumericAndText:
      Streamer.emitULEB128IntValue(item.IntValue);
      Streamer.emitBytes(item.StringValue);
      Streamer.emitInt8(0); // '\0'
      break;
    }
  }

  Contents.clear();
}

size_t GRISCVTargetELFStreamer::calculateContentSize() const {
  size_t Result = 0;
  for (AttributeItem item : Contents) {
    switch (item.Type) {
    case AttributeType::Hidden:
      break;
    case AttributeType::Numeric:
      Result += getULEB128Size(item.Tag);
      Result += getULEB128Size(item.IntValue);
      break;
    case AttributeType::Text:
      Result += getULEB128Size(item.Tag);
      Result += item.StringValue.size() + 1; // string + '\0'
      break;
    case AttributeType::NumericAndText:
      Result += getULEB128Size(item.Tag);
      Result += getULEB128Size(item.IntValue);
      Result += item.StringValue.size() + 1; // string + '\0';
      break;
    }
  }
  return Result;
}

namespace {
class GRISCVELFStreamer : public MCELFStreamer {
  static std::pair<unsigned, unsigned> getRelocPairForSize(unsigned Size) {
    switch (Size) {
    default:
      llvm_unreachable("unsupported fixup size");
    case 1:
      return std::make_pair(griscv::fixup_GRISCV_add_8, griscv::fixup_GRISCV_sub_8);
    case 2:
      return std::make_pair(griscv::fixup_GRISCV_add_16,
                            griscv::fixup_GRISCV_sub_16);
    case 4:
      return std::make_pair(griscv::fixup_GRISCV_add_32,
                            griscv::fixup_GRISCV_sub_32);
    case 8:
      return std::make_pair(griscv::fixup_GRISCV_add_64,
                            griscv::fixup_GRISCV_sub_64);
    }
  }

  static bool requiresFixups(MCContext &C, const MCExpr *Value,
                             const MCExpr *&LHS, const MCExpr *&RHS) {
    const auto *MBE = dyn_cast<MCBinaryExpr>(Value);
    if (MBE == nullptr)
      return false;

    MCValue E;
    if (!Value->evaluateAsRelocatable(E, nullptr, nullptr))
      return false;
    if (E.getSymA() == nullptr || E.getSymB() == nullptr)
      return false;

    const auto &A = E.getSymA()->getSymbol();
    const auto &B = E.getSymB()->getSymbol();

    LHS =
        MCBinaryExpr::create(MCBinaryExpr::Add, MCSymbolRefExpr::create(&A, C),
                             MCConstantExpr::create(E.getConstant(), C), C);
    RHS = E.getSymB();

    return (A.isInSection() ? A.getSection().hasInstructions()
                            : !A.getName().empty()) ||
           (B.isInSection() ? B.getSection().hasInstructions()
                            : !B.getName().empty());
  }

public:
  GRISCVELFStreamer(MCContext &C, std::unique_ptr<MCAsmBackend> MAB,
                    std::unique_ptr<MCObjectWriter> MOW,
                    std::unique_ptr<MCCodeEmitter> MCE)
      : MCELFStreamer(C, std::move(MAB), std::move(MOW), std::move(MCE)) {}

  void emitValueImpl(const MCExpr *Value, unsigned Size, SMLoc Loc) override {
    const MCExpr *A, *B;
    if (!requiresFixups(getContext(), Value, A, B))
      return MCELFStreamer::emitValueImpl(Value, Size, Loc);

    MCStreamer::emitValueImpl(Value, Size, Loc);

    MCDataFragment *DF = getOrCreateDataFragment();
    flushPendingLabels(DF, DF->getContents().size());
    MCDwarfLineEntry::make(this, getCurrentSectionOnly());

    unsigned Add, Sub;
    std::tie(Add, Sub) = getRelocPairForSize(Size);

    DF->getFixups().push_back(MCFixup::create(
        DF->getContents().size(), A, static_cast<MCFixupKind>(Add), Loc));
    DF->getFixups().push_back(MCFixup::create(
        DF->getContents().size(), B, static_cast<MCFixupKind>(Sub), Loc));

    DF->getContents().resize(DF->getContents().size() + Size, 0);
  }
};
} // namespace

namespace llvm {
MCELFStreamer *createGRISCVELFStreamer(MCContext &C,
                                       std::unique_ptr<MCAsmBackend> MAB,
                                       std::unique_ptr<MCObjectWriter> MOW,
                                       std::unique_ptr<MCCodeEmitter> MCE,
                                       bool RelaxAll) {
  GRISCVELFStreamer *S =
      new GRISCVELFStreamer(C, std::move(MAB), std::move(MOW), std::move(MCE));
  S->getAssembler().setRelaxAll(RelaxAll);
  return S;
}
} // namespace llvm
