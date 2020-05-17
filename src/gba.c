#include "gba.h"

volatile unsigned short *videoBuffer = (volatile unsigned short *)0x6000000;
u32 vBlankCounter = 0;

void waitForVBlank(void) {
  while (SCANLINECOUNTER > 160);
  while (SCANLINECOUNTER < 160);
  vBlankCounter++;
}

static int __qran_seed = 42;
static int qran(void) {
  __qran_seed = 1664525 * __qran_seed + 1013904223;
  return (__qran_seed >> 16) & 0x7FFF;
}

void seedRand(void) {
  __qran_seed = vBlankCounter;
}

int randint(int min, int max) {
  return (qran() * (max - min) >> 15) + min;
}

void setPixel(int row, int col, u16 color) {
  videoBuffer[OFFSET(row, col, WIDTH)] = color;
}

void drawRectDMA(int row, int col, int width, int height, volatile u16 color) {
  DMA[3].cnt = 0; // Stop DMA transfer
  DMA[3].src = (void *) &color; // Set the source to be the color
  for (int i = 0; i < height; i++) {
    DMA[3].dst = &videoBuffer[OFFSET(row + i, col, WIDTH)]; // The destination is the row + i
    DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON; // The mode is SOURCE_FIXED
  }
}

void drawFullScreenImageDMA(const u16 *image) {
  DMA[3].cnt = 0; // Stop DMA transfer
  DMA[3].src = image;
  DMA[3].dst = videoBuffer;
  DMA[3].cnt = (HEIGHT * WIDTH) | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT | DMA_ON;
}

void drawImageDMA(int row, int col, int width, int height, const u16 *image) {
  DMA[3].cnt = 0;
  for (int i = 0; i < height; i++) {
    DMA[3].src = &image[i * width];
    DMA[3].dst = &videoBuffer[OFFSET(row + i, col, WIDTH)];
    DMA[3].cnt = width | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT | DMA_ON;
  }
}

void drawSquareDiagonalMontage(const u16 *image, int width, u16 color) {
  DMA[3].cnt = 0;

  for (int row = 0; row < width; row++) {
    DMA[3].src = &image[row * width];
    DMA[3].dst = &videoBuffer[OFFSET(row, 0, WIDTH)];
    DMA[3].cnt = row | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;

    DMA[3].src = (void *)&color;
    DMA[3].dst = &videoBuffer[OFFSET(row, row, WIDTH)];
    DMA[3].cnt = width-row|DMA_SOURCE_FIXED|DMA_ON;
  }
}



void fillScreenDMA(volatile u16 color) {
  DMA[3].cnt = 0; // Stop DMA transfer
  DMA[3].src = (void *) &color;
  DMA[3].dst = videoBuffer;
  DMA[3].cnt = (HEIGHT * WIDTH) | DMA_SOURCE_FIXED | DMA_ON;
}

void drawChar(int row, int col, char ch, u16 color) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      if (fontdata_6x8[OFFSET(j, i, 6) + ch * 48]) {
        setPixel(row + j, col + i, color);
      }
    }
  }
}

void drawString(int row, int col, char *str, u16 color) {
  while (*str) {
    drawChar(row, col, *str++, color);
    col += 6;
  }
}

void drawCenteredString(int row, int col, int width, int height, char *str,
                        u16 color) {
  u32 len = 0;
  char *strCpy = str;
  while (*strCpy) {
    len++;
    strCpy++;
  }

  u32 strWidth = 6 * len;
  u32 strHeight = 8;

  int new_row = row + ((height - strHeight) >> 1);
  int new_col = col + ((width - strWidth) >> 1);
  drawString(new_row, new_col, str, color);
}

// Sprite code
OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *) obj_buffer;

void oam_init(OBJ_ATTR *obj, u32 count) {
  u32 nn= count;
  u32 *dst= (u32*)obj;

  // Hide each object
  while(nn--) {
    *dst++= ATTR0_HIDE;
    *dst++= 0;
  }
  // init oam
  oam_copy(oam_mem, obj, count);
}

void oam_copy(OBJ_ATTR *dst, const OBJ_ATTR *src, u32 count) {

// NOTE: while struct-copying is the Right Thing to do here,
//   there's a strange bug in DKP that sometimes makes it not work
//   If you see problems, just use the word-copy version.
#if 1
  while(count--)
    *dst++ = *src++;
#else
  u32 *dstw= (u32*)dst, *srcw= (u32*)src;
  while(count--) {
    *dstw++ = *srcw++;
    *dstw++ = *srcw++;
  }
#endif
}
