#ifndef __SUBWAY_SOCKET_H__
#define __SUBWAY_SOCKET_H__
#include "subwayGlobalDef.h"
#include "subwayMacro.h"

typedef void (*CMD_PROC_ENTER_FUNC)(const char cmdStr[MAX_RECEIVE_BUFFER_LENGTH], char returnStr[MAX_SEND_BUFFER_LENGTH]);

/*
@ 初始化Socket通信环境
*/
void InitSusbwaySocket(CMD_PROC_ENTER_FUNC func);

/*
@ 初始化监听socket，启动监听
@ 返回值: 0, 成功; -1, 失败：
*/
int ListenAndAcceptClient();

/*
@ 接收客户端的数据, 并调用消息处理接口进行处理
@ 返回值: void
*/
void ReceiveCmdFlow();

#endif