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

address_mode_t cpu_address_mode_a(cpu_t* cpu) { ASSERT_UNREACHABLE; }

address_mode_t cpu_address_mode_zp(cpu_t* cpu) { ASSERT_UNREACHABLE; }

address_mode_t cpu_address_mode_zp_x(cpu_t* cpu) { ASSERT_UNREACHABLE; }

address_mode_t cpu_address_mode_zp_y(cpu_t* cpu) { ASSERT_UNREACHABLE; }

address_mode_t cpu_address_mode_relative(cpu_t* cpu) { ASSERT_UNREACHABLE; }

address_mode_t cpu_address_mode_absolute(cpu_t* cpu) {
  address_mode_t address_mode = {0};
  address_mode.address = cpu_fetch16(cpu);
  address_mode.value = bus_read8(cpu->bus, address_mode.address);
  return address_mode;
}

address_mode_t cpu_address_mode_absolute_x(cpu_t* cpu) { ASSERT_UNREACHABLE; }

address_mode_t cpu_address_mode_absolute_y(cpu_t* cpu) { ASSERT_UNREACHABLE; }

address_mode_t cpu_address_mode_indirect(cpu_t* cpu) { ASSERT_UNREACHABLE; }

address_mode_t cpu_address_mode_indirect_x(cpu_t* cpu) { ASSERT_UNREACHABLE; }

address_mode_t cpu_address_mode_indirect_y(cpu_t* cpu) { ASSERT_UNREACHABLE; }