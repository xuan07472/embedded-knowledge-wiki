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
#define BUF_TEST_DATA ":) my first buffer message ^_^"

/**
 * \brief 缓存测试
 */
int buffer_unitest(void)
{
    printf("```````` %s start ````````\n", __func__);
    
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
    printf("________ %s test %s ________\n\n", __func__, result ? "FAIL!": "pass.");
    
    return result;
}

int pair_list_unitest(void)
{
    typedef struct _user_struct {
        pair_list_node_t mynode;
        unsigned char mydata[32];
    } user_struct;

    pair_list_t my_pair_list;
    user_struct mystruct[16] = {0};
    user_struct *pmystruct, *getstruct;
    pair_list_node_t *pnode;

    printf("```````` %s start ````````\n", __func__);

    /* 1.初始化 */
    pair_list_init(&my_pair_list);
    for (int i = 0; i < 16; i++) {
        pnode = &mystruct[i].mynode;
        INIT_LIST_HEAD(&pnode->node);
        pnode->pair_list = &my_pair_list;
        pair_list_free(pnode);
    }
    
    /* 2.获取数据体 */
    pnode = pair_list_alloc(&my_pair_list);
    pmystruct = container_of(pnode, user_struct, mynode);
    
    /* 3.赋值数据 */
    strcpy(pmystruct->mydata, BUF_TEST_DATA);
    printf("put data: %s\n", pmystruct->mydata);
    
    /* 4.推送数据 */
    pair_list_put(NULL, &pmystruct->mynode, PAIR_LIST_USED);
    
    /* 5.获取数据 */
    pnode = pair_list_get(&my_pair_list, PAIR_LIST_USED);
    getstruct = container_of(pnode, user_struct, mynode);
    printf("got data: %s\n", getstruct->mydata);
    
    /* 6.比较数据 */
    int result = strcmp(getstruct->mydata, BUF_TEST_DATA);
    printf("________ %s test %s ________\n\n", __func__, result ? "FAIL!": "pass.");

    /* 7.释放结构体 */
    pair_list_free(&getstruct->mynode);
    
    return result;
}

int circular_linked_list_unitest(void)
{
	int count;
    int result = 0;
    struct list_head entry, new1, new2;
	struct list_head *head, *node, *n; // node和n都是临时变量，不用关心

    printf("```````` %s start ````````\n", __func__);

    INIT_LIST_HEAD(&entry);
    
    printf("put a node\n");
    list_add(&new1, &entry);
    head = &entry;
    count = 0;
	if (!list_empty_careful(head)) { // 如果链表非空
		list_for_each_safe(node, n, head) { // 循环宏定义语句
			count++;
		}
	}
    printf("node count: %d\n", count);
    if (count != 1)
        result = -1;

    printf("put a tail node\n");
    list_add_tail(&new2, &entry);
    head = &entry;
    count = 0;
	if (!list_empty_careful(head)) { // 如果链表非空
		list_for_each_safe(node, n, head) { // 循环宏定义语句
			count++;
		}
	}
    printf("node count: %d\n", count);
    if (count != 2)
        result = -1;

    printf("delete a node\n");
    list_del(&new1);
    head = &entry;
    count = 0;
	if (!list_empty_careful(head)) { // 如果链表非空
		list_for_each_safe(node, n, head) { // 循环宏定义语句
			count++;
		}
	}
    printf("node count: %d\n", count);
    if (count != 1)
        result = -1;

    printf("________ %s test %s ________\n\n", __func__, result ? "FAIL!": "pass.");

    return 0;
}

#ifdef ALL_UNITEST
int main()
{
    int ret;
    int result = 0;
    
    ret = buffer_unitest();
    if (ret)
        result = -1;
    
    ret = pair_list_unitest();
    if (ret)
        result = -1;

    ret = circular_linked_list_unitest();
    if (ret)
        result = -1;
    
    if (result)
        printf("%s test FAIL!\n", __FILE__);
    else
        printf("%s test pass.\n", __FILE__);

    return 0;
}
#endif // ALL_UNITEST
