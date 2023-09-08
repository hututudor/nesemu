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

  address += 0x4020;
  address &= (mapper->rom->header.prg_rom_size * 0x4000 - 1);

  return mapper->rom->prg_rom[address];
}

u16 mapper_0_prg_read16(void* this, u16 address) {
  mapper_t* mapper = (mapper_t*)this;

  address += 0x4020;
  address &= (mapper->rom->header.prg_rom_size * 0x4000 - 1);

  return (mapper->rom->prg_rom[address + 1] << 8) |
         mapper->rom->prg_rom[address];
}