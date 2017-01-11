#include "stdafx.h"
#include <iostream>
#include "subwayCmdParse/include/cmdGlobal.h"
#include "subwayCmdParse/include/cmdDestroyCard.h"
using namespace std;


//购买单程票命令的正则表达式，用于检查命令格式是否正确
string g_cmdDesCardPattern("^[ ]{0,}[dD]{1}[ ]{1}[0-9]{1,}[ ]{0,}$"); 


//扣费命令的信元解码函数列表
ELEMENT_FUNC g_cmdDesCardFunc[EN_CMD_DESTROY_CARD_BUTT] = 
{
    cmdCmdParse<ST_CMD_DESTROY_CARD>,
    cmdCardNoParse<ST_CMD_DESTROY_CARD>,
};

//解析扣费命令
int parseCmdDesCard(string &cmd, void* pStCmd)
{
    int intValue = parseCmd<ST_CMD_DESTROY_CARD>(cmd, pStCmd, g_cmdDesCardPattern, g_cmdDesCardFunc);
    
    if(0 == intValue)
    {
        printfCmdDesCard(*((ST_CMD_DESTROY_CARD*)pStCmd));
    }
    return intValue;
}

//打印解析结果
void printfCmdDesCard(ST_CMD_DESTROY_CARD &stDesCard)
{
    cout<<"CMD:                 "<<stDesCard.cmd<<endl;
    cout<<"cardNo:              "<<stDesCard.cardNo<<endl;
}

