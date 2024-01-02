#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "instructions_table.h"

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
  u8 opcode = bus_read8(cpu->bus, cpu->pc);
  instruction_t instruction = instructions_table[opcode];

  printf("%04X  %02X ", cpu->pc, bus_read8(cpu->bus, cpu->pc));

  if (instruction.length == 2) {
    printf("%02X     ", bus_read8(cpu->bus, cpu->pc + 1));
  } else if (instruction.length == 3) {
    printf("%02X %02X  ", bus_read8(cpu->bus, cpu->pc + 1),
           bus_read8(cpu->bus, cpu->pc + 2));
  } else {
    printf("       ");
  }

  printf("A:%02X ", cpu->a);
  printf("X:%02X ", cpu->x);
  printf("Y:%02X ", cpu->y);
  printf("P:%02X ", cpu_get_status(cpu));
  printf("SP:%02X ", cpu->sp);

  fflush(stdout);
}