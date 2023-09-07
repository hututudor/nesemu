#pragma once

#include "../rom/rom.h"

#define MAPPERS_COUNT 256

typedef void (*create_mapper_t)(void*);
typedef void (*destroy_mapper_t)(void*);
typedef u8 (*prg_read8_mapper_t)(void*, u16);
typedef u16 (*prg_read16_mapper_t)(void*, u16);

typedef struct {
  rom_t* rom;

  void* state;

  create_mapper_t create;
  destroy_mapper_t destroy;
  prg_read8_mapper_t prg_read8;
  prg_read16_mapper_t prg_read16;
} mapper_t;

typedef struct {
  create_mapper_t create;
  destroy_mapper_t destroy;
  prg_read8_mapper_t prg_read8;
  prg_read16_mapper_t prg_read16;
} mapper_config_t;

bool mapper_is_available(u8 mapper_number);

mapper_t* mapper_create(rom_t* rom);
void mapper_destroy(mapper_t* mapper);
