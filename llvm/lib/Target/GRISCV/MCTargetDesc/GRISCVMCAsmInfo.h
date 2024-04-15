#ifndef __LLVM_LIB_TARGET_GRISCV_MCTARGETDESC_GRISCVMCASMINFO_H__
#define __LLVM_LIB_TARGET_GRISCV_MCTARGETDESC_GRISCVMCASMINFO_H__

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class GRISCVMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit GRISCVMCAsmInfo(const Triple &TT);
};

} // end namespace llvm

#endif // __LLVM_LIB_TARGET_GRISCV_MCTARGETDESC_GRISCVMCASMINFO_H__
