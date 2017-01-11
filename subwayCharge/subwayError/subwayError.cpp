#include "subwayError.h"

char g_errStr[EN_RETURN_BUTT][64] = 
{
    "成功",
    "无效的线路号",
    "余额不足",
    "余额过低, 请及时充值",
    "无效的命令",
    "无效的时间关系",
    "无效的地铁卡",
    "重复增加地铁卡",
    "无效的地铁站",
    "地铁站未启用",
    "申请的卡超出系统容量",
    "单程卡不能充值",
    "输入卡类型错误",
    "无效的距离",
    "办卡或充值后总余额超过上限",
    "内部错误"
};

/*
@ 返回错误字符串
@ 入参：enErrCode,错误码; 
@ 出参: 无
@ 返回值: 错误字符串;
*/
char* GetErrStr(EN_RETURN_CODE enErrCode)
{
    return g_errStr[enErrCode];
}