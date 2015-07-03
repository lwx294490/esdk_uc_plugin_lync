#ifndef _UC_CALL_MGR_H_
#define _UC_CALL_MGR_H_

#include "Group.h"

using namespace std;

enum {
	NOCALL		=	0,
	AUDIOCALL	=	1,
	VIDEOCALL	=	2
};


//���й���
class UCCallMgr
{
public:
	static inline UCCallMgr& Instance()
	{
		static UCCallMgr inst;
		return inst;
	}
public:
	static AVSessionClosedCB OnAVSessionClosedCB;			//���жϿ��ص�����ָ��
	static AVSessionConnectedCB OnAVSessionConnectedCB;		//���н�ͨ�ص�����ָ��
	static AVSessAddedCB OnAVSessAddedCB;					//�º������ӻص�����ָ��	
	static VideoCallEventCB OnVideoCallEventCB;				//��Ƶ���лص�����
	static CallReservedEventCB OnCallReservedEventCB;		//��չ����ҵ��ص�����
	static CallTransEventCB OnCallTransEventCB;				//����ת���¼��ص�����
public:
	void Init(void);
	void Uninit(void);
public:
	int InsertUCMember(const std::string& _ucAccount,const std::string& _ucBindNo);//����UC��Ա
	int InsertPhoneMember(const std::string& _phone);//����绰��Ա
	int MakeCall(void);
	int TransCallToConf(EM_MemberType _memberType,const std::string& strAccount);
	int TransCallToConf(std::vector<std::string>&,std::vector<std::string>&);
	int HoldCall(void);
	int ResumeCall(void);
	int MakeVideoCall(const STVideoWindow& _localWnd,const STVideoWindow& _remoteWnd);
	int HangupCall(void);
	int HangupVideoCall(void);
	int AcceptCall(void);
	int AcceptVideoCall(const STVideoWindow& _localWnd,const STVideoWindow& _remoteWnd);
	int RejectCall(void);
	int RejectVideoCall(void);
	int SendDTMF(char _tone);
	int ForwardCall(EM_MemberType _iMemberType, const std::string& _strMember);
	int BlindTransCall(EM_MemberType _iMemberType, const std::string& _strMember);
	
	int SetCallEventCB(AVSessionClosedCB _aVSessionClosedCallBack,
					   AVSessionConnectedCB _aVSessionConnectedCallBack,
					   AVSessAddedCB _aVSessAddedCallBack)const;
	int SetVideoCallEventCB(VideoCallEventCB _callEventCallBack)const;
	int SetCallTransEventCB(CallTransEventCB CallTransCallBack)const;
	int SetCallReservedEventCB(CallReservedEventCB _callReserveredEventCallBack)const;
	

	void SetCallTransType(CALLTRANS_TYPE type) { m_CallTransType = type;}
	CALLTRANS_TYPE GetCallTransType()const { return m_CallTransType;}

	TUP_UINT32 GetCallID()const {return m_uiCallID;}
	void SetCallID(TUP_UINT32 callid) {m_uiCallID = callid;}
	void SetConfStart(bool isStart) {isConfStart = isStart;}
	std::string GetCalleeAccountByCallID(TUP_UINT32 callid);
	void SetCallStatus(int iStatus){m_iCallStatus = iStatus;}

	int MuteMic()const;
	int UnMuteMic()const;
	int MuteSpeaker()const;
	int UnMuteSpeaker()const;

	int ClearCallMember(void);
	void ShowCallInfo(void);

	//����
public:
	int ClearConvMember(void);	
	bool GetConvStarted()const;
	int GetCallStatus(void){return m_iCallStatus;}

private:
	UCCallMgr(void);
	~UCCallMgr(void);

private:
	TUP_UINT32 m_uiCallID;

	UCMemList	 m_MemBindNOList;	//��Ա�󶨺��б��б�
	PhoneMemList m_MemPhoneList;	//��Աphone�б�

	typedef std::map<std::string,EM_MemStatusInCall> ConvMemberMap;
	ConvMemberMap m_ConvMemberMap;

	bool isConfStart;		//�����Ѿ���ʼ

	CALLTRANS_TYPE m_CallTransType;		//ת������ ת��,פ��,һ��ת��
	int m_iCallStatus;					//0��ʾû�к��� 1��ʾ����ͨ�� 2 ��ʾ��Ƶͨ��
};

#endif


