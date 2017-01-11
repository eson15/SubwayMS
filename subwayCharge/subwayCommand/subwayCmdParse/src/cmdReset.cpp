#include "stdafx.h"
#include <iostream>
#include "subwayCmdParse/include/cmdGlobal.h"
#include "subwayCmdParse/include/cmdReset.h"
using namespace std;

//重置系统的正则表达式，用于检查命令格式是否正确
string g_cmdResetPattern("^[ ]{0,}[rR]{1}[ ]{0,}$"); 

//扣费命令的信元解码函数列表
ELEMENT_FUNC g_cmdResetFunc[EN_CMD_RESET_CMD_BUTT] = 
{
    cmdCmdParse<ST_CMD_RESET>
};

//查询线路命令
int parseCmdReset(string &cmd, void* pStCmd)
{
    int intValue = parseCmd<ST_CMD_RESET>(cmd, pStCmd, g_cmdResetPattern, g_cmdResetFunc);
    
    if(0 == intValue)
    {
        printfCmdReset(*((ST_CMD_RESET*)pStCmd));
    }
    return intValue;
}

//打印解析结果
void printfCmdReset(ST_CMD_RESET &stReset)
{
    cout<<"CMD:                 "<<stReset.cmd<<endl;
}