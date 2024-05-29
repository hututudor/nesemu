#include "input.h"
#include "../utils/sdl.h"

bool keys[8] = {false};

void keys_update() {
  const u8* keys_state = SDL_GetKeyboardState(NULL);

  keys[KEY_A] = keys_state[SDL_SCANCODE_Z];
  keys[KEY_B] = keys_state[SDL_SCANCODE_X];
  keys[KEY_SELECT] = keys_state[SDL_SCANCODE_A];
  keys[KEY_START] = keys_state[SDL_SCANCODE_S];
  keys[KEY_UP] = keys_state[SDL_SCANCODE_UP];
  keys[KEY_DOWN] = keys_state[SDL_SCANCODE_DOWN];
  keys[KEY_LEFT] = keys_state[SDL_SCANCODE_LEFT];
  keys[KEY_RIGHT] = keys_state[SDL_SCANCODE_RIGHT];
}
