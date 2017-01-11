#include "stdafx.h"
#include <iostream>
#include "subwayCmdParse/include/cmdGlobal.h"
#include "subwayCmdParse/include/cmdFillCharge.h"
using namespace std;


//购买单程票命令的正则表达式，用于检查命令格式是否正确
string g_cmdFillChargePattern("^[ ]{0,}[fF]{1}[ ]{1}[0-9]{1,}[ ]{1}[0-9]{1,}[ ]{0,}$"); 


//扣费命令的信元解码函数列表
ELEMENT_FUNC g_cmdFillChargeFunc[EN_CMD_FILL_CHARGE_BUTT] = 
{
    cmdCmdParse<ST_CMD_FILL_CHARGE>,
    cmdCardNoParse<ST_CMD_FILL_CHARGE>,
    cmdFillChargeParse
};

//解码函数
int cmdFillChargeParse(void* outPut, string* str)
{
    CHECK_INPUT_PARA(outPut, str);

    ST_CMD_FILL_CHARGE* Cmd = (ST_CMD_FILL_CHARGE*)outPut;
    return cmdChargeParse(&(Cmd->cardCharge), str);
}

//解析扣费命令
int parseCmdFillCharge(string &cmd, void* pStCmd)
{
    int intValue = parseCmd<ST_CMD_FILL_CHARGE>(cmd, pStCmd, g_cmdFillChargePattern, g_cmdFillChargeFunc);
    
    if(0 == intValue)
    {
        printfCmdFillCharge(*((ST_CMD_FILL_CHARGE*)pStCmd));
    }
    return intValue;
}

//打印解析结果
void printfCmdFillCharge(ST_CMD_FILL_CHARGE &stCmdFillCharge)
{
    cout<<"CMD:                 "<<stCmdFillCharge.cmd<<endl;
    cout<<"cardNo:              "<<stCmdFillCharge.cardNo<<endl;
    cout<<"cardCharge:          "<<stCmdFillCharge.cardCharge<<endl;
}

