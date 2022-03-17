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

#define GROUP_QUEUE_UNITEST
#define ALL_UNITEST

int buffer_unitest(void)
{
    group_buf_queue_init();
    
    return 0;
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
