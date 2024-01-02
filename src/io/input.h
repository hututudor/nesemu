#pragma once

#include "../utils/types.h"

#define KEY_A 0
#define KEY_B 1
#define KEY_SELECT 2
#define KEY_START 3
#define KEY_UP 4
#define KEY_DOWN 5
#define KEY_LEFT 6
#define KEY_RIGHT 7

extern bool keys[8];

void keys_update();
