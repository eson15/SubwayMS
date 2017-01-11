#ifndef __SUBWAY_LINE_H__
#define __SUBWAY_LINE_H__
#include <iostream>
#include "subwayError.h"
using namespace std;

#define MAX_STATION_NUM 100
#define MAX_DIS_BETWEEN_STATION 50000

/*
@ 增加一个地铁站
@ 返回值: EN_RETURN_SUCC, 成功; 其他：失败
*/
EN_RETURN_CODE AddSubwayStation(char* stationName, unsigned int dis);

/*
@ 获取两个地铁站间的最小距离
@ 返回值: EN_RETURN_SUCC: 成功, EN_RETURN_INVALID_LINE: 失败
*/
EN_RETURN_CODE GetSubwayStationDis(char* stationName1, char* stationName2, unsigned int &dis);

/*
@ 初始化地铁线路管理子系统
*/
void InitSubwayLine();

/*
@ 删除地铁线
@ 返回值: void
*/
void DelSubwayLine();


/*
@ 设置默认地铁线路
@ 返回值: NULL
*/
void SetDefaultLine();

/*
@ 打印所有地铁线
*/
void GetLineInfo(string &outStr);

#endif