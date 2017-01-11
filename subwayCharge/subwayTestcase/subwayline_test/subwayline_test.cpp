#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayLine.h"

using namespace testing;

class subwayLineTest : public testing::Test
{
public:
    //测试套级别事件
    //在测试套中包含的用例运行前运行一次
    static void SetUpTestCase()     
    {
    }

    //在测试套中包含的用例运行全部运行结束后运行一次
    static void TearDownTestCase()
    {
    }

    //测试用例级别的事件
    //测试套中的每个用例开始运行前调用一次
    void SetUp()
    {
         //为减小测试测试套内用例之间的影响，这个可进行一些初始化动作
        InitSubwayLine();
    }

    //测试套中每个用例结束后运行一次
    void TearDown()
    {
         //可进行一些动态内存的释放操作
     }
};

//增加第一个站点，站名不满足要求，返回失败
TEST_F(subwayLineTest, AddStation_NameOutofRange_ReturnError)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = AddSubwayStation("S101", 1000);
    EXPECT_TRUE(EN_RETURN_INVALID_STATION == enValue);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}

//增加第一个站点，名称和距离都满足要求，返回成功
TEST_F(subwayLineTest, AddStation_FirstStationNameOk_ReturnSucc)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = AddSubwayStation("S1", 0);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    unsigned int dis = 0;
    enValue = GetSubwayStationDis("S1", "S1", dis);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);
    EXPECT_TRUE(0 == dis);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}

//重复增加一个站点，增加错误
TEST_F(subwayLineTest, AddStation_AddTheSameStationRepeat_ReturnErr)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = EN_RETURN_SUCC;
    enValue = AddSubwayStation("S1", 0);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S1", 1000);
    EXPECT_TRUE(EN_RETURN_ADD_STATION_REPEAT == enValue);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}

//增加第二个站点，和前一站点的距离为0，返回错误
TEST_F(subwayLineTest, AddStation_SecondStationDis0_ReturnErr)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = EN_RETURN_SUCC;
    enValue = AddSubwayStation("S1", 0);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S2", 0);
    EXPECT_TRUE(EN_RETURN_INVALID_DIS == enValue);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}

//增加第二个站点，和前一站点的距离为51Km，返回错误
TEST_F(subwayLineTest, AddStation_SecondStationDis51Km_ReturnErr)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = EN_RETURN_SUCC;
    enValue = AddSubwayStation("S1", 0);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S2", 51000);
    EXPECT_TRUE(EN_RETURN_INVALID_DIS == enValue);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}

//增加两个站点成功后，获取两站点间的距离成功
TEST_F(subwayLineTest, AddStation_AddTwoStaionGetDisSucc_ReturnSucc)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = EN_RETURN_SUCC;
    enValue = AddSubwayStation("S1", 0);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S2", 1200);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    unsigned int dis = 0;
    enValue = GetSubwayStationDis("S1", "S2", dis);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);
    EXPECT_TRUE(1200 == dis);

    enValue = GetSubwayStationDis("S2", "S1", dis);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);
    EXPECT_TRUE(1200 == dis);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}

//输入起始站点名称不在范围，返回错误
TEST_F(subwayLineTest, QueryDis_SrcStationInvalidNo_ReturnErr)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = EN_RETURN_SUCC;
    enValue = AddSubwayStation("S1", 0);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S2", 1200);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    unsigned int dis = 0;
    enValue = GetSubwayStationDis("S101", "S2", dis);
    EXPECT_TRUE(EN_RETURN_INVALID_STATION == enValue);
    EXPECT_TRUE(0 == dis);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}

//输入目的站点名称不在范围，返回错误
TEST_F(subwayLineTest, QueryDis_DstStationInvalidNo_ReturnErr)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = EN_RETURN_SUCC;
    enValue = AddSubwayStation("S1", 0);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S2", 1200);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    unsigned int dis = 0;
    enValue = GetSubwayStationDis("S1", "S102", dis);
    EXPECT_TRUE(EN_RETURN_INVALID_STATION == enValue);
    EXPECT_TRUE(0 == dis);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}

//输入起始站点未投入使用，返回错误
TEST_F(subwayLineTest, QueryDis_SrcStationUnused_ReturnErr)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = EN_RETURN_SUCC;
    enValue = AddSubwayStation("S1", 0);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S2", 1200);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    unsigned int dis = 0;
    enValue = GetSubwayStationDis("S10", "S2", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);
    EXPECT_TRUE(0 == dis);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}

//输入目标站点未投入使用，返回错误
TEST_F(subwayLineTest, QueryDis_DstStationUnused_ReturnErr)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = EN_RETURN_SUCC;
    enValue = AddSubwayStation("S1", 0);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S2", 1200);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    unsigned int dis = 0;
    enValue = GetSubwayStationDis("S1", "S12", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);
    EXPECT_TRUE(0 == dis);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}

//输入起始站点和目标站点都满足要求，返回成功
TEST_F(subwayLineTest, QueryDis_StationOK_ReturnSucc)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = EN_RETURN_SUCC;
    enValue = AddSubwayStation("S1", 0);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S2", 1200);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S3", 2200);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S4", 1000);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    unsigned int dis = 0;
    enValue = GetSubwayStationDis("S1", "S4", dis);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);
    EXPECT_TRUE(4400 == dis);

    enValue = GetSubwayStationDis("S4", "S1", dis);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);
    EXPECT_TRUE(4400 == dis);

    enValue = GetSubwayStationDis("S1", "S3", dis);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);
    EXPECT_TRUE(3400 == dis);

    enValue = GetSubwayStationDis("S3", "S1", dis);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);
    EXPECT_TRUE(3400 == dis);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}


//没有增加站点, 销毁后，查询任意站点间的距离均是“未启用的站点”
TEST_F(subwayLineTest, DestroyLine_NoUsedStaion)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = EN_RETURN_SUCC;
    (void)DelSubwayLine();

    unsigned int dis = 0;
    enValue = GetSubwayStationDis("S1", "S3", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);

    enValue = GetSubwayStationDis("S3", "S90", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);

    enValue = GetSubwayStationDis("S99", "S1", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);

    enValue = GetSubwayStationDis("S0", "S50", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);

    enValue = GetSubwayStationDis("S99", "S0", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);
}

//增加了站点, 销毁后，查询任意站点间的距离均是“未启用的站点”
TEST_F(subwayLineTest, DestroyLine_UsedStaion)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EN_RETURN_CODE enValue = EN_RETURN_SUCC;

    enValue = AddSubwayStation("S0", 0);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S1", 1200);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S50", 2200);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    enValue = AddSubwayStation("S99", 1000);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);

    //查询距离正常
    unsigned int dis = 0;
    enValue = GetSubwayStationDis("S1", "S99", dis);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);
    EXPECT_TRUE(3200 == dis);

    enValue = GetSubwayStationDis("S50", "S99", dis);
    EXPECT_TRUE(EN_RETURN_SUCC == enValue);
    EXPECT_TRUE(1000 == dis);

    //销毁
    (void)DelSubwayLine();

    enValue = GetSubwayStationDis("S1", "S99", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);

    enValue = GetSubwayStationDis("S99", "S0", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);

    enValue = GetSubwayStationDis("S0", "S50", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);

    enValue = GetSubwayStationDis("S50", "S0", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);

    enValue = GetSubwayStationDis("S99", "S0", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);

    enValue = GetSubwayStationDis("S99", "S1", dis);
    EXPECT_TRUE(EN_RETURN_STATION_UNUSED == enValue);
}


#endif
