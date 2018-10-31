; ModuleID = 'omp-simple-task.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32*, i32* }
%struct.anon.0 = type { i32*, i32* }
%struct..omp.task.priv. = type { i32 }
%struct.__kmp_depend_info_t = type { i64, i64, i8 }

@.str = private unnamed_addr constant [20 x i8] c"hello tasks %d, %d\0A\00", align 1
@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@0 = private unnamed_addr constant [41 x i8] c";omp-simple-task.c;.omp_microtask.;7;9;;\00"
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@1 = private unnamed_addr constant [42 x i8] c";omp-simple-task.c;.omp_microtask.;5;21;;\00"
@2 = private unnamed_addr constant [30 x i8] c";omp-simple-task.c;main;5;9;;\00"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %var_i = alloca i32, align 4
  %var_j = alloca i32, align 4
  %agg.captured = alloca %struct.anon, align 8
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 0, i32* %retval
  call void @llvm.dbg.declare(metadata !{i32* %var_i}, metadata !20), !dbg !21
  store i32 0, i32* %var_i, align 4, !dbg !22
  call void @llvm.dbg.declare(metadata !{i32* %var_j}, metadata !23), !dbg !24
  store i32 1, i32* %var_j, align 4, !dbg !22
  %2 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 0, !dbg !25
  store i32* %var_i, i32** %2, align 8, !dbg !25
  %3 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 1, !dbg !25
  store i32* %var_j, i32** %3, align 8, !dbg !25
  %4 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([30 x i8]* @2, i32 0, i32 0), i8** %4
  %5 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %5)
  ret i32 0, !dbg !26
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.(i32*, i32*, i8*) #0 {
entry:
  %.addr = alloca i32*, align 8
  %.addr1 = alloca i32*, align 8
  %.addr2 = alloca i8*, align 8
  %agg.captured = alloca %struct.anon.0, align 8
  %.flags.addr = alloca i32, align 4
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %3 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %4 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %.flags.addr
  store i32* %0, i32** %.addr, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !27), !dbg !28
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !29), !dbg !28
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !30), !dbg !28
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !28
  %arg3 = load i8** %.addr2, !dbg !28
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*, !dbg !28
  %7 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 0, !dbg !28
  %ref = load i32** %7, align 8, !dbg !28
  %8 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 1, !dbg !28
  %ref3 = load i32** %8, align 8, !dbg !28
  %9 = getelementptr inbounds %struct.anon.0* %agg.captured, i32 0, i32 0, !dbg !31
  store i32* %ref, i32** %9, align 8, !dbg !31
  %10 = getelementptr inbounds %struct.anon.0* %agg.captured, i32 0, i32 1, !dbg !31
  store i32* %ref3, i32** %10, align 8, !dbg !31
  %11 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([41 x i8]* @0, i32 0, i32 0), i8** %11
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  %.flags. = load i32* %.flags.addr
  %.task_t.val.addr = call { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* @__kmpc_omp_task_alloc({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 %.flags., i64 add (i64 ptrtoint ({ i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* getelementptr ({ i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* null, i32 1) to i64), i64 4), i64 16, i32 (i32, i8*)* @.omp_ptask.)
  %.shared.addr = getelementptr inbounds { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr, i32 0, i32 0
  %12 = load i8** %.shared.addr
  %13 = bitcast %struct.anon.0* %agg.captured to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %12, i8* %13, i64 16, i32 8, i1 false)
  %14 = getelementptr { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr, i32 1
  %15 = bitcast { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %14 to %struct..omp.task.priv.*
  %var_j = getelementptr inbounds %struct..omp.task.priv.* %15, i32 0, i32 0
  %16 = load i32* %ref3, align 4
  store i32 %16, i32* %var_j
  %.task.res. = call i32 @__kmpc_omp_task_with_deps({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.task_t.val.addr, i32 0, %struct.__kmp_depend_info_t* null, i32 0, %struct.__kmp_depend_info_t* null)
  %17 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([42 x i8]* @1, i32 0, i32 0), i8** %17
  %.gtid.4 = load i32* %.__kmpc_global_thread_num.
  %18 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.4)
  %19 = icmp ne i32 %18, 0
  br i1 %19, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %entry
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %entry
  ret void, !dbg !33
}

; Function Attrs: nounwind uwtable
define internal i32 @.omp_ptask.(i32, i8*) #0 {
entry:
  %retval = alloca i32, align 4
  %.addr = alloca i32, align 4
  %.addr1 = alloca i8*, align 8
  %.__kmpc_global_thread_num. = alloca i32, align 4
  store i32 %0, i32* %.addr, align 4
  call void @llvm.dbg.declare(metadata !{i32* %.addr}, metadata !34), !dbg !35
  store i8* %1, i8** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr1}, metadata !36), !dbg !35
  %2 = load i32* %.addr, !dbg !35
  store i32 %2, i32* %.__kmpc_global_thread_num., align 4, !dbg !35
  %3 = bitcast i8** %.addr1 to { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }**, !dbg !35
  %.arg2.shareds = load { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }** %3, !dbg !35
  %.arg2.shareds.addr = getelementptr inbounds { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %.arg2.shareds, i32 0, i32 0, !dbg !35
  %.arg2.shareds. = load i8** %.arg2.shareds.addr, !dbg !35
  %"(anon)shared" = bitcast i8* %.arg2.shareds. to %struct.anon.0*, !dbg !35
  %4 = load { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }** %3, !dbg !35
  %5 = getelementptr { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %4, i32 1, !dbg !35
  %6 = getelementptr inbounds %struct.anon.0* %"(anon)shared", i32 0, i32 0, !dbg !35
  %ref = load i32** %6, align 8, !dbg !35
  %7 = getelementptr inbounds %struct.anon.0* %"(anon)shared", i32 0, i32 1, !dbg !35
  %ref2 = load i32** %7, align 8, !dbg !35
  %8 = bitcast { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* %5 to %struct..omp.task.priv.*, !dbg !35
  %var_j = getelementptr inbounds %struct..omp.task.priv.* %8, i32 0, i32 0, !dbg !35
  %9 = load i32* %ref, align 4, !dbg !37
  %10 = load i32* %var_j, align 4, !dbg !37
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([20 x i8]* @.str, i32 0, i32 0), i32 %9, i32 %10), !dbg !37
  %11 = load i32* %retval, !dbg !39
  ret i32 %11, !dbg !39
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

declare { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }* @__kmpc_omp_task_alloc({ i32, i32, i32, i32, i8* }*, i32, i32, i64, i64, i32 (i32, i8*)*)

declare i32 @__kmpc_omp_task_with_deps({ i32, i32, i32, i32, i8* }*, i32, { i8*, i32 (i32, i8*)*, i32, i32 (i32, i8*)*, i32 }*, i32, %struct.__kmp_depend_info_t*, i32, %struct.__kmp_depend_info_t*)

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!17, !18}
!llvm.ident = !{!19}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 1} ; [ DW_TAG_compile_unit ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-simple-task.c] [DW_LANG_C99]
!1 = metadata !{metadata !"omp-simple-task.c", metadata !"/home/jeremy/code/research/hpxMP/omp-tests"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !9, metadata !14}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"main", metadata !"main", metadata !"", i32 3, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 ()* @main, null, null, metadata !2, i32 3} ; [ DW_TAG_subprogram ] [line 3] [def] [main]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-simple-task.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{metadata !8}
!8 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!9 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 5, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask., null, null, metadata !2, i32 5} ; [ DW_TAG_subprogram ] [line 5] [local] [def] [.omp_microtask.]
!10 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{null, metadata !12, metadata !12, metadata !13}
!12 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !8} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from int]
!13 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!14 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_ptask.", metadata !".omp_ptask.", metadata !"", i32 7, metadata !15, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 (i32, i8*)* @.omp_ptask., null, null, metadata !2, i32 7} ; [ DW_TAG_subprogram ] [line 7] [local] [def] [.omp_ptask.]
!15 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !16, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!16 = metadata !{metadata !8, metadata !8, metadata !13}
!17 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!18 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!19 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
!20 = metadata !{i32 786688, metadata !4, metadata !"var_i", metadata !5, i32 4, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [var_i] [line 4]
!21 = metadata !{i32 4, i32 9, metadata !4, null}
!22 = metadata !{i32 4, i32 5, metadata !4, null}
!23 = metadata !{i32 786688, metadata !4, metadata !"var_j", metadata !5, i32 4, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [var_j] [line 4]
!24 = metadata !{i32 4, i32 20, metadata !4, null}
!25 = metadata !{i32 5, i32 9, metadata !4, null}
!26 = metadata !{i32 12, i32 5, metadata !4, null}
!27 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 16777221, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 5]
!28 = metadata !{i32 5, i32 9, metadata !9, null}
!29 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 33554437, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 5]
!30 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 50331653, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 5]
!31 = metadata !{i32 7, i32 9, metadata !32, null}
!32 = metadata !{i32 786443, metadata !1, metadata !9, i32 6, i32 5, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-simple-task.c]
!33 = metadata !{i32 11, i32 5, metadata !9, null}
!34 = metadata !{i32 786689, metadata !14, metadata !"", metadata !5, i32 16777223, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 7]
!35 = metadata !{i32 7, i32 9, metadata !14, null}
!36 = metadata !{i32 786689, metadata !14, metadata !"", metadata !5, i32 33554439, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 7]
!37 = metadata !{i32 9, i32 13, metadata !38, null}
!38 = metadata !{i32 786443, metadata !1, metadata !14, i32 8, i32 9, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-simple-task.c]
!39 = metadata !{i32 10, i32 9, metadata !14, null}
