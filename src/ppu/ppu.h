#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../memory/bus.h"
#include "../utils/types.h"

typedef struct ppu_t {
  s32 scan_line;
  s32 cycle;
  u8 odd_frame;

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

  struct {
    u16 pattern_low;
    u16 pattern_high;
    u16 attribute_low;
    u16 attribute_high;

    u8 sprite_patten_low[8];
    u8 sprite_patten_high[8];
  } shifters;

  struct {
    u8 y;
    u8 id;
    u8 attribute;
    u8 x;
  } oam[64], scan_line_sprites[8];

  u8* oam_pointer;
  u8 oam_address;
  u8 scan_line_sprites_count;
  bool sprite_0_hit_possible;
  bool sprite_0_being_rendered;

  struct {
    u8 next_tile_background_index;
    u8 next_tile_background_attribute;
    u8 next_tile_background_lsb;
    u8 next_tile_background_msb;
  } internal;

  union {
    struct {
      u16 coarse_x : 5;
      u16 coarse_y : 5;
      u16 nametable_x : 1;
      u16 nametable_y : 1;
      u16 fine_y : 3;
      u16 unused : 1;
    };

    u16 reg;
  } vram_address, tram_address;

  u8 fine_x;

  u8 latch_high;
  u8 data_buffer;

  memory_t* nametable_memory;
  memory_t* palette_memory;

  bus_t* bus;
} ppu_t;

ppu_t* ppu_create();
void ppu_connect_bus(ppu_t* ppu, bus_t* bus);
void ppu_destroy(ppu_t* ppu);

void ppu_prepare_new_frame(ppu_t* ppu);
void ppu_prepare_render_state(ppu_t* ppu);
void ppu_render_pixel(ppu_t* ppu);

u8 ppu_read8(ppu_t* ppu, u16 address);
void ppu_write8(ppu_t* ppu, u16 address, u8 value);

u8 ppu_internal_read8(ppu_t* ppu, u16 address);
void ppu_internal_write8(ppu_t* ppu, u16 address, u8 value);

void ppu_clock(ppu_t* ppu);