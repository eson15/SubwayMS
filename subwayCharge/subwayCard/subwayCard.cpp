#include "stdafx.h"
#include <iostream>
#include "list.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
#include "../subwayPrice/subwayPrice.h"
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

	GetAssignedCardNum(cardNo);

	CARD *card = new CARD(cardNo, enCard, charge);
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
	if (recharge > 999 || recharge <= 0)
		return EN_RETURN_RECHARGE_OVERFLOW;

	unsigned int totalSum = cardInfoArray[cardNo]->getBalance() + recharge;

	if (totalSum > 999 || totalSum <= 0)
		return EN_RETURN_RECHARGE_OVERFLOW;

	cardInfoArray[cardNo]->setBalance(totalSum);
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
	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	if (cardNo > 99)
	{
		return EN_RETURN_INVALID_CARD;
	}
	if (cardInfoArray[cardNo] == nullptr)
	{
		return EN_RETURN_INVALID_CARD;
	}
	enCard = cardInfoArray[cardNo]->getType();
	balance = cardInfoArray[cardNo]->getBalance();

	return EN_RETURN_SUCC;
}

///*
//@ 获取卡余额
//@ 入参：cardNo,卡号;
//@ 出参: balance: 余额
//		enCard:  卡类型
//@ 返回值: EN_RETURN_SUCC，成功; EN_RETURN_INVALID_CARD, 失败;
//*/
//EN_RETURN_CODE GetCardInfo(unsigned int cardNo, unsigned int &balance, EN_CARD_TYPE &enCard)
//{
//	//替换，张翔
//	if (cardNo > 99 || cardNo < 0)
//		return EN_RETURN_INVALID_CARD;
//	
//	balance = cardInfoArray[cardNo]->getBalance();
//	enCard = cardInfoArray[cardNo]->getType();
//
//	return EN_RETURN_SUCC;
//}

/*
@ 卡扣费
@ 入参：cardNo,卡号; enCard, 卡类型; deductPrice, 扣费票价
@ 出参: balance, 扣费后的余额
@ 返回值: EN_RETURN_SUCC，成功; EN_RETURN_BALANCE_NOT_ENOUGH, 失败;
*/
EN_RETURN_CODE DeductCard(unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int deductPrice, unsigned int &balance)
{
	if (balance < deductPrice)
	{
		return EN_RETURN_BALANCE_NOT_ENOUGH;
	}
	balance = balance - deductPrice;
	cardInfoArray[cardNo]->setBalance(balance);

	if (balance <= 20)
	{
		return EN_RETURN_BALANCE_TOO_LOW;
	}

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
		return "无效卡类型";
		break;
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
	if (cardType[0] == 'C' || cardType[0] == 'c')
	{
		enCard = EN_CARD_TYPE_NOMAL;
	}
	else if (cardType[0] == 'B' || cardType[0] == 'b')
	{
		enCard = EN_CARD_TYPE_ELDER;
	}
	else
		return EN_RETURN_INPUT_INVALID_CARDTYPE;

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

void GetAssignedCardNum(unsigned int &cardNo)
{
	//卡队列非空，才进行卡号分配
	cardNo = cardNumQueue.front();
	cardNumQueue.pop();
	cardCount++;             //总已用卡数+1
	return;

	//本函数内不对系统内的卡总数进行校验，校验在上层通过调用CheckAvailCard()实现；
}


EN_RETURN_CODE CheckAvailCard()
{
	if (cardNumQueue.size() <= 0)
	{
		return EN_RETURN_CARD_OVERLOW;
	}
	else
	{
		return EN_RETURN_SUCC;
	}
}


bool CheckChargeValue(int chargeValue)
{
	if ((chargeValue >= 0) && (chargeValue <= 999))
		return true;
	else
		return false;
}


EN_RETURN_CODE CheckTime(ST_SUBWAY_TIME enterTime, ST_SUBWAY_TIME exitTime)
{
	int enterHour = enterTime.hour;
	int enterMinutes = enterTime.minutes;
	int exitHour = exitTime.hour;
	int exitMinutes = exitTime.minutes;
	if ((enterHour < 0) || (enterHour >= 24)
		|| (exitHour < 0) || (exitHour >= 24)
		|| (enterMinutes < 0) || (enterMinutes >= 60)
		|| (exitMinutes < 0) || (exitMinutes >= 60))
	{
		return EN_RETURN_INVALID_TIME;
	}
	else if ((enterHour * 60 + enterMinutes) >= (exitHour * 60 + exitMinutes))
	{
		return EN_RETURN_INVALID_TIME;
	}
	else
		return EN_RETURN_SUCC;
}

unsigned int CalDurationTime(ST_SUBWAY_TIME enterTime, ST_SUBWAY_TIME exitTime)
{
	int enterHour = enterTime.hour;
	int enterMinutes = enterTime.minutes;
	int exitHour = exitTime.hour;
	int exitMinutes = exitTime.minutes;
	unsigned int durationTime = (exitHour * 60 + exitMinutes) - (enterHour * 60 + enterMinutes);
	return durationTime;
}
