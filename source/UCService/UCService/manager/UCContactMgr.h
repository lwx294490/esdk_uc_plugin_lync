#ifndef _UCCONTACT_H
#define _UCCONTACT_H

class UCContactMgr
{
public:
	static inline UCContactMgr& Instance()
	{
		static UCContactMgr inst;
		return inst;
	}
public:
	void Init(void);
	void Uninit(void);
	int getContactByAccount(const std::string& _account, IM_S_USERINFO& _user);
	int getContactByNum(const std::string& _phone, IM_S_USERINFO& _user,IM_E_IMUSERQUERYTYPE _type);
	int getContactList(const std::string& _strSearchKey, int _fromIndex,int _toIndex, STContactList* _pContactList);

private:
	UCContactMgr(void);
	~UCContactMgr(void);
private:
	typedef std::map<int,IM_S_USERINFO> STAFF_MAP;
	STAFF_MAP m_mapStaff;
	static const int SEARCH_MAXAMOUNT=100;
	int m_iStaffSize;
};

#endif


