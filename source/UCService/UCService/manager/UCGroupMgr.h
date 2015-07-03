#pragma once
#include "Group.h"

typedef std::map<std::string,Group*> MapGroupList;

class UCGroupMgr
{
public:
	static inline UCGroupMgr& Instance()
	{
		static UCGroupMgr inst;
		return inst;
	}
public:
	int CreatGroup(std::string& groupID);
	int AddUCMemberInGroup(const std::string& groupID,const std::string& strUCAcc);//向服务器发送增加UC成员
	int AddPhoneMemberInGroup(const std::string& groupID,const std::string& strPhone);//向服务器发送增加电话成员
	int DelUCMemberInGroup(const std::string& groupID,const std::string& strUCAcc);//向服务器发送添加UC成员
	int DelPhoneMemberInGroup(const std::string& groupID,const std::string& strPhone);//向服务器发送添加电话成员
	int DelGroup(const std::string& groupID);
	int LeaveGroup(const std::string& groupID);

	
	void AddLocalUCMember(const std::string& groupID,const std::string& strUCAcc,const std::string& strBindNo);//添加本地UC成员
	void AddLocalPhoneMember(const std::string& groupID,const std::string& strPhone);//添加本地电话成员
	void DelLocalUCMember(const std::string& groupID,const std::string& strUCAcc);//删除本地UC成员
	void DelLocalPhoneMember(const std::string& groupID,const std::string& strPhone);//删除本地电话成员
	void DelLocalGroup(const std::string& groupID);//删除本地群组
	void AddLocalGroup(const std::string& groupid,const std::string& groupname,const std::string& groupowner);

	bool IsInGroupUCMember(const std::string& groupID,const std::string& strAccount);
	bool IsInGroupPhoneMember(const std::string& groupID,const std::string& strPhone);

	void ClearGroupMember();
	void ShowGroupInfo();

	void NotifyAllMember(const std::string& strGroupID);
	Group* GetGroupByID(const std::string& strGroupID);
private:
	UCGroupMgr(void);
	~UCGroupMgr(void);
private:
	MapGroupList m_mapGroupList;		//群组列表
};
