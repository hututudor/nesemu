#pragma once

#include "../utils/types.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240

typedef struct {
  u8 r, g, b;
} color_t;

void screen_clear();
void screen_draw_color(u16 x, u16 y, color_t color);

void screen_export_to_ppm(const char* file_path);