CC = gcc
CFLAGS = -Wall -g

SRC = src/main.c
OUT = build/emulator

all: build

run: build
	$(OUT)

build: 
	@mkdir -p build
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -rf build

.PHONY: all run build clean