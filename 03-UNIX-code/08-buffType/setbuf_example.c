/* Example show usage of setbuf() &setvbuf() */
#include<stdio.h>
#include<error.h>
#include<string.h>
int main( int argc , char ** argv )
{
	int i;
	FILE * fp;
	char msg1[]="hello,wolrd\n";
	char msg2[] = "hello\nworld";
	char buf[128];

//open a file and set nobuf(used setbuf).and write string to it,check it before close of flush the stream
	if(( fp = fopen("no_buf1.txt","w")) == NULL)// 打开文件
	{
		perror("file open failure!");
		return(-1);
	}
	setbuf(fp,NULL); 			// fp指向的缓冲区关闭	 
	memset(buf,'\0',128);		// 申请128字节的区域给buf，并初始化为0
	fwrite( msg1 , 7 , 1 , fp );// 将msg1的7个字符写入文件
	printf("test setbuf(no buf)!check no_buf1.txt\n");
	printf("now buf data is :buf=%s\n",buf);//查看缓冲区内容

	printf("press enter to continue!\n");
	getchar();
	fclose(fp);


//open a file and set nobuf(used setvbuf).and write string to it,check it before close of flush the stream
	if(( fp = fopen("no_buf2.txt","w")) == NULL)
	{
		perror("file open failure!");
		return(-1);
	}
	setvbuf( fp , NULL, _IONBF , 0 );// 设置无缓冲区
	memset(buf,'\0',128);		
	fwrite( msg1 , 7 , 1 , fp );	 // 写入数据 
	printf("test setvbuf(no buf)!check no_buf2.txt\n");

	printf("now buf data is :buf=%s\n",buf);//查看缓冲区的内容

	printf("press enter to continue!\n");
	getchar();
	fclose(fp);

//open a file and set line buf(used setvbuf).and write string(include '\n') to it,
//
//check it before close of flush the stream
	if(( fp = fopen("l_buf.txt","w")) == NULL)
	{
		perror("file open failure!");
		return(-1);
	}
	setvbuf( fp , buf , _IOLBF , sizeof(buf) );// 设置行缓冲区
	memset(buf,'\0',128);
	fwrite( msg2 , sizeof(msg2) , 1 , fp );// 将msg2写入fp，msg2有两行
	printf("test setvbuf(line buf)!check l_buf.txt, because line buf ,only data before enter send to file\n");

	printf("now buf data is :buf=%s\n",buf); // 打印缓冲区的值
	printf("press enter to continue!\n");
	getchar();
	fclose(fp);

//open a file and set full buf(used setvbuf).and write string to it for 20th time (it is large than the buf)
//check it before close of flush the stream
	if(( fp = fopen("f_buf.txt","w")) == NULL){
		perror("file open failure!");
		return(-1);
	}
	setvbuf( fp , buf , _IOFBF , sizeof(buf) ); // 设置全缓冲区
	memset(buf,'\0',128);
	fwrite( msg2 , sizeof(msg2) , 1 , fp );
	printf("test setbuf(full buf)!check f_buf.txt\n");
	
	printf("now buf data is :buf=%s\n",buf);// 打印缓冲区的值
	printf("press enter to continue!\n");
	getchar();

	fclose(fp);
	
}
