/**
 * \file group_buf_queue_unitest.c
 * \brief 队列组单元测试用例
 * \author 将狼才鲸
 * \date 2022-03-15
 * \remarks 如果用Qt编译则只能用Qt + MinGW，用MSVC时会报错编不过（使用了GNU C扩展关键字时）
 *          如果是自己用Qt创建工程，则只能选Paint C，不能选Paint C++，否则会报new等关键字
 *          使用错误或者高级的类型强制转换不支持等
 */

#include "group_buf_queue_init.h"
#include "arch_buffer_config.h"
#include "group_buf_queue.h"
#include "pair_list.h"
#include "list.h"
#include <stdio.h> // printf
#include <string.h> // strlen strcmp memcpy

#define GROUP_QUEUE_UNITEST
#define ALL_UNITEST

/**
 * \brief 缓存测试
 */
int buffer_unitest(void)
{
#define BUF_TEST_DATA ":) my first buffer message ^_^"

    /* 1. 缓存初始化 */
    group_buf_queue_init();
    
    /* 2. 获取缓存 */
    buffer_t *buf = buffer_alloc(BUFFER_GROUP_MSG);
    printf("got buf: [group_flag: %d] [addr: 0x%08x] [buf_maxsize: %d] [len: %d]\n",
            buf->group_flag,
            buf->addr,
            buf->buf_maxsize,
            buf->len);
    
    /* 3.赋值数据 */
    unsigned char *testmsg = BUF_TEST_DATA;
    memcpy(buf->addr, testmsg, strlen(testmsg) + 1);
    buf->len = strlen(testmsg) + 1;
    printf("push data: %s\n", testmsg);
    
    /* 4.推送数据 */
    buffer_push(buf);
    
    /* 5.获取数据 */
    buffer_t *buf_got = buffer_pop(BUFFER_GROUP_MSG);
    printf("got buf data: [group_flag: %d] [msg: %s] [len: %d]\n",
            buf_got->group_flag,
            buf_got->addr,
            buf_got->len);
    
    /* 6.释放缓存 */
    buffer_free(buf_got);
    
    /* 7.比较测试结果 */
    int result = strcmp(buf->addr, buf_got->addr);
    printf("--------buffer_unitest test %s--------\n\n", result ? "FAIL!": "pass.");
    
    return result;
}

int pair_list_unitest(void)
{
    
}

int circular_linked_list_unitest(void)
{
    struct list_head entry, new1, new2;

    INIT_LIST_HEAD(&entry);
    list_add(&new1, &entry);
    list_add_tail(&new2, &entry);
    
    return 0;
}

#ifdef ALL_UNITEST
int main()
{
    int ret = 0;
    
    ret = buffer_unitest();

    if (0 == ret)
        printf("%s test pass\n", __FILE__);

    return 0;
}
#endif // ALL_UNITEST
