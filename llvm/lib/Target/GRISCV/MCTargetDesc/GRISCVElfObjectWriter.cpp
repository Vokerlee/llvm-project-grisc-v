//===-- GRISCVELFObjectWriter.cpp - GRISCV ELF Writer -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/GRISCVFixupKinds.h"
#include "MCTargetDesc/GRISCVMCExpr.h"
#include "MCTargetDesc/GRISCVMCTargetDesc.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class GRISCVELFObjectWriter : public MCELFObjectTargetWriter {
public:
  GRISCVELFObjectWriter(uint8_t OSABI, bool Is64Bit);

  ~GRISCVELFObjectWriter() override;

  // Return true if the given relocation must be with a symbol rather than
  // section plus offset.
  bool needsRelocateWithSymbol(const MCValue &Val, const MCSymbol &Sym,
                               unsigned Type) const override {
    return true;
  }

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
};
}

GRISCVELFObjectWriter::GRISCVELFObjectWriter(uint8_t OSABI, bool Is64Bit)
    : MCELFObjectTargetWriter(Is64Bit, OSABI, ELF::EM_GRISCV,
                              /*HasRelocationAddend*/ true) {}

GRISCVELFObjectWriter::~GRISCVELFObjectWriter() {}

unsigned GRISCVELFObjectWriter::getRelocType(MCContext &Ctx,
                                             const MCValue &Target,
                                             const MCFixup &Fixup,
                                             bool IsPCRel) const {
  const MCExpr *Expr = Fixup.getValue();
  // Determine the type of the relocation
  unsigned Kind = Fixup.getTargetKind();
  if (Kind >= FirstLiteralRelocationKind)
    return Kind - FirstLiteralRelocationKind;
  if (IsPCRel) {
    switch (Kind) {
    default:
      Ctx.reportError(Fixup.getLoc(), "Unsupported relocation type");
      return ELF::R_GRISCV_NONE;
    case FK_Data_4:
    case FK_PCRel_4:
      return ELF::R_GRISCV_32_PCREL;
    case griscv::fixup_GRISCV_pcrel_hi20:
      return ELF::R_GRISCV_PCREL_HI20;
    case griscv::fixup_GRISCV_pcrel_lo12_i:
      return ELF::R_GRISCV_PCREL_LO12_I;
    case griscv::fixup_GRISCV_pcrel_lo12_s:
      return ELF::R_GRISCV_PCREL_LO12_S;
    case griscv::fixup_GRISCV_got_hi20:
      return ELF::R_GRISCV_GOT_HI20;
    case griscv::fixup_GRISCV_tls_got_hi20:
      return ELF::R_GRISCV_TLS_GOT_HI20;
    case griscv::fixup_GRISCV_tls_gd_hi20:
      return ELF::R_GRISCV_TLS_GD_HI20;
    case griscv::fixup_GRISCV_jal:
      return ELF::R_GRISCV_JAL;
    case griscv::fixup_GRISCV_branch:
      return ELF::R_GRISCV_BRANCH;
    case griscv::fixup_GRISCV_call:
      return ELF::R_GRISCV_CALL;
    case griscv::fixup_GRISCV_call_plt:
      return ELF::R_GRISCV_CALL_PLT;
    case griscv::fixup_GRISCV_add_8:
      return ELF::R_GRISCV_ADD8;
    case griscv::fixup_GRISCV_sub_8:
      return ELF::R_GRISCV_SUB8;
    case griscv::fixup_GRISCV_add_16:
      return ELF::R_GRISCV_ADD16;
    case griscv::fixup_GRISCV_sub_16:
      return ELF::R_GRISCV_SUB16;
    case griscv::fixup_GRISCV_add_32:
      return ELF::R_GRISCV_ADD32;
    case griscv::fixup_GRISCV_sub_32:
      return ELF::R_GRISCV_SUB32;
    case griscv::fixup_GRISCV_add_64:
      return ELF::R_GRISCV_ADD64;
    case griscv::fixup_GRISCV_sub_64:
      return ELF::R_GRISCV_SUB64;
    }
  }

  switch (Kind) {
  default:
    Ctx.reportError(Fixup.getLoc(), "Unsupported relocation type");
    return ELF::R_GRISCV_NONE;
  case FK_Data_1:
    Ctx.reportError(Fixup.getLoc(), "1-byte data relocations not supported");
    return ELF::R_GRISCV_NONE;
  case FK_Data_2:
    Ctx.reportError(Fixup.getLoc(), "2-byte data relocations not supported");
    return ELF::R_GRISCV_NONE;
  case FK_Data_4:
    if (Expr->getKind() == MCExpr::Target &&
        cast<GRISCVMCExpr>(Expr)->getKind() == GRISCVMCExpr::VK_GRISCV_32_PCREL)
      return ELF::R_GRISCV_32_PCREL;
    return ELF::R_GRISCV_32;
  case FK_Data_8:
    return ELF::R_GRISCV_64;
  case griscv::fixup_GRISCV_hi20:
    return ELF::R_GRISCV_HI20;
  case griscv::fixup_GRISCV_lo12_i:
    return ELF::R_GRISCV_LO12_I;
  case griscv::fixup_GRISCV_lo12_s:
    return ELF::R_GRISCV_LO12_S;
  case griscv::fixup_GRISCV_tprel_hi20:
    return ELF::R_GRISCV_TPREL_HI20;
  case griscv::fixup_GRISCV_tprel_lo12_i:
    return ELF::R_GRISCV_TPREL_LO12_I;
  case griscv::fixup_GRISCV_tprel_lo12_s:
    return ELF::R_GRISCV_TPREL_LO12_S;
  case griscv::fixup_GRISCV_tprel_add:
    return ELF::R_GRISCV_TPREL_ADD;
  case griscv::fixup_GRISCV_relax:
    return ELF::R_GRISCV_RELAX;
  case griscv::fixup_GRISCV_align:
    return ELF::R_GRISCV_ALIGN;
  case griscv::fixup_GRISCV_set_6b:
    return ELF::R_GRISCV_SET6;
  case griscv::fixup_GRISCV_sub_6b:
    return ELF::R_GRISCV_SUB6;
  case griscv::fixup_GRISCV_add_8:
    return ELF::R_GRISCV_ADD8;
  case griscv::fixup_GRISCV_set_8:
    return ELF::R_GRISCV_SET8;
  case griscv::fixup_GRISCV_sub_8:
    return ELF::R_GRISCV_SUB8;
  case griscv::fixup_GRISCV_set_16:
    return ELF::R_GRISCV_SET16;
  case griscv::fixup_GRISCV_add_16:
    return ELF::R_GRISCV_ADD16;
  case griscv::fixup_GRISCV_sub_16:
    return ELF::R_GRISCV_SUB16;
  case griscv::fixup_GRISCV_set_32:
    return ELF::R_GRISCV_SET32;
  case griscv::fixup_GRISCV_add_32:
    return ELF::R_GRISCV_ADD32;
  case griscv::fixup_GRISCV_sub_32:
    return ELF::R_GRISCV_SUB32;
  case griscv::fixup_GRISCV_add_64:
    return ELF::R_GRISCV_ADD64;
  case griscv::fixup_GRISCV_sub_64:
    return ELF::R_GRISCV_SUB64;
  }
}

std::unique_ptr<MCObjectTargetWriter>
llvm::createGRISCVELFObjectWriter(uint8_t OSABI, bool Is64Bit) {
  return std::make_unique<GRISCVELFObjectWriter>(OSABI, Is64Bit);
}
