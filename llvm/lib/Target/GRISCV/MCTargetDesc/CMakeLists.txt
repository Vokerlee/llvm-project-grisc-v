add_llvm_component_library(LLVMGRISCVDesc
  GRISCVMCTargetDesc.cpp

  LINK_COMPONENTS
  GRISCVInfo
  MC
  Support

  ADD_TO_COMPONENT
  GRISCV
  )
