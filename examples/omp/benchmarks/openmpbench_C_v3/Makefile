include Makefile.defs

# If CFLAGS_CRAY is empty set it to CFLAGS
ifeq ($(CFLAGS_CRAY),)
CFLAGS_CRAY = ${CFLAGS}
endif

.c.o:
	${CC} ${CFLAGS} $(OMPFLAG) -c $*.c 

SYNCOBJS =  syncbench.o common.o 
SCHEDOBJS = schedbench.o common_sched.o 
ARRAYOBJS = arraybench_$(IDA).o common.o 
TASKOBJS =  taskbench.o common.o 
SCHEDFLAGS = -DSCHEDBENCH

all:	syncbench schedbench taskbench
	$(MAKE) IDA=1 prog
	$(MAKE) IDA=3 prog
	$(MAKE) IDA=9 prog
	$(MAKE) IDA=27 prog
	$(MAKE) IDA=81 prog
	$(MAKE) IDA=243 prog
	$(MAKE) IDA=729 prog
	$(MAKE) IDA=2187 prog
	$(MAKE) IDA=6561 prog
	$(MAKE) IDA=19683 prog
	$(MAKE) IDA=59049 prog

prog: arraybench_$(IDA) 

syncbench: $(SYNCOBJS)
	$(CC) -o syncbench $(LDFLAGS) $(SYNCOBJS) $(CLOCKOBJS) $(LIBS) -lm

# Rule to ensure the lower optimisation level is picked up for common.c 
# with the Cray compiler
common.o:	
	${CC} ${CFLAGS_CRAY} $(OMPFLAG) -c $*.c 

# Separate rule to build common_sched.o as we need to ensure the correct 
# DEFAULT_DELAY_TIME is used. 
common_sched.o:	
	${CC} ${CFLAGS_CRAY} $(SCHEDFLAGS) $(OMPFLAG) -o common_sched.o -c common.c

schedbench: $(SCHEDOBJS)
	$(CC) -o schedbench  $(LDFLAGS) $(SCHEDOBJS) $(CLOCKOBJS) $(LIBS) -lm 

# Multiple header files due to multiple array sizes, makes header file arraybench_*.h
arraybench_$(IDA).h: arraybench.h
	$(CPP) -DIDA=$(IDA) $(OMPFLAG) -P arraybench.h -o $@

# Multiple object files due to multiple array sizes, makes object file arraybench_*.o
arraybench_$(IDA).o: arraybench_$(IDA).h arraybench.c
	$(CC) $(CFLAGS) -DIDA=$(IDA) $(OMPFLAG) arraybench.c -c -o $@

# Multiple executables due to multiple array sizes, makes exe file arraybench_*
arraybench_$(IDA): $(ARRAYOBJS) $(CLOCKOBJS) arraybench.c
	$(CC) $(LDFLAGS) $(ARRAYOBJS) $(CLOCKOBJS) $(LIBS) -lm -o $@ 

taskbench: $(TASKOBJS)
	$(CC) -o taskbench $(LDFLAGS) $(OMPFLAG) $(TASKOBJS) $(CLOCKOBJS) $(LIBS) -lm 

clean: 
	-rm *.o syncbench schedbench arraybench_* taskbench

clean-all: clean 	
	-rm OpenMPBench.* *.all


