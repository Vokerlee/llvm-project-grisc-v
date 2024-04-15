//===-- GRISCVAttributes.h - GRISCV Attributes --------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_SUPPORT_GRISCVATTRIBUTES_H
#define LLVM_SUPPORT_GRISCVATTRIBUTES_H

#include "llvm/Support/ELFAttributes.h"

namespace llvm {
namespace GRISCVAttrs {

const TagNameMap &getGRISCVAttributeTags();

enum AttrType : unsigned {
  // Attribute types in ELF/.GRISCV.attributes.
  STACK_ALIGN = 4,
  ARCH = 5,
  UNALIGNED_ACCESS = 6,
  PRIV_SPEC = 8,
  PRIV_SPEC_MINOR = 10,
  PRIV_SPEC_REVISION = 12,
};

enum StackAlign { ALIGN_4 = 4, ALIGN_16 = 16 };

enum { NOT_ALLOWED = 0, ALLOWED = 1 };

} // namespace GRISCVAttrs
} // namespace llvm

#endif // LLVM_SUPPORT_GRISCVATTRIBUTES_H
