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
	int AddUCMemberInGroup(const std::string& groupID,const std::string& strUCAcc);//���������������UC��Ա
	int AddPhoneMemberInGroup(const std::string& groupID,const std::string& strPhone);//��������������ӵ绰��Ա
	int DelUCMemberInGroup(const std::string& groupID,const std::string& strUCAcc);//��������������UC��Ա
	int DelPhoneMemberInGroup(const std::string& groupID,const std::string& strPhone);//�������������ӵ绰��Ա
	int DelGroup(const std::string& groupID);
	int LeaveGroup(const std::string& groupID);

	
	void AddLocalUCMember(const std::string& groupID,const std::string& strUCAcc,const std::string& strBindNo);//��ӱ���UC��Ա
	void AddLocalPhoneMember(const std::string& groupID,const std::string& strPhone);//��ӱ��ص绰��Ա
	void DelLocalUCMember(const std::string& groupID,const std::string& strUCAcc);//ɾ������UC��Ա
	void DelLocalPhoneMember(const std::string& groupID,const std::string& strPhone);//ɾ�����ص绰��Ա
	void DelLocalGroup(const std::string& groupID);//ɾ������Ⱥ��
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
	MapGroupList m_mapGroupList;		//Ⱥ���б�
};
