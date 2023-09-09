#include "../framework.h"
#include "../mocks/cpu.h"

TEST_BEGIN(should_execute_clc) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020, 0x18);

  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_cld) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020, 0xD8);

  cpu->status.d = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.d == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_cli) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020, 0x58);

  cpu->status.i = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.i == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_clv) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020, 0xB8);

  cpu->status.v = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.v == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_sec) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020, 0x38);

  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 1);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_sed) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020, 0xF8);

  cpu->status.d = 0;

  cpu_execute(cpu);
  ASSERT(cpu->status.d == 1);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_sei) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020, 0x78);

  cpu->status.i = 0;

  cpu_execute(cpu);
  ASSERT(cpu->status.i == 1);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

SUITE_BEGIN(cpu)
SUITE_ADD(should_execute_clc)
SUITE_ADD(should_execute_cld)
SUITE_ADD(should_execute_cli)
SUITE_ADD(should_execute_clv)
SUITE_ADD(should_execute_sec)
SUITE_ADD(should_execute_sed)
SUITE_ADD(should_execute_sei)
SUITE_END