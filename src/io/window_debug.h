#pragma once

#include "../utils/sdl.h"

#include "window.h"

void debug_screen_init();
void debug_screen_destroy();
void debug_screen_update(nes_t* nes);
void debug_screen_process_event(nes_t* nes, SDL_Event* e);