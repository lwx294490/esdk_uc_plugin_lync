#include "vos.h"

//lint -e438
namespace VPP
{
	VOS_Mutex *VOS_CreateMutex(void )
	{
		VOS_Mutex *pstMutex = VOS_NULL ;

		pstMutex = (VOS_Mutex *) VOS_malloc (sizeof(VOS_Mutex));//lint !e838
		if (NULL == pstMutex)
		{
			return NULL;
		}
    
		#if VOS_APP_OS == VOS_OS_LINUX
		ULONG ulResult = VOS_OK ;
		ulResult = (ULONG)pthread_mutex_init( &pstMutex->mutex, 0);
		if( VOS_OK != ulResult )
		{
			VOS_free( pstMutex );        
			return VOS_NULL ;    
		}
		#elif VOS_APP_OS == VOS_OS_WIN32
		pstMutex->mutex = CreateMutex(NULL,0,NULL);
		if (NULL == pstMutex->mutex)
		{
			VOS_free( pstMutex );        
			return VOS_NULL ;    
		}
		#endif

		return pstMutex ;
	}//lint !e529


	ULONG VOS_DestroyMutex( VOS_Mutex *pstMutex )
	{
		ULONG ulResult = VOS_OK ;

		#if VOS_APP_OS == VOS_OS_LINUX
		pthread_mutex_destroy( &pstMutex->mutex );
		#elif VOS_APP_OS == VOS_OS_WIN32
		CloseHandle(pstMutex->mutex);
		#endif
		VOS_free( pstMutex );

		return ulResult ;
	}


	ULONG VOS_MutexLock( VOS_Mutex *pstMutex )
	{
		ULONG ulResult = VOS_OK ;
    
		#if VOS_APP_OS == VOS_OS_LINUX 
		ulResult = (ULONG)pthread_mutex_lock(&pstMutex->mutex);
		if( VOS_OK != ulResult )
		{
			return ulResult ;
		}
		#elif VOS_APP_OS == VOS_OS_WIN32
		ulResult = WaitForSingleObject(pstMutex->mutex,INFINITE);//lint !e838
		if(WAIT_OBJECT_0 != ulResult)//lint !e835
		{
			return VOS_ERR;
		}
		#endif
		return VOS_OK ;
	}//lint !e818

	ULONG VOS_MutexUnlock( VOS_Mutex *pstMutex )
	{    
		#if VOS_APP_OS == VOS_OS_LINUX
		ULONG ulResult = VOS_OK ;
		ulResult = (ULONG)pthread_mutex_unlock(&pstMutex->mutex);
		if( VOS_OK != ulResult )
		{
			return ulResult ;
		}
		#elif VOS_APP_OS == VOS_OS_WIN32
		if (TRUE != ReleaseMutex(pstMutex->mutex))
		{
			return VOS_ERR;
		}
		#endif
		return VOS_OK ;
	}//lint !e818 !e529
}//end namespace

//lint +e438

