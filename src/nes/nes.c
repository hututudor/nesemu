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

static void nes_handle_dma_transfer(nes_t* nes) {
  if (nes->bus->dma_skip_odd_cycle) {
    if (nes->cycles % 2 == 1) {
      nes->bus->dma_skip_odd_cycle = false;
    }

    return;
  }

  if (nes->cycles % 2 == 0) {
    nes->bus->dma_data =
        bus_read8(nes->bus, nes->bus->dma_page << 8 | nes->bus->dma_address);
    return;
  }

  nes->ppu->oam_pointer[nes->bus->dma_address] = nes->bus->dma_data;
  nes->bus->dma_address++;

  if (nes->bus->dma_address == 0x00) {
    nes->bus->dma_transfer = false;
    nes->bus->dma_skip_odd_cycle = true;
  }
}

void nes_clock(nes_t* nes) {
  // TODO: any performance impact for updating controller on every clock?
  controller_update(nes->controller_1);
  controller_update(nes->controller_2);

  ppu_clock(nes->ppu);

  if (nes->cycles % 3 == 0) {
    if (nes->bus->dma_transfer) {
      nes_handle_dma_transfer(nes);
    } else {
      cpu_clock(nes->cpu);
    }
  }

  nes->cycles++;
}