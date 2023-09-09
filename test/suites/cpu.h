#include "../framework.h"
#include "../mocks/cpu.h"

TEST_BEGIN(should_execute_lda_immediate) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDA_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x00);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_LDA_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC003 - 0x4020, 0xFF);

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x00);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 1);

  cpu_execute(cpu);
  ASSERT(cpu->a == 0xFF);
  ASSERT(cpu->status.n == 1);
  ASSERT(cpu->status.z == 0);
}
TEST_END

TEST_BEGIN(should_execute_ldx_immediate) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x00);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC003 - 0x4020, 0xFF);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0x00);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 1);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0xFF);
  ASSERT(cpu->status.n == 1);
  ASSERT(cpu->status.z == 0);
}
TEST_END

TEST_BEGIN(should_execute_ldy_immediate) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDY_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x00);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_LDY_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC003 - 0x4020, 0xFF);

  cpu_execute(cpu);
  ASSERT(cpu->y == 0x00);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 1);

  cpu_execute(cpu);
  ASSERT(cpu->y == 0xFF);
  ASSERT(cpu->status.n == 1);
  ASSERT(cpu->status.z == 0);
}
TEST_END

TEST_BEGIN(should_execute_clc) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_CLC);

  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_cld) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_CLD);

  cpu->status.d = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.d == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_cli) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_CLI);

  cpu->status.i = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.i == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_clv) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_CLV);

  cpu->status.v = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.v == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_sec) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_SEC);

  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 1);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_sed) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_SED);

  cpu->status.d = 0;

  cpu_execute(cpu);
  ASSERT(cpu->status.d == 1);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_sei) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_SEI);

  cpu->status.i = 0;

  cpu_execute(cpu);
  ASSERT(cpu->status.i == 1);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

SUITE_BEGIN(cpu)
SUITE_ADD(should_execute_lda_immediate)
SUITE_ADD(should_execute_ldx_immediate)
SUITE_ADD(should_execute_ldy_immediate)
SUITE_ADD(should_execute_clc)
SUITE_ADD(should_execute_cld)
SUITE_ADD(should_execute_cli)
SUITE_ADD(should_execute_clv)
SUITE_ADD(should_execute_sec)
SUITE_ADD(should_execute_sed)
SUITE_ADD(should_execute_sei)
SUITE_END