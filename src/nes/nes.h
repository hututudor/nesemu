#pragma once

#include "../memory/bus.h"

typedef struct {
  bus_t* bus;
} nes_t;

nes_t* nes_create();
void nes_destroy(nes_t* nes);