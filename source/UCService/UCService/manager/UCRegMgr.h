#ifndef _UC_REG_MGR_H_
#define _UC_REG_MGR_H_

const unsigned int HEARTBEAT_TIMER_ID = 1;	//心跳定时器ID
const unsigned int HEARTBEAT_TIME_SEC = 30;	//心跳定时时长

//注册管理
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
	int SignInByPWD(const std::string& _account,const std::string& _pwd,const std::string& _serverUrl,const std::string& _langID);//使用密码登陆
	int SignOut(void);
	int SetLoginEventCB(ClientSignInNotifyCB _loginEventCB);
	int SetStatusEventCB(StatusChangedCB _statusEventCB);
	int PubSelfStatus(int _state,const::string& _desc);
	int SubscribeStatus(const std::string& _strAccount);//订阅状态
	int DisSubscribeStatus(const std::string& _strAccount);//去订阅状态
	int CheckSignStatus(void);//检查是否登录
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
	std::string m_strSipAccount;	//类似“11316pc”格式
	std::string m_strLoginAccount;	//正常的登录账户
	std::string m_strBindNO;		//类似“11316”格式，纯数字
	bool m_bLoginFlag;
	int m_iSelfStatus;				//自身状态
	std::string m_strLocalIP;       //登录IP地址////
public:
	bool m_bLogOutFlag;
};

#endif


