#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../memory/bus.h"
#include "../utils/types.h"

typedef struct ppu_t {
  s16 scan_line;
  s16 cycle;

  struct {
    u8 base_nametable_address : 2;
    u8 vram_increment : 1;
    u8 sprite_pattern_address : 1;
    u8 background_pattern_address : 1;
    u8 sprite_size : 1;
    u8 master_slave_select : 1;
    u8 generate_nmi : 1;
  } ctrl;

  struct {
    u8 grayscale : 1;
    u8 show_background_leftmost_8px : 1;
    u8 show_sprites_leftmost_8px : 1;
    u8 show_background : 1;
    u8 show_sprites : 1;
    u8 emphasize_red : 1;
    u8 emphasize_green : 1;
    u8 emphasize_blue : 1;
  } mask;

  struct {
    u8 sprite_overflow : 1;
    u8 sprite_0_hit : 1;
    u8 v_blank : 1;
  } status;

  u8 latch_low;
  u16 latch_address;
  u8 data_buffer;

  u8 scroll_x;
  u8 scroll_y;

  memory_t* nametable_memory;
  memory_t* palette_memory;

  bus_t* bus;
} ppu_t;

ppu_t* ppu_create();
void ppu_connect_bus(ppu_t* ppu, bus_t* bus);
void ppu_destroy(ppu_t* ppu);

u8 ppu_read8(ppu_t* ppu, u16 address);
void ppu_write8(ppu_t* ppu, u16 address, u8 value);

u8 ppu_internal_read8(ppu_t* ppu, u16 address);
void ppu_internal_write8(ppu_t* ppu, u16 address, u8 value);

void ppu_clock(ppu_t* ppu);