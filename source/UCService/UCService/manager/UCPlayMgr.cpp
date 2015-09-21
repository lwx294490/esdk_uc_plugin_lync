#include "StdAfx.h"
#include "Log.h"
#include "UCPlayMgr.h"

UCPlayMgr::UCPlayMgr(void):m_tupIncomingHandle(0)
							,m_tupRingBackHandle(0)
							,m_tupHoldCallHandle(0)
{
	try
	{
		eSDKTool::getCurrentPath(m_curPath);
		
	}
	catch(...){}

}

UCPlayMgr::~UCPlayMgr(void)
{
	try
	{
		eSDKTool::getCurrentPath(m_curPath);
		m_tupIncomingHandle = 0;
		m_tupRingBackHandle = 0;
		m_tupHoldCallHandle = 0;
	}
	catch(...){}
}

int UCPlayMgr::PlayLogin(void)
{
	INFO_LOG("Play Login");
	std::string strPlayFile = m_curPath+"\\audio\\log_in.wav";
	TUP_INT32 tupHandle=0;
	TUP_RESULT tRet = tup_call_media_startplay(1,strPlayFile.c_str(),&tupHandle);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_startplay failed.");
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;
}

int UCPlayMgr::StartPlayIncomingCall(void) 
{
	if (m_tupIncomingHandle != 0)
	{
		/////如果回铃音在响直接跳过此步骤/////////
		INFO_LOG("IncomingCall already Ringing");
	}
	else
	{
		//0表示循环播放，其他表示播放次数
		std::string strPlayFile = m_curPath+"\\audio\\In.wav";
		TUP_INT32 tupHandle=0;
		TUP_RESULT tRet = tup_call_media_startplay(0,strPlayFile.c_str(),&tupHandle);
		INFO_LOG("Start PlayIncomingCall,Handle:%d",tupHandle);
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_media_startplay failed.");
			return UC_SDK_Failed;
		}

		m_tupIncomingHandle = tupHandle;
	}
	
	return UC_SDK_Success;
}
int UCPlayMgr::EndPlayIncoming(void) 
{
	INFO_LOG("End PlayIncomingCall,Handle:%d",m_tupIncomingHandle);
	(void)tup_call_media_stopplay(m_tupIncomingHandle);	
	m_tupIncomingHandle = 0;
	return UC_SDK_Success;
}
//播放回保持通话音乐
int UCPlayMgr::StartPlayRingBack(void) 
{
	
	if (m_tupRingBackHandle != 0)
	{
		/////如果回铃音在响直接跳过此步骤/////////
		INFO_LOG("RingBack already Ringing");
	}
	else
	{
		//0表示循环播放，其他表示播放次数
		m_tupRingBackHandle = 0;
		std::string strPlayFile = m_curPath+"\\audio\\RingBack.wav";
		TUP_INT32 tupHandle=0;
		TUP_RESULT tRet = tup_call_media_startplay(0,strPlayFile.c_str(),&tupHandle);
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_media_startplay failed.");
			return UC_SDK_Failed;
		}
		INFO_LOG("Start PlayRingBack,Handle:%d",tupHandle);

		m_tupRingBackHandle = tupHandle;
	}
	return UC_SDK_Success;
}

int UCPlayMgr::EndPlayRingBack(void)
{
	INFO_LOG("End PlayRingBack,Handle:%d",m_tupRingBackHandle);
	(void)tup_call_media_stopplay(m_tupRingBackHandle);
	m_tupRingBackHandle = 0;	
	return UC_SDK_Success;
}

int UCPlayMgr::StartPlayHoldCall(void)
{
	if (m_tupHoldCallHandle != 0)
	{
		/////如果保持呼叫在响直接跳过此步骤/////////
		INFO_LOG("HoldCall already Ringing");
	}
	else
	{
		//0表示循环播放，其他表示播放次数
		m_tupHoldCallHandle =0;
		std::string strPlayFile = m_curPath + "\\audio\\inactive.wav";
		TUP_RESULT tRet = tup_call_media_startplay(0,strPlayFile.c_str(),&m_tupHoldCallHandle);
		INFO_LOG("StartPlayHoldCall,Handle:%d",m_tupHoldCallHandle);
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_media_startplay failed.");
			return UC_SDK_Failed;
		}
	}

	return UC_SDK_Success;

}

int UCPlayMgr::EndPlayHoldCall(void) 
{
	INFO_LOG("EndPlayHoldCall,Handle:%d",m_tupHoldCallHandle);
	(void)tup_call_media_stopplay(m_tupHoldCallHandle);	
	m_tupHoldCallHandle = 0;
	return UC_SDK_Success;
}

