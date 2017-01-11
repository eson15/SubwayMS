#ifndef __CMD_SINGLE_TICKET_H__
#define __CMD_SINGLE_TICKET_H__
#include <string>
#include "subwayCmdParse/include/cmdGlobal.h"

//命令中的每个信元
typedef enum
{
    EN_CMD_SINGLE_TICKET_CMD_CODE = 0,
    EN_CMD_SINGLE_TICKET_SRC_STATION,
    EN_CMD_SINGLE_TICKET_DST_STATION,
    EN_CMD_SINGLE_TICKET_BUTT
}EN_CMD_SINGLE_TICKET_ELEMENT;

//解析扣费命令
int parseCmdSingleTicket(string &cmd, void* pStCmd);

//打印解析结果
void printfCmdSingleTicket(ST_CMD_SINGLE_TICKET &pCmdSingleTicket);

//解码函数声明
int cmdSingleTicketDstStationParse(void* outPut, string* str);
int cmdSingleTicketSrcStationParse(void* outPut, string* str);
#endif