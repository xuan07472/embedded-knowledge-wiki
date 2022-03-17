/**
 * \file list.h
 * \brief 双向循环链表
 *
 * \details 一个借助编译器原理的使用小技巧：当用户自定义的结构体中有该链表入口节点作为成员时，
 *          对链表顺序的操作也就是对自定义结构体的操作，因为通过链表节点地址可以反推出结构体
 *          的地址；更进一步，如果链表节点是结构体中第一个元素，那么链表的地址也是结构体的地址
 *          直接对链表节点地址进行强制类型转换即可得到排好序的结构体地址。
 *
 * \author Linux kernel group
 * \version v5.16
 * \remarks list修改自Linux中的源码
 *          当前最新版v5.16的源码中即有（只有.h头文件，里面用了inline函数，不需要.c源文件）
 *          头文件路径：[Gitee极速下载/Linux Kernel](https://gitee.com/mirrors/linux_old1/blob/v5.16/include/linux/list.h)
 * \note 编码格式：UTF-8 + Window(CR LF)换行
 *
 */

/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LIST_H
#define _LIST_H

#include <stddef.h> // size_t

/**
 * \brief 链表节点结构体
 * \details 拷贝自include/linux/types.h
 */
struct list_head {
	struct list_head *next, *prev;
};

typedef int bool; /* from include/linux/types.h */
#define true	1
#define false	0
#define NULL ((void *)0)

/**
 * \brief 获取结构体中一个元素相对于结构体起始地址的偏移量
 * \details 拷贝自include/linux/stddef.h
 * \param[in] TYPE: 结构体的定义名称，如MY_STRUCT
 * \param[in] MEMBER: 结构体中的成员名称，如subitem
 * \return 结构体中一个元素相对于结构体起始地址的偏移量
 * \remarks 巧用了编译器对0地址的操作
 */
//typedef unsigned int size_t; // from stddef.h, 用Qt+MinGW编译时要注释此条
//#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
/**
 * \brief 从结构体的子元素地址倒推出结构体的首地址
 * \details include/linux/container_of.h
 * \param[in] ptr: 结构体的子元素地址，如&my_struct.subitem
 * \param[in] type: 结构体的名称，如struct MY_STRUCT
 * \param[in] member: 结构体中子元素的名称，如subitem
 * \return 结构体的首地址，等同于&my_struct
 */
#define container_of(ptr, type, member) ({				\
	void *__mptr = (void *)(ptr);					\
	((type *)(__mptr - offsetof(type, member))); })

/*
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized list entries.
 */
/**
 * \brief 定义一个非法的地址值，用于链表节点释放后指向这里
 * \details 这样程序调用了被释放的节点后系统能报错，而不是程序直接跑飞导致很难查问题
 * \note from include/linux/poison.h
 */
#define LIST_POISON1  ((void *) 0x100)
#define LIST_POISON2  ((void *) 0x122)

/******************************************************************************/

/*
 * Circular doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */
/**
 * \brief 定义名为name的链表节点，并初始化它，让它的前指针后指针都指向自己
 */
#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

/**
 * \brief 使用volatile保证没有缓存，数据立马赋值成功
 * \remarks tools/include/linux/compiler.h
 */
#define READ_ONCE(var) (*((volatile typeof(var) *)(&(var))))
#define WRITE_ONCE(var, val) (*((volatile typeof(val) *)(&(var))) = (val))

/**
 * INIT_LIST_HEAD - Initialize a list_head structure
 * @list: list_head structure to be initialized.
 *
 * Initializes the list_head to point to itself.  If it is a list header,
 * the result is an empty list.
 */
/**
 * \brief 初始化链表节点，前指针和后指针都指向自己
 */
static inline void INIT_LIST_HEAD(struct list_head *list)
{
	WRITE_ONCE(list->next, list);
	list->prev = list;
}

static inline bool __list_add_valid(struct list_head *new,
				struct list_head *prev,
				struct list_head *next)
{
	return true;
}
static inline bool __list_del_entry_valid(struct list_head *entry)
{
	return true;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
/**
 * \brief 将new这个节点加入到prev这个节点标示的链表开头
 * \details 因为是双向循环链表，所以加在prev入口节点的后面也就是加在了链表的最前面（入口节点不算有效节点），
 *          prev实际是是这个链表的开头，后面跟着最新加入的有效数据
 * \param new 要加入的节点
 * \param prev 链表入口，也就是entry
 * \param next 链表入口的下一个节点（原来的第一个最早加入的元素）
 */
static inline void __list_add(struct list_head *new, // 要加入的元素
			      struct list_head *prev, // 开头
			      struct list_head *next) // 第一个元素
{
    if (!__list_add_valid(new, prev, next))
		return;

    //       末尾            开头      第一个
    // 之前：entry->prev <== entry <== entry->next

    next->prev = new; // new ..< entry->next
    new->next = next; // new <== entry->next
    new->prev = prev; // entry ..< new
    WRITE_ONCE(prev->next, new); // entry <== new

    //       开头      第一个  第二个
    // 之后：entry <== new <== entry->next
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
/**
 * \brief 将new这个节点加入到head这个节点标示的链表开头（第一个有效节点）
 * \param new 要加入的节点
 * \param head 链表入口（后面跟着第一个有效数据）
 * \note 此函数暂未使用
 */
static inline void list_add(struct list_head *new, struct list_head *head)
{
    //       末尾           入口     第一个
    // 之前：head->prev <== head <== head->next

    __list_add(new, head, head->next);

    //       入口     第一个  第二个
    // 之后：head <== new <== head->next
}

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
/**
 * \brief 把新加入的new节点放到head链表的末尾（最后才pop的元素）
 * \note 此接口用来实现队列的数据推入

 */
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    //       倒数第二个           倒数第一个     开头
    // 之前：head->prev->prev <== head->prev <== head

    __list_add(new, head->prev, head);

    //       倒数第三个           倒数第二个      倒数第一个  开头
    // 之后：head->prev->prev ==>  head->prev ==> new ==>     head
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
/**
 * \brief 在链表中删除一个节点，将前后再重新接起来
 */
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    // 之前：prev <== 未知节点 <== next

	next->prev = prev;
	WRITE_ONCE(prev->next, next);

    // 之后：prev <== next
}

/*
 * Delete a list entry and clear the 'prev' pointer.
 *
 * This is a special-purpose list clearing method used in the networking code
 * for lists allocated as per-cpu, where we don't want to incur the extra
 * WRITE_ONCE() overhead of a regular list_del_init(). The code that uses this
 * needs to check the node 'prev' pointer instead of calling list_empty().
 */
/**
 * \brief 在链表中删除entry这个节点，将前后再重新接起来，并且只保留该节点的下一个指针
 */
static inline void __list_del_clearprev(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->prev = NULL;
}

/**
 * \brief 在链表中删除entry这个节点，将前后再重新接起来，原节点内容不删除
 */
static inline void __list_del_entry(struct list_head *entry)
{
	if (!__list_del_entry_valid(entry))
		return;

	__list_del(entry->prev, entry->next);
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
/**
 * \brief 在链表中删除entry这个节点，将前后再重新接起来，并且清除原节点内容
 */
static inline void list_del(struct list_head *entry)
{
	__list_del_entry(entry);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}

/**
 * list_replace - replace old entry by new one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
/* 将old节点替换成new节点 */
static inline void list_replace(struct list_head *old,
                struct list_head *new)
{
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}

/**
 * list_replace_init - replace old entry by new one and initialize the old one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
/* 将old节点替换为new节点，并且初始化替换下来的old节点 */
static inline void list_replace_init(struct list_head *old,
                     struct list_head *new)
{
    list_replace(old, new);
	INIT_LIST_HEAD(old);
}

/**
 * list_swap - replace entry1 with entry2 and re-add entry1 at entry2's position
 * @entry1: the location to place entry2
 * @entry2: the location to place entry1
 */
/* 交换两个节点的位置 */
static inline void list_swap(struct list_head *entry1,
			     struct list_head *entry2)
{
	struct list_head *pos = entry2->prev;

	list_del(entry2);
	list_replace(entry1, entry2);
	if (pos == entry1)
		pos = entry2;
	list_add(entry1, pos);
}

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
/* 删除并初始化一个节点 */
static inline void list_del_init(struct list_head *entry)
{
	__list_del_entry(entry);
	INIT_LIST_HEAD(entry);
}

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
/* 从原来的链表中删除list节点并加入到另一个链表head后面 */
static inline void list_move(struct list_head *list, struct list_head *head)
{
	__list_del_entry(list);
	list_add(list, head);
}

/**
 * list_is_head - tests whether @list is the list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static inline int list_is_head(const struct list_head *list, const struct list_head *head)
{
    return list == head;
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head)
{
	return READ_ONCE(head->next) == head;
}

/**
 * list_empty_careful - tests whether a list is empty and not being modified
 * @head: the list to test
 *
 * Description:
 * tests whether a list is empty _and_ checks that no other CPU might be
 * in the process of modifying either member (next or prev)
 *
 * NOTE: using list_empty_careful() without synchronization
 * can only be safe if the only activity that can happen
 * to the list entry is list_del_init(). Eg. it cannot be used
 * if another CPU could re-list_add() it.
 */
static inline int list_empty_careful(const struct list_head *head)
{
	struct list_head *next = (struct list_head *)&head->next;
	return list_is_head(next, head) && (next == head->prev);
}

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
/**
 * \brief 这里可以获取到包含该链表节点的上级结构体的真实地址，比如ptr是list_node地址，而返回的却是QUEUE_STRUCT的地址
 * \details 宏定义目的：从一个子元素地址返回主结构体地址
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Note, that list is expected to be not empty.
 */
/**
 * \brief 获取入口后面的第一个节点所属的结构体的地址
 */
#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
/* 用于对链表所有的节点进行计数 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; !list_is_head(pos, (head)); pos = pos->next)

/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:	the &struct list_head to use as a loop cursor.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; \
	     !list_is_head(pos, (head)); \
	     pos = n, n = pos->next)

#endif // _LIST_H

//**** 参考资料 ****//
//[linux内核中的list详解](https://blog.csdn.net/qq_26617115/article/details/53509321)
