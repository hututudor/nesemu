#include "../../src/mappers/mapper.h"
#include "../../src/memory/bus.h"
#include "../../src/rom/rom.h"
#include "../../src/utils/file.h"
#include "../framework.h"

TEST_BEGIN(should_parse_rom_correctly) {
  u8* rom_data = read_entire_file("test/roms/mock.nes");
  rom_t* rom = rom_load(rom_data);

  ASSERT(rom->header.mapper_number == 0);
  ASSERT(rom->header.mirroring == MIRRORING_VERTICAL);
  ASSERT(rom->header.four_screen_mirroring == false);
  ASSERT(rom->header.has_persistent_memory == false);
  ASSERT(rom->header.has_trainer == false);
  ASSERT(rom->header.tv_system == TV_SYSTEM_NTSC);

  ASSERT(rom->header.vs_unisystem == false);
  ASSERT(rom->header.is_nes_2 == false);

  ASSERT(rom->header.prg_rom_size == 1);
  ASSERT(rom->header.chr_rom_size == 1);
  ASSERT(rom->header.prg_ram_size == 0);

  ASSERT(rom->prg_rom[0] == 0x78);
  ASSERT(rom->chr_rom[0] == 0x03);
}
TEST_END

SUITE_BEGIN(rom)
SUITE_ADD(should_parse_rom_correctly)
SUITE_END