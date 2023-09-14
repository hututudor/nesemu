#include "screen.h"

#include <stdio.h>
#include <stdlib.h>

color_t screen[SCREEN_HEIGHT][SCREEN_WIDTH] = {0};

void screen_clear() {
  for (u16 y = 0; y < SCREEN_HEIGHT; y++) {
    for (u16 x = 0; x < SCREEN_WIDTH; x++) {
      screen[y][x].r = 0;
      screen[y][x].g = 0;
      screen[y][x].b = 0;
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