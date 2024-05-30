#pragma once

#include "../config/globals.h"
#include "../nes/nes.h"
#include "../utils/sdl.h"
#include "../utils/types.h"

#define UPSCALED_SCREEN_WIDTH (SCREEN_WIDTH * SCREEN_SCALE)
#define UPSCALED_SCREEN_HEIGHT (SCREEN_HEIGHT * SCREEN_SCALE)

#if !DEBUG_MODE
#define WINDOW_WIDTH (UPSCALED_SCREEN_WIDTH)
#define WINDOW_HEIGHT (UPSCALED_SCREEN_HEIGHT)
#else
#define WINDOW_WIDTH (UPSCALED_SCREEN_WIDTH + 594)
#define WINDOW_HEIGHT 888
#endif

extern bool window_is_running;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* screen_texture;

void window_init();
void window_destroy();

void window_update(nes_t* nes);
