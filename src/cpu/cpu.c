#include "cpu.h"

#include <stdio.h>
#include <stdlib.h>

#include "instructions_table.h"

cpu_t* cpu_create(bus_t* bus) {
  load_instruction_table();

  cpu_t* cpu = (cpu_t*)calloc(1, sizeof(cpu_t));
  cpu->bus = bus;

  cpu->pc = cpu_fetch_reset_vector(cpu);
  cpu->sp = 0xFD;

  cpu->status.i = 1;

  cpu->a = 0;
  cpu->x = 0;
  cpu->y = 0;

  return cpu;
}

void cpu_destroy(cpu_t* cpu) {
  if (!cpu) {
    return;
  }

  free(cpu);
}

void cpu_execute(cpu_t* cpu) {
  u8 opcode = cpu_fetch8(cpu);
  instruction_t instruction = instructions_table[opcode];

  if (!instruction.execute) {
    printf("[CPU] ILLEGAL INSTRUCTION REACHED: %02X\n", opcode);

    exit(0);
  }

  address_mode_t address_mode = instruction.parse_address_mode(cpu);
  instruction.execute(cpu, address_mode);
}

u8 cpu_fetch8(cpu_t* cpu) { return bus_read8(cpu->bus, cpu->pc++); }

u16 cpu_fetch16(cpu_t* cpu) {
  u16 value = bus_read16(cpu->bus, cpu->pc);
  cpu->pc += 2;
  return value;
}

u16 cpu_fetch_nmi_vector(cpu_t* cpu) { return bus_read16(cpu->bus, 0xFFFA); }

u16 cpu_fetch_irq_vector(cpu_t* cpu) { return bus_read16(cpu->bus, 0xFFFE); }

u16 cpu_fetch_reset_vector(cpu_t* cpu) { return bus_read16(cpu->bus, 0xFFFC); }

void cpu_push8(cpu_t* cpu, u8 value) {
  bus_write8(cpu->bus, 0x0100 + cpu->sp--, value);
}

u8 cpu_pop8(cpu_t* cpu) { return bus_read8(cpu->bus, 0x0100 + (++cpu->sp)); }

void cpu_push16(cpu_t* cpu, u16 value) {
  bus_write8(cpu->bus, 0x0100 + cpu->sp--, (value >> 8) & 0xFF);
  bus_write8(cpu->bus, 0x0100 + cpu->sp--, value & 0xFF);
}

u16 cpu_pop16(cpu_t* cpu) {
  u16 value = bus_read16(cpu->bus, 0x0100 + cpu->sp + 1);
  cpu->sp += 2;
  return value;
}

void cpu_set_status_c(cpu_t* cpu, u16 value) { cpu->status.c = value > 0xFF; }

void cpu_set_status_z(cpu_t* cpu, u8 value) { cpu->status.z = value == 0; }

void cpu_set_status_v(cpu_t* cpu, u8 result, u8 a, u8 b) {
  u8 aSign = (a & 0x80) >> 7;
  u8 bSign = (b & 0x80) >> 7;
  u8 resultSign = (result & 0x80) >> 7;

  cpu->status.v = (resultSign != aSign) && (resultSign != bSign);
}

u8 cpu_get_status(cpu_t* cpu) {
  u8 res = 0;

  res = (res << 1) + cpu->status.n;
  res = (res << 1) + cpu->status.v;
  res = (res << 1) + 1;
  res = (res << 1) + 0;
  res = (res << 1) + cpu->status.d;
  res = (res << 1) + cpu->status.i;
  res = (res << 1) + cpu->status.z;
  res = (res << 1) + cpu->status.c;

  return res;
}

void cpu_set_status(cpu_t* cpu, u8 status) {
  cpu->status.c = (status >> 0) & 1;
  cpu->status.z = (status >> 1) & 1;
  cpu->status.i = (status >> 2) & 1;
  cpu->status.d = (status >> 3) & 1;
  cpu->status.v = (status >> 6) & 1;
  cpu->status.n = (status >> 7) & 1;
}

void cpu_set_status_n(cpu_t* cpu, u8 value) {
  cpu->status.n = (value >> 7) & 1;
}