#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, int *argv[]){
	int fp1,fp2;
	printf("stdin is:\t%d\n",fileno(stdin));    // 标准输入设备
	printf("stdout is:\t%d\n",fileno(stdout));	// 标准输出设备 
	printf("stderr is:\t%d\n",fileno(stderr));	// 标准错误输出设备
	if((fp1=open("/mnt/GithubRepository/WeiMuYang/UNIX-advanced-programming/03-UNIX-code/11-POSIX-IO/test-1.txt",O_WRONLY))==-1)  // 打开文件
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if((fp2=open("/mnt/GithubRepository/WeiMuYang/UNIX-advanced-programming/03-UNIX-code/11-POSIX-IO/test-2.txt",O_WRONLY))==-1)  // 打开文件
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
	printf("test-1 file is: \t%d\n",fp1);	// 打印文件描述符
	printf("test-2 file is: \t%d\n",fp2);	// 打印文件描述符
	close(fp1);
	close(fp2);
	return 0;
}
