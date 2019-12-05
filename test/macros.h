#ifndef _MACROS_H
#define _MACROS_H

#define error 0
#define true 1
#define offsett 54

#define rangeb 30
#define ranger 30
#define rangeg 25

#define standardrb 75
#define standardrg 61
#define standardrr 166

#define standardgb 123
#define standardgg 195
#define standardgr 163

#define standardbb 146
#define standardbg 64
#define standardbr 25

#define WIDD 1280
#define HEII 720

//Finite State Machine;
#define R 0
#define G 1
#define B 2
#define syn 3

#define BMP 0
#define MARKF 1
#define PHOTO 2
#define CLR 3

#define abso(input)  abs(input)
#define round(mole,deno)    (int)(((float)mole/deno)+0.5)

typedef unsigned int   WORD;
typedef unsigned long  DWORD;
typedef long           LONG;
typedef unsigned char  BYTE;

#endif