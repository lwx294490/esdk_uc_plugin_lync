#pragma once
#include "ucevent.h"

class UCFileTransEvent: public UCEvent
{
public:
	UCFileTransEvent(void);
	~UCFileTransEvent(void);
public:
	virtual bool DoHandle(void);
public:
	void SetPara(IM_E_EVENT_ID eventID, void *body);
private:
	IM_E_EVENT_ID m_EventID;
	void *m_pBody;
};
