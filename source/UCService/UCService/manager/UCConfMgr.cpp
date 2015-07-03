#include "StdAfx.h"
#include "Log.h"
#include "Group.h"
#include "UCConfMgr.h"
#include "UCContactMgr.h"
#include "UCRegMgr.h"
#include "UCGroupEvent.h"
#include "UCEventMgr.h"
#include "UCPlayMgr.h"
#include "UCGroupMgr.h"


#define CHECK_CONFID_RETURN(interger,ret) if(0 == interger)\
{\
	ERROR_LOG("confid is 0");\
	return ret;\
}

ConfMemberEventCB UCConfMgr::OnConfMemberEventCB=NULL;

UCConfMgr::UCConfMgr(void):m_uiConfID(0)
	,m_strGroupID("")
	,m_strChairManAccount("")
	,m_strChairManBindNo("")
	,m_strCalleeNum("")
	,m_strCalleeAccount("")
	,m_bIsUCAccount(false)
	,m_emRecvConfCreate(CONF_INIT)
{
	try
	{
		m_confPhoneMemList.clear();
		m_confUCMemList.clear();
		m_mapConfStatusDesc[CONF_MEM_INVITING] = "CONF_MEM_INVITING";
		m_mapConfStatusDesc[CONF_MEM_HANGUP] = "CONF_MEM_HANGUP";
		m_mapConfStatusDesc[CONF_MEM_INCONF] = "CONF_MEM_INCONF";
		m_mapConfStatusDesc[CONF_MEM_QUIT] = "CONF_MEM_QUIT";
		m_mapConfStatusDesc[CONF_MEM_MUTE] = "CONF_MEM_MUTE";
		m_mapConfStatusDesc[CONF_MEM_UnMute] = "CONF_MEM_UnMute";
		m_mapConfStatusDesc[CONF_MEM_SPK] = "CONF_MEM_SPK";
		m_mapConfStatusDesc[CONF_MEM_ADD] = "CONF_MEM_ADD";
		m_mapConfStatusDesc[CONF_MEM_DEL] = "CONF_MEM_DEL";
	}
	catch(...)
	{}
}

UCConfMgr::~UCConfMgr(void)
{
	try
	{
		m_strChairManBindNo.clear();
		m_strChairManAccount.clear();
		m_strCalleeNum.clear();
		m_uiConfID = 0;
		m_strGroupID.clear();
		m_confPhoneMemList.clear();
		m_confUCMemList.clear();
		m_mapConfStatusDesc.clear();
	}
	catch(...)
	{}
}

int UCConfMgr::CreateConf(const std::string& groupID,const PhoneMemList& phoneList,const UCMemList& BindNoList,TUP_UINT32& callid)
{
	m_confPhoneMemList.insert(phoneList.begin(),phoneList.end());
	m_confUCMemList.insert(BindNoList.begin(),BindNoList.end());

	TUP_UINT32 uiConfID = 0;
	TUP_UINT32 uiCallID = 0;
	TUP_RESULT tRet = tup_call_serverconf_create(&uiConfID,&uiCallID,groupID.c_str());
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_serverconf_create failed:%d",tRet);
		return UC_SDK_Failed;
	}
	m_uiConfID = uiConfID;
	callid = uiCallID;

	//等待会议创建事件
	m_emRecvConfCreate = CONF_INIT;
	for(;;)
	{
		if(m_emRecvConfCreate == CONF_CREATE_SUCCESS)
		{
			INFO_LOG("Create Conf Success.");
			break;
		}
		if(m_emRecvConfCreate == CONF_CREATE_FAILED)
		{
			ERROR_LOG("Create Conf Failed.");
			return UC_SDK_Failed;
		}
		Sleep(100);
	}

	return UC_SDK_Success;

}
void UCConfMgr::SetCallerInfo(const std::string& calleenum,const std::string& calleeAccount,bool isUCAccount)
{
	m_strCalleeNum = calleenum;
	m_strCalleeAccount = calleeAccount;
	m_bIsUCAccount = isUCAccount;
}
int UCConfMgr::TransCallToConf(const std::string& groupID,const PhoneMemList& phoneList,const UCMemList& BindNoList,TUP_UINT32 callid)
{
	m_confPhoneMemList.insert(phoneList.begin(),phoneList.end());
	m_confUCMemList.insert(BindNoList.begin(),BindNoList.end());

	TUP_UINT32 uiConfID = 0;
	TUP_RESULT tRet = tup_call_serverconf_transferto_conf_non_refer(callid,&uiConfID,groupID.c_str());
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_serverconf_transferto_conf_non_refer failed:%d",tRet);
		return UC_SDK_Failed;
	}
	m_uiConfID = uiConfID;

	//等待会议创建事件
	m_emRecvConfCreate = CONF_INIT;
	for(;;)
	{
		if(m_emRecvConfCreate == CONF_CREATE_SUCCESS)
		{
			INFO_LOG("Trans Call to Conf Success.");
			break;
		}
		if(m_emRecvConfCreate == CONF_CREATE_FAILED)
		{
			ERROR_LOG("Trans Call to Conf Failed.");
			return UC_SDK_Failed;
		}
		Sleep(100);
	}
	return UC_SDK_Success;

}

void UCConfMgr::AddConfMember(void)
{
	TUP_RESULT tRet = TUP_FAIL;

	if(!m_strCalleeNum.empty())
	{
		STConfParam item={0};
		item.memStatus = CONF_MEM_INVITING;
		if(m_bIsUCAccount)
		{			
			item.memType = UC_ACCOUNT;
			strcpy_s(item.ucAcc,STRING_LENGTH,m_strCalleeAccount.c_str());
			//添加讨论组UC成员
			UCGroupMgr::Instance().AddUCMemberInGroup(m_strGroupID,m_strCalleeAccount);
			UCGroupMgr::Instance().AddLocalUCMember(m_strGroupID,m_strCalleeAccount,m_strCalleeNum);

		}
		else
		{
			item.memType = UC_IPPHONE;
			strcpy_s(item.ucAcc,STRING_LENGTH,m_strCalleeNum.c_str());
			//增加讨论群组电话用户
			UCGroupMgr::Instance().AddPhoneMemberInGroup(m_strGroupID,m_strCalleeNum);	
			UCGroupMgr::Instance().AddLocalPhoneMember(m_strGroupID,m_strCalleeNum);
		}
		NotifyConfUI(item);


		tRet = tup_call_serverconf_add_attendee(m_uiConfID,1,m_strCalleeNum.c_str(),m_strCalleeNum.size()+1);
		if(tRet != TUP_SUCCESS)
		{
			WARN_LOG("tup_call_serverconf_add_attendee add %s failed",m_strCalleeNum.c_str());
			item.memStatus = CONF_MEM_DEL;
			NotifyConfUI(item);
		}
	}

	
	//要先加UC用户群组再加电话用户，否则被叫端收不到话机用户的增加消息
	UCMemList::iterator ucit = m_confUCMemList.begin();
	UCMemList::iterator ucitEnd = m_confUCMemList.end();
	for(;ucit != ucitEnd;ucit++)
	{
		std::string strBindNO = (*ucit).second;
		if(strBindNO != m_strCalleeNum)//避免重复邀请
		{		
			std::string strAccount = (*ucit).first;
			STConfParam item;
			item.memStatus = CONF_MEM_INVITING;
			item.memType = UC_ACCOUNT;
			strcpy_s(item.ucAcc,STRING_LENGTH,strAccount.c_str());
			NotifyConfUI(item);

			//添加讨论组UC成员
			UCGroupMgr::Instance().AddUCMemberInGroup(m_strGroupID,strAccount);
			UCGroupMgr::Instance().AddLocalUCMember(m_strGroupID,strAccount,strBindNO);

			tRet = tup_call_serverconf_add_attendee(m_uiConfID,1,strBindNO.c_str(),strBindNO.size()+1);
			if(tRet != TUP_SUCCESS)
			{
				WARN_LOG("tup_call_serverconf_add_attendee add %s:%s failed,reason %d",strAccount.c_str(),strBindNO.c_str(),tRet);
				item.memStatus = CONF_MEM_DEL;
				NotifyConfUI(item);
			}
		}
	}

	std::string strGroup;
	PhoneMemList::iterator it = m_confPhoneMemList.begin();
	PhoneMemList::iterator itEnd = m_confPhoneMemList.end();
	for(;it != itEnd;it++)
	{
		std::string strPhoneNum = *it;
		if(strPhoneNum != m_strCalleeNum)//避免重复邀请
		{
			STConfParam item;
			item.memStatus = CONF_MEM_INVITING;
			item.memType = UC_IPPHONE;
			strcpy_s(item.ucAcc,STRING_LENGTH,strPhoneNum.c_str());
			NotifyConfUI(item);

			//增加讨论群组电话用户
			UCGroupMgr::Instance().AddPhoneMemberInGroup(m_strGroupID,strPhoneNum);	
			UCGroupMgr::Instance().AddLocalPhoneMember(m_strGroupID,strPhoneNum);

			tRet = tup_call_serverconf_add_attendee(m_uiConfID,1,strPhoneNum.c_str(),strPhoneNum.size()+1);
			if(tRet != TUP_SUCCESS)
			{
				WARN_LOG("tup_call_serverconf_add_attendee add %s failed",strPhoneNum.c_str());
				item.memStatus = CONF_MEM_DEL;
				NotifyConfUI(item);
			}
		}		
	}

	//主席也要放到成员列表里面
	m_strChairManAccount = UCRegMgr::Instance().GetSelfAccount();
	m_strChairManBindNo = UCRegMgr::Instance().GetBindNO();
	m_confUCMemList[m_strChairManAccount] = m_strChairManBindNo;

	//清除信息
	m_strCalleeNum.clear();
	m_strCalleeAccount.clear();
	m_bIsUCAccount = false;
}

int UCConfMgr::SetConfMemEventCB(ConfMemberEventCB _confmemberEventCB)const
{
	OnConfMemberEventCB = _confmemberEventCB;
	return UC_SDK_Success;
}
int UCConfMgr::NotifyConfUI(const STConfParam& item)
{	
	INFO_LOG("----NotifyConfUI:ConfID = %d, GroupID = %s,Account = %s, Status= %s.",m_uiConfID,m_strGroupID.c_str(),item.ucAcc,m_mapConfStatusDesc[item.memStatus].c_str());
	if(NULL == OnConfMemberEventCB)
	{
		ERROR_LOG("----OnConfMemberEventCB is NULL");
		return UC_SDK_Failed;
	}
	else
	{
		INFO_LOG("----Enter OnConfMemberEventCB");
		OnConfMemberEventCB(item);
		INFO_LOG("----Leave OnConfMemberEventCB");
	}
	return UC_SDK_Success;
}
void UCConfMgr::ClearConfMember(void)
{
	INFO_LOG("ClearConfMember");
	m_strChairManBindNo.clear();
	m_strChairManAccount.clear();
	m_strCalleeNum.clear();
	m_uiConfID = 0;
	m_strGroupID.clear();
	m_confPhoneMemList.clear();
	m_confUCMemList.clear();
}
int UCConfMgr::LeaveConf(void)
{
	DEBUG_TRACE("");
	
	if(0 == m_uiConfID)
	{	
		return UC_SDK_Success;
	}

	if(m_strChairManAccount == UCRegMgr::Instance().GetSelfAccount())
	{
		TUP_RESULT tRet = tup_call_serverconf_end(m_uiConfID);
		INFO_LOG("EndConf:ConfID=[%d]",m_uiConfID);
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_serverconf_end failed.");
			return UC_SDK_Failed;
		}

		//同时删除讨论组
		(void)UCGroupMgr::Instance().DelGroup(m_strGroupID);
		UCGroupMgr::Instance().DelLocalGroup(m_strGroupID);
	}
	else
	{
		TUP_RESULT tRet = tup_call_serverconf_leave(m_uiConfID);
		INFO_LOG("LeaveConf:ConfID=[%d]",m_uiConfID);
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_serverconf_leave failed.");
			return UC_SDK_Failed;
		}

		//离开讨论组
		(void)UCGroupMgr::Instance().LeaveGroup(m_strGroupID);
		UCGroupMgr::Instance().DelLocalGroup(m_strGroupID);
		
	}

	//清空本地群组数据
	UCGroupMgr::Instance().ClearGroupMember();

	return UC_SDK_Success;

}

int UCConfMgr::AcceptConf(void)
{
	CHECK_CONFID_RETURN(m_uiConfID,UC_SDK_Failed);

	//停止响铃
	(void)UCPlayMgr::Instance().EndPlayIncoming();
	(void)UCPlayMgr::Instance().EndPlayRingBack();

	if(m_strGroupID.empty())
	{
		ERROR_LOG("m_strGroupID is empty.");
		return UC_SDK_Failed;
	}

	//异步获取群组成员并上报
	IM_S_DISCUSSGROUP_NOTIFY* pInfo = new IM_S_DISCUSSGROUP_NOTIFY;
	memset(pInfo,0,sizeof(IM_S_DISCUSSGROUP_NOTIFY));
	strcpy_s(pInfo->groupID,m_strGroupID.c_str());
	UCGroupEvent* pEvent = new UCGroupEvent;
	pEvent->SetEventID(E_GroupMemNotify);
	pEvent->SetGroupID(m_strGroupID);
	pEvent->SetPara(pInfo);
	CUCEventMgr::Instance().PushEvent(pEvent);
	
	TUP_RESULT tRet = tup_call_serverconf_accept(m_uiConfID);
	INFO_LOG("AcceptConf,ConfID=[%d]",m_uiConfID);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_serverconf_accept failed:%d",tRet);
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;
}

int UCConfMgr::RejectConf(void)
{
	CHECK_CONFID_RETURN(m_uiConfID,UC_SDK_Failed);

	//停止响铃
	(void)UCPlayMgr::Instance().EndPlayIncoming();
	(void)UCPlayMgr::Instance().EndPlayRingBack();

	if(m_strGroupID.empty())
	{
		ERROR_LOG("m_strGroupID is empty.");
		return UC_SDK_Failed;
	}

	//离开群组
	(void)UCGroupMgr::Instance().LeaveGroup(m_strGroupID);
	UCGroupMgr::Instance().DelLocalGroup(m_strGroupID);

	TUP_RESULT tRet = tup_call_serverconf_leave(m_uiConfID);
	INFO_LOG("LeaveConf,ConfID:%d.",m_uiConfID);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_serverconf_leave failed.");
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;
}

int UCConfMgr::InviteMemberInConf(EM_MemberType _memberType,const std::string& strAccount)
{
	DEBUG_TRACE("");

	CHECK_CONFID_RETURN(m_uiConfID,UC_SDK_Failed);

	std::string strBindNO;

	STConfParam item;
	TUP_RESULT tRet = TUP_FAIL;
	if(_memberType == UC_IPPHONE)
	{
		strBindNO = strAccount;
		m_confPhoneMemList.insert(strBindNO);

		//增加讨论群组电话用户
		UCGroupMgr::Instance().AddPhoneMemberInGroup(m_strGroupID,strBindNO);	
		UCGroupMgr::Instance().AddLocalPhoneMember(m_strGroupID,strBindNO);

		item.memStatus = CONF_MEM_INVITING;
		item.memType = UC_IPPHONE;
		strcpy_s(item.ucAcc,STRING_LENGTH,strBindNO.c_str());
	}
	else
	{
		IM_S_USERINFO user;
		if(UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(strAccount,user))
		{
			ERROR_LOG("getContactByAccount Error!");
			return UC_SDK_FindUriErr;
		}
		strBindNO = user.bindNO;
		m_confUCMemList[strAccount] = strBindNO;

		(void)UCRegMgr::Instance().SubscribeStatus(strAccount);
		//添加讨论组UC成员
		UCGroupMgr::Instance().AddUCMemberInGroup(m_strGroupID,strAccount);
		UCGroupMgr::Instance().AddLocalUCMember(m_strGroupID,strAccount,strBindNO);

		item.memStatus = CONF_MEM_INVITING;
		item.memType = UC_ACCOUNT;
		strcpy_s(item.ucAcc,STRING_LENGTH,strAccount.c_str());

	}

	UCConfMgr::Instance().NotifyConfUI(item);

	tRet = tup_call_serverconf_add_attendee(m_uiConfID,1,strBindNO.c_str(),strBindNO.size()+1);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_serverconf_add_attendee failed.");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;

	
}

int UCConfMgr::DeleteMemberInCall(EM_MemberType _memberType,const std::string& strAccount)
{
	CHECK_CONFID_RETURN(m_uiConfID,UC_SDK_Failed);

	TUP_RESULT tRet = TUP_FAIL;
	std::string strBindNO;

	//删除讨论组成员
	if(_memberType == UC_IPPHONE)
	{
		strBindNO = strAccount;
		m_confPhoneMemList.erase(strAccount);

		(void)UCGroupMgr::Instance().DelPhoneMemberInGroup(m_strGroupID,strBindNO);
		UCGroupMgr::Instance().DelLocalPhoneMember(m_strGroupID,strBindNO);
	}
	else
	{
		strBindNO = m_confUCMemList[strAccount];
		m_confUCMemList.erase(strAccount);
		(void)UCGroupMgr::Instance().DelUCMemberInGroup(m_strGroupID,strAccount);
		UCGroupMgr::Instance().DelLocalUCMember(m_strGroupID,strAccount);
	}

	tRet = tup_call_serverconf_kick_attendee(m_uiConfID,strBindNO.c_str());
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_serverconf_kick_attendee failed.");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;	
}

int UCConfMgr::ModifyMemberStatusInCall(EM_ConvnerOperateType operateType
											, EM_MemberType _memberType
											, const std::string& strAccount)
{
	CHECK_CONFID_RETURN(m_uiConfID,UC_SDK_Failed);

	TUP_RESULT tRet = TUP_FAIL;
	std::string strBindNO;

	if(_memberType == UC_IPPHONE)
	{
		strBindNO = strAccount;

	}
	else
	{
		strBindNO = m_confUCMemList[strAccount];
	}


	//结束某成员的通话
	if(EndCallMember == operateType)
	{
		tRet = tup_call_serverconf_kick_attendee(m_uiConfID,strBindNO.c_str());
	}
	//重新呼叫某成员
	else if(ReInviteMember == operateType)
	{
		

		STConfParam item;

		//重新加入群组
		if(_memberType == UC_IPPHONE)
		{
			(void)UCGroupMgr::Instance().AddPhoneMemberInGroup(m_strGroupID,strBindNO);
			UCGroupMgr::Instance().AddLocalPhoneMember(m_strGroupID,strBindNO);
			item.memStatus = CONF_MEM_INVITING;
			item.memType = UC_IPPHONE;
			strcpy_s(item.ucAcc,STRING_LENGTH,strBindNO.c_str());
		}
		else
		{
			(void)UCGroupMgr::Instance().AddUCMemberInGroup(m_strGroupID,strAccount);
			UCGroupMgr::Instance().AddLocalUCMember(m_strGroupID,strAccount,strBindNO);
			item.memStatus = CONF_MEM_INVITING;
			item.memType = UC_ACCOUNT;
			strcpy_s(item.ucAcc,STRING_LENGTH,strAccount.c_str());
		}

		UCConfMgr::Instance().NotifyConfUI(item);

		tRet = tup_call_serverconf_add_attendee(m_uiConfID,1,strBindNO.c_str(),strBindNO.size()+1);
	}
	//对某成员静音
	else if(MuteMember == operateType)
	{
		tRet = tup_call_serverconf_modify_right(m_uiConfID,strBindNO.c_str(),0);
	}
	//对某成员取消静音
	else if(UnMuteMember == operateType)
	{
		tRet = tup_call_serverconf_modify_right(m_uiConfID,strBindNO.c_str(),1);
	}
	else
	{
		ERROR_LOG("operateType is invalid.");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}

void UCConfMgr::ShowConfInfo(void)
{
	DEBUG_TRACE("");
	INFO_LOG("ConfInfo:ConfID=%d,GroupID=%s,ChairManAccount=%s,ChairManBindNo=%s,CalleeNum=%s,CalleeAccount=%s",m_uiConfID
		,m_strGroupID.c_str()
		,m_strChairManAccount.c_str()
		,m_strChairManBindNo.c_str()
		,m_strCalleeNum.c_str()
		,m_strCalleeAccount.c_str());
	
}


