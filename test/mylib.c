#include"mylib.h"
#include<stdio.h>
#include<stdlib.h>

/*
function : recognize the color;
state = 
{
  R=0;
  G=1;
  B=2;
}
size = size of file data;(expressed by number of bytes)
masks = the mask of the file;
base = source data;
out = output file;
*/
int recg( BYTE state , DWORD size , MASK *masks , FILE *base , FILE *out )
{
  fseek(base,offset,SEEK_SET);
  WORD  comb1 = 0,comb2 = 0,comb3 = 0;

  DWORD cont1 = 0;
  BYTE  cont2 = 0;
  
  BYTE  *outb = (BYTE*)malloc(size);
  WORD  *mid  = (WORD*)malloc(size);
    if(state < 3)
    {
      fread(mid , 1 , size , base);
      comb1 = ((*mid++) & masks->red  )>>11;
      comb2 = ((*mid++) & masks->green)>>5 ;
      comb3 = ((*mid++) & masks->blue )    ;
    }
    else
    {
      return error;
    }
      for(cont1 = 0 ; cont1 < size ; cont1++)
      {
        if(state == R)
        {
          if(abso(comb1-18)<2)
          {
            cont2++;
          }
          if(abso(comb2-25)<2)
          {
            cont2++;
          }
          if(abso(comb3-15)<2)
          {
            cont2++;
          }
        }
        else if (state == G)
        {
          if(abso(comb1-15)<2)
          {
            cont2++;
          }
          if(abso(comb2-39)<2)
          {
            cont2++;
          }
          if(abso(comb3-15)<2)
          {
            cont2++;
          }
        }
        else if (state ==B)
        {
          if(abso(comb1-12)<2)
          {
            cont2++;
          }
          if(abso(comb2-26)<2)
          {
            cont2++;
          }
          if(abso(comb3-17)<2)
          {
            cont2++;
          }
        }
        
        if(cont2 == 3)
        {
          ++(*(outb++));
          cont2=0;
        }
      }
  rewind(base);
  return true;
}

/*
function : find the core of color block;
x = return parallel value;
y = return vertical value;
data = input data;
WID = input width;
LEN = input length;
*/
void core(int*x,int*y,BYTE*data,int WID,int LEN)
{
  int i=0,j=0;
  BYTE *dat=data;
  int m=0;
    for(j=0;j<LEN;j++)
    {
      for(i=0;i<WID;i++)
      {
        m+=*(dat++);
      }
    }
    dat=data;//SUPPLEMENT:you can't use data calculate directly;
  int zx=0;
    for(j=0;j<LEN;j++)
    {
      for(i=0;i<WID;i++)
      {
        zx+=(i+1)*(*(dat++));
      }
    }
    dat=data;

  int zy=0;
   for(j=0;j<LEN;j++)
    {
      for(i=0;i<WID;i++)
      {
        zy+=(j+1)*(*(dat++));
      }
    }

  *x=(int)(((float)zx/m)+0.5);
  *y=(int)(((float)zy/m)+0.5);
}

/*
function : make the track of core;
input = a core file;
marko = the used mark file;
*/
int mark(FILE *input,FILE *marko,MARK *mrhead)
{
  MARK *markhead;
  
}