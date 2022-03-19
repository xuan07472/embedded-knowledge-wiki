/**
 * \file module_queue.h
 * \brief 模块缓存，依赖group_buf_queue.h
 * \details group_buf有个机制，如果你alloc后并没有put到group组的链表对中去，那你
 *          就可以独立使用这个缓存，原来的缓存组既申请不到它也用不了它，那么你可以
 *          将它put到自己写成的队列中去，用完后再free回原来的group_buf队列
 * \note 当前设计的一个模块只保存一个缓存队列，够用了，如果以后想一个模块
 *       保存多个队列，如消息和数据，音频和视频分开从多个模块进来，那么可以
 *       参照group_buf_queue模块，将本模块struct list_head *queue_entry
 *       换成pair_list_t即可实现
 * \author 将狼才鲸
 * \date 2022-03-18
 * \remarks 源文件使用Windows(CR LF)换行 + UTF-8编码，tab使用4个空格
 */

#ifndef _MODULE_QUEUE_H
#define _MODULE_QUEUE_H

#include "group_buf_queue.h"
#include "arch_buffer_config.h"
#include "module.h"

/**** 具体module_queue.h需要的结构体和函数申明在module.h中 ****/

#endif // _MODULE_QUEUE_H
