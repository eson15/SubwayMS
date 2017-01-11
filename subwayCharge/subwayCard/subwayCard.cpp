#include "stdafx.h"
#include <iostream>
#include "list.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
using namespace std;


CARD *cardInfoArray[100];
int cardCount = 0;
queue<unsigned int> cardNumQueue;


/*
@ 初始化所有卡信息
@ 返回值: 无
*/
void InitCardManagerInfo()
{
	InitCardQueue(cardNumQueue);
}

/*
@ 开卡，分配卡号和卡信息
@ 入参：enCard,卡类型; charge: 充值
@ 出参: cardNo, 分配的卡号
@ 返回值: EN_RETURN_SUCC，分配成功; EN_RETURN_CARD_OVERLOW, 分配失败;
*/
EN_RETURN_CODE AssignCard(unsigned int &cardNo, EN_CARD_TYPE enCard, unsigned int charge)
{
	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	CARD *card = new CARD(cardNo, enCard, charge);
	returnCode = GetAssignedCardNum(cardNo);
	if (EN_RETURN_SUCC != returnCode)
	{
		return returnCode;
	}

	cardInfoArray[cardNo] = card;//关联哈希表与新申请的卡对象

	return EN_RETURN_SUCC;
}

/*
@ 充值
@ 入参：cardNo,卡号; recharge: 充值
@ 出参: 无
@ 返回值: EN_RETURN_SUCC，成功; 其他, 失败;
*/
EN_RETURN_CODE RechargeCard(unsigned int cardNo, unsigned int recharge)
{

	return EN_RETURN_SUCC;
}

/*
@ 获取卡余额
@ 入参：cardNo,卡号;
@ 出参: balance: 余额
		enCard:  卡类型
@ 返回值: EN_RETURN_SUCC，成功; EN_RETURN_INVALID_CARD, 失败;
*/
EN_RETURN_CODE GetCardInfo(unsigned int cardNo, unsigned int &balance, EN_CARD_TYPE &enCard)
{

	return EN_RETURN_SUCC;
}

/*
@ 卡扣费
@ 入参：cardNo,卡号; enCard, 卡类型; deductPrice, 扣费票价
@ 出参: balance, 扣费后的余额
@ 返回值: EN_RETURN_SUCC，成功; EN_RETURN_INVALID_CARD, EN_RETURN_BALANCE_NOT_ENOUGH, 失败;
*/
EN_RETURN_CODE DeductCard(unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int deductPrice, unsigned int &balance)
{

	return EN_RETURN_SUCC;
}

/*
@ 删除卡信息
@ 入参：cardNo,卡号;
@ 出参: 无
@ 返回值: 0，成功; -1, 失败;
*/
int DeleteCard(unsigned int cardNo)
{

	return 0;
}

/*
@ 获取卡类型字符串
@ 入参：enCard,卡类型;
@ 出参: 无
@ 返回值: 卡类型字符串;
*/
char* GetCardTypeStr(EN_CARD_TYPE enCard)
{
	switch (enCard)
	{
		case   EN_CARD_TYPE_SINGLE:
			return "单程卡";
			break;
		case   EN_CARD_TYPE_ELDER:
			return "老年卡";
			break;
		case   EN_CARD_TYPE_NOMAL:
			return "普通卡";
			break;
		default:
			return nullptr;
	}

}

/*
@ 根据卡类型字符串, 识别卡类型
@ 入参：cardType,      卡类型字符串;
@ 出参: enCard,        卡类型
@ 返回值: EN_RETURN_SUCC，成功; EN_RETURN_INPUT_INVALID_CARDTYPE, 失败;
*/
EN_RETURN_CODE GetCardType(char cardType[], EN_CARD_TYPE &enCard)
{


	return EN_RETURN_SUCC;
}

void InitCardQueue(queue<unsigned int> &cardNumQueue)
{
	int index = 0;
	for (; index < CARDNUM; ++index)
	{
		cardNumQueue.push(index);
	}
}

EN_RETURN_CODE GetAssignedCardNum(unsigned int &cardNo)
{
	//卡队列非空，才进行卡号分配
	if (cardNumQueue.size() < 1)
		return EN_RETURN_CARD_OVERLOW;
	else
	{
		cardNo = cardNumQueue.front();
		cardNumQueue.pop();
		return EN_RETURN_SUCC;
	}
}