#include"mylib.h"

ELEM* InitELEMB(DWORD size , WORD HEI)//Init elem block;
{
  int cont1=0;
  ELEM *elem=(ELEM*)malloc(sizeof(ELEM)*size);
  ELEM *stack=elem;
  for(;cont1<size;cont1++)
  {
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
  WORD  valur = 0,valug = 0,valub = 0;

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
        valub = ((*mid) & masks->red  );
        valug = ((*mid) & masks->green)>>5 ;
        valur = ((*mid) & masks->blue )>>11;

        if(state == R)//correspond to the lower1~lower2 bit in state_w;
        {
          if(abso(valur-16)<ranger)
          {
            tem=abso(valur-16);
            cont2++;
          }
          if(abso(valug-28)<ranger)
          {
            cont2++;
          }
          if(abso(valub-20)<ranger)
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
          if(abso(valur-19)<rangeg)
          {
            cont2++;
          }
          if(abso(valug-46)<rangeg)
          {
            cont2++;
          }
          if(abso(valub-17)<rangeg)
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
          if(abso(valur-14)<rangeb)
          {
            cont2++;
          }
          if(abso(valug-27)<rangeb)
          {
            cont2++;
          }
          if(abso(valub-19)<rangeb)
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
void new_pathname(BYTE *pname,BYTE mode)
{	 
	BYTE res;					 
	static WORD index=0;
  FILE *temp;
	while(index<0XFFFF)
	{
		if(mode==0)sprintf((char*)pname,"0:PHOTO/PIC%05d.bmp",index);
		else sprintf((char*)pname,"0:MARK/MARK%05d.mark",index);
		res=f_open(temp,(const char*)pname,"r");//³¢ÊÔ´ò¿ªÕâ¸öÎÄ¼þ
		if(res==NULL)break;		//¸ÃÎÄ¼þÃû²»´æÔÚ=ÕýÊÇÎÒÃÇÐèÒªµÄ.
		index++;
	}
} 
*/
/*
function : find the core of color block;
x = return parallel value;
y = return vertical value;
data = input data;
WID = input width;
LEN = input length;
*/
void core(WORD*x,WORD*y,FILE*marker,WORD WID,WORD LEN,BYTE state)
{
  int i=0,j=0;
  FILE *markerb=marker;
  BYTE dat=0;
  BYTE datr=0;
  BYTE datg=0;
  BYTE datb=0;
  int m=0;
  int zx=0;
  int zy=0;
  //
    for(j=0;j<LEN;j++)
    {
      for(i=0;i<WID;i++)
      {
        fread(&dat,1,1,markerb);
        datr=dat&maskR;
        datg=(dat&maskG)>>2;
        datb=(dat&maskB)>>4;
        if(state == R)
        {
          m+=datr;
          zx+=(i+1)*datr;
          zy+=(j+1)*datr;
        }
        else if(state == G)
        {
          m+=datg;
          zx+=(i+1)*datg;
          zy+=(j+1)*datg;
        }
        else if(state == B)
        {
          m+=datb;
          zx+=(i+1)*datb;
          zy+=(j+1)*datb;
        }
      }
    }

  *x=round(zx,m);
  *y=round(zy,m);
}