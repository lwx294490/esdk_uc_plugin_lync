#ifndef VOS_COMMON_H
#define SS_VOS_COMMON_H

#include <stdlib.h>

template<class T>
T* VOS_NEW(T* &m, unsigned long ulMuili = 0)
{
    try
    {
        if (ulMuili == 0)
        {
            m = new(T);
        }
        else
        {
            m = new(T[ulMuili]);
        }
        return m;
    }
    catch(...)
    {
        m = NULL;
        return NULL;
    }
};

enum DELETE_MULTI
{
    SINGLE = 0,
    MULTI = 1
};

template<class T>
void VOS_DELETE(T* &m, unsigned long ulMuili = 0)
{
    if(NULL == m)
    {
        return;
    }

    try
    {
        if (0 == ulMuili)
        {
            delete m;
        }
        else
        {
            delete[] m;
        }
    }
    catch(...)
    {
    }

    m = NULL;
};

//��ȫ��̬���䵥ʵ���ڴ棬���ɵ������࣬�����ص��Ǹ���ָ��
//���ͽ����ڼ̳���
template<class TBASE, class TREAL>
TBASE* VOS_NEW_REAL(TBASE* &m)
{
    try
    {
        m = new(TREAL);
    }
    catch(...)
    {
        m = NULL;
    }

    return m;
};

//��ȫ�ͷŵ�ʵ���ڴ棬�����ǻ������ָ�룬��ʵ��ɾ�������������
//���ͽ����ڼ̳���
//������������������麯�������ֱ��ʹ��VOS_DELETE
template<class TBASE, class TREAL>
void VOS_DELETE_REAL(TBASE* &m)
{
    try
    {
        TREAL* p = (TREAL*)m; /*lint !e1774*///ģ��,��ȫת��
        delete p;
    }
    catch(...)
    {
        m = NULL;
    }

    m = NULL;
};

//����ָ�밲ȫת��Ϊ��ʵָ��

template<class T>
T* VOS_CAST(T* pVoid)
{
    T* pReal = NULL;

    try
    {
        pReal = dynamic_cast<T*>(pVoid);
    }
    catch(...)
    {
        pReal = NULL;
    }

    return pReal;
};
#endif //VOS_COMMON_H_INCLUDE

