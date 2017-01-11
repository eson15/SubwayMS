#include "stdafx.h"
#include <iostream>
#include "subwayCmdParse/include/cmdGlobal.h"
#include "subwayCmdParse/include/cmdQueryHistory.h"
using namespace std;


//购买单程票命令的正则表达式，用于检查命令格式是否正确
string g_cmdQueHistoryPattern("^[ ]{0,}[hH]{1}[ ]{1}[0-9]{1,}[ ]{0,}$"); 


//扣费命令的信元解码函数列表
ELEMENT_FUNC g_cmdQueHistoryFunc[EN_CMD_QUERY_HIS_BUTT] = 
{
    cmdCmdParse<ST_CMD_QUERY_HIS>,
    cmdCardNoParse<ST_CMD_QUERY_HIS>,
};

//使用正则表达式检查命令是否符合规范
int checkQueHistory(string &cmd)
{
    return checkCmd(cmd, g_cmdQueHistoryPattern);
}

//解析扣费命令
int parseCmdQueHistory(string &cmd, void* pStCmd)
{
    int intValue = parseCmd<ST_CMD_QUERY_HIS>(cmd, pStCmd, g_cmdQueHistoryPattern, g_cmdQueHistoryFunc);
    
    if(0 == intValue)
    {
        printfCmdQueHistory(*((ST_CMD_QUERY_HIS*)pStCmd));
    }
    return intValue;
}

//打印解析结果
void printfCmdQueHistory(ST_CMD_QUERY_HIS &stQueHistory)
{
    cout<<"CMD:                 "<<stQueHistory.cmd<<endl;
    cout<<"cardNo:              "<<stQueHistory.cardNo<<endl;
}

