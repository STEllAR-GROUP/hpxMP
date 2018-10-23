#CC=~/openUH/bin/opencc
CC=icc
CFLAGS= -fopenmp -lpthread
#CFLAGS= -openmp -DUSING_PAPI -DNO_NATIVE
PAR=
OPT= -O0 -g
PAPI= #-lpapi
UTIL= util.o

all: mm_funcs.o strass.o benchmark.o util.o  $(UTIL)
	$(CC) $(OPT) benchmark.o mm_funcs.o strass.o $(UTIL) -o bench  $(CFLAGS) $(PAR) $(PAPI) 
	cp bench ../run

mm_funcs.o: mm_funcs.c
	$(CC) $(OPT) -c mm_funcs.c $(CFLAGS) $(PAR) $(PAPI)

strass.o: strass.c
	$(CC) $(OPT) -c strass.c $(CFLAGS) $(PAR) $(PAPI)

benchmark.o: benchmark.c
	$(CC) $(OPT) -c benchmark.c $(CFLAGS) $(PAR) $(PAPI)

util.o: util.c
	$(CC) $(OPT) -c util.c $(CFLAGS)


clean:
	rm *.o
	rm bench
	rm ../run
