#ifndef __SUBWAY_CMD_PARSE_H__
#define __SUBWAY_CMD_PARSE_H__
#include "subwayGlobalDef.h"

#define MAX_CMD_LENGTH 4
#define MAX_CARD_TYPE_LENGTH 4
#define MAX_STATION_NAME_LENGTH 32

/*******************************通用类型************************************************************/
//命令类型枚举
typedef enum
{
    EN_CMD_TYPE_DEDUCT = 0,
    EN_CMD_TYPE_SINGLE_TICKET,
    EN_CMD_TYPE_CREATE_CARD,
    EN_CMD_TYPE_FILL_CHARGE,
    EN_CMD_TYPE_QUERY_HIS,
    EN_CMD_TYPE_DESTROY_CARD,
    EN_CMD_TYPE_QUERY_LINE,
    EN_CMD_TYPE_INVALID_CMD,
    EN_CMD_TYPE_RESET,
    EN_CMD_TYPE_BUTT
}EN_CMD_TYPE;

/*******************************各命令结构************************************************************/
//扣费命令
typedef struct
{
    char cmd[MAX_CMD_LENGTH];
    int cardNo;
    ST_SUBWAY_TIME enterTime;
    char enterStation[MAX_STATION_NAME_LENGTH];
    ST_SUBWAY_TIME exitTime;
    char exitStation[MAX_STATION_NAME_LENGTH];
}ST_CMD_DEDUCT;

//办理单程卡命令
typedef struct
{
    char cmd[MAX_CMD_LENGTH];
    char srcStation[MAX_STATION_NAME_LENGTH];
    char dstStation[MAX_STATION_NAME_LENGTH];
}ST_CMD_SINGLE_TICKET;

//办理普通卡或老年卡命令
typedef struct
{
    char cmd[MAX_CMD_LENGTH];
    //EN_CARD_TYPE enCard;
    char cardType[MAX_CARD_TYPE_LENGTH];
    int cardCharge;
}ST_CMD_CREATE_CARD;

//充值命令
typedef struct
{
    char cmd[MAX_CMD_LENGTH];
    int cardNo;
    int cardCharge;
}ST_CMD_FILL_CHARGE;

//查询历史消费命令
typedef struct
{
    char cmd[MAX_CMD_LENGTH];
    int cardNo;
}ST_CMD_QUERY_HIS;

//销毁卡
typedef struct
{
    char cmd[MAX_CMD_LENGTH];
    int cardNo;
}ST_CMD_DESTROY_CARD;

//查询线路
typedef struct
{
    char cmd[MAX_CMD_LENGTH];
}ST_CMD_QUERY_LINE;

//重置系统
typedef struct
{
    char cmd[MAX_CMD_LENGTH];
}ST_CMD_RESET;

/*******************************解析后的命令结构******************************************************/
//命令联合
typedef union
{
    ST_CMD_DEDUCT stCmdDeduct;
    ST_CMD_SINGLE_TICKET stCmdSingleTicket;
    ST_CMD_CREATE_CARD stCmdCreateCard;
    ST_CMD_FILL_CHARGE stCmdFillCharge;
    ST_CMD_QUERY_HIS stCmdQueryHis;
    ST_CMD_QUERY_LINE stCmdQueryLine;
}UN_CMD;

//通用命令结构
typedef struct
{
    EN_CMD_TYPE enCmdType;
    UN_CMD unCmd;
}ST_COMM_CMD;


/*******************************命令解码函数入口******************************************************/
//解码命令函数
int cmdParse(ST_COMM_CMD &stCommCmd, const char* cmdStr);

//获取命令名称字符串
char* GetCmdNameStr(EN_CMD_TYPE enCmd);
#endif