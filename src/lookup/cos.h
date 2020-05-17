/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=lut --func=cos,int.8,0,360,1,1 cos 
 * Time-stamp: Tuesday 03/24/2020, 17:26:15
 * 
 * Look Up Table Information
 * -------------------------
 * Function: cos Type: int.8 Range: [0, 360] Step: 1
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef COS_H
#define COS_H

extern const int cos_table[361];
#define COS_TABLE_LENGTH 361
#define COS_TABLE_FIXED_LENGTH 8
#define COS_TABLE_BEGIN ((0 << 8) | 0x00)
#define COS_TABLE_END ((360 << 8) | 0x00)
#define COS_TABLE_STEP ((1 << 8) | 0x00)

#endif

