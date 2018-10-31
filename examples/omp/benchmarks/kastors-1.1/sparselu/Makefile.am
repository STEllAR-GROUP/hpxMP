
include ../common/common.am

check_SCRIPTS = check_sparselu_taskdep.sh\
				check_sparselu_task.sh\
				check_sparselu_seq.sh
TESTS= $(check_SCRIPTS)

check_%.sh:
	@python -c "print './' + '$@'[6:-3] + ' -c'" > $@
	@chmod +x $@

CLEANFILES=$(check_SCRIPTS)

bin_PROGRAMS = sparselu_seq sparselu_task sparselu_taskdep

sparselu_common_HDRS = include/sparselu.h $(COMMON_HDRS)
sparselu_common_SRCS = src/sparselu.c src/sparselu-seq.c $(COMMON_SRCS) \
	$(sparselu_common_HDRS)

sparselu_seq_SOURCES     = $(sparselu_common_SRCS)
sparselu_task_SOURCES    = $(sparselu_common_SRCS) src/sparselu-task.c
sparselu_taskdep_SOURCES = $(sparselu_common_SRCS) src/sparselu-task-dep.c

sparselu_comCFLAGS = -I$(srcdir)/include $(COMMON_comCFLAGS) \
		-DMSIZE -DSMSIZE
sparselu_seq_CFLAGS     = $(sparselu_comCFLAGS) $(COMMON_seqCFLAGS)
sparselu_parCFLAGS	= $(sparselu_comCFLAGS) $(COMMON_parCFLAGS)

sparselu_task_CFLAGS    = $(sparselu_parCFLAGS)
sparselu_taskdep_CFLAGS = $(sparselu_parCFLAGS)

sparselu_comLDFLAGS = $(COMMON_comLDFLAGS)
sparselu_seq_LDFLAGS = $(sparselu_comLDFLAGS) $(COMMON_seqLDFLAGS)
sparselu_parLDFLAGS = $(sparselu_comLDFLAGS) $(COMMON_parLDFLAGS)

sparselu_task_LDFLAGS    = $(sparselu_parLDFLAGS)
sparselu_taskdep_LDFLAGS = $(sparselu_parLDFLAGS)

run:
	sh ../run.sh -mode seq -bench sparselu -n_sparselu 128 -m_sparselu 64 | tee -a $(OUT)
	sh ../run.sh -mode seq -bench sparselu -n_sparselu 64 -m_sparselu 128 | tee -a $(OUT)
	sh ../run.sh -rs 0 -n_sparselu 128 -m_sparselu 64 -rt 10 -rtd 10 -bench sparselu | tee -a $(OUT)
	sh ../run.sh -rs 0 -n_sparselu 64 -m_sparselu 128 -rt 10 -rtd 10 -bench sparselu | tee -a $(OUT)

