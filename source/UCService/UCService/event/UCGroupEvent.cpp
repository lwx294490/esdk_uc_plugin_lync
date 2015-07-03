#include "StdAfx.h"
#include "UCConfMgr.h"
#include "UCGroupEvent.h"
#include "UCGroupMgr.h"
#include "UCContactMgr.h"
#include "UCRegMgr.h"
#include "Log.h"

UCGroupEvent::UCGroupEvent(void):m_strGroupID("")
	,m_iGroupEventID(EmptyEvent)
	,m_pBody(NULL)
{
}

UCGroupEvent::~UCGroupEvent(void)
{
}

bool UCGroupEvent::DoHandle(void)
{
	DEBUG_TRACE("");

	if(m_strGroupID.empty())
	{
		ERROR_LOG("----m_strGroupID is empty");
		return false;
	}

	std::string strCurGroupID = UCConfMgr::Instance().GetGroupID();
	INFO_LOG("----CurGroupID:%s,Event GroupID:%s.",strCurGroupID.c_str(),m_strGroupID.c_str());

	IM_S_DISCUSSGROUP_NOTIFY* pInfo = (IM_S_DISCUSSGROUP_NOTIFY*)m_pBody;
	if(NULL == pInfo)
	{
		ERROR_LOG("----GroupInfo is empty");
		return false;
	}

	switch (m_iGroupEventID)
	{
	case E_GroupMemRefresh:
		{
			INFO_LOG("----GroupMemRefresh");
			IM_S_REQUESTIMGROUPMEMBERS_ARG arg={0};
			IM_S_GROUPUSERLIST ack={0};

			arg.isSyncAll = TUP_TRUE;
			strcpy_s(arg.groupID, IM_D_GROUPID_LENGTH, m_strGroupID.c_str());

			//只能查询UC账户
			TUP_RESULT tRet = tup_im_getfixedgroupmembers(&arg,&ack);
			if(tRet != TUP_SUCCESS)
			{
				ERROR_LOG("----tup_im_getfixedgroupmembers failed.");
				return false;		
			}

			UCGroupMgr::Instance().AddLocalGroup(pInfo->groupID,pInfo->groupName,pInfo->adminAccount);

			
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
							if(m_strGroupID == strCurGroupID)
							{
								(void)UCRegMgr::Instance().SubscribeStatus(strAccount);
								UCConfMgr::Instance().NotifyConfUI(item);
							}
						}						
					}					
				}
				list = list->next;
			}

			//同时上报电话用户
			Group* GroupBean = UCGroupMgr::Instance().GetGroupByID(m_strGroupID);
			if(GroupBean != NULL && GroupBean->m_groupPhoneMemList.size() != 0)
			{
				STConfParam item;
				item.memStatus = CONF_MEM_ADD;
				item.memType = UC_IPPHONE;
				PhoneMemList::iterator phoneit = GroupBean->m_groupPhoneMemList.begin();
				PhoneMemList::iterator phoneitEnd = GroupBean->m_groupPhoneMemList.end();
				for(;phoneit!=phoneitEnd;phoneit++)
				{
					std::string strphone = *phoneit;
					strcpy_s(item.ucAcc,STRING_LENGTH,strphone.c_str());
					if(m_strGroupID == strCurGroupID)
					{
						UCConfMgr::Instance().NotifyConfUI(item);
					}
				}
			}
			


			break;
		}
	case E_GroupMemAdd:
		{
			//只有电话用户才走到这边
			INFO_LOG("----GroupMemAdd");
			STConfParam item;
			TUP_S_LIST* pPhone = pInfo->phonelist;
			while(pPhone != NULL)
			{
				IM_S_PHONENUM* pNum = (IM_S_PHONENUM*)(pPhone->data);
				if(NULL != pNum)
				{
					item.memStatus = CONF_MEM_ADD;
					item.memType = UC_IPPHONE;
					strcpy_s(item.ucAcc,STRING_LENGTH,pNum->phoneNum);
					UCGroupMgr::Instance().AddLocalPhoneMember(m_strGroupID,pNum->phoneNum);
					if(m_strGroupID == strCurGroupID)
					{
						UCConfMgr::Instance().NotifyConfUI(item);
					}
				}

				TUP_S_LIST* temppPhone = pPhone;
				pPhone = pPhone->next;	
				SAFE_DELETE(temppPhone);
				SAFE_DELETE(pNum);							
			}	
			break;
		}
	case E_GroupMemDel:
		{
			INFO_LOG("----GroupMemDel");
			STConfParam item;

			if(strlen(pInfo->memberAccount) != 0)
			{
				item.memStatus = CONF_MEM_DEL;
				item.memType = UC_ACCOUNT;
				strcpy_s(item.ucAcc,STRING_LENGTH,pInfo->memberAccount);
				UCGroupMgr::Instance().DelLocalUCMember(m_strGroupID,pInfo->memberAccount);
				if(m_strGroupID == strCurGroupID)
				{
					(void)UCRegMgr::Instance().DisSubscribeStatus(pInfo->memberAccount);
					UCConfMgr::Instance().NotifyConfUI(item);
				}

			}
			else
			{
				TUP_S_LIST* pPhone = pInfo->phonelist;
				while(pPhone != NULL)
				{
					IM_S_PHONENUM* pNum = (IM_S_PHONENUM*)(pPhone->data);
					if(NULL != pNum)
					{
						item.memStatus = CONF_MEM_DEL;
						item.memType = UC_IPPHONE;
						strcpy_s(item.ucAcc,STRING_LENGTH,pNum->phoneNum);
						UCGroupMgr::Instance().DelLocalPhoneMember(m_strGroupID,pNum->phoneNum);
						if(m_strGroupID == strCurGroupID)
						{
							UCConfMgr::Instance().NotifyConfUI(item);
						}
					}
					pPhone = pPhone->next;
				}
			}
	
			break;
		}
	case E_GroupMemNotify:
		{
			INFO_LOG("----GroupMemNotify");
			UCGroupMgr::Instance().NotifyAllMember(m_strGroupID);
			break;
		}
	}
	SAFE_DELETE(pInfo);
	return true;
}
