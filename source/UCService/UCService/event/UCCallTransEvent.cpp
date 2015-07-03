#include "StdAfx.h"
#include "Log.h"
#include "UCCallMgr.h"
#include "UCCallTransEvent.h"

UCCallTransEvent::UCCallTransEvent(void)
{
}

UCCallTransEvent::~UCCallTransEvent(void)
{
}

void UCCallTransEvent::SetPara(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	m_msgid = msgid;
	m_param1 = param1;
	m_param2 = param2;
	m_pBody = pBody;
}

bool UCCallTransEvent::DoHandle(void)
{
	DEBUG_TRACE("");

	int iType = -1;
	int iResult = -1;

	switch(m_msgid)
	{
		case CALL_E_EVT_CALL_BLD_TRANSFER_SUCCESS:
			{
				INFO_LOG("----Blind Trans SUCESS");
				iType = EM_BLIND_TRANS;
				iResult = UC_SDK_Success;
			}
			break;
		case CALL_E_EVT_CALL_BLD_TRANSFER_FAILED:
			{
				WARN_LOG("----Blind Trans Failed");
				iType = EM_BLIND_TRANS;
				iResult = UC_SDK_Failed;
				//盲转失败要取消呼叫转移
				(void)UCCallMgr::Instance().ResumeCall();
			}
			break;

		case CALL_E_EVT_CALL_ATD_TRANSFER_SUCCESS:
			{
				INFO_LOG("----Consult Trans SUCESS");
				iType = EM_CONSLUT_TRANS;
				iResult = UC_SDK_Success;
			}
			break;
		case CALL_E_EVT_CALL_ATD_TRANSFER_FAILED:
			{
				WARN_LOG("----Consult Trans Failed");
				iType = EM_CONSLUT_TRANS;
				iResult = UC_SDK_Failed;
			}
			break;
		default:
			break;
	}

	if(NULL == UCCallMgr::OnCallTransEventCB)
	{
		ERROR_LOG("----OnCallTransEventCB is NULL");
		return false;
	}

	INFO_LOG("----Enter OnCallTransEventCB");
	UCCallMgr::OnCallTransEventCB(iType,iResult);
	INFO_LOG("----Leave OnCallTransEventCB");

	return true;

}

