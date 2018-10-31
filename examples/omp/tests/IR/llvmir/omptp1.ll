; ModuleID = 'omp-threadprivate.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type {}

@var1.cache. = common global i8** null
@var1 = common global i32 0, align 4
@var2.cache. = common global i8** null
@var2 = common global i32 0, align 4
@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.str = private unnamed_addr constant [27 x i8] c"Initial, var1 = %d, at %p\0A\00", align 1
@.str1 = private unnamed_addr constant [27 x i8] c"Initial, var2 = %d, at %p\0A\00", align 1
@.str2 = private unnamed_addr constant [33 x i8] c"Thread %d, var1 = %d, var2 = %d\0A\00", align 1
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.str3 = private unnamed_addr constant [25 x i8] c"Final, var1 = %d, at %p\0A\00", align 1
@.str4 = private unnamed_addr constant [25 x i8] c"Final, var2 = %d, at %p\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %.__kmpc_global_thread_num. = alloca i32, align 4
  %2 = call i32 @__kmpc_global_thread_num({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2.)
  store i32 %2, i32* %.__kmpc_global_thread_num.
  %agg.captured = alloca %struct.anon, align 1
  store i32 0, i32* %retval
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  %3 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.)
  %4 = bitcast i8* %3 to i32*
  store i32 -1, i32* %4, align 4
  %.gtid.1 = load i32* %.__kmpc_global_thread_num.
  %5 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.1, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.)
  %6 = bitcast i8* %5 to i32*
  store i32 -2, i32* %6, align 4
  %.gtid.2 = load i32* %.__kmpc_global_thread_num.
  %7 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.2, i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.)
  %8 = bitcast i8* %7 to i32*
  %9 = load i32* %8, align 4
  %.gtid.3 = load i32* %.__kmpc_global_thread_num.
  %10 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.3, i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.)
  %11 = bitcast i8* %10 to i32*
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([27 x i8]* @.str, i32 0, i32 0), i32 %9, i32* %11)
  %.gtid.4 = load i32* %.__kmpc_global_thread_num.
  %12 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.)
  %13 = bitcast i8* %12 to i32*
  %14 = load i32* %13, align 4
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %15 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.5, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.)
  %16 = bitcast i8* %15 to i32*
  %call6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([27 x i8]* @.str1, i32 0, i32 0), i32 %14, i32* %16)
  %17 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %17)
  %.gtid.7 = load i32* %.__kmpc_global_thread_num.
  %18 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.7, i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.)
  %19 = bitcast i8* %18 to i32*
  %20 = load i32* %19, align 4
  %.gtid.8 = load i32* %.__kmpc_global_thread_num.
  %21 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.8, i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.)
  %22 = bitcast i8* %21 to i32*
  %call9 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @.str3, i32 0, i32 0), i32 %20, i32* %22)
  %.gtid.10 = load i32* %.__kmpc_global_thread_num.
  %23 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.10, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.)
  %24 = bitcast i8* %23 to i32*
  %25 = load i32* %24, align 4
  %.gtid.11 = load i32* %.__kmpc_global_thread_num.
  %26 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.11, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.)
  %27 = bitcast i8* %26 to i32*
  %call12 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @.str4, i32 0, i32 0), i32 %25, i32* %27)
  ret i32 0
}

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #1

declare i32 @__kmpc_global_thread_num({ i32, i32, i32, i32, i8* }*)

declare i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }*, i32, i8*, i64, i8***)

declare i32 @printf(i8*, ...) #2

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
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32* %0, i32** %.addr, align 8
  store i32* %1, i32** %.addr1, align 8
  store i8* %2, i8** %.addr2, align 8
  %.__kmpc_global_thread_num. = load i32** %.addr
  %arg3 = load i8** %.addr2
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*
  %call = call i32 @omp_get_thread_num()
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  %7 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.)
  %8 = bitcast i8* %7 to i32*
  store i32 %call, i32* %8, align 4
  %call3 = call i32 @omp_get_thread_num()
  %.gtid.4 = load i32* %.__kmpc_global_thread_num.
  %9 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4, i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.)
  %10 = bitcast i8* %9 to i32*
  %11 = load i32* %10, align 4
  %.gtid.5 = load i32* %.__kmpc_global_thread_num.
  %12 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.5, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.)
  %13 = bitcast i8* %12 to i32*
  %14 = load i32* %13, align 4
  %call6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([33 x i8]* @.str2, i32 0, i32 0), i32 %call3, i32 %11, i32 %14)
  %.gtid.7 = load i32* %.__kmpc_global_thread_num.
  %15 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.7)
  %16 = icmp ne i32 %15, 0
  br i1 %16, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %entry
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %entry
  ret void
}

declare i32 @omp_get_thread_num() #2

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
