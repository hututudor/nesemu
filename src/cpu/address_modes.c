#include "address_modes.h"

#include "../utils/assert.h"

address_mode_t cpu_address_mode_implied(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  return address_mode;
}

address_mode_t cpu_address_mode_immediate(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  address_mode.value = cpu_fetch8(cpu);
  return address_mode;
}

address_mode_t cpu_address_mode_a(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  address_mode.is_a_register = true;
  address_mode.value = cpu->a;
  return address_mode;
}

address_mode_t cpu_address_mode_zp(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  address_mode.address = cpu_fetch8(cpu);
  address_mode.value = bus_read8(cpu->bus, address_mode.address);
  return address_mode;
}

address_mode_t cpu_address_mode_zp_x(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  address_mode.address = (cpu_fetch8(cpu) + cpu->x) & 0xFF;
  address_mode.value = bus_read8(cpu->bus, address_mode.address);
  return address_mode;
}

address_mode_t cpu_address_mode_zp_y(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  address_mode.address = (cpu_fetch8(cpu) + cpu->y) & 0xFF;
  address_mode.value = bus_read8(cpu->bus, address_mode.address);
  return address_mode;
}

address_mode_t cpu_address_mode_relative(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  s8 relative = cpu_fetch8(cpu);
  address_mode.address = relative + cpu->pc;
  address_mode.value = bus_read8(cpu->bus, address_mode.address);
  return address_mode;
}

address_mode_t cpu_address_mode_absolute(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  address_mode.address = cpu_fetch16(cpu);
  address_mode.value = bus_read8(cpu->bus, address_mode.address);
  return address_mode;
}

address_mode_t cpu_address_mode_absolute_x(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  address_mode.address = cpu_fetch16(cpu) + cpu->x;
  address_mode.value = bus_read8(cpu->bus, address_mode.address);
  return address_mode;
}

address_mode_t cpu_address_mode_absolute_y(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  address_mode.address = cpu_fetch16(cpu) + cpu->y;
  address_mode.value = bus_read8(cpu->bus, address_mode.address);
  return address_mode;
}

address_mode_t cpu_address_mode_indirect(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  u16 address = cpu_fetch16(cpu);

  if ((address & 0xFF) == 0xFF) {
    address_mode.address = (bus_read8(cpu->bus, address & 0xFF00) << 8) |
                           bus_read8(cpu->bus, address);
  } else {
    address_mode.address = bus_read16(cpu->bus, address);
  }

  address_mode.value = bus_read8(cpu->bus, address_mode.address);
  return address_mode;
}

address_mode_t cpu_address_mode_indirect_x(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  u8 address = cpu_fetch8(cpu) + cpu->x;
  address_mode.address = bus_read16(cpu->bus, address);
  address_mode.value = bus_read8(cpu->bus, address_mode.address);
  return address_mode;
}

address_mode_t cpu_address_mode_indirect_y(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  u8 address = cpu_fetch8(cpu);
  address_mode.address = bus_read16(cpu->bus, address) + cpu->y;
  address_mode.value = bus_read8(cpu->bus, address_mode.address);
  return address_mode;
}