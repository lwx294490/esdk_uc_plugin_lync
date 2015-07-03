#include "StdAfx.h"
#include "Log.h"
#include "UCCallMgr.h"
#include "UCRegMgr.h"
#include "UCContactMgr.h"
#include "UCCallVideoEvent.h"
#include "UCEventMgr.h"
#include "UCConfMgr.h"
#include "UCPlayMgr.h"
#include "UCGroupMgr.h"

#define CHECK_CALLID_RETURN(interger,ret) if(0 == interger)\
{\
    ERROR_LOG("callid is 0");\
	return ret;\
}

//lint -e1788
AVSessionClosedCB UCCallMgr::OnAVSessionClosedCB=NULL;
AVSessionConnectedCB UCCallMgr::OnAVSessionConnectedCB=NULL;
AVSessAddedCB UCCallMgr::OnAVSessAddedCB=NULL;
VideoCallEventCB UCCallMgr::OnVideoCallEventCB=NULL;
CallReservedEventCB UCCallMgr::OnCallReservedEventCB=NULL;
CallTransEventCB UCCallMgr::OnCallTransEventCB= NULL;



UCCallMgr::UCCallMgr(void)
{
	try
	{
		m_uiCallID = 0;
		m_MemBindNOList.clear();
		m_MemPhoneList.clear();
		m_ConvMemberMap.clear();
		isConfStart = false;
		m_iCallStatus = NOCALL;
	}
	catch(...)
	{
	}

}

UCCallMgr::~UCCallMgr(void)
{
	try
	{
		m_uiCallID = 0;
		m_MemBindNOList.clear();
		m_MemPhoneList.clear();
		m_ConvMemberMap.clear();
		isConfStart = false;
		m_iCallStatus = NOCALL;
	}
	catch(...)
	{
	}
}

void UCCallMgr::Init(void)
{	
	DEBUG_TRACE("");
	std::string strPath;
	eSDKTool::getCurrentPath(strPath);
	strPath.append("\\log");

	tup_call_log_start(CALL_E_LOG_DEBUG,10000,10, strPath.c_str());
	TUP_RESULT tRet = tup_call_init();
	if(TUP_SUCCESS != tRet)
	{		
		return;
	}


	m_uiCallID = 0;
	m_MemBindNOList.clear();
	m_MemPhoneList.clear();
	m_ConvMemberMap.clear();

	OnAVSessionClosedCB = NULL;
	OnAVSessionConnectedCB = NULL;
	OnAVSessAddedCB = NULL;

}
void UCCallMgr::Uninit(void)
{
	DEBUG_TRACE("");

	OnAVSessionClosedCB = NULL;
	OnAVSessionConnectedCB = NULL;
	OnAVSessAddedCB = NULL;
	m_MemBindNOList.clear();
	m_MemPhoneList.clear();
	m_ConvMemberMap.clear();

	tup_call_log_stop();

}

int UCCallMgr::InsertUCMember(const std::string& _ucAccount,const std::string& _ucBindNo)
{
	m_MemBindNOList[_ucAccount] = _ucBindNo;

	//
	UCRegMgr::Instance().SubscribeStatus(_ucAccount);

	return UC_SDK_Success;
}
int UCCallMgr::InsertPhoneMember(const std::string& _phone)
{
	m_MemPhoneList.insert(_phone);
	return UC_SDK_Success;
}
int UCCallMgr::MakeCall(void)
{
	if(m_uiCallID > 0)
	{
		ERROR_LOG("you have in call now.");
		return UC_SDK_Failed;
	}
	size_t nMemberCount = m_MemBindNOList.size();
	size_t nPhoneNum = m_MemPhoneList.size();
	size_t nNum = nMemberCount + nPhoneNum;
	if (0 == nNum)
	{
		ERROR_LOG("memberList is empty");
		return UC_SDK_NotHaveCallTarget;
	}

	if (1 == nMemberCount && 0 == nPhoneNum)//呼叫单个账户
	{
		CALL_E_CALL_TYPE tupCallType = CALL_E_CALL_TYPE_IPAUDIO;
		UCMemList::iterator it = m_MemBindNOList.begin();
		TUP_RESULT tRet = tup_call_start_call(&m_uiCallID,tupCallType,(*it).second.c_str());
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_start_cal:add uc account failed");
			return UC_SDK_Failed;
		}
		SetCallStatus(AUDIOCALL);
		return UC_SDK_Success;
	}
	if (0 == nMemberCount && 1 == nPhoneNum)//呼叫单个电话
	{
		CALL_E_CALL_TYPE tupCallType = CALL_E_CALL_TYPE_IPAUDIO;
		PhoneMemList::iterator it = m_MemPhoneList.begin();
		TUP_RESULT tRet = tup_call_start_call(&m_uiCallID,tupCallType,(*it).c_str());
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_start_call: add  phone failed");
			return UC_SDK_Failed;
		}
		SetCallStatus(AUDIOCALL);
		return UC_SDK_Success;
	}

	std::string groupID;
	if(UC_SDK_Success != UCGroupMgr::Instance().CreatGroup(groupID))
	{
		ERROR_LOG("Creat Discuss Group Failed.");
		return UC_SDK_Failed;
	}

	UCConfMgr::Instance().SetGroupID(groupID);

	int iRet = UCConfMgr::Instance().CreateConf(groupID,m_MemPhoneList,m_MemBindNOList,m_uiCallID);
	if(iRet == UC_SDK_Success)
	{
		SetCallStatus(AUDIOCALL);
		isConfStart = true;
	}

	return iRet;
	
}

int UCCallMgr::TransCallToConf(EM_MemberType _memberType,const std::string& strAccountOrPhone)
{
	DEBUG_TRACE("");

	INFO_LOG("_memberType=%d,pAccountOrPhone=%s",_memberType,strAccountOrPhone.c_str());

	if(m_MemBindNOList.size() == 1)
	{
		UCMemList::iterator it = m_MemBindNOList.begin();
		UCConfMgr::Instance().SetCallerInfo((*it).second,(*it).first,true);	
	}
	else if(m_MemPhoneList.size() == 1)
	{
		PhoneMemList::iterator it = m_MemPhoneList.begin();
		UCConfMgr::Instance().SetCallerInfo((*it),"",false);
	}
	else
	{
		ERROR_LOG("cannot find callee");
		return UC_SDK_Failed;
	}
	if(_memberType == UC_ACCOUNT)
	{
		IM_S_USERINFO user;
		if(UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(strAccountOrPhone,user))
		{
			ERROR_LOG("getContactByAccount Error!");
			return UC_SDK_FindUriErr;
		}
		m_MemBindNOList[strAccountOrPhone] = user.bindNO;		
		(void)UCRegMgr::Instance().SubscribeStatus(strAccountOrPhone);		
	}
	else
	{
		m_MemPhoneList.insert(strAccountOrPhone);

	}
	std::string groupID;
	(void)UCGroupMgr::Instance().CreatGroup(groupID);
	UCConfMgr::Instance().SetGroupID(groupID);

	int iRet = UCConfMgr::Instance().TransCallToConf(groupID,m_MemPhoneList,m_MemBindNOList,m_uiCallID);
	if(iRet == UC_SDK_Success)
	{
		isConfStart = true;
	}
	return UC_SDK_Success;
}

int UCCallMgr::TransCallToConf(std::vector<std::string>& vecUCMember,std::vector<std::string>& vecPhoneMember)
{
	DEBUG_TRACE("");
	if(m_MemBindNOList.size() == 1)
	{
		UCMemList::iterator it = m_MemBindNOList.begin();
		UCConfMgr::Instance().SetCallerInfo((*it).second,(*it).first,true);	
	}
	else if(m_MemPhoneList.size() == 1)
	{
		PhoneMemList::iterator it = m_MemPhoneList.begin();
		UCConfMgr::Instance().SetCallerInfo((*it),"",false);
	}
	else
	{
		ERROR_LOG("cannot find callee");
		return UC_SDK_Failed;
	}

	std::vector<std::string>::iterator it = vecUCMember.begin();
	std::vector<std::string>::iterator itEnd = vecUCMember.end();
	for(;it!=itEnd;it++)
	{
		std::string account = *it;
		IM_S_USERINFO user;
		if(UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(account,user))
		{
			ERROR_LOG("getContactByAccount Error!");
			return UC_SDK_FindUriErr;
		}
		m_MemBindNOList[account] = user.bindNO;
		(void)UCRegMgr::Instance().SubscribeStatus(account);		
	}
	it = vecPhoneMember.begin();
	itEnd = vecPhoneMember.end();
	for(;it!=itEnd;it++)
	{
		std::string phone = *it;
		m_MemPhoneList.insert(phone);
	}

	std::string groupID;
	(void)UCGroupMgr::Instance().CreatGroup(groupID);
	UCConfMgr::Instance().SetGroupID(groupID);

	int iRet = UCConfMgr::Instance().TransCallToConf(groupID,m_MemPhoneList,m_MemBindNOList,m_uiCallID);
	if(iRet == UC_SDK_Success)
	{
		isConfStart = true;
	}
	return iRet;
}


int UCCallMgr::HoldCall(void)
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);

	if(tup_call_hold_call(m_uiCallID) != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_hold_call Failed.");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}

int UCCallMgr::ResumeCall(void)
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);
	if(tup_call_unhold_call(m_uiCallID) != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_unhold_call Failed.");
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;	
}


int UCCallMgr::MakeVideoCall(const STVideoWindow& stLocalWnd, const STVideoWindow& stRemoteWnd)
{

	size_t nMemberCount = m_MemBindNOList.size();
	size_t nPhoneNum = m_MemPhoneList.size();
	size_t nNum = nMemberCount + nPhoneNum;
	if (1 != nNum)
	{
		ERROR_LOG("membersize is invalid.");
		return UC_SDK_Failed;
	}

	std::string bindno;
	if (1 == nMemberCount && 0 == nPhoneNum)//呼叫单个账户
	{
		UCMemList::iterator it = m_MemBindNOList.begin();
		bindno = (*it).second;
	}
	if (0 == nMemberCount && 1 == nPhoneNum)//呼叫单个电话
	{
		PhoneMemList::iterator it = m_MemPhoneList.begin();
		bindno = (*it);
	}

	CALL_S_VIDEOWND_INFO videoWndInfo[2];
	memset(videoWndInfo, 0, sizeof(CALL_S_VIDEOWND_INFO)*2);
	videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulRender = (TUP_UINT32)stLocalWnd.hWnd;
	videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulVideoWndType = CALL_E_VIDEOWND_CALLLOCAL;
	videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulIndex = 1;
	videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulDisplayType = CALL_E_VIDEOWND_DISPLAY_FULL;

	videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulRender = (TUP_UINT32)stRemoteWnd.hWnd;
	videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulVideoWndType = CALL_E_VIDEOWND_CALLREMOTE;
	videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulIndex = 0;
	videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulDisplayType = CALL_E_VIDEOWND_DISPLAY_FULL;


	if(0 == m_uiCallID)//没有音频呼叫
	{
		TUP_RESULT tRet = tup_call_create_video_window(2, (CALL_S_VIDEOWND_INFO *)videoWndInfo);
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_create_video_window failed.");
			return UC_SDK_Failed;
		}

		tRet = tup_call_start_call(&m_uiCallID,CALL_E_CALL_TYPE_IPVIDEO,bindno.c_str());
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_start_call failed.");
			return UC_SDK_Failed;
		}
	}
	else
	{
		TUP_RESULT tRet = tup_call_update_video_window(2, (CALL_S_VIDEOWND_INFO *)videoWndInfo,m_uiCallID);
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_create_video_window failed.");
			return UC_SDK_Failed;
		}

		tRet = tup_call_add_video(m_uiCallID);
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_add_video failed.");
			return UC_SDK_Failed;
		}
	}
	SetCallStatus(VIDEOCALL);

	return UC_SDK_Success;
}
int UCCallMgr::ClearConvMember()
{
	INFO_LOG("ClearConvMember");
	m_ConvMemberMap.clear();
	isConfStart = false;
	return UC_SDK_Success;
}
int UCCallMgr::ClearCallMember()
{
	INFO_LOG("ClearCallMember");
	m_MemPhoneList.clear();
	m_MemBindNOList.clear();
	m_uiCallID = 0;
	return UC_SDK_Success;
}

bool UCCallMgr::GetConvStarted()const
{
	return isConfStart;
}


int UCCallMgr::HangupCall(void)
{
	DEBUG_TRACE("");

	//停止响铃
	(void)UCPlayMgr::Instance().EndPlayIncoming();
	(void)UCPlayMgr::Instance().EndPlayRingBack();

	//是会议，则先结束会议
	if(isConfStart)
	{	
		(void)UCConfMgr::Instance().LeaveConf();
		UCConfMgr::Instance().ClearConfMember();
	}
	else
	{
		INFO_LOG("HangupCall:CallID=%d",m_uiCallID);
		if(0 != m_uiCallID)
		{
			TUP_RESULT tRet = tup_call_end_call(m_uiCallID);
			if(tRet != TUP_SUCCESS)
			{
				ERROR_LOG("tup_call_end_call failed.");
				return UC_SDK_Failed;
			}
		}

	}

	UCGroupMgr::Instance().ClearGroupMember();

	//清除成员
	ClearConvMember();
	ClearCallMember();	

	return UC_SDK_Success;
}

int UCCallMgr::HangupVideoCall(void)
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);

	TUP_RESULT tRet =tup_call_del_video(m_uiCallID);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_del_video failed.");
		return UC_SDK_Failed;
	}
	
	return UC_SDK_Success;
}
int UCCallMgr::AcceptCall(void)
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);
	//停止响铃
	(void)UCPlayMgr::Instance().EndPlayIncoming();
	(void)UCPlayMgr::Instance().EndPlayRingBack();
	TUP_RESULT tRet = tup_call_accept_call(m_uiCallID,TUP_FALSE);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_accept_call failed.");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}
int UCCallMgr::AcceptVideoCall(const STVideoWindow& stLocalWnd,const STVideoWindow& stRemoteWnd)
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);

	CALL_S_VIDEOWND_INFO videoWndInfo[2];
	memset(videoWndInfo, 0, sizeof(CALL_S_VIDEOWND_INFO)*2);

	videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulRender = (TUP_UINT32)stRemoteWnd.hWnd;
	videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulVideoWndType = CALL_E_VIDEOWND_CALLREMOTE;
	videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulIndex = 0;
	videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulDisplayType = CALL_E_VIDEOWND_DISPLAY_FULL;

	videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulRender = (TUP_UINT32)stLocalWnd.hWnd;
	videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulVideoWndType = CALL_E_VIDEOWND_CALLLOCAL;
	videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulIndex = 1;
	videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulDisplayType = CALL_E_VIDEOWND_DISPLAY_FULL;

	TUP_RESULT tRet = TUP_FAIL;
	if(m_iCallStatus != VIDEOCALL)
	{
		tRet = tup_call_update_video_window(2, (CALL_S_VIDEOWND_INFO *)videoWndInfo,m_uiCallID);
	}
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("create wnd failed.");
		return UC_SDK_Failed;
	}

	if(m_iCallStatus == AUDIOCALL)
	{
		tRet = tup_call_reply_add_video(m_uiCallID,TUP_TRUE);
	}
	else
	{
		tRet = tup_call_accept_call(m_uiCallID,TUP_TRUE);
	}

	
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_accept_call failed.");
		return UC_SDK_Failed;
	}
	else
	{
		UCCallVideoEvent* pEvent = new UCCallVideoEvent;
		pEvent->SetCallid(m_uiCallID);
		pEvent->SetVideoStatus(CALL_VIDEO_CONNECTED);
		CUCEventMgr::Instance().PushEvent(pEvent);
	}
	
	
	return UC_SDK_Success;

}
int UCCallMgr::RejectCall(void)
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);

	//停止响铃
	(void)UCPlayMgr::Instance().EndPlayIncoming();
	(void)UCPlayMgr::Instance().EndPlayRingBack();


	TUP_RESULT tRet = tup_call_end_call(m_uiCallID);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_end_call failed.");
		return UC_SDK_Failed;
	}

	//清除成员
	(void)ClearConvMember();
	(void)ClearCallMember();

	return UC_SDK_Success;
}

int UCCallMgr::RejectVideoCall(void)
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);

	TUP_RESULT tRet = TUP_FAIL;
	if(m_iCallStatus == AUDIOCALL)
	{
		tRet = tup_call_reply_add_video(m_uiCallID,TUP_FALSE);
	}
	else
	{
		tRet = tup_call_end_call(m_uiCallID);
	}

	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("RejectVideoCall failed.");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;

}
int UCCallMgr::SendDTMF(char tone)
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);

	CALL_E_DTMF_TONE dtmfTone;
	if(tone == '0')
	{
		dtmfTone = CALL_E_DTMF0;
	}
	else if(tone == '1')
	{
		dtmfTone = CALL_E_DTMF1;
	}
	else if(tone == '2')
	{
		dtmfTone = CALL_E_DTMF2;
	}
	else if(tone == '3')
	{
		dtmfTone = CALL_E_DTMF3;
	}
	else if(tone == '4')
	{
		dtmfTone = CALL_E_DTMF4;
	}
	else if(tone == '5')
	{
		dtmfTone = CALL_E_DTMF5;
	}
	else if(tone == '6')
	{
		dtmfTone = CALL_E_DTMF6;
	}
	else if(tone == '7')
	{
		dtmfTone = CALL_E_DTMF7;
	}
	else if(tone == '8')
	{
		dtmfTone = CALL_E_DTMF8;
	}
	else if(tone == '9')
	{
		dtmfTone = CALL_E_DTMF9;
	}
	else if(tone == '*')
	{
		dtmfTone = CALL_E_DTMFSTAR;
	}
	else if(tone == '#')
	{
		dtmfTone = CALL_E_DTMFJIN;
	}
	else
	{
		ERROR_LOG("tone is invalid");
		return UC_SDK_InvalidPara;
	}		

	TUP_RESULT tRet = tup_call_send_DTMF(m_uiCallID,dtmfTone);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_send_DTMF failed.");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;

}
int UCCallMgr::ForwardCall(EM_MemberType iMemberType, const std::string& strNum)
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);

	if (UC_ACCOUNT == iMemberType)
	{
		std::string strAccount = strNum;
		IM_S_USERINFO user;
		if(UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(strAccount,user))
		{
			ERROR_LOG("getContactByAccount Error!");
			return UC_SDK_FindUriErr;
		}
		if(tup_call_divert_call(m_uiCallID,user.bindNO) != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_divert_call failed,forward account failed.");
			return UC_SDK_Failed;
		}
	}
	else if (UC_IPPHONE == iMemberType)
	{
		if(tup_call_divert_call(m_uiCallID,strNum.c_str()) != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_divert_call failed.");
			return UC_SDK_Failed;
		}		
	}
	else
	{
		return UC_SDK_InvalidPara;
	}
	return UC_SDK_Success;
}

int UCCallMgr::BlindTransCall(EM_MemberType iMemberType, const std::string& strNum)
{
	DEBUG_TRACE("");

	std::string bindcall;

	if (UC_ACCOUNT == iMemberType)
	{
		std::string strAccount = strNum;
		IM_S_USERINFO user;
		if(UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(strAccount,user))
		{
			ERROR_LOG("getContactByAccount Error!");
			return UC_SDK_FindUriErr;
		}
		bindcall = user.bindNO;
		
	}
	else if (UC_IPPHONE == iMemberType)
	{
		bindcall = strNum;
	}
	else
	{
		ERROR_LOG("iMemberType is invalid.");
		return UC_SDK_InvalidPara;
	}

	if(tup_call_blind_transfer(m_uiCallID,bindcall.c_str()) != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_blind_transfer failed.");
		return UC_SDK_Failed;
	}

	SetCallTransType(TRANSFER_TYPE);


	return UC_SDK_Success;

}

int UCCallMgr::SetCallEventCB(AVSessionClosedCB aVSessionClosedCallBack,
						  AVSessionConnectedCB aVSessionConnectedCallBack,
						  AVSessAddedCB aVSessAddedCallBack)const
{
	OnAVSessionClosedCB = aVSessionClosedCallBack;
	OnAVSessionConnectedCB = aVSessionConnectedCallBack;
	OnAVSessAddedCB = aVSessAddedCallBack;
	return UC_SDK_Success;
}

int UCCallMgr::SetVideoCallEventCB(VideoCallEventCB callEventCallBack)const
{
	OnVideoCallEventCB = callEventCallBack;
	return UC_SDK_Success;
}
int UCCallMgr::SetCallReservedEventCB(CallReservedEventCB _callReserveredEventCallBack)const
{
	OnCallReservedEventCB = _callReserveredEventCallBack;
	return UC_SDK_Success;
}
int UCCallMgr::SetCallTransEventCB(CallTransEventCB CallTransCallBack)const
{
	OnCallTransEventCB = CallTransCallBack;
	return UC_SDK_Success;
}

int UCCallMgr::MuteMic()const
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);

	TUP_RESULT tRet = tup_call_media_mute_mic(m_uiCallID,TUP_TRUE);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_call_media_mute_mic failed.");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;

}
int UCCallMgr::UnMuteMic()const
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);

	TUP_RESULT tRet = tup_call_media_mute_mic(m_uiCallID,TUP_FALSE);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_call_media_mute_mic failed.");
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;
}

int UCCallMgr::MuteSpeaker()const
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);
	TUP_RESULT tRet = tup_call_media_mute_speak(m_uiCallID,TUP_TRUE);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_call_media_mute_speak failed.");
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;
}
int UCCallMgr::UnMuteSpeaker()const
{
	CHECK_CALLID_RETURN(m_uiCallID,UC_SDK_Failed);
	TUP_RESULT tRet = tup_call_media_mute_speak(m_uiCallID,TUP_FALSE);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_call_media_mute_speak failed.");
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;
}

std::string UCCallMgr::GetCalleeAccountByCallID(TUP_UINT32 callid)
{
	if(m_uiCallID != callid)
	{
		ERROR_LOG("callid is invalids.");
		return "";
	}

	size_t nMemberCount = m_MemBindNOList.size();
	size_t nPhoneNum = m_MemPhoneList.size();
	size_t nNum = nMemberCount + nPhoneNum;
	if (0 == nNum)
	{
		ERROR_LOG("memberList is empty");
		return "";
	}

	if (1 == nMemberCount && 0 == nPhoneNum)
	{
		UCMemList::iterator it = m_MemBindNOList.begin();
		return (*it).first;
	}
	if (0 == nMemberCount && 1 == nPhoneNum)
	{
		PhoneMemList::iterator it = m_MemPhoneList.begin();
		return *it;
	}

	return "";
}

void UCCallMgr::ShowCallInfo(void)
{
	DEBUG_TRACE("");
	INFO_LOG("ShowCallInfo:CallID=%d",m_uiCallID);

	UCMemList::iterator it = m_MemBindNOList.begin();
	UCMemList::iterator itEnd = m_MemBindNOList.end();
	for(;it!=itEnd;it++)
	{
		std::string strAccount = it->first;
		std::string strBind = it->second;
		INFO_LOG("ShowCallInfo:UCMember[%s],BindNo[%s]",strAccount.c_str(),strBind.c_str());
	}
	PhoneMemList::iterator phoneit = m_MemPhoneList.begin();
	PhoneMemList::iterator phoneitEnd = m_MemPhoneList.end();
	for(;phoneit!=phoneitEnd;phoneit++)
	{
		std::string strphone = *phoneit;
		INFO_LOG("ShowCallInfo:PhoneMember[%s]",strphone.c_str());
	}
}


