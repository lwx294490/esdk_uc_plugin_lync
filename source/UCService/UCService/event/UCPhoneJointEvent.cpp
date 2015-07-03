#include "StdAfx.h"
#include "Log.h"
#include "UCPhoneJointEvent.h"
#include "UCCallConnectEvent.h"
#include "UCCallCloseEvent.h"
#include "UCEventMgr.h"
#include "UCConfigMgr.h"
#include "UCRegMgr.h"


UCPhoneJointEvent::UCPhoneJointEvent(void) 
{
}

UCPhoneJointEvent::~UCPhoneJointEvent(void)
{
}
bool UCPhoneJointEvent::DoHandle(void)
{
	DEBUG_TRACE("");

	CALL_S_JOINT_CMD_INFOS* pNotifyInfo = (CALL_S_JOINT_CMD_INFOS*)m_pBody;
	if(NULL == pNotifyInfo)
	{
		ERROR_LOG("----pNotifyInfo is NULL.");
		return false;
	}
	switch (m_EventID)
	{
		case CALL_E_EVT_TO_UI_JOINT_START:
			{
				if (!pNotifyInfo->ulResult)
				{
					ConfigMgr::Instance().NotifyPJUI(STATUS_START_SUCC);

					//////2015-05-05 by c00327158  /将话机联动信息保存下来（服务器及本地）/////
					ConfigMgr::Instance().SaveUserConfig(SETTING_ACTIVEDEVICE_IPPHONE,PhoneDevice);
					std::string m_path = ConfigMgr::Instance().GetConfigPath();
					if (!::WritePrivateProfileStringA("UCService","activedevice","ipphone",m_path.c_str()))
					{
						ERROR_LOG("----WriteProfileString ipphone failed.");
					}
					
					//////将话机联动信息保存下来/////
				} 
				else
				{
					ConfigMgr::Instance().NotifyPJUI(STATUS_START_FAILED);
					std::string m_path = ConfigMgr::Instance().GetConfigPath();
					if(!::WritePrivateProfileStringA("UCService","activedevice","pc",m_path.c_str()))
					{
						ERROR_LOG("----WriteProfileString PC failed");
					}
				}
				
			}
			break;
		case CALL_E_EVT_TO_UI_JOINT_CLOSE:
			{
				///////2015-05-07  by c00327158 ////解决话机联动状态退出时会弹出对话框提示退出联动状态/////////
				if (!UCRegMgr::Instance().m_bLogOutFlag)
				{
					if (!pNotifyInfo->ulResult)
					{
						ConfigMgr::Instance().NotifyPJUI(STATUS_STOP_SUCC);

						/////2015-05-05 by c00327158  清空话机联动记录信息//////
						ConfigMgr::Instance().SaveUserConfig(SETTING_ACTIVEDEVICE_IPPHONE,"");
						std::string m_path = ConfigMgr::Instance().GetConfigPath();
						if(!::WritePrivateProfileStringA("UCService","activedevice","pc",m_path.c_str()))
						{
							ERROR_LOG("----WriteProfileString PC failed");
						}
						/////清空话机联动记录信息//////
					} 
					else
					{
						ConfigMgr::Instance().NotifyPJUI(STATUS_STOP_FAILED);
						///////默认PC端通信////////////
						std::string m_path = ConfigMgr::Instance().GetConfigPath();
						if(!::WritePrivateProfileStringA("UCService","activedevice","pc",m_path.c_str()))
						{
							ERROR_LOG("----WriteProfileString PC failed");
						}
					}
				}

			}
			break;
		case CALL_E_EVT_TO_UI_JOINT_ONHOOK:
			{
				CALL_S_CALL_INFO *pNotify = new CALL_S_CALL_INFO;
				strcpy_s(pNotify->stCallStateInfo.acTelNum,CALL_D_MAX_LENGTH_NUM,pNotifyInfo->acCallNum);
				UCCallCloseEvent* pEvent = new UCCallCloseEvent;
				pEvent->SetPara(CALL_E_EVT_CALL_ENDED,pNotifyInfo->ulCallID,pNotifyInfo->ulConfID,(TUP_VOID*)pNotify);
				CUCEventMgr::Instance().PushEvent(pEvent);
			}
			break;
		case CALL_E_EVT_TO_UI_JOINT_OUTGOING:
			{
				////联动话机呼出消息/////
			}
			break;
		case CALL_E_EVT_TO_UI_JOINT_ESTABLISHED:
			{
				//联动接通
				//通知上层会议接通
				UCCallConnectEvent* pEvent = new UCCallConnectEvent;
				CALL_S_CALL_INFO* pInfo = new CALL_S_CALL_INFO;
				pInfo->stCallStateInfo.enCallType = CALL_E_CALL_TYPE_IPAUDIO;
				pEvent->SetPara(CALL_E_EVT_CALL_CONNECTED,pNotifyInfo->ulCallID,pNotifyInfo->ulConfID,(TUP_VOID*)pInfo);
				CUCEventMgr::Instance().PushEvent(pEvent);				
			}
			break;
		default:
			{
				ERROR_LOG("----m_EventID is invalid");
				return false;
			}
	}

	SAFE_DELETE(pNotifyInfo);

	return true;
}
void UCPhoneJointEvent::SetPara(TUP_UINT32 eventID, void *body)
{
	m_EventID = eventID;
	m_pBody = body;
}
