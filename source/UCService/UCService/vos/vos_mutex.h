#ifndef VOS_MUTEX_H
#define VOS_MUTEX_H
#ifndef WIN32
#include <pthread.h>
#endif
namespace VPP
{
	typedef struct tagVOSMutex
	{
	#if VOS_APP_OS == VOS_OS_WIN32
	  HANDLE  mutex;
	#else
	  pthread_mutex_t  mutex;
	#endif
	}VOS_Mutex;


	VOS_Mutex *VOS_CreateMutex( );
	ULONG VOS_DestroyMutex( VOS_Mutex *pstMutex );
	ULONG VOS_MutexLock( VOS_Mutex *pstMutex );
	ULONG VOS_MutexUnlock( VOS_Mutex *pstMutex );
}//end namespace

#endif /* __VOS_MUTEX_H__ */
