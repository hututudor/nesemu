#pragma once

#include "../memory/bus.h"
#include "utils/types.h"

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

cpu_t* cpu_create(bus_t* bus);
void cpu_destroy(cpu_t* cpu);
