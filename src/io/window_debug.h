#pragma once

#include <SDL2/SDL.h>

#include "window.h"

void debug_screen_init();
void debug_screen_destroy();
void debug_screen_update(nes_t* nes);
void debug_screen_process_event(SDL_Event* e);