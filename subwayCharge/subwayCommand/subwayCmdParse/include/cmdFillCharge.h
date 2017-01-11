#ifndef __CMD_FILL_CHARGE_H__
#define __CMD_FILL_CHARGE_H__
#include <string>
#include "subwayCmdParse/include/cmdGlobal.h"

//命令中的每个信元
typedef enum
{
    EN_CMD_FILL_CHARGE_CMD_CODE = 0,
    EN_CMD_FILL_CHARGE_CARDNO,
    EN_CMD_FILL_CHARGE_CHARGE,
    EN_CMD_FILL_CHARGE_BUTT
}EN_CMD_FILL_CHARGE_ELEMENT;

//解析扣费命令
int parseCmdFillCharge(string &cmd, void* pStCmd);

//打印解析结果
void printfCmdFillCharge(ST_CMD_FILL_CHARGE &stCmdFillCharge);

//解码函数声明
int cmdFillChargeParse(void* outPut, string* str);

#endif