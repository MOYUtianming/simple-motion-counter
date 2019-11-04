#include<stdio.h>
#include<stdlib.h>

#define SZ  1

int main()
{
    int p=0;
    FILE *file=NULL,*out=NULL;
    file=fopen("./PHOTO/PIC00001.bmp","r");
    out=fopen("./out","w");

    char *data=NULL;
    data=(char*)malloc(2*SZ);//One file has const volume = 768066*char;
    //in project,function "malloc" is replaced by "mymalloc" .
    fread(data,SZ,2,file);
    for(int i;i<2;i++)
    {
        printf("%d",*(data+i));
    }
    getchar();
    getchar();
    return 0;
}