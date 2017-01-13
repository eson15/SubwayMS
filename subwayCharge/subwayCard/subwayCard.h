#ifndef __SUBWAY_CARD_H__
#define __SUBWAY_CARD_H__
#include "subwayError.h"
#include "../subwayGlobal/subwayGlobalDef.h"
#include <queue>
using namespace std;



//最多允许系统开100张地铁卡
#define MAX_CARD_NUM 100

//最大余额值
#define MAX_BALANCE 999

//dongguanli
#define CARDNUM 100

//地铁卡类型
typedef enum
{
	EN_CARD_TYPE_SINGLE = 0,
	EN_CARD_TYPE_ELDER,
	EN_CARD_TYPE_NOMAL,
	EN_CARD_TYPE_BUTT
}EN_CARD_TYPE;



struct HISTORY {
	ST_SUBWAY_TIME inTime;
	ST_SUBWAY_TIME outTime;
	string inStation;
	string outStation;
	int pay;

	HISTORY();
	HISTORY(ST_SUBWAY_TIME inT, ST_SUBWAY_TIME outT, string inS, string outS, int p) :
		inTime(inT), outTime(outT), inStation(inS), outStation(outS), pay(p) {}

};



class CARD {
public:
	CARD() :num(0), type(EN_CARD_TYPE_BUTT), balance(0) {}

	CARD(unsigned int n, EN_CARD_TYPE t, unsigned int b = 0) : num(n), type(t), balance(b) {}
	~CARD()
	{
		
		HISTORY *h;
		/*try
		{*/
			while (!q_history.empty())
			{
				h = q_history.front();
				q_history.pop();
				if (NULL != h)
				{
					delete h;
					h = nullptr;
				}
			}
		//}
		//catch (const exception& e)
		//{
		//	//cerr << "Exception: " << e.what() << endl;
		//}
	}


	void setBalance(unsigned int b)
	{
		balance = b;
	}
	unsigned int getBalance()
	{
		return balance;
	}
	void updateHistory(HISTORY *record)
	{
		q_history.push(record);
	}
	unsigned int getNum()
	{
		return num;
	}
	EN_CARD_TYPE getType()
	{
		return type;
	}

private:
	unsigned int num;
	EN_CARD_TYPE type;
	unsigned int balance;
	queue<HISTORY*> q_history;

};
/*
@ 初始化所有卡信息
@ 返回值: 无
*/
void InitCardManagerInfo();

/*
@ 开卡，分配卡号和卡信息
@ 入参：enCard,卡类型; charge: 充值
@ 出参: cardNo, 分配的卡号
@ 返回值: EN_RETURN_SUCC，分配成功; EN_RETURN_CARD_OVERLOW, 分配失败;
*/
EN_RETURN_CODE AssignCard(unsigned int &cardNo, EN_CARD_TYPE enCard, unsigned int charge);


/*
@ 充值
@ 入参：cardNo,卡号; recharge: 充值
@ 出参: 无
@ 返回值: EN_RETURN_SUCC，成功; 其他, 失败;
*/
EN_RETURN_CODE RechargeCard(unsigned int cardNo, unsigned int recharge);

/*
@ 获取卡信息
@ 入参：cardNo,卡号;
@ 出参: balance: 余额
		enCard:  卡类型
@ 返回值: EN_RETURN_SUCC，成功; EN_RETURN_INVALID_CARD, 失败;
*/
EN_RETURN_CODE GetCardInfo(unsigned int cardNo, unsigned int &balance, EN_CARD_TYPE &enCard);

/*
@ 卡扣费
@ 入参：cardNo,卡号; enCard, 卡类型; deductPrice, 扣费票价
@ 出参: balance, 扣费后的余额;
@ 返回值: EN_RETURN_SUCC，成功; EN_RETURN_INVALID_CARD, EN_RETURN_BALANCE_NOT_ENOUGH, 失败;
*/
EN_RETURN_CODE DeductCard(unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int deductPrice, unsigned int &balance);

/*
@ 根据卡类型字符串, 识别卡类型
@ 入参：cardType,      卡类型字符串;
@ 出参: enCard,        卡类型
@ 返回值: EN_RETURN_SUCC，成功; EN_RETURN_INPUT_INVALID_CARDTYPE, 失败;
*/
EN_RETURN_CODE GetCardType(char cardType[], EN_CARD_TYPE &enCard);

/*
@ 删除卡信息
@ 入参：cardNo,卡号;
@ 出参: 无
@ 返回值: 0，成功; -1, 失败;
*/
int DeleteCard(unsigned int cardNo);

/*
@ 获取卡类型字符串
@ 入参：enCard,卡类型;
@ 出参: 无
@ 返回值: 卡类型字符串，比如"普通卡";
*/
char* GetCardTypeStr(EN_CARD_TYPE enCard);

void InitCardQueue(queue<unsigned int> &cardNumQueueTmp);

void GetAssignedCardNum(unsigned int &cardNo);

bool CheckChargeValue(int chargeValue);

EN_RETURN_CODE CheckAvailCard();

EN_RETURN_CODE CheckTime(ST_SUBWAY_TIME enterTime, ST_SUBWAY_TIME exitTime);

unsigned int CalDurationTime(ST_SUBWAY_TIME enterTime, ST_SUBWAY_TIME exitTime);

EN_RETURN_CODE DeleteAllCardInfo();



#endif