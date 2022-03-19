/**
 * \file module.h
 * \brief 应用模块统一接口
 * \author 将狼才鲸
 * \date 2022-03-18
 * \remarks 源文件使用Windows(CR LF)换行 + UTF-8编码，tab使用4个空格
 */

#ifndef _MODULE_H
#define _MODULE_H

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
struct module {

    const char name[64];
    MODULE_TYPE type;
    MSTATE state; // 状态机
    void *handle; // 每个模块自己专有的数据结构体，类似于C++ class中的private
    void *(*module_create)(struct mudule *m); // 函数指针
    void (*module_distroy)(struct mudule *m);
    int (*module_start)(struct mudule *m, void *param);
    int (*module_stop)(struct mudule *m);
    MSTATE (*module_process)(struct mudule *m);
    int (*module_control)(struct mudule *m, int cmd, void *param);
    struct list_head queue_entry;
};



#endif // _MODULE_H
