add_llvm_component_library(LLVMGRISCVDesc
  GRISCVMCTargetDesc.cpp
  GRISCVInfo.cpp

  GRISCVMCAsmInfo.cpp
  GRISCVMCExpr.cpp
  GRISCVObjectFileInfo.cpp
  GRISCVInstPrinter.cpp
  GRISCVTargetStreamer.cpp
  GRISCVAsmBackend.cpp
  GRISCVMCCodeEmitter.cpp
  GRISCVElfObjectWriter.cpp
  GRISCVElfStreamer.cpp

  LINK_COMPONENTS
  GRISCVInfo
  MC
  Support

  ADD_TO_COMPONENT
  GRISCV
  )
