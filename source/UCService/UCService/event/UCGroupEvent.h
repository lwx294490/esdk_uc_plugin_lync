#pragma once
#include "ucevent.h"

enum GroupEventType
{
	EmptyEvent,
	E_GroupMemRefresh,	//刷新所有成员
	E_GroupMemAdd,		//成员增加
	E_GroupMemDel,		//成员减少
	E_GroupMemNotify	//强制成员上报，用于在接听会议时，成员在之前已经上报了
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
