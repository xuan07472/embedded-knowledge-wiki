# Makefile 是make工具编译时的配置文件
# 参考网址：[Makefile多目录源文件](https://blog.csdn.net/qq_23087589/article/details/80668983)

SHELL=cmd.exe

# 编译器名称；=是给变量赋值
CC = gcc

# 编译器选项：-g打开调试选项，程序崩溃后可以看到崩溃前的各种信息
CFLAGS = -g

# 编译出来的应用程序名称
TARGETS := module_core_demo

# 文件路径
src1 = ../group_buf_queue
src2 = .

# 一个文件夹下的源文件；wildcard：变量定义时，通配符失效。使用函数wildcard使$通配符有效；$用于对变量取值
# = 是最基本的赋值
# := 是覆盖之前的值
# ?= 是如果没有被赋值过就赋予等号后面的值
# += 是添加等号后面的值
# filter-out 排除一组文件
SRC1 = $(wildcard ../group_buf_queue/*.c)
SRC1  := $(filter-out $(src1)/group_buf_queue_unitest.c, $(SRC1))

SRC2 = $(wildcard ./*.c)

# 输出字符串，类似于printf
$(warning build files: $(SRC1) $(SRC2))
$(warning ----)

# 头文件查找路径
INCLUDE= -I$(src1) -I$(src2)

# .c需要编译成.o，生成所有的.o目标名称；patsubst字符串替换；%匹配任何同类型文件
OBJ1 = $(patsubst %.c, %.o, $(SRC1))
OBJ2 = $(patsubst %.c, %.o, $(SRC2))

# 输出字符串，类似于printf
$(warning link files: $(OBJ1) $(OBJ2))
$(warning ----)

# : 冒号之前的是标签，make命令后可以跟着的参数，第一个是make的默认参数
# 标签后面的行数以tab起始（不能是空格），里面的命令会循环执行
# 从所有的.o编译的文件链接成可执行程序
# 行首的@表示编译时不回显信息；$对变量取值；$^所有依赖文件; $@所有目标文件
# -o 是gcc的链接命令
$(TARGETS) : $(OBJ1) $(OBJ2)
	@echo "prepare Link "
	@$(CC ) $^ -o $@
	@echo "prepare successfully!"

# 将所有.c编译成.o
# -c 是gcc的编译命令；$<第一个依赖文件
%.o : $(src1)/%.c
	@echo "prepare Compile1 "
	$(CC) -c $< $(CFLAGS ) $(INCLUDE) -o $@
	@echo "Compiled_1 "$<" successfully!"

%.o:%.c 
	@echo "prepare Compile2 "
	@$(CC) -c $< $(CFLAGS) $(INCLUDE) -o $@
	@echo "Compiled_2 "$<" successfully!"

# .PHONY定义伪标签；用于make clean清除所有以前编译的中间文件
.PHONY : clean
clean:
	@-rm $(TARGETS) $(OBJ1) $(OBJ2)
	@echo "Cleanup complete!"