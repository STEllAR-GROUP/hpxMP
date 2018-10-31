
CC=g++

default: jacobi

jacobi: jacobi_hpx.o jacobi.cpp jacobi.hpp
	$(CC) -o jacobi jacobi.cpp jacobi_hpx.o --std=c++11 `pkg-config --cflags --libs hpx_application` -DHPX_APPLICATION_NAME=jacobi

jacobi_hpx.o: jacobi_hpx.cpp jacobi.hpp
	$(CC) -c -o jacobi_hpx.o jacobi_hpx.cpp --std=c++11 `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=jacobi_hpx.o 

jacobi-omp: jacobi.cpp jacobi.hpp jacobi_omp.cpp
	$(CC) -g -fopenmp -o jacobi-omp jacobi_omp.cpp -std=c++11  `pkg-config --cflags --libs hpx_application` -DHPX_APPLICATION_NAME=jacobi-omp



clean:
	rm -rf *.o
	rm -rf jacobi

