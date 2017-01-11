#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "subwayCommon.h"

/*
@ 拆分字符串
@ 入参：  splitStr, 待拆分字符串; intervalStr, 拆分间隔符;
@ 出参：  splitArray, 拆分后的字符串数组; 
@ 返回值: true, 拆分成功; false, 拆分失败;
*/
bool strSplit(vector<string> &splitArray, const string &splitStr, const char* intervalStr)
{
    unsigned int strLength = splitStr.length();

    char* splitTmp = NULL;
    splitTmp = new char[strLength + 1];
    if(NULL == splitTmp)
    {
        return false;
    }

    memset(splitTmp, 0, strLength + 1);
    memcpy_s(splitTmp, strLength + 1, splitStr.c_str(), strLength);

    char *result = NULL; 
    char *pNext = NULL;  
    result = strtok_s(splitTmp, intervalStr, &pNext);
    while(result != NULL)    
    {         
        splitArray.push_back(result);
        result = strtok_s(NULL, intervalStr, &pNext);    
    }

    delete []splitTmp;
    return true;
}