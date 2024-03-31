//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the Sim register file
//===----------------------------------------------------------------------===//

// For tablegen(... -gen-emitter)  in CMakeLists.txt
class GriscvReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
}

//===----------------------------------------------------------------------===//
//@Registers
//===----------------------------------------------------------------------===//
//@ All registers definition
let Namespace = "GRISCV" in {
  //@ General Purpose Registers
  def R0    : GriscvReg<0,  "r0">,    DwarfRegNum<[0]>;  // gp
  def R1    : GriscvReg<1,  "r1">,    DwarfRegNum<[1]>;  // ra
  def R2    : GriscvReg<2,  "r2">,    DwarfRegNum<[2]>;  // sp
  def R3    : GriscvReg<3,  "r3">,    DwarfRegNum<[3]>;  // fp
  def R4    : GriscvReg<4,  "r4">,    DwarfRegNum<[4]>;  // bp
  def R5    : GriscvReg<5,  "r5">,    DwarfRegNum<[5]>;  // s0
  def R6    : GriscvReg<6,  "r6">,    DwarfRegNum<[6]>;  // s1
  def R7    : GriscvReg<7,  "r7">,    DwarfRegNum<[7]>;  // s2
  def R8    : GriscvReg<8,  "r8">,    DwarfRegNum<[8]>;  // s3
  def R9    : GriscvReg<9,  "r9">,    DwarfRegNum<[9]>;  // a0
  def R10   : GriscvReg<10, "r10">,   DwarfRegNum<[10]>; // a1
  def R11   : GriscvReg<11, "r11">,   DwarfRegNum<[11]>; // a2
  def R12   : GriscvReg<12, "r12">,   DwarfRegNum<[12]>; // a3
  def R13   : GriscvReg<13, "r13">,   DwarfRegNum<[13]>; // t0
  def R14   : GriscvReg<14, "r14">,   DwarfRegNum<[14]>; // t1
  def R15   : GriscvReg<15, "r15">,   DwarfRegNum<[15]>; // t2
}

//===----------------------------------------------------------------------===//
//@Register Classes
//===----------------------------------------------------------------------===//

def GPR : RegisterClass<"GRISCV", [i32], 32, (add
  R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15)>;
