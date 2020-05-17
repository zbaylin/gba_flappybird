#ifndef EFFECTS_H
#define EFFECTS_H

void playPointSFX(void);
void playHitSFX(void);
void refreshSounds(void);
void playThemeSong(void);

inline void stopSounds(void) {
  DMA[1].cnt = 0;
}

#endif
