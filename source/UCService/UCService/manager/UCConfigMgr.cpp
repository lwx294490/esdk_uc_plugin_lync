#include "StdAfx.h"
#include "data/model/user/config/UserConfig.h"
#include "Log.h"
#include "UCRegMgr.h"
#include "UCConfigMgr.h"
#include "UCCallMgr.h"
#include "SSOLogin.h"
#include "UCContactMgr.h"


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
		m_IPtSerStatus = IPtSer_Intit;
		m_bIsPhonnJointstarting = PhoneJont_init;
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
	std::string m_DeviceType;
	if (GetUserConfig(SETTING_ACTIVEDEVICE_IPPHONE,m_DeviceType))
	{
		if (PhoneDevice == m_DeviceType)
		{
			//INFO_LOG()
			INFO_LOG("ActiveDev is IPPhone");
			////开启话机联动/////
			SetPhoneJointDevType(IPPhone_Device);
		}
		else
		{
			//////默认设置为PC
			INFO_LOG("ActiveDev is PC");
			_iDevType = (int)PC_Device;
			std::string m_path = ConfigMgr::Instance().GetConfigPath();
			if(!::WritePrivateProfileStringA("UCService","activedevice","pc",m_path.c_str()))
			{
				ERROR_LOG("----WriteProfileString PC failed");
			}
			/////更新服务器配置////
			ConfigMgr::Instance().SaveUserConfig(SETTING_ACTIVEDEVICE_IPPHONE,"");
		}
	}
	else
	{
		//////默认设置为PC
		INFO_LOG("ActiveDev is PC");
		_iDevType = (int)PC_Device;
		std::string m_path = ConfigMgr::Instance().GetConfigPath();
		if(!::WritePrivateProfileStringA("UCService","activedevice","pc",m_path.c_str()))
		{
			ERROR_LOG("----WriteProfileString PC failed");
		}
		/////更新服务器配置////
		ConfigMgr::Instance().SaveUserConfig(SETTING_ACTIVEDEVICE_IPPHONE,"");
	}
	return UC_SDK_Success;
}
int ConfigMgr::SetPhoneJointDevType(int _iDevType)
{
	SetPhoneJontStartingStatus(PhoneJont_init);
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

std::string ConfigMgr::GetForwardCode(int _iType)
{
	return m_mapForward[_iType];
}

int ConfigMgr::SetCallExService(int iType,const std::string& strNum)
{
	INFO_LOG("iType=%d,strNum=%s",iType,strNum.c_str());
	CALL_S_SERVICE_RIGHT_CFG stServiceCfg;  /* 业务权限集结构体指针 */
	memset(&stServiceCfg, 0, sizeof(stServiceCfg));
	stServiceCfg.ulRight = 1;
	m_IPtSerStatus = IPtSer_Intit;

	CALL_E_SERVICE_CALL_TYPE forwardType;
	TUP_RESULT tRet = TUP_FAIL;

	switch (iType)
	{
	case FORWARD_UNCONDITION:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[0].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[1].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Active;			
			}
			else
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Deactive;
			}
			
			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFU, (TUP_VOID*)&stServiceCfg);
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
			//////等待IPT业务成功通知，设置10000毫秒超时/////
			int _Count = 100;
			while((_Count>0)&&(IPtSer_Intit == m_IPtSerStatus))
			{
				--_Count;
				Sleep(100);
				if (IPtSer_Sucess == m_IPtSerStatus)
				{
					SaveUserConfig(SETTING_FORWARD_FUC,strNum);
					return UC_SDK_Success;
				}
			    if(IPtSer_Failed == m_IPtSerStatus)
				{
					return UC_SDK_Failed;
				}
			}
			return UC_SDK_Failed;
			break;
		}
	case FORWARD_ONBUSY:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[2].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[3].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Active;
			}
			else
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Deactive;
			}
			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFB, (TUP_VOID*)&stServiceCfg);
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
			//////等待IPT业务成功通知，设置10000毫秒超时/////
			int _Count = 100;
			while((_Count>0)&&(IPtSer_Intit == m_IPtSerStatus))
			{
				--_Count;
				Sleep(100);
				if (IPtSer_Sucess == m_IPtSerStatus)
				{
					SaveUserConfig(SETTING_FORWARD_FB,strNum);
					return UC_SDK_Success;
				}
				if(IPtSer_Failed == m_IPtSerStatus)
				{
					return UC_SDK_Failed;
				}
			}
			return UC_SDK_Failed;
			break;
		}
	case FORWARD_NOREPLY:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[4].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[5].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Active;
			}
			else
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Deactive;
			}
			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFNA, (TUP_VOID*)&stServiceCfg);
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
			//////等待IPT业务成功通知，设置10000毫秒超时/////
			int _Count = 100;
			while((_Count>0)&&(IPtSer_Intit == m_IPtSerStatus))
			{
				--_Count;
				Sleep(100);
				if (IPtSer_Sucess == m_IPtSerStatus)
				{
					SaveUserConfig(SETTING_FORWARD_FNR,strNum);	
					return UC_SDK_Success;
				}
				if(IPtSer_Failed == m_IPtSerStatus)
				{
					return UC_SDK_Failed;
				}
			}
			return UC_SDK_Failed;		
			break;
		}
	case FORWARD_OFFLINE:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[6].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[7].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Active;
			}
			else
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Deactive;
			}
			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFNR , (TUP_VOID*)&stServiceCfg);
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
			//////等待IPT业务成功通知，设置10000毫秒超时/////
			int _Count = 100;
			while((_Count>0)&&(IPtSer_Intit == m_IPtSerStatus))
			{
				--_Count;
				Sleep(100);
				if (IPtSer_Sucess == m_IPtSerStatus)
				{
					SaveUserConfig(SETTING_FORWARD_FO,strNum);
					return UC_SDK_Success;
				}
				if(IPtSer_Failed == m_IPtSerStatus)
				{
					return UC_SDK_Failed;
				}
			}
			return UC_SDK_Failed;
			break;
		}
	case VOICEMAIL_UNCONDITION:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[8].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[9].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Active;
			}
			else
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Deactive;
			}

			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFU, (TUP_VOID*)&stServiceCfg);
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
			//////等待IPT业务成功通知，设置10000毫秒超时/////
			int _Count = 100;
			while((_Count>0)&&(IPtSer_Intit == m_IPtSerStatus))
			{
				--_Count;
				Sleep(100);
				if (IPtSer_Sucess == m_IPtSerStatus)
				{
					SaveUserConfig(SETTING_VOICEMAIL_VNC,strNum);
					return UC_SDK_Success;
				}
				if(IPtSer_Failed == m_IPtSerStatus)
				{
					return UC_SDK_Failed;
				}
			}
			return UC_SDK_Failed;
			break;
		}
	case VOICEMAIL_ONBUSY:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[10].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[11].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Active;
			}
			else
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Deactive;
			}
			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFB, (TUP_VOID*)&stServiceCfg);
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
			//////等待IPT业务成功通知，设置10000毫秒超时/////
			int _Count = 100;
			while((_Count>0)&&(IPtSer_Intit == m_IPtSerStatus))
			{
				--_Count;
				Sleep(100);
				if (IPtSer_Sucess == m_IPtSerStatus)
				{
					SaveUserConfig(SETTING_VOICEMAIL_VB,strNum);
					return UC_SDK_Success;
				}
				if(IPtSer_Failed == m_IPtSerStatus)
				{
					return UC_SDK_Failed;
				}
			}
			return UC_SDK_Failed;
			break;
		}
	case VOICEMAIL_NOREPLY:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[12].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[13].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Active;
			}
			else
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Deactive;
			}
			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFNA, (TUP_VOID*)&stServiceCfg);
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
			//////等待IPT业务成功通知，设置10000毫秒超时/////
			int _Count = 100;
			while((_Count>0)&&(IPtSer_Intit == m_IPtSerStatus))
			{
				--_Count;
				Sleep(100);
				if (IPtSer_Sucess == m_IPtSerStatus)
				{
					SaveUserConfig(SETTING_VOICEMAIL_VNR,strNum);
					return UC_SDK_Success;
				}
				if(IPtSer_Failed == m_IPtSerStatus)
				{
					return UC_SDK_Failed;
				}
			}
			return UC_SDK_Failed;
			break;
		}
	case VOICEMAIL_OFFLINE:
		{
			strncpy_s(stServiceCfg.acActiveAccessCode, m_mapForward[14].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, m_mapForward[15].c_str(), CALL_D_ACCESSCODE_MAX_LENGTH);
			if(!strNum.empty())
		   {
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Active;
			}
			else
			{
				forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Deactive;
			}
			tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFNR , (TUP_VOID*)&stServiceCfg);
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
			//////等待IPT业务成功通知，设置10000毫秒超时/////
			int _Count = 100;
			while((_Count>0)&&(IPtSer_Intit == m_IPtSerStatus))
			{
				--_Count;
				Sleep(100);
				if (IPtSer_Sucess == m_IPtSerStatus)
				{
			        SaveUserConfig(SETTING_VOICEMAIL_VO,strNum);
					return UC_SDK_Success;
				}
				if(IPtSer_Failed == m_IPtSerStatus)
				{
					return UC_SDK_Failed;
				}
			}
			return UC_SDK_Failed;
			break;
		}

	default:
		{
			ERROR_LOG("iType is invalid.");
			return UC_SDK_Failed;
		}
	}

}
int ConfigMgr::GetCallExService(int iType,std::string& strNum)
{
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
	case VOICEMAIL_UNCONDITION:
		{
			GetUserConfig(SETTING_VOICEMAIL_VNC,strNum);
			break;
		}
	case VOICEMAIL_ONBUSY:
		{
			GetUserConfig(SETTING_VOICEMAIL_VB,strNum);
			break;
		}
	case VOICEMAIL_NOREPLY:
		{
			GetUserConfig(SETTING_VOICEMAIL_VNR,strNum);
			break;
		}
	case VOICEMAIL_OFFLINE:
		{
			GetUserConfig(SETTING_VOICEMAIL_VO,strNum);
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

int ConfigMgr::NotifyPJUI(const PJStatusParam& _pjParam)
{
	DEBUG_TRACE("");
	if(NULL == m_OnPJEventCB)
	{
		ERROR_LOG("----m_OnPJEventCB is NULL");
		return UC_SDK_Failed;
	}
	INFO_LOG("----Enter OnPJEventCB ");
	ConfigMgr::m_OnPJEventCB(_pjParam);
	INFO_LOG("----Leave OnPJEventCB");
	return UC_SDK_Success;

}

void ConfigMgr::InitIPTService(void)
{
	//////获取个人portal设置信息///////
	IM_S_USERINFO userInfo;
	std::string m_SelfAccount = UCRegMgr::Instance().GetSelfAccount();
	int iRet = UCContactMgr::Instance().getContactByAccount(UCRegMgr::Instance().GetSelfAccount(),userInfo);
	if(iRet != UC_SDK_Success)
	{
		ERROR_LOG("getContactByAccount failed");
	}
	CALL_S_SERVICERIGHT_CFG servicecfg = {0};
	iRet = tup_call_get_serviceright(0,&servicecfg);

	if (TUP_SUCCESS != iRet )
	{
		ERROR_LOG("tup_call_get_serviceright Failed");
	}
	//////IPT语音转话机业务重置//////
	if (servicecfg.astSrvInfo[CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_UNCONDITIONAL].ulRight&&servicecfg.astSrvInfo[CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_UNCONDITIONAL].ulRegister)
	{
		const std::string m_strUNum = eSDKTool::utf8str2unicodestr(std::string(servicecfg.stServiceParam.acCallForwardUnconditionNum));
		SaveUserConfig(SETTING_FORWARD_FUC,m_strUNum);
	}
	else
	{
		SaveUserConfig(SETTING_FORWARD_FUC,"");
	}

	if (servicecfg.astSrvInfo[CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_ONBUSY].ulRight&&servicecfg.astSrvInfo[CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_ONBUSY].ulRegister)
	{
		const std::string m_strBNum = eSDKTool::utf8str2unicodestr(servicecfg.stServiceParam.acCallForwardOnBusyNum);
		SaveUserConfig(SETTING_FORWARD_FB,m_strBNum);
	}
	else
	{
		SaveUserConfig(SETTING_FORWARD_FB,"");
	}

	if (servicecfg.astSrvInfo[CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_NOREPLY].ulRight&&servicecfg.astSrvInfo[CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_NOREPLY].ulRegister)
	{
		const std::string m_strNNum = eSDKTool::utf8str2unicodestr(servicecfg.stServiceParam.acCallForwardNoReplyNum);
		SaveUserConfig(SETTING_FORWARD_FNR,m_strNNum);
	}
	else
	{
		SaveUserConfig(SETTING_FORWARD_FNR,"");
	}
}