#pragma once

#include "../config/globals.h"
#include "../utils/types.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240

#if !DEBUG_MODE
#define SCREEN_SCALE 3
#else
#define SCREEN_SCALE 2
#endif

#define PALETTE_COLORS_COUNT 0x40

typedef struct {
  u8 r, g, b, a;
} color_t;

extern color_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

extern color_t palette_colors[PALETTE_COLORS_COUNT];

void screen_init();
void screen_clear();
void screen_draw_color(u16 x, u16 y, color_t color);

void screen_export_to_ppm(const char* file_path);

void screen_init_palette_colors();
color_t screen_get_palette_color(u8 color);