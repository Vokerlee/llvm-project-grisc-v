//===-- GRISCVMCObjectFileInfo.cpp - griscv object file properties ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the GRISCVMCObjectFileInfo properties.
//
//===----------------------------------------------------------------------===//

#include "GRISCVObjectFileInfo.h"

using namespace llvm;

unsigned GRISCVMCObjectFileInfo::getTextSectionAlignment() const {
  return 4;
}
