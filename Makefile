CC = gcc
CFLAGS = -Wall -Wextra -g

ALL_SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard *_test.c)
SRCS = $(filter-out $(TEST_SRCS), $(ALL_SRCS))
OBJS = $(patsubst %.c, build/%.o, $(SRCS))

TEST_EXECUTABLES = $(patsubst %_test.c, build/%_test, $(TEST_SRCS))

INC_DIRS = -I.

.PHONY: all clean

all: build $(OBJS) $(TEST_EXECUTABLES)

build:
	mkdir -p build

build/%_test: %_test.c $(OBJS)
	$(CC) $(CFLAGS) $(INC_DIRS) -o $@ $^

build/%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIRS) -c -o $@ $<

clean:
	rm -rf build
