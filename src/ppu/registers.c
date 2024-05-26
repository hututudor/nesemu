#include "../cpu/cpu.h"
#include "ppu.h"

u8 ppu_read_ctrl(ppu_t* ppu) { return 0x00; }
void ppu_write_ctrl(ppu_t* ppu, u8 value) {
  ppu->ctrl.base_nametable_address = (value >> 0) & 0x03;
  ppu->ctrl.vram_increment = (value >> 2) & 0x01;
  ppu->ctrl.sprite_pattern_address = (value >> 3) & 0x01;
  ppu->ctrl.background_pattern_address = (value >> 4) & 0x01;
  ppu->ctrl.sprite_size = (value >> 5) & 0x01;
  ppu->ctrl.master_slave_select = (value >> 6) & 0x01;
  ppu->ctrl.generate_nmi = (value >> 7) & 0x01;

  ppu->tram_address.nametable_x = (value >> 0) & 0x01;
  ppu->tram_address.nametable_y = (value >> 1) & 0x01;
}

u8 ppu_read_mask(ppu_t* ppu) { return 0x00; }
void ppu_write_mask(ppu_t* ppu, u8 value) {
  ppu->mask.grayscale = (value >> 0) & 0x01;
  ppu->mask.show_background_leftmost_8px = (value >> 1) & 0x01;
  ppu->mask.show_sprites_leftmost_8px = (value >> 2) & 0x01;
  ppu->mask.show_background = (value >> 3) & 0x01;
  ppu->mask.show_sprites = (value >> 4) & 0x01;
  ppu->mask.emphasize_red = (value >> 5) & 0x01;
  ppu->mask.emphasize_green = (value >> 6) & 0x01;
  ppu->mask.emphasize_blue = (value >> 7) & 0x01;
}

u8 ppu_read_status(ppu_t* ppu) {
  u8 res = 0;

  res += ppu->status.v_blank;
  res <<= 1;

  res += ppu->status.sprite_0_hit;
  res <<= 1;

  res += ppu->status.sprite_overflow;
  res <<= 5;

  ppu->status.v_blank = 0;
  ppu->latch_high = 0;

  return res;
}

void ppu_write_status(ppu_t* ppu, u8 value) {}

u8 ppu_read_oam_addr(ppu_t* ppu) { return 0x00; }
void ppu_write_oam_addr(ppu_t* ppu, u8 value) { ppu->oam_address = value; }

u8 ppu_read_oam_data(ppu_t* ppu) { return ppu->oam_pointer[ppu->oam_address]; }
void ppu_write_oam_data(ppu_t* ppu, u8 value) {
  ppu->oam_pointer[ppu->oam_address] = value;
}

u8 ppu_read_scroll(ppu_t* ppu) { return 0x00; }
void ppu_write_scroll(ppu_t* ppu, u8 value) {
  if (ppu->latch_high == 0) {
    ppu->latch_high = 1;

    ppu->fine_x = value & 0x07;
    ppu->tram_address.coarse_x = value >> 3;
  } else {
    ppu->latch_high = 0;

    ppu->tram_address.fine_y = value & 0x07;
    ppu->tram_address.coarse_y = value >> 3;
  }
}

u8 ppu_read_addr(ppu_t* ppu) { return 0x00; }
void ppu_write_addr(ppu_t* ppu, u8 value) {
  if (ppu->latch_high == 0) {
    ppu->tram_address.reg &= 0x00FF;
    ppu->tram_address.reg |= ((u16)value) << 8;
    ppu->latch_high = 1;
  } else {
    ppu->tram_address.reg &= 0xFF00;
    ppu->tram_address.reg |= value;
    ppu->latch_high = 0;

    ppu->vram_address.reg = ppu->tram_address.reg;
  }
}

u8 ppu_read_data(ppu_t* ppu) {
  u8 value = ppu_internal_read8(ppu, ppu->vram_address.reg);

  u8 res = 0;
  if (ppu->vram_address.reg < 0x3F00) {
    res = value;
  } else {
    res = ppu->data_buffer;
  }

  ppu->data_buffer = value;
  ppu->vram_address.reg += (ppu->ctrl.vram_increment ? 32 : 1);

  return res;
}

void ppu_write_data(ppu_t* ppu, u8 value) {
  ppu_internal_write8(ppu, ppu->vram_address.reg & 0x3FFF, value);

  ppu->vram_address.reg += (ppu->ctrl.vram_increment ? 32 : 1);
}

static u16 ppu_get_nametable_mirrored_address(ppu_t* ppu, u16 address) {
  if (ppu->bus->mapper->rom->header.mirroring == MIRRORING_HORIZONTAL) {
    if (address >= 0x2400 && address < 0x2800) {
      return address - 0x400;
    }

    if (address >= 0x2C00 && address < 0x3000) {
      return address - 0x400;
    }
  }

  if (ppu->bus->mapper->rom->header.mirroring == MIRRORING_VERTICAL) {
    if (address >= 0x2800 && address < 0x2C00) {
      return address - 0x800;
    }

    if (address >= 0x2C00 && address < 0x3000) {
      return address - 0x800;
    }
  }

  return address;
}

u8 ppu_read8(ppu_t* ppu, u16 address) {
  switch (address & 0x07) {
    case 0x00:
      return ppu_read_ctrl(ppu);
    case 0x01:
      return ppu_read_mask(ppu);
    case 0x02:
      return ppu_read_status(ppu);
    case 0x03:
      return ppu_read_oam_addr(ppu);
    case 0x04:
      return ppu_read_oam_data(ppu);
    case 0x05:
      return ppu_read_scroll(ppu);
    case 0x06:
      return ppu_read_addr(ppu);
    case 0x07:
      return ppu_read_data(ppu);
  }

  return 0;
}

void ppu_write8(ppu_t* ppu, u16 address, u8 value) {
  switch (address & 0x07) {
    case 0x00:
      ppu_write_ctrl(ppu, value);
      return;
    case 0x01:
      ppu_write_mask(ppu, value);
      return;
    case 0x02:
      ppu_write_status(ppu, value);
      return;
    case 0x03:
      ppu_write_oam_addr(ppu, value);
      return;
    case 0x04:
      ppu_write_oam_data(ppu, value);
      return;
    case 0x05:
      ppu_write_scroll(ppu, value);
      return;
    case 0x06:
      ppu_write_addr(ppu, value);
      return;
    case 0x07:
      ppu_write_data(ppu, value);
      return;
  }
}

u8 ppu_internal_read8(ppu_t* ppu, u16 address) {
  if (address < 0x2000) {
    return ppu->bus->mapper->chr_read8(ppu->bus->mapper, address);
  }

  if (address < 0x3000) {
    u16 real_address = ppu_get_nametable_mirrored_address(ppu, address);
    return memory_read8(ppu->nametable_memory, real_address - 0x2000);
  }

  if (address < 0x3F00 || address > 0x3FFF) {
    printf("Invalid ppu_internal_read8 with address %04X\n", address);
    return 0;
  }

  return memory_read8(ppu->palette_memory, address - 0x3F00);
}

void ppu_internal_write8(ppu_t* ppu, u16 address, u8 value) {
  fflush(stdout);

  if (address < 0x2000) {
    ppu->bus->mapper->chr_write8(ppu->bus->mapper, address, value);
    return;
  }

  if (address < 0x3000) {
    u16 real_address = ppu_get_nametable_mirrored_address(ppu, address);
    memory_write8(ppu->nametable_memory, real_address - 0x2000, value);
    return;
  }

  if (address < 0x3F00 || address > 0x3FFF) {
    printf("Invalid ppu_internal_read8 with address %04X and value %02X\n",
           address, value);
    return;
  }

  memory_write8(ppu->palette_memory, address - 0x3F00, value);
}