#ifndef _TUP_IM_BASE_H_
#define _TUP_IM_BASE_H_

#include "tup_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

/** \brief 链表信息 */
typedef struct tagTUP_S_LIST{
  TUP_VOID *data; 
  struct tagTUP_S_LIST *next;
}TUP_S_LIST;


/**
 * \brief 向链表中添加一个节点，如果链表为空，会创建链表后再添加。
 * \param[in]  list 链表
 * \param[in] data 数据
 * \return 添加节点后的新链表
 */
TUP_API TUP_S_LIST *tup_list_append(TUP_S_LIST * list,
                                                 const TUP_VOID * data);

/**
 * \brief 释放链表内存
 * \param[in]  list 待释放的链表内存
 * \return void
 */
TUP_API void tup_list_free_all(TUP_S_LIST * list);



#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif //_TUP_IM_BASE_H_