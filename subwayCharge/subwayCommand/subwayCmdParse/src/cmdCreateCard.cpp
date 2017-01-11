#include "stdafx.h"
#include <iostream>
#include "subwayCmdParse/include/cmdGlobal.h"
#include "subwayCmdParse/include/cmdCreateCard.h"
using namespace std;

//办理乘车卡命令的正则表达式，用于检查命令格式是否正确
string g_cmdCreateCardPattern("^[ ]{0,}[bB]{1}[ ]{1}[a-zA-Z]{1}[ ]{1}[0-9]{1,}[ ]{0,}$"); 


//扣费命令的信元解码函数列表
ELEMENT_FUNC g_cmdCreateCardFunc[EN_CMD_CREATE_CARD_BUTT] = 
{
    cmdCmdParse<ST_CMD_CREATE_CARD>,
    cmdCardTypeParse<ST_CMD_CREATE_CARD>,
    cmdCreateCardChargeParse
};


//解码扣费命令中的预充值金额
int cmdCreateCardChargeParse(void* outPut, string* str)
{
    CHECK_INPUT_PARA(outPut, str);

    ST_CMD_CREATE_CARD* Cmd = (ST_CMD_CREATE_CARD*)outPut;
    return cmdChargeParse(&(Cmd->cardCharge), str);
}

//解码扣费命令
int parseCmdCreateCard(string &cmd, void* pStCmd)
{
    int intValue = parseCmd<ST_CMD_CREATE_CARD>(cmd, pStCmd, g_cmdCreateCardPattern, g_cmdCreateCardFunc);

    if(0 == intValue)
    {
        printfCmdCreateCard(*((ST_CMD_CREATE_CARD*)pStCmd));
    }
    return intValue;
}

//打印解码后的扣费命令
void printfCmdCreateCard(ST_CMD_CREATE_CARD &stCmdCreateCard)
{
    cout<<"CMD:                 "<<stCmdCreateCard.cmd<<endl;
    cout<<"CardType:            "<<stCmdCreateCard.cardType<<endl;
    cout<<"cardCharge:          "<<stCmdCreateCard.cardCharge<<endl;
}