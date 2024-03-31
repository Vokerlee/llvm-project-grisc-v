//===----------------------------------------------------------------------===//
// This is the top level entry point for the GRISCV target.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Target-dependent interfaces
//===----------------------------------------------------------------------===//

include "GRISCVRegisterInfo.td"

//===----------------------------------------------------------------------===//
// GRISCV processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

def GRISCV : Target {
//   let InstructionSet = GRISCVInstrInfo;
}
