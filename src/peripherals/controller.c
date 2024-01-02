#include "controller.h"

#include <stdio.h>
#include <stdlib.h>

#include "../io/input.h"

controller_t* controller_create() {
  controller_t* controller = (controller_t*)calloc(1, sizeof(controller_t));

  return controller;
}

void controller_destroy(controller_t* controller) {
  if (!controller) {
    return;
  }

  free(controller);
}

void controller_set_strobe(controller_t* controller, u8 value) {
  controller->strobe = value & 1;
}

bool controller_read(controller_t* controller) {
  bool value = controller->reg & 1;
  controller->reg >>= 1;
  controller->reg |= 0x80;
  return value;
}

void controller_update(controller_t* controller) {
  if (!controller->strobe) {
    return;
  }

  controller->reg = 0;
  for (s8 i = 7; i >= 0; i--) {
    controller->reg <<= 1;
    controller->reg |= keys[i];
  }
}