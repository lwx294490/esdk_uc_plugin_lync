#ifndef VOS_SEMA_H
#define VOS_SEMA_H

#if VOS_APP_OS == VOS_OS_WIN32

#else
	#include <semaphore.h>
#endif

#include "vos_config.h"
namespace VPP{  
typedef struct tagVOSSemaphore 
{
#if VOS_APP_OS == VOS_OS_WIN32
    HANDLE sem;
#else
    sem_t sem;
#endif

}VOS_Sem;


#if VOS_APP_OS != VOS_OS_VXWORKS
ULONG VOS_CreateSemaphore( ULONG ulInitValue, VOS_Sem**pstVosSem );
ULONG VOS_DestroySemaphore( VOS_Sem *pstVosSem );
ULONG VOS_SemPost(VOS_Sem *pstVosSem);
ULONG VOS_SemWait( VOS_Sem *pstVosSem );
ULONG VOS_SemTryWait( VOS_Sem *pstVosSem );
ULONG VOS_SemWaitTimeout(VOS_Sem *pstVosSem, ULONG ulTimeout);
ULONG VOS_GetSemValue( VOS_Sem *pstVosSem );

#endif

}//end namespace

#endif /* __VOS_SEMA_H__ */
