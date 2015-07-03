#ifndef _TUP_IM_BASE_H_
#define _TUP_IM_BASE_H_

#include "tup_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

/** \brief ������Ϣ */
typedef struct tagTUP_S_LIST{
  TUP_VOID *data; 
  struct tagTUP_S_LIST *next;
}TUP_S_LIST;


/**
 * \brief �����������һ���ڵ㣬�������Ϊ�գ��ᴴ�����������ӡ�
 * \param[in]  list ����
 * \param[in] data ����
 * \return ��ӽڵ���������
 */
TUP_API TUP_S_LIST *tup_list_append(TUP_S_LIST * list,
                                                 const TUP_VOID * data);

/**
 * \brief �ͷ������ڴ�
 * \param[in]  list ���ͷŵ������ڴ�
 * \return void
 */
TUP_API void tup_list_free_all(TUP_S_LIST * list);



#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif //_TUP_IM_BASE_H_