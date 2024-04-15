//===-- GRISCVMCCodeEmitter.cpp - Convert GRISCV code to machine code -------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "GRISCVInfo.h"
#include "GRISCVFixupKinds.h"
#include "GRISCVMCExpr.h"
#include "GRISCVMCTargetDesc.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/raw_ostream.h"

#define GET_REGINFO_ENUM
#include "GRISCVGenRegisterInfo.inc"

#define GET_COMPUTE_FEATURES
#define GET_INSTRINFO_MC_HELPER_DECLS
#define GET_INSTRINFO_ENUM
#include "GRISCVGenInstrsInfo.inc"

using namespace llvm;

#define DEBUG_TYPE "mccodeemitter"

STATISTIC(MCNumEmitted, "Number of MC instructions emitted");
STATISTIC(MCNumFixups, "Number of MC fixups created");

namespace {
class GRISCVMCCodeEmitter : public MCCodeEmitter {
  GRISCVMCCodeEmitter(const GRISCVMCCodeEmitter &) = delete;
  void operator=(const GRISCVMCCodeEmitter &) = delete;
  MCContext &Ctx;
  MCInstrInfo const &MCII;

public:
  GRISCVMCCodeEmitter(MCContext &ctx, MCInstrInfo const &MCII)
      : Ctx(ctx), MCII(MCII) {}

  ~GRISCVMCCodeEmitter() override {}

  void encodeInstruction(const MCInst &MI, SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;

  void expandFunctionCall(const MCInst &MI, SmallVectorImpl<char> &CB,
                          SmallVectorImpl<MCFixup> &Fixups,
                          const MCSubtargetInfo &STI) const;

  // void expandAddTPRel(const MCInst &MI, raw_ostream &OS,
  //                     SmallVectorImpl<MCFixup> &Fixups,
  //                     const MCSubtargetInfo &STI) const;

  /// TableGen'erated function for getting the binary encoding for an
  /// instruction.
  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;

  /// Return binary encoding of operand. If the machine operand requires
  /// relocation, record the relocation and return zero.
  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;

  unsigned getImmOpValueAsr1(const MCInst &MI, unsigned OpNo,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;

  unsigned getImmOpValue(const MCInst &MI, unsigned OpNo,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const;
};
} // end anonymous namespace

MCCodeEmitter *llvm::createGRISCVMCCodeEmitter(const MCInstrInfo &MCII,
                                               MCContext &Ctx) {
  return new GRISCVMCCodeEmitter(Ctx, MCII);
}

void GRISCVMCCodeEmitter::expandFunctionCall(const MCInst &MI, SmallVectorImpl<char> &CB,
                                             SmallVectorImpl<MCFixup> &Fixups,
                                             const MCSubtargetInfo &STI) const {
  MCInst TmpInst;
  MCOperand Func;
  MCRegister Ra;
  uint32_t Binary;

  if (MI.getOpcode() == griscv::PseudoCALL) {
    Func = MI.getOperand(0);
    Ra = griscv::X1;
  }
  assert(Func.isExpr() && "Expected expression");

  const MCExpr *CallExpr = Func.getExpr();

  // Emit AUIPC Ra, Func with R_GRISCV_CALL relocation type.
  TmpInst = MCInstBuilder(griscv::AUIPC)
                .addReg(Ra)
                .addOperand(MCOperand::createExpr(CallExpr));
  Binary = getBinaryCodeForInstr(TmpInst, Fixups, STI);
  support::endian::write(CB, Binary, endianness::little);

  // Emit JALR Ra, Ra, 0
  TmpInst = MCInstBuilder(griscv::JALR).addReg(Ra).addReg(Ra).addImm(0);
  Binary = getBinaryCodeForInstr(TmpInst, Fixups, STI);
  support::endian::write(CB, Binary, endianness::little);
}

// Expand PseudoAddTPRel to a simple ADD with the correct relocation.
// void GRISCVMCCodeEmitter::expandAddTPRel(const MCInst &MI, raw_ostream &OS,
//                                          SmallVectorImpl<MCFixup> &Fixups,
//                                          const MCSubtargetInfo &STI) const {
//   MCOperand DestReg = MI.getOperand(0);
//   MCOperand SrcReg = MI.getOperand(1);
//   MCOperand TPReg = MI.getOperand(2);
//   assert(TPReg.isReg() && TPReg.getReg() == griscv::X4 &&
//          "Expected thread pointer as second input to TP-relative add");

//   MCOperand SrcSymbol = MI.getOperand(3);
//   assert(SrcSymbol.isExpr() &&
//          "Expected expression as third input to TP-relative add");

//   const GRISCVMCExpr *Expr = dyn_cast<GRISCVMCExpr>(SrcSymbol.getExpr());
//   assert(Expr && Expr->getKind() == GRISCVMCExpr::VK_GRISCV_TPREL_ADD &&
//          "Expected tprel_add relocation on TP-relative symbol");

//   // Emit the correct tprel_add relocation for the symbol.
//   Fixups.push_back(MCFixup::create(
//       0, Expr, MCFixupKind(griscv::fixup_GRISCV_tprel_add), MI.getLoc()));

//   // Emit a normal ADD instruction with the given operands.
//   MCInst TmpInst = MCInstBuilder(griscv::ADD)
//                        .addOperand(DestReg)
//                        .addOperand(SrcReg)
//                        .addOperand(TPReg);
//   uint32_t Binary = getBinaryCodeForInstr(TmpInst, Fixups, STI);
//   support::endian::write(OS, Binary, endianness::little);
// }

void GRISCVMCCodeEmitter::encodeInstruction(const MCInst &MI, SmallVectorImpl<char> &CB,
                                            SmallVectorImpl<MCFixup> &Fixups,
                                            const MCSubtargetInfo &STI) const {
  GRISCV_MC::verifyInstructionPredicates(MI.getOpcode(),
      GRISCV_MC::computeAvailableFeatures(STI.getFeatureBits()));

  const MCInstrDesc &Desc = MCII.get(MI.getOpcode());
  // Get byte count of instruction.
  unsigned Size = Desc.getSize();

  // GRISCVInstrInfo::getInstSizeInBytes expects that the total size of the
  // expanded instructions for each pseudo is correct in the Size field of the
  // tablegen definition for the pseudo.
  if (MI.getOpcode() == griscv::PseudoCALL) {
    expandFunctionCall(MI, CB, Fixups, STI);
    MCNumEmitted += 2;
    return;
  }

  switch (Size) {
  default:
    llvm_unreachable("Unhandled encodeInstruction length!");
  // case 2: {
  //   uint16_t Bits = getBinaryCodeForInstr(MI, Fixups, STI);
  //   support::endian::write<uint16_t>(CB, Bits, endianness::little);
  //   break;
  // }
  case 4: {
    uint32_t Bits = getBinaryCodeForInstr(MI, Fixups, STI);
    support::endian::write(CB, Bits, endianness::little);
    break;
  }
  }

  ++MCNumEmitted; // Keep track of the # of mi's emitted.
}

unsigned
GRISCVMCCodeEmitter::getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                                       SmallVectorImpl<MCFixup> &Fixups,
                                       const MCSubtargetInfo &STI) const {

  if (MO.isReg())
    return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg());

  if (MO.isImm())
    return static_cast<unsigned>(MO.getImm());

  llvm_unreachable("Unhandled expression!");
  return 0;
}

unsigned
GRISCVMCCodeEmitter::getImmOpValueAsr1(const MCInst &MI, unsigned OpNo,
                                       SmallVectorImpl<MCFixup> &Fixups,
                                       const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpNo);

  if (MO.isImm()) {
    unsigned Res = MO.getImm();
    assert((Res & 1) == 0 && "LSB is non-zero");
    return Res >> 1;
  }

  return getImmOpValue(MI, OpNo, Fixups, STI);
}

unsigned GRISCVMCCodeEmitter::getImmOpValue(const MCInst &MI, unsigned OpNo,
                                           SmallVectorImpl<MCFixup> &Fixups,
                                           const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpNo);

  MCInstrDesc const &Desc = MCII.get(MI.getOpcode());
  unsigned MIFrm = griscvII::getFormat(Desc.TSFlags);

  // If the destination is an immediate, there is nothing to do.
  if (MO.isImm())
    return MO.getImm();

  assert(MO.isExpr() &&
         "getImmOpValue expects only expressions or immediates");
  const MCExpr *Expr = MO.getExpr();
  MCExpr::ExprKind Kind = Expr->getKind();
  griscv::Fixups FixupKind = griscv::fixup_GRISCV_invalid;
  if (Kind == MCExpr::Target) {
    const GRISCVMCExpr *RVExpr = cast<GRISCVMCExpr>(Expr);

    switch (RVExpr->getKind()) {
    case GRISCVMCExpr::VK_GRISCV_None:
    case GRISCVMCExpr::VK_GRISCV_Invalid:
    case GRISCVMCExpr::VK_GRISCV_32_PCREL:
      llvm_unreachable("Unhandled fixup kind!");
    case GRISCVMCExpr::VK_GRISCV_TPREL_ADD:
      // tprel_add is only used to indicate that a relocation should be emitted
      // for an add instruction used in TP-relative addressing. It should not be
      // expanded as if representing an actual instruction operand and so to
      // encounter it here is an error.
      llvm_unreachable(
          "VK_GRISCV_TPREL_ADD should not represent an instruction operand");
    case GRISCVMCExpr::VK_GRISCV_LO:
      if (MIFrm == griscvII::InstFormatI)
        FixupKind = griscv::fixup_GRISCV_lo12_i;
      else if (MIFrm == griscvII::InstFormatS)
        FixupKind = griscv::fixup_GRISCV_lo12_s;
      else
        llvm_unreachable("VK_GRISCV_LO used with unexpected instruction format");
      break;
    case GRISCVMCExpr::VK_GRISCV_HI:
      FixupKind = griscv::fixup_GRISCV_hi20;
      break;
    case GRISCVMCExpr::VK_GRISCV_PCREL_LO:
      if (MIFrm == griscvII::InstFormatI)
        FixupKind = griscv::fixup_GRISCV_pcrel_lo12_i;
      else if (MIFrm == griscvII::InstFormatS)
        FixupKind = griscv::fixup_GRISCV_pcrel_lo12_s;
      else
        llvm_unreachable(
            "VK_GRISCV_PCREL_LO used with unexpected instruction format");
      break;
    case GRISCVMCExpr::VK_GRISCV_PCREL_HI:
      FixupKind = griscv::fixup_GRISCV_pcrel_hi20;
      break;
    case GRISCVMCExpr::VK_GRISCV_GOT_HI:
      FixupKind = griscv::fixup_GRISCV_got_hi20;
      break;
    case GRISCVMCExpr::VK_GRISCV_TPREL_LO:
      if (MIFrm == griscvII::InstFormatI)
        FixupKind = griscv::fixup_GRISCV_tprel_lo12_i;
      else if (MIFrm == griscvII::InstFormatS)
        FixupKind = griscv::fixup_GRISCV_tprel_lo12_s;
      else
        llvm_unreachable(
            "VK_GRISCV_TPREL_LO used with unexpected instruction format");
      break;
    case GRISCVMCExpr::VK_GRISCV_TPREL_HI:
      FixupKind = griscv::fixup_GRISCV_tprel_hi20;
      break;
    case GRISCVMCExpr::VK_GRISCV_TLS_GOT_HI:
      FixupKind = griscv::fixup_GRISCV_tls_got_hi20;
      break;
    case GRISCVMCExpr::VK_GRISCV_TLS_GD_HI:
      FixupKind = griscv::fixup_GRISCV_tls_gd_hi20;
      break;
    case GRISCVMCExpr::VK_GRISCV_CALL:
      FixupKind = griscv::fixup_GRISCV_call;
      break;
    case GRISCVMCExpr::VK_GRISCV_CALL_PLT:
      FixupKind = griscv::fixup_GRISCV_call_plt;
      break;
    }
  } else if (Kind == MCExpr::SymbolRef &&
             cast<MCSymbolRefExpr>(Expr)->getKind() == MCSymbolRefExpr::VK_None) {
    if (MIFrm == griscvII::InstFormatJ) {
      FixupKind = griscv::fixup_GRISCV_jal;
    } else if (MIFrm == griscvII::InstFormatB) {
      FixupKind = griscv::fixup_GRISCV_branch;
    } else {
      llvm_unreachable("Unhandled fixup");
    }
  }

  assert(FixupKind != griscv::fixup_GRISCV_invalid && "Unhandled expression!");

  Fixups.push_back(
      MCFixup::create(0, Expr, MCFixupKind(FixupKind), MI.getLoc()));
  ++MCNumFixups;

  return 0;
}

#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "GRISCVGenMCCodeEmitter.inc"
