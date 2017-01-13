#include "stdafx.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "include/basePrice.h"
#include "include/deductPrice.h"
#include "subwayPrice.h"
#include <iostream>
using namespace std;

/*
@ 获取扣费票价，几种情况;
@   1. 里程数为0，按时间收费;
@   2. 里程数不为0;
@ 返回值: 
*/
EN_RETURN_CODE GetDeductPrice(EN_CARD_TYPE enCardType, unsigned int balance, unsigned int meters, ST_SUBWAY_TIME &enterTime, ST_SUBWAY_TIME &exitTime, unsigned int &deductPrice)
{
	int durationTime=0;
	if (meters == 0)
	{
		//计算乘车时长  DIFF_TIME
		durationTime = CalDurationTime(enterTime, exitTime);
		deductPrice = MaxValue(ChargeByTime(durationTime,enCardType),balance);
	}
	else
	{
		deductPrice = ChargeByDistance(meters,enCardType,enterTime,balance);
	}
    return EN_RETURN_SUCC;
}


unsigned int ChargeByTime(int minutes, EN_CARD_TYPE enCard)
{
	unsigned cost = 0;
	if (enCard == EN_CARD_TYPE_SINGLE)
	{
		if (minutes <= 30)
		{
			cost = 2;
		}
		else
		{
			cost = 3;
		}
	}
	else
	{
		if (minutes <= 30)
		{
			cost = 0;
		}
		else
		{
			cost = 3;
		}
	}
	return cost;
}

unsigned int ChargeByDistance(unsigned int distance, EN_CARD_TYPE enCard, ST_SUBWAY_TIME enterTime, unsigned int balance)
{

	unsigned int cost = GetBasePrice(distance);
	switch (enCard)
	{
	case EN_CARD_TYPE_SINGLE:
	{
		cost = MaxValue(cost, balance);
		break;
	}

	case EN_CARD_TYPE_NOMAL:
		break;
	case EN_CARD_TYPE_ELDER:
	{
		unsigned int currentTime = enterTime.hour * 60 + enterTime.minutes;
		if ((currentTime >= 600) && (currentTime < 900))
		{
			cost = cost * 4 / 5;
		}
		break;
	}
	}
	return cost;
}



