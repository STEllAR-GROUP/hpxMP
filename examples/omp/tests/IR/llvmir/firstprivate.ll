; ModuleID = 'test_omp_for_firstprivate.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32* }

@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@0 = private unnamed_addr constant [52 x i8] c";test_omp_for_firstprivate.c;.omp_microtask.;13;9;;\00"
@.str = private unnamed_addr constant [23 x i8] c"sum0 (%d) = %d, at %p\0A\00", align 1
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@1 = private unnamed_addr constant [53 x i8] c";test_omp_for_firstprivate.c;.omp_microtask.;13;35;;\00"
@.str1 = private unnamed_addr constant [17 x i8] c"sum0 = %d at %p\0A\00", align 1
@2 = private unnamed_addr constant [52 x i8] c";test_omp_for_firstprivate.c;.omp_microtask.;9;21;;\00"
@3 = private unnamed_addr constant [51 x i8] c";test_omp_for_firstprivate.c;.omp_microtask.;9;9;;\00"
@4 = private unnamed_addr constant [61 x i8] c";test_omp_for_firstprivate.c;test_omp_for_firstprivate;9;9;;\00"
@.str2 = private unnamed_addr constant [20 x i8] c"final sum0 = %d %p\0A\00", align 1

; Function Attrs: nounwind uwtable
define void @test_omp_for_firstprivate() #0 {
entry:
  %sum0 = alloca i32, align 4
  %agg.captured = alloca %struct.anon, align 8
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  call void @llvm.dbg.declare(metadata !{i32* %sum0}, metadata !20), !dbg !21
  store i32 10, i32* %sum0, align 4, !dbg !22
  %2 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 0, !dbg !23
  store i32* %sum0, i32** %2, align 8, !dbg !23
  %3 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([61 x i8]* @4, i32 0, i32 0), i8** %3
  %4 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %4)
  %5 = load i32* %sum0, align 4, !dbg !24
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([20 x i8]* @.str2, i32 0, i32 0), i32 %5, i32* %sum0), !dbg !24
  ret void, !dbg !25
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.(i32*, i32*, i8*) #0 {
entry:
  %.addr = alloca i32*, align 8
  %.addr1 = alloca i32*, align 8
  %.addr2 = alloca i8*, align 8
  %i = alloca i32, align 4
  %sum0 = alloca i32, align 4
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
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !26), !dbg !27
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !28), !dbg !27
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !29), !dbg !27
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !27
  %arg3 = load i8** %.addr2, !dbg !27
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*, !dbg !27
  %7 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 0, !dbg !27
  %ref = load i32** %7, align 8, !dbg !27
  %call = call i32 @omp_get_thread_num(), !dbg !30
  %8 = load i32* %ref, align 4, !dbg !30
  %add = add nsw i32 %8, %call, !dbg !30
  store i32 %add, i32* %ref, align 4, !dbg !30
  call void @llvm.dbg.declare(metadata !{i32* %i}, metadata !32), !dbg !33
  call void @llvm.dbg.declare(metadata !{i32* %sum0}, metadata !34), !dbg !35
  %9 = load i32* %ref, align 4, !dbg !36
  store i32 %9, i32* %sum0, !dbg !36
  %10 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([51 x i8]* @3, i32 0, i32 0), i8** %10
  %.gtid.14 = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.14)
  %11 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([52 x i8]* @0, i32 0, i32 0), i8** %11
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
  store i32 1, i32* %i.private., align 4, !dbg !35
  %17 = load i32* %.idx., align 4, !dbg !35
  %mul = mul nsw i32 %17, 1, !dbg !35
  %18 = load i32* %i.private., align 4, !dbg !35
  %add3 = add nsw i32 %18, %mul, !dbg !35
  store i32 %add3, i32* %i.private., align 4, !dbg !35
  %.idx.4 = load i32* %.idx., !dbg !35
  %19 = load i32* %ub, !dbg !35
  %omp.idx.le.ub = icmp sle i32 %.idx.4, %19, !dbg !35
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini, !dbg !35

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %20 = load i32* %sum0, align 4, !dbg !37
  %add5 = add nsw i32 %20, 1, !dbg !37
  store i32 %add5, i32* %sum0, align 4, !dbg !37
  %call6 = call i32 @omp_get_thread_num(), !dbg !39
  %21 = load i32* %sum0, align 4, !dbg !40
  %call7 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([23 x i8]* @.str, i32 0, i32 0), i32 %call6, i32 %21, i32* %sum0), !dbg !40
  br label %omp.cont.block, !dbg !41

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.8 = load i32* %.idx., !dbg !42
  %.next.idx. = add nsw i32 %.idx.8, 1, !dbg !42
  store i32 %.next.idx., i32* %.idx., !dbg !42
  br label %omp.loop.main, !dbg !42

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end, !dbg !41

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !44
  %22 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([53 x i8]* @1, i32 0, i32 0), i8** %22
  %.gtid.9 = load i32* %.__kmpc_global_thread_num.
  %23 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.9)
  %24 = icmp ne i32 %23, 0
  br i1 %24, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue13

omp.cancel_barrier.continue:                      ; preds = %omp.loop.end
  %25 = load i32* %ref, align 4, !dbg !46
  %call10 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([17 x i8]* @.str1, i32 0, i32 0), i32 %25, i32* %ref), !dbg !46
  %26 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4, !dbg !47
  store i8* getelementptr inbounds ([52 x i8]* @2, i32 0, i32 0), i8** %26, !dbg !47
  %.gtid.11 = load i32* %.__kmpc_global_thread_num., !dbg !47
  %27 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.11), !dbg !47
  %28 = icmp ne i32 %27, 0, !dbg !47
  br i1 %28, label %omp.cancel_barrier.exit12, label %omp.cancel_barrier.continue13, !dbg !47

omp.cancel_barrier.exit12:                        ; preds = %omp.cancel_barrier.continue
  br label %omp.cancel_barrier.continue13, !dbg !48

omp.cancel_barrier.continue13:                    ; preds = %omp.cancel_barrier.exit, %omp.cancel_barrier.exit12, %omp.cancel_barrier.continue
  ret void, !dbg !50
}

declare i32 @omp_get_thread_num() #2

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

declare void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }*, i32, i32, i32*, i32*, i32*, i32*, i32, i32)

declare i32 @printf(i8*, ...) #2

declare void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval
  call void @test_omp_for_firstprivate(), !dbg !53
  ret i32 0, !dbg !54
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!17, !18}
!llvm.ident = !{!19}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 1} ; [ DW_TAG_compile_unit ] [/home/jeremy/code/research/hpxMP/omp-tests/test_omp_for_firstprivate.c] [DW_LANG_C99]
!1 = metadata !{metadata !"test_omp_for_firstprivate.c", metadata !"/home/jeremy/code/research/hpxMP/omp-tests"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !8, metadata !14}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"test_omp_for_firstprivate", metadata !"test_omp_for_firstprivate", metadata !"", i32 6, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @test_omp_for_firstprivate, null, null, metadata !2, i32 6} ; [ DW_TAG_subprogram ] [line 6] [def] [test_omp_for_firstprivate]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/jeremy/code/research/hpxMP/omp-tests/test_omp_for_firstprivate.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{null}
!8 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 9, metadata !9, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask., null, null, metadata !2, i32 9} ; [ DW_TAG_subprogram ] [line 9] [local] [def] [.omp_microtask.]
!9 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !10, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!10 = metadata !{null, metadata !11, metadata !11, metadata !13}
!11 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !12} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from int]
!12 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!13 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!14 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"main", metadata !"main", metadata !"", i32 23, metadata !15, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 ()* @main, null, null, metadata !2, i32 24} ; [ DW_TAG_subprogram ] [line 23] [def] [scope 24] [main]
!15 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !16, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!16 = metadata !{metadata !12}
!17 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!18 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!19 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
!20 = metadata !{i32 786688, metadata !4, metadata !"sum0", metadata !5, i32 7, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [sum0] [line 7]
!21 = metadata !{i32 7, i32 9, metadata !4, null}
!22 = metadata !{i32 7, i32 5, metadata !4, null}
!23 = metadata !{i32 9, i32 9, metadata !4, null}
!24 = metadata !{i32 20, i32 5, metadata !4, null}
!25 = metadata !{i32 21, i32 1, metadata !4, null}
!26 = metadata !{i32 786689, metadata !8, metadata !"", metadata !5, i32 16777225, metadata !11, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 9]
!27 = metadata !{i32 9, i32 9, metadata !8, null}
!28 = metadata !{i32 786689, metadata !8, metadata !"", metadata !5, i32 33554441, metadata !11, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 9]
!29 = metadata !{i32 786689, metadata !8, metadata !"", metadata !5, i32 50331657, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 9]
!30 = metadata !{i32 11, i32 17, metadata !31, null}
!31 = metadata !{i32 786443, metadata !1, metadata !8, i32 10, i32 5, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/test_omp_for_firstprivate.c]
!32 = metadata !{i32 786688, metadata !31, metadata !"i", metadata !5, i32 12, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [i] [line 12]
!33 = metadata !{i32 12, i32 13, metadata !31, null}
!34 = metadata !{i32 786688, metadata !31, metadata !"sum0", metadata !5, i32 7, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [sum0] [line 7]
!35 = metadata !{i32 7, i32 9, metadata !31, null}
!36 = metadata !{i32 13, i32 9, metadata !31, null}
!37 = metadata !{i32 15, i32 13, metadata !38, null}
!38 = metadata !{i32 786443, metadata !1, metadata !31, i32 14, i32 33, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/test_omp_for_firstprivate.c]
!39 = metadata !{i32 16, i32 47, metadata !38, null}
!40 = metadata !{i32 16, i32 13, metadata !38, null}
!41 = metadata !{i32 17, i32 9, metadata !38, null}
!42 = metadata !{i32 17, i32 9, metadata !43, null}
!43 = metadata !{i32 786443, metadata !1, metadata !38, i32 17, i32 9, i32 1, i32 2} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/test_omp_for_firstprivate.c]
!44 = metadata !{i32 17, i32 9, metadata !45, null}
!45 = metadata !{i32 786443, metadata !1, metadata !38, i32 17, i32 9, i32 2, i32 3} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/test_omp_for_firstprivate.c]
!46 = metadata !{i32 18, i32 9, metadata !31, null}
!47 = metadata !{i32 19, i32 5, metadata !31, null}
!48 = metadata !{i32 19, i32 5, metadata !49, null}
!49 = metadata !{i32 786443, metadata !1, metadata !31, i32 19, i32 5, i32 1, i32 4} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/test_omp_for_firstprivate.c]
!50 = metadata !{i32 19, i32 5, metadata !51, null}
!51 = metadata !{i32 786443, metadata !1, metadata !52, i32 19, i32 5, i32 3, i32 6} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/test_omp_for_firstprivate.c]
!52 = metadata !{i32 786443, metadata !1, metadata !8, i32 19, i32 5, i32 2, i32 5} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/test_omp_for_firstprivate.c]
!53 = metadata !{i32 26, i32 5, metadata !14, null}
!54 = metadata !{i32 28, i32 5, metadata !14, null}
