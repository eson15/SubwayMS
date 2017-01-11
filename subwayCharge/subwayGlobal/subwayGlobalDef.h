#ifndef __SUBWAY_GLOBAL_H__
#define __SUBWAY_GLOBAL_H__

//Socket通信接收和发送缓存最大长度
#define MAX_RECEIVE_BUFFER_LENGTH 2048
#define MAX_SEND_BUFFER_LENGTH 2048

//地铁系统时间
typedef struct
{
    int hour;
    int minutes;
}ST_SUBWAY_TIME;

#endif