VPATH=../src
CFLAGS=-fPIC -I ../include
TAG = main
OBJ = ../src/main.c
SRC_C = $(filter-out $(OBJ),$(wildcard ../src/*.c))	#src里所有的.c文件，去除main.c
SRC_O = $(patsubst %.c,%.o,$(SRC_C))	#对应的.c替换成.o
LIB = ../lib/libloginSystem.so
LDFLAGS = -L ../lib -lloginSystem

ALL:$(TAG)

$(LIB):$(SRC_O)	#生成动态库，此处的所有.o文件被Make自动推导生成，自动推导过程中会添加CFLAGS的所有参数
	$(CC) $(CFLAGS) -shared $^ -o $@

$(TAG):$(OBJ) $(LIB)	#生成可执行文件并链接动态库，清除所有.o文件
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
	$(RM) $(SRC_O)

clean:
	$(RM) $(TAG) $(LIB)	#删除可执行文件和动态库

.PHONY:clean