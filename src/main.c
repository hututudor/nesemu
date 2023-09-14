#include <stdio.h>
#include <stdlib.h>

#include "mappers/mapper.h"
#include "nes/nes.h"
#include "peripherals/screen.h"
#include "rom/rom.h"
#include "utils/file.h"

void usage(char* program_name);

int main(int argv, char** argc) {
  if (argv < 2) {
    usage(argc[0]);
    return 0;
  }

  char* rom_path = argc[1];
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

  screen_clear();

  while (true) {
    // cpu_debug_print_state(nes->cpu);
    // printf("\n");
    nes_clock(nes);
  }

  nes_destroy(nes);

  return 0;
}

void usage(char* program_name) {
  printf("Usage: %s <ROM PATH>\n", program_name);
}