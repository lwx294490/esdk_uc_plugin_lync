#ifndef _TUP_IM_BASEDEF_H_
#define _TUP_IM_BASEDEF_H_

#include "tup_def.h"
#include "tup_im_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

//--------------------------------------------------------------���ȶ��� begin--------------------------------------------------------------

#define IM_D_GENEAL_LENGTH   (32)

#define IM_D_ICON_LENGTH      (1024)
/** \brief �ʺų��� */
#define IM_D_MAX_ACCOUNT_LENGTH (32) 

/** \brief �������� */
#define IM_D_MAX_NAME_LENGTH (512) 

/** \brief ���������� */
#define IM_D_MAX_DEPTNAME_LENGTH (1024) 

/** \brief ���볤�� */
#define IM_D_MAX_PASSWORD_LENGTH (512) 

/** \brief �汾�ų��� */
#define IM_D_MAX_VERSION_LENGTH (100) 

/** \brief ʱ������� */
#define IM_D_MAX_TIMESTAMP_LENGTH (15) 

/** \brief ���볤�� */
#define IM_D_MAX_PHONE_LENGTH (256) 

/** \brief ���ճ��� */
#define IM_D_MAX_BIRTHDAY_LENGTH (64) 

/** \brief �������ֳ��� */
#define IM_D_MAX_DESC_LENGTH (1024) 

/** \brief ״̬�������� */
#define IM_D_MAX_STATUS_DESCLEN (50)

/** \brief IP��ַ���� */
#define IM_D_IP_LENGTH  (16)   

/** \brief ���䳤�� */
#define IM_D_AGE_LENGTH  (8)   

/** \brief ȺID���� */
#define IM_D_GROUPID_LENGTH  (64)   

/** \brief ��ʱ��Ϣ���ֳ��� */
#define IM_D_MAX_MESSAGE_LENGTH (1024*10) 

/** \brief ���PROGID */
#define IM_D_MAX_PROGID_LENGTH (1024) 

/** \brief ����������� */
#define IM_D_MAX_PLUGINPARAM_LENGTH (1024) 

/** \brief �������URL���� */
#define IM_D_MAX_PLUGINURL_LENGTH (1024) 

/** \brief token ���� */
#define IM_D_LOGIN_TOKEN_LENGTH (1024)

/** \brief ·������ */
#define IM_D_MAX_PATH_LENGTH (1024)

/** \brief �ַ���� ���� */
#define IM_D_MAX_CHAR_LENGTH (1024*10)
//--------------------------------------------------------------���ȶ��� end--------------------------------------------------------------

//--------------------------------------------------------------ö�� begin--------------------------------------------------------------

/** \brief �ص�ͬʱ���¼�ID */
typedef enum tagIM_E_EVENT_ID
{
	IM_E_EVENT_IM_ORIGIN	= -1,					/**< ��ʼ�� */
/*******************************************************************��������&֪ͨ*************************************************************************************/
    IM_E_EVENT_IM_HEARTBEAT_NOTIFY,     /**< ���������� */
    IM_E_EVENT_IM_SYSURLRET_NOTIFY,     /**< ϵͳ��ַ����֪ͨ IM_S_SYSURLS_NOTIFY */
	IM_E_EVENT_IM_SYSTEMBULLETIN_NOTIFY,/**< ϵͳ����֪ͨ	 IM_S_SYSTEMBULLETIN_NOTIFY*/
	IM_E_EVENT_IM_KICKOUT_NOTIFY,		/**< �û�����֪ͨ	IM_S_CODECHAT_NOTIFY*/
	IM_E_EVENT_IM_SMS_NOTIFY,			/**< �¶���֪ͨ		IM_S_SENDSMS_NOTIFY*/
	IM_E_EVENT_IM_LOGOUT_NOTIFY,		/**< �û��˳�		IM_S_LOGOUT_NOTIFY*/

/*******************************************************************��ϵ��&����*************************************************************************************/
    IM_E_EVENT_IM_ADDFRIEND_NOTIFY, 		/**< �Է�����Լ����ѳɹ�֪ͨ IM_S_ADDFRIEND_NOTIFY */
    IM_E_EVENT_IM_USERSTATUS_NOTIFY, 		/**< ����״̬�仯֪ͨ IM_S_USERSTATUS_NOTIFY */
	IM_E_EVENT_IM_USERINFOCHANGE_NOTIFY, 	/**< ������Ϣ�仯֪ͨ  IM_S_USERINFOCHANGE_LIST_NOTIFY*/
	IM_E_EVENT_IM_GETIMGROUPDETAIL,			/**< ��ȡIMȺ��������Ӧ��Ϣ  IM_S_GETIMGROUPDETAIL_NOTIFY*/

/*******************************************************************�̶�Ⱥ��*************************************************************************************/
    IM_E_EVENT_IM_APPLYJOIN_FIXEDGROUP_NOTIFY, 	/**< Ⱥ����Ա�յ��û�����̶�Ⱥ֪ͨ (IM_S_APPLYJOINFIXEDGROUP_NOTIFY) */
    IM_E_EVENT_IM_APPLYJOIN_FIXEDGROUP_RESULT_NOTIFY, 	/**< Ⱥ��Ա�յ�����Ա��������̶�Ⱥ֪ͨ����Ӧ IM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_MEMADD_NOTIFY, /**< �̶�Ⱥ��ӳ�Ա֪ͨ IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_MEMDEL_NOTIFY, /**< Ⱥ����ɾ����Ա֪ͨ IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_INFOCHG_NOTIFY, /**< �̶�Ⱥ��Ϣ�޸�֪ͨ IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_OWNERCHG_NOTIFY, /**< Ⱥ�����Ա���֪ͨ IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_IM_INVITEJOIN_FIXEDGROUPRESULT_NOTIFY, /**< ����Ա�յ��û����������̶�Ⱥ�������  IM_S_INVITEJOINFIXEDGROUPRESULT_NOTIFY */
	IM_E_EVENT_IM_RECEIVEINVITETO_FIXEDGROUP_NOTIFY, /**< �û��յ�����Ա����֪ͨ	IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY*/
	IM_E_EVENT_IM_RECEIVEJOIN_FIXEDGROUP_NOTIFY,	 /**< ����Ա�յ��û��������Ⱥ��֪ͨ	IM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY*/

/*******************************************************************������*************************************************************************************/
	IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY,		/**< �������Ա�б���ӳ�Ա�����Ϣ	 IM_S_DISCUSSGROUP_NOTIFY*/
	IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY,		/**< �������Ա�б�ɾ����Ա�����Ϣ	 IM_S_DISCUSSGROUP_NOTIFY*/
	IM_E_EVENT_IM_DISCUSSGROUP_INFOCHANGE_NOTIFY,				/**< Ⱥ����Ϣ����	IM_S_DISCUSSGROUP_NOTIFY*/
	IM_E_EVENT_IM_DISCUSSGROUP_WASADDEDTOGROUP_NOTIFY,			/**< ����ӵ�Ⱥ��֪ͨ	IM_S_DISCUSSGROUP_NOTIFY*/
	IM_E_EVENT_IM_DISCUSSGROUP_OWNERCHANGE_NOTIFY,				/**< Ⱥ�����Ա���	 IM_S_DISCUSSGROUP_NOTIFY*/

/*******************************************************************�ļ�����***********************************************************************************/
	IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY, 		/**< �յ��ļ���������	IM_S_P2PFILECHOOSE_NOTIFY*/
	IM_E_EVENT_IM_FILEPROCESS_NOTIFY,			/**< �ļ��������֪ͨ	IM_S_FILEPROCESS_NOTIFY */
	IM_E_EVENT_IM_FILESTATISTIC_NOTIFY,			/**< �ϱ��ļ���Ϣ	    IM_S_P2PFILESTATISTIC_NOTIFY*/
	IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY, 	/**< �ļ����俪ʼ���	IM_S_P2PFILE_RESULT_NOTIFY*/
	IM_E_EVENT_IM_P2PFILE_STOPTRESULT_NOTIFY, 	/**< �ļ�����ֹͣ���	IM_S_P2PFILE_RESULT_NOTIFY*/
	IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY,			/**<�ļ�����ֹ֪ͣͨ	IM_S_P2PFILESTATISTIC_NOTIFY*/

/***********************************************************************IM��Ϣ*************************************************************************************/
	IM_E_EVENT_IM_SENDIMINPUT_NOTIFY,			/**< ����IM����״̬��Ϣ 	IM_S_SENDIMINPUT_NOTIFY*/	
	IM_E_EVENT_IM_CODECHAT_NOTIFY,				/**< �¼�ʱ��Ϣ֪ͨ 		IM_S_CODECHAT_NOTIFY*/	
	IM_E_EVENT_IM_CHATLIST_NOTIFY,				/**< �¼�ʱ��Ϣ����֪ͨ(����) 	IM_S_CHATLIST_NOTIFY*/

}IM_E_EVENT_ID;

/** \brief ��¼��� */
typedef enum tagIM_E_LOGIN_RESUL
{
    IM_E_LOGING_RESULT_TIMEOUT = -100,	/**< ��Ϣ��ʱ */
    IM_E_LOGING_RESULT_INTERNAL_ERROR = -1,   /**< �����ڲ����� */
    IM_E_LOGING_RESULT_SUCCESS = 0,    /**< ��¼�ɹ� */
    IM_E_LOGING_RESULT_FAILED = 1,    /**< ��¼ʧ�� */
    IM_E_LOGING_RESULT_PASSWORD_ERROR = 2,	/**< ������� */
    IM_E_LOGING_RESULT_ACCOUNT_NOT_EXIST = 3,	/**< �ʺŲ����� */
    IM_E_LOGING_RESULT_ALREADY_LOGIN = 4,	/**< �û��Ѵ��� */          //TODO:����������Ƿ��IM_E_LOING_RESULT_SUCCESS�ϲ���һ��
    IM_E_LOGING_RESULT_ACCOUNT_LOCKED = 5,	/**< �ʺ������� */
    IM_E_LOGING_RESULT_NEED_NEW_VERSION = 6,	/**< ��Ҫ�����°汾�������¼ */
    IM_E_LOGING_RESULT_NOT_ACTIVE = 7,	/**< �û�δ���� */
    IM_E_LOGING_RESULT_ACCOUNT_SUSPEND = 8,	/**< �û��˺ű���ͣ */
    IM_E_LOGING_RESULT_ACCOUNT_EXPIRE = 9,	/**< �û��˺Ź��� */
    IM_E_LOGING_RESULT_DECRYPT_FAILED = 10,	/**< ��Ϣ����ʧ�� */
    IM_E_LOGING_RESULT_CERT_DOWNLOAD_FAILED = 11,	/**< ֤������ʧ�� */
    IM_E_LOGING_RESULT_CERT_VALIDATE_FAILED = 12,	/**< ֤��У��ʧ�� */
    IM_E_LOGING_RESULT_DNS_ERROR = 13	/**< ������������ */
}IM_E_LOGIN_RESULT;

    /** \brief �Ա����� */
typedef enum tagIM_E_GENDER_TYPE
{
    IM_E_GENDER_MALE = 0,		/**< �� */
    IM_E_GENDER_FEMAIL = 1,		/**< Ů*/
    IM_E_GENDER_UNKNOWN = 2			/**< δ���� */
}IM_E_GENDER_TYPE;

/** \brief Ⱥ�����Ȩ�ޱ�� */
typedef enum tagIM_E_IMGROUP_JOIN_AUTH_FLAG
{
    IM_E_IMGROUP_JOIN_AUTO = 0,			/**< �Զ����� */
    IM_E_IMGROUP_JOIN_NEED_APPROVE = 1,			/**< ��Ҫ����Ա���� */
    IM_E_IMGROUP_JOIN_DENY = 2				/**< ��������� */
}IM_E_IMGROUP_JOIN_AUTH_FLAG;

/** \brief Ⱥ��������� */
typedef enum tagIM_E_IMGROUP_TYPE
{
    IM_E_IMGROUP_FIXGROUP_TYPE = 0,  /**< �̶�Ⱥ */
    IM_E_IMGROUP_DISCUSSIONGROUP_TYPE = 1    /**< ������ */
}IM_E_IMGROUP_TYPE;

/** \brief �û�����״̬ */
typedef enum tagIM_E_USER_ONLINESTATUS
{
    IM_E_STATUS_INIT = -1,		/**< ��ʼ״̬ */
    IM_E_STATUS_OFFLINE = 0,		/**< ���� */
    IM_E_STATUS_ONLINE = 1,		/**< ���� */
    IM_E_STATUS_HIDDEN = 2,		/**< ���� */
    IM_E_STATUS_BUSY = 3,		/**< æµ */
    IM_E_STATUS_LEAVE = 4,		/**< �뿪 */
    IM_E_STATUS_DONTDISTURB = 5			/**< ������� */
}IM_E_USER_ONLINESTATUS;

/** \brief �ͻ������� */
typedef enum tagIM_E_CLIENT_TYPE 
{
	IM_E_CLIENT_TYPE_PC			= 0,		/**< PC�ն� */
	IM_E_CLIENT_TYPE_MOBILE		= 1,		/**< �ƶ��ֻ��ն� */
	IM_E_CLIENT_TYPE_WEB		= 2,		/**< web�ͻ��� */
	IM_E_CLIENT_TYPE_MOBLIEHD	= 3			/**< �ƶ�PC�ն� */
}IM_E_CLIENT_TYPE;

/** \brief IM��Ϣ���� */
typedef enum tagIM_E_IM_CHAT_TYPE
{
    IM_E_IM_CHAT_TYPE_SINGLE = 0,	/**< ���� */
    IM_E_IM_CHAT_TYPE_FIXEDGROUP = 2,	/**< �̶�Ⱥ�� */
    IM_E_IM_CHAT_TYPE_DISCUSSIONGROUP= 6,	/**< ���˻Ự������ */
}IM_E_IM_CHAT_TYPE;

/** \brief IM��Ϣ���������� */
typedef enum tagIM_E_IM_CHAT_SOURCE_FLAG
{
    IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG = 0,	/**< IM���촰�� */
    IM_E_IM_CHAT_SOURCE_FLAG_MULTIMEETING = 1,	/**< ���ݻ������촰�� */
}IM_E_IM_CHAT_SOURCE_FLAG;

/** \brief IM��Ϣ���ݸ�ʽ */
typedef enum tagIM_E_IM_CHAT_CONTENT_TYPE 
{
    IM_E_IM_CHAT_CONTENT_TYPE_TEXT = 0,	/**< ���ı� */
    IM_E_IM_CHAT_CONTENT_TYPE_RICHTEXT = 1,	/**< ���ı� */
}IM_E_IM_CHAT_CONTENT_TYPE;

/** \brief IM��������״̬ */
typedef enum tagIM_E_IM_CHAT_STATUS
{
    IM_E_IM_CHAT_STATUS_CHATTING = 0,	 /**< ��������...*/
    IM_E_IM_CHAT_STATUS_STOPPED = 1		/**< ֹͣ����...*/
}IM_E_IM_CHAT_STATUS;

/** \brief IM��Ϣ���� */
typedef enum tagIM_E_CHAT_TYPE
{
	IM_E_CHAT_TYPE_SINGLE = 0,	/**< ���� */
	IM_E_CHAT_TYPE_TEMP = 1,	/**< ��ʱ���� */
	IM_E_CHAT_TYPE_FIXEDGROUP = 2,	/**< �̶�Ⱥ�� */
	IM_E_CHAT_TYPE_TEMPGROUP = 3,	/**< ��ʱȺ�� */
	IM_E_CHAT_TYPE_HELP = 4,	/**< ���߿ͷ� */
	IM_E_CHAT_TYPE_APPNOTIFY = 5,	/**< ������Ϣ */
	IM_E_CHAT_TYPE_DISCUSSIONGROUP = 6,	/**< ���˻Ự������ */
	IM_E_CHAT_TYPE_FILETRANSFER = 7,	/**< �ļ�����֪ͨ */
	IM_E_CHAT_TYPE_SYSTEMNOTIFY	= 10,	/**< ϵͳ֪ͨ */
	IM_E_CHAT_TYPE_SYSTEMAD	= 11,	/**< ϵͳ��� */
	IM_E_CHAT_TYPE_MULTIMEETINGS = 14,	/**< �ںϻ���֪ͨ */
	IM_E_CHAT_TYPE_IMNOTIFY	= 20,	/**< IM֪ͨ��Ϣ */
	IM_E_CHAT_TYPE_AUTOREPLAY = 101,	/**< �Զ��ظ� */
}IM_E_CHAT_TYPE;

/** \brief IMý���ʽ */
typedef enum tagIM_E_IM_CHATMEDIA_TYPE
{
	tagIM_E_IM_CHATMEDIA_TYPE_TEXT = 0,	 /**< ���ı� */
	tagIM_E_IM_CHATMEDIA_TYPE_AUDIO = 1, /**< ��ý�� ���� */
	tagIM_E_IM_CHATMEDIA_TYPE_VIDEO = 2, /**< ��ý�� ��Ƶ */
	tagIM_E_IM_CHATMEDIA_TYPE_IMAGE = 3, /**< ��ý�� ͼƬ */
}IM_E_IM_CHATMEDIA_TYPE;

/** \brief ��ʷ��Ϣ������Ϣ���� */
typedef enum tagIM_E_IM_HISTORYMESSAGEMSG_TYPE 
{
	IM_E_IM_HISTORYMESSAGEMSG_TYPE_SINGLECHAT = 0,	/**< ������Ϣ */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE_GROUPCHAT = 1,	/**< ������/�̶�Ⱥ��Ϣ */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE_SMS = 2,			/**< ������Ϣ */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE_BULLETIN = 3,	/**< ϵͳ���� */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE_NOTIFY = 4,		/**< ������P2P�ļ����䣬�������룬Ⱥ�����룬Ⱥ��֪ͨ�� */
}IM_E_IM_HISTORYMESSAGEMSG_TYPE;

/** \brief ���յ��Ķ�����Ϣ������ */
typedef enum tagIM_E_SMS_NOTIFY_TYPE
{
	IM_E_SMS_NOTIFY_TYPE_RECVSMS = 0,			/**< �յ�����֪ͨ*/
	IM_E_SMS_NOTIFY_TYPE_SENDSMSSUCCESS =1 ,	/**< ���Ͷ��ųɹ�֪ͨ*/
	IM_E_SMS_NOTIFY_TYPE_SMSRECEIPT = 3,        /**< ���Ż�ִ*/
	IM_E_SMS_NOTIFY_TYPE_SMSSENDFAIL = 4,       /**< ���ŷ���ʧ��*/
	IM_E_SMS_NOTIFY_TYPE_SMSRECEIPTFAIL = 5,    /**< ���Ż�ִʧ��*/
	IM_E_SMS_NOTIFY_TYPE_SMSSEND = 6,			/**< ���Ͷ��ţ���������ʱ�ã�*/
}IM_E_SMS_NOTIFY_TYPE;

/** \brief ��ʷ��Ϣ�������� */
typedef enum tagIM_E_IM_HISTORYMESSAGEOP_TYPE 
{
	IM_E_IM_HISTORYMESSAGEOP_TYPE_QUERYBEFORE,			/**< ��ѯMsgID֮ǰ����Ϣ */
	IM_E_IM_HISTORYMESSAGEOP_TYPE_FIRSTQUERY = 1,		/**< �״β�ѯ������ҪMsgID */
}IM_E_IM_HISTORYMESSAGEOP_TYPE ;

/** \brief Ⱥ���ѯ���� */
typedef enum tagIM_E_IMGROUPQUERYTYPE
{
    IM_E_IMGROUPQUERYTYPE_BY_NAME,       /**< �����Ʋ�ѯ */
    IM_E_IMGROUPQUERYTYPE_BY_ID,         /**< ��Ⱥ��ID��ѯ */
    IM_E_IMGROUPQUERYTYPE_BY_NAME_ID,   /**< �����ƺ�ID��ѯ */
}IM_E_IMGROUPQUERYTYPE;

/** \brief ��ѯ�û���Ϣ�Ĺؼ������� */
typedef enum tagIM_E_IMUSERQUERYTYPE
{
	IM_E_IMUSERQUERYTYPE_BY_PHONE = 0,    /**< ���� */
	IM_E_IMUSERQUERYTYPE_BY_ACCOUNT = 1,  /**< �ʺ� */
	IM_E_IMUSERQUERYTYPE_BY_BINDNO = 2,   /**< �󶨺��� */
	IM_E_IMUSERQUERYTYPE_BY_EMAIL = 3,    /**< ���� */
	IM_E_IMUSERQUERYTYPE_BY_STAFFNO = 4   /**< ���� */
}IM_E_IMUSERQUERYTYPE;

/** \brief Ⱥ�������� */
typedef enum tagIM_E_FIXEDGROUP_OP_RESULT
{
    //32- 50Ⱥ�����
    IM_E_FIXEDGROUP_OP_RESULT_SUCCESS = 0,	/**< �ɹ� */
    IM_E_FIXEDGROUP_OP_RESULT_FAILED = 1,	/**< ʧ�� */
    IM_E_FIXEDGROUP_OP_RESULT_REACH_MAXIMUM = 32	/**< ��ԱȺ����Ŀ�Ѿ��ﵽ��� */,			
    IM_E_FIXEDGROUP_OP_RESULT_MEMBER_REACH_MAXIMUM = 33,	/**< ���ڳ�Ա�ﵽ�����Ŀ */			
    IM_E_FIXEDGROUP_OP_RESULT_DB_ERROR = 34,	/**< ���ݿ��쳣�ķ����� */				
}IM_E_FIXEDGROUP_OP_RESULT;

/** \brief ת�Ʒ������� */
typedef enum tagIM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE
{
    IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE_MOVE = 0,	/**< �ƶ����·��� */
    IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE_COPY = 1,	/**< ���Ƶ��·��� */
}IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE;

/** \brief ��ҵͨѶ¼��ѯ�������� */
typedef enum tagIM_E_ADDRBOOKQUERY_ORDERTYPE
{
	IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_PINYIN	= 0,	/**< ��ƴ������ */
	IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_STAFFNO	= 1,	/**< �����ź����� */
	IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_NATIVENAME = 3	/**< ��nativename����  */
}IM_E_ADDRBOOKQUERY_ORDERTYPE;

/** \brief ��ҵͨѶ¼��ѯ����ʽ*/
typedef enum tagIM_E_ADDRBOOKQUERY_ORDERMODEL
{
	IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_ASC	= 0,	/**< ���� */
	IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_DESC	= 1,	/**< ���� */
}IM_E_ADDRBOOKQUERY_ORDERMODEL;

/** \brief Ⱥ��֪ͨ */
typedef enum tagIM_E_IMGROUP_NOTIFY_TYPE
{
    IM_E_FIXEDGROUP_NOTIFY_ADDMEMBER = 0,	/**< Ⱥ����������Ա֪ͨ */
    IM_E_FIXEDGROUP_NOTIFY_DELMEMBER = 1,	/**< Ⱥ����ɾ����Ա */
    IM_E_FIXEDGROUP_NOTIFY_DISMISS = 2,    /**< Ⱥ���ɢ */
    IM_E_FIXEDGROUP_NOTIFY_INFOCHANGE = 3,	/**< Ⱥ����Ϣ���� */
    IM_E_FIXEDGROUP_NOTIFY_OWNER_CHANGE = 4,    /**< Ⱥ�����Ա��� */
	IM_E_FIXEDGROUP_NOTIFY_WAS_ADDEDTOGROUP = 5, /**< ����ӵ�Ⱥ��֪ͨ */
    IM_E_FIXEDGROUP_NOTIFY_ADDPHONEMEMBER = 6, /**< Ⱥ�������������Ա֪ͨ */
    IM_E_FIXEDGROUP_NOTIFY_DELPHONEMEMBER = 7, /**< Ⱥ����ɾ�������Ա֪ͨ */
}IM_E_IMGROUP_NOTIFY_TYPE;

typedef enum tagIM_E_EXITSTATUS
{
	IM_E_EXITSTATUS_NORMALOFFLINE,     /**<�������� */
	IM_E_EXITSTATUS_PAUSEOFFLINE = 2,  /**<�˺ű��������ͣ������ */
	IM_E_EXITSTATUS_OVERDUEOFFLINE = 3 /**<�˺Ź������� */
}IM_E_EXITSTATUS;

typedef enum tagIM_E_SYNC_TYPE
{
	IM_E_SYNC_TYPE_VALID = 0,      /**< ��Ч */
	IM_E_SYNC_TYPE_INVALID = 1, /**< ��Ч */
}IM_E_SYNC_TYPE;
//--------------------------------------------------------------ö�� end--------------------------------------------------------------

//--------------------------------------------------------------������νṹ�� begin--------------------------------------------------------------

/** \brief ������Ϣ */
typedef struct tagIM_S_USERINFO
{
        TUP_INT64 staffID;									/**< ��ԱID */
        TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];			/**< ��Ա�˺� */ 
        TUP_CHAR staffNO[IM_D_MAX_ACCOUNT_LENGTH];			/**< ��Ա���� */ 
        TUP_CHAR name[IM_D_MAX_NAME_LENGTH];				/**< �û��� */
        TUP_CHAR nativeName[IM_D_MAX_NAME_LENGTH];			/**< �������� */
		TUP_CHAR qPinYin[IM_D_MAX_NAME_LENGTH];				/**< ȫƴ	*/
        IM_E_GENDER_TYPE gender;							/**< �Ա� */
        TUP_CHAR birthday[IM_D_MAX_BIRTHDAY_LENGTH];		/**< ���� */
        TUP_CHAR age[IM_D_AGE_LENGTH];						/**< ���� */
        TUP_CHAR bindNO[IM_D_MAX_PHONE_LENGTH];				/**< �󶨺��� */
        TUP_CHAR mobile[IM_D_MAX_PHONE_LENGTH];				/**< �ֻ����� */
        TUP_CHAR homePhone[IM_D_MAX_PHONE_LENGTH];			/**< ��ͥ�绰 */
        TUP_CHAR officePhone[IM_D_MAX_PHONE_LENGTH];		/**< �칫�绰 */
        TUP_CHAR shortPhone[IM_D_MAX_PHONE_LENGTH];			/**< �̺� */
        TUP_CHAR otherPhone[IM_D_MAX_PHONE_LENGTH];			/**< �����绰 */
        TUP_CHAR voip[IM_D_MAX_PHONE_LENGTH];				/**< VOIP���� */
		TUP_CHAR ipPhone[IM_D_MAX_PHONE_LENGTH];			/**< ��IPPhone���� */
        TUP_CHAR fax[IM_D_MAX_PHONE_LENGTH];				/**< ���� */
        TUP_CHAR email[IM_D_MAX_DESC_LENGTH];				/**< email��ַ */
        TUP_CHAR webSite[IM_D_MAX_DESC_LENGTH];				/**< ������վ */
        TUP_CHAR signature[IM_D_MAX_DESC_LENGTH];			/**< �û�ǩ�� */
        TUP_CHAR desc[IM_D_MAX_DESC_LENGTH];				/**< ���� */
        TUP_CHAR address[IM_D_MAX_DESC_LENGTH];				/**< ��ַ */
        TUP_CHAR imageID[IM_D_MAX_DESC_LENGTH];				/**< ͷ��ID */
        TUP_CHAR postalcode[IM_D_MAX_DESC_LENGTH];			/**< �������� */
		TUP_BOOL isSecrecy;									/**< �Ƿ��ܳ�Ա */
        TUP_CHAR title[IM_D_MAX_DESC_LENGTH];				/**< ְ�� */
		TUP_INT32 deptID;									/**< ����ID */
        TUP_CHAR deptNameEn[IM_D_MAX_NAME_LENGTH];			/**< ����Ӣ������ */
        TUP_CHAR deptNameCn[IM_D_MAX_NAME_LENGTH];			/**< ������������ */
        TUP_CHAR imageSyncTime[IM_D_MAX_TIMESTAMP_LENGTH];	/**< ͷ��ͬ��ʱ��� */
        TUP_CHAR oldAccount[IM_D_MAX_ACCOUNT_LENGTH];		/**< ���˺� */
        TUP_CHAR state[IM_D_MAX_DESC_LENGTH];				/**< ͬ��״̬ */
        TUP_CHAR modifyTime[IM_D_MAX_TIMESTAMP_LENGTH];     /**< ������ʱ�� */
}IM_S_USERINFO;

/** \brief ��ϵ����Ϣ */
typedef struct tagIM_S_CONTACTNFO
{	
    TUP_INT64 id;				/**< ��ϵ��ID */
    TUP_INT64 staffID;		/**< staff ID(��IM_S_USERINFO����) */
    TUP_CHAR name[IM_D_MAX_NAME_LENGTH];			/**< ���� */
    TUP_CHAR nickName[IM_D_MAX_NAME_LENGTH];		/**< �ǳ� */
    TUP_CHAR foreignName[IM_D_MAX_NAME_LENGTH];	/**< Ӣ���� */
    TUP_CHAR birthday[IM_D_MAX_BIRTHDAY_LENGTH];		/**< ���� */
    IM_E_GENDER_TYPE		gender;			/**< �Ա� */
    TUP_CHAR corpName[IM_D_MAX_NAME_LENGTH];		/**< ��˾�� */
    TUP_CHAR deptName[IM_D_MAX_NAME_LENGTH];		/**< �������� */
    TUP_CHAR title[IM_D_MAX_DESC_LENGTH];			/**< ͷ�� */
    TUP_CHAR mobile[IM_D_MAX_PHONE_LENGTH];			/**< �ֻ��� */
    TUP_CHAR officePhone[IM_D_MAX_PHONE_LENGTH];	/**< �칫���� */
    TUP_CHAR homePhone[IM_D_MAX_PHONE_LENGTH];		/**< ��ͥ�绰 */
    TUP_CHAR otherPhone[IM_D_MAX_PHONE_LENGTH];     /**< �������� */
    TUP_CHAR fax[IM_D_MAX_PHONE_LENGTH];			/**< ���� */
    TUP_CHAR email[IM_D_MAX_DESC_LENGTH];			/**< �������� */
    TUP_CHAR webSite[IM_D_MAX_DESC_LENGTH];		/**< ��ҳ */
    TUP_CHAR imNO[IM_D_MAX_DESC_LENGTH];			/**< ���칤�ߺ��� */
    TUP_CHAR address[IM_D_MAX_DESC_LENGTH];		/**< ��ַ */
    TUP_CHAR desc[IM_D_MAX_DESC_LENGTH];			/**< ���� */
    TUP_CHAR postalcode[IM_D_MAX_DESC_LENGTH];		/**< �ʱ� */
    TUP_CHAR state;			/**< ͬ��״̬(����ͬ��ʱ�õ�) */
}IM_S_CONTACTNFO;

/** \brief ������Ϣ */
typedef struct tagIM_S_USERGROUPINFO
{
    TUP_INT64 id;	/**< ��ID */
    TUP_CHAR name[IM_D_MAX_NAME_LENGTH];  /**< ������ */
    TUP_INT64 index; /**< ����� */
    TUP_CHAR state;	 /**< ͬ��״̬(����ͬ��ʱ�õ�) */
}IM_S_USERGROUPINFO;

/** \brief ����ͳ�Ա��Ӧ��ϵ */
typedef struct tagIM_S_USERGROUPMEMBERINFO
{
    TUP_INT64 groupID;	/**< ��ID(IM_S_USERGROUPINFO��id�ֶ�) */
    TUP_INT64 contactID;	/**< ��ϵ��ID(IM_S_CONTACTNFO��id�ֶ�)*/
    TUP_CHAR state;		/**< ͬ��״̬(����ͬ��ʱ�õ�) */
}IM_S_USERGROUPMEMBERINFO;

/** \brief �̶�Ⱥ��Ϣ */
typedef struct tagIM_S_IMGROUPINFO
{
        TUP_CHAR	id[IM_D_GROUPID_LENGTH];		/**< ȺID */
        TUP_CHAR	name[IM_D_MAX_NAME_LENGTH];			/**< Ⱥ���� */
        TUP_INT32	capacity;		/**< Ⱥ��С */
        TUP_CHAR	manifesto[IM_D_MAX_DESC_LENGTH];		/**< ���� */
        TUP_CHAR	desc[IM_D_MAX_DESC_LENGTH];			/**< ��� */
        TUP_CHAR	owner[IM_D_MAX_ACCOUNT_LENGTH];       /**< ����Ա */
        IM_E_IMGROUP_JOIN_AUTH_FLAG	autoJoinFlag;	/**< ����Ⱥ�Ƿ�������� */
}IM_S_IMGROUPINFO;

typedef struct tagIM_S_GroupUserInfo
{
    TUP_INT64 staffID;		/**< Ⱥ��ԱStaff ID */
    TUP_CHAR  state;			/**< ״̬ */
    IM_S_USERINFO userInfo;		/**< ��Ա��Ϣ */
}IM_S_GroupUserInfo;

/** \brief Ⱥ���Ա�б���Ϣ */
typedef struct tagIM_S_GROUPUSERLIST
{
    TUP_BOOL  isSyncAll;	/**< �Ƿ�ȫ��ͬ�� */
    TUP_CHAR  timpstamp[IM_D_MAX_TIMESTAMP_LENGTH];	/**< ͬ��ʱ�����19000000000000��������ʱ���룩 */
    TUP_CHAR  groupID[IM_D_GROUPID_LENGTH];		/**< ȺID */
    TUP_S_LIST* memberInfo;		    /**< ��Ա��Ϣ IM_S_GroupUserInfo */
}IM_S_GROUPUSERLIST;

/** \brief ͬ���̶�Ⱥ�б�ʱ������ */
typedef struct tagIM_S_SYNC_IMGROUPINFO
{
    IM_S_IMGROUPINFO groupInfo; /**< Ⱥ����Ϣ */
    IM_E_IMGROUP_TYPE  groupType;      /**< �̶�Ⱥ���������� */
    TUP_CHAR			state;			/**< ״̬ *///TODO:�޸ĳ�ö��
}IM_S_SYNC_IMGROUPINFO;

/** \brief ������Ϣ */
typedef struct tagIM_S_DEPTINFO
{
    TUP_INT64 deptID;				/**< ����ID */
    TUP_INT64 parentDeptID;		/**< �ϼ�����ID */
    TUP_INT64 deptLevel;			/**< ���Ų㼶 */
    TUP_CHAR deptName[IM_D_MAX_DEPTNAME_LENGTH];			/**< �������� */
    TUP_CHAR fullDeptName[IM_D_MAX_DEPTNAME_LENGTH];		/**< ����ȫ�� */
}IM_S_DEPTINFO;

/** \brief ��¼�������� */
typedef struct tagIM_S_LOGIN_ARG
 {
	 TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; 	 /**< �ʺ�(����) */
	 TUP_CHAR   password[IM_D_MAX_PASSWORD_LENGTH];  /**< ����(����) */
     TUP_CHAR   version[IM_D_MAX_VERSION_LENGTH];  /**< �汾��(ѡ��) */
 }IM_S_LOGIN_ARG;

/** \brief ��¼��Ӧ���� */
typedef struct tagIM_S_LOGIN_ACK
 {
     TUP_BOOL result; /**< ��¼��� */
	 IM_E_LOGIN_RESULT reason; 	 /**< ��¼������飨������resultΪfalse��ʱ���ȡʧ��ԭ�� */
     TUP_INT32 retryTimes;  /**< ��¼����ʣ�����(resultΪIM_E_LOGING_RESULT_ACCOUNT_LOCKED��Ч) */
     TUP_INT32 lockInterval;  /**< �ʺű�����ʣ��ʱ�䣨��λ�����ӣ� (resultΪIM_E_LOGING_RESULT_ACCOUNT_LOCKED��Ч*/
 }IM_S_LOGIN_ACK;

/** \brief ��ȡͨѶ¼���� */
typedef struct tagIM_S_GETCONTACTLIST_ARG
 {
	 TUP_BOOL	isSyncAll; 	 /**< �Ƿ�����ͬ��(����) */
	 TUP_CHAR   timestamp[IM_D_MAX_TIMESTAMP_LENGTH];  /**< ����ͬ��ʱ�����19000000000000��������ʱ���룩 (isSyncAllΪTUP_TRUEʱ����) */
 }IM_S_GETCONTACTLIST_ARG;

/** \brief ��ȡͨѶ¼���� */
typedef struct tagIM_S_GETCONTACTLIST_ACK
 {
     TUP_BOOL result; /**< ������� */
	 TUP_BOOL isSyncAll; 	 /**< ����ͬ���Ƿ�������ͬ�� */
	 TUP_CHAR   timestamp[IM_D_MAX_TIMESTAMP_LENGTH];  /**< ����ͬ��ʱ�����19000000000000��������ʱ���룩 (isSyncAllΪTUP_TRUEʱ��Ч) */
     TUP_S_LIST* userList; /**< �����б�IM_S_USERINFO */
     TUP_S_LIST* contactList;  /**< �Զ�����ϵ���б�IM_S_CONTACTNFO */
     TUP_S_LIST* userGroupList; /**< ���ѷ��飬IM_S_USERGROUPINFO */
     TUP_S_LIST* userGroupMemberList; /**< ���ѷ������ϵ�˶�Ӧ��ϵ��IM_S_USERGROUPMEMBERINFO */
     TUP_S_LIST* imGroupList; /**< �̶�Ⱥ�б� IM_S_IMGROUPINFO*/
 }IM_S_GETCONTACTLIST_ACK;

typedef struct tagIM_S_GETSERVICEPROFILEARG
{
    TUP_BOOL isSyncAll;      /**�Ƿ�ȫ��ͬ�� */
    TUP_BOOL needIcon;       /**�Ƿ���Ҫͼ�� */
    TUP_BOOL isVpnAccess;    /**�Ƿ�VPN����  */
	TUP_CHAR timestamp[IM_D_MAX_TIMESTAMP_LENGTH];  /**< ����ͬ��ʱ�����19000000000000��������ʱ���룩 (isSyncAllΪTUP_TRUEʱ��Ч) */
    TUP_CHAR localIP[IM_D_IP_LENGTH];    /**����IP��ַ */
}IM_S_GETSERVICEPROFILEARG;

typedef struct tagIM_S_CONFIGINFO
{
    TUP_CHAR name[IM_D_GENEAL_LENGTH];		/** \brief ���� */
    TUP_CHAR value[IM_D_GENEAL_LENGTH];		/** \brief ֵ */
}IM_S_CONFIGINFO;

/** \brief ����̨�����Ϣ */
typedef struct tagIM_S_PANELINFO
{
    TUP_INT64 id;							/**< ���ID */
    TUP_INT64 indexNO;						/**< ��� */
    TUP_CHAR name[IM_D_MAX_NAME_LENGTH];	/**< ���� */
    IM_E_SYNC_TYPE state;					/**< ״̬ */
}IM_S_PANELINFO;

/** \brief �����Ϣ */
typedef struct tagIM_S_COMPONETINFO
{
    TUP_INT64 id;								/**< ���ID */
    TUP_INT64 panelID;							/**< ��Ӧ���ID */
    TUP_INT64 functionID;						/**<  ��Ӧ����λ */
    TUP_INT64 indexNO;							/**<  ��� */
    TUP_INT64 serverID;							/**< ��Ӧ����ID  */
    TUP_CHAR progID[IM_D_MAX_PROGID_LENGTH];	/**< progid */
    TUP_CHAR name[IM_D_MAX_NAME_LENGTH];		/**< ������� */
    TUP_CHAR type[IM_D_GENEAL_LENGTH];			/**< ������� */
	TUP_CHAR path[IM_D_MAX_PATH_LENGTH];		/**< ���·�� */
	TUP_CHAR icon[IM_D_ICON_LENGTH];			/**< ���ͼ��*/
    TUP_CHAR protocol[IM_D_GENEAL_LENGTH];		/**< Э������ */
    IM_E_SYNC_TYPE state;						/**< ״̬ */
}IM_S_COMPONETINFO;

    /** \brief ���������Ϣ */
typedef struct tagIM_S_COMPONETPARAMINFO
{
    TUP_CHAR progID[IM_D_MAX_PROGID_LENGTH];	/**< progid */
    TUP_CHAR key[IM_D_MAX_PLUGINPARAM_LENGTH];
    TUP_CHAR value[IM_D_MAX_PLUGINPARAM_LENGTH];
}IM_S_COMPONETPARAMINFO;

/** \brief ��������Ϣ */
typedef struct tagIM_S_SERVERINFO
{
    TUP_INT64 id;									/**< server ID */
    TUP_CHAR name[IM_D_MAX_NAME_LENGTH];			/**< ���� */
    TUP_CHAR address[IM_D_MAX_PLUGINURL_LENGTH];	/**< ��ַ */
}IM_S_SERVERINFO;

typedef struct tagIM_S_DATACONFADDRINFO
{
    TUP_CHAR dataConfAddr[IM_D_GENEAL_LENGTH];
}IM_S_DATACONFADDRINFO;

typedef struct tagIM_S_SERVICEPROFILEACK
{
    TUP_BOOL syncType;									/**< �Ƿ�ȫ��ͬ�� */
    TUP_BOOL isSetIpphone;								/**< �Ƿ�������IPPhone */
    TUP_BOOL isJointUser;								/**< �Ƿ��������� */
    TUP_BOOL bindChange;								/**< IP�仯�Ƿ���л� */
    TUP_INT32   sipExpires;								/**< sipע������ʱ�� */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];	/**< ������ʱ��� */	
    TUP_CHAR	ipPhone[IM_D_GENEAL_LENGTH];			/**< ��IPPhone���� */
    TUP_CHAR	eConsoleAddr[IM_D_GENEAL_LENGTH];		/**< eConsole��ַ */
    TUP_CHAR	sipAccount[IM_D_GENEAL_LENGTH];			/**< sip�ʺ� */
    TUP_CHAR	sipPassword[IM_D_GENEAL_LENGTH];		/**< sipע����� */
    TUP_CHAR	sipServer[IM_D_GENEAL_LENGTH];			/**< sip��������ַ (���˿�)*/
    TUP_CHAR	sipicscfDomainName[IM_D_GENEAL_LENGTH]; /**< ICSCF���� */
    TUP_CHAR	sipCountryCode[IM_D_GENEAL_LENGTH];		/**< ������ */
    TUP_CHAR	sipOutgoingAccCode[IM_D_GENEAL_LENGTH]; /**< ��������� */
    TUP_CHAR	sipInfoAccCode[IM_D_GENEAL_LENGTH];		/**< ҵ������� */
    TUP_CHAR	sipUcPassword[IM_D_GENEAL_LENGTH];		/**<   */
    TUP_CHAR	sipNetType[IM_D_GENEAL_LENGTH];			/**< �������ͣ�IMS/NGN�� */
    TUP_S_LIST* funcIDList;								/**< �����б� int */
    TUP_S_LIST* configList;								/**< ������Ϣ�б� IM_S_CONFIGINFO */
    TUP_S_LIST* panelList;								/**< �����Ϣ�б� IM_S_PANELINFO */
    TUP_S_LIST* serverList;								/**< ����������б� IM_S_SERVERINFO */
    TUP_S_LIST* componentList;							/**< �����Ϣ�б� IM_S_COMPONETINFO*/
    TUP_S_LIST* componentParamList;						/**< ���������Ϣ�б� IM_S_COMPONETPARAMINFO */
    TUP_S_LIST* dataConfAddrList;						/**< ���ݻ����ַ�б� IM_S_DATACONFADDRINFO */
}IM_S_SERVICEPROFILEACK;

typedef struct tarIM_S_GETUSERINFOARG
{
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];		/**< �ʺ� */
    TUP_INT64 staffID;								/**< staffid */
}IM_S_GETUSERINFOARG;

/** \brief ��ȡȺ���б����� */
typedef struct tagIM_S_GETIMGROUPLIST_ARG
 {
     TUP_BOOL		   isNeedAmount;					/**< �Ƿ���Ҫ�������� (����)*/ 
     TUP_INT32		   offset;							/**< ��ѯƫ���� (ѡ��)*/ 
     TUP_INT32		   count;							/**< ��ѯ��Ŀ(����) */ 
     TUP_CHAR          queryKey[IM_D_GENEAL_LENGTH] ;	/**< �ؼ��� (����)*/ 
     IM_E_IMGROUPQUERYTYPE  queryType;					/**< Ⱥ���ѯ���� (����)*/
 }IM_S_GETIMGROUPLIST_ARG;

/** \brief ��ȡȺ���б���Ӧ */
typedef struct tagIM_S_GETIMGROUPLIST_ACK
 {
     TUP_INT32 recordAmount;	/**< �ܼ�¼�� */ 
     TUP_INT32 offset;			/**< ��ѯƫ���� */ 
     TUP_INT32 count;			/**< ��ѯ��Ŀ */ 
     TUP_S_LIST* imGroupList;	/**< Ⱥ���б� IM_S_IMGROUPINFO */ 
 }IM_S_GETIMGROUPLIST_ACK;

/** \brief ��Ӻ��Ѻ���ϵ�˷������� */
typedef struct tagIM_S_ADDUSERGROUP_ARG
 {
        TUP_CHAR name[IM_D_MAX_NAME_LENGTH];  /**< ��������(����) */
        TUP_INT32 index; /**< ���(����������Ҫ����������Ĭ����-1) */
 }IM_S_ADDUSERGROUP_ARG;

/** \brief ��Ӻ��Ѻ���ϵ�˷�����Ӧ */
typedef struct tagIM_S_ADDUSERGROUP_ACK
 {
     TUP_BOOL result; /**< ������� */
     TUP_INT64 id; /**< ����� */
 }IM_S_ADDUSERGROUP_ACK;

/** \brief �޸ĺ��Ѻ���ϵ�˷������� */
typedef struct tagIM_S_MODUSERGROUP_ARG
 {
     TUP_INT64 id; /**< �����(����) */
     TUP_CHAR name[IM_D_MAX_NAME_LENGTH];  /**< ��������(����) */
     TUP_INT32 index; /**< ���(����������Ҫ����������Ĭ����-1) */
 }IM_S_MODUSERGROUP_ARG;

/** \brief ��Ӻ������� */
typedef struct tagIM_S_ADDFRIEND_ARG
 {
     TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; /**< �����ʺ� (����)*/
     TUP_INT64 groupID; /**< ���ѷ���ID(����) */
     TUP_CHAR displayName[IM_D_MAX_NAME_LENGTH];  /**< ���ָ����ѵ���ʾ��(��ѡ) */
 }IM_S_ADDFRIEND_ARG;

/** \brief ��Ӻ�����Ӧ */
typedef struct tagIM_S_ADDFRIEND_ACK
 {
     TUP_BOOL result; /**< ������� */
     TUP_INT64 contactID; /**< ��ϵ��ID */
 }IM_S_ADDFRIEND_ACK;

/** \brief ����Զ�����ϵ�� */
typedef struct tagIM_S_ADDCONTACT_ARG
 {
     IM_S_CONTACTNFO contact; /**< ��ϵ����Ϣ�������ϵ��ʱid_�������ӳɹ��󷵻� (����) */
     TUP_INT64 groupID; /**< ��ӵ��ķ���ID(����) */
 }IM_S_ADDCONTACT_ARG;

/** \brief ����Զ�����ϵ����Ӧ */
typedef struct tagIM_S_ADDCONTACT_ACK
 {
     TUP_BOOL result; /**< ������� */
     TUP_INT64 contactID; /**< ��ϵ��ID */
 }IM_S_ADDCONTACT_ACK;

/** \brief �޸��Զ�����ϵ�� */
typedef struct tagIM_S_MODCONTACT_ARG
 {
     IM_S_CONTACTNFO contact; /**< ��ϵ����Ϣ��id���� (����) */
 }IM_S_MODCONTACT_ARG;

/** \brief ��ĳһ��������ɾ�����ѻ�/��ϵ�� */
typedef struct tagIM_S_DELCONTACT_ARG
 {
     TUP_INT64 contactID; /**< ��ϵ��ID(����) */
     TUP_INT64 groupID; /**< ����ID(����) */
 }IM_S_DELCONTACT_ARG;

/** \brief �޸ĺ���/��ϵ�˷��� */
typedef struct tagIM_S_MODCONTACTGROUP_ARG
 {
        TUP_INT64 contactID; /**< ��ϵ��ID(����) */ 
        TUP_INT64 oldGroupID; /**< ԭ��ID(����) */ 
        TUP_INT64 newGroupID; /**< ����ID(����) */ 
		IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE type; /**< �ƶ����Ǹ��� */ 
 }IM_S_MODCONTACTGROUP_ARG;

/** \brief ����IM��Ϣ���� */
typedef struct tagIM_S_SENDIM_ARG
{
	TUP_INT			regionID;							/**< ����ID �������� (��ѡ)*/
    IM_E_IM_CHAT_TYPE chatType;							/**< IM��Ϣ����(����) */
	IM_E_IM_CHAT_SOURCE_FLAG sourceFlag;				/**< IM��Ϣ��������(����) */
	IM_E_IM_CHAT_CONTENT_TYPE contentType;				/**< IM��Ϣ���ݸ�ʽ(����)*/
	TUP_CHAR		origin[IM_D_MAX_ACCOUNT_LENGTH];	/**< ���ͷ��˺�(����)*/
    TUP_CHAR		target[IM_D_MAX_ACCOUNT_LENGTH];	/**< ���շ��˺�(����) */
    TUP_CHAR		groupID[IM_D_GROUPID_LENGTH];		/**< Ⱥ��ID���̶�Ⱥ����������*/
    TUP_CHAR		content[IM_D_MAX_MESSAGE_LENGTH];	/**< IM��Ϣ����(����)*/
    TUP_CHAR		displayname[IM_D_MAX_NAME_LENGTH];	/**< ���ͷ�����(��ѡ) */
    TUP_INT64		utcStamp;							/**< UTCʱ�� (��ѡ) */
}IM_S_SENDIM_ARG;

/** \brief �Ѷ���Ϣ�������� */
typedef struct tagIM_S_SETMESSAGEREAD_ARG
{
	TUP_S_LIST* messageinfo;						/**< �Ѷ���Ϣ������Ϣ��ʽ IM_S_MESSAGEINFO */
}IM_S_SETMESSAGEREAD_ARG;

/** \brief ��ȡ��Ϣ�������� */
typedef struct tagIM_S_QUERYHISTORYMESSAGE_ARG
{
	IM_E_IM_HISTORYMESSAGEOP_TYPE opType;					/**< �������� */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE msgType;					/**< �������Ϣ���� */
	TUP_CHAR sender[IM_D_MAX_PHONE_LENGTH];			/**< ��Ϣ���ͷ���msgTypeΪ0ʱ��д��Ϣ�����ߣ�msgTypeΪ1ʱ��дȺID��msgTypeΪ2ʱΪ���ź��룬msgTypeΪ3ʱ���� */
	TUP_INT64 msgID;								/**< ��ϢID���״β�ѯ���Ը��ֶ� */
	TUP_INT count;									/**< ��ѯ����Ϣ���� */
}IM_S_QUERYHISTORYMESSAGE_ARG;

/** \brief ��ȡ��Ϣ������Ӧ */
typedef struct tagIM_S_QUERYHISTORYMESSAGE_ACK
{
	TUP_INT totalCount;						/**< ��Ϣ���������״β�ѯʱ���� */
	IM_E_IM_HISTORYMESSAGEOP_TYPE opType;	/**< �������� */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE msgType; /**< �������Ϣ���� */
	TUP_CHAR sender[IM_D_MAX_PHONE_LENGTH];	/**< ��Ϣ���ͷ���msgTypeΪ0ʱ��д��Ϣ�����ߣ�msgTypeΪ1ʱ��дȺID��msgTypeΪ2ʱΪ���ź��룬msgTypeΪ3ʱ���� */
	TUP_S_LIST* chatinfolist;				/**< ��Ϣ��ʽ IM_S_CODECHAT_NOTIFY */
	TUP_S_LIST* smsList;					/**< ������Ϣ�б� IM_S_SMSINFO*/
}IM_S_QUERYHISTORYMESSAGE_ACK;

/** \brief ������Ϣ��ʽ  */
typedef struct tagIM_S_SMSINFO
{
	TUP_CHAR origin[IM_D_MAX_PHONE_LENGTH];				/**< ���ͷ�����*/
	TUP_CHAR target[IM_D_MAX_PHONE_LENGTH];				/**< ���շ�����*/
	TUP_INT64 serverMsgID;								/**< ��������ϢID*/
	TUP_CHAR clientMsgID[IM_D_MAX_CHAR_LENGTH];			/**< �ͻ�����ϢID*/
	TUP_CHAR content[IM_D_MAX_MESSAGE_LENGTH];			/**< ��Ϣ����*/
	TUP_CHAR sendTime[IM_D_MAX_TIMESTAMP_LENGTH];       /**< ����ʱ��*/
	IM_E_SMS_NOTIFY_TYPE smsType;						/**< ���յ��Ķ�����Ϣ������ */
}IM_S_SMSINFO;

/** \brief �Ѷ���Ϣ������Ϣ��ʽ  */
typedef struct tagIM_S_MESSAGEINFO
{
	IM_E_IM_HISTORYMESSAGEMSG_TYPE msgType;			/** \brief ��Ϣ���� */
	TUP_CHAR	sender[IM_D_MAX_PHONE_LENGTH];		/** \brief ���ͷ� (�����˺š��̶�Ⱥ��������ID�����ź���)*/
	TUP_INT64	msgId;								/** \brief ��ϢID (serverChatID)*/
}IM_S_MESSAGEINFO;

/** \brief IM��Ϣ����״̬���� */
typedef struct tagIM_S_CHAT_STATUS_ARG
{
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];  /**< ���շ��˺�(����) */
    IM_E_IM_CHAT_STATUS type;  /**< ����״̬(����) */
}IM_S_CHAT_STATUS_ARG;

/** \brief ��ȡ�����б���Ӧ */
typedef struct tagIM_S_GETDEPTS_ACK
 {
     TUP_BOOL result; /**< ������� */
     TUP_S_LIST* deptList; /**< �����б�(IM_S_DEPTINFO) */
 }IM_S_GETDEPTS_ACK;

/** \brief ��ѯ��ҵͨѶ¼���� */
typedef struct tagIM_S_QUERY_ENTADDRESSBOOK_ARG
{
    TUP_BOOL isNeedAmount;  /**< �Ƿ���Ҫ��������(����) */ 
    IM_E_ADDRBOOKQUERY_ORDERTYPE orderType;	/**< ����Ĺؼ��� */ 
    IM_E_ADDRBOOKQUERY_ORDERMODEL orderModel;	/**< ����ķ�ʽ */ 
    TUP_INT32 offset; /**< ��ѯƫ����(����) */ 
    TUP_INT32 count; /**< ��ѯ��Ŀ(����) */ 
    TUP_INT64 deptID; /**< ��ѯ���ţ���������ָ�����ţ�����д-1�� */ 
    TUP_CHAR queryKey[IM_D_MAX_DESC_LENGTH];		/**< �ؼ��֣���ѡ�� */ 
}IM_S_QUERY_ENTADDRESSBOOK_ARG;

/** \brief ��ѯ��ҵͨѶ¼��Ӧ */
typedef struct tagIM_S_QUERY_ENTADDRESSBOOK_ACK
{
	TUP_BOOL result; /**< ������� */
	TUP_INT32 recordAmount;	/**< �ܼ�¼�� */ 
	TUP_S_LIST* userList; /**< ��Ա�б�IM_S_USERINFO�� */ 
}IM_S_QUERY_ENTADDRESSBOOK_ACK;

/** \brief ��ѯ�û���Ϣ���� */
typedef struct tagIM_S_QUERY_USERINFO_ARG
{
	TUP_CHAR key[IM_D_MAX_PHONE_LENGTH];		/**< �ؼ������� */
	IM_E_IMUSERQUERYTYPE type;					/**< �ؼ������� */
}IM_S_QUERY_USERINFO_ARG;

/** \brief ��ѯ�û���Ϣ��Ӧ */
typedef struct tagIM_S_QUERY_USERINFO_ACK
{
	TUP_S_LIST* userList;	/**< ��Ա�б�IM_S_USERINFO�� */ 
}IM_S_QUERY_USERINFO_ACK;

/** \brief ��ӹ̶�Ⱥ���� */
typedef struct tagIM_S_IMGROUP_OP_ARG
{
    IM_S_IMGROUPINFO fixedgroupInfo; /**< �̶�Ⱥ��Ϣ�����ʱid�����ack�з��أ��޸�ʱ��Ҫ��дid�� */
}IM_S_IMGROUP_OP_ARG;

/** \brief ��ӹ̶�Ⱥ��Ӧ */
typedef struct tagIM_S_ADDIMGROUP_ACK
{
     TUP_BOOL result; /**< ������� */
     TUP_CHAR id[IM_D_GROUPID_LENGTH]; /**< Ⱥ��ID  */
     IM_E_FIXEDGROUP_OP_RESULT reason;	/**< Ⱥ������������ֵ��resultΪTUP_FALSEʱ���ж�ԭ�� */
}IM_S_ADDIMGROUP_ACK;

/** \brief ��ӹ̶�Ⱥ��Ӧ */
typedef struct tagIM_S_MODFIXEDGROUP_ACK
{
     TUP_BOOL result; /**< ������� */
     IM_E_FIXEDGROUP_OP_RESULT reason;	/**< Ⱥ������������ֵ��resultΪTUP_FALSEʱ���ж�ԭ�� */
}IM_S_MODFIXEDGROUP_ACK;

/** \brief ��ӹ̶�Ⱥ��Ա���� */
typedef struct tagIM_S_ADDIMGROUPMEMBER_ARG
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< �̶�ȺID */ 
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; /**< ����û��ʺ� */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH]; /**< Ⱥ���� */ 
    TUP_CHAR displayName[IM_D_MAX_NAME_LENGTH]; /**< ��ʾ�� */ 
}IM_S_ADDIMGROUPMEMBER_ARG;

/** \brief ��ȡȺ��(�̶�Ⱥ����ʱȺ)��Ա���� */
typedef struct tagIM_S_REQUESTIMGROUPMEMBERS_ARG
{
    TUP_BOOL		isSyncAll;		/**< �Ƿ�ȫ��ͬ�� */
    TUP_CHAR        groupID[IM_D_GROUPID_LENGTH];   /**< ȺID */
    TUP_CHAR		timpstamp[IM_D_MAX_TIMESTAMP_LENGTH]; /**< ͬ��ʱ�����19000000000000��������ʱ����)������дʹ��Ĭ��ʱ��19000000000000 */
}IM_S_REQUESTIMGROUPMEMBERS_ARG;

/** \brief ɾ���̶�Ⱥ���� */
typedef struct tagIM_S_DELIMGROUPMEMBER_ARG
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< �̶�ȺID */ 
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; /**< ɾ���û��ʺ� */ 
}IM_S_DELIMGROUPMEMBER_ARG;

/** \brief ����Ա�����û��������̶�Ⱥ���룬�����û���������Ա�������̶�Ⱥ */
typedef struct tagIM_S_CONFIRM_JOINFIXEDGROUP_ARG
{
    TUP_BOOL  agreeJoin;     /**< ����Ա�Ƿ�ͬ���Ա������ */
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< �̶�ȺID */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH]; /**< Ⱥ����ID */ 
    TUP_CHAR memberAccount[IM_D_MAX_ACCOUNT_LENGTH]; /**< ��������Ա�ʺ� */ 
    TUP_CHAR displayName[IM_D_MAX_NAME_LENGTH]; /**< ����Ա��ʾ�� */ 
}IM_S_CONFIRM_JOINFIXEDGROUP_ARG;

/** \brief �������̶�Ⱥ���� */
typedef struct tagIM_S_JOINFIXEDGROUP_ARG
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< �̶�ȺID */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH]; /**< �̶�Ⱥ�� */ 
    TUP_CHAR displayName[IM_D_MAX_NAME_LENGTH]; /**< ��ʾ�� */ 
}IM_S_JOINFIXEDGROUP_ARG;

/** \brief ת�ƹ̶�Ⱥ���� */
typedef struct tagIM_S_TRANSFERIMGROUP_ARG
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< �̶�ȺID */ 
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; /**< ��Ա�ʺ� */ 
}IM_S_TRANSFERIMGROUP_ARG;

/** \brief ��������Ӻ������� */
typedef struct tagIM_S_IMGROUPPHONEMEMBER_OP_ARG
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< �̶�ȺID */ 
    TUP_S_LIST* phonelist; /**< �����б� */ 
}IM_S_IMGROUPPHONEMEMBER_OP_ARG;

//--------------------------------------------------------------������νṹ�� end--------------------------------------------------------------

//--------------------------------------------------------------�ص�֪ͨ�ṹ�� begin--------------------------------------------------------------
/** \brief ϵͳ������Ӧ*/
typedef struct tagIM_S_SYSURLS
{
    TUP_CHAR userPortalUrl[IM_D_IP_LENGTH];  /**< ����portal��ַ */
    TUP_CHAR updateServerAddr[IM_D_IP_LENGTH]; /**< �Զ�������������ַ */
}IM_S_SYSURLS_NOTIFY;

/** \brief ϵͳ������Ӧ*/
typedef struct tagIM_S_LOGOUT_NOTIFY
{
	TUP_BOOL LogOutRet;		/**< �û��˳���� */
}IM_S_LOGOUT_NOTIFY;

/** \brief �Է�����Լ����ѳɹ�֪ͨ */
typedef struct tagIM_S_ADDFRIEND_NOTIFY
 {
     TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];		/**< �Է������ʺ� */
     TUP_CHAR displayName[IM_D_MAX_NAME_LENGTH];	/**< �Է���ʾ�� */
	 TUP_INT64 serverMsgID;							/**< ��������ϢID */
 }IM_S_ADDFRIEND_NOTIFY;

/** \brief ����״̬�仯֪ͨ */
typedef struct tagIM_S_USERSTATUS_NOTIFY
 {
	 IM_E_USER_ONLINESTATUS status;					/**< ��״̬ */
	 TUP_CHAR	desc[IM_D_MAX_DESC_LENGTH];         /**< ״̬���� */
	 TUP_CHAR	origin[IM_D_MAX_ACCOUNT_LENGTH];    /**< ״̬�仯��Ա�ʺ� */
	 IM_E_CLIENT_TYPE clientType;					/**< �ͻ������� */
	 TUP_CHAR	clientDesc[IM_D_MAX_DESC_LENGTH];   /**< �ͻ������� */
 }IM_S_USERSTATUS_NOTIFY;

/** \brief ������Ϣ�б� */
typedef struct tagIM_S_USERINFOCHANGE_LIST_NOTIFY
{
	TUP_S_LIST* userInfoList;								/**< ͬ��״̬(����ͬ��ʱ�õ�) */
}IM_S_USERINFOCHANGE_LIST_NOTIFY;

/** \brief Ⱥ����Ա�յ��û�����̶�Ⱥ֪ͨ */
typedef struct tagIM_S_APPLYJOINFIXEDGROUP_NOTIFY
{
    TUP_BOOL agreeInvite;		/**< �û��Ƿ�ͬ�����Ա������ */
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< �̶�ȺID */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH]; /**< Ⱥ����ID */ 
    TUP_CHAR memberAccount[IM_D_MAX_ACCOUNT_LENGTH]; /**< �������Ա���ʺ� */ 
    TUP_CHAR memberName[IM_D_MAX_NAME_LENGTH]; /**< �������Ա������ */ 
}IM_S_APPLYJOINFIXEDGROUP_NOTIFY;

/** \brief �û��յ�����Ա�������̶�Ⱥ֪ͨ */
typedef struct tagIM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY
{
	TUP_CHAR groupID[IM_D_GROUPID_LENGTH];			/**< �̶�ȺID */ 
	TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH];		/**< Ⱥ����ID */ 
	TUP_CHAR adminAccount[IM_D_MAX_ACCOUNT_LENGTH]; /**< ����Ա�ʺ� */ 
	TUP_CHAR adminName[IM_D_MAX_NAME_LENGTH];		/**< ����Ա���� */
	TUP_INT64 serverMsgID;							/**< ��������ϢID */
}IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY;

/** \brief ����Ա�յ��û��������Ⱥ��֪ͨ */
typedef struct tagIM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY
{
	TUP_CHAR groupID[IM_D_GROUPID_LENGTH];				/**< �̶�ȺID */ 
	TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH];			/**< Ⱥ����ID */ 
	TUP_CHAR memberAccount[IM_D_MAX_ACCOUNT_LENGTH];	/**< �������ʺ� */ 
	TUP_CHAR memberName[IM_D_MAX_NAME_LENGTH];			/**< ���������� */ 
	TUP_INT64 serverMsgID;								/**< ��������ϢID */
}IM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY;

/** \brief IMȺ����ϸ��Ϣ */
typedef struct tagIM_S_GETIMGROUPDETAIL_NOTIFY
{
	IM_S_IMGROUPINFO imGroupInfo;   
}IM_S_GETIMGROUPDETAIL_NOTIFY;


/** \brief Ⱥ��Ա�յ�����Ա��������̶�Ⱥ֪ͨ����Ӧ */
typedef struct tagIM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY
{
    TUP_BOOL agreeJoin;     /**< ����Ա�Ƿ�ͬ���Ա������ */
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< �̶�ȺID */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH]; /**< Ⱥ����ID */ 
    TUP_CHAR adminAccount[IM_D_MAX_ACCOUNT_LENGTH]; /**< ����Ա���ʺ�  */ 
    TUP_CHAR adminName[IM_D_MAX_NAME_LENGTH]; /**< ����Ա������ */ 
}IM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY;

/** \brief �̶�Ⱥ���֪ͨ */
typedef struct tagIM_S_IMGROUP_NOTIFY
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH];				/**< �̶�ȺID */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH];			/**< Ⱥ����ID */ 
    TUP_CHAR adminAccount[IM_D_MAX_ACCOUNT_LENGTH];		/**< ����Ա�ʺ� */ 
    TUP_CHAR memberAccount[IM_D_MAX_ACCOUNT_LENGTH];	/**< ��������Ա�ʺ� */ 
    TUP_CHAR memberName[IM_D_MAX_NAME_LENGTH];			/**< ��������Ա���� */ 
	TUP_INT64  serverMsgID;								/**< ��������ϢID */
}IM_S_IMGROUP_NOTIFY;

/** \brief ���� */
typedef struct tagIM_S_PHONENUM
{
    TUP_CHAR phoneNum[IM_D_GENEAL_LENGTH];
}IM_S_PHONENUM;

/** \brief ��������֪ͨ */
typedef struct tagIM_S_DISCUSSGROUP_NOTIFY
{
	TUP_CHAR groupID[IM_D_GROUPID_LENGTH];				/**< ������ID */ 
	TUP_S_LIST* phonelist;								/**< �����б�:IM_S_PHONENUM */			
	TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH];			/**< ���������� */ 
	TUP_CHAR adminAccount[IM_D_MAX_ACCOUNT_LENGTH];		/**< ����Ա�ʺ� */ 
	TUP_CHAR memberAccount[IM_D_MAX_ACCOUNT_LENGTH];	/**< ������ɾ���ĳ�Ա�ʺ� */ 
	TUP_CHAR memberName[IM_D_MAX_NAME_LENGTH];			/**< ������ɾ���ĳ�Ա���� */ 
}IM_S_DISCUSSGROUP_NOTIFY;

/** \brief ������Ϣ */
typedef struct tagIM_S_CHATINFO_NOTIFY
{
	IM_E_CHAT_TYPE	chatType;								/**< IM��Ϣ���� */
	TUP_INT		sourceFlag;									/**< IM��Ϣ�������� */
	TUP_INT		contentType;								/**< IM��Ϣ���ݸ�ʽ*/
	TUP_INT64	utcStamp;									/**< UTCʱ��*/
	TUP_CHAR	origin[IM_D_MAX_ACCOUNT_LENGTH];			/**< ���ͷ��˺�*/
	TUP_CHAR	target[IM_D_MAX_ACCOUNT_LENGTH];			/**< ���շ��˺�*/
	TUP_CHAR	groupID[IM_D_GROUPID_LENGTH];				/**< Ⱥ��ID*/
	TUP_CHAR	content[IM_D_MAX_MESSAGE_LENGTH];			/**< IM��Ϣ����*/
	TUP_CHAR	name[IM_D_MAX_NAME_LENGTH];					/**< ���ͷ�����*/
	TUP_INT		regionID;									/**< ����ID �������� */
	TUP_INT64	clientChatID;								/**< �ͻ������ɵ���ϢID */
	TUP_INT64	serverChatID;								/**< ���������ɵ���ϢID���ͻ��˷���ʱ�������ʱ��������д�� */
	TUP_CHAR	groupName[IM_D_MAX_NAME_LENGTH];			/**< Ⱥ���� */
	IM_E_IM_CHATMEDIA_TYPE mediaType;						/**< ý������ */
}IM_S_CHATINFO_NOTIFY;

/** \brief �������յ�ϵͳ����֪ͨ */
typedef struct tagIM_S_SYSTEMBULLETIN_NOTIFY
{
	IM_S_CHATINFO_NOTIFY chatInfo;	/**< ������Ϣ */
}IM_S_SYSTEMBULLETIN_NOTIFY;

/** \brief ����IM����״̬��Ϣ */
typedef struct tagIM_S_SENDIMINPUT_NOTIFY
{
	TUP_CHAR				account[IM_D_MAX_ACCOUNT_LENGTH];		/** \brief �������˺� */
	IM_E_IM_CHAT_STATUS		status;									/** \brief IM��������״̬ */
}IM_S_SENDIMINPUT_NOTIFY;

/** \brief �¼�ʱ��Ϣ֪ͨ */
typedef struct tagIM_S_CODECHAT_NOTIFY
{
	IM_S_CHATINFO_NOTIFY chatInfo;	/**< ������Ϣ */
}IM_S_CODECHAT_NOTIFY;

/** \brief �¼�ʱ��Ϣ����֪ͨ */
typedef struct tagIM_S_CHATLIST_NOTIFY
{
	TUP_S_LIST* chatList;		/**< ����������Ϣ IM_S_CODECHAT_NOTIFY*/
	TUP_INT total;				/**< δ����Ϣ���� */
	TUP_INT64 minMsgID;			/**< ��С��ϢID */
	TUP_INT64 maxMsgID;			/**< �����ϢID */
}IM_S_CHATLIST_NOTIFY;

typedef struct tagIM_S_IMAGEINFO
{
    TUP_INT length;    /** \brief ͷ�����ݳ��� */
    TUP_CHAR* data;	    /** \brief ͷ������ */
}IM_S_IMAGEINFO;

typedef struct tagIM_S_USERIMAGEINFO
{
    IM_S_IMAGEINFO  imagebits;      /**< ͷ������ */
    TUP_CHAR		id[IM_D_MAX_ACCOUNT_LENGTH];				/**< ͷ��ID */
    TUP_CHAR		timestamp[IM_D_MAX_TIMESTAMP_LENGTH];		/**< ʱ��� */
}IM_S_USERIMAGEINFO;

typedef struct tagIM_S_IMAGEREQARG
{
    TUP_CHAR id[IM_D_MAX_ACCOUNT_LENGTH];				/** \brief ͷ��ID */
    TUP_CHAR timpstamp[IM_D_MAX_TIMESTAMP_LENGTH];		/** \brief ͬ��ʱ�����19000000000000��������ʱ���룩 */
}IM_S_IMAGEREQARG;

typedef struct tagIM_S_STATUSARG
{
    IM_E_USER_ONLINESTATUS status;					/**< ��״̬ */
    TUP_CHAR desc[IM_D_MAX_STATUS_DESCLEN];         /**< ״̬���� */
}IM_S_STATUSARG;

/** \brief �û���¼֪ͨ */
typedef struct tagIM_S_LOGIN_NOTIFY
{
	TUP_BOOL	result;										/**< ��¼��� */
	TUP_CHAR	token[IM_D_LOGIN_TOKEN_LENGTH];				/** \brief token */	 
	TUP_INT		regionID;									/** \brief ����ID */
	TUP_INT		retryTimes;									/** \brief ��¼����ʣ����� */
	TUP_INT		lockInterval;								/** \brief �ʺű�����ʣ��ʱ�䣨��λ�����ӣ� */
	TUP_CHAR	lastLoginIP[IM_D_IP_LENGTH];				/** \brief ��һ�ε�¼�ķ�����IP */
	TUP_CHAR	lastLoginTime[IM_D_MAX_TIMESTAMP_LENGTH];	/** \brief ��һ�ε�¼�ķ�����ʱ�� */
}IM_S_LOGIN_NOTIFY;

/** \brief �û�����֪ͨ */
typedef struct tagIM_S_KICKOUT_NOTIFY
{
	TUP_CHAR userAccount[IM_D_MAX_ACCOUNT_LENGTH];
	IM_E_EXITSTATUS exitFlag;
}IM_S_KICKOUT_NOTIFY;
//--------------------------------------------------------------�ص�֪ͨ�ṹ�� end--------------------------------------------------------------

//--------------------------------------------------------------�ص����� begin--------------------------------------------------------------
/**
 * \brief �ص�����
 * \param[in]  eventID �¼�ID
 * \param[in] body ��Ϣ��
 * \return TUP_VOID
 */
typedef TUP_BOOL (*TUP_IM_FN_CALLBACK_PTR)(IM_E_EVENT_ID eventID, void *body);
//--------------------------------------------------------------�ص����� end--------------------------------------------------------------

#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif//_TUP_IM_BASEDEF_H_