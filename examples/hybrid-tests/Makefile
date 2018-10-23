CC=clang++
default: hello
	
hello: hello.cpp
	$(CC) -fopenmp hello.cpp -o hello `pkg-config --cflags --libs hpx_application`
