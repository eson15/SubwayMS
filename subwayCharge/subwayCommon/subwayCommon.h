#ifndef __COMM_SPLIT_H__
#define __COMM_SPLIT_H__
#include <vector>
#include "list.h"
using namespace std;

/*
@ 拆分字符串
@ 入参：  splitStr, 待拆分字符串; intervalStr, 拆分间隔符;
@ 出参：  splitArray, 拆分后的字符串数组; 
@ 返回值: true, 拆分成功; false, 拆分失败;
*/
bool strSplit(vector<string> &splitArray, const string &splitStr, const char* intervalStr);


#endif