add_llvm_component_group(GRISCV)

set(LLVM_TARGET_DEFINITIONS GRISCV.td)

tablegen(LLVM GRISCVGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM GRISCVGenInstrsInfo.inc -gen-instr-info)
tablegen(LLVM GRISCVGenCallingConv.inc -gen-callingconv)
tablegen(LLVM GRISCVGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM GRISCVGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM GRISCVGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM GRISCVGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM GRISCVGenMCCodeEmitter.inc -gen-emitter)

add_public_tablegen_target(GRISCVCommonTableGen)

add_llvm_target(GRISCVCodeGen
  GRISCVTargetMachine.cpp
  GRISCVSubtarget.cpp

  GRISCVRegisterInfo.cpp
  GRISCVInstrsInfo.cpp

  GRISCVISelLowering.cpp
  GRISCVFrameLowering.cpp

  GRISCVMatInt.cpp
  GRISCVISelDagToDag.cpp
  GRISCVAsmPrinter.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  CodeGenTypes
  Core
  MC
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
