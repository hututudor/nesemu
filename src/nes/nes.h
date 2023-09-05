#pragma once

#include "../mappers/mapper.h"
#include "../memory/bus.h"
#include "../rom/rom.h"

typedef struct {
  bus_t* bus;
  mapper_t* mapper;
} nes_t;

nes_t* nes_create(rom_t* rom);
void nes_destroy(nes_t* nes);