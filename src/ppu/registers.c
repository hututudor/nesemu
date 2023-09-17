#include "ppu.h"

u8 ppu_read_ctrl(ppu_t* ppu) { return 0x00; }
void ppu_write_ctrl(ppu_t* ppu, u8 value) {}

u8 ppu_read_mask(ppu_t* ppu) { return 0x00; }
void ppu_write_mask(ppu_t* ppu, u8 value) {}

u8 ppu_read_status(ppu_t* ppu) { return 0x00; }
void ppu_write_status(ppu_t* ppu, u8 value) {}

u8 ppu_read_oam_addr(ppu_t* ppu) { return 0x00; }
void ppu_write_oam_addr(ppu_t* ppu, u8 value) {}

u8 ppu_read_oam_data(ppu_t* ppu) { return 0x00; }
void ppu_write_oam_data(ppu_t* ppu, u8 value) {}

u8 ppu_read_scroll(ppu_t* ppu) { return 0x00; }
void ppu_write_scroll(ppu_t* ppu, u8 value) {}

u8 ppu_read_addr(ppu_t* ppu) { return 0x00; }
void ppu_write_addr(ppu_t* ppu, u8 value) {}

u8 ppu_read_data(ppu_t* ppu) { return 0x00; }
void ppu_write_data(ppu_t* ppu, u8 value) {}

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

  if (address < 0x3F00) {
    return memory_read8(ppu->nametable_memory, address - 0x2000);
  }

  return memory_read8(ppu->palette_memory, address - 0x3F00);
}

void ppu_internal_write8(ppu_t* ppu, u16 address, u8 value) {
  if (address < 0x2000) {
    ppu->bus->mapper->chr_write8(ppu->bus->mapper, address, value);
    return;
  }

  if (address < 0x3F00) {
    memory_write8(ppu->nametable_memory, address - 0x2000, value);
    return;
  }

  memory_write8(ppu->palette_memory, address - 0x3F00, value);
}