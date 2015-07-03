#include "StdAfx.h"
#include "Log.h"
#include "UCCallConnectEvent.h"
#include "UCCallMgr.h"
#include "UCPlayMgr.h"
#include "UCCallVideoEvent.h"
#include "UCEventMgr.h"

UCCallConnectEvent::UCCallConnectEvent(void)
{
}

UCCallConnectEvent::~UCCallConnectEvent(void)
{
}

bool UCCallConnectEvent::DoHandle(void)
{
	DEBUG_TRACE("");

	INFO_LOG("----UCCallConnectEvent:param1=%d,param2=%d,m_pBody=0x%x",m_param1,m_param2,m_pBody);
	if(NULL == m_pBody)
	{
		ERROR_LOG("----m_pBody is NULL");
		return false;
	}

	CALL_S_CALL_INFO* pInfo = (CALL_S_CALL_INFO*)m_pBody;

	if(pInfo->stCallStateInfo.enCallType == CALL_E_CALL_TYPE_IPAUDIO)
	{
		if (VIDEOCALL == UCCallMgr::Instance().GetCallStatus())  /////发起的是视频，对方语音接听//////
		{
			INFO_LOG("Change VideoCall to AudioCall!");
			TUP_UINT32 callid = pInfo->stCallStateInfo.ulCallID;
			UCCallVideoEvent* pEvent = new UCCallVideoEvent;
			pEvent->SetCallid(callid);
			pEvent->SetVideoStatus(CALL_VIDEO_CLOSE);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}
		UCCallMgr::Instance().SetCallStatus(AUDIOCALL);
	}
	else if(pInfo->stCallStateInfo.enCallType == CALL_E_CALL_TYPE_IPVIDEO)
	{
		UCCallMgr::Instance().SetCallStatus(VIDEOCALL);
	}
	

	if(NULL == UCCallMgr::OnAVSessionConnectedCB)
	{
		ERROR_LOG("----OnAVSessionConnectedCB is NULL.");
		return false;
	}

	//结束播放铃音
	(void)UCPlayMgr::Instance().EndPlayIncoming();
	(void)UCPlayMgr::Instance().EndPlayRingBack();

	INFO_LOG("----Enter OnAVSessionConnectedCB");
	UCCallMgr::OnAVSessionConnectedCB();
	INFO_LOG("----Leave OnAVSessionConnectedCB");

	SAFE_DELETE(pInfo);

	return true;

}

void UCCallConnectEvent::SetPara(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	m_msgid = msgid;
	m_param1 = param1;
	m_param2 = param2;
	m_pBody = pBody;
}
