#pragma once
#include "ucevent.h"
#include "UserQueryHelper.h"

class UCConfEvent :
	public UCEvent , public CUserQueryHelper
{
public:
	UCConfEvent(void);
	virtual ~UCConfEvent(void);
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
