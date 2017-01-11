#include  <sstream>
#include "list.h"
#include "subwayLine.h"
#include "subwayMacro.h"

using namespace std;


//非法站点号
#define INVALID_STATION_NO (unsigned int)(-1)

//地铁线路方向
typedef enum
{
    EN_DERECT_NEXT = 0,
    EN_DERECT_PREV,
    EN_DERECT_BUTT
}EN_DERECT;

//地铁站
typedef struct
{
    unsigned int no;
    bool usrFlag;
    TListHead list;
    unsigned int dis[EN_DERECT_BUTT];
}ST_STATION;

//地铁线路
typedef struct
{
    TListHead subwayLine;
}ST_LINE;

//地铁站和地铁线列表
ST_STATION g_stasionList[MAX_STATION_NUM];
ST_LINE g_line;


/*
@ 初始化地铁站信息
@ 返回值:void
*/
void InitStation(unsigned int stationNo)
{
    g_stasionList[stationNo].list.next = NULL;
    g_stasionList[stationNo].list.prev = NULL;
    g_stasionList[stationNo].dis[EN_DERECT_NEXT] = 0;
    g_stasionList[stationNo].dis[EN_DERECT_PREV] = 0;
    g_stasionList[stationNo].usrFlag = false;
    g_stasionList[stationNo].no = stationNo;
}

/*
@ 初始化地铁线路信息
@ 返回值:void
*/
void InitSubwayLine()
{
    for(int i = 0; i < MAX_STATION_NUM; i++)
    {
        InitStation(i);
    }

    InitListHead(&(g_line.subwayLine));
}

/*
@ 增加一个地铁站
@ 返回值: -1, 失败;  0, 成功
*/
EN_RETURN_CODE AddSubwayStation(char* stationName, unsigned int dis)
{
    unsigned int stationNo = atoi(&(stationName[1]));

    IF_INVALID_RETURN(stationNo < MAX_STATION_NUM, EN_RETURN_INVALID_STATION)
    IF_INVALID_RETURN(!(g_stasionList[stationNo].usrFlag), EN_RETURN_ADD_STATION_REPEAT)
    IF_INVALID_RETURN(dis <= MAX_DIS_BETWEEN_STATION, EN_RETURN_INVALID_DIS)

    if(ListEmpty(&(g_line.subwayLine)))
    {
        dis = 0;
    }
    else
    {
        IF_INVALID_RETURN(dis != 0, EN_RETURN_INVALID_DIS)

        //把反方向的距离填写成功
        TListHead* prevNode = g_line.subwayLine.prev;
        ST_STATION* prevStation = CONTAINER_OF(prevNode, ST_STATION, list);
        prevStation->dis[EN_DERECT_PREV] = dis;
    }

    //填写当前站点
    g_stasionList[stationNo].usrFlag = true;
    g_stasionList[stationNo].dis[EN_DERECT_PREV] = 0;
    g_stasionList[stationNo].dis[EN_DERECT_NEXT] = dis;  

    ListAddTail(&(g_stasionList[stationNo].list), &(g_line.subwayLine));
    return EN_RETURN_SUCC;
}

/*
@ 根据方向获取下一节点
@ 返回值: TListHead* tmpNode
*/
TListHead* GetNextNode(TListHead* srcNode, EN_DERECT enDerect)
{
    TListHead* tmpNode = NULL;

    if(EN_DERECT_NEXT == enDerect)
    {
        tmpNode = srcNode->next;
    }
    else
    {
        tmpNode = srcNode->prev;
    }
    return tmpNode;
}

/*
@ 朝固定方向查找目标站点
@ 返回值: 0: 成功, -1: 失败
*/
int GetOneDerectDis(TListHead* srcNode, EN_DERECT enDerect, unsigned int stationNo2, unsigned int &dis)
{
    TListHead* tmpNode = NULL;
    ST_STATION* tmpStation = NULL;
    tmpNode = GetNextNode(srcNode, enDerect);
    while((NULL != tmpNode) && ((&(g_line.subwayLine)) != tmpNode))
    {
        tmpStation = CONTAINER_OF(tmpNode, ST_STATION, list);
        dis += tmpStation->dis[enDerect];
        if(tmpStation->no == stationNo2)
        {
            return 0;
        }

        tmpNode = GetNextNode(tmpNode, enDerect);
    }
    return -1;
}

/*
@ 获取两个地铁站间的最小距离
@ 返回值: EN_RETURN_SUCC: 成功, 其他: 失败
*/
EN_RETURN_CODE GetSubwayStationDis(char* stationName1, char* stationName2, unsigned int &dis)
{
    unsigned int stationNo1 = atoi(&(stationName1[1]));
    unsigned int stationNo2 = atoi(&(stationName2[1]));

    IF_INVALID_RETURN(stationNo1 < MAX_STATION_NUM, EN_RETURN_INVALID_STATION)
    IF_INVALID_RETURN(stationNo2 < MAX_STATION_NUM, EN_RETURN_INVALID_STATION)
    IF_INVALID_RETURN(g_stasionList[stationNo1].usrFlag, EN_RETURN_STATION_UNUSED)
    IF_INVALID_RETURN(g_stasionList[stationNo2].usrFlag, EN_RETURN_STATION_UNUSED)

    if(stationNo1 == stationNo2)
    {
        dis = 0;
        return EN_RETURN_SUCC;
    }

    dis = 0;
    if(0 == GetOneDerectDis(&(g_stasionList[stationNo1].list), EN_DERECT_NEXT, stationNo2, dis))
    {
        return EN_RETURN_SUCC;
    }

    dis = 0;
    if(0 == GetOneDerectDis(&(g_stasionList[stationNo1].list), EN_DERECT_PREV, stationNo2, dis))
    {
        return EN_RETURN_SUCC;
    }

    return EN_RETURN_INNER_ERR;
}

/*
@ 删除地铁线
@ 返回值: void
*/
void DelSubwayLine()
{
    InitSubwayLine();
    return;
}

/*
@ 打印所有地铁线
*/
void GetLineInfo(string &outStr)
{
    ostringstream oss;

    oss<<"地铁线路：";

    TListHead* pos = NULL;
    ST_STATION* tmpStation = NULL;
    ListForEach(pos, &(g_line.subwayLine))
    {
        tmpStation = CONTAINER_OF(pos, ST_STATION, list);
        oss<<"S"<<tmpStation->no;
        if(!ListIsLast(pos, &(g_line.subwayLine)))
        {
            oss<<"<->";
        }
    }
    outStr = oss.str();
}

/*
@ 设置默认地铁线路
@ 返回值: NULL
*/
void SetDefaultLine()
{
    AddSubwayStation("S0", 0);
    AddSubwayStation("S1", 800);
    AddSubwayStation("S2", 2168);
    AddSubwayStation("S3", 2098);
    AddSubwayStation("S4", 2165);
    AddSubwayStation("S5", 1500);
    AddSubwayStation("S6", 1345);
    AddSubwayStation("S7", 1567);
    AddSubwayStation("S8", 1897);
    AddSubwayStation("S9", 1000);
    AddSubwayStation("S10", 900);
    AddSubwayStation("S11", 1168);
    AddSubwayStation("S12", 2000);
    AddSubwayStation("S13", 1600);
    AddSubwayStation("S14", 1485);
    AddSubwayStation("S15", 1600);
    AddSubwayStation("S16", 1888);
}