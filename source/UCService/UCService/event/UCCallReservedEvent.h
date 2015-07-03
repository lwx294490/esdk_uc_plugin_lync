#pragma once
#include "ucevent.h"

class UCCallReservedEvent :
	public UCEvent
{
public:
	UCCallReservedEvent(void);
	virtual ~UCCallReservedEvent(void);
public:
	virtual bool DoHandle(void);
public:
	void SetPara(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody);
private:
	TUP_UINT32 m_msgid;
	TUP_UINT32 m_param1;
	TUP_UINT32 m_param2;
	TUP_VOID* m_pBody;
};
