#pragma once

#include "../utils/types.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240
#define PALETTE_COLORS_COUNT 0x40

typedef struct {
  u8 r, g, b, a;
} color_t;

extern color_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

void screen_init();
void screen_clear();
void screen_draw_color(u16 x, u16 y, color_t color);

void screen_export_to_ppm(const char* file_path);

void screen_init_palette_colors();
color_t screen_get_palette_color(u8 color);