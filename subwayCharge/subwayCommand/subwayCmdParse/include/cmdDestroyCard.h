#ifndef __CMD_DESTROY_CARD_H__
#define __CMD_DESTROY_CARD_H__
#include <string>
#include "subwayCmdParse/include/cmdGlobal.h"

//命令中的每个信元
typedef enum
{
    EN_CMD_DESTROY_CARD_CMD_CODE = 0,
    EN_CMD_DESTROY_CARD_CARD_NO,
    EN_CMD_DESTROY_CARD_BUTT
}EN_CMD_DESTROY_CARD_ELEMENT;

//解析扣费命令
int parseCmdDesCard(string &cmd, void* pStCmd);

//打印解析结果
void printfCmdDesCard(ST_CMD_DESTROY_CARD &stDesCard);


#endif