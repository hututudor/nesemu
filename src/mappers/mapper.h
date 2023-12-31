#pragma once

#include "../rom/rom.h"

#define MAPPERS_COUNT 256

typedef void (*create_mapper_t)(void*);
typedef void (*destroy_mapper_t)(void*);

typedef u8 (*prg_read8_mapper_t)(void*, u16);
typedef u16 (*prg_read16_mapper_t)(void*, u16);
typedef void (*prg_write8_mapper_t)(void*, u16, u8);
typedef void (*prg_write16_mapper_t)(void*, u16, u16);

typedef u8 (*chr_read8_mapper_t)(void*, u16);
typedef void (*chr_write8_mapper_t)(void*, u16, u8);

typedef struct {
  rom_t* rom;

  void* state;

  create_mapper_t create;
  destroy_mapper_t destroy;

  prg_read8_mapper_t prg_read8;
  prg_read16_mapper_t prg_read16;
  prg_write8_mapper_t prg_write8;
  prg_write16_mapper_t prg_write16;

  chr_read8_mapper_t chr_read8;
  chr_write8_mapper_t chr_write8;
} mapper_t;

typedef struct {
  create_mapper_t create;
  destroy_mapper_t destroy;

  prg_read8_mapper_t prg_read8;
  prg_read16_mapper_t prg_read16;
  prg_write8_mapper_t prg_write8;
  prg_write16_mapper_t prg_write16;

  chr_read8_mapper_t chr_read8;
  chr_write8_mapper_t chr_write8;
} mapper_config_t;

bool mapper_is_available(u8 mapper_number);

mapper_t* mapper_create(rom_t* rom);
void mapper_destroy(mapper_t* mapper);
