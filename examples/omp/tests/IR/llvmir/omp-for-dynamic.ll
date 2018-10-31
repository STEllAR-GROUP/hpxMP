; ModuleID = '../../src/omp-for-dynamic.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32* }
%struct.anon.0 = type { i32* }
%struct.anon.1 = type { i32* }
%struct.anon.2 = type { i32* }
%struct.anon.3 = type { i32* }
%struct.anon.4 = type { i32* }

@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.str = private unnamed_addr constant [23 x i8] c"Static Hello World %d\0A\00", align 1
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.str2 = private unnamed_addr constant [24 x i8] c"Static1 Hello World %d\0A\00", align 1
@.str4 = private unnamed_addr constant [24 x i8] c"Static2 Hello World %d\0A\00", align 1
@.str5 = private unnamed_addr constant [14 x i8] c"Dynamic loop\0A\00", align 1
@.str7 = private unnamed_addr constant [35 x i8] c"Thread %d: Dynamic Hello World %d\0A\00", align 1
@.str8 = private unnamed_addr constant [21 x i8] c"Static Ordered loop\0A\00", align 1
@.str10 = private unnamed_addr constant [42 x i8] c"Thread %d: Static Ordered Hello World %d\0A\00", align 1
@.str11 = private unnamed_addr constant [22 x i8] c"Dynamic Ordered loop\0A\00", align 1
@.str13 = private unnamed_addr constant [43 x i8] c"Thread %d: Dynamic Ordered Hello World %d\0A\00", align 1

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
  %agg.captured1 = alloca %struct.anon.0, align 8
  %agg.captured2 = alloca %struct.anon.1, align 8
  %agg.captured3 = alloca %struct.anon.2, align 8
  %agg.captured5 = alloca %struct.anon.3, align 8
  %agg.captured7 = alloca %struct.anon.4, align 8
  store i32 0, i32* %retval
  %2 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 0
  store i32* %i, i32** %2, align 8
  %3 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %3)
  %4 = getelementptr inbounds %struct.anon.0* %agg.captured1, i32 0, i32 0
  store i32* %i, i32** %4, align 8
  %5 = bitcast %struct.anon.0* %agg.captured1 to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.1 to void (i32*, i32*, ...)*), i8* %5)
  %6 = getelementptr inbounds %struct.anon.1* %agg.captured2, i32 0, i32 0
  store i32* %i, i32** %6, align 8
  %7 = bitcast %struct.anon.1* %agg.captured2 to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.3 to void (i32*, i32*, ...)*), i8* %7)
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([14 x i8]* @.str5, i32 0, i32 0))
  %8 = getelementptr inbounds %struct.anon.2* %agg.captured3, i32 0, i32 0
  store i32* %i, i32** %8, align 8
  %9 = bitcast %struct.anon.2* %agg.captured3 to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.6 to void (i32*, i32*, ...)*), i8* %9)
  %call4 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([21 x i8]* @.str8, i32 0, i32 0))
  %10 = getelementptr inbounds %struct.anon.3* %agg.captured5, i32 0, i32 0
  store i32* %i, i32** %10, align 8
  %11 = bitcast %struct.anon.3* %agg.captured5 to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.9 to void (i32*, i32*, ...)*), i8* %11)
  %call6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([22 x i8]* @.str11, i32 0, i32 0))
  %12 = getelementptr inbounds %struct.anon.4* %agg.captured7, i32 0, i32 0
  store i32* %i, i32** %12, align 8
  %13 = bitcast %struct.anon.4* %agg.captured7 to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.12 to void (i32*, i32*, ...)*), i8* %13)
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
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
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
  %.idx.3 = load i32* %.idx.
  %15 = load i32* %ub
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %15
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %16 = load i32* %i.private., align 4
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([23 x i8]* @.str, i32 0, i32 0), i32 %16)
  br label %omp.cont.block

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.4 = load i32* %.idx.
  %.next.idx. = add nsw i32 %.idx.4, 1
  store i32 %.next.idx., i32* %.idx.
  br label %omp.loop.main

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.)
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %17 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.5)
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void
}

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #1

declare void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }*, i32, i32, i32*, i32*, i32*, i32*, i32, i32)

declare i32 @printf(i8*, ...) #2

declare void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.1(i32*, i32*, i8*) #0 {
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
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %st
  store i32 1, i32* %last
  store i32* %0, i32** %.addr, align 8
  store i32* %1, i32** %.addr1, align 8
  store i8* %2, i8** %.addr2, align 8
  %.__kmpc_global_thread_num. = load i32** %.addr
  %arg3 = load i8** %.addr2
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.0*
  %7 = getelementptr inbounds %struct.anon.0* %"(anon)arg3", i32 0, i32 0
  %ref = load i32** %7, align 8
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 10, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 10, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 33, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 1)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %omp.loop.fini, %entry
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
  %.idx.3 = load i32* %.idx.
  %15 = load i32* %ub
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %15
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %16 = load i32* %i.private., align 4
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([24 x i8]* @.str2, i32 0, i32 0), i32 %16)
  br label %omp.cont.block

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.4 = load i32* %.idx.
  %.next.idx. = add nsw i32 %.idx.4, 1
  store i32 %.next.idx., i32* %.idx.
  br label %omp.loop.main

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  %17 = load i32* %st
  %18 = load i32* %lb
  %19 = add i32 %18, %17
  store i32 %19, i32* %lb
  %20 = load i32* %ub
  %21 = add i32 %20, %17
  store i32 %21, i32* %ub
  br label %omp.loop.begin

omp.loop.end:                                     ; preds = %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.)
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %22 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.5)
  %23 = icmp ne i32 %22, 0
  br i1 %23, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void
}

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.3(i32*, i32*, i8*) #0 {
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
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %st
  store i32 1, i32* %last
  store i32* %0, i32** %.addr, align 8
  store i32* %1, i32** %.addr1, align 8
  store i8* %2, i8** %.addr2, align 8
  %.__kmpc_global_thread_num. = load i32** %.addr
  %arg3 = load i8** %.addr2
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.1*
  %7 = getelementptr inbounds %struct.anon.1* %"(anon)arg3", i32 0, i32 0
  %ref = load i32** %7, align 8
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 10, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 10, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 33, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 2)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %omp.loop.fini, %entry
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
  %.idx.3 = load i32* %.idx.
  %15 = load i32* %ub
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %15
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %16 = load i32* %i.private., align 4
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([24 x i8]* @.str4, i32 0, i32 0), i32 %16)
  br label %omp.cont.block

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.4 = load i32* %.idx.
  %.next.idx. = add nsw i32 %.idx.4, 1
  store i32 %.next.idx., i32* %.idx.
  br label %omp.loop.main

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  %17 = load i32* %st
  %18 = load i32* %lb
  %19 = add i32 %18, %17
  store i32 %19, i32* %lb
  %20 = load i32* %ub
  %21 = add i32 %20, %17
  store i32 %21, i32* %ub
  br label %omp.loop.begin

omp.loop.end:                                     ; preds = %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.)
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %22 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.5)
  %23 = icmp ne i32 %22, 0
  br i1 %23, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void
}

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.6(i32*, i32*, i8*) #0 {
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
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %st
  store i32 0, i32* %last
  store i32* %0, i32** %.addr, align 8
  store i32* %1, i32** %.addr1, align 8
  store i8* %2, i8** %.addr2, align 8
  %.__kmpc_global_thread_num. = load i32** %.addr
  %arg3 = load i8** %.addr2
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.2*
  %7 = getelementptr inbounds %struct.anon.2* %"(anon)arg3", i32 0, i32 0
  %ref = load i32** %7, align 8
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 8, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 8, i32* %ub
  call void @__kmpc_dispatch_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 35, i32 0, i32 8, i32 1, i32 1)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %omp.loop.fini, %entry
  %8 = call i32 @__kmpc_dispatch_next_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32* %last, i32* %lb, i32* %ub, i32* %st)
  switch i32 %8, label %omp.loop.end [
    i32 1, label %omp.loop.init
  ]

omp.loop.init:                                    ; preds = %omp.loop.begin
  %9 = load i32* %lb
  %10 = load i32* %ub
  store i32 %9, i32* %.idx.
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.init
  store i32 0, i32* %i.private., align 4
  %11 = load i32* %.idx., align 4
  %mul = mul nsw i32 %11, 1
  %12 = load i32* %i.private., align 4
  %add = add nsw i32 %12, %mul
  store i32 %add, i32* %i.private., align 4
  %.idx.3 = load i32* %.idx.
  %13 = load i32* %ub
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %13
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini

omp.lb_ub.check_pass:                             ; preds = %omp.loop.main
  %call = call i32 @omp_get_thread_num()
  %14 = load i32* %i.private., align 4
  %call4 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([35 x i8]* @.str7, i32 0, i32 0), i32 %call, i32 %14)
  br label %omp.cont.block

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.5 = load i32* %.idx.
  %.next.idx. = add nsw i32 %.idx.5, 1
  store i32 %.next.idx., i32* %.idx.
  br label %omp.loop.main

omp.loop.fini:                                    ; preds = %omp.loop.main
  br label %omp.loop.begin

omp.loop.end:                                     ; preds = %omp.loop.begin
  %.gtid.6 = load i32* %.__kmpc_global_thread_num.
  %15 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.6)
  %16 = icmp ne i32 %15, 0
  br i1 %16, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void
}

declare void @__kmpc_dispatch_init_4({ i32, i32, i32, i32, i8* }*, i32, i32, i32, i32, i32, i32)

declare i32 @__kmpc_dispatch_next_4({ i32, i32, i32, i32, i8* }*, i32, i32*, i32*, i32*, i32*)

declare i32 @omp_get_thread_num() #2

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.9(i32*, i32*, i8*) #0 {
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
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %st
  store i32 0, i32* %last
  store i32* %0, i32** %.addr, align 8
  store i32* %1, i32** %.addr1, align 8
  store i8* %2, i8** %.addr2, align 8
  %.__kmpc_global_thread_num. = load i32** %.addr
  %arg3 = load i8** %.addr2
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.3*
  %7 = getelementptr inbounds %struct.anon.3* %"(anon)arg3", i32 0, i32 0
  %ref = load i32** %7, align 8
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 9, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 9, i32* %ub
  call void @__kmpc_dispatch_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 66, i32 0, i32 9, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %omp.loop.fini, %entry
  %8 = call i32 @__kmpc_dispatch_next_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32* %last, i32* %lb, i32* %ub, i32* %st)
  switch i32 %8, label %omp.loop.end [
    i32 1, label %omp.loop.init
  ]

omp.loop.init:                                    ; preds = %omp.loop.begin
  %9 = load i32* %lb
  %10 = load i32* %ub
  store i32 %9, i32* %.idx.
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.init
  store i32 0, i32* %i.private., align 4
  %11 = load i32* %.idx., align 4
  %mul = mul nsw i32 %11, 1
  %12 = load i32* %i.private., align 4
  %add = add nsw i32 %12, %mul
  store i32 %add, i32* %i.private., align 4
  %.idx.3 = load i32* %.idx.
  %13 = load i32* %ub
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %13
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini

omp.lb_ub.check_pass:                             ; preds = %omp.loop.main
  %.gtid.4 = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_ordered({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4)
  %call = call i32 @omp_get_thread_num()
  %14 = load i32* %i.private., align 4
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([42 x i8]* @.str10, i32 0, i32 0), i32 %call, i32 %14)
  %.gtid.6 = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_end_ordered({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.6)
  br label %omp.cont.block

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.7 = load i32* %.idx.
  %.next.idx. = add nsw i32 %.idx.7, 1
  store i32 %.next.idx., i32* %.idx.
  call void @__kmpc_dispatch_fini_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.)
  br label %omp.loop.main

omp.loop.fini:                                    ; preds = %omp.loop.main
  br label %omp.loop.begin

omp.loop.end:                                     ; preds = %omp.loop.begin
  %.gtid.8 = load i32* %.__kmpc_global_thread_num.
  %15 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.8)
  %16 = icmp ne i32 %15, 0
  br i1 %16, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void
}

declare void @__kmpc_ordered({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_end_ordered({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_dispatch_fini_4({ i32, i32, i32, i32, i8* }*, i32)

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.12(i32*, i32*, i8*) #0 {
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
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %st
  store i32 0, i32* %last
  store i32* %0, i32** %.addr, align 8
  store i32* %1, i32** %.addr1, align 8
  store i8* %2, i8** %.addr2, align 8
  %.__kmpc_global_thread_num. = load i32** %.addr
  %arg3 = load i8** %.addr2
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.4*
  %7 = getelementptr inbounds %struct.anon.4* %"(anon)arg3", i32 0, i32 0
  %ref = load i32** %7, align 8
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 15, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 15, i32* %ub
  call void @__kmpc_dispatch_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 67, i32 0, i32 15, i32 1, i32 1)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %omp.loop.fini, %entry
  %8 = call i32 @__kmpc_dispatch_next_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32* %last, i32* %lb, i32* %ub, i32* %st)
  switch i32 %8, label %omp.loop.end [
    i32 1, label %omp.loop.init
  ]

omp.loop.init:                                    ; preds = %omp.loop.begin
  %9 = load i32* %lb
  %10 = load i32* %ub
  store i32 %9, i32* %.idx.
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.init
  store i32 0, i32* %i.private., align 4
  %11 = load i32* %.idx., align 4
  %mul = mul nsw i32 %11, 1
  %12 = load i32* %i.private., align 4
  %add = add nsw i32 %12, %mul
  store i32 %add, i32* %i.private., align 4
  %.idx.3 = load i32* %.idx.
  %13 = load i32* %ub
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %13
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini

omp.lb_ub.check_pass:                             ; preds = %omp.loop.main
  %.gtid.4 = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_ordered({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4)
  %call = call i32 @omp_get_thread_num()
  %14 = load i32* %i.private., align 4
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([43 x i8]* @.str13, i32 0, i32 0), i32 %call, i32 %14)
  %.gtid.6 = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_end_ordered({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.6)
  br label %omp.cont.block

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.7 = load i32* %.idx.
  %.next.idx. = add nsw i32 %.idx.7, 1
  store i32 %.next.idx., i32* %.idx.
  call void @__kmpc_dispatch_fini_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.)
  br label %omp.loop.main

omp.loop.fini:                                    ; preds = %omp.loop.main
  br label %omp.loop.begin

omp.loop.end:                                     ; preds = %omp.loop.begin
  %.gtid.8 = load i32* %.__kmpc_global_thread_num.
  %15 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.8)
  %16 = icmp ne i32 %15, 0
  br i1 %16, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
