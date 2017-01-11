#ifndef __SUBWAY_CONTROL_H__
#define __SUBWAY_CONTROL_H__
#include "subwayGlobalDef.h"
/*
@ 处理命令入口
@ 入参：cmdStr, 命令内容
@ 出参: returnStr, 返回命令
@ 返回值: 无
*/
void ProcCmdEnter(const char cmdStr[MAX_RECEIVE_BUFFER_LENGTH], char returnStr[MAX_SEND_BUFFER_LENGTH]);

#endif