#include"mylib.h"
void count(BITMAPINFOHEADER*ih,int*iLineByteCnt,int*skip)
{
  *iLineByteCnt = (((ih->biWidth * ih->biBitCount) + 31) >> 5) << 2;
  *skip = 4 - (((ih->biWidth * ih->biBitCount))>>3) & 3;
}

ELEM* InitELEMB(DWORD size , WORD HEI)//Init elem block;
{
  int cont1=0;
  ELEM *elem=(ELEM*)malloc(sizeof(ELEM)*size);
  ELEM *stack=elem;
  for(;cont1<size;cont1++)
  {
      elem->state_r=0;
      elem->state_g=0;
      elem->state_b=0;
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
BYTE recg( BYTE state , BITMAPINFOHEADER*sizer , FILE *base , ELEM *out )
{
  BYTE  valur = 0,valug = 0,valub = 0;
  int liner=0,skip=0;
  count(sizer,&liner,&skip);
  DWORD cont1 = 0;
  BYTE  cont2 = 0;
  DWORD size=sizer->biWidth*sizer->biHeight;
  ELEM  *outb = out;
  
  ELEM  *outb_f = outb;
  BYTE *mid = (BYTE*)malloc(3);
  BYTE *midd = mid;
  DWORD contt =0;
    if(state < 3)
    {
      fseek(base,offsett,SEEK_SET);
    }
    else
    {
      return error;
    }
      for(cont1 = 0 ; cont1 < (((liner-skip)/3)*sizer->biHeight + sizer->biHeight) ; cont1++)
      {
        if(cont1 % liner == (liner-2))
        {
          fseek(base,skip,SEEK_CUR);
        }
          fread(mid , 1 , 3 , base);
        
        valub = *mid;
        valug = *(++mid);
        valur = *(++mid);
        mid = midd;
        if(state == R)//correspond to the lower1~lower2 bit in state_w;
        {
          if(abso(valur-standard1r)<ranger)
          {
            cont2++;
          }
          if(abso(valug-standard1g)<ranger)
          {
            cont2++;
          }
          if(abso(valub-standard1b)<ranger)
          {
            cont2++;
          }

          if(cont2 == 3)
          {
            outb->state_r++;
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
            outb->state_g++;
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
            outb->state_b++;
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

void new_pathname(BYTE *pname,BYTE mode)
{	 					 
	static WORD index=0;
  FILE *temp;
	while(index<0XFFFF)
	{
		if(mode == BMP)
      sprintf((char*)pname,"./PHOTO/PIC%05d.bmp",index);
		else if(mode == MARKF)
      sprintf((char*)pname,"./MARK/MARK%05d.mark",index);

		temp = fopen((const char*)pname,"r");
		if(temp==NULL)break;
		index++;
    if(mode == CLR)
      index = 0;
      break;
	}
} 

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
  ELEM *dat = (ELEM*)malloc(sizeof(ELEM));
  BYTE datr=0;
  BYTE datg=0;
  BYTE datb=0;
  int M00=0;
  int M10=0;
  int M01=0;
  //
    for(j=0;j<LEN;j++)
    {
      for(i=0;i<WID;i++)
      {
        fread(dat,1,3,markerb);
        datr=dat->state_r;
        datg=dat->state_g;
        datb=dat->state_b;
        if(state == R)
        {
          M00+=datr;
          M10+=(i+1)*datr;
          M01+=(j+1)*datr;
        }
        else if(state == G)
        {
          M00+=datg;
          M10+=(i+1)*datg;
          M01+=(j+1)*datg;
        }
        else if(state == B)
        {
          M00+=datb;
          M10+=(i+1)*datb;
          M01+=(j+1)*datb;
        }
      }
    }

  *x=round(M10,M00);
  *y=round(M01,M00);
}

void mark2pic(BITMAPINFOHEADER*sizer,BITMAPFILEHEADER*head,const char*pname)
{
  int iLineByteCnt=0,skip=0;
  count(sizer,&iLineByteCnt,&skip);
  int length=sizeof(ELEM)*iLineByteCnt*sizer->biHeight;
    ELEM*buf3=(ELEM*)malloc(sizeof(ELEM)*(length-sizer->biHeight*2));
    ELEM*buf3_f=buf3;
    BYTE buf4[2]={0xff,0};
    FILE *filet2 = NULL;
    FILE *fileo=NULL;
        fileo = fopen("./PHOTO/test.bmp","wb");
        fclose(fileo);
        fileo = fopen("./PHOTO/test.bmp","ab");
        filet2 = fopen(pname,"rb");

        fwrite(head,1,sizeof(BITMAPFILEHEADER),fileo);
        fwrite(sizer,1,sizeof(BITMAPINFOHEADER),fileo);

        fread(buf3,1,sizeof(ELEM)*(length-sizer->biHeight*2),filet2);
        for(int i=0;i<(((iLineByteCnt-skip)/3)*sizer->biHeight + sizer->biHeight);i++)
        {
            if(i%iLineByteCnt == iLineByteCnt-2)
            {
                for(int j=0;j<2;j++)
                fwrite((buf4+1),1,1,fileo);
            }
            else
            {
                if(buf3_f->state_r>0)
                {
                    for(int i=0;i<3;i++)
                    {
                    fwrite(buf4,1,1,fileo);
                    }
                }
                else
                {
                    for(int i=0;i<3;i++)
                    {
                    fwrite((buf4+1),1,1,fileo);
                    }
                }
                buf3_f++;
            }
        }
}