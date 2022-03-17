/**
 * \file buffer_config.h
 * \brief 缓存地址
 * \remarks 和具体硬件相关的操作独立出单独的文件，以后统统放到arch/文件夹下，
 *          让你的代码可复用，以后换了公司、换了平台、换了芯片之后自己的架构代码只需要
 *          小改即可，否则硬件相关的和纯逻辑的代码混合写在一起的话，更换平台后代码
 *          不好移植
 */

#ifndef _BUFFER_CONFIG_H
#define _BUFFER_CONFIG_H

extern unsigned char *MSGBUF_START_ADDR; // 当前的地址用数组地址代替，真实嵌入式板子中就是一个地址值
#define MSGBUF_PER_BUF_SIZE 512 // 长度需要是4字节对齐的
#define MSGBUF_MAX_BUF_CNT 16

extern unsigned char *DATBUF_START_ADDR;
#define DATBUF_PER_BUF_SIZE 1024
#define DATBUF_MAX_BUF_CNT 32

#define BUFFER_MAX_COUNT (MSGBUF_MAX_BUF_CNT + DATBUF_MAX_BUF_CNT)

void buffer_config(void);

#endif // _BUFFER_CONFIG_H
