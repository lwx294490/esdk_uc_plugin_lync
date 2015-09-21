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
	void AddPhoneMeminConf(std::string _phone){m_confPhoneMemList.insert(_phone);};  ////����ʹ�ã�����ȷ��Ⱥ���м���������
	void DelPhoneMeminConf(std::string _phone){m_confPhoneMemList.erase(_phone);};  
	void AddUCMeminConf(std::string _ucAccount,std::string _BindNum){m_confUCMemList[_ucAccount] = _BindNum ;};////����ʹ�ã�����ȷ��Ⱥ���м���������
	void DelUCMeminConf(std::string _ucAccount){m_confUCMemList.erase(_ucAccount); ;};
	bool IsPhoneMemberInconf(std::string strPhone){	return (m_confPhoneMemList.find(strPhone) != m_confPhoneMemList.end()) ;}
	bool IsUCMemberInconf(std::string _account){  return (m_confUCMemList.find(_account) != m_confUCMemList.end()) ;}
	bool IsChairman(void){return m_ISChairman ;};
	void SetChairmainRole(bool _role){m_ISChairman = _role;};



private:
	UCConfMgr(void);
	~UCConfMgr(void);
private:
	PhoneMemList m_confPhoneMemList;	//IP�绰��Ա�б�
	UCMemList m_confUCMemList;			//UC�˻���Ա�б�
	TUP_UINT32 m_uiConfID;				//����ID
	std::string m_strGroupID;			//Ⱥ��ID
	std::string m_strChairManAccount;	//��ϯ�˻�
	std::string m_strChairManBindNo;	//��ϯ�󶨺�
	std::string m_strCalleeNum;			//���к��룬��Ϊ2�˺���ת����ʱ�ĵ�һ������ĺ���
	std::string m_strCalleeAccount;		//�����˻�������m_bIsUCAccount��m_bIsUCAccountΪtrueʱ��ֵ��������ֵ
	bool m_bIsUCAccount;
	bool m_ISChairman;                  //�������ǲ��ǰ�����ϯ�Ľ�ɫ/////
	typedef std::map<int,std::string> MapConfStatusDesc;	//����״̬����
	MapConfStatusDesc m_mapConfStatusDesc;
	CONF_CREATE_STATUS m_emRecvConfCreate;//���鴴�����
	int m_count;                      ////��һ����ϯ�����ʱ����
};

