; ModuleID = 'omp-sections.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type {}

@.str = private unnamed_addr constant [29 x i8] c"entered the parallel region\0A\00", align 1
@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@0 = private unnamed_addr constant [39 x i8] c";omp-sections.c;.omp_microtask.;10;9;;\00"
@.str1 = private unnamed_addr constant [29 x i8] c"entered the sections region\0A\00", align 1
@.str2 = private unnamed_addr constant [25 x i8] c"section 1, by thread %d\0A\00", align 1
@.str3 = private unnamed_addr constant [25 x i8] c"section 2, by thread %d\0A\00", align 1
@.str4 = private unnamed_addr constant [25 x i8] c"section 3, by thread %d\0A\00", align 1
@.str5 = private unnamed_addr constant [25 x i8] c"section 4, by thread %d\0A\00", align 1
@.str6 = private unnamed_addr constant [25 x i8] c"section 5, by thread %d\0A\00", align 1
@.omp.default.loc.192. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 192, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@1 = private unnamed_addr constant [40 x i8] c";omp-sections.c;.omp_microtask.;10;21;;\00"
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@2 = private unnamed_addr constant [39 x i8] c";omp-sections.c;.omp_microtask.;7;21;;\00"
@3 = private unnamed_addr constant [27 x i8] c";omp-sections.c;main;7;9;;\00"

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %x = alloca i32, align 4
  %agg.captured = alloca %struct.anon, align 1
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 0, i32* %retval
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata !{i32* %argc.addr}, metadata !20), !dbg !21
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata !{i8*** %argv.addr}, metadata !22), !dbg !23
  call void @llvm.dbg.declare(metadata !{i32* %x}, metadata !24), !dbg !25
  store i32 0, i32* %x, align 4, !dbg !26
  %2 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([27 x i8]* @3, i32 0, i32 0), i8** %2
  %3 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %3)
  ret i32 0, !dbg !27
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
  %.idx.addr = alloca i32, align 4
  %last = alloca i32, align 4
  %lb = alloca i32, align 4
  %ub = alloca i32, align 4
  %st = alloca i32, align 4
  %.__kmpc_ident_t.192. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.192. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.192. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %7 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %8 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %7, i8* %8, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %st
  store i32 5, i32* %ub
  store i32 0, i32* %lb
  store i32 0, i32* %last
  store i32 0, i32* %.idx.addr
  store i32* %0, i32** %.addr, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !28), !dbg !29
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !30), !dbg !29
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !31), !dbg !29
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !29
  %arg3 = load i8** %.addr2, !dbg !29
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*, !dbg !29
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([29 x i8]* @.str, i32 0, i32 0)), !dbg !32
  %9 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([39 x i8]* @0, i32 0, i32 0), i8** %9
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_for_static_init_4u({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.sections.begin

omp.sections.begin:                               ; preds = %entry
  %10 = load i32* %ub
  %11 = icmp ult i32 %10, 5
  %12 = select i1 %11, i32 %10, i32 5
  store i32 %12, i32* %ub
  %13 = load i32* %lb
  store i32 %13, i32* %.idx.addr
  %omp.lb.le.ub = icmp ule i32 %13, %12
  br i1 %omp.lb.le.ub, label %omp.lb_ub.check_pass, label %omp.sections.end

omp.lb_ub.check_pass:                             ; preds = %omp.section.fini, %omp.sections.begin
  %.idx. = load i32* %.idx.addr
  switch i32 %.idx., label %omp.section.fini [
    i32 0, label %omp.section
    i32 1, label %omp.section4
    i32 2, label %omp.section8
    i32 3, label %omp.section12
    i32 4, label %omp.section16
    i32 5, label %omp.section20
  ]

omp.section:                                      ; preds = %omp.lb_ub.check_pass
  %call3 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([29 x i8]* @.str1, i32 0, i32 0)), !dbg !34
  br label %omp.section.fini, !dbg !34

omp.section4:                                     ; preds = %omp.lb_ub.check_pass
  %call5 = call i32 @sleep(i32 1), !dbg !35
  %call6 = call i32 @omp_get_thread_num(), !dbg !37
  %call7 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @.str2, i32 0, i32 0), i32 %call6), !dbg !38
  br label %omp.section.fini, !dbg !39

omp.section8:                                     ; preds = %omp.lb_ub.check_pass
  %call9 = call i32 @sleep(i32 2), !dbg !40
  %call10 = call i32 @omp_get_thread_num(), !dbg !42
  %call11 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @.str3, i32 0, i32 0), i32 %call10), !dbg !43
  br label %omp.section.fini, !dbg !44

omp.section12:                                    ; preds = %omp.lb_ub.check_pass
  %call13 = call i32 @sleep(i32 3), !dbg !45
  %call14 = call i32 @omp_get_thread_num(), !dbg !47
  %call15 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @.str4, i32 0, i32 0), i32 %call14), !dbg !48
  br label %omp.section.fini, !dbg !49

omp.section16:                                    ; preds = %omp.lb_ub.check_pass
  %call17 = call i32 @sleep(i32 4), !dbg !50
  %call18 = call i32 @omp_get_thread_num(), !dbg !52
  %call19 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @.str5, i32 0, i32 0), i32 %call18), !dbg !53
  br label %omp.section.fini, !dbg !54

omp.section20:                                    ; preds = %omp.lb_ub.check_pass
  %call21 = call i32 @sleep(i32 5), !dbg !55
  %call22 = call i32 @omp_get_thread_num(), !dbg !57
  %call23 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @.str6, i32 0, i32 0), i32 %call22), !dbg !58
  br label %omp.section.fini, !dbg !59

omp.section.fini:                                 ; preds = %omp.section20, %omp.section16, %omp.section12, %omp.section8, %omp.section4, %omp.section, %omp.lb_ub.check_pass
  %.next.idx. = add i32 %.idx., 1, !dbg !60
  store i32 %.next.idx., i32* %.idx.addr, !dbg !60
  %omp.idx.le.ub = icmp ule i32 %.next.idx., %12, !dbg !60
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.sections.end, !dbg !60

omp.sections.end:                                 ; preds = %omp.section.fini, %omp.sections.begin
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !62
  %14 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.192., i32 0, i32 4
  store i8* getelementptr inbounds ([40 x i8]* @1, i32 0, i32 0), i8** %14
  %.gtid.24 = load i32* %.__kmpc_global_thread_num.
  %15 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.192., i32 %.gtid.24)
  %16 = icmp ne i32 %15, 0
  br i1 %16, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.sections.end
  br label %omp.cancel_barrier.continue27

omp.cancel_barrier.continue:                      ; preds = %omp.sections.end
  %17 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([39 x i8]* @2, i32 0, i32 0), i8** %17
  %.gtid.25 = load i32* %.__kmpc_global_thread_num.
  %18 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.25)
  %19 = icmp ne i32 %18, 0
  br i1 %19, label %omp.cancel_barrier.exit26, label %omp.cancel_barrier.continue27

omp.cancel_barrier.exit26:                        ; preds = %omp.cancel_barrier.continue
  br label %omp.cancel_barrier.continue27

omp.cancel_barrier.continue27:                    ; preds = %omp.cancel_barrier.exit, %omp.cancel_barrier.exit26, %omp.cancel_barrier.continue
  ret void, !dbg !64
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

declare void @__kmpc_for_static_init_4u({ i32, i32, i32, i32, i8* }*, i32, i32, i32*, i32*, i32*, i32*, i32, i32)

declare i32 @sleep(i32) #2

declare i32 @omp_get_thread_num() #2

declare void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!17, !18}
!llvm.ident = !{!19}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 1} ; [ DW_TAG_compile_unit ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-sections.c] [DW_LANG_C99]
!1 = metadata !{metadata !"omp-sections.c", metadata !"/home/jeremy/code/research/hpxMP/omp-tests"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !12}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"main", metadata !"main", metadata !"", i32 5, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, i32 (i32, i8**)* @main, null, null, metadata !2, i32 5} ; [ DW_TAG_subprogram ] [line 5] [def] [main]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-sections.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{metadata !8, metadata !8, metadata !9}
!8 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!9 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !10} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!10 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !11} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from char]
!11 = metadata !{i32 786468, null, null, metadata !"char", i32 0, i64 8, i64 8, i64 0, i32 0, i32 6} ; [ DW_TAG_base_type ] [char] [line 0, size 8, align 8, offset 0, enc DW_ATE_signed_char]
!12 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 7, metadata !13, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask., null, null, metadata !2, i32 7} ; [ DW_TAG_subprogram ] [line 7] [local] [def] [.omp_microtask.]
!13 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !14, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!14 = metadata !{null, metadata !15, metadata !15, metadata !16}
!15 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !8} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from int]
!16 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!17 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!18 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!19 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
!20 = metadata !{i32 786689, metadata !4, metadata !"argc", metadata !5, i32 16777221, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [argc] [line 5]
!21 = metadata !{i32 5, i32 14, metadata !4, null}
!22 = metadata !{i32 786689, metadata !4, metadata !"argv", metadata !5, i32 33554437, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [argv] [line 5]
!23 = metadata !{i32 5, i32 27, metadata !4, null}
!24 = metadata !{i32 786688, metadata !4, metadata !"x", metadata !5, i32 6, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [x] [line 6]
!25 = metadata !{i32 6, i32 9, metadata !4, null}
!26 = metadata !{i32 6, i32 5, metadata !4, null}
!27 = metadata !{i32 40, i32 5, metadata !4, null}
!28 = metadata !{i32 786689, metadata !12, metadata !"", metadata !5, i32 16777223, metadata !15, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 7]
!29 = metadata !{i32 7, i32 9, metadata !12, null}
!30 = metadata !{i32 786689, metadata !12, metadata !"", metadata !5, i32 33554439, metadata !15, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 7]
!31 = metadata !{i32 786689, metadata !12, metadata !"", metadata !5, i32 50331655, metadata !16, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 7]
!32 = metadata !{i32 9, i32 9, metadata !33, null}
!33 = metadata !{i32 786443, metadata !1, metadata !12, i32 8, i32 5, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-sections.c]
!34 = metadata !{i32 12, i32 9, metadata !33, null}
!35 = metadata !{i32 15, i32 17, metadata !36, null}
!36 = metadata !{i32 786443, metadata !1, metadata !33, i32 14, i32 13, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-sections.c]
!37 = metadata !{i32 16, i32 53, metadata !36, null}
!38 = metadata !{i32 16, i32 17, metadata !36, null}
!39 = metadata !{i32 17, i32 13, metadata !36, null}
!40 = metadata !{i32 20, i32 17, metadata !41, null}
!41 = metadata !{i32 786443, metadata !1, metadata !33, i32 19, i32 13, i32 0, i32 2} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-sections.c]
!42 = metadata !{i32 21, i32 53, metadata !41, null}
!43 = metadata !{i32 21, i32 17, metadata !41, null}
!44 = metadata !{i32 22, i32 13, metadata !41, null}
!45 = metadata !{i32 25, i32 17, metadata !46, null}
!46 = metadata !{i32 786443, metadata !1, metadata !33, i32 24, i32 13, i32 0, i32 3} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-sections.c]
!47 = metadata !{i32 26, i32 53, metadata !46, null}
!48 = metadata !{i32 26, i32 17, metadata !46, null}
!49 = metadata !{i32 27, i32 13, metadata !46, null}
!50 = metadata !{i32 30, i32 17, metadata !51, null}
!51 = metadata !{i32 786443, metadata !1, metadata !33, i32 29, i32 13, i32 0, i32 4} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-sections.c]
!52 = metadata !{i32 31, i32 53, metadata !51, null}
!53 = metadata !{i32 31, i32 17, metadata !51, null}
!54 = metadata !{i32 32, i32 13, metadata !51, null}
!55 = metadata !{i32 35, i32 17, metadata !56, null}
!56 = metadata !{i32 786443, metadata !1, metadata !33, i32 34, i32 13, i32 0, i32 5} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-sections.c]
!57 = metadata !{i32 36, i32 53, metadata !56, null}
!58 = metadata !{i32 36, i32 17, metadata !56, null}
!59 = metadata !{i32 37, i32 13, metadata !56, null}
!60 = metadata !{i32 37, i32 13, metadata !61, null}
!61 = metadata !{i32 786443, metadata !1, metadata !56, i32 37, i32 13, i32 1, i32 6} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-sections.c]
!62 = metadata !{i32 37, i32 13, metadata !63, null}
!63 = metadata !{i32 786443, metadata !1, metadata !56, i32 37, i32 13, i32 2, i32 7} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-sections.c]
!64 = metadata !{i32 39, i32 5, metadata !12, null}
