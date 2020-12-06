# Linux文件属性管理   
## 1 读取文件的属性     
### 1.1 读取文件属性的函数   

```c
extern int stat(_const char* _restrict _file, struct stat* _reatrict _buf)
```

### 1.2 读取文件属性的程序      
```C
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])  {
	int i;
	struct stat buf;
	char *ptr;
	for (i = 1; i < argc; i++) 
	{
		printf("%s: ", argv[i]);
		if (lstat(argv[i], &buf) < 0) 
		{
			perror("lstat");
			continue;
		}
		if(S_ISREG(buf.st_mode))
			ptr = "regular file";                                     				// 判断是不是普通文件
		else if (S_ISDIR(buf.st_mode))	
			ptr = "directory file";                                   				// 判断是不是目录文件
		else if (S_ISCHR(buf.st_mode))	
			ptr = "character special file";                                  				// 判断是不是字符设备文件
		else if (S_ISBLK(buf.st_mode))	
			ptr = "block special file";
		else if (S_ISFIFO(buf.st_mode)) 
			ptr = "fifo file";

#ifdef	S_ISLNK
		else if (S_ISLNK(buf.st_mode))	
			ptr = "symbolic link";
#endif
#ifdef	S_ISSOCK
		else if (S_ISSOCK(buf.st_mode))	
			ptr = "socket";
#endif
		else	
			ptr = "** unknown mode **";

		printf("%s\n", ptr);
	}
	return 0;
}
```

## 2 修改文件权限操作    
### 2.1 函数说明    
在shell层面上，用户可以使用chmod命令来修改某个文件的权限，在应用编程中，如果要对文件的权限位进行修改，可以使用chmod()函数来实现。   
```C
extern int chmod(_const char* _file, _mode_t _mode);
// 第1个参数为要修改权限的文件名    
// 第2个参数为修改的权限描述
```

若要修改符号文件用lchmod函数，对已经打开的文件可以使用fchmod函数来修改权限      


## 3 修改系统的umask值   
### 3.1 函数说明    
在创建文件时，系统需要给文件一个默认的权限，根据系统的安全性，用户可以自己设置当前系统，使用touch目录创建一个普通的文件时的默认权限时0666-umask，如果使用mkdir命令创建一个目录，默认权限为0777-umask。在shell应用中，可以以下面的方式    

```shell
umask
```

在Linux的C应用编程中，umask将影响open、mkdir、create等函数创建文件的具体权限，获取当前系统的Umask值的函数时getmask，设置创建文件的掩码函数为umask     

```C
extern _mode_t umask(_mode_t  _mask);   
// 此函数执行成功，将设置系统的umask值为参数mask，并返回原来文件的权限umask值   
extern _mode_t getumask(void);   
```

### 3.2 程序示例   
```C
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc,char *argv)
{
	umask(0);
	if (creat("test01", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)
	{ 
		perror("creat");exit(EXIT_FAILURE);
	}
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("test02", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)
	{ 
		perror("creat");exit(EXIT_FAILURE);
	}
	return 0;
}
```

## 4 修改文件的其他属性     
### 4.1 修改文件的拥有者及组      
在shell中，使用chown和chgrp命令来修改 ，在Linux下C编程中，可以通过chown函数来修改文件的拥有者和拥有者的组       

### 4.2 用户名/组名与UID/GID的转换    
函数getpwuid和getpwnam可以通过用户UID或者用户名查看某特定用户的基本信息，这些信息在/etc/passwd文件中    

### 4.3 创建和删除硬连接    
1. 创建硬连接     
	- 在Linux下的C应用编程中，link函数用来创建硬连接文件。

```C
extern int link(_const char* _from, _const char* _to)
// 第1个参数为源文件的路径，即为哪个文件创建连接；   
// 第2个参数为硬连接文件的路径。这是需要保证源文件from是存在的，而目标文件to是不存在的，否则会引发错误。  
```

2. 删除硬连接   
	- 如果要执行删除某文件操作，则可以使用unlink函数，严格意义上说，unlink函数只是将该文件属性的硬连接自动减1，只是绝大多数的硬连接数为1，自减1后则为0，即删除    

3. 示例代码      

```c
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	unlink("hard_test");
	printf("befor create hard link\n");
	system("ls -l hard_test");                            // 在C语言中可以使用shell脚本的方法   
	if((link(argv[1],"hard_test"))==-1)			  // 创建连接，连接源是argv[1]，目标是hard_test  
	{
		perror("link");
		exit(EXIT_FAILURE);
	}
	printf("after create hard link for argv[1]\n");
	system("ls -l hard_test");
	if((unlink(argv[1]))==-1)
	{
		perror("unlink");
		exit(EXIT_FAILURE);
	}
	printf("after runlink the hard link\n");
	system("ls -l hard_test");
}

```


### 4.4 文件时间属性修改与时间处理     
文件的时间属性包括：最近访问时间、最近修改内容时间和最后修改属性时间，通过ls命令可以查看，在C语言编程中可以使用utime函数实现文件时间的修改        

```shell
ls  xxxx.c -l
```

修改特定文件的访问时间和修改内容时间，可以调用utime函数，相应的，在修改以上两个时间时，最近一次修改属性的时间也更新成了当前时间。     

```C
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
	time(&tm);
	buf.actime=tm-1000;
	buf.modtime=tm-5000;
	ptr=ctime(&tm);
	printf("now,the time is:%s\n",ptr);
	
	ptr=ctime(&buf.actime);
	printf("modify the %s access time is:%s\n",argv[1],ptr);

	ptr=ctime(&buf.modtime);
	printf("modify the %s content mod time is:%s\n",argv[1],ptr);
	utime(argv[1],&buf);                 // 最后这一步是进行修改的   
	printf("pls run ls -l to check\n");
}


```


<pre><font color="#8AE234"><b>yang@Yang-Ubuntu-1804LTS</b></font>:<font color="#729FCF"><b>13-LinuxFile</b></font>$ ./file_time file_time_att.c 
now,the time is:Sun Dec  6 14:34:18 2020

modify the file_time_att.c access time is:Sun Dec  6 14:17:38 2020

modify the file_time_att.c content mod time is:Sun Dec  6 13:10:58 2020

pls run ls -l to check
<font color="#8AE234"><b>yang@Yang-Ubuntu-1804LTS</b></font>:<font color="#729FCF"><b>13-LinuxFile</b></font>$ ls file_time_att.c -l
-rwxrwxrwx 1 root root 633 12月  6 13:10 <font color="#8AE234"><b>file_time_att.c</b></font>
</pre>














