#include "window.h"

#include <SDL2/SDL.h>

#include "../peripherals/screen.h"

#define SCREEN_SCALE 3

bool window_is_running;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* screen_texture = NULL;

u32 start_time;

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
  start_time = SDL_GetTicks();

  // if (frame_time < 1000 / 60) {
  //   SDL_Delay((1000 / 60) - frame_time);
  // }

  // frame_time = SDL_GetTicks() - start_time;

  // printf("FPS: %d\n", frame_time);

  // char* title = malloc(256);
  // sprintf(title, "FPS: %f", 1000.0f / frame_time);
  // printf("%s\n", title);
  // SDL_SetWindowTitle(window, title);
  // free(title);
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