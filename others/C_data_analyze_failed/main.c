#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mylib.h"
#include"macros.h"
#include"calcer.h"
int main()
{
//mainly values;
    FILE*countf = NULL , *outputf = NULL;
    countf = fopen("./count.md","r");
    outputf = fopen("./report.md","a");
    int temp = 0;
    int temp1 = '\n';
    char temp2 = 0;
    char flag_u = 0,flag_d = 0,flag_um = 0;
    char counter_sm = 0 , counter_fm = 0,count_BMP = 0;
    char counter_t = 0;
    char flagxa = 0,flagya = 0;
//standard buffers;
    int sta[9] = {0};//use first group of points as standard points;
    temp = strlen("./photograph/.bmp_  x= , y=\n")+1+1;//1 for end mark of string , 1 for R/G/B mark;
    temp *= 2*LENE;
    int temp_s = temp;
// data buffers;
    int buf1[9] = {0};
    char state1[3] = {0};
    int buf2[9] = {0};
    char state2[3] = {0};
    int buf3[9] = {0};
    char state3[3] = {0};
    char count_mnum = 0;//the number of motion;
    TDV d1,d2,d3,*dc = NULL;
    LINE *l0=NULL,*l1=NULL,*lv0=NULL,*lv1=NULL;
    TDV avr;
    avr.x = 0;
    avr.y = 0;
    //printf("%x",sizeof(long));
    //printf("%x",sizeof(int));
    int limit[4] = {0x7FFFFFFF,-0x7FFFFFFF,0x7FFFFFFF,-0x7FFFFFFF};//Xmin,Xmax,Ymin,Ymax for circle centers;
    int plimit[4] = {0x7FFFFFFF,0,0x7FFFFFFF,0};//Xmin,Xmax,Ymin,Ymax for points;
//main calculate block;
        for(temp1 = '\n';temp1=='\n';)//'\n' = 10;
        {
            readd(buf1,state1,countf);
            temp1 = getc(countf);
            if(temp1 == EOF)
            {
                break;
            }
            readd(buf2,state2,countf);
            temp1 = getc(countf);
            if(temp1 == EOF)
            {
                break;
            }
            readd(buf3,state3,countf);
            temp1 = getc(countf);
//find their commonly circle;
            //R;
            d1.x = buf1[XX];
            d1.y = buf1[YY];
            d2.x = buf2[XX];
            d2.y = buf2[YY];
            d3.x = buf3[XX];
            d3.y = buf3[YY];
                //lineAB;
                l0 = (LINE*)malloc(sizeof(LINE));
                    line(d1,d2,l0);
                //lineBC;
                l1 = (LINE*)malloc(sizeof(LINE));
                    line(d2,d3,l1);
                //vlineAB;
                lv0 = (LINE*)malloc(sizeof(LINE));
                    vline(d1,d2,l0,lv0);
                //vlineBC;
                lv1 = (LINE*)malloc(sizeof(LINE));
                    vline(d2,d3,l1,lv1);
                dc = (TDV*)malloc(sizeof(TDV));
                    vccenter(dc,lv0,lv1);
                    
                
//cycle analysis;
                count_BMP++;
                counter_t = buf1[0]/rangeT;
                if(counter_t%2 == 0)// swing up part;
                {
                    flag_u = 1;
                    //find the width of circle center;
                    //Xmin;
                    if(dc->x <= limit[0])
                    {
                        limit[0] = dc->x;
                    }
                    //Xmax;
                    if(dc->x >= limit[1])
                    {
                        limit[1] = dc->x;
                    }
                    //Ymin;
                    if(dc->y <= limit[2])
                    {
                        limit[2] = dc->y;
                    }
                    //Ymax;
                    if(dc->y >= limit[3])
                    {
                        limit[3] = dc->y;
                    }
                    //find the width of points;
                    //d1;
                    //Xmin;
                    if(d1.x <= plimit[0])
                    {
                        plimit[0] = d1.x;
                    }
                    //Xmax;
                    if(d1.x >= plimit[1])
                    {
                        plimit[1] = d1.x;
                    }
                    //Ymin;
                    if(d1.y <= plimit[2])
                    {
                        plimit[2] = d1.y;
                    }
                    //Ymax;
                    if(d1.y >= plimit[3])
                    {
                        plimit[3] = d1.y;
                    }
                    //d2;
                    //Xmin;
                    if(d2.x <= plimit[0])
                    {
                        plimit[0] = d2.x;
                    }
                    //Xmax;
                    if(d2.x >= plimit[1])
                    {
                        plimit[1] = d2.x;
                    }
                    //Ymin;
                    if(d2.y <= plimit[2])
                    {
                        plimit[2] = d2.y;
                    }
                    //Ymax;
                    if(d2.y >= plimit[3])
                    {
                        plimit[3] = d2.y;
                    }
                    //d3;
                    //Xmin;
                    if(d3.x <= plimit[0])
                    {
                        plimit[0] = d3.x;
                    }
                    //Xmax;
                    if(d3.x >= plimit[1])
                    {
                        plimit[1] = d3.x;
                    }
                    //Ymin;
                    if(d3.y <= plimit[2])
                    {
                        plimit[2] = d3.y;
                    }
                    //Ymax;
                    if(d3.y >= plimit[3])
                    {
                        plimit[3] = d3.y;
                    }

                }
                else if(counter_t%2 == 1)//swing down part;
                {
                    flag_d = 1;
                    //find the width of circle center;
                    //Xmin;
                    if(dc->x <= limit[0])
                    {
                        limit[0] = dc->x;
                    }
                    //Xmax;
                    if(dc->x >= limit[1])
                    {
                        limit[1] = dc->x;
                    }
                    //Ymin;
                    if(dc->y <= limit[2])
                    {
                        limit[2] = dc->y;
                    }
                    //Ymax;
                    if(dc->y <= limit[3])
                    {
                        limit[3] = dc->y;
                    }
                }
                else if(buf1[0]%rangeT == 0 && flag_u == 1)//vertical part;
                {
                    flag_u = 0;
                    //swing up motion analysis;

                        if((limit[1] - limit[0]) <= rangex)//circle center x-vector was enough approximative;
                        {
                            flagxa = 1;
                        }
                        if((limit[3] - limit[2]) <= rangey)//circle center y-vector was enough approximative;
                        {
                            flagya = 1;
                        }
                        if(flagxa == 1 && flagya == 1)//up motion is successful;
                        {
                            flag_um = 1;
                        }
                        flagxa = 0;
                        flagya = 0;
                }
                else if(buf1[0]%rangeT == 0 && flag_d == 1)//reparallel;
                {
                    counter_t++;// one whole cycle;
                    flag_d == 0;
                        if(limit[1] - limit[0] <= rangex)//circle center x-vector was enough approximative;
                        {
                            flagxa = 1;
                        }
                        if(limit[3] - limit[2] <= rangey)//circle center y-vector was enough approximative;
                        {
                            flagya = 1;
                        }
                        if(flagxa == 1 && flagya == 1 && flag_um == 1)//whole motion is successful;
                        {
                            counter_sm++;//successful motion number plus one;
                            fprintf(outputf,"%05d :success",counter_t);
                        }
                        else
                        {
                            counter_fm++;//failed motion number plus one;
                            fprintf(outputf,"%05d :failed",counter_t);
                        }
                        //clear flags;
                        flagxa = 0;
                        flagya = 0;
                        flag_um == 0;

                }
                else
                {
                    continue;
                }
                



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
            temp = temp_s;
        }
fprintf(outputf,"\n\n\n\n*******************************\n");
fprintf(outputf,"success    motion number is : %d\n",counter_sm);
fprintf(outputf,"faliure    motion number is : %d\n",counter_fm);
fprintf(outputf,"whole      motion number is : %d\n",counter_t);
fclose(outputf);
fclose(countf);
getchar();
return 0;
}