#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

u8* read_entire_file(char* path) {
  FILE* file = fopen(path, "rb");

  if (!file) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  s32 file_size = ftell(file);

  if (file_size < 0) {
    fclose(file);
    return NULL;
  }

  fseek(file, 0, SEEK_SET);
  u8* data = (u8*)calloc(file_size + 1, sizeof(u8));
  s32 read_size = fread(data, sizeof(u8), file_size, file);
  fclose(file);

  if (read_size != file_size) {
    free(data);
    return NULL;
  }

  data[file_size] = 0;

  return data;
}