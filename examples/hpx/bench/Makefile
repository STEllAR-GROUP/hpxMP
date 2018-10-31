CC=g++

all: micro taskbench


mmult: hpx-mmult.cpp matrix_block.h
	$(CC) -g hpx-mmult.cpp -o hpx-mmult `pkg-config --cflags --libs hpx_application`

1d_stencil:
	$(CC) -fopenmp 1d_stencil_3_omp_task.cpp -o omp4 `pkg-config --cflags --libs hpx_application`

lu-hpx: hpx-lu.cpp
	$(CC)  hpx-lu.cpp -o hpx-lu `pkg-config --cflags --libs hpx_application`

lu-hpx-dataflow: lu-hpx-dataflow.cpp lu-utils.o lu-local.o
	$(CC) -o lu-df lu-hpx-dataflow.cpp lu-utils.o lu-local.o `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=lu-df

lu-utils.o: lu-utils.cpp
	$(CC) -o lu-utils.o -c lu-utils.cpp `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=lu-utils.o

lu-local.o: lu-local.cpp
	$(CC) -o lu-local.o -c lu-local.cpp `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=lu-local.o

fib: fibonacci.cpp
	$(CC) -g fibonacci.cpp -o hpx-fib `pkg-config --cflags --libs hpx_application`

micro: micro-bench.cpp
	$(CC)  micro-bench.cpp -o micro `pkg-config --cflags --libs hpx_application`

taskbench: hpx-taskbench.cpp
	$(CC)  hpx-taskbench.cpp -o taskbench `pkg-config --cflags --libs hpx_application`

task-wait: hpx-wait-bench.cpp
	$(CC)  hpx-wait-bench.cpp -o task-wait `pkg-config --cflags --libs hpx_application`

startup: hpx-startup.cpp
	$(CC)  hpx-startup.cpp -o startup `pkg-config --cflags --libs hpx_application`

spawn: task-spawn.cpp
	$(CC) task-spawn.cpp -o spawn `pkg-config --cflags --libs hpx_application`

chain: task-chain.cpp
	$(CC) -O3 task-chain.cpp -o chain `pkg-config --cflags --libs hpx_application`

clean:
	rm -rf *.o micro taskbench
