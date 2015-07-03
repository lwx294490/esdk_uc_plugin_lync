#include "StdAfx.h"
#include "UCCallReservedEvent.h"
#include "Log.h"

UCCallReservedEvent::UCCallReservedEvent(void)
{
}

UCCallReservedEvent::~UCCallReservedEvent(void)
{
}
bool UCCallReservedEvent::DoHandle(void)
{
	DEBUG_TRACE("");

	INFO_LOG("----UCCallReservedEvent:param1=%d,param2=%d,m_pBody=0x%x",m_param1,m_param2,m_pBody);

	return true;
}
void UCCallReservedEvent::SetPara(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	m_msgid = msgid;
	m_param1 = param1;
	m_param2 = param2;
	m_pBody = pBody;
}

