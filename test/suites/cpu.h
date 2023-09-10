#include "../framework.h"
#include "../mocks/cpu.h"

TEST_BEGIN(should_execute_sta_absolute) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDA_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x20);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_STA_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC003 - 0x4020, 0x0002);

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x20);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_stx_absolute) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x20);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_STX_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC003 - 0x4020, 0x0002);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0x20);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_sty_absolute) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDY_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x20);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_STY_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC003 - 0x4020, 0x0002);

  cpu_execute(cpu);
  ASSERT(cpu->y == 0x20);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x20);
}
TEST_END

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

TEST_BEGIN(should_execute_adc_immediate) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_ADC_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x05);

  cpu->a = 0x02;
  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(cpu->a = 0x08);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.v == 0);
}
TEST_END

TEST_BEGIN(should_execute_sbc_immediate) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_SBC_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x04);

  cpu->a = 0x05;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x00);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.v == 0);
}
TEST_END

TEST_BEGIN(should_execute_tax) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDA_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFF);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_TAX);

  cpu_execute(cpu);
  ASSERT(cpu->a == 0xFF);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0xFF);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_tay) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDA_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x00);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_TAY);

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x00);

  cpu_execute(cpu);
  ASSERT(cpu->y == 0x00);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_txa) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFF);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_TXA);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0xFF);

  cpu_execute(cpu);
  ASSERT(cpu->a == 0xFF);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_tya) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDY_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x00);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_TYA);

  cpu_execute(cpu);
  ASSERT(cpu->y == 0x00);

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x00);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_txs) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFF);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_TXS);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0xFF);

  cpu_execute(cpu);
  ASSERT(cpu->sp == 0xFF);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_tsx) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFF);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_TXS);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC003 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC004 - 0x4020, 0x00);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC005 - 0x4020,
                               INSTRUCTION_TSX);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0xFF);

  cpu_execute(cpu);
  ASSERT(cpu->sp == 0xFF);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0x00);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0xFF);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_bit_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x1212, 0xD0);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0x1212, 0xD0);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_BIT_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC001 - 0x4020, 0x1212);

  cpu->a = 0x00;

  cpu_execute(cpu);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.v == 1);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_cmp_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x1212, 0xD0);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0x1212, 0xD0);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_CMP_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC001 - 0x4020, 0x1212);

  cpu->a = 0xC0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_cpx_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x1212, 0xD0);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0x1212, 0xD0);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_CPX_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC001 - 0x4020, 0x1212);

  cpu->x = 0xD0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 1);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_cpy_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x1212, 0xD0);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0x1212, 0xD0);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_CPY_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC001 - 0x4020, 0x1212);

  cpu->y = 0xE0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 1);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_inc_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0xFF);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_INC_ZP);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x02);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x00002) == 0x00);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_inc_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0003, 0xFF);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x01);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_INC_ZP_X);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC003 - 0x4020, 0x02);

  cpu_execute(cpu);
  ASSERT(cpu->x == 1);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0003) == 0x00);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_inc_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0202, 0xFE);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_INC_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC001 - 0x4020, 0x0202);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0202) == 0xFF);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_inc_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0103, 0xFE);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x01);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_INC_ABSOLUTE_X);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC003 - 0x4020, 0x0102);

  cpu_execute(cpu);
  ASSERT(cpu->x == 1);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0103) == 0xFF);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_inx) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFF);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_INX);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0xFF);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0x00);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_iny) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDY_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFF);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_INY);

  cpu_execute(cpu);
  ASSERT(cpu->y == 0xFF);

  cpu_execute(cpu);
  ASSERT(cpu->y == 0x00);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_dec_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x01);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_DEC_ZP);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x02);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x00002) == 0x00);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_dec_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0003, 0x00);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x01);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_DEC_ZP_X);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC003 - 0x4020, 0x02);

  cpu_execute(cpu);
  ASSERT(cpu->x == 1);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0003) == 0xFF);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_dec_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0202, 0xFF);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_DEC_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC001 - 0x4020, 0x0202);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0202) == 0xFE);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_dec_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0103, 0x01);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0x01);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_DEC_ABSOLUTE_X);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC003 - 0x4020, 0x0102);

  cpu_execute(cpu);
  ASSERT(cpu->x == 1);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0103) == 0x00);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_dex) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDX_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFF);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_DEX);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0xFF);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0xFE);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_dey) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_LDY_IMMEDIATE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFF);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC002 - 0x4020,
                               INSTRUCTION_DEY);

  cpu_execute(cpu);
  ASSERT(cpu->y == 0xFF);

  cpu_execute(cpu);
  ASSERT(cpu->y == 0xFE);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_jsr_absolute) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_JSR_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC001 - 0x4020, 0xC008);

  cpu->sp = 0xFF;

  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC008);
  ASSERT(cpu->sp == 0xFD);
  ASSERT(bus_read8(cpu->bus, 0x00FF) == 0xC0);
  ASSERT(bus_read8(cpu->bus, 0x00FE) == 0x02);
}
TEST_END

TEST_BEGIN(should_execute_rts_absolute) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_JSR_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC001 - 0x4020, 0xC008);

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC008 - 0x4020,
                               INSTRUCTION_RTS);

  cpu->sp = 0xFF;

  cpu_execute(cpu);
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC003);
  ASSERT(cpu->sp == 0xFF);
}
TEST_END

TEST_BEGIN(should_execute_jmp_absolute) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_JMP_ABSOLUTE);
  cpu->bus->mapper->prg_write16(cpu->bus->mapper, 0xC001 - 0x4020, 0xC008);

  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC008);
}
TEST_END

TEST_BEGIN(should_execute_bcc_relative) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_BCC_RELATIVE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFE);

  cpu->status.c = 0;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC000);

  cpu->status.c = 1;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC002);
}
TEST_END

TEST_BEGIN(should_execute_bcs_relative) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_BCS_RELATIVE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFE);

  cpu->status.c = 1;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC000);

  cpu->status.c = 0;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC002);
}
TEST_END

TEST_BEGIN(should_execute_beq_relative) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_BEQ_RELATIVE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFE);

  cpu->status.z = 1;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC000);

  cpu->status.z = 0;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC002);
}
TEST_END

TEST_BEGIN(should_execute_bne_relative) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_BNE_RELATIVE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFE);

  cpu->status.z = 0;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC000);

  cpu->status.z = 1;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC002);
}
TEST_END

TEST_BEGIN(should_execute_bmi_relative) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_BMI_RELATIVE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFE);

  cpu->status.n = 1;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC000);

  cpu->status.n = 0;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC002);
}
TEST_END

TEST_BEGIN(should_execute_bpl_relative) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_BPL_RELATIVE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFE);

  cpu->status.n = 0;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC000);

  cpu->status.n = 1;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC002);
}
TEST_END

TEST_BEGIN(should_execute_bvc_relative) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_BVC_RELATIVE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFE);

  cpu->status.v = 0;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC000);

  cpu->status.v = 1;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC002);
}
TEST_END

TEST_BEGIN(should_execute_bvs_relative) {
  cpu_t* cpu = mock_cpu();

  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC000 - 0x4020,
                               INSTRUCTION_BVS_RELATIVE);
  cpu->bus->mapper->prg_write8(cpu->bus->mapper, 0xC001 - 0x4020, 0xFE);

  cpu->status.v = 1;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC000);

  cpu->status.v = 0;
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC002);
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

SUITE_BEGIN(cpu) {
  SUITE_ADD(should_execute_lda_immediate);
  SUITE_ADD(should_execute_ldx_immediate);
  SUITE_ADD(should_execute_ldy_immediate);

  SUITE_ADD(should_execute_sta_absolute);
  SUITE_ADD(should_execute_stx_absolute);
  SUITE_ADD(should_execute_sty_absolute);

  SUITE_ADD(should_execute_adc_immediate);
  SUITE_ADD(should_execute_sbc_immediate);

  SUITE_ADD(should_execute_tax);
  SUITE_ADD(should_execute_txa);
  SUITE_ADD(should_execute_tya);
  SUITE_ADD(should_execute_txs);
  SUITE_ADD(should_execute_tsx);
  SUITE_ADD(should_execute_tay);

  SUITE_ADD(should_execute_bit_absolute);
  SUITE_ADD(should_execute_cmp_absolute);
  SUITE_ADD(should_execute_cpx_absolute);
  SUITE_ADD(should_execute_cpy_absolute);

  SUITE_ADD(should_execute_inc_zp);
  SUITE_ADD(should_execute_inc_zp_x);
  SUITE_ADD(should_execute_inc_absolute);
  SUITE_ADD(should_execute_inc_absolute_x);
  SUITE_ADD(should_execute_inx);
  SUITE_ADD(should_execute_iny);
  SUITE_ADD(should_execute_dec_zp);
  SUITE_ADD(should_execute_dec_zp_x);
  SUITE_ADD(should_execute_dec_absolute);
  SUITE_ADD(should_execute_dec_absolute_x);
  SUITE_ADD(should_execute_dex);
  SUITE_ADD(should_execute_dey);

  SUITE_ADD(should_execute_jsr_absolute);
  SUITE_ADD(should_execute_rts_absolute);
  SUITE_ADD(should_execute_jmp_absolute);

  SUITE_ADD(should_execute_bcc_relative);
  SUITE_ADD(should_execute_bcs_relative);
  SUITE_ADD(should_execute_beq_relative);
  SUITE_ADD(should_execute_bne_relative);
  SUITE_ADD(should_execute_bmi_relative);
  SUITE_ADD(should_execute_bpl_relative);
  SUITE_ADD(should_execute_bvc_relative);
  SUITE_ADD(should_execute_bvs_relative);

  SUITE_ADD(should_execute_clc);
  SUITE_ADD(should_execute_cld);
  SUITE_ADD(should_execute_cli);
  SUITE_ADD(should_execute_clv);
  SUITE_ADD(should_execute_sec);
  SUITE_ADD(should_execute_sed);
  SUITE_ADD(should_execute_sei);
}
SUITE_END