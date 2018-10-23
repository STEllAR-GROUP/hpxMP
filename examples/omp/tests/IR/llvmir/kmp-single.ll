; ModuleID = 'omp-single.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type {}

@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@0 = private unnamed_addr constant [36 x i8] c";omp-single.c;.omp_microtask.;6;9;;\00"
@.str = private unnamed_addr constant [12 x i8] c"one thread\0A\00", align 1
@1 = private unnamed_addr constant [36 x i8] c";omp-single.c;.omp_microtask.;6;9;;\00"
@.omp.default.loc.320. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 320, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@2 = private unnamed_addr constant [37 x i8] c";omp-single.c;.omp_microtask.;6;20;;\00"
@.str1 = private unnamed_addr constant [13 x i8] c"all threads\0A\00", align 1
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@3 = private unnamed_addr constant [37 x i8] c";omp-single.c;.omp_microtask.;4;21;;\00"
@4 = private unnamed_addr constant [25 x i8] c";omp-single.c;main;4;9;;\00"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %agg.captured = alloca %struct.anon, align 1
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 0, i32* %retval
  %2 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([25 x i8]* @4, i32 0, i32 0), i8** %2
  %3 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %3)
  ret i32 0, !dbg !17
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
  %.__kmpc_ident_t.320. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.320. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.320. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %7 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %8 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %7, i8* %8, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 0, i32* %.did_it.
  store i32* %0, i32** %.addr, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !18), !dbg !19
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !20), !dbg !19
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !21), !dbg !19
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !19
  %arg3 = load i8** %.addr2, !dbg !19
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*, !dbg !19
  store i32 0, i32* %.did_it., align 4, !dbg !22
  %9 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([36 x i8]* @0, i32 0, i32 0), i8** %9
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  %10 = call i32 @__kmpc_single({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.)
  %tobool = icmp ne i32 %10, 0
  br i1 %tobool, label %omp.single.then, label %omp.single.end

omp.single.then:                                  ; preds = %entry
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([12 x i8]* @.str, i32 0, i32 0)), !dbg !24
  store i32 1, i32* %.did_it., align 4, !dbg !24
  %11 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !24
  store i8* getelementptr inbounds ([36 x i8]* @1, i32 0, i32 0), i8** %11, !dbg !24
  %.gtid.3 = load i32* %.__kmpc_global_thread_num., !dbg !24
  call void @__kmpc_end_single({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.3), !dbg !24
  br label %omp.single.end, !dbg !24

omp.single.end:                                   ; preds = %omp.single.then, %entry
  %12 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.320., i32 0, i32 4
  store i8* getelementptr inbounds ([37 x i8]* @2, i32 0, i32 0), i8** %12
  %.gtid.4 = load i32* %.__kmpc_global_thread_num.
  %13 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.320., i32 %.gtid.4)
  %14 = icmp ne i32 %13, 0
  br i1 %14, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.single.end
  br label %omp.cancel_barrier.continue8

omp.cancel_barrier.continue:                      ; preds = %omp.single.end
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([13 x i8]* @.str1, i32 0, i32 0)), !dbg !25
  %15 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([37 x i8]* @3, i32 0, i32 0), i8** %15
  %.gtid.6 = load i32* %.__kmpc_global_thread_num.
  %16 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.6)
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %omp.cancel_barrier.exit7, label %omp.cancel_barrier.continue8

omp.cancel_barrier.exit7:                         ; preds = %omp.cancel_barrier.continue
  br label %omp.cancel_barrier.continue8

omp.cancel_barrier.continue8:                     ; preds = %omp.cancel_barrier.exit, %omp.cancel_barrier.exit7, %omp.cancel_barrier.continue
  ret void, !dbg !26
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata) #1

declare void @__kmpc_end_single({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_single({ i32, i32, i32, i32, i8* }*, i32)

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

declare i32 @printf(i8*, ...) #3

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }
attributes #3 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!14, !15}
!llvm.ident = !{!16}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 1} ; [ DW_TAG_compile_unit ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-single.c] [DW_LANG_C99]
!1 = metadata !{metadata !"omp-single.c", metadata !"/home/jeremy/code/research/hpxMP/omp-tests"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !9}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"main", metadata !"main", metadata !"", i32 3, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 ()* @main, null, null, metadata !2, i32 3} ; [ DW_TAG_subprogram ] [line 3] [def] [main]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-single.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{metadata !8}
!8 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!9 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 4, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask., null, null, metadata !2, i32 4} ; [ DW_TAG_subprogram ] [line 4] [local] [def] [.omp_microtask.]
!10 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{null, metadata !12, metadata !12, metadata !13}
!12 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !8} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from int]
!13 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!14 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!15 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!16 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
!17 = metadata !{i32 10, i32 5, metadata !4, null}
!18 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 16777220, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 4]
!19 = metadata !{i32 4, i32 9, metadata !9, null}
!20 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 33554436, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 4]
!21 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 50331652, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 4]
!22 = metadata !{i32 6, i32 9, metadata !23, null}
!23 = metadata !{i32 786443, metadata !1, metadata !9, i32 5, i32 5, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-single.c]
!24 = metadata !{i32 7, i32 9, metadata !23, null}
!25 = metadata !{i32 8, i32 9, metadata !23, null} ; [ DW_TAG_imported_declaration ]
!26 = metadata !{i32 9, i32 5, metadata !9, null}
