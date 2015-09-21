#include "StdAfx.h"
#include "UCGroupMgr.h"
#include "UCRegMgr.h"
#include "UCConfMgr.h"
#include "Log.h"

const std::string strGroupName = "eSDKDiscussGroup";

UCGroupMgr::UCGroupMgr(void)
{
}

UCGroupMgr::~UCGroupMgr(void)
{
}

int UCGroupMgr::CreatGroup(std::string& groupID )
{
	//创建讨论群组	
	IM_S_IMGROUP_OP_ARG addDgroupArg={0};
	IM_S_ADDIMGROUP_ACK addDGroupAck={0};
	strcpy_s(addDgroupArg.fixedgroupInfo.name,IM_D_MAX_NAME_LENGTH,strGroupName.c_str());
	strcpy_s(addDgroupArg.fixedgroupInfo.owner,IM_D_MAX_ACCOUNT_LENGTH,UCRegMgr::Instance().GetSelfAccount().c_str());
	TUP_RESULT tRet = tup_im_adddiscussiongroup(&addDgroupArg,&addDGroupAck);
	if(tRet != TUP_SUCCESS || addDGroupAck.result == TUP_FALSE)
	{
		ERROR_LOG("tup_im_adddiscussiongroup failed:%d",addDGroupAck.reason);
		return UC_SDK_Failed;
	}

	Group* pGroup = new Group;
	pGroup->m_strOwner = addDgroupArg.fixedgroupInfo.owner;
	pGroup->m_strGroupName = addDgroupArg.fixedgroupInfo.name;
	pGroup->m_strGroupID = addDGroupAck.id;
	m_mapGroupList[addDGroupAck.id] = pGroup;

	groupID = addDGroupAck.id;

	INFO_LOG("Create Group ID = %s",addDGroupAck.id);

	return UC_SDK_Success;

}
int UCGroupMgr::AddUCMemberInGroup(const std::string& strGroupID,const std::string& strUCAccount)
{
	if(strGroupID.empty())
	{
		ERROR_LOG("groupID is empty");
		return UC_SDK_Failed;
	}
	if(strUCAccount.empty())
	{
		ERROR_LOG("strUCAccount is empty");
		return UC_SDK_Failed;
	}

	//添加讨论组成员
	IM_S_ADDIMGROUPMEMBER_ARG AddMemberArg;
	strcpy_s(AddMemberArg.groupID,IM_D_GROUPID_LENGTH,strGroupID.c_str());
	strcpy_s(AddMemberArg.groupName,IM_D_MAX_NAME_LENGTH,strGroupName.c_str());
	strcpy_s(AddMemberArg.account,IM_D_MAX_ACCOUNT_LENGTH,strUCAccount.c_str());

	TUP_RESULT tRet = tup_im_adddiscussiongroupmember(&AddMemberArg);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_adddiscussiongroupmember failed");
	}

	return UC_SDK_Success;
}

int UCGroupMgr::AddPhoneMemberInGroup(const std::string& strGroupID,const std::string& strPhone)
{
	if(strGroupID.empty())
	{
		ERROR_LOG("groupID is empty");
		return UC_SDK_Failed;
	}
	if(strPhone.empty())
	{
		ERROR_LOG("strUCAccount is empty");
		return UC_SDK_Failed;
	}

	int iLength = strPhone.size()+1;

	char* pChPhone = new char[iLength];
	memset(pChPhone,0,iLength);
	strcpy_s(pChPhone,iLength,strPhone.c_str());

	//添加讨论组成员
	IM_S_IMGROUPPHONEMEMBER_OP_ARG AddMemberArg;
	strcpy_s(AddMemberArg.groupID,IM_D_GROUPID_LENGTH,strGroupID.c_str());

	TUP_S_LIST* pPhonelist =new TUP_S_LIST;
	pPhonelist->data = (TUP_VOID *)pChPhone;
	pPhonelist->next = NULL;
	AddMemberArg.phonelist = pPhonelist;
	TUP_RESULT  tRet = tup_im_adddiscussiongroupphonemember(&AddMemberArg);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_adddiscussiongroupmember failed");
	}

	SAFE_DELETE(pPhonelist);
	SAFE_DELETE_ARRAY(pChPhone);

	return UC_SDK_Success;
}

int UCGroupMgr::DelUCMemberInGroup(const std::string& groupID,const std::string& strUCAcc)
{
	IM_S_DELIMGROUPMEMBER_ARG arg;
	strcpy_s(arg.groupID,IM_D_GROUPID_LENGTH,groupID.c_str());
	strcpy_s(arg.account,IM_D_MAX_ACCOUNT_LENGTH,strUCAcc.c_str());

	TUP_RESULT tRet = tup_im_deldiscussiongroupmember(&arg);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_deldiscussiongroupmember failed.");
	}

	return UC_SDK_Success;
}
int UCGroupMgr::DelPhoneMemberInGroup(const std::string& groupID,const std::string& strPhone)
{
	int iLength = strPhone.size()+1;

	char* pChPhone = new char[iLength];
	memset(pChPhone,0,iLength);
	strcpy_s(pChPhone,iLength,strPhone.c_str());

	//删除讨论组成员
	IM_S_IMGROUPPHONEMEMBER_OP_ARG AddMemberArg;
	strcpy_s(AddMemberArg.groupID,IM_D_GROUPID_LENGTH,groupID.c_str());

	TUP_S_LIST* pPhonelist =new TUP_S_LIST;
	pPhonelist->data = (TUP_VOID *)pChPhone;
	pPhonelist->next = NULL;
	AddMemberArg.phonelist = pPhonelist;
	TUP_RESULT tRet = tup_im_deldiscussiongroupphonemember(&AddMemberArg);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_deldiscussiongroupphonemember failed");
	}

	SAFE_DELETE(pPhonelist);
	SAFE_DELETE_ARRAY(pChPhone);
	return UC_SDK_Success;
}

int UCGroupMgr::DelGroup(const std::string& groupID)
{
	//同时删除讨论组
	TUP_BOOL result = TUP_FALSE;
	TUP_RESULT tRet = tup_im_deldiscussiongroup(groupID.c_str(),&result);

	if(tRet != TUP_SUCCESS || result != TUP_TRUE)
	{
		ERROR_LOG("tup_im_deldiscussiongroup failed.");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;

}
int UCGroupMgr::LeaveGroup(const std::string& groupID)
{
	//退出讨论组
	TUP_RESULT tRet = tup_im_leavediscussiongroup(groupID.c_str());
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_leavediscussiongroup failed.");
		return UC_SDK_Failed;
	}	
	return UC_SDK_Success;
}

Group* UCGroupMgr::GetGroupByID(const std::string& strGroupID)
{
	if(strGroupID.empty())
	{
		ERROR_LOG("strGroupID is empty.");
		return NULL;
	}
	MapGroupList::iterator it = m_mapGroupList.find(strGroupID);
	if(it == m_mapGroupList.end())
	{
		return NULL;
	}

	return (*it).second;
}

void UCGroupMgr::AddLocalUCMember(const std::string& groupID,const std::string& strUCAcc,const std::string& strBindNo)
{	
	Group* GroupBean = GetGroupByID(groupID);
	if(NULL == GroupBean)
	{
		ERROR_LOG("AddLocalUCMember failed");
		return;
	}

	GroupBean->m_groupUCMemList[strUCAcc] = strBindNo;

}
void UCGroupMgr::AddLocalPhoneMember(const std::string& groupID,const std::string& strPhone)
{
	Group* GroupBean = GetGroupByID(groupID);
	if(NULL == GroupBean)
	{
		ERROR_LOG("AddLocalPhoneMember failed");
		return;
	}

	GroupBean->m_groupPhoneMemList.insert(strPhone);

}
void UCGroupMgr::DelLocalUCMember(const std::string& groupID,const std::string& strUCAcc)
{
	Group* GroupBean = GetGroupByID(groupID);
	if(NULL == GroupBean)
	{
		ERROR_LOG("DelLocalUCMember failed");
		return;
	}
	GroupBean->m_groupUCMemList.erase(strUCAcc);

}
void UCGroupMgr::DelLocalPhoneMember(const std::string& groupID,const std::string& strPhone)
{
	Group* GroupBean = GetGroupByID(groupID);
	if(NULL == GroupBean)
	{
		ERROR_LOG("DelLocalPhoneMember failed");
		return;
	}
	GroupBean->m_groupPhoneMemList.erase(strPhone);

}

void UCGroupMgr::DelLocalGroup(const std::string& groupID)
{
	Group* GroupBean = GetGroupByID(groupID);
	if(NULL == GroupBean)
	{
		INFO_LOG("No this Group Local");
		return;
	}
	m_mapGroupList.erase(groupID);
	SAFE_DELETE(GroupBean);
}

void UCGroupMgr::AddLocalGroup(const std::string& groupid,const std::string& groupname,const std::string& groupowner)
{
	Group* GroupBean = GetGroupByID(groupid);
	if(NULL != GroupBean)
	{
		INFO_LOG("group[%s] has already been saved",groupid.c_str());
		return;
	}

	Group* pGroup = new Group;
	pGroup->m_strGroupID = groupid;	
	pGroup->m_strGroupName = groupname;
	pGroup->m_strOwner = groupowner;

	m_mapGroupList[groupid] = pGroup;

}

void UCGroupMgr::ShowGroupInfo()
{	
	DEBUG_TRACE("");
	
	std::string strGroupID = UCConfMgr::Instance().GetGroupID();
	Group* GroupBean = GetGroupByID(strGroupID);
	if(NULL == GroupBean)
	{
		ERROR_LOG("ShowDisGroupInfo failed");
		return;
	}


	UCMemList::iterator it = GroupBean->m_groupUCMemList.begin();
	UCMemList::iterator itEnd = GroupBean->m_groupUCMemList.end();
	for(;it!=itEnd;it++)
	{
		std::string strAccount = it->first;
		std::string strBindNo = it->second;
		INFO_LOG("ShowDisGroupInfo:GroupID[%s],UCMember[%s],BindNO[%s]",strGroupID.c_str(),strAccount.c_str(),strBindNo.c_str());
	}
	PhoneMemList::iterator phoneit = GroupBean->m_groupPhoneMemList.begin();
	PhoneMemList::iterator phoneitEnd = GroupBean->m_groupPhoneMemList.end();
	for(;phoneit!=phoneitEnd;phoneit++)
	{
		std::string strphone = *phoneit;
		INFO_LOG("ShowDisGroupInfo:GroupID[%s],PhoneMember[%s]",strGroupID.c_str(),strphone.c_str());
	}
}
void UCGroupMgr::NotifyAllMember(const std::string& strGroupID)
{
	DEBUG_TRACE("");

	std::string strConfGroupID = UCConfMgr::Instance().GetGroupID();
	if(strGroupID != strConfGroupID)
	{
		ERROR_LOG("strConfGroupID=%s,strGroupID=%s",strConfGroupID.c_str(),strGroupID.c_str());
		return;
	}

	Group* GroupBean = GetGroupByID(strGroupID);
	if(NULL == GroupBean)
	{
		ERROR_LOG("NotifyAllMember failed");
		return;
	}

	STConfParam item;

	UCMemList::iterator it = GroupBean->m_groupUCMemList.begin();
	UCMemList::iterator itEnd = GroupBean->m_groupUCMemList.end();
	for(;it!=itEnd;it++)
	{
		std::string strAccount = it->first;
		item.memStatus = CONF_MEM_ADD;
		item.memType = UC_ACCOUNT;
		strcpy_s(item.ucAcc,STRING_LENGTH,strAccount.c_str());
		//DTS2015080403235 已经存在会议中的人，不上报  by c00327158 2015.8.5 Start///////
		if (!UCConfMgr::Instance().IsUCMemberInconf(strAccount))
		{
			UCConfMgr::Instance().NotifyConfUI(item);
		}
		//DTS2015080403235 已经存在会议中的人，不上报  by c00327158 2015.8.5 End///////
		////2015-07-21  byc00327158 上报并获取群组成员状态,解决会议成员状态问题/////
		TUP_S_LIST arg;
		char account[IM_D_MAX_ACCOUNT_LENGTH] = {0};
		strcpy_s(account,IM_D_MAX_ACCOUNT_LENGTH,strAccount.c_str());
		arg.data = account;
		arg.next = NULL;
		tup_im_detectuserstatus(&arg);
	}
	PhoneMemList::iterator phoneit = GroupBean->m_groupPhoneMemList.begin();
	PhoneMemList::iterator phoneitEnd = GroupBean->m_groupPhoneMemList.end();
	for(;phoneit!=phoneitEnd;phoneit++)
	{
		std::string strphone = *phoneit;
		item.memStatus = CONF_MEM_ADD;
		item.memType = UC_IPPHONE;
		strcpy_s(item.ucAcc,STRING_LENGTH,strphone.c_str());
		//DTS2015080403235 已经存在会议中的人，不上报  by c00327158 2015.8.5 Start///////
		if (!UCConfMgr::Instance().IsUCMemberInconf(strphone))
		{
			UCConfMgr::Instance().NotifyConfUI(item);
		}
		//DTS2015080403235 已经存在会议中的人，不上报  by c00327158 2015.8.5 End///////
	}
}
void UCGroupMgr::ClearGroupMember()
{
	INFO_LOG("ClearGroupMember");
	MapGroupList::iterator it =  m_mapGroupList.begin();
	MapGroupList::iterator itEnd =  m_mapGroupList.end();
	Group* pGroupbean = NULL;
	for(;it!=itEnd;it++)
	{
		pGroupbean = (*it).second;
		SAFE_DELETE(pGroupbean);
	}
	m_mapGroupList.clear();
}

bool UCGroupMgr::IsInGroupUCMember(const std::string& groupID,const std::string& strAccount)
{
	Group* GroupBean = GetGroupByID(groupID);
	if(NULL == GroupBean)
	{
		ERROR_LOG("IsInGroupUCMember failed");
		return false;
	}

	if(GroupBean->m_groupUCMemList.find(strAccount) != GroupBean->m_groupUCMemList.end())
	{
		return true;
	}
	return false;
}
bool UCGroupMgr::IsInGroupPhoneMember(const std::string& groupID,const std::string& strPhone)
{
	Group* GroupBean = GetGroupByID(groupID);
	if(NULL == GroupBean)
	{
		ERROR_LOG("IsInGroupPhoneMember failed");
		return false;
	}

	if(GroupBean->m_groupPhoneMemList.find(strPhone) != GroupBean->m_groupPhoneMemList.end())
	{
		return true;
	}
	return false;
}