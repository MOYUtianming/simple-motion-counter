#include<stdio.h>
#include<stdlib.h>
#include"mylib.h"
#include"macros.h"
#include"linkedlist.h"
#include<string.h>
int main()
{
    WORD x=0,y=0;
    FILE*markf=fopen("./MARK/MARK00000.mark","rb");
    core(&x,&y,markf,2714,1280,R);
    printf("x=%d , y=%d\n",x,y);
    getchar();
    return 0;
}

// test recg;