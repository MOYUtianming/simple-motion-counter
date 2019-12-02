//1
    FILE*pic=NULL;
    FILE*out=NULL;
    DWORD maskn[3]={0};//0xf800=R;0x07e0=G;0x001f=B;
        pic=fopen("PHOTO/PIC00002.bmp","rb");
            BITMAPFILEHEADER*fileh=NULL;
            fileh=(BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
                fread(fileh,1,sizeof(BITMAPFILEHEADER),pic);
                WORD *pfile1=NULL;
                DWORD*pfile2=NULL;
                printf("head of fileheader :\n");
                    pfile1=(WORD*)fileh;
                    printf("%c",(*(pfile1)<<8)>>8);
                    printf("%c\n",(*(pfile1++))>>8);
                    pfile2=(DWORD*)(pfile1);
                    printf("%d\n",*(pfile2++));
                    pfile1=(WORD*)pfile2;
                    for(int i=0;i<2;i++)
                    {
                        printf("%d\n",*(pfile1++));
                    }
                    pfile2=(DWORD*)(pfile1);
                    printf("%d\n",*(pfile2)++);
                printf("end  of fileheader.\n");
            free(fileh);
//2
            BITMAPINFOHEADER*infoh=NULL;
            infoh=(BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
                fread(infoh,1,sizeof(BITMAPINFOHEADER),pic);
                WORD *pinfo1=NULL;
                DWORD*pinfo2=NULL;
                LONG *pinfo3=NULL;
                printf("head of infoheader :");
                    pinfo2=(DWORD*)infoh;
                    printf("%d\n",*(pinfo2++));
                    pinfo3=(LONG*)pinfo2;
                    for(int i=0;i<2;i++)
                    {
                        printf("%d\n",*(pinfo3++));
                    }
                    pinfo1=(WORD*)pinfo3;
                    for(int i=0;i<2;i++)
                    {
                        printf("%d\n",*(pinfo1++));
                    }
                    pinfo2=(DWORD*)pinfo1;
                    for(int i=0;i<2;i++)
                    {
                        printf("%d\n",*(pinfo2++));
                    }
                    pinfo3=(LONG*)pinfo2;
                    for(int i=0;i<2;i++)
                    {
                        printf("%d\n",*(pinfo3++));
                    }
                    pinfo2=(DWORD*)pinfo3;
                    for(int i=0;i<2;i++)
                    {
                        printf("%d\n",*(pinfo2++));
                    }
                printf("end of infoheader.\n");
            free(infoh);

            MASK*mask=NULL;
            mask=(MASK*)malloc(sizeof(MASK));
                fread(mask,1,sizeof(MASK),pic);
                DWORD*pmask=NULL;
                printf("head of mask: \n");
                    pmask=(DWORD*)mask;
                    for(int i=0;i<3;i++)
                    {
                        maskn[i]=*pmask;
                        printf("NO.%d mask is: %x\n",i,*(pmask++));
                    }
                    //0xf800=R;0x07e0=G;0x001f=B;
                printf("end of mask.\n");
            free(mask);

            long buffer[1]={0};
                fread(buffer,1,3,pic);
                int pelem[3]={0};
                printf("head of rgb: \n");
                    printf("%d\n",*(buffer));
                    pelem[1]=((*buffer)&maskn[0])>>11;
                    printf("%d\n",pelem[1]);
                    pelem[2]=((*buffer)&maskn[1])>>5;
                    printf("%d\n",pelem[2]);
                    pelem[3]=(*buffer)&maskn[2];
                    printf("%d\n",pelem[3]);
                printf("end of rgb.\n");
        fclose(pic);
     getchar();
    return 0;

    FILE*file11=fopen("./PHOTO/PIC00002.bmp","rb");
    BYTE *head=(BYTE*)malloc(66);
    fread(head,1,66,file11);
    char colorb[3]={12,26,17};
    char colorg[3]={15,39,15};
    char colorr[3]={18,25,15};
    char color0[3]={0,0,0};
    FILE*file22=fopen("out1.bmp","wb");
    fclose(file22);
    file22=fopen("out1.bmp","ab");
    fwrite(head,1,66,file22);
    for(int i=0;i<200*480;i++)
    {
        fwrite(colorr,1,3,file22);
    }
    for(int i=0;i<200*480;i++)
    {
        fwrite(colorg,1,3,file22);
    }
    /*
    for(int i=0;i<200*480;i++)
    {
        fwrite(colorr,1,3,file22);
    }
    for(int i=0;i<200*480;i++)
    {
        fwrite(color0,1,3,file22);
    }
    */
   fclose(file22);
    getchar();
    return 0;
//3
    FILE*file22=NULL;
    unsigned char colorb[2]={81,99};
    unsigned char colorr[2]={144,163};
    file22=fopen("out1.bmp","ab");
    fseek(file22,66,SEEK_SET);
    for(int i=0;i<20;i++)
    {
        for(int i=0;i<240;i++)
        {
            fwrite(colorb,1,2,file22);
        }
        for(int i=0;i<240;i++)
        {
            fwrite(colorr,1,2,file22);
        }
    }
   fclose(file22);

#include<stdio.h>
#include<stdlib.h>
#include"mylib.h"
int main()
{

    FILE*filet=fopen("./PHOTO/PIC00002.bmp","rb");
    BITMAPFILEHEADER*fh = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));//stack volume 1;
        fread(fh,1,sizeof(BITMAPFILEHEADER),filet);
    BITMAPINFOHEADER*ih = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));//stack volume 2;
        fread(ih,1,sizeof(BITMAPINFOHEADER),filet);
        int size=ih->biWidth * ih->biHeight;
    MASK*masker = (MASK*)malloc(sizeof(MASK));//stack volume 3;
        fread(masker,1,sizeof(MASK),filet);

    MARK*outa=NULL;
        outa=InitMARKB(size,ih);// stack volume 4;

    ELEM*outb=NULL;
        outb=InitELEMB(size,ih->biHeight);//stack volume 5;
                recg(R,ih,masker,filet,outb);
                recg(G,ih,masker,filet,outb);
                recg(B,ih,masker,filet,outb);
                /*track code site*/

    FILE*fileo=fopen("./MARK/mark1.mark","wb");
        fwrite(outa,1,sizeof(MARK),fileo);
        fclose(fileo);
        fileo=fopen("./MARK/mark1.mark","ab");
        fwrite(outb,1,sizeof(ELEM)*size,fileo);
        fclose(fileo);
    fclose(filet);


    FILE*file1=fopen("./MARK/mark1.mark","rb");
    MARK*buf1=(MARK*)malloc(sizeof(MARK));
    fread(buf1,1,sizeof(MARK),file1);
    FILE*file2=fopen("./PHOTO/PIC00002.bmp","rb");
    BYTE*buf2=(BYTE*)malloc(66);
    fread(buf2,1,66,file2);
    fclose(file2);
    file2=fopen("./PHOTO/echorb.bmp","wb");
    fwrite(buf2,1,66,file2);

    fclose(file2);
    file2=fopen("./PHOTO/echorb.bmp","ab");
    ELEM*buf3=(ELEM*)malloc(sizeof(ELEM));
    WORD *buf4=(WORD*)malloc(sizeof(WORD)*480*800);
    WORD *point1=buf4;
    for(int i=0;i<480*800;i++)
    {
    
        fread(buf3,1,sizeof(ELEM),file1);
        if(buf3->value_b>0)
        {
            *(point1++)=0;
        }
        else
        {
            *(point1++)=0XFFFF;
        }
    
    }
    fwrite(buf4,1,sizeof(WORD)*480*800,file2);
    fclose(file2);

    getchar();
    return 0;
}
//core original version
void core(int*x,int*y,BYTE*data,int WID,int LEN,BYTE state)
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

【HEAD】
//photograph file read block;
    //head reading;
    FILE*filet=fopen("./PHOTO/PIC00002.bmp","rb");
    BITMAPFILEHEADER*fh = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));//stack volume 1;
        fread(fh,1,sizeof(BITMAPFILEHEADER),filet);
    BITMAPINFOHEADER*ih = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));//stack volume 2;
        fread(ih,1,sizeof(BITMAPINFOHEADER),filet);
        int size=ih->biWidth * ih->biHeight;
    MASK*masker = (MASK*)malloc(sizeof(MASK));//stack volume 3;
        fread(masker,1,sizeof(MASK),filet);

    ELEM*outb=NULL;
        outb=InitELEMB(size,ih->biHeight);//stack volume 5;
               // recg(R,ih,masker,filet,outb);
                recg(G,ih,masker,filet,outb);
                //recg(B,ih,masker,filet,outb);
                /*track code site*/
    //create a mark file;
    FILE*fileo=NULL;
        fileo=fopen("./MARK/mark1.mark","wb");
        fwrite(outb,1,sizeof(ELEM)*size,fileo);
        fclose(fileo);
    fclose(filet);
    //output experimental echo bmpfile;
    //open mark file ;
    FILE*file1=fopen("./MARK/mark1.mark","rb");
    //read bmp file head and write in the output file;
    FILE*file2=fopen("./PHOTO/PIC00002.bmp","rb");
    BYTE*buf2=(BYTE*)malloc(66);
        fread(buf2,1,66,file2);
        fclose(file2);

        file2=fopen("./PHOTO/echorb.bmp","wb");
        fwrite(buf2,1,66,file2);
    fclose(file2);
    //write echo file elements;
    file2=fopen("./PHOTO/echorb.bmp","ab");
    ELEM*buf3=(ELEM*)malloc(sizeof(ELEM));
    WORD *buf4=(WORD*)malloc(sizeof(WORD));
    for(int i=0;i<480*800;i++)
    {
    
        fread(buf3,1,sizeof(ELEM),file1);
        if(buf3->state_w&maskB>0)
        {
            *(buf4)=0;
            printf("b :%d\n",buf3->state_w&maskB);
        }
        else
        {
            *(buf4)=0XFFFF;
        }
        fwrite(buf4,1,sizeof(WORD),file2);
    }
    fclose(file2);
    //find core block;
    WORD x , y;
    //rewind(file1);
    //core(&x,&y,file1,480,800,R);
    //printf("R :x = %d , y = %d\n",x,y);
    rewind(file1);
    core(&x,&y,file1,480,800,G);
    printf("G :x = %d , y = %d\n",x,y);
    //rewind(file1);
    //core(&x,&y,file1,480,800,B);
    //printf("B :x = %d , y = %d\n",x,y);

//track saving block;
    TRACKH *theader=NULL;
    TRACKE *thead=NULL;
    theader=(TRACKH*)malloc(sizeof(TRACKH));
    CreateH(&thead);
    thead->x=0;
    thead->y=0;
    InitTRACKE(thead);
    InitTRACKH(theader,thead);
    //use 'for' loop here.
    CreateTRACKE(&thead,1);
    //test function.
    int i=0;
    //PTRACKE(thead,TRACKELength(thead));

    getchar();
    return 0;
【END】

