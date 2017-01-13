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
	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	EN_CARD_TYPE cardType = EN_CARD_TYPE_BUTT;
	unsigned int balance = 0;
	unsigned int distance = 0;
	unsigned int cost = 0;
	//根据卡号获取卡信息  GetCardInfo
	returnCode = GetCardInfo(unCmd.stCmdDeduct.cardNo, balance, cardType);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
		return;
	}
	//检查时间格式  CHECK_TIME
	returnCode = CheckTime(unCmd.stCmdDeduct.enterTime, unCmd.stCmdDeduct.exitTime);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
		return;
	}

	//计算里程数  GetSubwayStationDis
	returnCode = GetSubwayStationDis(unCmd.stCmdDeduct.enterStation, unCmd.stCmdDeduct.exitStation, distance);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
		return;
	}

	//计算扣费价格 
	returnCode = GetDeductPrice(cardType, balance, distance, unCmd.stCmdDeduct.enterTime, unCmd.stCmdDeduct.exitTime, cost);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
		return;
	}



	//对乘车卡进行扣费 DeductCard
	returnCode = DeductCard(unCmd.stCmdDeduct.cardNo, cardType, cost, balance);
	if ((returnCode != EN_RETURN_SUCC)&&(returnCode != EN_RETURN_BALANCE_TOO_LOW))
	{
		GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
		return;
	}
	if (EN_CARD_TYPE_SINGLE == cardType)
	{
		DeleteCard(unCmd.stCmdDeduct.cardNo);
	}
	

	

	//输出字符串
	GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
	return;
}