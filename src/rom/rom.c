#include "rom.h"

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

rom_header_t parse_header(u8* data);

rom_t* rom_load(u8* data) {
  rom_t* rom = (rom_t*)calloc(1, sizeof(rom_t));

  rom->header = parse_header(data);

  u32 data_offset = 16;  // header offset
  if (rom->header.has_trainer) {
    data_offset += 512;
  }

  if (rom->header.prg_rom_size) {
    rom->prg_rom = (u8*)calloc(rom->header.prg_rom_size, 0x4000);

    s8 prg_rom_total_size = rom->header.prg_rom_size * 0x4000;
    memcpy(rom->prg_rom, data + data_offset, prg_rom_total_size);
    data_offset += prg_rom_total_size;
  }

  if (rom->header.chr_rom_size) {
    rom->chr_rom = (u8*)calloc(rom->header.chr_rom_size, 0x2000);

    s8 chr_rom_total_size = rom->header.chr_rom_size * 0x2000;
    memcpy(rom->chr_rom, data + data_offset, chr_rom_total_size);
  }

  return rom;
}

bool rom_is_valid(u8* data) {
  return data && data[0] == 'N' && data[1] == 'E' && data[2] == 'S' &&
         data[3] == 0x1A;
}

rom_header_t parse_header(u8* data) {
  rom_header_t header = {0};

  header.prg_rom_size = data[4];
  header.chr_rom_size = data[5];

  u8 flag6 = data[6];
  header.mirroring = flag6 & 0x01;
  header.has_persistent_memory = (flag6 & 0x02) >> 1;
  header.has_trainer = (flag6 & 0x04) >> 2;
  header.four_screen_mirroring = (flag6 & 0x08) >> 3;
  header.mapper_number = flag6 >> 4;

  u8 flag7 = data[7];
  header.vs_unisystem = flag7 & 0x01;
  header.is_nes_2 = ((flag7 & 0x04) >> 2 == 1) && ((flag7 & 0x08) >> 3 == 1);
  header.mapper_number |= (flag7 >> 4) << 4;

  u8 flag8 = data[8];
  header.prg_ram_size = flag8;

  u8 flag9 = data[9];
  header.tv_system = flag9 & 0x01;

  return header;
}

void rom_debug_print(rom_t* rom) {
  if (!rom) {
    printf("ROM: null\n");
    return;
  }

  printf("ROM\n");
  printf("  Mapper: %d\n", rom->header.mapper_number);

  printf("  PRG ROM: %04X (%d) | CHR ROM: %04X (%d) | PRG RAM: ? (%d)\n",
         rom->header.prg_rom_size * 0x4000, rom->header.prg_rom_size,
         rom->header.chr_rom_size * 0x2000, rom->header.chr_rom_size,
         rom->header.prg_ram_size);

  printf(
      "  Mirroring: %c | Four Screen Mirroring: %d | Battery: %d | Trainer: "
      "%d\n",
      rom->header.mirroring == MIRRORING_HORIZONTAL ? 'H' : 'V',
      rom->header.four_screen_mirroring, rom->header.has_persistent_memory,
      rom->header.has_trainer);

  printf("  TV system: %s | VS Unisystem: %d | NES 2.0 Format %d\n",
         rom->header.tv_system == TV_SYSTEM_PAL ? "PAL" : "NTSC",
         rom->header.vs_unisystem, rom->header.is_nes_2);
}