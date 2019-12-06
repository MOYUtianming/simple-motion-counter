#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mylib.h"
#include"macros.h"
#include"calcer.h"
int main()
{
//mainly values;
    FILE*countf = NULL;
    countf = fopen("./count.md","r");
    int temp = 0;
    int temp1 = '\n';
    char temp2 = 0;
    int counter = 0;
    int cmp1 = 0,cmp2 = 0;
//standard buffers;
    int sta[9] = {0};//use first group of points as standard points;
    temp = strlen("./photograph/.bmp_  x= , y=\n")+1+1;//1 for end mark of string , 1 for R/G/B mark;
    temp *= 2*3;
    int temp_s = temp;
// data buffers;
    int buf1[9] = {0};
    char state1[3] = {0};
    int buf2[9] = {0};
    char state2[3] = {0};
    int buf3[9] = {0};
    char state3[3] = {0};

// building standard block;
        for(temp1 = 0;temp1<4;temp1++)
        {
        //read two elements;
            readd(buf1,state1,countf);
            temp1 = getc(countf);
            readd(buf2,state2,countf);
            temp1 = getc(countf);
        //compress them;
            
        }
        
getchar();
//main calculate block;
        for(temp1 = '\n';temp1=='\n';)//'\n' = 10;
        {
            readd(buf1,state1,countf);
            temp1 = getc(countf);
            readd(buf2,state2,countf);
            temp1 = getc(countf);
            readd(buf3,state3,countf);
            temp1 = getc(countf);



// calculate the length of strings which are needing to skip;
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
            counter++;
            temp = temp_s;
        }


getchar();
return 0;
}