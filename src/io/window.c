#include "window.h"

#include <SDL2/SDL.h>

#include "../peripherals/screen.h"

#define SCREEN_SCALE 3

#define TARGET_FPS 60
#define TITLE_UPDATE_INTERVAL 500

bool window_is_running;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* screen_texture = NULL;

u32 start_time;
u32 title_updated_time;

SDL_Event e;

void window_init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    perror("Could not init SDL\n");
    return;
  }

  window = SDL_CreateWindow("NESEMU", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * SCREEN_SCALE,
                            SCREEN_HEIGHT * SCREEN_SCALE, 0);
  if (!window) {
    perror("Could not init SDL window\n");
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    perror("Could not init SDL renderer\n");
  }

  screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                     SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH,
                                     SCREEN_HEIGHT);
  if (!screen_texture) {
    perror("Could not init SDL screen texture\n");
  }

  window_is_running = true;
  start_time = SDL_GetTicks();

  screen_init();
}

void window_destroy() {
  if (screen_texture) {
    SDL_DestroyTexture(screen_texture);
  }

  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }

  if (window) {
    SDL_DestroyWindow(window);
  }

  SDL_Quit();
}

static void update_fps() {
  u32 frame_time = SDL_GetTicks() - start_time;

  if (frame_time < (1000.0f / TARGET_FPS)) {
    SDL_Delay((1000.0f / TARGET_FPS) - frame_time);
    frame_time = SDL_GetTicks() - start_time;
  }

  u32 fps = 1000.0f / frame_time;

  start_time = SDL_GetTicks();

  if (SDL_GetTicks() - title_updated_time < TITLE_UPDATE_INTERVAL) {
    return;
  }

  title_updated_time = SDL_GetTicks();

  char* title = malloc(256);
  sprintf(title, "FPS: %d", fps);
  SDL_SetWindowTitle(window, title);
  free(title);
}

static void render_screen() {
  SDL_UpdateTexture(screen_texture, NULL, screen, sizeof(u32) * SCREEN_WIDTH);
  SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void window_update() {
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      window_is_running = false;
    }
  }

  render_screen();
  update_fps();
}