#include "cpu.h"

#include <stdlib.h>

#include "instructions_table.h"

cpu_t* cpu_create(bus_t* bus) {
  load_instruction_table();

  cpu_t* cpu = (cpu_t*)calloc(1, sizeof(cpu_t));
  cpu->bus = bus;

  cpu->pc = cpu_fetch_reset_vector(cpu);

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

u16 cpu_fetch_nmi_vector(cpu_t* cpu) { return bus_read16(cpu->bus, 0xFFFA); }

u16 cpu_fetch_irq_vector(cpu_t* cpu) { return bus_read16(cpu->bus, 0xFFFE); }

u16 cpu_fetch_reset_vector(cpu_t* cpu) { return bus_read16(cpu->bus, 0xFFFC); }