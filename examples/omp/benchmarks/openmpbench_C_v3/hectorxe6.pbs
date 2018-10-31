#!/bin/bash --login
#PBS -N OpenMPBench
#PBS -l mppwidth=24
#PBS -l mppnppn=24
#PBS -l walltime=02:00:00
#PBS -A d23-epcc

# EXEDIR is the location of the executable files (on /home usually)
# RUNDIR is where the job will be executed from (this needs to be on /work on HECToR) 
# Paths for main XE6
export EXEDIR=/home/d23/d23/fiona/Projects/TEXT/dev/openmpbench_C_v3
export RUNDIR=/work/d23/d23/fiona/TEXT
# Paths for HECToR test system
#export EXEDIR=/work/z01/z01/fiona/TEXT/dev/openmpbench_C_v3
#export RUNDIR=/work/z01/z01/fiona/TEXT/openmpbench

# cd to RUNDIR
cd $RUNDIR

# Remove any old output (*bench.all) files before starting the run
rm *bench*.all

# Run the benchmarks 10 times so that reliable statistics can be obtained
for RUN in {1..10}
do

	echo "EPCC OpenMP microbenchmark,Run $RUN"
	
# Run schedbench and arraybench for common thread count across all machines
	export OMP_NUM_THREADS=12
	touch schedbench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/schedbench 2>&1 >> schedbench_common.all
	
	touch arraybench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_1  2>&1 >> arraybench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_3  2>&1 >> arraybench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_9  2>&1 >> arraybench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_27  2>&1 >> arraybench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_81  2>&1 >> arraybench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_243  2>&1 >> arraybench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_729  2>&1 >> arraybench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_2187  2>&1 >> arraybench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_6561  2>&1 >> arraybench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_19683  2>&1 >> arraybench_common.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_59049  2>&1 >> arraybench_common.all

# Also run for the maximum thread count on this (HECToR XE6) machine. 
# You will need to increase or decrease as appropriate for your system
	export OMP_NUM_THREADS=24

	touch schedbench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/schedbench 2>&1 >> schedbench.all
	
	touch arraybench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_1  2>&1 >> arraybench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_3  2>&1 >> arraybench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_9  2>&1 >> arraybench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_27  2>&1 >> arraybench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_81  2>&1 >> arraybench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_243  2>&1 >> arraybench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_729  2>&1 >> arraybench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_2187  2>&1 >> arraybench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_6561  2>&1 >> arraybench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_19683  2>&1 >> arraybench.all
	aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_59049  2>&1 >> arraybench.all
	
# Now run the syncbench, arraybench (with variable thread count) & taskbench
# benchmarks over a range of thread counts
	for OMP_NUM_THREADS in 1 2 4 8 12 16 20 24
	do
		touch syncbench.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/syncbench  2>&1 >> syncbench.all
		
		touch arraybench.vthreads.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_1  2>&1 >> arraybench.vthreads.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_3  2>&1 >> arraybench.vthreads.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_9  2>&1 >> arraybench.vthreads.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_27  2>&1 >> arraybench.vthreads.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_81  2>&1 >> arraybench.vthreads.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_243  2>&1 >> arraybench.vthreads.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_729  2>&1 >> arraybench.vthreads.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_2187  2>&1 >> arraybench.vthreads.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_6561  2>&1 >> arraybench.vthreads.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_19683  2>&1 >> arraybench.vthreads.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/arraybench_59049  2>&1 >> arraybench.vthreads.all
		
		touch taskbench.all
		aprun -n 1 -N 1 -d $OMP_NUM_THREADS $EXEDIR/taskbench  2>&1 >> taskbench.all
	
	done
	
done