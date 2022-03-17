#include "group_buf_queue.h"
#include "arch_buffer_config.h"

#define ENOMEM 12 // from errno.h

/**
 * \brief 所有的缓存组，每个组都有自己一对链表入口，链表成员则在其它位置定义
 */
static pair_list_t g_all_bufgroup[BUFFER_GROUP_MAX_COUNT];

/**
 * \brief 所有的缓存放在同一个数组里，每个缓存中有一个链表节点，同时也有一个
 *        自己缓存组链表地址的索引
 *        一开始这些没使用的缓存都属于BUFFER_GROUP_NOTUSE缓存组，直到一个缓存组
 *        初始化之后才分配到自己的缓存组
 */
static buffer_t g_all_buffer[BUFFER_MAX_COUNT];

/**
 * \brief 默认初始化所有缓存组和所有缓存子项
 */
void all_buffer_group_default_init(void)
{
    int i;
    buffer_t *per_buf; // 一个缓存
    pair_list_node_t *buf_node; // 这个缓存的链表节点，和这个缓存所属的缓存组的两条链表的入口
    
    /* 初始化所有缓存队列 */
    for (i = 0; i < BUFFER_GROUP_MAX_COUNT; i++) {
        pair_list_init(&g_all_bufgroup[i]);
    }
    
    /* 初始化所有缓存 */
    memset(g_all_buffer, 0, sizeof(g_all_buffer));
    for (i = 0; i < BUFFER_MAX_COUNT; i++) {
        per_buf = &g_all_buffer[i]; // 获取当前buffer
        buf_node = &per_buf->list_node; // 获取当前buffer对应的链表节点
        INIT_LIST_HEAD(&buf_node->node); // 初始化该缓存的链表节点
        // 将该缓存所属的缓存组都先定向于NOTUSE未使用缓存组（等待具体缓存组初始化后才归类到那一组）
        buf_node->pair_list = &g_all_bufgroup[BUFFER_GROUP_NOTUSE];
        pair_list_free(buf_node); // 释放该缓存链表节点（将节点归类到自己缓存组的释放队列中）
    }
}

/**
 * \brief 使用地址等参数初始化一个缓存组
 */
int group_buf_init(buffer_group_t *group_addr, unsigned int group_type)
{
    int i;
    buffer_t *per_buf, *old_buf; // 一个缓存
    pair_list_node_t *buf_node; // 这个缓存的链表节点，和这个缓存所属的缓存组的两条链表的入口
    pair_list_t *pair_list; // 缓存组对应的链表对（这个缓存所属的缓存组的两条链表的入口）
    
    if (!group_addr || group_type <= BUFFER_GROUP_NOTUSE
                    || group_type >= BUFFER_GROUP_MAX_COUNT ) {
        return -EPERM;
    }
    
    pair_list = &g_all_bufgroup[group_type]; // 获取需要的缓存组的指针
    
    /* 清除已经初始化过的同一组的缓存 */
    for (i = 0; i < BUFFER_MAX_COUNT; i++) {
        per_buf = &g_all_buffer[i]; // 获取当前buffer
        buf_node = &per_buf->list_node; // 当前buffer的链表节点
        if (buf_node->pair_list == pair_list) {
            buf_node->pair_list = &g_all_bufgroup[BUFFER_GROUP_NOTUSE];
            // 将该缓存送到自己缓存组的free链表中去
            // 也就是将当前缓存加入到NOTUSE缓存组的free链表中去
            pair_list_free(buf_node);
        }
    }
    
    /* 初始化队列 */
    pair_list_init(pair_list);
    
    /* 初始化队列中每个元素 */
    old_buf = NULL;
    for (i = 0; i < group_addr->count; i++) {
        // 从所有缓存指针中先找一个没有被放入指定缓存组的空缓存
        // （如果所有的缓存组都初始化，则g_all_bufgroup就被消耗空了）
        buf_node = pair_list_alloc(&g_all_bufgroup[BUFFER_GROUP_NOTUSE]);
        if (NULL == buf_node)
            return -ENOMEM;
        
        // 从pair_list_node_t子元素地址倒推出buffer_t地址
        per_buf = container_of(buf_node, buffer_t, list_node);
        per_buf->buf_maxsize = group_addr->unitsize;
        per_buf->len = 0;
        if (NULL == old_buf) {
            per_buf->addr = group_addr->addr;
        } else {
            per_buf->addr = old_buf->addr + group_addr->unitsize;
        }
        old_buf = per_buf;
        
        // 让该缓存的链表节点所属的缓存组链表对指向要设置的组地址（一个全局变量指针）
        buf_node->pair_list = pair_list;
        
        // 在自己所属的缓存组内，将缓存放到free未分配这个链表中去
        pair_list_free(buf_node);
    }

    return 0;
}
