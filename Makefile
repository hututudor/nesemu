SDL_FLAGS := $(shell sdl2-config --cflags --libs)

CC = gcc
CFLAGS = -Wall -g
LINKER_FLAGS = $(SDL_FLAGS)

OUT = build/nesemu
MAIN = src/main.c
SRC = src/memory/memory.c src/memory/bus.c \
			src/nes/nes.c src/rom/rom.c \
			src/peripherals/screen.c src/peripherals/controller.c \
			src/mappers/mapper.c src/mappers/mapper_0.c \
			src/cpu/cpu.c src/cpu/debug.c src/cpu/instructions.c src/cpu/instructions_table.c src/cpu/address_modes.c \
			src/ppu/ppu.c src/ppu/registers.c src/ppu/rendering.c\
			src/io/window.c src/io/window_debug.c src/io/input.c  src/io/file_dialog.c \
			libs/tinyfiledialogs/tinyfiledialogs.c

TEST_OUT = build/test
TEST_MAIN = test/main.c
TEST_SRC = $(SRC)

# ROM = roms/nestest.nes
# ROM = roms/hello.nes
# ROM = roms/test/cpu_dummy_reads/cpu_dummy_reads.nes
# ROM = roms/ice_climber.nes
# ROM = roms/super_mario_bros.nes
# ROM = roms/donkey.nes
# ROM = roms/tetris_mapper0.nes
# ROM = roms/mario.nes

all: build

run: build
	@mkdir -p frames
	$(OUT) $(ROM)

build: 
	@mkdir -p build
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(MAIN) $(LINKER_FLAGS)

test: test_build
	$(TEST_OUT)

test_build:
	@mkdir -p build
	$(CC) $(CFLAGS) -o $(TEST_OUT) $(TEST_SRC) $(TEST_MAIN) $(LINKER_FLAGS)

debug: build
	gdb -ex=run --args $(OUT) $(ROM)

clean:
	rm -rf build

.PHONY: all run build test test_build clean