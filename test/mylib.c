#include"mylib.h"
#include<stdio.h>
#include<stdlib.h>

void InitELEM(ELEM *input , DWORD size , WORD WID , WORD HEI)
{int cont1=0;
ELEM *in=input;
  for(;cont1<size;cont1++)
  {
      in->x = ( cont1 % WID ) + 1;
      in->y = ( cont1 / HEI ) + 1;
      in->value_b=0;
      in->value_g=0;
      in->value_r=0;
      in++;
  }
}
/*
function : recognize the color and mark the number of each ;
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
supplement : Since the size have been got I didn't take care of 4 byte alignment problem;
*/
int recg( BYTE state , DWORD size , MASK *masks , FILE *base , FILE *out )
{
  WORD  comb1 = 0,comb2 = 0,comb3 = 0;

  DWORD cont1 = 0;
  BYTE  cont2 = 0;
  
  ELEM  *outb = (ELEM*)malloc(sizeof(ELEM)*round(size,2) + sizeof(BYTE));
  ELEM  *outb_f = outb;
  BYTE  *end = NULL;
  WORD  *mid  = (WORD*)malloc(size);
  MARK  *marker = (MARK*)malloc(sizeof(MARK));
  
    marker->dsize=sizeof(MARK) + sizeof(ELEM)*round(size,2) + sizeof(BYTE);
    marker->hei = 800;
    marker->wid = 480;
    marker->mod = 0;

    if(state < 3)
    {
      fseek(base,offset,SEEK_SET);
      fread(mid , 1 , size , base);
      rewind(base);
    }
    else
    {
      return error;
    }
      for(cont1 = 0 ; cont1 < size ; cont1++)
      {
        comb1 = ((*mid++) & masks->red  )>>11;
        comb2 = ((*mid++) & masks->green)>>5 ;
        comb3 = ((*mid++) & masks->blue )    ;
        

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

          if(cont2 == 3)
          {
            outb->value_r++;
            outb++;
            cont2=0;
          }
          else
          {
            outb++;
            cont2=0;
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

          if(cont2 == 3)
          {
            outb->value_g++;
            outb++;
            cont2=0;
          }
          else
          {
            outb++;
            cont2=0;
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

          if(cont2 == 3)
          {
            outb->value_b++;
            outb++;
            cont2=0;
          }
          else
          {
            outb++;
            cont2=0;
          }
        }
      }
    end=(BYTE*)outb;
    *end=EOF;

    fwrite(outb_f,1,sizeof(ELEM)*round(size,2) + sizeof(BYTE),out);
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

  *x=round(zx,m);
  *y=round(zy,m);
}