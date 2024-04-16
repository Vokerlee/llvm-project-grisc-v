let TargetPrefix = "griscv" in {  // All intrinsics start with "llvm.griscv.".

def int_griscv_rand: ClangBuiltin<"__builtin_griscv_rand">,
  Intrinsic<[llvm_i64_ty], [llvm_i64_ty], [IntrNoMem, IntrHasSideEffects]>;

def int_griscv_draw: ClangBuiltin<"__builtin_griscv_draw">,
  Intrinsic<[], [llvm_ptr_ty], [IntrNoMem, IntrHasSideEffects]>;

} // TargetPrefix = "griscv"
