#include<stdio.h>
#include<stdlib.h>
#include"mylib.h"

int main()
{
    FILE*pic=NULL;
    FILE*out=NULL;
    DWORD maskn[3]={0};//0xf800=R;0x07e0=G;0x001f=B;
        pic=fopen("PHOTO/PICr.bmp","rb");
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
                printf("end of mask.\n");
        fclose(pic);
     getchar();
    return 0;
}