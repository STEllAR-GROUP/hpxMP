; ModuleID = 'src/omp-reduction.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32*, i32*, i32* }

@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.str = private unnamed_addr constant [31 x i8] c"i = %d, sum = %d, thread = %d\0A\00", align 1
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.omp.default.loc.16. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 16, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.lck. = private global [8 x i32] zeroinitializer
@.str1 = private unnamed_addr constant [10 x i8] c"sum = %d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %i = alloca i32, align 4
  %num_steps = alloca i32, align 4
  %x = alloca i32, align 4
  %sum = alloca i32, align 4
  %pi = alloca i32, align 4
  %agg.captured = alloca %struct.anon, align 8
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 0, i32* %retval
  store i32 15, i32* %num_steps, align 4
  store i32 0, i32* %sum, align 4
  %2 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 0
  store i32* %i, i32** %2, align 8
  %3 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 1
  store i32* %num_steps, i32** %3, align 8
  %4 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 2
  store i32* %sum, i32** %4, align 8
  %5 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %5)
  %6 = load i32* %sum, align 4
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([10 x i8]* @.str1, i32 0, i32 0), i32 %6)
  ret i32 0
}

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.(i32*, i32*, i8*) #0 {
entry:
  %.addr = alloca i32*, align 8
  %.addr1 = alloca i32*, align 8
  %.addr2 = alloca i8*, align 8
  %reduction.rec.var = alloca { i32* }, align 8
  %sum = alloca i32, align 4
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
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %.__kmpc_ident_t.16. = alloca { i32, i32, i32, i32, i8* }, align 8
  %7 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.16. to i8*
  %8 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.16. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %7, i8* %8, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %sum.addr.lhs. = alloca i32*, align 8
  store i32 1, i32* %st
  store i32 1, i32* %last
  store i32 0, i32* %sum
  store i32* %0, i32** %.addr, align 8
  store i32* %1, i32** %.addr1, align 8
  store i8* %2, i8** %.addr2, align 8
  %.__kmpc_global_thread_num. = load i32** %.addr
  %arg3 = load i8** %.addr2
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*
  %9 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 0
  %ref = load i32** %9, align 8
  %10 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 1
  %ref3 = load i32** %10, align 8
  %11 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 2
  %ref4 = load i32** %11, align 8
  %sum.addr = getelementptr { i32* }* %reduction.rec.var, i32 0, i32 0
  store i32* %sum, i32** %sum.addr
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  %12 = load i32* %ref3, align 4
  %sub = sub nsw i32 %12, 1
  %add = add nsw i32 %sub, 1
  %div = sdiv i32 %add, 1
  %sub5 = sub nsw i32 %div, 1
  store i32 %sub5, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 %sub5, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %entry
  %13 = load i32* %lb
  store i32 %13, i32* %.idx.
  %14 = load i32* %ub
  %15 = icmp slt i32 %14, %sub5
  %16 = select i1 %15, i32 %14, i32 %sub5
  store i32 %16, i32* %ub
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.begin
  %17 = icmp sle i32 %13, %sub5
  br i1 %17, label %omp.lb.le.global_ub., label %omp.loop.end

omp.lb.le.global_ub.:                             ; preds = %omp.loop.main
  store i32 1, i32* %i.private., align 4
  %18 = load i32* %.idx., align 4
  %mul = mul nsw i32 %18, 1
  %19 = load i32* %i.private., align 4
  %add6 = add nsw i32 %19, %mul
  store i32 %add6, i32* %i.private., align 4
  %.idx.7 = load i32* %.idx.
  %20 = load i32* %ub
  %omp.idx.le.ub = icmp sle i32 %.idx.7, %20
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %21 = load i32* %i.private., align 4
  %22 = load i32* %i.private., align 4
  %mul8 = mul nsw i32 %21, %22
  %conv = sitofp i32 %mul8 to double
  %add9 = fadd double 1.000000e+00, %conv
  %23 = load i32* %sum, align 4
  %conv10 = sitofp i32 %23 to double
  %add11 = fadd double %conv10, %add9
  %conv12 = fptosi double %add11 to i32
  store i32 %conv12, i32* %sum, align 4
  %24 = load i32* %i.private., align 4
  %25 = load i32* %sum, align 4
  %call = call i32 (...)* @omp_get_thread_num()
  %call13 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([31 x i8]* @.str, i32 0, i32 0), i32 %24, i32 %25, i32 %call)
  br label %omp.cont.block

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.14 = load i32* %.idx.
  %.next.idx. = add nsw i32 %.idx.14, 1
  store i32 %.next.idx., i32* %.idx.
  br label %omp.loop.main

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.)
  %.gtid.15 = load i32* %.__kmpc_global_thread_num.
  %26 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.15)
  %27 = icmp ne i32 %26, 0
  br i1 %27, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %reduction.continue

omp.cancel_barrier.continue:                      ; preds = %omp.loop.end
  %.gtid.16 = load i32* %.__kmpc_global_thread_num.
  %"(void*)reductionrec" = bitcast { i32* }* %reduction.rec.var to i8*
  %28 = call i32 @__kmpc_reduce({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.16., i32 %.gtid.16, i32 1, i64 8, i8* %"(void*)reductionrec", void (i8*, i8*)* @.omp_reduction_op., [8 x i32]* @.lck.)
  switch i32 %28, label %reduction.continue [
    i32 1, label %reduction.case1
    i32 2, label %reduction.case2
  ]

reduction.case1:                                  ; preds = %omp.cancel_barrier.continue
  store i32* %ref4, i32** %sum.addr.lhs.
  %sum.addr.rhs = getelementptr { i32* }* %reduction.rec.var, i32 0, i32 0
  %29 = load i32** %sum.addr.rhs, align 8
  %30 = load i32* %29, align 4
  %31 = load i32** %sum.addr.lhs., align 8
  %32 = load i32* %31, align 4
  %add17 = add nsw i32 %32, %30
  store i32 %add17, i32* %31, align 4
  %.gtid.20 = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_end_reduce({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.20, [8 x i32]* @.lck.)
  br label %reduction.continue

reduction.case2:                                  ; preds = %omp.cancel_barrier.continue
  %.gtid.18 = load i32* %.__kmpc_global_thread_num.
  %sum.addr.rhs19 = getelementptr { i32* }* %reduction.rec.var, i32 0, i32 0
  %sum.rhs = load i32** %sum.addr.rhs19
  %33 = load i32* %sum.rhs
  call void @__kmpc_atomic_fixed4_add({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.18, i32* %ref4, i32 %33)
  br label %reduction.continue

reduction.continue:                               ; preds = %omp.cancel_barrier.exit, %reduction.case2, %reduction.case1, %omp.cancel_barrier.continue
  ret void
}

; Function Attrs: nounwind uwtable
define internal void @.omp_reduction_op.(i8*, i8*) #0 {
entry:
  %.addr = alloca i8*, align 8
  %.addr1 = alloca i8*, align 8
  store i8* %0, i8** %.addr, align 8
  store i8* %1, i8** %.addr1, align 8
  %reduction.lhs = bitcast i8* %0 to { i32* }*
  %reduction.rhs = bitcast i8* %1 to { i32* }*
  %sum.addr.lhs = getelementptr { i32* }* %reduction.lhs, i32 0, i32 0
  %sum.addr.rhs = getelementptr { i32* }* %reduction.rhs, i32 0, i32 0
  %2 = load i32** %sum.addr.rhs, align 8
  %3 = load i32* %2, align 4
  %4 = load i32** %sum.addr.lhs, align 8
  %5 = load i32* %4, align 4
  %add = add nsw i32 %5, %3
  store i32 %add, i32* %4, align 4
  ret void
}

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #1

declare void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }*, i32, i32, i32*, i32*, i32*, i32*, i32, i32)

declare i32 @printf(i8*, ...) #2

declare i32 @omp_get_thread_num(...) #2

declare void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_reduce({ i32, i32, i32, i32, i8* }*, i32, i32, i64, i8*, void (i8*, i8*)*, [8 x i32]*)

declare void @__kmpc_atomic_fixed4_add({ i32, i32, i32, i32, i8* }*, i32, i32*, i32)

declare void @__kmpc_end_reduce({ i32, i32, i32, i32, i8* }*, i32, [8 x i32]*)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
