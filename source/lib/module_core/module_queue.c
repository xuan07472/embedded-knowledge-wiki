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

#include "module_queue.h"

/**
 * \brief 将所有的系统缓存都重新映射一个属于module的节点入口
 * \details 一开始所有的节点都是free状态
 */
static module_buffer_node_t module_all_buffers[BUFFER_MAX_COUNT];

/**
 * \brief 所有节点都设置为free状态
 */
void module_all_nodes_init(void)
{
    memset(module_all_buffers, 0, sizeof(module_all_buffers));
}

/**
 * \brief 初始化自己模块的缓存队列
 */
void module_queue_init(struct module *m)
{
    if (!m)
        return;

    INIT_LIST_HEAD(&m->queue_entry);
}

/**
 * \brief 销毁自己模块的缓存队列，将用过的缓存还给group_buf_queue模块
 */
void module_queue_exit(struct module *m)
{
    module_buf_t *mbuf;

    if (!m)
        return;

    do {
        mbuf = module_queue_pop(m);
        if (mbuf)
            module_queue_free(mbuf);
    } while (mbuf);
}

/**
 * \brief 从module本地free列表中申请一个节点信息
 * \details 实际的缓存已经从group_buf_queue模块中获取过了，这些缓存是全局的
 *          不用自己分配
 */
static module_buffer_node_t *module_node_alloc(module_queue_t *queue, module_buf_t *buf)
{
    int i;
    module_buffer_node_t *mbnode = NULL; // 节点+队列入口+一个缓存

    if (!queue || !buf)
        return NULL;

    /* 获取一个空节点 */
    for (i = 0; i < BUFFER_MAX_COUNT; i++) {
        mbnode = &module_all_buffers[i];
        if (!mbnode->mbuf)
            break; // 如果缓存是空的，则已找到

        mbnode = NULL;
    }

    /* 初始化这个节点 */
    if (!mbnode) {
        mbnode->mbuf = buf;
        INIT_LIST_HEAD(&mbnode->qnode.node);
    }

    return mbnode;
}

/**
 * \brief 将缓存还给module本地free列表中
 * \details 和group_buf_queue模块无关
 */
static module_buf_t *module_node_free(module_buffer_node_t *mbnode)
{
    module_buf_t *buf;

    if (!mbnode)
        return NULL;

    buf = mbnode->mbuf;
    mbnode->mbuf = NULL;

    return buf;
}

/**
 * \brief 将缓存推送到对方模块
 * \param m 对方模块
 * \param buf 已实现申请好或获取到并修改了内容的缓存
 */
module_buf_t *module_queue_push(struct module *m, module_buf_t *buf)
{
    module_buffer_node_t *mbnode; // 节点+队列入口+一个缓存
    module_buf_t *ret_buf;

    if (!m || !buf)
        return NULL;

    /* 申请一个目标缓存的节点 */
    mbnode = module_node_alloc(&m->queue_entry, buf);
    if (!mbnode)
        return NULL;

    ret_buf = mbnode->mbuf;

    list_del_init(&mbnode->qnode.node); // 从node自己所属的链表中删除node节点并初始化node节点
    list_add_tail(&mbnode->qnode.node, &m->queue_entry); //node加入到head的前面，也就是entry链表的末尾（因为是双向循环链表）

    return ret_buf;
}

/**
 * \brief 从自己模块的队列中推出一个缓存
 */
module_buf_t *module_queue_pop(struct module *m)
{
    module_buf_t *buf = NULL;
    queue_node_t *queue_node = NULL;
    module_buffer_node_t *mbnode = NULL;
    struct list_head *cur_node, *entry;

    if (!m)
        return NULL;

    entry = &m->queue_entry;
    if (!list_empty_careful(entry)) { // 链表非空
        // 获取入口后面的第一个节点所属的结构体的地址（从子元素地址推导父元素地址）
        queue_node = list_first_entry(entry, queue_node_t, node); // 这里的node只是一个标号，是queue_node_t中的元素名

        cur_node = &queue_node->node;
        list_del_init(cur_node); // 从原链表中删除这个缓存对应的节点

        // 获取该节点下的module节点
        mbnode = list_entry(queue_node, module_buffer_node_t, qnode);
    }

    if (mbnode)
        buf = module_node_free(mbnode);

    return buf;
}

/**
 * \brief 获取目标模块的缓存数量
 */
int module_queue_num(struct module *m)
{
    int count = 0;
    struct list_head *head, *node, *n; // node和n都是临时变量，不用关心

    if (!m)
        return 0;

    head = &m->queue_entry;

    if ( !list_empty_careful(head) ) {
        list_for_each_safe(node, n, head) {
            count++;
        }
    }

    return count;
}
