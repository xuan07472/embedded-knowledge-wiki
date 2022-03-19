/**
 * \file module_unitest.c
 * \brief 统一格式的模块的单元测试用例
 * \author 将狼才鲸
 * \date 2022-03-19
 * \remarks 如果用Qt编译则只能用Qt + MinGW，用MSVC时会报错编不过（使用了GNU C扩展关键字时）
 *          如果是自己用Qt创建工程，则只能选Paint C，不能选Paint C++，否则会报new等关键字
 *          使用错误或者高级的类型强制转换不支持等；推荐直接使用gcc + make编译
 */

#include "module.h"
#include "group_buf_queue_init.h"

#include <stdio.h>
#include "module.h"

#define GROUP_QUEUE_UNITEST
#define ALL_UNITEST

extern struct module g_module1;
extern struct module g_module2;
extern struct module g_module3;

static struct module *g_modules[] = {
    &g_module1,
    &g_module2,
    &g_module3,
    NULL, // NULL是用来标示模块循环结尾的
};

/**
 * \brief 模块接口测试
 */
int module_unitest(void)
{
    int i;
    int ret;
    int result = 0;
    MSTATE state;
    struct module *top_module;

    printf("```````` %s start ````````\n", __func__);

    /* 1.初始化系统缓存 */
    group_buf_queue_init();

    /* 2.初始化所有模块 */
    module_all_create(g_modules);

    /* 3.获取顶层模块 */
    top_module = module_get(MODULE_VIDEO_IN);

    /* 4.启动顶层模块 */
    if (top_module)
        top_module->module_start(top_module, NULL);

    /* 5.运行模块 */
    i = 3;
    while (i--) {
        if (top_module->state == STATE_IDLE) {
            // 此时方可发送数据
        }

        state = top_module->module_process(top_module);
        if (state <= STATE_CREATE)
            break;
    }

    /* 6.停止顶层模块 */
    if (top_module)
        top_module->module_stop(top_module);

    /* 7.销毁所有模块 */
    module_all_destroy(g_modules);

    /* 8.打印测试结果 */
    printf("________ %s test %s ________\n\n", __func__, result ? "FAIL!": "pass.");

    return result;
}

#ifdef ALL_UNITEST
int main()
{
    int ret;
    int result = 0;

    ret = module_unitest();
    if (ret)
        result = -1;

    if (result)
        printf("%s test FAIL!\n", __FILE__);
    else
        printf("%s test pass.\n", __FILE__);

    return 0;
}
#endif // ALL_UNITEST
