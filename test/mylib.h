#ifndef _MYLIB_H
#define _MYLIB_H
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

  typedef struct tagRGBQUAD {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
  } RGBQUAD;
void core(int*x,int*y,int*data,int WID,int LEN);//find the core of color block;

#endif
