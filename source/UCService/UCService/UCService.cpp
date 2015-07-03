//lint -e1784
// UCService.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Log.h"
#include "UCService.h"
#include "UCRegMgr.h"
#include "UCCallMgr.h"
#include "UCEventMgr.h"
#include "UCContactMgr.h"
#include "UCDeviceMgr.h"
#include "UCConfMgr.h"
#include "UCHistoryMgr.h"
#include "UCIMMgr.h"
#include "UCConfigMgr.h"

using namespace ecs::ecsdata;

#ifdef WIN32

//状态与注册
#pragma comment(linker, "/EXPORT:UC_SDK_Init=_UC_SDK_Init@0")
#pragma comment(linker, "/EXPORT:UC_SDK_SignInByPWD=_UC_SDK_SignInByPWD@16")
#pragma comment(linker, "/EXPORT:UC_SDK_SignOut=_UC_SDK_SignOut@0")
#pragma comment(linker, "/EXPORT:UC_SDK_UnInit=_UC_SDK_UnInit@0")
#pragma comment(linker, "/EXPORT:UC_SDK_PubSelfStatus=_UC_SDK_PubSelfStatus@8")
#pragma comment(linker, "/EXPORT:UC_SDK_GetContactStatus=_UC_SDK_GetContactStatus@12")
#pragma comment(linker, "/EXPORT:UC_SDK_GetContactInfo=_UC_SDK_GetContactInfo@8")
#pragma comment(linker, "/EXPORT:UC_SDK_SubscribeStatus=_UC_SDK_SubscribeStatus@4")
#pragma comment(linker, "/EXPORT:UC_SDK_UnSubscribeStatus=_UC_SDK_UnSubscribeStatus@4")


//呼叫管理
#pragma comment(linker, "/EXPORT:UC_SDK_AddCallMember=_UC_SDK_AddCallMember@8")
#pragma comment(linker, "/EXPORT:UC_SDK_MakeCall=_UC_SDK_MakeCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_HangupCall=_UC_SDK_HangupCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_AcceptCall=_UC_SDK_AcceptCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_RejectCall=_UC_SDK_RejectCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_SendDTMF=_UC_SDK_SendDTMF@4")
#pragma comment(linker, "/EXPORT:UC_SDK_HoldCall=_UC_SDK_HoldCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_ResumeCall=_UC_SDK_ResumeCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_ForwardCall=_UC_SDK_ForwardCall@8")
#pragma comment(linker, "/EXPORT:UC_SDK_BlindTransCall=_UC_SDK_BlindTransCall@8")

//视频呼叫
#pragma comment(linker, "/EXPORT:UC_SDK_HangupVideoCall=_UC_SDK_HangupVideoCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_MakeVideoCall=_UC_SDK_MakeVideoCall@40")
#pragma comment(linker, "/EXPORT:UC_SDK_AcceptVideoCall=_UC_SDK_AcceptVideoCall@40")
#pragma comment(linker, "/EXPORT:UC_SDK_RejectVideoCall=_UC_SDK_RejectVideoCall@0")

//语音会议
#pragma comment(linker, "/EXPORT:UC_SDK_InviteMemberInCall=_UC_SDK_InviteMemberInCall@8")
#pragma comment(linker, "/EXPORT:UC_SDK_TransCallToConf=_UC_SDK_TransCallToConf@8")
#pragma comment(linker, "/EXPORT:UC_SDK_DeleteMemberInCall=_UC_SDK_DeleteMemberInCall@8")
#pragma comment(linker, "/EXPORT:UC_SDK_ModifyMemberStatusInCall=_UC_SDK_ModifyMemberStatusInCall@12")

//设备管理
#pragma comment(linker, "/EXPORT:UC_SDK_MuteMic=_UC_SDK_MuteMic@0")
#pragma comment(linker, "/EXPORT:UC_SDK_UnMuteMic=_UC_SDK_UnMuteMic@0")
#pragma comment(linker, "/EXPORT:UC_SDK_MuteSpker=_UC_SDK_MuteSpker@0")
#pragma comment(linker, "/EXPORT:UC_SDK_UnMuteSpker=_UC_SDK_UnMuteSpker@0")
#pragma comment(linker, "/EXPORT:UC_SDK_GetMicLevel=_UC_SDK_GetMicLevel@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetMicLevel=_UC_SDK_SetMicLevel@4")
#pragma comment(linker, "/EXPORT:UC_SDK_GetSpkerLevel=_UC_SDK_GetSpkerLevel@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetSpkerLevel=_UC_SDK_SetSpkerLevel@4")
#pragma comment(linker, "/EXPORT:UC_SDK_GetMicDevList=_UC_SDK_GetMicDevList@16")
#pragma comment(linker, "/EXPORT:UC_SDK_GetSpeakerDevList=_UC_SDK_GetSpeakerDevList@16")
#pragma comment(linker, "/EXPORT:UC_SDK_GetVideoDevList=_UC_SDK_GetVideoDevList@16")
#pragma comment(linker, "/EXPORT:UC_SDK_GetCurrentMicDev=_UC_SDK_GetCurrentMicDev@4")
#pragma comment(linker, "/EXPORT:UC_SDK_GetCurrentSpeakerDev=_UC_SDK_GetCurrentSpeakerDev@4")
#pragma comment(linker, "/EXPORT:UC_SDK_GetCurrentVideoDev=_UC_SDK_GetCurrentVideoDev@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetCurrentMicDev=_UC_SDK_SetCurrentMicDev@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetCurrentSpeakerDev=_UC_SDK_SetCurrentSpeakerDev@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetCurrentVideoDev=_UC_SDK_SetCurrentVideoDev@4")

//历史记录
#pragma comment(linker, "/EXPORT:UC_SDK_QueryCallHistory=_UC_SDK_QueryCallHistory@20")
#pragma comment(linker, "/EXPORT:UC_SDK_InsertCallHistory=_UC_SDK_InsertCallHistory@16")
#pragma comment(linker, "/EXPORT:UC_SDK_ClearCallHistroy=_UC_SDK_ClearCallHistroy@4")
#pragma comment(linker, "/EXPORT:UC_SDK_QueryConvHistory=_UC_SDK_QueryConvHistory@16")
#pragma comment(linker, "/EXPORT:UC_SDK_InsertConvHistory=_UC_SDK_InsertConvHistory@16")
#pragma comment(linker, "/EXPORT:UC_SDK_InsertConvHistoryPart=_UC_SDK_InsertConvHistoryPart@12")
#pragma comment(linker, "/EXPORT:UC_SDK_ClearConvHistroy=_UC_SDK_ClearConvHistroy@0")
#pragma comment(linker, "/EXPORT:UC_SDK_QueryHisConvPartByID=_UC_SDK_QueryHisConvPartByID@20")
#pragma comment(linker, "/EXPORT:UC_SDK_DeleteCallHistory=_UC_SDK_DeleteCallHistory@4")
#pragma comment(linker, "/EXPORT:UC_SDK_DeleteConvHistory=_UC_SDK_DeleteConvHistory@4")

//话机联动
#pragma comment(linker, "/EXPORT:UC_SDK_GetPhoneJointDevType=_UC_SDK_GetPhoneJointDevType@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetPhoneJointDevType=_UC_SDK_SetPhoneJointDevType@4")

//通讯录查找
#pragma comment(linker, "/EXPORT:UC_SDK_GetUCAccount=_UC_SDK_GetUCAccount@8")

//事件回调
#pragma comment(linker, "/EXPORT:UC_SDK_SetLoginEventCB=_UC_SDK_SetLoginEventCB@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetStatusChangedCB=_UC_SDK_SetStatusChangedCB@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetCallEventCallBack=_UC_SDK_SetCallEventCallBack@12")
#pragma comment(linker, "/EXPORT:UC_SDK_SetVideoCallEventCallBack=_UC_SDK_SetVideoCallEventCallBack@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetConfMemEventCallBack=_UC_SDK_SetConfMemEventCallBack@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetPhoneJointEventCallBack=_UC_SDK_SetPhoneJointEventCallBack@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetCallReservedEventCallBack=_UC_SDK_SetCallReservedEventCallBack@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetIMEventCallBack=_UC_SDK_SetIMEventCallBack@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetCallTransEventCallBack=_UC_SDK_SetCallTransEventCallBack@4")



//打开portal
#pragma comment(linker, "/EXPORT:UC_SDK_OpenPortal=_UC_SDK_OpenPortal@4")

//扩展业务
#pragma comment(linker, "/EXPORT:UC_SDK_SetCallExService=_UC_SDK_SetCallExService@8")
#pragma comment(linker, "/EXPORT:UC_SDK_GetCallExService=_UC_SDK_GetCallExService@8")

//IM
#pragma comment(linker, "/EXPORT:UC_SDK_SendIM=_UC_SDK_SendIM@8")

#pragma comment(linker, "/EXPORT:UC_SDK_SetFileRecvEventCallBack=_UC_SDK_SetFileRecvEventCallBack@4")
#pragma comment(linker, "/EXPORT:UC_SDK_TransFile=_UC_SDK_TransFile@16")
#pragma comment(linker, "/EXPORT:UC_SDK_AcceptFile=_UC_SDK_AcceptFile@12")
#pragma comment(linker, "/EXPORT:UC_SDK_CancelFile=_UC_SDK_CancelFile@8")
#pragma comment(linker, "/EXPORT:UC_SDK_RejectFile=_UC_SDK_SendIM@8")

#endif

bool isInit = false;

#define CHECK_INIT_RETURN(isFlag,ret) if(!isFlag)\
{\
	ERROR_LOG("not init");\
	return ret;\
}

//初始化
int __UC_SDK_CALL UC_SDK_Init(void)
{
	if(isInit) 
	{
		INFO_LOG("already init");
		return UC_SDK_Success;
	}
	SetUnhandledExceptionFilter(GPTUnhandledExceptionFilter);

	//初始化日志
	std::string path;
	eSDKTool::getCurrentPath(path);
	std::string strLogCfgFile = path+"\\eSDKClientLogCfg.ini";
	std::string strLogStorePath = path+"\\eSDKLog";
	unsigned int logLevel[LOG_CATEGORY] = {INVALID_LOG_LEVEL,INVALID_LOG_LEVEL,INVALID_LOG_LEVEL};
	LogInit(PRODUCT_NAME,strLogCfgFile.c_str(),logLevel,strLogStorePath.c_str());
	INFO_TRACE("");

	UCHistoryMgr::Instance().Init(path);	
	UCRegMgr::Instance().Init();
	UCCallMgr::Instance().Init();
	ConfigMgr::Instance().Init();
	CUCEventMgr::Instance().Init();

	isInit = true;
	return UC_SDK_Success;
}

//去初始化
int __UC_SDK_CALL UC_SDK_UnInit()
{	
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	{	
		INFO_TRACE("");
		CUCEventMgr::Instance().Uninit();
		ConfigMgr::Instance().Uninit();
		UCCallMgr::Instance().Uninit();
		UCRegMgr::Instance().Uninit();		
		UCHistoryMgr::Instance().Uninit();
	}
	
	LogFini(PRODUCT_NAME);

	isInit = false;
	return UC_SDK_Success;
}

//通过用户名和密码登录
int __UC_SDK_CALL UC_SDK_SignInByPWD(const char* account, const char* pwd, const char* serverUrl,const char* langID)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if(NULL == account || NULL ==pwd || NULL == serverUrl || NULL == langID)
	{
		ERROR_LOG("Null Pointer");
		return UC_SDK_InvalidPara;
	}
	if( 0==strlen(account) || 0==strlen(pwd) || 0==strlen(serverUrl) || 0 ==strlen(langID))
	{
		ERROR_LOG("para is invalid");
		return UC_SDK_InvalidPara;
	}
	
	INFO_LOG("account=%s,serverUrl=%s,langID=%s",account,serverUrl,langID);

	std::string strAccount(account);
	std::string strPWD(pwd);
	std::string strUrl(serverUrl);
	std::string strLangID(langID);
	return UCRegMgr::Instance().SignInByPWD(strAccount,strPWD,strUrl,strLangID);
}

//登出
int __UC_SDK_CALL UC_SDK_SignOut()
{

	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	int iRet = UCRegMgr::Instance().SignOut();

	UCHistoryMgr::Instance().UninitUserData();
	return iRet;
}

//增加呼叫成员
int __UC_SDK_CALL UC_SDK_AddCallMember(int _memberType,const char* _member)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if(NULL == _member)
	{
		ERROR_LOG("phoneNum is null");
		return UC_SDK_InvalidPara;
	}
	if(0 == strlen(_member))
	{
		ERROR_LOG("phoneNum is empty");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("_member=%s,_memberType=%d",_member,_memberType);

	if(UC_ACCOUNT == _memberType)
	{
		std::string strAccount = _member;
		IM_S_USERINFO user;
		if(UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(strAccount,user))
		{
			ERROR_LOG("getContactByAccount Error!");
			return UC_SDK_FindUriErr;
		}

		(void)UCCallMgr::Instance().InsertUCMember(strAccount,user.bindNO);
		return UC_SDK_Success;
		
	}
	else if (UC_IPPHONE == _memberType)
	{
		std::string phone = _member;
		(void)UCCallMgr::Instance().InsertPhoneMember(phone);
		return UC_SDK_Success;
	}
	return UC_SDK_InvalidPara;
}

int __UC_SDK_CALL UC_SDK_GetUCAccount(const char* phoneNum,char _UCAcc[STRING_LENGTH])
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if(NULL == phoneNum)
	{
		ERROR_LOG("phoneNum is null.");
		return UC_SDK_NotFound;
	}
	INFO_LOG("phoneNum=%s",phoneNum);

	memset(_UCAcc,0,STRING_LENGTH);

	IM_S_USERINFO user;
	if(UC_SDK_Success != UCContactMgr::Instance().getContactByNum(phoneNum,user,IM_E_IMUSERQUERYTYPE_BY_BINDNO))
	{
		if(UC_SDK_Success != UCContactMgr::Instance().getContactByNum(phoneNum,user,IM_E_IMUSERQUERYTYPE_BY_PHONE))
		{
			ERROR_LOG("getContactByPhone failed.");
			return UC_SDK_Failed;
		}		
	}

	strcpy_s(_UCAcc,STRING_LENGTH,user.account);
	int iRet = UC_SDK_Success;
	return iRet;

}

//发起呼叫
int __UC_SDK_CALL UC_SDK_MakeCall()
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	return UCCallMgr::Instance().MakeCall();
}

//通话保持
int __UC_SDK_CALL UC_SDK_HoldCall()
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	return UCCallMgr::Instance().HoldCall();
}

//通话恢复
int __UC_SDK_CALL UC_SDK_ResumeCall()
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	return UCCallMgr::Instance().ResumeCall();
}

//来电转移
int __UC_SDK_CALL UC_SDK_ForwardCall(int iMemberType,const char* pMember)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	if (NULL == pMember)
	{
		ERROR_LOG("phoneNum is null pointer.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("iMemberType=%d, pMember=%s",iMemberType, pMember);
	if (0 == strlen(pMember))
	{
		ERROR_LOG("phoneNum is empty.");
		return UC_SDK_InvalidPara;
	}
	if (UC_ACCOUNT != iMemberType && UC_IPPHONE != iMemberType)
	{
		ERROR_LOG("memberType invalid.");
		return UC_SDK_InvalidPara;
	}

	std::string strMember = pMember;
	return UCCallMgr::Instance().ForwardCall((EM_MemberType)iMemberType,strMember);
}

//结束通话
int __UC_SDK_CALL UC_SDK_HangupCall()
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	return UCCallMgr::Instance().HangupCall();
}
//结束视频通话
int __UC_SDK_CALL UC_SDK_HangupVideoCall()
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	return UCCallMgr::Instance().HangupVideoCall();
}

//接听呼叫
int __UC_SDK_CALL UC_SDK_AcceptCall()
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);


	if(UCConfMgr::Instance().GetConfID() != 0)
	{
		return UCConfMgr::Instance().AcceptConf();
	}

	return UCCallMgr::Instance().AcceptCall();	
}

//接听呼叫
int __UC_SDK_CALL UC_SDK_AcceptVideoCall(int localHWnd, int localLeft, int localTop, int localWidth, int localHeight,
									int remoteHWnd, int remoteLeft, int remoteTop, int remoteWidth, int remoteHeight)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	INFO_LOG("localHWnd=%d, localLeft=%d, localTop=%d, localWidth=%d, localHeight=%d"
		,localHWnd
		,localLeft
		,localTop
		,localWidth
		,localHeight);
	INFO_LOG("remoteHWnd=%d, remoteLeft=%d, remoteTop=%d, remoteWidth=%d, remoteHeight=%d"
		,remoteHWnd
		,remoteLeft
		,remoteTop
		,remoteWidth
		,remoteHeight);

	STVideoWindow stLocalWnd;
	stLocalWnd.hWnd = localHWnd;
	stLocalWnd.left = localLeft;
	stLocalWnd.top = localTop;
	stLocalWnd.width = localWidth;
	stLocalWnd.height = localHeight;

	STVideoWindow stRemoteWnd;
	stRemoteWnd.hWnd = remoteHWnd;
	stRemoteWnd.left = remoteLeft;
	stRemoteWnd.top = remoteTop;
	stRemoteWnd.width = remoteWidth;
	stRemoteWnd.height = remoteHeight;

	return UCCallMgr::Instance().AcceptVideoCall(stLocalWnd,stRemoteWnd);
}

//拒绝呼叫
int __UC_SDK_CALL UC_SDK_RejectCall()
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UCConfMgr::Instance().GetConfID() != 0)
	{
		return UCConfMgr::Instance().RejectConf();
	}

	return UCCallMgr::Instance().RejectCall();
}

//拒绝视频呼叫
int __UC_SDK_CALL UC_SDK_RejectVideoCall()
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	return UCCallMgr::Instance().RejectVideoCall();
}

//二次拨号
int __UC_SDK_CALL UC_SDK_SendDTMF(char tone)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	return UCCallMgr::Instance().SendDTMF(tone);
}

//麦克风静音
int __UC_SDK_CALL UC_SDK_MuteMic(void)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	
	return UCCallMgr::Instance().MuteMic();
}

//麦克风取消静音
int __UC_SDK_CALL UC_SDK_UnMuteMic(void)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	return UCCallMgr::Instance().UnMuteMic();

}
//获取麦克风音量
int __UC_SDK_CALL UC_SDK_GetMicLevel(int& level)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	level = 0;

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}


	return UCDeviceMgr::Instance().GetMicLevel(level);


}
//设置麦克风音量
int __UC_SDK_CALL UC_SDK_SetMicLevel(int level)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	INFO_LOG("level=%d",level);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}


	return UCDeviceMgr::Instance().SetMicLevel(level);

}
//扬声器静音
int __UC_SDK_CALL UC_SDK_MuteSpker(void)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);


	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	return UCCallMgr::Instance().MuteSpeaker();

}
//扬声器取消静音
int __UC_SDK_CALL UC_SDK_UnMuteSpker(void)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	return UCCallMgr::Instance().UnMuteSpeaker();
}
//获取扬声器音量
int __UC_SDK_CALL UC_SDK_GetSpkerLevel(int& level)
{	
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	
	level = 0;

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	return UCDeviceMgr::Instance().GetSpeakerLevel(level);
	
}
//设置扬声器音量
int __UC_SDK_CALL UC_SDK_SetSpkerLevel(int level)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	INFO_LOG("level=%d",level);


	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	return UCDeviceMgr::Instance().SetSpeakerLevel(level);

}

//发起视频呼叫或者将当前语音呼叫升级为视频呼叫
int __UC_SDK_CALL UC_SDK_MakeVideoCall(int localHWnd, int localLeft, int localTop, int localWidth, int localHeight,
									   int remoteHWnd, int remoteLeft, int remoteTop, int remoteWidth, int remoteHeight)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_LOG("localHWnd=%d, localLeft=%d, localTop=%d, localWidth=%d, localHeight=%d"
		,localHWnd
		,localLeft
		,localTop
		,localWidth
		,localHeight);
	INFO_LOG("remoteHWnd=%d, remoteLeft=%d, remoteTop=%d, remoteWidth=%d, remoteHeight=%d"
		,remoteHWnd
		,remoteLeft
		,remoteTop
		,remoteWidth
		,remoteHeight);

	//校验入参
	if (0 == localHWnd || 0 == remoteHWnd)
	{
		ERROR_LOG("localHWnd or remoteHWnd is 0");
		return UC_SDK_Failed;
	}

	STVideoWindow stLocalWnd;
	stLocalWnd.height = localHeight;
	stLocalWnd.width = localWidth;
	stLocalWnd.top = localTop;
	stLocalWnd.left = localLeft;
	stLocalWnd.hWnd = localHWnd;	

	STVideoWindow stRemoteWnd;	
	stRemoteWnd.height = remoteHeight;
	stRemoteWnd.width = remoteWidth;
	stRemoteWnd.top = remoteTop;
	stRemoteWnd.left = remoteLeft;
	stRemoteWnd.hWnd = remoteHWnd;

	return UCCallMgr::Instance().MakeVideoCall(stLocalWnd,stRemoteWnd);

}

//语音会议中邀请成员
int __UC_SDK_CALL UC_SDK_InviteMemberInCall(int _memberType,const char* pAccount)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if (NULL == pAccount)
	{
		ERROR_LOG("pAccount is null pointer.");
		return UC_SDK_InvalidPara;
	}
	if (0 == strlen(pAccount))
	{
		ERROR_LOG("pAccount is empty.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("_memberType=%d,pAccount=%s",_memberType,pAccount);

	if(UCCallMgr::Instance().GetConvStarted())
	{
		INFO_LOG("%s Into conference directly",pAccount);
		//如果会议开始，则直接新增成员
		return UCConfMgr::Instance().InviteMemberInConf((EM_MemberType)_memberType,pAccount);
		
	}
	else 
	{
		INFO_LOG("%s Into conference by call",pAccount);
		//如果会议未开始，调用call转conf接口
		return UCCallMgr::Instance().TransCallToConf((EM_MemberType)_memberType,pAccount);
		
	}
}

int __UC_SDK_CALL UC_SDK_TransCallToConf(STConfMemList* pMemList,int memsize)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if (NULL == pMemList)
	{
		ERROR_LOG("memList is null pointer.");
		return UC_SDK_InvalidPara;
	}

	INFO_LOG("pMemList=0x%d,pMemList.size=%d,size=%d",pMemList,pMemList->size,memsize);

	unsigned int uiSize = sizeof(STConfMemList)+((unsigned int)pMemList->size-1)*sizeof(STConfMember);

	if(memsize != (int)uiSize)
	{
		ERROR_LOG("size[%d] is error.",uiSize);
		return UC_SDK_InvalidPara;
	}
	std::vector<std::string> ucMemList;
	std::vector<std::string> phoneMemList;
	std::string allmember;
	for(int i=0;i<pMemList->size;i++)
	{
		std::string phoneoraccount = pMemList->stConfMem[i].account;
		if(pMemList->stConfMem[i].membertype == UC_ACCOUNT)
		{
			ucMemList.push_back(phoneoraccount);
		}
		else
		{
			phoneMemList.push_back(phoneoraccount);
		}
		allmember.append(phoneoraccount);
		allmember.append(",");
	}

	INFO_LOG("UC_SDK_TransCallToConf:%s",allmember.c_str());
	return UCCallMgr::Instance().TransCallToConf(ucMemList,phoneMemList);
}

//语音会议中删除成员
int __UC_SDK_CALL UC_SDK_DeleteMemberInCall(int _memberType,const char* pAccount)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if(_memberType < UC_ACCOUNT || _memberType > UC_IPPHONE)
	{
		ERROR_LOG("invalid memberType.");
		return UC_SDK_InvalidPara;
	}
	
	if (NULL == pAccount)
	{
		ERROR_LOG("pAccount is null pointer");
		return UC_SDK_InvalidPara;
	}
	if (0 == strlen(pAccount))
	{
		ERROR_LOG("pAccount is empty.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("_memberType=%d,pAccount=%s",_memberType,pAccount);

	if(!UCCallMgr::Instance().GetConvStarted())
	{
		ERROR_LOG("No Conf.");
		return UC_SDK_Failed;
	}

	//如果会议已经开始，则直接踢出
	return UCConfMgr::Instance().DeleteMemberInCall((EM_MemberType)_memberType,pAccount);

}

//包括语音会议中断开某成员的语音，语音会议中重新呼叫某成员，语音会议中对某成员静音，对某成员取消静音4种。
int __UC_SDK_CALL UC_SDK_ModifyMemberStatusInCall(int operateType,int memberType,const char* pAccount)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	
	if (NULL == pAccount)
	{
		ERROR_LOG("pAccount is null.");
		return UC_SDK_InvalidPara;
	}
	if(operateType < EndCallMember || operateType > UnMuteMember)
	{
		ERROR_LOG("invalid operateType.");
		return UC_SDK_InvalidPara;
	}
	if(memberType < UC_ACCOUNT || memberType > UC_IPPHONE)
	{
		ERROR_LOG("invalid memberType.");
		return UC_SDK_InvalidPara;
	}

	INFO_LOG("operateType=%d,memberType=%d,pAccount=%s",operateType,memberType,pAccount);

	std::string strAccount = pAccount;
	int iRet = UCConfMgr::Instance().ModifyMemberStatusInCall((EM_ConvnerOperateType)operateType, (EM_MemberType)memberType,strAccount);

	return iRet;
}

//获取麦克风设备列表
int __UC_SDK_CALL UC_SDK_GetMicDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_LOG("_fromIndex=%d,_toIndex=%d,_size=%d,devList=0x%x",_fromIndex,_toIndex,_size,devList);
	if (NULL == devList || 0>_fromIndex || _fromIndex>_toIndex || 0>=_size)
	{
		ERROR_LOG("Invalid Param");
		return UC_SDK_InvalidPara;
	}

	int queryMicSize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STDeviceListParam)+(unsigned int)(queryMicSize-1)*sizeof(STDeviceParam));
	if(_size != iSize)
	{
		ERROR_LOG("alloc memory invalid.");
		return UC_SDK_InvalidPara;
	}

	return UCDeviceMgr::Instance().GetMicDevList(_fromIndex,_toIndex,devList);
}
//获取扬声器设备列表
int __UC_SDK_CALL UC_SDK_GetSpeakerDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_LOG("_fromIndex=%d,_toIndex=%d,_size=%d,devList=0x%x",_fromIndex,_toIndex,_size,devList);
	if (NULL == devList || 0>_fromIndex || _fromIndex>_toIndex || 0>=_size)
	{
		ERROR_LOG("Invalid Param");
		return UC_SDK_InvalidPara;
	}

	int querySpeakerSize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STDeviceListParam)+(unsigned int)(querySpeakerSize-1)*sizeof(STDeviceParam));
	if(_size != iSize)
	{
		ERROR_LOG("alloc memory invalid.");
		return UC_SDK_InvalidPara;
	}

	return UCDeviceMgr::Instance().GetSpeakerDevList(_fromIndex,_toIndex,devList);
}
//获取视频设备列表
int __UC_SDK_CALL UC_SDK_GetVideoDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_LOG("_fromIndex=%d,_toIndex=%d,_size=%d,devList=0x%x",_fromIndex,_toIndex,_size,devList);
	if (NULL == devList || 0>_fromIndex || _fromIndex>_toIndex || 0>=_size)
	{
		ERROR_LOG("Invalid Param");
		return UC_SDK_InvalidPara;
	}

	int queryVideoSize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STDeviceListParam)+((unsigned int)(queryVideoSize-1))*sizeof(STDeviceParam));
	if(_size != iSize)
	{
		ERROR_LOG("alloc memory invalid.");
		return UC_SDK_InvalidPara;
	}

	return UCDeviceMgr::Instance().GetVideoDevList(_fromIndex,_toIndex,devList);
}
//获取当前麦克风设备
int __UC_SDK_CALL UC_SDK_GetCurrentMicDev(STDeviceParam* device)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if (NULL == device)
	{
		ERROR_LOG("device is null pointer.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("device=0x%x",device);
	return UCDeviceMgr::Instance().GetCurrentMicDev(device);

}
//获取当前扬声器设备
int __UC_SDK_CALL UC_SDK_GetCurrentSpeakerDev(STDeviceParam* device)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if (NULL == device)
	{
		ERROR_LOG("device is null pointer.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("device=0x%x",device);
	return UCDeviceMgr::Instance().GetCurrentSpeakerDev(device);
}
//获取当前视频设备
int __UC_SDK_CALL UC_SDK_GetCurrentVideoDev(STDeviceParam* device)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if (NULL == device)
	{
		ERROR_LOG("device is null pointer.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("device=0x%x",device);
	return UCDeviceMgr::Instance().GetCurrentVideoDev(device);
}
//设置当前麦克风设备
int __UC_SDK_CALL UC_SDK_SetCurrentMicDev(int index)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_LOG("index = %d",index);
	if (index < 0)
	{
		ERROR_LOG("index is less than 0");
		return UC_SDK_InvalidPara;
	}
	return UCDeviceMgr::Instance().SetCurrentMicDev(index);
}
//设置当前扬声器设备
int __UC_SDK_CALL UC_SDK_SetCurrentSpeakerDev(int index)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_LOG("index = %d",index);
	if (index < 0)
	{
		ERROR_LOG("index is less than 0");
		return UC_SDK_InvalidPara;
	}
	return UCDeviceMgr::Instance().SetCurrentSpeakerDev(index);
}
//设置当前视频设备
int __UC_SDK_CALL UC_SDK_SetCurrentVideoDev(int index)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_LOG("index = %d",index);
	if (index < 0)
	{
		ERROR_LOG("index is less than 0");
		return UC_SDK_InvalidPara;
	}
	return UCDeviceMgr::Instance().SetCurrentVideoDev(index);
}

//设置登录回调
int __UC_SDK_CALL UC_SDK_SetLoginEventCB(ClientSignInNotifyCB _loginEventCB)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_loginEventCB=0x%x",_loginEventCB);

	if (NULL == _loginEventCB)
	{
		ERROR_LOG("Null Pointer");
		return UC_SDK_InvalidPara;
	}

	int iRet = UCRegMgr::Instance().SetLoginEventCB(_loginEventCB);


	return iRet;
}

//设置状态回调（登陆前必须调用）
int __UC_SDK_CALL UC_SDK_SetStatusChangedCB(StatusChangedCB _statusEventCB)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_statusEventCB=0x%x",_statusEventCB);

	if (NULL == _statusEventCB)
	{
		ERROR_LOG("Null Pointer");
		return UC_SDK_InvalidPara;
	}

	return UCRegMgr::Instance().SetStatusEventCB(_statusEventCB);
}

//设置呼叫事件回调
int __UC_SDK_CALL UC_SDK_SetCallEventCallBack(AVSessionClosedCB _AVSessClosedCB,
											  AVSessionConnectedCB _AVSessConnCB,
											  AVSessAddedCB _AVSessAddedCB)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_AVSessClosedCB=0x%x,_AVSessConnCB=0x%x,_AVSessAddedCB=0x%x",_AVSessClosedCB,_AVSessConnCB,_AVSessAddedCB);

	if (NULL == _AVSessClosedCB || NULL == _AVSessConnCB || NULL == _AVSessAddedCB)
	{
		ERROR_LOG("CallBack Function is NULL");
		return UC_SDK_InvalidPara;
	}

	return UCCallMgr::Instance().SetCallEventCB(_AVSessClosedCB,_AVSessConnCB,_AVSessAddedCB);

}

int __UC_SDK_CALL UC_SDK_SetVideoCallEventCallBack(VideoCallEventCB _callEventCallBack)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_callEventCallBack=0x%x",_callEventCallBack);

	if (NULL == _callEventCallBack)
	{
		ERROR_LOG("CallBack Function is NULL");
		return UC_SDK_InvalidPara;
	}

	return UCCallMgr::Instance().SetVideoCallEventCB(_callEventCallBack);

}
int __UC_SDK_CALL UC_SDK_SetConfMemEventCallBack(ConfMemberEventCB confMemEventCallBack)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("confMemEventCallBack=0x%x",confMemEventCallBack);

	if (NULL == confMemEventCallBack)
	{
		ERROR_LOG("confMemEventCallBack Function is NULL");
		return UC_SDK_InvalidPara;
	}

	return UCConfMgr::Instance().SetConfMemEventCB(confMemEventCallBack);

}

int __UC_SDK_CALL UC_SDK_QueryCallHistory(int _callType,  int _fromIndex, int _toIndex, STCallHistroyData* _queryResult,int _size)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_callType=%d,_fromIndex=%d,_toIndex=%d,_size=%d",_callType,_fromIndex,_toIndex,_size);
	if(NULL == _queryResult)
	{
		ERROR_LOG("_queryResult is NULL.");
		return UC_SDK_InvalidPara;
	}

	if(_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG("query para is invalid.");
		return UC_SDK_InvalidPara;
	}

	int querySize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STCallHistroyData)+(unsigned int)(querySize-1)*sizeof(STCallHistroyItem));
	if(_size != iSize)
	{
		ERROR_LOG("memory size is invalid.");
		return UC_SDK_InvalidPara;
	}	

	return UCHistoryMgr::Instance().QueryCallHistory(_callType,_fromIndex,_toIndex,_queryResult);
}

int __UC_SDK_CALL UC_SDK_ClearCallHistroy(int _callType)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_callType=%d",_callType);

	return UCHistoryMgr::Instance().ClearCallHistory(_callType);
}

int __UC_SDK_CALL UC_SDK_InsertCallHistory(int _CallType,const char* _account,const char* _name,int _duration)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if(NULL == _account)
	{
		ERROR_LOG("account is NULL.");
		return UC_SDK_InvalidPara;
	}
	if(0 == strlen(_account))
	{
		ERROR_LOG("account length is 0.");
		return UC_SDK_InvalidPara;
	}
	if(NULL == _name)
	{
		ERROR_LOG("name is NULL.");
		return UC_SDK_InvalidPara;
	}
	if(0 == strlen(_name))
	{
		ERROR_LOG("name length is 0.");
		return UC_SDK_InvalidPara;
	}

	INFO_LOG("_CallType=%d,_account=%s,_name=%s,_duration=%d",_CallType,_account,_name,_duration);

	return UCHistoryMgr::Instance().InsertCallHistory(_CallType,_account,_name,_duration);

}

int __UC_SDK_CALL UC_SDK_QueryConvHistory(int _fromIndex,int _toIndex,STConvHistroyData* _result,int _size)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_fromIndex=%d,_toIndex=%d,_size=%d",_fromIndex,_toIndex,_size);

	if(NULL == _result)
	{
		ERROR_LOG("_queryResult is NULL.");
		return UC_SDK_InvalidPara;
	}

	if(_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG("query para is invalid.");
		return UC_SDK_InvalidPara;
	}

	int querySize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STConvHistroyData)+(unsigned int)(querySize-1)*sizeof(STConvHistroyItem));
	if(_size != iSize)
	{
		ERROR_LOG("memory size is invalid.");
		return UC_SDK_InvalidPara;
	}

	return UCHistoryMgr::Instance().QueryConvHistory(_fromIndex,_toIndex,_result);
}
int __UC_SDK_CALL UC_SDK_QueryHisConvPartByID(const char* _convID,int _fromIndex,int _toIndex,STConfPartData* _result,int _size)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_fromIndex=%d,_toIndex=%d,_size=%d",_fromIndex,_toIndex,_size);

	if(NULL == _convID)
	{
		ERROR_LOG("convID is null.");
		return UC_SDK_InvalidPara;
	}

	if(0 == strlen(_convID))
	{
		ERROR_LOG("convID is empty.");
		return UC_SDK_InvalidPara;
	}

	if(NULL == _result)
	{
		ERROR_LOG("_queryResult is NULL.");
		return UC_SDK_InvalidPara;
	}

	if(_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG("query para is invalid.");
		return UC_SDK_InvalidPara;
	}

	int querySize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STConfPartData)+(unsigned int)(querySize-1)*sizeof(STConfPartItem));
	if(_size != iSize)
	{
		ERROR_LOG("memory size is invalid.");
		return UC_SDK_InvalidPara;
	}

	return UCHistoryMgr::Instance().QueryHisConvPartByID(_convID,_fromIndex,_toIndex,_result);
}


int __UC_SDK_CALL UC_SDK_ClearConvHistroy()
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	return UCHistoryMgr::Instance().ClearConvHistory();
}

int __UC_SDK_CALL UC_SDK_InsertConvHistory(const char* _leaderAccount,const char* _leaderName,int _duration,char _historyID[STRING_LENGTH])
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if(NULL == _leaderAccount)
	{
		ERROR_LOG("leaderAccount is NULL.");
		return UC_SDK_InvalidPara;
	}

	if(NULL == _leaderName)
	{
		ERROR_LOG("leaderName is NULL.");
		return UC_SDK_InvalidPara;
	}

	std::string strHisID = eSDKTool::CreateGuidStr();
	if("" == strHisID)
	{
		ERROR_LOG("creat strHisID failed");
		return UC_SDK_Failed;
	}

	INFO_LOG("_leaderAccount=%s,_leaderName=%s,_duration=%d",_leaderAccount,_leaderName,_duration);

	int iRet = UCHistoryMgr::Instance().InsertConvHistory(strHisID,_leaderAccount,_leaderName,_duration);

	if(UC_SDK_Success == iRet)
	{
		memset(_historyID,0,STRING_LENGTH);
		strcpy_s(_historyID,STRING_LENGTH,strHisID.c_str());
	}	

	return iRet;
}

int __UC_SDK_CALL UC_SDK_InsertConvHistoryPart(const char* _historyConvID,const char* _partAccount,const char* _partName)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if(NULL == _historyConvID)
	{
		ERROR_LOG("historyConvID is NULL.");
		return UC_SDK_InvalidPara;
	}

	if(0 == strlen(_historyConvID))
	{
		ERROR_LOG("historyConvID size is 0.");
		return UC_SDK_InvalidPara;

	}

	if(NULL == _partAccount)
	{
		ERROR_LOG("partAccount is NULL.");
		return UC_SDK_InvalidPara;
	}
	if(0 == strlen(_partAccount))
	{
		ERROR_LOG("partAccount size is 0.");
		return UC_SDK_InvalidPara;

	}

	if(NULL == _partName)
	{
		ERROR_LOG("partName is NULL.");
		return UC_SDK_InvalidPara;
	}
	if(0 == strlen(_partName))
	{
		ERROR_LOG("partName size is 0.");
		return UC_SDK_InvalidPara;

	}

	INFO_LOG("_historyConvID=%s,_partAccount=%s,_partName=%s",_historyConvID,_partAccount,_partName);

	return UCHistoryMgr::Instance().InsertConvHistoryPart(_historyConvID,_partAccount,_partName);
}

int __UC_SDK_CALL UC_SDK_DeleteCallHistory(int iRcdID)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("iRcdID=%d",iRcdID);

	return UCHistoryMgr::Instance().DeleteCallHistory(iRcdID);
}

int __UC_SDK_CALL UC_SDK_DeleteConvHistory(const char* _pConvID)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if(NULL == _pConvID)
	{
		ERROR_LOG("invalid  ConvID.");
		return UC_SDK_InvalidPara;
	}

	INFO_LOG("_pConvID=%s",_pConvID);

	std::string strConvID(_pConvID);
	return UCHistoryMgr::Instance().DeleteConvHistory(strConvID);
}

int __UC_SDK_CALL UC_SDK_GetPhoneJointDevType(int& _iDevType)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_iDevType=%d",_iDevType);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{

		return UC_SDK_NotLogin;
	}
	return ConfigMgr::Instance().GetPhoneJointDevType(_iDevType);
}

int __UC_SDK_CALL UC_SDK_SetPhoneJointDevType(int _iDevType)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_iDevType=%d",_iDevType);
	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	
	return ConfigMgr::Instance().SetPhoneJointDevType(_iDevType);
}

int __UC_SDK_CALL UC_SDK_SetPhoneJointEventCallBack(PhoneJointEventCB pjEventCallBack)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("pjEventCallBack=0x%x",pjEventCallBack);

	return ConfigMgr::Instance().SetPhoneJointEventCB(pjEventCallBack);
}

int __UC_SDK_CALL UC_SDK_OpenPortal(int _type)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_type=%d",_type);
	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}	

	int iRet = UC_SDK_Success;


	return iRet;

}

int __UC_SDK_CALL UC_SDK_PubSelfStatus(int _Status,const char* _Desc)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_Status=%d",_Status);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		ERROR_LOG("Publish self status failed.");

		return UC_SDK_NotLogin;
	}

	if(_Status < UC_Offline || _Status > UC_NoDisturb)
	{
		ERROR_LOG("invalid  status.");
		return UC_SDK_InvalidPara;
	}
	if(NULL == _Desc)
	{
		ERROR_LOG("invalid  Desc.");
		return UC_SDK_InvalidPara;
	}

	std::string strDesc(_Desc);
	return UCRegMgr::Instance().PubSelfStatus(_Status,strDesc);
}

int __UC_SDK_CALL UC_SDK_GetContactStatus(int _AccountType,const char* _Account,int& _Status)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(NULL == _Account)
	{
		ERROR_LOG("account is NULL.");
		return UC_SDK_InvalidPara;
	}

	INFO_LOG("_AccountType=%d,_Account=%s",_AccountType,_Account);

	//非UC账户直接设置为离线
	if(UC_ACCOUNT != _AccountType)
	{
		_Status = UC_Offline;
		INFO_LOG("%s is Offline.",_Account);
		return UC_SDK_Success;
	}

	return UCRegMgr::Instance().GetContactStatus(_Account,_Status);
}

int __UC_SDK_CALL UC_SDK_GetContactInfo(const char* _Account,STContact* _pContactInfo)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if(NULL == _Account)
	{
		ERROR_LOG("account is NULL.");
		return UC_SDK_InvalidPara;
	}

	if(NULL == _pContactInfo)
	{
		ERROR_LOG("_pContactInfo is NULL.");
		return UC_SDK_InvalidPara;
	}

	INFO_LOG("_Account=%s",_Account);

	std::string strAccount(_Account);
	return UCRegMgr::Instance().GetContactInfo(strAccount,*_pContactInfo);
}

int __UC_SDK_CALL UC_SDK_SubscribeStatus(const char* _Account)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if(NULL == _Account)
	{
		ERROR_LOG("account is NULL.");
		return UC_SDK_InvalidPara;
	}

	INFO_LOG("_Account=%s",_Account);

	return UCRegMgr::Instance().SubscribeStatus(_Account);
}

int __UC_SDK_CALL UC_SDK_UnSubscribeStatus(const char* _Account)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if(NULL == _Account)
	{
		ERROR_LOG("account is NULL.");
		return UC_SDK_InvalidPara;
	}

	INFO_LOG("account=%s",_Account);
	return UCRegMgr::Instance().DisSubscribeStatus(_Account);
}

int __UC_SDK_CALL UC_SDK_SetCallExService(int _type,const STCallExData* _CallExData)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_type=%d",_type);

	if(NULL == _CallExData)
	{
		ERROR_LOG("_CallExData is NULL.");
		return UC_SDK_NullPtr;
	}

	INFO_LOG("_type=%d,_CallExData->Num=%s",_type,_CallExData->Num);
	if(_type < FORWARD_UNCONDITION || _type >= FORWARD_BORDER)
	{
		ERROR_LOG("_type is invalid.");
		return UC_SDK_InvalidPara;
	}
	
	return ConfigMgr::Instance().SetCallExService(_type,_CallExData->Num);
}

int __UC_SDK_CALL UC_SDK_GetCallExService(int _type,STCallExData* _CallExData)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("_type=%d",_type);

	if(NULL == _CallExData)
	{
		ERROR_LOG("_CallExData is NULL.");
		return UC_SDK_NullPtr;
	}

	std::string strNum;
	int iRet = ConfigMgr::Instance().GetCallExService(_type,strNum);
	if(UC_SDK_Success == iRet)
	{
		(void)strcpy_s(_CallExData->Num,strNum.c_str());
		return UC_SDK_Success;
	}


	return iRet;
}

int __UC_SDK_CALL UC_SDK_BlindTransCall(int iMemberType,const char* pMember)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);

	if(UC_SDK_Success != UCRegMgr::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	if (NULL == pMember)
	{
		ERROR_LOG("phoneNum is null pointer.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("iMemberType=%d, pMember=%s",iMemberType, pMember);
	if (0 == strlen(pMember))
	{
		ERROR_LOG("phoneNum is empty.");
		return UC_SDK_InvalidPara;
	}
	if (UC_ACCOUNT != iMemberType && UC_IPPHONE != iMemberType)
	{
		ERROR_LOG("memberType invalid.");
		return UC_SDK_InvalidPara;
	}

	std::string strMember = pMember;
	int iRet = UCCallMgr::Instance().BlindTransCall((EM_MemberType)iMemberType,strMember);
	return iRet;

}


int __UC_SDK_CALL UC_SDK_SetCallReservedEventCallBack(CallReservedEventCB CREventCB)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	INFO_LOG("CREventCB=0x%x",CREventCB);
	return UCCallMgr::Instance().SetCallReservedEventCB(CREventCB);
}

int __UC_SDK_CALL UC_SDK_GetEntContactList(const char* strSearchKey
										   ,int _fromIndex
										   ,int _toIndex
										   , STContactList* _pContactList)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if (NULL == strSearchKey)
	{
		ERROR_LOG("strSearchKey is null pointer.");
		return UC_SDK_InvalidPara;
	}
	if (NULL == _pContactList)
	{
		ERROR_LOG("phoneNum is null pointer.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("strSearchKey=%s,_fromIndex=%d,_toIndex=%d",strSearchKey,_fromIndex,_toIndex);

	return UCContactMgr::Instance().getContactList(strSearchKey,_fromIndex,_toIndex,_pContactList);

}

int __UC_SDK_CALL UC_SDK_SendIM(const char* _account,const char* _IMContent)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if (NULL == _account)
	{
		ERROR_LOG("_account is null pointer.");
		return UC_SDK_InvalidPara;
	}
	if (NULL == _IMContent)
	{
		ERROR_LOG("_IMContent is null pointer.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("_account=%s",_account);

	if(0 == strlen(_account))
	{
		ERROR_LOG("_account is empty.");
		return UC_SDK_InvalidPara;
	}
	if(0 == strlen(_IMContent))
	{
		ERROR_LOG("_IMContent is empty.");
		return UC_SDK_InvalidPara;
	}

	return UCIMMgr::Instance().SendP2PIM(_account,_IMContent);
}

int __UC_SDK_CALL UC_SDK_SetIMEventCallBack(IMRecvNotifyCB IMRecvCallBack)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if (NULL == IMRecvCallBack)
	{
		ERROR_LOG("IMRecvCallBack is null pointer.");
		return UC_SDK_InvalidPara;
	}

	return UCIMMgr::Instance().SetIMEventCallBack(IMRecvCallBack);
}

int __UC_SDK_CALL UC_SDK_SetFileRecvEventCallBack(FileTransNotifyCB FileTransCallBack)
{
	INFO_TRACE("");
	if (NULL == FileTransCallBack)
	{
		ERROR_LOG("FileTransCallBack is null pointer.");
		return UC_SDK_InvalidPara;
	}


	return UCIMMgr::Instance().SetFileTransCallBack(FileTransCallBack);
}

int __UC_SDK_CALL UC_SDK_TransFile(const char* _account,const char* _filePath,char _ConvID[STRING_LENGTH],char _TranID[STRING_LENGTH])
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if (NULL == _account)
	{
		ERROR_LOG("_account is null pointer.");
		return UC_SDK_InvalidPara;
	}
	if (NULL == _filePath)
	{
		ERROR_LOG("_filePath is null pointer.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("_account=%s",_account);
	std::string tansid;
	std::string confid;

	int iRet =  UCIMMgr::Instance().TransFile(_account,_filePath,tansid,confid);
	if(UC_SDK_Success == iRet)
	{
		memset(_ConvID,0,STRING_LENGTH);
		memcpy_s(_ConvID,STRING_LENGTH,confid.c_str(),(confid.size()<(STRING_LENGTH)) ? (confid.size()) : (STRING_LENGTH-1) );
		memset(_TranID,0,STRING_LENGTH);
		memcpy_s(_TranID,STRING_LENGTH,tansid.c_str(),(tansid.size()<(STRING_LENGTH)) ? (tansid.size()) : (STRING_LENGTH-1) );	
		INFO_LOG("_ConvID=%s,_TranID=%s",_ConvID,_TranID);
	}
	return iRet;

}

int __UC_SDK_CALL UC_SDK_AcceptFile(const char* _ConvID,const char* _TranID,const char* _FileSavePath)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if (NULL == _ConvID)
	{
		ERROR_LOG("_ConvID is null pointer.");
		return UC_SDK_InvalidPara;
	}
	if (NULL == _TranID)
	{
		ERROR_LOG("_TranID is null pointer.");
		return UC_SDK_InvalidPara;
	}
	if (NULL == _FileSavePath)
	{
		ERROR_LOG("_FileSavePath is null pointer.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("_ConvID=%s,_TranID=%s,_FileSavePath=%s",_ConvID,_TranID,_FileSavePath);

	return UCIMMgr::Instance().AcceptFile(_ConvID,_TranID,_FileSavePath);

}

int __UC_SDK_CALL UC_SDK_CancelFile(const char* _ConvID,const char* _TranID)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if (NULL == _ConvID)
	{
		ERROR_LOG("_ConvID is null pointer.");
		return UC_SDK_InvalidPara;
	}
	if (NULL == _TranID)
	{
		ERROR_LOG("_TranID is null pointer.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG("_ConvID=%s,_TranID=%s",_ConvID,_TranID);
	return UCIMMgr::Instance().CancelFile(_ConvID,_TranID);
}

int __UC_SDK_CALL UC_SDK_RejectFile(const char* _ConvID,const char* _TranID)
{
	INFO_TRACE("");
	CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	if (NULL == _ConvID)
	{
		ERROR_LOG("_ConvID is null pointer.");
		return UC_SDK_InvalidPara;
	}
	if (NULL == _TranID)
	{
		ERROR_LOG("_TranID is null pointer.");
		return UC_SDK_InvalidPara;
	}
	INFO_LOG(_ConvID,_TranID);

	return UCIMMgr::Instance().RejectFile(_ConvID,_TranID);

}

 int __UC_SDK_CALL UC_SDK_SetCallTransEventCallBack(CallTransEventCB CallTransCallBack)
 {
	 INFO_TRACE("");
	 CHECK_INIT_RETURN(isInit,UC_SDK_NotInit);
	 if (NULL == CallTransCallBack)
	 {
		 ERROR_LOG("CallTransCallBack is null pointer.");
		 return UC_SDK_InvalidPara;
	 }
	 INFO_LOG("CallTransCallBack=0x%x",CallTransCallBack);

	 return UCCallMgr::Instance().SetCallTransEventCB(CallTransCallBack);

 }
