#ifndef _UC_CONFIG_H
#define _UC_CONFIG_H

//前传
const std::string SETTING_FORWARD_FUC = "FUC";
const std::string SETTING_FORWARD_FB = "FB";
const std::string SETTING_FORWARD_FNR = "FNR";
const std::string SETTING_FORWARD_FO = "FO";
//
const std::string SETTING_VOICEMAIL_VNC = "VNC";
const std::string SETTING_VOICEMAIL_VB = "VB";
const std::string SETTING_VOICEMAIL_VNR = "VNR";
const std::string SETTING_VOICEMAIL_VO = "VO";

//来电时PC端接听还是IPONE端接听
const std::string SETTING_ACTIVEDEVICE_IPPHONE = "IPPHONE";
const std::string PhoneDevice = "IPPHONE";

//免打扰
const std::string SETTING_DND_ACTIVE = "";


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
	std::string GetForwardCode(int& _iType);			//获取业务码
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

	int NotifyPJUI(int iState);

public:
	static PhoneJointEventCB m_OnPJEventCB;
	std::map<int,std::string> m_mapForward;
private:
	std::string m_strRegDNDCode;	//注册DND业务激活码
	std::string m_strUNRegDNDCode;	//注销DND业务激活码
};

#endif
