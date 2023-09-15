#include "ppu.h"

#include "../peripherals/screen.h"

u32 frame_count = 0;

static void ppu_export_frame() {
  char* path = (char*)calloc(256, sizeof(char));
  sprintf(path, "frames/frame%d.ppm", frame_count++);

  screen_export_to_ppm(path);
  screen_clear();

  free(path);

  // temporary hard stop after 1s of frames
  if (frame_count > 59) {
    exit(0);
  }
}

ppu_t* ppu_create() {
  ppu_t* ppu = (ppu_t*)calloc(1, sizeof(ppu_t));

  ppu->scan_line = 0;
  ppu->cycle = 0;

  return ppu;
}

void ppu_connect_bus(ppu_t* ppu, bus_t* bus) {
  if (!ppu || !bus) {
    return;
  }

  ppu->bus = bus;
}

void ppu_destroy(ppu_t* ppu) {
  if (!ppu) {
    return;
  }

  free(ppu);
}

void ppu_clock(ppu_t* ppu) {
  ppu->cycle++;

  if (ppu->cycle > 341) {
    ppu->cycle = 0;
    ppu->scan_line++;
  }

  if (ppu->scan_line > 262) {
    ppu->scan_line = 0;
  }

  if (ppu->scan_line == 241 && ppu->cycle == 1) {
    ppu_export_frame();
  }

  if (ppu->scan_line < 240 && ppu->cycle < 256) {
    color_t color = {0};
    color.r = ppu->cycle & 0xFF;
    color.g = (ppu->cycle & 0xFF00) >> 8;
    color.b = ppu->scan_line;
    screen_draw_color(ppu->cycle, ppu->scan_line, color);
  }

  // printf("PPU %d %d\n", ppu->scan_line, ppu->cycle);
}
