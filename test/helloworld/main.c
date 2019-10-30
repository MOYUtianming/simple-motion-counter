     #include<stdio.h>
     main()
     {
          FILE *fp;                /*定义一个文件指针*/
          int i;
          fp=fopen("CLIB", "rb");  /*打开当前文件夹名为CLIB的文件仅仅读*/
          if(fp==NULL)             /*推断文件是否打开成功*/
             puts("File open error");/*提示打开不成功*/
          i=fclose(fp);            /*关闭打开的文件*/
          if(i==0)                 /*推断文件是否关闭成功*/
            printf("O,K");         /*提示关闭成功*/
          else
            puts("File close error");/*提示关闭不成功*/
     }