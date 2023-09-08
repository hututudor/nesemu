#include "nes.h"

#include <stdlib.h>

nes_t* nes_create(rom_t* rom) {
  nes_t* nes = (nes_t*)calloc(1, sizeof(nes_t));

  mapper_t* mapper = mapper_create(rom);

  nes->mapper = mapper;
  nes->bus = bus_create(mapper);
  nes->cpu = cpu_create(nes->bus);

  return nes;
}

void nes_destroy(nes_t* nes) {
  if (!nes) {
    return;
  }

  cpu_destroy(nes->cpu);
  bus_destroy(nes->bus);
  mapper_destroy(nes->mapper);
  free(nes);
}