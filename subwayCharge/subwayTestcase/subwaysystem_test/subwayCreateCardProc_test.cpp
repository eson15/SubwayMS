#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"
#include "subwayLine.h"
#include "../../subwayCommand/subwayCmdProc/include/subwayCreateCardProc.h"

using namespace testing;


class subwayCreateCardProcTest : public testing::Test
{
public:
	//测试套级别事件
	//在测试套中包含的用例运行前运行一次
	static void SetUpTestCase()
	{
		cout << " -----------开始运行：subwayCreateCardProcTest-----------------" << endl;
	}

	//在测试套中包含的用例运行全部运行结束后运行一次
	static void TearDownTestCase()
	{
		cout << " -----------结束运行：subwayCreateCardProcTest-----------------" << endl;
	}

	//测试用例级别的事件
	//测试套中的每个用例开始运行前调用一次
	void SetUp()
	{
		DeleteAllCardInfo();
		InitCardQueue();
	}

	//测试套中每个用例结束后运行一次
	void TearDown()
	{
		//可进行一些动态内存的释放操作
	}
};

/*
@ 办理普通卡
@ 入参：unCmd, 命令内容
@ 出参: returnStr
@ 返回值: 无
*/
//void ProcCreateCardCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH]);// 普通+ 老年

//买一张普通卡
TEST_F(subwayCreateCardProcTest, ProcQueryLineCmd_NormalSucessTest) {

	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	EN_CARD_TYPE cardType = EN_CARD_TYPE_BUTT;

	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr="办理乘车卡<成功><卡号=0><卡类型=普通卡><余额=100>";

	UN_CMD unCmd ;
	unCmd.stCmdCreateCard.cmd[0] = 'B';
	unCmd.stCmdCreateCard.cardType[0] = 'C';
	unCmd.stCmdCreateCard.cardCharge = 100 ;	
	ProcCreateCardCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	EXPECT_EQ(expectStr, resultStr);


}

//购买卡类型错误
TEST_F(subwayCreateCardProcTest, ProcQueryLineCmd_CardTypeFailTest) {

	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr= "办理乘车卡<失败><失败原因=输入卡类型错误>";

	UN_CMD unCmd;
	unCmd.stCmdCreateCard.cmd[0] = 'B';
	unCmd.stCmdCreateCard.cardType[0] = 'Z';
	unCmd.stCmdCreateCard.cardCharge = 100;
	ProcCreateCardCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	EXPECT_EQ(expectStr, resultStr);

}
//充值金额错误
TEST_F(subwayCreateCardProcTest, ProcQueryLineCmd_CardChargeFailTest) {

	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "办理乘车卡<失败><失败原因=办卡或充值后总余额超过上限>";

	UN_CMD unCmd;
	unCmd.stCmdCreateCard.cmd[0] = 'B';
	unCmd.stCmdCreateCard.cardType[0] = 'C';
	unCmd.stCmdCreateCard.cardCharge = 1000;
	ProcCreateCardCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	EXPECT_EQ(expectStr, resultStr);

}
//达到系统容量
TEST_F(subwayCreateCardProcTest, ProcQueryLineCmd_CardOutOfRangeTest) {

	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "办理乘车卡<失败><失败原因=申请的卡超出系统容量>";

	UN_CMD unCmd;
	unCmd.stCmdCreateCard.cmd[0] = 'B';
	unCmd.stCmdCreateCard.cardType[0] = 'C';
	unCmd.stCmdCreateCard.cardCharge = 100;
	for (int i = 0; i < 100; i++) ProcCreateCardCmd(unCmd, returnStr);  //买100张
	ProcCreateCardCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	EXPECT_EQ(expectStr, resultStr);

}
#endif