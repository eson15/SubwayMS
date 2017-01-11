#include "stdafx.h"
#include <iostream>
#include "subwayCmdParse/include/cmdGlobal.h"
#include "subwayCmdParse/include/cmdSingleTicket.h"
using namespace std;


//购买单程票命令的正则表达式，用于检查命令格式是否正确
string g_cmdSingleTicketPattern("^[ ]{0,}[sS]{1}[ ]{1}[sS]{1}[0-9]{1,}[ ]{1}[sS]{1}[0-9]{1,}[ ]{0,}$"); 


//扣费命令的信元解码函数列表
ELEMENT_FUNC g_cmdSingleTicketFunc[EN_CMD_SINGLE_TICKET_BUTT] = 
{
    cmdCmdParse<ST_CMD_SINGLE_TICKET>,
    cmdSingleTicketSrcStationParse,
    cmdSingleTicketDstStationParse,
};

//解码进站站点名称
int cmdSingleTicketSrcStationParse(void* outPut, string* str)
{
    CHECK_INPUT_PARA(outPut, str);

    ST_CMD_SINGLE_TICKET* deductCmd = (ST_CMD_SINGLE_TICKET*)outPut;
    return cmdStationParse(deductCmd->srcStation, str);
}

//解码出站站点名称
int cmdSingleTicketDstStationParse(void* outPut, string* str)
{
    CHECK_INPUT_PARA(outPut, str);

    ST_CMD_SINGLE_TICKET* deductCmd = (ST_CMD_SINGLE_TICKET*)outPut;
    return cmdStationParse(deductCmd->dstStation, str);
}

//解码扣费命令
int parseCmdSingleTicket(string &cmd, void* pStCmd)
{
    int intValue = parseCmd<ST_CMD_SINGLE_TICKET>(cmd, pStCmd, g_cmdSingleTicketPattern, g_cmdSingleTicketFunc);
    
    if(0 == intValue)
    {
        printfCmdSingleTicket(*((ST_CMD_SINGLE_TICKET*)pStCmd));
    }
    return intValue;
}


//打印解码后的扣费命令
void printfCmdSingleTicket(ST_CMD_SINGLE_TICKET &stCmdSingleTicket)
{
    cout<<"CMD:                 "<<stCmdSingleTicket.cmd<<endl;
    cout<<"srcStation:          "<<stCmdSingleTicket.srcStation<<endl;
    cout<<"dstStation:          "<<stCmdSingleTicket.dstStation<<endl;
}