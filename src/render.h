#ifndef RENDER_H
#define RENDER_H

#include "consts.h"
#include "state.h"
#include "sprites/sprites.h"
#include "lookup/sin.h"
#include "lookup/cos.h"
#include "lookup/lookup.h"


#define INIT_SPRITE(LOC, NAME) \
  (LOC) = (OBJ_ATTR) { \
    .attr0 = (s16) (ATTR0_Y(0) | ATTR0_REG | ATTR0_BLEND | ATTR0_HIDE | ATTR0_8BPP | NAME##_SPRITE_SHAPE), \
    .attr1 = (s16) (ATTR1_X(0) | NAME##_SPRITE_SIZE), \
    .attr2 = (s16) (ATTR2_ID(NAME##_ID) | ATTR2_PALBANK(NAME##_PALETTE_ID)) \
  };

#define INIT_AFF_SPRITE(LOC, NAME, IDX) \
  (LOC) = (OBJ_ATTR) { \
    .attr0 = (s16) (ATTR0_Y(0) | ATTR0_AFF | ATTR0_BLEND | ATTR0_HIDE | ATTR0_8BPP | NAME##_SPRITE_SHAPE), \
    .attr1 = (s16) (ATTR1_X(0) | ATTR1_AFFIDX(IDX) | NAME##_SPRITE_SIZE), \
    .attr2 = (s16) (ATTR2_ID(NAME##_ID) | ATTR2_PALBANK(NAME##_PALETTE_ID)) \
  };

inline void affineSpriteRotate(OBJ_AFFINE *sprite, int angle) {
  sprite->pa = FIXED_COS(angle % 360);
  sprite->pb = FIXED_SIN(angle % 360);
  sprite->pc = -1 * FIXED_SIN(angle % 360);
  sprite->pd = FIXED_COS(angle % 360);
}

inline void refreshSprites(void) {
  oam_copy(oam_mem, obj_buffer, 128);
}

void hideAllSprites(void);

inline void intIntoSprite(OBJ_ATTR *sprite, int i) {
  switch (i) {
  case 0:
    INIT_SPRITE(*sprite, NUMBER_0);
    break;
  case 1:
    INIT_SPRITE(*sprite, NUMBER_1);
    break;
  case 2:
    INIT_SPRITE(*sprite, NUMBER_2);
    break;
  case 3:
    INIT_SPRITE(*sprite, NUMBER_3);
    break;
  case 4:
    INIT_SPRITE(*sprite, NUMBER_4);
    break;
  case 5:
    INIT_SPRITE(*sprite, NUMBER_5);
    break;
  case 6:
    INIT_SPRITE(*sprite, NUMBER_6);
    break;
  case 7:
    INIT_SPRITE(*sprite, NUMBER_7);
    break;
  case 8:
    INIT_SPRITE(*sprite, NUMBER_8);
    break;
  default:
    INIT_SPRITE(*sprite, NUMBER_9);
    break;
  }
}

void drawScore(int score);
bool renderGameFrame(GameState *state, u32 prevButtons, u32 currButtons);

#endif
