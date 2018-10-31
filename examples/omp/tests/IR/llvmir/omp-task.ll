; ModuleID = 'src/omp-task.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32*, i32* }
%struct.anon.0 = type { i32* }
%struct.anon.1 = type { i32*, i32* }
%struct.__kmp_depend_info_t = type { i64, i64, i8 }
%struct..omp.task.priv..2 = type { i32 }

@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.str = private unnamed_addr constant [8 x i8] c"x = %d\0A\00", align 1
@.str2 = private unnamed_addr constant [10 x i8] c"x%d = %d\0A\00", align 1
@.omp.default.loc.320. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 320, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
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
  store i32 10, i32* %x, align 4
  store i32 0, i32* %i, align 4
  %2 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 0
  store i32* %x, i32** %2, align 8
  %3 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 1
  store i32* %i, i32** %3, align 8
  %4 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %4)
  %5 = load i32* %x, align 4
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([14 x i8]* @.str3, i32 0, i32 0), i32 %5)
  ret i32 0
}

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
  store i32* %1, i32** %.addr1, align 8
  store i8* %2, i8** %.addr2, align 8
  %.__kmpc_global_thread_num. = load i32** %.addr
  %arg3 = load i8** %.addr2
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*
  %9 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 0
  %ref = load i32** %9, align 8
  %10 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 1
  %ref3 = load i32** %10, align 8
  store i32 0, i32* %.did_it., align 4
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  %11 = call i32 @__kmpc_single({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.)
  %tobool = icmp ne i32 %11, 0
  br i1 %tobool, label %omp.single.then, label %omp.single.end

omp.single.then:                                  ; preds = %entry
  %12 = getelementptr inbounds %struct.anon.0* %agg.captured, i32 0, i32 0
  store i32* %ref, i32** %12, align 8
  %.gtid.4 = load i32* %.__kmpc_global_thread_num.
  %.flags. = load i32* %.flags.addr
  %.task_t.val.addr = call { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* @__kmpc_omp_task_alloc({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4, i32 %.flags., i64 ptrtoint ({ i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* getelementptr ({ i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* null, i32 1) to i64), i64 8, i32 (i32, i8*)* @.omp_ptask.)
  %.shared.addr = getelementptr inbounds { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr, i32 0, i32 0
  %13 = load i8** %.shared.addr
  %14 = bitcast %struct.anon.0* %agg.captured to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %13, i8* %14, i64 8, i32 8, i1 false)
  %15 = getelementptr { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr, i32 1
  %.task.res. = call i32 @__kmpc_omp_task_with_deps({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4, { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr, i32 0, %struct.__kmp_depend_info_t* null, i32 0, %struct.__kmp_depend_info_t* null)
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %16 = call i32 @__kmpc_omp_taskwait({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.5)
  store i32 0, i32* %ref3, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %omp.single.then
  %17 = load i32* %ref3, align 4
  %cmp = icmp slt i32 %17, 4
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %18 = getelementptr inbounds %struct.anon.1* %agg.captured6, i32 0, i32 0
  store i32* %ref3, i32** %18, align 8
  %19 = getelementptr inbounds %struct.anon.1* %agg.captured6, i32 0, i32 1
  store i32* %ref, i32** %19, align 8
  %.gtid.8 = load i32* %.__kmpc_global_thread_num.
  %.flags.9 = load i32* %.flags.addr7
  %.task_t.val.addr10 = call { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* @__kmpc_omp_task_alloc({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.8, i32 %.flags.9, i64 add (i64 ptrtoint ({ i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* getelementptr ({ i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* null, i32 1) to i64), i64 4), i64 16, i32 (i32, i8*)* @.omp_ptask.1)
  %.shared.addr11 = getelementptr inbounds { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr10, i32 0, i32 0
  %20 = load i8** %.shared.addr11
  %21 = bitcast %struct.anon.1* %agg.captured6 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %20, i8* %21, i64 16, i32 8, i1 false)
  %22 = getelementptr { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr10, i32 1
  %23 = bitcast { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %22 to %struct..omp.task.priv..2*
  %i = getelementptr inbounds %struct..omp.task.priv..2* %23, i32 0, i32 0
  %24 = load i32* %ref3, align 4
  store i32 %24, i32* %i
  %.task.res.12 = call i32 @__kmpc_omp_task_with_deps({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.8, { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr10, i32 0, %struct.__kmp_depend_info_t* null, i32 0, %struct.__kmp_depend_info_t* null)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %25 = load i32* %ref3, align 4
  %inc = add nsw i32 %25, 1
  store i32 %inc, i32* %ref3, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %.gtid.13 = load i32* %.__kmpc_global_thread_num.
  %26 = call i32 @__kmpc_omp_taskwait({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.13)
  store i32 1, i32* %.did_it., align 4
  %.gtid.14 = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_end_single({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.14)
  br label %omp.single.end

omp.single.end:                                   ; preds = %for.end, %entry
  %.gtid.15 = load i32* %.__kmpc_global_thread_num.
  %27 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.320., i32 %.gtid.15)
  %28 = icmp ne i32 %27, 0
  br i1 %28, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.single.end
  br label %omp.cancel_barrier.continue18

omp.cancel_barrier.continue:                      ; preds = %omp.single.end
  %.gtid.16 = load i32* %.__kmpc_global_thread_num.
  %29 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.16)
  %30 = icmp ne i32 %29, 0
  br i1 %30, label %omp.cancel_barrier.exit17, label %omp.cancel_barrier.continue18

omp.cancel_barrier.exit17:                        ; preds = %omp.cancel_barrier.continue
  br label %omp.cancel_barrier.continue18

omp.cancel_barrier.continue18:                    ; preds = %omp.cancel_barrier.exit, %omp.cancel_barrier.exit17, %omp.cancel_barrier.continue
  ret void
}

declare void @__kmpc_end_single({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_single({ i32, i32, i32, i32, i8* }*, i32)

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #1

; Function Attrs: nounwind uwtable
define internal i32 @.omp_ptask.(i32, i8*) #0 {
entry:
  %retval = alloca i32, align 4
  %.addr = alloca i32, align 4
  %.addr1 = alloca i8*, align 8
  %.__kmpc_global_thread_num. = alloca i32, align 4
  store i32 %0, i32* %.addr, align 4
  store i8* %1, i8** %.addr1, align 8
  %2 = load i32* %.addr
  store i32 %2, i32* %.__kmpc_global_thread_num., align 4
  %3 = bitcast i8** %.addr1 to { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }**
  %.arg2.shareds = load { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }** %3
  %.arg2.shareds.addr = getelementptr inbounds { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.arg2.shareds, i32 0, i32 0
  %.arg2.shareds. = load i8** %.arg2.shareds.addr
  %"(anon)shared" = bitcast i8* %.arg2.shareds. to %struct.anon.0*
  %4 = load { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }** %3
  %5 = getelementptr { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %4, i32 1
  %6 = getelementptr inbounds %struct.anon.0* %"(anon)shared", i32 0, i32 0
  %ref = load i32** %6, align 8
  %7 = load i32* %ref, align 4
  %add = add nsw i32 %7, 1
  store i32 %add, i32* %ref, align 4
  %8 = load i32* %ref, align 4
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([8 x i8]* @.str, i32 0, i32 0), i32 %8)
  %9 = load i32* %retval
  ret i32 %9
}

declare i32 @printf(i8*, ...) #2

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
  store i8* %1, i8** %.addr1, align 8
  %2 = load i32* %.addr
  store i32 %2, i32* %.__kmpc_global_thread_num., align 4
  %3 = bitcast i8** %.addr1 to { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }**
  %.arg2.shareds = load { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }** %3
  %.arg2.shareds.addr = getelementptr inbounds { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.arg2.shareds, i32 0, i32 0
  %.arg2.shareds. = load i8** %.arg2.shareds.addr
  %"(anon)shared" = bitcast i8* %.arg2.shareds. to %struct.anon.1*
  %4 = load { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }** %3
  %5 = getelementptr { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %4, i32 1
  %6 = getelementptr inbounds %struct.anon.1* %"(anon)shared", i32 0, i32 0
  %ref = load i32** %6, align 8
  %7 = getelementptr inbounds %struct.anon.1* %"(anon)shared", i32 0, i32 1
  %ref2 = load i32** %7, align 8
  %8 = bitcast { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %5 to %struct..omp.task.priv..2*
  %i = getelementptr inbounds %struct..omp.task.priv..2* %8, i32 0, i32 0
  %9 = load i32* %i, align 4
  %10 = load i32* %ref2, align 4
  %11 = load i32* %i, align 4
  %add = add nsw i32 %10, %11
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([10 x i8]* @.str2, i32 0, i32 0), i32 %9, i32 %add)
  %12 = load i32* %retval
  ret i32 %12
}

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
