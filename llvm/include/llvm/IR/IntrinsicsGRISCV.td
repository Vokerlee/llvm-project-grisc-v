let TargetPrefix = "griscv" in {  // All intrinsics start with "llvm.griscv.".

def int_griscv_rand: ClangBuiltin<"__builtin_griscv_rand">,
  Intrinsic<[llvm_i64_ty], [llvm_i64_ty], [IntrNoMem, IntrHasSideEffects]>;

def int_griscv_gr_frame: ClangBuiltin<"__builtin_griscv_gr_frame">,
  Intrinsic<[llvm_ptr_ty], [llvm_i64_ty], [IntrNoMem, IntrHasSideEffects]>;

def int_griscv_gr_flush: ClangBuiltin<"__builtin_griscv_gr_flush">,
  Intrinsic<[], [], [IntrNoMem, IntrHasSideEffects]>;

} // TargetPrefix = "griscv"
