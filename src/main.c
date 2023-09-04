#include <stdio.h>
#include <stdlib.h>

#include "memory/bus.h"

int main() {
  bus_t* bus = bus_create();

  bus_write8(bus, 0x0010, 0x23);
  u8 value = bus_read8(bus, 0x0810);

  printf("%02X\n", value);

  bus_destroy(bus);

  return 0;
}