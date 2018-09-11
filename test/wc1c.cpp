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

//此函数计算英文单词个数
int readWord() 
{
    FILE* fp;
    char ch;
    char flag = 0;
    int num=0;
     char filename[MAX];
     
     printf("请输入文件名：")；
     gets(filename);
    if((fp = fopen(filename,"r")) == NULL)
    {
        printf("%s 读取失败！",filename);
        exit(EXIT_FAILURE);
    }
    printf("%s 读取成功！！！\n",filename);
    while(!feof(fp))		//设置循环，同时判断是否到达文件尾或者发生错误；
    {
        ch = fgetc(fp);		//从文件中读取一个字符；
        if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
            flag = 0;
        else if(flag == 0 && (ch != '-' && ch != '/'&& ch != '\''))
        {
            num++;
            flag = 1;
        }
    }
    fclose(fp);
    printf("File %s has %ld characters\n",filename,num);
    return num;
}

int readChar()	//计算文件中的字符数；
{
	FILE *fp;
	char ch;
	char flag = 0;
	int num = 0;
	char filename[MAX];
     
     printf("请输入文件名：")；
     gets(filename);
	if((fp = fopen(filename,"r")) == NULL)
	{
		printf("%s 读取失败！",filename);
        	exit(EXIT_FAILURE);
	}
	  printf("%s 读取成功！！！\n",filename);
	  while((ch=getc(fp))!=EOF)
 	{
  		putc(ch,stdout);
  		num++;
 	}
 	fclose(fp);
 	printf("File %s has %ld characters\n",filename,num);
 	return 0;
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
