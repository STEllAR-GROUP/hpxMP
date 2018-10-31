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
@0 = private unnamed_addr constant [32 x i8] c";omp-threadprivate.c;main;8;5;;\00"
@1 = private unnamed_addr constant [32 x i8] c";omp-threadprivate.c;main;8;5;;\00"
@2 = private unnamed_addr constant [32 x i8] c";omp-threadprivate.c;main;9;5;;\00"
@.str = private unnamed_addr constant [27 x i8] c"Initial, var1 = %d, at %p\0A\00", align 1
@3 = private unnamed_addr constant [34 x i8] c";omp-threadprivate.c;main;10;43;;\00"
@4 = private unnamed_addr constant [34 x i8] c";omp-threadprivate.c;main;10;50;;\00"
@.str1 = private unnamed_addr constant [27 x i8] c"Initial, var2 = %d, at %p\0A\00", align 1
@5 = private unnamed_addr constant [34 x i8] c";omp-threadprivate.c;main;11;43;;\00"
@6 = private unnamed_addr constant [34 x i8] c";omp-threadprivate.c;main;11;50;;\00"
@7 = private unnamed_addr constant [44 x i8] c";omp-threadprivate.c;.omp_microtask.;14;9;;\00"
@.str2 = private unnamed_addr constant [33 x i8] c"Thread %d, var1 = %d, var2 = %d\0A\00", align 1
@8 = private unnamed_addr constant [45 x i8] c";omp-threadprivate.c;.omp_microtask.;16;75;;\00"
@9 = private unnamed_addr constant [45 x i8] c";omp-threadprivate.c;.omp_microtask.;16;81;;\00"
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@10 = private unnamed_addr constant [45 x i8] c";omp-threadprivate.c;.omp_microtask.;12;21;;\00"
@11 = private unnamed_addr constant [33 x i8] c";omp-threadprivate.c;main;12;9;;\00"
@.str3 = private unnamed_addr constant [25 x i8] c"Final, var1 = %d, at %p\0A\00", align 1
@12 = private unnamed_addr constant [34 x i8] c";omp-threadprivate.c;main;18;41;;\00"
@13 = private unnamed_addr constant [34 x i8] c";omp-threadprivate.c;main;18;48;;\00"
@.str4 = private unnamed_addr constant [25 x i8] c"Final, var2 = %d, at %p\0A\00", align 1
@14 = private unnamed_addr constant [34 x i8] c";omp-threadprivate.c;main;19;41;;\00"
@15 = private unnamed_addr constant [34 x i8] c";omp-threadprivate.c;main;19;48;;\00"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %.__kmpc_global_thread_num. = alloca i32, align 4
  %2 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([32 x i8]* @1, i32 0, i32 0), i8** %2
  %3 = call i32 @__kmpc_global_thread_num({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2.)
  store i32 %3, i32* %.__kmpc_global_thread_num.
  %agg.captured = alloca %struct.anon, align 1
  store i32 0, i32* %retval
  %4 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([32 x i8]* @0, i32 0, i32 0), i8** %4
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  %5 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.)
  %6 = bitcast i8* %5 to i32*
  store i32 -1, i32* %6, align 4
  %7 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !20
  store i8* getelementptr inbounds ([32 x i8]* @2, i32 0, i32 0), i8** %7, !dbg !20
  %.gtid.1 = load i32* %.__kmpc_global_thread_num., !dbg !20
  %8 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.1, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.), !dbg !20
  %9 = bitcast i8* %8 to i32*, !dbg !20
  store i32 -2, i32* %9, align 4, !dbg !20
  %10 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !21
  store i8* getelementptr inbounds ([34 x i8]* @3, i32 0, i32 0), i8** %10, !dbg !21
  %.gtid.2 = load i32* %.__kmpc_global_thread_num., !dbg !21
  %11 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.2, i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.), !dbg !21
  %12 = bitcast i8* %11 to i32*, !dbg !21
  %13 = load i32* %12, align 4, !dbg !21
  %14 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !21
  store i8* getelementptr inbounds ([34 x i8]* @4, i32 0, i32 0), i8** %14, !dbg !21
  %.gtid.3 = load i32* %.__kmpc_global_thread_num., !dbg !21
  %15 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.3, i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.), !dbg !21
  %16 = bitcast i8* %15 to i32*, !dbg !21
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([27 x i8]* @.str, i32 0, i32 0), i32 %13, i32* %16), !dbg !21
  %17 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !22
  store i8* getelementptr inbounds ([34 x i8]* @5, i32 0, i32 0), i8** %17, !dbg !22
  %.gtid.4 = load i32* %.__kmpc_global_thread_num., !dbg !22
  %18 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.), !dbg !22
  %19 = bitcast i8* %18 to i32*, !dbg !22
  %20 = load i32* %19, align 4, !dbg !22
  %21 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !22
  store i8* getelementptr inbounds ([34 x i8]* @6, i32 0, i32 0), i8** %21, !dbg !22
  %.gtid.5 = load i32* %.__kmpc_global_thread_num., !dbg !22
  %22 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.5, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.), !dbg !22
  %23 = bitcast i8* %22 to i32*, !dbg !22
  %call6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([27 x i8]* @.str1, i32 0, i32 0), i32 %20, i32* %23), !dbg !22
  %24 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !23
  store i8* getelementptr inbounds ([33 x i8]* @11, i32 0, i32 0), i8** %24, !dbg !23
  %25 = bitcast %struct.anon* %agg.captured to i8*, !dbg !23
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %25), !dbg !23
  %26 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !24
  store i8* getelementptr inbounds ([34 x i8]* @12, i32 0, i32 0), i8** %26, !dbg !24
  %.gtid.7 = load i32* %.__kmpc_global_thread_num., !dbg !24
  %27 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.7, i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.), !dbg !24
  %28 = bitcast i8* %27 to i32*, !dbg !24
  %29 = load i32* %28, align 4, !dbg !24
  %30 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !24
  store i8* getelementptr inbounds ([34 x i8]* @13, i32 0, i32 0), i8** %30, !dbg !24
  %.gtid.8 = load i32* %.__kmpc_global_thread_num., !dbg !24
  %31 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.8, i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.), !dbg !24
  %32 = bitcast i8* %31 to i32*, !dbg !24
  %call9 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @.str3, i32 0, i32 0), i32 %29, i32* %32), !dbg !24
  %33 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !25
  store i8* getelementptr inbounds ([34 x i8]* @14, i32 0, i32 0), i8** %33, !dbg !25
  %.gtid.10 = load i32* %.__kmpc_global_thread_num., !dbg !25
  %34 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.10, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.), !dbg !25
  %35 = bitcast i8* %34 to i32*, !dbg !25
  %36 = load i32* %35, align 4, !dbg !25
  %37 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !25
  store i8* getelementptr inbounds ([34 x i8]* @15, i32 0, i32 0), i8** %37, !dbg !25
  %.gtid.11 = load i32* %.__kmpc_global_thread_num., !dbg !25
  %38 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.11, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.), !dbg !25
  %39 = bitcast i8* %38 to i32*, !dbg !25
  %call12 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @.str4, i32 0, i32 0), i32 %36, i32* %39), !dbg !25
  ret i32 0, !dbg !26
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
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !27), !dbg !28
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !29), !dbg !28
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !30), !dbg !28
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !28
  %arg3 = load i8** %.addr2, !dbg !28
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*, !dbg !28
  %call = call i32 @omp_get_thread_num(), !dbg !31
  %7 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([44 x i8]* @7, i32 0, i32 0), i8** %7
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  %8 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.)
  %9 = bitcast i8* %8 to i32*
  store i32 %call, i32* %9, align 4
  %call3 = call i32 @omp_get_thread_num(), !dbg !33
  %10 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !34
  store i8* getelementptr inbounds ([45 x i8]* @8, i32 0, i32 0), i8** %10, !dbg !34
  %.gtid.4 = load i32* %.__kmpc_global_thread_num., !dbg !34
  %11 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4, i8* bitcast (i32* @var1 to i8*), i64 4, i8*** @var1.cache.), !dbg !34
  %12 = bitcast i8* %11 to i32*, !dbg !34
  %13 = load i32* %12, align 4, !dbg !34
  %14 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !34
  store i8* getelementptr inbounds ([45 x i8]* @9, i32 0, i32 0), i8** %14, !dbg !34
  %.gtid.5 = load i32* %.__kmpc_global_thread_num., !dbg !34
  %15 = call i8* @__kmpc_threadprivate_cached({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.5, i8* bitcast (i32* @var2 to i8*), i64 4, i8*** @var2.cache.), !dbg !34
  %16 = bitcast i8* %15 to i32*, !dbg !34
  %17 = load i32* %16, align 4, !dbg !34
  %call6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([33 x i8]* @.str2, i32 0, i32 0), i32 %call3, i32 %13, i32 %17), !dbg !34
  %18 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([45 x i8]* @10, i32 0, i32 0), i8** %18
  %.gtid.7 = load i32* %.__kmpc_global_thread_num.
  %19 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.7)
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %entry
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %entry
  ret void, !dbg !35
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata) #3

declare i32 @omp_get_thread_num() #2

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!17, !18}
!llvm.ident = !{!19}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !14, metadata !2, metadata !"", i32 1} ; [ DW_TAG_compile_unit ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-threadprivate.c] [DW_LANG_C99]
!1 = metadata !{metadata !"omp-threadprivate.c", metadata !"/home/jeremy/code/research/hpxMP/omp-tests"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !9}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"main", metadata !"main", metadata !"", i32 7, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 ()* @main, null, null, metadata !2, i32 7} ; [ DW_TAG_subprogram ] [line 7] [def] [main]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-threadprivate.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{metadata !8}
!8 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!9 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 12, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask., null, null, metadata !2, i32 12} ; [ DW_TAG_subprogram ] [line 12] [local] [def] [.omp_microtask.]
!10 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{null, metadata !12, metadata !12, metadata !13}
!12 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !8} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from int]
!13 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!14 = metadata !{metadata !15, metadata !16}
!15 = metadata !{i32 786484, i32 0, null, metadata !"var1", metadata !"var1", metadata !"", metadata !5, i32 4, metadata !8, i32 0, i32 1, i32* @var1, null} ; [ DW_TAG_variable ] [var1] [line 4] [def]
!16 = metadata !{i32 786484, i32 0, null, metadata !"var2", metadata !"var2", metadata !"", metadata !5, i32 4, metadata !8, i32 0, i32 1, i32* @var2, null} ; [ DW_TAG_variable ] [var2] [line 4] [def]
!17 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!18 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!19 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
!20 = metadata !{i32 9, i32 5, metadata !4, null}
!21 = metadata !{i32 10, i32 5, metadata !4, null}
!22 = metadata !{i32 11, i32 5, metadata !4, null}
!23 = metadata !{i32 12, i32 9, metadata !4, null}
!24 = metadata !{i32 18, i32 5, metadata !4, null}
!25 = metadata !{i32 19, i32 5, metadata !4, null}
!26 = metadata !{i32 20, i32 5, metadata !4, null}
!27 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 16777228, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 12]
!28 = metadata !{i32 12, i32 9, metadata !9, null}
!29 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 33554444, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 12]
!30 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 50331660, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 12]
!31 = metadata !{i32 14, i32 16, metadata !32, null}
!32 = metadata !{i32 786443, metadata !1, metadata !9, i32 13, i32 5, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-threadprivate.c]
!33 = metadata !{i32 16, i32 53, metadata !32, null}
!34 = metadata !{i32 16, i32 9, metadata !32, null}
!35 = metadata !{i32 17, i32 5, metadata !9, null}
