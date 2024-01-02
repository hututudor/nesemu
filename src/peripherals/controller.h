#pragma once

#include "../utils/types.h"

typedef struct controller_t {
  u8 reg;
  bool strobe;
} controller_t;

controller_t *controller_create();
void controller_destroy(controller_t *controller);

void controller_set_strobe(controller_t *controller, u8 value);
bool controller_read(controller_t *controller);

void controller_update(controller_t *controller);