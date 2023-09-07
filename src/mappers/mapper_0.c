#include <stdio.h>

#include "mapper.h"

void mapper_0_create(void* this);
void mapper_0_destroy(void* this);
u8 mapper_0_prg_read8(void* this, u16 address);
u16 mapper_0_prg_read16(void* this, u16 address);

mapper_config_t mapper_0 = {.create = mapper_0_create,
                            .destroy = mapper_0_destroy,
                            .prg_read8 = mapper_0_prg_read8,
                            .prg_read16 = mapper_0_prg_read16};

void mapper_0_create(void* mapper) {}
void mapper_0_destroy(void* mapper) {}

u8 mapper_0_prg_read8(void* this, u16 address) {
  mapper_t* mapper = (mapper_t*)this;

  u16 prg_size = mapper->rom->header.prg_rom_size * 0x4000;
  if (address >= prg_size) {
    printf("[ERROR][MAPPER] Read from unknown address %04X\n", address);
    return 0;
  }

  return mapper->rom->prg_rom[address];
}

u16 mapper_0_prg_read16(void* this, u16 address) {
  mapper_t* mapper = (mapper_t*)this;

  fflush(stdout);

  u16 prg_size = mapper->rom->header.prg_rom_size * 0x4000;
  if ((address + 1) >= prg_size) {
    printf("[ERROR][MAPPER] Read from unknown address %04X\n", address);
    return 0;
  }

  return (mapper->rom->prg_rom[address + 1] << 8) |
         mapper->rom->prg_rom[address];
}