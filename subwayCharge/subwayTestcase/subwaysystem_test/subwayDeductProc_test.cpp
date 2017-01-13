#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"
#include "subwayLine.h"
#include "../../subwayCommand/subwayCmdProc/include/subwayDeductProc.h";
#include "subwayPrice.h"

using namespace testing;

class subwayDeductProcTest : public testing::Test
{
public:
	//测试套级别事件
	//在测试套中包含的用例运行前运行一次
	static void SetUpTestCase()
	{
		cout << " -----------开始运行：subwayDeductProcTest-----------------" << endl;
		InitSubwayLine();
		SetDefaultLine();
		DeleteAllCardInfo();

	}

	//在测试套中包含的用例运行全部运行结束后运行一次
	static void TearDownTestCase()
	{
		cout << " -----------结束运行：subwayDeductProcTest-----------------" << endl;
		DeleteAllCardInfo();
	}

	//测试用例级别的事件
	//测试套中的每个用例开始运行前调用一次
	void SetUp()
	{
		//为减小测试测试套内用例之间的影响，这个可进行一些初始化动作
		DeleteAllCardInfo();
		InitCardManagerInfo();
	}

	//测试套中每个用例结束后运行一次
	void TearDown()
	{
		//可进行一些动态内存的释放操作
	}
};

//测试普通卡扣费
TEST_F(subwayDeductProcTest, subwayDeductProcTest_NormalSucessTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	unsigned int charge = 100;
	unsigned int cardNo;
	unsigned int balance = 0;
	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "乘车卡扣费<成功><卡号=0><卡类型=普通卡><余额=98>";
     AssignCard(cardNo, enCardType, charge);  //办卡

	UN_CMD un_Cmd;
	un_Cmd.stCmdDeduct.cmd[0] = 'C';
	un_Cmd.stCmdDeduct.enterStation[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[1] = '1';
	un_Cmd.stCmdDeduct.exitStation[0] = 'S';
	un_Cmd.stCmdDeduct.exitStation[1] = '0';
	un_Cmd.stCmdDeduct.cardNo = cardNo;
	un_Cmd.stCmdDeduct.enterTime.hour=11;
	un_Cmd.stCmdDeduct.enterTime.minutes=0;
	un_Cmd.stCmdDeduct.exitTime.hour=14;
	un_Cmd.stCmdDeduct.exitTime.minutes=0;
	ProcDeductCmd(un_Cmd, returnStr);
	//string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;
	EXPECT_EQ(expectStr,resultStr);
}
//测试普通卡扣费余额不足
TEST_F(subwayDeductProcTest, subwayDeductProcTest_NormalLowBalanceFaliTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	unsigned int charge = 3;
	unsigned int cardNo;
	unsigned int balance = 0;
	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "乘车卡扣费<失败><卡号=0><卡类型=普通卡><余额=3><失败原因=余额不足>";
	AssignCard(cardNo, enCardType, charge);  //办卡

	UN_CMD un_Cmd;
	un_Cmd.stCmdDeduct.cmd[0] = 'C';
	un_Cmd.stCmdDeduct.enterStation[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[1] = '1';
	un_Cmd.stCmdDeduct.enterStation[2] = '6';
	un_Cmd.stCmdDeduct.exitStation[0] = 'S';
	un_Cmd.stCmdDeduct.exitStation[1] = '0';
	un_Cmd.stCmdDeduct.cardNo = cardNo;
	un_Cmd.stCmdDeduct.enterTime.hour = 11;
	un_Cmd.stCmdDeduct.enterTime.minutes = 0;
	un_Cmd.stCmdDeduct.exitTime.hour = 14;
	un_Cmd.stCmdDeduct.exitTime.minutes = 0;
	ProcDeductCmd(un_Cmd, returnStr);
	
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	EXPECT_EQ(expectStr, resultStr);
}
//测试单程卡扣费
TEST_F(subwayDeductProcTest, subwayDeductProcTest_SingleCardSucessTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_SINGLE;
	UN_CMD un_Cmd;
	unsigned int distance = 0;
	int basePrice = 2;
	unsigned int cardNo;
	AssignCard(cardNo, enCardType, basePrice);  //办卡

	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "乘车卡扣费<成功><卡号=0><卡类型=单程卡><余额=0>";

	un_Cmd.stCmdDeduct.cmd[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[1] = '1';
	un_Cmd.stCmdDeduct.exitStation[0] = 'S';
	un_Cmd.stCmdDeduct.exitStation[1] = '0';
	un_Cmd.stCmdDeduct.cardNo = cardNo;
	un_Cmd.stCmdDeduct.enterTime.hour = 11;
	un_Cmd.stCmdDeduct.enterTime.minutes = 0;
	un_Cmd.stCmdDeduct.exitTime.hour = 14;
	un_Cmd.stCmdDeduct.exitTime.minutes = 0;
	ProcDeductCmd(un_Cmd, returnStr);
	
	//string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);

	EXPECT_EQ(expectStr, resultStr);
}
//测试单程卡扣费余额不足
TEST_F(subwayDeductProcTest, subwayDeductProcTest_SingleTicketLowBalanceFaliTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_SINGLE;
	UN_CMD un_Cmd;
	unsigned int distance = 0;
	int basePrice = 2;
	unsigned int cardNo;
	AssignCard(cardNo, enCardType, basePrice);  //办卡

	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "乘车卡扣费<失败><卡号=0><卡类型=单程卡><余额=2><失败原因=余额不足>";

	un_Cmd.stCmdDeduct.cmd[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[1] = '1';
	un_Cmd.stCmdDeduct.enterStation[2] = '6';
	un_Cmd.stCmdDeduct.exitStation[0] = 'S';
	un_Cmd.stCmdDeduct.exitStation[1] = '0';
	un_Cmd.stCmdDeduct.cardNo = cardNo;
	un_Cmd.stCmdDeduct.enterTime.hour = 11;
	un_Cmd.stCmdDeduct.enterTime.minutes = 0;
	un_Cmd.stCmdDeduct.exitTime.hour = 14;
	un_Cmd.stCmdDeduct.exitTime.minutes = 0;
	ProcDeductCmd(un_Cmd, returnStr);

	//string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	//cout << "------------------expectStr=" << expectStr << endl;
	//cout << "------------------resultStr=" << resultStr << endl;
	EXPECT_EQ(expectStr, resultStr);
}

#endif
