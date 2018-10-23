; ModuleID = 'src/omp-for-nowait.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32* }

@.str = private unnamed_addr constant [22 x i8] c"Hello From thread %d\0A\00", align 1
@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.str1 = private unnamed_addr constant [16 x i8] c"Hello World %d\0A\00", align 1
@.str2 = private unnamed_addr constant [16 x i8] c"Hello Again %d\0A\00", align 1
@.str3 = private unnamed_addr constant [17 x i8] c"Second Hello %d\0A\00", align 1
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.str4 = private unnamed_addr constant [16 x i8] c"Final Hello %d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %agg.captured = alloca %struct.anon, align 8
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 0, i32* %retval
  %2 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 0
  store i32* %i, i32** %2, align 8
  %3 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %3)
  ret i32 0
}

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.(i32*, i32*, i8*) #0 {
entry:
  %.addr = alloca i32*, align 8
  %.addr1 = alloca i32*, align 8
  %.addr2 = alloca i8*, align 8
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %3 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %4 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %debug.ub = alloca i32, align 4
  %last = alloca i32, align 4
  %lb = alloca i32, align 4
  %ub = alloca i32, align 4
  %st = alloca i32, align 4
  %.idx. = alloca i32, align 4
  %i.private. = alloca i32, align 4
  %debug.ub8 = alloca i32, align 4
  %last9 = alloca i32, align 4
  %lb10 = alloca i32, align 4
  %ub11 = alloca i32, align 4
  %st12 = alloca i32, align 4
  %.idx.13 = alloca i32, align 4
  %i.private.14 = alloca i32, align 4
  %debug.ub30 = alloca i32, align 4
  %last31 = alloca i32, align 4
  %lb32 = alloca i32, align 4
  %ub33 = alloca i32, align 4
  %st34 = alloca i32, align 4
  %.idx.35 = alloca i32, align 4
  %i.private.36 = alloca i32, align 4
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %debug.ub53 = alloca i32, align 4
  %last54 = alloca i32, align 4
  %lb55 = alloca i32, align 4
  %ub56 = alloca i32, align 4
  %st57 = alloca i32, align 4
  %.idx.58 = alloca i32, align 4
  %i.private.59 = alloca i32, align 4
  store i32 1, i32* %st57
  store i32 1, i32* %last54
  store i32 1, i32* %st34
  store i32 1, i32* %last31
  store i32 1, i32* %st12
  store i32 1, i32* %last9
  store i32 1, i32* %st
  store i32 1, i32* %last
  store i32* %0, i32** %.addr, align 8
  store i32* %1, i32** %.addr1, align 8
  store i8* %2, i8** %.addr2, align 8
  %.__kmpc_global_thread_num. = load i32** %.addr
  %arg3 = load i8** %.addr2
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*
  %7 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 0
  %ref = load i32** %7, align 8
  %call = call i32 (...)* @omp_get_thread_num()
  %call3 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([22 x i8]* @.str, i32 0, i32 0), i32 %call)
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 10, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 10, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %entry
  %8 = load i32* %lb
  store i32 %8, i32* %.idx.
  %9 = load i32* %ub
  %10 = icmp slt i32 %9, 10
  %11 = select i1 %10, i32 %9, i32 10
  store i32 %11, i32* %ub
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.begin
  %12 = icmp sle i32 %8, 10
  br i1 %12, label %omp.lb.le.global_ub., label %omp.loop.end

omp.lb.le.global_ub.:                             ; preds = %omp.loop.main
  store i32 0, i32* %i.private., align 4
  %13 = load i32* %.idx., align 4
  %mul = mul nsw i32 %13, 1
  %14 = load i32* %i.private., align 4
  %add = add nsw i32 %14, %mul
  store i32 %add, i32* %i.private., align 4
  %.idx.4 = load i32* %.idx.
  %15 = load i32* %ub
  %omp.idx.le.ub = icmp sle i32 %.idx.4, %15
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %16 = load i32* %i.private., align 4
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([16 x i8]* @.str1, i32 0, i32 0), i32 %16)
  br label %omp.cont.block

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.6 = load i32* %.idx.
  %.next.idx. = add nsw i32 %.idx.6, 1
  store i32 %.next.idx., i32* %.idx.
  br label %omp.loop.main

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.)
  %.gtid.7 = load i32* %.__kmpc_global_thread_num.
  store i32 5, i32* %debug.ub8
  store i32 0, i32* %lb10
  store i32 5, i32* %ub11
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.7, i32 34, i32* %last9, i32* %lb10, i32* %ub11, i32* %st12, i32 1, i32 0)
  br label %omp.loop.begin15

omp.loop.begin15:                                 ; preds = %omp.loop.end
  %17 = load i32* %lb10
  store i32 %17, i32* %.idx.13
  %18 = load i32* %ub11
  %19 = icmp slt i32 %18, 5
  %20 = select i1 %19, i32 %18, i32 5
  store i32 %20, i32* %ub11
  br label %omp.loop.main16

omp.loop.main16:                                  ; preds = %omp.cont.block24, %omp.loop.begin15
  %21 = icmp sle i32 %17, 5
  br i1 %21, label %omp.lb.le.global_ub.17, label %omp.loop.end28

omp.lb.le.global_ub.17:                           ; preds = %omp.loop.main16
  store i32 0, i32* %i.private.14, align 4
  %22 = load i32* %.idx.13, align 4
  %mul18 = mul nsw i32 %22, 2
  %23 = load i32* %i.private.14, align 4
  %add19 = add nsw i32 %23, %mul18
  store i32 %add19, i32* %i.private.14, align 4
  %.idx.20 = load i32* %.idx.13
  %24 = load i32* %ub11
  %omp.idx.le.ub21 = icmp sle i32 %.idx.20, %24
  br i1 %omp.idx.le.ub21, label %omp.lb_ub.check_pass22, label %omp.loop.fini27

omp.lb_ub.check_pass22:                           ; preds = %omp.lb.le.global_ub.17
  %25 = load i32* %i.private.14, align 4
  %call23 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([16 x i8]* @.str2, i32 0, i32 0), i32 %25)
  br label %omp.cont.block24

omp.cont.block24:                                 ; preds = %omp.lb_ub.check_pass22
  %.idx.25 = load i32* %.idx.13
  %.next.idx.26 = add nsw i32 %.idx.25, 1
  store i32 %.next.idx.26, i32* %.idx.13
  br label %omp.loop.main16

omp.loop.fini27:                                  ; preds = %omp.lb.le.global_ub.17
  br label %omp.loop.end28

omp.loop.end28:                                   ; preds = %omp.loop.fini27, %omp.loop.main16
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.7)
  %.gtid.29 = load i32* %.__kmpc_global_thread_num.
  store i32 4, i32* %debug.ub30
  store i32 0, i32* %lb32
  store i32 4, i32* %ub33
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.29, i32 34, i32* %last31, i32* %lb32, i32* %ub33, i32* %st34, i32 1, i32 0)
  br label %omp.loop.begin37

omp.loop.begin37:                                 ; preds = %omp.loop.end28
  %26 = load i32* %lb32
  store i32 %26, i32* %.idx.35
  %27 = load i32* %ub33
  %28 = icmp slt i32 %27, 4
  %29 = select i1 %28, i32 %27, i32 4
  store i32 %29, i32* %ub33
  br label %omp.loop.main38

omp.loop.main38:                                  ; preds = %omp.cont.block46, %omp.loop.begin37
  %30 = icmp sle i32 %26, 4
  br i1 %30, label %omp.lb.le.global_ub.39, label %omp.loop.end50

omp.lb.le.global_ub.39:                           ; preds = %omp.loop.main38
  store i32 0, i32* %i.private.36, align 4
  %31 = load i32* %.idx.35, align 4
  %mul40 = mul nsw i32 %31, 3
  %32 = load i32* %i.private.36, align 4
  %add41 = add nsw i32 %32, %mul40
  store i32 %add41, i32* %i.private.36, align 4
  %.idx.42 = load i32* %.idx.35
  %33 = load i32* %ub33
  %omp.idx.le.ub43 = icmp sle i32 %.idx.42, %33
  br i1 %omp.idx.le.ub43, label %omp.lb_ub.check_pass44, label %omp.loop.fini49

omp.lb_ub.check_pass44:                           ; preds = %omp.lb.le.global_ub.39
  %34 = load i32* %i.private.36, align 4
  %call45 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([17 x i8]* @.str3, i32 0, i32 0), i32 %34)
  br label %omp.cont.block46

omp.cont.block46:                                 ; preds = %omp.lb_ub.check_pass44
  %.idx.47 = load i32* %.idx.35
  %.next.idx.48 = add nsw i32 %.idx.47, 1
  store i32 %.next.idx.48, i32* %.idx.35
  br label %omp.loop.main38

omp.loop.fini49:                                  ; preds = %omp.lb.le.global_ub.39
  br label %omp.loop.end50

omp.loop.end50:                                   ; preds = %omp.loop.fini49, %omp.loop.main38
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.29)
  %.gtid.51 = load i32* %.__kmpc_global_thread_num.
  %35 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.51)
  %36 = icmp ne i32 %35, 0
  br i1 %36, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end50
  br label %omp.cancel_barrier.continue79

omp.cancel_barrier.continue:                      ; preds = %omp.loop.end50
  %.gtid.52 = load i32* %.__kmpc_global_thread_num.
  store i32 3, i32* %debug.ub53
  store i32 0, i32* %lb55
  store i32 3, i32* %ub56
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.52, i32 34, i32* %last54, i32* %lb55, i32* %ub56, i32* %st57, i32 1, i32 0)
  br label %omp.loop.begin60

omp.loop.begin60:                                 ; preds = %omp.cancel_barrier.continue
  %37 = load i32* %lb55
  store i32 %37, i32* %.idx.58
  %38 = load i32* %ub56
  %39 = icmp slt i32 %38, 3
  %40 = select i1 %39, i32 %38, i32 3
  store i32 %40, i32* %ub56
  br label %omp.loop.main61

omp.loop.main61:                                  ; preds = %omp.cont.block69, %omp.loop.begin60
  %41 = icmp sle i32 %37, 3
  br i1 %41, label %omp.lb.le.global_ub.62, label %omp.loop.end73

omp.lb.le.global_ub.62:                           ; preds = %omp.loop.main61
  store i32 0, i32* %i.private.59, align 4
  %42 = load i32* %.idx.58, align 4
  %mul63 = mul nsw i32 %42, 4
  %43 = load i32* %i.private.59, align 4
  %add64 = add nsw i32 %43, %mul63
  store i32 %add64, i32* %i.private.59, align 4
  %.idx.65 = load i32* %.idx.58
  %44 = load i32* %ub56
  %omp.idx.le.ub66 = icmp sle i32 %.idx.65, %44
  br i1 %omp.idx.le.ub66, label %omp.lb_ub.check_pass67, label %omp.loop.fini72

omp.lb_ub.check_pass67:                           ; preds = %omp.lb.le.global_ub.62
  %45 = load i32* %i.private.59, align 4
  %call68 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([16 x i8]* @.str4, i32 0, i32 0), i32 %45)
  br label %omp.cont.block69

omp.cont.block69:                                 ; preds = %omp.lb_ub.check_pass67
  %.idx.70 = load i32* %.idx.58
  %.next.idx.71 = add nsw i32 %.idx.70, 1
  store i32 %.next.idx.71, i32* %.idx.58
  br label %omp.loop.main61

omp.loop.fini72:                                  ; preds = %omp.lb.le.global_ub.62
  br label %omp.loop.end73

omp.loop.end73:                                   ; preds = %omp.loop.fini72, %omp.loop.main61
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.52)
  %.gtid.74 = load i32* %.__kmpc_global_thread_num.
  %46 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.74)
  %47 = icmp ne i32 %46, 0
  br i1 %47, label %omp.cancel_barrier.exit75, label %omp.cancel_barrier.continue76

omp.cancel_barrier.exit75:                        ; preds = %omp.loop.end73
  br label %omp.cancel_barrier.continue79

omp.cancel_barrier.continue76:                    ; preds = %omp.loop.end73
  %.gtid.77 = load i32* %.__kmpc_global_thread_num.
  %48 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.77)
  %49 = icmp ne i32 %48, 0
  br i1 %49, label %omp.cancel_barrier.exit78, label %omp.cancel_barrier.continue79

omp.cancel_barrier.exit78:                        ; preds = %omp.cancel_barrier.continue76
  br label %omp.cancel_barrier.continue79

omp.cancel_barrier.continue79:                    ; preds = %omp.cancel_barrier.exit, %omp.cancel_barrier.exit75, %omp.cancel_barrier.exit78, %omp.cancel_barrier.continue76
  ret void
}

declare i32 @printf(i8*, ...) #1

declare i32 @omp_get_thread_num(...) #1

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

declare void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }*, i32, i32, i32*, i32*, i32*, i32*, i32, i32)

declare void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
