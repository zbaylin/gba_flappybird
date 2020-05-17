#ifndef CONSTS_H
#define CONSTS_H

#include "gba.h"
#include "fixed.h"

#define MAX_PIPES (6)

#define BIRD_X (8)
#define INITIAL_BIRD_Y (80)

#define BIRD_WIDTH (16)
#define BIRD_HEIGHT (16)

#define TENS_DIGIT_X (110)
#define TENS_DIGIT_Y (2)

#define ONES_DIGIT_X (120)
#define ONES_DIGIT_Y (2)

#define MAX_VERT_PIPES (7)
#define TOP_BOTTOM_DIFF (6)
#define PIPE_BLOCK_HEIGHT (16)
#define PIPE_BLOCK_WIDTH (24)
#define PIPE_BLOCK_GAP (3)
#define PIPE_GAP (PIPE_BLOCK_GAP * PIPE_BLOCK_HEIGHT)

#define INITIAL_BIRD_VELOCITY 0
#define GRAVITY (INT_TO_FIXED(1) >> 4)
#define JUMP_VELOCITY (-0x180) // 1.3

#define ONES_SPRITE &obj_buffer[0] // Affine sprite 0
#define TENS_SPRITE &obj_buffer[1]

#define PIPE_ZERO_0 &obj_buffer[2]
#define PIPE_ZERO_1 &obj_buffer[3]
#define PIPE_ZERO_2 &obj_buffer[4] // Affine sprite 1
#define PIPE_ZERO_3 &obj_buffer[5]
#define PIPE_ZERO_4 &obj_buffer[6]
#define PIPE_ZERO_5 &obj_buffer[7]
#define PIPE_ZERO_6 &obj_buffer[8] // Affine sprite 2
#define PIPE_ZERO_7 &obj_buffer[9]

#define PIPE_ONE_0 &obj_buffer[10]
#define PIPE_ONE_1 &obj_buffer[11]
#define PIPE_ONE_2 &obj_buffer[12] // Affine sprite 3
#define PIPE_ONE_3 &obj_buffer[13]
#define PIPE_ONE_4 &obj_buffer[14]
#define PIPE_ONE_5 &obj_buffer[15]
#define PIPE_ONE_6 &obj_buffer[16] // Affine sprite 4
#define PIPE_ONE_7 &obj_buffer[17]

#define PIPE_TWO_0 &obj_buffer[18]
#define PIPE_TWO_1 &obj_buffer[19]
#define PIPE_TWO_2 &obj_buffer[20] // Affine sprite 5
#define PIPE_TWO_3 &obj_buffer[21]
#define PIPE_TWO_4 &obj_buffer[22]
#define PIPE_TWO_5 &obj_buffer[23]
#define PIPE_TWO_6 &obj_buffer[24] // Affine sprite 6
#define PIPE_TWO_7 &obj_buffer[25]

#define PIPE_THREE_0 &obj_buffer[26]
#define PIPE_THREE_1 &obj_buffer[27]
#define PIPE_THREE_2 &obj_buffer[28] // Affine sprite 7
#define PIPE_THREE_3 &obj_buffer[29]
#define PIPE_THREE_4 &obj_buffer[30]
#define PIPE_THREE_5 &obj_buffer[31]
#define PIPE_THREE_6 &obj_buffer[32] // Affine sprite 8
#define PIPE_THREE_7 &obj_buffer[33]

#define PIPE_FOUR_0 &obj_buffer[34]
#define PIPE_FOUR_1 &obj_buffer[35]
#define PIPE_FOUR_2 &obj_buffer[36] // Affine sprite 9
#define PIPE_FOUR_3 &obj_buffer[37]
#define PIPE_FOUR_4 &obj_buffer[38]
#define PIPE_FOUR_5 &obj_buffer[39]
#define PIPE_FOUR_6 &obj_buffer[40] // Affine sprite 10
#define PIPE_FOUR_7 &obj_buffer[41]

#define PIPE_FIVE_0 &obj_buffer[42]
#define PIPE_FIVE_1 &obj_buffer[43]
#define PIPE_FIVE_2 &obj_buffer[44] // Affine sprite 11
#define PIPE_FIVE_3 &obj_buffer[45]
#define PIPE_FIVE_4 &obj_buffer[46]
#define PIPE_FIVE_5 &obj_buffer[47]
#define PIPE_FIVE_6 &obj_buffer[48] // Affine sprite 12
#define PIPE_FIVE_7 &obj_buffer[49]


extern OBJ_ATTR *pipeSprites[MAX_PIPES][MAX_VERT_PIPES];

#define BIRD_SPRITE_IDX (17)
#define BIRD_SPRITE (&obj_buffer[68]) // Affine sprite 4
#define BIRD_AFF_SPRITE (&obj_aff_buffer[BIRD_SPRITE_IDX])

#endif
