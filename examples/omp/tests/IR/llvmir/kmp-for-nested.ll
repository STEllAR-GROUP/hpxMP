; ModuleID = 'omp-for-nested.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32*, i32* }
%struct.anon.0 = type { i32*, i32* }

@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@0 = private unnamed_addr constant [40 x i8] c";omp-for-nested.c;.omp_microtask.;7;9;;\00"
@1 = private unnamed_addr constant [40 x i8] c";omp-for-nested.c;.omp_microtask.;9;9;;\00"
@.str = private unnamed_addr constant [20 x i8] c"Hello World %d, %d\0A\00", align 1
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@2 = private unnamed_addr constant [41 x i8] c";omp-for-nested.c;.omp_microtask.;9;41;;\00"
@3 = private unnamed_addr constant [40 x i8] c";omp-for-nested.c;.omp_microtask.;9;9;;\00"
@4 = private unnamed_addr constant [40 x i8] c";omp-for-nested.c;.omp_microtask.;9;9;;\00"
@5 = private unnamed_addr constant [41 x i8] c";omp-for-nested.c;.omp_microtask.;7;25;;\00"
@6 = private unnamed_addr constant [29 x i8] c";omp-for-nested.c;main;7;9;;\00"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %agg.captured = alloca %struct.anon, align 8
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  %1 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %1, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 0, i32* %retval
  call void @llvm.dbg.declare(metadata !{i32* %i}, metadata !18), !dbg !19
  call void @llvm.dbg.declare(metadata !{i32* %j}, metadata !20), !dbg !21
  %2 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 0, !dbg !22
  store i32* %i, i32** %2, align 8, !dbg !22
  %3 = getelementptr inbounds %struct.anon* %agg.captured, i32 0, i32 1, !dbg !22
  store i32* %j, i32** %3, align 8, !dbg !22
  %4 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([29 x i8]* @6, i32 0, i32 0), i8** %4
  %5 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %5)
  ret i32 0, !dbg !23
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
  %debug.ub = alloca i32, align 4
  %last = alloca i32, align 4
  %lb = alloca i32, align 4
  %ub = alloca i32, align 4
  %st = alloca i32, align 4
  %.idx. = alloca i32, align 4
  %i.private. = alloca i32, align 4
  %agg.captured = alloca %struct.anon.0, align 8
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %st
  store i32 1, i32* %last
  store i32* %0, i32** %.addr, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !24), !dbg !25
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !26), !dbg !25
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !27), !dbg !25
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !25
  %arg3 = load i8** %.addr2, !dbg !25
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon*, !dbg !25
  %7 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 0, !dbg !25
  %ref = load i32** %7, align 8, !dbg !25
  %8 = getelementptr inbounds %struct.anon* %"(anon)arg3", i32 0, i32 1, !dbg !25
  %ref3 = load i32** %8, align 8, !dbg !25
  %9 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([40 x i8]* @0, i32 0, i32 0), i8** %9
  %.gtid. = load i32* %.__kmpc_global_thread_num.
  store i32 4, i32* %debug.ub
  store i32 0, i32* %lb
  store i32 4, i32* %ub
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0)
  br label %omp.loop.begin

omp.loop.begin:                                   ; preds = %entry
  %10 = load i32* %lb
  store i32 %10, i32* %.idx.
  %11 = load i32* %ub
  %12 = icmp slt i32 %11, 4
  %13 = select i1 %12, i32 %11, i32 4
  store i32 %13, i32* %ub
  br label %omp.loop.main

omp.loop.main:                                    ; preds = %omp.cont.block, %omp.loop.begin
  %14 = icmp sle i32 %10, 4
  br i1 %14, label %omp.lb.le.global_ub., label %omp.loop.end

omp.lb.le.global_ub.:                             ; preds = %omp.loop.main
  store i32 0, i32* %i.private., align 4, !dbg !25
  %15 = load i32* %.idx., align 4, !dbg !25
  %mul = mul nsw i32 %15, 1, !dbg !25
  %16 = load i32* %i.private., align 4, !dbg !25
  %add = add nsw i32 %16, %mul, !dbg !25
  store i32 %add, i32* %i.private., align 4, !dbg !25
  %.idx.4 = load i32* %.idx., !dbg !25
  %17 = load i32* %ub, !dbg !25
  %omp.idx.le.ub = icmp sle i32 %.idx.4, %17, !dbg !25
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini, !dbg !25

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %18 = getelementptr inbounds %struct.anon.0* %agg.captured, i32 0, i32 0, !dbg !28
  store i32* %ref3, i32** %18, align 8, !dbg !28
  %19 = getelementptr inbounds %struct.anon.0* %agg.captured, i32 0, i32 1, !dbg !28
  store i32* %i.private., i32** %19, align 8, !dbg !28
  %20 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4, !dbg !28
  store i8* getelementptr inbounds ([40 x i8]* @4, i32 0, i32 0), i8** %20, !dbg !28
  %21 = bitcast %struct.anon.0* %agg.captured to i8*, !dbg !28
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask.1 to void (i32*, i32*, ...)*), i8* %21), !dbg !28
  br label %omp.cont.block, !dbg !30

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.5 = load i32* %.idx., !dbg !31
  %.next.idx. = add nsw i32 %.idx.5, 1, !dbg !31
  store i32 %.next.idx., i32* %.idx., !dbg !31
  br label %omp.loop.main, !dbg !31

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end, !dbg !30

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !33
  %22 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([41 x i8]* @5, i32 0, i32 0), i8** %22
  %.gtid.6 = load i32* %.__kmpc_global_thread_num.
  %23 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.6)
  %24 = icmp ne i32 %23, 0
  br i1 %24, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void, !dbg !35
}

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

declare void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }*, i32, i32, i32*, i32*, i32*, i32*, i32, i32)

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.1(i32*, i32*, i8*) #0 {
entry:
  %.addr = alloca i32*, align 8
  %.addr1 = alloca i32*, align 8
  %.addr2 = alloca i8*, align 8
  %i = alloca i32, align 4
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
  %j.private. = alloca i32, align 4
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %5 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  %6 = bitcast { i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 ptrtoint ({ i32, i32, i32, i32, i8* }* getelementptr ({ i32, i32, i32, i32, i8* }* null, i32 1) to i64), i32 8, i1 false)
  store i32 1, i32* %st
  store i32 1, i32* %last
  store i32* %0, i32** %.addr, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr}, metadata !36), !dbg !37
  store i32* %1, i32** %.addr1, align 8
  call void @llvm.dbg.declare(metadata !{i32** %.addr1}, metadata !38), !dbg !37
  store i8* %2, i8** %.addr2, align 8
  call void @llvm.dbg.declare(metadata !{i8** %.addr2}, metadata !39), !dbg !37
  %.__kmpc_global_thread_num. = load i32** %.addr, !dbg !37
  %arg3 = load i8** %.addr2, !dbg !37
  %"(anon)arg3" = bitcast i8* %arg3 to %struct.anon.0*, !dbg !37
  %7 = getelementptr inbounds %struct.anon.0* %"(anon)arg3", i32 0, i32 0, !dbg !37
  %ref = load i32** %7, align 8, !dbg !37
  %8 = getelementptr inbounds %struct.anon.0* %"(anon)arg3", i32 0, i32 1, !dbg !37
  %ref3 = load i32** %8, align 8, !dbg !37
  call void @llvm.dbg.declare(metadata !{i32* %i}, metadata !40), !dbg !41
  %9 = load i32* %ref3, align 4, !dbg !37
  store i32 %9, i32* %i, !dbg !37
  %10 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([40 x i8]* @3, i32 0, i32 0), i8** %10
  %.gtid.7 = load i32* %.__kmpc_global_thread_num.
  call void @__kmpc_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.7)
  %11 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 0, i32 4
  store i8* getelementptr inbounds ([40 x i8]* @1, i32 0, i32 0), i8** %11
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
  store i32 0, i32* %j.private., align 4, !dbg !41
  %17 = load i32* %.idx., align 4, !dbg !41
  %mul = mul nsw i32 %17, 1, !dbg !41
  %18 = load i32* %j.private., align 4, !dbg !41
  %add = add nsw i32 %18, %mul, !dbg !41
  store i32 %add, i32* %j.private., align 4, !dbg !41
  %.idx.4 = load i32* %.idx., !dbg !41
  %19 = load i32* %ub, !dbg !41
  %omp.idx.le.ub = icmp sle i32 %.idx.4, %19, !dbg !41
  br i1 %omp.idx.le.ub, label %omp.lb_ub.check_pass, label %omp.loop.fini, !dbg !41

omp.lb_ub.check_pass:                             ; preds = %omp.lb.le.global_ub.
  %20 = load i32* %i, align 4, !dbg !42
  %21 = load i32* %j.private., align 4, !dbg !42
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([20 x i8]* @.str, i32 0, i32 0), i32 %20, i32 %21), !dbg !42
  br label %omp.cont.block, !dbg !44

omp.cont.block:                                   ; preds = %omp.lb_ub.check_pass
  %.idx.5 = load i32* %.idx., !dbg !45
  %.next.idx. = add nsw i32 %.idx.5, 1, !dbg !45
  store i32 %.next.idx., i32* %.idx., !dbg !45
  br label %omp.loop.main, !dbg !45

omp.loop.fini:                                    ; preds = %omp.lb.le.global_ub.
  br label %omp.loop.end, !dbg !44

omp.loop.end:                                     ; preds = %omp.loop.fini, %omp.loop.main
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.), !dbg !47
  %22 = getelementptr inbounds { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 0, i32 4
  store i8* getelementptr inbounds ([41 x i8]* @2, i32 0, i32 0), i8** %22
  %.gtid.6 = load i32* %.__kmpc_global_thread_num.
  %23 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.6)
  %24 = icmp ne i32 %23, 0
  br i1 %24, label %omp.cancel_barrier.exit, label %omp.cancel_barrier.continue

omp.cancel_barrier.exit:                          ; preds = %omp.loop.end
  br label %omp.cancel_barrier.continue

omp.cancel_barrier.continue:                      ; preds = %omp.cancel_barrier.exit, %omp.loop.end
  ret void, !dbg !49
}

declare i32 @printf(i8*, ...) #3

declare void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }
attributes #3 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!15, !16}
!llvm.ident = !{!17}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 1} ; [ DW_TAG_compile_unit ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for-nested.c] [DW_LANG_C99]
!1 = metadata !{metadata !"omp-for-nested.c", metadata !"/home/jeremy/code/research/hpxMP/omp-tests"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !9, metadata !14}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"main", metadata !"main", metadata !"", i32 4, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 ()* @main, null, null, metadata !2, i32 4} ; [ DW_TAG_subprogram ] [line 4] [def] [main]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for-nested.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{metadata !8}
!8 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!9 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 7, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask., null, null, metadata !2, i32 7} ; [ DW_TAG_subprogram ] [line 7] [local] [def] [.omp_microtask.]
!10 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{null, metadata !12, metadata !12, metadata !13}
!12 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !8} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from int]
!13 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!14 = metadata !{i32 786478, metadata !1, metadata !5, metadata !".omp_microtask.", metadata !".omp_microtask.", metadata !"", i32 9, metadata !10, i1 true, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i32*, i32*, i8*)* @.omp_microtask.1, null, null, metadata !2, i32 9} ; [ DW_TAG_subprogram ] [line 9] [local] [def] [.omp_microtask.]
!15 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!16 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!17 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
!18 = metadata !{i32 786688, metadata !4, metadata !"i", metadata !5, i32 5, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [i] [line 5]
!19 = metadata !{i32 5, i32 9, metadata !4, null}
!20 = metadata !{i32 786688, metadata !4, metadata !"j", metadata !5, i32 5, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [j] [line 5]
!21 = metadata !{i32 5, i32 11, metadata !4, null}
!22 = metadata !{i32 7, i32 9, metadata !4, null}
!23 = metadata !{i32 17, i32 5, metadata !4, null}
!24 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 16777223, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 7]
!25 = metadata !{i32 7, i32 9, metadata !9, null}
!26 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 33554439, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 7]
!27 = metadata !{i32 786689, metadata !9, metadata !"", metadata !5, i32 50331655, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 7]
!28 = metadata !{i32 9, i32 9, metadata !29, null}
!29 = metadata !{i32 786443, metadata !1, metadata !9, i32 8, i32 28, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for-nested.c]
!30 = metadata !{i32 13, i32 5, metadata !29, null}
!31 = metadata !{i32 13, i32 5, metadata !32, null}
!32 = metadata !{i32 786443, metadata !1, metadata !29, i32 13, i32 5, i32 1, i32 2} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for-nested.c]
!33 = metadata !{i32 13, i32 5, metadata !34, null}
!34 = metadata !{i32 786443, metadata !1, metadata !29, i32 13, i32 5, i32 2, i32 3} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for-nested.c]
!35 = metadata !{i32 13, i32 5, metadata !9, null}
!36 = metadata !{i32 786689, metadata !14, metadata !"", metadata !5, i32 16777225, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 9]
!37 = metadata !{i32 9, i32 9, metadata !14, null}
!38 = metadata !{i32 786689, metadata !14, metadata !"", metadata !5, i32 33554441, metadata !12, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 9]
!39 = metadata !{i32 786689, metadata !14, metadata !"", metadata !5, i32 50331657, metadata !13, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [line 9]
!40 = metadata !{i32 786688, metadata !14, metadata !"i", metadata !5, i32 5, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [i] [line 5]
!41 = metadata !{i32 5, i32 9, metadata !14, null}
!42 = metadata !{i32 11, i32 13, metadata !43, null}
!43 = metadata !{i32 786443, metadata !1, metadata !14, i32 10, i32 32, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for-nested.c]
!44 = metadata !{i32 12, i32 9, metadata !43, null}
!45 = metadata !{i32 12, i32 9, metadata !46, null}
!46 = metadata !{i32 786443, metadata !1, metadata !43, i32 12, i32 9, i32 1, i32 4} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for-nested.c]
!47 = metadata !{i32 12, i32 9, metadata !48, null}
!48 = metadata !{i32 786443, metadata !1, metadata !43, i32 12, i32 9, i32 2, i32 5} ; [ DW_TAG_lexical_block ] [/home/jeremy/code/research/hpxMP/omp-tests/omp-for-nested.c]
!49 = metadata !{i32 12, i32 9, metadata !14, null}
