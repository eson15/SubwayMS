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
@ 处理扣费命令
@ 入参：stCmdDeduct, 命令内容
@ 出参: returnStr
@ 返回值: void
*/
void ProcDeductCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    //根据卡号获取卡信息  GetCardInfo

    //检查时间格式  CHECK_TIME

    //计算乘车时长  DIFF_TIME

    //计算里程数  GetSubwayStationDis

    //计算扣费价格 GetDeductPrice
     
    //对乘车卡进行扣费 DeductCard

    

    //输出字符串
    //GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, pCmdDeduct->cardNo, enCard, balance, returnStr);
    return;
}