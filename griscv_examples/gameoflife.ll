; ModuleID = 'gameoflife.c'
source_filename = "gameoflife.c"
target datalayout = "e-m:e-p:64:64-i64:64-i128:128-n32:64-S128"
target triple = "griscv"

; Function Attrs: noinline nounwind optnone
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %width = alloca i64, align 8
  %height = alloca i64, align 8
  %bytes_per_pixel = alloca i64, align 8
  %seed = alloca i64, align 8
  %n_max_iters = alloca i64, align 8
  %frame = alloca ptr, align 8
  %index = alloca i64, align 8
  %y = alloca i64, align 8
  %x = alloca i64, align 8
  %i = alloca i64, align 8
  %j = alloca i64, align 8
  %y16 = alloca i64, align 8
  %x21 = alloca i64, align 8
  %n_neighbours = alloca i64, align 8
  store i32 0, ptr %retval, align 4
  store i64 1080, ptr %width, align 8
  store i64 720, ptr %height, align 8
  store i64 4, ptr %bytes_per_pixel, align 8
  store i64 42, ptr %seed, align 8
  store i64 1000, ptr %n_max_iters, align 8
  %0 = call ptr @llvm.griscv.gr.frame(i64 0)
  store ptr %0, ptr %frame, align 8
  store i64 0, ptr %index, align 8
  %1 = load i64, ptr %height, align 8
  %sub = sub nsw i64 %1, 1
  store i64 %sub, ptr %y, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.end, %entry
  %2 = load i64, ptr %y, align 8
  %tobool = icmp ne i64 %2, 0
  br i1 %tobool, label %while.body, label %while.end12

while.body:                                       ; preds = %while.cond
  %3 = load i64, ptr %width, align 8
  %sub1 = sub nsw i64 %3, 1
  store i64 %sub1, ptr %x, align 8
  br label %while.cond2

while.cond2:                                      ; preds = %while.body4, %while.body
  %4 = load i64, ptr %x, align 8
  %tobool3 = icmp ne i64 %4, 0
  br i1 %tobool3, label %while.body4, label %while.end

while.body4:                                      ; preds = %while.cond2
  %5 = load i64, ptr %bytes_per_pixel, align 8
  %6 = load i64, ptr %width, align 8
  %7 = load i64, ptr %y, align 8
  %mul = mul nsw i64 %6, %7
  %8 = load i64, ptr %x, align 8
  %add = add nsw i64 %mul, %8
  %mul5 = mul nsw i64 %5, %add
  store i64 %mul5, ptr %index, align 8
  %9 = load ptr, ptr %frame, align 8
  %10 = load i64, ptr %index, align 8
  %add6 = add nsw i64 %10, 3
  %arrayidx = getelementptr inbounds i8, ptr %9, i64 %add6
  store i8 -1, ptr %arrayidx, align 1
  %11 = load i64, ptr %seed, align 8
  %12 = call i64 @llvm.griscv.rand(i64 %11)
  %and = and i64 %12, 1
  %mul7 = mul nsw i64 170, %and
  %conv = trunc i64 %mul7 to i8
  %13 = load ptr, ptr %frame, align 8
  %14 = load i64, ptr %index, align 8
  %add8 = add nsw i64 %14, 1
  %arrayidx9 = getelementptr inbounds i8, ptr %13, i64 %add8
  store i8 %conv, ptr %arrayidx9, align 1
  %15 = load i64, ptr %x, align 8
  %sub10 = sub nsw i64 %15, 1
  store i64 %sub10, ptr %x, align 8
  br label %while.cond2, !llvm.loop !3

while.end:                                        ; preds = %while.cond2
  %16 = load i64, ptr %y, align 8
  %sub11 = sub nsw i64 %16, 1
  store i64 %sub11, ptr %y, align 8
  br label %while.cond, !llvm.loop !5

while.end12:                                      ; preds = %while.cond
  call void @llvm.griscv.gr.flush()
  store i64 0, ptr %i, align 8
  store i64 0, ptr %j, align 8
  br label %while.cond13

while.cond13:                                     ; preds = %while.end94, %while.end12
  %17 = load i64, ptr %n_max_iters, align 8
  %tobool14 = icmp ne i64 %17, 0
  br i1 %tobool14, label %while.body15, label %while.end96

while.body15:                                     ; preds = %while.cond13
  %18 = load i64, ptr %height, align 8
  %sub17 = sub nsw i64 %18, 1
  store i64 %sub17, ptr %y16, align 8
  br label %while.cond18

while.cond18:                                     ; preds = %while.end92, %while.body15
  %19 = load i64, ptr %y16, align 8
  %tobool19 = icmp ne i64 %19, 0
  br i1 %tobool19, label %while.body20, label %while.end94

while.body20:                                     ; preds = %while.cond18
  %20 = load i64, ptr %width, align 8
  %sub22 = sub nsw i64 %20, 1
  store i64 %sub22, ptr %x21, align 8
  br label %while.cond23

while.cond23:                                     ; preds = %if.end90, %while.body20
  %21 = load i64, ptr %x21, align 8
  %tobool24 = icmp ne i64 %21, 0
  br i1 %tobool24, label %while.body25, label %while.end92

while.body25:                                     ; preds = %while.cond23
  store i64 0, ptr %n_neighbours, align 8
  store i64 3, ptr %i, align 8
  br label %while.cond26

while.cond26:                                     ; preds = %while.end45, %while.body25
  %22 = load i64, ptr %i, align 8
  %tobool27 = icmp ne i64 %22, 0
  br i1 %tobool27, label %while.body28, label %while.end47

while.body28:                                     ; preds = %while.cond26
  store i64 3, ptr %j, align 8
  br label %while.cond29

while.cond29:                                     ; preds = %if.end, %while.body28
  %23 = load i64, ptr %j, align 8
  %tobool30 = icmp ne i64 %23, 0
  br i1 %tobool30, label %while.body31, label %while.end45

while.body31:                                     ; preds = %while.cond29
  %24 = load i64, ptr %bytes_per_pixel, align 8
  %25 = load i64, ptr %y16, align 8
  %26 = load i64, ptr %i, align 8
  %sub32 = sub nsw i64 %26, 2
  %add33 = add nsw i64 %25, %sub32
  %27 = load i64, ptr %height, align 8
  %add34 = add nsw i64 %add33, %27
  %28 = load i64, ptr %height, align 8
  %rem = srem i64 %add34, %28
  %29 = load i64, ptr %width, align 8
  %mul35 = mul nsw i64 %rem, %29
  %30 = load i64, ptr %x21, align 8
  %31 = load i64, ptr %j, align 8
  %sub36 = sub nsw i64 %31, 2
  %add37 = add nsw i64 %30, %sub36
  %32 = load i64, ptr %width, align 8
  %add38 = add nsw i64 %add37, %32
  %33 = load i64, ptr %width, align 8
  %rem39 = srem i64 %add38, %33
  %add40 = add nsw i64 %mul35, %rem39
  %mul41 = mul nsw i64 %24, %add40
  store i64 %mul41, ptr %index, align 8
  %34 = load ptr, ptr %frame, align 8
  %35 = load i64, ptr %index, align 8
  %add42 = add nsw i64 %35, 1
  %arrayidx43 = getelementptr inbounds i8, ptr %34, i64 %add42
  %36 = load i8, ptr %arrayidx43, align 1
  %tobool44 = icmp ne i8 %36, 0
  br i1 %tobool44, label %if.then, label %if.end

if.then:                                          ; preds = %while.body31
  %37 = load i64, ptr %n_neighbours, align 8
  %inc = add nsw i64 %37, 1
  store i64 %inc, ptr %n_neighbours, align 8
  br label %if.end

if.end:                                           ; preds = %if.then, %while.body31
  %38 = load i64, ptr %j, align 8
  %dec = add nsw i64 %38, -1
  store i64 %dec, ptr %j, align 8
  br label %while.cond29, !llvm.loop !6

while.end45:                                      ; preds = %while.cond29
  %39 = load i64, ptr %i, align 8
  %dec46 = add nsw i64 %39, -1
  store i64 %dec46, ptr %i, align 8
  br label %while.cond26, !llvm.loop !7

while.end47:                                      ; preds = %while.cond26
  %40 = load i64, ptr %bytes_per_pixel, align 8
  %41 = load i64, ptr %y16, align 8
  %42 = load i64, ptr %height, align 8
  %add48 = add nsw i64 %41, %42
  %43 = load i64, ptr %height, align 8
  %rem49 = srem i64 %add48, %43
  %44 = load i64, ptr %width, align 8
  %mul50 = mul nsw i64 %rem49, %44
  %45 = load i64, ptr %x21, align 8
  %46 = load i64, ptr %width, align 8
  %add51 = add nsw i64 %45, %46
  %47 = load i64, ptr %width, align 8
  %rem52 = srem i64 %add51, %47
  %add53 = add nsw i64 %mul50, %rem52
  %mul54 = mul nsw i64 %40, %add53
  store i64 %mul54, ptr %index, align 8
  %48 = load ptr, ptr %frame, align 8
  %49 = load i64, ptr %index, align 8
  %add55 = add nsw i64 %49, 1
  %arrayidx56 = getelementptr inbounds i8, ptr %48, i64 %add55
  %50 = load i8, ptr %arrayidx56, align 1
  %tobool57 = icmp ne i8 %50, 0
  br i1 %tobool57, label %if.then58, label %if.end60

if.then58:                                        ; preds = %while.end47
  %51 = load i64, ptr %n_neighbours, align 8
  %dec59 = add nsw i64 %51, -1
  store i64 %dec59, ptr %n_neighbours, align 8
  br label %if.end60

if.end60:                                         ; preds = %if.then58, %while.end47
  %52 = load i64, ptr %n_neighbours, align 8
  %cmp = icmp eq i64 %52, 3
  br i1 %cmp, label %if.then62, label %if.else

if.then62:                                        ; preds = %if.end60
  %53 = load ptr, ptr %frame, align 8
  %54 = load i64, ptr %index, align 8
  %add63 = add nsw i64 %54, 1
  %arrayidx64 = getelementptr inbounds i8, ptr %53, i64 %add63
  %55 = load i8, ptr %arrayidx64, align 1
  %conv65 = sext i8 %55 to i32
  %cmp66 = icmp eq i32 %conv65, 0
  br i1 %cmp66, label %if.then68, label %if.end71

if.then68:                                        ; preds = %if.then62
  %56 = load ptr, ptr %frame, align 8
  %57 = load i64, ptr %index, align 8
  %add69 = add nsw i64 %57, 1
  %arrayidx70 = getelementptr inbounds i8, ptr %56, i64 %add69
  store i8 -86, ptr %arrayidx70, align 1
  br label %if.end71

if.end71:                                         ; preds = %if.then68, %if.then62
  br label %if.end90

if.else:                                          ; preds = %if.end60
  %58 = load i64, ptr %n_neighbours, align 8
  %cmp72 = icmp eq i64 %58, 2
  br i1 %cmp72, label %if.then74, label %if.else79

if.then74:                                        ; preds = %if.else
  %59 = load ptr, ptr %frame, align 8
  %60 = load i64, ptr %index, align 8
  %add75 = add nsw i64 %60, 1
  %arrayidx76 = getelementptr inbounds i8, ptr %59, i64 %add75
  %61 = load i8, ptr %arrayidx76, align 1
  %62 = load ptr, ptr %frame, align 8
  %63 = load i64, ptr %index, align 8
  %add77 = add nsw i64 %63, 1
  %arrayidx78 = getelementptr inbounds i8, ptr %62, i64 %add77
  store i8 %61, ptr %arrayidx78, align 1
  br label %if.end89

if.else79:                                        ; preds = %if.else
  %64 = load ptr, ptr %frame, align 8
  %65 = load i64, ptr %index, align 8
  %add80 = add nsw i64 %65, 1
  %arrayidx81 = getelementptr inbounds i8, ptr %64, i64 %add80
  %66 = load i8, ptr %arrayidx81, align 1
  %conv82 = sext i8 %66 to i32
  %cmp83 = icmp ne i32 %conv82, 0
  br i1 %cmp83, label %if.then85, label %if.end88

if.then85:                                        ; preds = %if.else79
  %67 = load ptr, ptr %frame, align 8
  %68 = load i64, ptr %index, align 8
  %add86 = add nsw i64 %68, 1
  %arrayidx87 = getelementptr inbounds i8, ptr %67, i64 %add86
  store i8 0, ptr %arrayidx87, align 1
  br label %if.end88

if.end88:                                         ; preds = %if.then85, %if.else79
  br label %if.end89

if.end89:                                         ; preds = %if.end88, %if.then74
  br label %if.end90

if.end90:                                         ; preds = %if.end89, %if.end71
  %69 = load i64, ptr %x21, align 8
  %sub91 = sub nsw i64 %69, 1
  store i64 %sub91, ptr %x21, align 8
  br label %while.cond23, !llvm.loop !8

while.end92:                                      ; preds = %while.cond23
  %70 = load i64, ptr %y16, align 8
  %sub93 = sub nsw i64 %70, 1
  store i64 %sub93, ptr %y16, align 8
  br label %while.cond18, !llvm.loop !9

while.end94:                                      ; preds = %while.cond18
  call void @llvm.griscv.gr.flush()
  %71 = load i64, ptr %n_max_iters, align 8
  %sub95 = sub nsw i64 %71, 1
  store i64 %sub95, ptr %n_max_iters, align 8
  br label %while.cond13, !llvm.loop !10

while.end96:                                      ; preds = %while.cond13
  ret i32 0
}

; Function Attrs: nounwind
declare ptr @llvm.griscv.gr.frame(i64) #1

; Function Attrs: nounwind
declare i64 @llvm.griscv.rand(i64) #1

; Function Attrs: nounwind
declare void @llvm.griscv.gr.flush() #1

attributes #0 = { noinline nounwind optnone "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #1 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{!"clang version 19.0.0git (https://github.com/Vokerlee/llvm-project-grisc-v.git d0c146b49cd863979237d12f817d6cb6e033821a)"}
!3 = distinct !{!3, !4}
!4 = !{!"llvm.loop.mustprogress"}
!5 = distinct !{!5, !4}
!6 = distinct !{!6, !4}
!7 = distinct !{!7, !4}
!8 = distinct !{!8, !4}
!9 = distinct !{!9, !4}
!10 = distinct !{!10, !4}
