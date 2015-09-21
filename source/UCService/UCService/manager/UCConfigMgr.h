#ifndef _UC_CONFIG_H
#define _UC_CONFIG_H


//通话前传
const std::string SETTING_FORWARD_FUC = "FUC";
const std::string SETTING_FORWARD_FB = "FB";
const std::string SETTING_FORWARD_FNR = "FNR";
const std::string SETTING_FORWARD_FO = "FO";
//语音信箱前传
const std::string SETTING_VOICEMAIL_VNC = "VNC";
const std::string SETTING_VOICEMAIL_VB = "VB";
const std::string SETTING_VOICEMAIL_VNR = "VNR";
const std::string SETTING_VOICEMAIL_VO = "VO";

//来电时PC端接听还是IPONE端接听
const std::string SETTING_ACTIVEDEVICE_IPPHONE = "IPPHONE";
const std::string PhoneDevice = "IPPHONE";

////上次登录IP//////
const std::string LOCALIP = "";

/////IPT业务状态////
enum IPtServiceStatus
{
	IPtSer_Intit = -1,
	IPtSer_Sucess = 0,
	IPtSer_Failed = 1
};
//话机联动设置状态
enum StartPhoneJontStatus
{
	PhoneJont_init			=	0,	//话机联动初始状态
	PhoneJont_Sucess	    =	1,	//话机联动开启成功
	PhoneJont_Faliled		=	2	//话机联动开启失败
};

class ConfigMgr
{
private:
	ConfigMgr(void);
	~ConfigMgr(void);
public:
	static inline ConfigMgr& Instance()
	{
		static ConfigMgr inst;
		return inst;
	}
private:
	std::string m_ConfigPath;
public:
	void Init(void);
	void Uninit(void);
	int GetPhoneJointDevType(int& _iDevType);//获取话机联动设备类型
	int SetPhoneJointDevType(int _iDevType);//设置话机联动设备类型
	int SetPhoneJointEventCB(PhoneJointEventCB _EventCB)const;//设置话机联动消息回调
	int OpenPortal(int);
	std::string GetForwardCode(int _iType);			//获取业务码
	bool GetFowardTypeByNum(const std::string& num,int& iType,std::string& bindno);
	void InitForwardCode(void);
	void InitDNDCode(void);
	std::string GetRegDNDCode(void)const;
	std::string GetUnRegDNDCode(void)const;
	int SetCallExService(int iType,const std::string& strNum);			//设置前传号码
	int GetCallExService(int iType,std::string& strNum);				//获取前传号码

	bool GetUserConfig(	const std::string & _strkey, std::string & _strValue) const;
	bool SaveUserConfig(const std::string & _strkey, const std::string & _strValue) const;

	std::string GetConfigPath(){return m_ConfigPath ;};

	int NotifyPJUI(const PJStatusParam &_pjParam);
	void SetIPTServiceStatus(int _result){m_IPtSerStatus = _result;};
	void SetPhoneJontStartingStatus(int Result){m_bIsPhonnJointstarting = Result;};
	int GettPhoneJontStartingStatus(void){ return m_bIsPhonnJointstarting;};
	void InitIPTService(void);

public:
	static PhoneJointEventCB m_OnPJEventCB;
	std::map<int,std::string> m_mapForward;
private:
	std::string m_strRegDNDCode;	//注册DND业务激活码
	std::string m_strUNRegDNDCode;	//注销DND业务激活码
	int m_IPtSerStatus;             //设置的IPT业务状态
	int m_bIsPhonnJointstarting;   ///是否正在设置话机联动///// 
};

#endif
