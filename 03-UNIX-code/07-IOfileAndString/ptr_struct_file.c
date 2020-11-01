#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// 1. 宏定义：定义打印的形式
#define prt(CONTENT,MSG) printf(CONTENT":\t%p\n",MSG)

int main(int argc, char *argv[])
{
	FILE *fp_src,*fp_des;
	char buffer[10],buffer1[128];
	int i;
	// 2. 以可读方式打开文件，文件名由argv传入
	if((fp_src=fopen(argv[1],"r+"))== NULL)	
	{
		perror("open1");
		exit(EXIT_FAILURE);
	}
	// 3. 以可写方式打开文件，文件名由argv传入
	if((fp_des=fopen(argv[2],"w+"))== NULL)
	{
		perror("open2");
		exit(EXIT_FAILURE);
	}
	// 4. 显示缓冲区的位置和类型，在一般应用中不需要，这里为了演示示例
	setvbuf(fp_src,buffer1,_IOLBF,128);
	do
	{
		prt("src_IO_read_ptr",fp_src->_IO_read_ptr);	// 源文件读位置
 		prt("_IO_read_end",fp_src->_IO_read_end);	
 		prt("_IO_read_base",fp_src->_IO_read_base);
	
 		prt("src_IO_write_ptr",fp_src->_IO_write_ptr);	// 源文件写位置
 		prt("_IO_write_base",fp_src->_IO_write_base);
 		prt("_IO_write_end",fp_src->_IO_write_end);
	
		prt("_IO_buf_base",fp_src->_IO_buf_base);	// 源文件缓冲区位置
		prt("_IO_buf_end",fp_src->_IO_buf_end);
		
		memset(buffer,'\0',10);
		i = fread(buffer,1,10,fp_src);	// 读
		fwrite(buffer,1,i,fp_des);	// 写
		
 		prt("des_IO_read_ptr",fp_des->_IO_read_ptr);	// 目标文件读位置
		prt("des_IO_write_ptr",fp_des->_IO_write_ptr);	// 目标文件写位置
	}while(i==10);
	fclose(fp_src);
	fclose(fp_des);
}
