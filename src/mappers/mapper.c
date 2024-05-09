#include "mapper.h"

#include <stdlib.h>

#include "../utils/assert.h"

extern mapper_config_t mapper_0;

mapper_config_t* mappers[MAPPERS_COUNT] = {&mapper_0, NULL, NULL, &mapper_0};

bool mapper_is_available(u8 mapper_number) {
  return mappers[mapper_number] != NULL;
}

mapper_t* mapper_create(rom_t* rom) {
  u8 mapper_number = rom->header.mapper_number;

  if (!mapper_is_available(mapper_number)) {
    return NULL;
  }

  mapper_t* mapper = (mapper_t*)calloc(1, sizeof(mapper_t));
  mapper->rom = rom;

  mapper_config_t* mapper_config = mappers[mapper_number];
  mapper->create = mapper_config->create;
  mapper->destroy = mapper_config->destroy;

  mapper->prg_read8 = mapper_config->prg_read8;
  mapper->prg_read16 = mapper_config->prg_read16;
  mapper->prg_write8 = mapper_config->prg_write8;
  mapper->prg_write16 = mapper_config->prg_write16;

  mapper->chr_read8 = mapper_config->chr_read8;
  mapper->chr_write8 = mapper_config->chr_write8;

  mapper->create(mapper);

  return mapper;
}

void mapper_destroy(mapper_t* mapper) {
  if (!mapper) {
    return;
  }

  mapper->destroy(mapper);

  free(mapper);
}