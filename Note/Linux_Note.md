# Linux教程
[toc]
## Linux用户信息存储的文件
- etc/passwd(7列):用户基本信息文件

  - 例:`root:x:0:0:5:/root:/bin/bash`
    - 1. root:用户名
      2. x:密码占位符
      3. 0:UID，用户身份证号，0为最高权限账号，>500为非系统账号，1000+是普通用户
      4. 0:GID，group组号，0为最高权限账号，>500为非系统账号，1000+是普通用户
      5. root:用户描述
      6. /root:家目录路径
      7. /bin/bash:登录shell

- /etc/shadow(8列):用户密码信息文件

  - 例`root:$6$……G1b1:19047:3:4:5:6:7:8`
    1. root:用户名
    2. 加密值:
       `$6$`开头的，表明是用SHA-512加密的
       `$1$`表明是用MD5加密的
       `$2$`是用Blowfish加密的
       `$5$`是用SHA-256加密的。
    3. 最后一次修改时间：1970年1月9日到今天过了多少天
    4. 最小间隔，第2次修改密码需要等待的时间
    5. 最大时间间隔，密码有效期，9999代表无限期
    6. 警告时间，提示修改密码的时间
    7. 不活动时间，表示用户没有登录活动，但账号仍能保持使用的有效最大天数
    8. 账号失效时间，过了该天数后账号失效
    9. 保留

- /etc/group：组信息文件

  - 例：`root:x:0:`
    1. root：组名
    2. x：组密码
    3. 0：组ID，0为最高权限账号，>500为非系统账号，1000+是普通用户
    4. 组成员
##  配置Linux编程环境

- **安装VMware-tools**：菜单中的虚拟机-->安装VMtools-->桌面出现光盘图标,双击打开-->将.tar.gz格式的压缩包放到家目录下的某个文件夹，然后解压-->用终端sudo权限执行VMware-install.pl文件-->`sudo ./VMware-intall.ol`-->输入管理员密码
- **创建其他普通账户，为其赋予sudo权限：** 
  - 创建新用户命令：`sudo adduser user1 user2`
  - 设置普通用户获取临时sudo权限：通过配置etc/sudoers来实现，先执行`sudo visudo`，在`root ALL = (ALL)ALL`下面手动添加`user1 ALL=(ALL)ALL`，ctrl+O保存，ctrl+X退出。
  - 三个ALL的含义
    - 第一个代表所有的主机名
    - 第二个代表user1可以以任意的用户身份运行后面的命令
    - 第三个是指user1可以使用sudo来执行所nvi 有的Shell命令
- **gnome桌面系统**
  - 安装命令：`sudo apt-get install gnome-session-fallback`
-  **手动配置网络**
  - //(新版貌似没有该文件)编辑网络配置文件：`sudo gedit /etc/network/interfaces`
    - auto eth0（自动识别并启动以太网0）
    - iface eth0 inet static或dhcp（获取ip地址的方式，自动ip或者静态ip）
    - address x.x.x.x（IP地址）
    - gateway y.y.y.y（网关）
    - netmask z.z.z.z（子网掩码）
  - 配置DNS：`gedit /etc/resolv.conf/`，nameserver后面就是域名服务的地址。
  - 重启网络命令：`sudo /etc/init.d/networking restart`
  - 重启DNS：`sudo /etc/init.d/resolvconf/restart`
  - 重启系统命令：`sudo shutdown -r now`
- 软件的安装与卸载：
  - 安装：`sudo apt-get install xxx`（vim, manpages, manpages-dev）
  - 卸载：`sudo apt-get remove xxx`
- man的函数关键字查找参数-k
  - `man -k function`

## shell命令

1. **alias**
   - `alias c='clear'`，给clear取临时别名c，服务器重启就没有了。永久设置参考[CSDN，ctrl+鼠标左键单击](https://blog.csdn.net/MANlidong/article/details/100085481)
   - `alias`，查看当前已经设置过的alias
   - `unalias c`，删除别名为c的命令
2. **cat（conCATenate——连接）**
- cat file -A，显示全部字符（包括换行符、制表符等）
3. cd（change directory）

   - `cd /mnt/hgfs/share`
4. **chmod（change mode）**
   - chmod 777 file
   - `chmod u+r,g+w,o+x file`
   - `chomd u=rw,go=rwx dir/ -R`，递归改变这个文件夹内所有文件的权限
5. chown（change owner）

   - `chown foo file`，把file的**所有者**改成foo
   - `chown :bar file`，把file的**所属组**改成bar
   - `chown foo :bar file`，把file的**所属组和所有者**改成……
6. clear

   - 清屏命令
7. **cp（copy）**
   - `cp file1 file2`，复制**文件**file1，并将其更名file2
   - `cp dir1 dir2 -r`，复制**目录**dir1，并将其更名dir2，复制目录时需要加-r或-R，表示递归复制
   - cp遇到**文件同名**时会覆盖掉原文件
8. **df -h**
- 查看当前文件系统的详细情况，-h 以MB和GB为单位显示
9. diff（篇幅很长，也许以后会用到，做个记录）P22
   - 对比两个文件或目录的异同，并将其加工成符合某种格式的文档——补丁文件
10. **dpkg**
    - 安装软件包，Linux的软件安装包后缀是.deb，如安装example.deb可以用以下命令
      - `sudo dpkg -i example.deb`
11. echo
    - 回显在屏幕上，如`echo "hello"`,如果需要支持转义则需要加上参数 -e，如`echo -e "hello\tworld"`
12. **find**
    - 文件查找命令
    - `find /opt/src -name "*.c"`——查找/opt/src下的.c文件
    - `find /opt/src -empty`——查找所有空文件和空目录
    - `find /opt/src -size n[cwbkMG]`——查找大小为n的文件，cwbkMG表示文件长度以字节计算
    - `find /opt/src -executable`——查找所有的可执行文件
    - `find /opt/src -mmin n`——查找n分钟之前修改过的文件
    - `find /opt/src -type [bcdpfls]`——查找某种类型的文件
    - `find /opt/src -uid n`——查找所有用户ID为n的文件

## GCC编译器的四大过程

- **预处理**(-E)：解释预处理指令，删除注释	**输出file.i**
- **编译**(-S)：最复杂的过程，生成某平台的汇编文件，平台类型由编译器决定，GCC是x86的汇编文件，ARM的交叉编译器是ARM格式的汇编文件。	**输出file.s**
- **汇编**(-c)：将汇编文件翻译成处理器能直接运行的指令，生成一个ELF格式的可重定位文件(relocatable)，重定位就是找出全局变量或函数真正定义的地址，而不是被extern修饰的变量或函数。 **输出file.o**
- **链接**(-lg -lgcc)：①链接库文件，-lc是链接C库，-lgcc是链接gcc内置库。②将所有ELF文件的段进行相同权限合并操作，形成一个ELF格式的可执行文件。**输出file**
  - ELF文件存放着多个不同的段
    - .text运行代码
    - .data 存放着已经初始化的全局变量和静态局部变量
    - .rodata 存放程序中的常量
    - .rel.text 存放着代码重定位信息
    - .symtab EFL格式文件中的符号表

## 内存管理

**内存的划分（readelf 文件名)**

- **栈内存**
  - 存储程序执行过程中的局部变量以及函数嵌套、调用的定位地址，栈的大小有个最大限度，这个限度一般是8MB，超过了这个值系统会报错栈溢出。

- **堆内存**
  - 堆和栈的最大区别在于堆是不设大小限制的。

- **数据段**
  
  - .bss：存放未初始化的静态数据，<!--静态数据是指：全局变量、static修饰的局部变量-->
  - .data：已经初始化的静态数据
  - .rodata：存放只读数据，即常量(read only)
- **代码段**
  
  - .text：存放用户程序代码
  - .init：存放系统给每一个可执行程序自动添加的**初始化**代码

- **不可访问区域**
## 结构体和共用体占用字节的计算

- Tips:虚拟内存和物理内存之间的映射是借助MMU完成的

- **结构体**的大小与cpu的位数有关，若为32位CPU时，CPU每次至少存取4字节的数据

  - 当变量大小＜4字节时,m值=该变量的长度
  - 当变量大小>=4字节时,m值按4字节处理

  ```c
  //示例1
  struct node
  {
  	short a;
  	double b;
  	char c;
  }x;
  ```

  上面结构体,m~a~=2、m~b~=4、m~c~=1，结构体大小为（double为8字节，a为2字节<4，按4字节处理，c为1字节<4，同理按4字节处理）8+4+4=16字节。

- **共用体**的大小取决于共用体的最大成员占用的字节数，若示例1是以共用体来定义的话，其大小就是8字节

## 函数

- 变参函数：例如：`int printf(const char *format , ...);`

  ![](./pic/%E5%8F%98%E5%8F%82%E5%87%BD%E6%95%B0.png)

  - 自主设计变参函数，实现参数值相加

  - ```c
    //需要用到的知识点:
    //1.va_list，字符指针的类型
    //2.va_start(p,format)，将p指向字符串format的首字符
    //3.va_arg(p,int)，将p回溯int个字节地址
    #include <stdio.h>
    #include <stdarg.h>
    #include <string.h>
    #define SIZE 50
    
    double sumup(const char *format, ...);
    
    int main(void)
    {
        short a = 1;
        float b = 1.2;
        char c = '\0';
        int d = 4;
        printf("%.2lf\n",sumup("#s#f#c#i",a,b,c,d));
        return 0;
    }
    
    double sumup(const char *format , ...)
    {
        va_list p;
        va_start(p,format);
        double ans = 0;
        char arg[SIZE]={0}; //数组初始化为0
        int arg_num = 0;
        for(int i = 0;format[i];++i)
        {
            if(format[i] == '#')
            {
                arg[arg_num++] = format[i+1]; 
            }
        }
        for(int i =0;arg[i];++i)
        {
            switch(arg[i])
            {
                case 'i':
                case 's':
                case 'c':
                    ans += va_arg(p,int);
                    break;
                case 'f':
                case 'd':
                    ans += va_arg(p,double);
                    break;
                default:
                    printf("format error!\n");
                    break;
            }
        }
        return ans;
    }
    ```

- 内联函数：static inline
- 回调函数：
```c
#include<stdio.h>

int Callback_1() // Callback Function 1
{
    printf("Hello, this is Callback_1 ");
    return 0;
}

int Callback_2() // Callback Function 2
{
    printf("Hello, this is Callback_2 ");
    return 0;
}

int Callback_3() // Callback Function 3
{
    printf("Hello, this is Callback_3 ");
    return 0;
}

int Handle(int (*Callback)())
{
    printf("Entering Handle Function. ");
    Callback();
    printf("Leaving Handle Function. ");
}

int main()
{
    printf("Entering Main Function. ");
    Handle(Callback_1);
    Handle(Callback_2);
    Handle(Callback_3);
    printf("Leaving Main Function. ");
    return 0;
}
```

## 结构体

- 结构体的3种初始化方式

```c
//若有结构体声明如下
struct book{
	char *name;
	int pages;
	float price;
};

//方式1:
struct book A = {"math",200,10.1};

//方式2:
struct book A = {
	.name = "math";
	.pages = 200;
	.price = 10.1;
};

//方式3:
struct book A;
A.name = "math";
A.pages = 200;
A.price = 10.1;
```

- 结构体的嵌套写法

```c
struct book{
	struct{
		char *animal;
		char *nature;
		char *human;
		char *future;
	}sort;//注意此处的sort是变量名
	int pages;
	float price;
};
```

- 结构体的字节对齐问题

```c
struct Node{
	int a;	//4Byte
	char b;	//1Byte
	short c;//2Byte
};
```

m值得概念：int型数据的地址必须至少是4的整数倍，这句话就意味着int型数据的m值为4。

m值关联着变量的存放位置，为了CPU的处理效率，系统会将变量以其m值的整数倍地址为起始点进行存放，结构体的m值取决于结构体内部最大变量的m值。

对于一个32位的cpu：

- 若变量尺寸小于4字节，那么变量的m值等于变量的长度

- 若变量尺寸大于或等于4字节，m值按4计算，如:double变量的m值为4

## 动态库与静态库

- 静态库

  ```
  gcc fun.c -c -o fun.o	//将各个.c文件编译成.o文件，若.h文件不在当前目录则需要在后面加-I ./头文件路径
  ...
  ar rcs libfun.a fun.o	//将fun.o放入静态库libfun.a
  gcc main.c -o main -L . -l fun
  ```

- 动态库

  ```
  gcc fun.c -c -fPIC -o fun.o	//将各个.c文件编译成.o文件
  ...
  gcc -fPIC -shared  fun.o -o libfun.so	//将fun.o添加到动态库
  gcc main.c -o main -I . -L . -l fun	//动态库生成的执行文件用./执行时需和库文件在同一目录下，否则需要修改环境变量来找到动态库
  ```

  ```
  export LD_LIBRARY_PATH=路径	//将路径设置为环境变量
  ```
## 文件IO
### 系统IO和文件IO的区别
- 文件IO属于库函数，系统IO属于系统函数
- 所有的文件操作遵循预读入换输出机制
- 数据从用户空间传递到内核空间时需要借助系统函数来完成数据传输，内核空间会将数据写入到物理设备上，
- 据中转会借助缓冲区，从而达到高效数据传输的目的

### 系统IO

-  文件描述符
   - #define STDIN_FILENO 0 //标准输入，对象：键盘
   - #define STDOUT_FILENO 1//标准输出，对象：屏幕
   - #define STDERR_FILENO 2 //标准出错，对象：屏幕
   - 前三个文件描述符被以上三个标准占用，所以用户自定义的文件描述符会从3开始
   - Linux下的文件描述符取值范围为0~1023，即1024个。
- open()
-  int **open**(const char *pathname, int flags)
   -  return
      -  成功：文件描述符
      -  失败：-1
   -  pathname：要打开的文件路径
   -  flags
      -  O_RDONLY
      -  O_WRONLY
      -  O_RDWR
      -  O_APPEND //以追加的方式打开文件
      -  O_CREAT, 新建的文件后面可以追加权限，如0777(八进制)
      -  O_TRUNC //truncate截断，删节
      -  O_EXCL //若使用O_CREAT选项且文件已经存在，则返回错误
      -  O_NOCTTY //若文件为终端，则终端不可以作为特定进程的控制终端
- close()
-  int **close**(int fd) //关闭文件描述符
   -  return
      -  成功：0
      -  失败：-1

- read()
-  ssize_t **read**(int fd, void *buf, size_t count)
   -  return
      -  成功：实际读到的字节数
      -  失败：-1
   -  fd：文件描述符
   -  buf：缓冲区
   -  count：读出的字节数

- write()
-  ssize_t **write**(int fd, const void*buf,size_t count)
   -  return
      -  成功：实际写入的字节数
      -  失败：-1
   -  fd：文件描述符
   -  buf：缓冲区
   -  count：写入的字节数
-  **Tips**：读/写函数的count只是一个愿望值，当实际读/写的字节数小于count时，会出现以下几种情形
   -  读操作时，文件剩余可读字节数不足count
      -  这种情况下一般需要将剩余的字节数读取完，利用ftell函数获取begin和end标志，写入end-begin个字节数，即剩余的字节数，详情见P
   -  读写操作期间，进程收到异步信号
- lseek()
- 原型：`off_t lseek(int fildes, off_t offset, int whence)`
- return
  - 成功：返回从文件开头开始以字节为单位测量的偏移量
  - 失败：-1
- od
- od -tc**x** filename 查看文件的16 进制表示形式
- od -tc**d** filename 查看文件的10进制表示形式
- dup&dup2
  - 原型:`int dup(int oldfd)` 
    -  return
        -  成功：新的文件描述符
        -  失败：-1
      
  -  功能:复制文件描述符oldfd为当前系统可用文件描述符的最小可用描述符，如当前已经分配了0,1,2描述符，那么调用dup(x)后返回4

  - 原型:`int dup2(int oldfd, int newfd)` 
    - return
      -  成功：新的文件描述符
      -  失败：-1
  - 功能:复制oldfd描述符为newfd，可以复写，例如:dup2(oldfd, STDIN_FILENO)，这样做之后标准输入的描述符就变成了oldfd，也就相当于是往标准输入写入的内容会传递给oldfd.

### 标准IO

- 三个标准文件

- stdin
- stdout
- stderr

- fopen()

- FILE *fopen(const char *path, const char *mode)
  - return
    - 成功：文件指针
    - 失败：NULL
  - path：要打开的文件路径
  - mode
    - r/w/rb/wb/r+/w+/a/a+

- fclose()

- int fclose(FILE *fp)
  - return
    - 成功：0
    - 失败：EOF
  - fp：即将要关闭的文件

- fgetc()

- fgetc(FILE *)，getc(FILE *)，getchar(void)
  - return
    - 成功：读到的字符
    - 失败：EOF

- fputc()

- fputc(int, FILE *)，putc(int, FILE *)，putchar(int)
  - return
    - 成功：写入的字符
    - 失败：EOF
  - int：需要写入的字符

- feof()&ferror()

- int feof(FILE *stream)
  - 成功：1，已到达文件尾部
- int ferror(FILE *stream)
  - 成功：1，遇到错误

- fgets()
- char *fgets(char *s, int size, FILE *stream)
- char *gets(char *s) //s：自定义缓冲区指针
  - 成功：自定义缓冲区指针s
  - 失败：NULL

- fputs()
- int fputs(const char *s, FILE *stream)
- int puts(const char *s) //将s打印到stdout
  - 成功：非负整数
  - 失败：EOF

- fread()
- size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
  - 成功：读取的数据块个数，等于nmemb
  - 失败：读取的数据块个数，小于nmemb或等于0
- fwrite()
- size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
  - return
    - 成功：写入的数据块个数，等于nmemb
    - 失败：写入的数据块个数，小于nmemb或等于0

- fseek()
- int fseek(FILE *stream, long offset, int whence)
  - return
    - 成功：0
    - 失败：-1
  - stream：文件流
  - offset：相对基准点的偏移量
  - whence：基准点
    - SEEK_SET：文件开头处
    - SEEK_CUR：当前位置
    - SEEK_END：文件末尾处

- ftell()
- long ftell(FILE *stream)
  - return
    - 成功：当前文件位置偏移量
    - 失败：-1

- rewind()
- void rewind(FILE *stream) //将当前位置偏移量设置到文件开头处

#### fd和fp的关系
-  FILE*中的内容包括文件描述符和缓冲区

```c
//fp转fd
int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    fp  = fopen("/home/super_bert/test.dat", "r");    /*得到文件指针*/
    if (fp == NULL)
    {
        perror("open file error.");
        exit(1);
    }
    else
    {
        printf("open file successfully...\n");
    }
    int fd;
    fd = fileno(fp);    /*文件指针转换为文件描述符*/
    if (-1 == fd)
    {
        perror("fp to fd error.");
    }
    else
    {
        printf("transform successfully...\n")
        exit(1);
    }
    return 0;
}

//fd转fp
int main(int argc, char *argv[])
{
    int  fd;
    fd = open("/home/super_bert/test.dat", O_CREAT|O_RDWR, 0666);    /*得到文件描述符*/
    if ( -1 == fd )
    {
        perror("open file error.");
        exit(1);
    }
    else
    {
        printf("open file successfully...\n");
    }
    FILE *fp = NULL;
    fp = fdopen(fd, "r");       /*文件描述符转换为文件指针*/
    if (NULL == fp)
    {
        perror("fd to fp error.");
    }
    else
    {
        printf("transform successfully...\n");
        exit(1);
    }
    return 0;
}
————————————————
版权声明：本文为CSDN博主「爱代码的呆子」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/luzhiweistudy/article/details/72633106
```

### 硬链接和软连接
#### 软连接命令
- `ln -s src dest`
- 需要注意的点：
  - 软连接文件的大小是源文件的路径字符串长度
  - 若需要查看软连接的**内容**(链接的源文件路径),需要用`readlink`命令，软连接文件内容无法被`cat`命令查看
  - 若创建软连接时使用相对路径，则移动软连接的文件位置后，链接文件将会失效。如:ln -S ./src dest
  - 软连接的权限是777并不代表链接的原文件也是777，也就是并不会发生穿透
#### 硬链接命令
- `ln src dest`
- 特点：
  - 硬链接函数实质上会创建一个dentry链接到inode
  - 硬链接的所有文件，内容会同步
#### 硬连接函数
- 原型：
  - `int link(const char *oldpath, const char *newpath);`
  - `int unlink(const char *pathname);`
```c
//用硬链接函数实现mv指令
int main(int argc, char **argv)
{
  link(argv[1], argv[2]);
  unlink(argv[1]);
}
```
- **注意**：unlink函数被调用后不会立即删除dentry，它会等所有打开该文件的进程都关闭后，系统才会挑时间释放dentry。**为什么要这么做?**，若程序还未来得及运行unlink时发生崩溃，那么本该被释放的dentry没有被释放，因此为了解决这个问题，unlink就有了如上机制，当打开文件后及时运行unlink函数，那么一旦程序崩溃或者文件正常关闭，unlink会在这个时机之后正常起作用，达到释放dentry的目的。
#### 隐式回收
- 指进程结束时，系统会自动关闭或释放那些本该被手动关闭或释放的文件或堆空间等等。

### 目录IO

| directory                |
| ------------------------ |
| ![](./pic/directory.png) |

- 查看目录文件权限:`ls -ld xxx`

| ls -ld               |
| -------------------- |
| ![](./pic/ls-ld.png) |


#### 目录IO函数索引<a id="dirFunIndex"></a>

| 查询man手册    | 跳转                             | 功能                 |
| -------------- | -------------------------------- | -------------------- |
| man 3 opendir  | <a href="#opendir">opendir</a>   | 打开目录             |
| man 3 closedir | <a href="#closedir">closedir</a> | 关闭目录             |
| man 3 readdir  | <a href="#readdir">readdir</a>   | 读取目录             |
| man 2 getcwd   | <a href="#getcwd">getcwd</a>     | 获取当前工作目录     |
| man 2 chdir    | <a href="#chdir">chdir</a>       | 修改当前进程工作目录 |
| man 2 fcntl    | <a href="#fcntl">fcntl</a>       | 设置/获取文件状态    |
| man d          | <a href="#d">d</a>               | d                    |

#### 目录IO代码索引<a id="dirCodeIndex"></a>

| 代码跳转                                   | 功能描述 |
| ------------------------------------------ | -------- |
| <a href="#customized_ls">customized_ls</a> | 自定义ls |
| <a href="#d">d</a>                         | d        |

**opendir**<a id="opendir"></a>

- 头文件：`include <sys/types.h> <dirent.h>`
- 原型：`DIR *opendir(const char *name)`
  - 功能：打开目录
  - return
    - 成功：目录指针
    - 失败：NULL
- <a href="#dirFunIndex">return index</a>

**closedir**<a id="closedir"></a>
- 头文件：`#include <sys/types.h> #include <dirent.h>`
- 原型：`int closedir(DIR *dirp)`
  - 功能：关闭目录
  - return
    - 成功：0
    - 失败：-1
- <a href="#dirFunIndex">return index</a>

**readdir**<a id="readdir"></a>
- 头文件：`#include <dirent.h>`
- 原型：`struct dirent *readdir(DIR *dirp)`
  - 功能：读取dirp指向的目录信息，目录信息通过函数返回
  - return
    - 成功：目录项结构体指针
    - 失败：NULL
  - dirp：目录项指针
```c
//目录项结构体
struct dirent
{
  ino_t d_ino;  //文件索引号
  off_t d_off;  //目录项偏移量
  unsigned short d_reclen;  //该目录项大小
  unsigned char d_type; //文件类型
  char d_name[256]; //文件名
}
```
- <a href="#dirFunIndex">return index</a>

**getcwd**<a id="getcwd"></a>
- 头文件：`#include <unistd.h>`
- 原型：`char *getcwd(char *buf, size_t size)`
  - 功能：获取当前进程的工作路径,将该路径存放至buf
  - return
    - 成功：当前进程工作路径
    - 失败：NULL
  - buf:用于存放路径的数组，size:buf的大小
- <a href="#dirFunIndex">return index</a>

**chdir**<a id="chdir"></a>
- 头文件：`#include <unistd.h>`
- 原型：`int chdir(const char *path)`
  - 功能:将当前进程的工作路径改变为path指定的路径
  - return
    - 成功：0
    - 失败：-1
  - buf:用于存放路径的数组，size:buf的大小
- <a href="#dirFunIndex">return index</a>

| ls详解            |
| ----------------- |
| ![](./pic/ls.png) |

<a id="customized_ls"></a>
| 自定义ls命令 | [customized_ls.c](../../Code/share/DIR_IO/customized_ls.c) |
| ------------ | :--------------------------------------------------------: |
| 运行结果     |            ![](./pic/customized_ls_result.png)             |
| 返回索引     |             <a href="#dirCodeIndex">return</a>             |

**fcntl**<a id="fcntl"></a>
- 头文件：`#include <fcntl.h>`
- 原型：`int fcntl(int fd, int cmd, ... /* arg */ )`

```c
#include <fcntl.h>
int flgs=fcntl (fd,F_GETFL);  //定义一个flgs接收文件描述符fd的属性值
flgs |= O_NONBLOCK; //给flgs非阻塞属性
fcntl (fd,F_SETFL, flgs); //将flag的属性给到文件描述符fd
//获取文件状态:F_GETFL
//设置文件状态:F_SETFL
```
- <a href="#dirFunIndex">return index</a>
#### 目录的rwx权限

| 目录的rwx权限          |
| ---------------------- |
| ![](./pic/dir_rwx.png) |

### 获取/修改文件信息
#### stat()和lstat()
- 原型：
  - `int stat(const char *restrict pathname,
                struct stat *restrict statbuf);`
  - `int lstat(const char *restrict pathname,
                struct stat *restrict statbuf);`
- 头文件：`#include <sys/stat.h>`
- return
  - 成功：0
  - 失败：-1
- 功能：查看文件属性,stat会拿到符号链接指向那个文件或目录的属性。不想穿透符号就用lstat.
```c
struct stat {
  dev_t     st_dev;         /* ID of device containing file */
  ino_t     st_ino;         /* Inode number */
  mode_t    st_mode;        /* File type and mode */
  nlink_t   st_nlink;       /* Number of hard links */
  uid_t     st_uid;         /* User ID of owner */
  gid_t     st_gid;         /* Group ID of owner */
  dev_t     st_rdev;        /* Device ID (if special file) */
  off_t     st_size;        /* Total size, in bytes */
  blksize_t st_blksize;     /* Block size for filesystem I/O */
  blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */
}
//用法示例
int main(int argc, char *argv[])
{
  struct stat buf;
  int ret = stat(argv[1], &buf);
  if(ret==-1)
    return -1;
  printf("file size=%d\n",buf.st_size);
}
//判断文件类型(宏，返回bool值)
S_ISREG(m)  //is it a regular file?(普通文件)
S_ISDIR(m)  //directory?(目录文件)
S_ISCHR(m)  //character device?(字符设备)
S_ISBLK(m)  //block device?(块设备)
S_ISFIFO(m) //FIFO (named pipe)?(管道)
S_ISLNK(m)  //symbolic link?  (Not in POSIX.1-1996.)(链接文件)
S_ISSOCK(m) //socket?  (Not in POSIX.1-1996.)(套接字文件)
//用法示例
stat(pathname, &sb);
if (S_ISREG(sb.st_mode)) {
    /* Handle regular file 对文件的处理操作*/
}
/* 注意：stat会穿透符号链接，而lstat不会，在校验链接文件的类型时需要使用lstat才能查找链接文件的类型，否则会穿透到原文件，即检测的是原文件的类型 */

```
#### truncate()截断
- 原型：`int truncate(const char *path, off_t length)`
- return
  - 成功：0
  - 失败：-1
- 功能：将path文件截断为length大小(可扩展)

#### access()获取文件存储权限
- 原型：`int access(const char *path, int amode)`
- return
  - 成功：0
  - 失败：-1
- 功能：检查path文件是否具有amode权限
- amode：R_OK, W_OK, X_OK
```c
#include <unistd.h>
int main(int argc, char **argv)
{
  if((access(argv[1],W_OK)==0))
    putchar('w');
    return 0;
}
```
#### chmod()修改文件访问权限
- `int chmod(const char *pathname, mode_t mode);`
- mod:八进制权限数

## 开发板操作
### tftp传输文件

- -g表示下载文件(get)
  -p表示上传文件(put)
  -l表示本地文件名(local file)
  -r表示远程主机的文件名(remote file)

- 例：要从远程主机192.168.1.2上下载embedexpert，则应输入命令:`tftp -g -r embedexpert 192.168.1.2`
### 显示bmp图片
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

void displayBmp(char *picName, int setx, int sety)
{
    int lcdFd = open("/dev/fd0", O_RDWR); //打开lcd文件
    if (lcdFd == -1)
    {
        printf("open lcd error.\n");
        return -1;
    }
    struct fb_var_screeninfo var;                                                     //定义可变参数结构体var
    ioctl(lcdFd, FBIOGET_VSCREENINFO, &var);                                          //将lcd的屏幕参数存入到var
    int lcd_w = var.xres;                                                             //获取屏幕宽度,单位：字节
    int lcd_h = var.yres;                                                             //获取屏幕高度,单位：字节
    int lcd_size = lcd_h * lcd_w * (var.bits_per_pixel / 8);                          //整块屏幕的字节数大小,单位：字节
    char lcdBuf[lcd_size];                                                            //定义lcdBuf
    int *lcdmem = mmap(NULL, lcd_size, PORT_READ | PORT_WRITE, MAP_SHARED, lcdFd, 0); // lcd内存映射
    //------------------------------------[第一部分↑]-------------------------------------
    // 1.打开lcd
    // 2.获取lcd的长，宽,单位为像素
    // 3.计算lcdj总字节数(用于申请lcd缓冲和共享内存),计算方法：长*宽*每像素所占位数/8
    // 4.申请共享内存(mmap)
    // tips:lcd缓冲区用于像素对齐(RGB->ARGB)，共享内存用于显示图片

    int bmpFd = open(picName, O_RDWR);
    if (bmpFd == -1)
    {
        printf("open %s error.\n", picName);
        return -1;
    }
    char bmpHeadInfo[54]; //用于存放bmp头文件信息
    read(bmpFd, bmpHeadInfo, 54);
    // int bmp_w = bmpHeadInfo[18] | bmpHeadInfo[19] <<8 |bmpHeadInfo[20] << 16 | bmpHeadInfo[21] << 24;
    // int bmp_h = bmpHeadInfo[22] | bmpHeadInfo[23] <<8 |bmpHeadInfo[24] << 16 | bmpHeadInfo[25] << 24;
    // int bmp_bit = bmpHeadInfo[28] | bmpHeadInfo[29] << 8; //获取图片位数,用于定义bmpBuf的大小
    int bmp_bit, bmp_byte, bmp_w, bmp_h;
    memcpy(&bmp_bit, bmpHeadInfo + 28, 2);
    memcpy(&bmp_w, bmpHeadInfo + 18, 4); //获取图片宽度,单位：像素
    memcpy(&bmp_h, bmpHeadInfo + 22, 4); //获取图片高度,单位：像素
    bmp_byte = bmp_bit / 8;
    int bmp_complete = (4 - bmp_w * bmp_byte % 4) % 4; // bmp行补齐的字节数
    int bmp_line = bmp_w * bmp_byte + bmp_complete;    // bmp行字节数 = 实际行字节数 + 补齐字节数
    char bmpBuf[bmp_line * bmp_h];                     //定义bmpBuf
    //------------------------------------[第二部分↑]-------------------------------------
    // 1.打开bmp
    // 2.获取bmp的位数，长，宽(bmp_bit,bmp_w,bmp_h)
    // 3.计算每个像素所占字节数(bmp_byte)
    // 4.计算行补齐字节数(bmp_complete)
    // 5.计算行字节数(bmp_line)
    // 6.定义bmpbuf

    int x, y;
    for (y = 0; y < lcd_h && y < bmp_h; y++)
    {
        for (x = 0; x < lcd_w && x < bmp_w; x++)
        {
            lcdBuf[0 + var.bits_per_pixel / 8 * (x + y * lcd_w)] = bmpBuf[0 + bmp_byte * (x + (bmp_h - 1 - y) * bmp_w)];
            lcdBuf[1 + var.bits_per_pixel / 8 * (x + y * lcd_w)] = bmpBuf[1 + bmp_byte * (x + (bmp_h - 1 - y) * bmp_w)];
            lcdBuf[2 + var.bits_per_pixel / 8 * (x + y * lcd_w)] = bmpBuf[2 + bmp_byte * (x + (bmp_h - 1 - y) * bmp_w)];
            lcdBuf[3 + var.bits_per_pixel / 8 * (x + y * lcd_w)] = 0; //透明度
        }
    }
    //------------------------------------[第三部分↑]-------------------------------------
    // RGB->ARGB，bmpBuf转到lcdBuf，并垂直翻转

    int draw_w = bmp_w < lcd_w - setx ? bmp_w : lcd_w - setx;
    int draw_h = bmp_h < lcd_h - sety ? bmp_h : lcd_h - sety;
    for (y = 0; y < bmp_h; y++)
    {
        memcpy(lcdmem + setx + (sety + y) * lcd_w, &lcdBuf[var.bits_per_pixel / 8 * lcd_w * y], draw_w * var.bits_per_pixel / 8);
    }
    //------------------------------------[第四部分↑]-------------------------------------
    // 将lcdBuf的内容输出到屏幕上，如果图片超出显示范围，则截除超出范围的像素点
    munmap(lcdmem, lcd_size);
    close(lcdFd);
    close(bmpFd);
    //------------------------------------[第五部分↑]-------------------------------------
    //关闭所有文件并释放共享内存
}
```
### 获取屏幕坐标

## gdb调试
`gcc main.c -o main` >> `gdb main`
| 命令                 | 简写 | 作用                                   |
| -------------------- | ---- | -------------------------------------- |
| help                 | h    | 列出命令类                             |
| help class           |      | 查看某一类型具体命令                   |
| list                 | l    | 查看代码，可跟行号和函数名             |
| quit                 | q    | 退出gdb调试                            |
| run                  | r    | 全速运行程序                           |
| start                |      | 单步执行，运行程序，停在第一行执行语句 |
| next                 | n    | 全速运行程序                           |
| backtrace            | bt   | 查看函数调用的栈帧和层级关系           |
| frame                | f    | 切换函数的栈帧                         |
| info                 | i    | 查看gdb内部局部变量的数值              |
| finish               |      | 结束当前函数                           |
| set                  |      | 设置变量的值，set var n = 100          |
| set args a b c       |      | 设置外部传参，set args a b c           |
| run argv[1] ...      |      | 传入外部参数并运行                     |
| print                | p    | 打印变量和地址                         |
| break                | b    | 设置断点，可根据行号和函数名           |
| delete               | d    | 删除断点                               |
| display              |      | 设置观察变量                           |
| undisplay            |      | 取消观察变量                           |
| continue             |      | 运行到下一个断点                       |
| stop only if arg = n |      | 条件断点(如果arg = n)                  |
| ptype arg            |      | 查看变量类型                           |

## Linux系统编程
### 进程管理
#### 进程管理相关指令
- `pstree`,(print system tree)
- `ps -ef`静态查看进程状态
- `ps ajx` & `ps aux`
- `top`动态查看进程状态
#### 进程常用函数
| 原型                | 返回成功                        | 返回失败 | 功能                   |
| ------------------- | ------------------------------- | -------- | ---------------------- |
| pid_t fork(void)    | 父进程返回子进程号，子进程返回0 | -1       | 创建子进程             |
| pid_t getpid(void)  | 当前进程号                      | 无       | 获取当前进程id         |
| pid_t getppid(void) | 当前进程的父进程号              | 无       | 获取当前进程的父进程id |
| uid_t getgid(void)  | 当前进程的组ID号                | 无       | 获取当前进程的组id     |
| uid_t getuid(void)  | 当前进程的用户ID号              | 无       | 获取当前进程的用户id   |

#### 创建多进程模板
| 进程扇 | [process_fan.c](../../Code/03_SystemPrograming/05_process/process_fan.c) |
| ------ | ------------------------------------------------------------------------ |
| -      |                                                                          |

#### 父子进程在fork后有哪些相同，哪些不同？
- 相同：全局变量，.data，.text，栈，堆，环境变量，用户ID，宿主目录，进程工作目录，信号处理方式...
- 不同：进程ID，fork返回值，父进程ID，进程运行时间，闹钟，未决信号集
- 父子进程共享：文件描述符表，mmap建立的映射区
- 重点：父子进程间遵循**读时共享，写时复制** 的原则，这样设计可以有效的节省内存开销。

#### wait | waitpid
| 原型                                                | 返回成功           | 返回失败 | 功能                    |
| --------------------------------------------------- | ------------------ | -------- | ----------------------- |
| pid_t wait(int *wstatus)                            | 结束的子进程ID     | -1       | 等待子进程结束          |
| pid_t waitpid(pid_t pid, int *wstatus, int options) | 结束的指定子进程ID | -1       | 等待pid指定的子进程结束 |
| -                                                   | -                  | -        | -                       |

#### wait函数的宏

| wait宏                     |
| -------------------------- |
| ![](./pic/wait_define.png) |

### 管道
- 实现原理：借助环形队列机制，使用内核缓冲区实现。
- 特点
    - 管道内的数据只能读取一次
    - 数据在管道中只能单向流动
    - 伪文件(内核缓冲区)
    - 半双工通信
- 查看管道大小
  - `ulimit -a`命令
  - fpathconf函数

#### 匿名管道(支持多写一读)
| 原型                | 返回成功 | 返回失败 | 功能             |
| ------------------- | -------- | -------- | ---------------- |
| int pipe(int fd[2]) | 0        | -1       | fd[0]读，fd[1]写 |
| -                   | -        | -        | -                |
```c
//利用父子进程实现ls|wc -l命令
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int fd[2];
    int ret = pipe(fd);
    if(ret==-1)
    {
        perror("pipe error.");
        exit(1);
    }
    pid_t pid;
    pid = fork();
    if(pid==-1)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid > 0)
    {
        close(fd[1]);//关闭写端
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
        perror("execlp wc error");
    }
    else if(pid==0)
    {
        close(fd[0]);//关闭读端
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
        perror("execlp error");
    }
    return 0;
}


//利用兄弟进程实现ls|wc -l
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd[2], i;
    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe error.");
        exit(1);
    }
    pid_t pid;
    for (i = 0; i < 2; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork error");
            exit(1);
        } else if (pid == 0) {
            break;
        }
    }
    if (2 == i) {   //父进程
        close(fd[0]);
        close(fd[1]);
        wait(NULL);
        wait(NULL);
    }else if (0 == i) { //兄进程
        close(fd[1]);  //关闭写端
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc error");
    } else if (1 == i) {    //弟进程
        close(fd[0]);  //关闭读端
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
        perror("execlp error");
    }
    return 0;
}

```

#### 有名管道
- **注意:fifo文件只能在linux中创建，不能在共享文件夹中创建**
- 函数创建fifo：

| 头文件                | 原型                                      |
| --------------------- | ----------------------------------------- |
| #include <sys/stat.h> | int mkfifo(const char *path, mode_t mode) |
| -                     | -                                         |

- 命令创建fifo：`mkfifo`
```c
//读端
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>   //mkfifo

int main(int argc, char **argv)
{
    if(argc!=2)
    {
        printf("input like this:./a.out fifo_file.\n");
        exit(-1);
    }
    if(access(argv[1],F_OK)){
        if(-1 == mkfifo(argv[1],0644)){
            perror("fifo");
            exit(-1);
        }
    }
    int fd = open(argv[1],O_RDONLY);
    if(fd==-1){
        perror("open");
        exit(-1);
    }
    int i=0,len;
    char buf[4096];
    while(1)
    {
        len = read(fd,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,len);
        sleep(1);
    }
    return 0;
}

//写端
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>   //mkfifo

int main(int argc, char **argv)
{
    if(argc!=2)
    {
        printf("input like this:./a.out fifo_file.\n");
        exit(-1);
    }
    if(access(argv[1],F_OK)){
        if(-1 == mkfifo(argv[1],0644)){
            perror("fifo");
            exit(-1);
        }
    }
    int fd = open(argv[1],O_WRONLY);
    if(fd==-1){
        perror("open");
        exit(-1);
    }
    int i=0;
    char buf[4096];
    while(1)
    {
        sprintf(buf,"%d is coming...\n",i++);
        write(fd,buf,strlen(buf));
        sleep(1);
    }
    return 0;
}
```

### Signal

| signal                     |
| -------------------------- |
| ![](./pic/signal_list.png) |

#### The way of sendding the signal
- Kernel sends the signal and process it.
- The usage of kill
  - `kill -s SIGINT 1234`,1234:process id
  - `kill -9 1234`
  - `killall filename`,the 15th signal
  
#### kill and signal

| head file           | model                                           |
| ------------------- | ----------------------------------------------- |
| #include <signal.h> | int kill(pid_t pid, int sig)                    |
| #include <signal.h> | void (*signal(int sig, void (*func)(int)))(int) |
| #include <unistd.h> | int pause(void);                                |


The SIG_IGN won't be worked for `SIGKILL` and `SIGSTOP`

#### Signal set

| head file           | model                                                                           |
| ------------------- | ------------------------------------------------------------------------------- |
| #include <signal.h> | int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset) |

- Signalset option
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);

#### Sigqueue and sigaction
![](./pic/sigqueue_outline.png)
```c
//sigqueue 发送信号端
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv)
{
    pid_t pid;
    union sigval info;
    info.sival_int = 999;
    printf("input pid:");
    scanf("%d", &pid);
    getchar();
    sigqueue(pid, SIGINT, info);
    return 0;
}

//sigaction 接收信号端
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void action_fun(int data, siginfo_t *info, void *etc)//定义复杂响应函数
{
    printf("data = %d\n", info->si_status);
}

int main(int argc, char **argv)
{
    printf("pid = %d\n",getpid());
    struct sigaction ac;
    bzero(&ac, sizeof(ac));
    ac.sa_sigaction = action_fun;
    ac.sa_flags = SA_SIGINFO;//如果标志位设置为SA_SIGINFO，则信号会响应复杂型的函数
    sigaction(SIGINT, &ac, NULL);
    pause();
    return 0;
}
```
TIPS:
- 信号的阻塞掩码会被继承给子进程
- 挂起的信号不会继承给子进程
- 不同的非实时信号会相互嵌套，但是已经在响应的信号不会嵌套
- 对于非实时信号而言，挂起的信号不会重复，但是对实时信号而言，挂起的信号可以重复
- 实时信号有响应优先级，信号越大响应优先级越高，非实时信号无响应优先级，且可能被丢失.

### IPC
- `ipcs -a`,check the all ipc objections of system
- `ipcs -q`,check the message queues
- `ipcs -m`,check the shared memory
- `ipcs -s`,check the semaphore arrays

#### Shared memory
- get key token
  - Discription:It is used to distinguish communication group

| head file            | model                                         |
| -------------------- | --------------------------------------------- |
| #include <sys/ipc.h> | key_t ftok(const char *pathname, int proj_id) |
  
- get shared memory id

| shmget                |
| --------------------- |
| ![](./pic/shmget.png) |

- attach and detach shared memory

| shmat                |
| -------------------- |
| ![](./pic/shmat.png) |

- delete shared memory
  - via command
    - `ipcrm -M key`
    - `ipcrm -m shmid`

  
  - via function

| shmctl                |
| --------------------- |
| ![](./pic/shmctl.png) |

- Example
```c
//Please run shmsnd first and then run the shmrcv
//shmsnd.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_SIZE 1024

int main(void)
{
    int shmid = shmget(ftok(".", 1), SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shm error");
        exit(-1);
    }
    char *shm_p = shmat(shmid, NULL, 0); // 0代表以共享内存的访问权限为可读可写
    fgets(shm_p, SHM_SIZE, stdin);
    return 0;
}
//shmrcv.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_SIZE 1024

int main(void)
{
    int shmid = shmget(ftok(".", 1), SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shm error");
        exit(-1);
    }
    char *shm_p = shmat(shmid, NULL, 0); // 0代表以共享内存的访问权限为可读可写
    printf("%s",shm_p);
    shmdt(shm_p);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
```

#### Message queue
- get message queue id

| msgget                |
| --------------------- |
| ![](./pic/msgget.png) |

- send and receive message

| msgget                |
| --------------------- |
| ![](./pic/msgsnd.png) |

- delete the message queue

| msgctl                |
| --------------------- |
| ![](./pic/msgctl.png) |

- Example
```c
//msgsnd.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MSG_SIZE 50

struct msgbuf
{
    long mtype;
    char mtext[MSG_SIZE];
};

int main(void)
{
    int key = ftok(".", 1);
    int msgid = msgget(key, IPC_CREAT | 0666);
    struct msgbuf info;
    info.mtype = 1;
    while (1)
    {
        printf("send msg:");
        fgets(info.mtext,MSG_SIZE, stdin);
        msgsnd(msgid, &info, sizeof(info), 0);
        if (strncmp(info.mtext, "quit", 4) == 0)
            break;
    }
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
//msgrcv.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MSG_SIZE 50

struct msgbuf
{
    long mtype;
    char mtext[MSG_SIZE];
};

int main(void)
{
    int key = ftok(".", 1);
    int msgid = msgget(key, IPC_CREAT | 0666);
    struct msgbuf info;
    bzero(&info, sizeof(info));
    while (1)
    {
        msgrcv(msgid, &info, sizeof(info), 1, 0);
        if (strncmp(info.mtext, "quit", 4) == 0)
            break;
        printf("%s", info.mtext);
    }
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
```

#### Semaphore array(system V)
- get semaphore id

| semget                |
| --------------------- |
| ![](./pic/semget.png) |

- semaphore control

| semctl                |
| --------------------- |
| ![](./pic/semctl.png) |
- 若semctl的cmd值为SETVAL，则它的第四个参数应该为如下的联合体类型
```c
union semun {
    int val;			/* value for SETVAL */
    struct semid_ds *buf;	/* buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;	/* array for GETALL, SETALL */
};
```

- semaphore option

| semop                |
| -------------------- |
| ![](./pic/semop.png) |
```c
struct sembuf
{
  unsigned short int sem_num;	/* semaphore number */
  short int sem_op;		/* semaphore operation */
  short int sem_flg;		/* operation flag */
};
```

- Example
[sem.h](../../Code/share/ISP/sem.h) 
[sem.c](../../Code/share/ISP/sem.c)
[semsnd.c](../../Code/share/ISP/semsnd.c) 
[semrcv.c](../../Code/share/ISP/semrcv.c) 
```shell
#process 1
make semsnd semrcv
./semsnd
#process 2
./semrcv
```
#### POSIX有名信号量
- 与系统V信号量的区别
  - 相同：都是为了实现进程同步
  - 不同：系统V信号量存放在内核，具有多个信号量同时操作的原子性，POSIX有名信号量存放于`/dev/shm`中，只具有对单个信号量操作的原子性


| sem_open                |
| ----------------------- |
| ![](./pic/sem_open.png) |


| p/v option of posix sem |
| ----------------------- |
| ![](./pic/sem_pv.png)   |

| delete the posix sem      |
| ------------------------- |
| ![](./pic/sem_delete.png) |

- Example
[p_sem.h](../../Code/share/ISP/p_sem.h) 
[p_semsnd.c](../../Code/share/ISP/p_semsnd.c)
[p_semrcv.c](../../Code/share/ISP/p_semrcv.c) 

### Thread

| pthread creat                |
| ---------------------------- |
| ![](./pic/pthread_creat.png) |


| pthread exit                |
| --------------------------- |
| ![](./pic/pthread_exit.png) |

| pthread join                |
| --------------------------- |
| ![](./pic/pthread_join.png) |


| pthread attribute           |
| --------------------------- |
| ![](./pic/pthread_attr.png) |


| pthread set detach state                   |
| ------------------------------------------ |
| ![](./pic/pthread_attr_setdetachstate.png) |

- Example

| [pthread_detach_test.c](../../Code/03system_programing/07_thread/pthread_detach_test.c) |
| --------------------------------------------------------------------------------------- |
| 功能：分离属性测试                                                                      |


- Tips:
  - `pthread_exit(NULL)`的NULL就是线程的例程函数(routine)的返回值
  - 分离属性有两种设置方法：
    - 1.在父线程中设置`pthread_join()`
    - 2.在当前线程中设置`pthread_detach(pthread_self())`,`pthread_self()`可以获取当前线程的tid


| pthread set inherit schedual                |
| ------------------------------------------- |
| ![](./pic/pthread_attr_setinheritsched.png) |

| pthread set schedual policy                |
| ------------------------------------------ |
| ![](./pic/pthread_attr_setschedpolicy.png) |

| pthread set schedual paramter(范围/参数/界限) |
| --------------------------------------------- |
| ![](./pic/pthread_attr_setschedparam.png)     |

```c
struct sched_param
{
    int sched_priority; /* Scheduling priority */
};
```

- Example

| [pthread_schedual_policy_test.c](../../Code/share/thread/pthread_schedpolicy_test.c) |
| ------------------------------------------------------------------------------------ |
| 已弃用 kernel 5.15，功能：测试FIFO和OTHER的线程优先级                                |

#### POSIX无名信号量

| posix anonymous semaphore |
| ------------------------- |
| ![](./pic/sem_init.png)   |

- Example

| POSIX匿名信号量 | [sem_anonymous.c](../../Code/03system_programing/07_thread/sem_anonymous.c) |
| --------------- | --------------------------------------------------------------------------- |
| 功能            | 主线程写，子线程读出内容和字节数                                            |
#### 互斥锁与读写锁
- `pthread_mutex_t`：互斥锁变量类型

| head file            | model                                                                                                    | function |
| -------------------- | -------------------------------------------------------------------------------------------------------- | -------- |
| #include <pthread.h> | `int` pthread_mutex_lock(`pthread_mutex_t` *mutex)                                                       | 上锁     |
| #include <pthread.h> | `int` pthread_mutex_unlock(`pthread_mutex_t` *mutex)                                                     | 解锁     |
| #include <pthread.h> | `int` pthread_mutex_init(`pthread_mutex_t` *restrict mutex, `const pthread_mutexattr_t` *restrict attr); | 初始化   |
       
      
- Example

| 互斥锁   | [pthread_mutex_lock.c](../../Code/share/thread/pthread_mutex_lock.c) |
| -------- | -------------------------------------------------------------------- |
| 运行结果 | ![](./pic/mutex_result.png)                                          |
| 功能     | 互斥锁会使一个线程的工作执行完成后再完成另一个线程的工作             |
       

| 读写锁   | [pthread_rwlock.c](../../Code/share/thread/pthread_rwlock.c) |
| -------- | ------------------------------------------------------------ |
| 运行结果 | ![](./pic/rwlock_result.png)                                 |
| 功能     | 写锁的结果和互斥锁一样，读锁结果如上                         |

| pthread_cancel                |
| ----------------------------- |
| ![](./pic/pthread_cancel.png) |

| pthread_cancelstate                |
| ---------------------------------- |
| ![](./pic/pthread_cancelstate.png) |

| cancel的取消点                     |
| ---------------------------------- |
| ![](./pic/pthread_cancelpoint.png) |

#### 取消例程函数

- Example

| 取消函数 | [ptread_cancel.c](../../Code/share/thread/pthread_cancel.c) |
| -------- | ----------------------------------------------------------- |
| 运行结果 | ![](./pic/cancel_result.png)                                |
| 功能     | 取消一个线程的例程函数                                      |

| pthread_cleanup                |
| ------------------------------ |
| ![](./pic/pthread_cleanup.png) |


- Example

| 例程的压栈和弹栈 | [ptread_cleanup.c](../../Code/share/thread/pthread_cleanup.c) |
| ---------------- | ------------------------------------------------------------- |
| 运行结果         | ![](./pic/cleanup_result.png)                                 |
| 功能             | 解决取消函数导致的死锁问题                                    |

| pthread_cond_init                |
| -------------------------------- |
| ![](./pic/pthread_cond_init.png) |

| pthread_cond_wait                |
| -------------------------------- |
| ![](./pic/pthread_cond_wait.png) |

| pthread_cond_broadcast                |
| ------------------------------------- |
| ![](./pic/pthread_cond_broadcast.png) |

#### 条件变量
- Example

| 条件变量 | [pthread_condition.c](../../Code/share/thread/pthread_condition.c) |
| -------- | ------------------------------------------------------------------ |
| 运行结果 | ![](./pic/cond_result.png)                                         |
| 功能     | 条件锁的应用                                                       |

#### 线程池

| thread_pool                |
| -------------------------- |
| ![](./pic/thread_pool.png) |

| 线程池 | [thread_pool.c](../../Code/share/thread/thread_pool.c) |
| ------ | ------------------------------------------------------ |
| -      |                                                        |

## Linux网络编程
### 基础概念
IP地址，可以在网络环境中，唯一标识一台主机。
端口号：可以在网络的一台主机上，唯一标识一个进程。
ip地址+端口号：可以在网络环境中，唯一标识一个进程。

- UDP协议
  - 16位：源端口号。
  - 16位：目的端口号。
  - 2^16 = 65536
- TCP协议
  - 16位，源端口号
  - 16位：目的端口号。
  - 32序号：
  - 32确认序号。
  - 6个标志位。
  - 16位窗口大小。2^16=65536
### TCP通讯时序
| TCP通讯时序                |
| -------------------------- |
| ![](./pic/tcp_connect.png) |
  - 三次握手(建立连接)
    1. 客户端发送一个带SYN标志的TCP报文到服务器。这是三次握手过程中的段1。
    2. 服务器端回应客户端，是三次握手中的第2个报文段，同时带ACK标志和SYN标志。它表示对刚才客户端SYN的回应；同时又发送SYN给客户端，询问客户端是否准备好进行数据通讯。
    3. 客户必须再次回应服务器端一个ACK报文，这是报文段3。
  - 四次挥手(断开连接)
    1. 客户端发出段7，FIN位表示关闭连接的请求。
    2. 服务器发出段8，应答客户端的关闭连接请求。
    3. 服务器发出段9，其中也包含FIN位，向客户端发送关闭连接请求。
    4. 客户端发出段10，应答服务器的关闭连接请求。
### c/s模型和b/s模型
- client server
  - 优点：缓存大，协议选择灵活，速度快
  - 缺点：安全性、无法跨平台
- browser server
  - 优点：安全、跨平台、开发工作量小
  - 缺点：不能缓存大量数据、需要严格遵守http协议
  
### socket套接字
socket的本质是内核提供的两个缓冲区
#### 网络字节序
大端存储(网络)：低地址存高字节，高地址存低字节
小端存储(本机)：高地址存高字节，低地址存低字节

| 函数  | 转换       | 位数         |
| ----- | ---------- | ------------ |
| htonl | 本地转网络 | 32位(ip地址) |
| htons | 本地转网络 | 16位(端口号) |
| ntohl | 网络转本地 | 32位(ip地址) |
| ntohs | 网络转本地 | 16位(端口号) |

| #include <arpa/inet.h> | int inet_pton(int af, const char *src, void *dst)         |
| ---------------------- | --------------------------------------------------------- |
| af                     | 网络协议:AF_INET、AF_INET6                                |
| src                    | 点分式字符ip地址                                          |
| dst                    | 网络字节序ip地址                                          |
| 返回值                 | 成功：1  失败：-1  异常:说明src指向的不是一个有效的ip地址 |
| 功能                   | 点分式ip转网络字节序ip                                    |

| #include <arpa/inet.h> | const char *inet_ntop(int af, const void *src, char *dst, socklen_t size) |
| ---------------------- | ------------------------------------------------------------------------- |
| af                     | 网络协议:AF_INET、AF_INET6                                                |
| src                    | 网络字节序ip地址                                                          |
| dst                    | 点分式字符ip地址                                                          |
| size                   | dst的大小                                                                 |
| 返回值                 | 成功：dst  失败：NULL                                                     |
| 功能                   | 网络字节序ip转点分式ip                                                    |

#### socket函数

| socket                |
| --------------------- |
| ![](./pic/socket.png) |

| bind                |
| ------------------- |
| ![](./pic/bind.png) |

```c
struct sockaddr_in
{
    sa_family_t sin_family;  /* address family: AF_INET */
    in_port_t sin_port;      /* port in network byte order */
    struct in_addr sin_addr; /* internet address */
};

struct sockaddr
{
    sa_family_t sa_family;
    char sa_data[14];
}

/* Internet address */
struct in_addr
{
    uint32_t s_addr; /* address in network byte order */
};
```
| struct_sockaddr                |
| ------------------------------ |
| ![](./pic/struct_sockaddr.png) |

| __listen__        |         头文件          |              函数原型               | 功能         |
| :---------------- | :---------------------: | :---------------------------------: | :----------- |
| 成功:0<br>失败:-1 | #include <sys/socket.h> | int listen(int sockfd, int backlog) | 设置监听上限 |
| __参数__          |        __含义__         |              __备注__               |
| sockfd            |   套接字的文件描述符    |                  -                  |
| backlog           |  同时连接的最大连接数   |              最大值128              |

| socketCommunication                |
| ---------------------------------- |
| ![](./pic/socketCommunication.png) |

| __accept__                           |                  头文件                  |                                               函数原型                                                | 功能                 |
| :----------------------------------- | :--------------------------------------: | :---------------------------------------------------------------------------------------------------: | :------------------- |
| 成功:已连接的套接字描述符<br>失败:-1 |         #include <sys/socket.h>          |      int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len)       | 阻塞等待用户建立连接 |
| __参数__                             |                 __含义__                 |                                               __备注__                                                |
| socket                               |               套接字描述符               |                                                   -                                                   |
| address                              |          客户端传过来的地址信息          |                                                   -                                                   |
| address_len                          | 保存客户机地址信息结构体大小的容器的地址 | 为什么是指针类型：因为它是传入传出参数，既需要引用服务端的大小,也需要将客户端信息容器大小传出到服务端 |

| __connect__       |              头文件              |                                    函数原型                                    | 功能                               |
| :---------------- | :------------------------------: | :----------------------------------------------------------------------------: | :--------------------------------- |
| 成功:0<br>失败:-1 |     #include <sys/socket.h>      | int connect(int socket, const struct sockaddr *address, socklen_t address_len) | 使用现有的socket与服务器socket链接 |
| __参数__          |             __含义__             |                                    __备注__                                    |
| socket            |         套接字文件描述符         |                                       -                                        |
| address           | 想要链接的服务器的地址信息结构体 |                                       -                                        |
| address_len       |       地址信息结构体的大小       |                                       -                                        |
