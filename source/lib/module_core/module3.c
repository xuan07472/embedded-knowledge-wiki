/**
 * \brief 测试模块3
 */

#include "module.h"
#include <stdio.h>
#include <string.h>

#define EPERM 1 // from errno.h
#define EINVAL 22

/**
 * \brief 本模块唯一存放全局变量的地方
 */
typedef struct _module_unit {
    struct module *m; // 自己模块的入口
    struct module *m_target; // 目标模块，所有处理过的数据都只能送给它
    // 缓存阈值，本模块的缓存已经被存入了这个数，就再也不允许上级模块送数据下来了
    int buffer_threshold;
    char self_data[64]; // 私有数据
} m_unit_t;

/* 本模块唯一的全局变量 */
static m_unit_t gm_unit;

static int module_stop(struct module *m);
static MSTATE module_process(struct module *m)
{
    int ret = 0;
    module_buf_t *buf = NULL;
    char *mydata = " '^..^ ^_^ from module3 3 3' ";
    m_unit_t *munit;
    if (!m)
        return STATE_NONE;
    munit = (m_unit_t *)m->handle;

    printf(" '%s' %s\n", m->name, __func__);

    /* 状态控制1 */
    if (m->state == STATE_STOP) {
        if (munit->m_target) {
            // 通知子模块stop
            MSTATE target_state = STATE_STOP;
            module_command(munit->m_target, MCMD_SET_STATE, (void *)&target_state);
        }
        m->module_stop(m); // stop自己模块
    }

    /* 级联运行 */
    if (munit->m_target)
        module_run(munit->m_target);

    /* 状态控制2 */
    if (m->state != STATE_IDLE && m->state != STATE_PROCESS)
        return m->state;

    /* 数据处理 */
    buf = module_queue_pop(m);
    if (buf) {
        printf("%s got data: %s <<<<<<<< \n\n", m->name, buf->addr);
    }
    if (module_queue_num(m) >= munit->buffer_threshold)
        m->state = STATE_PROCESS; // 数据缓存已满

    if (munit->m_target) {
        // 如果下级模块缓存阈值没满，可以发送数据
        if (munit->m_target->state == STATE_IDLE) {
            if (buf) {
                strcpy(buf->addr, mydata);
                buf->len = strlen(mydata) + 1;
                printf("\n%s put data: %s >>>>>>>>\n", m->name, buf->addr);
                module_queue_push(munit->m_target, buf);
            }
        }
    }

    if (buf) {
        module_queue_free(buf);
    }

    return m->state;
}

static int module_control(struct module *m, int cmd, void *param)
{
    int ret = 0;
    m_unit_t *munit;
    if (!m || m->state < STATE_CREATE) // 状态控制
        return -EPERM;
    munit = (m_unit_t *)m->handle;

    switch (cmd) {
    case MCMD_SKIP:
        break;
    case MCMD_GET_SPEED:
        break;
    case MCMD_SET_SPEED:
        break;
    case MCMD_SET_STATE:
        if (*(MSTATE *)param == STATE_STOP) {
            if (m->state >= STATE_CREATE)
                m->state = *(MSTATE *)param;
        }
        break;
    default:
        printf("module '%s' command %d unknown!\n", m->name, cmd);
        ret = -EINVAL;
        break;
    }

    return ret;
}

static void module_distroy(struct module *m)
{
    m_unit_t *munit;
    if (!m)
        return;
    munit = (m_unit_t *)m->handle;

    printf(" '%s' %s\n", m->name, __func__);

    /* 销毁用过的资源 */
    module_queue_exit(m);

    m->handle = NULL;
}

/**
 * \brief 关闭模块，只能由上级模块调用下级模块依次关闭
 */
static int module_stop(struct module *m)
{
    m_unit_t *munit;
    if (!m || m->state < STATE_IDLE) // 状态控制
        return -EPERM;
    munit = (m_unit_t *)m->handle;

    printf(" '%s' %s\n", m->name, __func__);

    /* 清理用过的资源 */
    module_queue_exit(m);
    if (munit->m_target)
        munit->m_target->module_stop(munit->m_target);

    m->state = STATE_CREATE;

    return 0;
}

/**
 * \brief 重新准备好运行的条件
 * \details 注意：多次重新运行时m_unit_t中的全局数据并没有被清理，有记忆功能，
 *          有需要的话可以在module_control()中做一个清理所有全局变量的接口
 */
static int module_start(struct module *m, void *param)
{
/* 本缓存阈值，本模块的缓存已经被存入了这个数，就再也不允许上级模块送数据下来了 */
#define BUFFER_THRESHOLD 2
    m_unit_t *munit;
    if (!m || m->state < STATE_CREATE) // 状态控制
        return -EPERM;
    munit = (m_unit_t *)m->handle;

    printf(" '%s' %s\n", m->name, __func__);

    /* 初始化自己用到的数据 */
    module_queue_exit(m);
    munit->buffer_threshold = BUFFER_THRESHOLD;

    // 默认目标模块为空
    munit->m_target = NULL;
    if (munit->m_target)
        munit->m_target->module_start(munit->m_target, NULL);

    m->state = STATE_IDLE;

    return 0;
}

static void *module_create(struct module *m)
{
    m_unit_t *munit = &gm_unit;

    if (!m)
        return NULL;

    printf(" '%s' %s\n", m->name, __func__);

    memset(munit, 0, sizeof(m_unit_t));
    munit->m = m;
    m->handle = (void *)munit;
    m->state = STATE_CREATE;

    m->module_distroy = module_distroy;
    m->module_start = module_start;
    m->module_stop = module_stop;
    m->module_process = module_process;
    m->module_control = module_control;

    return m->handle;
}

/**
 * \brief 本模块唯一对外开放的结构体，类似于C++的class new
 * \details 不开放函数接口，靠函数指针调用执行
 */
struct module g_module3 = {
    "module3 \\\\\\3///", MODULE_VIDEO_OUT,
    &module_create,
    };
