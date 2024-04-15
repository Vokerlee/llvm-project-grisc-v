//===----------------------------------------------------------------------===//
// This is the top level entry point for the GRISCV target.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// GRISCV Subtarget features
//===----------------------------------------------------------------------===//

defvar GRV64 = DefaultMode;

//===----------------------------------------------------------------------===//
// Target-dependent interfaces
//===----------------------------------------------------------------------===//

include "GRISCVRegisterInfo.td"

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "GRISCVSchedule.td"
include "GRISCVCallingConv.td"

include "GRISCVInstrsInfo.td"
def GRISCVInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// GRISCV processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

def GRISCVAsmParser : AsmParser {
  let ShouldEmitMatchRegisterAltName = 1;
  let AllowDuplicateRegisterNames = 1;
}

def GRISCV : Target {
  let InstructionSet = GRISCVInstrInfo;
}
