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

  typedef struct tagMASK {
    DWORD blue;
    DWORD green;
    DWORD red;
  } MASK;
  /*
  final file : elem;
  sizeof(ELEM)=5;
  */
  typedef struct tagELEM {
    BYTE state_w;//R=bit1~2,G=bit3~4,B=bit5~6;
  }ELEM;

#pragma pack(4)

ELEM*   InitELEMB(DWORD size , WORD HEI);// Before use ELEM Block formally, you should use this function to init the memory;
void    core(WORD*x,WORD*y,FILE*marker,WORD WID,WORD LEN,BYTE state);//find the core of color block;
BYTE    recg( BYTE state , BITMAPINFOHEADER*sizer , MASK *masks , FILE *base , ELEM *out );//recognize special color element;
#endif
