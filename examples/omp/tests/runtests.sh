#!/bin/bash
RT=$1
CC=$2
TEST_DIR=bin/$RT/$CC
logfile=logs/$CC-$RT.log
nthreads=4
preload=../../$RT

echo "running the $CC compiled code with the $RT runtime"
echo "output written to $logfile"

echo `date` > $logfile

test_num=0

for test in $TEST_DIR/*
do
    echo "running test #$test_num: $test" | tee -a $logfile
    OMP_NUM_THREADS=$nthreads LD_PRELOAD=$preload timeout 30s ./$test >>$logfile 2>&1
    retval=$?
    if [ $retval -eq 124 ]
    then 
        echo "ERROR: test ran for longer than 30 seconds" | tee -a $logfile
    elif [ $retval -ne 0 ]
    then echo "Error: test returned ($retval)" | tee -a $logfile
    fi
    test_num=$((test_num+1))
done

