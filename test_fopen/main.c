#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define SIZE_PO 533206
main()
{
  /*
  FILE *fp;              
  int i;
  fp=fopen("pic/glory.bmp", "rb"); 
  if(fp==NULL)             
      puts("File open error");
  */
  /*User code*/
  /*User code*/
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
  FILE*fp=NULL;
  char*p=NULL;
  long size=0;
    fp=fopen("pic/glory.bmp","r");
    fseek(fp,0,SEEK_END);
    size=ftell(fp);
    printf("%ld\n",size);
    rewind(fp);
    p=(char*)malloc(sizeof(char) * SIZE_PO);
    fread(p,1,SIZE_PO,fp);
  int i=0;
  char *elem=p;
  FILE*fp2=NULL;
  fp2=fopen("text.bmp","w");
  fwrite(p,sizeof(char),SIZE_PO,fp2);
  /*
    for(i=0;i<5000;i++)
    {
      printf("%d\n",*elem);
      elem++;
    }
  */
    free(p);
  return 0;
}