#include "sfx_point.h"
#include "sfx_hit.h"
#include "theme.h"
#include "../gba.h"
#include <stdio.h>

u32 endAtVBlank = 0;

void playPointSFX(void) {
  endAtVBlank = vBlankCounter + (sfx_point_len / 240);

  REG_TM0CNT = 0;
  DMA[1].cnt = 0;

  REG_SOUNDCNT_H |= DSA_FIFO_RESET;

  REG_TM0D = TIMER_INTERVAL;
  REG_TM0CNT = TIMER_ENABLED;

  DMA[1].src = (void *)sfx_point;
	DMA[1].dst = (void *)REG_FIFO_A;
  DMA[1].cnt = ENABLE_DMA | START_ON_FIFO_EMPTY | WORD_DMA | DMA_REPEAT;
}

void playHitSFX(void) {
  endAtVBlank = vBlankCounter + (sfx_hit_len / 60);

  REG_TM0CNT = 0;
  DMA[1].cnt = 0;

  REG_SOUNDCNT_H |= DSA_FIFO_RESET;

  REG_TM0D = TIMER_INTERVAL;
  REG_TM0CNT = TIMER_ENABLED;

  DMA[1].src = (void *)sfx_hit;
	DMA[1].dst = (void *)REG_FIFO_A;
  DMA[1].cnt = ENABLE_DMA | START_ON_FIFO_EMPTY | WORD_DMA | DMA_REPEAT;
}

void playThemeSong(void) {
  REG_TM0CNT = 0;
  DMA[1].cnt = 0;

  REG_SOUNDCNT_H |= DSA_FIFO_RESET;

  REG_TM0D = TIMER_INTERVAL;
  REG_TM0CNT = TIMER_ENABLED;

  DMA[1].src = (void *)theme;
	DMA[1].dst = (void *)REG_FIFO_A;
  DMA[1].cnt = ENABLE_DMA | START_ON_FIFO_EMPTY | WORD_DMA | DMA_REPEAT;
}

void refreshSounds(void) {
  if (vBlankCounter > endAtVBlank) {
    DMA[1].cnt = 0;
  }
}
