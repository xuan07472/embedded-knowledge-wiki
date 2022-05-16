/**
 * \brief PCP(Private communication peotocol)私有通信协议单元测试用例
 * \details 两个线程之间、两个CPU核之间、或者两个设备之间的通信测试
 * \date 2022-05-16
 * \note 本Qt工程只能使用MinGW编译，不能使用MSVC
 */

/**** 头文件 ****/
#include <stdio.h>  // printf
#include <string.h> // strncmp strlen
// 需要在Qt .pro文件中加入pthread的CFLAG和库
#include <pthread.h> // pthread_t pthread_create
#include <unistd.h> // sleep

/**** 宏定义 ****/
#define ALL_UNITEST // 整个系统统一执行所有的模块测试用例
#define GROUP_COMMUNICATION_PROTOCOL_UNITEST // 执行单独的单元测试用例
#define pr_info printf // 预留用作输出重定向
#define EPERM 1 // from linux errno.h
#define test_msg "my test data" // 本测试用的字符串

/**** 模块私有函数 ****/
static int server_init(void)
{
//    pcp_host_msg_init();

    return 0;
}

static int server_run(void)
{
//    pcp_host_msg_run();

    return 0;
}

static int server_exit(void)
{
//    pcp_host_msg_exit();

    return 0;
}


static int client_init(void)
{
//    pcp_client_msg_init();

    return 0;
}

static int client_send_message(void *data, int len)
{
#define MSG_CMD_DEBUG 1
    int ret;
    int cmd = MSG_CMD_DEBUG;

    if (!data || !len)
        return -EPERM;

//    ret = pcp_client_msg_send(MSG_CMD_DEBUG, data, len);

    return ret;
}

static int client_get_message(void *data, int *len)
{
#define MSG_CMD_DEBUG 1
    int ret;
    int cmd = MSG_CMD_DEBUG;

    if (!data || !len)
        return -EPERM;

//    ret = pcp_client_msg_get(MSG_CMD_DEBUG, data, len);

    return ret;
}

static int client_exit(void)
{
//    pcp_client_msg_exit();

    return 0;
}

static void *server_thread(void *param)
{
    while (1) {
        pr_info("t ");
        fflush(stdout); // Qt中要使用fflush实时输出打印的信息，否则看不到信息输出
        sleep(1);
    }

    return NULL;
}

#ifdef ALL_UNITEST
/**** 模块接口函数 ****/
/**
 * \brief 私有通信协议单元测试用例
 * \details 客户端发送一个字符串，然后再从服务器端读取一个字符串，
 *          服务器端返回的字符串会在之前缓存的字符串前面加上“host: ”字符串
 *          并返回
 */
int pcp_unitest(void)
{
#define HOST_REBACK_STR "host: "
#define RECV_BUF_LEN 32
    int ret = 0;
    int rlen = 0;
    char rbuf[RECV_BUF_LEN];
    pthread_t thread;

    pr_info("%s enter\n", __func__);

    /* 1. 创建服务器端线程并运行 */
    ret = pthread_create(&thread, NULL, server_thread, NULL);

    /* 2. 开始执行客户端代码，本函数剩下的部分都是客户端代码 */
    /* 2-1. 客户端初始化 */
    client_init();

    /* 2-2. 客户端发送消息并获取响应 */
    ret = client_send_message(test_msg, strlen(test_msg) + 1);
    if (ret) {
        pr_info("%s test fail!\n", __func__);
        goto exit;
    }

    ret = client_get_message(rbuf, &rlen);
    if (ret || !rlen) {
        pr_info("%s test fail!\n", __func__);
        goto exit;
    }

    /* 字符串比较 */
    ret = strncmp(rbuf, HOST_REBACK_STR, strlen(HOST_REBACK_STR));
    if (ret) {
        pr_info("%s test fail!\n", __func__);
        goto exit;
    }

    int origin_pos = strlen(HOST_REBACK_STR);
    ret = strncmp(rbuf + origin_pos, test_msg, strlen(test_msg));
    if (ret)
        pr_info("%s test fail!\n", __func__);
    else
        pr_info("%s test pass\n", __func__);

exit:
    /* 2-3. 客户端退出 */
    client_exit();

    return ret;
}
#endif // ALL_UNITEST

#ifdef GROUP_COMMUNICATION_PROTOCOL_UNITEST
/* 单独的单元测试用例 */
int main()
{
    pcp_unitest();

    while (1) {
        pr_info("m ");
        fflush(stdout); // Qt中要使用fflush实时输出打印的信息，否则看不到信息输出
        sleep(1);
    }

    return 0;
}
#endif // GROUP_COMMUNICATION_PROTOCOL_UNITEST
