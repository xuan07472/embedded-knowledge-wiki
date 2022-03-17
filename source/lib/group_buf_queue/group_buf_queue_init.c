#include "group_buf_queue_init.h"
#include "group_buf_queue.h"
#include "arch_buffer_config.h"

void group_buf_queue_init(void)
{
    buffer_group_t buffer_group;
    
    all_buffer_group_default_init();
    buffer_config();
    
    buffer_group.addr = MSGBUF_START_ADDR; // 整个缓存组的起始地址
    buffer_group.unitsize = MSGBUF_PER_BUF_SIZE; // 单个缓存的长度，同组内每个缓存的长度都一样
    buffer_group.count = MSGBUF_MAX_BUF_CNT; // 缓存个数
    group_buf_init(&buffer_group, BUFFER_GROUP_MSG);
    
    buffer_group.addr = DATBUF_START_ADDR; // 整个缓存组的起始地址
    buffer_group.unitsize = DATBUF_PER_BUF_SIZE; // 单个缓存的长度，同组内每个缓存的长度都一样
    buffer_group.count = DATBUF_MAX_BUF_CNT; // 缓存个数
    group_buf_init(&buffer_group, BUFFER_GROUP_DATA);
}