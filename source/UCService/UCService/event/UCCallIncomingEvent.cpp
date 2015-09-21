#include "StdAfx.h"
#include "Log.h"
#include "UCCallIncomingEvent.h"
#include "UCCallMgr.h"
#include "UCConfMgr.h"
#include "UCPlayMgr.h"
#include "Group.h"
#include "UCGroupMgr.h"
#include "UCRegMgr.h"

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
			////////DTS2015071401729 by c00327158 增加话机拨打软终端时话机端听到回铃音///////
			if (TUP_SUCCESS != tup_call_alerting_call(pInfo->stCallStateInfo.ulCallID))
			{
				ERROR_LOG("tup_call_alerting_call Failed");
			}
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
			//////重新呼叫方式入会的，重新创建本地群组//////
			std::string m_strGroupID(pInfo->acGroupUri);
			Group* GroupBean = UCGroupMgr::Instance().GetGroupByID(m_strGroupID);
			if(NULL == GroupBean)
			{
				IM_S_IMGROUPINFO m_infoArg = {0};
				TUP_RESULT tRet = tup_im_getfixedgroupdetail(pInfo->acGroupUri,&m_infoArg);
				//////创建本地群组/////
				Group* pGroup = new Group;
				pGroup->m_strOwner = m_infoArg.owner;
				pGroup->m_strGroupName = m_infoArg.name;
				pGroup->m_strGroupID = m_infoArg.id;
				UCGroupMgr::Instance().AddGroupINGrouplist(m_infoArg.id,pGroup);
                ////增加群组成员//////
				IM_S_REQUESTIMGROUPMEMBERS_ARG arg={0};
				IM_S_GROUPUSERLIST ack={0};
				arg.isSyncAll = TUP_TRUE;
				strcpy_s(arg.groupID, IM_D_GROUPID_LENGTH, m_strGroupID.c_str());
				strcpy_s(arg.timpstamp,IM_D_MAX_TIMESTAMP_LENGTH,"19000000000000");
				//只能查询UC账户
				 tRet = tup_im_getfixedgroupmembers(&arg,&ack);
				if(tRet != TUP_SUCCESS)
				{
					ERROR_LOG("----tup_im_getfixedgroupmembers failed.");
					return false;		
				}

                TUP_S_LIST* list =  ack.memberInfo;
				while(list != NULL)
				{
					IM_S_GroupUserInfo* groupUser = (IM_S_GroupUserInfo*)list->data;
					if(NULL != groupUser)
					{
						STConfParam item;
						std::string strAccount = groupUser->userInfo.account;
						INFO_LOG("----GroupID:%s,GroupMember:%s",m_strGroupID.c_str(),strAccount.c_str());
						if(strAccount.empty())
						{
							ERROR_LOG("----strAccount is empty");
						}
						else
						{		
							if(!UCGroupMgr::Instance().IsInGroupUCMember(m_strGroupID,strAccount))
							{
								item.memStatus = CONF_MEM_ADD;
								item.memType = UC_ACCOUNT;
								strcpy_s(item.ucAcc,STRING_LENGTH,strAccount.c_str());
								UCGroupMgr::Instance().AddLocalUCMember(m_strGroupID,strAccount,groupUser->userInfo.bindNO);
								if(m_strGroupID == UCConfMgr::Instance().GetGroupID())
								{
									(void)UCRegMgr::Instance().SubscribeStatus(strAccount);
									UCConfMgr::Instance().NotifyConfUI(item);
								}
							}						
						}					
					}
					list = list->next;
				}

			}
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
