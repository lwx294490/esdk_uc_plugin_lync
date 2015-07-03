#pragma once
#include <set>
#include <map>

typedef std::set<std::string> PhoneMemList;
typedef std::map<std::string,std::string> UCMemList;

class Group
{
public:
	Group(void);
	virtual ~Group(void);
public:
	std::string m_strGroupID;			//Ⱥ��ID
	std::string m_strGroupName;
	std::string m_strOwner;				
	PhoneMemList m_groupPhoneMemList;	//IP�绰��Ա�б�
	UCMemList m_groupUCMemList;			//UC�˻���Ա�б�
};

