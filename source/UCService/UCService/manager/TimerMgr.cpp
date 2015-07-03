#include "TimerMgr.h"
#include "Log.h"


TimerMgr::TimerMgr(void)
	: m_threadHandle(NULL)
	, m_mutex(NULL)
	, m_bStop(false)
	, m_TimerCBFunc(NULL)
{	
}


TimerMgr::~TimerMgr(void)
{
	try
	{
		m_bStop = true;
		m_TimerMap.clear();

		if(VOS_NULL != m_threadHandle)
		{
			(void)VOS_ThreadJoin(m_threadHandle);
			m_threadHandle = NULL;
		}
		if (VOS_NULL != m_mutex)
		{
			(void)VOS_DestroyMutex(m_mutex);
			m_mutex = NULL;
		}
		m_bStop = false;

		m_TimerCBFunc = NULL;
	}
	catch(...){}
}

TimerMgr& TimerMgr::instance()
{
	static TimerMgr s_TimerMgr;
	return s_TimerMgr;
}

void TimerMgr::init(OnTimer timercbfunc)
{
	m_bStop = false;
	if (NULL == m_threadHandle)
	{
		(void)VOS_CreateThread(TimerMgr::threadproc,this,&m_threadHandle,0);
		m_mutex = VOS_CreateMutex();
	}
	m_TimerCBFunc = timercbfunc;
}

void TimerMgr::uninit()
{
	if (NULL != m_mutex)
	{
		(void)VOS_MutexLock(m_mutex);
	}
	m_bStop = true;
	m_TimerMap.clear();
	if (NULL != m_mutex)
	{
		(void)VOS_MutexUnlock(m_mutex);
	}
	
	if(VOS_NULL != m_threadHandle)
	{
		(void)VOS_ThreadJoin(m_threadHandle);
		m_threadHandle = NULL;
	}
	if (VOS_NULL != m_mutex)
	{
		(void)VOS_DestroyMutex(m_mutex);
		m_mutex = NULL;
	}
	m_TimerCBFunc = NULL;
}

void TimerMgr::settimer(unsigned int timerId, unsigned int elapse)
{
	INFO_LOG("settimer:id=%d",timerId);
	if (NULL == m_mutex)
	{
		ERROR_LOG("m_mutex is NULL");
		return;
	}

	(void)VOS_MutexLock(m_mutex);
	if (m_TimerMap.end() != m_TimerMap.find(timerId))
	{
		(void)VOS_MutexUnlock(m_mutex);
		return;
	}

	TIMER_DATA timer_data;
	timer_data.elapse = elapse;
	timer_data.left = elapse;
	(void)m_TimerMap.insert(std::make_pair(timerId, timer_data));
	(void)VOS_MutexUnlock(m_mutex);
}

void TimerMgr::killtimer(unsigned int timerId)
{
	INFO_LOG("killtimer:id=%d",timerId);
	if (NULL == m_mutex)
	{
		ERROR_LOG("m_mutex is NULL");
		return;
	}
	(void)VOS_MutexLock(m_mutex);
	TIMER_MAP::iterator itor = m_TimerMap.find(timerId);
	if (m_TimerMap.end() != itor)
	{
		m_TimerMap.erase(itor);
	}
	(void)VOS_MutexUnlock(m_mutex);
}

unsigned long __stdcall TimerMgr::threadproc(void *para)
{
	TimerMgr* pMgr=(TimerMgr*)para;
	while (!instance().m_bStop)
	{
		(void)VOS_MutexLock(instance().m_mutex);
		TIMER_MAP::iterator itor = instance().m_TimerMap.begin();
		for (; instance().m_TimerMap.end() != itor; itor++)
		{
			if (0 == --(itor->second.left))
			{
				itor->second.left = itor->second.elapse;
				if(NULL != pMgr->m_TimerCBFunc)
				{
					pMgr->m_TimerCBFunc(itor->first);
				}

			}
		}
		(void)VOS_MutexUnlock(instance().m_mutex);
		Sleep(1000);

	}

	return 1;
}
