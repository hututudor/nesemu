#include "../framework.h"
#include "../mocks/cpu.h"

TEST_BEGIN(should_execute_sta_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STA_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x20;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_sta_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STA_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x20;
  cpu->x = 0x05;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0007) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_sta_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STA_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x20;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_sta_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STA_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x20;
  cpu->x = 0x05;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0007) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_sta_absolute_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STA_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0007);

  cpu->a = 0x20;
  cpu->y = 0x05;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0007) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_sta_indirect_x) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0007, 0x0202);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STA_INDIRECT_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x20;
  cpu->x = 0x05;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0202) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_sta_indirect_y) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0002, 0x0200);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STA_INDIRECT_Y);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x20;
  cpu->y = 0x05;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0205) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_stx_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STX_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->x = 0x20;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_stx_zp_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STX_ZP_Y);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->x = 0x20;
  cpu->y = 0x05;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0007) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_stx_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STX_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->x = 0x20;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_sty_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STY_ZP);
  bus_write16(cpu->bus, 0xC001, 0x02);

  cpu->y = 0x20;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_sty_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STY_ZP_X);
  bus_write16(cpu->bus, 0xC001, 0x02);

  cpu->y = 0x20;
  cpu->x = 0x05;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0007) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_sty_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_STY_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->y = 0x20;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_lda_immediate) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDA_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x00);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_LDA_IMMEDIATE);
  bus_write8(cpu->bus, 0xC003, 0xFF);

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

TEST_BEGIN(should_execute_lda_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDA_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_lda_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0007, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDA_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->x = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_lda_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0203, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDA_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0203);

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_lda_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0208, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDA_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0203);

  cpu->x = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_lda_absolute_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0208, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDA_ABSOLUTE_Y);
  bus_write16(cpu->bus, 0xC001, 0x0203);

  cpu->y = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_lda_indirect_x) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0007, 0x0202);
  bus_write8(cpu->bus, 0x0202, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDA_INDIRECT_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->x = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_lda_indirect_y) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0002, 0x0202);
  bus_write8(cpu->bus, 0x0207, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDA_INDIRECT_Y);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->y = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_ldx_immediate) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x00);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC003, 0xFF);

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

TEST_BEGIN(should_execute_ldx_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_ldx_zp_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0007, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_ZP_Y);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->y = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->x == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_ldx_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu_execute(cpu);
  ASSERT(cpu->x == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_ldx_absolute_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0007, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_ABSOLUTE_Y);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->y = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->x == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_ldy_immediate) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDY_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x00);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_LDY_IMMEDIATE);
  bus_write8(cpu->bus, 0xC003, 0xFF);

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

TEST_BEGIN(should_execute_ldy_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDY_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu_execute(cpu);
  ASSERT(cpu->y == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_ldy_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0007, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDY_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->x = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->y == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_ldy_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDY_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu_execute(cpu);
  ASSERT(cpu->y == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_ldy_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0007, 0x10);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDY_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->x = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->y == 0x10);
}
TEST_END

TEST_BEGIN(should_execute_adc_immediate) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ADC_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x05);

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

TEST_BEGIN(should_execute_adc_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x05);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ADC_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

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

TEST_BEGIN(should_execute_adc_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0007, 0x05);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ADC_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x02;
  cpu->x = 0x05;
  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(cpu->a = 0x08);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.v == 0);
}
TEST_END

TEST_BEGIN(should_execute_adc_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x05);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ADC_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

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

TEST_BEGIN(should_execute_adc_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x02);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ADC_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x02;
  cpu->x = 0x03;
  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(cpu->a = 0x08);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.v == 0);
}
TEST_END

TEST_BEGIN(should_execute_adc_absolute_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x02);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ADC_ABSOLUTE_Y);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x02;
  cpu->y = 0x03;
  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(cpu->a = 0x08);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.v == 0);
}
TEST_END

TEST_BEGIN(should_execute_adc_indirect_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x05);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ADC_INDIRECT_X);
  bus_write16(cpu->bus, 0xC001, 0x01);

  cpu->a = 0x02;
  cpu->x = 0x01;
  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(cpu->a = 0x08);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.v == 0);
}
TEST_END

TEST_BEGIN(should_execute_adc_indirect_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0007, 0x05);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ADC_INDIRECT_Y);
  bus_write16(cpu->bus, 0xC001, 0x05);

  cpu->a = 0x02;
  cpu->x = 0x02;
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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_SBC_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x04);

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

TEST_BEGIN(should_execute_sbc_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x04);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_SBC_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

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

TEST_BEGIN(should_execute_sbc_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0003, 0x04);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_SBC_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x05;
  cpu->x = 0x01;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x00);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.v == 0);
}
TEST_END

TEST_BEGIN(should_execute_sbc_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x04);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_SBC_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

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

TEST_BEGIN(should_execute_sbc_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0003, 0x04);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_SBC_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x05;
  cpu->x = 0x01;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x00);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.v == 0);
}
TEST_END

TEST_BEGIN(should_execute_sbc_absolute_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0003, 0x04);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_SBC_ABSOLUTE_Y);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x05;
  cpu->y = 0x01;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x00);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.v == 0);
}
TEST_END

TEST_BEGIN(should_execute_sbc_indirect_x) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0003, 0x0204);
  bus_write8(cpu->bus, 0x0204, 0x04);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_SBC_INDIRECT_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x05;
  cpu->x = 0x01;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x00);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.n == 0);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.v == 0);
}
TEST_END

TEST_BEGIN(should_execute_sbc_indirect_y) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0002, 0x0204);
  bus_write8(cpu->bus, 0x0205, 0x04);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_SBC_INDIRECT_Y);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x05;
  cpu->y = 0x01;
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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDA_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0xFF);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_TAX);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDA_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x00);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_TAY);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0xFF);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_TXA);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDY_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x00);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_TYA);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0xFF);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_TXS);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0xFF);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_TXS);

  bus_write8(cpu->bus, 0xC003, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC004, 0x00);

  bus_write8(cpu->bus, 0xC005, INSTRUCTION_TSX);

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

TEST_BEGIN(should_execute_pha_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_PHA);

  cpu->a = 0x20;
  cpu->sp = 0xFF;

  cpu_execute(cpu);
  ASSERT(cpu->sp == 0xFE);
  ASSERT(bus_read8(cpu->bus, 0x01FF) == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_pla_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x01FF, 0x20);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_PLA);

  cpu->sp = 0xFE;

  cpu_execute(cpu);
  ASSERT(cpu->sp == 0xFF);
  ASSERT(cpu->a == 0x20);
}
TEST_END

TEST_BEGIN(should_execute_php_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_PHP);

  cpu->sp = 0xFF;
  cpu->status.c = 1;
  cpu->status.v = 1;
  cpu->status.n = 1;

  cpu_execute(cpu);
  ASSERT(cpu->sp == 0xFE);
  ASSERT(bus_read8(cpu->bus, 0x01FF) == 0b11110101);
}
TEST_END

TEST_BEGIN(should_execute_plp_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x01FF, 0b11110101);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_PLP);

  cpu->sp = 0xFE;

  cpu_execute(cpu);
  ASSERT(cpu->sp == 0xFF);
  ASSERT(cpu->status.c == 1);
  ASSERT(cpu->status.v == 1);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_and_immediate) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_AND_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x03);

  cpu->a = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x01);
}
TEST_END

TEST_BEGIN(should_execute_and_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_AND_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x01);
}
TEST_END

TEST_BEGIN(should_execute_and_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_AND_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x05;
  cpu->x = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x01);
}
TEST_END

TEST_BEGIN(should_execute_and_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_AND_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x01);
}
TEST_END

TEST_BEGIN(should_execute_and_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_AND_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x05;
  cpu->x = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x01);
}
TEST_END

TEST_BEGIN(should_execute_and_absolute_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_AND_ABSOLUTE_Y);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x05;
  cpu->y = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x01);
}
TEST_END

TEST_BEGIN(should_execute_and_indirect_x) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0005, 0x0302);
  bus_write8(cpu->bus, 0x0302, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_AND_INDIRECT_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x05;
  cpu->x = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x01);
}
TEST_END

TEST_BEGIN(should_execute_and_indirect_y) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0002, 0x0302);
  bus_write8(cpu->bus, 0x0305, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_AND_INDIRECT_Y);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x05;
  cpu->y = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x01);
}
TEST_END

TEST_BEGIN(should_execute_eor_immediate) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_EOR_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x03);

  cpu->a = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x06);
}
TEST_END

TEST_BEGIN(should_execute_eor_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_EOR_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x06);
}
TEST_END

TEST_BEGIN(should_execute_eor_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_EOR_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x05;
  cpu->x = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x06);
}
TEST_END

TEST_BEGIN(should_execute_eor_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_EOR_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x05;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x06);
}
TEST_END

TEST_BEGIN(should_execute_eor_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_EOR_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x05;
  cpu->x = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x06);
}
TEST_END

TEST_BEGIN(should_execute_eor_absolute_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_EOR_ABSOLUTE_Y);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x05;
  cpu->y = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x06);
}
TEST_END

TEST_BEGIN(should_execute_eor_indirect_x) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0005, 0x0302);
  bus_write8(cpu->bus, 0x0302, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_EOR_INDIRECT_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x05;
  cpu->x = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x06);
}
TEST_END

TEST_BEGIN(should_execute_eor_indirect_y) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0002, 0x0302);
  bus_write8(cpu->bus, 0x0305, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_EOR_INDIRECT_Y);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x05;
  cpu->y = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x06);
}
TEST_END

TEST_BEGIN(should_execute_ora_immediate) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ORA_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x03);

  cpu->a = 0x04;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x07);
}
TEST_END

TEST_BEGIN(should_execute_ora_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ORA_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x04;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x07);
}
TEST_END

TEST_BEGIN(should_execute_ora_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ORA_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->a = 0x04;
  cpu->x = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x07);
}
TEST_END

TEST_BEGIN(should_execute_ora_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ORA_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x04;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x07);
}
TEST_END

TEST_BEGIN(should_execute_ora_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ORA_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x04;
  cpu->x = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x07);
}
TEST_END

TEST_BEGIN(should_execute_ora_absolute_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ORA_ABSOLUTE_Y);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x04;
  cpu->y = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x07);
}
TEST_END

TEST_BEGIN(should_execute_ora_indirect_x) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0005, 0x0302);
  bus_write16(cpu->bus, 0x0302, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ORA_INDIRECT_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x04;
  cpu->x = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x07);
}
TEST_END

TEST_BEGIN(should_execute_ora_indirect_y) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0002, 0x0302);
  bus_write16(cpu->bus, 0x0305, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ORA_INDIRECT_Y);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->a = 0x04;
  cpu->y = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x07);
}
TEST_END

TEST_BEGIN(should_execute_bit_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0012, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_BIT_ZP);
  bus_write16(cpu->bus, 0xC001, 0x12);

  cpu->a = 0x00;

  cpu_execute(cpu);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.v == 1);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_bit_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x1212, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_BIT_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x1212);

  cpu->a = 0x00;

  cpu_execute(cpu);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.v == 1);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_cmp_immediate) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CMP_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0xD0);

  cpu->a = 0xC0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_cmp_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0012, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CMP_ZP);
  bus_write8(cpu->bus, 0xC001, 0x12);

  cpu->a = 0xC0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_cmp_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0012, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CMP_ZP_X);
  bus_write16(cpu->bus, 0xC001, 0x10);

  cpu->a = 0xC0;
  cpu->x = 0x02;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_cmp_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x1212, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CMP_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x1212);

  cpu->a = 0xC0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_cmp_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0012, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CMP_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0010);

  cpu->a = 0xC0;
  cpu->x = 0x02;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_cmp_absolute_y) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0012, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CMP_ABSOLUTE_Y);
  bus_write16(cpu->bus, 0xC001, 0x0010);

  cpu->a = 0xC0;
  cpu->y = 0x02;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_cmp_indirect_x) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0012, 0x1212);
  bus_write8(cpu->bus, 0x1212, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CMP_INDIRECT_X);
  bus_write8(cpu->bus, 0xC001, 0x10);

  cpu->a = 0xC0;
  cpu->x = 0x02;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_cmp_indirect_y) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x0012, 0x1212);
  bus_write8(cpu->bus, 0x1215, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CMP_INDIRECT_Y);
  bus_write8(cpu->bus, 0xC001, 0x12);

  cpu->a = 0xC0;
  cpu->y = 0x03;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_cpx_immediate) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CPX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0xD0);

  cpu->x = 0xD0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 1);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_cpx_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0012, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CPX_ZP);
  bus_write8(cpu->bus, 0xC001, 0x12);

  cpu->x = 0xD0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 1);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_cpx_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x1212, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CPX_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x1212);

  cpu->x = 0xD0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 1);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_cpy_immediate) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CPY_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0xD0);

  cpu->y = 0xE0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 1);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_cpy_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0012, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CPY_ZP);
  bus_write8(cpu->bus, 0xC001, 0x12);

  cpu->y = 0xE0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 1);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_cpy_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x1212, 0xD0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CPY_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x1212);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_INC_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x00002) == 0x00);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_inc_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0003, 0xFF);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x01);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_INC_ZP_X);
  bus_write8(cpu->bus, 0xC003, 0x02);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_INC_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0202);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0202) == 0xFF);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_inc_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0103, 0xFE);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x01);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_INC_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC003, 0x0102);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0xFF);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_INX);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDY_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0xFF);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_INY);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_DEC_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x00002) == 0x00);
  ASSERT(cpu->status.z == 1);
  ASSERT(cpu->status.n == 0);
}
TEST_END

TEST_BEGIN(should_execute_dec_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0003, 0x00);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x01);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_DEC_ZP_X);
  bus_write8(cpu->bus, 0xC003, 0x02);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_DEC_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0202);

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0202) == 0xFE);
  ASSERT(cpu->status.z == 0);
  ASSERT(cpu->status.n == 1);
}
TEST_END

TEST_BEGIN(should_execute_dec_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0103, 0x01);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0x01);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_DEC_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC003, 0x0102);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDX_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0xFF);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_DEX);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LDY_IMMEDIATE);
  bus_write8(cpu->bus, 0xC001, 0xFF);

  bus_write8(cpu->bus, 0xC002, INSTRUCTION_DEY);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_JSR_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0xC008);

  cpu->sp = 0xFF;

  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC008);
  ASSERT(cpu->sp == 0xFD);
  ASSERT(bus_read8(cpu->bus, 0x01FF) == 0xC0);
  ASSERT(bus_read8(cpu->bus, 0x01FE) == 0x02);
}
TEST_END

TEST_BEGIN(should_execute_rts_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_JSR_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0xC008);

  bus_write8(cpu->bus, 0xC008, INSTRUCTION_RTS);

  cpu->sp = 0xFF;

  cpu_execute(cpu);
  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC003);
  ASSERT(cpu->sp == 0xFF);
}
TEST_END

TEST_BEGIN(should_execute_rol_a_reg) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ROL_A_REG);

  cpu->a = 0xF0;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0xE0);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_rol_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0xF0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ROL_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0xE0);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_rol_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0xF0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ROL_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->x = 0x03;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0005) == 0xE0);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_rol_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0xF0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ROL_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0xE0);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_rol_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0xF0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ROL_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->x = 0x03;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0005) == 0xE0);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_asl_a_reg) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ASL_A_REG);

  cpu->a = 0xF0;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0xE0);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_asl_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0xF0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ASL_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0xE0);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_asl_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0xF0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ASL_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->status.c = 0;
  cpu->x = 0x03;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0005) == 0xE0);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_asl_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0xF0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ASL_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0xE0);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_asl_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0xF0);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ASL_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->status.c = 0;
  cpu->x = 0x03;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0005) == 0xE0);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_lsr_a_reg) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LSR_A_REG);

  cpu->a = 0x03;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x01);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_lsr_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LSR_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x01);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_lsr_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LSR_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->x = 0x03;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0005) == 0x01);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_lsr_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LSR_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x01);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_lsr_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_LSR_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->x = 0x03;
  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0005) == 0x01);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_ror_a_reg) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ROR_A_REG);

  cpu->a = 0x03;
  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(cpu->a == 0x81);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_ror_zp) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ROR_ZP);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x81);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_ror_zp_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ROR_ZP_X);
  bus_write8(cpu->bus, 0xC001, 0x02);

  cpu->x = 0x03;
  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0005) == 0x81);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_ror_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0002, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ROR_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0002) == 0x81);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_ror_absolute_x) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0x0005, 0x03);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_ROR_ABSOLUTE_X);
  bus_write16(cpu->bus, 0xC001, 0x0002);

  cpu->x = 0x03;
  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(bus_read8(cpu->bus, 0x0005) == 0x81);
  ASSERT(cpu->status.c == 1);
}
TEST_END

TEST_BEGIN(should_execute_jmp_absolute) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_JMP_ABSOLUTE);
  bus_write16(cpu->bus, 0xC001, 0xC008);

  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC008);
}
TEST_END

TEST_BEGIN(should_execute_bcc_relative) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_BCC_RELATIVE);
  bus_write8(cpu->bus, 0xC001, 0xFE);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_BCS_RELATIVE);
  bus_write8(cpu->bus, 0xC001, 0xFE);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_BEQ_RELATIVE);
  bus_write8(cpu->bus, 0xC001, 0xFE);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_BNE_RELATIVE);
  bus_write8(cpu->bus, 0xC001, 0xFE);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_BMI_RELATIVE);
  bus_write8(cpu->bus, 0xC001, 0xFE);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_BPL_RELATIVE);
  bus_write8(cpu->bus, 0xC001, 0xFE);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_BVC_RELATIVE);
  bus_write8(cpu->bus, 0xC001, 0xFE);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_BVS_RELATIVE);
  bus_write8(cpu->bus, 0xC001, 0xFE);

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

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CLC);

  cpu->status.c = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_cld) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CLD);

  cpu->status.d = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.d == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_cli) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CLI);

  cpu->status.i = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.i == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_clv) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_CLV);

  cpu->status.v = 1;

  cpu_execute(cpu);
  ASSERT(cpu->status.v == 0);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_sec) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_SEC);

  cpu->status.c = 0;

  cpu_execute(cpu);
  ASSERT(cpu->status.c == 1);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_sed) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_SED);

  cpu->status.d = 0;

  cpu_execute(cpu);
  ASSERT(cpu->status.d == 1);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_sei) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_SEI);

  cpu->status.i = 0;

  cpu_execute(cpu);
  ASSERT(cpu->status.i == 1);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_nop) {
  cpu_t* cpu = mock_cpu();

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_NOP);

  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xC001);
}
TEST_END

TEST_BEGIN(should_execute_brk) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0xFFFE, 0xD000);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_BRK);

  cpu->sp = 0xFF;

  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xD000);
  ASSERT(cpu->sp == 0xFC);
}
TEST_END

TEST_BEGIN(should_execute_rti) {
  cpu_t* cpu = mock_cpu();

  bus_write16(cpu->bus, 0x01FE, 0xD000);

  bus_write8(cpu->bus, 0xC000, INSTRUCTION_RTI);

  cpu->sp = 0xFC;

  cpu_execute(cpu);
  ASSERT(cpu->pc == 0xD000);
}
TEST_END

SUITE_BEGIN(cpu) {
  SUITE_ADD(should_execute_lda_immediate);
  SUITE_ADD(should_execute_lda_zp);
  SUITE_ADD(should_execute_lda_zp_x);
  SUITE_ADD(should_execute_lda_absolute);
  SUITE_ADD(should_execute_lda_absolute_x);
  SUITE_ADD(should_execute_lda_absolute_y);
  SUITE_ADD(should_execute_lda_indirect_x);
  SUITE_ADD(should_execute_lda_indirect_y);

  SUITE_ADD(should_execute_ldx_immediate);
  SUITE_ADD(should_execute_ldx_zp);
  SUITE_ADD(should_execute_ldx_zp_y);
  SUITE_ADD(should_execute_ldx_absolute);
  SUITE_ADD(should_execute_ldx_absolute_y);

  SUITE_ADD(should_execute_ldy_immediate);
  SUITE_ADD(should_execute_ldy_zp);
  SUITE_ADD(should_execute_ldy_zp_x);
  SUITE_ADD(should_execute_ldy_absolute);
  SUITE_ADD(should_execute_ldy_absolute_x);

  SUITE_ADD(should_execute_sta_zp);
  SUITE_ADD(should_execute_sta_zp_x);
  SUITE_ADD(should_execute_sta_absolute);
  SUITE_ADD(should_execute_sta_absolute_x);
  SUITE_ADD(should_execute_sta_absolute_y);
  SUITE_ADD(should_execute_sta_indirect_x);
  SUITE_ADD(should_execute_sta_indirect_y);

  SUITE_ADD(should_execute_stx_zp);
  SUITE_ADD(should_execute_stx_zp_y);
  SUITE_ADD(should_execute_stx_absolute);

  SUITE_ADD(should_execute_sty_zp);
  SUITE_ADD(should_execute_sty_zp_x);
  SUITE_ADD(should_execute_sty_absolute);

  SUITE_ADD(should_execute_adc_immediate);
  SUITE_ADD(should_execute_adc_zp);
  SUITE_ADD(should_execute_adc_zp_x);
  SUITE_ADD(should_execute_adc_absolute);
  SUITE_ADD(should_execute_adc_absolute_x);
  SUITE_ADD(should_execute_adc_absolute_y);
  SUITE_ADD(should_execute_adc_indirect_x);
  SUITE_ADD(should_execute_adc_indirect_y);

  SUITE_ADD(should_execute_sbc_immediate);
  SUITE_ADD(should_execute_sbc_zp);
  SUITE_ADD(should_execute_sbc_zp_x);
  SUITE_ADD(should_execute_sbc_absolute);
  SUITE_ADD(should_execute_sbc_absolute_x);
  SUITE_ADD(should_execute_sbc_absolute_y);
  SUITE_ADD(should_execute_sbc_indirect_x);
  SUITE_ADD(should_execute_sbc_indirect_y);

  SUITE_ADD(should_execute_tax);
  SUITE_ADD(should_execute_txa);
  SUITE_ADD(should_execute_tya);
  SUITE_ADD(should_execute_txs);
  SUITE_ADD(should_execute_tsx);
  SUITE_ADD(should_execute_tay);

  SUITE_ADD(should_execute_pha_absolute);
  SUITE_ADD(should_execute_pla_absolute);
  SUITE_ADD(should_execute_php_absolute);
  SUITE_ADD(should_execute_plp_absolute);

  SUITE_ADD(should_execute_and_immediate);
  SUITE_ADD(should_execute_and_zp);
  SUITE_ADD(should_execute_and_zp_x);
  SUITE_ADD(should_execute_and_absolute);
  SUITE_ADD(should_execute_and_absolute_x);
  SUITE_ADD(should_execute_and_absolute_y);
  SUITE_ADD(should_execute_and_indirect_x);
  SUITE_ADD(should_execute_and_indirect_y);

  SUITE_ADD(should_execute_eor_immediate);
  SUITE_ADD(should_execute_eor_zp);
  SUITE_ADD(should_execute_eor_zp_x);
  SUITE_ADD(should_execute_eor_absolute);
  SUITE_ADD(should_execute_eor_absolute_x);
  SUITE_ADD(should_execute_eor_absolute_y);
  SUITE_ADD(should_execute_eor_indirect_x);
  SUITE_ADD(should_execute_eor_indirect_y);

  SUITE_ADD(should_execute_ora_immediate);
  SUITE_ADD(should_execute_ora_zp);
  SUITE_ADD(should_execute_ora_zp_x);
  SUITE_ADD(should_execute_ora_absolute);
  SUITE_ADD(should_execute_ora_absolute_x);
  SUITE_ADD(should_execute_ora_absolute_y);
  SUITE_ADD(should_execute_ora_indirect_x);
  SUITE_ADD(should_execute_ora_indirect_y);

  SUITE_ADD(should_execute_bit_zp);
  SUITE_ADD(should_execute_bit_absolute);

  SUITE_ADD(should_execute_cmp_immediate);
  SUITE_ADD(should_execute_cmp_zp);
  SUITE_ADD(should_execute_cmp_zp_x);
  SUITE_ADD(should_execute_cmp_absolute);
  SUITE_ADD(should_execute_cmp_absolute_x);
  SUITE_ADD(should_execute_cmp_absolute_y);
  SUITE_ADD(should_execute_cmp_indirect_x);
  SUITE_ADD(should_execute_cmp_indirect_y);

  SUITE_ADD(should_execute_cpx_immediate);
  SUITE_ADD(should_execute_cpx_zp);
  SUITE_ADD(should_execute_cpx_absolute);

  SUITE_ADD(should_execute_cpy_immediate);
  SUITE_ADD(should_execute_cpy_zp);
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

  SUITE_ADD(should_execute_asl_a_reg);
  SUITE_ADD(should_execute_asl_zp);
  SUITE_ADD(should_execute_asl_zp_x);
  SUITE_ADD(should_execute_asl_absolute);
  SUITE_ADD(should_execute_asl_absolute_x);

  SUITE_ADD(should_execute_lsr_a_reg);
  SUITE_ADD(should_execute_lsr_zp);
  SUITE_ADD(should_execute_lsr_zp_x);
  SUITE_ADD(should_execute_lsr_absolute);
  SUITE_ADD(should_execute_lsr_absolute_x);

  SUITE_ADD(should_execute_rol_a_reg);
  SUITE_ADD(should_execute_rol_zp);
  SUITE_ADD(should_execute_rol_zp_x);
  SUITE_ADD(should_execute_rol_absolute);
  SUITE_ADD(should_execute_rol_absolute_x);

  SUITE_ADD(should_execute_ror_a_reg);
  SUITE_ADD(should_execute_ror_zp);
  SUITE_ADD(should_execute_ror_zp_x);
  SUITE_ADD(should_execute_ror_absolute);
  SUITE_ADD(should_execute_ror_absolute_x);

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

  SUITE_ADD(should_execute_nop);
  SUITE_ADD(should_execute_brk);
  SUITE_ADD(should_execute_rti);
}
SUITE_END