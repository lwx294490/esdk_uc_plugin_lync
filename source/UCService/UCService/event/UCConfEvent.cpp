#include "StdAfx.h"
#include "Log.h"
#include "UCConfEvent.h"
#include "UCConfMgr.h"
#include "UCRegMgr.h"
#include "UCEventMgr.h"
#include "UCGroupMgr.h"
#include "UCCallConnectEvent.h"
#include "UCCallCloseEvent.h"

UCConfEvent::UCConfEvent(void):m_pBody(NULL)
{
}

UCConfEvent::~UCConfEvent(void)
{
}
bool UCConfEvent::DoHandle(void)
{
	DEBUG_TRACE("");
	switch(m_msgid)
	{
	case CALL_E_EVT_SERVERCONF_CREATE_RESULT://创建会议成功
		{			
			CALL_S_CONF_CREATE_RESULT* pResult = (CALL_S_CONF_CREATE_RESULT*)m_pBody;
			if(pResult->ulResult == TUP_SUCCESS)
			{
				INFO_LOG("%s create conference success.",UCRegMgr::Instance().GetSelfAccount().c_str());
				//通知上层会议接通
				UCCallConnectEvent* pEvent = new UCCallConnectEvent;
				CALL_S_CALL_INFO* pInfo = new CALL_S_CALL_INFO;
				pInfo->stCallStateInfo.enCallType = CALL_E_CALL_TYPE_IPAUDIO;
				pEvent->SetPara(CALL_E_EVT_CALL_CONNECTED,0,0,(TUP_VOID*)pInfo);
				if(pEvent->DoHandle())
				{
					//增加会议成员
					UCConfMgr::Instance().AddConfMember();
				}
				SAFE_DELETE(pEvent);
			}
			else
			{				
				//通知call模块 创建会议失败
				ERROR_LOG("%s create conference failed.",UCRegMgr::Instance().GetSelfAccount().c_str());
			}			
			SAFE_DELETE(pResult);
		}
		break;
	case CALL_E_EVT_SERVERCONF_CONNECT_RESULT:
		{
			CALL_S_CONF_CONNECT_RESULT *pInfo = (CALL_S_CONF_CONNECT_RESULT*)m_pBody;
			if(pInfo->ulResult == TUP_SUCCESS)
			{
				INFO_LOG("%s join conference success.",UCRegMgr::Instance().GetSelfAccount().c_str());
			}
			else
			{
				ERROR_LOG("chairman %s join conference failed.",UCRegMgr::Instance().GetSelfAccount().c_str());
			}
			SAFE_DELETE(pInfo);
		}
		break;
	case CALL_E_EVT_SERVERCONF_REFRESHLIST:
		{
			std::string strGroupID = UCConfMgr::Instance().GetGroupID();

			CALL_S_CONF_MEMBER* pMem = (CALL_S_CONF_MEMBER*)m_pBody;
			TUP_UINT32 uiMemberSize = m_param2;
			for(TUP_UINT32 i=0;i<uiMemberSize;i++)
			{
				STConfParam item;
				INFO_LOG("REFRESHLIST:number=[%s],enState=%d",pMem[i].acAttendeeNumber,pMem[i].enState);		

				IM_S_USERINFO targetUserInfo;
				if(GetTargetUserInfo(pMem[i].acAttendeeNumber,targetUserInfo))
				{
					item.memType = UC_ACCOUNT;
					strcpy_s(item.ucAcc,STRING_LENGTH,targetUserInfo.account);
				}
				else
				{	
					item.memType = UC_IPPHONE;
					strcpy_s(item.ucAcc,STRING_LENGTH,pMem[i].acAttendeeNumber);
				}
				if(pMem[i].enState == CALL_E_CONF_ATTENDEE_INVITING)
				{	
					item.memStatus = CONF_MEM_INVITING;
				}
				else if(pMem[i].enState == CALL_E_CONF_ATTENDEE_INCONF)
				{
					item.memStatus = CONF_MEM_INCONF;
					if(pMem[i].ulRight != 1)
					{
						item.memStatus = CONF_MEM_MUTE;
					}
					else
					{
						item.memStatus = CONF_MEM_UnMute;
					}
				}
				else/* if(pMem[i].enState == CALL_E_CONF_ATTENDEE_INVITE_FAIL)*/
				{
					if(item.memType == UC_ACCOUNT)
					{
						if(UCGroupMgr::Instance().IsInGroupUCMember(strGroupID,item.ucAcc))
						{							
							item.memStatus = CONF_MEM_HANGUP;
						}
						else
						{
							item.memStatus = CONF_MEM_DEL;
						}

					}
					else
					{
						if(UCGroupMgr::Instance().IsInGroupPhoneMember(strGroupID,item.ucAcc))
						{							
							item.memStatus = CONF_MEM_HANGUP;
						}
						else
						{
							item.memStatus = CONF_MEM_DEL;
						}
					}
				}
				
				UCConfMgr::Instance().NotifyConfUI(item);
			}
			SAFE_DELETE(pMem);
		}
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_SUCCESS:
		{
			std::string strGroupID;

			TUP_CHAR* pNum = (TUP_CHAR*)m_pBody;
			if(NULL == pNum)
			{
				ERROR_LOG("pNum is NULL");
				return false;
			}
			STConfParam item;
			item.memStatus = CONF_MEM_INCONF;
			IM_S_USERINFO targetUserInfo;
			if(GetTargetUserInfo(pNum,targetUserInfo))
			{
				item.memType = UC_ACCOUNT;
				strcpy_s(item.ucAcc,STRING_LENGTH,targetUserInfo.account);
				INFO_LOG("[%s][%s] join conf success.",targetUserInfo.account,pNum);
			}
			else
			{	
				item.memType = UC_IPPHONE;
				strcpy_s(item.ucAcc,STRING_LENGTH,pNum);
				INFO_LOG("[%s] join conf success.",pNum);
			}
			UCConfMgr::Instance().NotifyConfUI(item);
			SAFE_DELETE_ARRAY(pNum);
		}
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_FAILED:
		{
			std::string strGroupID = UCConfMgr::Instance().GetGroupID();

			TUP_CHAR* pNum = (TUP_CHAR*)m_pBody;
			if(NULL == pNum)
			{
				ERROR_LOG("pNum is NULL");
				return false;
			}
			STConfParam item;
			
			IM_S_USERINFO targetUserInfo;
			if(GetTargetUserInfo(pNum,targetUserInfo))
			{
				item.memType = UC_ACCOUNT;
				strcpy_s(item.ucAcc,STRING_LENGTH,targetUserInfo.account);
				if(UCGroupMgr::Instance().IsInGroupUCMember(strGroupID,item.ucAcc))
				{
					item.memStatus = CONF_MEM_HANGUP;
				}
				else
				{
					item.memStatus = CONF_MEM_DEL;
				}
				INFO_LOG("[%s][%s] join conf failed",targetUserInfo.account,pNum);
			}
			else
			{	
				item.memType = UC_IPPHONE;
				strcpy_s(item.ucAcc,STRING_LENGTH,pNum);
				if(UCGroupMgr::Instance().IsInGroupPhoneMember(strGroupID,item.ucAcc))
				{
					item.memStatus = CONF_MEM_HANGUP;
				}
				else
				{
					item.memStatus = CONF_MEM_DEL;
				}
				INFO_LOG("[%s] join conf failed",pNum);
			}
			UCConfMgr::Instance().NotifyConfUI(item);
			SAFE_DELETE_ARRAY(pNum);
		}
		break;
	}
	m_pBody  = NULL;
	return true;
}

void UCConfEvent::SetPara(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	m_msgid = msgid;
	m_param1 = param1;
	m_param2 = param2;
	m_pBody = pBody;
}
