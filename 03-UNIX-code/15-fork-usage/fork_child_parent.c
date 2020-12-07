#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(void)
{
	pid_t pid;
	if((pid=fork())==-1)
		printf("fork error");
	if((pid=fork())==-1)
		printf("fork error");
	else if(pid==0)
	{
		printf("in the child0 process\n");
	}
	else if(pid==1)
	{
		printf("in the child1 process\n");
	}
	return 0;
}
