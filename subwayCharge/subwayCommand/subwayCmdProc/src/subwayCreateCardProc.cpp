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
@ 办理普通卡
@ 入参：unCmd, 命令内容
@ 出参: returnStr
@ 返回值: 无
*/
void ProcCreateCardCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH]) // 普通+ 老年
{
	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	EN_CARD_TYPE cardType = EN_CARD_TYPE_BUTT;


	//首先计算是否有可用的卡
	returnCode = CheckAvailCard();
	if (returnCode != EN_RETURN_SUCC)
	{
		//TODO
		GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, cardNo, cardType, unCmd.stCmdCreateCard.cardCharge, returnStr);
		return;
	}


	//识别卡类型 GetCardType
	returnCode = GetCardType(unCmd.stCmdCreateCard.cardType, cardType);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, cardNo, cardType, unCmd.stCmdCreateCard.cardCharge, returnStr);
		return;
	}
	//检查充值金额是否合法

	if (!CheckChargeValue(unCmd.stCmdCreateCard.cardCharge))
	{
		returnCode = EN_RETURN_RECHARGE_OVERFLOW;
		GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, cardNo, cardType, unCmd.stCmdCreateCard.cardCharge, returnStr);
		return;
	}


	//办卡 AssignCard
	returnCode = AssignCard(cardNo, cardType, unCmd.stCmdCreateCard.cardCharge);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, cardNo, cardType, unCmd.stCmdCreateCard.cardCharge, returnStr);
		return;
	}
	//输出字符串
	GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, cardNo, cardType, unCmd.stCmdCreateCard.cardCharge, returnStr);
	return;
}