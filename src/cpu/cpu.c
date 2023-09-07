#include "cpu.h"

#include <stdlib.h>

cpu_t* cpu_create(bus_t* bus) {
  cpu_t* cpu = (cpu_t*)calloc(1, sizeof(cpu_t));
  cpu->bus = bus;

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

u8 cpu_fetch8(cpu_t* cpu) { return bus_read8(cpu->bus, cpu->pc++); }

u16 cpu_fetch16(cpu_t* cpu) { return bus_read16(cpu->bus, cpu->pc += 2); }