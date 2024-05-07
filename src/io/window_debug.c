#include "window_debug.h"

#include "../peripherals/screen.h"

static u8 palettes_index = 0;

void debug_screen_init() {}

void debug_screen_destroy() {}

void debug_screen_process_event(SDL_Event* e) {
  if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {
      case SDLK_LEFTBRACKET:
        palettes_index = (u8)(palettes_index - 1) % 8;
        break;
      case SDLK_RIGHTBRACKET:
        palettes_index = (u8)(palettes_index + 1) % 8;
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
          color_t color = palette_colors[color_index];

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
  // SDL_Rect color_rect;

  // color_rect.x = x;
  // color_rect.y = y;
  // color_rect.w = 256;
  // color_rect.h = 240;

  // u8 color_index = ppu_internal_read8(
  //     nes->ppu, get_palette_real_address(0x3F00 + palettes_index + 4 + x %
  //     4));
  // color_t color = palette_colors[color_index];

  // SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  // SDL_RenderFillRect(renderer, &color_rect);
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

  if (nes->mapper->rom->header.mirroring == MIRRORING_HORIZONTAL) {
    nametable_addresses[2] = 0x2000;
    nametable_addresses[3] = 0x2400;
  } else if (nes->mapper->rom->header.mirroring == MIRRORING_VERTICAL) {
    nametable_addresses[1] = 0x2000;
    nametable_addresses[3] = 0x2400;
  }

  render_nametable(nes, nametable_addresses[0], UPSCALED_SCREEN_WIDTH + 32,
                   384);
  render_nametable(nes, nametable_addresses[1], UPSCALED_SCREEN_WIDTH + 288,
                   384);
  render_nametable(nes, nametable_addresses[2], UPSCALED_SCREEN_WIDTH + 32,
                   624);
  render_nametable(nes, nametable_addresses[3], UPSCALED_SCREEN_WIDTH + 288,
                   624);
}

void debug_screen_update(nes_t* nes) {
  SDL_SetRenderDrawColor(renderer, 156, 156, 156, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  render_pallettes(nes);
  render_pattern_tables(nes);
  render_nametables(nes);
}
