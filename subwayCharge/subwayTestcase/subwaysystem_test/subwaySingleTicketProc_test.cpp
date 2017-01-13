#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"

#include "subwayLine.h"
#include "subwayCommand\subwayCmdProc\include\subwaySingleTicketProc.h"
using namespace testing;


class subwaySingleTicketProcTest : public testing::Test
{
public:
	//测试套级别事件
	//在测试套中包含的用例运行前运行一次
	static void SetUpTestCase()
	{
		cout << " -----------开始运行：subwaySingleTicketProcTest-----------------" << endl;
		InitSubwayLine();
		SetDefaultLine();
		//DeleteAllCardInfo();

	}

	//在测试套中包含的用例运行全部运行结束后运行一次
	static void TearDownTestCase()
	{
		cout << " -----------结束运行：subwaySingleTicketProcTest-----------------" << endl;
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


//测试用例：成功购买单程票
// "r   s s0 s1";

TEST_F(subwaySingleTicketProcTest, ProcCreateSingleTicketCmd_StationSuccessTest) {


	UN_CMD unCmd;
	unCmd.stCmdSingleTicket.cmd[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[1] = '0';
	unCmd.stCmdSingleTicket.srcStation[2] = '0';
	unCmd.stCmdSingleTicket.srcStation[3] = '0';

	unCmd.stCmdSingleTicket.dstStation[0] = 'S';
	unCmd.stCmdSingleTicket.dstStation[1] = '0';
	unCmd.stCmdSingleTicket.dstStation[2] = '0';
	unCmd.stCmdSingleTicket.dstStation[3] = '1';

	char result[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "购买单程票<成功><卡号=0><卡类型=单程卡><余额=2>";
	ProcCreateSingleTicketCmd(unCmd, result);
	string resultStr(&result[0], &result[strlen(result)]);
	//cout << "------------------expectStr="<< expectStr <<endl;
	//cout << "------------------resultStr=" << resultStr << endl;
	EXPECT_EQ(expectStr, resultStr);
}

//测试用例：购买单程票失败  地铁站不存在
// "r   s s100 s1";

TEST_F(subwaySingleTicketProcTest, ProcCreateSingleTicketCmd_Station2NotExitTest) {

	UN_CMD unCmd;
	unCmd.stCmdSingleTicket.cmd[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[1] = '0';
	unCmd.stCmdSingleTicket.srcStation[2] = '0';
	unCmd.stCmdSingleTicket.srcStation[3] = '0';

	unCmd.stCmdSingleTicket.dstStation[0] = 'S';
	unCmd.stCmdSingleTicket.dstStation[1] = '1';
	unCmd.stCmdSingleTicket.dstStation[2] = '0';
	unCmd.stCmdSingleTicket.dstStation[3] = '1';

	char result[MAX_SEND_BUFFER_LENGTH];

	string expectStr = "购买单程票<失败><失败原因=无效的地铁站>";
	
	ProcCreateSingleTicketCmd(unCmd, result);
	string resultStr(&result[0], &result[strlen(result)]);
	//cout << "------------------expectStr=" << expectStr << endl;
	//cout << "------------------resultStr=" << resultStr << endl;
	EXPECT_EQ(expectStr, resultStr);
}

//测试用例：购买单程票失败  超过容量
// "r   s s100 s1";

TEST_F(subwaySingleTicketProcTest, ProcCreateSingleTicketCmd_Station1NotExitTest) {

	UN_CMD unCmd;
	unCmd.stCmdSingleTicket.cmd[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[1] = '1';
	unCmd.stCmdSingleTicket.srcStation[2] = '0';
	unCmd.stCmdSingleTicket.srcStation[3] = '0';

	unCmd.stCmdSingleTicket.dstStation[0] = 'S';
	unCmd.stCmdSingleTicket.dstStation[1] = '0';
	unCmd.stCmdSingleTicket.dstStation[2] = '0';
	unCmd.stCmdSingleTicket.dstStation[3] = '1';

	char result[MAX_SEND_BUFFER_LENGTH];

	string expectStr= "购买单程票<失败><失败原因=无效的地铁站>";
	ProcCreateSingleTicketCmd(unCmd, result);
	string resultStr(&result[0], &result[strlen(result)]);
	//cout << "------------------expectStr=" << expectStr << endl;
	//cout << "------------------resultStr=" << resultStr << endl;
	EXPECT_EQ(expectStr, resultStr);
}

TEST_F(subwaySingleTicketProcTest, ProcCreateSingleTicketOutOfRangeTest) {

	UN_CMD unCmd;
	unCmd.stCmdSingleTicket.cmd[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[1] = '0';
	unCmd.stCmdSingleTicket.srcStation[2] = '0';
	unCmd.stCmdSingleTicket.srcStation[3] = '2';

	unCmd.stCmdSingleTicket.dstStation[0] = 'S';
	unCmd.stCmdSingleTicket.dstStation[1] = '0';
	unCmd.stCmdSingleTicket.dstStation[2] = '0';
	unCmd.stCmdSingleTicket.dstStation[3] = '1';

	char result[MAX_SEND_BUFFER_LENGTH];	
	string expectStr = "购买单程票<失败><失败原因=申请的卡超出系统容量>";

	ProcCreateSingleTicketCmd(unCmd, result);
	for (int i = 0; i < 200; i++)  ProcCreateSingleTicketCmd(unCmd, result);  //买100张
	ProcCreateSingleTicketCmd(unCmd, result);   //超过100张
	string resultStr(&result[0], &result[strlen(result)]);
	/*cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;*/
	EXPECT_EQ(expectStr, resultStr);
}

#endif