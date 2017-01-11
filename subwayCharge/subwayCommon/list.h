/******************************************************************************

版权所有 (C), 2016-2036,华为技术有限公司

******************************************************************************
文 件 名   : list.h
版 本 号   : 初稿
作    者   : 
生成日期   : 
最近修改   :
功能描述   : 链表的具体实现
函数列表   :
修改历史   :
1.日    期   : 
作    者   : 
修改内容   : 生成

******************************************************************************/

#ifndef _COMM_LIST_H
#define _COMM_LIST_H

/*链表的抽象结构体*/
typedef struct ListHead {
    struct ListHead *next;
    struct ListHead *prev;
}TListHead;


/*用来动态的对某个链表节点做初始化工作*/
#define InitListHead(ptr) do { \
    TListHead* list_head_ptr = (TListHead*)ptr; \
    list_head_ptr->next = list_head_ptr; \
    list_head_ptr->prev = list_head_ptr; \
} while (0)


/*获取链表节点的数据区地址*/
#define OFF_SET_OF(type,member) ((char*)&(((type *)0)->member))
#define CONTAINER_OF(ptr, type, member) ((type *)((char *)ptr - OFF_SET_OF(type,member)))
#define ListEntryGet(ptr, type, member)   CONTAINER_OF(ptr, type, member)

/*在没有删除动作的时候,第一个是安全的,否则就要使用safe的那个*/
#define ListForEach(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define  ListForEachSafe(pos, n, head) \
    for(pos = (head)->next,n = pos->next; pos != (head);pos = n, n = pos->next)


/*****************************************************************************
函 数 名  : __list_add
功能描述  : 双向链表插入的抽象
输入参数  : struct list_head *new
struct list_head *prev
struct list_head *next
输出参数  : 无
返 回 值  : 无

修改历史      :
1.日    期   : 
作    者   : 
修改内容   : 新生成函数
说明:因为对于双向链表的插入来说,操作都是头,以及头的前一个或者后一个,以及
新节点插入的关系;实际上只要将这三个节点之间的关系调整好即可,
所以抽象出来一个总的list add出来;
*****************************************************************************/
static inline void ListAdd(TListHead *ptNew,
                       TListHead *ptPrev,
                       TListHead *ptNext)
{
    ptNext->prev = ptNew;
    ptNew->next = ptNext;
    ptNew->prev = ptPrev;
    ptPrev->next = ptNew;
}
/*****************************************************************************
函 数 名  : list_add
功能描述  : 从链表头开始添加
输入参数  : TListHead *new
TListHead *head
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 无

修改历史      :
1.日    期   : 
作    者   : 
修改内容   : 新生成函数

*****************************************************************************/
 static inline void ListAddHead(TListHead *ptNew, TListHead *ptHead)
{
    ListAdd(ptNew, ptHead, ptHead->next);
}
/*****************************************************************************
函 数 名  : list_add_tail
功能描述  : 从链表尾开始添加
输入参数  : TListHead *new
TListHead *head
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 无

修改历史      :
1.日    期   : 
作    者   :
修改内容   : 新生成函数

*****************************************************************************/
static inline void ListAddTail(TListHead *ptNew, TListHead *ptHead)
{
    ListAdd(ptNew, ptHead->prev, ptHead);
}


/*****************************************************************************
函 数 名  : list_empty
功能描述  : 判断当前链表是否为空
输入参数  : const TListHead *head
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 无

修改历史      :
1.日    期   :
作    者   : 
修改内容   : 新生成函数

*****************************************************************************/
static inline unsigned int ListEmpty(const TListHead *ptHead)
{
    return ptHead->next == ptHead;
}
/*****************************************************************************
 函 数 名  : list_is_last
 功能描述  : 判断是否节点是最后一个节点
 输入参数  : const TListHead *ptList
             const TListHead *ptHead
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
static inline unsigned int ListIsLast(const TListHead *ptList,const TListHead *ptHead)
{
    return ptList->next == ptHead;
}

/*****************************************************************************
函 数 名  : __list_del
功能描述  : 删除链表
输入参数  : TListHead * prev
TListHead * next
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 无

修改历史      :
1.日    期   : 
作    者   : 
修改内容   : 新生成函数

*****************************************************************************/
static inline void _ListDel(TListHead * ptPrev, TListHead * ptNext)
{
    ptNext->prev = ptPrev;
    ptPrev->next = ptNext;
}
/*****************************************************************************
函 数 名  : list_del
功能描述  : 删除化链表并清零
输入参数  : TListHead *entry
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 无

修改历史      :
1.日    期   : 
作    者   : 
修改内容   : 新生成函数

*****************************************************************************/
static inline void ListDel(TListHead *ptEntry)

{
    _ListDel(ptEntry->prev, ptEntry->next);
    ptEntry->next = (TListHead*)0;
    ptEntry->prev = (TListHead*)0;
}
/*****************************************************************************
 函 数 名  : list_move_tail
 功能描述  : 讲一个节点从当前移动到链表尾巴
 输入参数  : TListHead *ptList
             TListHead *ptHead
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
static inline void ListMoveTail(TListHead *ptList, TListHead *ptHead)
 {
     _ListDel(ptList->prev, ptList->next);
     ListAddTail(ptList, ptHead);
 }

static inline void __ListSplice(const TListHead *list,
				 TListHead *prev,
				 TListHead *next)
{
	TListHead *first = list->next;
	TListHead *last = list->prev;

	first->prev = prev;
	prev->next = first;

	last->next = next;
	next->prev = last;
}
/*****************************************************************************
 函 数 名  : ListSpliceTail
 功能描述  : 将一个链表挂到head链表的头
 输入参数  : TListHead *list
             				TListHead *head
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 
    作    者   : 
    修改内容   : 新生成函数
    说明:head是原链表，list是新链表，将list挂接到head    的头

注意:如果用户的头结点是动态申请的，需要用户挂完链表后
手工释放链表头
*****************************************************************************/

static inline void ListSplice(const TListHead *list,
				TListHead *head)
{
	if (!ListEmpty(list))
		__ListSplice(list, head, head->next);
}
/*****************************************************************************
 函 数 名  : ListSpliceTail
 功能描述  : 将一个链表挂到head链表的尾巴
 输入参数  : TListHead *list
             				TListHead *head
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 
    作    者   : 
    修改内容   : 新生成函数
    说明:head是原链表，list是新链表，将list挂接到head
    注意:如果用户的头结点是动态申请的，需要用户挂完链表后
    手工释放链表头
*****************************************************************************/
static inline void ListSpliceTail(TListHead *list,
				TListHead *head)
{
	if (!ListEmpty(list))
		__ListSplice(list, head->prev, head);
}


#endif
