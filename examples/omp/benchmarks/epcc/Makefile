CC = icpc
CFLAGS = -O3 -fopenmp -std=c++11

all: taskbench 

common.o: common.cpp
	${CC} ${CFLAGS} -c common.cpp

taskbench: common.o taskbench.cpp
	$(CC) ${CFLAGS} common.o -o taskbench taskbench.cpp 

clean: 
	-rm -rf *.o taskbench

