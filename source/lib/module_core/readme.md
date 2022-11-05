# 如何实现嵌入式通用模块、模块统一接口、统一API（架构、状态机、队列）  

|作者|将狼才鲸|
|---|---|
|日期|2022-03-20|

---

## 1、自行实现的 **“通用模块”**  

Gitee仓库源码：[点击此处查看源码](https://gitee.com/langcai1943/embedded-knowledge-wiki/tree/develop/source/lib/module_core)  

本地路径：嵌入式知识图谱WiKi\source\lib\module_core\ 支持make编译和Qt编译，带详细注释和单元测试用例。  

## 2、目录结构  

```
jim@DESKTOP-SVP3BEM MINGW64 /d/3_doc/嵌入式知识图谱WiKi/source/lib/module_core (develop)
$ tree
.
|-- Makefile
|-- module.c
|-- module.h
|-- module1.c
|-- module2.c
|-- module3.c
|-- module_queue.c
|-- module_queue.h
|-- module_unitest.c
`-- module_unitest_qt_proj
    `-- module_unitest_qt_proj.pro

1 directory, 10 files
```

## 3、单元测试结果：  

```
jim@DESKTOP-SVP3BEM MINGW64 /d/3_doc/嵌入式知识图谱WiKi/source/lib/module_core (develop)
$ ./module_core_demo.exe
         module_unitest start         
 'module1 >>>1<<<' module_create
 'module2 )))2(((' module_create
 'module3 \\\3///' module_create
 'module1 >>>1<<<' module_start
 'module2 )))2(((' module_start
 'module3 \\\3///' module_start
 'module1 >>>1<<<' module_process
 'module2 )))2(((' module_process
 'module3 \\\3///' module_process

module1 >>>1<<< put data:  '@_@ @o@ from module1 1 1'  >>>>>>>>
 'module1 >>>1<<<' module_process
 'module2 )))2(((' module_process
 'module3 \\\3///' module_process
module2 )))2((( got data:  '@_@ @o@ from module1 1 1'  <<<<<<<<


module2 )))2((( put data:  ':) :-) from module2 2 2'  >>>>>>>>

module1 >>>1<<< put data:  '@_@ @o@ from module1 1 1'  >>>>>>>>
 'module1 >>>1<<<' module_process
 'module2 )))2(((' module_process
 'module3 \\\3///' module_process
module3 \\\3/// got data:  ':) :-) from module2 2 2'  <<<<<<<<

module2 )))2((( got data:  '@_@ @o@ from module1 1 1'  <<<<<<<<


module2 )))2((( put data:  ':) :-) from module2 2 2'  >>>>>>>>

module1 >>>1<<< put data:  '@_@ @o@ from module1 1 1'  >>>>>>>>
 'module1 >>>1<<<' module_stop
 'module2 )))2(((' module_stop
 'module3 \\\3///' module_stop
 'module1 >>>1<<<' module_distroy
 'module2 )))2(((' module_distroy
 'module3 \\\3///' module_distroy
________ module_unitest test pass. ________

module_unitest.c test pass.
```

## 4、实现原理：  

……待编写……  

## 5、编译说明：  

* 备注：用Visual Studio和Qt + MSVC编译偏底层的C程序会报错（如使用了typeof等GNU C特性时），推荐使用Qt + MinGW 64-bit 或者 gcc编译。  
* 备注：Windows下也可以安装gcc和make（安装此软件时同时也会后台安装MinGW环境），然后可以直接在Windows命令行cmd中执行make生成exe。  
* 备注：Qt + MinGW创建工程时不能使用Paint C++，只能使用Paint C，因为编译时会报一些C++专有的关键字错误（如new关键字），和部分类型强制转换不支持等错误。  
