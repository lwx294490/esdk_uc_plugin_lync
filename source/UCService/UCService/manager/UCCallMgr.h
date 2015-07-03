#ifndef _UC_CALL_MGR_H_
#define _UC_CALL_MGR_H_

#include "Group.h"

using namespace std;

enum {
	NOCALL		=	0,
	AUDIOCALL	=	1,
	VIDEOCALL	=	2
};


//呼叫管理
class UCCallMgr
{
public:
	static inline UCCallMgr& Instance()
	{
		static UCCallMgr inst;
		return inst;
	}
public:
	static AVSessionClosedCB OnAVSessionClosedCB;			//呼叫断开回调函数指针
	static AVSessionConnectedCB OnAVSessionConnectedCB;		//呼叫接通回调函数指针
	static AVSessAddedCB OnAVSessAddedCB;					//新呼叫连接回调函数指针	
	static VideoCallEventCB OnVideoCallEventCB;				//视频呼叫回调函数
	static CallReservedEventCB OnCallReservedEventCB;		//扩展呼叫业务回调函数
	static CallTransEventCB OnCallTransEventCB;				//呼叫转移事件回调函数
public:
	void Init(void);
	void Uninit(void);
public:
	int InsertUCMember(const std::string& _ucAccount,const std::string& _ucBindNo);//插入UC成员
	int InsertPhoneMember(const std::string& _phone);//插入电话成员
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

	//会议
public:
	int ClearConvMember(void);	
	bool GetConvStarted()const;
	int GetCallStatus(void){return m_iCallStatus;}

private:
	UCCallMgr(void);
	~UCCallMgr(void);

private:
	TUP_UINT32 m_uiCallID;

	UCMemList	 m_MemBindNOList;	//成员绑定号列表列表
	PhoneMemList m_MemPhoneList;	//成员phone列表

	typedef std::map<std::string,EM_MemStatusInCall> ConvMemberMap;
	ConvMemberMap m_ConvMemberMap;

	bool isConfStart;		//会议已经开始

	CALLTRANS_TYPE m_CallTransType;		//转移类型 转移,驻留,一键转接
	int m_iCallStatus;					//0表示没有呼叫 1表示语音通话 2 表示视频通话
};

#endif


