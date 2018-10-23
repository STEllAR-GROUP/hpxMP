; ModuleID = 'omp-single-copyprivate.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32*, i32* }

@LOOPCOUNT = constant i32 10, align 4
@j.cache. = common global i8** null
@j = common global i32 0, align 4
@var2.cache. = common global i8** null
@var2 = common global i32 0, align 4
@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.gomp_critical_user_.var = common global [8 x i32] zeroinitializer
@.omp.default.loc.32. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 32, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.str = private unnamed_addr constant [33 x i8] c"result = %d, nr_iterations = %d\0A\00", align 1
@.str1 = private unnamed_addr constant [19 x i8] c"result is correct\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @test_omp_single_copyprivate() #0 {
entry:
  %result = alloca i32, align 4
  %nr_iterations = alloca i32, align 4
  %agg.captured = alloca %struct.anon, align 8
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 0, i32* %result, align 4
  store i32 0, i32* %nr_iterations, align 4
  %2 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 0
  store i32* %nr_iterations, i32** %2, align 8
  %3 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 1
  store i32* %result, i32** %3, align 8
  %4 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %4)
  %5 = load i32* %result, align 4
  %cmp = icmp eq i32 %5, 0
  br i1 %cmp, label %land.lhs.true, label %if.then

land.lhs.true:                                    ; preds = %entry
  %6 = load i32* %nr_iterations, align 4
  %cmp1 = icmp eq i32 %6, 10
  br i1 %cmp1, label %if.end, label %if.then

if.then:                                          ; preds = %land.lhs.true, %entry
  %7 = load i32* %result, align 4
  %8 = load i32* %nr_iterations, align 4
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([33 x i8]* @.str, i32 0, i32 0), i32 %7, i32 %8)
  br label %if.end

if.end:                                           ; preds = %if.then, %land.lhs.true
  %9 = load i32* %result, align 4
  %cmp2 = icmp eq i32 %9, 0
  br i1 %cmp2, label %land.rhs, label %land.end

land.rhs:                                         ; preds = %if.end
  %10 = load i32* %nr_iterations, align 4
  %cmp3 = icmp eq i32 %10, 10
  br label %land.end

land.end:                                         ; preds = %land.rhs, %if.end
  %11 = phi i1 [ false, %if.end ], [ %cmp3, %land.rhs ]
  %land.ext = zext i1 %11 to i32
  ret i32 %land.ext
}

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.(i32*, i32*, i8*) #0 {
entry:
  %.addr = alloca i32*, align 8
  %.addr1 = alloca i32*, align 8
  %.addr2 = alloca i8*, align 8
  %i = alloca i32, align 4
  %.did_it. = alloca i32, align 4
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %3 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %4 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %cpy.var = alloca { i32*, i32* }, align 8
  %.__kmpc_ident_t.32. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.32. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.32. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %7 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %8 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %7, i8* %8, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
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
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %11 = load i32* %i, align 4
  %cmp = icmp slt i32 %11, 10
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %.did_it., align 4
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  %12 = call i32 @__kmpc_single({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.)
  %tobool = icmp ne i32 %12, 0
  br i1 %tobool, label %omp.single.then, label %omp.single.end

omp.single.then:                                  ; preds = %for.body
  %13 = load i32* %ref, align 4
  %inc = add nsw i32 %13, 1
  store i32 %inc, i32* %ref, align 4
  %14 = load i32* %i, align 4
  %.gtid.4 = load i32* %.__kmpc_global_thread_num.
  %15 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4, i8* bitcast (i32* @j to i8*), i64 4, i8*** @j.cache.)
  %16 = bitcast i8* %15 to i32*
  store i32 %14, i32* %16, align 4
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %17 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.5, i8* bitcast (i32* @j to i8*), i64 4, i8*** @j.cache.)
  %18 = bitcast i8* %17 to i32*
  %19 = load i32* %18, align 4
  %.gtid.6 = load i32* %.__kmpc_global_thread_num.
  %20 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.6, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.)
  %21 = bitcast i8* %20 to i32*
  store i32 %19, i32* %21, align 4
  store i32 1, i32* %.did_it., align 4
  %.gtid.7 = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_end_single({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.7)
  br label %omp.single.end

omp.single.end:                                   ; preds = %omp.single.then, %for.body
  %22 = getelementptr { i32*, i32* }* %cpy.var, i32 0, i32 0
  %.gtid.8 = load i32* %.__kmpc_global_thread_num.
  %23 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.8, i8* bitcast (i32* @j to i8*), i64 4, i8*** @j.cache.)
  %24 = bitcast i8* %23 to i32*
  store i32* %24, i32** %22
  %25 = getelementptr { i32*, i32* }* %cpy.var, i32 0, i32 1
  %.gtid.9 = load i32* %.__kmpc_global_thread_num.
  %26 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.9, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.)
  %27 = bitcast i8* %26 to i32*
  store i32* %27, i32** %25
  %.gtid.10 = load i32* %.__kmpc_global_thread_num.
  %28 = load i32* %.did_it., align 4
  %"(void*)cpyrec" = bitcast { i32*, i32* }* %cpy.var to i8*
  call void @__kmpc_copyprivate({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.10, i64 16, i8* %"(void*)cpyrec", void (i8*, i8*)* @.omp_copy_func., i32 %28)
  %.gtid.11 = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_critical({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.11, [8 x i32]* @.gomp_critical_user_.var)
  %29 = load i32* %ref3, align 4
  %.gtid.12 = load i32* %.__kmpc_global_thread_num.
  %30 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.12, i8* bitcast (i32* @j to i8*), i64 4, i8*** @j.cache.)
  %31 = bitcast i8* %30 to i32*
  %32 = load i32* %31, align 4
  %add = add nsw i32 %29, %32
  %33 = load i32* %i, align 4
  %sub = sub nsw i32 %add, %33
  store i32 %sub, i32* %ref3, align 4
  call void @__kmpc_end_critical({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.11, [8 x i32]* @.gomp_critical_user_.var)
  %.gtid.13 = load i32* %.__kmpc_global_thread_num.
  %34 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.32., i32 %.gtid.13)
  %35 = icmp ne i32 %34, 0
  br i1 %35, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.single.end
  br label %omp.cancel_barrier.continue17

omp.cancel_barrier.continue:                      ; preds = %omp.single.end
  br label %for.inc

for.inc:                                          ; preds = %omp.cancel_barrier.continue
  %36 = load i32* %i, align 4
  %inc14 = add nsw i32 %36, 1
  store i32 %inc14, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %.gtid.15 = load i32* %.__kmpc_global_thread_num.
  %37 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.15)
  %38 = icmp ne i32 %37, 0
  br i1 %38, label %omp.cancel_barrier.exit16, label %omp.cancel_barrier.continue17

omp.cancel_barrier.exit16:                        ; preds = %for.end
  br label %omp.cancel_barrier.continue17

omp.cancel_barrier.continue17:                    ; preds = %omp.cancel_barrier.exit, %omp.cancel_barrier.exit16, %for.end
  ret void
}

declare void @__kmpc_end_single({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_single({ i32, i32, i32, i32, i8* }*, i32)

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #1

declare i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }*, i32, i8*, i64, i8***)

; Function Attrs: nounwind uwtable
define internal void @.omp_copy_func.(i8*, i8*) #0 {
entry:
  %.addr = alloca i8*, align 8
  %.addr1 = alloca i8*, align 8
  store i8* %0, i8** %.addr, align 8
  store i8* %1, i8** %.addr1, align 8
  %cpy.dst = bitcast i8* %0 to { i32*, i32* }*
  %cpy.src = bitcast i8* %1 to { i32*, i32* }*
  %2 = getelementptr { i32*, i32* }* %cpy.dst, i32 0, i32 0
  %3 = getelementptr { i32*, i32* }* %cpy.src, i32 0, i32 0
  %4 = load i32** %2, align 8
  %5 = load i32** %3, align 8
  %6 = load i32* %5, align 4
  store i32 %6, i32* %4, align 4
  %7 = getelementptr { i32*, i32* }* %cpy.dst, i32 0, i32 1
  %8 = getelementptr { i32*, i32* }* %cpy.src, i32 0, i32 1
  %9 = load i32** %7, align 8
  %10 = load i32** %8, align 8
  %11 = load i32* %10, align 4
  store i32 %11, i32* %9, align 4
  ret void
}

declare void @__kmpc_copyprivate({ i32, i32, i32, i32, i8* }*, i32, i64, i8*, void (i8*, i8*)*, i32)

declare void @__kmpc_critical({ i32, i32, i32, i32, i8* }*, i32, [8 x i32]*)

declare void @__kmpc_end_critical({ i32, i32, i32, i32, i8* }*, i32, [8 x i32]*)

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

declare i32 @printf(i8*, ...) #2

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval
  %call = call i32 @test_omp_single_copyprivate()
  %tobool = icmp ne i32 %call, 0
  br i1 %tobool, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %call1 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([19 x i8]* @.str1, i32 0, i32 0))
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  ret i32 0
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
