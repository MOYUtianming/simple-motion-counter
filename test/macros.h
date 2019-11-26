#ifndef _MACROS_H
#define _MACROS_H

#define error 0
#define true 1
#define offsett 66
#define rangeb 1
#define ranger 2
#define rangeg 3
//Finite State Machine;
#define R 0
#define G 1
#define B 2
#define syn 3

#define abso(input)  abs(input)
#define round(mole,deno)    (int)(((float)mole/deno)+0.5)

typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef long           LONG;
typedef unsigned char  BYTE;

#endif