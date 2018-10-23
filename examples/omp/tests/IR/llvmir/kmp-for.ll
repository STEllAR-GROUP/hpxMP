; ModuleID = 'omp-for.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32* }
%struct.anon.0 = type { i32* }
%struct.anon.1 = type { i32* }
%struct.anon.2 = type { i32* }
%struct.anon.3 = type { i32* }
%struct.anon.4 = type { i32* }
%struct.anon.5 = type { i32*, i32* }
%struct.anon.6 = type { i32*, i32* }

@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@0 = private unnamed_addr constant [33 x i8] c";omp-for.c;.omp_microtask.;6;9;;\00"
@.str = private unnamed_addr constant [16 x i8] c"Hello World %d\0A\00", align 1
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@1 = private unnamed_addr constant [34 x i8] c";omp-for.c;.omp_microtask.;6;25;;\00"
@2 = private unnamed_addr constant [22 x i8] c";omp-for.c;main;6;9;;\00"
@.str1 = private unnamed_addr constant [43 x i8] c"loop 2: separate parallel and for pragmas\0A\00", align 1
@3 = private unnamed_addr constant [34 x i8] c";omp-for.c;.omp_microtask.;15;9;;\00"
@4 = private unnamed_addr constant [35 x i8] c";omp-for.c;.omp_microtask.;15;17;;\00"
@5 = private unnamed_addr constant [35 x i8] c";omp-for.c;.omp_microtask.;13;22;;\00"
@6 = private unnamed_addr constant [23 x i8] c";omp-for.c;main;13;9;;\00"
@.str3 = private unnamed_addr constant [26 x i8] c"loop 3: stride of 2, 0-9\0A\00", align 1
@7 = private unnamed_addr constant [34 x i8] c";omp-for.c;.omp_microtask.;22;9;;\00"
@.str5 = private unnamed_addr constant [16 x i8] c"Hello world %d\0A\00", align 1
@8 = private unnamed_addr constant [35 x i8] c";omp-for.c;.omp_microtask.;22;26;;\00"
@9 = private unnamed_addr constant [23 x i8] c";omp-for.c;main;22;9;;\00"
@.str6 = private unnamed_addr constant [27 x i8] c"loop 4: stride of 2, 0-10\0A\00", align 1
@10 = private unnamed_addr constant [34 x i8] c";omp-for.c;.omp_microtask.;28;9;;\00"
@11 = private unnamed_addr constant [35 x i8] c";omp-for.c;.omp_microtask.;28;26;;\00"
@12 = private unnamed_addr constant [23 x i8] c";omp-for.c;main;28;9;;\00"
@.str8 = private unnamed_addr constant [27 x i8] c"loop 5: stride of 1, -5-4\0A\00", align 1
@13 = private unnamed_addr constant [34 x i8] c";omp-for.c;.omp_microtask.;34;9;;\00"
@14 = private unnamed_addr constant [35 x i8] c";omp-for.c;.omp_microtask.;34;26;;\00"
@15 = private unnamed_addr constant [23 x i8] c";omp-for.c;main;34;9;;\00"
@.str10 = private unnamed_addr constant [27 x i8] c"loop 6: stride of 2, -5-4\0A\00", align 1
@16 = private unnamed_addr constant [34 x i8] c";omp-for.c;.omp_microtask.;40;9;;\00"
@17 = private unnamed_addr constant [35 x i8] c";omp-for.c;.omp_microtask.;40;26;;\00"
@18 = private unnamed_addr constant [23 x i8] c";omp-for.c;main;40;9;;\00"
@.str12 = private unnamed_addr constant [30 x i8] c"loop 7: nested par for loops\0A\00", align 1
@19 = private unnamed_addr constant [34 x i8] c";omp-for.c;.omp_microtask.;46;9;;\00"
@20 = private unnamed_addr constant [34 x i8] c";omp-for.c;.omp_microtask.;48;9;;\00"
@.str15 = private unnamed_addr constant [20 x i8] c"Hello World %d, %d\0A\00", align 1
@.str16 = private unnamed_addr constant [13 x i8] c"addr %p, %p\0A\00", align 1
@21 = private unnamed_addr constant [35 x i8] c";omp-for.c;.omp_microtask.;48;41;;\00"
@22 = private unnamed_addr constant [34 x i8] c";omp-for.c;.omp_microtask.;48;9;;\00"
@23 = private unnamed_addr constant [34 x i8] c";omp-for.c;.omp_microtask.;48;9;;\00"
@24 = private unnamed_addr constant [35 x i8] c";omp-for.c;.omp_microtask.;46;25;;\00"
@25 = private unnamed_addr constant [23 x i8] c";omp-for.c;main;46;9;;\00"

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
  %agg.captured3 = alloca %struct.anon.1, align 8
  %agg.captured5 = alloca %struct.anon.2, align 8
  %agg.captured7 = alloca %struct.anon.3, align 8
  %agg.captured9 = alloca %struct.anon.4, align 8
  %agg.captured11 = alloca %struct.anon.5, align 8
  store i32 0, i32* %retval
  call void @llvm.dbg.declare(metadata !{i32* %i}, metadata !24), !dbg !25
  call void @llvm.dbg.declare(metadata !{i32* %j}, metadata !26), !dbg !27
  %2 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 0, !dbg !28
  store i32* %i, i32** %2, align 8, !dbg !28
  %3 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([22 x i8]* @2, i32 0, i32 0), i8** %3
  %4 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %4)
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([43 x i8]* @.str1, i32 0, i32 0)), !dbg !29
  %5 = getelementptr inbounds %struct.anon.0* %agg.captured1, i32 0, i32 0, !dbg !30
  store i32* %i, i32** %5, align 8, !dbg !30
  %6 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !30
  store i8* getelementptr inbounds ([23 x i8]* @6, i32 0, i32 0), i8** %6, !dbg !30
  %7 = bitcast %struct.anon.0* %agg.captured1 to i8*, !dbg !30
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.2 to void (i32*, i32*, ...)*), i8* %7), !dbg !30
  %call2 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([26 x i8]* @.str3, i32 0, i32 0)), !dbg !31
  %8 = getelementptr inbounds %struct.anon.1* %agg.captured3, i32 0, i32 0, !dbg !32
  store i32* %i, i32** %8, align 8, !dbg !32
  %9 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !32
  store i8* getelementptr inbounds ([23 x i8]* @9, i32 0, i32 0), i8** %9, !dbg !32
  %10 = bitcast %struct.anon.1* %agg.captured3 to i8*, !dbg !32
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.4 to void (i32*, i32*, ...)*), i8* %10), !dbg !32
  %call4 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([27 x i8]* @.str6, i32 0, i32 0)), !dbg !33
  %11 = getelementptr inbounds %struct.anon.2* %agg.captured5, i32 0, i32 0, !dbg !34
  store i32* %i, i32** %11, align 8, !dbg !34
  %12 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !34
  store i8* getelementptr inbounds ([23 x i8]* @12, i32 0, i32 0), i8** %12, !dbg !34
  %13 = bitcast %struct.anon.2* %agg.captured5 to i8*, !dbg !34
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.7 to void (i32*, i32*, ...)*), i8* %13), !dbg !34
  %call6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([27 x i8]* @.str8, i32 0, i32 0)), !dbg !35
  %14 = getelementptr inbounds %struct.anon.3* %agg.captured7, i32 0, i32 0, !dbg !36
  store i32* %i, i32** %14, align 8, !dbg !36
  %15 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !36
  store i8* getelementptr inbounds ([23 x i8]* @15, i32 0, i32 0), i8** %15, !dbg !36
  %16 = bitcast %struct.anon.3* %agg.captured7 to i8*, !dbg !36
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.9 to void (i32*, i32*, ...)*), i8* %16), !dbg !36
  %call8 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([27 x i8]* @.str10, i32 0, i32 0)), !dbg !37
  %17 = getelementptr inbounds %struct.anon.4* %agg.captured9, i32 0, i32 0, !dbg !38
  store i32* %i, i32** %17, align 8, !dbg !38
  %18 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !38
  store i8* getelementptr inbounds ([23 x i8]* @18, i32 0, i32 0), i8** %18, !dbg !38
  %19 = bitcast %struct.anon.4* %agg.captured9 to i8*, !dbg !38
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.11 to void (i32*, i32*, ...)*), i8* %19), !dbg !38
  %call10 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str12, i32 0, i32 0)), !dbg !39
  %20 = getelementptr inbounds %struct.anon.5* %agg.captured11, i32 0, i32 0, !dbg !40
  store i32* %i, i32** %20, align 8, !dbg !40
  %21 = getelementptr inbounds %struct.anon.5* %agg.captured11, i32 0, i32 1, !dbg !40
  store i32* %j, i32** %21, align 8, !dbg !40
  %22 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !40
  store i8* getelementptr inbounds ([23 x i8]* @25, i32 0, i32 0), i8** %22, !dbg !40
  %23 = bitcast %struct.anon.5* %agg.captured11 to i8*, !dbg !40
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.13 to void (i32*, i32*, ...)*), i8* %23), !dbg !40
  ret i32 0, !dbg !41
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata) #1

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
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !42), !dbg !43
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !44), !dbg !43
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !45), !dbg !43
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !43
  %arg3 = load i8** %.addr2, !dbg !43
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*, !dbg !43
  %7 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 0, !dbg !43
  %ref = load i32** %7, align 8, !dbg !43
  %8 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([33 x i8]* @0, i32 0, i32 0), i8** %8
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 10, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 10, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %entry
  %9 = load i32* %lb
  store i32 %9, i32* %.idx.
  %10 = load i32* %ub
  %11 = icmp slt i32 %10, 10
  %12 = select i1 %11, i32 %10, i32 10
  store i32 %12, i32* %ub
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.begin
  %13 = icmp sle i32 %9, 10
  br i1 %13, label %omp.lb.le.global_ub., label %omp.loop.end

omp.lb.le.global_ub.:                             ; preds = %omp.loop.main
  store i32 0, i32* %i.private., align 4, !dbg !43
  %14 = load i32* %.idx., align 4, !dbg !43
  %mul = mul nsw i32 %14, 1, !dbg !43
  %15 = load i32* %i.private., align 4, !dbg !43
  %add = add nsw i32 %15, %mul, !dbg !43
  store i32 %add, i32* %i.private., align 4, !dbg !43
  %.idx.3 = load i32* %.idx., !dbg !43
  %16 = load i32* %ub, !dbg !43
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %16, !dbg !43
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini, !dbg !43

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %17 = load i32* %i.private., align 4, !dbg !46
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([16 x i8]* @.str, i32 0, i32 0), i32 %17), !dbg !46
  br label %omp.cont.block, !dbg !48

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.4 = load i32* %.idx., !dbg !49
  %.next.idx. = add nsw i32 %.idx.4, 1, !dbg !49
  store i32 %.next.idx., i32* %.idx., !dbg !49
  br label %omp.loop.main, !dbg !49

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end, !dbg !48

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !51
  %18 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([34 x i8]* @1, i32 0, i32 0), i8** %18
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %19 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.5)
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void, !dbg !53
}

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

declare void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }*, i32, i32, i32*, i32*, i32*, i32*, i32, i32)

declare i32 @printf(i8*, ...) #3

declare void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.2(i32*, i32*, i8*) #0 {
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
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !54), !dbg !55
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !56), !dbg !55
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !57), !dbg !55
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !55
  %arg3 = load i8** %.addr2, !dbg !55
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.0*, !dbg !55
  %7 = getelementptr inbounds %struct.anon.0* %"(anon)arg3", i32 0, i32 0, !dbg !55
  %ref = load i32** %7, align 8, !dbg !55
  %8 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([34 x i8]* @3, i32 0, i32 0), i8** %8
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 10, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 10, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %entry
  %9 = load i32* %lb
  store i32 %9, i32* %.idx.
  %10 = load i32* %ub
  %11 = icmp slt i32 %10, 10
  %12 = select i1 %11, i32 %10, i32 10
  store i32 %12, i32* %ub
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.begin
  %13 = icmp sle i32 %9, 10
  br i1 %13, label %omp.lb.le.global_ub., label %omp.loop.end

omp.lb.le.global_ub.:                             ; preds = %omp.loop.main
  store i32 0, i32* %i.private., align 4, !dbg !58
  %14 = load i32* %.idx., align 4, !dbg !58
  %mul = mul nsw i32 %14, 1, !dbg !58
  %15 = load i32* %i.private., align 4, !dbg !58
  %add = add nsw i32 %15, %mul, !dbg !58
  store i32 %add, i32* %i.private., align 4, !dbg !58
  %.idx.3 = load i32* %.idx., !dbg !58
  %16 = load i32* %ub, !dbg !58
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %16, !dbg !58
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini, !dbg !58

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %17 = load i32* %i.private., align 4, !dbg !60
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([16 x i8]* @.str, i32 0, i32 0), i32 %17), !dbg !60
  br label %omp.cont.block, !dbg !62

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.4 = load i32* %.idx., !dbg !63
  %.next.idx. = add nsw i32 %.idx.4, 1, !dbg !63
  store i32 %.next.idx., i32* %.idx., !dbg !63
  br label %omp.loop.main, !dbg !63

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end, !dbg !62

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !65
  %18 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([35 x i8]* @4, i32 0, i32 0), i8** %18
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %19 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.5)
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue8

omp.cancel_barrier.continue:                      ; preds = %omp.loop.end
  %21 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4, !dbg !67
  store i8* getelementptr inbounds ([35 x i8]* @5, i32 0, i32 0), i8** %21, !dbg !67
  %.gtid.6 = load i32* %.__kmpc_global_thread_num., !dbg !67
  %22 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.6), !dbg !67
  %23 = icmp ne i32 %22, 0, !dbg !67
  br i1 %23, label %omp.cancel_barrier.exit7, label %omp.cancel_barrier.continue8, !dbg !67

omp.cancel_barrier.exit7:                         ; preds = %omp.cancel_barrier.continue
  br label %omp.cancel_barrier.continue8, !dbg !68

omp.cancel_barrier.continue8:                     ; preds = %omp.cancel_barrier.exit, %omp.cancel_barrier.exit7, %omp.cancel_barrier.continue
  ret void, !dbg !70
}

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.4(i32*, i32*, i8*) #0 {
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
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !73), !dbg !74
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !75), !dbg !74
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !76), !dbg !74
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !74
  %arg3 = load i8** %.addr2, !dbg !74
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.1*, !dbg !74
  %7 = getelementptr inbounds %struct.anon.1* %"(anon)arg3", i32 0, i32 0, !dbg !74
  %ref = load i32** %7, align 8, !dbg !74
  %8 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([34 x i8]* @7, i32 0, i32 0), i8** %8
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 4, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 4, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %entry
  %9 = load i32* %lb
  store i32 %9, i32* %.idx.
  %10 = load i32* %ub
  %11 = icmp slt i32 %10, 4
  %12 = select i1 %11, i32 %10, i32 4
  store i32 %12, i32* %ub
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.begin
  %13 = icmp sle i32 %9, 4
  br i1 %13, label %omp.lb.le.global_ub., label %omp.loop.end

omp.lb.le.global_ub.:                             ; preds = %omp.loop.main
  store i32 0, i32* %i.private., align 4, !dbg !74
  %14 = load i32* %.idx., align 4, !dbg !74
  %mul = mul nsw i32 %14, 2, !dbg !74
  %15 = load i32* %i.private., align 4, !dbg !74
  %add = add nsw i32 %15, %mul, !dbg !74
  store i32 %add, i32* %i.private., align 4, !dbg !74
  %.idx.3 = load i32* %.idx., !dbg !74
  %16 = load i32* %ub, !dbg !74
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %16, !dbg !74
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini, !dbg !74

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %17 = load i32* %i.private., align 4, !dbg !77
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([16 x i8]* @.str5, i32 0, i32 0), i32 %17), !dbg !77
  br label %omp.cont.block, !dbg !79

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.4 = load i32* %.idx., !dbg !80
  %.next.idx. = add nsw i32 %.idx.4, 1, !dbg !80
  store i32 %.next.idx., i32* %.idx., !dbg !80
  br label %omp.loop.main, !dbg !80

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end, !dbg !79

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !82
  %18 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([35 x i8]* @8, i32 0, i32 0), i8** %18
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %19 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.5)
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void, !dbg !84
}

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.7(i32*, i32*, i8*) #0 {
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
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !85), !dbg !86
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !87), !dbg !86
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !88), !dbg !86
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !86
  %arg3 = load i8** %.addr2, !dbg !86
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.2*, !dbg !86
  %7 = getelementptr inbounds %struct.anon.2* %"(anon)arg3", i32 0, i32 0, !dbg !86
  %ref = load i32** %7, align 8, !dbg !86
  %8 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([34 x i8]* @10, i32 0, i32 0), i8** %8
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 5, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 5, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %entry
  %9 = load i32* %lb
  store i32 %9, i32* %.idx.
  %10 = load i32* %ub
  %11 = icmp slt i32 %10, 5
  %12 = select i1 %11, i32 %10, i32 5
  store i32 %12, i32* %ub
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.begin
  %13 = icmp sle i32 %9, 5
  br i1 %13, label %omp.lb.le.global_ub., label %omp.loop.end

omp.lb.le.global_ub.:                             ; preds = %omp.loop.main
  store i32 0, i32* %i.private., align 4, !dbg !86
  %14 = load i32* %.idx., align 4, !dbg !86
  %mul = mul nsw i32 %14, 2, !dbg !86
  %15 = load i32* %i.private., align 4, !dbg !86
  %add = add nsw i32 %15, %mul, !dbg !86
  store i32 %add, i32* %i.private., align 4, !dbg !86
  %.idx.3 = load i32* %.idx., !dbg !86
  %16 = load i32* %ub, !dbg !86
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %16, !dbg !86
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini, !dbg !86

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %17 = load i32* %i.private., align 4, !dbg !89
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([16 x i8]* @.str5, i32 0, i32 0), i32 %17), !dbg !89
  br label %omp.cont.block, !dbg !91

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.4 = load i32* %.idx., !dbg !92
  %.next.idx. = add nsw i32 %.idx.4, 1, !dbg !92
  store i32 %.next.idx., i32* %.idx., !dbg !92
  br label %omp.loop.main, !dbg !92

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end, !dbg !91

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !94
  %18 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([35 x i8]* @11, i32 0, i32 0), i8** %18
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %19 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.5)
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void, !dbg !96
}

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
  store i32 1, i32* %last
  store i32* %0, i32** %.addr, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !97), !dbg !98
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !99), !dbg !98
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !100), !dbg !98
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !98
  %arg3 = load i8** %.addr2, !dbg !98
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.3*, !dbg !98
  %7 = getelementptr inbounds %struct.anon.3* %"(anon)arg3", i32 0, i32 0, !dbg !98
  %ref = load i32** %7, align 8, !dbg !98
  %8 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([34 x i8]* @13, i32 0, i32 0), i8** %8
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 9, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 9, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %entry
  %9 = load i32* %lb
  store i32 %9, i32* %.idx.
  %10 = load i32* %ub
  %11 = icmp slt i32 %10, 9
  %12 = select i1 %11, i32 %10, i32 9
  store i32 %12, i32* %ub
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.begin
  %13 = icmp sle i32 %9, 9
  br i1 %13, label %omp.lb.le.global_ub., label %omp.loop.end

omp.lb.le.global_ub.:                             ; preds = %omp.loop.main
  store i32 -5, i32* %i.private., align 4, !dbg !98
  %14 = load i32* %.idx., align 4, !dbg !98
  %mul = mul nsw i32 %14, 1, !dbg !98
  %15 = load i32* %i.private., align 4, !dbg !98
  %add = add nsw i32 %15, %mul, !dbg !98
  store i32 %add, i32* %i.private., align 4, !dbg !98
  %.idx.3 = load i32* %.idx., !dbg !98
  %16 = load i32* %ub, !dbg !98
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %16, !dbg !98
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini, !dbg !98

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %17 = load i32* %i.private., align 4, !dbg !101
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([16 x i8]* @.str5, i32 0, i32 0), i32 %17), !dbg !101
  br label %omp.cont.block, !dbg !103

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.4 = load i32* %.idx., !dbg !104
  %.next.idx. = add nsw i32 %.idx.4, 1, !dbg !104
  store i32 %.next.idx., i32* %.idx., !dbg !104
  br label %omp.loop.main, !dbg !104

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end, !dbg !103

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !106
  %18 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([35 x i8]* @14, i32 0, i32 0), i8** %18
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %19 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.5)
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void, !dbg !108
}

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.11(i32*, i32*, i8*) #0 {
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
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !109), !dbg !110
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !111), !dbg !110
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !112), !dbg !110
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !110
  %arg3 = load i8** %.addr2, !dbg !110
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.4*, !dbg !110
  %7 = getelementptr inbounds %struct.anon.4* %"(anon)arg3", i32 0, i32 0, !dbg !110
  %ref = load i32** %7, align 8, !dbg !110
  %8 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([34 x i8]* @16, i32 0, i32 0), i8** %8
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 4, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 4, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %entry
  %9 = load i32* %lb
  store i32 %9, i32* %.idx.
  %10 = load i32* %ub
  %11 = icmp slt i32 %10, 4
  %12 = select i1 %11, i32 %10, i32 4
  store i32 %12, i32* %ub
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.begin
  %13 = icmp sle i32 %9, 4
  br i1 %13, label %omp.lb.le.global_ub., label %omp.loop.end

omp.lb.le.global_ub.:                             ; preds = %omp.loop.main
  store i32 -5, i32* %i.private., align 4, !dbg !110
  %14 = load i32* %.idx., align 4, !dbg !110
  %mul = mul nsw i32 %14, 2, !dbg !110
  %15 = load i32* %i.private., align 4, !dbg !110
  %add = add nsw i32 %15, %mul, !dbg !110
  store i32 %add, i32* %i.private., align 4, !dbg !110
  %.idx.3 = load i32* %.idx., !dbg !110
  %16 = load i32* %ub, !dbg !110
  %omp.idx.le.ub = icmp sle i32 %.idx.3, %16, !dbg !110
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini, !dbg !110

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %17 = load i32* %i.private., align 4, !dbg !113
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([16 x i8]* @.str5, i32 0, i32 0), i32 %17), !dbg !113
  br label %omp.cont.block, !dbg !115

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.4 = load i32* %.idx., !dbg !116
  %.next.idx. = add nsw i32 %.idx.4, 1, !dbg !116
  store i32 %.next.idx., i32* %.idx., !dbg !116
  br label %omp.loop.main, !dbg !116

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end, !dbg !115

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !118
  %18 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([35 x i8]* @17, i32 0, i32 0), i8** %18
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %19 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.5)
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void, !dbg !120
}

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.13(i32*, i32*, i8*) #0 {
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
  %agg.captured = alloca %struct.anon.6, align 8
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %st
  store i32 1, i32* %last
  store i32* %0, i32** %.addr, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !121), !dbg !122
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !123), !dbg !122
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !124), !dbg !122
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !122
  %arg3 = load i8** %.addr2, !dbg !122
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.5*, !dbg !122
  %7 = getelementptr inbounds %struct.anon.5* %"(anon)arg3", i32 0, i32 0, !dbg !122
  %ref = load i32** %7, align 8, !dbg !122
  %8 = getelementptr inbounds %struct.anon.5* %"(anon)arg3", i32 0, i32 1, !dbg !122
  %ref3 = load i32** %8, align 8, !dbg !122
  %9 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([34 x i8]* @19, i32 0, i32 0), i8** %9
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 4, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 4, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %entry
  %10 = load i32* %lb
  store i32 %10, i32* %.idx.
  %11 = load i32* %ub
  %12 = icmp slt i32 %11, 4
  %13 = select i1 %12, i32 %11, i32 4
  store i32 %13, i32* %ub
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.begin
  %14 = icmp sle i32 %10, 4
  br i1 %14, label %omp.lb.le.global_ub., label %omp.loop.end

omp.lb.le.global_ub.:                             ; preds = %omp.loop.main
  store i32 0, i32* %i.private., align 4, !dbg !122
  %15 = load i32* %.idx., align 4, !dbg !122
  %mul = mul nsw i32 %15, 1, !dbg !122
  %16 = load i32* %i.private., align 4, !dbg !122
  %add = add nsw i32 %16, %mul, !dbg !122
  store i32 %add, i32* %i.private., align 4, !dbg !122
  %.idx.4 = load i32* %.idx., !dbg !122
  %17 = load i32* %ub, !dbg !122
  %omp.idx.le.ub = icmp sle i32 %.idx.4, %17, !dbg !122
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini, !dbg !122

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %18 = getelementptr inbounds %struct.anon.6* %agg.captured, i32 0, i32 0, !dbg !125
  store i32* %ref3, i32** %18, align 8, !dbg !125
  %19 = getelementptr inbounds %struct.anon.6* %agg.captured, i32 0, i32 1, !dbg !125
  store i32* %i.private., i32** %19, align 8, !dbg !125
  %20 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !125
  store i8* getelementptr inbounds ([34 x i8]* @23, i32 0, i32 0), i8** %20, !dbg !125
  %21 = bitcast %struct.anon.6* %agg.captured to i8*, !dbg !125
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.14 to void (i32*, i32*, ...)*), i8* %21), !dbg !125
  br label %omp.cont.block, !dbg !127

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.5 = load i32* %.idx., !dbg !128
  %.next.idx. = add nsw i32 %.idx.5, 1, !dbg !128
  store i32 %.next.idx., i32* %.idx., !dbg !128
  br label %omp.loop.main, !dbg !128

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end, !dbg !127

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !130
  %22 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([35 x i8]* @24, i32 0, i32 0), i8** %22
  %.gtid.6 = load i32* %.__kmpc_global_thread_num.
  %23 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.6)
  %24 = icmp ne i32 %23, 0
  br i1 %24, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void, !dbg !132
}

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.14(i32*, i32*, i8*) #0 {
entry:
  %.addr = alloca i32*, align 8
  %.addr1 = alloca i32*, align 8
  %.addr2 = alloca i8*, align 8
  %i = alloca i32, align 4
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
  %j.private. = alloca i32, align 4
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %st
  store i32 1, i32* %last
  store i32* %0, i32** %.addr, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !133), !dbg !134
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !135), !dbg !134
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !136), !dbg !134
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !134
  %arg3 = load i8** %.addr2, !dbg !134
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.6*, !dbg !134
  %7 = getelementptr inbounds %struct.anon.6* %"(anon)arg3", i32 0, i32 0, !dbg !134
  %ref = load i32** %7, align 8, !dbg !134
  %8 = getelementptr inbounds %struct.anon.6* %"(anon)arg3", i32 0, i32 1, !dbg !134
  %ref3 = load i32** %8, align 8, !dbg !134
  call void @llvm.dbg.declare(metadata !{i32* %i}, metadata !137), !dbg !138
  %9 = load i32* %ref3, align 4, !dbg !134
  store i32 %9, i32* %i, !dbg !134
  %10 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([34 x i8]* @22, i32 0, i32 0), i8** %10
  %.gtid.8 = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.8)
  %11 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([34 x i8]* @20, i32 0, i32 0), i8** %11
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 4, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 4, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %entry
  %12 = load i32* %lb
  store i32 %12, i32* %.idx.
  %13 = load i32* %ub
  %14 = icmp slt i32 %13, 4
  %15 = select i1 %14, i32 %13, i32 4
  store i32 %15, i32* %ub
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.begin
  %16 = icmp sle i32 %12, 4
  br i1 %16, label %omp.lb.le.global_ub., label %omp.loop.end

omp.lb.le.global_ub.:                             ; preds = %omp.loop.main
  store i32 0, i32* %j.private., align 4, !dbg !138
  %17 = load i32* %.idx., align 4, !dbg !138
  %mul = mul nsw i32 %17, 1, !dbg !138
  %18 = load i32* %j.private., align 4, !dbg !138
  %add = add nsw i32 %18, %mul, !dbg !138
  store i32 %add, i32* %j.private., align 4, !dbg !138
  %.idx.4 = load i32* %.idx., !dbg !138
  %19 = load i32* %ub, !dbg !138
  %omp.idx.le.ub = icmp sle i32 %.idx.4, %19, !dbg !138
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini, !dbg !138

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %20 = load i32* %i, align 4, !dbg !139
  %21 = load i32* %j.private., align 4, !dbg !139
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([20 x i8]* @.str15, i32 0, i32 0), i32 %20, i32 %21), !dbg !139
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([13 x i8]* @.str16, i32 0, i32 0), i32* %i, i32* %j.private.), !dbg !141
  br label %omp.cont.block, !dbg !142

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.6 = load i32* %.idx., !dbg !143
  %.next.idx. = add nsw i32 %.idx.6, 1, !dbg !143
  store i32 %.next.idx., i32* %.idx., !dbg !143
  br label %omp.loop.main, !dbg !143

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end, !dbg !142

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !145
  %22 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([35 x i8]* @21, i32 0, i32 0), i8** %22
  %.gtid.7 = load i32* %.__kmpc_global_thread_num.
  %23 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.7)
  %24 = icmp ne i32 %23, 0
  br i1 %24, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void, !dbg !147
}

declare void @__kmpc_barrier({ i32, i32, i32, i32, i8* }*, i32)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }
attributes #3 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!21, !22}
!llvm.ident = !{!23}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 1} ; [ DW_TAG_compile_unit ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c] [DW_LANG_C99]
!1 = metadata !{metadata !"omp-for.c", metadata !"/home/jeremy/code/research/hpxMP/omp-tests"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !9, metadata !14, metadata !15, metadata !16, metadata !17, metadata !18, metadata !19, metadata !20}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"main", metadata !"main", metadata !"", i32 3, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 ()* @main, null, null, metadata !2, i32 3} ; [ DW_TAG_subprogram ] [line 3] [def] [main]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{metadata !8}
!8 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!9 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 6, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask., null, null, metadata !2, i32 6} ; [ DW_TAG_subprogram ] [line 6] [local] [def] [.omp_microtask.]
!10 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{null, metadata !12, metadata !12, metadata !13}
!12 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !8} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from int]
!13 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!14 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 13, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask.2, null, null, metadata !2, i32 13} ; [ DW_TAG_subprogram ] [line 13] [local] [def] [.omp_microtask.]
!15 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 22, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask.4, null, null, metadata !2, i32 22} ; [ DW_TAG_subprogram ] [line 22] [local] [def] [.omp_microtask.]
!16 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 28, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask.7, null, null, metadata !2, i32 28} ; [ DW_TAG_subprogram ] [line 28] [local] [def] [.omp_microtask.]
!17 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 34, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask.9, null, null, metadata !2, i32 34} ; [ DW_TAG_subprogram ] [line 34] [local] [def] [.omp_microtask.]
!18 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 40, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask.11, null, null, metadata !2, i32 40} ; [ DW_TAG_subprogram ] [line 40] [local] [def] [.omp_microtask.]
!19 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 46, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask.13, null, null, metadata !2, i32 46} ; [ DW_TAG_subprogram ] [line 46] [local] [def] [.omp_microtask.]
!20 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 48, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask.14, null, null, metadata !2, i32 48} ; [ DW_TAG_subprogram ] [line 48] [local] [def] [.omp_microtask.]
!21 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!22 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!23 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
!24 = metadata !{i32 786688, metadata !4, metadata !"i", metadata !5, i32 4, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [i] [line 4]
!25 = metadata !{i32 4, i32 9, metadata !4, null}
!26 = metadata !{i32 786688, metadata !4, metadata !"j", metadata !5, i32 4, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [j] [line 4]
!27 = metadata !{i32 4, i32 11, metadata !4, null}
!28 = metadata !{i32 6, i32 9, metadata !4, null}
!29 = metadata !{i32 12, i32 5, metadata !4, null}
!30 = metadata !{i32 13, i32 9, metadata !4, null}
!31 = metadata !{i32 21, i32 5, metadata !4, null}
!32 = metadata !{i32 22, i32 9, metadata !4, null}
!33 = metadata !{i32 27, i32 5, metadata !4, null}
!34 = metadata !{i32 28, i32 9, metadata !4, null}
!35 = metadata !{i32 33, i32 5, metadata !4, null}
!36 = metadata !{i32 34, i32 9, metadata !4, null}
!37 = metadata !{i32 39, i32 5, metadata !4, null}
!38 = metadata !{i32 40, i32 9, metadata !4, null}
!39 = metadata !{i32 45, i32 5, metadata !4, null}
!40 = metadata !{i32 46, i32 9, metadata !4, null}
!41 = metadata !{i32 58, i32 5, metadata !4, null} ; [ DW_TAG_imported_module ]
!42 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 16777222, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 6]
!43 = metadata !{i32 6, i32 9, metadata !9, null}
!44 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 33554438, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 6]
!45 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 50331654, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 6]
!46 = metadata !{i32 9, i32 9, metadata !47, null}
!47 = metadata !{i32 786443, metadata !1, metadata !9, i32 8, i32 5, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!48 = metadata !{i32 10, i32 5, metadata !47, null}
!49 = metadata !{i32 10, i32 5, metadata !50, null}
!50 = metadata !{i32 786443, metadata !1, metadata !47, i32 10, i32 5, i32 1, i32 9} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!51 = metadata !{i32 10, i32 5, metadata !52, null}
!52 = metadata !{i32 786443, metadata !1, metadata !47, i32 10, i32 5, i32 2, i32 10} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!53 = metadata !{i32 10, i32 5, metadata !9, null}
!54 = metadata !{i32 786689, metadata !14, metadata !"", metadata !5, i32 16777229, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 13]
!55 = metadata !{i32 13, i32 9, metadata !14, null}
!56 = metadata !{i32 786689, metadata !14, metadata !"", metadata !5, i32 33554445, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 13]
!57 = metadata !{i32 786689, metadata !14, metadata !"", metadata !5, i32 50331661, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 13]
!58 = metadata !{i32 15, i32 9, metadata !59, null}
!59 = metadata !{i32 786443, metadata !1, metadata !14, i32 14, i32 5, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!60 = metadata !{i32 18, i32 13, metadata !61, null}
!61 = metadata !{i32 786443, metadata !1, metadata !59, i32 17, i32 9, i32 0, i32 2} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!62 = metadata !{i32 19, i32 9, metadata !61, null}
!63 = metadata !{i32 19, i32 9, metadata !64, null}
!64 = metadata !{i32 786443, metadata !1, metadata !61, i32 19, i32 9, i32 1, i32 11} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!65 = metadata !{i32 19, i32 9, metadata !66, null}
!66 = metadata !{i32 786443, metadata !1, metadata !61, i32 19, i32 9, i32 2, i32 12} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!67 = metadata !{i32 20, i32 5, metadata !59, null}
!68 = metadata !{i32 20, i32 5, metadata !69, null}
!69 = metadata !{i32 786443, metadata !1, metadata !59, i32 20, i32 5, i32 1, i32 13} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!70 = metadata !{i32 20, i32 5, metadata !71, null}
!71 = metadata !{i32 786443, metadata !1, metadata !72, i32 20, i32 5, i32 3, i32 15} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!72 = metadata !{i32 786443, metadata !1, metadata !14, i32 20, i32 5, i32 2, i32 14} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!73 = metadata !{i32 786689, metadata !15, metadata !"", metadata !5, i32 16777238, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 22]
!74 = metadata !{i32 22, i32 9, metadata !15, null}
!75 = metadata !{i32 786689, metadata !15, metadata !"", metadata !5, i32 33554454, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 22]
!76 = metadata !{i32 786689, metadata !15, metadata !"", metadata !5, i32 50331670, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 22]
!77 = metadata !{i32 25, i32 9, metadata !78, null}
!78 = metadata !{i32 786443, metadata !1, metadata !15, i32 24, i32 5, i32 0, i32 3} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!79 = metadata !{i32 26, i32 5, metadata !78, null}
!80 = metadata !{i32 26, i32 5, metadata !81, null}
!81 = metadata !{i32 786443, metadata !1, metadata !78, i32 26, i32 5, i32 1, i32 16} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!82 = metadata !{i32 26, i32 5, metadata !83, null}
!83 = metadata !{i32 786443, metadata !1, metadata !78, i32 26, i32 5, i32 2, i32 17} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!84 = metadata !{i32 26, i32 5, metadata !15, null}
!85 = metadata !{i32 786689, metadata !16, metadata !"", metadata !5, i32 16777244, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 28]
!86 = metadata !{i32 28, i32 9, metadata !16, null}
!87 = metadata !{i32 786689, metadata !16, metadata !"", metadata !5, i32 33554460, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 28]
!88 = metadata !{i32 786689, metadata !16, metadata !"", metadata !5, i32 50331676, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 28]
!89 = metadata !{i32 31, i32 9, metadata !90, null}
!90 = metadata !{i32 786443, metadata !1, metadata !16, i32 30, i32 5, i32 0, i32 4} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!91 = metadata !{i32 32, i32 5, metadata !90, null}
!92 = metadata !{i32 32, i32 5, metadata !93, null}
!93 = metadata !{i32 786443, metadata !1, metadata !90, i32 32, i32 5, i32 1, i32 18} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!94 = metadata !{i32 32, i32 5, metadata !95, null}
!95 = metadata !{i32 786443, metadata !1, metadata !90, i32 32, i32 5, i32 2, i32 19} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!96 = metadata !{i32 32, i32 5, metadata !16, null}
!97 = metadata !{i32 786689, metadata !17, metadata !"", metadata !5, i32 16777250, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 34]
!98 = metadata !{i32 34, i32 9, metadata !17, null}
!99 = metadata !{i32 786689, metadata !17, metadata !"", metadata !5, i32 33554466, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 34]
!100 = metadata !{i32 786689, metadata !17, metadata !"", metadata !5, i32 50331682, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 34]
!101 = metadata !{i32 37, i32 9, metadata !102, null}
!102 = metadata !{i32 786443, metadata !1, metadata !17, i32 36, i32 5, i32 0, i32 5} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!103 = metadata !{i32 38, i32 5, metadata !102, null}
!104 = metadata !{i32 38, i32 5, metadata !105, null}
!105 = metadata !{i32 786443, metadata !1, metadata !102, i32 38, i32 5, i32 1, i32 20} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!106 = metadata !{i32 38, i32 5, metadata !107, null}
!107 = metadata !{i32 786443, metadata !1, metadata !102, i32 38, i32 5, i32 2, i32 21} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!108 = metadata !{i32 38, i32 5, metadata !17, null}
!109 = metadata !{i32 786689, metadata !18, metadata !"", metadata !5, i32 16777256, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 40]
!110 = metadata !{i32 40, i32 9, metadata !18, null}
!111 = metadata !{i32 786689, metadata !18, metadata !"", metadata !5, i32 33554472, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 40]
!112 = metadata !{i32 786689, metadata !18, metadata !"", metadata !5, i32 50331688, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 40]
!113 = metadata !{i32 43, i32 9, metadata !114, null}
!114 = metadata !{i32 786443, metadata !1, metadata !18, i32 42, i32 5, i32 0, i32 6} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!115 = metadata !{i32 44, i32 5, metadata !114, null}
!116 = metadata !{i32 44, i32 5, metadata !117, null}
!117 = metadata !{i32 786443, metadata !1, metadata !114, i32 44, i32 5, i32 1, i32 22} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!118 = metadata !{i32 44, i32 5, metadata !119, null}
!119 = metadata !{i32 786443, metadata !1, metadata !114, i32 44, i32 5, i32 2, i32 23} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!120 = metadata !{i32 44, i32 5, metadata !18, null}
!121 = metadata !{i32 786689, metadata !19, metadata !"", metadata !5, i32 16777262, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 46]
!122 = metadata !{i32 46, i32 9, metadata !19, null}
!123 = metadata !{i32 786689, metadata !19, metadata !"", metadata !5, i32 33554478, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 46]
!124 = metadata !{i32 786689, metadata !19, metadata !"", metadata !5, i32 50331694, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 46]
!125 = metadata !{i32 48, i32 9, metadata !126, null}
!126 = metadata !{i32 786443, metadata !1, metadata !19, i32 47, i32 28, i32 0, i32 7} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!127 = metadata !{i32 53, i32 5, metadata !126, null}
!128 = metadata !{i32 53, i32 5, metadata !129, null}
!129 = metadata !{i32 786443, metadata !1, metadata !126, i32 53, i32 5, i32 1, i32 24} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!130 = metadata !{i32 53, i32 5, metadata !131, null}
!131 = metadata !{i32 786443, metadata !1, metadata !126, i32 53, i32 5, i32 2, i32 25} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!132 = metadata !{i32 53, i32 5, metadata !19, null}
!133 = metadata !{i32 786689, metadata !20, metadata !"", metadata !5, i32 16777264, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 48]
!134 = metadata !{i32 48, i32 9, metadata !20, null}
!135 = metadata !{i32 786689, metadata !20, metadata !"", metadata !5, i32 33554480, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 48]
!136 = metadata !{i32 786689, metadata !20, metadata !"", metadata !5, i32 50331696, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 48]
!137 = metadata !{i32 786688, metadata !20, metadata !"i", metadata !5, i32 4, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [i] [line 4]
!138 = metadata !{i32 4, i32 9, metadata !20, null}
!139 = metadata !{i32 50, i32 13, metadata !140, null}
!140 = metadata !{i32 786443, metadata !1, metadata !20, i32 49, i32 32, i32 0, i32 8} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!141 = metadata !{i32 51, i32 13, metadata !140, null}
!142 = metadata !{i32 52, i32 9, metadata !140, null}
!143 = metadata !{i32 52, i32 9, metadata !144, null}
!144 = metadata !{i32 786443, metadata !1, metadata !140, i32 52, i32 9, i32 1, i32 26} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!145 = metadata !{i32 52, i32 9, metadata !146, null}
!146 = metadata !{i32 786443, metadata !1, metadata !140, i32 52, i32 9, i32 2, i32 27} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for.c]
!147 = metadata !{i32 52, i32 9, metadata !20, null}
