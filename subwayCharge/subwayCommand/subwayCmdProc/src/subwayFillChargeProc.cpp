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
@ 充值命令
@ 入参：unCmd, 命令内容
@ 出参: returnStr
@ 返回值: 无
*/
void ProcFillChargeCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    //获取卡信息 GetCardInfo

    //进行充值 RechargeCard

    //根据充值后的卡信息  GetCardInfo

    //输出字符串
    //GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, pCmdCharge->cardNo, enCard, balance, returnStr);

    return;
}