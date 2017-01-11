#ifndef __CMD_QUERY_LINE_H__
#define __CMD_QUERY_LINE_H__
#include <string>
#include "subwayCmdParse/include/cmdGlobal.h"

//命令中的每个信元
typedef enum
{
    EN_CMD_QUERY_LINE_CMD_CODE = 0,
    EN_CMD_QUERY_LINE_BUTT
}EN_CMD_QUERY_LINE_ELEMENT;

//解析扣费命令
int parseCmdQueryLine(string &cmd, void* pStCmd);

//打印解析结果
void printfCmdQueryLine(ST_CMD_QUERY_LINE &pCmdSingleTicket);

#endif