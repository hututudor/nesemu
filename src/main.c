#include <stdio.h>
#include <stdlib.h>

#include "nes/nes.h"

int main() {
  nes_t* nes = nes_create();

  bus_write8(nes->bus, 0x0010, 0x23);
  u8 value = bus_read8(nes->bus, 0x0810);

  printf("%02X\n", value);

  nes_destroy(nes);

  return 0;
}