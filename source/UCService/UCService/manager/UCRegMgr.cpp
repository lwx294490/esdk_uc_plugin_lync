#include "StdAfx.h"
#include <WinSock2.h>
#include "UCRegMgr.h"
#include "UCConfigMgr.h"
#include "UCContactMgr.h"
#include "Log.h"
#include "UCRegEvent.h"
#include "UCEventMgr.h"
#include "UCStatusChangeEvent.h"




//lint -e1762
//lint -e1788
ClientSignInNotifyCB UCRegMgr::OnClientSignInNotifyCB = NULL;
StatusChangedCB UCRegMgr::OnStatusChangedCB = NULL;

UCRegMgr::UCRegMgr(void):m_strSipAccount("")
						,m_strLoginAccount("")
						,m_strBindNO("")
						,m_bLoginFlag(false)
						,m_iSelfStatus(UC_Offline)
						,m_bLogOutFlag(false)
{
}

UCRegMgr::~UCRegMgr(void)
{
}
void UCRegMgr::Init(void)
{
	TUP_RESULT tRet = tup_im_init();
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_init failed,return %d",tRet);
		return;
	}
}
void UCRegMgr::Uninit(void)
{
	DEBUG_TRACE("");

	OnClientSignInNotifyCB = NULL;
	OnStatusChangedCB = NULL;

	TUP_RESULT tRet = tup_im_uninit();
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_uninit failed,return %d",tRet);
		return;
	}
}

int UCRegMgr::SignInByPWD(const std::string& _account
							  ,const std::string& _pwd
							  ,const std::string& _serverUrl
							  ,const std::string& /*_langID*/)
{
	std::string strIP;
	int iPort;
	eSDKTool::GetIPPort(_serverUrl,strIP,iPort);
	TUP_RESULT tRet = tup_im_setserveraddress(strIP.c_str(),(TUP_UINT16)iPort);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_setserveraddress failed.");
		return UC_SDK_Failed;
	}

	std::string localip;
	if(!eSDKTool::GetBestHostip(localip,strIP))
	{
		ERROR_LOG("GetBestHostip failed.");
		return UC_SDK_Failed;
	}
    INFO_LOG("localip=%s",localip.c_str());
	tRet = tup_im_register_callback(CNotifyCallBack::IMNotify);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_register_callback failed.");
		return UC_SDK_Failed;
	}

	IM_S_LOGIN_ARG arg;
	strcpy_s(arg.account,IM_D_MAX_ACCOUNT_LENGTH,_account.c_str());
	strcpy_s(arg.password,IM_D_MAX_PASSWORD_LENGTH,_pwd.c_str());
	strcpy_s(arg.version,IM_D_MAX_VERSION_LENGTH,"v1.1.11.103");

	IM_S_LOGIN_ACK ack;
	tRet = tup_im_login(&arg,&ack);
	
	
	if(tRet != TUP_SUCCESS && IM_E_LOGING_RESULT_ALREADY_LOGIN != ack.reason)
	{
		ERROR_LOG("tup_im_login failed.reason:%d",ack.reason);
		UCRegEvent* pEvent = new UCRegEvent();
		pEvent->m_state = UC__SignedFailed;
		pEvent->m_stateDesc = NORMAL_ERROR;
		switch(ack.reason)
		{
		case IM_E_LOGING_RESULT_TIMEOUT:
			{				
				pEvent->m_stateDesc = TIME_OUT;				
				break;
			}
		case IM_E_LOGING_RESULT_INTERNAL_ERROR:
		case IM_E_LOGING_RESULT_FAILED:
		case IM_E_LOGING_RESULT_DECRYPT_FAILED:
		case IM_E_LOGING_RESULT_CERT_DOWNLOAD_FAILED:
		case IM_E_LOGING_RESULT_CERT_VALIDATE_FAILED:
		case IM_E_LOGING_RESULT_DNS_ERROR:
			{
				pEvent->m_stateDesc = NORMAL_ERROR;				
				break;
			}
		case IM_E_LOGING_RESULT_PASSWORD_ERROR:
			{
				pEvent->m_stateDesc = ERROR_PWD;
				break;
			}
		case IM_E_LOGING_RESULT_ACCOUNT_NOT_EXIST:
			{
				pEvent->m_stateDesc = ACC_NOT_EXISTED;
				break;
			}
		case IM_E_LOGING_RESULT_ACCOUNT_LOCKED:
			{
				pEvent->m_stateDesc = ACC_LOCKED;
				break;
			}
		case IM_E_LOGING_RESULT_NEED_NEW_VERSION:
			{
				pEvent->m_stateDesc = NEED_NEW_VERSION;
				break;
			}
		case IM_E_LOGING_RESULT_NOT_ACTIVE:
			{
				pEvent->m_stateDesc = NEED_ACTIVE;
				break;
			}
		case IM_E_LOGING_RESULT_ACCOUNT_SUSPEND:
			{
				pEvent->m_stateDesc = NEED_ACTIVE;
				break;
			}
		case IM_E_LOGING_RESULT_ACCOUNT_EXPIRE:
			{
				pEvent->m_stateDesc = NEED_ACTIVE;
				break;
			}
		}
		CUCEventMgr::Instance().PushEvent(pEvent);
		return UC_SDK_Failed;
	}

	tRet = tup_im_setdispatchmessage(TUP_TRUE);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_im_setdispatchmessage failed.");
		return UC_SDK_Failed;
	}

	IM_S_GETSERVICEPROFILEARG serviceArg;
	serviceArg.isSyncAll  = TUP_TRUE;
	serviceArg.needIcon = TUP_TRUE;
	serviceArg.isVpnAccess = TUP_FALSE;

	strcpy_s(serviceArg.localIP,IM_D_IP_LENGTH,localip.c_str());
	strcpy_s(serviceArg.timestamp,IM_D_MAX_TIMESTAMP_LENGTH,"1900000000000");

	IM_S_SERVICEPROFILEACK serviceAck;
	tRet = tup_im_getserviceprofile(&serviceArg,&serviceAck);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_im_getserviceprofile failed.");
		return UC_SDK_Failed;
	}

	tRet = tup_call_register_process_notifiy(CNotifyCallBack::CallNotify);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_call_register_process_notifiy failed.");
		return UC_SDK_Failed;
	}

	CALL_E_TRANSPORTMODE eTransMode =  CALL_E_TRANSPORTMODE_UDP;
	tRet = tup_call_set_cfg(CALL_D_CFG_SIP_TRANS_MODE, &eTransMode);
	if (TUP_SUCCESS != tRet)
	{
		ERROR_LOG("set SIP_TRANS_MODE failed.");
		return UC_SDK_Failed;
	}

	std::string ip;
	int iServerPort;
	eSDKTool::GetIPPort(serviceAck.sipServer,ip,iServerPort);

	TUP_UINT32 server_port = iServerPort;
	if (eTransMode == CALL_E_TRANSPORTMODE_TLS)
	{
		TUP_CHAR path[] = ".\root_cert_1.pem";
		tRet = tup_call_set_cfg(CALL_D_CFG_SIP_TLS_ROOTCERTPATH, path);
		if (TUP_SUCCESS != tRet)
		{
			ERROR_LOG("set SIP_TLS_ROOTCERTPATH failed.");
			return UC_SDK_Failed;
		}
		server_port = 5061;
	}

	CALL_S_SERVER_CFG sipServerCfg = {0};
	strcpy_s(sipServerCfg.server_address, ip.c_str());
	sipServerCfg.server_port = iServerPort;
	tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_REG_PRIMARY, &sipServerCfg );
	if (TUP_SUCCESS != tRet)
	{
		ERROR_LOG("set reg primary failed.");
		return UC_SDK_Failed;
	}

	memset(&sipServerCfg,0,sizeof(sipServerCfg));
	strcpy_s(sipServerCfg.server_address, ip.c_str());
	sipServerCfg.server_port = iServerPort;

	tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_PROXY_PRIMARY,&sipServerCfg);
	if (TUP_SUCCESS != tRet)
	{
		ERROR_LOG("set proxy primary failed.");
		return UC_SDK_Failed;
	}

	tRet = tup_call_set_cfg(CALL_D_CFG_ENV_USEAGENT, USER_AGENT);
	if (TUP_SUCCESS != tRet)
	{
		ERROR_LOG("set useagent failed.");
		return UC_SDK_Failed;
	}

	CALL_E_PRODUCT_TYPE eProductType = CALL_E_PRODUCT_TYPE_PC;
	tRet = tup_call_set_cfg(CALL_D_CFG_ENV_PRODUCT_TYPE, (TUP_VOID*)&eProductType);
	if (TUP_SUCCESS != tRet)
	{
		ERROR_LOG("set producttype failed.");
		return UC_SDK_Failed;
	}

	CALL_S_IF_INFO IFInfo  ;
	memset(&IFInfo,0,sizeof(CALL_S_IF_INFO));
	IFInfo.ulType =  CALL_E_IP_V4;
	IFInfo.uAddress.ulIPv4 = inet_addr(localip.c_str());
	tRet = tup_call_set_cfg(CALL_D_CFG_NET_NETADDRESS,  &IFInfo);
	if (TUP_SUCCESS != tRet)
	{
		ERROR_LOG("cfg netaddress failed.");
		return UC_SDK_Failed;
	}


	std::string sipAccount = serviceAck.sipAccount;
	std::string sipUserName = sipAccount + "@" + localip;

	tRet = tup_call_register(sipAccount.c_str(),sipUserName.c_str(),serviceAck.sipPassword);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_call_register failed.");
		return UC_SDK_Failed;
	}

	m_strSipAccount = sipAccount;
	m_strLoginAccount = _account;

	IM_S_USERINFO userinfo;
	if(UC_SDK_Success == UCContactMgr::Instance().getContactByAccount(_account,userinfo))
	{
		m_strBindNO = userinfo.bindNO;
	}
	

	////////2015-05-08 by c00327158标记用户登录是否登出/////
	m_bLogOutFlag = false;

	return UC_SDK_Success;
}
int UCRegMgr::SignOut()
{
	UCRegMgr::Instance().SetLoginFlag(false);

	TUP_RESULT tRet = tup_call_deregister(m_strSipAccount.c_str());
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_deregister failed.");
	}

	tRet = tup_im_setcancelsendingmessage();
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_setcancelsendingmessage failed.");
	}

	tRet = tup_im_logout();
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_logout failed.");
		return UC_SDK_Failed;
	}
	
	m_strSipAccount = "";
	m_strLoginAccount = "";
	m_strBindNO = "";
	////////2015-05-08 by c00327158标记用户登录是否登出/////
	m_bLogOutFlag = true;
	return UC_SDK_Success;
}

int UCRegMgr::SetLoginEventCB(ClientSignInNotifyCB _loginEventCB)
{
	UCRegMgr::OnClientSignInNotifyCB = _loginEventCB;
	return UC_SDK_Success;

}
int UCRegMgr::SetStatusEventCB(StatusChangedCB _statusEventCB)
{
	UCRegMgr::OnStatusChangedCB = _statusEventCB;
	return UC_SDK_Success;
}

int UCRegMgr::PubSelfStatus(int _state,const std::string& _desc)
{
	IM_S_STATUSARG arg;
	switch (_state)
	{
	case UC_Offline:
		{
			arg.status = IM_E_STATUS_OFFLINE;
			break;
		}
	case UC_Online:
		{
			arg.status = IM_E_STATUS_ONLINE;
			break;
		}
	case UC_Busy:
		{
			arg.status = IM_E_STATUS_BUSY;
			break;
		}
	case UC_Leave:
		{
			arg.status = IM_E_STATUS_LEAVE;
			break;
		}
	case UC_NoDisturb:
		{
			arg.status = IM_E_STATUS_DONTDISTURB;
			break;
		}
	case UC_Hide:
		{
			arg.status = IM_E_STATUS_HIDDEN;
			break;
		}
	default:
		{
			ERROR_LOG("pNotify->status is invalid");
			break;
		}
	}

	strcpy_s(arg.desc,IM_D_MAX_STATUS_DESCLEN,_desc.c_str());
		 
	TUP_RESULT tRet = tup_im_publishstatus(&arg);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_publishstatus failed");
		return UC_SDK_Failed;
	}


	if(_state == UC_NoDisturb && m_iSelfStatus != !UC_NoDisturb)
	{
		//开启免打扰
		std::string DNDActiveCode = ConfigMgr::Instance().GetRegDNDCode();
		std::string DNDDeActiveCode = ConfigMgr::Instance().GetUnRegDNDCode();
		if(DNDActiveCode.empty())
		{
			DNDActiveCode = "*56#";
		}
		if(DNDDeActiveCode.empty())
		{
			DNDDeActiveCode = "#56#";
		}

		CALL_S_SERVICE_RIGHT_CFG stServiceCfg;
		memset(&stServiceCfg, 0, sizeof(stServiceCfg));
		stServiceCfg.ulRight = 1;
		strcpy_s(stServiceCfg.acActiveAccessCode,CALL_D_ACCESSCODE_MAX_LENGTH, DNDActiveCode.c_str());
		strcpy_s(stServiceCfg.acDeactiveAccessCode,CALL_D_ACCESSCODE_MAX_LENGTH, DNDDeActiveCode.c_str());
		TUP_RESULT tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_DND, (TUP_VOID*)&stServiceCfg);
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_set_cfg DND failed,return:%d",tRet);
		}
		tRet= tup_call_set_IPTservice(CALL_E_SERVICE_CALL_TYPE_REG_DND,"");	
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_set_IPTservice RegDND failed,return:%d",tRet);
		}
	}
	else if(_state != UC_NoDisturb && m_iSelfStatus == UC_NoDisturb)
	{
		//关闭免打扰
		std::string DNDActiveCode = ConfigMgr::Instance().GetRegDNDCode();
		std::string DNDDeActiveCode = ConfigMgr::Instance().GetUnRegDNDCode();
		if(DNDActiveCode.empty())
		{
			DNDActiveCode = "*56#";
		}
		if(DNDDeActiveCode.empty())
		{
			DNDDeActiveCode = "#56#";
		}

		CALL_S_SERVICE_RIGHT_CFG stServiceCfg;
		memset(&stServiceCfg, 0, sizeof(stServiceCfg));
		stServiceCfg.ulRight = 1;
		strcpy_s(stServiceCfg.acActiveAccessCode,CALL_D_ACCESSCODE_MAX_LENGTH, DNDActiveCode.c_str());
		strcpy_s(stServiceCfg.acDeactiveAccessCode,CALL_D_ACCESSCODE_MAX_LENGTH, DNDDeActiveCode.c_str());
		TUP_RESULT tRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_DND, (TUP_VOID*)&stServiceCfg);
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_set_cfg DND failed,return:%d",tRet);
		}
		tRet = tup_call_set_IPTservice(CALL_E_SERVICE_CALL_TYPE_UNREG_DND,"");	
		if(tRet != TUP_SUCCESS)
		{
			ERROR_LOG("tup_call_set_IPTservice UnRegDND failed,return:%d",tRet);
		}
	}

	//通知自身状态
	IM_S_USERSTATUS_NOTIFY* pInfo = new IM_S_USERSTATUS_NOTIFY;
	pInfo->status = arg.status;
	strcpy_s(pInfo->origin,STRING_LENGTH,m_strLoginAccount.c_str());	
	UCStatusChangeEvent* pEvent = new UCStatusChangeEvent();
	pEvent->SetPara(IM_E_EVENT_IM_USERSTATUS_NOTIFY,(void*)pInfo);
	CUCEventMgr::Instance().PushEvent(pEvent);

	m_iSelfStatus = _state;

	return UC_SDK_Success;

}
int UCRegMgr::DisSubscribeStatus(const std::string& strAccount)
{
	TUP_S_LIST arg;
	char account[IM_D_MAX_ACCOUNT_LENGTH] = {0};
	strcpy_s(account,IM_D_MAX_ACCOUNT_LENGTH,strAccount.c_str());
	arg.data = account;
	arg.next = NULL;

	TUP_RESULT tRet = tup_im_unsubscribeuserstatus(&arg); 
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_unsubscribeuserstatus failed");
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;

}
int UCRegMgr::SubscribeStatus(const std::string& strAccount)
{
	TUP_S_LIST arg;
	char account[IM_D_MAX_ACCOUNT_LENGTH] = {0};
	strcpy_s(account,IM_D_MAX_ACCOUNT_LENGTH,strAccount.c_str());
	arg.data = account;
	arg.next = NULL;



	TUP_RESULT tRet = tup_im_subscribeuserstatus(&arg); 
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_subscribeuserstatus failed");
		return UC_SDK_Failed;
	}

	INFO_LOG("Subscribe %s Status Success.",strAccount.c_str());
	return UC_SDK_Success;

}

int UCRegMgr::CheckSignStatus(void)
{
	if(m_bLoginFlag)
	{
		return UC_SDK_Success;
	}
	else
	{
		return UC_SDK_NotLogin;
	}
	
}

int UCRegMgr::GetContactStatus(const std::string& _account,int& _status)
{
	TUP_S_LIST arg;
	char account[IM_D_MAX_ACCOUNT_LENGTH] = {0};
	strcpy_s(account,IM_D_MAX_ACCOUNT_LENGTH,_account.c_str());
	arg.data = account;
	arg.next = NULL;
	TUP_RESULT tRet = tup_im_detectuserstatus(&arg);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_im_detectuserstatus failed");
		return UC_SDK_Failed;
	}
	_status = UC_Offline;
	return UC_SDK_Success;
}

int UCRegMgr::GetContactInfo(const std::string& _account,STContact& _contact)
{
	IM_S_USERINFO userInfo;
	int iRet = UCContactMgr::Instance().getContactByAccount(_account,userInfo);
	if(iRet != UC_SDK_Success)
	{
		ERROR_LOG("getContactByAccount failed");
		return UC_SDK_Failed;
	}

	strcpy_s(_contact.ucAcc_,STRING_LENGTH,userInfo.account);
	strcpy_s(_contact.ipphone1_,STRING_LENGTH,userInfo.bindNO);
	return UC_SDK_Success;
}


void UCRegMgr::OnTime(unsigned int uiTimerID)
{
	if(uiTimerID == HEARTBEAT_TIMER_ID)
	{
		if(tup_im_sendheartbeat() == TUP_SUCCESS)
		{
			INFO_LOG("send heartbeat success.");
		}
		else
		{
			ERROR_LOG("tup_im_sendheartbeat failed.");
		}
	}
	return;
}

