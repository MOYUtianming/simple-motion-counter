#include<stdio.h>
#include<stdlib.h>
#include"mylib.h"
#include"macros.h"
#include"linkedlist.h"
#include<string.h>
int main()
{
//recg block;
    FILE*filet=fopen("./photograph/16.bmp","rb");
    BITMAPFILEHEADER*fh = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));//stack volume 1;
        fread(fh,1,sizeof(BITMAPFILEHEADER),filet);
    BITMAPINFOHEADER*ih = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));//stack volume 2;
        fread(ih,1,sizeof(BITMAPINFOHEADER),filet);
    long vlength = ih->biWidth*ih->biHeight;
    ELEM *out = (ELEM*)malloc(vlength*sizeof(ELEM));
    BYTE *pnamem = (BYTE*)malloc(21);
    BYTE *pnameb = (BYTE*)malloc(20);
    BYTE *pnamemr = (BYTE*)malloc(21);
    BYTE *pnamemg = (BYTE*)malloc(21);
    BYTE *pnamemb = (BYTE*)malloc(21);
    FILE *fileo = NULL;
    //R;
        new_pathname(pnamem,MARKF);
        fileo = fopen((const char*)pnamem,"wb");
            recg(R,ih,filet,out);
            fwrite(out,1,vlength*sizeof(ELEM),fileo);
            *pnamemr = *pnamem;
        fclose(fileo);
    //G;
        fseek(filet,fh->bfOffBits,SEEK_SET);
        new_pathname(pnamem,1);
        fileo = fopen((const char*)pnamem,"wb");
            recg(G,ih,filet,out);
            fwrite(out,1,vlength*sizeof(ELEM),fileo);
            *pnamemg = *pnamem;
        fclose(fileo);
    //B;
        fseek(filet,fh->bfOffBits,SEEK_SET);
        new_pathname(pnamem,1);
        fileo = fopen((const char*)pnamem,"wb");
            recg(B,ih,filet,out);
            fwrite(out,1,vlength*sizeof(ELEM),fileo);
            *pnamemb = *pnamem;
        fclose(fileo);
    free(out);
    //free(pnamem);
    //free(pnameb);
            new_pathname(pnameb,BMP);
            mark2pic(R,ih,fh,(const char*)pnamemr,(const char*)pnameb);
            new_pathname(pnameb,BMP);
            mark2pic(G,ih,fh,(const char*)pnamemg,(const char*)pnameb);
            new_pathname(pnameb,BMP);
            mark2pic(B,ih,fh,(const char*)pnamemb,(const char*)pnameb);

// core block;
    WORD x=0,y=0;
    FILE*markf=NULL;
    markf = fopen((const char*)pnamemr,"rb");
        core(&x,&y,markf,WIDD,HEII,R);
        printf("R  x=%d , y=%d\n",x,y);
    fclose(markf);
    markf = fopen((const char*)pnamemg,"rb");
        core(&x,&y,markf,WIDD,HEII,G);
        printf("G  x=%d , y=%d\n",x,y);
    fclose(markf);
    markf = fopen((const char*)pnamemb,"rb");
        core(&x,&y,markf,WIDD,HEII,B);
        printf("B  x=%d , y=%d\n",x,y);
    fclose(markf);

    getchar();
    return 0;
}

// test recg;