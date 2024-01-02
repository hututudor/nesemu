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
  palette_colors[0x00] = (color_t){.r = 0x62, .g = 0x62, .b = 0x62};
  palette_colors[0x01] = (color_t){.r = 0x00, .g = 0x1F, .b = 0xB2};
  palette_colors[0x02] = (color_t){.r = 0x24, .g = 0x04, .b = 0xC8};
  palette_colors[0x03] = (color_t){.r = 0x52, .g = 0x00, .b = 0xB2};
  palette_colors[0x04] = (color_t){.r = 0x73, .g = 0x00, .b = 0x76};
  palette_colors[0x05] = (color_t){.r = 0x80, .g = 0x00, .b = 0x24};
  palette_colors[0x06] = (color_t){.r = 0x73, .g = 0x0B, .b = 0x00};
  palette_colors[0x07] = (color_t){.r = 0x52, .g = 0x28, .b = 0x00};
  palette_colors[0x08] = (color_t){.r = 0x24, .g = 0x44, .b = 0x00};
  palette_colors[0x09] = (color_t){.r = 0x00, .g = 0x57, .b = 0x00};
  palette_colors[0x0A] = (color_t){.r = 0x00, .g = 0x5C, .b = 0x00};
  palette_colors[0x0B] = (color_t){.r = 0x00, .g = 0x53, .b = 0x24};
  palette_colors[0x0C] = (color_t){.r = 0x00, .g = 0x3C, .b = 0x76};
  palette_colors[0x0D] = (color_t){.r = 0x00, .g = 0x00, .b = 0x00};
  palette_colors[0x0E] = (color_t){.r = 0x00, .g = 0x00, .b = 0x00};
  palette_colors[0x0F] = (color_t){.r = 0x00, .g = 0x00, .b = 0x00};

  palette_colors[0x10] = (color_t){.r = 0xAB, .g = 0xAB, .b = 0xAB};
  palette_colors[0x11] = (color_t){.r = 0x0D, .g = 0x57, .b = 0xFF};
  palette_colors[0x12] = (color_t){.r = 0x4B, .g = 0x30, .b = 0xFF};
  palette_colors[0x13] = (color_t){.r = 0x8A, .g = 0x13, .b = 0xFF};
  palette_colors[0x14] = (color_t){.r = 0xBC, .g = 0x08, .b = 0xD6};
  palette_colors[0x15] = (color_t){.r = 0xD2, .g = 0x12, .b = 0x69};
  palette_colors[0x16] = (color_t){.r = 0xC7, .g = 0x2E, .b = 0x00};
  palette_colors[0x17] = (color_t){.r = 0x9D, .g = 0x54, .b = 0x00};
  palette_colors[0x18] = (color_t){.r = 0x60, .g = 0x7B, .b = 0x00};
  palette_colors[0x19] = (color_t){.r = 0x20, .g = 0x98, .b = 0x00};
  palette_colors[0x1A] = (color_t){.r = 0x00, .g = 0xA3, .b = 0x00};
  palette_colors[0x1B] = (color_t){.r = 0x00, .g = 0x99, .b = 0x42};
  palette_colors[0x1C] = (color_t){.r = 0x00, .g = 0x7D, .b = 0xB4};
  palette_colors[0x1D] = (color_t){.r = 0x00, .g = 0x00, .b = 0x00};
  palette_colors[0x1E] = (color_t){.r = 0x00, .g = 0x00, .b = 0x00};
  palette_colors[0x1F] = (color_t){.r = 0x00, .g = 0x00, .b = 0x00};

  palette_colors[0x20] = (color_t){.r = 0xFF, .g = 0xFF, .b = 0xFF};
  palette_colors[0x21] = (color_t){.r = 0x53, .g = 0xAE, .b = 0xFF};
  palette_colors[0x22] = (color_t){.r = 0x90, .g = 0x85, .b = 0xFF};
  palette_colors[0x23] = (color_t){.r = 0xD3, .g = 0x65, .b = 0xFF};
  palette_colors[0x24] = (color_t){.r = 0xFF, .g = 0x57, .b = 0xFF};
  palette_colors[0x25] = (color_t){.r = 0xFF, .g = 0x5D, .b = 0xCF};
  palette_colors[0x26] = (color_t){.r = 0xFF, .g = 0x77, .b = 0x57};
  palette_colors[0x27] = (color_t){.r = 0xFA, .g = 0x9E, .b = 0x00};
  palette_colors[0x28] = (color_t){.r = 0xBD, .g = 0xC7, .b = 0x00};
  palette_colors[0x29] = (color_t){.r = 0x7A, .g = 0xE7, .b = 0x00};
  palette_colors[0x2A] = (color_t){.r = 0x43, .g = 0xF6, .b = 0x11};
  palette_colors[0x2B] = (color_t){.r = 0x26, .g = 0xEF, .b = 0x7E};
  palette_colors[0x2C] = (color_t){.r = 0x2C, .g = 0xD5, .b = 0xF6};
  palette_colors[0x2D] = (color_t){.r = 0x4E, .g = 0x4E, .b = 0x4E};
  palette_colors[0x2E] = (color_t){.r = 0x00, .g = 0x00, .b = 0x00};
  palette_colors[0x2F] = (color_t){.r = 0x00, .g = 0x00, .b = 0x00};

  palette_colors[0x30] = (color_t){.r = 0xFF, .g = 0xFF, .b = 0xFF};
  palette_colors[0x31] = (color_t){.r = 0xB6, .g = 0xE1, .b = 0xFF};
  palette_colors[0x32] = (color_t){.r = 0xCE, .g = 0xD1, .b = 0xFF};
  palette_colors[0x33] = (color_t){.r = 0xE9, .g = 0xC3, .b = 0xFF};
  palette_colors[0x34] = (color_t){.r = 0xFF, .g = 0xBC, .b = 0xFF};
  palette_colors[0x35] = (color_t){.r = 0xFF, .g = 0xBD, .b = 0xF4};
  palette_colors[0x36] = (color_t){.r = 0xFF, .g = 0xC6, .b = 0xC3};
  palette_colors[0x37] = (color_t){.r = 0xFF, .g = 0xD5, .b = 0x9A};
  palette_colors[0x38] = (color_t){.r = 0xE9, .g = 0xE6, .b = 0x81};
  palette_colors[0x39] = (color_t){.r = 0xCE, .g = 0xF4, .b = 0x81};
  palette_colors[0x3A] = (color_t){.r = 0xB6, .g = 0xFB, .b = 0x9A};
  palette_colors[0x3B] = (color_t){.r = 0xA9, .g = 0xFA, .b = 0xC3};
  palette_colors[0x3C] = (color_t){.r = 0xA9, .g = 0xF0, .b = 0xF4};
  palette_colors[0x3D] = (color_t){.r = 0xB8, .g = 0xB8, .b = 0xB8};
  palette_colors[0x3E] = (color_t){.r = 0x00, .g = 0x00, .b = 0x00};
  palette_colors[0x3F] = (color_t){.r = 0x00, .g = 0x00, .b = 0x00};
}

color_t screen_get_palette_color(u8 color) {
  if (color >= PALETTE_COLORS_COUNT) {
    printf("[SCREEN] Palette color 0x%02X not found\n", color);
    return (color_t){.r = 0, .g = 0, .b = 0};
  }

  return palette_colors[color];
}