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