#include "StdAfx.h"
#include "NotifyCallBack.h"
#include "Log.h"
#include "UCEventMgr.h"
#include "UCRegEvent.h"
#include "UCCallConnectEvent.h"
#include "UCCallIncomingEvent.h"
#include "UCCallCloseEvent.h"
#include "UCCallVideoEvent.h"
#include "UCConfEvent.h"
#include "UCStatusChangeEvent.h"
#include "UCFileTransEvent.h"
#include "UCIMRecvEvent.h"
#include "UCPhoneJointEvent.h"
#include "UCCallReservedEvent.h"
#include "UCCallTransEvent.h"
#include "UCGroupEvent.h"
#include "UCPlayMgr.h"
#include "UCCallMgr.h"
#include "UCConfMgr.h"
#include "UCGroupMgr.h"
#include "UCRegMgr.h"
#include "UCConfigMgr.h"


CNotifyCallBack::CNotifyCallBack(void)
{
}

CNotifyCallBack::~CNotifyCallBack(void)
{
}
TUP_BOOL CNotifyCallBack::IMNotify(IM_E_EVENT_ID eventID, void *body)
{
	INFO_LOG("IMEventID=%d,body=0x%x",eventID,body);
	switch(eventID)
	{	
	case IM_E_EVENT_IM_HEARTBEAT_NOTIFY:
		{
			INFO_LOG("receive heartbeat success.");
			UCGroupMgr::Instance().ShowGroupInfo();
			UCConfMgr::Instance().ShowConfInfo();
			UCCallMgr::Instance().ShowCallInfo();
		}
		break;
	case IM_E_EVENT_IM_LOGOUT_NOTIFY:
		{
			INFO_LOG("IM_E_EVENT_IM_LOGOUT_NOTIFY.");
			//log out
			IM_S_LOGOUT_NOTIFY* notify = (IM_S_LOGOUT_NOTIFY*)body;
			if(notify!=NULL && notify->LogOutRet == TUP_TRUE)
			{
				UCRegEvent* pEvent = new UCRegEvent();
				pEvent->m_state = UC__SignedFailed;
				pEvent->m_stateDesc = LOGOUT_OK;
				CUCEventMgr::Instance().PushEvent(pEvent);
			}//lint !e429
		}
		break;
	case IM_E_EVENT_IM_ADDFRIEND_NOTIFY:
		{
			INFO_LOG("IM_E_EVENT_IM_ADDFRIEND_NOTIFY.");
		}	
		break;
	case IM_E_EVENT_IM_KICKOUT_NOTIFY:
		{	
			INFO_LOG("IM_E_EVENT_IM_KICKOUT_NOTIFY.");			
			IM_S_KICKOUT_NOTIFY* notify = (IM_S_KICKOUT_NOTIFY*)body;
			if(notify!=NULL)
			{				
				if(notify->exitFlag == IM_E_EXITSTATUS_NORMALOFFLINE)
				{
					//kicked out					
					UCRegEvent* pEvent = new UCRegEvent();
					pEvent->m_state = UC__KickOut;
					pEvent->m_stateDesc = ACC_KICKED;
					CUCEventMgr::Instance().PushEvent(pEvent);
				}//lint !e429
				else if(notify->exitFlag == IM_E_EXITSTATUS_PAUSEOFFLINE)
				{
					//账号暂停
					UCRegEvent* pEvent = new UCRegEvent();
					pEvent->m_state = UC__SignedFailed;
					pEvent->m_stateDesc = NEED_ACTIVE;
					CUCEventMgr::Instance().PushEvent(pEvent);
				}//lint !e429
				else
				{
					//账号已过期
					UCRegEvent* pEvent = new UCRegEvent();
					pEvent->m_state = UC__SignedFailed;
					pEvent->m_stateDesc = NEED_ACTIVE;
					CUCEventMgr::Instance().PushEvent(pEvent);
				}//lint !e429
			}
		}
		break;
	case IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY:
		{
			INFO_LOG("IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY.");
			IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)body;
			TUP_S_LIST* pphonelist = pNotify->phonelist;
			if(pphonelist == NULL)
			{
				IM_S_DISCUSSGROUP_NOTIFY* pInfo = new IM_S_DISCUSSGROUP_NOTIFY;
				memcpy(pInfo,pNotify,sizeof(IM_S_DISCUSSGROUP_NOTIFY));
				UCGroupEvent* pEvent = new UCGroupEvent;
				INFO_LOG("UC[%s] Enter Group[%s]",pInfo->memberAccount,pInfo->groupID);
				pEvent->SetGroupID(pNotify->groupID);
				pEvent->SetEventID(E_GroupMemRefresh);
				pEvent->SetPara((TUP_VOID*)pInfo);
				CUCEventMgr::Instance().PushEvent(pEvent);
			}//lint !e429
			else
			{
				while(pphonelist != NULL)
				{
					IM_S_PHONENUM* pNum = (IM_S_PHONENUM*)(pphonelist->data);
					INFO_LOG("PHONE[%s] Enter Group[%s]",pNum->phoneNum,pNotify->groupID);
					IM_S_DISCUSSGROUP_NOTIFY* pInfo = new IM_S_DISCUSSGROUP_NOTIFY;
					memcpy(pInfo,pNotify,sizeof(IM_S_DISCUSSGROUP_NOTIFY));
					TUP_S_LIST* tempphonelist = new TUP_S_LIST;
					pInfo->phonelist = tempphonelist;
					IM_S_PHONENUM* pPhone = new IM_S_PHONENUM;
					memcpy(pPhone,pNum,sizeof(IM_S_PHONENUM));
					tempphonelist->next = NULL;
					tempphonelist->data = (TUP_VOID *)pPhone;

					UCGroupEvent* pEvent = new UCGroupEvent;
					pEvent->SetGroupID(pNotify->groupID);
					pEvent->SetEventID(E_GroupMemAdd);
					pEvent->SetPara((TUP_VOID*)pInfo);
					CUCEventMgr::Instance().PushEvent(pEvent);

					pphonelist = pphonelist->next;
				}//lint !e429
			}
		}//lint !e429
		break;
	case IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY:
		{
			INFO_LOG("IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY.");
			IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)body;
			IM_S_DISCUSSGROUP_NOTIFY* pInfo = new IM_S_DISCUSSGROUP_NOTIFY;
			memcpy(pInfo,pNotify,sizeof(IM_S_DISCUSSGROUP_NOTIFY));

			UCGroupEvent* pEvent = new UCGroupEvent;
			pEvent->SetGroupID(pNotify->groupID);
			pEvent->SetEventID(E_GroupMemDel);
			pEvent->SetPara((TUP_VOID*)pInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case IM_E_EVENT_IM_DISCUSSGROUP_INFOCHANGE_NOTIFY:
		{
			INFO_LOG("IM_E_EVENT_IM_DISCUSSGROUP_INFOCHANGE_NOTIFY.");
			IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)body;
			IM_S_DISCUSSGROUP_NOTIFY* pInfo = new IM_S_DISCUSSGROUP_NOTIFY;
			memcpy(pInfo,pNotify,sizeof(IM_S_DISCUSSGROUP_NOTIFY));
			UCGroupEvent* pEvent = new UCGroupEvent;
			pEvent->SetGroupID(pNotify->groupID);
			pEvent->SetEventID(E_GroupMemRefresh);
			pEvent->SetPara((TUP_VOID*)pInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case IM_E_EVENT_IM_DISCUSSGROUP_WASADDEDTOGROUP_NOTIFY:
		{
			INFO_LOG("IM_E_EVENT_IM_DISCUSSGROUP_WASADDEDTOGROUP_NOTIFY.");
			IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)body;
			IM_S_DISCUSSGROUP_NOTIFY* pInfo = new IM_S_DISCUSSGROUP_NOTIFY;
			memcpy(pInfo,pNotify,sizeof(IM_S_DISCUSSGROUP_NOTIFY));
			UCGroupEvent* pEvent = new UCGroupEvent;
			pEvent->SetGroupID(pNotify->groupID);
			pEvent->SetEventID(E_GroupMemRefresh);
			pEvent->SetPara((TUP_VOID*)pInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;

	case IM_E_EVENT_IM_USERSTATUS_NOTIFY:
		{
			INFO_LOG("IM_E_EVENT_IM_USERSTATUS_NOTIFY.");
			IM_S_USERSTATUS_NOTIFY* pNotify = (IM_S_USERSTATUS_NOTIFY*)body;
			IM_S_USERSTATUS_NOTIFY* pInfo = new IM_S_USERSTATUS_NOTIFY;
			memcpy(pInfo,pNotify,sizeof(IM_S_USERSTATUS_NOTIFY));
			UCStatusChangeEvent* pEvent = new UCStatusChangeEvent();
			pEvent->SetPara(eventID,(void*)pInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case IM_E_EVENT_IM_CODECHAT_NOTIFY:
		{
			INFO_LOG("IM_E_EVENT_IM_CODECHAT_NOTIFY.");
			IM_S_CODECHAT_NOTIFY* pNotify = (IM_S_CODECHAT_NOTIFY*)body;
			IM_S_CODECHAT_NOTIFY* pInfo = new IM_S_CODECHAT_NOTIFY;
			memcpy(pInfo,pNotify,sizeof(IM_S_CODECHAT_NOTIFY));
			UCIMRecvEvent* pEvent = new UCIMRecvEvent();
			pEvent->SetPara(eventID,(void*)pInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);		
		}//lint !e429
		break;
	case IM_E_EVENT_IM_CHATLIST_NOTIFY:
		{
			INFO_LOG("IM_E_EVENT_IM_CHATLIST_NOTIFY.");
		}
		break;
	case IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY: 		/**< 收到文件传输请求	IM_S_P2PFILECHOOSE_NOTIFY*/
		{
			INFO_LOG("IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY.");
			IM_S_P2PFILECHOOSE_NOTIFY* pNotify = (IM_S_P2PFILECHOOSE_NOTIFY*)body;
			IM_S_P2PFILECHOOSE_NOTIFY* pInfo = new IM_S_P2PFILECHOOSE_NOTIFY;
			memcpy(pInfo,pNotify,sizeof(IM_S_P2PFILECHOOSE_NOTIFY));
			UCFileTransEvent * pEvent = new UCFileTransEvent();
			pEvent->SetPara(eventID,(void*)pInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case IM_E_EVENT_IM_FILEPROCESS_NOTIFY:			/**< 文件传输进度通知	IM_S_FILEPROCESS_NOTIFY */
		{
			INFO_LOG("IM_E_EVENT_IM_FILEPROCESS_NOTIFY.");
			IM_S_FILEPROCESS_NOTIFY* pNotify = (IM_S_FILEPROCESS_NOTIFY*)body;
			IM_S_FILEPROCESS_NOTIFY* pInfo = new IM_S_FILEPROCESS_NOTIFY;
			memcpy(pInfo,pNotify,sizeof(IM_S_FILEPROCESS_NOTIFY));
			UCFileTransEvent * pEvent = new UCFileTransEvent();
			pEvent->SetPara(eventID,(void*)pInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
    case IM_E_EVENT_IM_FILESTATISTIC_NOTIFY:			/**< 上报文件信息	    IM_S_P2PFILESTATISTIC_NOTIFY*/
		{
			INFO_LOG("IM_E_EVENT_IM_FILESTATISTIC_NOTIFY.");
			IM_S_P2PFILESTATISTIC_NOTIFY* pNotify = (IM_S_P2PFILESTATISTIC_NOTIFY*)body;
			IM_S_P2PFILESTATISTIC_NOTIFY* pInfo = new IM_S_P2PFILESTATISTIC_NOTIFY;
			memcpy(pInfo,pNotify,sizeof(IM_S_P2PFILESTATISTIC_NOTIFY));
			UCFileTransEvent * pEvent = new UCFileTransEvent();
			pEvent->SetPara(eventID,(void*)pInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY: 	/**< 文件传输开始结果	IM_S_P2PFILE_RESULT_NOTIFY*/
		{
			INFO_LOG("IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY.");
			IM_S_P2PFILE_RESULT_NOTIFY* pNotify = (IM_S_P2PFILE_RESULT_NOTIFY*)body;
			IM_S_P2PFILE_RESULT_NOTIFY* pInfo = new IM_S_P2PFILE_RESULT_NOTIFY;
			memcpy(pInfo,pNotify,sizeof(IM_S_P2PFILE_RESULT_NOTIFY));
			UCFileTransEvent * pEvent = new UCFileTransEvent();
			pEvent->SetPara(eventID,(void*)pInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case IM_E_EVENT_IM_P2PFILE_STOPTRESULT_NOTIFY: 	/**< 文件传输停止结果	IM_S_P2PFILE_RESULT_NOTIFY*/
		{
			INFO_LOG("IM_E_EVENT_IM_P2PFILE_STOPTRESULT_NOTIFY.");
			IM_S_P2PFILE_RESULT_NOTIFY* pNotify = (IM_S_P2PFILE_RESULT_NOTIFY*)body;
			IM_S_P2PFILE_RESULT_NOTIFY* pInfo = new IM_S_P2PFILE_RESULT_NOTIFY;
			memcpy(pInfo,pNotify,sizeof(IM_S_P2PFILE_RESULT_NOTIFY));
			UCFileTransEvent * pEvent = new UCFileTransEvent();
			pEvent->SetPara(eventID,(void*)pInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY:			/**<文件传输停止通知	IM_S_P2PFILESTATISTIC_NOTIFY*/
		{
			INFO_LOG("IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY.");
			IM_S_P2PFILECHOOSE_NOTIFY* pNotify = (IM_S_P2PFILECHOOSE_NOTIFY*)body;
			IM_S_P2PFILECHOOSE_NOTIFY* pInfo = new IM_S_P2PFILECHOOSE_NOTIFY;
			memcpy(pInfo,pNotify,sizeof(IM_S_P2PFILECHOOSE_NOTIFY));
			UCFileTransEvent * pEvent = new UCFileTransEvent();
			pEvent->SetPara(eventID,(void*)pInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case IM_E_EVENT_IM_SENDIMINPUT_NOTIFY:
		{
			INFO_LOG("IM_E_EVENT_IM_SENDIMINPUT_NOTIFY.");
		}
		break;
	default:
		break;
	}
	return TUP_TRUE;
}
TUP_VOID CNotifyCallBack::CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	INFO_LOG("CallEventID=%d,param1=%d,param2=%d,pBody=0x%x",msgid,param1,param2,pBody);
	switch (msgid)
	{
	case CALL_E_EVT_SIPACCOUNT_INFO:
		{
			INFO_LOG("CALL_E_EVT_SIPACCOUNT_INFO.");
			CALL_S_SIP_ACCOUNT_INFO* accountInfo = (CALL_S_SIP_ACCOUNT_INFO*)pBody;
			if(accountInfo ==NULL)
			{
				ERROR_LOG("accountInfo is NULL.");
			}
			else
			{
				INFO_LOG("SIPRegState:%d",accountInfo->enRegState);
				if(CALL_E_REG_STATE_REGISTERED == accountInfo->enRegState)
				{
					UCRegEvent* pEvent = new UCRegEvent();
					pEvent->m_state = UC__SignedIn;
					pEvent->m_stateDesc = "";
					CUCEventMgr::Instance().PushEvent(pEvent);
				}//lint !e429
			}
		}
		break;
	case CALL_E_EVT_CALL_AUTHORIZE_SUCCESS:
		{
			//call reg ok
			INFO_LOG("CALL_E_EVT_CALL_AUTHORIZE_SUCCESS.");
			UCRegEvent* pEvent = new UCRegEvent();
			pEvent->m_state = UC__SignedIn;
			pEvent->m_stateDesc = "";
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_CALL_AUTHORIZE_FAILED:
		{
			//call reg failed
			INFO_LOG("CALL_E_EVT_CALL_AUTHORIZE_FAILED.");
			UCRegEvent* pEvent = new UCRegEvent();
			pEvent->m_state = UC__SignedFailed;
			pEvent->m_stateDesc = "";
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_CALL_STARTCALL_RESULT:
		{
			INFO_LOG("CALL_E_EVT_CALL_STARTCALL_RESULT.");
		}
		break;
	case CALL_E_EVT_CALL_INCOMMING:
		{
			INFO_LOG("CALL_E_EVT_CALL_INCOMMING.");
			//新来电			
			CALL_S_CALL_INFO* pInfo = (CALL_S_CALL_INFO*)pBody;
			if(NULL == pInfo)
			{
				ERROR_LOG("incomming call error!");
				return;
			}
			CALL_S_CALL_INFO *pNotify = new CALL_S_CALL_INFO;
			memcpy(pNotify,pInfo,sizeof(CALL_S_CALL_INFO));
			UCCallIncomingEvent* pEvent = new UCCallIncomingEvent;
			pEvent->SetPara(msgid,param1,param2,(TUP_VOID*)pNotify);
			CUCEventMgr::Instance().PushEvent(pEvent);

		}//lint !e429
		break;
	case CALL_E_EVT_CALL_RINGBACK:
		{
			INFO_LOG("CALL_E_EVT_CALL_RINGBACK.");
			//收到回铃音事件，开始振铃
			(void)UCPlayMgr::Instance().StartPlayRingBack();
		}
		break;
	case CALL_E_EVT_CALL_CONNECTED:
		{
			INFO_LOG("CALL_E_EVT_CALL_CONNECTED.");
			//呼叫接通
			CALL_S_CALL_INFO* pInfo = (CALL_S_CALL_INFO*)pBody;
			if(NULL == pInfo)
			{
				ERROR_LOG("msgid:%d,pInfo is NULL.",CALL_E_EVT_CALL_CONNECTED);
				return;
			}
			CALL_S_CALL_INFO *pNotify = new CALL_S_CALL_INFO;
			memcpy(pNotify,pInfo,sizeof(CALL_S_CALL_INFO));
			UCCallConnectEvent* pEvent = new UCCallConnectEvent;
			pEvent->SetPara(msgid,param1,param2,(TUP_VOID*)pNotify);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_CALL_ENDED:
		{
			INFO_LOG("CALL_E_EVT_CALL_ENDED.");
			//呼叫结束
			CALL_S_CALL_INFO* pInfo = (CALL_S_CALL_INFO*)pBody;
			if(NULL == pInfo)
			{
				ERROR_LOG("msgid:%d,pInfo is NULL.",CALL_E_EVT_CALL_ENDED);
				return;
			}
			CALL_S_CALL_INFO *pNotify = new CALL_S_CALL_INFO;
			memcpy(pNotify,pInfo,sizeof(CALL_S_CALL_INFO));

			UCCallCloseEvent* pEvent = new UCCallCloseEvent;
			pEvent->SetPara(msgid,param1,param2,(TUP_VOID*)pNotify);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_CALL_DESTROY:
		{
			INFO_LOG("CALL_E_EVT_CALL_DESTROY.");
			//呼叫结束
			CALL_S_CALL_INFO* pInfo = (CALL_S_CALL_INFO*)pBody;
			if(NULL == pInfo)
			{
				ERROR_LOG("msgid:%d,pInfo is NULL.",CALL_E_EVT_CALL_DESTROY);
				return;
			}
			CALL_S_CALL_INFO *pNotify = new CALL_S_CALL_INFO;
			memcpy(pNotify,pInfo,sizeof(CALL_S_CALL_INFO));

			UCCallCloseEvent* pEvent = new UCCallCloseEvent;
			pEvent->SetPara(msgid,param1,param2,(TUP_VOID*)pNotify);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_CALL_RTP_CREATED:
		{
			INFO_LOG("CALL_E_EVT_CALL_RTP_CREATED");
		}
		break;
	case CALL_E_EVT_CALL_ADD_VIDEO:
		{
			INFO_LOG("CALL_E_EVT_CALL_ADD_VIDEO.");
			//收到音频转视频请求
			TUP_UINT32 callid = param1;
			UCCallVideoEvent* pEvent = new UCCallVideoEvent;
			pEvent->SetCallid(callid);
			pEvent->SetVideoStatus(CALL_VIDEO_REQ);
			CUCEventMgr::Instance().PushEvent(pEvent);			
		}//lint !e429
		break;
	case CALL_E_EVT_CALL_DEL_VIDEO:
		{
			INFO_LOG("CALL_E_EVT_CALL_DEL_VIDEO.");
			//收到视频转语音请求
			TUP_UINT32 callid = param1;
			UCCallVideoEvent* pEvent = new UCCallVideoEvent;
			pEvent->SetCallid(callid);
			pEvent->SetVideoStatus(CALL_VIDEO_CLOSE);
			CUCEventMgr::Instance().PushEvent(pEvent);			
		}//lint !e429
		break;
	case CALL_E_EVT_CALL_MODIFY_VIDEO_RESULT:
		{
			INFO_LOG("CALL_E_EVT_CALL_MODIFY_VIDEO_RESULT.");
			CALL_S_MODIFY_VIDEO_RESULT* pNotify = (CALL_S_MODIFY_VIDEO_RESULT*)pBody;
			if(NULL == pNotify)
			{
				ERROR_LOG("pNotify is NULL.");
				return;
			}
			if(/*!pNotify->bIsVideo && */pNotify->ulResult == TUP_SUCCESS)
			{
				UCCallVideoEvent* pEvent = new UCCallVideoEvent;
				pEvent->SetCallid(pNotify->ulCallID);
				if (pNotify->bIsVideo)
				{
					pEvent->SetVideoStatus(CALL_VIDEO_CONNECTED);
				}
				else
				{
					pEvent->SetVideoStatus(CALL_VIDEO_CLOSE);

				}
				CUCEventMgr::Instance().PushEvent(pEvent);			
			}//lint !e429
		}
		break;
	case CALL_E_EVT_NET_QUALITY_CHANGE:
		{
			INFO_LOG("CALL_E_EVT_NET_QUALITY_CHANGE.");
		}
		break;
	case CALL_E_EVT_STATISTIC_NETINFO:
		{
			INFO_LOG("CALL_E_EVT_STATISTIC_NETINFO.");
		}
		break;
	case CALL_E_EVT_MICDEV_VOLUME_CHANGE:
		{
			INFO_LOG("CALL_E_EVT_MICDEV_VOLUME_CHANGE.");
		}
		break;
	case CALL_E_EVT_VIDEO_OPERATION:
		{
			INFO_LOG("CALL_E_EVT_VIDEO_OPERATION.");
		}
		break;
	case CALL_E_EVT_VIDEO_STATISTIC_NETINFO:
		{
			INFO_LOG("CALL_E_EVT_VIDEO_STATISTIC_NETINFO.");
		}
		break;
	case CALL_E_EVT_VIDEO_QUALITY:
		{
			INFO_LOG("CALL_E_EVT_VIDEO_QUALITY.");
		}
		break;
	case CALL_E_EVT_SET_IPT_SERVICE_SUCCESS:
		{
			INFO_LOG("CALL_E_EVT_SET_IPT_SERVICE_SUCCESS.");
			UCCallReservedEvent* pEvent = new UCCallReservedEvent;
			pEvent->SetPara(msgid,param1,param2,NULL);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_SET_IPT_SERVICE_FAILED:
		{
			INFO_LOG("CALL_E_EVT_SET_IPT_SERVICE_FAILED.");
			UCCallReservedEvent* pEvent = new UCCallReservedEvent;
			pEvent->SetPara(msgid,param1,param2,NULL);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_SIPACCOUNT_WMI:
		{
			//////留言处理消息///////
			INFO_LOG("CALL_E_EVT_SIPACCOUNT_WMI.");
	//		CALL_S_MSG_WAIT_INFOS *pNotify = (CALL_S_MSG_WAIT_INFOS*)pBody;
			
		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_START:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_START.");
			CALL_S_JOINT_CMD_INFOS* pInfo = (CALL_S_JOINT_CMD_INFOS*)pBody;
			CALL_S_JOINT_CMD_INFOS* pNotifyInfo = new CALL_S_JOINT_CMD_INFOS;
			memcpy(pNotifyInfo,pInfo,sizeof(CALL_S_JOINT_CMD_INFOS));
			UCPhoneJointEvent* pEvent = new UCPhoneJointEvent;
			pEvent->SetPara(msgid,(TUP_VOID*)pNotifyInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);		
		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_CLOSE:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_CLOSE.");
			CALL_S_JOINT_CMD_INFOS* pInfo = (CALL_S_JOINT_CMD_INFOS*)pBody;
			CALL_S_JOINT_CMD_INFOS* pNotifyInfo = new CALL_S_JOINT_CMD_INFOS;
			memcpy(pNotifyInfo,pInfo,sizeof(CALL_S_JOINT_CMD_INFOS));
			UCPhoneJointEvent* pEvent = new UCPhoneJointEvent;
			pEvent->SetPara(msgid,(TUP_VOID*)pNotifyInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);		
		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_ONLINE:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_ONLINE.");
			CALL_S_JOINT_CMD_INFOS* pInfo = (CALL_S_JOINT_CMD_INFOS*)pBody;
			CALL_S_JOINT_CMD_INFOS* pNotifyInfo = new CALL_S_JOINT_CMD_INFOS;
			memcpy(pNotifyInfo,pInfo,sizeof(CALL_S_JOINT_CMD_INFOS));
			UCPhoneJointEvent* pEvent = new UCPhoneJointEvent;
			pEvent->SetPara(msgid,(TUP_VOID*)pNotifyInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_OFFLINE:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_OFFLINE.");
			CALL_S_JOINT_CMD_INFOS* pInfo = (CALL_S_JOINT_CMD_INFOS*)pBody;
			CALL_S_JOINT_CMD_INFOS* pNotifyInfo = new CALL_S_JOINT_CMD_INFOS;
			memcpy(pNotifyInfo,pInfo,sizeof(CALL_S_JOINT_CMD_INFOS));
			UCPhoneJointEvent* pEvent = new UCPhoneJointEvent;
			pEvent->SetPara(msgid,(TUP_VOID*)pNotifyInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}
		break;
	case CALL_E_EVT_TO_UI_JOINT_ACCEPTCALL:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_ACCEPTCALL.");
		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_STARTCALL:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_STARTCALL.");
		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_ONHOOK:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_ONHOOK.");		
		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_OUTGOING:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_OUTGOING.");
			CALL_S_JOINT_CMD_INFOS* pInfo = (CALL_S_JOINT_CMD_INFOS*)pBody;
			CALL_S_JOINT_CMD_INFOS* pNotifyInfo = new CALL_S_JOINT_CMD_INFOS;
			memcpy(pNotifyInfo,pInfo,sizeof(CALL_S_JOINT_CMD_INFOS));
			UCPhoneJointEvent* pEvent = new UCPhoneJointEvent;
			pEvent->SetPara(msgid,(TUP_VOID*)pNotifyInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_HUNGUP:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_HUNGUP.");

		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_ESTABLISHED:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_ESTABLISHED.");
			CALL_S_JOINT_CMD_INFOS* pInfo = (CALL_S_JOINT_CMD_INFOS*)pBody;
			CALL_S_JOINT_CMD_INFOS* pNotifyInfo = new CALL_S_JOINT_CMD_INFOS;
			memcpy(pNotifyInfo,pInfo,sizeof(CALL_S_JOINT_CMD_INFOS));
			//通知上层会议接通//////
			UCCallConnectEvent* m_pEvent = new UCCallConnectEvent;
			CALL_S_CALL_INFO* m_pInfo = new CALL_S_CALL_INFO;
			m_pInfo->stCallStateInfo.enCallType = CALL_E_CALL_TYPE_IPAUDIO;
			m_pEvent->SetPara(CALL_E_EVT_CALL_CONNECTED,pNotifyInfo->ulCallID,pNotifyInfo->ulConfID,(TUP_VOID*)pInfo);
			CUCEventMgr::Instance().PushEvent(m_pEvent);
			/////////通知上层会议接通//////
			UCPhoneJointEvent* pEvent = new UCPhoneJointEvent;
			pEvent->SetPara(msgid,(TUP_VOID*)pNotifyInfo);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_RINGRING:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_RINGRING.");
		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PHONE:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PHONE.");
		}//lint !e429
		break;
	case CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PC:
		{
			INFO_LOG("CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PC.");
		}//lint !e429
		break;
	case CALL_E_EVT_NEW_SERVICE_RIGHT:
		{
			INFO_LOG("CALL_E_EVT_NEW_SERVICE_RIGHT.");
		}//lint !e429
		break;
	case CALL_E_EVT_SERVERCONF_CREATE_RESULT:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_CREATE_RESULT.");
			CALL_S_CONF_CREATE_RESULT* pResult = (CALL_S_CONF_CREATE_RESULT*)pBody;
			if(pResult->ulResult == TUP_SUCCESS)
			{
				UCConfMgr::Instance().SetConfCreateResult(CONF_CREATE_SUCCESS);
				UCConfMgr::Instance().SetChairmainRole(true);
			}
			else
			{
				UCConfMgr::Instance().SetConfCreateResult(CONF_CREATE_FAILED);
			}

			CALL_S_CONF_CREATE_RESULT *pNotify = new CALL_S_CONF_CREATE_RESULT;
			memcpy(pNotify,pResult,sizeof(CALL_S_CONF_CREATE_RESULT));
			UCConfEvent* pEvent = new UCConfEvent;
			pEvent->SetPara(msgid,param1,param2,(TUP_VOID*)pNotify);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_SERVERCONF_CONNECT_RESULT:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_CONNECT_RESULT.");
			//加入会议结果
			CALL_S_CONF_CONNECT_RESULT *pInfo = (CALL_S_CONF_CONNECT_RESULT*)pBody;
			if(NULL == pInfo)
			{
				ERROR_LOG("conf info error.");
				return;
			}
			INFO_LOG("ConnectConf,ConfID=[%d]",pInfo->ulConfID);
			CALL_S_CONF_CONNECT_RESULT *pNotify = new CALL_S_CONF_CONNECT_RESULT;
			memcpy(pNotify,pInfo,sizeof(CALL_S_CONF_CONNECT_RESULT));
			UCConfEvent* pEvent = new UCConfEvent;
			pEvent->SetPara(msgid,param1,param2,(TUP_VOID*)pNotify);
			CUCEventMgr::Instance().PushEvent(pEvent);			
		}//lint !e429
		break;
	case CALL_E_EVT_SERVERCONF_REFRESHLIST:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_REFRESHLIST.");
			//刷新所有与会者
			TUP_UINT32 uiMemberSize = param2;
			CALL_S_CONF_MEMBER* pMem = (CALL_S_CONF_MEMBER*)pBody;
			CALL_S_CONF_MEMBER* pNotify = new CALL_S_CONF_MEMBER[uiMemberSize];
			memcpy(pNotify,pMem,sizeof(CALL_S_CONF_MEMBER)*uiMemberSize);
			UCConfEvent* pEvent = new UCConfEvent;
			pEvent->SetPara(msgid,param1,param2,(TUP_VOID*)pNotify);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_SERVERCONF_INCOMING:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_INCOMING.");
			//会议来电
			CALL_S_CONF_INFO* pInfo = (CALL_S_CONF_INFO*)pBody;
			if(NULL == pInfo)
			{
				ERROR_LOG("conf incomming call error.");
				return;
			}
			INFO_LOG("InComingConf,ConfID=[%d]",pInfo->ulConfID);
			CALL_S_CONF_INFO *pNotify = new CALL_S_CONF_INFO;
			memcpy(pNotify,pInfo,sizeof(CALL_S_CONF_INFO));
			UCCallIncomingEvent* pEvent = new UCCallIncomingEvent;
			pEvent->SetPara(msgid,param1,param2,(TUP_VOID*)pNotify);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_SUCCESS:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_SUCCESS.");
			TUP_CHAR* pNum = (TUP_CHAR*)pBody;
			unsigned int iSize = strlen(pNum);
			TUP_CHAR* pNotify = new TUP_CHAR[iSize+1];
			memset(pNotify,0,iSize+1);
			memcpy(pNotify,pNum,iSize);
			UCConfEvent* pEvent = new UCConfEvent;
			pEvent->SetPara(msgid,param1,param2,(TUP_VOID*)pNotify);
			CUCEventMgr::Instance().PushEvent(pEvent);			
		}//lint !e429
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_FAILED:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_FAILED.");
			TUP_CHAR* pNum = (TUP_CHAR*)pBody;
			unsigned int iSize = strlen(pNum);
			TUP_CHAR* pNotify = new TUP_CHAR[iSize+1];
			memset(pNotify,0,iSize+1);
			memcpy(pNotify,pNum,iSize);
			UCConfEvent* pEvent = new UCConfEvent;
			pEvent->SetPara(msgid,param1,param2,(TUP_VOID*)pNotify);
			CUCEventMgr::Instance().PushEvent(pEvent);		
		}//lint !e429
		break;
	case CALL_E_EVT_SERVERCONF_ADDATTENDEE_RESULT:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_ADDATTENDEE_RESULT.");
		}
		break;
	case CALL_E_EVT_SERVERCONF_SUBJECT:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_SUBJECT.");
		}
		break;
	case CALL_E_EVT_SERVERCONF_CHAIRMAN_NUM:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_CHAIRMAN_NUM.");
		}
		break;
	case CALL_E_EVT_SERVERCONF_MODIFYATTENDEE_RESULT:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_MODIFYATTENDEE_RESULT.");
		}
		break;
	case CALL_E_EVT_SERVERCONF_DROPATTENDEE_RESULT:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_DROPATTENDEE_RESULT.");
		}
		break;
	case CALL_E_EVT_SERVERCONF_END_RESULT:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_END_RESULT.");
		}
		break;
	case CALL_E_EVT_SERVERCONF_ENDED:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_ENDED.");
		}
		break;
	case CALL_E_EVT_SERVERCONF_ATTENDEEQUIT:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_ATTENDEEQUIT.");
		}
		break;
	case CALL_E_EVT_SERVERCONF_ADDRESSOR:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_ADDRESSOR.");
		}
		break;
	case CALL_E_EVT_SERVERCONF_BETRANSFERTOCONF:
		{
			INFO_LOG("CALL_E_EVT_SERVERCONF_BETRANSFERTOCONF.");
			CALL_S_CONF_BETRANSFERTOCONF* pResult = (CALL_S_CONF_BETRANSFERTOCONF*)pBody;
			if(NULL != pResult)
			{
				UCConfMgr::Instance().SetGroupID(pResult->acGroupUri);
				UCCallMgr::Instance().SetConfStart(true);
				UCConfMgr::Instance().SetConfID(pResult->ulConfID);
				UCCallMgr::Instance().SetCallID(pResult->ulCallID);
				/////DTS2015080404109 将已经进入群组的成员上报界面 byc00327158 201508.5 Start//////
				UCGroupMgr::Instance().NotifyAllMember(pResult->acGroupUri);
				/////DTS2015080404109 将已经进入群组的成员上报界面 byc00327158 201508.5 End////////

				IM_S_DISCUSSGROUP_NOTIFY* pInfo = new IM_S_DISCUSSGROUP_NOTIFY;
				memset(pInfo,0,sizeof(IM_S_DISCUSSGROUP_NOTIFY));
				strcpy_s(pInfo->groupID,IM_D_GROUPID_LENGTH,pResult->acGroupUri);
				UCGroupEvent* pEvent = new UCGroupEvent;
				pEvent->SetGroupID(pInfo->groupID);
				pEvent->SetEventID(E_GroupMemRefresh);	
				pEvent->SetPara((TUP_VOID*)pInfo);
				CUCEventMgr::Instance().PushEvent(pEvent);
			}//lint !e429
			else
			{
				ERROR_LOG("CALL_S_CONF_BETRANSFERTOCONF:pResult is NULL");
			}
		}
		break;
	case CALL_E_EVT_SESSION_CODEC:
		{
			INFO_LOG("CALL_E_EVT_SESSION_CODEC.");
		}
		break;
	case CALL_E_EVT_CALL_HOLD_SUCCESS:
		{
			INFO_LOG("CALL_E_EVT_CALL_HOLD_SUCCESS.");
		}
		break;
	case CALL_E_EVT_CALL_HOLD_FAILED:
		{
			ERROR_LOG("CALL_E_EVT_CALL_HOLD_FAILED.");
		}
		break;
	case CALL_E_EVT_CALL_UNHOLD_SUCCESS:
		{
			INFO_LOG("CALL_E_EVT_CALL_UNHOLD_SUCCESS.");
		}
		break;
	case CALL_E_EVT_CALL_UNHOLD_FAILED:
		{
			ERROR_LOG("CALL_E_EVT_CALL_UNHOLD_FAILED.");
		}
		break;
	case CALL_E_EVT_CALL_BLD_TRANSFER_SUCCESS:
	case CALL_E_EVT_CALL_BLD_TRANSFER_FAILED:
	case CALL_E_EVT_CALL_ATD_TRANSFER_SUCCESS:
	case CALL_E_EVT_CALL_ATD_TRANSFER_FAILED:
		{
			INFO_LOG("TRANSFER RESULT.");
			UCCallTransEvent* pEvent = new UCCallTransEvent;
			pEvent->SetPara(msgid,param1,param2,pBody);
			CUCEventMgr::Instance().PushEvent(pEvent);
		}//lint !e429
		break;
	case CALL_E_EVT_CALL_UPATE_REMOTEINFO:
		{
			INFO_LOG("CALL_E_EVT_CALL_UPATE_REMOTEINFO.");
		}
		break;
	case CALL_E_EVT_CALL_SRTP_STATE:
		{
			INFO_LOG("CALL_E_EVT_CALL_SRTP_STATE.");
		}
		break;
	case CALL_E_EVT_CALL_CALL_REINVITED:
		{
			INFO_LOG("CALL_E_EVT_CALL_CALL_REINVITED.");
		}
		break;
	default:
		break;
	}
	return;
}


