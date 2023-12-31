#pragma once

#include "../../src/cpu/cpu.h"
#include "./bus.h"

cpu_t* mock_cpu() {
  bus_t* bus = mock_bus();
  return bus->cpu;
}

#define INSTRUCTION_LDA_ABSOLUTE 0xAD
#define INSTRUCTION_LDA_ABSOLUTE_X 0xBD
#define INSTRUCTION_LDA_ABSOLUTE_Y 0xB9
#define INSTRUCTION_LDA_IMMEDIATE 0xA9
#define INSTRUCTION_LDA_ZP 0xA5
#define INSTRUCTION_LDA_INDIRECT_X 0xA1
#define INSTRUCTION_LDA_ZP_X 0xB5
#define INSTRUCTION_LDA_INDIRECT_Y 0xB1

#define INSTRUCTION_LDX_ABSOLUTE 0xAE
#define INSTRUCTION_LDX_ABSOLUTE_Y 0xBE
#define INSTRUCTION_LDX_IMMEDIATE 0xA2
#define INSTRUCTION_LDX_ZP 0xA6
#define INSTRUCTION_LDX_ZP_Y 0xB6

#define INSTRUCTION_LDY_ABSOLUTE 0xAC
#define INSTRUCTION_LDY_ABSOLUTE_X 0xBC
#define INSTRUCTION_LDY_IMMEDIATE 0xA0
#define INSTRUCTION_LDY_ZP 0xA4
#define INSTRUCTION_LDY_ZP_X 0xB4

#define INSTRUCTION_STA_ABSOLUTE 0x8D
#define INSTRUCTION_STA_ABSOLUTE_X 0x9D
#define INSTRUCTION_STA_ABSOLUTE_Y 0x99
#define INSTRUCTION_STA_ZP 0x85
#define INSTRUCTION_STA_INDIRECT_X 0x81
#define INSTRUCTION_STA_ZP_X 0x95
#define INSTRUCTION_STA_INDIRECT_Y 0x91

#define INSTRUCTION_STX_ABSOLUTE 0x8E
#define INSTRUCTION_STX_ZP 0x86
#define INSTRUCTION_STX_ZP_Y 0x96

#define INSTRUCTION_STY_ABSOLUTE 0x8C
#define INSTRUCTION_STY_ZP 0x84
#define INSTRUCTION_STY_ZP_X 0x94

#define INSTRUCTION_ADC_ABSOLUTE 0x6D
#define INSTRUCTION_ADC_ABSOLUTE_X 0x7D
#define INSTRUCTION_ADC_ABSOLUTE_Y 0x79
#define INSTRUCTION_ADC_IMMEDIATE 0x69
#define INSTRUCTION_ADC_ZP 0x65
#define INSTRUCTION_ADC_INDIRECT_X 0x61
#define INSTRUCTION_ADC_ZP_X 0x75
#define INSTRUCTION_ADC_INDIRECT_Y 0x71

#define INSTRUCTION_SBC_ABSOLUTE 0xED
#define INSTRUCTION_SBC_ABSOLUTE_X 0xFD
#define INSTRUCTION_SBC_ABSOLUTE_Y 0xF9
#define INSTRUCTION_SBC_IMMEDIATE 0xE9
#define INSTRUCTION_SBC_ZP 0xE5
#define INSTRUCTION_SBC_INDIRECT_X 0xE1
#define INSTRUCTION_SBC_ZP_X 0xF5
#define INSTRUCTION_SBC_INDIRECT_Y 0xF1

#define INSTRUCTION_INC_ABSOLUTE 0xEE
#define INSTRUCTION_INC_ABSOLUTE_X 0xFE
#define INSTRUCTION_INC_ZP 0xE6
#define INSTRUCTION_INC_ZP_X 0xF6

#define INSTRUCTION_INX 0xE8
#define INSTRUCTION_INY 0xC8

#define INSTRUCTION_DEC_ABSOLUTE 0xCE
#define INSTRUCTION_DEC_ABSOLUTE_X 0xDE
#define INSTRUCTION_DEC_ZP 0xC6
#define INSTRUCTION_DEC_ZP_X 0xD6

#define INSTRUCTION_DEX 0xCA
#define INSTRUCTION_DEY 0x88

#define INSTRUCTION_ASL_A_REG 0x0A
#define INSTRUCTION_ASL_ABSOLUTE 0x0E
#define INSTRUCTION_ASL_ABSOLUTE_X 0x1E
#define INSTRUCTION_ASL_ZP 0x06
#define INSTRUCTION_ASL_ZP_X 0x16

#define INSTRUCTION_LSR_A_REG 0x4A
#define INSTRUCTION_LSR_ABSOLUTE 0x4E
#define INSTRUCTION_LSR_ABSOLUTE_X 0x5E
#define INSTRUCTION_LSR_ZP 0x46
#define INSTRUCTION_LSR_ZP_X 0x56

#define INSTRUCTION_ROL_ABSOLUTE 0x2E
#define INSTRUCTION_ROL_ABSOLUTE_X 0x3E
#define INSTRUCTION_ROL_A_REG 0x2A
#define INSTRUCTION_ROL_ZP 0x26
#define INSTRUCTION_ROL_ZP_X 0x36

#define INSTRUCTION_ROR_ABSOLUTE 0x6E
#define INSTRUCTION_ROR_ABSOLUTE_X 0x7E
#define INSTRUCTION_ROR_A_REG 0x6A
#define INSTRUCTION_ROR_ZP 0x66
#define INSTRUCTION_ROR_ZP_X 0x76

#define INSTRUCTION_AND_ABSOLUTE 0x2D
#define INSTRUCTION_AND_ABSOLUTE_X 0x3D
#define INSTRUCTION_AND_ABSOLUTE_Y 0x39
#define INSTRUCTION_AND_IMMEDIATE 0x29
#define INSTRUCTION_AND_ZP 0x25
#define INSTRUCTION_AND_INDIRECT_X 0x21
#define INSTRUCTION_AND_ZP_X 0x35
#define INSTRUCTION_AND_INDIRECT_Y 0x31

#define INSTRUCTION_ORA_ABSOLUTE 0x0D
#define INSTRUCTION_ORA_ABSOLUTE_X 0x1D
#define INSTRUCTION_ORA_ABSOLUTE_Y 0x19
#define INSTRUCTION_ORA_IMMEDIATE 0x09
#define INSTRUCTION_ORA_ZP 0x05
#define INSTRUCTION_ORA_INDIRECT_X 0x01
#define INSTRUCTION_ORA_ZP_X 0x15
#define INSTRUCTION_ORA_INDIRECT_Y 0x11

#define INSTRUCTION_EOR_ABSOLUTE 0x4D
#define INSTRUCTION_EOR_ABSOLUTE_X 0x5D
#define INSTRUCTION_EOR_ABSOLUTE_Y 0x59
#define INSTRUCTION_EOR_IMMEDIATE 0x49
#define INSTRUCTION_EOR_ZP 0x45
#define INSTRUCTION_EOR_INDIRECT_X 0x41
#define INSTRUCTION_EOR_ZP_X 0x55
#define INSTRUCTION_EOR_INDIRECT_Y 0x51

#define INSTRUCTION_CMP_ABSOLUTE 0xCD
#define INSTRUCTION_CMP_ABSOLUTE_X 0xDD
#define INSTRUCTION_CMP_ABSOLUTE_Y 0xD9
#define INSTRUCTION_CMP_IMMEDIATE 0xC9
#define INSTRUCTION_CMP_ZP 0xC5
#define INSTRUCTION_CMP_INDIRECT_X 0xC1
#define INSTRUCTION_CMP_ZP_X 0xD5
#define INSTRUCTION_CMP_INDIRECT_Y 0xD1

#define INSTRUCTION_CPX_ABSOLUTE 0xEC
#define INSTRUCTION_CPX_IMMEDIATE 0xE0
#define INSTRUCTION_CPX_ZP 0xE4

#define INSTRUCTION_CPY_ABSOLUTE 0xCC
#define INSTRUCTION_CPY_IMMEDIATE 0xC0
#define INSTRUCTION_CPY_ZP 0xC4

#define INSTRUCTION_BIT_ABSOLUTE 0x2C
#define INSTRUCTION_BIT_IMMEDIATE 0x89
#define INSTRUCTION_BIT_ZP 0x24

#define INSTRUCTION_BCC_RELATIVE 0x90
#define INSTRUCTION_BCS_RELATIVE 0xB0
#define INSTRUCTION_BNE_RELATIVE 0xD0
#define INSTRUCTION_BEQ_RELATIVE 0xF0
#define INSTRUCTION_BPL_RELATIVE 0x10
#define INSTRUCTION_BMI_RELATIVE 0x30
#define INSTRUCTION_BVC_RELATIVE 0x50
#define INSTRUCTION_BVS_RELATIVE 0x70

#define INSTRUCTION_TAX 0xAA
#define INSTRUCTION_TXA 0x8A
#define INSTRUCTION_TAY 0xA8
#define INSTRUCTION_TYA 0x98
#define INSTRUCTION_TSX 0xBA
#define INSTRUCTION_TXS 0x9A

#define INSTRUCTION_PHA 0x48
#define INSTRUCTION_PLA 0x68
#define INSTRUCTION_PHP 0x08
#define INSTRUCTION_PLP 0x28

#define INSTRUCTION_JMP_ABSOLUTE 0x4C
#define INSTRUCTION_JMP_IND_ABSOLUTE 0x6C

#define INSTRUCTION_JSR_ABSOLUTE 0x20

#define INSTRUCTION_RTS 0x60
#define INSTRUCTION_RTI 0x40

#define INSTRUCTION_CLC 0x18
#define INSTRUCTION_SEC 0x38
#define INSTRUCTION_CLD 0xD8
#define INSTRUCTION_SED 0xF8
#define INSTRUCTION_CLI 0x58
#define INSTRUCTION_SEI 0x78
#define INSTRUCTION_CLV 0xB8

#define INSTRUCTION_BRK 0x00
#define INSTRUCTION_NOP 0xEA
