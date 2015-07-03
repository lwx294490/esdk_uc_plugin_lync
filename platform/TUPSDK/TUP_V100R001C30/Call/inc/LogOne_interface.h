/*******************************************************************************
* 版权         :   2010-2011, Huawei Tech.Co.,Ltd
* 作者         :   终端公共平台团队 
* 日期         :   2014-5-5
* 版本号       :   TUP V100R001C30
* 描述         :   统一日志接口头文件
* 历史记录     :   
******************************************************************************/

#ifndef LOGONE_INTERFACE_H
#define LOGONE_INTERFACE_H

//#include "LogOne.h"

#if 1
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#endif

typedef void * LOGONE_HANLE;

#if 0
/* 关闭日志文件 */
typedef enum tagLOGONE_E_LOG_LEVEL
{
	LOGONE_E_LOG_ERROR = 0,    // 错误(运行日志)
	LOGONE_E_LOG_WARNING,      // 告警(运行日志)
	LOGONE_E_LOG_INFO,         // 提示(运行日志)
    LOGONE_E_LOG_DEBUG         // 调试(运行日志)
}LOGONE_E_LOG_LEVEL;

#endif

/* 关闭日志文件 */
typedef enum tagE_LOG_LEVEL
{
	E_LOG_ERROR = 0,    // 错误(运行日志)
	E_LOG_WARNING,      // 告警(运行日志)
	E_LOG_INFO,         // 提示(运行日志)
    E_LOG_DEBUG         // 调试(运行日志)
}E_LOG_LEVEL;


#ifdef  _lint
#ifndef __FUNCTION__
#define __FUNCTION__	""
#endif
#endif

#define BASIC_INFO				__FUNCTION__, __FILE__, __LINE__

typedef struct tagLOGONE_S_CONFIG
{
    char *          pucPath;        /* 日志文件路径 */
    int             lMaxSizeKB;     /* 日志大小，单位KB */
    int             lFileCount;     /* 支持日志文件总个数 */
    E_LOG_LEVEL     enLogLevel;     /* 日志级别 */
}LOGONE_S_CONFIG, *LOGONE_S_CONFIG_PTR;


/*****************************************************************************
 函 数 名  : LogOne_StartLog
 功能描述  : 日志模块初始化接口，所以使用该模块日志输出接口最终打印到同一份
             日志文件中
 输入参数  : const VOS_UINT8* szPath  
 输出参数  : 无
 返 回 值  : LOGONE_HANLE
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : jianghaiping 00191694
    修改内容   : 新生成函数

*****************************************************************************/
LOGONE_HANLE LogOne_StartLog(const LOGONE_S_CONFIG_PTR pstLogConfig);


/*****************************************************************************
 函 数 名  : LogOne_CloseLog
 功能描述  : 关闭日志打印,可以重新调用LogOne_StartLog开启日志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : jianghaiping 00191694
    修改内容   : 新生成函数

*****************************************************************************/
void     LogOne_CloseLog();


/*****************************************************************************
 函 数 名  : LogOne_SetPrintLevel
 功能描述  : 设置统一日志级别
 输入参数  : E_LOG_LEVEL enLogLevel  
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : jianghaiping 00191694
    修改内容   : 新生成函数

*****************************************************************************/
void   LogOne_SetPrintLevel(E_LOG_LEVEL enLogLevel);


/*****************************************************************************
 函 数 名  : LogOne_Outputf
 功能描述  : 日志输出接口
 输入参数  : VOS_INT8  *pszModelName     
             E_LOG_LEVEL enLogLevel      
             const VOS_CHAR* szFunction  
             const VOS_CHAR* szFile      
             VOS_INT32 iLine             
             const VOS_INT8 *pszFmt      
             ...                         
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : jianghaiping 00191694
    修改内容   : 新生成函数

*****************************************************************************/
void     LogOne_Outputf(char  *pszModelName, 
                                    E_LOG_LEVEL enLogLevel, const char* szFunction,
                                    const char* szFile, int iLine, const char *pszFmt, ...);


//todo chenyake
void  LogOne_Outputf_test(char  *pszModelName, E_LOG_LEVEL enLogLevel, const char* szFunction,
                                    const char* szFile, int iLine, const char *pszFmt, va_list valist);


#define LOGONE_D_OUTPUT(pszModelName, ulLevel, fmt,...) \
        LogOne_Outputf(pszModeName, ulLevel, BASIC_INFO, ##fmt)

#define LOGONE_D_DEBUG(pszModelName, fmt,...) \
        LogOne_Outputf(pszModelName, E_LOG_DEBUG, BASIC_INFO, ##fmt)

#define LOGONE_D_INFO(pszModelName, fmt,...) \
        LogOne_Outputf(pszModelName, E_LOG_INFO, BASIC_INFO, ##fmt)
        
#define LOGONE_D_WARNING(pszModelName, fmt,...) \
        LogOne_Outputf(pszModelName, E_LOG_WARNING, BASIC_INFO, ##fmt)

#define LOGONE_D_ERROR(pszModelName, fmt,...) \
        LogOne_Outputf(pszModelName, E_LOG_ERROR, BASIC_INFO, ##fmt)

#if 1
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#endif

#endif //LOGONE_INTERFACE_H


