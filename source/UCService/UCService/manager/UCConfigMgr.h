#ifndef _UC_CONFIG_H
#define _UC_CONFIG_H

//ǰ��
const std::string SETTING_FORWARD_FUC = "FUC";
const std::string SETTING_FORWARD_FB = "FB";
const std::string SETTING_FORWARD_FNR = "FNR";
const std::string SETTING_FORWARD_FO = "FO";
//
const std::string SETTING_VOICEMAIL_VNC = "VNC";
const std::string SETTING_VOICEMAIL_VB = "VB";
const std::string SETTING_VOICEMAIL_VNR = "VNR";
const std::string SETTING_VOICEMAIL_VO = "VO";

//����ʱPC�˽�������IPONE�˽���
const std::string SETTING_ACTIVEDEVICE_IPPHONE = "IPPHONE";
const std::string PhoneDevice = "IPPHONE";

//�����
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
	int GetPhoneJointDevType(int& _iDevType);//��ȡ���������豸����
	int SetPhoneJointDevType(int _iDevType);//���û��������豸����
	int SetPhoneJointEventCB(PhoneJointEventCB _EventCB)const;//���û���������Ϣ�ص�
	int OpenPortal(int);
	std::string GetForwardCode(int& _iType);			//��ȡҵ����
	bool GetFowardTypeByNum(const std::string& num,int& iType,std::string& bindno);
	void InitForwardCode(void);
	void InitDNDCode(void);
	std::string GetRegDNDCode(void)const;
	std::string GetUnRegDNDCode(void)const;
	int SetCallExService(int iType,const std::string& strNum);			//����ǰ������
	int GetCallExService(int iType,std::string& strNum);				//��ȡǰ������

	bool GetUserConfig(	const std::string & _strkey, std::string & _strValue) const;
	bool SaveUserConfig(const std::string & _strkey, const std::string & _strValue) const;

	std::string GetConfigPath(){return m_ConfigPath ;};

	int NotifyPJUI(int iState);

public:
	static PhoneJointEventCB m_OnPJEventCB;
	std::map<int,std::string> m_mapForward;
private:
	std::string m_strRegDNDCode;	//ע��DNDҵ�񼤻���
	std::string m_strUNRegDNDCode;	//ע��DNDҵ�񼤻���
};

#endif
