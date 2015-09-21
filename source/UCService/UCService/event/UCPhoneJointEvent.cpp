#include "StdAfx.h"
#include "Log.h"
#include "UCPhoneJointEvent.h"
#include "UCCallConnectEvent.h"
#include "UCCallCloseEvent.h"
#include "UCEventMgr.h"
#include "UCConfigMgr.h"
#include "UCRegMgr.h"
#include "UCCallMgr.h"
#include "UCConfMgr.h"
#include "UCGroupEvent.h"


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
	
	std::string m_strCallee = pNotifyInfo->acCallNum;
	////�ص���������/////
	PJStatusParam _pjParam = {0};
	memset(_pjParam.ucCalleeAcc,0,STRING_LENGTH);
	memset(_pjParam.CalleeName,0,STRING_LENGTH);
	memset(_pjParam.CalleeNum,0,STRING_LENGTH);
	/////��ѯ��Ϣ/////
	IM_S_QUERY_USERINFO_ARG arg;
	IM_S_QUERY_USERINFO_ACK ack;
	strcpy_s(arg.key, IM_D_MAX_PHONE_LENGTH, m_strCallee.c_str());
	arg.type = IM_E_IMUSERQUERYTYPE_BY_BINDNO;
	TUP_RESULT tRet = tup_im_queryuserinfo(&arg, &ack);
	if (TUP_SUCCESS == tRet)
	{
		///////��ѯ���˻�/////
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)ack.userList->data;
        m_strCallee.clear();
		m_strCallee = pUser->name;
		strcpy_s(_pjParam.CalleeName,STRING_LENGTH,m_strCallee.c_str());
		m_strCallee.clear();
		m_strCallee = pUser->account;
        strcpy_s(_pjParam.ucCalleeAcc,STRING_LENGTH,m_strCallee.c_str());
		m_strCallee.clear();
		m_strCallee = pUser->bindNO;
		strcpy_s(_pjParam.CalleeNum,STRING_LENGTH,m_strCallee.c_str());
		/////DTS2015071006825/ by c00327158 ��Ҫ���滰������ʱ�Է��ĺ��룬������Զ����////
//		UCCallMgr::Instance().InsertUCMember(pUser->account,pUser->bindNO);
	}
	else
	{
		/////û��ѯ���˻�////
		INFO_LOG("%s has no ucAccount",m_strCallee.c_str());
		strcpy_s(_pjParam.CalleeNum,STRING_LENGTH,m_strCallee.c_str());
	   /////DTS2015071006825/ by c00327158 ��Ҫ���滰������ʱ�Է��ĺ��룬������Զ����////
//		UCCallMgr::Instance().InsertPhoneMember(m_strCallee);
	}


	switch (m_EventID)
	{
		case CALL_E_EVT_TO_UI_JOINT_START:
			{
				if (!pNotifyInfo->ulResult)
				{
					_pjParam.PJ_Status = STATUS_START_SUCC;
					//////2015-05-05 by c00327158  /������������Ϣ���������������������أ�/////
					ConfigMgr::Instance().SaveUserConfig(SETTING_ACTIVEDEVICE_IPPHONE,PhoneDevice);
					std::string m_path = ConfigMgr::Instance().GetConfigPath();
					if (!::WritePrivateProfileStringA("UCService","activedevice","ipphone",m_path.c_str()))
					{
						ERROR_LOG("----WriteProfileString ipphone failed.");
					}
					//////������������Ϣ��������/////

					//////DTS2015080406127  ��¼��������״̬����ֹ�������������淢�ʹ�����Ϣ by c00327158 2015.8.5 Start/////
					if (PhoneJont_Sucess == ConfigMgr::Instance().GettPhoneJontStartingStatus() )
					{
						/////���������Ѿ��ɹ�����������汨����Ϣ//////
						INFO_LOG("STATUS_START_SUCC  do not notify UI");
					}
					else
					{
						ConfigMgr::Instance().NotifyPJUI(_pjParam);

						ConfigMgr::Instance().SetPhoneJontStartingStatus(PhoneJont_Sucess);
					}
					//////DTS2015080406127  ��¼��������״̬����ֹ�������������淢�ʹ�����Ϣ by c00327158 2015.8.5 End/////
				} 
				else
				{
					_pjParam.PJ_Status = STATUS_START_FAILED;
					ConfigMgr::Instance().SaveUserConfig(SETTING_ACTIVEDEVICE_IPPHONE,"");
					std::string m_path = ConfigMgr::Instance().GetConfigPath();
					if(!::WritePrivateProfileStringA("UCService","activedevice","pc",m_path.c_str()))
					{
						ERROR_LOG("----WriteProfileString PC failed");
					}
					//////DTS2015080406127  ��¼��������״̬����ֹ�������������淢�ʹ�����Ϣ by c00327158 2015.8.5 Start/////
					if (PhoneJont_Faliled == ConfigMgr::Instance().GettPhoneJontStartingStatus() )
					{
						/////������������ʧ�ܣ���������汨����Ϣ//////
						INFO_LOG("STATUS_START_FAILED  do not notify UI");
					}
					else
					{
						ConfigMgr::Instance().NotifyPJUI(_pjParam);

						ConfigMgr::Instance().SetPhoneJontStartingStatus(PhoneJont_Faliled);
					}
					//////DTS2015080406127  ��¼��������״̬����ֹ�������������淢�ʹ�����Ϣ by c00327158 2015.8.5 End/////
				}
				
			}
			break;
		case CALL_E_EVT_TO_UI_JOINT_CLOSE:
			{
				if (!pNotifyInfo->ulResult)
				{
					_pjParam.PJ_Status = STATUS_STOP_SUCC;
					INFO_LOG("STATUS_STOP_SUCC");
					/////2015-05-05 by c00327158  ��ջ���������¼��Ϣ//////
					ConfigMgr::Instance().SaveUserConfig(SETTING_ACTIVEDEVICE_IPPHONE,"");
					std::string m_path = ConfigMgr::Instance().GetConfigPath();
					if(!::WritePrivateProfileStringA("UCService","activedevice","pc",m_path.c_str()))
					{
						ERROR_LOG("----WriteProfileString PC failed");
					}
					/////��ջ���������¼��Ϣ//////
				} 
				else
				{
					_pjParam.PJ_Status = STATUS_STOP_FAILED;
					INFO_LOG("STATUS_STOP_FAILED");
					///////Ĭ��PC��ͨ��////////////
					ConfigMgr::Instance().SaveUserConfig(SETTING_ACTIVEDEVICE_IPPHONE,"");
					std::string m_path = ConfigMgr::Instance().GetConfigPath();
					if(!::WritePrivateProfileStringA("UCService","activedevice","pc",m_path.c_str()))
					{
						ERROR_LOG("----WriteProfileString PC failed");
					}
				}
				
				if (!UCRegMgr::Instance().m_bLogOutFlag)
				{
					///////2015-05-07  by c00327158 ////�����������״̬�˳�ʱ�ᵯ���Ի�����ʾ�˳�����״̬/////////
					ConfigMgr::Instance().NotifyPJUI(_pjParam);
				}
			}
			break;
		case CALL_E_EVT_TO_UI_JOINT_OFFLINE:
			{
				//////��������
				_pjParam.PJ_Status = STATUS_OFFLINE;
				ConfigMgr::Instance().NotifyPJUI(_pjParam);
				std::string m_path = ConfigMgr::Instance().GetConfigPath();
				if(!::WritePrivateProfileStringA("UCService","activedevice","pc",m_path.c_str()))
				{
					ERROR_LOG("----WriteProfileString PC failed");
				}
				/////���·���������////
				ConfigMgr::Instance().SaveUserConfig(SETTING_ACTIVEDEVICE_IPPHONE,"");
			}
			break;
		case CALL_E_EVT_TO_UI_JOINT_ONLINE:
			{
				/////������������/////
				_pjParam.PJ_Status = STATUS_ONLINE;
				ConfigMgr::Instance().NotifyPJUI(_pjParam);

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
				INFO_LOG("STATUS_JOINT_OUTGOING");
				////��������������Ϣ/////
				_pjParam.PJ_Status = STATUS_JOINT_OUTGOING;
				ConfigMgr::Instance().NotifyPJUI(_pjParam);
				UCCallMgr::Instance().SetCallID(pNotifyInfo->ulCallID);
				UCConfMgr::Instance().SetConfID(pNotifyInfo->ulConfID);
				UCConfMgr::Instance().SetGroupID("");

			}
			break; 
		case CALL_E_EVT_TO_UI_JOINT_ESTABLISHED:
			{	
				//////���������飬�첽��ȡȺ���Ա���ϱ�///////
				if (0 != pNotifyInfo->ulConfID )
				{
					std::string m_strGroupID = UCConfMgr::Instance().GetGroupID();
					IM_S_DISCUSSGROUP_NOTIFY* pInfo = new IM_S_DISCUSSGROUP_NOTIFY;
					memset(pInfo,0,sizeof(IM_S_DISCUSSGROUP_NOTIFY));
					strcpy_s(pInfo->groupID,m_strGroupID.c_str());
					UCGroupEvent* pEvent = new UCGroupEvent;
					pEvent->SetEventID(E_GroupMemNotify);
					pEvent->SetGroupID(m_strGroupID);
					pEvent->SetPara(pInfo);
					CUCEventMgr::Instance().PushEvent(pEvent);
				}
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
