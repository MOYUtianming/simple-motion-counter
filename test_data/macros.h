#ifndef _MACROS_H
#define _MACROS_H
//general macros;
#define error 0
#define true 1
//some key number for read BMP888;
#define offsett 54
#define WIDD 1280
#define HEII 720
//range for divide original picture;
#define rangeb 30
#define ranger 30
#define rangeg 25
//standard for divide original picture;
//R;
#define standardrb 75
#define standardrg 61
#define standardrr 166
//G;
#define standardgb 123
#define standardgg 195
#define standardgr 163
//B;
#define standardbb 146
#define standardbg 64
#define standardbr 25

// mylib.c file mainly Finite State Machine;
#define R 0
#define G 1
#define B 2

//new_pathname function's FSM;
#define BMP 0
#define MARKF 1
#define PHOTO 2
#define CLR 3

//compress function's FSM;
#define EQU 0//equal;
#define LSML 1 //little smaller;
#define LLAG 2//little larger;
#define VSML 3//very smaller;
#define VLAG 4//very larger;

#define round(mole,deno)    (int)(((float)mole/deno)+0.5)

typedef unsigned int   WORD;
typedef unsigned long  DWORD;
typedef long           LONG;
typedef unsigned char  BYTE;

#endif