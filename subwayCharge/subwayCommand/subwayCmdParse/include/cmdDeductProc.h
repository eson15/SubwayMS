#ifndef __CMD_DEDUCT_H__
#define __CMD_DEDUCT_H__
#include <string>
#include "subwayCmdParse/include/cmdGlobal.h"

//命令中的每个信元
typedef enum
{
    EN_CMD_DEDUCT_CMD_CODE = 0,
    EN_CMD_DEDUCT_CARD_NO,
    EN_CMD_DEDUCT_ENTER_TIME,
    EN_CMD_DEDUCT_ENTER_STATION,
    EN_CMD_DEDUCT_EXIT_TIME,
    EN_CMD_DEDUCT_EXIT_STATION,
    EN_CMD_DEDUCT_BUTT
}EN_CMD_DEDUCT_ELEMENT;

//解析扣费命令
int parseCmdDeduct(string &cmd, void* pStCmd);

//打印解析结果
void printfCmdDeduct(ST_CMD_DEDUCT &stCmdDeduct);

//解码函数声明
int cmdDeductEnterTimeParse(void* outPut, string* str);
int cmdDeductEnterStationParse(void* outPut, string* str);
int cmdDeductExitTimeParse(void* outPut, string* str);
int cmdDeductExitStationParse(void* outPut, string* str);
#endif