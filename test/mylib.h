#ifndef _MYLIB_H
#define _MYLIB_H

#define error 0
#define true 1
#define offset 66
//Finite State Machine;
#define R 0
#define G 1
#define B 2
#define syn 3

#define abso(input)  (input>=0) ? input : (-input)
#pragma pack(1)
  typedef unsigned short WORD;
  typedef unsigned long  DWORD;
  typedef long           LONG;
  typedef unsigned char  BYTE;
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
  } BITMAPINFOHEADER,*LPBITMAPINFOHEADER,*PBITMAPINFOHEADER;

  typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
  } BITMAPFILEHEADER,*LPBITMAPFILEHEADER,*PBITMAPFILEHEADER;

  typedef struct tagMASK {
    DWORD blue;
    DWORD green;
    DWORD red;
  } MASK;
/*
dsize = data size;
wid = the width of data;
hei = the height of data;
mod = 
{
  0 = negative sequence;
  1 = positive sequence;
}
offset_h = the offset bytes from head to data;
offset_* = the offset bytes from head to the newest * core;
cont_* = the number of * core;
*/
  typedef struct tagMARK {
    DWORD dsize;
    WORD  wid;
    WORD  hei;
    BYTE  mod;
    WORD  offset_h;
    WORD  offset_r;
    WORD  offset_g;
    WORD  offset_b;
    WORD  cont_r;
    WORD  cont_g;
    WORD  cont_b;
  }MARK;

void core(int*x,int*y,BYTE*data,int WID,int LEN);//find the core of color block;
int recg( BYTE state , DWORD size , MASK *masks , FILE *base , FILE *out );//recognize special color element;
#endif
