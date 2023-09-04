#include "../../src/memory/bus.h"
#include "../framework.h"

TEST_BEGIN(should_read_and_write_same_byte) {
  bus_t* bus = bus_create();

  bus_write8(bus, 0x0100, 0x10);
  ASSERT(bus_read8(bus, 0x0100) == 0x10);

  bus_write8(bus, 0x0900, 0x11);
  ASSERT(bus_read8(bus, 0x0900) == 0x11);

  bus_write8(bus, 0x1100, 0x12);
  ASSERT(bus_read8(bus, 0x1100) == 0x12);

  bus_write8(bus, 0x1900, 0x13);
  ASSERT(bus_read8(bus, 0x1900) == 0x13);

  bus_write8(bus, 0x2002, 0x14);
  ASSERT(bus_read8(bus, 0x2002) == 0x14);

  bus_write8(bus, 0x2100, 0x15);
  ASSERT(bus_read8(bus, 0x2100) == 0x15);

  bus_write8(bus, 0x4012, 0x16);
  ASSERT(bus_read8(bus, 0x4012) == 0x16);

  bus_write8(bus, 0x401A, 0x17);
  ASSERT(bus_read8(bus, 0x401A) == 0x17);

  bus_write8(bus, 0x4500, 0x18);
  ASSERT(bus_read8(bus, 0x4500) == 0x18);
}
TEST_END

TEST_BEGIN(should_read_and_write_mirrored) {
  bus_t* bus = bus_create();

  bus_write8(bus, 0x0100, 0x10);
  ASSERT(bus_read8(bus, 0x0100) == 0x10);
  ASSERT(bus_read8(bus, 0x0900) == 0x10);
  ASSERT(bus_read8(bus, 0x1100) == 0x10);
  ASSERT(bus_read8(bus, 0x1900) == 0x10);

  bus_write8(bus, 0x2002, 0x11);
  ASSERT(bus_read8(bus, 0x2002) == 0x11);
  ASSERT(bus_read8(bus, 0x2102) == 0x11);
  ASSERT(bus_read8(bus, 0x210A) == 0x11);
}
TEST_END

SUITE_BEGIN(bus)
SUITE_ADD(should_read_and_write_same_byte)
SUITE_ADD(should_read_and_write_mirrored)
SUITE_END