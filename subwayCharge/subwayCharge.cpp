// subwayCharge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "subwaySocket.h"
#include "subwayline.h"
#include "subwayCard.h"
#include "subwayCommand.h"

#if _SUBWAY_LLT
#include "gtest/gtest.h"
using namespace testing;
#endif

/*
@ 初始化地铁收费系统, 调用各个模块的初始化函数
*/
void InitSubwayCharge()
{
    InitCardManagerInfo();
    InitSubwayLine();
    InitSusbwaySocket(ProcCmdEnter);

    //预置默认地铁线路
    SetDefaultLine();
}

int _tmain(int argc, _TCHAR* argv[])
{
#if _SUBWAY_LLT
    //LLT工程中进行DT
    printf("Running main()------------------ \n");
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    getchar();
    return result;
#else
    InitSubwayCharge();

    //监听客户端的连接请求
    if(-1 == ListenAndAcceptClient())
    {
        return -1;
    }

    //循环接收客户端的命令流
    ReceiveCmdFlow();
#endif
	return 0;
}

