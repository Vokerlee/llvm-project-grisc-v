add_llvm_component_library(LLVMGRISCVInfo
  GRISCVTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  GRISCV
  )
