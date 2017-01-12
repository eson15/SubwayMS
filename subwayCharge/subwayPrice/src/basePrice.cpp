#include "stdafx.h"
#include <iostream>
#include  <sstream>
#include "subwayMacro.h"
#include "include/basePrice.h"
using namespace std;

/*
@ 获取基础票价, 即按进站点与出站点之间的最短里程分级计算
@ -1, 查询基础票价失败; 其他, 基础票价
*/
int GetBasePrice(unsigned int meters)
{
	int price = -2;

	if (meters == 0)
		price = -1;
	else if (meters <= 3000)
		price = 2;
	else if (meters <= 5000)
		price = 3;
	else if (meters <= 10000)
		price = 4;
	else
		price = 5;

	return price;
}