

#ifndef __CALL_DEF_H__
#define __CALL_DEF_H__


#include "tup_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

#define CALL_D_ACCESSCODE_MAX_LENGTH     (32)  /* �������ַ�����󳤶�*/
#define CALL_D_IP_LENGTH                 (16)   
#define CALL_D_PROTOCOL_LENGTH           (30)  /** Э�����ֳ��� */
#define MPROC_D_AAC_CONFIG_LEN           (16)  /**< AAC��config����*/
#define MPROC_D_AUD_RATE_NUM             (16)  /** ��ʽ��Ƶ֧�ֶ�����ʵĸ���*/
#define MPROC_D_MAX_AUDIO_OUT_VOLUME     (100)

#define CALL_D_MAX_CODEC_LIST_LEN        (127) /** �����list��󳤶�*/

#define CALL_MAX_CODEC_NAME_LEN          (31)  /** ����Ƶ��������Ƴ��� */
#define CALL_MAX_FRAMESIZE_LEN            (16)  /** ��Ƶ�ֱ��ʳ��� */    
#define CALL_MAX_PROFILE_LEN              (8)   /** ��Ƶ������ʽ����*/

#define CALL_D_MAX_LENGTH_NUM           (256) 
#define CALL_D_MAX_DISPLAY_NAME         (256)
#define CALL_D_MAX_USERNAME_LENGTH      (256)
#define CALL_D_MAX_PASSWORD_LENGTH      (256)
#define CALL_D_MAX_URL_LENGTH           (256)
    
#define CALL_D_MAXDEVICENUM             (8)             /* ����豸���� */

/** Ԥ����Ϣ�ַ������ */
#define CALL_D_MAX_PRESET_MSG_LENGTH     (100)

#define CALL_D_MAX_MSGSUMMARY_NUM (10)

    /*Multiline*/
#define CALL_D_MAX_ACCOUNT_NUM (24)             /**< �����··�� */
#define CALL_D_MAX_CALL_NUM (24)               /**< ������·�� */
#define CALL_D_MAX_LINE_NUM (24)              /**< �����··�� */
#define CALL_D_MAX_LINE_KEY_NUM (24)

    /*IPT*/
#define CALL_D_MAX_ACB_NUM (5)             /**< ���غ����� */

#define CALL_D_MAX_FOWARD_NUM (24)                  /**< ���ǰת���ƿ鴦�����*/

#define CALL_D_MAX_INTERCOM_GROUPNUM (CALL_D_MAX_ACCOUNT_NUM-1)     /**< ���intercom��·��,��������˺�����һ· */

/** ������ض��� */
#define CALL_D_PASSCODE_LENGTH          (50)  /*���鴴�������passcode�ĳ��� */
#define CALL_D_DATACONF_PARAM_LENGTH    (32) //���ݻ��������������ֵ
#define CALL_D_DATACONF_CMADDR_LENGTH   (64) //���ݻ������cm_address����ֵ
#define CALL_D_CONF_CODE_LENGTH   (33) /*��������룬��INFO 241����Я����invite-chairman-flag=0ʱ�з��أ�USM������PC��������ʹ��*/

/** ����ģ��ID */
typedef enum tagCALL_E_MOD_ID
{
    CALL_E_MOD_ID_TSP = 0,         /**< ���п�������Ϣ����ģ�� */
//    CALL_E_MOD_ID_STACK = PID_SIP_STACK,           /**< SIPЭ��ջ��Ϣ����ģ�� */ //modify by zhangwp 00192189
    CALL_E_MOD_ID_STACK ,           /**< SIPЭ��ջ��Ϣ����ģ�� */ //modify by zhouxinzhong for TUP, depart from minidopra

    CALL_E_MOD_ID_SIP = 4096,      /**< SIPC��Ϣ����ģ�� */
    CALL_E_MOD_ID_HLLM,            /**< HLLM����DNS��ѯ��Ϣ����ģ�� */
    CALL_E_MOD_ID_VCOM,            /**< VCOM��Ϣ����ģ�� */
    CALL_E_MOD_ID_TPTD,            /**< TPTD��Ϣ����ģ�� */
    //CALL_E_MOD_ID_STACK,           /**< SIPЭ��ջ��Ϣ����ģ�� */   //modify by zhangwp 00192189

    CALL_E_MOD_ID_BUTT
} CALL_E_MOD_ID;

typedef enum tagCALL_E_ID_TYPE
{
    CALL_E_IDTYPE_CALL_ID,
    CALL_E_IDTYPE_CONF_ID
}CALL_E_ID_TYPE;

/*��־���� */
enum CALL_E_LOG_LEVEL
{
    CALL_E_LOG_ERROR = 0,    
    CALL_E_LOG_WARNING,     
    CALL_E_LOG_INFO,         
    CALL_E_LOG_DEBUG         
};

/** ϵͳ�����붨��,TODO, to be better */
typedef enum tagCALL_E_ERR_ID
{
    CALL_E_ERR_BEGIN = 0x08002100UL,
    CALL_E_ERR_GENERAL_ERROR,                     /**<1 һ����� */
    CALL_E_ERR_PARAM_ERROR,                       /**<2�������� */
    CALL_E_ERR_MEM_ERROR,                         /**<3�����ڴ���� */
    CALL_E_ERR_SYSTEM_ERROR,                      /**<4ϵͳ���� */
    CALL_E_ERR_MSG_ERROR,                         /**<5������Ϣ���� */
    CALL_E_ERR_CFG_ERROR,                         /**<6��ȡϵͳ���ô��� */
    CALL_E_ERR_NET_ERROR,                         /**<7����������� */
    CALL_E_ERR_ACCESS_ERROR,                      /**<8�������ʧ�ܴ��� */
    CALL_E_ERR_TIMER_ERROR,                       /**<9������ʱ������ */
    CALL_E_ERR_STATE_ERROR,                       /**<10����״̬����ȷ */
    CALL_E_ERR_OPERATE_ERROR,                     /**<11���ڽ��������������� */
    CALL_E_ERR_REQSRV_ERROR,                      /**<12�������ؽ��к��п�ʼ���� */
    CALL_E_ERR_REQRES_ERROR,                      /**<13������Ƶ��Դ���� */
    CALL_E_ERR_SERVICE_DOING,                     /**<14���ڽ�����������ҵ�� */
    CALL_E_ERR_CALLRECORD_ERROR,                  /**<15��¼ͨ����¼���� */
    CALL_E_ERR_MPROC_ERROR,                       /**<16ý����̷��صĴ��� */
    CALL_E_ERR_MAX_CALL_ERROR,                    /**<17����������·�� */
    CALL_E_ERR_SIPID_NOTEXIT_ERROR,               /**<18SIP�˻�ID������ */
    CALL_E_ERR_CALLID_NOEXIT_ERROR,               /**<19����ID������ */
    CALL_E_ERR_REGISTERING_ERROR,                 /**<20����ע����ʧ��*/
    CALL_E_ERR_REGIST_FALL_ERROR,                 /**<21����sip�ӿ�ע��ʧ�� */
    CALL_E_ERR_DEREGIST_FALL_ERROR,               /**<22����sip�ӿ�ע��ʧ�� */
    CALL_E_ERR_SET_SIP_INFO_ERROR,                /**<23�����˻���Ϣ���� */
    CALL_E_ERR_SETACCOUNT_ERROR,                  /**<24����SIPģ��ʧ��*/
    CALL_E_ERR_NOTIFYSIPACCOUNT_ERROR,            /**<25�ϱ�ʧ��  */
    CALL_E_ERR_SIPSEVER_ERROR,                    /**<26��������Ϣ����*/
    CALL_E_ERR_SIPACCOUNTINFO_ERROR,              /**<27�˻���Ϣ����*/
    CALL_E_ERR_SIPC_ERROR,

    CALL_E_ERR_UNREGISTER_ERROR,                  /**<28δע�����addby chendk*/
    CALL_E_ERR_SUB_FALL_ERROR,                    /**<29����Sip�ӿڶ���ʧ�� */
    CALL_E_ERR_DESUBING_ERROR,                    /**<30ע�������д��� */
    CALL_E_ERR_SUBING_ERROR,                      /**<31�����д��� */

    CALL_E_ERR_LOCAL_MAX_CONFER_ERROR,            /**<32���ػ����Ѵ�����ֻ����һ���᳡*/
    CALL_E_ERR_LOCAL_CONFER_NOEXIT_ERROR,         /**<33���ػ���δ���� */
    CALL_E_ERR_LOCAL_CONFER_NOMATCH_ERROR,        /**<34�������·����ϯ�˻���ƥ��*/
    CALL_E_ERR_CONF_STATE_ERROR,                  /**<35���ػ���״̬����*/
    CALL_E_ERR_JOINTSTATENOTIFY_ERROR,            /**<36IP Phone������״̬�ϱ�ʧ��*/
    CALL_E_ERR_CONFID_NOTEXIST_ERROR,             /* 37����ID������ */
    CALL_E_ERR_CONF_VIDEO_HOLD_ERROR,             /* 38��Ƶ����ʧ�� */
    CALL_E_ERR_CONF_VIDEO_UNHOLD_ERROR,             /* 39��Ƶ�ָ�ʧ�� */
    CALL_E_ERR_MAX_SERVER_CONF_ERROR,             /* 40����������������� */
    CALL_E_ERR_AA_REQRANDOMNUM_ERROR,             /* 41AA��ȡ�����ʧ�� */
    CALL_E_ERR_AA_LOGIN_ERROR,                    /* 42AA��½ʧ�� */
    CALL_E_ERR_CONF_VIDEO_TYPE_NO_MATCH,          /**43�������Ͳ�ƥ��*/
    CALL_E_ERR_CONF_VIDEO_START_ERROR,              /**44 ��Ƶ���鿪��ʧ��*/
    CALL_E_ERR_AA_NOMAINSERVER_ERROR,           /* 45AA���������� */
    CALL_E_ERR_AA_PASSWORD_ERROR,                   /*46 ������� */
    CALL_E_ERR_AA_USERNAME_ERROR,                   /* 47�û������� */
    CALL_E_ERR_AA_USERLOGINED_ERROR,                /* 48�û��ѵ�¼ */
    CALL_E_ERR_AA_ACCOUNTLOCKED_ERROR,             /* 49�˻������� */
    CALL_E_ERR_AA_TERMINALTYPE_ERROR,               /* 50�ն����Ͳ�ƥ�� */
    CALL_E_ERR_AA_PARSEXML_ERROR,                   /* 51����XML���� */
    CALL_E_ERR_AA_CONNECT_ERROR,                    /* 52���ӷ��������� */

    CALL_E_ERR_MEDIA_CFG_ERROR,                   /** 53��ȡý������ʧ�� */
    CALL_E_ERR_AA_GETSRINFO_ERROR,                /* 54��ȡҵ��Ȩ��ʧ�� */
    CALL_E_ERR_AA_LACKSR_ERROR,                    /* 55ҵ��Ȩ�޲���ʧ�� */

    CALL_E_ERR_NETWORKENV_ERROR,                    /* 56���绷������ */
    CALL_E_ERR_SERVICE_CONFLICT_ERROR,              /** 57ҵ���ͻ add by sunpy*/
    CALL_E_ERR_AA_TIMEOUT_ERROR,                  /* 58���ӳ�ʱ */
    CALL_E_ERR_AA_UNKOWN_ERROR,                   /** 59δ֪����*/
    CALL_E_ERR_PICKUP_ADDTIP_ERROR,                /* ���������Ϣʧ�� */
    CALL_E_ERR_PICKUP_REMOVETIP_ERROR,             /* ɾ����������Ϣʧ�� */
    CALL_E_ERR_PICKUP_CREATERINGNUM_ERROR,             /* �����������ʧ�� */
    CALL_E_ERR_VVM_PARAM_ERR,                      /** VVM�������� */

    CALL_E_ERR_GET_IPT_INFO_ERR,                   /** ��ȡ�Ǽ�ҵ����� */
    CALL_E_ERR_VVM_GETVOICEMAIL_ERR,               /** ��ȡ�������� */
    CALL_E_ERR_ATTENDEE_ALREADY_EXIST,             /** ������Ѿ����� */
    CALL_E_ERR_ATTENDEE_NOT_EXIST,                  /** ����߲����� */
    CALL_E_ERR_CREATE_CONF_WND_ERROR,                /** ������������Ƶ���鴰��ʧ��*/
    CALL_E_ERR_CREATE_CONF_WND_EXIST,                /** ��Ƶ���ڲ�����*/
    CALL_E_ERR_GET_CONF_LIST_INFO_ERROR,               /** ��ȡCONF LIST ʧ��*/
    CALL_E_ERR_NEED_CHAIRMAN_TO_OPERATE,            /** ��Ҫ������Ȩ�޲��ܲ���*/
    CALL_E_ERR_NO_VIDEO_DEVICE_TO_OPERATE,            /** û����Ƶ�豸���Բ���*/

    CALL_E_ERR_BUTT,
    CALL_E_ERR_NUM = (CALL_E_ERR_BUTT & 0x00001FFF)
} CALL_E_ERR_ID;

/** ����ʧ�ܵ�ԭ���� */
typedef enum tagCALL_E_REASON_CODE
{
    CALL_E_REASON_CODE_OK = 0,

    /** ����ʧ�ܵĴ����� */
    CALL_E_REASON_CODE_BADREQUEST = 400,
    CALL_E_REASON_CODE_PAYMENTREQUIRED = 402,
    CALL_E_REASON_CODE_FORBIDDEN = 403,
    CALL_E_REASON_CODE_NOTFOUND = 404,
    CALL_E_REASON_CODE_METHODNOTALLOWED = 405,
    CALL_E_REASON_CODE_RESNOTACCEPTABLE = 406,
    CALL_E_REASON_CODE_REQUESTTIMEOUT = 408,
    CALL_E_REASON_CODE_GONE = 410,
    CALL_E_REASON_CODE_REQUESTENTITYTOOLARGE = 413,
    CALL_E_REASON_CODE_REQUESTURITOOLONG = 414,
    CALL_E_REASON_CODE_UPSUPPORTEDMEDIATYPE = 415,
    CALL_E_REASON_CODE_UPSUPPORTEDURISCHEME = 416,
    CALL_E_REASON_CODE_BADEXTENSION = 420,
    CALL_E_REASON_CODE_EXTENSIONREQUIRED = 421,
    CALL_E_REASON_CODE_TEMPORARILYUNAVAILABLE = 480,
    CALL_E_REASON_CODE_CALLTRANSACTIONDOESNOTEXIST = 481,
    CALL_E_REASON_CODE_LOOPDETECTED = 482,
    CALL_E_REASON_CODE_TOOMANYHOPS = 483,
    CALL_E_REASON_CODE_ADDRESSINCOMPLETE = 484,
    CALL_E_REASON_CODE_AMBIGUOUS = 485,
    CALL_E_REASON_CODE_BUSYHERE = 486,
    CALL_E_REASON_CODE_REQUESTTEMINATED = 487,
    CALL_E_REASON_CODE_NOTACCEPTABLEHERE = 488,
    CALL_E_REASON_CODE_REQUESTPENDING = 491,
    CALL_E_REASON_CODE_UNDECIPHERABLE = 493,

    CALL_E_REASON_CODE_SERVERINTERNALERROR = 500,
    CALL_E_REASON_CODE_NOTIMPLEMENTED = 501,
    CALL_E_REASON_CODE_BADGATEWAY = 502,
    CALL_E_REASON_CODE_SERVICEUNAVAILABLE = 503,
    CALL_E_REASON_CODE_SERVERTIMEOUT = 504,
    CALL_E_REASON_CODE_VERSIONNOTSUPPORTED = 505,
    CALL_E_REASON_CODE_MESSAGETOOLARGE = 513,

    CALL_E_REASON_CODE_BUSYEVERYWHERE = 600,
    CALL_E_REASON_CODE_DECLINE = 603,
    CALL_E_REASON_CODE_DOESNOTEXISTEVERYWHERE = 604,
    CALL_E_REASON_CODE_NOTACCEPTABLE = 606,

    CALL_E_REASON_CODE_END
} CALL_E_REASON_CODE;


/*TODO: same to CALL_E_SERVICE_RIGHT_TYPE, need del one. */

/* ������ҵ������*/
typedef enum tagCALL_E_SERVICE_CALL_TYPE
{
    CALL_E_SERVICE_CALL_NORMAL,


    CALL_E_SERVICE_CALL_TYPE_REG_DND,           /** �Ǽ�DND */
    CALL_E_SERVICE_CALL_TYPE_UNREG_DND,        /** ȡ���Ǽ�DND */

    
    CALL_E_SERVICE_CALL_TYPE_CALL_WAIT_ACTIVE,            /* ���еȴ����� */
    CALL_E_SERVICE_CALL_TYPE_CALL_WAIT_DEACTIVE,        /* ���еȴ��ر� */

    CALL_E_SERVICE_CALL_TYPE_REG_SCAPRIVATE,      /** �Ǽ�˽�˺��� */
    CALL_E_SERVICE_CALL_TYPE_UNREG_SCAPRIVATE,  /** ȡ���Ǽ�˽�˺��� */


    /* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR-0000159474] [2013/1/18] [zhanglusha 00219468]]
       �޸�ԭ��: ��������ҵ��:���羲����privacy */

    CALL_E_SERVICE_CALL_TYPE_REG_ALERT_SILENCE,     /** �Ǽǹ��������羲�� */
    CALL_E_SERVICE_CALL_TYPE_UNREG_ALERT_SILENCE,   /** ȡ�����������羲�� */
    CALL_E_SERVICE_CALL_TYPE_REG_PRIVACY,           /** �Ǽ�privacyҵ��*/
    CALL_E_SERVICE_CALL_TYPE_UNREG_PRIVACY,         /** ȡ��privacyҵ��*/

    /* END   add: [[eSpace 7900 V100R001C02B010] [IR-0000159474] [2013/1/18] [zhanglusha 00219468]] */

    CALL_E_SERVICE_CALL_TYPE_SET_CALLPARK,      /** ���ú���פ�� */
    CALL_E_SERVICE_CALL_TYPE_DIRECTCALLPARK,    /** ֱ�Ӻ���פ�� */
    CALL_E_SERVICE_CALL_TYPE_GET_CALLPARK,      /** ȡ�غ���פ�� */

    /**����ǰת */
    CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION,                      /**������ǰת*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY,                           /**��æǰת*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY,                          /**��Ӧ��ǰת*/

    /**��������ǰת */
    CALL_E_SERVICE_CALL_TYPE_CFUVoiceMail_Active,        /* ������ת��������Ǽ�(����) */
    CALL_E_SERVICE_CALL_TYPE_CFUVoiceMail_Deactive,     /* ������ת��������ע��*/
    CALL_E_SERVICE_CALL_TYPE_CFBVoiceMail_Active,        /* ��æ ת��������Ǽ�(����) */
    CALL_E_SERVICE_CALL_TYPE_CFBVoiceMail_Deactive,   /* ��æ ת��������ע��*/
    CALL_E_SERVICE_CALL_TYPE_CFNVoiceMail_Active,        /* ��Ӧ�� ת��������Ǽ�(����) */
    CALL_E_SERVICE_CALL_TYPE_CFNVoiceMail_Deactive,   /* ��Ӧ�� ת��������ע��*/
    CALL_E_SERVICE_CALL_TYPE_CFOVoiceMail_Active,        /* ���� ת��������Ǽ�(����) */
    CALL_E_SERVICE_CALL_TYPE_CFOVoiceMail_Deactive,   /* ���� ת��������ע��*/
    /*basic*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Active,                      /**������ǰת*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Deactive,
    CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Active,                           /**��æǰת*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Deactive,
    CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Active,                          /**��Ӧ��ǰת*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Deactive,
    CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Active,                          /**����ǰת*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Deactive,

    /** ��������ҵ�������ڴ����*/
    CALL_E_SERVICE_CALL_TYPE_SCAPRIVATE_ACTIVE,        /* ������·˽�˺��еǼ�*/
    CALL_E_SERVICE_CALL_TYPE_SCAPRIVATE_DEACTIVE,     /* ������·˽�˺���ע��*/

    CALL_E_SERVICE_CALL_TYPE_ACBCALL_ACTIVE,        /* ���лغ��Ǽ�(����) */
    CALL_E_SERVICE_CALL_TYPE_ACBCALL_DEACTIVE,     /* ���лغ�ע�� */

    CALL_E_SERVICE_CALL_TYPE_GOURPPICKUP,                  /**Ⱥ�����*/
    CALL_E_SERVICE_CALL_TYPE_DESPICKUP,                    /**ָ������*/

    CALL_E_SERVICE_CALL_TYPE_DIVERT,                /**ƫת**/

    /* BEGIN add: [[V100R001C50] [IR.IPT.025] [2013/12/3] [WuDingyuan]]
       �޸�ԭ��: ������:�ܾ�ǰת���� */
    CALL_E_SERVICE_CALL_TYPE_REG_DICF,          /** �Ǽ�DICF */
    CALL_E_SERVICE_CALL_TYPE_UNREG_DICF,        /** ע��DICF */
    /* END   add: [[V100R001C50] [IR.IPT.025] [2013/12/3] [WuDingyuan]] */

    CALL_E_SERVICE_CALL_TYPE_ABSENT_ON,        /** ����absence */
    CALL_E_SERVICE_CALL_TYPE_ABSENT_OFF,       /** �ر�absence */

    CALL_E_SERVICE_CALL_TYPE_MCID,             /* ������и��� */

    CALL_E_SERVICE_CALL_TYPE_CALL_LIMIT_ACTIVE,         /** ���������޺� */
    CALL_E_SERVICE_CALL_TYPE_CALL_LIMIT_DEACTIVE,       /** �ر������޺� */

    CALL_E_SERVICE_CALL_TYPE_ATTENDCONF_BY_ONEKEY,                /**һ�����**/
    /* BEGIN add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] 
       �޸�ԭ��: huntgroupǩ��ǩ�� */
    CALL_E_SERVICE_CALL_TYPE_HUNTGROUP_SIGNIN,      /* huntgroupǩ�� */
    CALL_E_SERVICE_CALL_TYPE_HUNTGROUP_SIGNOUT,     /* huntgroupǩ�� */
    CALL_E_SERVICE_CALL_TYPE_GET_VIRTUALVM,
    /* END   add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] */

    CALL_E_SERVICE_CALL_TYPE_BUIT

} CALL_E_SERVICE_CALL_TYPE;




typedef enum tagCALL_E_DTMF_TONE
{
    CALL_E_DTMF0,   /**< dtmf����0 */
    CALL_E_DTMF1,   /**< dtmf����1 */
    CALL_E_DTMF2,   /**< dtmf����2 */
    CALL_E_DTMF3,   /**< dtmf����3 */
    CALL_E_DTMF4,   /**< dtmf����4 */
    CALL_E_DTMF5,   /**< dtmf����5 */
    CALL_E_DTMF6,   /**< dtmf����6 */
    CALL_E_DTMF7,   /**< dtmf����7 */
    CALL_E_DTMF8,   /**< dtmf����8 */
    CALL_E_DTMF9,   /**< dtmf����9 */
    CALL_E_DTMFSTAR,    /**< dtmf����'*' */
    CALL_E_DTMFJIN,     /**< dtmf����'#' */
    CALL_E_DTMFA,   /**< dtmf����A */
    CALL_E_DTMFB,   /**< dtmf����B */
    CALL_E_DTMFC,   /**< dtmf����C */
    CALL_E_DTMFD,   /**< dtmf����D */
    CALL_E_DTMFFLASH,   /**< dtmf����FLASH */
    CALL_E_BUTT
} CALL_E_DTMF_TONE;




/** �ϱ���������¼� */
/*Do we need split it to basic and advanced  notify?*/
typedef enum tagCALL_E_CALL_EVENT
{
    CALL_E_EVT_BEGIN = 0,

    CALL_E_EVT_SIPACCOUNT_INFO,                     /**< ֪ͨ�ϲ�Ӧ�ã�SIP�˻���Ϣ�ı� 1*/
    CALL_E_EVT_CALL_STARTCALL_RESULT,               /*���������Ӧ���첽2*/

    CALL_E_EVT_CALL_INCOMMING,                      /**< �����¼� 3*/
    CALL_E_EVT_CALL_OUTGOING,                       /**< �����¼� 4*/
        
    CALL_E_EVT_CALL_RINGBACK,                        /**< �������¼� */
    CALL_E_EVT_CALL_CONNECTED,                        /**< ͨ���ѽ��� */
    CALL_E_EVT_CALL_ENDED,                            /**< ��н��� */
    CALL_E_EVT_CALL_DESTROY,                        /**8< ɾ������ID */
    CALL_E_EVT_CALL_RTP_CREATED,                    /** RTPͨ���ѽ��������Խ��ж��β��� */
    CALL_E_EVT_CALL_ADD_VIDEO,
    CALL_E_EVT_CALL_DEL_VIDEO,
    CALL_E_EVT_CALL_MODIFY_VIDEO_RESULT,

    CALL_E_EVT_REFRESH_VIEW,                /*��Ƶviewˢ��֪ͨ*/
    CALL_E_EVT_MOBILE_ROUTE_CHANGE,                       /**�ƶ�·�ɱ仯֪ͨ*/
    CALL_E_EVT_AUDIO_END_FILE,   /** ��Ƶ�ļ����Ž���֪ͨ*/
    CALL_E_EVT_NET_QUALITY_CHANGE,  /** ���������ı�֪ͨ*/
    CALL_E_EVT_STATISTIC_NETINFO, /** ��������ͳ����Ϣ*/
    CALL_E_EVT_STATISTIC_MOS,   /** MOS���ϱ�*/ 
    /**��������Ƶ�����ϱ�ulQualityLevel 0-5 level=0ʱerrorֵ��Ч������� 0 : û�д��� 1 : ���緢�˴��� 2 : �����ն˴��� 3 : �����շ�������*/
    CALL_E_EVT_SPKDEV_VOLUME_CHANGE,           /*�������豸�����仯(pc/mac)*/
    CALL_E_EVT_MICDEV_VOLUME_CHANGE,           /*��˷��豸�����仯(pc/mac)*/
    CALL_E_EVT_AUDIO_UNIT_INIT,           /*��Ƶ��Ԫ��ʼ�����֪ͨ(������֪ͨ�ϲ�����·��)*/
    CALL_E_EVT_AUDIO_SET_INDEVICE_ERR,    /*��Ƶ���������豸ʧ��*/
    CALL_E_EVT_AUDIO_SET_OUTDEVICE_ERR,    /*��Ƶ��������豸ʧ��*/

    CALL_E_EVT_VIDEO_OPERATION, /**��Ƶ����*/
    CALL_E_EVT_VIDEO_STATISTIC_NETINFO,     /**��Ƶ��������ͳ����Ϣ*/
    CALL_E_EVT_VIDEO_QUALITY,   /**��Ƶ����*/
    CALL_E_EVT_VIDEO_FRAMESIZE_CHANGE,  /**��Ƶ��С���*/

    CALL_E_EVT_SESSION_MODIFIED, /**�Ự�޸����֪ͨ*/
    CALL_E_EVT_SESSION_CODEC,    /**�Ự����ʹ�õ�codec֪ͨ*/

    CALL_E_EVT_CALL_HOLD_SUCCESS,                   /**< ���ֳɹ� */
    CALL_E_EVT_CALL_HOLD_FAILED,                    /**< ����ʧ�� */
    CALL_E_EVT_CALL_UNHOLD_SUCCESS,                 /**< �ָ��ɹ� */
    CALL_E_EVT_CALL_UNHOLD_FAILED,                  /**< �ָ�ʧ�� */

    CALL_E_EVT_CALL_ENDCALL_FAILED,                 /**< ����ͨ��ʧ�� */
    CALL_E_EVT_CALL_DIVERT_FAILED,                  /**< ƫתʧ�� */

    CALL_E_EVT_CALL_BLD_TRANSFER_SUCCESS,           /**< äת�ɹ� */
    CALL_E_EVT_CALL_BLD_TRANSFER_FAILED,            /**< äתʧ�� */
    CALL_E_EVT_CALL_ATD_TRANSFER_SUCCESS,           /**< ��ѯת�ɹ� */
    CALL_E_EVT_CALL_ATD_TRANSFER_FAILED,            /**< ��ѯתʧ�� */


    CALL_E_EVT_SET_IPT_SERVICE_SUCCESS,        /*21* �Ǽ�ҵ��ɹ�,���ں��п���ʹ�� */
    CALL_E_EVT_SET_IPT_SERVICE_FAILED,         /** �Ǽ�ҵ��ʧ��,���ں��п���ʹ�� */

    CALL_E_EVT_SIPACCOUNT_WMI,                      /**< ����֪ͨ*/
    CALL_E_EVT_VVM_DOWNLOAD_SUCCESS_NOTIFY,          /*VVM���ؽ��֪ͨ*/
    CALL_E_EVT_VVM_DOWNLOAD_FAIL_NOTIFY,
    CALL_E_EVT_VVM_FORWARD_SUCCESS_NOTIFY,           /*VVMת�����Խ��֪ͨ */
    CALL_E_EVT_VVM_FORWARD_FAIL_NOTIFY,
    CALL_E_EVT_VVM_DELETE_SUCCESS_NOTIFY,           /*VVMɾ�����Խ��֪ͨ */
    CALL_E_EVT_VVM_DELETE_FAIL_NOTIFY,
    CALL_E_EVT_VVM_DELETEALL_SUCCESS_NOTIFY,           /*30 VVMɾ���������Խ��֪ͨ */
    CALL_E_EVT_VVM_DELETEALL_FAIL_NOTIFY,    
        
    CALL_E_EVT_CALL_VoiceMail_SUB_SUCCESS,          /*�������䶩�Ľ�� */
    CALL_E_EVT_CALL_VoiceMail_SUB_FAILED,
    
    CALL_E_EVT_TO_UI_JOINT_START,                  /* ���������¼�*/
    CALL_E_EVT_TO_UI_JOINT_CLOSE,                  /* �����ر��¼�*/
    CALL_E_EVT_TO_UI_JOINT_ACCEPTCALL,             /* ���������¼�*/
    CALL_E_EVT_TO_UI_JOINT_STARTCALL,              /* ���������¼�*/
    CALL_E_EVT_TO_UI_JOINT_HUNGUP,                 /* ���������¼�*/
    CALL_E_EVT_TO_UI_JOINT_HOLD,                   /* ������������ */
    CALL_E_EVT_TO_UI_JOINT_UNHOLD,                 /* �����ָ����� */
    CALL_E_EVT_TO_UI_JOINT_DIVERT,                 /* ����ƫת���� */
    CALL_E_EVT_TO_UI_JOINT_BLDTRANSFER,            /* ����äת���� */
    CALL_E_EVT_TO_UP_JOINT_TO_CONF,                /* ��������ת���� */
    CALL_E_EVT_TO_UI_JOINT_DTMF,
    CALL_E_EVT_TO_UI_JOINT_CONFCREATE,

    CALL_E_EVT_TO_UI_JOINT_ONLINE,                  /*������������*/
    CALL_E_EVT_TO_UI_JOINT_OFFLINE,                 /*������������*/
    CALL_E_EVT_TO_UI_JOINT_ONHOOK,                  /*���������ѹһ�*/
    CALL_E_EVT_TO_UI_JOINT_OFFHOOK,                 /*����������ժ��*/
    CALL_E_EVT_TO_UI_JOINT_OUTGOING,                /*���������Ѻ���*/
    CALL_E_EVT_TO_UI_JOINT_ESTABLISHED,             /*������������ͨ����*/
    CALL_E_EVT_TO_UI_JOINT_RINGRING,                /*������������*/
    CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PHONE,
    CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PC,
    CALL_E_EVT_TO_UI_JOINT_CREATE_CONFERENCE,       /* IPPHONE����֪ͨ*/
    CALL_E_EVT_TO_UI_JOINT_REFER_RESULT,
    CALL_E_EVT_TO_UI_JOINT_STARTVIDEOCALL,              /* ������Ƶ�����¼�*/
    CALL_E_EVT_TO_UI_JOINT_CONF_RESULT,              /* ����PC������֪ͨ�����ķ�����Ϣ*/
    
    CALL_E_EVT_TO_UI_CTD_INFO,
    
    CALL_E_EVT_SERVER_LINK_OK,                     /*���������������������� �� suijun193874 */

    CALL_E_EVT_CALL_RECORD_SUCCESS,                   /**< ¼�������ɹ� */
    CALL_E_EVT_CALL_RECORD_FAILED,                    /**< ¼������ʧ�� */
    CALL_E_EVT_CALL_UNRECORD_SUCCESS,                 /**< ¼���رճɹ� */
    CALL_E_EVT_CALL_UNRECORD_FAILED,                  /**< ¼���ر�ʧ�� */

    CALL_E_EVT_CALL_CALLINFO_SUB_FAILED,            /**< ������·״̬����ʧ�� */
    CALL_E_EVT_CALL_CALLINFO_UNSUB_FAILED,          /**< ������·״̬ȥ����ʧ�� */
    CALL_E_EVT_CALL_LINESEIZE_UNSUB_FAILED,         /**< ����ժ��ȥ����ʧ�� */
    CALL_E_EVT_CALL_LINESEIZE_UNSUB_SUCCESS,         /**< ����ժ��ȥ���ĳɹ�*/
    CALL_E_EVT_CALL_LINESEIZE_SUCCESS,
    CALL_E_EVT_CALL_LINESEIZE_FAILED,               /**< ����ժ��ʧ�� */
    CALL_E_EVT_CALL_CALLINFO_NOTIFY,                /**<������·״̬֪ͨ*/    

    CALL_E_EVT_CALL_MODIFY_SUCCESS,                 /**< �޸�ͨ���ɹ� */
    CALL_E_EVT_CALL_MODIFY_FAILED,                  /**< �޸�ͨ��ʧ�� */
    CALL_E_EVT_CALL_JOIN_CONF,                      /**< ͨ�����뱾�ػ��飬֪ͨͨ��״̬ */
    CALL_E_EVT_LCONF_JOIN_SUCCESS,                  /**< ���ػ������ɹ� add by h00206999 */
    CALL_E_EVT_LCONF_JOIN_FAILED,                   /**< ���ػ������ʧ�� add by h00206999 */
    CALL_E_EVT_LCONF_TALK_STATE_CHANGE,             /**< ����߷���״̬�ı� */
    CALL_E_EVT_LCONF_CONFEREE_DROPED,               /**< �޳������/������˳��᳡ */
    CALL_E_EVT_LCONF_CONFER_ENDED,                  /**< ��������֪ͨ */
    CALL_E_EVT_LCONF_HOLD_SUCESS,                   /**< ���ֻ᳡�ɹ�*/
    CALL_E_EVT_LCONF_HOLD_FAILED,                   /**< ���ֻ᳡ʧ�� */
    CALL_E_EVT_LCONF_UNHOLD_SUCESS,                 /**< �ָ��᳡�ɹ� */
    CALL_E_EVT_LCONF_UNHOLD_FAILED,                 /**< �ָ��᳡ʧ�� */
    CALL_E_EVT_CALL_MOBILE_EXTEND_SUCCESS,          /**�ֻ��ֻ��л��ɹ�*/
    CALL_E_EVT_CALL_MOBILE_EXTEND_FAILED,           /*70*�ֻ��ֻ��л�ʧ�� */

    CALL_E_EVT_CALL_ACBCALL_REQ,                  /**< ACB���� */
    CALL_E_EVT_CALL_ACBCALL_TIMEOUT,              /**< ACB��ʱ */
    CALL_E_EVT_CALL_CALLPARK_GET_SUCCESS,       /* פ��ȡ�سɹ�*/
    CALL_E_EVT_CALL_CALLPARK_GET_FAILED,        /* פ��ȡ��ʧ��*/
    CALL_E_EVT_CALL_CALLPARK_INVALID,             /**< פ����ʱ���߱�ȡ�� */
    
    CALL_E_EVT_CONTACT_STATUS_CHANGE,            /**< ��ϵ��״̬�ϱ� */
    CALL_E_EVT_CONTACTINCRE_STATUS_CHANGE,            /**< PGM��ϵ�������ϱ� */
    CALL_E_EVT_CONTACT_INFO,                      /**< ��ϵ����Ϣ */
    CALL_E_EVT_PHONE_SETTING_STATUS_CHANGE,
    
    CALL_E_EVT_CALL_AUTHORIZE_SUCCESS,              /* ��Ȩ�ɹ�  */
    CALL_E_EVT_CALL_AUTHORIZE_FAILED,               /*80 ��Ȩʧ�� */
    CALL_E_EVT_NEW_SERVICE_RIGHT,                   /* 81 ҵ��Ȩ�޸ı䣬֪ͨ���� */
    
    CALL_E_EVT_SERVERCONF_INCOMING,                  /**< ���������¼� */
    CALL_E_EVT_SERVERCONF_CREATE_RESULT,            /**< ���������� */
    CALL_E_EVT_SERVERCONF_CONNECT_RESULT,           /**< ��������� */
    CALL_E_EVT_SERVERCONF_ADDATTENDEE_RESULT,      /**< �������߽�� */
    CALL_E_EVT_SERVERCONF_REFRESHLIST,              /**< ˢ��������б� */
    CALL_E_EVT_SERVERCONF_SUBJECT,              /**< �ϱ���������*/
    CALL_E_EVT_SERVERCONF_CHAIRMAN_NUM,              /**< �ϱ���ϯ����*/
    CALL_E_EVT_SERVERCONF_DATACONF_PARAM,    /* �ϱ����ݻ�����ز��� */
    CALL_E_EVT_SERVERCONF_MODIFYATTENDEE_RESULT,   /**< �޸�����߷���Ȩ��� */
    CALL_E_EVT_SERVERCONF_DROPATTENDEE_RESULT,      /**< �߳�����߽�� */
    CALL_E_EVT_SERVERCONF_END_RESULT,                /**< ���������� */
    CALL_E_EVT_SERVERCONF_ATTENDEEKICKED,            /**< ����߱��߳� */
    CALL_E_EVT_SERVERCONF_ENDED,                      /**< ���鱻���� */
    CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_SUCCESS,   /**< ����߼���ɹ� */
    CALL_E_EVT_SERVERCONF_ACCESSCODEJOINED_SUCCESS,   /**< ��������м��룬����߼���ɹ� */
    CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_FAILED,   /**< ����߼���ʧ�� */
    CALL_E_EVT_SERVERCONF_ATTENDEEQUIT,              /**< ������˳� */
    CALL_E_EVT_SERVERCONF_ADDRESSOR,                 /**< ��ʾ������ */
    CALL_E_EVT_SERVERCONF_BETRANSFERTOCONF,        /**< ��ת���� */
    CALL_E_EVT_SERVERCONF_TRANSFERTOCONF_SUCCESS,  /**< ת����ɹ� */
    CALL_E_EVT_SERVERCONF_TRANSFERTOCONF_FAILED,   /**< ת����ʧ�� */
    CALL_E_EVT_SERVERCONF_HOLD_SUCESS,                   /**< ���ֻ᳡�ɹ�*/
    CALL_E_EVT_SERVERCONF_HOLD_FAILED,                   /**< ���ֻ᳡ʧ�� */
    CALL_E_EVT_SERVERCONF_UNHOLD_SUCESS,                 /**< �ָ��᳡�ɹ� */
    CALL_E_EVT_SERVERCONF_UNHOLD_FAILED,                 /**< �ָ��᳡ʧ�� */
    CALL_E_EVT_SERVERCONF_MUTE_STATUS_CHANGE,      /**< �᳡����״̬��� */
    CALL_E_EVT_SERVERCONF_LOCK_STATUS_CHANGE,      /**< �᳡����״̬��� */ 

    CALL_E_EVT_PICKUP_NOTIFY,                                            /**< UC2.0 ͬ�����֪ͨ/ȡ��*/
    CALL_E_EVT_FORWARD_RESULT,                /**< ǰת���еĽ��*/
    CALL_E_EVT_IMS_FORWARD_RESULT,                /**< IMS��ǰת��Ŀ�ĺ�����*/
    
    CALL_E_EVT_CALL_LOGOUT_NOTIFY,         /**֪ͨ����logout**/

    CALL_E_EVT_TURN_CALL_NOTIFY,/*֪ͨ���棬�ֻ��ֻ����ֻ��������Ҷ� */

    CALL_E_EVT_SUB_BLF_RESULT_NOTIFY, /*BLF���Ľ�� */
    CALL_E_EVT_SUB_RLS_RESULT_NOTIFY, /*RLS���Ľ�� */
    CALL_E_EVT_CALL_CALLOUT_TIMEOUT,  /**������ʱ*/
    CALL_E_EVT_CALL_REPORTED_CALLINFO,/*���������ϱ�**/

    CALL_E_EVT_CALL_CLEAN_SCALINE,                /**<���������·״̬*/
    CALL_E_EVT_UM_MSG_NOTIFY,           /**UM �¼�����*/
    CALL_E_EVT_CALL_INTERCOM_NUMBER,    /** �ϱ�����AA���͵�intercom���� */
    CALL_E_EVT_CALL_CALLPARK_SUCCESS,
    CALL_E_EVT_CALL_183_BUSY,       /**ͨ���յ�183busy*/
    CALL_E_EVT_CALL_PICKUP_REMOTE_INFO,       /**200ok��Я���������з���Ϣ*/
    CALL_E_EVT_CALL_ACB_LIST_NOTIFY,       /**�غ��б�֪ͨ*/
    CALL_E_EVT_CALL_PICKUP_INTERCOM_SUCCESS,
    CALL_E_EVT_CALL_PICKUP_INTERCOM_FAILED,
    CALL_E_EVT_CALL_INTERCOM_BEPICKUP,  /** intercom ��pick up �¼�*/
    CALL_E_EVT_CALL_UPATE_REMOTEINFO,   /** ����Զ�˺�����Ϣ  */
    CALL_E_EVT_CALL_SRTP_STATE,         /** SRTP������ر� */

    CALL_E_EVT_CALL_PINCODE_VALID,       /*ͨ�����Ƿ����� PinCode */
    CALL_E_EVT_CALL_PINCODE_OK,          /*������֤ͨ�� */
    CALL_E_EVT_CALL_PINCODE_ERROR,       /*������֤ʧ�ܣ����������� */

    CALL_E_EVT_CALL_CALLACCEPTED_RMTCTRL,       /* �Զ˻ظ� 200 OK �� P-Notification: Callee Ctrl */
    CALL_E_EVT_CALL_CALL_REINVITED,             /* Call���ܶԶ˵�Reinvite�� ���ϱ��� */

    CALL_E_EVT_SET_IPT_SERVICE_BATCH_SUCCESS,  /** �����Ǽ�ҵ��ɹ�  */
    CALL_E_EVT_SET_IPT_SERVICE_BATCH_FAILED,   /** �����Ǽ�ҵ��ʧ��  */

    CALL_E_EVT_SET_CALL_LIMIT_ON_LOCKED,       /* �Ǽ������޺�ʧ��(������) */

    CALL_E_EVT_SET_CALL_LIMIT_OFF_LOCKED,      /* ȡ�������޺�ʧ��(������) */

    CALL_E_EVT_SERVERCONF_MERGER_RESULT,       /* �ϲ������� */
    CALL_E_EVT_SERVERCONF_SPLIT_RESULT,        /* ��ֻ����� */
    CALL_E_EVT_ACCOUNT_STATUS_CHANGE,          /**�˺�״̬��� */
    CALL_E_EVT_MESSAGE_RELOGIN_REQUEST,        /** �յ�relogin��message��֪ͨ��������AA��¼ */

    CALL_E_EVT_CALL_ONEKEY_TO_WM_ON_CALL_SUCCESS,
    CALL_E_EVT_CALL_ONEKEY_TO_WM_ON_CALL_FAIL,

    CALL_E_EVT_CALL_CALLPARK_FAILED,           /* פ��ʧ�� */

    CALL_E_EVT_SERVERCONF_CONNECT_ONEKEY_TO_CONF_RESULT, /**< һ����������� */
    CALL_E_EVT_SERVERCONF_VIDEOCONF_CREATEWND_RESULT,   /**< ��Ƶ���鴴�����ڽ��*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_CREATEVIDEO_MEETING_FAILED, /** ������Ƶ����ʧ��*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_LEAVECONF_RESULT,   /** < ��Ƶ���������뿪������*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_ATTEND_JOINED_CONF,   /** < ��Ƶ�����Ա�������*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_END_CONF,      /** < ��Ƶ�������*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_BEKICKOUT_CONF,      /** < ��Ƶ�����б���ϯ�߳�*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_LEAVE_CONF,      /** < ��Ƶ��������������˳�*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_STATUS_CHANGE,    /**<��Ƶ����������߰����Լ�����Ƶ״̬�ı�֪ͨ*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_REQUEST_CHANGE,   /**< ��Ƶ��������Ƶ�����������������/�ر�*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_DEVICE_STATUS,    /**<��Ƶ����������߰����Լ�����Ƶ�豸״̬�ı�֪ͨ: �β�*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_JOINCHANNEL,          /** ��Ƶ���뵽�ߵ���ʱ�ķ����������������뵽�ߵ���*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_DISCONNECT,          /** ��Ƶ����ʧȥ����*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_RECONNECT,     /** ��Ƶ������������*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_USERDEVICE_STATUSCHANGE,     /** ��Ƶ�������豸״̬�ı�(��ͣ����ȡ����ͣ)*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_WARNING_FLOWCONTROL,    /** ���ظ澯(��ǰ��Ƶ�����£�����Ҫ���أ���ر���Ƶ����ʾ)*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_NOTIFY_FLOWCONTROL,     /** ������Ƶ�ֱ��ʸ���֪ͨ*/
    CALL_E_EVT_SERVERCONF_VOICECONF_TO_VIDEOCONF_SUCCESS,   /**< ��Ƶ����ת��Ƶ����ɹ� */
    CALL_E_EVT_SERVERCONF_VOICECONF_TO_VIDEOCONF_FAILED,    /**< ��Ƶ����ת��Ƶ����ʧ��*/
    CALL_E_EVT_SERVERCONF_VIDEO_ON_FIRST_KEYFRAME,          /**< �ؼ�֪֡ͨ*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_NET_STATUS,             /**< ����״̬֪ͨ*/
    
    CALL_E_EVT_MEETING_MSG_NOTIFY,           /**�����¼�����*/

    CALL_E_EVT_GET_MEETING_CONF_RESULT,     /** ��ȡ�����б���*/
    CALL_E_EVT_GET_MEETING_CONF_XML_RESULT,     /** ��ȡ����XML �ļ����*/

    CALL_E_EVT_SIP_AUTH_INFO_WRITTEN,
    CALL_E_EVT_SWITCH_DND_SUCCESS,           /*�л�DNDģʽ�ɹ���add by l00214300@2014-3-7 */
    CALL_E_EVT_SWITCH_DND_FAIL,              /*�л�DNDģʽʧ�ܣ�add by l00214300@2014-3-7 */
    CALL_E_EVT_CALL_RECORDINFO_NOTIFY,

    /*TCר��֪ͨ*/
    CALL_E_EVT_SPKDEV_MUTE_CHANGE,           /*�������豸����״̬�仯 iMute ��ǰ����״̬ 0��ǰ״̬Ϊ�Ǿ���  ��0 ��ǰ״̬Ϊ����*/
    CALL_E_EVT_MICDEV_MUTE_CHANGE,           /*��˷��豸����״̬�仯 iMute ��ǰ����״̬ 0��ǰ״̬Ϊ�Ǿ���  ��0 ��ǰ״̬Ϊ����*/
    CALL_E_EVT_VMTC_VERSION_INFO,            /*VMTC�汾��Ϣ uiVerInfo �汾�ȽϽ�� 0:�汾���� 1:VM�汾�� 2:TC�汾�� */
    CALL_E_EVT_VMTC_DISCONNECT,              /*VMTC�Ͽ�����֪ͨ uiInfo �Ͽ�������Ϣ*/
    CALL_E_EVT_VMTC_CONNECTOK,               /*VMTC���ӳɹ�֪ͨ uiInfo ���ӳɹ���Ϣ*/

    CALL_E_EVT_SYN_MISSCALL,                   /* ����ͨ����¼ͬ�� */
    CALL_E_EVT_HUNTGROUP_STATUS_CHANGE,
    CALL_E_EVT_PAGING_INCOMING,
    CALL_E_EVT_PAGING_ENDED,

    CALL_E_EVT_BUTT
} CALL_E_CALL_EVENT;




/** SIP�˻�ע��״̬ */
typedef enum tagCALL_E_REG_STATE
{
    CALL_E_REG_STATE_UNREGISTER,     /**< SIP�˻�δע�� */
    CALL_E_REG_STATE_REGISTERING,    /**< SIP�˻�ע���� */
    CALL_E_REG_STATE_DEREGISTERING,  /**< SIP�˻�ע���� */
    CALL_E_REG_STATE_REGISTERED,     /**< SIP�˻���ע�� */
    CALL_E_REG_STATE_BUTT            /**< SIP�˻���Ч״̬ */
} CALL_E_REG_STATE;

/** �������� */
typedef enum tagCALL_E_CALL_TYPE
{
    CALL_E_CALL_TYPE_IPAUDIO,        /**< IP�������� */
    CALL_E_CALL_TYPE_IPVIDEO,         /**< IP��Ƶ���� */
    CALL_E_CALL_TYPE_BUTT            /**< ��Ч���ͺ��� */
} CALL_E_CALL_TYPE;



/** ���л���״̬ */
typedef enum tagCALL_E_CALL_STATE
{
    CALL_E_CALL_STATE_IDLE,    /**< ���п���̬ */
    CALL_E_CALL_STATE_IN,       /**< ���к���̬ */
    CALL_E_CALL_STATE_OUT,    /**< ���к���̬ */
    CALL_E_CALL_STATE_LIVE,   /**< ����ͨ��̬ */
    CALL_E_CALL_STATE_HOLD,  /**< ���б���̬ */
    CALL_E_CALL_STATE_END,    /**< ���н���̬ */
    CALL_E_CALL_STATE_BUTT   /**< ������Ч̬ */
} CALL_E_CALL_STATE;

/** �豸���� */
typedef enum tagCALL_E_DEVICE_TYPE
{
    CALL_E_CALL_DEVICE_MIC,         /* ��˷��豸 */
    CALL_E_CALL_DEVICE_SPEAK,       /* �������豸 */
    CALL_E_CALL_DEVICE_VIDEO,       /* ��Ƶ�豸 */
    CALL_E_CALL_DEVICE_BUTT         /* ��Ч�豸 */
} CALL_E_DEVICE_TYPE;

/**�������ͣ�add by w0213797 */
typedef enum tagCALL_E_CALL_ALERTTYPE
{
    CALL_E_CALL_ALERTTYPE_COMMON = 0x1,        /**< ��ͨ���� */
    CALL_E_CALL_ALERTTYPE_INTERNAL,        /**< Ⱥ�� */
    CALL_E_CALL_ALERTTYPE_EXTERNAL,        /**< Ⱥ�� */
    CALL_E_CALL_ALERTTYPE_NETWORK,        /**< ������� */

    /* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/1/29] [zhanglusha 00219468]]
       �޸�ԭ��: ����������ǿ_���羲�� */
    CALL_E_CALL_ALERTTYPE_SILENCE,        /**< ���羲�� */
    /* END   add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/1/29] [zhanglusha 00219468]] */
    CALL_E_CALL_ALERTTYPE_WAKEUP,
   /* BEGIN add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] 
      �޸�ԭ��: huntgroup���� */
   CALL_E_CALL_ALERTYPE_HUNTGROUP,
   /* END   add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] */

    CALL_E_CALL_ALERTTYPE_BUTT = 0x0
} CALL_E_CALL_ALERTTYPE;


/** �ϱ�������������������� */
typedef enum tagCALL_E_MSG_WAIT_TYPE
{
    CALL_E_MSG_WAIT_TYPE_VOICE = 0,    /**< ������Ϣ */
    CALL_E_MSG_WAIT_TYPE_VIDEO,        /**< ��Ƶ��Ϣ */
    CALL_E_MSG_WAIT_TYPE_FAX,          /**< ������Ϣ */
    CALL_E_MSG_WAIT_TYPE_PAGER,        /**< ҳ����Ϣ */
    CALL_E_MSG_WAIT_TYPE_MULTIMEDIA,   /**< ý����Ϣ */
    CALL_E_MSG_WAIT_TYPE_TEXT,         /**< �ı���Ϣ */
    CALL_E_MSG_WAIT_TYPE_VITRUALVM,    /**< ��������������Ϣ */
    CALL_E_MSG_WAIT_TYPE_BUTT          /**< δ֪��Ϣ */
} CALL_E_MSG_WAIT_TYPE;

/* �����ɫ */
typedef enum tagCALL_E_CONF_ROLE
{
    CALL_E_CONF_ROLE_ATTENDEE,         /* ����� */
    CALL_E_CONF_ROLE_CHAIRMAN,         /* ��ϯ�� */
    CALL_E_CONF_ROLE_CONFCHAIN,        /* ����(�ϲ�����ҵ��) */
    CALL_E_CONF_ROLE_BUTT
} CALL_E_CONF_ROLE;

/* ���������������״̬ */
typedef enum tagCALL_E_CONF_STATE
{
    CALL_E_CONF_ATTENDEE_INVITING,              /* ������  */
    CALL_E_CONF_ATTENDEE_INVITE_FAIL,           /* ����ʧ��  */
    CALL_E_CONF_ATTENDEE_ADD_FAIL,              /* ���ʧ��  */
    CALL_E_CONF_ATTENDEE_INCONF,                /* ������  */
    CALL_E_CONF_ATTENDEE_OUT,                   /*DTS2012111404123*/
    CALL_E_CONF_ATTENDEE_STATE_BUTT
} CALL_E_CONF_ATTENDEE_STATE;





/** ҵ��Ȩ��ҵ���б�ע��һ��Ҫ  ��CALL_S_SERVICERIGHT_CFG ��Ӧ*/
typedef enum tagCALL_E_SERVICE_RIGHT_TYPE
{
    CALL_E_SERVICE_RIGHT_TYPE_NULL = -1,
    CALL_E_SERVICE_RIGHT_TYPE_ABBRDIAL = 0,                                     /**< ��λ���� */
    CALL_E_SERVICE_RIGHT_TYPE_CTD,                                           /* 0 ������� */
    CALL_E_SERVICE_RIGHT_TYPE_CALLDEFLECTION,                               /* 1 ����ƫתҵ�� */
    CALL_E_SERVICE_RIGHT_TYPE_ATTENDANT,                                     /* 2 ����Ա  */
    CALL_E_SERVICE_RIGHT_TYPE_SECRETARYSERVICE,                             /* 3 ����ҵ�� */
    CALL_E_SERVICE_RIGHT_TYPE_SECRETARYSTATIONSERVICE,                     /* 4 ����̨ */
    /*CALL_E_SERVICE_RIGHT_TYPE_ANONYMOUSCALLREJECTION, */                       /* �������оܾ�  */
    CALL_E_SERVICE_RIGHT_TYPE_GROUPPICKUP,                                   /* 5 ͬ����� */
    CALL_E_SERVICE_RIGHT_TYPE_DESIGNATEPICKUP,                               /* 6 ָ������ */
    CALL_E_SERVICE_RIGHT_TYPE_ACB,                                            /* 7 �Զ��ؽ�ҵ�� */
    CALL_E_SERVICE_RIGHT_TYPE_RECORDING,                                     /* 8 ¼�� */
    CALL_E_SERVICE_RIGHT_TYPE_CALLTRANSFER,                                  /* 9 ����ת�� */
    CALL_E_SERVICE_RIGHT_TYPE_CALLPARK,                                      /* 10 ����Ԥ�� */
    CALL_E_SERVICE_RIGHT_TYPE_CALLHOLD,                                      /* 11 ���б��� */
    /*CALL_E_SERVICE_RIGHT_TYPE_BARGEININSERT,*/                                /* ǿ�� */
    /*CALL_E_SERVICE_RIGHT_TYPE_BARGEINDISCONNECT,*/                            /* ǿ��  */
    /*CALL_E_SERVICE_RIGHT_TYPE_BARGEINOVERRIDE, */                             /* ǿ�� */
    /*CALL_E_SERVICE_RIGHT_TYPE_BARGEINMONITOR, */                              /* ��*���ôʻ�*�� */
    CALL_E_SERVICE_RIGHT_TYPE_DONOTDISTURB,                                 /* 12 ����� */
    CALL_E_SERVICE_RIGHT_TYPE_THREEPARTYCONFERENCE,                         /* 13 ����ͨ�� */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_UNCONDITIONAL,                  /* 14 ������ת�� */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_ONBUSY,                         /* 15 ��æת�� */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_NOREPLY,                        /* 16 ��Ӧ��ת�� */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_OFFLINE,                        /* 17 ����ת�� */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_UNCONDITIONAL,    /* 18 ������ת�������� */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_ONBUSY,            /* 19 ��æת�������� */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_NOREPLY,           /* 20 ��Ӧ��ת�������� */
    /*CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOFAXMAILBOX_UNCONDITIONAL, */      /* ������ת����  */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_OFFLINE,        /* 21 ����ת�������� */
    /*CALL_E_SERVICE_RIGHT_TYPE_DATACONFERENCE, */                                /*  ���ݻ��� */
    /*CALL_E_SERVICE_RIGHT_TYPE_FILETRANSFER, */                                  /*  �ļ����� */
    /*CALL_E_SERVICE_RIGHT_TYPE_VIDEOCALL,  */                                    /*  ��Ƶͨ������ */
    CALL_E_SERVICE_RIGHT_TYPE_VOICECONFERENCE,                                /* 22 �������� */
    CALL_E_SERVICE_RIGHT_TYPE_CORPORATEDIRECTORY,                             /* 23 ��ҵͨѶ¼ */
    CALL_E_SERVICE_RIGHT_TYPE_INDIVIDUALDIRECTORY,                            /* 24 ����ͨѶ¼ */
    /*CALL_E_SERVICE_RIGHT_TYPE_INSTANTMESSAGE,*/                                  /* ��ʱ��Ϣ */
    CALL_E_SERVICE_RIGHT_TYPE_TURNPHONE,                                       /* 25 һ��ת�� */
    CALL_E_SERVICE_RIGHT_TYPE_VOICECALL,                                       /* 26 ��Ƶͨ������ */
    /*CALL_E_SERVICE_RIGHT_TYPE_CREATEGROUP,*/                                     /* ������     */
    /*CALL_E_SERVICE_RIGHT_TYPE_NOTIFICATION,*/                                    /* ֪ͨ     */
    /*CALL_E_SERVICE_RIGHT_TYPE_GROUPMESSAGE,*/                                    /*  Ⱥ����Ϣ     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MCTC,  */                                          /*  �ƶ��ն˼�ʱ����     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MCTD,  */                                          /*  �ƶ��ն˵������     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEVOICECALL, */                                /*  �ֻ�/IPAD�ͻ�����������     */
    /*CALL_E_SERVICE_RIGHT_TYPE_WEBVOICECALL,    */                                /*  WEB�ͻ�����������     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEDIGITALCONFERENCE, */                        /* �ֻ��ͻ������ݻ���     */
    /*CALL_E_SERVICE_RIGHT_TYPE_IPADDIGITALCONFERENCE,  */                         /* IPAD�ͻ������ݻ���     */
    /*CALL_E_SERVICE_RIGHT_TYPE_WEBDIGITALCONFERENCE, */                           /* WEB�ͻ������ݻ���     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEVIDEO,         */                            /*  �ֻ�/IPAD�ͻ�����Ƶ     */
    /*CALL_E_SERVICE_RIGHT_TYPE_WEBVIDEO,         */                               /*  WEB�ͻ�����Ƶ      */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEFILETRANSFER,  */                            /*  �ֻ�/IPAD�ͻ����ļ�����      */
    /*CALL_E_SERVICE_RIGHT_TYPE_WEBFILETRANSFER,     */                            /*  WEB�ͻ����ļ�����      */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEDIRECTORYRELATIONSHIP, */                    /* �ֻ�ͨ��¼����     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEBOOKINGCONFERENCE,  */                       /* �ֻ��ͻ���ԤԼ����     */
    /*CALL_E_SERVICE_RIGHT_TYPE_VIDEOCONFERENCE,    */                             /* ��Ƶ����     */
    /*CALL_E_SERVICE_RIGHT_TYPE_BINDOCSCLIENT,      */                             /* ��OCS�ͻ���     */
    CALL_E_SERVICE_RIGHT_TYPE_EXTENSIONMOBILITY,                              /* 27 �ֻ�Я��,AA�����ͣ�WEB���޸� */
    CALL_E_SERVICE_RIGHT_TYPE_SUBREGSTATE,                                     /* 28 �ֻ�Я��ʱ����ҵ��Ȩ��,AA�����ͣ�WEB���޸� */
    CALL_E_SERVICE_RIGHT_TYPE_BLF,                                              /* 29 BLF, AA�����ͣ�WEB���޸� */
    /* BEGIN add: [[DTS2012101703429] [2012/10/30] [caoruihong 00205112]] */
    CALL_E_SERVICE_RIGHT_TYPE_PRESENCE,                                             /*30 ״̬���� */
    /* END   add: [[DTS2012101703429] [2012/10/30] [caoruihong 00205112]] */
    CALL_E_SERVICE_RIGHT_TYPE_INTERCOM,                                          /* 31 intercomҵ�� */

    /* BEGIN add: [[V100R001C50] [IR.IPT.025] [2013/12/3] [WuDingyuan]]
       �޸�ԭ��: ������:�ܾ�ǰת���� */
    CALL_E_SERVICE_RIGHT_TYPE_DICF,                                    /* �ܾ�ǰת���� */
    /* END   add: [[V100R001C50] [IR.IPT.025] [2013/12/3] [WuDingyuan]] */
    CALL_E_SERVICE_RIGHT_TYPE_ABSENT,                                  /* ȱϯҵ�� */

    /* BEGIN add: [[V100R001C50] [IR.IPT.002] [2013/12/13] [zhanglusha 00219468]]
       �޸�ԭ��: VM�������� */
    CALL_E_SERVICE_RIGHT_TYPE_TURN_VM,                                 /* һ��ת��������*/
    /* END   add: [[V100R001C50] [IR.IPT.002] [2013/12/13] [zhanglusha 00219468]] */

    CALL_E_SERVICE_RIGHT_TYPE_HOT_LINE,                                 /* [98]����ҵ�� */

    /* BEGIN add: [[IR.IPT.034] [2013/12/18] [zhanglusha 00219468]]
       �޸�ԭ��: ������:������и��� */
    CALL_E_SERVICE_RIGHT_TYPE_MCID,                                    /* [99]������и��� */
    /* END   add: [[IR.IPT.034] [2013/12/18] [zhanglusha 00219468]] */

    /* BEGIN add: [[IR.IPT.013] [2013/12/26] [zhanglusha 00219468]]
       �޸�ԭ��: �����޺�ҵ��Ȩ�� */
    CALL_E_SERVICE_RIGHT_TYPE_CALL_LIMIT,                               /* [02]�����޺� */
    /* END   add: [[IR.IPT.013] [2013/12/26] [zhanglusha 00219468]] */

    CALL_E_SERVICE_RIGHT_TYPE_CALL_WAIT,                                /* [28]182���еȴ� */

    CALL_E_SERVICE_RIGHT_TYPE_VVM,                                      /* [112]���ӻ��������� */
    CALL_E_SERVICE_RIGHT_TYPE_BARGE,                                    /* ǿ��*/
    CALL_E_SERVICE_RIGHT_TYPE_LBS,                                     /* [89]LBS*/

    /* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR-0000159474] [2013/1/18] [zhanglusha 00219468]]
       �޸�ԭ��: ����������ǿ */
    CALL_E_SERVICE_RIGHT_TYPE_PRIVACY,                                 /* privacyҵ�� */
    CALL_E_SERVICE_RIGHT_TYPE_HOLD_PRIVATE,                            /* ˽�˱���ҵ�� */
    CALL_E_SERVICE_RIGHT_TYPE_BRIDGE,                                  /* bridgeҵ�� */
    CALL_E_SERVICE_RIGHT_TYPE_RESUME,                                  /* resumeҵ�� */
    /* END   add: [[eSpace 7900 V100R001C02B010] [IR-0000159474] [2013/1/18] [zhanglusha 00219468]] */
    CALL_E_SERVICE_RIGHT_TYPE_VOICE_MAIL,                                    /*[97] Message Waiting */
    /* BEGIN add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] 
       �޸�ԭ��: huntgroupҵ��Ȩ�� */
    CALL_E_SERVICE_RIGHT_TYPE_HUNTGROUP,                               /** huntgroupȨ�� */
    CALL_E_SERVICE_RIGHT_TYPE_VIRTUALVM,                               /** ������������ */
    /* END   add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] */
    CALL_E_SERVICE_RIGHT_TYPE_UC2X_VOICECONFERENCE,                    /* 50 UC2.X�������� */

#ifdef __ESPACE_7900_C03__
    CALL_E_SERVICE_RIGHT_TYPE_ONENUMBER,                                        /* һ��ͨ */
    CALL_E_SERVICE_RIGHT_TYPE_ARLERT_SILCNCE,                          /* ���羲�� */
    CALL_E_SERVICE_RIGHT_TYPE_ANONYMOUS,                               /**�������� */
    CALL_E_SERVICE_RIGHT_TYPE_MULTIPLEAPPEARANCESERVICE,               /*[103] Multiple Appearance Service*/
#endif

    CALL_E_SERVICE_RIGHT_TYPE_BUTT
} CALL_E_SERVICE_RIGHT_TYPE;

/*�����ź���ö��*/
typedef enum  enumAUDIO_CompoundVoice
{
    COMPOUND_E_NONE   = 0,  /* ���ź��� */
    COMPOUND_E_BUSY,        /* æ�� */    
    COMPOUND_E_BACK,        /* ������ */
    COMPOUND_E_DIAL,        /* ������ */
    COMPOUND_E_WAIT,        /* ������ */
    COMPOUND_E_TIP,         /* ��ʾ�� */
    COMPOUND_E_WARN,        /* ������ */
    COMPOUND_E_LEAVE,       /* �᳡�뿪�� */
    COMPOUND_E_UFWD,      /* ������ǰת���Ⲧ���� */

    COMPOUND_E_DTMF0,   /* dtmf����0 */
    COMPOUND_E_DTMF1,   /* dtmf����1 */
    COMPOUND_E_DTMF2,   /* dtmf����2 */
    COMPOUND_E_DTMF3,   /* dtmf����3 */
    COMPOUND_E_DTMF4,   /* dtmf����4 */
    COMPOUND_E_DTMF5,   /* dtmf����5 */
    COMPOUND_E_DTMF6,   /* dtmf����6 */
    COMPOUND_E_DTMF7,   /* dtmf����7 */
    COMPOUND_E_DTMF8,   /* dtmf����8 */
    COMPOUND_E_DTMF9,   /* dtmf����9 */ 
    COMPOUND_E_DTMFSTAR, /* dtmf����'*' */
    COMPOUND_E_DTMFJIN,  /* dtmf����'#' */
    COMPOUND_E_DTMFA,    /* dtmf����A */
    COMPOUND_E_DTMFB,    /* dtmf����B */
    COMPOUND_E_DTMFC,    /* dtmf����C */
    COMPOUND_E_DTMFD,    /* dtmf����D */
    COMPOUND_E_DTMFFLASH, /* dtmf����FLASH */
    COMPOUND_E_BUTT
}AUDIO_E_COMPOUNT_VOICE;

/** CALL_E_MSG_SET_AUDIOCAP Minor */
typedef enum tagCALL_E_AUDIO_CAP
{
    CALL_E_AUDIO_CAP_AACLD = 0,
    CALL_E_AUDIO_CAP_G722,
    CALL_E_AUDIO_CAP_G7221,
    CALL_E_AUDIO_CAP_G7222,
    CALL_E_AUDIO_CAP_G711A,
    CALL_E_AUDIO_CAP_G711U,
    CALL_E_AUDIO_CAP_G729AB,
    CALL_E_AUDIO_CAP_G726,
    CALL_E_AUDIO_CAP_ILBC,
    CALL_E_AUDIO_CAP_OPUS,
    CALL_E_AUDIO_CAP_DTMF,
    CALL_E_AUDIO_CAP_BUTT
}CALL_E_AUDIO_CAP;


/** CALL_E_MSG_SET_VIDEOCAP Minor */

/** ֧�ֵ���ƵЭ������ */
typedef enum tagCALL_E_VIDEO_CAP
{
    CALL_E_VIDEO_CAP_H264 = 0,
    CALL_E_VIDEO_CAP_H263, 
    CALL_E_VIDEO_CAP_BUTT
}CALL_E_VIDEO_CAP;



/** DTMF ����ģʽ */
typedef enum
{
    CALL_E_DTMF_MODE_TRANSPARENT = 0,        /**< ͸��ģʽ */
    CALL_E_DTMF_MODE_RFC2833,            /**< RFC2833ģʽ(�Զ�Э��) */
    CALL_E_DTMF_MODE_CONST2833,          /**< ǿ��2833ģʽ */
    CALL_E_DTMF_MODE_INFO,               /**< INFOģʽ */    
    CALL_E_DTMF_MODE_BUTT
}CALL_E_DTMF_MODE;




typedef enum tagCALL_E_NET_EVT_TYPE
{
    CALL_E_NET_EVENT_CONNECTED,
    CALL_E_NET_EVENT_CONNECTFAIL,    
    CALL_E_NET_EVENT_LINKUP,        
    CALL_E_NET_EVENT_LINKDOWN,    

    CALL_E_NET_EVENT_BUTT

}CALL_E_NET_EVT_TYPE;


typedef enum tagCALL_E_PRODUCT_TYPE
{
    CALL_E_PRODUCT_TYPE_PHONE = 0,
    CALL_E_PRODUCT_TYPE_PC,
    CALL_E_PRODUCT_TYPE_MOBILE,
    CALL_E_PRODUCT_TYPE_BUTT
}CALL_E_PRODUCT_TYPE;

/*neet combind to one*/

/**��Ƶ�����������*/
typedef enum
{
    CALL_E_AO_DEV_SPEAKER = 0,       /**< ������ */
    CALL_E_AO_DEV_BLUETOOTH,         /**< ������� */
    CALL_E_AO_DEV_EARPIECE,  /**< �ֱ���� */
    CALL_E_AO_DEV_HEADSET,           /**< 3.5mm������� */
    CALL_E_AO_DEV_HDMI,           /**< HDMI��� */
    CALL_E_AO_DEV_USB,               /**< USB��� */
    //MPROC_E_AO_DEV_HEADSET,         /**< ������� */
    CALL_E_AO_DEV_SPEAKERRING,       /**< ����������(��ȡ����ֵʱ���õ�) */
    CALL_E_AO_DEV_BLUETOOTHRING,     /**< �����������(��ȡ����ֵʱ���õ�) */
    CALL_E_AO_DEV_HDMIRING,           /**< �ֱ���� */
    CALL_E_AO_DEV_USBRING,           /**< USB�������(��ȡ����ֵʱ���õ�) */
    CALL_E_AO_DEV_BUTT               /**< ��Чֵ */
} CALL_E_AO_DEV;


//��Ƶ·��ͬ��TUP ENUM_TUP_AUDDEV_ROUTE
typedef enum tagCALL_E_AUDDEV_ROUTE
{
    CALL_E_AUD_DEV_ROUTE_DEFAULT         = 0x0,                    //����ֵ�����ò���Ч
    CALL_E_AUD_DEV_ROUTE_LOUDSPEAKER     = 0x1,                    //������ ��֧���������
    CALL_E_AUD_DEV_ROUTE_BLUETOOTH       = 0x2,                    //�������� ��֧���������
    CALL_E_AUD_DEV_ROUTE_EARPIECE        = 0x3,                    //��Ͳ �ֱ��豸��֧���������
    CALL_E_AUD_DEV_ROUTE_HEADSET         = 0x4,                    //3.5���׶��� ��֧���������
    CALL_E_AUD_DEV_ROUTE_SUBDEFAULT      = 0x5,                    //����ֵ�����ò���Ч
    CALL_E_AUD_DEV_ROUTE_HDMI            = 0x6,                    //HDMI,֧�����
    CALL_E_AUD_DEV_ROUTE_USB             = 0x7,                    //USB���� ��֧���������
    CALL_E_AUD_DEV_ROUTE_MAX             = 0X8                     //��Чֵ
} CALL_E_AUDDEV_ROUTE;

typedef enum tagCALL_E_REG_FAILOVER_MODE{
    CALL_E_REG_FAILOVER_MODE_REGMASTER,        /**< ��-> �� */
    CALL_E_REG_FAILOVER_MODE_REGALL,        /**< ������ͬʱ */
    CALL_E_REG_FAILOVER_MODE_BUTT
}CALL_E_REG_FAILOVER_MODE;


/** ��������, ��Ҫ��cmo_enum.h�е�HCS_E_SIP_NETWORK_MODE���屣��һ�� */
typedef enum tagCALL_E_NET_ENVIRONMENT
{
    CALL_E_NET_UC1X = 0,        /** UC1.0����*/
    CALL_E_NET_UC2X,            /** UC2.0����*/
    CALL_E_NET_OTHERS,          /** ���������������ϰ汾��Ϊ2 */
    CALL_E_NET_ASTERISK,        /** Asterisk����*/
    CALL_E_NET_BROADSOFT,       /** Broadsoft����*/
    CALL_E_NET_IPCC,            /** IPCC����  */
    CALL_E_NET_IMSUC_MIX,       /** IMS+UC */
    CALL_E_NET_TE,              /* ���� */
    CALL_E_NETWORK_HUAWEIUC,    /*Only for  soft terminal who register on CallAS now*/
    CALL_E_NET_BUTT
} CALL_E_NET_ENVIRONMENT;



typedef enum tagCALL_E_IP_PROTOCOL_TYPE
{
    CALL_E_IP_V4 = 0,
    CALL_E_IP_V6,
}CALL_E_IP_PROTOCOL_TYPE;



typedef enum
{
    CALL_E_SEVICERIGHT_LACK = 0,        /* ûȨ�� */
    CALL_E_SEVICERIGHT_HAVE         /* ��Ȩ�� */
} CALL_E_SEVICERIGHT_STATUS;

typedef enum
{
    CALL_E_SERVERCONF_AUDIO = 1,        /* �᳡���ͣ����� */
    CALL_E_SERVERCONF_DATA  = 3         /* �᳡���ͣ�����+���� */
} CALL_E_SERVERCONF_TYPE;


typedef enum tagCALL_E_REFRESHVIEW_MIDEATYPE
{
    CALL_E_REFRESHVIEW_VIDEO = 2,     /**��ͨ��Ƶ */
    CALL_E_REFRESHVIEW_DATA = 3   /**���� */
} CALL_E_REFRESHVIEW_MIDEATYPE;


typedef enum tagCALL_E_REFRESHVIEW_EVENT
{
    CALL_E_LOCALVIEW_ADD = 1,     /**����view��� */
    CALL_E_LOCALVIEW_REMOVE   /**����viewɾ�� */
} CALL_E_REFRESHVIEW_EVENT;

/* ����URI��������:��ͨ����,intercom,paging,����SIP_E_URI_PARAMTYPE��Ӧ */
typedef enum tagCALL_E_URI_PARAMTYPE
{
    CALL_E_URI_PARAM_NORAML,     /** ��Я������ */
    CALL_E_URI_PARAM_INTERCOM,   /** intercom=true */
    CALL_E_URI_PARAM_PAGING,     /** paging=true */
    CALL_E_URI_PARAM_APPEARANCE_PRIVATE, /** appearance-private=true */
    CALL_E_URI_PARAM_BUTT
}CALL_E_URI_PARAMTYPE;


typedef enum tagCALL_E_VIDEOWND_TYPE
{
    CALL_E_VIDEOWND_CALLREMOTE = 0,                  /* ͨ��Զ�˴��� */
    CALL_E_VIDEOWND_CALLLOCAL,                  /* ͨ�����ش���  */
    CALL_E_VIDEOWND_PREVIEW,
    CALL_E_VIDEOWND_BUTT
} CALL_E_VIDEOWND_TYPE;

typedef enum tagCALL_E_COORDINATE_TYPE
{
    CALL_E_COORDINATE_X = 0,
    CALL_E_COORDINATE_Y,
    CALL_E_COORDINATE_W,
    CALL_E_COORDINATE_H,
    CALL_E_COORDINATE_Z,
    CALL_E_COORDINATE_BUTT
} CALL_E_COORDINATE_TYPE;

typedef enum tagCALL_E_VIDEOWND_DISPLAY_TYPE
{
    CALL_E_VIDEOWND_DISPLAY_ZOOM = 0,             /* 0:���ֱ�������,�Ӻڱ�,Ĭ��Ϊ��ֵ */
    CALL_E_VIDEOWND_DISPLAY_CUT,                  /* 1:���ֱ�������,����ü�   */
    CALL_E_VIDEOWND_DISPLAY_FULL,                 /* 2:ȫ������,���Ӻڱߣ������ü�   */
    CALL_E_VIDEOWND_DISPLAY_BUTT
} CALL_E_VIDEOWND_DISPLAY_TYPE;


/*******************************************************************************
 *   ���ݽṹ���ͺ����������Ͷ���
 *******************************************************************************/
/** װ������*/
typedef struct tagMPROC_S_AUDIO_EQPTTEST
{
    TUP_UINT32 ulVolume;
    TUP_UINT32 ulSampleFreq;
    TUP_UINT32 ulBitWide;
    TUP_UINT32 em7950AMPType;
} MPROC_S_AUDIO_EQPTTEST;

/*register result*/
typedef struct tagCALL_S_SIP_ACCOUNT_INFO
{
    TUP_UINT32 ulSipAccountID;                  /**< SIP�˻�ID */
    CALL_E_REG_STATE enRegState;                /**< SIP�˻�ע��״̬ */
    TUP_UINT32 ulReasonCode;                    /**< ע��ʧ�ܵ�ԭ���� */
    TUP_INT8 acUserNum[CALL_D_MAX_USERNAME_LENGTH];   /**< SIP�˻��û��� */
    TUP_INT8 acTelNum[CALL_D_MAX_LENGTH_NUM];   /**< SIP�˻����� */
} CALL_S_SIP_ACCOUNT_INFO;

typedef struct tagCALL_S_CALL_PARAMS
{
    TUP_UINT32 ulLineId;
    TUP_UINT32 ulCallType;
    TUP_UINT32 ulAccountId;
    TUP_UINT32 ulReserved;
    TUP_UINT32 ulCallId; //���������������
    TUP_INT8 acTelNum1[CALL_D_MAX_LENGTH_NUM];
    TUP_INT8 acTelNum2[CALL_D_MAX_LENGTH_NUM];
    TUP_VOID* pReserved;
}CALL_S_CALL_PARAMS;

typedef struct tagCALL_S_CALL_STATE_INFO
{
    TUP_UINT32 ulSipAccountID;              /**< ͨ��������·ID */
    TUP_UINT32 ulCallID;                    /**< ͨ��ID */
    CALL_E_CALL_TYPE enCallType;            /**< �������� */
    CALL_E_CALL_STATE enCallState;          /**< ͨ��״̬ */
    TUP_INT8 acTelNum[CALL_D_MAX_LENGTH_NUM];   /**<  ������� */
    TUP_INT8 acDisplayName[CALL_D_MAX_DISPLAY_NAME];  /**< �������� */
    TUP_UINT32 ulReasonCode;       /**< ʧ��ԭ���� endcall */ 
    TUP_BOOL bIsIn;                         /**< ��ʶ��·ͨ���Ƿ�Ϊ���� */
    TUP_BOOL bIsPassiveEnd;                 /**< ��ʶ��·�����Ƿ�Զ�˹Ҷ� */
    CALL_E_CALL_ALERTTYPE enAlertType;        /** �����������ͣ�add by w00213797 */
    TUP_BOOL bIsAccept;                     /**< �����Ƿ��Ѿ�������־ */
    TUP_BOOL bIsTimeout;                    /**< ���г�ʱ��־��������¼���糬ʱδ�Ӽ�¼ */
    TUP_BOOL bIsInLocalConf;                /**< ��־�Ƿ���뱾�ػ��� add by h00206999*/
    TUP_BOOL bIsInBridgeConf;               /**< ��ʶ�Ƿ��ǽ���bridge����״̬ */
    TUP_BOOL bCompletedElsewhere;               /**< ��ʶ�Ƿ��ǲ��ü���δ������ı��������� */
    TUP_BOOL bIsAutoAnswer;                /**������ �����Ƿ��Զ�������־  ��add by w00213797  */
    TUP_UINT32 ulAutoAnswerTime;            /** �����������Զ�����ʱ�䣬add by w00213797 */
    TUP_UINT32 ulCause;           /* sip����cause�� */
    TUP_CHAR szPresetMsg[CALL_D_MAX_PRESET_MSG_LENGTH];              /**< Ԥ����Ϣ */
    TUP_BOOL bIsPaging;
    TUP_BOOL bHaveSDP;            /* �Ƿ����SDP */
}CALL_S_CALL_STATE_INFO;



typedef struct tagCALL_S_CALL_INFO
{
    CALL_S_CALL_STATE_INFO stCallStateInfo;     /**< ͨ��״̬��Ϣ */

    /* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/1/26] [zhanglusha 00219468]]
       �޸�ԭ��: intercomҵ�� */
    CALL_E_URI_PARAMTYPE enUriType;   
    /* END   add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/1/26] [zhanglusha 00219468]] */
    TUP_BOOL bIsFwdCallForbidden;             /**< ������ָʾ��ֹ����ǰ��,���ڶԽ�BROADSOFT������*/
    TUP_BOOL bIsFwdCall;
    TUP_INT8 acFwdFromNum[CALL_D_MAX_LENGTH_NUM];  /**<ǰת�ߺ��� */
    TUP_INT8 acFwdFromName[CALL_D_MAX_DISPLAY_NAME];  /**< ǰת������ */

    /*Ϊƥ��ɳ��ATS���������ں�����ʾ������PAI�еĵڶ���URI��Ĭ��ΪTEL�� */
    TUP_INT8 acTelNumTel[CALL_D_MAX_LENGTH_NUM];   /**<  ������� */
    TUP_INT8 acDisplayNameTel[CALL_D_MAX_LENGTH_NUM];  /**< �������� */
    /*Ϊƥ��ɳ��ATS���������ں�����ʾ������PAI�еĵڶ���URI��Ĭ��ΪTEL�� */

    /*others*/
    TUP_BOOL bIsShareLine;
    TUP_UINT32 ulSCALineID;
    TUP_UINT32 ulBossLineID;
    TUP_BOOL   bIsReplace;                        /**< �Ƿ��滻��· */
    TUP_UINT32 ulReplaceID;                     /**<��ѯת���� �滻��ԭ����ID */
    TUP_CHAR acBossNum[CALL_D_MAX_LENGTH_NUM];
    TUP_UINT32 ulRmtCtrl;                        /* �Ƿ�Զ˿� */
    TUP_UINT32 ulSwitchId;                      /**PC����һ���л�*/

    TUP_BOOL bIsFocus;            /**�Ƿ��isfoucs��ʶ���ƶ����鳡��ʹ��*/  
    TUP_INT8 acServerConfType[CALL_D_MAX_LENGTH_NUM];       /**�������ͣ��ƶ����鳡��ʹ��*/  
    TUP_INT8 acServerConfID[CALL_D_MAX_LENGTH_NUM];      /**����ID, �ƶ����鳡��ʹ��*/
    TUP_UINT32 ulOrientType;    /** �ƶ���Ƶ���������*/
    TUP_INT8 acLocalAddr[CALL_D_IP_LENGTH];   /**�ƶ��ϱ����ص�ַ*/
    TUP_INT8 acRemoteAddr[CALL_D_IP_LENGTH];    /**�ƶ��ϱ�Զ�˵�ַ*/
} CALL_S_CALL_INFO;

/*voice mail notify,*/
typedef struct tagCALL_S_MSG_INFO
{
    CALL_E_MSG_WAIT_TYPE enMsgType;     /**< ���Ե����� */
    TUP_UINT32 ulNewMsgNum;             /**< ����Ϣ���� */
    TUP_UINT32 ulOldMsgNum;             /**< ����Ϣ���� */
    TUP_UINT32 ulNewEmgMsgNum;          /**< �½�����Ϣ���� */
    TUP_UINT32 ulOldEmgMsgNum;          /**< �ɽ�����Ϣ���� */
    TUP_CHAR   aszSubscriber[CALL_D_MAX_LENGTH_NUM];               /**< �����ĺ��� */
} CALL_S_MSG_INFO;

typedef struct tagCALL_S_MSG_WAIT_INFOS
{
    TUP_UINT32 ulMsgCnt;                /**< ��Ϣ���͸��� */
    CALL_S_MSG_INFO astMsgInfos[CALL_D_MAX_MSGSUMMARY_NUM];        /**< ��Ϣ���� */
} CALL_S_MSG_WAIT_INFOS;



typedef struct _CALL_CHANNEL_EMODEL_RESULT_STRU
{
    TUP_UINT8  ucSendMOSValidFlag;   /**< ���ͷ���MOS����Ч��־,��ͨ��δ�յ�RTCP RR����ʱ������4�����ͷ����MOS�ֲ�������Ч */
    TUP_UINT8  ucRecvMOSValidFlag;   /**< ���շ���MOS����Ч��־,��ͨ��δ�յ��κα��Ļ�δ�ﵽ��������(RTCP�������ڣ�5s)ʱ������4�����շ����MOS�ֲ�������Ч */
    TUP_UINT16 uwResv;               /**< ����λ����֤4�ֽڶ��� */

    TUP_UINT32 ulSendAverageMosQ;    /**< ���ͷ���MOS��ƽ��ֵ,��������ʾ:4000����4.000��ȡֵ��Χ[1000, 5000], 0xFFFFFFFF��ʾ�ò�����Ч */
    TUP_UINT32 ulSendMaxMosQ;        /**< ���ͷ���MOS�����ֵ,��������ʾ:4000����4.000��ȡֵ��Χ[1000, 5000], 0xFFFFFFFF��ʾ�ò�����Ч */
    TUP_UINT32 ulSendMinMosQ;        /**< ���ͷ���MOS����Сֵ,��������ʾ:4000����4.000��ȡֵ��Χ[1000, 5000], 0xFFFFFFFF��ʾ�ò�����Ч */
    TUP_UINT32 ulSendCurMosQ;        /**< ���ͷ���MOS�ֵ�ǰֵ,��������ʾ:4000����4.000��ȡֵ��Χ[1000, 5000], 0xFFFFFFFF��ʾ�ò�����Ч */

    TUP_UINT32 ulRecvAverageMosQ;    /**< ���շ���MOS��ƽ��ֵ,��������ʾ:4000����4.000��ȡֵ��Χ[1000, 5000], 0xFFFFFFFF��ʾ�ò�����Ч */
    TUP_UINT32 ulRecvMaxMosQ;        /**< ���շ���MOS�����ֵ,��������ʾ:4000����4.000��ȡֵ��Χ[1000, 5000], 0xFFFFFFFF��ʾ�ò�����Ч */
    TUP_UINT32 ulRecvMinMosQ;        /**< ���շ���MOS����Сֵ,��������ʾ:4000����4.000��ȡֵ��Χ[1000, 5000], 0xFFFFFFFF��ʾ�ò�����Ч */
    TUP_UINT32 ulRecvCurMosQ;        /**< ���շ���MOS�ֵ�ǰֵ,��������ʾ:4000����4.000��ȡֵ��Χ[1000, 5000], 0xFFFFFFFF��ʾ�ò�����Ч */
} CALL_CHANNEL_EMODEL_RESULT_STRU;

typedef struct tagCALL_S_AUDIO_STREAM_INFO
{
    TUP_BOOL bIsCalling;                        /**< �Ƿ���ͨ����*/
    TUP_INT8 acEncodeProtocol[CALL_D_PROTOCOL_LENGTH];               /**< ����Э��*/
    TUP_INT8 acDecodeProtocol[CALL_D_PROTOCOL_LENGTH];               /**< ����Э��*/
    TUP_UINT32 ulChannelID;                     /**< ͨ��ID */
    TUP_UINT32 ulSendBitRate;                   /**< ���ͱ����� */
    TUP_UINT32 ulRecvBitRate;                   /**< ���ձ����� */
    TUP_UINT32 ulSendTotalLostPacket;           /**< ���ͷ��ۼư��� */
    TUP_FLOAT fSendLossFraction;                /**< ���ͷ�������(%) */
    TUP_FLOAT fSendJitter;                      /**< ���ͷ�ƽ������(ms) */
    TUP_FLOAT fSendDelay;                       /**< ���ͷ�ƽ��ʱ��(ms) */
    TUP_UINT32 ulRecvTotalLostPacket;           /**< ���շ��ۼư��� */
    TUP_FLOAT fRecvLossFraction;                /**< ���շ�������(%) */
    TUP_FLOAT fRecvJitter;                      /**< ���շ�ƽ������(ms) */
    TUP_FLOAT fRecvDelay;                       /**< ���շ�ƽ��ʱ��(ms) */
    CALL_CHANNEL_EMODEL_RESULT_STRU stMosResult; /**< ����mosֵ */
    //del by chendk
    //HME_CHANNEL_EMODEL_RESULT_STRU  stMosResult;/**< ����mosֵ */
} CALL_S_AUDIO_STREAM_INFO, *CALL_S_AUDIO_STREAM_INFO_PTR;

typedef struct tagCALL_S_VIDEO_STREAM_INFO
{
    TUP_INT8 acEncodeName[CALL_MAX_CODEC_NAME_LEN];        /**< ��������*/
    TUP_INT8 acDecodeName[CALL_MAX_CODEC_NAME_LEN];        /**< ��������*/
    TUP_INT8 acEncoderSize[CALL_MAX_FRAMESIZE_LEN];        /**< ͼ��ֱ���(����)*/
    TUP_INT8 acDecoderSize[CALL_MAX_FRAMESIZE_LEN];        /**< ͼ��ֱ���(����)*/
    TUP_UINT32 ulSendFrameRate;                            /**< ��Ƶ֡��(����)*/
    TUP_UINT32 ulRecvFrameRate;                            /**< ��Ƶ֡��(����)*/
    TUP_UINT32 ulVideoSendBitRate;                        /**< ��������*/
    TUP_UINT32 ulVideoRecvBitRate;                        /**< ��������*/
    TUP_INT8 acEncoderProfile[CALL_MAX_PROFILE_LEN];        /**< ��Ƶ�����ʽ*/
    TUP_INT8 acDecoderProfile[CALL_MAX_PROFILE_LEN];        /**< ��Ƶ�����ʽ*/
    TUP_FLOAT fVideoSendLossFraction;                    /**< ���ͷ�������(%) */
    TUP_FLOAT fVideoSendJitter;                          /**< ���ͷ�ƽ������(ms) */
    TUP_FLOAT fVideoSendDelay;                           /**< ���ͷ�ƽ��ʱ��(ms) */
    TUP_FLOAT fVideoRecvLossFraction;                    /**< ���շ�������(%) */
    TUP_FLOAT fVideoRecvJitter;                          /**< ���շ�ƽ������(ms) */
    TUP_FLOAT fVideoRecvDelay;                           /**< ���շ�ƽ��ʱ��(ms) */
    TUP_UINT32 ulWidth;                                    /**< ��Ƶ�ֱ���-��*/
    TUP_UINT32 ulHeight;                                   /**< ��Ƶ�ֱ���-��*/
} CALL_S_VIDEO_STREAM_INFO, *CALL_S_VIDEO_STREAM_INFO_PTR;

//�Ự��ý������Ϣ
typedef struct tagCALL_S_MEDIA_STREAM_INFO
{
    TUP_UINT32 uiCt; //�Ự������ ct
    TUP_CHAR   szAudioCodec[CALL_D_MAX_CODEC_LIST_LEN+1]; /*�ỰЭ�̳�����֧�ֵ���Ƶ������б� "G722,PCMA,PCMU,G729,iLBC,telephone-event,red"*/
    TUP_CHAR   szVideoCodec[CALL_D_MAX_CODEC_LIST_LEN+1]; /*�ỰЭ�̳�����֧�ֵ���Ƶ������б� Ԥ��*/
}CALL_S_MEDIA_STREAM_INFO, *CALL_S_MEDIA_STREAM_INFO_PTR;

typedef struct tagCALL_S_STREAM_INFO
{
    CALL_S_MEDIA_STREAM_INFO stMediaStreamInfo;         /*�Ự����Ϣ*/
    CALL_S_AUDIO_STREAM_INFO stAudioStreamInfo;         /*��Ƶ����Ϣ*/
    CALL_S_VIDEO_STREAM_INFO stVideoStreamInfo;         /*��Ƶ����Ϣ*/
    TUP_BOOL bIsIn;                                     /**< ��ʶ��·ͨ���Ƿ�Ϊ���� */
    TUP_BOOL bIsEndCall;                          /**< ��ʶ�Ƿ�Ϊ�����ϱ� */
    TUP_CHAR acLocalIP[CALL_D_IP_LENGTH];               /*����IP*/
    TUP_CHAR acRemoteNum[CALL_D_MAX_LENGTH_NUM];        /*Զ�˺���*/
    TUP_CHAR acLocalNum[CALL_D_MAX_LENGTH_NUM];         /*���˺���*/
} CALL_S_STREAM_INFO, *CALL_S_STREAM_INFO_PTR;

#define TUP_CONF_VALID_CONFID_BEG (1)


typedef struct tagCALL_S_SCA_CALL_INFO
{
    TUP_BOOL bIsShareLine;
    TUP_UINT32 ulSCALineID;
    TUP_UINT32 ulBossLineID;
    TUP_CHAR acBossNum[CALL_D_MAX_LENGTH_NUM];
} CALL_S_SCA_CALL_INFO;


typedef struct tagCALL_S_CONF_INFO
{
    TUP_UINT32 ulConfID;//���鱾�ؿ���id                
    CALL_E_SERVERCONF_TYPE eConfType;  //�������᳡����
    TUP_UINT32 ulCallID;
    TUP_UINT32 ulSipAccountID;  
    TUP_INT8 acUserNumber[CALL_D_MAX_LENGTH_NUM];
    TUP_INT8 acGroupUri[CALL_D_MAX_LENGTH_NUM];
    
    /** �������Ƿ�ָʾ�Զ����� add by k00175673 */
    TUP_UINT32 ulSvrAutoAnswer;          
    /** ������ָʾ�Զ�����ʱ�� add by k00175673 **/
    TUP_UINT32 ulSvrAutoAnswerTime;
    CALL_S_SCA_CALL_INFO stScaCallInfo; /* �����ڻ��������ʱ���ϱ�����������Ϣ */
} CALL_S_CONF_INFO;

//zhubin 202161 �᳡�������
typedef struct tagCALL_S_CONF_CREATE_RESULT
{
    TUP_UINT32 ulConfID;//���鱾�ؿ���id
    TUP_UINT32 ulResult;//������
    CALL_E_SERVERCONF_TYPE eConfType;//�������᳡����
    TUP_CHAR acPasscode[CALL_D_PASSCODE_LENGTH];
} CALL_S_CONF_CREATE_RESULT;

//zhubin 202161 ���ݻ��������ز���
typedef struct tagCALL_S_DATACONF_PARAM
{
    TUP_UINT32          ulConfID;/**<���鱾�ؿ���id*/
    TUP_UINT32          ulCallID;/* ��Ӧ��CallID */
    CALL_E_CONF_ROLE    enRole;  /**<�����û������н�ɫ*/
    TUP_CHAR            acDataConfID[CALL_D_DATACONF_PARAM_LENGTH];/**<�������᳡id*/
    TUP_CHAR            acAuthKey[CALL_D_DATACONF_PARAM_LENGTH]; /**<�᳡��Ȩ��*/
    TUP_CHAR            acPassCode[CALL_D_MAX_LENGTH_NUM];
    TUP_CHAR            acCmAddr[CALL_D_DATACONF_CMADDR_LENGTH];/**<U19���ܵ�ַ���˿�*/
    TUP_CHAR            acGroupUri[CALL_D_MAX_LENGTH_NUM];
    TUP_CHAR            acCharman[CALL_D_DATACONF_PARAM_LENGTH];         /**< ������UC����*/
    TUP_CHAR            bP2PDataConf;   /* �Ƿ��Ե����ݻ��� */
} CALL_S_DATACONF_PARAM;

/* �������Ϣ */
typedef struct tagCALL_S_CONF_MEMBER
{
    TUP_CHAR acAttendeeNumber[CALL_D_MAX_LENGTH_NUM];   /* ���� */
    TUP_CHAR acAttendeeFullNumber[CALL_D_MAX_LENGTH_NUM];   /*����߳� ���� */
    CALL_E_CONF_ROLE enRole;                             /* ��ɫ */
    CALL_E_CONF_ATTENDEE_STATE enState;                  /* ״̬ */
    TUP_UINT32 ulRight;                                  /* ����Ȩ  1��  0��  */
    TUP_UINT32 ulAttendeeID;                             /* �����ID , ����ָ��ʹ���ĸ����飬89 C50C00����ʱ��ʹ��*/
} CALL_S_CONF_MEMBER;

/* ���������Ϣ */
typedef struct tagCALL_S_CONF_SPEAKER
{
    TUP_CHAR acFirstSpeakMem[CALL_D_MAX_LENGTH_NUM];  /* ���� */
    TUP_CHAR acSecondSpeakMem[CALL_D_MAX_LENGTH_NUM];     /*����߳� ���� */
} CALL_S_CONF_SPEAKER;


typedef struct tagCALL_S_MODIFY_VIDEO_RESULT
{
    TUP_UINT32 ulCallID;
    TUP_UINT32 ulResult;
    TUP_BOOL  bIsVideo;
    TUP_UINT32 ulOrientType;
}CALL_S_MODIFY_VIDEO_RESULT;


typedef struct tagCALL_S_VIDEOWND_INFO
{
    TUP_UINT32 ulVideoWndType;            /*CALL_E_VIDEOWND_TYPE*/
    TUP_INT32 ucCoordinate[CALL_E_COORDINATE_BUTT];/**X1,Y1,w,h,Z*/
    TUP_UINT32 ulRender;                 /*���ھ��*/
    TUP_INT32 ulIndex;                   /*�������*/
    TUP_UINT32 ulSessionID;             /*����Ԥ��sessionֵ*/
    TUP_UINT32 ulRefCount;              /*ʹ�����ü���*/
    TUP_UINT32 ulDisplayType;           /*��ʾģʽCALL_E_VIDEOWND_DISPLAY_TYPE*/
    TUP_CHAR  acStartImage[CALL_D_MAX_LENGTH_NUM]; /*��Ƶ��ʾ��ʼͼ�񣬱���Ϊjpegͼ���ҳ�����8�ı���*/
} CALL_S_VIDEOWND_INFO, CALL_S_VIDEOCONFWND_INFO;



typedef enum tagCALL_E_VIDEOWND_CTRL_TYPE
{
    CALL_E_VIDEOWND_MOVE,                  /* �����ƶ�����Z��ı�����ͨ���ı�Z�� */
    CALL_E_VIDEOWND_CLOSE,              /* ���ڹر�  */
    CALL_E_VIDEOWND_ZOOM,               /* ��������  */
    CALL_E_VIDEOWND_DISPLAYTYPE,         /*��ʾģʽ  */
    CALL_E_VIDEOWND_CTRL_BUTT
} CALL_E_VIDEOWND_CTRL_TYPE;


/**CFG:MAJOR_TYPE
In the future, maybe need support multi-account, we can use the first 16bit as account
,use the second 16bit as major type.

*/
typedef enum tagCALL_E_CFG_MAJOR_TYPE
{
    CALL_E_CFG_CALLENV = 1, /*��������*/
    CALL_E_CFG_SERVER,      /*��������ַ*/
    CALL_E_CFG_NET,         /*��������ӿڵ�ַ*/
    CALL_E_CFG_USERAGENT,
    CALL_E_CFG_SERVRIGHT,   /*ҵ��Ȩ��*/
    CALL_E_CFG_DSCP,        /*DSCP*/    
    CALL_E_CFG_SIP,         /*SIP��������*/
    CALL_E_CFG_ACCOUNT,
    CALL_E_CFG_COMPATIBLE_PARAM,
    CALL_E_CFG_CONF,        /*�����������*/
    CALL_E_CFG_MEDIA,       /* ý��ȫ������*/
    CALL_E_CFG_AUDIO,       /*��Ƶ����*/
    CALL_E_CFG_VIDEO,       /*��Ƶ����*/
    CALL_E_CFG_DATA,        /*��������*/
    CALL_E_CFG_MOBILE_VOICEMAIL,   /*�ƶ���������Ȩ��*/
    CALL_E_CFG_BUTT
}CALL_E_CFG_MAJOR_TYPE;



typedef enum tagCALL_E_CFG_DATA_TYPE
{
    CALL_E_CFG_DATA_TYPE_INT = 0x01,     
    CALL_E_CFG_DATA_TYPE_STRING = 0x02,             
    CALL_E_CFG_DATA_TYPE_STRUCTURE = 0x04,   
    CALL_E_CFG_DATA_TYPE_BOOL = 0x08,
    CALL_E_CFG_DATA_TYPE_BUTT,

} CALL_E_CFG_DATA_TYPE;

/*index can be used as multi instance,such as account */
#define CFG_ID_DEF(major,data_type,id,index)    ((major)<<24|((data_type) << 16)|(id) <<8|(index))

#define GET_CFG_DATA_TYPE(cfgid)            ((cfgid>>16)&0x000000FF)
#define GET_CFG_MAJOR_TYPE(cfgid)           ((cfgid>>24)&0x000000FF)
#define GET_CFG_INDEX(cfgid)                ((cfgid)&0x000000FF)
#define GET_CFG_ID(cfgid)                   ((cfgid>>8)&0x000000FF)


/* ������ط��������� */
#define CALL_D_CFG_SERVER_REG_PRIMARY     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x01,0)
#define CALL_D_CFG_SERVER_REG_BACKUP1     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x02,0)
#define CALL_D_CFG_SERVER_REG_BACKUP2     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x03,0)
#define CALL_D_CFG_SERVER_REG_BACKUP3     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x04,0)
#define CALL_D_CFG_SERVER_REG_LOCAL       CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x05,0)
#define CALL_D_CFG_SERVER_PROXY_PRIMARY   CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x11,0)
#define CALL_D_CFG_SERVER_PROXY_BACKUP1   CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x12,0)    
#define CALL_D_CFG_SERVER_PROXY_BACKUP2   CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x13,0)  
#define CALL_D_CFG_SERVER_PROXY_BACKUP3   CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x14,0)
#define CALL_D_CFG_SERVER_PROXY_LOCAL     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x15,0) 
#define CALL_D_CFG_SERVER_UMS_PRIMARY     CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x21,0)
#define CALL_D_CFG_SERVER_UMS_BACKUP      CFG_ID_DEF(CALL_E_CFG_SERVER,CALL_E_CFG_DATA_TYPE_STRUCTURE,0x22,0)

/* ������������ */
#define CALL_D_CFG_ENV_SOLUTION                  CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_INT,0x01,0) 
#define CALL_D_CFG_ENV_DISASTER_RECOVERY_MODE    CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_INT,0x02,0)
#define CALL_D_CFG_ENV_PRODUCT_TYPE              CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_INT,0x03,0) 
#define CALL_D_CFG_ENV_USEAGENT                  CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_STRING,0x04,0)  

/* ҵ��������� */
#define CALL_D_CFG_SERVRIGHT_DND        CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_DONOTDISTURB,0)
#define CALL_D_CFG_SERVRIGHT_CFU        CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_UNCONDITIONAL,0)  
#define CALL_D_CFG_SERVRIGHT_CFB        CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_ONBUSY,0)
#define CALL_D_CFG_SERVRIGHT_CFNR       CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_OFFLINE,0)
#define CALL_D_CFG_SERVRIGHT_CFNA       CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_NOREPLY,0)
#define CALL_D_CFG_SERVRIGHT_CALLWAIT   CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALL_WAIT,0)

/* DSCP������� */
#define CALL_D_CFG_DSCP_ENABLE   CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_BOOL,0x1,0)
#define CALL_D_CFG_DSCP_AUDIO    CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_INT,0x2,0)
#define CALL_D_CFG_DSCP_VIDEO    CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_INT,0x3,0)
#define CALL_D_CFG_DSCP_SIP      CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_INT,0x4,0)

/* ����������� */
#define CALL_E_CFG_CONF_ENABLE_INTERCONF            CFG_ID_DEF(CALL_E_CFG_CONF, CALL_E_CFG_DATA_TYPE_BOOL, 0x1, 0)
#define CALL_E_CFG_CONF_MS_ADDR                     CFG_ID_DEF(CALL_E_CFG_CONF, CALL_E_CFG_DATA_TYPE_STRING, 0x4, 0)
#define CALL_E_CFG_CONF_APPAGENT_ADDR               CFG_ID_DEF(CALL_E_CFG_CONF, CALL_E_CFG_DATA_TYPE_STRING, 0x5, 0)
#define CALL_D_CFG_COMPATIBLE_PARAM_SELFNUM         CFG_ID_DEF(CALL_E_CFG_COMPATIBLE_PARAM,CALL_E_CFG_DATA_TYPE_STRING,0x2,0)/* ���ñ��˺��� */
#define CALL_D_CFG_COMPATIBLE_PARAM_OUTGOINGCODE    CFG_ID_DEF(CALL_E_CFG_COMPATIBLE_PARAM,CALL_E_CFG_DATA_TYPE_STRING,0x3,0)/* ����OUTGOING�� */ 

/* sip������� */
#define CALL_D_CFG_SIP_PORT                 CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x1, 0)
#define CALL_D_CFG_SIP_REGIST_TIMEOUT       CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x2, 0)
#define CALL_D_CFG_SIP_SUBSCRIBE_TIMEOUT    CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x3, 0)
#define CALL_D_CFG_SIP_REREGISTER_TIMEOUT   CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x4, 0)
#define CALL_D_CFG_SIP_SWITCHCALL_TIMEOUT   CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x5, 0)
#define CALL_D_CFG_SIP_SESSIONTIMER_ENABLE  CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0x6, 0)
#define CALL_D_CFG_SIP_SESSIONTIME          CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x7, 0)
#define CALL_D_CFG_SIP_REJECT_TYPE          CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x8, 0)
#define CALL_D_CFG_SIP_TRANS_MODE           CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_INT,    0x9, 0)
#define CALL_D_CFG_SIP_TLS_ROOTCERTPATH     CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_STRING, 0xA, 0)
#define CALL_D_CFG_SIP_SUPPORT_100REL       CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0xB, 0)
#define CALL_D_CFG_SIP_ENABLE_REG_SUB       CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0xC, 0) //�Ƿ�������ע��

/* ȫ��ý��������� */
#define CALL_D_CFG_MEDIA_SRTPMKI            CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x1,0)  //SRTP mki��ʽ
#define CALL_D_CFG_MEDIA_SRTP_MODE          CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x2,0)  //SRTPģʽ
#define CALL_D_CFG_MEDIA_MERGE_SRTP_RTP     CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x3,0)  //�Ƿ�ϲ�SRTP��RTP��m�У�TRUE �ϲ���FALSE ���ϲ�
#define CALL_D_CFG_MEDIA_RTP_PRIORITY       CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x4,0)  //rtp srtp����˳�� 1 rtp���� 2srtp����
#define CALL_D_CFG_MEDIA_CRYPTOSUITE        CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_STRING,    0x5,0)  //SRTP���ܷ������ȼ�
#define CALL_D_CFG_MEDIA_SDP_OLINE_INFO     CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_STRUCTURE, 0x6,0)  //����SDP O����Ϣ
#define CALL_D_CFG_MEDIA_MOS_TIME           CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x7,0)  //MOSֵ�ϱ����ʱ��
#define CALL_D_CFG_MEDIA_MOS_THRESHOLD      CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x8,0)  //MOSֵ�ϱ���ֵ
#define CALL_D_CFG_MEDIA_MOS_SENDINFOSWITCH CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x9,0)  //UC C50 VQM����
#define CALL_D_CFG_MEDIA_SENDONLYFREE       CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0xA,0)  //ý�巽��Ϊsendonly���Ƿ��ͷ���Դ
#define CALL_D_CFG_MEDIA_USEPACKMODE        CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0xB,0)  //H264��ƵЭ��ʱ���Ƿ��жϴ��ģʽһֱ
#define CALL_D_CFG_MEDIA_RECORDFILE_INFO    CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_STRUCTURE, 0xC,0)  //����¼���ļ�������Ϣ

/* ��Ƶ���� */
#define CALL_D_CFG_AUDIO_CODEC              CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_STRING,     0x1, 0) //��Ƶ��������ȼ�
#define CALL_D_CFG_AUDIO_ANR                CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x2, 0) //�������� 
#define CALL_D_CFG_AUDIO_AEC                CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x3, 0) //�������� 
#define CALL_D_CFG_AUDIO_AGC                CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x4, 0) //�Զ����� 
#define CALL_D_CFG_AUDIO_DTMF_MODE          CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x5, 0) //DTMFģʽ
#define CALL_D_CFG_AUDIO_DTMF_PT            CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x6, 0) //DTMF PTֵ      
#define CALL_D_CFG_AUDIO_ILBCMODE           CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x7, 0) //ILBCģʽ 20 �� 30    
#define CALL_D_CFG_AUDIO_PACKETTIME         CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x8, 0) //���ʱ��
#define CALL_D_CFG_AUDIO_NETATELEVEL        CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,       0x9, 0) //netate���༶�� 0~4
#define CALL_D_CFG_AUDIO_VADFLAG            CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_BOOL,       0xA, 0) //Vad���ñ�־λ  0�ر� 1����
#define CALL_D_CFG_AUDIO_CLOCKRATE          CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0xB, 0) //����Ƶ��
#define CALL_D_CFG_AUDIO_CHANNELS           CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0xC, 0) //��������
#define CALL_D_CFG_AUDIO_BITS               CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0xD, 0) //����λ��
#define CALL_D_CFG_AUDIO_PORT_RANGE         CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xE, 0) //��Ƶ�˿ڷ�Χ
#define CALL_D_CFG_AUDIO_PLAYFILE_ADDITIONINFO         CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xF, 0) //������Ƶ�ļ�������Ϣ

/* ��Ƶ���� */
#define CALL_D_CFG_VIDEO_LEVEL              CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x1, 0) //��Ƶ���뼶���Լ���������
#define CALL_D_CFG_VIDEO_DEFAULT_IMAGE      CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRING,     0x2, 0) //����Ƶʱʹ�õ�ͼƬ��ͼƬ������bmp��ʽ��
#define CALL_D_CFG_VIDEO_ARQ                CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x3, 0) //�����ش�
#define CALL_D_CFG_VIDEO_TACTIC             CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0x4, 0) //��Ƶ���� 0 ͼ����������  1 ��������
#define CALL_D_CFG_VIDEO_CODEC              CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRING,     0x5, 0) //��Ƶ��������ȼ�
#define CALL_D_CFG_VIDEO_ERRORCORRECTING    CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x6, 0) //�Ƿ�������У�鹦��
#define CALL_D_CFG_VIDEO_FRAMESIZE          CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x7, 0) //��Ƶ�ֱ���
#define CALL_D_CFG_VIDEO_DATARATE           CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x8, 0) //��Ƶ����
#define CALL_D_CFG_VIDEO_HDACCELERATE       CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x9, 0) //Ӳ������
#define CALL_D_CFG_VIDEO_FRAMERATE          CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xA, 0) //֡��
#define CALL_D_CFG_VIDEO_CODER_QUALITY      CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0xB, 0) //�������� [0-4]
#define CALL_D_CFG_VIDEO_KEYFRAMEINTERVAL   CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0xC, 0) //�ؼ�֡��� [1,30] ��λΪs
#define CALL_D_CFG_VIDEO_ARS                CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xD, 0) //��ƵArs��������
#define CALL_D_CFG_VIDEO_CAPTURE_ROTATION   CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0xE, 0) //����ͷ�ɼ��Ƕ�
#define CALL_D_CFG_VIDEO_PORT_RANGE         CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xF,0) //��Ƶ�˿ڷ�Χ
#define CALL_D_CFG_VIDEO_FORCE_IDR_INFO     CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x10, 0) //�Ƿ�ǿ�ƴ�info idr������շ�
#define CALL_D_CFG_VIDEO_DISPLAYTYPE        CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,       0x11, 0) //��Ƶ��ʾģʽ

/* ���ص�ַ���� */
#define CALL_D_CFG_NET_NETADDRESS           CFG_ID_DEF(CALL_E_CFG_NET, CALL_E_CFG_DATA_TYPE_STRUCTURE, 0x1, 0) //sipʹ�ã���ý��û�е�������ʱ����ý��Ҳ�������ַ
#define CALL_D_CFG_AUDIO_NETADDRESS         CFG_ID_DEF(CALL_E_CFG_NET, CALL_E_CFG_DATA_TYPE_STRING,    0x2, 0) //������Ƶʹ�õ�ַ
#define CALL_D_CFG_VDIEO_NETADDRESS         CFG_ID_DEF(CALL_E_CFG_NET, CALL_E_CFG_DATA_TYPE_STRING,    0x3, 0) //������Ƶʹ�õ�ַ

/* �˺����� */
#define CALL_D_CFG_ACCOUNT_AUTH             CFG_ID_DEF(CALL_E_CFG_ACCOUNT, CALL_E_CFG_DATA_TYPE_STRUCTURE, 0x1, 0)


/**�ƶ���������Ȩ������*/
#define CALL_D_CFG_MOBILE_VVM_RIGHT         CFG_ID_DEF(CALL_E_CFG_MOBILE_VOICEMAIL, CALL_E_CFG_DATA_TYPE_BOOL, 0x1, 0)


/** server config data */
typedef struct tagCALL_S_SERVER_CFG
{
     TUP_CHAR server_address[CALL_D_MAX_URL_LENGTH];   /**server address server_address*/
     TUP_UINT32 server_port;                           /*server port server_port*/
} CALL_S_SERVER_CFG;


typedef struct tagCALL_S_SERVICE_RIGHT_CFG
{
    TUP_UINT32   ulRight;          
    TUP_CHAR     acActiveAccessCode[CALL_D_ACCESSCODE_MAX_LENGTH];         /* �Ǽ������� */
    TUP_CHAR     acDeactiveAccessCode[CALL_D_ACCESSCODE_MAX_LENGTH];       /*ȡ���Ǽ�������*/
}CALL_S_SERVICE_RIGHT_CFG;


/** AACý�������� */
typedef struct
{
     TUP_INT32     bProfileLevel;      /**< �Ƿ��С�profile-level ֵ��*/
     TUP_INT32     lProfileLevel;      /**< profile-level ֵ��*/
     TUP_UINT32    bMaxBitRate;         /**< �Ƿ��д���ֵ */
     TUP_UINT32    ulMaxBitRate;         /**< ����ֵ:��λ: 1bps*/
     TUP_UINT8     bAudioObjectType;     /**< �Ƿ���������Ƶ��������*/
     TUP_UINT8     ucAudioObjectType;  /**< ��Ƶ�������� AAC-LC:2,AAC-LD:23 */
     TUP_UINT8     ucAACFormatType;     /**< ����formattype ����rawdata��latm:1:raw��2:֧��latm��3:��֧��raw��֧��latm*/
     TUP_UINT8     bConfigPresent;     /**< ��Ƶ�����Ƿ���ڴ���,0Ϊ���⴫�ͣ�1Ϊ���ڴ���*/
     TUP_UINT8     bConfig;             /**< �Ƿ������������ַ��� */
     TUP_UINT8     aucReserve[3];      /**< ����λ,�����ֽڶ���*/
     TUP_UINT32    ulConfig;             /**< �����ַ����ĳ��� */
     TUP_UINT8     pcMuxConfig[MPROC_D_AAC_CONFIG_LEN];     /**< �����ַ��� */
}MPROC_S_AAC_CAP_SPECIAL, *MPROC_S_AAC_CAP_SPECIAL_PTR;

/** DTMFý�������� */
typedef struct
{
     TUP_UINT32 ulDTMFTransferMode;      /**< 0���� or 1���⡡*/
}MPROC_S_DTMF_CAP_SPECIAL;

 
typedef struct
{
    TUP_BOOL   bEnable;            /**< TUP_TRUE:֧��*/
    TUP_UINT32  ulPktLen;           /**< ���ʱ��ms */
    TUP_UINT32  ulFrameLen;         /**< ֡��ms, iLBC mode*/
    TUP_UINT32   ulSampleRate;       /**< ������ */
    TUP_UINT8   ucPayLoad;          /**< ��format��Ӧ��ptֵ*/
    TUP_UINT8   ulBitNum;           /**< ֧�ֵ����ʸ��� */
    TUP_UINT8   ulBitRate[MPROC_D_AUD_RATE_NUM];    /**< ���ʺ�ö��ֵ��Ӧ::AUDIO_E_DECODERATE */
    TUP_UINT8   ulPadding[1];                       /**< �ֽڶ��� */
    union{
        MPROC_S_AAC_CAP_SPECIAL stAacSpecial;   /**< aac*/
        MPROC_S_DTMF_CAP_SPECIAL stDTMFSpecial;   /**< DTMF*/
    }uMedSpecialCap;
}MPROC_S_FORMAT_CAP, *MPROC_S_FORMAT_CAP_PTR;



/*ͳһIP��ַ����ӿ���Ϣ���ݽṹ*/
typedef struct CALL_S_IF_INFO 
{
    CALL_E_IP_PROTOCOL_TYPE  ulType;                     // IP��ַ����
    union
    {
        TUP_UINT32 ulIPv4;                              //IPv4��ַ
        TUP_UINT8  aucIPv6[CALL_D_IP_LENGTH];       //IPv6��ַ������16�ֽ�
    }uAddress;
    union
    {
        TUP_UINT32 ulNetMask;                           //IPv4��������
        TUP_UINT8  ulPrefixLen;                         //IPv6��ַǰ׺����
    }uMask;
    union
    {
        TUP_UINT32 ulIPv4;                              //����IPv4��ַ
        TUP_UINT8  aucIPv6[CALL_D_IP_LENGTH];       //����IPv6��ַ������16�ֽ�
    }uGateWay;
} CALL_S_IF_INFO;

typedef struct tagCALL_S_DEVICEINFO
{
    TUP_UINT32 ulIndex;      //�豸��Ӧ��index
    TUP_CHAR   strName[CALL_D_MAX_DISPLAY_NAME]; //�豸����
} CALL_S_DEVICEINFO;



typedef struct tagCALL_S_REFRESH_VIEW
{
    TUP_UINT32 ulCallID;                  /**ͨ��ID */
    CALL_E_REFRESHVIEW_MIDEATYPE enMeidaType;                /**viewˢ��ý������ */
    CALL_E_REFRESHVIEW_EVENT enEvent;                    /**viewˢ���¼� */
} CALL_S_REFRESH_VIEW;
 
typedef struct tagCALL_S_VIDEO_LEVEL
{
    TUP_UINT32 ulLevel;              // H264��level {10,11,12,13,20,21,22,30,31,32,40,41,42,50,51}
    TUP_UINT32 ulMaxMBPS;            // H264��max-bmps  0��ʾʹ�ö�Ӧ�����Ĭ��ֵ
    TUP_UINT32 ulMaxFS;              // H264��max-fs    0��ʾʹ�ö�Ӧ�����Ĭ��ֵ
    TUP_UINT32 ulMaxBR;              // H264��max-br    0��ʾʹ�ö�Ӧ�����Ĭ��ֵ
} CALL_S_VIDEO_LEVEL;

//SDP O����Ϣ
typedef struct tagCALL_S_SDP_OLINE_INFO
{
    TUP_CHAR acUserName[CALL_D_MAX_LENGTH_NUM];              // username       "FAST_V2R1"
    TUP_CHAR acSessionId[CALL_D_MAX_LENGTH_NUM];             // session identifier  "2006"
    TUP_CHAR acSessionVersion[CALL_D_MAX_LENGTH_NUM];        // session version     "2006"
} CALL_S_SDP_OLINE_INFO;

//SRTP��Ϣ
typedef struct tagCALL_S_SRTP_INFO
{
    TUP_BOOL bMkiMode;
    TUP_CHAR acCryptoSuite[CALL_D_MAX_LENGTH_NUM];
} CALL_S_SRTP_INFO;

typedef struct tagCALL_S_VIDEO_DATARATE
{
    TUP_UINT32 ulDataRate;
    TUP_UINT32 ulMinDataRate; 
    TUP_UINT32 ulMaxDataRate;
    TUP_UINT32 ulMaxBw;
} CALL_S_VIDEO_DATARATE;


typedef struct tagCALL_S_VIDEO_FRAMERATE
{
    TUP_UINT32 uiFrameRate;
    TUP_UINT32 uiMinFrameRate; 
} CALL_S_VIDEO_FRAMERATE;

typedef struct tagCALL_S_VIDEO_FRAMESIZE
{
    TUP_UINT32 uiFramesize;
    TUP_UINT32 uiMinFramesize; 
    TUP_UINT32 uiDecodeFrameSize;
} CALL_S_VIDEO_FRAMESIZE;


typedef struct tagCALL_S_VIDEO_ARS
{
    TUP_BOOL bArs;
    TUP_BOOL bArsCtrlFec;
    TUP_UINT32 ulMaxFecProFac;
    TUP_BOOL  bArsCtrlBitRate;
    TUP_BOOL  bArsCtrlFrameRate;
    TUP_BOOL  bArsCtrlFrameSize;
} CALL_S_VIDEO_ARS;

typedef struct tagCALL_S_VIDEO_RENDER_INFO
{
    CALL_E_VIDEOWND_TYPE enRenderType;//��������ö��ֵ 0:Զ�˴��ڣ�1:���˴���
    TUP_UINT32 ulDisplaytype; //������ʾģʽ 0:����ģʽ 1:(������)�ڱ�ģʽ 2:(������)�ü�ģʽ
    TUP_UINT32 ulMirrortype;  //���ھ���ģʽ 0:��������(Ĭ��ֵ) 1:���¾���(Ŀǰδ֧��) 2:���Ҿ���
}CALL_S_VIDEO_RENDER_INFO;

typedef struct tagCALL_S_VIDEO_ORIENT
{
    TUP_UINT32 ulChoice;         //��Ƶ��������� 1��������2��������3���������
    TUP_UINT32 ulPortrait;       //������Ƶ������ʱ����ת���Ƕ� 0��0�ȣ�1��90�ȣ�2��180�ȣ�3��270�ȣ�
    TUP_UINT32 ulLandscape;      //������Ƶ������ʱ����ת���Ƕ� 0��0�ȣ�1��90�ȣ�2��180�ȣ�3��270�ȣ�
    TUP_UINT32 ulSeascape;       //���������Ƶ������ʱ����ת���Ƕ� 0��0�ȣ�1��90�ȣ�2��180�ȣ�3��270�ȣ�
}CALL_S_VIDEO_ORIENT; //4

typedef struct tagCALL_S_RTP_PORT_RANGE
{
    TUP_UINT32 ulMinPort;
    TUP_UINT32 ulMaxPort;
} CALL_S_RTP_PORT_RANGE;

typedef enum tagCALL_E_SRTP_MODE
{
    CALL_E_SRTP_MODE_DISABLE,
    CALL_E_SRTP_MODE_OPTION,
    CALL_E_SRTP_MODE_FORCE,
    CALL_E_SRTP_MODE_BUTT
} CALL_E_SRTP_MODE;

typedef enum tagCALL_E_TRANSPORTMODE
{
    CALL_E_TRANSPORTMODE_UDP,
    CALL_E_TRANSPORTMODE_TLS,
    CALL_E_TRANSPORTMODE_TCP,
    CALL_E_TRANSPORTMODE_DEFAULT,    /* Ĭ��ʹ�ù��ô��䷽ʽ */
    CALL_E_TRANSPORTMODE_SVN,
    CALL_E_TRANSPORTMODE_BUTT
} CALL_E_TRANSPORTMODE;

//todo chenyake 
typedef TUP_VOID (*CALL_FN_CALLBACK_PTR)(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *data);
 
typedef TUP_VOID (*CALL_FN_DEBUG_CALLBACK_PTR)(const TUP_INT8 *app_name, TUP_UINT32 level,
                            const TUP_INT8* function, const TUP_INT8* filename, TUP_UINT32 line_num, const TUP_INT8 *format, ...);



#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif  /* __CALL_DEF_H__ */

/** @}*/
