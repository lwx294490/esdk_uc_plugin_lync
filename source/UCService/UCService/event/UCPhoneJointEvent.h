#pragma once
#include "ucevent.h"

class UCPhoneJointEvent :
	public UCEvent
{
public:
	UCPhoneJointEvent(void);
	virtual ~UCPhoneJointEvent(void);
public:
	virtual bool DoHandle(void);
public:
	void SetPara(TUP_UINT32 eventID, void *body);
private:
	TUP_UINT32 m_EventID;
	void *m_pBody;
};
