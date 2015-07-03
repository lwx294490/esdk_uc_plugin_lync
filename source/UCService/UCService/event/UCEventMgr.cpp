#include "StdAfx.h"
#include "Log.h"
#include "UCEventMgr.h"

CUCEventMgr::CUCEventMgr(void):m_pVosThread(NULL),m_pQueueMutex(NULL),m_pIsStartMutex(NULL),m_bIsStart(false)
{
	m_pQueueMutex = VOS_CreateMutex();
	m_pIsStartMutex = VOS_CreateMutex();
}

CUCEventMgr::~CUCEventMgr(void)
{
	if(NULL != m_pQueueMutex)
	{
		VOS_DestroyMutex(m_pQueueMutex);
		m_pQueueMutex = NULL;
	}
	if(NULL !=  m_pIsStartMutex)
	{
		VOS_DestroyMutex(m_pIsStartMutex);
		m_pIsStartMutex = NULL;
	}	
}
void *CUCEventMgr::HandleEventThread(void *argc)
{
	INFO_LOG("HandleEvent Thread Start.");
	CUCEventMgr* pEmgr = (CUCEventMgr*)argc;
	if(NULL == pEmgr)
	{
		return NULL;
	}
	UCEvent* pEvent = NULL;
	bool bIsStart = pEmgr->GetIsStart();
	while(bIsStart)
	{
		pEvent = pEmgr->PopEvent();
		if(NULL != pEvent)
		{
			if(!pEvent->DoHandle())
			{
				ERROR_LOG("Process Event Failed.");
			}
			SAFE_DELETE(pEvent);
		}

		Sleep(200);

		bIsStart = pEmgr->GetIsStart();
		if(!bIsStart)
		{
			break;
		}
	}

	INFO_LOG("HandleEvent Thread End.");
	return NULL;
}


void CUCEventMgr::Init(void)
{
	SetIsStart(true);
	if (VOS_OK != VOS_CreateThread((VOS_THREAD_FUNC)HandleEventThread, (void *)this, 
		&m_pVosThread, VOS_DEFAULT_STACK_SIZE))
	{
		WARN_LOG("Create play thread failed");
		return;
	}
	INFO_LOG("VOS_CreateThread Success.");
	
	return;
}
void CUCEventMgr::Uninit(void)
{
	DEBUG_TRACE("");
	SetIsStart(false);
	Sleep(1000);
}
void CUCEventMgr::SetIsStart(bool bValue)
{
	VOS_MutexLock(m_pIsStartMutex);
	m_bIsStart = bValue;
	VOS_MutexUnlock(m_pIsStartMutex);

}
bool CUCEventMgr::GetIsStart(void)
{
	VOS_MutexLock(m_pIsStartMutex);
	bool bRet = m_bIsStart;
	VOS_MutexUnlock(m_pIsStartMutex);
	return bRet;
}
void CUCEventMgr::PushEvent(UCEvent* pEvent)
{
	VOS_MutexLock(m_pQueueMutex);
	m_EventQueue.push(pEvent);
	VOS_MutexUnlock(m_pQueueMutex);
}
UCEvent* CUCEventMgr::PopEvent()
{
	UCEvent* pEvent = NULL;
	VOS_MutexLock(m_pQueueMutex);
	if(!m_EventQueue.empty())
	{
		pEvent = m_EventQueue.front();
		m_EventQueue.pop();
	}
	VOS_MutexUnlock(m_pQueueMutex);
	return pEvent;
}
