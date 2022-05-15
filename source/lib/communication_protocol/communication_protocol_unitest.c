
#define GROUP_COMMUNICATION_PROTOCOL_UNITEST
#define ALL_UNITEST

#include <stdio.h>

#ifdef GROUP_COMMUNICATION_PROTOCOL_UNITEST
int main()
{
    printf("Hello World!\n");

    UtpApp_Msg_Client_Init();

    return 0;
}
#endif // GROUP_COMMUNICATION_PROTOCOL_UNITEST
