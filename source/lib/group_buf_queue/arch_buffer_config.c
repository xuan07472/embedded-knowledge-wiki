#include "arch_buffer_config.h"

unsigned char *MSGBUF_START_ADDR;
unsigned char *DATBUF_START_ADDR;

unsigned char message_buffer[MSGBUF_MAX_BUF_CNT * MSGBUF_PER_BUF_SIZE];
unsigned char data_buffer[DATBUF_MAX_BUF_CNT * DATBUF_PER_BUF_SIZE];

void buffer_config(void)
{
    MSGBUF_START_ADDR = (unsigned char *)message_buffer;
    DATBUF_START_ADDR = (unsigned char *)data_buffer;
}
