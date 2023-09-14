#include "instructions_table.h"

#include "address_modes.h"
#include "cpu.h"
#include "instructions.h"

static bool is_instruction_table_loaded = false;
extern instruction_t instructions_table[INSTRUCTIONS_COUNT];

void load_instruction_table() {
  if (is_instruction_table_loaded) {
    return;
  }

  is_instruction_table_loaded = true;

  INSTRUCTION(0x69, "[#] ADC", cpu_adc, cpu_address_mode_immediate, 2, 2);
  INSTRUCTION(0x65, "[ZP] ADC", cpu_adc, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0x75, "[ZP, X] ADC", cpu_adc, cpu_address_mode_zp_x, 2, 4);
  INSTRUCTION(0x6D, "[ABS] ADC", cpu_adc, cpu_address_mode_absolute, 3, 4);
  INSTRUCTION(0x7D, "[ABS, X] ADC", cpu_adc, cpu_address_mode_absolute_x, 3, 4);
  INSTRUCTION(0x79, "[ABS, Y] ADC", cpu_adc, cpu_address_mode_absolute_y, 3, 4);
  INSTRUCTION(0x61, "[(ZP), X] ADC", cpu_adc, cpu_address_mode_indirect_x, 2,
              6);
  INSTRUCTION(0x71, "[(ZP), Y] ADC", cpu_adc, cpu_address_mode_indirect_y, 2,
              5);

  INSTRUCTION(0x29, "[#] AND", cpu_and, cpu_address_mode_immediate, 2, 2);
  INSTRUCTION(0x25, "[ZP] AND", cpu_and, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0x35, "[ZP, X] AND", cpu_and, cpu_address_mode_zp_x, 2, 4);
  INSTRUCTION(0x2D, "[ABS] AND", cpu_and, cpu_address_mode_absolute, 3, 4);
  INSTRUCTION(0x3D, "[ABS, X] AND", cpu_and, cpu_address_mode_absolute_x, 3, 4);
  INSTRUCTION(0x39, "[ABS, Y] AND", cpu_and, cpu_address_mode_absolute_y, 3, 4);
  INSTRUCTION(0x21, "[(ZP), X] AND", cpu_and, cpu_address_mode_indirect_x, 2,
              6);
  INSTRUCTION(0x31, "[(ZP), Y] AND", cpu_and, cpu_address_mode_indirect_y, 2,
              5);

  INSTRUCTION(0x0A, "[A] ASL", cpu_asl, cpu_address_mode_a, 1, 2);
  INSTRUCTION(0x06, "[ZP] ASL", cpu_asl, cpu_address_mode_zp, 2, 5);
  INSTRUCTION(0x16, "[ZP, X] ASL", cpu_asl, cpu_address_mode_zp_x, 2, 6);
  INSTRUCTION(0x0E, "[ABS] ASL", cpu_asl, cpu_address_mode_absolute, 3, 6);
  INSTRUCTION(0x1E, "[ABS, X] ASL", cpu_asl, cpu_address_mode_absolute_x, 3, 7);

  INSTRUCTION(0x90, "[REL] BCC", cpu_bcc, cpu_address_mode_relative, 2, 2);
  INSTRUCTION(0xB0, "[REL] BCS", cpu_bcs, cpu_address_mode_relative, 2, 2);
  INSTRUCTION(0xF0, "[REL] BEQ", cpu_beq, cpu_address_mode_relative, 2, 2);
  INSTRUCTION(0x30, "[REL] BMI", cpu_bmi, cpu_address_mode_relative, 2, 2);
  INSTRUCTION(0xD0, "[REL] BNE", cpu_bne, cpu_address_mode_relative, 2, 2);
  INSTRUCTION(0x10, "[REL] BPL", cpu_bpl, cpu_address_mode_relative, 2, 2);
  INSTRUCTION(0x50, "[REL] BVC", cpu_bvc, cpu_address_mode_relative, 2, 2);
  INSTRUCTION(0x70, "[REL] BVS", cpu_bvs, cpu_address_mode_relative, 2, 2);

  INSTRUCTION(0x00, "BRK", cpu_brk, cpu_address_mode_implied, 1, 7);

  INSTRUCTION(0x24, "[ZP] BIT", cpu_bit, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0x2C, "[ABS] BIT", cpu_bit, cpu_address_mode_absolute, 3, 4);

  INSTRUCTION(0x18, "CLC", cpu_clc, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0xD8, "CLD", cpu_cld, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0x58, "CLI", cpu_cli, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0xB8, "CLV", cpu_clv, cpu_address_mode_implied, 1, 2);

  INSTRUCTION(0xC9, "[#] CMP", cpu_cmp, cpu_address_mode_immediate, 2, 2);
  INSTRUCTION(0xC5, "[ZP] CMP", cpu_cmp, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0xD5, "[ZP, X] CMP", cpu_cmp, cpu_address_mode_zp_x, 2, 4);
  INSTRUCTION(0xCD, "[ABS] CMP", cpu_cmp, cpu_address_mode_absolute, 3, 4);
  INSTRUCTION(0xDD, "[ABS, X] CMP", cpu_cmp, cpu_address_mode_absolute_x, 3, 4);
  INSTRUCTION(0xD9, "[ABS, Y] CMP", cpu_cmp, cpu_address_mode_absolute_y, 3, 4);
  INSTRUCTION(0xC1, "[(ZP), X] CMP", cpu_cmp, cpu_address_mode_indirect_x, 2,
              6);
  INSTRUCTION(0xD1, "[(ZP), Y] CMP", cpu_cmp, cpu_address_mode_indirect_y, 2,
              5);

  INSTRUCTION(0xE0, "[#] CPX", cpu_cpx, cpu_address_mode_immediate, 2, 2);
  INSTRUCTION(0xE4, "[ZP] CPX", cpu_cpx, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0xEC, "[ABS] CPX", cpu_cpx, cpu_address_mode_absolute, 3, 4);

  INSTRUCTION(0xC0, "[#] CPY", cpu_cpy, cpu_address_mode_immediate, 2, 2);
  INSTRUCTION(0xC4, "[ZP] CPY", cpu_cpy, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0xCC, "[ABS] CPY", cpu_cpy, cpu_address_mode_absolute, 3, 4);

  INSTRUCTION(0xC6, "[ZP] DEC", cpu_dec, cpu_address_mode_zp, 2, 5);
  INSTRUCTION(0xD6, "[ZP, x] DEC", cpu_dec, cpu_address_mode_zp_x, 2, 6);
  INSTRUCTION(0xCE, "[ABS] DEC", cpu_dec, cpu_address_mode_absolute, 3, 6);
  INSTRUCTION(0xDE, "[ABS, X] DEC", cpu_dec, cpu_address_mode_absolute_x, 3, 7);

  INSTRUCTION(0xCA, "DEX", cpu_dex, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0x88, "DEY", cpu_dey, cpu_address_mode_implied, 1, 2);

  INSTRUCTION(0x49, "[#] EOR", cpu_eor, cpu_address_mode_immediate, 2, 2);
  INSTRUCTION(0x45, "[ZP] EOR", cpu_eor, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0x55, "[ZP, X] EOR", cpu_eor, cpu_address_mode_zp_x, 2, 4);
  INSTRUCTION(0x4D, "[ABS] EOR", cpu_eor, cpu_address_mode_absolute, 3, 4);
  INSTRUCTION(0x5D, "[ABS, X] EOR", cpu_eor, cpu_address_mode_absolute_x, 3, 4);
  INSTRUCTION(0x59, "[ABS, Y] EOR", cpu_eor, cpu_address_mode_absolute_y, 3, 4);
  INSTRUCTION(0x41, "[(ZP), X] EOR", cpu_eor, cpu_address_mode_indirect_x, 2,
              6);
  INSTRUCTION(0x51, "[(ZP), Y] EOR", cpu_eor, cpu_address_mode_indirect_y, 2,
              5);

  INSTRUCTION(0xE6, "[ZP] INC", cpu_inc, cpu_address_mode_zp, 2, 5);
  INSTRUCTION(0xF6, "[ZP, X] INC", cpu_inc, cpu_address_mode_zp_x, 2, 6);
  INSTRUCTION(0xEE, "[ABS] INC", cpu_inc, cpu_address_mode_absolute, 3, 6);
  INSTRUCTION(0xFE, "[ABS, X] INC", cpu_inc, cpu_address_mode_absolute_x, 3, 7);

  INSTRUCTION(0xE8, "INX", cpu_inx, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0xC8, "INY", cpu_iny, cpu_address_mode_implied, 1, 2);

  INSTRUCTION(0x4C, "[ABS] JMP", cpu_jmp, cpu_address_mode_absolute, 3, 3);
  INSTRUCTION(0x6C, "[(ZP)] JMP", cpu_jmp, cpu_address_mode_indirect, 3, 5);
  INSTRUCTION(0x20, "[ABS] JSR", cpu_jsr, cpu_address_mode_absolute, 3, 6);

  INSTRUCTION(0xA9, "[#] LDA", cpu_lda, cpu_address_mode_immediate, 2, 2);
  INSTRUCTION(0xA5, "[ZP] LDA", cpu_lda, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0xB5, "[ZP, X] LDA", cpu_lda, cpu_address_mode_zp_x, 2, 4);
  INSTRUCTION(0xAD, "[ABS] LDA", cpu_lda, cpu_address_mode_absolute, 3, 4);
  INSTRUCTION(0xBD, "[ABS, X] LDA", cpu_lda, cpu_address_mode_absolute_x, 3, 4);
  INSTRUCTION(0xB9, "[ABS, Y] LDA", cpu_lda, cpu_address_mode_absolute_y, 3, 4);
  INSTRUCTION(0xA1, "[(ZP), X] LDA", cpu_lda, cpu_address_mode_indirect_x, 2,
              6);
  INSTRUCTION(0xB1, "[(ZP), Y] LDA", cpu_lda, cpu_address_mode_indirect_y, 2,
              5);

  INSTRUCTION(0xA2, "[#] LDX", cpu_ldx, cpu_address_mode_immediate, 2, 2);
  INSTRUCTION(0xA6, "[ZP] LDX", cpu_ldx, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0xB6, "[ZP, Y] LDX", cpu_ldx, cpu_address_mode_zp_y, 2, 4);
  INSTRUCTION(0xAE, "[ABS] LDX", cpu_ldx, cpu_address_mode_absolute, 3, 4);
  INSTRUCTION(0xBE, "[ABS, Y] LDX", cpu_ldx, cpu_address_mode_absolute_y, 3, 4);

  INSTRUCTION(0xA0, "[#] LDY", cpu_ldy, cpu_address_mode_immediate, 2, 2);
  INSTRUCTION(0xA4, "[ZP] LDY", cpu_ldy, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0xB4, "[ZP, X] LDY", cpu_ldy, cpu_address_mode_zp_x, 2, 4);
  INSTRUCTION(0xAC, "[ABS] LDY", cpu_ldy, cpu_address_mode_absolute, 3, 4);
  INSTRUCTION(0xBC, "[ABS, X] LDY", cpu_ldy, cpu_address_mode_absolute_x, 3, 4);

  INSTRUCTION(0x4A, "[A] LSR", cpu_lsr, cpu_address_mode_a, 1, 2);
  INSTRUCTION(0x46, "[ZP] LSR", cpu_lsr, cpu_address_mode_zp, 2, 5);
  INSTRUCTION(0x56, "[ZP, X] LSR", cpu_lsr, cpu_address_mode_zp_x, 2, 6);
  INSTRUCTION(0x4E, "[ABS] LSR", cpu_lsr, cpu_address_mode_absolute, 3, 6);
  INSTRUCTION(0x5E, "[ABS, X] LSR", cpu_lsr, cpu_address_mode_absolute_x, 3, 7);

  INSTRUCTION(0xEA, "NOP", cpu_nop, cpu_address_mode_implied, 1, 2);

  INSTRUCTION(0x09, "[#] ORA", cpu_ora, cpu_address_mode_immediate, 2, 2);
  INSTRUCTION(0x05, "[ZP] ORA", cpu_ora, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0x15, "[ZP, X] ORA", cpu_ora, cpu_address_mode_zp_x, 2, 4);
  INSTRUCTION(0x0D, "[ABS] ORA", cpu_ora, cpu_address_mode_absolute, 3, 4);
  INSTRUCTION(0x1D, "[ABS, X] ORA", cpu_ora, cpu_address_mode_absolute_x, 3, 4);
  INSTRUCTION(0x19, "[ABS, Y] ORA", cpu_ora, cpu_address_mode_absolute_y, 3, 4);
  INSTRUCTION(0x01, "[(ZP), X] ORA", cpu_ora, cpu_address_mode_indirect_x, 2,
              6);
  INSTRUCTION(0x11, "[(ZP), Y] ORA", cpu_ora, cpu_address_mode_indirect_y, 2,
              5);

  INSTRUCTION(0x48, "PHA", cpu_pha, cpu_address_mode_implied, 1, 3);
  INSTRUCTION(0x08, "PHP", cpu_php, cpu_address_mode_implied, 1, 3);
  INSTRUCTION(0x68, "PLA", cpu_pla, cpu_address_mode_implied, 1, 4);
  INSTRUCTION(0x28, "PLP", cpu_plp, cpu_address_mode_implied, 1, 4);

  INSTRUCTION(0x2A, "[A] ROL", cpu_rol, cpu_address_mode_a, 1, 2);
  INSTRUCTION(0x26, "[ZP] ROL", cpu_rol, cpu_address_mode_zp, 2, 5);
  INSTRUCTION(0x36, "[ZP, X] ROL", cpu_rol, cpu_address_mode_zp_x, 2, 6);
  INSTRUCTION(0x2E, "[ABS] ROL", cpu_rol, cpu_address_mode_absolute, 3, 6);
  INSTRUCTION(0x3E, "[ABS, X] ROL", cpu_rol, cpu_address_mode_absolute_x, 3, 7);

  INSTRUCTION(0x6A, "[A] ROR", cpu_ror, cpu_address_mode_a, 1, 2);
  INSTRUCTION(0x66, "[ZP] ROR", cpu_ror, cpu_address_mode_zp, 2, 5);
  INSTRUCTION(0x76, "[ZP, X] ROR", cpu_ror, cpu_address_mode_zp_x, 2, 6);
  INSTRUCTION(0x6E, "[ABS] ROR", cpu_ror, cpu_address_mode_absolute, 3, 6);
  INSTRUCTION(0x7E, "[ABS, X] ROR", cpu_ror, cpu_address_mode_absolute_x, 3, 7);

  INSTRUCTION(0x40, "RTI", cpu_rti, cpu_address_mode_implied, 1, 6);
  INSTRUCTION(0x60, "RTS", cpu_rts, cpu_address_mode_implied, 1, 6);

  INSTRUCTION(0xE9, "[#] SBC", cpu_sbc, cpu_address_mode_immediate, 2, 2);
  INSTRUCTION(0xE5, "[ZP] SBC", cpu_sbc, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0xF5, "[ZP, X] SBC", cpu_sbc, cpu_address_mode_zp_x, 2, 4);
  INSTRUCTION(0xED, "[ABS] SBC", cpu_sbc, cpu_address_mode_absolute, 3, 4);
  INSTRUCTION(0xFD, "[ABS, X] SBC", cpu_sbc, cpu_address_mode_absolute_x, 3, 4);
  INSTRUCTION(0xF9, "[ABS, Y] SBC", cpu_sbc, cpu_address_mode_absolute_y, 3, 4);
  INSTRUCTION(0xE1, "[(ZP), X] SBC", cpu_sbc, cpu_address_mode_indirect_x, 2,
              6);
  INSTRUCTION(0xF1, "[(ZP), Y] SBC", cpu_sbc, cpu_address_mode_indirect_y, 2,
              5);

  INSTRUCTION(0x38, "SEC", cpu_sec, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0xF8, "SED", cpu_sed, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0x78, "SEI", cpu_sei, cpu_address_mode_implied, 1, 2);

  INSTRUCTION(0x85, "[ZP] STA", cpu_sta, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0x95, "[ZP, X] STA", cpu_sta, cpu_address_mode_zp_x, 2, 4);
  INSTRUCTION(0x8D, "[ABS] STA", cpu_sta, cpu_address_mode_absolute, 3, 4);
  INSTRUCTION(0x9D, "[ABS, X] STA", cpu_sta, cpu_address_mode_absolute_x, 3, 5);
  INSTRUCTION(0x99, "[ABS, Y] STA", cpu_sta, cpu_address_mode_absolute_y, 3, 5);
  INSTRUCTION(0x81, "[(ZP), X] STA", cpu_sta, cpu_address_mode_indirect_x, 2,
              6);
  INSTRUCTION(0x91, "[(ZP), Y] STA", cpu_sta, cpu_address_mode_indirect_y, 2,
              6);

  INSTRUCTION(0x86, "[ZP] STX", cpu_stx, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0x96, "[ZP, Y] STX", cpu_stx, cpu_address_mode_zp_y, 2, 4);
  INSTRUCTION(0x8E, "[ABS] STX", cpu_stx, cpu_address_mode_absolute, 3, 4);

  INSTRUCTION(0x84, "[ZP] STY", cpu_sty, cpu_address_mode_zp, 2, 3);
  INSTRUCTION(0x94, "[ZP, X] STY", cpu_sty, cpu_address_mode_zp_x, 2, 4);
  INSTRUCTION(0x8C, "[ABS] STY", cpu_sty, cpu_address_mode_absolute, 3, 4);

  INSTRUCTION(0xAA, "TAX", cpu_tax, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0xA8, "TAY", cpu_tay, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0xBA, "TSX", cpu_tsx, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0x8A, "TXA", cpu_txa, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0x9A, "TXS", cpu_txs, cpu_address_mode_implied, 1, 2);
  INSTRUCTION(0x98, "TYA", cpu_tya, cpu_address_mode_implied, 1, 2);
}