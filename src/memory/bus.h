#pragma once

#include "../mappers/mapper.h"
#include "memory.h"

typedef struct ppu_t ppu_t;

typedef struct {
  memory_t* ram;
  memory_t* apu_and_io;
  ppu_t* ppu;
  mapper_t* mapper;
} bus_t;

typedef struct {
  memory_t* memory;
  u16 address;
} bus_address_t;

bus_t* bus_create(mapper_t* mapper, ppu_t* ppu);
void bus_destroy(bus_t* bus);

u8 bus_read8(bus_t* bus, u16 address);
void bus_write8(bus_t* bus, u16 address, u8 value);

u16 bus_read16(bus_t* bus, u16 address);
void bus_write16(bus_t* bus, u16 address, u16 value);