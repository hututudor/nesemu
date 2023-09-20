#include "instructions.h"

#include <stdio.h>

#include "../utils/assert.h"

u8 cpu_lda(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = bus_read8(cpu->bus, address_mode.address);

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);

  return address_mode.extra_cycle;
}

u8 cpu_ldx(cpu_t* cpu, address_mode_t address_mode) {
  cpu->x = bus_read8(cpu->bus, address_mode.address);

  cpu_set_status_z(cpu, cpu->x);
  cpu_set_status_n(cpu, cpu->x);

  return address_mode.extra_cycle;
}

u8 cpu_ldy(cpu_t* cpu, address_mode_t address_mode) {
  cpu->y = bus_read8(cpu->bus, address_mode.address);

  cpu_set_status_z(cpu, cpu->y);
  cpu_set_status_n(cpu, cpu->y);

  return address_mode.extra_cycle;
}

u8 cpu_sta(cpu_t* cpu, address_mode_t address_mode) {
  bus_write8(cpu->bus, address_mode.address, cpu->a);

  return 0;
}

u8 cpu_stx(cpu_t* cpu, address_mode_t address_mode) {
  bus_write8(cpu->bus, address_mode.address, cpu->x);

  return 0;
}

u8 cpu_sty(cpu_t* cpu, address_mode_t address_mode) {
  bus_write8(cpu->bus, address_mode.address, cpu->y);

  return 0;
}

u8 cpu_tax(cpu_t* cpu, address_mode_t address_mode) {
  cpu->x = cpu->a;

  cpu_set_status_z(cpu, cpu->x);
  cpu_set_status_n(cpu, cpu->x);

  return 0;
}

u8 cpu_tay(cpu_t* cpu, address_mode_t address_mode) {
  cpu->y = cpu->a;

  cpu_set_status_z(cpu, cpu->y);
  cpu_set_status_n(cpu, cpu->y);

  return 0;
}

u8 cpu_txa(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu->x;

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);

  return 0;
}

u8 cpu_tya(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu->y;

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);

  return 0;
}

u8 cpu_tsx(cpu_t* cpu, address_mode_t address_mode) {
  cpu->x = cpu->sp;

  cpu_set_status_z(cpu, cpu->x);
  cpu_set_status_n(cpu, cpu->x);

  return 0;
}

u8 cpu_txs(cpu_t* cpu, address_mode_t address_mode) {
  cpu->sp = cpu->x;

  cpu_set_status_z(cpu, cpu->sp);
  cpu_set_status_n(cpu, cpu->sp);

  return 0;
}

u8 cpu_pha(cpu_t* cpu, address_mode_t address_mode) {
  cpu_push8(cpu, cpu->a);

  return 0;
}

u8 cpu_php(cpu_t* cpu, address_mode_t address_mode) {
  cpu_push8(cpu, cpu_get_status(cpu));

  return 0;
}

u8 cpu_pla(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu_pop8(cpu);

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);

  return 0;
}

u8 cpu_plp(cpu_t* cpu, address_mode_t address_mode) {
  cpu_set_status(cpu, cpu_pop8(cpu));

  return 0;
}

u8 cpu_and(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu->a & bus_read8(cpu->bus, address_mode.address);

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);

  return address_mode.extra_cycle;
}

u8 cpu_eor(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu->a ^ bus_read8(cpu->bus, address_mode.address);

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);

  return address_mode.extra_cycle;
}

u8 cpu_ora(cpu_t* cpu, address_mode_t address_mode) {
  cpu->a = cpu->a | bus_read8(cpu->bus, address_mode.address);

  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_n(cpu, cpu->a);

  return address_mode.extra_cycle;
}

u8 cpu_bit(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = bus_read8(cpu->bus, address_mode.address);
  u8 result = value & cpu->a;

  cpu->status.z = result == 0;
  cpu->status.v = (value >> 6) & 1;
  cpu->status.n = (value >> 7) & 1;

  return 0;
}

u8 cpu_adc(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = bus_read8(cpu->bus, address_mode.address);

  u8 previous_a = cpu->a;
  u8 previous_result = value + cpu->status.c;

  u16 result = previous_a + previous_result;
  cpu->a = result;

  cpu_set_status_c(cpu, result);
  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_v(cpu, cpu->a, previous_a, previous_result);
  cpu_set_status_n(cpu, cpu->a);

  return address_mode.extra_cycle;
}

u8 cpu_sbc(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = bus_read8(cpu->bus, address_mode.address);

  u8 previous_a = cpu->a;
  u8 previous_result = value + (1 - cpu->status.c);

  u16 result = previous_a - previous_result;
  cpu->a = result;

  cpu_set_status_c(cpu, result);
  cpu_set_status_z(cpu, cpu->a);
  cpu_set_status_v(cpu, cpu->a, previous_a, -previous_result);
  cpu_set_status_n(cpu, cpu->a);

  return address_mode.extra_cycle;
}

u8 cpu_cmp(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = bus_read8(cpu->bus, address_mode.address);

  cpu->status.c = cpu->a >= value;
  cpu->status.z = cpu->a == value;
  cpu->status.n = (cpu->a - value) >> 7;

  return address_mode.extra_cycle;
}

u8 cpu_cpx(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = bus_read8(cpu->bus, address_mode.address);

  cpu->status.c = cpu->x >= value;
  cpu->status.z = cpu->x == value;
  cpu->status.n = (cpu->x - value) >> 7;

  return 0;
}

u8 cpu_cpy(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = bus_read8(cpu->bus, address_mode.address);

  cpu->status.c = cpu->y >= value;
  cpu->status.z = cpu->y == value;
  cpu->status.n = (cpu->y - value) >> 7;

  return 0;
}

u8 cpu_inc(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = bus_read8(cpu->bus, address_mode.address) + 1;

  bus_write8(cpu->bus, address_mode.address, value);

  cpu_set_status_z(cpu, value);
  cpu_set_status_n(cpu, value);

  return 0;
}

u8 cpu_inx(cpu_t* cpu, address_mode_t address_mode) {
  cpu->x++;

  cpu_set_status_z(cpu, cpu->x);
  cpu_set_status_n(cpu, cpu->x);

  return 0;
}

u8 cpu_iny(cpu_t* cpu, address_mode_t address_mode) {
  cpu->y++;

  cpu_set_status_z(cpu, cpu->y);
  cpu_set_status_n(cpu, cpu->y);

  return 0;
}

u8 cpu_dec(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = bus_read8(cpu->bus, address_mode.address) - 1;

  bus_write8(cpu->bus, address_mode.address, value);

  cpu_set_status_z(cpu, value);
  cpu_set_status_n(cpu, value);

  return 0;
}

u8 cpu_dex(cpu_t* cpu, address_mode_t address_mode) {
  cpu->x--;

  cpu_set_status_z(cpu, cpu->x);
  cpu_set_status_n(cpu, cpu->x);

  return 0;
}

u8 cpu_dey(cpu_t* cpu, address_mode_t address_mode) {
  cpu->y--;

  cpu_set_status_z(cpu, cpu->y);
  cpu_set_status_n(cpu, cpu->y);

  return 0;
}

u8 cpu_asl(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = address_mode.is_a_register
                 ? cpu->a
                 : bus_read8(cpu->bus, address_mode.address);

  u8 result = value << 1;
  cpu->status.c = (result >> 7) & 1;

  if (address_mode.is_a_register) {
    cpu->a = result;
  } else {
    bus_write8(cpu->bus, address_mode.address, result);
  }

  cpu_set_status_z(cpu, result);
  cpu_set_status_n(cpu, result);

  return 0;
}

u8 cpu_lsr(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = address_mode.is_a_register
                 ? cpu->a
                 : bus_read8(cpu->bus, address_mode.address);

  u8 result = value >> 1;
  cpu->status.c = result & 1;

  if (address_mode.is_a_register) {
    cpu->a = result;
  } else {
    bus_write8(cpu->bus, address_mode.address, result);
  }

  cpu_set_status_z(cpu, result);
  cpu_set_status_n(cpu, result);

  return 0;
}

u8 cpu_rol(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = address_mode.is_a_register
                 ? cpu->a
                 : bus_read8(cpu->bus, address_mode.address);

  u8 result = (value << 1) | cpu->status.c;
  cpu->status.c = (value >> 7) & 1;

  if (address_mode.is_a_register) {
    cpu->a = result;
  } else {
    bus_write8(cpu->bus, address_mode.address, result);
  }

  cpu_set_status_z(cpu, result);
  cpu_set_status_n(cpu, result);

  return 0;
}

u8 cpu_ror(cpu_t* cpu, address_mode_t address_mode) {
  u8 value = address_mode.is_a_register
                 ? cpu->a
                 : bus_read8(cpu->bus, address_mode.address);

  u8 result = (value >> 1) | (cpu->status.c << 7);
  cpu->status.c = value & 1;

  if (address_mode.is_a_register) {
    cpu->a = result;
  } else {
    bus_write8(cpu->bus, address_mode.address, result);
  }

  cpu_set_status_z(cpu, result);
  cpu_set_status_n(cpu, result);

  return 0;
}

u8 cpu_jmp(cpu_t* cpu, address_mode_t address_mode) {
  cpu->pc = address_mode.address;

  return 0;
}

u8 cpu_jsr(cpu_t* cpu, address_mode_t address_mode) {
  cpu_push16(cpu, cpu->pc - 1);
  cpu->pc = address_mode.address;

  return 0;
}

u8 cpu_rts(cpu_t* cpu, address_mode_t address_mode) {
  cpu->pc = cpu_pop16(cpu) + 1;

  return 0;
}

u8 cpu_bcc(cpu_t* cpu, address_mode_t address_mode) {
  if (cpu->status.c) {
    return 0;
  }

  cpu->pc = address_mode.address;

  return 1 + address_mode.extra_cycle;
}

u8 cpu_bcs(cpu_t* cpu, address_mode_t address_mode) {
  if (!cpu->status.c) {
    return 0;
  }

  cpu->pc = address_mode.address;

  return 1 + address_mode.extra_cycle;
}

u8 cpu_beq(cpu_t* cpu, address_mode_t address_mode) {
  if (!cpu->status.z) {
    return 0;
  }

  cpu->pc = address_mode.address;

  return 1 + address_mode.extra_cycle;
}

u8 cpu_bmi(cpu_t* cpu, address_mode_t address_mode) {
  if (!cpu->status.n) {
    return 0;
  }

  cpu->pc = address_mode.address;

  return 1 + address_mode.extra_cycle;
}

u8 cpu_bne(cpu_t* cpu, address_mode_t address_mode) {
  if (cpu->status.z) {
    return 0;
  }

  cpu->pc = address_mode.address;

  return 1 + address_mode.extra_cycle;
}

u8 cpu_bpl(cpu_t* cpu, address_mode_t address_mode) {
  if (cpu->status.n) {
    return 0;
  }

  cpu->pc = address_mode.address;

  return 1 + address_mode.extra_cycle;
}

u8 cpu_bvc(cpu_t* cpu, address_mode_t address_mode) {
  if (cpu->status.v) {
    return 0;
  }

  cpu->pc = address_mode.address;

  return 1 + address_mode.extra_cycle;
}

u8 cpu_bvs(cpu_t* cpu, address_mode_t address_mode) {
  if (!cpu->status.v) {
    return 0;
  }

  cpu->pc = address_mode.address;

  return 1 + address_mode.extra_cycle;
}

u8 cpu_clc(cpu_t* cpu, address_mode_t address_mode) {
  cpu->status.c = 0;

  return 0;
}

u8 cpu_cld(cpu_t* cpu, address_mode_t address_mode) {
  cpu->status.d = 0;

  return 0;
}

u8 cpu_cli(cpu_t* cpu, address_mode_t address_mode) {
  cpu->status.i = 0;

  return 0;
}

u8 cpu_clv(cpu_t* cpu, address_mode_t address_mode) {
  cpu->status.v = 0;

  return 0;
}

u8 cpu_sec(cpu_t* cpu, address_mode_t address_mode) {
  cpu->status.c = 1;

  return 0;
}

u8 cpu_sed(cpu_t* cpu, address_mode_t address_mode) {
  cpu->status.d = 1;

  return 0;
}

u8 cpu_sei(cpu_t* cpu, address_mode_t address_mode) {
  cpu->status.i = 1;

  return 0;
}

u8 cpu_brk(cpu_t* cpu, address_mode_t address_mode) {
  cpu_push16(cpu, cpu->pc);
  cpu_push8(cpu, cpu_get_status(cpu));

  cpu->pc = cpu_fetch_irq_vector(cpu);

  return 0;
}

u8 cpu_nop(cpu_t* cpu, address_mode_t address_mode) { return 0; }

u8 cpu_rti(cpu_t* cpu, address_mode_t address_mode) {
  cpu_set_status(cpu, cpu_pop8(cpu));
  cpu->pc = cpu_pop16(cpu);

  return 0;
}
