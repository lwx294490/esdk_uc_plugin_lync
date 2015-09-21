#pragma once
#include "UCCallMgr.h"

typedef enum CONF_CREATE_STATUS
{
	CONF_INIT,
	CONF_CREATE_SUCCESS,
	CONF_CREATE_FAILED
};


class UCConfMgr
{
public:
	static inline UCConfMgr& Instance()
	{
		static UCConfMgr inst;
		return inst;
	}
public:
	static ConfMemberEventCB OnConfMemberEventCB;

public:
	int CreateConf(const std::string& groupID,const PhoneMemList& phoneList,const UCMemList& BindNoList,TUP_UINT32& callid);
	int TransCallToConf(const std::string& groupID,const PhoneMemList& phoneList,const UCMemList& BindNoList,TUP_UINT32 callid);
	void AddConfMember(void);
	int SetConfMemEventCB(ConfMemberEventCB _confmemberEventCB)const;
	int NotifyConfUI(const STConfParam&);
	int LeaveConf(void);
	void ClearConfMember(void);
	int AcceptConf(void);
	int RejectConf(void);
	void SetCallerInfo(const std::string& calleenum,const std::string& calleeAccount,bool isUCAccount);

	TUP_UINT32 GetConfID() {return m_uiConfID;}
	void SetConfID(TUP_UINT32 confid) {m_uiConfID = confid;}
	void SetGroupID(const std::string& groupid) {m_strGroupID = groupid;}
	std::string GetGroupID(void) {return m_strGroupID;}
	void ShowConfInfo(void);
	void SetConfCreateResult(CONF_CREATE_STATUS result) {m_emRecvConfCreate = result;}
public:
	int InviteMemberInConf(EM_MemberType _memberType,const std::string& strAccount);
	int DeleteMemberInCall(EM_MemberType _memberType,const std::string& strAccount);
	int ModifyMemberStatusInCall(EM_ConvnerOperateType operateType
		,EM_MemberType _memberType
		,const std::string& strAccount);
	void AddPhoneMeminConf(std::string _phone){m_confPhoneMemList.insert(_phone);};  ////被叫使用，用于确定群组中加入会议的人
	void DelPhoneMeminConf(std::string _phone){m_confPhoneMemList.erase(_phone);};  
	void AddUCMeminConf(std::string _ucAccount,std::string _BindNum){m_confUCMemList[_ucAccount] = _BindNum ;};////被叫使用，用于确定群组中加入会议的人
	void DelUCMeminConf(std::string _ucAccount){m_confUCMemList.erase(_ucAccount); ;};
	bool IsPhoneMemberInconf(std::string strPhone){	return (m_confPhoneMemList.find(strPhone) != m_confPhoneMemList.end()) ;}
	bool IsUCMemberInconf(std::string _account){  return (m_confUCMemList.find(_account) != m_confUCMemList.end()) ;}
	bool IsChairman(void){return m_ISChairman ;};
	void SetChairmainRole(bool _role){m_ISChairman = _role;};



private:
	UCConfMgr(void);
	~UCConfMgr(void);
private:
	PhoneMemList m_confPhoneMemList;	//IP电话成员列表
	UCMemList m_confUCMemList;			//UC账户成员列表
	TUP_UINT32 m_uiConfID;				//会议ID
	std::string m_strGroupID;			//群组ID
	std::string m_strChairManAccount;	//主席账户
	std::string m_strChairManBindNo;	//主席绑定号
	std::string m_strCalleeNum;			//被叫号码，作为2人呼叫转会议时的第一次邀请的号码
	std::string m_strCalleeAccount;		//被叫账户，依赖m_bIsUCAccount。m_bIsUCAccount为true时有值，否则无值
	bool m_bIsUCAccount;
	bool m_ISChairman;                  //会议中是不是扮演主席的角色/////
	typedef std::map<int,std::string> MapConfStatusDesc;	//会议状态描述
	MapConfStatusDesc m_mapConfStatusDesc;
	CONF_CREATE_STATUS m_emRecvConfCreate;//会议创建结果
	int m_count;                      ////第一次主席入会延时处理
};

