#pragma once

#include "cpu.h"

void cpu_lda(cpu_t* cpu, address_mode_t address_mode);
void cpu_ldx(cpu_t* cpu, address_mode_t address_mode);
void cpu_ldy(cpu_t* cpu, address_mode_t address_mode);
void cpu_sta(cpu_t* cpu, address_mode_t address_mode);
void cpu_stx(cpu_t* cpu, address_mode_t address_mode);
void cpu_sty(cpu_t* cpu, address_mode_t address_mode);

void cpu_tax(cpu_t* cpu, address_mode_t address_mode);
void cpu_tay(cpu_t* cpu, address_mode_t address_mode);
void cpu_txa(cpu_t* cpu, address_mode_t address_mode);
void cpu_tya(cpu_t* cpu, address_mode_t address_mode);

void cpu_tsx(cpu_t* cpu, address_mode_t address_mode);
void cpu_txs(cpu_t* cpu, address_mode_t address_mode);
void cpu_pha(cpu_t* cpu, address_mode_t address_mode);
void cpu_php(cpu_t* cpu, address_mode_t address_mode);
void cpu_pla(cpu_t* cpu, address_mode_t address_mode);
void cpu_plp(cpu_t* cpu, address_mode_t address_mode);

void cpu_and(cpu_t* cpu, address_mode_t address_mode);
void cpu_eor(cpu_t* cpu, address_mode_t address_mode);
void cpu_ora(cpu_t* cpu, address_mode_t address_mode);
void cpu_bit(cpu_t* cpu, address_mode_t address_mode);

void cpu_adc(cpu_t* cpu, address_mode_t address_mode);
void cpu_sbc(cpu_t* cpu, address_mode_t address_mode);
void cpu_cmp(cpu_t* cpu, address_mode_t address_mode);
void cpu_cpx(cpu_t* cpu, address_mode_t address_mode);
void cpu_cpy(cpu_t* cpu, address_mode_t address_mode);

void cpu_inc(cpu_t* cpu, address_mode_t address_mode);
void cpu_inx(cpu_t* cpu, address_mode_t address_mode);
void cpu_iny(cpu_t* cpu, address_mode_t address_mode);
void cpu_dec(cpu_t* cpu, address_mode_t address_mode);
void cpu_dex(cpu_t* cpu, address_mode_t address_mode);
void cpu_dey(cpu_t* cpu, address_mode_t address_mode);

void cpu_asl(cpu_t* cpu, address_mode_t address_mode);
void cpu_lsr(cpu_t* cpu, address_mode_t address_mode);
void cpu_rol(cpu_t* cpu, address_mode_t address_mode);
void cpu_ror(cpu_t* cpu, address_mode_t address_mode);

void cpu_jmp(cpu_t* cpu, address_mode_t address_mode);
void cpu_jsr(cpu_t* cpu, address_mode_t address_mode);
void cpu_rts(cpu_t* cpu, address_mode_t address_mode);

void cpu_bcc(cpu_t* cpu, address_mode_t address_mode);
void cpu_bcs(cpu_t* cpu, address_mode_t address_mode);
void cpu_beq(cpu_t* cpu, address_mode_t address_mode);
void cpu_bmi(cpu_t* cpu, address_mode_t address_mode);
void cpu_bne(cpu_t* cpu, address_mode_t address_mode);
void cpu_bpl(cpu_t* cpu, address_mode_t address_mode);
void cpu_bvc(cpu_t* cpu, address_mode_t address_mode);
void cpu_bvs(cpu_t* cpu, address_mode_t address_mode);

void cpu_clc(cpu_t* cpu, address_mode_t address_mode);
void cpu_cld(cpu_t* cpu, address_mode_t address_mode);
void cpu_cli(cpu_t* cpu, address_mode_t address_mode);
void cpu_clv(cpu_t* cpu, address_mode_t address_mode);
void cpu_sec(cpu_t* cpu, address_mode_t address_mode);
void cpu_sed(cpu_t* cpu, address_mode_t address_mode);
void cpu_sei(cpu_t* cpu, address_mode_t address_mode);

void cpu_brk(cpu_t* cpu, address_mode_t address_mode);
void cpu_nop(cpu_t* cpu, address_mode_t address_mode);
void cpu_rti(cpu_t* cpu, address_mode_t address_mode);
