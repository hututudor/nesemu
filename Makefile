CC = gcc
CFLAGS = -Wall -g

OUT = build/nesemu
MAIN = src/main.c
SRC = src/memory/memory.c src/memory/bus.c \
			src/nes/nes.c src/rom/rom.c \
			src/peripherals/screen.c \
			src/mappers/mapper.c src/mappers/mapper_0.c \
			src/cpu/cpu.c src/cpu/debug.c src/cpu/instructions.c src/cpu/instructions_table.c src/cpu/address_modes.c \
			src/ppu/ppu.c src/ppu/registers.c src/ppu/rendering.c\

TEST_OUT = build/test
TEST_MAIN = test/main.c
TEST_SRC = $(SRC)

ROM = roms/nestest.nes

all: build

run: build
	@mkdir -p frames
	$(OUT) $(ROM)
	convert frames/*.ppm frames/frame.png
	rm frames/*.ppm

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