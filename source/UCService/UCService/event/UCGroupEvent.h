#pragma once
#include "ucevent.h"

enum GroupEventType
{
	EmptyEvent,
	E_GroupMemRefresh,	//ˢ�����г�Ա
	E_GroupMemAdd,		//��Ա����
	E_GroupMemDel,		//��Ա����
	E_GroupMemNotify	//ǿ�Ƴ�Ա�ϱ��������ڽ�������ʱ����Ա��֮ǰ�Ѿ��ϱ���
};

class UCGroupEvent : public UCEvent
{
public:
	UCGroupEvent(void);
	virtual ~UCGroupEvent(void);
public:
	virtual bool DoHandle(void);
	void SetGroupID(const std::string groupid) {m_strGroupID = groupid;}
	void SetEventID(int id) {m_iGroupEventID = id;}
	void SetPara(TUP_VOID *pBody) {m_pBody = pBody;}
private:
	std::string m_strGroupID;
	int m_iGroupEventID;
	TUP_VOID* m_pBody;
};
