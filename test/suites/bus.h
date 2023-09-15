#include "../framework.h"
#include "../mocks/bus.h"

TEST_BEGIN(should_read_and_write_same_byte) {
  bus_t* bus = mock_bus();

  bus_write8(bus, 0x0100, 0x10);
  ASSERT(bus_read8(bus, 0x0100) == 0x10);

  bus_write8(bus, 0x0900, 0x11);
  ASSERT(bus_read8(bus, 0x0900) == 0x11);

  bus_write8(bus, 0x1100, 0x12);
  ASSERT(bus_read8(bus, 0x1100) == 0x12);

  bus_write8(bus, 0x1900, 0x13);
  ASSERT(bus_read8(bus, 0x1900) == 0x13);

  bus_write8(bus, 0x4012, 0x16);
  ASSERT(bus_read8(bus, 0x4012) == 0x16);
}
TEST_END

TEST_BEGIN(should_read_and_write_same_2_bytes) {
  bus_t* bus = mock_bus();

  bus_write16(bus, 0x0100, 0x1020);
  ASSERT(bus_read16(bus, 0x0100) == 0x1020);

  bus_write16(bus, 0x0900, 0x1120);
  ASSERT(bus_read16(bus, 0x0900) == 0x1120);

  bus_write16(bus, 0x1100, 0x1220);
  ASSERT(bus_read16(bus, 0x1100) == 0x1220);

  bus_write16(bus, 0x1900, 0x1320);
  ASSERT(bus_read16(bus, 0x1900) == 0x1320);

  bus_write16(bus, 0x4012, 0x1620);
  ASSERT(bus_read16(bus, 0x4012) == 0x1620);
}
TEST_END

TEST_BEGIN(should_read_and_write_mirrored) {
  bus_t* bus = mock_bus();

  bus_write8(bus, 0x0100, 0x10);
  ASSERT(bus_read8(bus, 0x0100) == 0x10);
  ASSERT(bus_read8(bus, 0x0900) == 0x10);
  ASSERT(bus_read8(bus, 0x1100) == 0x10);
  ASSERT(bus_read8(bus, 0x1900) == 0x10);
}
TEST_END

SUITE_BEGIN(bus)
SUITE_ADD(should_read_and_write_same_byte)
SUITE_ADD(should_read_and_write_same_2_bytes)
SUITE_ADD(should_read_and_write_mirrored)
SUITE_END