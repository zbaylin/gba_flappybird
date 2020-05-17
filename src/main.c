#include "gba.h"

#include "state.h"
#include "render.h"

#include "sprites/sprites.h"
#include "sounds/effects.h"
#include "images/titlescreen.h"
#include "images/game_bg.h"
#include "images/ridicule.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(void) {
  // Move the sprites and palettes into the OAM
  memcpy(&tile_mem[5][0], sprites, SPRITES_SIZE);
  memcpy(pal_obj_mem, sprites_palette, SPRITES_PALETTE_SIZE);

  oam_init(obj_buffer, 128);

  // Set display properties
  REG_DISPCNT = MODE3 | BG2_ENABLE | SPRITES_ENABLE | SPRITES_DIMENSION_TYPE;

  // Enable the sound register
  REG_SOUNDCNT_X = SND_ENABLED;

  REG_SOUND1CNT_L = 0;

  REG_SOUNDCNT_H = SND_OUTPUT_RATIO_100 | // 100% sound output
                   DSA_OUTPUT_RATIO_100 | // 100% direct sound A output
                   DSA_OUTPUT_TO_BOTH |   // output Direct Sound A to both right and left speakers
                   DSA_TIMER0 |           // use timer 0 to determine the playback frequency of Direct Sound A
                   DSA_FIFO_RESET;

  // Initialize the global state
  GlobalState globalState = START;

  // Initialize a blank gamestate
  GameState gameState;

  // Store both the previous and current buttons
  u32 prevButtons = BUTTONS;
  u32 currButtons = BUTTONS;



  while (1) {
    currButtons = BUTTONS;

    if (KEY_JUST_PRESSED(BUTTON_SELECT, currButtons, prevButtons)) {
      hideAllSprites();
      refreshSprites();
      globalState = START;
    }

    switch (globalState) {
    case START:
      waitForVBlank();

      playThemeSong();

      globalState = TITLE;
      break;

    case TITLE:
      waitForVBlank();

      drawSquareDiagonalMontage((u16 *) titlescreen, 30, RED);

      if (KEY_JUST_PRESSED(BUTTON_START, currButtons, prevButtons)) {
        globalState = SETUP_GAME;
      };

      break;

    case SETUP_GAME:
      stopSounds();
      drawFullScreenImageDMA((u16 *) game_bg);
      seedRand();
      initGameState(&gameState);
      globalState = ACTIVE_GAME;
      break;

    case ACTIVE_GAME:
      waitForVBlank();

      if (!renderGameFrame(&gameState, prevButtons, currButtons)) {
        globalState = SETUP_GAME_OVER;
      }
      break;

    case SETUP_GAME_OVER:
      stopSounds();
      playHitSFX();
      hideAllSprites();
      refreshSprites();

      fillScreenDMA(BLACK);


      char buffer[32];
      sprintf(buffer, "Score: %d", gameState.score);
      drawCenteredString(40, WIDTH / 2 - 25, 50, 20, buffer, GREEN);

      drawCenteredString(80, WIDTH / 2 - 50, 100, 20, "Press SELECT to play again!", WHITE);
      drawImageDMA(110, (WIDTH - RIDICULE_WIDTH) / 2, RIDICULE_WIDTH, RIDICULE_HEIGHT, ridicule);
      globalState = GAME_OVER;
      break;

    default:
      waitForVBlank();
      drawRectDMA(((vBlankCounter - 1) % 100) / 4, 0, WIDTH, 20, BLACK);
      drawCenteredString((vBlankCounter % 100) / 4, (WIDTH / 2 - 25) + (FIXED_SIN(vBlankCounter) / 4), 50, 20, "GAME OVER!", WHITE);
      refreshSounds();
      break;
    }

    prevButtons = currButtons;
  }

}
