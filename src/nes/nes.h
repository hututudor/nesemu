#pragma once

#include "../cpu/cpu.h"
#include "../mappers/mapper.h"
#include "../memory/bus.h"
#include "../peripherals/controller.h"
#include "../ppu/ppu.h"
#include "../rom/rom.h"

typedef struct {
  bus_t* bus;
  mapper_t* mapper;
  cpu_t* cpu;
  ppu_t* ppu;

  controller_t* controller_1;
  controller_t* controller_2;

  u64 cycles;
} nes_t;

nes_t* nes_create(rom_t* rom);
void nes_destroy(nes_t* nes);

void nes_clock(nes_t* nes);