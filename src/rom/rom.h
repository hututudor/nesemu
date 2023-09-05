#pragma once

#include "../utils/types.h"

#define MIRRORING_HORIZONTAL false
#define MIRRORING_VERTICAL true

#define TV_SYSTEM_NTSC false
#define TV_SYSTEM_PAL true

typedef struct {
  u8 prg_rom_size;
  u8 chr_rom_size;
  u8 prg_ram_size;

  u8 mapper_number;

  bool mirroring;
  bool four_screen_mirroring;
  bool has_persistent_memory;
  bool has_trainer;

  bool vs_unisystem;
  bool is_nes_2;

  bool tv_system;
} rom_header_t;

typedef struct {
  rom_header_t header;
  u8* prg_rom;
  u8* chr_rom;
} rom_t;

rom_t* rom_load(u8* data);
bool rom_is_valid(u8* data);

void rom_debug_print(rom_t* rom);