#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"

using namespace testing;

class subwayPriceTest : public testing::Test
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
    }

    //测试套中每个用例结束后运行一次
    void TearDown()
    {
         //可进行一些动态内存的释放操作
     }
};

//****
TEST_F(subwayPriceTest, Test1)
{
  	//1 变量定义,初始化
    
     
    //2  用户写自己的测试流程，调用被测函数
    EXPECT_TRUE(1 == 1);

    //3  可以使用gtest的断言来进行用例通过与否的判断
    
}

#endif