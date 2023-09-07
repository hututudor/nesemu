#pragma once

#include "../utils/types.h"

typedef struct {
  u8* data;
  u16 size;

  u16 start;
  u16 end;
} memory_t;

memory_t* memory_create(u16 start, u16 size);
void memory_destroy(memory_t* memory);

u8 memory_read8(memory_t* memory, u16 address);
void memory_write8(memory_t* memory, u16 address, u8 value);

u16 memory_read16(memory_t* memory, u16 address);
void memory_write16(memory_t* memory, u16 address, u16 value);
