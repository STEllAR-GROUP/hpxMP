CC=g++
OPT=-O1

default: mmult-df

strass-df: strass-df.cpp block.o
	$(CC) $(OPT) -fopenmp --std=c++11 strass-df.cpp block.o -o strass-df

mmult-df: mmult-df.cpp block.o
	$(CC) $(OPT) -fopenmp --std=c++11 mmult-df.cpp block.o -o mmult-df

block.o: block.h block.cpp
	$(CC) $(OPT) -fopenmp -c block.cpp -std=c++11 -o block.o

mkl: mmult-mkl.cpp
	$(CC) $(OPT) mmult-mkl.cpp -std=c++11 -o mmult-mkl -liomp5 -lpthread -ldl -lm -mkl


clean:
	rm -f *.o
	rm -f strass-df
	rm -f mmult-df
