; ModuleID = 'omp-crit.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32* }

@.str = private unnamed_addr constant [8 x i8] c"x = %d\0A\00", align 1
@.gomp_critical_user_.var = common global [8 x i32] zeroinitializer
@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@0 = private unnamed_addr constant [35 x i8] c";omp-crit.c;.omp_microtask.;11;9;;\00"
@.str1 = private unnamed_addr constant [9 x i8] c"\09x = %d\0A\00", align 1
@1 = private unnamed_addr constant [35 x i8] c";omp-crit.c;.omp_microtask.;14;9;;\00"
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@2 = private unnamed_addr constant [35 x i8] c";omp-crit.c;.omp_microtask.;7;21;;\00"
@3 = private unnamed_addr constant [23 x i8] c";omp-crit.c;main;7;9;;\00"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  %agg.captured = alloca %struct.anon, align 8
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 0, i32* %retval
  call void @llvm.dbg.declare(metadata !{i32* %x}, metadata !17), !dbg !18
  store i32 0, i32* %x, align 4, !dbg !19
  %2 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 0, !dbg !20
  store i32* %x, i32** %2, align 8, !dbg !20
  %3 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([23 x i8]* @3, i32 0, i32 0), i8** %3
  %4 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %4)
  ret i32 0, !dbg !21
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
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32* %0, i32** %.addr, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !22), !dbg !23
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !24), !dbg !23
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !25), !dbg !23
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !23
  %arg3 = load i8** %.addr2, !dbg !23
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*, !dbg !23
  %7 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 0, !dbg !23
  %ref = load i32** %7, align 8, !dbg !23
  store i32 3, i32* %ref, align 4, !dbg !26
  %8 = load i32* %ref, align 4, !dbg !28
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([8 x i8]* @.str, i32 0, i32 0), i32 %8), !dbg !28
  %9 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([35 x i8]* @0, i32 0, i32 0), i8** %9
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_critical({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., [8 x i32]* @.gomp_critical_user_.var)
  store i32 42, i32* %ref, align 4, !dbg !29
  call void @__kmpc_end_critical({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., [8 x i32]* @.gomp_critical_user_.var), !dbg !29
  %10 = load i32* %ref, align 4, !dbg !30
  %call3 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([9 x i8]* @.str1, i32 0, i32 0), i32 %10), !dbg !30
  %11 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !31
  store i8* getelementptr inbounds ([35 x i8]* @1, i32 0, i32 0), i8** %11, !dbg !31
  %.gtid.4 = load i32* %.__kmpc_global_thread_num., !dbg !31
  call void @__kmpc_critical({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4, [8 x i32]* @.gomp_critical_user_.var), !dbg !31
  store i32 43, i32* %ref, align 4, !dbg !32
  call void @__kmpc_end_critical({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.4, [8 x i32]* @.gomp_critical_user_.var), !dbg !32
  %12 = load i32* %ref, align 4, !dbg !33
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([9 x i8]* @.str1, i32 0, i32 0), i32 %12), !dbg !33
  %13 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([35 x i8]* @2, i32 0, i32 0), i8** %13
  %.gtid.6 = load i32* %.__kmpc_global_thread_num.
  %14 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.6)
  %15 = icmp ne i32 %14, 0
  br i1 %15, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %entry
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %entry
  ret void, !dbg !34
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

declare void @__kmpc_critical({ i32, i32, i32, i32, i8* }*, i32, [8 x i32]*)

declare void @__kmpc_end_critical({ i32, i32, i32, i32, i8* }*, i32, [8 x i32]*)

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!14, !15}
!llvm.ident = !{!16}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 1} ; [ DW_TAG_compile_unit ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-crit.c] [DW_LANG_C99]
!1 = metadata !{metadata !"omp-crit.c", metadata !"/home/jeremy/code/research/hpxMP/omp-tests"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !9}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"main", metadata !"main", metadata !"", i32 4, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 ()* @main, null, null, metadata !2, i32 4} ; [ DW_TAG_subprogram ] [line 4] [def] [main]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-crit.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{metadata !8}
!8 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!9 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 7, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask., null, null, metadata !2, i32 7} ; [ DW_TAG_subprogram ] [line 7] [local] [def] [.omp_microtask.]
!10 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{null, metadata !12, metadata !12, metadata !13}
!12 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !8} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from int]
!13 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!14 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!15 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!16 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
!17 = metadata !{i32 786688, metadata !4, metadata !"x", metadata !5, i32 5, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [x] [line 5]
!18 = metadata !{i32 5, i32 9, metadata !4, null}
!19 = metadata !{i32 5, i32 5, metadata !4, null}
!20 = metadata !{i32 7, i32 9, metadata !4, null}
!21 = metadata !{i32 18, i32 5, metadata !4, null}
!22 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 16777223, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 7]
!23 = metadata !{i32 7, i32 9, metadata !9, null}
!24 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 33554439, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 7]
!25 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 50331655, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 7]
!26 = metadata !{i32 9, i32 9, metadata !27, null}
!27 = metadata !{i32 786443, metadata !1, metadata !9, i32 8, i32 5, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-crit.c]
!28 = metadata !{i32 10, i32 9, metadata !27, null}
!29 = metadata !{i32 12, i32 9, metadata !27, null}
!30 = metadata !{i32 13, i32 9, metadata !27, null}
!31 = metadata !{i32 14, i32 9, metadata !27, null}
!32 = metadata !{i32 15, i32 9, metadata !27, null}
!33 = metadata !{i32 16, i32 9, metadata !27, null}
!34 = metadata !{i32 17, i32 5, metadata !9, null}
