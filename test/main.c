#include<stdio.h>
#include<stdlib.h>
#include"mylib.h"
#include"macros.h"
#include"linkedlist.h"

#include<stdio.h>
#include<stdlib.h>
#include"mylib.h"
int main()
{
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
        if(buf3->state_w&maskB>0)
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


//track saving block;
    TRACKH *theader=NULL;
    TRACKE *thead=NULL;
    CreateH(&thead);
    thead->x=0;
    thead->y=0;
    InitTRACKE(thead);
    InitTRACKH(theader,thead);
    //use for loop here.
    CreateTRACKE(&thead,1);
    //test function
    int i=0;
    PTRACKE(thead,TRACKELength(thead));

    getchar();
    return 0;
}
