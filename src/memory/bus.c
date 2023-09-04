#include "bus.h"

#include <stdlib.h>

bus_t* bus_create() {
  bus_t* bus = (bus_t*)calloc(1, sizeof(bus_t));

  bus->ram = memory_create(0x0000, 0x0800);
  bus->ppu_registers = memory_create(0x2000, 0x0008);
  bus->apu_and_io = memory_create(0x4000, 0x0020);
  bus->rom = memory_create(0x4020, 0xBFE0);

  return bus;
}

void bus_destroy(bus_t* bus) {
  if (!bus) {
    return;
  }

  memory_destroy(bus->ram);
  memory_destroy(bus->ppu_registers);
  memory_destroy(bus->apu_and_io);
  memory_destroy(bus->rom);

  free(bus);
}

bus_address_t parse_bus_address(bus_t* bus, u16 address) {
  bus_address_t bus_address;

  if (address < 0x2000) {
    bus_address.memory = bus->ram;
    bus_address.address = address & 0x07FF;
    return bus_address;
  }

  if (address < 0x4000) {
    bus_address.memory = bus->ppu_registers;
    bus_address.address = (address - 0x2000) & 0x0007;
    return bus_address;
  }

  if (address < 0x4020) {
    bus_address.memory = bus->apu_and_io;
    bus_address.address = (address - 0x4000);
    return bus_address;
  }

  bus_address.memory = bus->rom;
  bus_address.address = (address - 0x4020);
  return bus_address;
}

u8 bus_read8(bus_t* bus, u16 address) {
  bus_address_t bus_address = parse_bus_address(bus, address);
  return memory_read8(bus_address.memory, bus_address.address);
}

void bus_write8(bus_t* bus, u16 address, u8 value) {
  bus_address_t bus_address = parse_bus_address(bus, address);
  memory_write8(bus_address.memory, bus_address.address, value);
}