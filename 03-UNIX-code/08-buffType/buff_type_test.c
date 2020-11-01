#include <stdio.h>
// 函数声明
void pr_stdio(const char *, FILE *);
int main(void)
{
        FILE* fp;
        fputs("enter any character\n", stdout);
        if(getchar()==EOF) // 如果获取的是文件的结尾符号
                printf("getchar error");
        fputs("one line to standard error\n", stderr); // 输出
        pr_stdio("stdin",  stdin);	// 行缓冲区
        pr_stdio("stdout", stdout);	// 行缓冲区
        pr_stdio("stderr", stderr);	// 无缓冲区

        if ( (fp = fopen("/etc/motd", "r")) == NULL)
                printf("fopen error");
        if (fgetc(fp) == EOF)
                printf("getc error");
        pr_stdio("/etc/motd", fp);		// 普通文件全缓冲区（16.04没找到文件）
        return(0);
}
// 
void pr_stdio(const char *name, FILE *fp)
{
        printf("stream = %s, ", name);// 要存的字符串
        if (fp->_flags & _IO_UNBUFFERED)
			printf("unbuffered");   // 无缓冲区
        else if (fp->_flags & _IO_LINE_BUF) 
			printf("line buffered");// 行缓冲区
        else
			printf("fully buffered");// 全缓冲区
        printf(", buffer size = %ld\n", fp->_IO_buf_end-fp->_IO_buf_base);
}
