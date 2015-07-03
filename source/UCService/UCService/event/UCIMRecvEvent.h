#pragma once
#include "ucevent.h"

class UCIMRecvEvent :
	public UCEvent
{
public:
	UCIMRecvEvent(void);
	virtual ~UCIMRecvEvent(void);
public:
	virtual bool DoHandle(void);
public:
	void SetPara(IM_E_EVENT_ID eventID, void *body);
private:
	IM_E_EVENT_ID m_EventID;
	void *m_pBody;
};
