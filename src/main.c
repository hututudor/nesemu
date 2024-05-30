#include <stdio.h>
#include <stdlib.h>

#include "io/file_dialog.h"
#include "io/input.h"
#include "io/window.h"
#include "mappers/mapper.h"
#include "nes/nes.h"
#include "peripherals/screen.h"
#include "rom/rom.h"
#include "utils/file.h"

void usage(char* program_name);

#define CPU_CYCLES_PER_FRAME 29780
#define PPU_CYCLES_PER_FRAME (CPU_CYCLES_PER_FRAME * 3)

int main(int argc, char** argv) {
  if (argc >= 2 && !strcmp(argv[1], "-h")) {
    usage(argv[0]);
  }

  char* rom_path = argc >= 2 ? argv[1] : (char*)file_dialog_pick();
  u8* rom_data = read_entire_file(rom_path);

  if (!rom_data) {
    perror("Could not read file\n");
    return 0;
  }

  if (!rom_is_valid(rom_data)) {
    perror("Provided file is not a NES rom\n");
    return 0;
  }

  rom_t* rom = rom_load(rom_data);
  free(rom_data);

  rom_debug_print(rom);
  printf("\n");

  if (!mapper_is_available(rom->header.mapper_number)) {
    printf("Provided ROM has a mapper that is not yet implemented: %d\n",
           rom->header.mapper_number);
    return 0;
  }

  nes_t* nes = nes_create(rom);

  window_init();

  while (window_is_running) {
    window_update(nes);
    keys_update();

    for (int i = 0; i < PPU_CYCLES_PER_FRAME; i++) {
      nes_clock(nes);
    }
  }

  nes_destroy(nes);
  window_destroy();

  return 0;
}

void usage(char* program_name) {
  printf("Usage: %s <ROM PATH>\n", program_name);
}