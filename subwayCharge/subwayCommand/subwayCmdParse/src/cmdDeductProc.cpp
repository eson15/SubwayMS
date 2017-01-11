#include "stdafx.h"
#include <iostream>
#include "subwayCmdParse/include/cmdGlobal.h"
#include "subwayCmdParse/include/cmdDeductProc.h"
using namespace std;

//扣费命令的信元解码函数列表
ELEMENT_FUNC g_cmdDeductFunc[EN_CMD_DEDUCT_BUTT] = 
{
    cmdCmdParse<ST_CMD_DEDUCT>,
    cmdCardNoParse<ST_CMD_DEDUCT>,
    cmdDeductEnterTimeParse,
    cmdDeductEnterStationParse,
    cmdDeductExitTimeParse,
    cmdDeductExitStationParse
};

//扣费命令的正则表达式，用于检查命令格式是否正确
string g_cmdDeductPattern("^[ ]{0,}[cC]{1}[ ]{1}[0-9]{1,}[ ]{1}[0-9]{1,2}[:]{1}[0-9]{1,2}[ ]{1}[sS]{1}[0-9]{1,}[ ]{1}[0-9]{1,2}[:]{1}[0-9]{1,2}[ ]{1}[sS]{1}[0-9]{1,}[ ]{0,}$"); 

//解码进站时间
int cmdDeductEnterTimeParse(void* outPut, string* str)
{
    CHECK_INPUT_PARA(outPut, str);

    ST_CMD_DEDUCT* deductCmd = (ST_CMD_DEDUCT*)outPut;
    return cmdTimeParse(&(deductCmd->enterTime), str);
}

//解码进站站点
int cmdDeductEnterStationParse(void* outPut, string* str)
{
    CHECK_INPUT_PARA(outPut, str);

    ST_CMD_DEDUCT* deductCmd = (ST_CMD_DEDUCT*)outPut;
    return cmdStationParse(deductCmd->enterStation, str);
}

//解码出站时间
int cmdDeductExitTimeParse(void* outPut, string* str)
{
    CHECK_INPUT_PARA(outPut, str);

    ST_CMD_DEDUCT* deductCmd = (ST_CMD_DEDUCT*)outPut;
    return cmdTimeParse(&(deductCmd->exitTime), str);
}

//解码出站站点
int cmdDeductExitStationParse(void* outPut, string* str)
{
    CHECK_INPUT_PARA(outPut, str);

    ST_CMD_DEDUCT* deductCmd = (ST_CMD_DEDUCT*)outPut;
    return cmdStationParse(deductCmd->exitStation, str);
}

//解码扣费命令
int parseCmdDeduct(string &cmd, void* pStCmd)
{
    int intValue = parseCmd<ST_CMD_DEDUCT>(cmd, pStCmd, g_cmdDeductPattern, g_cmdDeductFunc);
    if(0 == intValue)
    {
        printfCmdDeduct(*((ST_CMD_DEDUCT*)pStCmd));
    }
    return intValue;
}

//打印解码后的扣费命令
void printfCmdDeduct(ST_CMD_DEDUCT &stCmdDeduct)
{
    cout<<"CMD:                 "<<stCmdDeduct.cmd<<endl;
    cout<<"cardNo:              "<<stCmdDeduct.cardNo<<endl;
    cout<<"enterTime:           "<<stCmdDeduct.enterTime.hour<<":"<<stCmdDeduct.enterTime.minutes<<endl;
    cout<<"enterStation:        "<<stCmdDeduct.enterStation<<endl;
    cout<<"exitTime:            "<<stCmdDeduct.exitTime.hour<<":"<<stCmdDeduct.exitTime.minutes<<endl;
    cout<<"exitStation:         "<<stCmdDeduct.exitStation<<endl;
}