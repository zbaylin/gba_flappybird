/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=sprites --bpp=8 --for_bitmap --transparent=ffffff sprites ./blue_bird.png ./number_0.png ./number_1.png ./number_2.png ./number_3.png ./number_4.png ./number_5.png ./number_6.png ./number_7.png ./number_8.png ./number_9.png ./pipebody.png ./pipehead.png 
 * Time-stamp: Friday 04/10/2020, 15:00:28
 * 
 * Image Information
 * -----------------
 * ./blue_bird.png 16@16
 * ./number_0.png 16@16
 * ./number_1.png 16@16
 * ./number_2.png 16@16
 * ./number_3.png 16@16
 * ./number_4.png 16@16
 * ./number_5.png 16@16
 * ./number_6.png 16@16
 * ./number_7.png 16@16
 * ./number_8.png 16@16
 * ./number_9.png 16@16
 * ./pipebody.png 32@32
 * ./pipehead.png 32@32
 * Transparent color: (255, 255, 255)
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef SPRITES_H
#define SPRITES_H

#define SPRITES_PALETTE_TYPE (1 << 13)
#define SPRITES_DIMENSION_TYPE (1 << 6)

extern const unsigned short sprites_palette[21];
#define SPRITES_PALETTE_SIZE 42
#define SPRITES_PALETTE_LENGTH 21

extern const unsigned short sprites[2432];
#define SPRITES_SIZE 4864
#define SPRITES_LENGTH 2432

#define BLUE_BIRD_PALETTE_ID (0 << 12)
#define BLUE_BIRD_SPRITE_SHAPE (0 << 14)
#define BLUE_BIRD_SPRITE_SIZE (1 << 14)
#define BLUE_BIRD_ID 512

#define NUMBER_0_PALETTE_ID (0 << 12)
#define NUMBER_0_SPRITE_SHAPE (0 << 14)
#define NUMBER_0_SPRITE_SIZE (1 << 14)
#define NUMBER_0_ID 520

#define NUMBER_1_PALETTE_ID (0 << 12)
#define NUMBER_1_SPRITE_SHAPE (0 << 14)
#define NUMBER_1_SPRITE_SIZE (1 << 14)
#define NUMBER_1_ID 528

#define NUMBER_2_PALETTE_ID (0 << 12)
#define NUMBER_2_SPRITE_SHAPE (0 << 14)
#define NUMBER_2_SPRITE_SIZE (1 << 14)
#define NUMBER_2_ID 536

#define NUMBER_3_PALETTE_ID (0 << 12)
#define NUMBER_3_SPRITE_SHAPE (0 << 14)
#define NUMBER_3_SPRITE_SIZE (1 << 14)
#define NUMBER_3_ID 544

#define NUMBER_4_PALETTE_ID (0 << 12)
#define NUMBER_4_SPRITE_SHAPE (0 << 14)
#define NUMBER_4_SPRITE_SIZE (1 << 14)
#define NUMBER_4_ID 552

#define NUMBER_5_PALETTE_ID (0 << 12)
#define NUMBER_5_SPRITE_SHAPE (0 << 14)
#define NUMBER_5_SPRITE_SIZE (1 << 14)
#define NUMBER_5_ID 560

#define NUMBER_6_PALETTE_ID (0 << 12)
#define NUMBER_6_SPRITE_SHAPE (0 << 14)
#define NUMBER_6_SPRITE_SIZE (1 << 14)
#define NUMBER_6_ID 568

#define NUMBER_7_PALETTE_ID (0 << 12)
#define NUMBER_7_SPRITE_SHAPE (0 << 14)
#define NUMBER_7_SPRITE_SIZE (1 << 14)
#define NUMBER_7_ID 576

#define NUMBER_8_PALETTE_ID (0 << 12)
#define NUMBER_8_SPRITE_SHAPE (0 << 14)
#define NUMBER_8_SPRITE_SIZE (1 << 14)
#define NUMBER_8_ID 584

#define NUMBER_9_PALETTE_ID (0 << 12)
#define NUMBER_9_SPRITE_SHAPE (0 << 14)
#define NUMBER_9_SPRITE_SIZE (1 << 14)
#define NUMBER_9_ID 592

#define PIPEBODY_PALETTE_ID (0 << 12)
#define PIPEBODY_SPRITE_SHAPE (0 << 14)
#define PIPEBODY_SPRITE_SIZE (2 << 14)
#define PIPEBODY_ID 600

#define PIPEHEAD_PALETTE_ID (0 << 12)
#define PIPEHEAD_SPRITE_SHAPE (0 << 14)
#define PIPEHEAD_SPRITE_SIZE (2 << 14)
#define PIPEHEAD_ID 632

#endif

