#include "memory.h"

#include <stdio.h>
#include <stdlib.h>

#include "../utils/assert.h"

memory_t* memory_create(u16 start, u16 size) {
  memory_t* memory = (memory_t*)calloc(1, sizeof(memory));
  if (!memory) {
    ASSERT_UNREACHABLE;
  }

  void* data = (void*)calloc(size, sizeof(u8));
  if (!data) {
    ASSERT_UNREACHABLE;
  }

  memory->data = data;
  memory->size = size;

  memory->start = start;
  memory->end = start + size - 1;

  return memory;
}

void memory_destroy(memory_t* memory) {
  if (!memory->data) {
    return;
  }

  free(memory->data);
  free(memory);
}

u8 memory_read8(memory_t* memory, u16 address) {
  if (address > memory->size) {
    ASSERT_UNREACHABLE;
  }

  return memory->data[address];
}

void memory_write8(memory_t* memory, u16 address, u8 value) {
  if (address > memory->end) {
    ASSERT_UNREACHABLE;
  }

  memory->data[address] = value;
}

u16 memory_read16(memory_t* memory, u16 address) {
  if ((address + 1) > memory->size) {
    ASSERT_UNREACHABLE;
  }

  return (memory->data[address + 1] << 8) | memory->data[address];
}

void memory_write16(memory_t* memory, u16 address, u16 value) {
  if ((address + 1) > memory->end) {
    ASSERT_UNREACHABLE;
  }

  memory->data[address] = value & 0xFF;
  memory->data[address + 1] = (value & 0xFF00) >> 8;
}
