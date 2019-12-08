#include<stdio.h>
#include<stdlib.h>

int main()
{
    char buf = 0;
    FILE*base = fopen("../data/count.md","r");
    FILE*outR = fopen("../data/output_R.md","w");
    FILE*outG = fopen("../data/output_G.md","w");
    FILE*outB = fopen("../data/output_B.md","w");

    int bufferR[3] = {0};
    int bufferG[3] = {0};
    int bufferB[3] = {0};
    while(1)
    {
        fscanf(base,"./photograph/%d.bmp_R  x=%d , y=%d\n",&(bufferR[0]),&(bufferR[1]),&(bufferR[2]));
        fscanf(base,"./photograph/%d.bmp_G  x=%d , y=%d\n",&(bufferG[0]),&(bufferG[1]),&(bufferG[2]));
        fscanf(base,"./photograph/%d.bmp_B  x=%d , y=%d\n",&(bufferB[0]),&(bufferB[1]),&(bufferB[2]));

        fread(&buf,1,1,base);
        if(buf=='.')
        {
            fseek(base,-1,SEEK_CUR);
        }
        else
        {
            break;
        }
        fprintf(outR,"%4d %4d %4d\n",bufferR[0],bufferR[1],bufferR[2]);
        fprintf(outG,"%4d %4d %4d\n",bufferG[0],bufferG[1],bufferG[2]);
        fprintf(outB,"%4d %4d %4d\n",bufferB[0],bufferB[1],bufferB[2]);
        
        
    }
printf("divide data program has been completed ,please input anykey to exit\n");
getchar();
return 0;
}
