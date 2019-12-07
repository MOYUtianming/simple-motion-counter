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
// circle center functions;
void line(TDV d1,TDV d2,LINE*l0)//line;
{
    l0->k = (d1.x-d2.x) / (d1.y-d2.y);
    l0->b = d1.x-(l0->k)*d1.y;
}
void vline(TDV d1,TDV d2,LINE*l0,LINE*l1)//vertical line;
{
    double xa = 0,ya = 0;
    l1->k = 1 / l0->k;
    xa = (d1.x+d2.x)/2;
    ya = (d1.y+d2.y)/2;
    l1->b = xa - l1->k * ya;
}
void vccenter(TDV*dc,LINE *l0,LINE *l1)//vertical line to circle center;
{
    dc->y = (int)((l1->b-l0->b) / (l1->k - l0->k));
    dc->x = (int)(l1->k * dc->y + l1->b);
}

char  compress(int firnum,int secnum)
{
    double fir = firnum;
    double sec = secnum;
    double cmp = 0;
    cmp = fir-sec;
    if(abs(cmp) < 1)
    {
        return EQU;
    }
    else if(1 <= cmp && cmp <= 10)
    {
        return LLAG;
    }
    else if(cmp>=-10 && cmp<=-1)
    {
        return LSML;
    }
    else if(cmp>10)
    {
        return VLAG;
    }
    else if(cmp<-10)
    {
        return VSML;
    }
    else
    {
        return error;
    }
    
}