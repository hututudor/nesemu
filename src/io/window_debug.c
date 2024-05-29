#include "window_debug.h"

#include "../peripherals/screen.h"

static u8 palettes_index = 0;
static bool show_scroll_marker = true;

void debug_screen_init() {}

void debug_screen_destroy() {}

static void debug_print_cpu_address8(nes_t* nes, u16 address) {
  printf("[cpu_address] %04X = %02X\n", address, bus_read8(nes->bus, address));
}

static void debug_print_cpu_address16(nes_t* nes, u16 address) {
  printf("[cpu_address] %04X = %04X\n", address, bus_read16(nes->bus, address));
}

static void debug_print_log(nes_t* nes) {
  for (int i = 0; i < 64; i++) {
    printf("SPRITE (%d, %d) ID = %02X ATTRIBUTE = %02X\n", nes->ppu->oam[i].x,
           nes->ppu->oam[i].y, nes->ppu->oam[i].id, nes->ppu->oam[i].attribute);
  }
}

void debug_screen_process_event(nes_t* nes, SDL_Event* e) {
  if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {
      case SDLK_LEFTBRACKET:
        palettes_index = (u8)(palettes_index - 1) % 8;
        break;
      case SDLK_RIGHTBRACKET:
        palettes_index = (u8)(palettes_index + 1) % 8;
        break;
      case SDLK_l:
        debug_print_log(nes);
        break;
      case SDLK_m:
        show_scroll_marker = !show_scroll_marker;
        break;
    }
  }
}

static u16 get_palette_real_address(u16 address) {
  if (address % 4 == 0) {
    address &= 0xFFFC;
  }

  if (address == 0x3F10) {
    return 0x3F00;
  }

  return address;
}

static void render_pallette(nes_t* nes, u16 address, u32 x, u32 y) {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      u8 color_index = ppu_internal_read8(
          nes->ppu, get_palette_real_address(address + row * 4 + col));
      color_t color = palette_colors[color_index];

      SDL_Rect color_rect;

      color_rect.x = x + col * 16;
      color_rect.y = y + row * 16;
      color_rect.w = 16;
      color_rect.h = 16;

      SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
      SDL_RenderFillRect(renderer, &color_rect);
    }
  }
}

static void render_current_pallette(nes_t* nes, u16 address, u32 x, u32 y) {
  for (int col = 0; col < 4; col++) {
    u8 color_index = ppu_internal_read8(nes->ppu, address + col);
    color_t color = palette_colors[color_index];

    SDL_Rect color_rect;

    color_rect.x = x + col * 16;
    color_rect.y = y;
    color_rect.w = 16;
    color_rect.h = 16;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &color_rect);
  }
}

static void render_pattern_table(nes_t* nes, u16 address, u32 x, u32 y) {
  for (int sprites_row = 0; sprites_row < 16; sprites_row++) {
    for (int sprites_col = 0; sprites_col < 16; sprites_col++) {
      for (int row = 0; row < 8; row++) {
        u8 pattern_low = ppu_internal_read8(
            nes->ppu, address + sprites_row * 256 + sprites_col * 16 + row);
        u8 pattern_high = ppu_internal_read8(
            nes->ppu, address + sprites_row * 256 + sprites_col * 16 + row + 8);

        for (int col = 0; col < 8; col++) {
          u8 palette_index = (((pattern_high >> (7 - col)) & 0x01) << 1) |
                             ((pattern_low >> (7 - col)) & 0x01);

          u8 color_index = ppu_internal_read8(
              nes->ppu, get_palette_real_address(0x3F00 + palettes_index * 4 +
                                                 palette_index));

          color_t color = screen_get_palette_color(color_index);

          SDL_Rect color_rect;

          color_rect.x = x + sprites_col * 16 + col * 2;
          color_rect.y = y + sprites_row * 16 + row * 2;
          color_rect.w = 2;
          color_rect.h = 2;

          SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
          SDL_RenderFillRect(renderer, &color_rect);
        }
      }
    }
  }
}

static void render_nametable(nes_t* nes, u16 address, u32 x, u32 y) {
  u16 base_pattern_table_address =
      nes->ppu->ctrl.background_pattern_address == 0 ? 0x0000 : 0x1000;

  for (int col = 0; col < 32; col++) {
    for (int row = 0; row < 30; row++) {
      u8 tile_index = ppu_internal_read8(nes->ppu, address + row * 32 + col);
      u8 attributes = ppu_internal_read8(
          nes->ppu, address + 0x03C0 + (row / 4) * 8 + (col / 4));

      u8 palette_attribute = 0;
      if (row % 4 < 2) {
        if (col % 4 < 2) {
          palette_attribute = (attributes >> 0) & 0x03;
        } else {
          palette_attribute = (attributes >> 2) & 0x03;
        }
      } else {
        if (col % 4 < 2) {
          palette_attribute = (attributes >> 4) & 0x03;
        } else {
          palette_attribute = (attributes >> 6) & 0x03;
        }
      }

      for (int tile_row = 0; tile_row < 8; tile_row++) {
        u8 pattern_low = ppu_internal_read8(
            nes->ppu, base_pattern_table_address + tile_index * 16 + tile_row);
        u8 pattern_high =
            ppu_internal_read8(nes->ppu, base_pattern_table_address +
                                             tile_index * 16 + tile_row + 8);

        for (int tile_col = 0; tile_col < 8; tile_col++) {
          u8 palette_index = (((pattern_high >> (7 - tile_col)) & 0x01) << 1) |
                             ((pattern_low >> (7 - tile_col)) & 0x01);

          u8 color_index = ppu_internal_read8(
              nes->ppu, get_palette_real_address(
                            0x3F00 + palette_attribute * 4 + palette_index));
          color_t color = palette_colors[color_index];

          SDL_Rect color_rect;

          color_rect.x = x + col * 8 + tile_col;
          color_rect.y = y + row * 8 + tile_row;
          color_rect.w = 1;
          color_rect.h = 1;

          SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
          SDL_RenderFillRect(renderer, &color_rect);
        }
      }
    }
  }
}

static void render_pallettes(nes_t* nes) {
  render_pallette(nes, 0x3F00, UPSCALED_SCREEN_WIDTH + 32, 8);
  render_pallette(nes, 0x3F10, UPSCALED_SCREEN_WIDTH + 128, 8);

  render_current_pallette(nes, 0x3F00 + palettes_index * 4,
                          UPSCALED_SCREEN_WIDTH + 32, 88);
}

static void render_pattern_tables(nes_t* nes) {
  render_pattern_table(nes, 0x0000, UPSCALED_SCREEN_WIDTH + 32, 112);
  render_pattern_table(nes, 0x1000, UPSCALED_SCREEN_WIDTH + 296, 112);
}

static void render_nametables(nes_t* nes) {
  u16 nametable_addresses[4] = {0x2000, 0x2400, 0x2800, 0x2C00};

  render_nametable(nes, nametable_addresses[0], UPSCALED_SCREEN_WIDTH + 32,
                   384);
  render_nametable(nes, nametable_addresses[1], UPSCALED_SCREEN_WIDTH + 288,
                   384);
  render_nametable(nes, nametable_addresses[2], UPSCALED_SCREEN_WIDTH + 32,
                   624);
  render_nametable(nes, nametable_addresses[3], UPSCALED_SCREEN_WIDTH + 288,
                   624);

  if (show_scroll_marker) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect scroll_marker_rect;

    scroll_marker_rect.x = UPSCALED_SCREEN_WIDTH + 32 +
                           (u16)nes->ppu->tram_address.nametable_x * 256 +
                           ((u16)nes->ppu->tram_address.coarse_x << 3) +
                           nes->ppu->fine_x;
    scroll_marker_rect.y = 384 + (u16)nes->ppu->tram_address.nametable_y * 240 +
                           ((u16)nes->ppu->tram_address.coarse_y << 3) +
                           nes->ppu->tram_address.fine_y;
    scroll_marker_rect.w = 256;
    scroll_marker_rect.h = 240;

    SDL_RenderDrawRect(renderer, &scroll_marker_rect);
  }
}

static void render_sprite(nes_t* nes, int i) {
  u8 x = nes->ppu->oam[i].x;
  u8 y = nes->ppu->oam[i].y;
  u8 id = nes->ppu->oam[i].id;
  u8 attribute = nes->ppu->oam[i].attribute;

  if (y >= 240) {
    return;
  }

  for (int row = 0; row < 8; row++) {
    if (y + row >= 240) {
      continue;
    }

    u8 pattern_low = ppu_internal_read8(nes->ppu, id * 16 + row);
    u8 pattern_high = ppu_internal_read8(nes->ppu, id * 16 + row + 8);

    for (int col = 0; col < 8; col++) {
      if ((u16)x + (u16)col >= 256) {
        continue;
      }

      if (nes->ppu->mask.show_sprites_leftmost_8px == 0 && x + col < 8) {
        continue;
      }

      bool is_x_flipped = attribute & 0x40;
      u8 pattern_byte = is_x_flipped ? col : 7 - col;

      u8 palette_index = (((pattern_high >> pattern_byte) & 0x01) << 1) |
                         ((pattern_low >> pattern_byte) & 0x01);

      u8 color_index = ppu_internal_read8(
          nes->ppu,
          get_palette_real_address(0x3F00 + ((attribute & 0x03) << 2) + 0x10 +
                                   palette_index));

      color_t color = palette_colors[color_index];

      SDL_Rect color_rect;

      color_rect.x = 32 + x + col;
      color_rect.y = UPSCALED_SCREEN_HEIGHT + 32 + y + row;
      color_rect.w = 1;
      color_rect.h = 1;

      SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
      SDL_RenderFillRect(renderer, &color_rect);
    }
  }
}

static void render_sprites(nes_t* nes) {
  u8 bg_color_index = ppu_internal_read8(nes->ppu, 0x3F00);
  color_t bg_color = palette_colors[bg_color_index];

  SDL_Rect bg_rect;

  bg_rect.x = 32;
  bg_rect.y = UPSCALED_SCREEN_HEIGHT + 32;
  bg_rect.w = 256;
  bg_rect.h = 240;

  SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, 256);
  SDL_RenderFillRect(renderer, &bg_rect);

  for (int i = 0; i < 64; i++) {
    render_sprite(nes, i);
  }
}

void debug_screen_update(nes_t* nes) {
  SDL_SetRenderDrawColor(renderer, 156, 156, 156, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  render_pallettes(nes);
  render_pattern_tables(nes);
  render_nametables(nes);
  render_sprites(nes);
}
