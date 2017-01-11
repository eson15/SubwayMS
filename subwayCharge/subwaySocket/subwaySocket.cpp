#include <Winsock2.h>
#include <iostream>
#include "subwayCommon.h"
#include "subwaySocket.h"
using namespace std;

typedef enum
{
    EN_LOGIN = 0,
    EN_LOGOUT,
    EN_LOG_BUTT
}EN_LOG_TYPE;

//监听socket信息
intptr_t g_ListenSocketId;
intptr_t g_ClientSocketId;
struct sockaddr_in  g_addrClient;

//socket接收和发送buffer
char g_receiveBuff[MAX_RECEIVE_BUFFER_LENGTH];
char g_sendBuff[MAX_SEND_BUFFER_LENGTH];

//命令处理入口函数
CMD_PROC_ENTER_FUNC g_cmdProcEnter = NULL;

//登入登出打印
char g_logStr[EN_LOG_BUTT][16] = 
{
    " login",
    " logout"
};

/*
@ 打印客户端信息
@ 入参： type 登入或登出
*/
void PrintClientInfo(EN_LOG_TYPE type)
{
    cout<<"Client: "<<(int)(g_addrClient.sin_addr.S_un.S_un_b.s_b1)<<".";
    cout<<(int)(g_addrClient.sin_addr.S_un.S_un_b.s_b2)<<".";
    cout<<(int)(g_addrClient.sin_addr.S_un.S_un_b.s_b3)<<".";
    cout<<(int)(g_addrClient.sin_addr.S_un.S_un_b.s_b4)<<":";
    cout<<(int)(g_addrClient.sin_port)<<g_logStr[type]<<"!"<<endl;
}

/*
@ 初始化Socket通信环境
*/
void InitSusbwaySocket(CMD_PROC_ENTER_FUNC func)
{
    g_cmdProcEnter = func;

    WORD wVersionRequested;  
	WSADATA wsaData;
	int err;   
	wVersionRequested = MAKEWORD( 1, 1 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if(err != 0)
	{
        exit(1);
		return; 
	}  

	if(LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1)
	{
		WSACleanup();
        exit(1);
		return;
	}
}

/*
@ 接受客户端的连接请求
@ 返回值: 0, 成功; -1, 失败：
*/
int AcceptClient()
{
    int socklen = sizeof(g_addrClient);
	g_ClientSocketId = accept(g_ListenSocketId, (struct sockaddr*)&g_addrClient, &socklen);
	if (g_ClientSocketId < 0)
	{
		cout<<"ListenAndAcceptClient::Call accept() fail."<<endl;
		return -1;
	}
    
    PrintClientInfo(EN_LOGIN);
    return 0;
}

/*
@ 初始化监听socket，启动监听
@ 返回值: 0, 成功; -1, 失败：
*/
int ListenAndAcceptClient()
{
    struct sockaddr_in srcAddr;
	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_family = AF_INET;
	srcAddr.sin_port = htons(5555);

    g_ListenSocketId = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == g_ListenSocketId)
	{
		cout<<"ListenAndAcceptClient::Call socket() fail."<<endl;
		return -1;
	}

	if(bind(g_ListenSocketId, (struct sockaddr *)&srcAddr, sizeof (struct sockaddr_in)) != 0)
	{
        cout<<"ListenAndAcceptClient::Call bind() fail."<<endl;
		closesocket(g_ListenSocketId);
		return -1;
	}

	if(listen(g_ListenSocketId, 10) < 0)
	{
		cout<<"ListenAndAcceptClient::Call listen() fail."<<endl;
		closesocket(g_ListenSocketId);
		return 0;
	}

	return AcceptClient();
}


/*
@ 接收客户端的数据, 并调用消息处理接口进行处理
@ 返回值: void
*/
void ReceiveCmdFlow()
{
    unsigned int realReceiveLen = 0;

    while(1)
    {
        realReceiveLen = recv(g_ClientSocketId, g_receiveBuff, MAX_RECEIVE_BUFFER_LENGTH, 0);
        g_receiveBuff[realReceiveLen] = 0;

        if((0 == realReceiveLen) || (0xFFFFFFFF == realReceiveLen))
        {
            PrintClientInfo(EN_LOGOUT);
            closesocket(g_ClientSocketId);
            (void)AcceptClient();
            continue;
        }

        if(NULL != g_cmdProcEnter)
        {
            g_cmdProcEnter(g_receiveBuff, g_sendBuff);

            send(g_ClientSocketId, g_sendBuff, strlen(g_sendBuff)+1, 0); 
        }
    }
}

