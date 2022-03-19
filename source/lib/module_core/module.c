/**
 * \file module.c
 * \brief 应用模块统一接口
 * \author 将狼才鲸
 * \date 2022-03-18
 * \remarks 源文件使用Windows(CR LF)换行 + UTF-8编码，tab使用4个空格
 */

#include "module.h"

#define EINVAL 22 // from errno.h
#define EACCES 13

/* 未初始化时指向的空模块组 */
static struct module *g_modules_null[2] = {NULL, NULL};
/* 初始化时会重新赋值的全局变量 */
static struct module **g_all_modules = (struct module **)g_modules_null;

/**
 * \brief 按类型获取模块指针
 */
struct module *module_get(MODULE_TYPE type)
{
    struct module *m = NULL;
    int index = 0;

    while (g_all_modules[index]) {
        m = g_all_modules[index];
        if (m->type == type)
            break;

        index++;
        m = NULL;
    }

    return m;
}

/**
 * \brief 按顺序获取模块指针
 */
struct module *module_next(struct module *m)
{
    struct module *module = NULL;
    int index = 0;

    if (!m)
        return (struct module *)g_all_modules[0];

    while (g_all_modules[index]) {
        module = g_all_modules[index];
        if (module == m) {
            module = g_all_modules[index + 1];
            break;
        }

        index++;
        module = NULL;
    }

    return module;
}

/**
 * \brief 创建所有模块
 */
void module_all_create(struct module *all_modules[])
{
    struct module *m;

    /* 初始化所有缓存节点 */
    module_all_nodes_init();

    /* 赋值全局变量 */
    g_all_modules = (struct module **)all_modules;

    int index = 0;
    while (g_all_modules[index]) {
        m = g_all_modules[index];
        m->state = STATE_NONE;
        m->module_create(m); // 初始化模块
        module_queue_init(m); // 初始化模块缓存
        index++;
    }
}

/**
 * \brief 销毁所有模块
 */
void module_all_destroy(struct module *all_modules[])
{
    struct module *m;
    int index = 0;

    while (all_modules[index]) {
        m = all_modules[index];
        m->module_distroy(m); // 销毁模块
        index++;
    }
}

/**
 * \brief 运行一个模块
 */
MSTATE module_run(struct module *m)
{
    int index;
    MSTATE state;

    if (!m)
        return -EINVAL;

    /* 防止运行未初始化过的模块 */
    while (g_all_modules[index]) {
        if (m == g_all_modules[index])
            break;

        index++;
    }
    if (g_all_modules[index] == NULL)
        return -EACCES;

    /* 运行该模块 */
    state = m->module_process(m);

    return state;
}

/**
 * \brief 执行模块的私有函数
 */
int module_command(struct module *m, int cmd, void *param)
{
    int ret, index;
    MSTATE state;

    if (!m)
        return -EINVAL;

    /* 防止执行未初始化过模块的函数 */
    while (g_all_modules[index]) {
        if (m == g_all_modules[index])
            break;

        index++;
    }
    if (g_all_modules[index] == NULL)
        return -EACCES;

    /* 执行模块的私有函数 */
    ret = m->module_control(m, cmd, param);

    return ret;
}
