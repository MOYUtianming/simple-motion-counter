#ifndef _MYLIB_H
#define _MYLIB_H
#include<stdio.h>
#include<stdlib.h>
#include"macros.h"

#define maskR 0x03
#define maskG 0x0C
#define maskB 0x30

#pragma pack(1)
  typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
  } BITMAPINFOHEADER;

  typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
  } BITMAPFILEHEADER;

  typedef struct tagPIXEL {
    BYTE blue;
    BYTE green;
    BYTE red;
  } PIXEL;
  /*
  final file : elem;
  sizeof(ELEM)=3;
  */
  typedef struct tagELEM {
    BYTE state_r;
    BYTE state_g;
    BYTE state_b;
  }ELEM;

#pragma pack(4)
void    count(BITMAPINFOHEADER*ih,int*iLineByteCnt,int*skip);
ELEM*   InitELEMB(DWORD size , WORD HEI);// Before use ELEM Block formally, you should use this function to init the memory;
void    core(WORD*x,WORD*y,FILE*marker,WORD WID,WORD LEN,BYTE state);//find the core of color block;
BYTE    recg( BYTE state , BITMAPINFOHEADER*sizer , FILE *base , ELEM *out );//recognize special color element;
void    new_pathname(BYTE *pname,BYTE mode);
//test functions.
void    mark2pic(BYTE state, BITMAPINFOHEADER*sizer,BITMAPFILEHEADER*head,const char*pnamem,const char*pnameb);
#endif
