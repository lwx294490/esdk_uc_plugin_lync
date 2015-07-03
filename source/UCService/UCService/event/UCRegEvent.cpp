#include "StdAfx.h"
#include "Log.h"
#include "UCRegEvent.h"
#include "UCRegMgr.h"
#include "TimerMgr.h"
#include "UCDeviceMgr.h"
#include "UCHistoryMgr.h"
#include "UCConfigMgr.h"
#include "UCPlayMgr.h"



UCRegEvent::UCRegEvent(void)
{
}

UCRegEvent::~UCRegEvent(void)
{
}

bool UCRegEvent::DoHandle(void)
{
	DEBUG_TRACE("");

	if (NULL == UCRegMgr::OnClientSignInNotifyCB)
	{
		ERROR_LOG("----OnClientSignInNotifyCB is NULL.");
		return false;
	}

	if(m_state == UC__SignedIn)
	{
		/////2015-05-19 by c00327158  �жϵ�½״̬�Ƿ���ȷ////////
		if (UCRegMgr::Instance().GetLoginFlag())
		{
			INFO_LOG("----already login.");
			return true ;
		}
		/////////�ж��Ѿ���½������£���������ʼ������//////////

		TimerMgrInstance().init(UCRegMgr::OnTime);
		TimerMgrInstance().settimer(HEARTBEAT_TIMER_ID, HEARTBEAT_TIME_SEC);
		UCDeviceMgr::Instance().Init();

		//��ʼ��userdataĿ¼
		std::string path;
		eSDKTool::getCurrentPath(path);
		path.append("\\UserData\\");
		int mkdirRet = eSDKTool::MakeDir(path);
		INFO_LOG("----profile dir created: %d", mkdirRet);
		path.append(UCRegMgr::Instance().GetSelfAccount());
		path.append("\\");
		UCHistoryMgr::Instance().InitUserData(path);
		ConfigMgr::Instance().InitForwardCode();
		ConfigMgr::Instance().InitDNDCode();

		////2015-05-05 by c00327158 �ж��û���һ�ε�½�Ƿ������˻���������Ϣ///////
		std::string ActiceDevice;
		ConfigMgr::Instance().GetUserConfig(SETTING_ACTIVEDEVICE_IPPHONE,ActiceDevice);

		if (PhoneDevice == ActiceDevice)
		{
			ConfigMgr::Instance().SetPhoneJointDevType(IPPhone_Device);
			INFO_LOG("_iDevType=%d",IPPhone_Device);
		}

		UCRegMgr::Instance().SetLoginFlag(true);
		(void)UCPlayMgr::Instance().PlayLogin();

		//��ȡ��һ�����õ��豸
		std::string strDevIndex;
		if(ConfigMgr::Instance().GetUserConfig(SETTING_MEDIA_AUDIOINPUTDEVICE,strDevIndex))
		{
			int iIndex = atoi(strDevIndex.c_str());
			(void)UCDeviceMgr::Instance().SetCurrentMicDev(iIndex);
			strDevIndex.clear();
		}
		if(ConfigMgr::Instance().GetUserConfig(SETTING_MEDIA_AUDIOOUTPUTDEVICE,strDevIndex))
		{
			int iIndex = atoi(strDevIndex.c_str());
			(void)UCDeviceMgr::Instance().SetCurrentSpeakerDev(iIndex);
			strDevIndex.clear();
		}
		if(ConfigMgr::Instance().GetUserConfig(SETTING_MEDIA_VIDEODEVICE,strDevIndex))
		{
			int iIndex = atoi(strDevIndex.c_str());
			(void)UCDeviceMgr::Instance().SetCurrentVideoDev(iIndex);
			strDevIndex.clear();
		}

		INFO_LOG("----Login success.");
	
	}
	else
	{
		TimerMgrInstance().killtimer(HEARTBEAT_TIMER_ID);
		TimerMgrInstance().uninit();
		UCRegMgr::Instance().SetLoginFlag(false);
		WARN_LOG("----Login failed.");
	}
	INFO_LOG("----Enter OnClientSignInNotifyCB");
	INFO_LOG("----state=%d,desc=%s",m_state,m_stateDesc.c_str());
	UCRegMgr::OnClientSignInNotifyCB(m_state,m_stateDesc.c_str());
	INFO_LOG("----Leave OnClientSignInNotifyCB");
	return true;
}


