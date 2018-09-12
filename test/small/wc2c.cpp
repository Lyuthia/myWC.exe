#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define MAX 100
 
int c=0;
int w=0;
int l=0;
int i=0;

void calculate()
{
    FILE * fp;
    char a;
    char filename[MAX];
     
     printf("请  输入文件名：")；
     gets(filename);
    if((fp=fopen(filename,"r"))==NULL)
    {
        printf("%s 读取失败！\n",filename);
        exit(-1);
    }
    while(!feof(fp))		//设置循环，同时判断是否到达文件尾或者发生错误；
    {
        a=fgetc(fp);		//从文件中读取一个字符；
        if(a!=' '&&a!='\n'&&a!='\t'&&a!=','&&a!='.'&&a!='!'&&a!=';'&&a!='=')
            c++;
        if(a==' '||a=='\n'||a=='\t'||a==','||a=='.'||a=='!'||a=='='||a==';')
            w++;
        if(a=='\n'||a=='\t')
            l++;
    }
    l++;
    c--;         
    fclose(fp);
}


 
/*dsgdrfg rdgdrg 
 gdfgfdggd
 ghjhgyj*/
int main(int argc, char* argv[])             
{
    FILE *fp;
    calculate(argv[2]);
    readWord();
    readChar();
    while(1)
    {
        if((fp=fopen(argv[2],"r"))==NULL)
        {  
        printf("没有找到该文件！\n\n\n");
        scanf("%s%s%s",argv[0],argv[1],argv[2]);
        continue;
        }
        else if(!strcmp(argv[1],"-c"))                 
            printf("File:%sCharNum:%d\n",argv[2],c);
        else if(!strcmp(argv[1],"-w"))                  
            printf("File:%sWordNum:%d\n",argv[2],w);
        else if(!strcmp(argv[1],"-l"))                
            printf("File:%sLineNum:%d\n",argv[2],l);
        else if(!strcmp(argv[1],"exit"))
        {
            printf("Exit!\n");
            break;
        }
        else
            printf("NullPoint\n");
        printf("\n\n");
        scanf("%s%s%s",argv[0],argv[1],argv[2]);
    }
    return 0;
     
}
