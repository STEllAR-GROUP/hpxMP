
include ../common/common.am

check_SCRIPTS = check_strassen_taskdep.sh\
				check_strassen_task.sh\
				check_strassen_seq.sh
TESTS= $(check_SCRIPTS)

check_%.sh:
	@python -c "print './' + '$@'[6:-3] + ' -c'" > $@
	@chmod +x $@

CLEANFILES=$(check_SCRIPTS)

bin_PROGRAMS = strassen_seq strassen_task strassen_taskdep

strassen_common_HDRS = include/strassen.h $(COMMON_HDRS)
strassen_common_SRCS = src/strassen.c src/strassen-seq.c $(COMMON_SRCS) \
	$(strassen_common_HDRS)

strassen_seq_SOURCES     = $(strassen_common_SRCS)
strassen_task_SOURCES    = $(strassen_common_SRCS) src/strassen-task.c
strassen_taskdep_SOURCES = $(strassen_common_SRCS) src/strassen-task-dep.c

strassen_comCFLAGS = -I$(srcdir)/include $(COMMON_comCFLAGS) \
		-DMSIZE -DCUTOFF_SIZE -DCUTOFF_DEPTH
strassen_seq_CFLAGS = $(strassen_comCFLAGS) $(COMMON_seqCFLAGS)
strassen_parCFLAGS = $(strassen_comCFLAGS) $(COMMON_parCFLAGS)

strassen_task_CFLAGS    = $(strassen_parCFLAGS)
strassen_taskdep_CFLAGS = $(strassen_parCFLAGS)

strassen_comLDFLAGS = $(COMMON_comLDFLAGS)
strassen_seq_LDFLAGS = $(strassen_comLDFLAGS) $(COMMON_seqLDFLAGS)
strassen_parLDFLAGS = $(strassen_comLDFLAGS) $(COMMON_parLDFLAGS)

strassen_task_LDFLAGS    = $(strassen_parLDFLAGS)
strassen_taskdep_LDFLAGS = $(strassen_parLDFLAGS)

run:
	sh ../run.sh -mode seq -bench strassen -n_strassen 4096 | tee -a $(OUT)
	sh ../run.sh -mode seq -bench strassen -n_strassen 8192 | tee -a $(OUT)
	sh ../run.sh -rs 0 -n_strassen 4096 -rt 10 -rtd 10 -bench strassen | tee -a $(OUT)
	sh ../run.sh -rs 0 -n_strassen 8192 -rt 10 -rtd 10 -bench strassen | tee -a $(OUT)
