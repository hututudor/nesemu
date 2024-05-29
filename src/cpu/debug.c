#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "instructions_table.h"

#define CPU_DEBUG_FILE "cpu.log"
FILE* cpu_debug_file;

static void print_disassembled_instruction(cpu_t* cpu) {
  u8 opcode = bus_read8(cpu->bus, cpu->pc);
  instruction_t instruction = instructions_table[opcode];

  printf("[0x%02X] ", opcode);
  printf("%s ", instruction.mnemonic);

  switch (instruction.length) {
    case 2:
      printf("0x%02X", bus_read8(cpu->bus, cpu->pc + 1));
      break;

    case 3:
      printf("0x%04X", bus_read16(cpu->bus, cpu->pc + 1));
      break;

    default:
      break;
  }

  printf("\n");
}

void cpu_debug_print_state(cpu_t* cpu) {
  printf("PC: 0x%04X | A: 0x%02X | X: 0x%02X | Y: 0x%02X | SP: 0x%02X\n",
         cpu->pc, cpu->a, cpu->x, cpu->y, cpu->sp);
  printf("C: %d | Z: %d | I: %d | D: %d | V: %d | N: %d\n", cpu->status.c,
         cpu->status.z, cpu->status.i, cpu->status.d, cpu->status.v,
         cpu->status.n);

  print_disassembled_instruction(cpu);
}

void cpu_debug_print_log(cpu_t* cpu) {
  if (!cpu_debug_file) {
    cpu_debug_file = fopen(CPU_DEBUG_FILE, "w");
  }

  u8 opcode = bus_read8(cpu->bus, cpu->pc);
  instruction_t instruction = instructions_table[opcode];

  fprintf(cpu_debug_file, "%04X  $%02X ", cpu->pc,
          bus_read8(cpu->bus, cpu->pc));

  if (instruction.length == 2) {
    fprintf(cpu_debug_file, "$%02X      ", bus_read8(cpu->bus, cpu->pc + 1));
  } else if (instruction.length == 3) {
    fprintf(cpu_debug_file, "$%02X $%02X  ", bus_read8(cpu->bus, cpu->pc + 1),
            bus_read8(cpu->bus, cpu->pc + 2));
  } else {
    fprintf(cpu_debug_file, "         ");
  }

  fprintf(cpu_debug_file, "A:%02X ", cpu->a);
  fprintf(cpu_debug_file, "X:%02X ", cpu->x);
  fprintf(cpu_debug_file, "Y:%02X ", cpu->y);
  fprintf(cpu_debug_file, "P:%02X ", cpu_get_status(cpu));
  fprintf(cpu_debug_file, "SP:%02X ", cpu->sp);
  fprintf(cpu_debug_file, "CPUCYC:%ld", cpu->total_cycles);

  fprintf(cpu_debug_file, "\n");

  fflush(cpu_debug_file);
}