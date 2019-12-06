#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mylib.h"
#include"macros.h"
#include"calcer.h"
int main()
{
    FILE*countf = NULL;
    countf = fopen("./count.md","r");
    int temp = 0;
    int temp1 = '\n';
    char temp2 = 0;
    int counter = 0;

    int buf1[9] = {0};
    char state1[3] = {0};
    int buf2[9] = {0};
    char state2[3] = {0};
    int buf3[9] = {0};
    char state3[3] = {0};
    temp = strlen("./photograph/.bmp_  x= , y=\n")+1+1;//1 for end mark of string , 1 for R/G/B mark;
    temp *= 2*3;
    int temp_s = temp;
        for(temp1 = '\n';temp1=='\n';)//'\n' = 10;
        {
            readd(buf1,state1,countf);
            temp1 = getc(countf);
            readd(buf2,state2,countf);
            temp1 = getc(countf);
            readd(buf3,state3,countf);
            temp1 = getc(countf);
// calculate the length of first string;
            for(temp2 = 0;temp2<9;temp2++)
            {
                temp += numlen(buf2[temp2]);
                temp += numlen(buf3[temp2]);
            }
// the judgement of attaching the end or not;
            temp1 = getc(countf);
            if(temp1 != EOF)
            {
                fseek(countf,-2,SEEK_CUR);
                temp1 = getc(countf);

                fseek(countf,-temp,SEEK_CUR);
            }
            counter++;// it should be 4 at the end;
            temp = temp_s;
        }


    getchar();
    return 0;
}