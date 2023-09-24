#pragma once

#include "../../src/cpu/cpu.h"
#include "../../src/mappers/mapper.h"
#include "../../src/memory/bus.h"
#include "../../src/ppu/ppu.h"
#include "../../src/rom/rom.h"
#include "../../src/utils/file.h"

bus_t* mock_bus() {
  u8* rom_data = read_entire_file("test/roms/mock.nes");
  rom_t* rom = rom_load(rom_data);

  mapper_t* mapper = mapper_create(rom);
  ppu_t* ppu = ppu_create();
  cpu_t* cpu = cpu_create();

  bus_t* bus = bus_create(mapper, cpu, ppu);

  ppu_connect_bus(ppu, bus);
  cpu_connect_bus(cpu, bus);

  return bus;
}