#include "../framework.h"
#include "../mocks/bus.h"

TEST_BEGIN(should_allow_reading_from_prg_rom) {
  bus_t* bus = mock_bus();

  ASSERT(bus_read8(bus, 0x4020) == 0x78);
  ASSERT(bus_read8(bus, 0x4021) == 0xD8);
}
TEST_END

SUITE_BEGIN(mapper_0)
SUITE_ADD(should_allow_reading_from_prg_rom)
SUITE_END