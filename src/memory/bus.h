#pragma once

#include "../mappers/mapper.h"
#include "memory.h"

typedef struct ppu_t ppu_t;
typedef struct cpu_t cpu_t;
typedef struct controller_t controller_t;

typedef struct {
  memory_t* ram;
  memory_t* apu_and_io;
  ppu_t* ppu;
  cpu_t* cpu;
  controller_t* controller_1;
  controller_t* controller_2;
  mapper_t* mapper;

  bool dma_transfer;
  bool dma_skip_odd_cycle;

  u8 dma_page;
  u8 dma_address;
  u8 dma_data;
} bus_t;

typedef struct {
  memory_t* memory;
  u16 address;
} bus_address_t;

bus_t* bus_create(mapper_t* mapper, cpu_t* cpu, ppu_t* ppu,
                  controller_t* controller_1, controller_t* controller_2);
void bus_destroy(bus_t* bus);

u8 bus_read8(bus_t* bus, u16 address);
void bus_write8(bus_t* bus, u16 address, u8 value);

u16 bus_read16(bus_t* bus, u16 address);
void bus_write16(bus_t* bus, u16 address, u16 value);