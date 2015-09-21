#include "StdAfx.h"
#include "UCCallReservedEvent.h"
#include "Log.h"
#include "UCConfigMgr.h"

UCCallReservedEvent::UCCallReservedEvent(void)
{
}

UCCallReservedEvent::~UCCallReservedEvent(void)
{
}
bool UCCallReservedEvent::DoHandle(void)
{
	DEBUG_TRACE("");

	INFO_LOG("----UCCallReservedEvent:param1=%d,param2=%d,m_pBody=0x%x",m_param1,m_param2,m_pBody);
		//////IPT业务成功//////
	switch (m_param1)
	{
	case CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Active:
		{
			if (CALL_E_EVT_SET_IPT_SERVICE_SUCCESS== m_msgid)
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Active Sucess");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Sucess);
			} 
			else
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Active Failed");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Failed);
			}
			break;
		}
	case CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Deactive:
		{
			if (CALL_E_EVT_SET_IPT_SERVICE_SUCCESS== m_msgid)
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Deactive Sucess");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Sucess);
			} 
			else
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Deactive Failed");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Failed);
			}
			break;
		}
	case CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Active:
		{
			if (CALL_E_EVT_SET_IPT_SERVICE_SUCCESS== m_msgid)
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Active Sucess");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Sucess);
			} 
			else
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Active Failed");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Failed);
			}
			break;
		}
	case CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Deactive:
		{
			if (CALL_E_EVT_SET_IPT_SERVICE_SUCCESS== m_msgid)
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Deactive Sucess");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Sucess);
			} 
			else
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Deactive Failed");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Failed);
			}
			break;
		}
	case CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Active:
		{
			if (CALL_E_EVT_SET_IPT_SERVICE_SUCCESS== m_msgid)
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Active Sucess");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Sucess);
			} 
			else
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Active Failed");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Failed);
			}
			break;
		}
	case CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Deactive:
		{
			if (CALL_E_EVT_SET_IPT_SERVICE_SUCCESS== m_msgid)
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Deactive Sucess");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Sucess);
			} 
			else
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Deactive Failed");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Failed);
			}
			break;
		}
	case CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Active:
		{
			if (CALL_E_EVT_SET_IPT_SERVICE_SUCCESS== m_msgid)
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Active Sucess");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Sucess);
			} 
			else
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Active Failed");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Failed);
			}
			break;
		}
	case CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Deactive:
		{
			if (CALL_E_EVT_SET_IPT_SERVICE_SUCCESS== m_msgid)
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Deactive Sucess");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Sucess);
			} 
			else
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Deactive Failed");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Failed);
			}
			break;
		}
	case CALL_E_SERVICE_CALL_TYPE_REG_DND:
		{
			if (CALL_E_EVT_SET_IPT_SERVICE_SUCCESS== m_msgid)
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_REG_DND Sucess");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Sucess);
			} 
			else
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_REG_DND Failed");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Failed);
			}
			break;
		}
	case CALL_E_SERVICE_CALL_TYPE_UNREG_DND:
		{
			if (CALL_E_EVT_SET_IPT_SERVICE_SUCCESS== m_msgid)
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_UNREG_DND Sucess");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Sucess);
			} 
			else
			{
				INFO_LOG("CALL_E_SERVICE_CALL_TYPE_UNREG_DND Failed");
				ConfigMgr::Instance().SetIPTServiceStatus(IPtSer_Failed);
			}
			break;

		}
	default:
		{
			ERROR_LOG("NoneType Notify.");
			break; ;
		}

	} 
	

	return true;
}
void UCCallReservedEvent::SetPara(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	m_msgid = msgid;
	m_param1 = param1;
	m_param2 = param2;
	m_pBody = pBody;
}

