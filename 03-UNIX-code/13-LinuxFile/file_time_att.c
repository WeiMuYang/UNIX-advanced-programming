#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<utime.h>
#include<time.h>
#include<sys/types.h>

int main(int argc,char *argv[])
{
	char *ptr;	
	time_t tm;
	struct utimbuf buf;
	time(&tm);		// 获取当前时间
	buf.actime=tm-1000;	// 访问时间
	buf.modtime=tm-5000;	// 修改时间
	ptr=ctime(&tm);		// 将当前时间转成字符串
	printf("now,the time is:%s\n",ptr);
	
	ptr=ctime(&buf.actime);	// 访问时间
	printf("modify the %s access time is:%s\n",argv[1],ptr);

	ptr=ctime(&buf.modtime);// 修改时间
	printf("modify the %s content mod time is:%s\n",argv[1],ptr);
	utime(argv[1],&buf);
	printf("pls run ls -l to check\n");
}
