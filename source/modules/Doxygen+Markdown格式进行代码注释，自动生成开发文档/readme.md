使用Doxygen + Markdown进行代码注释，自动生成技术文档
===

|作者|将狼才鲸|
|---|---|
|创建日期|2024-01-24|

---

## 一、介绍

* 开源软件Doxygen能将代码的注释自动生成文档，1.8.0版本之后的注释格式已经能支持Markdown语法了，而Markdown能通过写代码的方式生成序号、表格、图片、链接、框图、流程图。默认输出网页格式，再使用LaTeX + RTF插件后能输出pdf和doc格式的文档。
* 下载Doxygen 1.10.0版本
  * 下载地址：[Download Doxygen](https://www.doxygen.nl/files/doxygen-1.10.0-setup.exe)，下载速度比较慢，但是软件不大。

## 二、使用

1. 在你的C/C++源码中用Doxygen的样式写注释

* 例如：

```c
/******************************************************************************
 * \brief	一个C语言的main文件
 * \details	用于展示Doxygen通过注释自动生成文档的用法
 * \remark	养成良好的编码习惯和注释习惯是一个好程序员该有的素养
 * \author	将狼才鲸
 * \date	2024-01-24
 ******************************************************************************/

#include <stdio.h>

/**
 * \brief	主函数
 * \param	argc, 传入参数的个数
 * \param	argv, 传入参数的内容
 * \remark	始终有一个默认参数argv[0]，里面是本程序的路径+程序名，用户的参数从argv[1]开始
 * \return	0代表执行正常，负数代码错误码
 */
int main(int argc, char *argv[])
{
	printf("hello world!\n");
	
	return 0;
}
```

2. 安装Doxygen软件后写Doxygen的配置文件

* 方法：
  * 可以自动生成默认配置：
  * 1）你可以使用doxygen图形界面来配置，步骤略
    * 运行D:\Program Files\doxygen\bin\doxywizard.exe软件，必须要配置Source code directory；配置文件的输出目录Destination directory
    * 你也可以Show configuration后生成配置后复制，并保存到你新建的配置文本文件中
  * 2）你也可以用命令行的方式来生成默认配置
    * 先将doxygen程序的路径加入到Windows或Linux系统的环境变量，过程略
      * 例如：Win10的话打开环境变量，点开Path，加入一行：D:\Program Files\doxygen\bin
    * 执行命令 doxygen -g <config-file-name>
    * 执行效果如下：

```shell
jim@DESKTOP-SVP3BEM MINGW64 /d/1_git/Doxygen+Markdown代码注释格式，自动生成文档/src
$ doxygen -g doxygen-config.txt


Configuration file 'doxygen-config.txt' created.

Now edit the configuration file and enter

  doxygen doxygen-config.txt

to generate the documentation for your project
```

* 生成的默认配置文件比较大，有一两百k，生成后必须还要手动改里面的配置

3. 用doxygen从你的注释中生成文档

* 注意，一定一定要保证你源码中注释的格式正确，Doxygen配置文件配置正确，不建议新手从头开始修改，要不然不一定能生成正确，非常浪费时间，还是建议下载一个已经制作好的源码 + 注释 + Doxygen配置开始，这样不会遇到问题。

* 方法：
  * 如果是用命令行生成的默认配置，修改你生成的配置中的INPUT选项
    * 例如改成 . 也就是当前目录
  * 同时还要修改其它项，如：
  * 使用命令 doxygen <config-file-name>
  * 默认输出含有多个文件的html
  * 打开src\html\index.html就能看到自动输出的技术文档了，效果如下：

![img]()

* 生成pdf的开发文档：
  * 首先安装xxx

