#pragma once

#include "cpu.h"

#define INSTRUCTIONS_COUNT 0xFF

#define INSTRUCTION(opcode, _mnemonic, _execute, _parse_address_mode, _length) \
  instructions_table[opcode].mnemonic = _mnemonic;                             \
  instructions_table[opcode].length = _length;                                 \
  instructions_table[opcode].parse_address_mode = _parse_address_mode;         \
  instructions_table[opcode].execute = _execute;

instruction_t instructions_table[INSTRUCTIONS_COUNT];

void load_instruction_table();