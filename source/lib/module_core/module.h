/**
 * \file module.h
 * \brief 应用模块统一接口
 * \author 将狼才鲸
 * \date 2022-03-18
 * \remarks 源文件使用Windows(CR LF)换行 + UTF-8编码，tab使用4个空格
 */

#ifndef _MODULE_H
#define _MODULE_H

#include "list.h"
#include "group_buf_queue.h"

/**
 * \brief 状态机
 * \details 多线程、多任务、多模块相互配合循环运行时就要用到状态机，进行模块分离
 */
typedef enum {
    STATE_NULL = 0,
    STATE_CREATE,
    STATE_PROCESS,
    STATE_IDLE,
    STATE_PAUSE,
    STATE_DESTROY,
}MSTATE;

/**
 * \brief 所有的模块类型
 */
typedef enum _MODULE_TYPE{
    MODULE_AUDIO_IN = 0,
    MODULE_AUDIO_OUT,
    MODULE_VIDEO_IN,
    MODULE_VIDEO_OUT,
    MODULE_AUDIO_DECODE,
    MODULE_AUDIO_ENCODE,
    MODULE_VIDEO_DECODE,
    MODULE_VIDEO_ENCODE,
    MODULE_AV_SYNC,
} MODULE_TYPE;

/**
 * \brief 模块的所有操作命令
 */
typedef enum {
    MCMD_NONE = 0,
    MCMD_SKIP, // 跳过一段数据的处理
    MCMD_GET_SPEED, // 获取当前速度
    MCMD_SET_SPEED, // 设置速度
} MCMD;

/**
 * \brief 模块私有数据
 * \details 类似于C++ class中定义的变量和方法
 */
struct module{
    const char name[64];
    MODULE_TYPE type;
    MSTATE state; // 状态机
    void *handle; // 每个模块自己专有的数据结构体，类似于C++ class中的private
    void *(*module_create)(struct module *m); // 函数指针
    void (*module_distroy)(struct module *m);
    int (*module_start)(struct module *m, void *param);
    int (*module_stop)(struct module *m);
    MSTATE (*module_process)(struct module *m);
    int (*module_control)(struct module *m, int cmd, void *param);
    struct list_head queue_entry;
};

/**************** 以下是module_queue.h需要的结构体和函数申明 ****************/

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
extern void module_queue_init(struct module *m);

/**
 * \brief 销毁自己模块的缓存队列，将用过的缓存还给group_buf_queue模块
 */
extern void module_queue_exit(struct module *m);

/**
 * \brief 将缓存推送到对方模块
 * \param m 对方模块
 * \param buf 已实现申请好或获取到并修改了内容的缓存
 */
extern module_buf_t *module_queue_push(struct module *m, module_buf_t *buf);

/**
 * \brief 从自己模块的队列中推出一个缓存
 */
extern module_buf_t *module_queue_pop(struct module *m);

/**
 * \brief 获取目标模块的缓存数量
 */
extern int module_queue_num(struct module *m, module_buf_t *buf);

#endif // _MODULE_H
