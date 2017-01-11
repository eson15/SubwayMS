#ifndef __CMD_QUERY_HIS_H__
#define __CMD_QUERY_HIS_H__
#include <string>
#include "subwayCmdParse/include/cmdGlobal.h"

//命令中的每个信元
typedef enum
{
    EN_CMD_QUERY_HIS_CMD_CODE = 0,
    EN_CMD_QUERY_HIS_CARD_NO,
    EN_CMD_QUERY_HIS_BUTT
}EN_CMD_QUERY_HIS_ELEMENT;

//解析扣费命令
int parseCmdQueHistory(string &cmd, void* pStCmd);

//打印解析结果
void printfCmdQueHistory(ST_CMD_QUERY_HIS &stCmd);

#endif