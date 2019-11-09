#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"mylib.h"

#define HEI 800
#define WID 480
#define USINT16 unsigned short int
#define DWORD   unsigned long  int

typedef struct tag_BITMAPFILEHEADER
{
  USINT16 bftype;     //type of file;
  DWORD   bfsize;     //size of file;
  DWORD   bfreserved; //reserved space;
  DWORD   bfofbits;   //offset number(described by bytes)
}BMPFH;

typedef struct tag_BITMAPINFOHEADER
{
  DWORD   typsize;//number of bytes which are used to describe this type;
  DWORD   biwid;
  DWORD   bihei;//if this number is positive,it means this map's sequence is negative;
  USINT16 biplanes;//always be 1;
  USINT16 bitcount;//number of bytes which is used to describe a pixel;
  DWORD   bicompression;//0 means without any compression.
  DWORD   mapsize;//this map's size;
  DWORD   XPP;
  DWORD   YPP;
  DWORD   clrused;//0 means use all color sheet;
  DWORD   clrimptt;//useful color classes;
}BMPIH;

int main()
{
  /*Init code*/
  int tt[HEI*WID]={0};
  BMPFH *fh;
  fh=(BMPFH*)malloc(sizeof(BMPFH));
  BMPIH *ih;
  ih=(BMPIH*)malloc(sizeof(BMPIH));
  FILE*map=NULL;
  map=fopen("PHOTO/PIC00001.bmp","r");
  /*End of Init code*/


  getchar();
  return 0;
}

