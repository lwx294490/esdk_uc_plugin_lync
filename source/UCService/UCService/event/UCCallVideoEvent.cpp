#include "StdAfx.h"
#include "Log.h"
#include "UCCallVideoEvent.h"
#include "UCCallIncomingEvent.h"
#include "UCCallMgr.h"

UCCallVideoEvent::UCCallVideoEvent(void):m_CallID(0)
	,m_iVideoStatus(CALL_VIDEO_CLOSE)
{
}

UCCallVideoEvent::~UCCallVideoEvent(void)
{
}
bool UCCallVideoEvent::DoHandle(void)
{	
	STVideoCallParam st={0};
	memset(st.ucAcc,0,STRING_LENGTH);

	std::string account = UCCallMgr::Instance().GetCalleeAccountByCallID(m_CallID);
	strcpy_s(st.ucAcc,STRING_LENGTH,account.c_str());

	st.callStatus = m_iVideoStatus;

	INFO_LOG("----UCCallVideoEvent:account=%s,VideoStatus=%d",account.c_str(),m_iVideoStatus);

	if(m_iVideoStatus == CALL_VIDEO_CONNECTED)
	{
		UCCallMgr::Instance().SetCallStatus(VIDEOCALL);
	}
	else
	{
		UCCallMgr::Instance().SetCallStatus(AUDIOCALL);
	}
	

	if (NULL == UCCallMgr::OnVideoCallEventCB)
	{
		ERROR_LOG("----OnVideoCallEventCB is null");
		return false;
	}

	INFO_LOG("----Enter OnVideoCallEventCB");
	UCCallMgr::OnVideoCallEventCB(st);
	INFO_LOG("----Leave OnVideoCallEventCB");

	return true;
}
void UCCallVideoEvent::SetCallid(TUP_UINT32 callid)
{
	m_CallID = callid;
}

void UCCallVideoEvent::SetVideoStatus(int iStatus)
{
	m_iVideoStatus = iStatus;
}
