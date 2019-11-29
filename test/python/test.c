#include<stdio.h>
#include<string.h>
int main()
{
    char a[]="link";
    char value[]="value";
    strcat(a,value);
    strcpy(a,value);
    printf("%s",a);
    getchar();
    return 0;
}