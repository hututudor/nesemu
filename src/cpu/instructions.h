#pragma once

#include "cpu.h"

u8 cpu_lda(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_ldx(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_ldy(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_sta(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_stx(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_sty(cpu_t* cpu, address_mode_t address_mode);

u8 cpu_tax(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_tay(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_txa(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_tya(cpu_t* cpu, address_mode_t address_mode);

u8 cpu_tsx(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_txs(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_pha(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_php(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_pla(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_plp(cpu_t* cpu, address_mode_t address_mode);

u8 cpu_and(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_eor(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_ora(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_bit(cpu_t* cpu, address_mode_t address_mode);

u8 cpu_adc(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_sbc(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_cmp(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_cpx(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_cpy(cpu_t* cpu, address_mode_t address_mode);

u8 cpu_inc(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_inx(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_iny(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_dec(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_dex(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_dey(cpu_t* cpu, address_mode_t address_mode);

u8 cpu_asl(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_lsr(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_rol(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_ror(cpu_t* cpu, address_mode_t address_mode);

u8 cpu_jmp(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_jsr(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_rts(cpu_t* cpu, address_mode_t address_mode);

u8 cpu_bcc(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_bcs(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_beq(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_bmi(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_bne(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_bpl(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_bvc(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_bvs(cpu_t* cpu, address_mode_t address_mode);

u8 cpu_clc(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_cld(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_cli(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_clv(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_sec(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_sed(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_sei(cpu_t* cpu, address_mode_t address_mode);

u8 cpu_brk(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_nop(cpu_t* cpu, address_mode_t address_mode);
u8 cpu_rti(cpu_t* cpu, address_mode_t address_mode);
