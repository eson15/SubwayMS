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

	unsigned int balance = 0;
	EN_CARD_TYPE enCard = EN_CARD_TYPE_BUTT;

	//获取卡信息
	EN_RETURN_CODE returnCode = GetCardInfo(unCmd.stCmdFillCharge.cardNo, balance, enCard);
	//卡无效判断
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, unCmd.stCmdFillCharge.cardNo, enCard, balance, returnStr);
		return;
	}
	//卡类型判断
	if (EN_CARD_TYPE_SINGLE == enCard)
	{
		returnCode = EN_RETURN_SINGLE_CARD_CANNOT_RECHARGE;
		GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, unCmd.stCmdFillCharge.cardNo, enCard, balance, returnStr);
		return;
	}

	//进行充值，包括充值范围，以及最后的余额范围判断，充值成功则更新卡余额
	returnCode = RechargeCard(unCmd.stCmdFillCharge.cardNo, unCmd.stCmdFillCharge.cardCharge);

	//根据充值后的卡信息  GetCardInfo
	GetCardInfo(unCmd.stCmdFillCharge.cardNo, balance, enCard);
	//输出字符串
	//GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, pCmdCharge->cardNo, enCard, balance, returnStr);
	GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, unCmd.stCmdFillCharge.cardNo, enCard, balance, returnStr);

	return;
}