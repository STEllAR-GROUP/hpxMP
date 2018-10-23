
include ../common/common.am

check_SCRIPTS = check_dgetrf_seq.sh\
				check_dgetrf_taskdep.sh\
				check_dgeqrf_seq.sh\
				check_dgeqrf_taskdep.sh\
				check_dpotrf_seq.sh\
				check_dpotrf_taskdep.sh
TESTS= $(check_SCRIPTS)

check_%.sh:
	@python -c "print './' + '$@'[6:-3] + ' -c'" > $@
	@chmod +x $@

CLEANFILES=$(check_SCRIPTS)


bin_PROGRAMS = dpotrf_seq dpotrf_taskdep dgetrf_seq dgetrf_taskdep dgeqrf_seq dgeqrf_taskdep

# Get all source files from ./src except the one called time_xxx
plasma_SRCS = \
	src/auxiliary.c 		\
	src/core_dgeqrt.c		\
	src/core_dgetrf_rectil.c	\
	src/core_dlaswp.c 		\
	src/core_dormqr.c 		\
	src/core_dpamm.c 		\
	src/core_dparfb.c 		\
	src/core_dplgsy.c		\
	src/core_dplrnt.c		\
	src/core_dtsmqr.c 		\
	src/core_dtsqrt.c		\
	src/dauxiliary.c		\
	src/descriptor.c		\
	src/dgeqrs.c 			\
	src/dgetrs.c 			\
	src/dpotrs.c			\
	src/global.c			\
	src/pdgeqrf.c 			\
	src/pdgetrf_rectil.c 		\
	src/pdlaswp.c 			\
	src/pdormqr.c			\
	src/pdplgsy.c			\
	src/pdpltmg.c			\
	src/pdpotrf.c			\
	src/pdtile.c 			\
	src/pdtrsm.c 			\
	src/workspace.c

plasma_common_HDRS = include/common.h\
					 include/auxiliary.h\
					 include/compute_d.h\
					 include/core_blas.h\
					 include/core_dblas.h\
					 include/dauxiliary.h\
					 include/descriptor.h\
					 include/flops.h\
					 include/plasma.h\
					 include/plasma_d.h\
					 include/plasmatypes.h\
					 include/random.h\
					 include/tile.h\
					 include/timing.h\
					 include/workspace.h\
					 src/timing.inc\
					 $(COMMON_HDRS)
plasma_common_SRCS = $(plasma_SRCS) $(COMMON_SRCS) $(plasma_common_HDRS)

plasma_comLIBS		= @PLASMA_comLIBS@ @LD_PLASMA@


noinst_LIBRARIES = libplasma-seq.a libplasma-par.a
libplasma_seq_a_SOURCES = $(plasma_common_SRCS)
libplasma_par_a_SOURCES = 

dpotrf_seq_SOURCES      = src/time_dpotrf-task.c
dpotrf_taskdep_SOURCES  = src/time_dpotrf-task.c $(plasma_common_SRCS)
dgetrf_seq_SOURCES      = src/time_dgetrf-task.c
dgetrf_taskdep_SOURCES  = src/time_dgetrf-task.c $(plasma_common_SRCS)
dgeqrf_seq_SOURCES      = src/time_dgeqrf-task.c
dgeqrf_taskdep_SOURCES  = src/time_dgeqrf-task.c $(plasma_common_SRCS)

dpotrf_seq_LDADD      = libplasma-seq.a $(plasma_comLIBS)
dpotrf_taskdep_LDADD  = libplasma-par.a $(plasma_comLIBS)
dgetrf_seq_LDADD      = libplasma-seq.a $(plasma_comLIBS)
dgetrf_taskdep_LDADD  = libplasma-par.a $(plasma_comLIBS)
dgeqrf_seq_LDADD      = libplasma-seq.a $(plasma_comLIBS)
dgeqrf_taskdep_LDADD  = libplasma-par.a $(plasma_comLIBS)

plasma_comCFLAGS	= -I$(srcdir)/include $(COMMON_comCFLAGS) \
		-DADD_ -DMSIZE -DBSIZE -DGFLOPS @I_PLASMA@
plasma_seqCFLAGS	= $(plasma_comCFLAGS) $(COMMON_seqCFLAGS)
plasma_parCFLAGS	= $(plasma_comCFLAGS) $(COMMON_parCFLAGS)

libplasma_seq_a_CFLAGS  = $(plasma_seqCFLAGS)
libplasma_par_a_CFLAGS  = $(plasma_parCFLAGS)

dpotrf_seq_CFLAGS       = $(plasma_seqCFLAGS)
dpotrf_taskdep_CFLAGS   = $(plasma_parCFLAGS)
dgetrf_seq_CFLAGS       = $(plasma_seqCFLAGS)
dgetrf_taskdep_CFLAGS   = $(plasma_parCFLAGS)
dgeqrf_seq_CFLAGS       = $(plasma_seqCFLAGS) -DIBSIZE
dgeqrf_taskdep_CFLAGS   = $(plasma_parCFLAGS) -DIBSIZE

plasma_comLDFLAGS	= $(COMMON_comLDFLAGS)
plasma_seqLDFLAGS	= $(plasma_comLDFLAGS) $(COMMON_seqLDFLAGS)
plasma_parLDFLAGS	= $(plasma_comLDFLAGS) $(COMMON_parLDFLAGS)

dpotrf_seq_LDFLAGS      = $(plasma_seqLDFLAGS)
dpotrf_taskdep_LDFLAGS  = $(plasma_parLDFLAGS)
dgetrf_seq_LDFLAGS      = $(plasma_seqLDFLAGS)
dgetrf_taskdep_LDFLAGS  = $(plasma_parLDFLAGS)
dgeqrf_seq_LDFLAGS      = $(plasma_seqLDFLAGS)
dgeqrf_taskdep_LDFLAGS  = $(plasma_parLDFLAGS)

run:
	sh ../run.sh -bench dpotrf -bench dgetrf -bench dgeqrf -rs 0 -n_dgetrf 2048 -b_dgetrf 128 -n_dpotrf 2048 -b_dpotrf 128 -n_dgeqrf 2048 -b_dgeqrf 128 -rt 10 -rtd 10 | tee -a $(OUT)
	sh ../run.sh -bench dpotrf -bench dgetrf -bench dgeqrf -rs 0 -n_dgetrf 4096 -b_dgetrf 128 -n_dpotrf 4096 -b_dpotrf 128 -n_dgeqrf 4096 -b_dgeqrf 128 -rt 10 -rtd 10 | tee -a $(OUT)
	sh ../run.sh -bench dpotrf -bench dgetrf -bench dgeqrf -rs 0 -n_dgetrf 8192 -b_dgetrf 224 -n_dpotrf 8192 -b_dpotrf 224 -n_dgeqrf 8192 -b_dgeqrf 224 -rt 10 -rtd 10 | tee -a $(OUT)

