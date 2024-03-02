add_llvm_component_group(GRISCV)

# Add tablegen in future here

add_llvm_target(GRISCVCodeGen
  GRISCVTargetMachine.cpp

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
