CC = gcc
CFLAGS = -Wall -g

OUT = build/nesemu
SRC = src/memory/memory.c src/memory/bus.c 
MAIN = src/main.c

TEST_OUT = build/test
TEST_SRC = $(SRC)
TEST_MAIN = test/main.c

all: build

run: build
	$(OUT)

build: 
	@mkdir -p build
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(MAIN)

test: test_build
	$(TEST_OUT)

test_build:
	@mkdir -p build
	$(CC) $(CFLAGS) -o $(TEST_OUT) $(TEST_SRC) $(TEST_MAIN)

clean:
	rm -rf build

.PHONY: all run build test test_build clean