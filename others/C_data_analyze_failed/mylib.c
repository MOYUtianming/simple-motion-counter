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
  DWORD cont1 = 0;
  BYTE  cont2 = 0;
  DWORD size=sizer->biWidth*sizer->biHeight;
  ELEM  *outb = out;
  
  PIXEL *mid = (PIXEL*)malloc(sizeof(PIXEL));
  PIXEL *midd = mid;
  DWORD contt =0;
  int contter=0;
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
          fread(midd , 1 , 3 , base);
        
        valub = midd->blue;
        valug = midd->green;
        valur = midd->red;
        midd = mid;
        if(state == R)
        {
          if(abs(valur-standardrr)<ranger)
          {
            cont2++;
          }
          if(abs(valug-standardrg)<ranger)
          {
            cont2++;
          }
          if(abs(valub-standardrb)<ranger)
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
        else if (state == G)
        {
          if(abs(valur-standardgr)<rangeg)
          {
            cont2++;
          }
          if(abs(valug-standardgg)<rangeg)
          {
            cont2++;
          }
          if(abs(valub-standardgb)<rangeg)
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
        else if (state ==B)
        {
          if(abs(valur-standardbr)<rangeb)
          {
            cont2++;
          }
          if(abs(valug-standardbg)<rangeb)
          {
            cont2++;
          }
          if(abs(valub-standardbb)<rangeb)
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

void new_pathname(char *pname,BYTE mode)
{	 					 
  FILE *temp;
	static int indexb = 0;
  static int indexm = 0;
  static int indexp = 1;
  if(mode == BMP)
    while(indexb<0XFFFF)
    {
        sprintf(pname,"./PHOTO/PIC%05d.bmp",indexb);

      temp = fopen((const char*)pname,"r");
      if(temp==NULL)
      {
        fclose(temp);
        indexb++;
        break;
      }
    }
  else if(mode == MARKF)
      while(indexm<0XFFFF)
    {
      sprintf(pname,"./MARK/MARK%05d.mark",indexm);

      temp = fopen((const char*)pname,"r");
      if(temp==NULL)
      {
        fclose(temp);
        indexm++;
        break;
      }
    }
  else if(mode == PHOTO)
      while(indexp<0XFFFFFFFF)
    {
      sprintf(pname,"./photograph/%d.bmp",indexp);
      temp = fopen((const char*)pname,"r");
      indexp++;
      if(temp!=NULL)
      {
        fclose(temp);
        break;
      }
      else if(temp == NULL)
      {
        pname = error;
        break;
      }
      
    }
  else if(mode == CLR)
    {
      indexb = 0;
      indexm = 0;
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
  int i=0,j=0,q=0;
  FILE *markerb=marker;
  ELEM *dat = (ELEM*)malloc(sizeof(ELEM));
  BYTE datr=0;
  BYTE datg=0;
  BYTE datb=0;
  double M00=0;
  double M10=0;
  double M01=0;
  
    for(i=0;i<LEN;i++)
    {
      for(j=0;j<WID;j++)
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
  free(dat);
}

void mark2pic(BYTE state, BITMAPINFOHEADER*sizer,BITMAPFILEHEADER*head,const char*pnamem,const char*pnameb)
{
    int i=0,j=0,k=0; 
  //count(sizer,&iLineByteCnt,&skip);
  int length=sizer->biWidth*sizer->biHeight;
    ELEM*buf3=(ELEM*)malloc(length*sizeof(ELEM));
    ELEM*buf3_f=buf3;
    BYTE buf4[2]={0xff,0};
    FILE *filet = NULL;
    FILE *fileo=NULL;
        filet = fopen(pnamem,"rb");
        fileo = fopen(pnameb,"wb");
        fclose(fileo);
        fileo = fopen(pnameb,"ab");

        fwrite(head,1,sizeof(BITMAPFILEHEADER),fileo);
        fwrite(sizer,1,sizeof(BITMAPINFOHEADER),fileo);

        fread(buf3,1,sizeof(ELEM)*(length),filet);
        for(i=0;i<(sizer->biWidth*sizer->biHeight);i++)
        {
          if(state == R)
            if(buf3->state_r>0)
            {
                for(k=0;k<3;k++)
                {
                  fwrite(buf4,1,1,fileo);
                }
            }
            else
            {
                for(k=0;k<3;k++)
                {
                  fwrite((buf4+1),1,1,fileo);
                }
            }
            else if(state == G)
              if(buf3->state_g>0)
              {
                  for(k=0;k<3;k++)
                  {
                  fwrite(buf4,1,1,fileo);
                  }
              }
              else
              {
                  for(k=0;k<3;k++)
                  {
                  fwrite((buf4+1),1,1,fileo);
                  }
              }
            else if(state == B)
              if(buf3->state_b>0)
              {
                  for(k=0;k<3;k++)
                  {
                  fwrite(buf4,1,1,fileo);
                  }
              }
              else
              {
                  for(k=0;k<3;k++)
                  {
                  fwrite((buf4+1),1,1,fileo);
                  }
              }
          buf3++;
        }
        fclose(filet);
        fclose(fileo);
}
