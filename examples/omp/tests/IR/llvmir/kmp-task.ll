; ModuleID = 'omp-task.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32*, i32* }
%struct.anon.0 = type { i32* }
%struct.anon.1 = type { i32*, i32* }
%struct.__kmp_depend_info_t = type { i64, i64, i8 }
%struct..omp.task.priv..2 = type { i32 }

@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@0 = private unnamed_addr constant [34 x i8] c";omp-task.c;.omp_microtask.;7;9;;\00"
@.str = private unnamed_addr constant [8 x i8] c"x = %d\0A\00", align 1
@1 = private unnamed_addr constant [34 x i8] c";omp-task.c;.omp_microtask.;9;9;;\00"
@2 = private unnamed_addr constant [35 x i8] c";omp-task.c;.omp_microtask.;14;9;;\00"
@.str2 = private unnamed_addr constant [10 x i8] c"x%d = %d\0A\00", align 1
@3 = private unnamed_addr constant [35 x i8] c";omp-task.c;.omp_microtask.;18;9;;\00"
@4 = private unnamed_addr constant [35 x i8] c";omp-task.c;.omp_microtask.;23;9;;\00"
@5 = private unnamed_addr constant [34 x i8] c";omp-task.c;.omp_microtask.;7;9;;\00"
@.omp.default.loc.320. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 320, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@6 = private unnamed_addr constant [35 x i8] c";omp-task.c;.omp_microtask.;7;19;;\00"
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@7 = private unnamed_addr constant [35 x i8] c";omp-task.c;.omp_microtask.;5;21;;\00"
@8 = private unnamed_addr constant [23 x i8] c";omp-task.c;main;5;9;;\00"
@.str3 = private unnamed_addr constant [14 x i8] c"final x = %d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  %i = alloca i32, align 4
  %agg.captured = alloca %struct.anon, align 8
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 0, i32* %retval
  call void @llvm.dbg.declare(metadata !{i32* %x}, metadata !21), !dbg !22
  store i32 10, i32* %x, align 4, !dbg !23
  call void @llvm.dbg.declare(metadata !{i32* %i}, metadata !24), !dbg !25
  store i32 0, i32* %i, align 4, !dbg !23
  %2 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 0, !dbg !26
  store i32* %x, i32** %2, align 8, !dbg !26
  %3 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 1, !dbg !26
  store i32* %i, i32** %3, align 8, !dbg !26
  %4 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([23 x i8]* @8, i32 0, i32 0), i8** %4
  %5 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %5)
  %6 = load i32* %x, align 4, !dbg !27
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([14 x i8]* @.str3, i32 0, i32 0), i32 %6), !dbg !27
  ret i32 0, !dbg !28
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.(i32*, i32*, i8*) #0 {
entry:
  %.addr = alloca i32*, align 8
  %.addr1 = alloca i32*, align 8
  %.addr2 = alloca i8*, align 8
  %.did_it. = alloca i32, align 4
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %3 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %4 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %agg.captured = alloca %struct.anon.0, align 8
  %.flags.addr = alloca i32, align 4
  %agg.captured6 = alloca %struct.anon.1, align 8
  %.flags.addr7 = alloca i32, align 4
  %.__kmpc_ident_t.320. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.320. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.320. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %7 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %8 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %7, i8* %8, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %.flags.addr7
  store i32 1, i32* %.flags.addr
  store i32 0, i32* %.did_it.
  store i32* %0, i32** %.addr, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !29), !dbg !30
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !31), !dbg !30
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !32), !dbg !30
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !30
  %arg3 = load i8** %.addr2, !dbg !30
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*, !dbg !30
  %9 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 0, !dbg !30
  %ref = load i32** %9, align 8, !dbg !30
  %10 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 1, !dbg !30
  %ref3 = load i32** %10, align 8, !dbg !30
  store i32 0, i32* %.did_it., align 4, !dbg !33
  %11 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([34 x i8]* @0, i32 0, i32 0), i8** %11
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  %12 = call i32 @__kmpc_single({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.)
  %tobool = icmp ne i32 %12, 0
  br i1 %tobool, label %omp.single.then, label %omp.single.end

omp.single.then:                                  ; preds = %entry
  %13 = getelementptr inbounds %struct.anon.0* %agg.captured, i32 0, i32 0, !dbg !35
  store i32* %ref, i32** %13, align 8, !dbg !35
  %14 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !35
  store i8* getelementptr inbounds ([34 x i8]* @1, i32 0, i32 0), i8** %14, !dbg !35
  %.gtid.4 = load i32* %.__kmpc_global_thread_num., !dbg !35
  %.flags. = load i32* %.flags.addr, !dbg !35
  %.task_t.val.addr = call { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* @__kmpc_omp_task_alloc({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4, i32 %.flags., i64 ptrtoint ({ i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* getelementptr ({ i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* null, i32 1) to i64), i64 8, i32 (i32, i8*)* @.omp_ptask.), !dbg !35
  %.shared.addr = getelementptr inbounds { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr, i32 0, i32 0, !dbg !35
  %15 = load i8** %.shared.addr, !dbg !35
  %16 = bitcast %struct.anon.0* %agg.captured to i8*, !dbg !35
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %15, i8* %16, i64 8, i32 8, i1 false), !dbg !35
  %17 = getelementptr { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr, i32 1, !dbg !35
  %.task.res. = call i32 @__kmpc_omp_task_with_deps({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4, { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr, i32 0, %struct.__kmp_depend_info_t* null, i32 0, %struct.__kmp_depend_info_t* null), !dbg !35
  %18 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !37
  store i8* getelementptr inbounds ([35 x i8]* @2, i32 0, i32 0), i8** %18, !dbg !37
  %.gtid.5 = load i32* %.__kmpc_global_thread_num., !dbg !37
  %19 = call i32 @__kmpc_omp_taskwait({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.5), !dbg !37
  store i32 0, i32* %ref3, align 4, !dbg !38
  br label %for.cond, !dbg !38

for.cond:                                         ; preds = %for.inc, %omp.single.then
  %20 = load i32* %ref3, align 4, !dbg !40
  %cmp = icmp slt i32 %20, 4, !dbg !40
  br i1 %cmp, label %for.body, label %for.end, !dbg !40

for.body:                                         ; preds = %for.cond
  %21 = getelementptr inbounds %struct.anon.1* %agg.captured6, i32 0, i32 0, !dbg !43
  store i32* %ref3, i32** %21, align 8, !dbg !43
  %22 = getelementptr inbounds %struct.anon.1* %agg.captured6, i32 0, i32 1, !dbg !43
  store i32* %ref, i32** %22, align 8, !dbg !43
  %23 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !43
  store i8* getelementptr inbounds ([35 x i8]* @3, i32 0, i32 0), i8** %23, !dbg !43
  %.gtid.8 = load i32* %.__kmpc_global_thread_num., !dbg !43
  %.flags.9 = load i32* %.flags.addr7, !dbg !43
  %.task_t.val.addr10 = call { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* @__kmpc_omp_task_alloc({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.8, i32 %.flags.9, i64 add (i64 ptrtoint ({ i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* getelementptr ({ i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* null, i32 1) to i64), i64 4), i64 16, i32 (i32, i8*)* @.omp_ptask.1), !dbg !43
  %.shared.addr11 = getelementptr inbounds { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr10, i32 0, i32 0, !dbg !43
  %24 = load i8** %.shared.addr11, !dbg !43
  %25 = bitcast %struct.anon.1* %agg.captured6 to i8*, !dbg !43
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %24, i8* %25, i64 16, i32 8, i1 false), !dbg !43
  %26 = getelementptr { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr10, i32 1, !dbg !43
  %27 = bitcast { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %26 to %struct..omp.task.priv..2*, !dbg !43
  %i = getelementptr inbounds %struct..omp.task.priv..2* %27, i32 0, i32 0, !dbg !43
  %28 = load i32* %ref3, align 4, !dbg !43
  store i32 %28, i32* %i, !dbg !43
  %.task.res.12 = call i32 @__kmpc_omp_task_with_deps({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.8, { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr10, i32 0, %struct.__kmp_depend_info_t* null, i32 0, %struct.__kmp_depend_info_t* null), !dbg !43
  br label %for.inc, !dbg !45

for.inc:                                          ; preds = %for.body
  %29 = load i32* %ref3, align 4, !dbg !46
  %inc = add nsw i32 %29, 1, !dbg !46
  store i32 %inc, i32* %ref3, align 4, !dbg !46
  br label %for.cond, !dbg !46

for.end:                                          ; preds = %for.cond
  %30 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !47
  store i8* getelementptr inbounds ([35 x i8]* @4, i32 0, i32 0), i8** %30, !dbg !47
  %.gtid.13 = load i32* %.__kmpc_global_thread_num., !dbg !47
  %31 = call i32 @__kmpc_omp_taskwait({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.13), !dbg !47
  store i32 1, i32* %.did_it., align 4, !dbg !48
  %32 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !48
  store i8* getelementptr inbounds ([34 x i8]* @5, i32 0, i32 0), i8** %32, !dbg !48
  %.gtid.14 = load i32* %.__kmpc_global_thread_num., !dbg !48
  call void @__kmpc_end_single({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.14), !dbg !48
  br label %omp.single.end, !dbg !48

omp.single.end:                                   ; preds = %for.end, %entry
  %33 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.320., i32 0, i32 4
  store i8* getelementptr inbounds ([35 x i8]* @6, i32 0, i32 0), i8** %33
  %.gtid.15 = load i32* %.__kmpc_global_thread_num.
  %34 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.320., i32 %.gtid.15)
  %35 = icmp ne i32 %34, 0
  br i1 %35, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.single.end
  br label %omp.cancel_barrier.continue18

omp.cancel_barrier.continue:                      ; preds = %omp.single.end
  %36 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([35 x i8]* @7, i32 0, i32 0), i8** %36
  %.gtid.16 = load i32* %.__kmpc_global_thread_num.
  %37 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.16)
  %38 = icmp ne i32 %37, 0
  br i1 %38, label %omp.cancel_barrier.exit17, label %omp.cancel_barrier.continue18

omp.cancel_barrier.exit17:                        ; preds = %omp.cancel_barrier.continue
  br label %omp.cancel_barrier.continue18

omp.cancel_barrier.continue18:                    ; preds = %omp.cancel_barrier.exit, %omp.cancel_barrier.exit17, %omp.cancel_barrier.continue
  ret void, !dbg !49
}

declare void @__kmpc_end_single({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_single({ i32, i32, i32, i32, i8* }*, i32)

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

; Function Attrs: nounwind uwtable
define internal i32 @.omp_ptask.(i32, i8*) #0 {
entry:
  %retval = alloca i32, align 4
  %.addr = alloca i32, align 4
  %.addr1 = alloca i8*, align 8
  %.__kmpc_global_thread_num. = alloca i32, align 4
  store i32 %0, i32* %.addr, align 4
  call void @llvm.dbg.declare(metadata !{i32* %.addr}, metadata !50), !dbg !51
  store i8* %1, i8** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr1}, metadata !52), !dbg !51
  %2 = load i32* %.addr, !dbg !51
  store i32 %2, i32* %.__kmpc_global_thread_num., align 4, !dbg !51
  %3 = bitcast i8** %.addr1 to { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }**, !dbg !51
  %.arg2.shareds = load { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }** %3, !dbg !51
  %.arg2.shareds.addr = getelementptr inbounds { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.arg2.shareds, i32 0, i32 0, !dbg !51
  %.arg2.shareds. = load i8** %.arg2.shareds.addr, !dbg !51
  %"(anon)shared" = bitcast i8* %.arg2.shareds. to %struct.anon.0*, !dbg !51
  %4 = load { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }** %3, !dbg !51
  %5 = getelementptr { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %4, i32 1, !dbg !51
  %6 = getelementptr inbounds %struct.anon.0* %"(anon)shared", i32 0, i32 0, !dbg !51
  %ref = load i32** %6, align 8, !dbg !51
  %7 = load i32* %ref, align 4, !dbg !53
  %add = add nsw i32 %7, 1, !dbg !53
  store i32 %add, i32* %ref, align 4, !dbg !53
  %8 = load i32* %ref, align 4, !dbg !55
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([8 x i8]* @.str, i32 0, i32 0), i32 %8), !dbg !55
  %9 = load i32* %retval, !dbg !56
  ret i32 %9, !dbg !56
}

declare i32 @printf(i8*, ...) #3

declare { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* @__kmpc_omp_task_alloc({ i32, i32, i32, i32, i8* }*, i32, i32, i64, i64, i32 (i32, i8*)*)

declare i32 @__kmpc_omp_task_with_deps({ i32, i32, i32, i32, i8* }*, i32, { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }*, i32, %struct.__kmp_depend_info_t*, i32, %struct.__kmp_depend_info_t*)

declare i32 @__kmpc_omp_taskwait({ i32, i32, i32, i32, i8* }*, i32)

; Function Attrs: nounwind uwtable
define internal i32 @.omp_ptask.1(i32, i8*) #0 {
entry:
  %retval = alloca i32, align 4
  %.addr = alloca i32, align 4
  %.addr1 = alloca i8*, align 8
  %.__kmpc_global_thread_num. = alloca i32, align 4
  store i32 %0, i32* %.addr, align 4
  call void @llvm.dbg.declare(metadata !{i32* %.addr}, metadata !57), !dbg !58
  store i8* %1, i8** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr1}, metadata !59), !dbg !58
  %2 = load i32* %.addr, !dbg !58
  store i32 %2, i32* %.__kmpc_global_thread_num., align 4, !dbg !58
  %3 = bitcast i8** %.addr1 to { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }**, !dbg !58
  %.arg2.shareds = load { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }** %3, !dbg !58
  %.arg2.shareds.addr = getelementptr inbounds { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.arg2.shareds, i32 0, i32 0, !dbg !58
  %.arg2.shareds. = load i8** %.arg2.shareds.addr, !dbg !58
  %"(anon)shared" = bitcast i8* %.arg2.shareds. to %struct.anon.1*, !dbg !58
  %4 = load { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }** %3, !dbg !58
  %5 = getelementptr { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %4, i32 1, !dbg !58
  %6 = getelementptr inbounds %struct.anon.1* %"(anon)shared", i32 0, i32 0, !dbg !58
  %ref = load i32** %6, align 8, !dbg !58
  %7 = getelementptr inbounds %struct.anon.1* %"(anon)shared", i32 0, i32 1, !dbg !58
  %ref2 = load i32** %7, align 8, !dbg !58
  %8 = bitcast { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %5 to %struct..omp.task.priv..2*, !dbg !58
  %i = getelementptr inbounds %struct..omp.task.priv..2* %8, i32 0, i32 0, !dbg !58
  %9 = load i32* %i, align 4, !dbg !60
  %10 = load i32* %ref2, align 4, !dbg !60
  %11 = load i32* %i, align 4, !dbg !60
  %add = add nsw i32 %10, %11, !dbg !60
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([10 x i8]* @.str2, i32 0, i32 0), i32 %9, i32 %add), !dbg !60
  %12 = load i32* %retval, !dbg !62
  ret i32 %12, !dbg !62
}

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }
attributes #3 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!18, !19}
!llvm.ident = !{!20}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 1} ; [ DW_TAG_compile_unit ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-task.c] [DW_LANG_C99]
!1 = metadata !{metadata !"omp-task.c", metadata !"/home/jeremy/code/research/hpxMP/omp-tests"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !9, metadata !14, metadata !17}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"main", metadata !"main", metadata !"", i32 3, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 ()* @main, null, null, metadata !2, i32 3} ; [ DW_TAG_subprogram ] [line 3] [def] [main]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-task.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{metadata !8}
!8 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!9 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 5, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask., null, null, metadata !2, i32 5} ; [ DW_TAG_subprogram ] [line 5] [local] [def] [.omp_microtask.]
!10 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{null, metadata !12, metadata !12, metadata !13}
!12 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !8} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from int]
!13 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!14 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_ptask.", metadata !".omp_ptask.", metadata !"", i32 9, metadata !15, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 (i32, i8*)* @.omp_ptask., null, null, metadata !2, i32 9} ; [ DW_TAG_subprogram ] [line 9] [local] [def] [.omp_ptask.]
!15 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !16, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!16 = metadata !{metadata !8, metadata !8, metadata !13}
!17 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_ptask.", metadata !".omp_ptask.", metadata !"", i32 18, metadata !15, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 (i32, i8*)* @.omp_ptask.1, null, null, metadata !2, i32 18} ; [ DW_TAG_subprogram ] [line 18] [local] [def] [.omp_ptask.]
!18 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!19 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!20 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
!21 = metadata !{i32 786688, metadata !4, metadata !"x", metadata !5, i32 4, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [x] [line 4]
!22 = metadata !{i32 4, i32 9, metadata !4, null}
!23 = metadata !{i32 4, i32 5, metadata !4, null}
!24 = metadata !{i32 786688, metadata !4, metadata !"i", metadata !5, i32 4, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [i] [line 4]
!25 = metadata !{i32 4, i32 17, metadata !4, null}
!26 = metadata !{i32 5, i32 9, metadata !4, null}
!27 = metadata !{i32 26, i32 5, metadata !4, null}
!28 = metadata !{i32 27, i32 5, metadata !4, null}
!29 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 16777221, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 5]
!30 = metadata !{i32 5, i32 9, metadata !9, null}
!31 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 33554437, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 5]
!32 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 50331653, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 5]
!33 = metadata !{i32 7, i32 9, metadata !34, null}
!34 = metadata !{i32 786443, metadata !1, metadata !9, i32 6, i32 5, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-task.c]
!35 = metadata !{i32 9, i32 9, metadata !36, null}
!36 = metadata !{i32 786443, metadata !1, metadata !34, i32 8, i32 9, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-task.c]
!37 = metadata !{i32 14, i32 9, metadata !36, null}
!38 = metadata !{i32 16, i32 17, metadata !39, null}
!39 = metadata !{i32 786443, metadata !1, metadata !36, i32 16, i32 13, i32 0, i32 3} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-task.c]
!40 = metadata !{i32 16, i32 17, metadata !41, null}
!41 = metadata !{i32 786443, metadata !1, metadata !42, i32 16, i32 17, i32 2, i32 7} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-task.c]
!42 = metadata !{i32 786443, metadata !1, metadata !39, i32 16, i32 17, i32 1, i32 6} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-task.c]
!43 = metadata !{i32 18, i32 9, metadata !44, null}
!44 = metadata !{i32 786443, metadata !1, metadata !39, i32 17, i32 13, i32 0, i32 4} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-task.c]
!45 = metadata !{i32 22, i32 13, metadata !44, null}
!46 = metadata !{i32 16, i32 31, metadata !39, null}
!47 = metadata !{i32 23, i32 9, metadata !36, null}
!48 = metadata !{i32 24, i32 9, metadata !36, null}
!49 = metadata !{i32 25, i32 5, metadata !9, null}
!50 = metadata !{i32 786689, metadata !14, metadata !"", metadata !5, i32 16777225, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 9]
!51 = metadata !{i32 9, i32 9, metadata !14, null}
!52 = metadata !{i32 786689, metadata !14, metadata !"", metadata !5, i32 33554441, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 9]
!53 = metadata !{i32 11, i32 17, metadata !54, null}
!54 = metadata !{i32 786443, metadata !1, metadata !14, i32 10, i32 13, i32 0, i32 2} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-task.c]
!55 = metadata !{i32 12, i32 17, metadata !54, null}
!56 = metadata !{i32 13, i32 13, metadata !14, null}
!57 = metadata !{i32 786689, metadata !17, metadata !"", metadata !5, i32 16777234, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 18]
!58 = metadata !{i32 18, i32 9, metadata !17, null}
!59 = metadata !{i32 786689, metadata !17, metadata !"", metadata !5, i32 33554450, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 18]
!60 = metadata !{i32 20, i32 21, metadata !61, null}
!61 = metadata !{i32 786443, metadata !1, metadata !17, i32 19, i32 17, i32 0, i32 5} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-task.c]
!62 = metadata !{i32 21, i32 17, metadata !17, null}
