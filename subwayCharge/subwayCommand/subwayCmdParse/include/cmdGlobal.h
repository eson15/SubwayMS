#ifndef __CMD_GLOBAL_H__
#define __CMD_GLOBAL_H__
#include <string>
#include <vector>
#include <time.h>
#include <regex>
#include <stdlib.h>
#include "subwayCommon.h"
#include "subwayCmdParse\subwayCmdParse.h"
using namespace std;

//每个信元的解码函数
typedef int (*ELEMENT_FUNC)(void* outPut, string* str);

//命令的解码函数类型
typedef int (*CMD_DECODE_FUNC)(string &cmd, void* pStCmd);

//检查入参是否满足要求
#define CHECK_INPUT_PARA(outPutPtr, strInput) \
    if((NULL == (str)) || (NULL == (outPut))) \
    {\
        return -1;\
    }

//通用解码命令码
template <typename T>
int cmdCmdParse(void* outPut, string* str)
{
    CHECK_INPUT_PARA(outPut, str);

    T* Cmd = (T*)outPut;
    return memcpy_s(Cmd->cmd, MAX_CMD_LENGTH, str->c_str(), str->length());
}

//通用解码卡号
template <typename T>
int cmdCardNoParse(void* outPut, string* str)
{
    CHECK_INPUT_PARA(outPut, str);

    T* Cmd = (T*)outPut;
    Cmd->cardNo = atoi(str->c_str());
    return 0;
}

//通用解码卡类型
template <typename T>
int cmdCardTypeParse(void* outPut, string* str)
{
    CHECK_INPUT_PARA(outPut, str);

    T* Cmd = (T*)outPut;
    return memcpy_s(Cmd->cardType, MAX_CARD_TYPE_LENGTH, str->c_str(), str->length());
}

//通用解码时间
static inline int cmdTimeParse(ST_SUBWAY_TIME *pTime, string* str)
{
    vector<string> tokens;
    //boost::split(tokens, (*str), boost::is_any_of(":")); 

    if(!strSplit(tokens, (*str), ":"))
    {
        return -1;
    }

    pTime->hour = atoi(tokens[0].c_str());
    pTime->minutes = atoi(tokens[1].c_str());
    return 0;
}

//通用解码地铁站名
static inline int cmdStationParse(char station[MAX_STATION_NAME_LENGTH], string* str)
{
    return memcpy_s(station, MAX_STATION_NAME_LENGTH, str->c_str(), str->length());
}

//通用解码钱额度
static inline int cmdChargeParse(int* charge, string* str)
{
    *charge = atoi(str->c_str());
    return 0;
}

//使用正则表达式检查命令是否符合规范
static inline int checkCmd(string &cmd, string &pattern)
{
    std::smatch results;

    regex r(pattern);

    if(regex_search(cmd, results, r))
    {
        return 0;
    }

    return -1;
}

//解码命令行
template <typename T>
int parseCmd(string &cmd, void* pStCmd, string pattern, ELEMENT_FUNC func[])
{
    vector<string> tokens;

    T* pCmd = (T*)pStCmd;
    
    if(0 != checkCmd(cmd, pattern))
    {
        return -1;
    }

    if(!strSplit(tokens, cmd, " "))
    {
        return -1;
    }

    for (size_t i = 0; i < tokens.size(); ++ i)
    {
        func[i](pCmd, &(tokens[i]));
    }

    return 0;
}

#endif