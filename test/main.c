#include<stdio.h>
#include<stdlib.h>
#include"mylib.h"
#include"macros.h"
#include"linkedlist.h"
#include<string.h>
int main()
{
    int temp=0;
    char porigin[22] = {0};
    FILE*fileb=NULL;
    FILE*fileE=NULL,*fileER = NULL,*fileEG = NULL,*fileEB = NULL;
    new_pathname(porigin,PHOTO);
    fileb = fopen((const char*)porigin,"rb");


    fileE = fopen("./count.md","w");
    fileER = fopen("./countR.md","w");
    fileER = fopen("./countG.md","w");
    fileER = fopen("./countB.md","w");
    fclose(fileE);
    fclose(fileER);
    fclose(fileEG);
    fclose(fileEB);
        while(fileb!=NULL)
        {
            
//recg block;
            BITMAPFILEHEADER*fh = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));//stack volume 1;
                fread(fh,1,sizeof(BITMAPFILEHEADER),fileb);
            BITMAPINFOHEADER*ih = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));//stack volume 2;
                fread(ih,1,sizeof(BITMAPINFOHEADER),fileb);
            long vlength = ih->biWidth*ih->biHeight;
            ELEM *out = (ELEM*)malloc(vlength*sizeof(ELEM));
            char *pnamem = (char*)malloc(22);
            char *pnameb = (char*)malloc(21);
            char *pnamemr = (char*)malloc(22);
            char *pnamemg = (char*)malloc(22);
            char *pnamemb = (char*)malloc(22);
            FILE *fileo = NULL;
            //R;
                new_pathname(pnamem,MARKF);
                fileo = fopen((const char*)pnamem,"wb");
                    recg(R,ih,fileb,out);
                    fwrite(out,1,vlength*sizeof(ELEM),fileo);
                    strcpy((char*)pnamemr,(const char*)pnamem);
                fclose(fileo);
            //G;
                fseek(fileb,fh->bfOffBits,SEEK_SET);
                new_pathname(pnamem,MARKF);
                fileo = fopen((const char*)pnamem,"wb");
                    recg(G,ih,fileb,out);
                    fwrite(out,1,vlength*sizeof(ELEM),fileo);
                    strcpy((char*)pnamemg,(const char*)pnamem);
                fclose(fileo);
            //B;
                fseek(fileb,fh->bfOffBits,SEEK_SET);
                new_pathname(pnamem,MARKF);
                fileo = fopen((const char*)pnamem,"wb");
                    recg(B,ih,fileb,out);
                    fwrite(out,1,vlength*sizeof(ELEM),fileo);
                    strcpy((char*)pnamemb,(const char*)pnamem);
                fclose(fileo);
            free(out);
            /*
                    new_pathname(pnameb,BMP);
                    mark2pic(R,ih,fh,(const char*)pnamemr,(const char*)pnameb);
                    new_pathname(pnameb,BMP);
                    mark2pic(G,ih,fh,(const char*)pnamemg,(const char*)pnameb);
                    new_pathname(pnameb,BMP);
                    mark2pic(B,ih,fh,(const char*)pnamemb,(const char*)pnameb);
            */
           /*
            free(fh);
            free(ih);
            free(pnamem);// the real length of a "(word)" is strlen("(word)")+1,the 1 is the length of ending mark;
            */
// core block;
        //R;
            WORD x=0,y=0;
            char *counter = (char*)malloc(37);
            WORD leng = 0;
            FILE*markf=NULL;
            markf = fopen((const char*)pnamemr,"rb");
            fileE = fopen("./count.md","a");
            fileER = fopen("./countR.md","a");
                core(&x,&y,markf,WIDD,HEII,R);
                printf("%s_R  x=%d , y=%d\n",porigin,x,y);
                sprintf(counter,"%s_R  x=%d , y=%d\n",porigin,x,y);
                leng = strlen(counter);
                fwrite(counter,1,leng,fileE);
                fflush(fileE);
                fwrite(counter,1,leng,fileER);
                fflush(fileER);
            fclose(markf);
            fclose(fileER);
        //G;
            markf = fopen((const char*)pnamemg,"rb");
            fileEG = fopen("./countG.md","a");
                core(&x,&y,markf,WIDD,HEII,G);
                printf("%s_G  x=%d , y=%d\n",porigin,x,y);
                sprintf(counter,"%s_G  x=%d , y=%d\n",porigin,x,y);
                leng = strlen(counter);
                fwrite(counter,1,leng,fileE);
                fwrite(counter,1,leng,fileEG);
            fclose(markf);
            fclose(fileEG);
        //B;
            markf = fopen((const char*)pnamemb,"rb");
            fileEB = fopen("./countB.md","a");
                core(&x,&y,markf,WIDD,HEII,B);
                printf("%s_B  x=%d , y=%d\n",porigin,x,y);
                sprintf(counter,"%s_B  x=%d , y=%d\n",porigin,x,y);
                leng = strlen(counter);
                fwrite(counter,1,leng,fileE);
                fwrite(counter,1,leng,fileEB);
            fclose(markf);
            fclose(fileEB);
        fclose(fileE);
        fclose(fileb);
        free(pnamemr);
        free(pnamemg);
        free(pnamemb);

//open new original file;
            if(fileb!=NULL)
                printf("the %s file has been calculated\n",porigin);
            new_pathname(porigin,PHOTO);
            fileb = fopen((const char*)porigin,"rb");
        }
    getchar();
    return 0;
}

// test recg;