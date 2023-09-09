#include "instructions.h"

#include <stdio.h>

#include "../utils/assert.h"

void cpu_lda(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_ldx(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_ldy(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_sta(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_stx(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_sty(cpu_t* cpu, address_mode_t address_mode) {
  ASSERT_UNREACHABLE { ASSERT_UNREACHABLE; }
}

void cpu_tax(cpu_t* cpu, address_mode_t address_mode) {
  ASSERT_UNREACHABLE { ASSERT_UNREACHABLE; }
}

void cpu_tay(cpu_t* cpu, address_mode_t address_mode) {
  ASSERT_UNREACHABLE { ASSERT_UNREACHABLE; }
}

void cpu_txa(cpu_t* cpu, address_mode_t address_mode) {
  ASSERT_UNREACHABLE { ASSERT_UNREACHABLE; }
}

void cpu_tya(cpu_t* cpu, address_mode_t address_mode) {
  ASSERT_UNREACHABLE { ASSERT_UNREACHABLE; }
}

void cpu_tsx(cpu_t* cpu, address_mode_t address_mode) {
  ASSERT_UNREACHABLE { ASSERT_UNREACHABLE; }
}

void cpu_txs(cpu_t* cpu, address_mode_t address_mode) {
  ASSERT_UNREACHABLE { ASSERT_UNREACHABLE; }
}

void cpu_pha(cpu_t* cpu, address_mode_t address_mode) {
  ASSERT_UNREACHABLE { ASSERT_UNREACHABLE; }
}

void cpu_php(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_pla(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_plp(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_and(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_eor(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_ora(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_bit(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_adc(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_sbc(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_cmp(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_cpx(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_cpy(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_inc(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_inx(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_iny(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_dec(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_dex(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_dey(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_asl(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_lsr(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_rol(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_ror(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_jmp(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_jsr(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_rts(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_bcc(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_bcs(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_beq(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_bmi(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_bne(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_bpl(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_bvc(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_bvs(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_clc(cpu_t* cpu, address_mode_t address_mode) { cpu->status.c = 0; }

void cpu_cld(cpu_t* cpu, address_mode_t address_mode) { cpu->status.d = 0; }

void cpu_cli(cpu_t* cpu, address_mode_t address_mode) { cpu->status.i = 0; }

void cpu_clv(cpu_t* cpu, address_mode_t address_mode) { cpu->status.v = 0; }

void cpu_sec(cpu_t* cpu, address_mode_t address_mode) { cpu->status.c = 1; }

void cpu_sed(cpu_t* cpu, address_mode_t address_mode) { cpu->status.d = 1; }

void cpu_sei(cpu_t* cpu, address_mode_t address_mode) { cpu->status.i = 1; }

void cpu_brk(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_nop(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }

void cpu_rti(cpu_t* cpu, address_mode_t address_mode) { ASSERT_UNREACHABLE; }
