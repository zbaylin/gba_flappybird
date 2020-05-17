#ifndef GBA_H
#define GBA_H

#include "types.h"

// ---------------------------------------------------------------------------
//                       MODE3 MACROS
// ---------------------------------------------------------------------------
#define OFFSET(row, col, width) ((col)+(width)*(row))

#define REG_DISPCNT  *(volatile unsigned short *) 0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define WHITE COLOR(31,31,31)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK 0
#define GRAY COLOR(5, 5, 5)

// The size of the GBA Screen
#define WIDTH 240
#define HEIGHT 160

// This is initialized in gba.c
extern volatile unsigned short *videoBuffer;

// ---------------------------------------------------------------------------
//                       BUTTON INPUT
// ---------------------------------------------------------------------------
#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define BUTTONS *(volatile u32 *) 0x4000130
#define KEY_DOWN(key, buttons) (~(buttons) & (key))

#define KEY_JUST_PRESSED(key, buttons, oldbuttons) (KEY_DOWN(key, buttons) && !KEY_DOWN(key, oldbuttons))

// ---------------------------------------------------------------------------
//                       DMA
// ---------------------------------------------------------------------------
typedef struct {
  const volatile void *src;
  const volatile void *dst;
  u32                  cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

// ---------------------------------------------------------------------------
//                       VBLANK
// ---------------------------------------------------------------------------
#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

// Use this variable to count vBlanks. Initialized in gba.c and to be
// manipulated by waitForVBlank()
extern u32 vBlankCounter;

/**
 * Runs a blocking loop until the start of next VBlank.
 */
void waitForVBlank(void);

// ---------------------------------------------------------------------------
//                       MISC
// ---------------------------------------------------------------------------
#define UNUSED(param) ((void)((param)))

/**
 * Generates a pseudo-random number between min and max, inclusive.
 *
 * @param  min bottom end of range.
 * @param  max top end of range.
 * @return random number in the given range.
 */
int randint(int min, int max);

void seedRand(void);

// ---------------------------------------------------------------------------
//                       DRAWING
// ---------------------------------------------------------------------------
void setPixel(int row, int col, u16 color);
void drawRectDMA(int row, int col, int width, int height, volatile u16 color);
void drawFullScreenImageDMA(const u16 *image);
void drawImageDMA(int row, int col, int width, int height, const u16 *image);
void fillScreenDMA(volatile u16 color);
void drawChar(int row, int col, char ch, u16 color);
void drawString(int row, int col, char *str, u16 color);
void drawCenteredString(int row, int col, int width, int height, char *str, u16 color);
void drawSquareDiagonalMontage(const u16 *image, int width, u16 color);


/** Contains the pixels of each character from a 6x8 font */
// This is in the font.c file. You can replace the font if you want.
extern const unsigned char fontdata_6x8[12288];

// ---------------------------------------------------------------------------
//                       SPRITES
// ---------------------------------------------------------------------------
// Most, if not all of this, comes from the TONC section on sprites.

#define SPRITES_ENABLE (1 << 12)
#define ONE_DIM_MAPPING (1 << 6)

typedef struct {
  u32 data[8];
} TILE, TILE4;
typedef struct {
  u32 data[16];
} TILE8;
typedef TILE  CHARBLOCK[512];
typedef TILE8 CHARBLOCK8[256];

#define tile_mem  ((CHARBLOCK*) 0x06000000)
#define tile8_mem ((CHARBLOCK8*) 0x06000000)

#define MEM_PAL (0x05000000)
#define PAL_BG_SIZE (0x00200)
#define MEM_PAL_OBJ (MEM_PAL + PAL_BG_SIZE)
#define pal_obj_mem ((u16 *) MEM_PAL_OBJ)

typedef struct {
  u16 attr0; // Y coord (8 bits) + attr0 flags
  u16 attr1; // X coord (9 bits) + affine index (5 bits << 9) + attr1 flags
  u16 attr2; // ID (10 bits) + priority (2 bits << 10) + palette bank (4 bits << 0xC)
  s16 fill;
} __attribute__(( aligned(4) )) OBJ_ATTR;

#define ATTR0_Y(Y) (Y)
#define ATTR0_Y_MASK (0xFF)
#define ATTR0_Y_SHIFT (0)

#define ATTR0_MODE_MASK (0x3)
#define ATTR0_MODE_SHIFT (8)
#define ATTR0_REG (0 << 8)
#define ATTR0_AFF (1 << 8)
#define ATTR0_HIDE (2 << 8)
#define ATTR0_AFF_DBL (3 << 8)

#define ATTR0_BLEND (1 << 0xA)
#define ATTR0_WIN (2 << 0xA)

#define ATTR0_MOSAIC (1 << 0xC)

#define ATTR0_4BPP (0 << 0xD)
#define ATTR0_8BPP (1 << 0xD)

#define ATTR0_SHAPE_MASK
#define ATTR0_SQUARE (0 << 0xE)
#define ATTR0_WIDE (1 << 0xE)
#define ATTR0_TALL (2 << 0xE)

#define ATTR1_X(X) (X)
#define ATTR1_X_MASK (0x1FF)
#define ATTR1_X_SHIFT (0)

#define ATTR1_AFFIDX(IDX) ((IDX) << 9)
#define ATTR1_HFLIP (1 << 0xC)
#define ATTR1_VFLIP (1 << 0xD)

#define ATTR1_TINY (0 << 0xE)
#define ATTR1_NORMAL (1 << 0xE)
#define ATTR1_LARGE (2 << 0xE)
#define ATTR1_HUGE (3 << 0xE)

#define ATTR2_ID(ID) (ID)
#define ATTR2_PRI(PRI) ((PRI) << 0xA)
#define ATTR2_PALBANK(PAL) ((PAL) << 0xC)

#define BF_PREP(x, name)         ( ((x)<<name##_SHIFT)& name##_MASK  )
#define BF_GET(x, name)          ( ((x) & name##_MASK)>> name##_SHIFT )
#define BF_SET(y, x, name)       (y = ((y)&~name##_MASK) | BF_PREP(x,name) )

#define BF_PREP2(x, name)        ( (x) & name##_MASK )
#define BF_GET2(y, name)         ( (y) & name##_MASK )
#define BF_SET2(y, x, name)      (y = ((y)&~name##_MASK) | BF_PREP2(x, name) )

typedef struct {
  u16 fill0[3];
  s16 pa; // 8.8 fixed
  u16 fill1[3];
  s16 pb; // 8.8 fixed
  u16 fill2[3];
  s16 pc; // 8.8 fixed
  u16 fill3[3];
  s16 pd; // 8.8 fixed
} __attribute__(( aligned(4) )) OBJ_AFFINE;

#define MEM_OAM 0x07000000
#define oam_mem ((OBJ_ATTR *) MEM_OAM)

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE *obj_aff_buffer;

void oam_init(OBJ_ATTR *obj, u32 count);
void oam_copy(OBJ_ATTR *dst, const OBJ_ATTR *src, u32 count);

inline void sprite_set_pos(OBJ_ATTR *sprite, int x, int y) {
  BF_SET(sprite->attr1, x, ATTR1_X);
  BF_SET(sprite->attr0, y, ATTR0_Y);
}

inline void sprite_hide(OBJ_ATTR *sprite) {
  sprite->attr0 |= ATTR0_HIDE;
}

inline void sprite_show(OBJ_ATTR *sprite) {
  sprite->attr0 &= ~ATTR0_HIDE;
}

inline void aff_sprite_hide(OBJ_ATTR *sprite) {
  sprite->attr0 &= ~ATTR0_AFF;
  sprite->attr0 |= ATTR0_HIDE;
}

inline void aff_sprite_show(OBJ_ATTR *sprite) {
  sprite->attr0 |= ATTR0_AFF;
  sprite->attr0 &= ~ATTR0_HIDE;
}



// ---------------------------------------------------------------------------
//                       SOUND
// ---------------------------------------------------------------------------
// This forum post is SUPER helpful for sound
// https://www.gamedev.net/articles/programming/general-and-gameplay-programming/audio-programming-on-the-gameboy-advance-part-1-r1823/

#define REG_SOUND1CNT_L	(*(vu16*)0x04000060)
#define REG_SOUND1CNT_H	(*(vu16*)0x04000062)
#define REG_SOUND1CNT_X	(*(vu16*)0x04000064)
#define REG_SOUND2CNT_L	(*(vu16*)0x04000068)
#define REG_SOUND2CNT_H	(*(vu16*)0x0400006C)
#define REG_SOUND3CNT_L	(*(vu16*)0x04000070)
#define REG_SOUND3CNT_H	(*(vu16*)0x04000072)
#define REG_SOUND3CNT_X	(*(vu16*)0x04000074)
#define REG_SOUND4CNT_L	(*(vu16*)0x04000078)
#define REG_SOUND4CNT_H	(*(vu16*)0x0400007C)

// Master registers
#define REG_SOUNDCNT_L	(*(vu16*)0x04000080)
#define REG_SOUNDCNT_H	(*(vu16*)0x04000082)
#define REG_SOUNDCNT_X	(*(vu16*)0x04000084)
#define REG_SOUNDBIAS	(*(vu16*)0x04000088)

#define PTR_WAVE_RAM	((vu8*)0x0400008a)

#define SND_ENABLED 0x00000080
#define SND_OUTPUT_RATIO_25 0x0000
#define SND_OUTPUT_RATIO_50 0x0001
#define SND_OUTPUT_RATIO_100 0x0002
#define DSA_OUTPUT_RATIO_50 0x0000
#define DSA_OUTPUT_RATIO_100 0x0004
#define DSA_OUTPUT_TO_RIGHT 0x0100
#define DSA_OUTPUT_TO_LEFT 0x0200
#define DSA_OUTPUT_TO_BOTH 0x0300
#define DSA_TIMER0 0x0000
#define DSA_TIMER1 0x0400
#define DSA_FIFO_RESET 0x0800
#define DSB_OUTPUT_RATIO_50 0x0000
#define DSB_OUTPUT_RATIO_100 0x0008
#define DSB_OUTPUT_TO_RIGHT 0x1000
#define DSB_OUTPUT_TO_LEFT 0x2000
#define DSB_OUTPUT_TO_BOTH 0x3000
#define DSB_TIMER0 0x0000
#define DSB_TIMER1 0x4000
#define DSB_FIFO_RESET 0x8000

// DMA flags
#define WORD_DMA 0x04000000
#define HALF_WORD_DMA 0x00000000
#define ENABLE_DMA 0x80000000
#define START_ON_FIFO_EMPTY 0x30000000
#define DEST_REG_SAME 0x00400000

// Timer 0 register definitions
#define REG_TM0D *(u16*)0x4000100
#define REG_TM0CNT *(u16*)0x4000102

// Timer flags
#define TIMER_ENABLED 0x0080

// FIFO address defines
#define REG_FIFO_A 0x040000A0
#define REG_FIFO_B 0x040000A4

// DMA channel 1 register definitions
#define REG_DMA1SAD *(u32*)0x40000BC // source address
#define REG_DMA1DAD *(u32*)0x40000C0 // destination address
#define REG_DMA1CNT *(u32*)0x40000C4 // control register

#define TIMER_INTERVAL (0xFA0E)
#define SAMPLES_PER_VBLANK (0xB8)

#endif
