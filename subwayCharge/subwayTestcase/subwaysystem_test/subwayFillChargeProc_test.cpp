#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"
#include "subwayLine.h"
#include "../../subwayCommand/subwayCmdProc/include/subwayFillChargeProc.h"

using namespace testing;

class subwayFillChargeProcTest : public testing::Test
{
public:
	//测试套级别事件
	//在测试套中包含的用例运行前运行一次
	static void SetUpTestCase()
	{
		cout << " -----------开始运行：subwayFillChargeProcTest-----------------" << endl;
		InitSubwayLine();
		SetDefaultLine();
	}

	//在测试套中包含的用例运行全部运行结束后运行一次
	static void TearDownTestCase()
	{
		cout << " -----------结束运行：subwayFillChargeProcTest-----------------" << endl;
		//		DeleteAllCardInfo();
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
//普通卡充值 100元
TEST_F(subwayFillChargeProcTest, subwayFillChargeProcTest_NormalSucessTest) {

	unsigned int pre_balance= 100;  //原金额
	unsigned int charge = 100;    //充值金额
	unsigned int cardNo;
	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	unsigned int current_balance;
	EN_CARD_TYPE current_cardType;
	AssignCard(cardNo, enCardType, pre_balance);

	UN_CMD unCmd;
	unCmd.stCmdFillCharge.cardCharge = charge;
	unCmd.stCmdFillCharge.cardNo = cardNo;
	unCmd.stCmdFillCharge.cmd[0] = 'F';
    char returnStr[MAX_SEND_BUFFER_LENGTH];


	ProcFillChargeCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string expectStr = "乘车卡充值<成功><卡号=0><卡类型=普通卡><余额=200>";
	EXPECT_EQ(expectStr, resultStr);
	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;
	GetCardInfo(cardNo, current_balance, current_cardType);
	EXPECT_EQ(200, current_balance);
	EXPECT_EQ(EN_CARD_TYPE_NOMAL, current_cardType);
}

//单程卡不能充值
TEST_F(subwayFillChargeProcTest, subwayFillChargeProcTest_SingleCardCantRechangeTest) {

	unsigned int pre_balance = 5;  //原金额
	unsigned int charge = 100;    //充值金额
	unsigned int cardNo;
	EN_CARD_TYPE enCardType = EN_CARD_TYPE_SINGLE;
	unsigned int current_balance;
	EN_CARD_TYPE current_cardType;
	AssignCard(cardNo, enCardType, pre_balance);

	UN_CMD unCmd;
	unCmd.stCmdFillCharge.cardCharge = charge;
	unCmd.stCmdFillCharge.cardNo = cardNo;
	unCmd.stCmdFillCharge.cmd[0] = 'F';
	char returnStr[MAX_SEND_BUFFER_LENGTH];

	
	ProcFillChargeCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string expectStr = "乘车卡充值<失败><卡号=0><卡类型=单程卡><失败原因=单程卡不能充值>";
	EXPECT_EQ(expectStr, resultStr);
	GetCardInfo(cardNo,current_balance,current_cardType);
	EXPECT_EQ(5,current_balance);
	EXPECT_EQ(EN_CARD_TYPE_SINGLE, current_cardType);
	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;
}
//无效的卡类型
TEST_F(subwayFillChargeProcTest, subwayFillChargeProcTest_ValidCardTest) {

	unsigned int pre_balance = 5;  //原金额
	unsigned int charge = 100;    //充值金额
	unsigned int cardNo;

	UN_CMD unCmd;
	unCmd.stCmdFillCharge.cardCharge = charge;
	unCmd.stCmdFillCharge.cardNo = 100;
	unCmd.stCmdFillCharge.cmd[0] = 'F';
	char returnStr[MAX_SEND_BUFFER_LENGTH];

	ProcFillChargeCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string expectStr = "乘车卡充值<失败><卡号=100><卡类型=无效卡类型><失败原因=无效的地铁卡>";
	EXPECT_EQ(expectStr, resultStr);

	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;
}
//充值超过上限
TEST_F(subwayFillChargeProcTest, subwayFillChargeProcTest_OutOfMoneyTest) {

	unsigned int pre_balance = 100;  //原金额
	unsigned int charge = 900;    //充值金额
	unsigned int cardNo;
	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	unsigned int current_balance;
	EN_CARD_TYPE current_cardType;
	AssignCard(cardNo, enCardType, pre_balance);

	UN_CMD unCmd;
	unCmd.stCmdFillCharge.cardCharge = charge;
	unCmd.stCmdFillCharge.cardNo = cardNo;
	unCmd.stCmdFillCharge.cmd[0] = 'F';
	char returnStr[MAX_SEND_BUFFER_LENGTH];


	ProcFillChargeCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string expectStr = "乘车卡充值<失败><卡号=0><卡类型=普通卡><失败原因=办卡或充值后总余额超过上限>";
	EXPECT_EQ(expectStr, resultStr);
	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;
	GetCardInfo(cardNo, current_balance, current_cardType);
	EXPECT_EQ(100, current_balance);
	EXPECT_EQ(EN_CARD_TYPE_NOMAL, current_cardType);
}

#endif