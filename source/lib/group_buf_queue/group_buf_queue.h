/**
 * \file group_buf_queue.h
 * \brief 缓存队列的操作（可针对多组不同的缓存进行操作）
 * \note buffer相关的结构体和list相关的结构体需要分开独立操作
 * \author 将狼才鲸
 * \date 2022-03-17
 * \remarks 源文件使用Windows(CR LF)换行 + UTF-8编码，tab使用4个空格
 */

/**
 * \brief 缓存组类别
 * \details 不同的缓存组可以有不同的缓存长度和缓存个数，不同的缓存组之间传递数据需要用到memcpy，
 *          而不能直接拷贝缓存指针（直接拷贝指针会非常节省时间），所以非必要情况下不要在不同
 *          组别间传递缓存
 */

#ifndef _GROUP_BUF_QUEUE_H
#define ifndef_GROUP_BUF_QUEUE_H

#include "pair_list.h"

#define ENOMEM 12 // from errno.h

enum {
    BUFFER_GROUP_NOTUSE = 0,
    BUFFER_GROUP_MSG,
    BUFFER_GROUP_DATA,
    BUFFER_GROUP_MAX_COUNT,
};

/**
 * \brief 一块最小的不可再分割的缓存
 * \remarks buffer和list需要分开独立进行操作
 */
typedef struct _buffer {
    pair_list_node_t list_node; // 一个缓存对应一个链表节点
    unsigned int group_flag; // 缓存组的标志
    void *addr; // 缓存地址
    unsigned int buf_maxsize; // 缓存空间大小
    unsigned int len; // 已存储的数据长度
    unsigned int user_data1; // 数据传递双方自定义的额外数据
    unsigned int user_data2;
} buffer_t;

/**
 * \brief 同组缓存的内存起始地址和缓存个数信息
 * \details 整个缓存组的数据总长度通过count * unitsize算出来
 */
typedef struct _buffer_group {
    void *addr; // 整个缓存组的起始地址
    unsigned int unitsize; // 单个缓存的长度，同组内每个缓存的长度都一样
    unsigned int count; // 缓存个数
} buffer_group_t;

/**
 * \brief 默认初始化所有缓存组和所有缓存子项
 */
void all_buffer_group_default_init(void);

/**
 * \brief 使用地址等参数初始化一个缓存组
 */
int group_buf_init(buffer_group_t *group_addr, unsigned int group_type);



#endif // ifndef_GROUP_BUF_QUEUE_H
