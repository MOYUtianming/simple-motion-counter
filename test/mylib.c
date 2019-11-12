#include"mylib.h"
#include<stdio.h>
/*
   x = return parallel value;
   y = return vertical value;
data = input data;
 WID = input width;
 LEN = input length;
*/
void core(int*x,int*y,int*data,int WID,int LEN)
{
  int i=0,j=0,*dat=data;
  int m=0;
    for(j=0;j<LEN;j++)
    {
      for(i=0;i<WID;i++)
      {
        m+=*(dat++);
      }
    }
    dat=data;//SUPPLEMENT:you can't use data calculate directly;
  int zx=0;
    for(j=0;j<LEN;j++)
    {
      for(i=0;i<WID;i++)
      {
        zx+=(i+1)*(*(dat++));
      }
    }
    dat=data;
  int zy=0;
   for(j=0;j<LEN;j++)
    {
      for(i=0;i<WID;i++)
      {
        zy+=(j+1)*(*(dat++));
      }
    }
  *x=(int)(((float)zx/m)+0.5);
  *y=(int)(((float)zy/m)+0.5);
}
