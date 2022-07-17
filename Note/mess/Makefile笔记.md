# Makefile学习笔记

> [Makefile教程 CSDN](https://blog.csdn.net/weixin_38391755/article/details/80380786)

TIPS:
- 如果makefile文件是其他名称(filename)可以这么做
`make -f filename`
- makefile的文件格式：xxx.mk
##### 显式规则

### 标准格式

```makefile
#目标文件:依赖文件
#	命令行...	
#例如:
main.o:main.c
	gcc -c main.c  #-c参数告诉gcc，对源文件进行编译会汇编，但不进行链接
```

### 伪目标

```makefile
OBJ=main.o list.o func.o ...


.PHONY clean#伪目标固定格式，该格式以下的目标都是伪目标
clean:	#clean是自定义的名称,在终端中执行make clean即可执行clear下的命令
	-rm $(OBJ)	#rm命令前面加了一个小减号的意思就是，也许执行该行代码出现问题，但不影响后续代码的执行(如果有的话)。
```
## 三个自动变量
- $@：在规则的命令中，表示规则中的目标。
- $^：在规则的命令中，表示所有依赖条件。
- $<：在规则的命令中，表示第一个依赖条件。

### 命令参数
-n：模拟执行过程，但不会真执行
-f：指定文件执行make命令

##模式规则
```makefile
%.o:%.c
  gcc -c $< -o $@
  #$<应用在模式规则中，它可将依赖条件列表中的依赖依次取出，套用模式规则。
```
## 终极模板
```makefile
src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))
ALL:a.out
a.out: $(obj)
  gcc $^ -o $@
%.o:%.c
  gcc -c $< -o $@
clean:
  -rm
  -rf $(obj) a. out
#-----------------------------------
src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src))
ALL:$(target)
%:%.c
  gcc $< -o $@
clean:
rm -rf $(target)
.PHONY:clean ALL
#-----------------------------------
"CC=arm-linux-gcc
"CC=gcc
"CC=g++
CFLAG = -g -Wall
#C源文件和目标文件
C_SRC = $(wildcard *.c)
#Cpp源文件和目标文件
CPP_SRC = $(wildcard *.cpp)
#目标文件
TAR = $(patsubst %.c,%,$(C_SRC)) $(patsubst %.cpp,%,$(CPP_SRC))

ALL:$(TAR)
%:%.c
	$(CC) $(CFLAG) $< -o $@ 

%:%.cpp
	$(CC) $(CFLAG) $< -o $@ 

clean: 
	$(RM) $(TAR)

.PHONY: clean ALL

```
## 静态模式

<目标>:<目标模式>:<依赖模式 ...>

```makefile
#看一个例子：
objects=foo.o bar.o
a11：$（objects）
$（objects）：%.o:%.c
	$（CC）-c $（CFLAGS）$^ -o $@
#上面的例子中,指明了我们的目标从$object中获取,"%.o"表明要所有以".o"结尾的目标,也就是"foo.o bar.o",也就是变量Subject集合的模式,而依赖模式"%.c"则取模式"%.o"的"%",也就是"foo bar",并为其加下".c"的后缀,于是,我们的依赖目标就是"foo.cbar.c".而命令中的"$〈"和"$@"则是自动化变量,"^"表示所有的依赖目标集(也就是"foo.cbar.c"),"$@"表示目标集(也就是"foo.obar.o").于是,上面的规则展开后等价于下面的规则:
foo.o: foo.c
$(CC) -c $(CFLAGS) foo.c -o foo.o
bar.o: bar.c
$(CC) -c $(CFLAGS) bar.c -o bar.o
```
## 隐式规则

### make自动推导

> 只要make 看到一个.o文件，它就会自动的把.c文件加在依赖关系中，如果make 找到一个whatever.o，那么whatever.c，就会是whatever.o的依赖文件。并且cc-c whatever.c也会被推导出来，于是，我们的makefile再也不用写得这么复杂。

```makefile
#使用自动推导前
objects=main.o kbd.o command.o display.o\ #\表示换行，增加可读性
insert.o search.o files.o utils.o
edit:$(objects)
cc -o edit $(obiects)
main.o: main.c defs.h
cc -c main.c
kbd.o: kbd.c defs.h command.h
cc -c kbd.c
command.o: command.c defs.h command.h
cc -c command.c
display.o: display.c defs.h buffer.h
cc -c display.c
insert.o: insert.c defs.h buffer.h
cc -c insert.c
search.o: search.c defs.h buffer.h
cc -c search.c
files.o: files.c defs.h buffer.h command.h
cc -c files.c
utils.o: utils.c defs.h
cc -c utils.c
clean:
rm edit $(objects)
#使用自动推导后，.c和命令执行都可以被省略
objects=main.o kbd.o command.o display.o\
insert.o search.o files.o utils.o
edit:$(objects)
cc -o edit $(objects)
main.o: defs.h
kbd.o: defs.h command.h
command.o: defs.h command.h
display.o: defs.h buffer.h
insert.o: defs.h buffer.h
search.o: defs.h buffer.h
files.o: defs.h buffer.h command.h
utils.o: defs.h
. PHONY: clean
clean:
rm edit $(objects)
#甚至可以再次简化成如下代码
objects=main.o kbd.o command.o display.o\
insert.o search.o files.o utils.o
edit:$(objects)
cc -o edit $(objects)
$(objects): defs.h
kbd.o command.o files.o: command.h
display.o insert.o search.o files.o: buffer.h
. PHONY: clean
clean:
rm edit $(objects)
```
## 引用其他makefile

### include语法

```makefile
#举个例子，你有这样几个Makefile:a.mk、b.mk、c.mk，还有一个文件叫foo.make，以及一个变量$（bar），其包含了e.mk和f.mk，那么使用下面一条语句就可以全部包含上述文件，被包含的文件会原模原样的放在当前文件的包含位置。
include foo. make *. mk $(bar)
```

### make寻找包含文件的方式

make首先会在当前目录找，如果找不到还会在以下目录找：

1. 如果make执行时，有“-I”或“-一include-dir”参数，那么make就会在这个参数所指定的目录下去寻找。
2. 如果目录<prefix>/include（一般是：/usr/local/bin 或/usr/include）存在的话，make也会去找。如果有文件没有找到的话，make会生成一条警告信息，但不会马上出现致命错误。它会继续载入其它的文件，一旦完成makefile的读取，make会再重试这些没有找到，或是不能读取的文件，如果还是不行，make才会出现一条致命信息。**如果你想让make不理那些无法读取的文件，而继续执行，你可以在include前加一个减号“-”。**

## 文件搜索

- VPATH是makefile的特殊**变量**，它的值是路径，其意义是：Makefile在当前目录找不到所需要的文件时，会去VPATH定义的路径中去寻找文件，存在多条路径时以冒号':'分隔开。
  例如：`VPATH=src:../headers`，makefile找完当前路径会去src和../headers两个路径中一次寻找

- vpath**关键字**的3种模式

  1. vpath<pattern〉<directories>为符合模式<pattern>的文件指定搜索目录<directories>

  2. vpath<pattern〉清除符合模式<pattern〉的文件的搜索目录

  3. vpath清除所有已被设置好了的文件搜索目录

     例如`vpath %.h../headers`,要求make在../header目录下搜索所有以.h结尾的文件

- vpath可以连续地使用，以制定不同搜索策略

## 多目标

```makefile
bigoutput littleoutput:text.g
generate text.g -$（subst output,,$@）>$@
#上述规则等价于：
bigoutput:text.g
generate text.g -big > bigoutput
littleoutput:text.g
generate text.g -little > littleoutput
#其中,-$(subst output,,$@)中的"$"表示执行一个Makefile的函数,函数名为subst,后面的为参数.这里的这个函数是截取字符串的意思,"$@"表示目标的集合,就像一个数组,"$@"依次取出目标,并执于命令.
```

## 函数
### filter
- 原型：`$(filter PATTERN,TEXT)` 
- 功能：过滤掉字串“TEXT”中所有不符合模式“PATTERN”的单词，保留所有符合此模式的单词。
### filter-out
- 原型：`$(filter-out PATTERN,TEXT)`
- 功能：在TEXT名单中去除PATTERN
- 示例：`$(filter-out main.c,*.c`)
### wildcard和patsubst
- `src = $(wildcard./*.c)`：匹配当前工作目录下的所有.o文件。将文件名组成列表，赋值给变量src
- `obj = $(patsubst%.c，%.o，$(src))`：将参数3中，包含参数1的部分，替换为参数2
