/**
 * \brief 队列组单元测试用例
 * \author 将狼才鲸
 * \date 2022-03-15
 * \remarks 如果用Qt编译则只能用Qt + MinGW，用MSVC时会报错编不过（使用了GNU C扩展关键字时）
 *          如果是自己用Qt创建工程，则只能选Paint C，不能选Paint C++，否则会报new等关键字
 *          使用错误或者高级的类型强制转换不支持等
 */

#include <stdio.h>
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
    printf("%s test pass\n", __FILE__);

    return 0;
}
#endif // ALL_UNITEST
