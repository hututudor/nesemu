CC = gcc
CFLAGS = -Wall -g

OUT = build/nesemu
MAIN = src/main.c
SRC = src/memory/memory.c src/memory/bus.c \
			src/nes/nes.c

TEST_OUT = build/test
TEST_MAIN = test/main.c
TEST_SRC = $(SRC)

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