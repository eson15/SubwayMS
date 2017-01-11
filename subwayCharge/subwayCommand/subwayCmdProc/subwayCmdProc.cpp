#include "stdafx.h"
#include <iostream>
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCommon.h"
#include "subwayError.h"
#include "subwayOutput\subwayOutput.h"
#include "subwayCmdProc\include\subwayCreateCardProc.h"
#include "subwayCmdProc\include\subwayDeductProc.h"
#include "subwayCmdProc\include\subwayFillChargeProc.h"
#include "subwayCmdProc\include\subwayQueryHistoryProc.h"
#include "subwayCmdProc\include\subwayQueryLineProc.h"
#include "subwayCmdProc\include\subwayResetProc.h"
#include "subwayCmdProc\include\subwaySingleTicketProc.h"

using namespace std;

typedef void (*CMD_PROC_FUNC)(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH]);
void ProcInvalidCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH]);


//命令处理分发矩阵
CMD_PROC_FUNC g_cmdProcFuncList[EN_CMD_TYPE_BUTT] = 
{
    ProcDeductCmd,
    ProcCreateSingleTicketCmd,
    ProcCreateCardCmd,
    ProcFillChargeCmd,
    ProcQueryHistoryCmd,
    NULL,
    ProcQueryLineCmd,
    ProcInvalidCmd,
    ProcResetCmd
};

/*
@ 无效命令处理
@ 入参：unCmd, 命令内容
@ 出参: returnStr
@ 返回值: 无
*/
void ProcInvalidCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    //输出字符串
    GetOutputResultStr(EN_CMD_TYPE_INVALID_CMD, EN_RETURN_INVALID_CMD, 0, EN_CARD_TYPE_BUTT, 0, returnStr);
    return;
}


/*
@ 处理命令入口, 负责所有命令的分发
@ 入参：cmdStr, 命令内容
@ 出参: 无
@ 返回值: 无
*/
void ProcCmdEnter(const char cmdStr[MAX_RECEIVE_BUFFER_LENGTH], char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    ST_COMM_CMD stCommCmd;
    memset(&stCommCmd, 0, sizeof(stCommCmd));
    stCommCmd.enCmdType = EN_CMD_TYPE_INVALID_CMD;

    do
    {
        //如果命令行中存在回车换行符，会影响正则表达式, 故限制一次只能输入一个命令
        vector<string> tokens;
        bool boolValue = strSplit(tokens, cmdStr, "\n\r");
        IF_INVALID_SET_RETURN_VALUE(boolValue, EN_CMD_TYPE_INVALID_CMD, stCommCmd.enCmdType)
        IF_INVALID_BREAK(boolValue)
        IF_INVALID_SET_RETURN_VALUE(tokens.size() <= 1, EN_CMD_TYPE_INVALID_CMD, stCommCmd.enCmdType)
        IF_INVALID_BREAK(tokens.size() == 1)

        //解析命令
        int result = cmdParse(stCommCmd, tokens[0].c_str());
        IF_INVALID_SET_RETURN_VALUE(result != -1, EN_CMD_TYPE_INVALID_CMD, stCommCmd.enCmdType);
    }while(false);

    //调用处理函数处理命令
    EN_CMD_TYPE enCmdType = stCommCmd.enCmdType;

    if(NULL == g_cmdProcFuncList[enCmdType])
    {
        cout<<"ProcCmdEnter()::Cmd " << enCmdType << " have not proc func!!"<<endl;
        return ;
    }
    g_cmdProcFuncList[enCmdType](stCommCmd.unCmd, returnStr);

}
