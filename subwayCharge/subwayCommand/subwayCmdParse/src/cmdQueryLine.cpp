#include "stdafx.h"
#include <iostream>
#include "subwayCmdParse/include/cmdGlobal.h"
#include "subwayCmdParse/include/cmdQueryLine.h"
using namespace std;

//查询线路的正则表达式，用于检查命令格式是否正确
string g_cmdQueLinePattern("^[ ]{0,}[lL]{1}[ ]{0,}$"); 


//扣费命令的信元解码函数列表
ELEMENT_FUNC g_cmdQueLineFunc[EN_CMD_QUERY_LINE_BUTT] = 
{
    cmdCmdParse<ST_CMD_QUERY_LINE>
};

//查询线路命令
int parseCmdQueryLine(string &cmd, void* pStCmd)
{
    int intValue = parseCmd<ST_CMD_QUERY_LINE>(cmd, pStCmd, g_cmdQueLinePattern, g_cmdQueLineFunc);
    
    if(0 == intValue)
    {
        printfCmdQueryLine(*((ST_CMD_QUERY_LINE*)pStCmd));
    }
    return intValue;
}

//打印解析结果
void printfCmdQueryLine(ST_CMD_QUERY_LINE &stQueLine)
{
    cout<<"CMD:                 "<<stQueLine.cmd<<endl;
}
