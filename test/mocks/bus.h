#pragma once

#include "../../src/mappers/mapper.h"
#include "../../src/memory/bus.h"
#include "../../src/rom/rom.h"
#include "../../src/utils/file.h"

bus_t* mock_bus() {
  u8* rom_data = read_entire_file("test/roms/mock.nes");
  rom_t* rom = rom_load(rom_data);

  mapper_t* mapper = mapper_create(rom);

  return bus_create(mapper);
}