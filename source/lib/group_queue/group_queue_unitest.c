/**
 * \brief 队列组单元测试用例
 * \author 将狼才鲸
 * \date 2022-03-15
 */

#include "list.h"

#define GROUP_QUEUE_UNITEST
#define ALL_UNITEST

#ifdef ALL_UNITEST
int main()
{
    struct list_head entry, new1, new2;

    INIT_LIST_HEAD(&entry);
    list_add(&new1, &entry);
    list_add_tail(&new2, &entry);

    return 0;
}
#endif // ALL_UNITEST