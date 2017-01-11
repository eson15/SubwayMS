#ifndef __SUBWAY_PRICE_H__
#define __SUBWAY_PRICE_H__
#include "subwayCard.h"
#include "subwayError.h"

/*
@ 获取基础票价, 即按进站点与出站点之间的最短里程分级计算
*/
int GetBasePrice(unsigned int meters);

/*
@ 获取扣费票价，几种情况;
@   1. 里程数为0，按时间收费;
@   2. 里程数不为0;
@ 返回值: 
*/
EN_RETURN_CODE GetDeductPrice(EN_CARD_TYPE enCardType, unsigned int balance, unsigned int meters, ST_SUBWAY_TIME &enterTime, ST_SUBWAY_TIME &exitTime, unsigned int &deductPrice);

#endif