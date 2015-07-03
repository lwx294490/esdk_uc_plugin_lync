#pragma once
#include "ucevent.h"


class UCCallVideoEvent : public UCEvent
{
public:
	UCCallVideoEvent(void);
	virtual ~UCCallVideoEvent(void);
public:
	virtual bool DoHandle(void);
public:
	void SetCallid(TUP_UINT32 callid);
	void SetVideoStatus(int iStatus);
private:
	TUP_UINT32 m_CallID;
	int m_iVideoStatus;
};
