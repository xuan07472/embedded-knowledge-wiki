/**
 * \file pair_list.h
 * \brief 实现队列（FIFO、Queue）的一对链表的操作
 * \note 一个链表放已存入的链表节点，一个链表放已释放的链表节点，所有的节点加起来就是
 *       当前队列组别的所有的缓存个数（允许有多个队列同时存在，可以每个模块有个自己的队列，
 *       也可以不同元素长度的缓存组成不同的队列）
 *
 * \author 将狼才鲸
 * \date 2022-03-16
 * \remarks 源文件使用Windows(CR LF)换行 + UTF-8编码，tab使用4个空格
 */

#ifndef _PAIR_LIST_H
#define _PAIR_LIST_H

#include "list.h"

#define EPERM 1 // from errno.h

enum {
    PAIR_LIST_USED = 0,
    PAIR_LIST_FREE,
    PAIR_LIST_MAX,
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
typedef struct _pair_list_node {
    struct list_head node; // 单个缓存对应的链表节点
    pair_list_t *pair_list; // 当前缓存所属的队列的指针
} pair_list_node_t;

/**
 * \brief 初始化一个队列
 */
void pair_list_init(pair_list_t *pl);

/**
 * \brief 初始化队列中的单个缓存
 */
void pair_list_node_init(pair_list_node_t *plnode);

/**
 * \brief 用于两级队列的缓存推送
 * \note 如果pl为空，则是将plnode这个节点推送到自己原本的队列中
 *       如果pl不为空，则是将plnode这个节点从自己原本的队列推送到pl这个队列中
 */
int pair_list_put(pair_list_t *pl, pair_list_node_t *plnode, unsigned int used_or_free);

/**
 * \brief 从队列中获取一个元素
 * \remarks 队列中的第一个元素只作为入口标记用，第二个元素才是第一个需要最早弹出的数据
 */
pair_list_node_t *pair_list_get(pair_list_t *pl, unsigned int used_or_free);

/**
 * \brief 申请一个缓存
 * \remarks 在队列初始化时，已经提前把所有的缓存都放入到PAIR_LIST_FREE列表中去了
 *          申请之后就是推送，推送是推到PAIR_LIST_USED这个链表中去
 */
pair_list_node_t *pair_list_alloc(pair_list_t *pl);

/**
 * \brief 释放一个缓存
 * \remarks 也就是将plnode从PAIR_LIST_USED这个链表中删除，送到PAIR_LIST_FREE中去
 */
int pair_list_free(pair_list_node_t *plnode);

/**
 * \brief 获取有效缓存总数
 */
unsigned pair_list_count(pair_list_t *pl, unsigned int used_or_free);

#endif // _PAIR_LIST_H
