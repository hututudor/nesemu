#include <memory.h>
#include <stdlib.h>

#include "../peripherals/screen.h"
#include "ppu.h"

static u8 sprite_flip_byte(u8 byte) {
  byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
  byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
  byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;
  return byte;
}

static void ppu_handle_sprite_0_hit(ppu_t* ppu) {
  if (!ppu->sprite_0_hit_possible || !ppu->sprite_0_being_rendered) {
    return;
  }

  if (ppu->mask.show_background && ppu->mask.show_sprites) {
    if (!(ppu->mask.show_background_leftmost_8px ||
          ppu->mask.show_sprites_leftmost_8px)) {
      if (ppu->cycle >= 9 && ppu->cycle < 258) {
        ppu->status.sprite_0_hit = 1;
      }
    } else {
      if (ppu->cycle >= 1 && ppu->cycle < 258) {
        ppu->status.sprite_0_hit = 1;
      }
    }
  }
}

static void increment_scroll_x(ppu_t* ppu) {
  if (!ppu->mask.show_background && !ppu->mask.show_sprites) {
    return;
  }

  if (ppu->vram_address.coarse_x == 31) {
    ppu->vram_address.coarse_x = 0;
    ppu->vram_address.nametable_x = ~ppu->vram_address.nametable_x;
  } else {
    ppu->vram_address.coarse_x++;
  }
}

static void increment_scroll_y(ppu_t* ppu) {
  if (!ppu->mask.show_background && !ppu->mask.show_sprites) {
    return;
  }

  if (ppu->vram_address.fine_y < 7) {
    ppu->vram_address.fine_y++;
    return;
  }

  ppu->vram_address.fine_y = 0;

  if (ppu->vram_address.coarse_y == 29) {
    ppu->vram_address.coarse_y = 0;
    ppu->vram_address.nametable_y = ~ppu->vram_address.nametable_y;
  } else if (ppu->vram_address.coarse_y == 31) {
    ppu->vram_address.coarse_y = 0;
  } else {
    ppu->vram_address.coarse_y++;
  }
}

static void transfer_address_x(ppu_t* ppu) {
  if (!ppu->mask.show_background && !ppu->mask.show_sprites) {
    return;
  }

  ppu->vram_address.nametable_x = ppu->tram_address.nametable_x;
  ppu->vram_address.coarse_x = ppu->tram_address.coarse_x;
}

static void transfer_address_y(ppu_t* ppu) {
  if (!ppu->mask.show_background && !ppu->mask.show_sprites) {
    return;
  }

  ppu->vram_address.fine_y = ppu->tram_address.fine_y;
  ppu->vram_address.nametable_y = ppu->tram_address.nametable_y;
  ppu->vram_address.coarse_y = ppu->tram_address.coarse_y;
}

static void load_background_shifters(ppu_t* ppu) {
  ppu->shifters.pattern_low = (ppu->shifters.pattern_low & 0xFF00) |
                              ppu->internal.next_tile_background_lsb;
  ppu->shifters.pattern_high = (ppu->shifters.pattern_high & 0xFF00) |
                               ppu->internal.next_tile_background_msb;

  ppu->shifters.attribute_low =
      (ppu->shifters.attribute_low & 0xFF00) |
      ((ppu->internal.next_tile_background_attribute & 0x01) ? 0xFF : 0x00);

  ppu->shifters.attribute_high =
      (ppu->shifters.attribute_high & 0xFF00) |
      ((ppu->internal.next_tile_background_attribute & 0x02) ? 0xFF : 0x00);
}

static void update_shifters(ppu_t* ppu) {
  if (ppu->mask.show_background) {
    ppu->shifters.pattern_low <<= 1;
    ppu->shifters.pattern_high <<= 1;

    ppu->shifters.attribute_low <<= 1;
    ppu->shifters.attribute_high <<= 1;
  }

  if (ppu->mask.show_sprites && ppu->cycle >= 1 && ppu->cycle < 258) {
    for (u8 i = 0; i < ppu->scan_line_sprites_count; i++) {
      if (ppu->scan_line_sprites[i].x > 0) {
        ppu->scan_line_sprites[i].x--;
      } else {
        ppu->shifters.sprite_patten_low[i] <<= 1;
        ppu->shifters.sprite_patten_high[i] <<= 1;
      }
    }
  }
}

static void fetch_next_tile_background_index(ppu_t* ppu) {
  load_background_shifters(ppu);

  u16 address = 0x2000 + (ppu->vram_address.reg & 0x0FFF);
  ppu->internal.next_tile_background_index = ppu_internal_read8(ppu, address);
}

static void fetch_next_tile_background_attribute(ppu_t* ppu) {
  u16 address = 0x23C0 | (ppu->vram_address.nametable_y << 11) |
                (ppu->vram_address.nametable_x << 10) |
                ((ppu->vram_address.coarse_y >> 2) << 3) |
                (ppu->vram_address.coarse_x >> 2);

  ppu->internal.next_tile_background_attribute =
      ppu_internal_read8(ppu, address);

  if (ppu->vram_address.coarse_y & 0x02) {
    ppu->internal.next_tile_background_attribute >>= 4;
  }

  if (ppu->vram_address.coarse_x & 0x02) {
    ppu->internal.next_tile_background_attribute >>= 2;
  }

  ppu->internal.next_tile_background_attribute &= 0x03;
}

static void fetch_next_tile_background_lsb(ppu_t* ppu) {
  u16 address = (ppu->ctrl.background_pattern_address << 12) +
                ((u16)ppu->internal.next_tile_background_index << 4) +
                ppu->vram_address.fine_y;

  ppu->internal.next_tile_background_lsb = ppu_internal_read8(ppu, address);
}

static void fetch_next_tile_background_msb(ppu_t* ppu) {
  u16 address = (ppu->ctrl.background_pattern_address << 12) +
                ((u16)ppu->internal.next_tile_background_index << 4) +
                ppu->vram_address.fine_y + 8;

  ppu->internal.next_tile_background_msb = ppu_internal_read8(ppu, address);
}

static void ppu_prepare_background_state(ppu_t* ppu) {
  if ((ppu->cycle >= 2 && ppu->cycle < 258) ||
      (ppu->cycle >= 321 && ppu->cycle < 338)) {
    update_shifters(ppu);

    switch ((ppu->cycle - 1) % 8) {
      case 0:
        fetch_next_tile_background_index(ppu);
        break;
      case 2:
        fetch_next_tile_background_attribute(ppu);
        break;
      case 4:
        fetch_next_tile_background_lsb(ppu);
        break;
      case 6:
        fetch_next_tile_background_msb(ppu);
        break;
      case 7:
        increment_scroll_x(ppu);
        break;
    }
  }

  if (ppu->cycle == 256) {
    increment_scroll_y(ppu);
  }

  if (ppu->cycle == 257) {
    load_background_shifters(ppu);
    transfer_address_x(ppu);
  }

  if (ppu->cycle == 338 || ppu->cycle == 340) {
    ppu->internal.next_tile_background_index =
        ppu_internal_read8(ppu, 0x2000 | (ppu->vram_address.reg & 0x0FFF));
  }

  if (ppu->scan_line == -1 && ppu->cycle >= 280 && ppu->cycle < 305) {
    transfer_address_y(ppu);
  }
}

static void fetch_visible_sprites(ppu_t* ppu) {
  memset(ppu->scan_line_sprites, 0xFF, sizeof(ppu->scan_line_sprites));
  ppu->scan_line_sprites_count = 0;
  ppu->sprite_0_hit_possible = false;

  u8 oam_index = 0;
  while (oam_index < 64 && ppu->scan_line_sprites_count < 9) {
    s16 sprite_height = (ppu->ctrl.sprite_size ? 16 : 8);
    s16 height_diff = (s16)ppu->scan_line - (s16)ppu->oam[oam_index].y;

    if (height_diff >= 0 && height_diff < sprite_height) {
      if (ppu->scan_line_sprites_count < 8) {
        if (oam_index == 0) {
          ppu->sprite_0_hit_possible = true;
        }

        memcpy(&ppu->scan_line_sprites[ppu->scan_line_sprites_count],
               &ppu->oam[oam_index], sizeof(ppu->oam[oam_index]));
        ppu->scan_line_sprites_count++;
      }
    }
    oam_index++;
  }

  ppu->status.sprite_overflow = ppu->scan_line_sprites_count > 8;
}

static void update_sprite_shifters(ppu_t* ppu) {
  for (u8 i = 0; i < ppu->scan_line_sprites_count; i++) {
    u8 sprite_pattern_bites_low;
    u8 sprite_pattern_bites_high;

    u16 sprite_pattern_address_low;
    u16 sprite_pattern_address_high;

    if (!ppu->ctrl.sprite_size) {
      if (!(ppu->scan_line_sprites[i].attribute & 0x80)) {
        sprite_pattern_address_low =
            (ppu->ctrl.sprite_pattern_address << 12) |
            (ppu->scan_line_sprites[i].id << 4) |
            (ppu->scan_line - ppu->scan_line_sprites[i].y);
      } else {
        sprite_pattern_address_low =
            (ppu->ctrl.sprite_pattern_address << 12) |
            (ppu->scan_line_sprites[i].id << 4) |
            (7 - ppu->scan_line - ppu->scan_line_sprites[i].y);
      }
    } else {
      if (!(ppu->scan_line_sprites[i].attribute & 0x80)) {
        if (ppu->scan_line - ppu->scan_line_sprites[i].y < 8) {
          sprite_pattern_address_low =
              (ppu->scan_line_sprites[i].id & 0x01) << 12 |
              ((ppu->scan_line_sprites[i].id & 0xFE) << 4) |
              ((ppu->scan_line - ppu->scan_line_sprites[i].y) & 0x07);
        } else {
          sprite_pattern_address_low =
              (ppu->scan_line_sprites[i].id & 0x01) << 12 |
              (((ppu->scan_line_sprites[i].id & 0xFE) + 1) << 4) |
              ((ppu->scan_line - ppu->scan_line_sprites[i].y) & 0x07);
        }
      } else {
        if (ppu->scan_line - ppu->scan_line_sprites[i].y < 8) {
          sprite_pattern_address_low =
              (ppu->scan_line_sprites[i].id & 0x01) << 12 |
              (((ppu->scan_line_sprites[i].id & 0xFE) + 1) << 4) |
              ((7 - ppu->scan_line - ppu->scan_line_sprites[i].y) & 0x07);
        } else {
          sprite_pattern_address_low =
              (ppu->scan_line_sprites[i].id & 0x01) << 12 |
              ((ppu->scan_line_sprites[i].id & 0xFE) << 4) |
              ((7 - ppu->scan_line - ppu->scan_line_sprites[i].y) & 0x07);
        }
      }
    }

    sprite_pattern_address_high = sprite_pattern_address_low + 8;
    sprite_pattern_bites_low =
        ppu_internal_read8(ppu, sprite_pattern_address_low);
    sprite_pattern_bites_high =
        ppu_internal_read8(ppu, sprite_pattern_address_high);

    if (ppu->scan_line_sprites[i].attribute & 0x40) {
      sprite_pattern_bites_low = sprite_flip_byte(sprite_pattern_bites_low);
      sprite_pattern_bites_high = sprite_flip_byte(sprite_pattern_bites_high);
    }

    ppu->shifters.sprite_patten_low[i] = sprite_pattern_bites_low;
    ppu->shifters.sprite_patten_high[i] = sprite_pattern_bites_high;
  }
}

static void ppu_prepare_foreground_state(ppu_t* ppu) {
  if (ppu->cycle == 257 && ppu->scan_line >= 0) {
    fetch_visible_sprites(ppu);
  }

  if (ppu->cycle == 340) {
    update_sprite_shifters(ppu);
  }
}

void ppu_prepare_new_frame(ppu_t* ppu) {
  ppu->status.v_blank = 0;
  ppu->status.sprite_0_hit = 0;
  ppu->status.sprite_overflow = 0;

  for (int i = 0; i < 8; i++) {
    ppu->shifters.sprite_patten_low[i] = 0;
    ppu->shifters.sprite_patten_high[i] = 0;
  }
}

void ppu_prepare_render_state(ppu_t* ppu) {
  ppu_prepare_background_state(ppu);
  ppu_prepare_foreground_state(ppu);
}

void ppu_render_pixel(ppu_t* ppu) {
  u8 background_pixel = 0;
  u8 background_palette = 0;

  if (ppu->mask.show_background) {
    u16 bit_mux = 0x8000 >> ppu->fine_x;

    u8 pixel_lsb = (ppu->shifters.pattern_low & bit_mux) > 0;
    u8 pixel_msb = (ppu->shifters.pattern_high & bit_mux) > 0;
    background_pixel = (pixel_msb << 1) | pixel_lsb;

    u8 palette_lsb = (ppu->shifters.attribute_low & bit_mux) > 0;
    u8 palette_msb = (ppu->shifters.attribute_high & bit_mux) > 0;
    background_palette = (palette_msb << 1) | palette_lsb;
  }

  u8 foreground_pixel = 0;
  u8 foreground_palette = 0;
  u8 foreground_priority = 0;

  if (ppu->mask.show_sprites) {
    ppu->sprite_0_being_rendered = false;

    for (int i = 0; i < ppu->scan_line_sprites_count; i++) {
      if (ppu->scan_line_sprites[i].x == 0) {
        u8 pixel_lsb = (ppu->shifters.sprite_patten_low[i] & 0x80) > 0;
        u8 pixel_msb = (ppu->shifters.sprite_patten_high[i] & 0x80) > 0;
        foreground_pixel = (pixel_msb << 1) | pixel_lsb;

        foreground_palette =
            (ppu->scan_line_sprites[i].attribute & 0x03) + 0x04;
        foreground_priority = (ppu->scan_line_sprites[i].attribute & 0x20) == 0;

        if (foreground_pixel != 0) {
          if (i == 0) {
            ppu->sprite_0_being_rendered = true;
          }
          break;
        }
      }
    }
  }

  u8 pixel = 0;
  u8 pallette = 0;

  if (background_pixel == 0 && foreground_pixel == 0) {
    pixel = 0;
    pallette = 0;
  } else if (background_pixel == 0 && foreground_pixel > 0) {
    pixel = foreground_pixel;
    pallette = foreground_palette;
  } else if (background_pixel > 0 && foreground_pixel == 0) {
    pixel = background_pixel;
    pallette = background_palette;
  } else if (background_pixel > 0 && foreground_pixel > 0) {
    if (foreground_priority) {
      pixel = foreground_pixel;
      pallette = foreground_palette;
    } else {
      pixel = background_pixel;
      pallette = background_palette;
    }

    ppu_handle_sprite_0_hit(ppu);
  }

  u8 palette_color = ppu_internal_read8(ppu, 0x3F00 + (pallette << 2) + pixel);

  screen_draw_color(ppu->cycle - 1, ppu->scan_line,
                    screen_get_palette_color(palette_color));
}
