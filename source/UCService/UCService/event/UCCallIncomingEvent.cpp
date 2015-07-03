#include "StdAfx.h"
#include "Log.h"
#include "UCCallIncomingEvent.h"
#include "UCCallMgr.h"
#include "UCConfMgr.h"
#include "UCPlayMgr.h"

UCCallIncomingEvent::UCCallIncomingEvent(void):m_msgid(0)
	,m_param1(0)
	,m_param2(0)
	,m_pBody(NULL)
{
}

UCCallIncomingEvent::~UCCallIncomingEvent(void)
{
}
bool UCCallIncomingEvent::DoHandle(void)
{
	DEBUG_TRACE("");

	std::string strBindNo("");
	STAudioVideoParam item;
	switch(m_msgid)
	{
	case CALL_E_EVT_CALL_INCOMMING:
		{
			//点对点呼叫来电
			item.isConference = 0;
			CALL_S_CALL_INFO* pInfo = (CALL_S_CALL_INFO*)m_pBody;
			if(NULL == pInfo)
			{
				ERROR_LOG("----pInfo is NULL");
				return false;
			}
			strBindNo = pInfo->stCallStateInfo.acTelNum;
			if(pInfo->stCallStateInfo.enCallType == CALL_E_CALL_TYPE_IPVIDEO)
			{
				item.isvideo_ = 1;
			}
			else
			{
				item.isvideo_ = 0;
			}
			UCCallMgr::Instance().SetCallID(m_param1);
			UCConfMgr::Instance().SetConfID(0);
			UCConfMgr::Instance().SetGroupID("");
			SAFE_DELETE(pInfo);
			break;
		}
	case CALL_E_EVT_SERVERCONF_INCOMING:
		{
			//会议呼叫来电
			item.isConference = 1;
			CALL_S_CONF_INFO* pInfo = (CALL_S_CONF_INFO*)m_pBody;
			if(NULL == pInfo)
			{
				ERROR_LOG("----pInfo is NULL");
				return false;
			}			
			strBindNo = pInfo->acUserNumber;
			item.isvideo_ = 0;
			UCCallMgr::Instance().SetCallID(pInfo->ulCallID);
			UCCallMgr::Instance().SetConfStart(true);
			UCConfMgr::Instance().SetConfID(pInfo->ulConfID);
			UCConfMgr::Instance().SetGroupID(pInfo->acGroupUri);
			SAFE_DELETE(pInfo);
			break;
		}
	default:
		break;
	}

	if(strBindNo.empty())
	{
		ERROR_LOG("----strBindNo is empty");
		return false;
	}
	
	IM_S_USERINFO targetUserInfo;
	if(GetTargetUserInfo(strBindNo.c_str(),targetUserInfo))
	{
		item.AccountType = UC_ACCOUNT;
		item.callMode = UC_ACCOUNT;
		strcpy_s(item.ucAcc,STRING_LENGTH,targetUserInfo.account);
		UCCallMgr::Instance().InsertUCMember(targetUserInfo.account,strBindNo);
	}
	else
	{
		item.AccountType = UC_IPPHONE;
		item.callMode = UC_IPPHONE;
		strcpy_s(item.ucAcc,STRING_LENGTH,strBindNo.c_str());
		UCCallMgr::Instance().InsertPhoneMember(strBindNo);
	}

	if (NULL == UCCallMgr::OnAVSessAddedCB)
	{
		ERROR_LOG("----OnAVSessAddedCB is null");
		return false;
	}
	(void)UCPlayMgr::Instance().StartPlayIncomingCall();

	INFO_LOG("----Enter OnAVSessAddedCB ");
	INFO_LOG("----OnAVSessAddedCB:ucAcc=%s,callMode=%d,isvideo_=%d,AccountType=%d，IsConference=%d",item.ucAcc,item.callMode,item.isvideo_,item.AccountType,item.isConference);
	UCCallMgr::OnAVSessAddedCB(item);
	INFO_LOG("----Leave OnAVSessAddedCB");

	return true;
}
void UCCallIncomingEvent::SetPara(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	m_msgid = msgid;
	m_param1 = param1;
	m_param2 = param2;
	m_pBody = pBody;
}
