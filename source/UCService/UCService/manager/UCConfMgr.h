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
	typedef std::map<int,std::string> MapConfStatusDesc;	//����״̬����
	MapConfStatusDesc m_mapConfStatusDesc;
	CONF_CREATE_STATUS m_emRecvConfCreate;//���鴴�����
};

