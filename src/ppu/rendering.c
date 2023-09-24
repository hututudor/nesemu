#include "../peripherals/screen.h"
#include "ppu.h"

static u16 get_palette_real_address(u16 address) {
  if (address % 4 == 0) {
    address &= 0xFFFC;
  }

  if (address == 0x3F10) {
    return 0x3F00;
  }

  return address;
}

static u8 get_attribute_palette(u8 attribute, u8 fine_x, u8 fine_y) {
  if (fine_x < 2) {
    if (fine_y < 2) {
      return attribute & 0x3;
    }

    return (attribute >> 4) & 0x3;
  }

  if (fine_y < 2) {
    return (attribute >> 2) & 0x3;
  }

  return (attribute >> 6) & 0x3;
}

void ppu_render_pixel(ppu_t* ppu, u32 frames) {
  s16 x = ppu->cycle;
  s16 y = ppu->scan_line;

  u8 nametable_coarse_x = x / 8;
  u8 nametable_fine_x = x % 8;
  u8 nametable_coarse_y = y / 8;
  u8 nametable_fine_y = y % 8;

  u16 nametable_pattern_address =
      0x2000 + (nametable_coarse_y * 32) + nametable_coarse_x;

  u8 tile_index = ppu_internal_read8(ppu, nametable_pattern_address);

  u16 chr_address = ppu->ctrl.background_pattern_address == 0 ? 0x0000 : 0x1000;
  u16 tile_address = chr_address + (((u16)tile_index) << 4);

  u8 pattern_low = ppu_internal_read8(ppu, tile_address + nametable_fine_y);
  u8 pattern_high =
      ppu_internal_read8(ppu, tile_address + nametable_fine_y + 8);

  u8 palette_index = (((pattern_high >> (7 - nametable_fine_x)) & 0x01) << 1) |
                     ((pattern_low >> (7 - nametable_fine_x)) & 0x01);

  u8 attribute_coarse_x = nametable_coarse_x / 4;
  u8 attribute_fine_x = nametable_coarse_x % 4;
  u8 attribute_coarse_y = nametable_coarse_y / 4;
  u8 attribute_fine_y = nametable_coarse_y % 4;
  u16 attribute_address = 0x23C0 + attribute_coarse_y * 8 + attribute_coarse_x;
  u8 attribute = ppu_internal_read8(ppu, attribute_address);

  u8 attribute_palette =
      get_attribute_palette(attribute, attribute_fine_x, attribute_fine_y);
  u16 palette_address =
      get_palette_real_address(0x3F00 + attribute_palette * 4 + palette_index);
  u8 palette_color = ppu_internal_read8(ppu, palette_address);

  screen_draw_color(ppu->cycle, ppu->scan_line,
                    screen_get_palette_color(palette_color));
}