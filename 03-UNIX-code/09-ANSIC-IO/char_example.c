#include<stdio.h>
int main(int argc,char *argv[])
{
    FILE *fp=NULL; // 定义文件流
    char ch;
    if(argc<=1)    // 如果没有指示要操作的文件
    {
        printf("check usage of %s \n",argv[0]);
        return -1;
    }
if((fp=fopen(argv[1],"r"))==NULL)	// 以只读形式打开argv[1]所指明的文件
    {
        printf("can not open %s\n",argv[1]);
        return -1;
    }
    while ((ch=fgetc(fp))!=EOF)	// 如果ch不是文件的结束
        fputc(ch,stdout);	// 把打开的文件的数据逐个字符输出到标准输出
    fclose(fp);			// 关闭文件
    return 0;
}
