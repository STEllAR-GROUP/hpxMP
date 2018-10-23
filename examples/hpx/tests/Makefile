all: lu-hpx lu-hpx-dataflow

tied-test: omp_queue_test.cpp
	g++ omp_queue_test.cpp -o tied-test `pkg-config --cflags --libs hpx_application`

target: target_test.cpp
	g++ target_test.cpp -o target `pkg-config --cflags --libs hpx_application`

1d_stencil:
	clang++ -fopenmp 1d_stencil_3_omp_task.cpp -o omp4 `pkg-config --cflags --libs hpx_application`

lu-hpx: hpx-lu.cpp
	g++  hpx-lu.cpp -o hpx-lu `pkg-config --cflags --libs hpx_application`

lu-hpx-dataflow: lu-hpx-dataflow.cpp lu-utils.o lu-local.o
	g++ -o lu-df lu-hpx-dataflow.cpp lu-utils.o lu-local.o `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=lu-df

lu-utils.o: lu-utils.cpp
	g++ -o lu-utils.o -c lu-utils.cpp `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=lu-utils.o

lu-local.o: lu-local.cpp
	g++ -o lu-local.o -c lu-local.cpp `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=lu-local.o

exec: exec_test.cpp
	g++ -g exec_test.cpp -o test-exec `pkg-config --cflags --libs hpx_application`

exec-ptr: exec_ptr_test.cpp
	g++ -g exec_ptr_test.cpp -o test-exec-ptr `pkg-config --cflags --libs hpx_application`

os_count: os_count_test.cpp
	g++ -g os_count_test.cpp -o os_count `pkg-config --cflags --libs hpx_application`

fib: fibonacci.cpp
	g++ -g fibonacci.cpp -o hpx-fib `pkg-config --cflags --libs hpx_application`


barrier: barrier_test.cpp
	g++ -g barrier_test.cpp -o hpx-barrier `pkg-config --cflags --libs hpx_application`

micro: micro-bench.cpp
	g++  micro-bench.cpp -o micro `pkg-config --cflags --libs hpx_application`
