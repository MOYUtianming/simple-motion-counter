#include"mylib.h"

MARK* InitMARKB(DWORD size,BITMAPINFOHEADER*ihh)
{
    MARK  *marker = (MARK*)malloc(sizeof(MARK));
    marker->offset_h=sizeof(MARK);
    return marker;
}

ELEM* InitELEMB(DWORD size , WORD HEI)//Init elem block;
{
  int cont1=0;
  ELEM *elem=(ELEM*)malloc(sizeof(ELEM)*size);
  ELEM *stack=elem;
  for(;cont1<size;cont1++)
  {
      elem->x = ( cont1 % HEI ) + 1;
      elem->y = ( cont1 / HEI ) + 1;
      elem->state_w=0;
      elem++;
  }
  return stack;
}

/*
function : recognize the color and mark the number of each ;
state = 
{
  R=0;
  G=1;
  B=2;
} ;
size = size of file data;(expressed by number of bytes)
masks = the mask of the file;
base = source data;
out = output file;
supplement : Since the size have been got I didn't take care of 4 byte alignment problem;
*/
BYTE recg( BYTE state , BITMAPINFOHEADER*sizer , MASK *masks , FILE *base , ELEM *out )
{
  WORD  comb1 = 0,comb2 = 0,comb3 = 0;

  DWORD cont1 = 0;
  BYTE  cont2 = 0;
  DWORD size=sizer->biWidth*sizer->biHeight;
  ELEM  *outb = out;
    
  ELEM  *outb_f = outb;
  WORD  *mid = (WORD*)malloc(sizeof(WORD));
  int tem=0;
    if(state < 3)
    {
      fseek(base,offsett,SEEK_SET);
    }
    else
    {
      return error;
    }
      for(cont1 = 0 ; cont1 < size ; cont1++)
      {
        fread(mid , 1 , 2 , base);
        comb3 = ((*mid) & masks->red  );
        comb2 = ((*mid) & masks->green)>>5 ;
        comb1 = ((*mid) & masks->blue )>>11;
        
        if(state == R)//correspond to the lower1~lower2 bit in state_w;
        {
          if(abso(comb1-16)<ranger)
          {
            tem=abso(comb1-16);
            cont2++;
          }
          if(abso(comb2-28)<ranger)
          {
            cont2++;
          }
          if(abso(comb3-20)<ranger)
          {
            cont2++;
          }

          if(cont2 == 3)
          {
            outb->state_w++;
            outb++;
            cont2=0;
          }
          else
          {
            outb++;
            cont2=0;
          }
        }
        else if (state == G)//correspond to the lower3~lower4 bit in state_w;
        {
          if(abso(comb1-19)<rangeg)
          {
            cont2++;
          }
          if(abso(comb2-46)<rangeg)
          {
            cont2++;
          }
          if(abso(comb3-17)<rangeg)
          {
            cont2++;
          }

          if(cont2 == 3)
          {
            outb->state_w+=4;
            outb++;
            cont2=0;
          }
          else
          {
            outb++;
            cont2=0;
          }
        }
        else if (state ==B)//correspond to the lower5~lower6 bit in state_w;
        {
          if(abso(comb1-14)<rangeb)
          {
            cont2++;
          }
          if(abso(comb2-27)<rangeb)
          {
            cont2++;
          }
          if(abso(comb3-19)<rangeb)
          {
            cont2++;
          }

          if(cont2 == 3)
          {
            outb->state_w+=16;
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
      free(mid);
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