#ifndef __CMD_RESET_H__
#define __CMD_RESET_H__
#include <string>
#include "subwayCmdParse/include/cmdGlobal.h"

//命令中的每个信元
typedef enum
{
    EN_CMD_RESET_CMD_CODE = 0,
    EN_CMD_RESET_CMD_BUTT
}EN_CMD_RESET_CMD_ELEMENT;

//解析扣费命令
int parseCmdReset(string &cmd, void* pStCmd);

//打印解析结果
void printfCmdReset(ST_CMD_RESET &pCmdReset);

#endif