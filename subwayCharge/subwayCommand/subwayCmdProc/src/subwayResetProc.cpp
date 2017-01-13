#include "stdafx.h"
#include <iostream>
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
#include "subwayline.h"
#include "subwayPrice.h"
#include "subwayCommon.h"
#include "subwayError.h"
#include "subwayCmdParse/subwayCmdParse.h"
#include "subwayOutput/subwayOutput.h"
using namespace std;

/*
@ 重置系统命令
@ 入参：unCmd, 命令内容
@ 出参: returnStr
@ 返回值: 无
*/
void ProcResetCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	DeleteAllCardInfo();

    InitCardManagerInfo();
    //输出字符串
    GetOutputResultStr(EN_CMD_TYPE_RESET, returnCode, 0, EN_CARD_TYPE_BUTT, 0, returnStr);
    return;
}