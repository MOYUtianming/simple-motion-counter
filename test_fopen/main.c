#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"mylib.h"
//#include<windows.h>
//#define SIZE_PI 533206
//#define TEST test
#define LEN 10
#define WID 15
//int test(int a);
//void core(int*x,int*y,int*data);
int main()
{
  int tt[LEN*WID]={0};
  int u=0; 
     for(u=0;u<LEN*WID;u++)
     {
       if(u>((WID)*2-1))
       {
         tt[u]=1;
       }
       printf("%d ",tt[u]);
       if((u+1)%WID==0)
       {
         printf("\n");
       }
     }
  int xx=0,yy=0;
  core(&xx,&yy,tt,WID,LEN);
  printf("x=%d\ny=%d\n",xx,yy);
  /*
    FILE*data;
    FILE*out;
    data=fopen("PHOTO/PIC00001.bmp","r");
    out =fopen("testpic/blueout","w");
    char *p=NULL;
      p=(char*)malloc(sizeof(char)*4);
        fseek(data,0x22,SEEK_SET);
        fread(p,1,4,data);
        int i=0;
          for(i=0;i<4;i++)
          {
            printf("%d: %x\n",i+1,(unsigned char)*p++);
          }
        //fseek(data,0,SEEK_SET);
      free(p-4);
  */
    	return 0;
}
/*
*/
/*
  srand(time(NULL));  
  for(int i=0;i<LEN*WID;i++)
  {
  int s=0; 
  tt[i]=(int)rand()%255;
  printf("%d\n",tt[i]);
  }
*/
/*
  void core(int*x,int*y,int*data)
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
*/

/*
  FILE *fp;              
  int i;
  fp=fopen("pic/glory.bmp", "rb"); 
  if(fp==NULL)             
      puts("File open error");
*/
/*
  i=fclose(fp);           
  if(i==0)                
    printf("O,K");        
  else
    puts("File close error");
*/
 /*
  char *s="That's good news";  
  int i=617;                   
  FILE *fp;                     
  fp=fopen("test.dat", "w");    
  fputs("Your score of TOEFLis", fp);
  fputc(':', fp);             
  fprintf(fp, "%d/n", i);       
  fprintf(fp, "%s", s);        
  fclose(fp);                  
*/
/*
  char *s, m[20];
  int i;
  FILE  *fp;
  fp=fopen("test.dat", "r");   
  fgets(s, 24, fp);          
  printf("%s", s);             
  fscanf(fp, "%d", &i);        
  printf("%d", i);             
  putchar(fgetc(fp));          
  fgets(m, 17, fp);          
  puts(m);                      
  fclose(fp);                 
  getchar();        
*/
/*
  FILE *fp;
  int get=100;
  if((fp=fopen("pic/glory.bmp", "rb"))==NULL)
    {
      printf("Can't open file");
      return 1;
    }
  fseek(fp, 8, SEEK_SET);//From the head of the file,skip 8 byte;
  get=fgetc(fp);
  printf("%d\n",get);
  fclose(fp);        
*/
/*
  FILE*fp=NULL;
  char*p=NULL;
  long size=0;
    fp=fopen("pic/glory.bmp","r");
    fseek(fp,0,SEEK_END);
    size=ftell(fp);
    printf("%ld\n",size);
    rewind(fp);
    p=(char*)malloc(sizeof(char) * SIZE_PI);
    fread(p,1,SIZE_PI,fp);
  int i=0;
  char *elem=p;
  FILE*fp2=NULL;
  fp2=fopen("text.bmp","w");
  fwrite(p,sizeof(char),SIZE_PI,fp2);
*/
/*
  for(i=0;i<5000;i++)
  {
    printf("%d\n",*elem);
    elem++;
  }
*/
 /*
    free(p);
  int x=TEST(1);
  printf("%d\n",x);
*/
/*
  int test(int a)
  {
    a=a+1;
    return a;
  }
*/
