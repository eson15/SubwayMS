#ifndef __CMD_CREATE_CARD_H__
#define __CMD_CREATE_CARD_H__
#include <string>
#include "subwayCmdParse/include/cmdGlobal.h"

//命令中的每个信元
typedef enum
{
    EN_CMD_CREATE_CARD_CMD_CODE = 0,
    EN_CMD_CREATE_CARD_TYPE,
    EN_CMD_CREATE_CARD_CHARGE,
    EN_CMD_CREATE_CARD_BUTT
}EN_CMD_CREATE_CARD_ELEMENT;

//解析扣费命令
int parseCmdCreateCard(string &cmd, void* pStCmd);

//打印解析结果
void printfCmdCreateCard(ST_CMD_CREATE_CARD &stCmdCreateCard);

//解码函数声明
int cmdCreateCardChargeParse(void* outPut, string* str);

#endif