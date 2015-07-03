#ifndef _TUP_IM_EXTENDDEF_H_
#define _TUP_IM_EXTENDDEF_H_

#include "tup_im_basedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

/** \brief 文件路径长度 */
#define IM_D_MAX_FILEPATH_LENGTH (260) 

/** \brief 短信ID长度 */
#define IM_D_MAX_SMSID_LENGTH (16) 

/** \brief 短信内容长度 */
#define IM_D_MAX_SMSCONENT_LENGTH (350) 

/** \brief 短信收件人长度 */
#define IM_D_MAX_SMSRECEIVEER_LENGTH (1000) 

/** \brief 文件传输终止原因 */
typedef enum tagIM_E_FILETRANSFER_P2PFILESTOP_REASON
{
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_UNKNOW	= -1,
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_NORMAL	= 0,
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_TIMEOUT = 1,
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_SENDERROR = 2,
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_ACCEPTERROR = 3,
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_COMPLETED = 4,
	IM_E_FILETRANSFER_P2PFILESTOP_REASON_ABNORMAL = 5,
}IM_E_FILETRANSFER_P2PFILESTOP_REASON;

/** \brief 文件信息 */
typedef struct tagIM_S_P2PFILE_INFO
{
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; /**< 对方账号 */ 
    TUP_CHAR filePath[IM_D_MAX_FILEPATH_LENGTH]; /**< 本地文件路径 */ 
}IM_S_P2PFILE_INFO;


/** \brief 发送文件请求 */
typedef struct tagIM_S_SENDP2PFILE_ARG
{
    IM_S_P2PFILE_INFO fileInfo;  /**< 文件信息 */
    TUP_UINT32 timeoutSeconds; /**< 文件传输等待超时时间 */ 
    TUP_BOOL isEncrypt; /**< 是否进行加密（加密会影响传输速度） */ 
}IM_S_SENDP2PFILE_ARG;


/** \brief 接收文件 */
typedef struct tagIM_S_ACCEPTP2PFILE_ARG
{
    IM_S_P2PFILE_INFO fileInfo;  /**< 文件信息 */
}IM_S_ACCEPTP2PFILE_ARG;

/** \brief 拒绝文件传输 */
typedef struct tagIM_S_REJECTP2PFILE_ARG
{
    IM_S_P2PFILE_INFO fileInfo;  /**< 文件信息 */
}IM_S_REJECTP2PFILE_ARG;

/** \brief 取消文件传输 */
typedef struct tagIM_S_CANCELP2PFILE_ARG
{
    IM_S_P2PFILE_INFO fileInfo;  /**< 文件信息 */
}IM_S_CANCELP2PFILE_ARG;

/** \brief 文件传输结果通知 */
typedef struct tagIM_S_P2PFILE_RESULT_NOTIFY
{
	TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];		/** \brief 对方账号 */
	TUP_CHAR fileName[IM_D_MAX_DESC_LENGTH];		/** \brief 文件名 */
	TUP_INT32 result; /**< 结果 */
}IM_S_P2PFILE_RESULT_NOTIFY;


/** \brief 文件传输进度通知 */
typedef struct tagIM_S_FILEPROCESS_NOTIFY
{
	TUP_CHAR	account[IM_D_MAX_ACCOUNT_LENGTH];		/** \brief 对方账号 */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];			/** \brief 文件名 */
	TUP_INT64	current;								/** \brief 当前已传输大小 */
	TUP_INT64	total;									/** \brief 文件总大小 */
	TUP_CHAR	dir[IM_D_MAX_DESC_LENGTH];				/** \brief 文件夹名称 */
	TUP_INT64	totalFileCount;							/** \brief 文件总数 */
	TUP_INT32	currentFileIndex;						/** \brief 当前文件序号 */
	TUP_INT64	currentFileSize;						/** \brief 文件夹已经传输的大小 */
	TUP_INT64	totalFileSize;							/** \brief 文件夹所有文件总大小 */
}IM_S_FILEPROCESS_NOTIFY;

/** \brief 收到文件传输请求通知 */
typedef struct tagIM_S_P2PFILECHOOSE_NOTIFY
{
	TUP_CHAR targetAccount[IM_D_MAX_ACCOUNT_LENGTH];	/** \brief 对方账号 */
	TUP_CHAR fileName[IM_D_MAX_DESC_LENGTH];			/** \brief 文件名 */
	TUP_INT64 totalSize;								/** \brief 文件总大小 */
	TUP_BOOL bIsPic;									/** \brief 是否是图片 */
	TUP_BOOL bisDir;									/** \brief 是否是文件夹 */
}IM_S_P2PFILECHOOSE_NOTIFY;

/** \brief 文件传输上报文件信息 */
typedef struct tagIM_S_P2PFILESTATISTIC_NOTIFY
{
	TUP_CHAR	account[IM_D_MAX_ACCOUNT_LENGTH];			/** \brief 对方账号 */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];				/** \brief 文件名 */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON	reason;			/** \brief 停止原因 */
}IM_S_P2PFILESTATISTIC_NOTIFY;


/** \brief 短信发送 */
typedef struct tagIM_S_SENDSMS_ARG
{
    TUP_CHAR msgID[IM_D_MAX_SMSID_LENGTH];					/**< 客户端产生的消息ID */ 
    TUP_CHAR bindNo[IM_D_MAX_PHONE_LENGTH];					/**< 当前用户的绑定号码 */ 
    TUP_CHAR content[IM_D_MAX_SMSCONENT_LENGTH];			/**< 短信内容 */ 
    TUP_CHAR receiverList[IM_D_MAX_SMSRECEIVEER_LENGTH];	/**< 收信人列表，以半角分号分割 */ 
    TUP_CHAR sendTime[IM_D_MAX_TIMESTAMP_LENGTH];			/**< 短信发送时间 19000000000000（年月日时分秒） */ 
	TUP_BOOL needReceipt;									/**< 是否需要回执 */ 
}IM_S_SENDSMS_ARG;

/** \brief 短信通知 */
typedef struct tagIM_S_SENDSMS_NOTIFY
{
    TUP_CHAR msgID[IM_D_MAX_SMSID_LENGTH];			/**< 客户端产生的消息ID */ 
    TUP_CHAR origin[IM_D_MAX_PHONE_LENGTH];			/**< 发送方号码 */ 
	TUP_CHAR target[IM_D_MAX_PHONE_LENGTH];			/**< 接收方号码*/
    TUP_CHAR content[IM_D_MAX_SMSCONENT_LENGTH];	/**< 短信内容 */ 
    TUP_CHAR sendTime[IM_D_MAX_TIMESTAMP_LENGTH];	/**< 短信发送时间 19000000000000（年月日时分秒） */ 
    IM_E_SMS_NOTIFY_TYPE smsType;					/**<接收到的短信消息的类型 */
	TUP_INT64 serverMsgID;							/**< 服务器消息ID */
}IM_S_SENDSMS_NOTIFY;

#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */



#endif //_TUP_IM_EXTENDDEF_H_