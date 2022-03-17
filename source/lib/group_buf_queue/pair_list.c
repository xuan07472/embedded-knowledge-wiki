/**
 * \file pair_list.c
 * \brief 实现队列（FIFO、Queue）的一对链表的操作
 * \note 一个链表放已存入的链表节点，一个链表放已释放的链表节点，所有的节点加起来就是
 *       当前队列组别的所有的缓存个数（允许有多个队列同时存在，可以每个模块有个自己的队列，
 *       也可以不同元素长度的缓存组成不同的队列）
 *
 * \author 将狼才鲸
 * \date 2022-03-16
 * \remarks 源文件使用Windows(CR LF)换行 + UTF-8编码，tab使用4个空格
 */

#include "pair_list.h"

/**
 * \brief 初始化一个队列
 */
void pair_list_init(pair_list_t *pl)
{
    if (NULL == pl)
        return;
    
    for (int i = 0; i < PAIR_LIST_MAX; i++) {
        INIT_LIST_HEAD(&(pl->lists[i]));
    }
}

/**
 * \brief 初始化队列中的单个缓存
 */
void pair_list_node_init(pair_list_node_t *plnode)
{
    if (NULL == plnode)
        return;
    
    INIT_LIST_HEAD(&plnode->node); // ->优先级比&高
    plnode->pair_list = NULL;
}

/**
 * \brief 用于两级队列的缓存推送
 * \note 如果pl为空，则是将plnode这个节点推送到自己原本的队列中
 *       如果pl不为空，则是将plnode这个节点从自己原本的队列推送到pl这个队列中
 */
int pair_list_put(pair_list_t *pl, pair_list_node_t *plnode, unsigned int used_or_free)
{
    struct list_head *node, *entry;
    
    if (!plnode || used_or_free >= PAIR_LIST_MAX)
        return -EPERM;
    
    if (!pl)
        pl = plnode->pair_list; // 如果从当前队列推到另一个队列中去
    if (!pl)
        return -EPERM;
    
    node = &plnode->node; // 当前缓存对应的聊表节点
    entry = &pl->lists[used_or_free]; // entry是该链表的入口，也是链表最早推入和最晚弹出的元素
    
    list_del_init(node); // 从node自己所属的链表中删除node节点并初始化node节点
    list_add_tail(node, entry); //node加入到head的前面，也就是entry链表的末尾（因为是双向循环链表）
    
    return 0;
}

/**
 * \brief 从队列中获取一个元素
 * \remarks 队列中的第一个元素只作为入口标记用，第二个元素才是第一个需要最早弹出的数据
 */
pair_list_node_t *pair_list_get(pair_list_t *pl, unsigned int used_or_free)
{
    pair_list_node_t *plnode;
    struct list_head *cur_node, *entry;
    
    if (!pl || used_or_free >= PAIR_LIST_MAX)
        return NULL;

    entry = &pl->lists[used_or_free];
    plnode = NULL;
    
	if (!list_empty_careful(entry)) { // 链表非空
        // 获取入口后面的第一个节点所属的结构体的地址（从子元素地址推导父元素地址）
		plnode = list_first_entry(entry, pair_list_node_t, node); // 这里的node只是一个标号，是pair_list_node_t中的元素名

		cur_node = &plnode->node;
		list_del_init(cur_node); // 从原链表中删除这个缓存对应的节点
	}
    // else 如果整个链表只有一个节点，则认为这个节点只是入口，后面一个数据都没有
    
    return plnode;
}

/**
 * \brief 申请一个缓存
 * \remarks 在队列初始化时，已经提前把所有的缓存都放入到PAIR_LIST_FREE列表中去了
 *          申请之后就是推送，推送是推到PAIR_LIST_USED这个链表中去
 */
pair_list_node_t *pair_list_alloc(pair_list_t *pl)
{
	return pair_list_get(pl, PAIR_LIST_FREE);
}

/**
 * \brief 释放一个缓存
 * \remarks 也就是将plnode从PAIR_LIST_USED这个链表中删除，送到PAIR_LIST_FREE中去
 */
int pair_list_free(pair_list_node_t *plnode)
{
	return pair_list_put(NULL, plnode, PAIR_LIST_FREE);
}

/**
 * \brief 获取有效缓存总数
 */
unsigned pair_list_count(pair_list_t *pl, unsigned int used_or_free)
{
	int count = 0;
	struct list_head *head, *node, *n; // node和n都是临时变量，不用关心

	if (!pl || used_or_free >= PAIR_LIST_FREE)
		return -EPERM;

	head = &(pl->lists[used_or_free]);

	if (!list_empty_careful(head)) { // 如果链表非空
		list_for_each_safe(node, n, head) { // 循环宏定义语句
			count++;
		}
	}

	return count;
}