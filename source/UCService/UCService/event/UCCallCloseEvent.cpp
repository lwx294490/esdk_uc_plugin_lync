#include "StdAfx.h"
#include "Log.h"
#include "UCCallCloseEvent.h"
#include "UCCallMgr.h"
#include "UCPlayMgr.h"
#include "UCGroupMgr.h"
#include "UCConfMgr.h"

UCCallCloseEvent::UCCallCloseEvent(void):m_msgid(0)
	,m_param1(0)
	,m_param2(0)
	,m_pBody(NULL)
{
}

UCCallCloseEvent::~UCCallCloseEvent(void)
{
}
bool UCCallCloseEvent::DoHandle(void)
{
	DEBUG_TRACE("");
	INFO_LOG("----UCCallCloseEvent:param1=%d,param2=%d",m_param1,m_param2);

	UCCallMgr::Instance().SetCallStatus(NOCALL);

	if(NULL == UCCallMgr::OnAVSessionClosedCB)
	{
		ERROR_LOG("----OnAVSessionClosedCB is NULL.");
		return false;
	}

	CALL_S_CALL_INFO* pNotify = (CALL_S_CALL_INFO*)m_pBody;

	STMsgAVSessionClosedParam stPara={0};
	strcpy_s(stPara.callerUri_,STRING_LENGTH,pNotify->stCallStateInfo.acTelNum);
	strcpy_s(stPara.AVSessionId_,STRING_LENGTH,"");
	_itoa_s(pNotify->stCallStateInfo.ulReasonCode,stPara.reason_,10);

	//Ω· ¯≤•∑≈¡Â“Ù
	(void)UCPlayMgr::Instance().EndPlayIncoming();
	(void)UCPlayMgr::Instance().EndPlayRingBack();

	if(UCCallMgr::Instance().GetCallID() == m_param1)
	{
		INFO_LOG("----Enter OnAVSessionClosedCB");
		UCCallMgr::OnAVSessionClosedCB(stPara);
		INFO_LOG("----Leave OnAVSessionClosedCB");
		UCCallMgr::Instance().ClearCallMember();
		UCCallMgr::Instance().ClearConvMember();
		UCConfMgr::Instance().ClearConfMember();
		UCGroupMgr::Instance().ClearGroupMember();
	}
	else
	{
		INFO_LOG("----call to conv,do not notify UI");
	}
	

	SAFE_DELETE(pNotify);

	return true;
}

void UCCallCloseEvent::SetPara(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	m_msgid = msgid;
	m_param1 = param1;
	m_param2 = param2;
	m_pBody = pBody;
}
