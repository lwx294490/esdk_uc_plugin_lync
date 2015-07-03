#ifndef _TUP_IM_EXTENDDEF_H_
#define _TUP_IM_EXTENDDEF_H_

#include "tup_im_basedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

/** \brief �ļ�·������ */
#define IM_D_MAX_FILEPATH_LENGTH (260) 

/** \brief ����ID���� */
#define IM_D_MAX_SMSID_LENGTH (16) 

/** \brief �������ݳ��� */
#define IM_D_MAX_SMSCONENT_LENGTH (350) 

/** \brief �����ռ��˳��� */
#define IM_D_MAX_SMSRECEIVEER_LENGTH (1000) 

/** \brief �ļ�������ֹԭ�� */
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

/** \brief �ļ���Ϣ */
typedef struct tagIM_S_P2PFILE_INFO
{
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; /**< �Է��˺� */ 
    TUP_CHAR filePath[IM_D_MAX_FILEPATH_LENGTH]; /**< �����ļ�·�� */ 
}IM_S_P2PFILE_INFO;


/** \brief �����ļ����� */
typedef struct tagIM_S_SENDP2PFILE_ARG
{
    IM_S_P2PFILE_INFO fileInfo;  /**< �ļ���Ϣ */
    TUP_UINT32 timeoutSeconds; /**< �ļ�����ȴ���ʱʱ�� */ 
    TUP_BOOL isEncrypt; /**< �Ƿ���м��ܣ����ܻ�Ӱ�촫���ٶȣ� */ 
}IM_S_SENDP2PFILE_ARG;


/** \brief �����ļ� */
typedef struct tagIM_S_ACCEPTP2PFILE_ARG
{
    IM_S_P2PFILE_INFO fileInfo;  /**< �ļ���Ϣ */
}IM_S_ACCEPTP2PFILE_ARG;

/** \brief �ܾ��ļ����� */
typedef struct tagIM_S_REJECTP2PFILE_ARG
{
    IM_S_P2PFILE_INFO fileInfo;  /**< �ļ���Ϣ */
}IM_S_REJECTP2PFILE_ARG;

/** \brief ȡ���ļ����� */
typedef struct tagIM_S_CANCELP2PFILE_ARG
{
    IM_S_P2PFILE_INFO fileInfo;  /**< �ļ���Ϣ */
}IM_S_CANCELP2PFILE_ARG;

/** \brief �ļ�������֪ͨ */
typedef struct tagIM_S_P2PFILE_RESULT_NOTIFY
{
	TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];		/** \brief �Է��˺� */
	TUP_CHAR fileName[IM_D_MAX_DESC_LENGTH];		/** \brief �ļ��� */
	TUP_INT32 result; /**< ��� */
}IM_S_P2PFILE_RESULT_NOTIFY;


/** \brief �ļ��������֪ͨ */
typedef struct tagIM_S_FILEPROCESS_NOTIFY
{
	TUP_CHAR	account[IM_D_MAX_ACCOUNT_LENGTH];		/** \brief �Է��˺� */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];			/** \brief �ļ��� */
	TUP_INT64	current;								/** \brief ��ǰ�Ѵ����С */
	TUP_INT64	total;									/** \brief �ļ��ܴ�С */
	TUP_CHAR	dir[IM_D_MAX_DESC_LENGTH];				/** \brief �ļ������� */
	TUP_INT64	totalFileCount;							/** \brief �ļ����� */
	TUP_INT32	currentFileIndex;						/** \brief ��ǰ�ļ���� */
	TUP_INT64	currentFileSize;						/** \brief �ļ����Ѿ�����Ĵ�С */
	TUP_INT64	totalFileSize;							/** \brief �ļ��������ļ��ܴ�С */
}IM_S_FILEPROCESS_NOTIFY;

/** \brief �յ��ļ���������֪ͨ */
typedef struct tagIM_S_P2PFILECHOOSE_NOTIFY
{
	TUP_CHAR targetAccount[IM_D_MAX_ACCOUNT_LENGTH];	/** \brief �Է��˺� */
	TUP_CHAR fileName[IM_D_MAX_DESC_LENGTH];			/** \brief �ļ��� */
	TUP_INT64 totalSize;								/** \brief �ļ��ܴ�С */
	TUP_BOOL bIsPic;									/** \brief �Ƿ���ͼƬ */
	TUP_BOOL bisDir;									/** \brief �Ƿ����ļ��� */
}IM_S_P2PFILECHOOSE_NOTIFY;

/** \brief �ļ������ϱ��ļ���Ϣ */
typedef struct tagIM_S_P2PFILESTATISTIC_NOTIFY
{
	TUP_CHAR	account[IM_D_MAX_ACCOUNT_LENGTH];			/** \brief �Է��˺� */
	TUP_CHAR	fileName[IM_D_MAX_DESC_LENGTH];				/** \brief �ļ��� */
	IM_E_FILETRANSFER_P2PFILESTOP_REASON	reason;			/** \brief ֹͣԭ�� */
}IM_S_P2PFILESTATISTIC_NOTIFY;


/** \brief ���ŷ��� */
typedef struct tagIM_S_SENDSMS_ARG
{
    TUP_CHAR msgID[IM_D_MAX_SMSID_LENGTH];					/**< �ͻ��˲�������ϢID */ 
    TUP_CHAR bindNo[IM_D_MAX_PHONE_LENGTH];					/**< ��ǰ�û��İ󶨺��� */ 
    TUP_CHAR content[IM_D_MAX_SMSCONENT_LENGTH];			/**< �������� */ 
    TUP_CHAR receiverList[IM_D_MAX_SMSRECEIVEER_LENGTH];	/**< �������б��԰�Ƿֺŷָ� */ 
    TUP_CHAR sendTime[IM_D_MAX_TIMESTAMP_LENGTH];			/**< ���ŷ���ʱ�� 19000000000000��������ʱ���룩 */ 
	TUP_BOOL needReceipt;									/**< �Ƿ���Ҫ��ִ */ 
}IM_S_SENDSMS_ARG;

/** \brief ����֪ͨ */
typedef struct tagIM_S_SENDSMS_NOTIFY
{
    TUP_CHAR msgID[IM_D_MAX_SMSID_LENGTH];			/**< �ͻ��˲�������ϢID */ 
    TUP_CHAR origin[IM_D_MAX_PHONE_LENGTH];			/**< ���ͷ����� */ 
	TUP_CHAR target[IM_D_MAX_PHONE_LENGTH];			/**< ���շ�����*/
    TUP_CHAR content[IM_D_MAX_SMSCONENT_LENGTH];	/**< �������� */ 
    TUP_CHAR sendTime[IM_D_MAX_TIMESTAMP_LENGTH];	/**< ���ŷ���ʱ�� 19000000000000��������ʱ���룩 */ 
    IM_E_SMS_NOTIFY_TYPE smsType;					/**<���յ��Ķ�����Ϣ������ */
	TUP_INT64 serverMsgID;							/**< ��������ϢID */
}IM_S_SENDSMS_NOTIFY;

#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */



#endif //_TUP_IM_EXTENDDEF_H_