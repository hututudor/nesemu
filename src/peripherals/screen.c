#include "screen.h"

#include <stdio.h>
#include <stdlib.h>

color_t screen[SCREEN_HEIGHT][SCREEN_WIDTH] = {0};
color_t palette_colors[PALETTE_COLORS_COUNT] = {0};

void screen_init() {
  screen_clear();
  screen_init_palette_colors();
}

void screen_clear() {
  for (u16 y = 0; y < SCREEN_HEIGHT; y++) {
    for (u16 x = 0; x < SCREEN_WIDTH; x++) {
      screen[y][x].r = 0;
      screen[y][x].g = 0;
      screen[y][x].b = 0;
      screen[y][x].a = 0xFF;
    }
  }
}

void screen_draw_color(u16 x, u16 y, color_t color) {
  if (x >= SCREEN_WIDTH) {
    return;
  }

  if (y >= SCREEN_HEIGHT) {
    return;
  }

  screen[y][x] = color;
}

void screen_export_to_ppm(const char* file_path) {
  FILE* file = fopen(file_path, "w");

  fprintf(file, "P3 \n%d %d\n255\n", SCREEN_WIDTH, SCREEN_HEIGHT);

  for (u16 y = 0; y < SCREEN_HEIGHT; y++) {
    for (u16 x = 0; x < SCREEN_WIDTH; x++) {
      fprintf(file, "%d %d %d\n", screen[y][x].r, screen[y][x].g,
              screen[y][x].b);
    }
  }

  fclose(file);
}

void screen_init_palette_colors() {
  palette_colors[0x00] = (color_t){.r = 84, .g = 84, .b = 84};
  palette_colors[0x01] = (color_t){.r = 0, .g = 30, .b = 116};
  palette_colors[0x02] = (color_t){.r = 8, .g = 16, .b = 144};
  palette_colors[0x03] = (color_t){.r = 48, .g = 0, .b = 136};
  palette_colors[0x04] = (color_t){.r = 68, .g = 0, .b = 100};
  palette_colors[0x05] = (color_t){.r = 92, .g = 0, .b = 48};
  palette_colors[0x06] = (color_t){.r = 84, .g = 4, .b = 0};
  palette_colors[0x07] = (color_t){.r = 60, .g = 24, .b = 0};
  palette_colors[0x08] = (color_t){.r = 32, .g = 42, .b = 0};
  palette_colors[0x09] = (color_t){.r = 8, .g = 58, .b = 0};
  palette_colors[0x0A] = (color_t){.r = 0, .g = 64, .b = 0};
  palette_colors[0x0B] = (color_t){.r = 9, .g = 60, .b = 0};
  palette_colors[0x0C] = (color_t){.r = 0, .g = 50, .b = 60};
  palette_colors[0x0D] = (color_t){.r = 0, .g = 0, .b = 0};
  palette_colors[0x0E] = (color_t){.r = 0, .g = 0, .b = 0};
  palette_colors[0x0F] = (color_t){.r = 0, .g = 0, .b = 0};

  palette_colors[0x10] = (color_t){.r = 152, .g = 150, .b = 152};
  palette_colors[0x11] = (color_t){.r = 8, .g = 76, .b = 196};
  palette_colors[0x12] = (color_t){.r = 48, .g = 50, .b = 236};
  palette_colors[0x13] = (color_t){.r = 92, .g = 30, .b = 228};
  palette_colors[0x14] = (color_t){.r = 136, .g = 20, .b = 176};
  palette_colors[0x15] = (color_t){.r = 160, .g = 20, .b = 100};
  palette_colors[0x16] = (color_t){.r = 152, .g = 34, .b = 32};
  palette_colors[0x17] = (color_t){.r = 120, .g = 60, .b = 0};
  palette_colors[0x18] = (color_t){.r = 84, .g = 90, .b = 0};
  palette_colors[0x19] = (color_t){.r = 40, .g = 114, .b = 0};
  palette_colors[0x1A] = (color_t){.r = 8, .g = 124, .b = 0};
  palette_colors[0x1B] = (color_t){.r = 0, .g = 118, .b = 40};
  palette_colors[0x1C] = (color_t){.r = 0, .g = 102, .b = 120};
  palette_colors[0x1D] = (color_t){.r = 0, .g = 0, .b = 0};
  palette_colors[0x1E] = (color_t){.r = 0, .g = 0, .b = 0};
  palette_colors[0x1F] = (color_t){.r = 0, .g = 0, .b = 0};

  palette_colors[0x20] = (color_t){.r = 236, .g = 238, .b = 236};
  palette_colors[0x21] = (color_t){.r = 76, .g = 154, .b = 236};
  palette_colors[0x22] = (color_t){.r = 120, .g = 124, .b = 236};
  palette_colors[0x23] = (color_t){.r = 176, .g = 98, .b = 236};
  palette_colors[0x24] = (color_t){.r = 228, .g = 84, .b = 236};
  palette_colors[0x25] = (color_t){.r = 236, .g = 88, .b = 180};
  palette_colors[0x26] = (color_t){.r = 236, .g = 106, .b = 100};
  palette_colors[0x27] = (color_t){.r = 212, .g = 136, .b = 32};
  palette_colors[0x28] = (color_t){.r = 160, .g = 170, .b = 0};
  palette_colors[0x29] = (color_t){.r = 116, .g = 196, .b = 0};
  palette_colors[0x2A] = (color_t){.r = 76, .g = 208, .b = 32};
  palette_colors[0x2B] = (color_t){.r = 56, .g = 204, .b = 208};
  palette_colors[0x2C] = (color_t){.r = 56, .g = 180, .b = 203};
  palette_colors[0x2D] = (color_t){.r = 60, .g = 60, .b = 60};
  palette_colors[0x2E] = (color_t){.r = 0, .g = 0, .b = 0};
  palette_colors[0x2F] = (color_t){.r = 0, .g = 0, .b = 0};

  palette_colors[0x30] = (color_t){.r = 236, .g = 238, .b = 236};
  palette_colors[0x31] = (color_t){.r = 168, .g = 204, .b = 236};
  palette_colors[0x32] = (color_t){.r = 188, .g = 188, .b = 236};
  palette_colors[0x33] = (color_t){.r = 212, .g = 178, .b = 236};
  palette_colors[0x34] = (color_t){.r = 236, .g = 174, .b = 236};
  palette_colors[0x35] = (color_t){.r = 236, .g = 174, .b = 212};
  palette_colors[0x36] = (color_t){.r = 236, .g = 180, .b = 176};
  palette_colors[0x37] = (color_t){.r = 228, .g = 196, .b = 144};
  palette_colors[0x38] = (color_t){.r = 204, .g = 210, .b = 120};
  palette_colors[0x39] = (color_t){.r = 180, .g = 222, .b = 120};
  palette_colors[0x3A] = (color_t){.r = 168, .g = 226, .b = 144};
  palette_colors[0x3B] = (color_t){.r = 152, .g = 226, .b = 180};
  palette_colors[0x3C] = (color_t){.r = 160, .g = 214, .b = 228};
  palette_colors[0x3D] = (color_t){.r = 160, .g = 162, .b = 160};
  palette_colors[0x3E] = (color_t){.r = 0, .g = 0, .b = 0};
  palette_colors[0x3F] = (color_t){.r = 0, .g = 0, .b = 0};
}

color_t screen_get_palette_color(u8 color) {
  if (color >= PALETTE_COLORS_COUNT) {
    printf("[SCREEN] Palette color 0x%02X not found\n", color);
    return (color_t){.r = 0, .g = 0, .b = 0};
  }

  return palette_colors[color];
}