#ifndef _CALCER_H
#define _CALCER_H
#include<stdio.h>
#include"macros.h"
#include<stdlib.h>

#define INF(x,y) (x == (-2147483648) || x == (-2147483648))

typedef struct tag2Dvector
{
    double x;
    double y;
}TDV;


typedef struct tagline
{
    double k;
    double b;
} LINE;

//function statements;
    int numlen(int num);
    void readd(int buf1[9],char state1[3],FILE*source);
    void line(TDV d1,TDV d2,LINE*l0);//line;
    void vline(TDV d1,TDV d2,LINE*l0,LINE*l1);//vertical line;
    void vccenter(TDV*dc,LINE *l0,LINE *l1);//vertical line to circle center;
    char  compress(int firnum,int secnum);
#endif