#include "instructions.h"

#include <stdio.h>

#include "../utils/assert.h"

void cpu_lda(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = address_mode.value;

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);
}

void cpu_ldx(cpu_t* cpu, address_mode_t address_mode) {
  cpu->x = address_mode.value;

  cpu_set_status_z(cpu, cpu->x);
  cpu_set_status_n(cpu, cpu->x);
}

void cpu_ldy(cpu_t* cpu, address_mode_t address_mode) {
  cpu->y = address_mode.value;

  cpu_set_status_z(cpu, cpu->y);
  cpu_set_status_n(cpu, cpu->y);
}

void cpu_sta(cpu_t* cpu, address_mode_t address_mode) {
  bus_write8(cpu->bus, address_mode.address, cpu->a);
}

void cpu_stx(cpu_t* cpu, address_mode_t address_mode) {
  bus_write8(cpu->bus, address_mode.address, cpu->x);
}

void cpu_sty(cpu_t* cpu, address_mode_t address_mode) {
  bus_write8(cpu->bus, address_mode.address, cpu->y);
}

void cpu_tax(cpu_t* cpu, address_mode_t address_mode) {
  cpu->x = cpu->a;

  cpu_set_status_z(cpu, cpu->x);
  cpu_set_status_n(cpu, cpu->x);
}

void cpu_tay(cpu_t* cpu, address_mode_t address_mode) {
  cpu->y = cpu->a;

  cpu_set_status_z(cpu, cpu->y);
  cpu_set_status_n(cpu, cpu->y);
}

void cpu_txa(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu->x;

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);
}

void cpu_tya(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu->y;

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);
}

void cpu_tsx(cpu_t* cpu, address_mode_t address_mode) {
  cpu->x = cpu->sp;

  cpu_set_status_z(cpu, cpu->x);
  cpu_set_status_n(cpu, cpu->x);
}

void cpu_txs(cpu_t* cpu, address_mode_t address_mode) {
  cpu->sp = cpu->x;

  cpu_set_status_z(cpu, cpu->sp);
  cpu_set_status_n(cpu, cpu->sp);
}

void cpu_pha(cpu_t* cpu, address_mode_t address_mode) {
  cpu_push8(cpu, cpu->a);
}

void cpu_php(cpu_t* cpu, address_mode_t address_mode) {
  cpu_push8(cpu, cpu_get_status(cpu));
}

void cpu_pla(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu_pop8(cpu);

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);
}

void cpu_plp(cpu_t* cpu, address_mode_t address_mode) {
  cpu_set_status(cpu, cpu_pop8(cpu));
}

void cpu_and(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu->a & address_mode.value;

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);
}

void cpu_eor(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu->a ^ address_mode.value;

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);
}

void cpu_ora(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu->a | address_mode.value;

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);
}

void cpu_bit(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = address_mode.value & cpu->a;

  cpu->status.z = value == 0;
  cpu->status.v = (address_mode.value >> 6) & 1;
  cpu->status.n = (address_mode.value >> 7) & 1;
}

void cpu_adc(cpu_t* cpu, address_mode_t address_mode) {
  u8 previous_a = cpu->a;
  u8 previous_result = address_mode.value + cpu->status.c;

  u16 result = previous_a + previous_result;
  cpu->a = result;

  cpu_set_status_c(cpu, result);
  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_v(cpu, cpu->a, previous_a, previous_result);
  cpu_set_status_n(cpu, cpu->a);
}

void cpu_sbc(cpu_t* cpu, address_mode_t address_mode) {
  u8 previous_a = cpu->a;
  u8 previous_result = address_mode.value + (1 - cpu->status.c);

  u16 result = previous_a - previous_result;
  cpu->a = result;

  cpu_set_status_c(cpu, result);
  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_v(cpu, cpu->a, previous_a, -previous_result);
  cpu_set_status_n(cpu, cpu->a);
}

void cpu_cmp(cpu_t* cpu, address_mode_t address_mode) {
  cpu->status.c = cpu->a >= address_mode.value;
  cpu->status.z = cpu->a == address_mode.value;
  cpu->status.n = (cpu->a - address_mode.value) >> 7;
}

void cpu_cpx(cpu_t* cpu, address_mode_t address_mode) {
  cpu->status.c = cpu->x >= address_mode.value;
  cpu->status.z = cpu->x == address_mode.value;
  cpu->status.n = (cpu->x - address_mode.value) >> 7;
}

void cpu_cpy(cpu_t* cpu, address_mode_t address_mode) {
  cpu->status.c = cpu->y >= address_mode.value;
  cpu->status.z = cpu->y == address_mode.value;
  cpu->status.n = (cpu->y - address_mode.value) >> 7;
}

void cpu_inc(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = address_mode.value + 1;

  bus_write8(cpu->bus, address_mode.address, value);

  cpu_set_status_z(cpu, value);
  cpu_set_status_n(cpu, value);
}

void cpu_inx(cpu_t* cpu, address_mode_t address_mode) {
  cpu->x++;

  cpu_set_status_z(cpu, cpu->x);
  cpu_set_status_n(cpu, cpu->x);
}

void cpu_iny(cpu_t* cpu, address_mode_t address_mode) {
  cpu->y++;

  cpu_set_status_z(cpu, cpu->y);
  cpu_set_status_n(cpu, cpu->y);
}

void cpu_dec(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = address_mode.value - 1;

  bus_write8(cpu->bus, address_mode.address, value);

  cpu_set_status_z(cpu, value);
  cpu_set_status_n(cpu, value);
}

void cpu_dex(cpu_t* cpu, address_mode_t address_mode) {
  cpu->x--;

  cpu_set_status_z(cpu, cpu->x);
  cpu_set_status_n(cpu, cpu->x);
}

void cpu_dey(cpu_t* cpu, address_mode_t address_mode) {
  cpu->y--;

  cpu_set_status_z(cpu, cpu->y);
  cpu_set_status_n(cpu, cpu->y);
}

void cpu_asl(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_lsr(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_rol(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = (address_mode.value << 1) | cpu->status.c;
  cpu->status.c = (address_mode.value >> 7) & 1;

  if (address_mode.is_a_register) {
    cpu->a = value;
  } else {
    bus_write8(cpu->bus, address_mode.address, value);
  }

  cpu_set_status_z(cpu, value);
  cpu_set_status_n(cpu, value);
}

void cpu_ror(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = (address_mode.value >> 1) | (cpu->status.c << 7);
  cpu->status.c = address_mode.value & 1;

  if (address_mode.is_a_register) {
    cpu->a = value;
  } else {
    bus_write8(cpu->bus, address_mode.address, value);
  }

  cpu_set_status_z(cpu, value);
  cpu_set_status_n(cpu, value);
}

void cpu_jmp(cpu_t* cpu, address_mode_t address_mode) {
  cpu->pc = address_mode.address;
}

void cpu_jsr(cpu_t* cpu, address_mode_t address_mode) {
  cpu_push16(cpu, cpu->pc - 1);
  cpu->pc = address_mode.address;
}

void cpu_rts(cpu_t* cpu, address_mode_t address_mode) {
  cpu->pc = cpu_pop16(cpu) + 1;
}

void cpu_bcc(cpu_t* cpu, address_mode_t address_mode) {
  if (cpu->status.c) {
    return;
  }

  cpu->pc = address_mode.address;
}

void cpu_bcs(cpu_t* cpu, address_mode_t address_mode) {
  if (!cpu->status.c) {
    return;
  }

  cpu->pc = address_mode.address;
}

void cpu_beq(cpu_t* cpu, address_mode_t address_mode) {
  if (!cpu->status.z) {
    return;
  }

  cpu->pc = address_mode.address;
}

void cpu_bmi(cpu_t* cpu, address_mode_t address_mode) {
  if (!cpu->status.n) {
    return;
  }

  cpu->pc = address_mode.address;
}

void cpu_bne(cpu_t* cpu, address_mode_t address_mode) {
  if (cpu->status.z) {
    return;
  }

  cpu->pc = address_mode.address;
}

void cpu_bpl(cpu_t* cpu, address_mode_t address_mode) {
  if (cpu->status.n) {
    return;
  }

  cpu->pc = address_mode.address;
}

void cpu_bvc(cpu_t* cpu, address_mode_t address_mode) {
  if (cpu->status.v) {
    return;
  }

  cpu->pc = address_mode.address;
}

void cpu_bvs(cpu_t* cpu, address_mode_t address_mode) {
  if (!cpu->status.v) {
    return;
  }

  cpu->pc = address_mode.address;
}

void cpu_clc(cpu_t* cpu, address_mode_t address_mode) { cpu->status.c = 0; }

void cpu_cld(cpu_t* cpu, address_mode_t address_mode) { cpu->status.d = 0; }

void cpu_cli(cpu_t* cpu, address_mode_t address_mode) { cpu->status.i = 0; }

void cpu_clv(cpu_t* cpu, address_mode_t address_mode) { cpu->status.v = 0; }

void cpu_sec(cpu_t* cpu, address_mode_t address_mode) { cpu->status.c = 1; }

void cpu_sed(cpu_t* cpu, address_mode_t address_mode) { cpu->status.d = 1; }

void cpu_sei(cpu_t* cpu, address_mode_t address_mode) { cpu->status.i = 1; }

void cpu_brk(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_nop(cpu_t* cpu, address_mode_t address_mode) {}

void cpu_rti(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }
