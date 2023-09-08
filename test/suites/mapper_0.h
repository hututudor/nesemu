#include "../framework.h"
#include "../mocks/bus.h"

TEST_BEGIN(should_allow_reading_from_prg_rom) {
  bus_t* bus = mock_bus();

  ASSERT(bus_read8(bus, 0xC000) == 0x78);
  ASSERT(bus_read8(bus, 0xC001) == 0xD8);

  ASSERT(bus_read16(bus, 0xC000) == 0xD878);
}
TEST_END

SUITE_BEGIN(mapper_0)
SUITE_ADD(should_allow_reading_from_prg_rom)
SUITE_END