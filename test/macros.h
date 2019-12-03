#ifndef _MACROS_H
#define _MACROS_H

#define error 0
#define true 1
#define offsett 54
#define rangeb 1
#define ranger 5
#define rangeg 1
#define standard1b 34
#define standard1g 34
#define standard1r 139

//Finite State Machine;
#define R 0
#define G 1
#define B 2
#define syn 3

#define BMP 0
#define MARKF 1
#define CLR 2

#define abso(input)  abs(input)
#define round(mole,deno)    (int)(((float)mole/deno)+0.5)

typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef long           LONG;
typedef unsigned char  BYTE;

#endif