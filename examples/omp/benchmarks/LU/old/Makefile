CC=clang
all: lu-dep lu-task

timed: lu-dep-timed

lu-dep: lu-depends.c
	$(CC) -O3 -fopenmp -o lu-dep lu-depends.c

lu-dep-timed: lu-dep-timed.c
	$(CC) -O3 -fopenmp -o lu-dep-timed lu-dep-timed.c

lu-task: omp-task.c
	$(CC) -O3 -fopenmp -o lu-task omp-task.c
