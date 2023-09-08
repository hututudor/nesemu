#include "../framework.h"
#include "../mocks/cpu.h"

TEST_BEGIN(should_execute_sei) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000, 0x78);

  cpu->status.i = 0;

  cpu_execute(cpu);
  ASSERT(cpu->status.i == 1);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

SUITE_BEGIN(cpu)
SUITE_ADD(should_execute_sei)
SUITE_END