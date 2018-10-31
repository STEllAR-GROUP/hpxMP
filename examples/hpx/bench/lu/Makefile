CC=g++

all: lu-hpx-dataflow

lu-hpx: hpx-lu.cpp
	$(CC) -O3 hpx-lu.cpp -o hpx-lu `pkg-config --cflags --libs hpx_application`

lu-hpx-dataflow: lu-hpx-dataflow.cpp lu-utils.o lu-local.o
	$(CC) -O3 -o lu-df lu-hpx-dataflow.cpp lu-utils.o lu-local.o `pkg-config --cflags --libs hpx_application` -DHPX_APPLICATION_NAME=lu-df

lu-utils.o: lu-utils.cpp
	$(CC) -O3 -o lu-utils.o -c lu-utils.cpp `pkg-config --cflags --libs hpx_application` -DHPX_APPLICATION_NAME=lu-utils.o

lu-local.o: lu-local.cpp
	$(CC) -O3 -o lu-local.o -c lu-local.cpp `pkg-config --cflags --libs hpx_application` -DHPX_APPLICATION_NAME=lu-local.o

clean:
	rm -rf *.o
	rm -rf lu-hpx
	rm -rf lu-hpx-dataflow
