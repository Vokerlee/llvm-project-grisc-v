; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-p:64:64-i64:64-i128:128-n32:64-S128"
target triple = "griscv"

; Function Attrs: noinline nounwind optnone
define dso_local i64 @test_rand(i64 noundef %arg1) #0 {
entry:
  %arg1.addr = alloca i64, align 8
  store i64 %arg1, ptr %arg1.addr, align 8
  %0 = load i64, ptr %arg1.addr, align 8
  %1 = call i64 @llvm.griscv.rand(i64 %0)
  ret i64 %1
}

; Function Attrs: nounwind
declare i64 @llvm.griscv.rand(i64) #1

; Function Attrs: noinline nounwind optnone
define dso_local ptr @test_get_frame() #0 {
entry:
  %0 = call ptr @llvm.griscv.gr.frame(i64 0)
  ret ptr %0
}

; Function Attrs: nounwind
declare ptr @llvm.griscv.gr.frame(i64) #1

; Function Attrs: noinline nounwind optnone
define dso_local void @test_flush() #0 {
entry:
  call void @llvm.griscv.gr.flush()
  ret void
}

; Function Attrs: nounwind
declare void @llvm.griscv.gr.flush() #1

; Function Attrs: noinline nounwind optnone
define dso_local i64 @test_call(i64 noundef %arg) #0 {
entry:
  %arg.addr = alloca i64, align 8
  %tmp = alloca i64, align 8
  store i64 %arg, ptr %arg.addr, align 8
  store i64 2, ptr %tmp, align 8
  %0 = load i64, ptr %arg.addr, align 8
  %1 = load i64, ptr %tmp, align 8
  %add = add nsw i64 %0, %1
  %call = call i64 @test_rand(i64 noundef %add)
  %add1 = add nsw i64 %call, 7
  ret i64 %add1
}

; Function Attrs: noinline nounwind optnone
define dso_local i64 @test_control_flow(i64 noundef %arg1, i64 noundef %arg2) #0 {
entry:
  %arg1.addr = alloca i64, align 8
  %arg2.addr = alloca i64, align 8
  %res = alloca i64, align 8
  store i64 %arg1, ptr %arg1.addr, align 8
  store i64 %arg2, ptr %arg2.addr, align 8
  store i64 1, ptr %res, align 8
  %0 = load i64, ptr %arg1.addr, align 8
  %1 = load i64, ptr %arg2.addr, align 8
  %cmp = icmp ne i64 %0, %1
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %2 = load i64, ptr %arg1.addr, align 8
  %3 = load i64, ptr %arg2.addr, align 8
  %mul = mul nsw i64 %2, %3
  store i64 %mul, ptr %res, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  %4 = load i64, ptr %arg1.addr, align 8
  %add = add nsw i64 %4, 10
  store i64 %add, ptr %arg1.addr, align 8
  %5 = load i64, ptr %arg1.addr, align 8
  %6 = load i64, ptr %arg2.addr, align 8
  %div = sdiv i64 %5, %6
  %7 = load i64, ptr %res, align 8
  %add1 = add nsw i64 %7, %div
  store i64 %add1, ptr %res, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %8 = load i64, ptr %res, align 8
  %9 = load i64, ptr %res, align 8
  %mul2 = mul nsw i64 %8, %9
  %10 = load i64, ptr %res, align 8
  %sub = sub nsw i64 %mul2, %10
  ret i64 %sub
}

; Function Attrs: noinline nounwind optnone
define dso_local i32 @test_imm_minus(i32 noundef %arg1) #0 {
entry:
  %arg1.addr = alloca i32, align 4
  %arg2 = alloca i32, align 4
  store i32 %arg1, ptr %arg1.addr, align 4
  store i32 1, ptr %arg2, align 4
  %0 = load i32, ptr %arg2, align 4
  %sub = sub nsw i32 0, %0
  ret i32 %sub
}

; Function Attrs: noinline nounwind optnone
define dso_local i64 @test_for_sum(i64 noundef %n_iters) #0 {
entry:
  %n_iters.addr = alloca i64, align 8
  %sum = alloca i64, align 8
  store i64 %n_iters, ptr %n_iters.addr, align 8
  store i64 0, ptr %sum, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %0 = load i64, ptr %n_iters.addr, align 8
  %tobool = icmp ne i64 %0, 0
  br i1 %tobool, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %1 = load i64, ptr %n_iters.addr, align 8
  %2 = load i64, ptr %sum, align 8
  %add = add nsw i64 %2, %1
  store i64 %add, ptr %sum, align 8
  %3 = load i64, ptr %n_iters.addr, align 8
  %sub = sub nsw i64 %3, 1
  store i64 %sub, ptr %n_iters.addr, align 8
  br label %while.cond, !llvm.loop !3

while.end:                                        ; preds = %while.cond
  %4 = load i64, ptr %sum, align 8
  ret i64 %4
}

; Function Attrs: noinline nounwind optnone
define dso_local i64 @test_for_for(i64 noundef %n_iters1, i64 noundef %n_iters2) #0 {
entry:
  %n_iters1.addr = alloca i64, align 8
  %n_iters2.addr = alloca i64, align 8
  %sum = alloca i64, align 8
  store i64 %n_iters1, ptr %n_iters1.addr, align 8
  store i64 %n_iters2, ptr %n_iters2.addr, align 8
  store i64 0, ptr %sum, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.end, %entry
  %0 = load i64, ptr %n_iters1.addr, align 8
  %tobool = icmp ne i64 %0, 0
  br i1 %tobool, label %while.body, label %while.end5

while.body:                                       ; preds = %while.cond
  br label %while.cond1

while.cond1:                                      ; preds = %while.body3, %while.body
  %1 = load i64, ptr %n_iters2.addr, align 8
  %tobool2 = icmp ne i64 %1, 0
  br i1 %tobool2, label %while.body3, label %while.end

while.body3:                                      ; preds = %while.cond1
  %2 = load i64, ptr %n_iters2.addr, align 8
  %3 = load i64, ptr %n_iters1.addr, align 8
  %mul = mul nsw i64 %2, %3
  %4 = load i64, ptr %sum, align 8
  %add = add nsw i64 %4, %mul
  store i64 %add, ptr %sum, align 8
  %5 = load i64, ptr %n_iters2.addr, align 8
  %sub = sub nsw i64 %5, 1
  store i64 %sub, ptr %n_iters2.addr, align 8
  br label %while.cond1, !llvm.loop !5

while.end:                                        ; preds = %while.cond1
  %6 = load i64, ptr %n_iters1.addr, align 8
  %sub4 = sub nsw i64 %6, 1
  store i64 %sub4, ptr %n_iters1.addr, align 8
  br label %while.cond, !llvm.loop !6

while.end5:                                       ; preds = %while.cond
  %7 = load i64, ptr %sum, align 8
  ret i64 %7
}

; Function Attrs: noinline nounwind optnone
define dso_local i64 @test_imm_div(i64 noundef %arg) #0 {
entry:
  %arg.addr = alloca i64, align 8
  store i64 %arg, ptr %arg.addr, align 8
  %0 = load i64, ptr %arg.addr, align 8
  %div = sdiv i64 %0, 9000
  ret i64 %div
}

; Function Attrs: noinline nounwind optnone
define dso_local i32 @test_int_vals(i32 noundef %arg, i64 noundef %arg2) #0 {
entry:
  %arg.addr = alloca i32, align 4
  %arg2.addr = alloca i64, align 8
  %kek = alloca i32, align 4
  %lol = alloca i32, align 4
  store i32 %arg, ptr %arg.addr, align 4
  store i64 %arg2, ptr %arg2.addr, align 8
  %0 = load i64, ptr %arg2.addr, align 8
  %conv = trunc i64 %0 to i32
  store i32 %conv, ptr %kek, align 4
  %1 = load i32, ptr %kek, align 4
  %2 = load i32, ptr %kek, align 4
  %mul = mul nsw i32 %1, %2
  store i32 %mul, ptr %lol, align 4
  %3 = load i64, ptr %arg2.addr, align 8
  %4 = load i32, ptr %arg.addr, align 4
  %conv1 = sext i32 %4 to i64
  %div = sdiv i64 %3, %conv1
  %5 = load i32, ptr %arg.addr, align 4
  %conv2 = sext i32 %5 to i64
  %add = add nsw i64 %div, %conv2
  %6 = load i32, ptr %lol, align 4
  %conv3 = sext i32 %6 to i64
  %sub = sub nsw i64 %add, %conv3
  %conv4 = trunc i64 %sub to i32
  ret i32 %conv4
}

attributes #0 = { noinline nounwind optnone "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #1 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{!"clang version 19.0.0git (https://github.com/Vokerlee/llvm-project-grisc-v.git aeb41931c739f22db142805825a4885eee96746a)"}
!3 = distinct !{!3, !4}
!4 = !{!"llvm.loop.mustprogress"}
!5 = distinct !{!5, !4}
!6 = distinct !{!6, !4}
