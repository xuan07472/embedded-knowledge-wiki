/**
 * \file module.c
 * \brief 应用模块统一接口
 * \author 将狼才鲸
 * \date 2022-03-18
 * \remarks 源文件使用Windows(CR LF)换行 + UTF-8编码，tab使用4个空格
 */

#include "module.h"

struct module *module_get(MODULE_TYPE *type)
{

}

struct module *module_next(struct module *m)
{

}

void module_all_create(struct module *g_all_modules[])
{

}

void module_all_destroy(struct module *g_all_modules[])
{

}

MSTATE module_run(struct module *m)
{

}

int module_command(struct module *m, int cmd, void *param)
{

}
