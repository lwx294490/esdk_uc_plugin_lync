#include "StdAfx.h"
#include "Log.h"
#include "UCStatusChangeEvent.h"
#include "UCRegMgr.h"
#include "UCContactMgr.h"

UCStatusChangeEvent::UCStatusChangeEvent(void):m_EventID(IM_E_EVENT_IM_ORIGIN),m_pBody(NULL)
{
}

UCStatusChangeEvent::~UCStatusChangeEvent(void)
{
}
bool UCStatusChangeEvent::DoHandle(void)
{
	DEBUG_TRACE("");

	if(NULL == UCRegMgr::OnStatusChangedCB)
	{
		ERROR_LOG("----OnStatusChangedCB is NULL");
		return false;
	}

	if(m_EventID != IM_E_EVENT_IM_USERSTATUS_NOTIFY)
	{
		ERROR_LOG("----m_EventID is invalid");
		return false;
	}

	IM_S_USERSTATUS_NOTIFY* pNotify = (IM_S_USERSTATUS_NOTIFY*)m_pBody;
	if(NULL == pNotify)
	{
		ERROR_LOG("----pNotify is null");
		return false;
	}

	int _state = UC_Offline;	
	switch (pNotify->status)
	{
	case IM_E_STATUS_OFFLINE:
		{
			_state = UC_Offline;
			break;
		}
	case IM_E_STATUS_ONLINE:
		{
			_state = UC_Online;
			break;
		}
	case IM_E_STATUS_BUSY:
		{
			_state = UC_Busy;
			break;
		}
	case IM_E_STATUS_LEAVE:
		{
			_state = UC_Leave;
			break;
		}
	case IM_E_STATUS_DONTDISTURB:
		{
			_state = UC_NoDisturb;
			break;
		}
	case IM_E_STATUS_HIDDEN:
		{
			_state = UC_Hide;
			break;
		}
	default:
		{
			ERROR_LOG("pNotify->status is invalid");
			break;
		}
	}

	INFO_LOG("----UCStatusChangeEvent:Account=%s,Status=%d",pNotify->origin,_state);

	IM_S_USERINFO info;
	if(UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(pNotify->origin,info))
	{
		ERROR_LOG("----Account:%s is invalid",pNotify->origin);
		return false;
	}

	STContact _contact = {0};
	strcpy_s(_contact.ucAcc_,STRING_LENGTH,info.account);
	//strcpy_s(_contact.address_,STRING_LENGTH,info.address);
	//strcpy_s(_contact.ipphone1_,STRING_LENGTH,info.bindNO);
	//strcpy_s(_contact.deptName_,STRING_LENGTH,info.deptNameCn);
	//strcpy_s(_contact.desc_,STRING_LENGTH,info.desc);
	//strcpy_s(_contact.email_,STRING_LENGTH,info.email);
	//strcpy_s(_contact.fax_,STRING_LENGTH,info.fax);
	//strcpy_s(_contact.homePhone_,STRING_LENGTH,info.homePhone);

	//strcpy_s(_contact.ipphone1_,STRING_LENGTH,info.ipPhone);
	//strcpy_s(_contact.mobile_,STRING_LENGTH,info.mobile);
	//strcpy_s(_contact.name_,STRING_LENGTH,info.name);
	//strcpy_s(_contact.nickName_,STRING_LENGTH,info.nativeName);
	//strcpy_s(_contact.officePhone_,STRING_LENGTH,info.officePhone);
	//strcpy_s(_contact.otherPhone_,STRING_LENGTH,info.otherPhone);
	//strcpy_s(_contact.zip_,STRING_LENGTH,info.postalcode);
	//strcpy_s(_contact.signature_,STRING_LENGTH,info.signature);
	//strcpy_s(_contact.staffNo_,STRING_LENGTH,info.staffNO);
	//strcpy_s(_contact.webSite_,STRING_LENGTH,info.webSite);


	INFO_LOG("----Enter OnStatusChangedCB");
	UCRegMgr::OnStatusChangedCB(_state,_contact);
	INFO_LOG("----Leave OnStatusChangedCB");

	return true;
}
void UCStatusChangeEvent::SetPara(IM_E_EVENT_ID eventID, void *body)
{
	m_EventID = eventID;
	m_pBody = body;
}

