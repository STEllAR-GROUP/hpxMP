# Author: Deepak
# Quick script to run a test with different number of threads to test
# scalability

#!/bin/bash

TEST=$1

if [ "$2" ]; then
COMPILER=$2
else
COMPILER="openuh"
fi

if [ "$3" ]; then
VERSION=$3
else
VERSION="omp-tasks"
fi

for np in 1 2 4 8 16 24 32 40 48; do
    echo "./run-$TEST.sh -c $np -l $COMPILER -v $VERSION | tee $TEST/$TEST.$COMPILER-$np.out"
    ./run-$TEST.sh -c $np -l $COMPILER -v $VERSION | tee $TEST/$TEST.$COMPILER-$np.out
done 
