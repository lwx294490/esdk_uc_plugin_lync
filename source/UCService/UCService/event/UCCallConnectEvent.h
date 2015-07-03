#pragma once
#include "UCEvent.h"

class UCCallConnectEvent :	public UCEvent
{
public:
	UCCallConnectEvent(void);
	virtual ~UCCallConnectEvent(void);
public:
	virtual bool DoHandle(void);
public:
	void SetPara(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody);
private:
	TUP_UINT32 m_msgid;
	TUP_UINT32 m_param1;
	TUP_UINT32 m_param2;
	TUP_VOID*  m_pBody;
};
