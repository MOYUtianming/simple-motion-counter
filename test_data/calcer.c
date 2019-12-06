#include"calcer.h"

int numlen(int num)
{
    int temp = 0;
    int buf = num;
        for(temp = 0;buf!=0;temp++)
        {
            buf /= 10;
        }
    return temp;
}

void readd(int buf1[9],char state1[3],FILE*source)
{
    fscanf(source,"./photograph/%d.bmp_%c  x=%d , y=%d\n",&(buf1[0]),&(state1[0]),&(buf1[1]),&(buf1[2]) );
    fscanf(source,"./photograph/%d.bmp_%c  x=%d , y=%d\n",&(buf1[3]),&(state1[1]),&(buf1[4]),&(buf1[5]) );
    fscanf(source,"./photograph/%d.bmp_%c  x=%d , y=%d",&(buf1[6]),&(state1[2]),&(buf1[7]),&(buf1[8]) );
}