CC=clang++

all: spawn

chain: task-chain.cpp
	$(CC) -O3 -fopenmp --std=c++11 task-chain.cpp -o chain 

spawn: task-spawn.cpp
	$(CC) -O3 -fopenmp --std=c++11 task-spawn.cpp -o spawn
