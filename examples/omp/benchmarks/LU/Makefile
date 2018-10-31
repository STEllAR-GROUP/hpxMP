CC=g++
OPT=-O1

default: lu-dataflow

lu-dataflow: lu-dataflow.cpp lu-local.o lu-utils.o
	$(CC) $(OPT) -fopenmp --std=c++11 lu-dataflow.cpp lu-local.o lu-utils.o -o lu-dataflow

serial-lu: lu-dataflow.cpp lu-local.o lu-utils.o
	$(CC) $(OPT) --std=c++11 lu-dataflow.cpp lu-local.o lu-utils.o -o serial-lu

lu-local.o: lu-local.h lu-local.cpp
	$(CC) $(OPT) -fopenmp -c lu-local.cpp -std=c++11 -o lu-local.o

lu-utils.o: lu-utils.h lu-utils.cpp
	$(CC) $(OPT) -fopenmp -c lu-utils.cpp -std=c++11 -o lu-utils.o

clean:
	rm -f *.o
	rm -f serial-lu
	rm -f lu-dataflow
