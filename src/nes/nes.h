#pragma once

#include "../cpu/cpu.h"
#include "../mappers/mapper.h"
#include "../memory/bus.h"
#include "../ppu/ppu.h"
#include "../rom/rom.h"

typedef struct {
  bus_t* bus;
  mapper_t* mapper;
  cpu_t* cpu;
  ppu_t* ppu;

  u64 cycles;
} nes_t;

nes_t* nes_create(rom_t* rom);
void nes_destroy(nes_t* nes);

void nes_clock(nes_t* nes);