# Linux下VFS虚拟文件系统     

## 1 VFS文件系统的简介   
Linux采用VFS来管理文件系统，VFS的全称是虚拟文件系统。它是异构文件系统智商的软件粘合层，因为VFS可以无缝地使用多个不同类型的文件系统。    
VFS最早是由Sun公司提出来用以实现NFS（网络文件系统）的。现在很多类UNIX系统采用VFS。     
通过VFS，就可以抽象地访问接口而隐蔽了底层文件系统和物理介质之间的差异性。   

## 2 ext2文件系统结构   
对于一个磁盘分区来说，在其被指定为相应文件系统后，整个分区被分为1024、2048和4096字节大小的块。根据块的使用不同，可以分为。    
1. 超级块：整个文件系统的第一块空间。包括整个文件系统的基本信息，如块大小、指向空间inode和数据块的指针等信息。    
2. Inode块：文件系统索引。它是文件系统的基本单元，是文件系统连接任何子目录和任何文件的桥梁。每个子目录和文件只有唯一的一个Inode块。      
3. 数据块：具体存放数据的位置区域。为了提高目录访问效率，Linux还提供了表达路径和Inode对应关系的dentry结构。它描述了路径信息并连接到节点Inode，它包括各种目录信息。还指向了Inode和超级块。    

- 就像一本书有封面、目录和正文一样，在文件系统中，     
	- 超级块相当于封面，可以从封面中，可以中封面中得知书的基本信息；   
	- Inode相当于目录，从目录中可以得知各个章节的位置；    
	- 数据块相当于书中的正文，记录着具体的信息。      
	- 每个文件由两部分构成：一部分是Inode，另一部分是数据块       

- 在Linux操作系统下，用户可以根据`ls -li`指令，通过Inode值，就能很快找到相对应的元数据      

```C
struct inode{
	struct hlist_node	i_hash;
	struct list_head	i_list;
	struct list_head i_sb_list;
	struct list_head i_dentry;
	unsigned long i_ino;	// 索引节点值
	atomic_t  	i_count;
	umode_t 	i_mode;		// 文件的类型访问权限  
	unsigned int  i_nlink;	//  该节点文件的硬链接数
	uid_t   i_uid;						// 文件的拥有者的ID
	gid_t  i_gid;						// 文件的拥有者的组ID 
	dev_t i_rdev;					// 次设备号
	loff_t i_size;						// 文件大小
	........
}
```

## 3 Linux系统下文件类型及属性   
### 3.1 Linux文件类型及权限    

- 文件属性存储结构体inode的成员变量i_mode存储着该文件的类型和权限。      
- 在应用中，习惯将这些二进制数每3位联合到一起组成6位八进制数。例如：八进制数0100777描述的是个常规文件，其权限位是所有用户都可以读写的执行，第一个0是八进制的意思，紧接着的10是文件类型是常规文件，中间的0是该文件没有，设置有效的用户ID，有效的用组ID以及粘贴位，777代表文件的访问权限，表示拥有者、同组其他用户以及所有其他用户均有可读、可写、可执行的权限。     

### 3.2 Linux文件类型     
- Linux系统的一个特点，一切都是文件，所有的资源都是通过文件映射出来进行管理的。文件的类型主要有：目录文件、字符设备文件、块设备文件、常规文件、管道文件、符号链接文件和套接字文件。      
	- 常规文件：ls -l    
	- 目录文件：ls -ld    
	- 字符设备文件：ls -l中显示c开头的   
	- 块设备文件：ls -l中显示b开头   
	- 符号链接文件：ls -l中显示l开头   
	- 套接字文件：ls -l中显示s开头   
	- 管道文件：ls -l中显示P开头       

### 3.3 文件权限修饰符   
文件的权限修饰符：setuid，setgid和sticky位。    
	- 如果文件的setuid被设置，则该文件被执行时，进程的有效用户ID被设置成该文件的所有者。即对系统其他文件的访问权限上升为当前文件的拥有者对该文件的访问权限    
	- 如果一个文件的setgid被设置，则该文件被执行时，进程的有效组ID被设置成该文件的所有者的组。    
	- sticky位使用不多，如果一个文件设置了sticky位，则系统将尽可能使该文件常驻内存     

### 3.4 文件访问的权限位     
Linux对文件实行完善的访问权限管理中，普通用户要读写某个文件，必须具备对该文件的读写权限，管理员通过chmod命令实现文件权限的修改      














