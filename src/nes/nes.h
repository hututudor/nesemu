#pragma once

#include "../cpu/cpu.h"
#include "../mappers/mapper.h"
#include "../memory/bus.h"
#include "../rom/rom.h"

typedef struct {
  bus_t* bus;
  mapper_t* mapper;
  cpu_t* cpu;
} nes_t;

nes_t* nes_create(rom_t* rom);
void nes_destroy(nes_t* nes);