#include "nes.h"

#include <stdlib.h>

nes_t* nes_create(rom_t* rom) {
  nes_t* nes = (nes_t*)calloc(1, sizeof(nes_t));

  mapper_t* mapper = mapper_create(rom);

  nes->mapper = mapper;
  nes->ppu = ppu_create(nes->bus);
  nes->bus = bus_create(mapper, nes->ppu);
  nes->cpu = cpu_create(nes->bus);

  ppu_connect_bus(nes->ppu, nes->bus);

  nes->cycles = 0;

  return nes;
}

void nes_destroy(nes_t* nes) {
  if (!nes) {
    return;
  }

  ppu_destroy(nes->ppu);
  cpu_destroy(nes->cpu);
  bus_destroy(nes->bus);
  mapper_destroy(nes->mapper);
  free(nes);
}

void nes_clock(nes_t* nes) {
  if (nes->cycles % 3 == 0) {
    cpu_clock(nes->cpu);
  }

  ppu_clock(nes->ppu);

  nes->cycles++;
}