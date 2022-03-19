/**
 * \file module_queue.h
 * \brief 模块缓存，依赖group_buf_queue.h
 * \details group_buf有个机制，如果你alloc后并没有put到group组的链表对中去，那你
 *          就可以独立使用这个缓存，原来的缓存组既申请不到它也用不了它，那么你可以
 *          将它put到自己写成的队列中去，用完后再free回原来的group_buf队列
 * \note 当前设计的一个模块只保存一个缓存队列，够用了，如果以后想一个模块
 *       保存多个队列，如消息和数据，音频和视频分开从多个模块进来，那么可以
 *       参照group_buf_queue模块，将本模块struct list_head *queue_entry
 *       换成pair_list_t即可实现
 * \author 将狼才鲸
 * \date 2022-03-18
 * \remarks 源文件使用Windows(CR LF)换行 + UTF-8编码，tab使用4个空格
 */

#ifndef _MODULE_QUEUE_H
#define _MODULE_QUEUE_H

#include "group_buf_queue.h"
#include "module.h"

/* 模块缓存 */
typedef buffer_t module_buf_t;

/* 模块缓存链表 */
typedef struct list_head module_queue_t;

/**
 * \brief 单个缓存对应的链表节点
 * \remarks list.h中的机制可以通过node的地址推导出queue_node_t的地址
 *          所以对struct list_head的操作也是对queue_node_t的操作
 *          实际的队列中每个list_head都有该节点对应的queue_node_t
 */
typedef struct _queue_node {
    struct list_head node; // 单个缓存对应的链表节点
    struct list_head *qentry; // 当前缓存所属的队列的指针（当前未使用）
} queue_node_t;

/**
 * \brief 一个module缓存节点
 */
typedef struct _module_buf {
    queue_node_t qnode;
    module_buf_t *mbuf;
} module_buffer_node_t;

/**
 * \brief 从系统缓存中申请一个缓存
 */
#define module_queue_alloc buffer_alloc

/**
 * \brief 将已经申请的缓存送回系统缓存
 */
#define module_queue_free buffer_free

/**
 * \brief 初始化自己模块的缓存队列
 */
void module_queue_init(struct mudule *m);

/**
 * \brief 销毁自己模块的缓存队列，将用过的缓存还给group_buf_queue模块
 */
void module_queue_exit(struct mudule *m);

/**
 * \brief 从module本地free列表中申请一个节点信息
 * \details 实际的缓存已经从group_buf_queue模块中获取过了，这些缓存是全局的
 *          不用自己分配
 */
static module_buffer_node_t *module_node_alloc(module_queue_t *queue, module_buf_t *buf);

/**
 * \brief 将缓存还给module本地free列表中
 * \details 和group_buf_queue模块无关
 */
static module_buf_t *module_node_free(module_buffer_node_t *mbnode);

/**
 * \brief 将缓存推送到对方模块
 * \param m 对方模块
 * \param buf 已实现申请好或获取到并修改了内容的缓存
 */
module_buf_t *module_queue_push(struct mudule *m, module_buf_t *buf);

/**
 * \brief 从自己模块的队列中推出一个缓存
 */
module_buf_t *module_queue_pop(struct mudule *m);

/**
 * \brief 获取目标模块的缓存数量
 */
int module_queue_num(struct mudule *m, module_buf_t *buf);


#endif // _MODULE_QUEUE_H
