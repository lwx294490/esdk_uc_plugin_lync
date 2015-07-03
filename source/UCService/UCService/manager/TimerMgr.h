#ifndef __TIMER_MGR_H__
#define __TIMER_MGR_H__

#include "./vos/vos.h"
#include <map>
#include <string>

// ¶¨Ê±Æ÷ÊµÀý
#define TimerMgrInstance()		(TimerMgr::instance())

typedef void (*OnTimer)(unsigned int);

struct TIMER_DATA
{
	unsigned int elapse;
	unsigned int left;
};

typedef std::map<unsigned int, TIMER_DATA> TIMER_MAP;

class TimerMgr
{
private:
	TimerMgr(void);
	~TimerMgr(void);

public:
	static TimerMgr& instance();
	void init(OnTimer timercbfunc);
	void uninit();
	void settimer(unsigned int timerId, unsigned int elapse);
	void killtimer(unsigned int timerId);

private:
	static unsigned long __stdcall threadproc(void *param);
private:
	VOS_Thread* m_threadHandle;
	VPP::VOS_Mutex* m_mutex;
	TIMER_MAP m_TimerMap;
	bool m_bStop;
	OnTimer m_TimerCBFunc;
};

#endif
