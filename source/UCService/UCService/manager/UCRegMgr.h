#ifndef _UC_REG_MGR_H_
#define _UC_REG_MGR_H_

const unsigned int HEARTBEAT_TIMER_ID = 1;	//������ʱ��ID
const unsigned int HEARTBEAT_TIME_SEC = 30;	//������ʱʱ��

//ע�����
class UCRegMgr
{

public:
	static inline UCRegMgr& Instance()
	{
		static UCRegMgr inst;
		return inst;
	}
	static void OnTime(unsigned int _id);
public:
	static ClientSignInNotifyCB OnClientSignInNotifyCB;
	static StatusChangedCB OnStatusChangedCB;
public:
	void Init(void);
	void Uninit(void);
	int SignInByPWD(const std::string& _account,const std::string& _pwd,const std::string& _serverUrl,const std::string& _langID);//ʹ�������½
	int SignOut(void);
	int SetLoginEventCB(ClientSignInNotifyCB _loginEventCB);
	int SetStatusEventCB(StatusChangedCB _statusEventCB);
	int PubSelfStatus(int _state,const::string& _desc);
	int SubscribeStatus(const std::string& _strAccount);//����״̬
	int DisSubscribeStatus(const std::string& _strAccount);//ȥ����״̬
	int CheckSignStatus(void);//����Ƿ��¼
	int GetContactStatus(const std::string& _account,int& _status);
	int GetContactInfo(const std::string& _account,STContact& _contact);
public:
	std::string GetSelfAccount(){return m_strLoginAccount;}
	std::string GetSipAccount(){return m_strSipAccount;}
	std::string GetBindNO(){return m_strBindNO;}
	std::string GelLocalIP(){return m_strLocalIP;}
	void SetLoginFlag(bool isFlag) {m_bLoginFlag = isFlag;}
	bool GetLoginFlag() { return m_bLoginFlag; }
private:
	UCRegMgr(void);
	~UCRegMgr(void);
private:
	std::string m_strSipAccount;	//���ơ�11316pc����ʽ
	std::string m_strLoginAccount;	//�����ĵ�¼�˻�
	std::string m_strBindNO;		//���ơ�11316����ʽ��������
	bool m_bLoginFlag;
	int m_iSelfStatus;				//����״̬
	std::string m_strLocalIP;       //��¼IP��ַ////
public:
	bool m_bLogOutFlag;
};

#endif


