#ifndef __SUBWAY_MACRO_H__
#define __SUBWAY_MACRO_H__

//检查时间格式是否正确
#define CHECK_TIME(timeTmp) (((timeTmp)->hour < 24) && ((timeTmp)->minutes <= 60))

//计算时间差
#define DIFF_TIME(time1, time2, diffMinutes) \
    (diffMinutes) = ((time1)->hour - (time2)->hour) * 60;\
    (diffMinutes) += ((time1)->minutes - (time2)->minutes);

//常用参数判断宏和内存释放宏
#define IF_INVALID_BREAK(condition) if(!(condition)) {break;}
#define IF_INVALID_RETURN(condition, returnValue) if(!(condition)) {return (returnValue);}
#define IF_INVALID_RETURN_NOVALUE(condition) if(!(condition)) {return ;}
#define IF_INVALID_SET_RETURN_VALUE(condition, returnValue, returenPara) if(!(condition)) {(returenPara) = (returnValue);}
#define FREE_PTR(ptr) if((ptr)) {free((ptr)); (ptr) = NULL;}

//求数组大小
#define SIZE(arr) sizeof((arr))/sizeof((arr)[0])

//求最大值
static inline int MaxValue(int x, int y)
{
    return (x > y) ? x : y;
}

//求最小值
static inline int MinValue(int x, int y)
{
    return (x < y) ? x : y;
}

#endif