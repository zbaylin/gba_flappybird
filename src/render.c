#include "render.h"
#include "consts.h"
#include "state.h"
#include "gba.h"
#include "sprites/sprites.h"
#include "fixed.h"
#include "lookup/sin.h"
#include "lookup/cos.h"
#include "lookup/lookup.h"
#include "images/game_bg.h"
#include "sounds/effects.h"

#include <stdio.h>
#include <stdbool.h>

void drawScore(int score) {
  int ones = score % 10;
  int tens = (score % 100) / 10;
  intIntoSprite(ONES_SPRITE, ones);
  intIntoSprite(TENS_SPRITE, tens);

  sprite_show(ONES_SPRITE);
  sprite_set_pos(ONES_SPRITE, ONES_DIGIT_X, ONES_DIGIT_Y);

  sprite_show(TENS_SPRITE);
  sprite_set_pos(TENS_SPRITE, TENS_DIGIT_X, TENS_DIGIT_Y);
}

void drawBird(GameState *state) {
  aff_sprite_show(BIRD_SPRITE);
  state->birdY += state->birdVelocity;
  sprite_set_pos(BIRD_SPRITE, BIRD_X, FIXED_TO_INT(state->birdY));

  if (FIXED_TO_INT(state->birdVelocity) > 200) {
    affineSpriteRotate(BIRD_AFF_SPRITE, (state->birdVelocity / 10) % 360 + 180);
  } else {
    affineSpriteRotate(BIRD_AFF_SPRITE, state->birdVelocity / 10);
  }

  state->birdVelocity += GRAVITY;
}

void drawPipes(GameState *state) {
  for (int i = 0; i < MAX_PIPES; i++) {
    for (int j = 0; j < MAX_VERT_PIPES; j++) {
      OBJ_ATTR *pipeSprite = pipeSprites[i][j];
      if (j <= state->pipes[i].numTop) {
        if (j == state->pipes[i].numTop) {
          INIT_SPRITE(*pipeSprite, PIPEHEAD);
        } else {
          INIT_SPRITE(*pipeSprite, PIPEBODY);
        }
        sprite_set_pos(pipeSprite, state->pipes[i].x, j * PIPE_BLOCK_HEIGHT);
      } else {
        if (j == state->pipes[i].numTop + 1) {
          INIT_SPRITE(*pipeSprite, PIPEHEAD);
        } else {
          INIT_SPRITE(*pipeSprite, PIPEBODY);
        }
        sprite_set_pos(pipeSprite, state->pipes[i].x, j * PIPE_BLOCK_HEIGHT + PIPE_GAP);
      }
      sprite_show(pipeSprite);
    }
    state->pipes[i].x--;
    if (state->pipes[i].x % 512 == 512 - PIPE_BLOCK_WIDTH) {
      playPointSFX();
      state->pipeFront = (state->pipeFront + 1) % MAX_PIPES;
      state->score++;
      state->pipes[i].numTop = randint(1, 4);
    }
  }
}

bool testCollisions(GameState *state) {
  Pipe frontPipe = state->pipes[state->pipeFront];

  if (
    FIXED_TO_INT(state->birdY) >= HEIGHT - BIRD_HEIGHT ||
    (s32)(FIXED_TO_INT(state->birdY)) <= 0 ||
    (BIRD_X < frontPipe.x % 512 + PIPE_BLOCK_WIDTH &&
     BIRD_X + BIRD_WIDTH > frontPipe.x % 512 && (
       (FIXED_TO_INT(state->birdY) < (s32)((frontPipe.numTop + 1) * PIPE_BLOCK_HEIGHT) &&
        FIXED_TO_INT(state->birdY) + (s32)(BIRD_HEIGHT > 0)) ||
       (FIXED_TO_INT(state->birdY) < (s32)((frontPipe.numTop + 1 + PIPE_BLOCK_GAP) * PIPE_BLOCK_HEIGHT) + HEIGHT &&
        FIXED_TO_INT(state->birdY) + BIRD_HEIGHT > (s32)((frontPipe.numTop + 1 + PIPE_BLOCK_GAP) * PIPE_BLOCK_HEIGHT))
     ))
  ) {
    return false;
  }
  return true;
}

bool renderGameFrame(GameState *state, u32 prevButtons, u32 currButtons) {

  INIT_AFF_SPRITE(*BIRD_SPRITE, BLUE_BIRD, BIRD_SPRITE_IDX);

  if (KEY_JUST_PRESSED(BUTTON_A, currButtons, prevButtons)) {
    state->birdVelocity = JUMP_VELOCITY;
  }

  if (!testCollisions(state)) {
    return false;
  }

  drawBird(state);

  drawPipes(state);

  drawScore(state->score);

  refreshSprites();
  refreshSounds();

  return true;
}

void hideAllSprites(void) {
  for (int i = 0; i < 128; i++) {
    sprite_hide(&obj_buffer[i]);
    if (i % 4 == 0) {
      aff_sprite_hide(&obj_buffer[i]);
    }
  }
}
