#include "StdAfx.h"
#include "data/model/user/config/UserConfig.h"
#include "Log.h"
#include "UCRegMgr.h"
#include "UCConfigMgr.h"
#include "UCCallMgr.h"
#include "SSOLogin.h"


PhoneJointEventCB ConfigMgr::m_OnPJEventCB = NULL;

const std::string ChineseSimplified = "2052";	//简体中文
const std::string BrazilPortuguese	= "1046";	//巴西葡萄牙文
//日志配置文件
#define CONFIG_FILE "UCService.ini"

ConfigMgr::ConfigMgr(void)
{
	try
	{
		m_ConfigPath = "";
		m_strRegDNDCode = "";
		m_strUNRegDNDCode = "";
	}
	catch(...)
	{

	}
}

ConfigMgr::~ConfigMgr(void)
{
	try
	{
		m_ConfigPath = "";
	}
	catch(...)
	{

	}
}

void ConfigMgr::Init(void)
{
	//加载联动的配置
	std::string ConfigPath;
	eSDKTool::getCurrentPath(ConfigPath);
	ConfigPath.append("\\");
	ConfigPath.append(CONFIG_FILE);
	m_ConfigPath = ConfigPath;
	return;
}

void ConfigMgr::Uninit(void)
{	
	DEBUG_TRACE("");
}

int ConfigMgr::GetPhoneJointDevType(int& _iDevType)
{
	const int LENGTH = 10;
	char tchValue[LENGTH] = {0};
	(void)::GetPrivateProfileStringA("UCService","activedevice","",tchValue,LENGTH-1,m_ConfigPath.c_str());

	std::string strActiveDev(tchValue);
	if(0 == strActiveDev.compare("pc"))
	{
		INFO_LOG("ActiveDev is PC");
		_iDevType = (int)PC_Device;
	}
	else
	{
		INFO_LOG("ActiveDev is IPPhone");
		_iDevType = (int)IPPhone_Device;
	}

	INFO_LOG("_iDevType=%d",_iDevType);

	return UC_SDK_Success;
}
int ConfigMgr::SetPhoneJointDevType(int _iDevType)
{
	std::string strLinkNum = UCRegMgr::Instance().GetBindNO();
	TUP_RESULT tRet = tup_call_joint_setting(0, TUP_TRUE, strLinkNum.c_str());
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_joint_setting %s failed.",strLinkNum.c_str());
		return UC_SDK_Failed;
	}

	if( PC_Device == _iDevType)
	{
		TUP_RESULT tRet = tup_call_joint_stop();
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_joint_stop failed.");
		}
	}
	else if(IPPhone_Device == _iDevType)
	{
		TUP_RESULT tRet = tup_call_joint_start();
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_joint_start failed.");
		}
	}
	else
	{
		ERROR_LOG("DevType is invalid.");
		return UC_SDK_InvalidPara;
	}

	return UC_SDK_Success;
}

int ConfigMgr::SetPhoneJointEventCB(PhoneJointEventCB _EventCB)const
{
	m_OnPJEventCB = _EventCB;
	return UC_SDK_Success;
}

int ConfigMgr::OpenPortal(int /*_type*/)
{
	return UC_SDK_Success;
}
void ConfigMgr::InitDNDCode(void)
{
	const int LENGTH = 10;
	char tchValue[LENGTH] = {0};
	(void)::GetPrivateProfileStringA("UCService","regDNDcode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_strRegDNDCode = tchValue;

	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","unregDNDcode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_strUNRegDNDCode = tchValue;
}
std::string ConfigMgr::GetRegDNDCode(void)const
{
	return m_strRegDNDCode;
}
std::string ConfigMgr::GetUnRegDNDCode(void)const
{
	return m_strUNRegDNDCode;
}
void ConfigMgr::InitForwardCode(void)
{
	const int LENGTH = 10;
	char tchValue[LENGTH] = {0};
	(void)::GetPrivateProfileStringA("UCService","regfnccode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[0] = tchValue;

	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","unregfnccode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[1] = tchValue;

	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","regfbcode","",tchValue,LENGTH-1,m_ConfigPath.c_str());	
	m_mapForward[2] = tchValue;

	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","unregfbcode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[3] = tchValue;

	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","regfnrcode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[4] = tchValue;

	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","unregfnrcode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[5] = tchValue;

	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","regfocode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[6] = tchValue;

	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","unregfocode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[7] = tchValue;

	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","regvnccode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[8] = tchValue;
	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","unregvnccode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[9] = tchValue;
	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","regvbcode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[10] = tchValue;
	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","unregvbcode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[11] = tchValue;
	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","regvnrcode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[12] = tchValue;
	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","unregvnrcode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[13] = tchValue;
	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","regvocode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[14] = tchValue;
	memset(tchValue,0,LENGTH);
	(void)::GetPrivateProfileStringA("UCService","unregvocode","",tchValue,LENGTH-1,m_ConfigPath.c_str());
	m_mapForward[15] = tchValue;

}
bool ConfigMgr::GetFowardTypeByNum(const std::string& num,int& iType,std::string& bindno)
{
	//遍历num，看符合哪种呼叫前转业务码
	for(int i=0;i<16;i++)
	{	
		INFO_LOG("m_mapForward[i]=%d,num=%s",m_mapForward[i],num.c_str());
		if(eSDKTool::CheckString(m_mapForward[i],num,bindno))
		{
			iType = i/2;
			return true;
		}
	}
	return false;

}

std::string ConfigMgr::GetForwardCode(int& _iType)
{
	return m_mapForward[_iType];
}

int ConfigMgr::SetCallExService(int iType,const std::string& strNum)
{
	INFO_LOG("iType=%d,strNum=%s",iType,strNum.c_str());
	CALL_S_SERVICE_RIGHT_CFG stServiceCfg;  /* 业务权限集结构体指针 */
	memset(&stServiceCfg, 0, sizeof(stServiceCfg));
	stServiceCfg.ulRight = 1;

	CALL_E_SERVICE_CALL_TYPE forwardType;
	TUP_RESULT tRet = TUP_FAIL;

	std::string strServiceCode;
	switch (iType)
	{
	case FORWARD_UNCONDITION:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[0].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[1].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				strServiceCode = m_mapForward[0]+strNum;
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Active;				
			}
			else
			{
				strServiceCode = m_mapForward[1];
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Deactive;
			}
			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFU, (TUP_VOID*)&stServiceCfg);
			SaveUserConfig(SETTING_FORWARD_FUC,strNum);
			break;
		}
	case FORWARD_ONBUSY:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[2].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[3].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				strServiceCode = m_mapForward[2]+strNum;
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Active;
			}
			else
			{
				strServiceCode = m_mapForward[3];
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Deactive;
			}
			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFB, (TUP_VOID*)&stServiceCfg);
			SaveUserConfig(SETTING_FORWARD_FB,strNum);
			break;
		}
	case FORWARD_NOREPLY:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[4].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[5].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				strServiceCode = m_mapForward[4]+strNum;
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Active;
			}
			else
			{
				strServiceCode = m_mapForward[5];
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Deactive;
			}
			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFNA, (TUP_VOID*)&stServiceCfg);
			SaveUserConfig(SETTING_FORWARD_FNR,strNum);			
			break;
		}
	case FORWARD_OFFLINE:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[6].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[7].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				strServiceCode = m_mapForward[6]+strNum;
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Active;
			}
			else
			{
				strServiceCode = m_mapForward[7];
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Deactive;
			}
			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFNR , (TUP_VOID*)&stServiceCfg);
			SaveUserConfig(SETTING_FORWARD_FO,strNum);
			break;
		}
	case VOICEMAIL_UNCONDITION:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[8].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[9].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				strServiceCode = m_mapForward[8]+strNum;
				forwardType = CALL_E_SERVICE_CALL_TYPE_CFUVoiceMail_Active;
			}
			else
			{
				strServiceCode = m_mapForward[9];
				forwardType = CALL_E_SERVICE_CALL_TYPE_CFUVoiceMail_Deactive;
			}
			SaveUserConfig(SETTING_VOICEMAIL_VNC,strNum);
			break;
		}
	case VOICEMAIL_ONBUSY:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[10].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[11].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				strServiceCode = m_mapForward[10]+strNum;
				forwardType = CALL_E_SERVICE_CALL_TYPE_CFBVoiceMail_Active;
			}
			else
			{
				strServiceCode = m_mapForward[11];
			}
			SaveUserConfig(SETTING_VOICEMAIL_VB,strNum);
			forwardType = CALL_E_SERVICE_CALL_TYPE_CFBVoiceMail_Deactive;
			break;
		}
	case VOICEMAIL_NOREPLY:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[12].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[13].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				strServiceCode = m_mapForward[12]+strNum;
				forwardType = CALL_E_SERVICE_CALL_TYPE_CFNVoiceMail_Active;
			}
			else
			{
				strServiceCode = m_mapForward[13];
				forwardType = CALL_E_SERVICE_CALL_TYPE_CFNVoiceMail_Deactive;
			}
			SaveUserConfig(SETTING_VOICEMAIL_VNR,strNum);
			break;
		}
	case VOICEMAIL_OFFLINE:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[14].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[15].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				strServiceCode = m_mapForward[14]+strNum;
				forwardType = CALL_E_SERVICE_CALL_TYPE_CFOVoiceMail_Active;
			}
			else
			{
				strServiceCode = m_mapForward[15];
			}
			SaveUserConfig(SETTING_VOICEMAIL_VO,strNum);
			forwardType = CALL_E_SERVICE_CALL_TYPE_CFOVoiceMail_Deactive;
			break;
		}

	default:
		{
			ERROR_LOG("iType is invalid.");
			return UC_SDK_Failed;
		}
	}

	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_set_cfg failed.");
		return UC_SDK_Failed;
	}

	tRet = tup_call_set_IPTservice(forwardType, (TUP_VOID*)strNum.c_str());
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_set_IPTservice failed.");
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;

}
int ConfigMgr::GetCallExService(int iType,std::string& strNum)
{
	std::string num;
	INFO_LOG("iType=%d",iType);	
	switch (iType)
	{
	case FORWARD_UNCONDITION:
		{		
			GetUserConfig(SETTING_FORWARD_FUC,strNum);
			break;
		}
	case FORWARD_ONBUSY:
		{
			GetUserConfig(SETTING_FORWARD_FB,strNum);
			break;
		}
	case FORWARD_NOREPLY:
		{
			GetUserConfig(SETTING_FORWARD_FNR,strNum);
			break;
		}
	case FORWARD_OFFLINE:
		{
			GetUserConfig(SETTING_FORWARD_FO,strNum);
			break;
		}
	default:
		{
			ERROR_LOG("iType is invalid.");
			return UC_SDK_Failed;
		}
	}
	INFO_LOG("strNum=%s",strNum.c_str());	
	return UC_SDK_Success;
	
}

bool ConfigMgr::GetUserConfig(const std::string & _strkey, std::string & _strValue) const
{
	ecs::ecsdata::ConfigPair resPair;
	if (ecs::ecsdata::UserConfigQuery::QueryByKey(_strkey, resPair) )
	{
		_strValue = resPair.strValue;
		return true;
	}
	else
	{
		return false;
	}
}

bool ConfigMgr::SaveUserConfig(const std::string & _strkey, const std::string & _strValue) const
{
	ecs::ecsdata::ConfigPair configInfo;
	configInfo.strKey = _strkey;
	configInfo.strValue = _strValue;
	return 1 == ecs::ecsdata::AddUserConfigCommand::SingleAdd(configInfo);
}

int ConfigMgr::NotifyPJUI(int iState)
{
	DEBUG_TRACE("");
	if(NULL == m_OnPJEventCB)
	{
		ERROR_LOG("----m_OnPJEventCB is NULL");
		return UC_SDK_Failed;
	}
	INFO_LOG("----Enter OnPJEventCB ");
	m_OnPJEventCB(iState);
	INFO_LOG("----Leave OnPJEventCB");
	return UC_SDK_Success;

}
