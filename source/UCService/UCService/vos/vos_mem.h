#ifndef VOS_MEM_H
#define VOS_MEM_H

#include <stdlib.h>

namespace VPP
{
	VOID *VOS_malloc( LONG size );
	VOID VOS_free( VOID *buff );
}//end namespace
#endif /* __VOS_MEM_H__ */
