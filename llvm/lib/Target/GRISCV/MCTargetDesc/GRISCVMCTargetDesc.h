//===-- GRISCVMCTargetDesc.h - GRISC-V Target Descriptions --------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides GRISC-V specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_GRISCV_MCTARGETDESC_GRISCVMCTARGETDESC_H
#define LLVM_LIB_TARGET_GRISCV_MCTARGETDESC_GRISCVMCTARGETDESC_H

#include "llvm/MC/MCTargetOptions.h"
#include <memory>

namespace llvm {
class Triple;
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class Target;

extern Target TheGRISCVTarget;

MCCodeEmitter *createGRISCVMCCodeEmitter(const MCInstrInfo &MCII,
                                         MCContext &Ctx);

std::unique_ptr<MCObjectTargetWriter> createGRISCVELFObjectWriter(uint8_t OSABI,
                                                                  bool Is64Bit);

MCAsmBackend *createGRISCVAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                     const MCRegisterInfo &MRI,
                                     const MCTargetOptions &Options);
} // namespace llvm

#endif // LLVM_LIB_TARGET_GRISCV_MCTARGETDESC_GRISCVMCTARGETDESC_H
