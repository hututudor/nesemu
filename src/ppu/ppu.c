#include "ppu.h"

#include "../cpu/cpu.h"
#include "../peripherals/screen.h"

u32 frame_count = 0;

ppu_t* ppu_create() {
  ppu_t* ppu = (ppu_t*)calloc(1, sizeof(ppu_t));

  ppu->nametable_memory = memory_create(0x2000, 0x1000);
  ppu->palette_memory = memory_create(0x03F00, 0x0100);

  ppu->scan_line = 0;
  ppu->cycle = 0;

  ppu->internal.next_tile_background_index = 0;
  ppu->internal.next_tile_background_attribute = 0;
  ppu->internal.next_tile_background_lsb = 0;
  ppu->internal.next_tile_background_msb = 0;

  ppu->shifters.pattern_low = 0;
  ppu->shifters.pattern_high = 0;
  ppu->shifters.attribute_low = 0;
  ppu->shifters.attribute_high = 0;

  ppu->oam_pointer = (u8*)ppu->oam;
  ppu->oam_address = 0;
  ppu->scan_line_sprites_count = 0;

  ppu->sprite_0_hit_possible = false;
  ppu->sprite_0_being_rendered = false;

  ppu->latch_high = 0;
  ppu->fine_x = 0;
  ppu->tram_address.reg = 0;
  ppu->vram_address.reg = 0;

  ppu->status.v_blank = 0;
  ppu->status.sprite_0_hit = 0;
  ppu->status.sprite_overflow = 0;

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

  memory_destroy(ppu->palette_memory);
  memory_destroy(ppu->nametable_memory);

  free(ppu);
}

void ppu_clock(ppu_t* ppu) {
  if (ppu->scan_line >= -1 && ppu->scan_line < 240) {
    if (ppu->scan_line == 0 && ppu->cycle == 0) {
      ppu->cycle = 1;
    }

    if (ppu->scan_line == -1 && ppu->cycle == 1) {
      ppu_prepare_new_frame(ppu);
    }

    ppu_prepare_render_state(ppu);
  }

  if (ppu->scan_line == 241 && ppu->cycle == 1) {
    ppu->status.v_blank = 1;
    if (ppu->ctrl.generate_nmi) {
      cpu_nmi(ppu->bus->cpu);
    }
  }

  ppu_render_pixel(ppu);

  ppu->cycle++;
  if (ppu->cycle >= 341) {
    ppu->cycle = 0;
    ppu->scan_line++;

    if (ppu->scan_line >= 261) {
      ppu->scan_line = -1;
    }
  }
}
