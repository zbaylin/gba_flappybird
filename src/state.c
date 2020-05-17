#include <stdlib.h>

#include "consts.h"
#include "state.h"
#include "render.h"


void initGameState(GameState *state) {
  state->score = 0;
  state->birdY = INT_TO_FIXED(INITIAL_BIRD_Y);
  state->birdVelocity = INITIAL_BIRD_VELOCITY;
  state->pipeFront = 0;
  /* There are 2^9 = 512 possible x-coords for each sprite
    Since each sprite is 24 pixels wide, we need to space them
    (512 - (6 * 24)) / 6 = 61.333 pixels apart. Obviously
    we don't have subpixel positioning, so I have to interpolate
    the thirds myself.
   */
  state->pipes[0] = (Pipe) {
    .x = 61,
    .numTop = randint(1, 4)
  };
  state->pipes[1] = (Pipe) {
    .x = 146,
    .numTop = randint(1, 4)
  };
  state->pipes[2] = (Pipe) {
    .x = 232,
    .numTop = randint(1, 4)
  };
  state->pipes[3] = (Pipe) {
    .x = 317,
    .numTop = randint(1, 4)
  };
  state->pipes[4] = (Pipe) {
    .x = 402,
    .numTop = randint(1, 4)
  };
  state->pipes[5] = (Pipe) {
    .x = 488,
    .numTop = randint(1, 4)
  };
}
