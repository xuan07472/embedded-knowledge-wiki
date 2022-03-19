# C语言如何实现多级队列缓存（Queue、FIFO）

|作者|将狼才鲸|
|---|---|
|日期|2022-03-20|

---

## 1、各种缓存结构：  

基础：指针、链表、内存、数组。  
数据结构基础：表、树、图（多对多）。  
缓冲区/buffer/顺序表/平直缓存/数组/内存指针（malloc）。  
栈/stack：因为是先进后出，也用于函数调用时的压栈，编译器和高级算法中用的多，日常编程基本上不用。  
堆/heap/完全二叉树：方便排序，编译器和算法中常用，日常编程基本上不用。  
环形缓冲区/环形缓存区/循环队列/loop_buffer/ring_buffer/队列/FIFO/Queue：先进先出，满和空。  

*参考网址：*  [什么是队列（队列存储结构）](http://c.biancheng.net/view/3352.html)  
*参考网址：* [链式队列及基本操作（C语言实现）](http://c.biancheng.net/view/3354.html)  
*参考网址：*  [数据结构与算法教程，数据结构C语言版教程！](http://c.biancheng.net/data_structure/)  

分组队列/多级队列/group_buffer/fifo/queue：每个模块都有自己的队列，且不同队列间可直接通过数据指针无消耗转移大块数据。  

##  2、自行实现的 **“多级缓存队列”模块**   
Gitee仓库源码：  
[点击此处查看源码](https://gitee.com/langcai1943/embedded-knowledge-wiki/tree/develop/source/lib/group_buf_queue)  
本地路径：嵌入式知识图谱WiKi\source\lib\group_buf_queue\   

有gcc-makefile和Qt两个工程都能编过，带详细注释和单元测试用例。  

### 目录结构：  

```
jim@DESKTOP-SVP3BEM MINGW64 /d/3_doc/嵌入式知识图谱WiKi/source/lib/group_buf_queue (develop)
$ tree
.
|-- Makefile
|-- arch_buffer_config.c
|-- arch_buffer_config.h
|-- group_buf_queue.c
|-- group_buf_queue.h
|-- group_buf_queue_init.c
|-- group_buf_queue_init.h
|-- group_buf_queue_unitest.c
|-- group_buf_queue_unitest_qt_proj
|   `-- group_buf_queue_unitest_qt_proj.pro
|-- list.h
|-- module_buf_queue.c
|-- pair_list.c
|-- pair_list.h
`-- readme.txt

1 directory, 15 files
```

### 单元测试结果：  

```
jim@DESKTOP-SVP3BEM MINGW64 /d/3_doc/嵌入式知识图谱WiKi/source/lib/group_buf_queue (develop)
$ ./group_buf_queue_demo.exe
         buffer_unitest start          
got buf: [group_flag: 1] [addr: 0x0040d760] [buf_maxsize: 512] [len: 0]
push data: :) my first buffer message ^_^
got buf data: [group_flag: 1] [msg: :) my first buffer message ^_^] [len: 31]
________ buffer_unitest test pass. ________

          pair_list_unitest start          
put data: :) my first buffer message ^_^
got data: :) my first buffer message ^_^
________ pair_list_unitest test pass. ________

         circular_linked_list_unitest start         
put a node
node count: 1
put a tail node
node count: 2
delete a node
node count: 1
________ circular_linked_list_unitest test pass. ________

group_buf_queue_unitest.c test pass.
```

## 3、实现原理：  

……待编写……  

## 4、编译说明  
* 用Visual Studio创建底层C程序工程编译会报错，放弃。  
* 用Qt + MSVC创建底层C程序工程编译会报错，放弃。  
* 可以用gcc 直接make编译，我用的是Windows下安装的gcc和make工具（安装这些工具的同时也会自动安装MinGW工具），生成的是exe。  
* 也可以用Qt + MinGW 64-bit（安装Qt时勾选MinGW选项即可，Qt6版本及以上的MinGW只有64位可用了）。  
* Qt创建工程时不能使用Paint C++，只能使用Paint C，因为编译时会报一些C++专有的关键字错误，和类型强制转换不支持等错误。  

* group_buf_queue_unitest_qt_proj/group_buf_queue_unitest_qt_proj.pro是Qt的工程入口，双击即可打开。  
* 点击编译，在Qt下方的一个“应用程序输出”内嵌窗口中可以看到程序输出。  
* Qt源码界面上可能出现一些C++相关的报错，但是程序编译时并没有error（实际上也是调用gcc编的，没用C++的东西），只有一些warnning（用gcc直接make时没有这些warnning），能编译通过，程序正常输出结果。  
