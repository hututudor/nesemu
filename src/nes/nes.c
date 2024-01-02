#include "nes.h"

#include <stdlib.h>

nes_t* nes_create(rom_t* rom) {
  nes_t* nes = (nes_t*)calloc(1, sizeof(nes_t));

  mapper_t* mapper = mapper_create(rom);

  nes->mapper = mapper;
  nes->ppu = ppu_create();
  nes->cpu = cpu_create();
  nes->controller_1 = controller_create();
  nes->controller_2 = controller_create();

  nes->bus = bus_create(mapper, nes->cpu, nes->ppu, nes->controller_1,
                        nes->controller_2);

  ppu_connect_bus(nes->ppu, nes->bus);
  cpu_connect_bus(nes->cpu, nes->bus);

  nes->cycles = 0;

  return nes;
}

void nes_destroy(nes_t* nes) {
  if (!nes) {
    return;
  }

  controller_destroy(nes->controller_1);
  controller_destroy(nes->controller_2);

  ppu_destroy(nes->ppu);
  cpu_destroy(nes->cpu);
  bus_destroy(nes->bus);
  mapper_destroy(nes->mapper);
  free(nes);
}

void nes_clock(nes_t* nes) {
  // TODO: any performance impact for updating controller on every clock?
  controller_update(nes->controller_1);
  controller_update(nes->controller_2);

  if (nes->cycles % 3 == 0) {
    cpu_clock(nes->cpu);
  }

  ppu_clock(nes->ppu);

  nes->cycles++;
}