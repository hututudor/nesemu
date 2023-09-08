#pragma once

#include "../memory/bus.h"
#include "../utils/types.h"

typedef struct {
  u8 c : 1;  // carry
  u8 z : 1;  // zero
  u8 i : 1;  // interrupt disable
  u8 d : 1;  // decimal
  u8 unused : 2;
  u8 v : 1;  // overflow
  u8 n : 1;  // negative
} cpu_status_flags_t;

typedef struct {
  u8 a;
  u8 x;
  u8 y;

  u16 pc;
  u8 sp;
  cpu_status_flags_t status;

  bus_t* bus;
} cpu_t;

typedef struct {
  u8 value;
  u16 address;
} address_mode_t;

typedef address_mode_t (*parse_address_mode_t)(cpu_t* cpu);
typedef void (*execute_t)(cpu_t* cpu, address_mode_t address_mode);

typedef struct {
  parse_address_mode_t parse_address_mode;
  execute_t execute;
  char* mnemonic;
  u8 length;
} instruction_t;

cpu_t* cpu_create(bus_t* bus);
void cpu_destroy(cpu_t* cpu);

void cpu_execute(cpu_t* cpu);

u8 cpu_fetch8(cpu_t* cpu);
u16 cpu_fetch16(cpu_t* cpu);

u16 cpu_fetch_nmi_vector(cpu_t* cpu);
u16 cpu_fetch_irq_vector(cpu_t* cpu);
u16 cpu_fetch_reset_vector(cpu_t* cpu);

void cpu_debug_print_state(cpu_t* cpu);