#include "StdAfx.h"
#include "Log.h"
#include "UCIMRecvEvent.h"
#include "UCIMMgr.h"

UCIMRecvEvent::UCIMRecvEvent(void)
{
}

UCIMRecvEvent::~UCIMRecvEvent(void)
{
}
bool UCIMRecvEvent::DoHandle(void)
{
	DEBUG_TRACE("");

	if(m_EventID != IM_E_EVENT_IM_CODECHAT_NOTIFY)
	{
		ERROR_LOG("----m_EventID is invalid");
		return false;
	}

	if(NULL == m_pBody)
	{
		ERROR_LOG("----m_pBody is null");
		return false;
	}

	IM_S_CODECHAT_NOTIFY* pInfo = (IM_S_CODECHAT_NOTIFY*)m_pBody;

	UCIMMgr::Instance().NotifyIMUI(pInfo->chatInfo.origin,pInfo->chatInfo.content);

	return true;
}
void UCIMRecvEvent::SetPara(IM_E_EVENT_ID eventID, void *body)
{
	m_EventID = eventID;
	m_pBody = body;
}