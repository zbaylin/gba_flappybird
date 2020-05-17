#ifndef STATE_H
#define STATE_H

#include <stdbool.h>

#include "types.h"
#include "consts.h"

/* GlobalState
  Basically a virtual FSM for the game/program
  Differs from the gamestate because the gamestate
  is tied to a specific instance of the game.
 */
typedef enum { START, TITLE, SETUP_GAME, ACTIVE_GAME, SETUP_GAME_OVER, GAME_OVER } GlobalState;

typedef struct {
  u16 x;
  u8 numTop;
} Pipe;

/* GameState
  Stores all the revelant game information.
  Specific to an instance of a game, i.e.
  if you die 3 times, then a new gamestate must be created
 */
typedef struct {
  u32 score;
  s32 birdVelocity;
  s32 birdY;
  Pipe pipes[MAX_PIPES];
  u32 pipeFront;
} GameState;

void initGameState(GameState *state);

#endif
