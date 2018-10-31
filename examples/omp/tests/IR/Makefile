CC=~/openUH/bin/uhcc

all: parallel for nested-parallel task barrier single master

parallel:
	$(CC) ../omp-par.c -fopenmp -CLIST:emit_nested_pu:before_cg

nested-parallel:
	$(CC) ../omp-nested-par.c -fopenmp -CLIST:emit_nested_pu:before_cg

for:
	$(CC) ../omp-for.c -fopenmp -CLIST:emit_nested_pu:before_cg 

for-dynamic:
	$(CC) ../omp-for-dynamic.c -fopenmp -CLIST:emit_nested_pu:before_cg 

task:
	$(CC) ../omp-task.c -fopenmp -CLIST:emit_nested_pu:before_cg 

barrier:
	$(CC) ../omp-barrier.c -fopenmp -CLIST:emit_nested_pu:before_cg 

single:
	$(CC) ../omp-single.c -fopenmp -CLIST:emit_nested_pu:before_cg 

master:
	$(CC) ../omp-master.c -fopenmp -CLIST:emit_nested_pu:before_cg 

thrdprvt:
	$(CC) ../omp-thrdprvt.c -fopenmp -CLIST:emit_nested_pu:before_cg -Wb,-trlow,-tslow 

lu:
	$(CC) ../omp-lu.c -fopenmp -CLIST:emit_nested_pu:before_cg -Wb,-trlow,-tslow 
