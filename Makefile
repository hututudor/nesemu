CC = gcc
CFLAGS = -Wall -g

OUT = build/nesemu
SRC = src/main.c \
			src/memory/memory.c src/memory/bus.c 

all: build

run: build
	$(OUT)

build: 
	@mkdir -p build
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -rf build

.PHONY: all run build clean