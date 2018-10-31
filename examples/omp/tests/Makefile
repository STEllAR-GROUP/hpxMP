CC = clang
RT = libiomp5.so

CFLAGS = -g -fopenmp

SRCS = $(wildcard src/*.c)

TESTS = $(patsubst src/%.c,bin/$(RT)/$(CC)/%,$(SRCS))

default: $(TESTS)
	sh runtests.sh $(RT) $(CC)

bin/$(RT)/$(CC)/%: src/%.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean clean-all clean-logs
clean:
	rm -rf bin/$(RT)/$(CC)/*

clean-all: clean-logs
	rm  bin/*/*/*

clean-logs:
	rm logs/*.log
