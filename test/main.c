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
}
