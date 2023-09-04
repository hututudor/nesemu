#include "nes.h"

#include <stdlib.h>

nes_t* nes_create() {
  nes_t* nes = (nes_t*)calloc(1, sizeof(nes_t));

  nes->bus = bus_create();

  return nes;
}

void nes_destroy(nes_t* nes) {
  if (!nes) {
    return;
  }

  bus_destroy(nes->bus);
  free(nes);
}