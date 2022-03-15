/**
 * \file list.h
 * \brief 双向循环链表
 *
 * \details 一个借助编译器原理的使用小技巧：当用户自定义的结构体中有该链表入口节点作为成员时，
 *          对链表顺序的操作也就是对自定义结构体的操作，因为通过链表节点地址可以反推出结构体
 *          的地址；更进一步，如果链表节点是结构体中第一个元素，那么链表的地址也是结构体的地址
 *          直接对链表节点地址进行强制类型转换即可得到排好序的结构体地址。
 *
 * \author Linux kernel group
 * \version v5.16
 * \remarks list修改自Linux中的源码
 *          当前最新版v5.16的源码中即有（只有.h头文件，里面用了inline函数，不需要.c源文件）
 *          头文件路径：[Gitee极速下载/Linux Kernel](https://gitee.com/mirrors/linux_old1/blob/v5.16/include/linux/list.h)
 */
 
 //**** 参考资料 ****//
 //[linux内核中的list详解](https://blog.csdn.net/qq_26617115/article/details/53509321)
 