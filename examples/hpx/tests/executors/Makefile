all: static

static: static_test.cpp
	g++ static_test.cpp -o static `pkg-config --cflags --libs hpx_application`
