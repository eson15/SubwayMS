#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"

#include "../../subwayCommand/subwayCmdProc/include/subwayQueryLineProc.h"
#include "subwayLine.h"

using namespace testing;

class subwayQueryLineProcTest : public testing::Test
{
public:
	//测试套级别事件
	//在测试套中包含的用例运行前运行一次
	static void SetUpTestCase()
	{
		cout << " -----------开始运行：subwayQueryLineProc_test-----------------" << endl;
		InitSubwayLine();
		SetDefaultLine();
	}

	//在测试套中包含的用例运行全部运行结束后运行一次
	static void TearDownTestCase()
	{
		cout << " -----------结束运行：subwayQueryLineProc_test-----------------" << endl;
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


//测试用例1:   查询地铁线路  ProcQueryLineCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])

TEST_F(subwayQueryLineProcTest, ProcQueryLineCmd_SucessTest) {

	char result[MAX_SEND_BUFFER_LENGTH];
	string expectStr="地铁线路：S0<->S1<->S2<->S3<->S4<->S5<->S6<->S7<->S8<->S9<->S10<->S11<->S12<->S13<->S14<->S15<->S16";
	UN_CMD unCmd;
	unCmd.stCmdQueryLine.cmd[0] = 'L';

	//ProcQueryLineCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
	ProcQueryLineCmd(unCmd, result);
	string resultStr(&result[0], &result[99]);
	EXPECT_EQ(expectStr, resultStr);
	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;


}


#endif