add_llvm_component_group(GRISCV)

set(LLVM_TARGET_DEFINITIONS GRISCV.td)

tablegen(LLVM GRISCVGenRegisterInfo.inc -gen-register-info)

add_public_tablegen_target(GRISCVCommonTableGen)

add_llvm_target(GRISCVCodeGen
  GRISCVTargetMachine.cpp
  GRISCVRegisterInfo.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  CodeGenTypes
  Core
  GlobalISel
  GRISCVInfo
  Scalar
  SelectionDAG
  Support
  Target
  TargetParser

  ADD_TO_COMPONENT
  GRISCV
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
