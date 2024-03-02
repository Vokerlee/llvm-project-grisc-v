//===-- GRISCVTargetInfo.cpp - GRISC-V Target Implementation ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/GRISCVTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheGRISCVTarget() {
  static Target TheGRISCVTarget;
  return TheGRISCVTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeGRISCVTargetInfo() {
  RegisterTarget<Triple::griscv, /*HasJIT=*/false> X(
        getTheGRISCVTarget(), "griscv", "64-bit GRISC-V", "GRISCV");
}
