/**
 * \file pair_list.h
 * \brief 实现队列（FIFO、Queue）的一对链表的操作
 * \note 一个队列放已存入的链表节点，一个队列放已释放的链表节点，所有的节点加起来就是
 *       当前队列组别的所有的缓存个数（有多个队列同时存在，可以每个模块有个自己的队列，
 *       也可以不同元素长度的缓存组成不同的队列）
 *
 * \author 将狼才鲸
 * \date 2022-03-16
 * \remarks 源文件使用Windows(CR LF)换行 + UTF-8编码，tab使用4个空格
 */

#ifndef _PAIR_LIST_H
#define _PAIR_LIST_H

#include "list.h"

enum {
    PAIR_LIST_USED,
    PAIR_LIST_FREE,
#define PAIR_LIST_MAX PAIR_LIST_FREE
};

/**
 * \brief 一个队列的链表入口
 */
typedef struct _pair_list {
    struct list_head lists[PAIR_LIST_MAX];
} pair_list_t;

/**
 * \brief 单个缓存对应的链表节点
 * \remarks list.h中的机制可以通过node的地址推导出pair_list_node_t的地址
 *          所以对struct list_head的操作也是对pair_list_node_t的操作
 *          实际的队列中每个list_head都有该节点对应的pair_list_node_t
 */
typedef struct pair_list_node {
    struct list_head node; // 单个缓存对应的链表节点
    pair_list_t *pair_list; // 当前缓存所属的队列的指针
} pair_list_node_t;

#endif // _PAIR_LIST_H
