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
     
     printf("��  �����ļ�����")��
     gets(filename);
    if((fp=fopen(filename,"r"))==NULL)
    {
        printf("%s ��ȡʧ�ܣ�\n",filename);
        exit(-1);
    }
    while(!feof(fp))		//����ѭ����ͬʱ�ж��Ƿ񵽴��ļ�β���߷�������
    {
        a=fgetc(fp);		//���ļ��ж�ȡһ���ַ���
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
        printf("û���ҵ����ļ���\n\n\n");
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
