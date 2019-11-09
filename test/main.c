#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"mylib.h"

#define HEI 800
#define WID 480
#define USINT16 unsigned short int
#define DWORD   unsigned long  int
#define UCAHR   unsigned char

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
  BMPFH *fh;
  fh=(BMPFH*)malloc(sizeof(BMPFH));
  BMPIH *ih;
  ih=(BMPIH*)malloc(sizeof(BMPIH));
  FILE*map=NULL;
  map=fopen("PHOTO/PIC00001.bmp","r");
  USINT16*num=NULL;
  num=(USINT16*)malloc(sizeof(USINT16));
  UCAHR   *p0=NULL;
  USINT16 *p1=NULL;
  DWORD   *p2=NULL;
  /*End of Init code*/
  /*Loop code*/
  fread(fh,sizeof(char),sizeof(BMPFH),map);
  fseek(map,14,SEEK_SET);
  fread(ih,sizeof(char),sizeof(BMPIH),map);
  p0=(UCAHR*)fh;
  for(int i=0;i<2;i++)
  {
    printf("%c\n",*(p0++));
  }

  p2=(DWORD*)p0;
  for(int i=0;i<3;i++)
  {
    printf("%d\n",*(p2++));
  }
  printf("end of fh\n\n");

  p2=(DWORD*)ih;
  for(int i=0;i<3;i++)
  {
    printf("%d\n",*(p2++));
  }
  p1=(USINT16*)p2;
  for(int i=0;i<2;i++)
  {
    printf("%d\n",*(p1++));
  }
  p2=(DWORD*)p1;
  for(int i=0;i<6;i++)
  {
    printf("%d\n",*(p2++));
  }
  printf("end of ih\n\n");

  fseek(map,2,SEEK_END);
  fread(num,2,1,map);
  printf("first num is %d\n",*num);
  printf("%d\n",sizeof(long int));
  /*End of Loop code*/
  getchar();
  return 0;
}

