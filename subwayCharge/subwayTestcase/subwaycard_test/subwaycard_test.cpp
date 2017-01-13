#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"

using namespace testing;

class subwayCardTest : public testing::Test
{
public:
  
    static void SetUpTestCase()     
    {
		cout <<" -----------开始运行：subwayCardTest-----------------"<< endl;
		//初始化卡信息
//		InitCardManagerInfo();
    }   
    static void TearDownTestCase()
    {
//		DeleteAllCardInfo();
//		InitCardQueue(cardNumQueue);
		cout << " -----------结束运行：subwayCardTest-----------------" << endl;
    }   
    void SetUp()
    {
		DeleteAllCardInfo();
		InitCardQueue();
    }

    
    void TearDown()
    {
         
     }
};


/*---------------办卡测试用例1-2-----------------------*/
//测试用例1：测试系统卡数量<100   
//入参：单程卡  3  
//返回：{,,,,,,}

TEST_F(subwayCardTest, AssignCard_CardMostNumTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	int charge = 3;
	unsigned int cardNo;
	EN_RETURN_CODE code;

	//前100张成功办卡

	for (int i = 0; i < 100; i++) {
		code = AssignCard(cardNo, enCardType, charge);		
		EXPECT_EQ(code, EN_RETURN_SUCC);
	}
	//100张后无法办理
	for (int i = 0; i < 5; i++) {		
		code = CheckAvailCard();
		EXPECT_EQ(code, EN_RETURN_CARD_OVERLOW);
	}
}
//测试用例2：单程卡 卡号分配、充值金额是否正确？   
//入参：单程卡  5  
//返回：{,,,,,,}
TEST_F(subwayCardTest, AssignCard_SucessSingleCardTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_SINGLE;
	unsigned int charge = 5;

	unsigned int cardNo;
	unsigned int current_balance;
	EN_CARD_TYPE currentCardType;

	EN_RETURN_CODE success_code = AssignCard(cardNo, enCardType, charge);  //办卡

	EXPECT_EQ(success_code, EN_RETURN_SUCC);    //返回码正确？
	EXPECT_TRUE(cardNo >= 0 && cardNo <= 99);      //分配卡号正确？	

	GetCardInfo(cardNo, current_balance, currentCardType);   //充值后的卡金额、卡类型
	EXPECT_EQ(current_balance, charge);	       //充值金额是否正确
	EXPECT_EQ(currentCardType,enCardType);	   //分配卡类型是否正确

}
//测试用例3：普通卡 卡号分配、充值金额是否正确？   
//入参：单程卡 100  
//返回：{,,,,,,}
TEST_F(subwayCardTest, AssignCard_SucessNormalCardTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	unsigned int charge = 100;

	unsigned int cardNo;
	unsigned int current_balance;
	EN_CARD_TYPE currentCardType;

	EN_RETURN_CODE success_code = AssignCard(cardNo, enCardType, charge);  //办卡

	EXPECT_EQ(success_code, EN_RETURN_SUCC);    //返回码正确？
	EXPECT_TRUE(cardNo >= 0 && cardNo <= 99);      //分配卡号正确？	

	GetCardInfo(cardNo, current_balance, currentCardType);   //充值后的卡金额、卡类型
	EXPECT_EQ(current_balance, charge);	       //充值金额是否正确
	EXPECT_EQ(currentCardType, enCardType);	   //分配卡类型是否正确

}

/*---------------普通卡充值测试用例1-4-----------------------*/
//测试用例1： 正确进行充值
//入参：cardNo  recharge
//返回值：EN_RETURN_SUCC

TEST_F(subwayCardTest, RechargeCard_SuccessTest) {

	unsigned int cardNo;
	unsigned int current_balance;
	unsigned int charge = 100;
	unsigned int recharge = 100;
	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	EN_CARD_TYPE enCard;

	AssignCard(cardNo, enCardType, charge);  //办卡
	EN_RETURN_CODE success_code = RechargeCard(cardNo, recharge);    //充值100元	
	EXPECT_TRUE(EN_RETURN_SUCC == success_code);  //返回码是否正确
	GetCardInfo(cardNo, current_balance, enCard);   //充值后的卡金额
	EXPECT_TRUE(200 == current_balance);	   //充值金额是否正确

}


//测试用例4：测试充值总金额 0-999

TEST_F(subwayCardTest, RechargeCard_reChargeMoneyTest) {

	unsigned int cardNo;
	unsigned int current_balance;
	unsigned int charge = 100;
	unsigned int recharge = 100;
	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	EN_RETURN_CODE code;

	AssignCard(cardNo, enCardType, charge);  //办卡 100

	code = RechargeCard(cardNo, 10);   //返回值   110
	EXPECT_EQ(EN_RETURN_SUCC, code);
	code = RechargeCard(cardNo,20);   //返回值   130
	EXPECT_EQ(EN_RETURN_SUCC, code);
	code = RechargeCard(cardNo, 100);   //返回值   230
	EXPECT_EQ(EN_RETURN_SUCC, code);
	code = RechargeCard(cardNo, 900);   //返回值   1130
	EXPECT_EQ(EN_RETURN_RECHARGE_OVERFLOW, code);
}

/*-----------------------查询卡信息测试用例1-3-------------------------------*/

//测试用例1： 正确返回正确信息（普通卡）  
//入参：cardNo  
//出参：金额 balance   卡类型  cardtype
TEST_F(subwayCardTest, GetCardInfo_SuccessNomalTest) {

	
	unsigned int cardNo;
	unsigned int expect_balance= 10;
	unsigned int balance;
	EN_CARD_TYPE enCard;

	AssignCard(cardNo, EN_CARD_TYPE_NOMAL, expect_balance);	
	EN_RETURN_CODE success_code = GetCardInfo(cardNo, balance, enCard);

	EXPECT_TRUE(success_code == EN_RETURN_SUCC);    //返回值是否正确
	EXPECT_TRUE(enCard == EN_CARD_TYPE_NOMAL);       //卡类型是否正确
	EXPECT_TRUE(balance == expect_balance);         //余额是否正确
}

//测试用例2： 正确返回正确信息（单程卡）  
//入参：cardNo  
//出参：金额 balance   卡类型  cardtype
TEST_F(subwayCardTest, GetCardInfo_SuccessSingleTest) {

	unsigned int cardNo;
	unsigned int expect_balance = 3;
	AssignCard(cardNo, EN_CARD_TYPE_SINGLE, expect_balance);

	unsigned int balance;
	EN_CARD_TYPE enCard;
	EN_RETURN_CODE success_code = GetCardInfo(cardNo, balance, enCard);

	EXPECT_TRUE(success_code == EN_RETURN_SUCC);    //返回值是否正确
	EXPECT_TRUE(enCard == EN_CARD_TYPE_SINGLE);       //卡类型是否正确
	EXPECT_TRUE(balance == expect_balance);         //余额是否正确
}

//测试用例3： 输入卡号有误  
//入参：cardNo  
//出参：金额 balance   卡类型  cardtype

TEST_F(subwayCardTest, GetCardInfo_ValidCardTest) {

	unsigned int cardNo = 120;
	unsigned int balance;
	EN_CARD_TYPE enCard = EN_CARD_TYPE_SINGLE;

	EN_RETURN_CODE fail_code = GetCardInfo(cardNo, balance, enCard);
	EXPECT_EQ(EN_RETURN_INVALID_CARD, fail_code);
}


/*-----------------------扣费功能测试用例1-3-------------------------------*/

//测试用例1： 普通卡正确进行扣费 ,并返回正确信息（余额） 
//入参： cardNo,卡号;
//         card, 卡类型; 
//  deductPrice, 扣费票价   
//出参: balance, 扣费后的余额
TEST_F(subwayCardTest, DeductCard_NomalSuccessTest) {

	//输入参数
	unsigned int cardNo;
	unsigned int balance = 100;  //卡余额
	unsigned int deductPrice = 5;   //扣费5
	EN_CARD_TYPE enCard= EN_CARD_TYPE_BUTT;
	AssignCard(cardNo, EN_CARD_TYPE_NOMAL, balance);

	//期待扣费后卡余额
	unsigned int expect_balance = 95;
	//扣费后输出卡余额
	unsigned int return_balance=0;
	//实际查询的扣费后卡余额
	unsigned int current_balance=0;

	EN_RETURN_CODE success_code = DeductCard(cardNo, enCard, deductPrice, balance);   //扣费
	GetCardInfo(cardNo, current_balance, enCard); //获取扣费后卡信息

	EXPECT_EQ(success_code, EN_RETURN_SUCC);     //返回码是否正确
	EXPECT_EQ(current_balance, expect_balance);     //  是否正确修改卡余额	
}

////测试用例2： 单程卡正确进行扣费 ,并返回正确信息（余额） 
////入参： cardNo,卡号;
////         card, 卡类型; 
////  deductPrice, 扣费票价   
////出参: balance, 扣费后的余额
//
TEST_F(subwayCardTest, DeductCard_SingleSuccessTest) {

//输入参数
unsigned int cardNo;
unsigned int balance = 5;  //扣费前卡余额
unsigned int deductPrice = 5;   //扣费5元
EN_CARD_TYPE enCard;
AssignCard(cardNo, EN_CARD_TYPE_SINGLE, balance);

//期待扣费后卡余额
unsigned int expect_balance = 0;

//实际查询的扣费后卡余额
unsigned int current_balance;

GetCardInfo(cardNo, balance, enCard);   //获取原始卡信息
EN_RETURN_CODE success_code = DeductCard(cardNo, enCard, deductPrice, balance);   //扣费
GetCardInfo(cardNo, current_balance, enCard); //获取扣费后卡信息

EXPECT_EQ(EN_RETURN_SUCC, success_code);     //返回码是否正确
//EN_RETURN_BALANCE_TOO_LOW
EXPECT_EQ(current_balance, expect_balance);     //  是否正确修改卡余额
}
//
//测试用例3： 普通卡卡内余额不足  1元
//入参： cardNo,卡号;
//         card, 卡类型; 
//  deductPrice, 扣费票价   
//出参: balance, 扣费后的余额

TEST_F(subwayCardTest, DeductCard_NOMALShortOfMoneyTest) {

	unsigned int cardNo;
	unsigned int balance = 0;  //扣费前卡余额
	unsigned int deductPrice = 5;   //扣费5元
	EN_CARD_TYPE enCard = EN_CARD_TYPE_BUTT;
	unsigned int current_balance;  //实际查询的扣费后卡余额
	AssignCard(cardNo, EN_CARD_TYPE_NOMAL, balance);
	
	EN_RETURN_CODE fail_code = DeductCard(cardNo, enCard, deductPrice, balance);   //扣费
	GetCardInfo(cardNo, current_balance, enCard); //获取扣费后卡信息

	EXPECT_EQ(EN_RETURN_BALANCE_NOT_ENOUGH, fail_code);     //返回码是否正确
	EXPECT_EQ(current_balance, 0);     //  是否正确修改卡余额
}


//测试用例4： 单程卡卡内余额不足  1元
//入参： cardNo,卡号;
//         card, 卡类型; 
//  deductPrice, 扣费票价   
//出参: balance, 扣费后的余额

TEST_F(subwayCardTest, DeductCard_SingleShortOfMoneyTest) {

	unsigned int cardNo;
	unsigned int balance = 0;  //扣费前卡余额
	unsigned int deductPrice = 5;   //扣费5元
	EN_CARD_TYPE enCard = EN_CARD_TYPE_BUTT;
	unsigned int current_balance;  //实际查询的扣费后卡余额
	AssignCard(cardNo, EN_CARD_TYPE_SINGLE, balance);

	EN_RETURN_CODE fail_code = DeductCard(cardNo, enCard, deductPrice, balance);   //扣费
	GetCardInfo(cardNo, current_balance, enCard); //获取扣费后卡信息

	EXPECT_EQ(EN_RETURN_BALANCE_NOT_ENOUGH, fail_code);     //返回码是否正确
	EXPECT_EQ(current_balance, 0);     //  是否正确修改卡余额

}

#endif