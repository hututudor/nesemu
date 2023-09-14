#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../memory/bus.h"
#include "../utils/types.h"

typedef struct {
  s16 scan_line;
  s16 cycle;

  bus_t* bus;
} ppu_t;

ppu_t* ppu_create(bus_t* bus);
void ppu_destroy(ppu_t* ppu);

void ppu_clock(ppu_t* ppu);