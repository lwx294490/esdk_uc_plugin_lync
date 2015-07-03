#ifndef VOS_TIME_H
#define VOS_TIME_H

namespace VPP{  

extern  VOID  VOS_Sleep( ULONG ulMs );

extern  ULONG  VOS_GetTicks();

extern  VOID  VOS_Delay (ULONG ulDelayTimeMs);

}//end namespace

#endif /* __VOS_TIME_H__ */
