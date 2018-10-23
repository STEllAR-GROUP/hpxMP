; ModuleID = 'omp-for-simple.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32* }

@.omp.default.loc. = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00"
@.omp.default.loc.2. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }
@.str = private unnamed_addr constant [16 x i8] c"Hello World %d\0A\00", align 1
@.omp.default.loc.64. = private unnamed_addr constant { i32, i32, i32, i32, i8* } { i32 0, i32 64, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8]* @.omp.default.loc., i32 0, i32 0) }

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %i = alloca i32, align 4
  %agg.captured = alloca %struct.anon, align 8
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %0 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* bitcast ({ i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*), i64 24, i32 8, i1 false)
  %1 = getelementptr inbounds %struct.anon* %agg.captured, i64 0, i32 0
  store i32* %i, i32** %1, align 8, !tbaa !1
  %2 = bitcast %struct.anon* %agg.captured to i8*
  call void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 2, void (i32*, i32*, ...)* bitcast (void (i32*, i32*, i8*)* @.omp_microtask. to void (i32*, i32*, ...)*), i8* %2) #1
  ret i32 0
}

; Function Attrs: nounwind uwtable
define internal void @.omp_microtask.(i32* nocapture readonly, i32* nocapture readnone, i8* nocapture readnone) #0 {
entry:
  %.__kmpc_ident_t.2. = alloca { i32, i32, i32, i32, i8* }, align 8
  %3 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* bitcast ({ i32, i32, i32, i32, i8* }* @.omp.default.loc.2. to i8*), i64 24, i32 8, i1 false)
  %last = alloca i32, align 4
  %lb = alloca i32, align 4
  %ub = alloca i32, align 4
  %st = alloca i32, align 4
  %.__kmpc_ident_t.64. = alloca { i32, i32, i32, i32, i8* }, align 8
  %4 = bitcast { i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64. to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %4, i8* bitcast ({ i32, i32, i32, i32, i8* }* @.omp.default.loc.64. to i8*), i64 24, i32 8, i1 false)
  store i32 1, i32* %st, align 4
  store i32 1, i32* %last, align 4
  %.gtid. = load i32* %0, align 4
  store i32 0, i32* %lb, align 4
  store i32 10, i32* %ub, align 4
  call void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid., i32 34, i32* %last, i32* %lb, i32* %ub, i32* %st, i32 1, i32 0) #1
  %5 = load i32* %lb, align 4
  %6 = load i32* %ub, align 4
  %7 = icmp slt i32 %6, 10
  %8 = select i1 %7, i32 %6, i32 10
  store i32 %8, i32* %ub, align 4
  %9 = icmp sgt i32 %5, 10
  %omp.idx.le.ub9 = icmp sgt i32 %5, %8
  %or.cond10 = or i1 %9, %omp.idx.le.ub9
  br i1 %or.cond10, label %omp.loop.end, label %omp.lb_ub.check_pass

omp.lb_ub.check_pass:                             ; preds = %entry, %omp.lb_ub.check_pass
  %.idx..011 = phi i32 [ %.next.idx., %omp.lb_ub.check_pass ], [ %5, %entry ]
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([16 x i8]* @.str, i64 0, i64 0), i32 %.idx..011) #1
  %.next.idx. = add nsw i32 %.idx..011, 1
  %10 = load i32* %ub, align 4
  %omp.idx.le.ub = icmp sge i32 %.idx..011, %10
  %or.cond = or i1 %9, %omp.idx.le.ub
  br i1 %or.cond, label %omp.loop.end, label %omp.lb_ub.check_pass

omp.loop.end:                                     ; preds = %omp.lb_ub.check_pass, %entry
  call void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.2., i32 %.gtid.) #1
  %.gtid.5 = load i32* %0, align 4
  %11 = call i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }* %.__kmpc_ident_t.64., i32 %.gtid.5) #1
  ret void
}

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #1

declare void @__kmpc_for_static_init_4({ i32, i32, i32, i32, i8* }*, i32, i32, i32*, i32*, i32*, i32*, i32, i32)

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) #2

declare void @__kmpc_for_static_fini({ i32, i32, i32, i32, i8* }*, i32)

declare i32 @__kmpc_cancel_barrier({ i32, i32, i32, i32, i8* }*, i32)

declare void @__kmpc_fork_call({ i32, i32, i32, i32, i8* }*, i32, void (i32*, i32*, ...)*, i8*)

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.5.0 (https://github.com/clang-omp/clang a3011cace361bda84d6e1e1cd1827c986a07dc37) (https://github.com/clang-omp/llvm e45b045553e027cbe400cbb8ac8c264abbbfaf83)"}
!1 = metadata !{metadata !2, metadata !2, i64 0}
!2 = metadata !{metadata !"omnipotent char", metadata !3, i64 0}
!3 = metadata !{metadata !"Simple C/C++ TBAA"}
