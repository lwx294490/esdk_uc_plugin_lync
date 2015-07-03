#pragma once
#include "./vos/vos.h"
#include <queue>
#include "UCEvent.h"

class CUCEventMgr
{
public:
	
public:
	CUCEventMgr(void);
	~CUCEventMgr(void);
public:
	static inline CUCEventMgr& Instance()
	{
		static CUCEventMgr inst;
		return inst;
	}
	static inline void Destroy()
	{		
	}
public:
	static void *HandleEventThread(void *argc);
	void PushEvent(UCEvent*);
	UCEvent* PopEvent();

	void Init(void);
	void Uninit(void);
private:
	void SetIsStart(bool);
	bool GetIsStart(void);
private:
	VOS_Thread *m_pVosThread;

	VOS_Mutex *m_pQueueMutex;	
	std::queue<UCEvent*> m_EventQueue;

	VOS_Mutex *m_pIsStartMutex;
	bool m_bIsStart;

};
