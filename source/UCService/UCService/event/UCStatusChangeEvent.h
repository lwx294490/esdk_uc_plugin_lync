#pragma once
#include "ucevent.h"

class UCStatusChangeEvent :
	public UCEvent
{
public:
	UCStatusChangeEvent(void);
	virtual ~UCStatusChangeEvent(void);
public:
	virtual bool DoHandle(void);
public:
	void SetPara(IM_E_EVENT_ID eventID, void *body);
private:
	IM_E_EVENT_ID m_EventID;
	void *m_pBody;
};
