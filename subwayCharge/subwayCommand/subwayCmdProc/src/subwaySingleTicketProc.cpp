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
@ 办理单程票
@ 入参：unCmd, 命令内容
@ 出参: returnStr
@ 返回值: 无
*/
void ProcCreateSingleTicketCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	unsigned int distance = 0;
	int basePrice = -2;
	//获取两个站点间的里程数 GetSubwayStationDis

	 //获取两个站点间的基本票价  GetBasePrice
	returnCode = GetSubwayStationDis(unCmd.stCmdSingleTicket.srcStation, unCmd.stCmdSingleTicket.dstStation, distance);
	//cout <<  << endl;
	//查询不到站点或者站点之间不可达
	
	if (returnCode!= EN_RETURN_SUCC)
	{		
		//输出字符串
		GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, returnCode, 0, EN_CARD_TYPE_SINGLE, 0, returnStr);
		return;
	}
	//获取两个站点之间的基本票价
	basePrice = GetBasePrice(distance);

	//起点终点重叠，无法办临时卡，显示为内部错误
	if (basePrice < 0)
	{
		returnCode = EN_RETURN_INNER_ERR;
		GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, returnCode, 0, EN_CARD_TYPE_SINGLE, 0, returnStr);
		return;
	}

	//办单程卡 AssignCard
	returnCode = AssignCard(cardNo, EN_CARD_TYPE_SINGLE, basePrice);

	//不论成功与否都会输出信息 成功与否根据returnCode的类型
	//输出字符串
	

	GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, returnCode, cardNo, EN_CARD_TYPE_SINGLE, basePrice, returnStr);

	return;
}