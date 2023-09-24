#include "bus.h"

#include <stdlib.h>

#include "../cpu/cpu.h"
#include "../ppu/ppu.h"

bus_t* bus_create(mapper_t* mapper, cpu_t* cpu, ppu_t* ppu) {
  bus_t* bus = (bus_t*)calloc(1, sizeof(bus_t));

  bus->ram = memory_create(0x0000, 0x0800);
  bus->apu_and_io = memory_create(0x4000, 0x0020);
  bus->cpu = cpu;
  bus->ppu = ppu;
  bus->mapper = mapper;

  return bus;
}

void bus_destroy(bus_t* bus) {
  if (!bus) {
    return;
  }

  memory_destroy(bus->ram);
  memory_destroy(bus->apu_and_io);

  free(bus);
}

bus_address_t parse_bus_address(bus_t* bus, u16 address) {
  bus_address_t bus_address;

  if (address < bus->apu_and_io->start) {
    bus_address.memory = bus->ram;
  } else {
    bus_address.memory = bus->apu_and_io;
  }

  bus_address.address =
      (address - bus_address.memory->start) & (bus_address.memory->size - 1);

  return bus_address;
}

u8 bus_read8(bus_t* bus, u16 address) {
  if (address >= 0x4020) {
    return bus->mapper->prg_read8(bus->mapper, address - 0x4020);
  }

  if (address >= 0x2000 && address <= 0x3FFF) {
    return ppu_read8(bus->ppu, address - 0x2000);
  }

  bus_address_t bus_address = parse_bus_address(bus, address);
  return memory_read8(bus_address.memory, bus_address.address);
}

void bus_write8(bus_t* bus, u16 address, u8 value) {
  if (address >= 0x4020) {
    bus->mapper->prg_write8(bus->mapper, address - 0x4020, value);
    return;
  }

  if (address >= 0x2000 && address <= 0x3FFF) {
    ppu_write8(bus->ppu, address - 0x2000, value);
    return;
  }

  bus_address_t bus_address = parse_bus_address(bus, address);
  memory_write8(bus_address.memory, bus_address.address, value);
}

u16 bus_read16(bus_t* bus, u16 address) {
  if (address >= 0x4020) {
    return bus->mapper->prg_read16(bus->mapper, address - 0x4020);
  }

  bus_address_t bus_address = parse_bus_address(bus, address);
  return memory_read16(bus_address.memory, bus_address.address);
}

void bus_write16(bus_t* bus, u16 address, u16 value) {
  if (address >= 0x4020) {
    bus->mapper->prg_write16(bus->mapper, address - 0x4020, value);
    return;
  }

  bus_address_t bus_address = parse_bus_address(bus, address);
  memory_write16(bus_address.memory, bus_address.address, value);
}