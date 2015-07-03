

#ifndef __CALL_DEF_H__
#define __CALL_DEF_H__


#include "tup_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

#define CALL_D_ACCESSCODE_MAX_LENGTH     (32)  /* 接入码字符串最大长度*/
#define CALL_D_IP_LENGTH                 (16)   
#define CALL_D_PROTOCOL_LENGTH           (30)  /** 协议名字长度 */
#define MPROC_D_AAC_CONFIG_LEN           (16)  /**< AAC的config码流*/
#define MPROC_D_AUD_RATE_NUM             (16)  /** 格式音频支持多个码率的个数*/
#define MPROC_D_MAX_AUDIO_OUT_VOLUME     (100)

#define CALL_D_MAX_CODEC_LIST_LEN        (127) /** 编解码list最大长度*/

#define CALL_MAX_CODEC_NAME_LEN          (31)  /** 音视频编解码名称长度 */
#define CALL_MAX_FRAMESIZE_LEN            (16)  /** 视频分辨率长度 */    
#define CALL_MAX_PROFILE_LEN              (8)   /** 视频编解码格式长度*/

#define CALL_D_MAX_LENGTH_NUM           (256) 
#define CALL_D_MAX_DISPLAY_NAME         (256)
#define CALL_D_MAX_USERNAME_LENGTH      (256)
#define CALL_D_MAX_PASSWORD_LENGTH      (256)
#define CALL_D_MAX_URL_LENGTH           (256)
    
#define CALL_D_MAXDEVICENUM             (8)             /* 最大设备数量 */

/** 预设消息字符串最大长 */
#define CALL_D_MAX_PRESET_MSG_LENGTH     (100)

#define CALL_D_MAX_MSGSUMMARY_NUM (10)

    /*Multiline*/
#define CALL_D_MAX_ACCOUNT_NUM (24)             /**< 最大线路路数 */
#define CALL_D_MAX_CALL_NUM (24)               /**< 最大呼叫路数 */
#define CALL_D_MAX_LINE_NUM (24)              /**< 最大线路路数 */
#define CALL_D_MAX_LINE_KEY_NUM (24)

    /*IPT*/
#define CALL_D_MAX_ACB_NUM (5)             /**< 最大回呼个数 */

#define CALL_D_MAX_FOWARD_NUM (24)                  /**< 最大前转控制块处理个数*/

#define CALL_D_MAX_INTERCOM_GROUPNUM (CALL_D_MAX_ACCOUNT_NUM-1)     /**< 最大intercom线路数,最多比最大账号数少一路 */

/** 会议相关定义 */
#define CALL_D_PASSCODE_LENGTH          (50)  /*会议创建结果中passcode的长度 */
#define CALL_D_DATACONF_PARAM_LENGTH    (32) //数据会议参数长度普适值
#define CALL_D_DATACONF_CMADDR_LENGTH   (64) //数据会议参数cm_address长度值
#define CALL_D_CONF_CODE_LENGTH   (33) /*会议接入码，在INFO 241中若携带的invite-chairman-flag=0时有返回；USM组网下PC联动会议使用*/

/** 呼叫模块ID */
typedef enum tagCALL_E_MOD_ID
{
    CALL_E_MOD_ID_TSP = 0,         /**< 呼叫控制主消息处理模块 */
//    CALL_E_MOD_ID_STACK = PID_SIP_STACK,           /**< SIP协议栈消息处理模块 */ //modify by zhangwp 00192189
    CALL_E_MOD_ID_STACK ,           /**< SIP协议栈消息处理模块 */ //modify by zhouxinzhong for TUP, depart from minidopra

    CALL_E_MOD_ID_SIP = 4096,      /**< SIPC消息处理模块 */
    CALL_E_MOD_ID_HLLM,            /**< HLLM负责DNS查询消息处理模块 */
    CALL_E_MOD_ID_VCOM,            /**< VCOM消息处理模块 */
    CALL_E_MOD_ID_TPTD,            /**< TPTD消息处理模块 */
    //CALL_E_MOD_ID_STACK,           /**< SIP协议栈消息处理模块 */   //modify by zhangwp 00192189

    CALL_E_MOD_ID_BUTT
} CALL_E_MOD_ID;

typedef enum tagCALL_E_ID_TYPE
{
    CALL_E_IDTYPE_CALL_ID,
    CALL_E_IDTYPE_CONF_ID
}CALL_E_ID_TYPE;

/*日志级别 */
enum CALL_E_LOG_LEVEL
{
    CALL_E_LOG_ERROR = 0,    
    CALL_E_LOG_WARNING,     
    CALL_E_LOG_INFO,         
    CALL_E_LOG_DEBUG         
};

/** 系统错误码定义,TODO, to be better */
typedef enum tagCALL_E_ERR_ID
{
    CALL_E_ERR_BEGIN = 0x08002100UL,
    CALL_E_ERR_GENERAL_ERROR,                     /**<1 一般错误 */
    CALL_E_ERR_PARAM_ERROR,                       /**<2参数错误 */
    CALL_E_ERR_MEM_ERROR,                         /**<3分配内存错误 */
    CALL_E_ERR_SYSTEM_ERROR,                      /**<4系统错误 */
    CALL_E_ERR_MSG_ERROR,                         /**<5发送消息错误 */
    CALL_E_ERR_CFG_ERROR,                         /**<6获取系统配置错误 */
    CALL_E_ERR_NET_ERROR,                         /**<7物理网络错误 */
    CALL_E_ERR_ACCESS_ERROR,                      /**<8网络接入失败错误 */
    CALL_E_ERR_TIMER_ERROR,                       /**<9创建定时器错误 */
    CALL_E_ERR_STATE_ERROR,                       /**<10呼叫状态不正确 */
    CALL_E_ERR_OPERATE_ERROR,                     /**<11正在进行其他操作错误 */
    CALL_E_ERR_REQSRV_ERROR,                      /**<12请求主控进行呼叫开始错误 */
    CALL_E_ERR_REQRES_ERROR,                      /**<13申请音频资源错误 */
    CALL_E_ERR_SERVICE_DOING,                     /**<14正在进行其他补充业务 */
    CALL_E_ERR_CALLRECORD_ERROR,                  /**<15记录通话记录错误 */
    CALL_E_ERR_MPROC_ERROR,                       /**<16媒体进程返回的错误 */
    CALL_E_ERR_MAX_CALL_ERROR,                    /**<17超过最大呼叫路数 */
    CALL_E_ERR_SIPID_NOTEXIT_ERROR,               /**<18SIP账户ID不存在 */
    CALL_E_ERR_CALLID_NOEXIT_ERROR,               /**<19呼叫ID不存在 */
    CALL_E_ERR_REGISTERING_ERROR,                 /**<20正在注册中失败*/
    CALL_E_ERR_REGIST_FALL_ERROR,                 /**<21调用sip接口注册失败 */
    CALL_E_ERR_DEREGIST_FALL_ERROR,               /**<22调用sip接口注销失败 */
    CALL_E_ERR_SET_SIP_INFO_ERROR,                /**<23设置账户信息错误 */
    CALL_E_ERR_SETACCOUNT_ERROR,                  /**<24设置SIP模块失败*/
    CALL_E_ERR_NOTIFYSIPACCOUNT_ERROR,            /**<25上报失败  */
    CALL_E_ERR_SIPSEVER_ERROR,                    /**<26服务器信息错误*/
    CALL_E_ERR_SIPACCOUNTINFO_ERROR,              /**<27账户信息错误*/
    CALL_E_ERR_SIPC_ERROR,

    CALL_E_ERR_UNREGISTER_ERROR,                  /**<28未注册错误addby chendk*/
    CALL_E_ERR_SUB_FALL_ERROR,                    /**<29调用Sip接口订阅失败 */
    CALL_E_ERR_DESUBING_ERROR,                    /**<30注销订阅中错误 */
    CALL_E_ERR_SUBING_ERROR,                      /**<31订阅中错误 */

    CALL_E_ERR_LOCAL_MAX_CONFER_ERROR,            /**<32本地会议已创建，只允许一个会场*/
    CALL_E_ERR_LOCAL_CONFER_NOEXIT_ERROR,         /**<33本地会议未创建 */
    CALL_E_ERR_LOCAL_CONFER_NOMATCH_ERROR,        /**<34与会者线路与主席账户不匹配*/
    CALL_E_ERR_CONF_STATE_ERROR,                  /**<35本地会议状态错误*/
    CALL_E_ERR_JOINTSTATENOTIFY_ERROR,            /**<36IP Phone端联动状态上报失败*/
    CALL_E_ERR_CONFID_NOTEXIST_ERROR,             /* 37会议ID不存在 */
    CALL_E_ERR_CONF_VIDEO_HOLD_ERROR,             /* 38视频保持失败 */
    CALL_E_ERR_CONF_VIDEO_UNHOLD_ERROR,             /* 39视频恢复失败 */
    CALL_E_ERR_MAX_SERVER_CONF_ERROR,             /* 40服务器会议个数超出 */
    CALL_E_ERR_AA_REQRANDOMNUM_ERROR,             /* 41AA获取随机数失败 */
    CALL_E_ERR_AA_LOGIN_ERROR,                    /* 42AA登陆失败 */
    CALL_E_ERR_CONF_VIDEO_TYPE_NO_MATCH,          /**43会议类型不匹配*/
    CALL_E_ERR_CONF_VIDEO_START_ERROR,              /**44 视频会议开启失败*/
    CALL_E_ERR_AA_NOMAINSERVER_ERROR,           /* 45AA无主服务器 */
    CALL_E_ERR_AA_PASSWORD_ERROR,                   /*46 密码错误 */
    CALL_E_ERR_AA_USERNAME_ERROR,                   /* 47用户名错误 */
    CALL_E_ERR_AA_USERLOGINED_ERROR,                /* 48用户已登录 */
    CALL_E_ERR_AA_ACCOUNTLOCKED_ERROR,             /* 49账户已锁定 */
    CALL_E_ERR_AA_TERMINALTYPE_ERROR,               /* 50终端类型不匹配 */
    CALL_E_ERR_AA_PARSEXML_ERROR,                   /* 51解析XML错误 */
    CALL_E_ERR_AA_CONNECT_ERROR,                    /* 52连接服务器错误 */

    CALL_E_ERR_MEDIA_CFG_ERROR,                   /** 53获取媒体配置失败 */
    CALL_E_ERR_AA_GETSRINFO_ERROR,                /* 54获取业务权限失败 */
    CALL_E_ERR_AA_LACKSR_ERROR,                    /* 55业务权限不足失败 */

    CALL_E_ERR_NETWORKENV_ERROR,                    /* 56网络环境错误 */
    CALL_E_ERR_SERVICE_CONFLICT_ERROR,              /** 57业务冲突 add by sunpy*/
    CALL_E_ERR_AA_TIMEOUT_ERROR,                  /* 58连接超时 */
    CALL_E_ERR_AA_UNKOWN_ERROR,                   /** 59未知错误*/
    CALL_E_ERR_PICKUP_ADDTIP_ERROR,                /* 添加振铃信息失败 */
    CALL_E_ERR_PICKUP_REMOVETIP_ERROR,             /* 删除加振铃信息失败 */
    CALL_E_ERR_PICKUP_CREATERINGNUM_ERROR,             /* 创建振铃号码失败 */
    CALL_E_ERR_VVM_PARAM_ERR,                      /** VVM参数错误 */

    CALL_E_ERR_GET_IPT_INFO_ERR,                   /** 获取登记业务错误 */
    CALL_E_ERR_VVM_GETVOICEMAIL_ERR,               /** 获取语音邮箱 */
    CALL_E_ERR_ATTENDEE_ALREADY_EXIST,             /** 与会者已经存在 */
    CALL_E_ERR_ATTENDEE_NOT_EXIST,                  /** 与会者不存在 */
    CALL_E_ERR_CREATE_CONF_WND_ERROR,                /** 创建服务器视频会议窗口失败*/
    CALL_E_ERR_CREATE_CONF_WND_EXIST,                /** 视频窗口不存在*/
    CALL_E_ERR_GET_CONF_LIST_INFO_ERROR,               /** 获取CONF LIST 失败*/
    CALL_E_ERR_NEED_CHAIRMAN_TO_OPERATE,            /** 需要主持人权限才能操作*/
    CALL_E_ERR_NO_VIDEO_DEVICE_TO_OPERATE,            /** 没有视频设备可以操作*/

    CALL_E_ERR_BUTT,
    CALL_E_ERR_NUM = (CALL_E_ERR_BUTT & 0x00001FFF)
} CALL_E_ERR_ID;

/** 信令失败的原因码 */
typedef enum tagCALL_E_REASON_CODE
{
    CALL_E_REASON_CODE_OK = 0,

    /** 信令失败的错误码 */
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

/* 特征码业务类型*/
typedef enum tagCALL_E_SERVICE_CALL_TYPE
{
    CALL_E_SERVICE_CALL_NORMAL,


    CALL_E_SERVICE_CALL_TYPE_REG_DND,           /** 登记DND */
    CALL_E_SERVICE_CALL_TYPE_UNREG_DND,        /** 取消登记DND */

    
    CALL_E_SERVICE_CALL_TYPE_CALL_WAIT_ACTIVE,            /* 呼叫等待开启 */
    CALL_E_SERVICE_CALL_TYPE_CALL_WAIT_DEACTIVE,        /* 呼叫等待关闭 */

    CALL_E_SERVICE_CALL_TYPE_REG_SCAPRIVATE,      /** 登记私人呼叫 */
    CALL_E_SERVICE_CALL_TYPE_UNREG_SCAPRIVATE,  /** 取消登记私人呼叫 */


    /* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR-0000159474] [2013/1/18] [zhanglusha 00219468]]
       修改原因: 经理秘书业务:来电静音和privacy */

    CALL_E_SERVICE_CALL_TYPE_REG_ALERT_SILENCE,     /** 登记共享线来电静音 */
    CALL_E_SERVICE_CALL_TYPE_UNREG_ALERT_SILENCE,   /** 取消共享线来电静音 */
    CALL_E_SERVICE_CALL_TYPE_REG_PRIVACY,           /** 登记privacy业务*/
    CALL_E_SERVICE_CALL_TYPE_UNREG_PRIVACY,         /** 取消privacy业务*/

    /* END   add: [[eSpace 7900 V100R001C02B010] [IR-0000159474] [2013/1/18] [zhanglusha 00219468]] */

    CALL_E_SERVICE_CALL_TYPE_SET_CALLPARK,      /** 设置呼叫驻留 */
    CALL_E_SERVICE_CALL_TYPE_DIRECTCALLPARK,    /** 直接呼叫驻留 */
    CALL_E_SERVICE_CALL_TYPE_GET_CALLPARK,      /** 取回呼叫驻留 */

    /**本地前转 */
    CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION,                      /**无条件前转*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY,                           /**遇忙前转*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY,                          /**无应答前转*/

    /**服务器类前转 */
    CALL_E_SERVICE_CALL_TYPE_CFUVoiceMail_Active,        /* 无条件转语音邮箱登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_CFUVoiceMail_Deactive,     /* 无条件转语音邮箱注销*/
    CALL_E_SERVICE_CALL_TYPE_CFBVoiceMail_Active,        /* 遇忙 转语音邮箱登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_CFBVoiceMail_Deactive,   /* 遇忙 转语音邮箱注销*/
    CALL_E_SERVICE_CALL_TYPE_CFNVoiceMail_Active,        /* 无应答 转语音邮箱登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_CFNVoiceMail_Deactive,   /* 无应答 转语音邮箱注销*/
    CALL_E_SERVICE_CALL_TYPE_CFOVoiceMail_Active,        /* 离线 转语音邮箱登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_CFOVoiceMail_Deactive,   /* 离线 转语音邮箱注销*/
    /*basic*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Active,                      /**无条件前转*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Deactive,
    CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Active,                           /**遇忙前转*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Deactive,
    CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Active,                          /**无应答前转*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Deactive,
    CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Active,                          /**离线前转*/
    CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Deactive,

    /** 各特征码业务类型在此添加*/
    CALL_E_SERVICE_CALL_TYPE_SCAPRIVATE_ACTIVE,        /* 共享线路私人呼叫登记*/
    CALL_E_SERVICE_CALL_TYPE_SCAPRIVATE_DEACTIVE,     /* 共享线路私人呼叫注销*/

    CALL_E_SERVICE_CALL_TYPE_ACBCALL_ACTIVE,        /* 呼叫回呼登记(激活) */
    CALL_E_SERVICE_CALL_TYPE_ACBCALL_DEACTIVE,     /* 呼叫回呼注销 */

    CALL_E_SERVICE_CALL_TYPE_GOURPPICKUP,                  /**群组代答*/
    CALL_E_SERVICE_CALL_TYPE_DESPICKUP,                    /**指定代答*/

    CALL_E_SERVICE_CALL_TYPE_DIVERT,                /**偏转**/

    /* BEGIN add: [[V100R001C50] [IR.IPT.025] [2013/12/3] [WuDingyuan]]
       修改原因: 新需求:拒绝前转来电 */
    CALL_E_SERVICE_CALL_TYPE_REG_DICF,          /** 登记DICF */
    CALL_E_SERVICE_CALL_TYPE_UNREG_DICF,        /** 注销DICF */
    /* END   add: [[V100R001C50] [IR.IPT.025] [2013/12/3] [WuDingyuan]] */

    CALL_E_SERVICE_CALL_TYPE_ABSENT_ON,        /** 开启absence */
    CALL_E_SERVICE_CALL_TYPE_ABSENT_OFF,       /** 关闭absence */

    CALL_E_SERVICE_CALL_TYPE_MCID,             /* 恶意呼叫跟踪 */

    CALL_E_SERVICE_CALL_TYPE_CALL_LIMIT_ACTIVE,         /** 开启密码限呼 */
    CALL_E_SERVICE_CALL_TYPE_CALL_LIMIT_DEACTIVE,       /** 关闭密码限呼 */

    CALL_E_SERVICE_CALL_TYPE_ATTENDCONF_BY_ONEKEY,                /**一键入会**/
    /* BEGIN add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] 
       修改原因: huntgroup签入签出 */
    CALL_E_SERVICE_CALL_TYPE_HUNTGROUP_SIGNIN,      /* huntgroup签入 */
    CALL_E_SERVICE_CALL_TYPE_HUNTGROUP_SIGNOUT,     /* huntgroup签出 */
    CALL_E_SERVICE_CALL_TYPE_GET_VIRTUALVM,
    /* END   add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] */

    CALL_E_SERVICE_CALL_TYPE_BUIT

} CALL_E_SERVICE_CALL_TYPE;




typedef enum tagCALL_E_DTMF_TONE
{
    CALL_E_DTMF0,   /**< dtmf按键0 */
    CALL_E_DTMF1,   /**< dtmf按键1 */
    CALL_E_DTMF2,   /**< dtmf按键2 */
    CALL_E_DTMF3,   /**< dtmf按键3 */
    CALL_E_DTMF4,   /**< dtmf按键4 */
    CALL_E_DTMF5,   /**< dtmf按键5 */
    CALL_E_DTMF6,   /**< dtmf按键6 */
    CALL_E_DTMF7,   /**< dtmf按键7 */
    CALL_E_DTMF8,   /**< dtmf按键8 */
    CALL_E_DTMF9,   /**< dtmf按键9 */
    CALL_E_DTMFSTAR,    /**< dtmf按键'*' */
    CALL_E_DTMFJIN,     /**< dtmf按键'#' */
    CALL_E_DTMFA,   /**< dtmf按键A */
    CALL_E_DTMFB,   /**< dtmf按键B */
    CALL_E_DTMFC,   /**< dtmf按键C */
    CALL_E_DTMFD,   /**< dtmf按键D */
    CALL_E_DTMFFLASH,   /**< dtmf按键FLASH */
    CALL_E_BUTT
} CALL_E_DTMF_TONE;




/** 上报给界面的事件 */
/*Do we need split it to basic and advanced  notify?*/
typedef enum tagCALL_E_CALL_EVENT
{
    CALL_E_EVT_BEGIN = 0,

    CALL_E_EVT_SIPACCOUNT_INFO,                     /**< 通知上层应用，SIP账户信息改变 1*/
    CALL_E_EVT_CALL_STARTCALL_RESULT,               /*发起呼叫响应，异步2*/

    CALL_E_EVT_CALL_INCOMMING,                      /**< 来电事件 3*/
    CALL_E_EVT_CALL_OUTGOING,                       /**< 呼出事件 4*/
        
    CALL_E_EVT_CALL_RINGBACK,                        /**< 回铃音事件 */
    CALL_E_EVT_CALL_CONNECTED,                        /**< 通话已建立 */
    CALL_E_EVT_CALL_ENDED,                            /**< 会叫结束 */
    CALL_E_EVT_CALL_DESTROY,                        /**8< 删除呼叫ID */
    CALL_E_EVT_CALL_RTP_CREATED,                    /** RTP通道已建立，可以进行二次拨号 */
    CALL_E_EVT_CALL_ADD_VIDEO,
    CALL_E_EVT_CALL_DEL_VIDEO,
    CALL_E_EVT_CALL_MODIFY_VIDEO_RESULT,

    CALL_E_EVT_REFRESH_VIEW,                /*视频view刷新通知*/
    CALL_E_EVT_MOBILE_ROUTE_CHANGE,                       /**移动路由变化通知*/
    CALL_E_EVT_AUDIO_END_FILE,   /** 音频文件播放结束通知*/
    CALL_E_EVT_NET_QUALITY_CHANGE,  /** 网络质量改变通知*/
    CALL_E_EVT_STATISTIC_NETINFO, /** 网络质量统计信息*/
    CALL_E_EVT_STATISTIC_MOS,   /** MOS分上报*/ 
    /**话机；视频质量上报ulQualityLevel 0-5 level=0时error值有效网络错误 0 : 没有错误 1 : 网络发端错误 2 : 网络收端错误 3 : 网络收发均错误。*/
    CALL_E_EVT_SPKDEV_VOLUME_CHANGE,           /*扬声器设备音量变化(pc/mac)*/
    CALL_E_EVT_MICDEV_VOLUME_CHANGE,           /*麦克风设备音量变化(pc/mac)*/
    CALL_E_EVT_AUDIO_UNIT_INIT,           /*音频单元初始化完成通知(可用于通知上层设置路由)*/
    CALL_E_EVT_AUDIO_SET_INDEVICE_ERR,    /*音频设置输入设备失败*/
    CALL_E_EVT_AUDIO_SET_OUTDEVICE_ERR,    /*音频设置输出设备失败*/

    CALL_E_EVT_VIDEO_OPERATION, /**视频操作*/
    CALL_E_EVT_VIDEO_STATISTIC_NETINFO,     /**视频网络质量统计信息*/
    CALL_E_EVT_VIDEO_QUALITY,   /**视频质量*/
    CALL_E_EVT_VIDEO_FRAMESIZE_CHANGE,  /**视频大小变更*/

    CALL_E_EVT_SESSION_MODIFIED, /**会话修改完成通知*/
    CALL_E_EVT_SESSION_CODEC,    /**会话正在使用的codec通知*/

    CALL_E_EVT_CALL_HOLD_SUCCESS,                   /**< 保持成功 */
    CALL_E_EVT_CALL_HOLD_FAILED,                    /**< 保持失败 */
    CALL_E_EVT_CALL_UNHOLD_SUCCESS,                 /**< 恢复成功 */
    CALL_E_EVT_CALL_UNHOLD_FAILED,                  /**< 恢复失败 */

    CALL_E_EVT_CALL_ENDCALL_FAILED,                 /**< 结束通话失败 */
    CALL_E_EVT_CALL_DIVERT_FAILED,                  /**< 偏转失败 */

    CALL_E_EVT_CALL_BLD_TRANSFER_SUCCESS,           /**< 盲转成功 */
    CALL_E_EVT_CALL_BLD_TRANSFER_FAILED,            /**< 盲转失败 */
    CALL_E_EVT_CALL_ATD_TRANSFER_SUCCESS,           /**< 咨询转成功 */
    CALL_E_EVT_CALL_ATD_TRANSFER_FAILED,            /**< 咨询转失败 */


    CALL_E_EVT_SET_IPT_SERVICE_SUCCESS,        /*21* 登记业务成功,仅在呼叫控制使用 */
    CALL_E_EVT_SET_IPT_SERVICE_FAILED,         /** 登记业务失败,仅在呼叫控制使用 */

    CALL_E_EVT_SIPACCOUNT_WMI,                      /**< 留言通知*/
    CALL_E_EVT_VVM_DOWNLOAD_SUCCESS_NOTIFY,          /*VVM下载结果通知*/
    CALL_E_EVT_VVM_DOWNLOAD_FAIL_NOTIFY,
    CALL_E_EVT_VVM_FORWARD_SUCCESS_NOTIFY,           /*VVM转发留言结果通知 */
    CALL_E_EVT_VVM_FORWARD_FAIL_NOTIFY,
    CALL_E_EVT_VVM_DELETE_SUCCESS_NOTIFY,           /*VVM删除留言结果通知 */
    CALL_E_EVT_VVM_DELETE_FAIL_NOTIFY,
    CALL_E_EVT_VVM_DELETEALL_SUCCESS_NOTIFY,           /*30 VVM删除所有留言结果通知 */
    CALL_E_EVT_VVM_DELETEALL_FAIL_NOTIFY,    
        
    CALL_E_EVT_CALL_VoiceMail_SUB_SUCCESS,          /*语言邮箱订阅结果 */
    CALL_E_EVT_CALL_VoiceMail_SUB_FAILED,
    
    CALL_E_EVT_TO_UI_JOINT_START,                  /* 联动开启事件*/
    CALL_E_EVT_TO_UI_JOINT_CLOSE,                  /* 联动关闭事件*/
    CALL_E_EVT_TO_UI_JOINT_ACCEPTCALL,             /* 联动代接事件*/
    CALL_E_EVT_TO_UI_JOINT_STARTCALL,              /* 联动代拨事件*/
    CALL_E_EVT_TO_UI_JOINT_HUNGUP,                 /* 联动代挂事件*/
    CALL_E_EVT_TO_UI_JOINT_HOLD,                   /* 联动保持请求 */
    CALL_E_EVT_TO_UI_JOINT_UNHOLD,                 /* 联动恢复请求 */
    CALL_E_EVT_TO_UI_JOINT_DIVERT,                 /* 联动偏转请求 */
    CALL_E_EVT_TO_UI_JOINT_BLDTRANSFER,            /* 联动盲转请求 */
    CALL_E_EVT_TO_UP_JOINT_TO_CONF,                /* 联动两方转三方 */
    CALL_E_EVT_TO_UI_JOINT_DTMF,
    CALL_E_EVT_TO_UI_JOINT_CONFCREATE,

    CALL_E_EVT_TO_UI_JOINT_ONLINE,                  /*联动话机上线*/
    CALL_E_EVT_TO_UI_JOINT_OFFLINE,                 /*联动话机下线*/
    CALL_E_EVT_TO_UI_JOINT_ONHOOK,                  /*联动话机已挂机*/
    CALL_E_EVT_TO_UI_JOINT_OFFHOOK,                 /*联动话机已摘机*/
    CALL_E_EVT_TO_UI_JOINT_OUTGOING,                /*联动话机已呼出*/
    CALL_E_EVT_TO_UI_JOINT_ESTABLISHED,             /*联动话机进入通话中*/
    CALL_E_EVT_TO_UI_JOINT_RINGRING,                /*联动话机振铃*/
    CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PHONE,
    CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PC,
    CALL_E_EVT_TO_UI_JOINT_CREATE_CONFERENCE,       /* IPPHONE创会通知*/
    CALL_E_EVT_TO_UI_JOINT_REFER_RESULT,
    CALL_E_EVT_TO_UI_JOINT_STARTVIDEOCALL,              /* 联动视频代拨事件*/
    CALL_E_EVT_TO_UI_JOINT_CONF_RESULT,              /* 联动PC建会结果通知话机的返回消息*/
    
    CALL_E_EVT_TO_UI_CTD_INFO,
    
    CALL_E_EVT_SERVER_LINK_OK,                     /*服务器连接正常，话机自 检 suijun193874 */

    CALL_E_EVT_CALL_RECORD_SUCCESS,                   /**< 录音开启成功 */
    CALL_E_EVT_CALL_RECORD_FAILED,                    /**< 录音开启失败 */
    CALL_E_EVT_CALL_UNRECORD_SUCCESS,                 /**< 录音关闭成功 */
    CALL_E_EVT_CALL_UNRECORD_FAILED,                  /**< 录音关闭失败 */

    CALL_E_EVT_CALL_CALLINFO_SUB_FAILED,            /**< 共享线路状态订阅失败 */
    CALL_E_EVT_CALL_CALLINFO_UNSUB_FAILED,          /**< 共享线路状态去订阅失败 */
    CALL_E_EVT_CALL_LINESEIZE_UNSUB_FAILED,         /**< 共享摘机去订阅失败 */
    CALL_E_EVT_CALL_LINESEIZE_UNSUB_SUCCESS,         /**< 共享摘机去订阅成功*/
    CALL_E_EVT_CALL_LINESEIZE_SUCCESS,
    CALL_E_EVT_CALL_LINESEIZE_FAILED,               /**< 共享摘机失败 */
    CALL_E_EVT_CALL_CALLINFO_NOTIFY,                /**<共享线路状态通知*/    

    CALL_E_EVT_CALL_MODIFY_SUCCESS,                 /**< 修改通话成功 */
    CALL_E_EVT_CALL_MODIFY_FAILED,                  /**< 修改通话失败 */
    CALL_E_EVT_CALL_JOIN_CONF,                      /**< 通话加入本地会议，通知通话状态 */
    CALL_E_EVT_LCONF_JOIN_SUCCESS,                  /**< 本地会议加入成功 add by h00206999 */
    CALL_E_EVT_LCONF_JOIN_FAILED,                   /**< 本地会议加入失败 add by h00206999 */
    CALL_E_EVT_LCONF_TALK_STATE_CHANGE,             /**< 与会者发言状态改变 */
    CALL_E_EVT_LCONF_CONFEREE_DROPED,               /**< 剔除与会者/与会者退出会场 */
    CALL_E_EVT_LCONF_CONFER_ENDED,                  /**< 结束会议通知 */
    CALL_E_EVT_LCONF_HOLD_SUCESS,                   /**< 保持会场成功*/
    CALL_E_EVT_LCONF_HOLD_FAILED,                   /**< 保持会场失败 */
    CALL_E_EVT_LCONF_UNHOLD_SUCESS,                 /**< 恢复会场成功 */
    CALL_E_EVT_LCONF_UNHOLD_FAILED,                 /**< 恢复会场失败 */
    CALL_E_EVT_CALL_MOBILE_EXTEND_SUCCESS,          /**手机分机切换成功*/
    CALL_E_EVT_CALL_MOBILE_EXTEND_FAILED,           /*70*手机分机切换失败 */

    CALL_E_EVT_CALL_ACBCALL_REQ,                  /**< ACB请求 */
    CALL_E_EVT_CALL_ACBCALL_TIMEOUT,              /**< ACB超时 */
    CALL_E_EVT_CALL_CALLPARK_GET_SUCCESS,       /* 驻留取回成功*/
    CALL_E_EVT_CALL_CALLPARK_GET_FAILED,        /* 驻留取回失败*/
    CALL_E_EVT_CALL_CALLPARK_INVALID,             /**< 驻留超时或者被取回 */
    
    CALL_E_EVT_CONTACT_STATUS_CHANGE,            /**< 联系人状态上报 */
    CALL_E_EVT_CONTACTINCRE_STATUS_CHANGE,            /**< PGM联系人增量上报 */
    CALL_E_EVT_CONTACT_INFO,                      /**< 联系人信息 */
    CALL_E_EVT_PHONE_SETTING_STATUS_CHANGE,
    
    CALL_E_EVT_CALL_AUTHORIZE_SUCCESS,              /* 鉴权成功  */
    CALL_E_EVT_CALL_AUTHORIZE_FAILED,               /*80 鉴权失败 */
    CALL_E_EVT_NEW_SERVICE_RIGHT,                   /* 81 业务权限改变，通知界面 */
    
    CALL_E_EVT_SERVERCONF_INCOMING,                  /**< 会议邀请事件 */
    CALL_E_EVT_SERVERCONF_CREATE_RESULT,            /**< 创建会议结果 */
    CALL_E_EVT_SERVERCONF_CONNECT_RESULT,           /**< 加入会议结果 */
    CALL_E_EVT_SERVERCONF_ADDATTENDEE_RESULT,      /**< 添加与会者结果 */
    CALL_E_EVT_SERVERCONF_REFRESHLIST,              /**< 刷新与会者列表 */
    CALL_E_EVT_SERVERCONF_SUBJECT,              /**< 上报会议主题*/
    CALL_E_EVT_SERVERCONF_CHAIRMAN_NUM,              /**< 上报主席号码*/
    CALL_E_EVT_SERVERCONF_DATACONF_PARAM,    /* 上报数据会议相关参数 */
    CALL_E_EVT_SERVERCONF_MODIFYATTENDEE_RESULT,   /**< 修改与会者发言权结果 */
    CALL_E_EVT_SERVERCONF_DROPATTENDEE_RESULT,      /**< 踢出与会者结果 */
    CALL_E_EVT_SERVERCONF_END_RESULT,                /**< 结束会议结果 */
    CALL_E_EVT_SERVERCONF_ATTENDEEKICKED,            /**< 与会者被踢出 */
    CALL_E_EVT_SERVERCONF_ENDED,                      /**< 会议被结束 */
    CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_SUCCESS,   /**< 与会者加入成功 */
    CALL_E_EVT_SERVERCONF_ACCESSCODEJOINED_SUCCESS,   /**< 接入码呼叫加入，与会者加入成功 */
    CALL_E_EVT_SERVERCONF_ATTENDEEJOINED_FAILED,   /**< 与会者加入失败 */
    CALL_E_EVT_SERVERCONF_ATTENDEEQUIT,              /**< 与会者退出 */
    CALL_E_EVT_SERVERCONF_ADDRESSOR,                 /**< 显示发言人 */
    CALL_E_EVT_SERVERCONF_BETRANSFERTOCONF,        /**< 被转会议 */
    CALL_E_EVT_SERVERCONF_TRANSFERTOCONF_SUCCESS,  /**< 转会议成功 */
    CALL_E_EVT_SERVERCONF_TRANSFERTOCONF_FAILED,   /**< 转会议失败 */
    CALL_E_EVT_SERVERCONF_HOLD_SUCESS,                   /**< 保持会场成功*/
    CALL_E_EVT_SERVERCONF_HOLD_FAILED,                   /**< 保持会场失败 */
    CALL_E_EVT_SERVERCONF_UNHOLD_SUCESS,                 /**< 恢复会场成功 */
    CALL_E_EVT_SERVERCONF_UNHOLD_FAILED,                 /**< 恢复会场失败 */
    CALL_E_EVT_SERVERCONF_MUTE_STATUS_CHANGE,      /**< 会场静音状态变更 */
    CALL_E_EVT_SERVERCONF_LOCK_STATUS_CHANGE,      /**< 会场锁定状态变更 */ 

    CALL_E_EVT_PICKUP_NOTIFY,                                            /**< UC2.0 同组代答通知/取消*/
    CALL_E_EVT_FORWARD_RESULT,                /**< 前转呼叫的结果*/
    CALL_E_EVT_IMS_FORWARD_RESULT,                /**< IMS被前转的目的号码结果*/
    
    CALL_E_EVT_CALL_LOGOUT_NOTIFY,         /**通知界面logout**/

    CALL_E_EVT_TURN_CALL_NOTIFY,/*通知界面，手机分机，分机接听、挂断 */

    CALL_E_EVT_SUB_BLF_RESULT_NOTIFY, /*BLF订阅结果 */
    CALL_E_EVT_SUB_RLS_RESULT_NOTIFY, /*RLS订阅结果 */
    CALL_E_EVT_CALL_CALLOUT_TIMEOUT,  /**呼出超时*/
    CALL_E_EVT_CALL_REPORTED_CALLINFO,/*语音质量上报**/

    CALL_E_EVT_CALL_CLEAN_SCALINE,                /**<清除共享线路状态*/
    CALL_E_EVT_UM_MSG_NOTIFY,           /**UM 事件定义*/
    CALL_E_EVT_CALL_INTERCOM_NUMBER,    /** 上报界面AA推送的intercom号码 */
    CALL_E_EVT_CALL_CALLPARK_SUCCESS,
    CALL_E_EVT_CALL_183_BUSY,       /**通话收到183busy*/
    CALL_E_EVT_CALL_PICKUP_REMOTE_INFO,       /**200ok中携带代答主叫方信息*/
    CALL_E_EVT_CALL_ACB_LIST_NOTIFY,       /**回呼列表通知*/
    CALL_E_EVT_CALL_PICKUP_INTERCOM_SUCCESS,
    CALL_E_EVT_CALL_PICKUP_INTERCOM_FAILED,
    CALL_E_EVT_CALL_INTERCOM_BEPICKUP,  /** intercom 被pick up 事件*/
    CALL_E_EVT_CALL_UPATE_REMOTEINFO,   /** 更新远端号码信息  */
    CALL_E_EVT_CALL_SRTP_STATE,         /** SRTP开启或关闭 */

    CALL_E_EVT_CALL_PINCODE_VALID,       /*通话中是否启用 PinCode */
    CALL_E_EVT_CALL_PINCODE_OK,          /*密码验证通过 */
    CALL_E_EVT_CALL_PINCODE_ERROR,       /*密码验证失败，需重新输入 */

    CALL_E_EVT_CALL_CALLACCEPTED_RMTCTRL,       /* 对端回复 200 OK 带 P-Notification: Callee Ctrl */
    CALL_E_EVT_CALL_CALL_REINVITED,             /* Call接受对端的Reinvite后 向上报告 */

    CALL_E_EVT_SET_IPT_SERVICE_BATCH_SUCCESS,  /** 批量登记业务成功  */
    CALL_E_EVT_SET_IPT_SERVICE_BATCH_FAILED,   /** 批量登记业务失败  */

    CALL_E_EVT_SET_CALL_LIMIT_ON_LOCKED,       /* 登记密码限呼失败(被锁定) */

    CALL_E_EVT_SET_CALL_LIMIT_OFF_LOCKED,      /* 取消密码限呼失败(被锁定) */

    CALL_E_EVT_SERVERCONF_MERGER_RESULT,       /* 合并会议结果 */
    CALL_E_EVT_SERVERCONF_SPLIT_RESULT,        /* 拆分会议结果 */
    CALL_E_EVT_ACCOUNT_STATUS_CHANGE,          /**账号状态变更 */
    CALL_E_EVT_MESSAGE_RELOGIN_REQUEST,        /** 收到relogin的message后通知界面重新AA登录 */

    CALL_E_EVT_CALL_ONEKEY_TO_WM_ON_CALL_SUCCESS,
    CALL_E_EVT_CALL_ONEKEY_TO_WM_ON_CALL_FAIL,

    CALL_E_EVT_CALL_CALLPARK_FAILED,           /* 驻留失败 */

    CALL_E_EVT_SERVERCONF_CONNECT_ONEKEY_TO_CONF_RESULT, /**< 一键加入会议结果 */
    CALL_E_EVT_SERVERCONF_VIDEOCONF_CREATEWND_RESULT,   /**< 视频会议创建窗口结果*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_CREATEVIDEO_MEETING_FAILED, /** 创建视频会议失败*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_LEAVECONF_RESULT,   /** < 视频会议主动离开会议结果*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_ATTEND_JOINED_CONF,   /** < 视频会议成员加入会议*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_END_CONF,      /** < 视频会议结束*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_BEKICKOUT_CONF,      /** < 视频会议中被主席踢出*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_LEAVE_CONF,      /** < 视频会议中有与会者退出*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_STATUS_CHANGE,    /**<视频会议中与会者包含自己的视频状态改变通知*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_REQUEST_CHANGE,   /**< 视频会议中视频被其他与会者请求开启/关闭*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_DEVICE_STATUS,    /**<视频会议中与会者包含自己的视频设备状态改变通知: 拔插*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_JOINCHANNEL,          /** 视频加入到高低流时的反馈触发条件：加入到高低流*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_DISCONNECT,          /** 视频网络失去连接*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_VIDEO_RECONNECT,     /** 视频网络重新连上*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_USERDEVICE_STATUSCHANGE,     /** 视频发送者设备状态改变(暂停或是取消暂停)*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_WARNING_FLOWCONTROL,    /** 流控告警(当前视频参数下，还需要流控，请关闭视频的提示)*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_NOTIFY_FLOWCONTROL,     /** 流控视频分辨率更改通知*/
    CALL_E_EVT_SERVERCONF_VOICECONF_TO_VIDEOCONF_SUCCESS,   /**< 音频会议转视频会议成功 */
    CALL_E_EVT_SERVERCONF_VOICECONF_TO_VIDEOCONF_FAILED,    /**< 音频会议转视频会议失败*/
    CALL_E_EVT_SERVERCONF_VIDEO_ON_FIRST_KEYFRAME,          /**< 关键帧通知*/
    CALL_E_EVT_SERVERCONF_VIDEOCONF_NET_STATUS,             /**< 网络状态通知*/
    
    CALL_E_EVT_MEETING_MSG_NOTIFY,           /**会议事件定义*/

    CALL_E_EVT_GET_MEETING_CONF_RESULT,     /** 获取会议列表结果*/
    CALL_E_EVT_GET_MEETING_CONF_XML_RESULT,     /** 获取会议XML 文件结果*/

    CALL_E_EVT_SIP_AUTH_INFO_WRITTEN,
    CALL_E_EVT_SWITCH_DND_SUCCESS,           /*切换DND模式成功，add by l00214300@2014-3-7 */
    CALL_E_EVT_SWITCH_DND_FAIL,              /*切换DND模式失败，add by l00214300@2014-3-7 */
    CALL_E_EVT_CALL_RECORDINFO_NOTIFY,

    /*TC专用通知*/
    CALL_E_EVT_SPKDEV_MUTE_CHANGE,           /*扬声器设备静音状态变化 iMute 当前静音状态 0当前状态为非静音  非0 当前状态为静音*/
    CALL_E_EVT_MICDEV_MUTE_CHANGE,           /*麦克风设备静音状态变化 iMute 当前静音状态 0当前状态为非静音  非0 当前状态为静音*/
    CALL_E_EVT_VMTC_VERSION_INFO,            /*VMTC版本信息 uiVerInfo 版本比较结果 0:版本兼容 1:VM版本老 2:TC版本老 */
    CALL_E_EVT_VMTC_DISCONNECT,              /*VMTC断开连接通知 uiInfo 断开连接信息*/
    CALL_E_EVT_VMTC_CONNECTOK,               /*VMTC连接成功通知 uiInfo 连接成功信息*/

    CALL_E_EVT_SYN_MISSCALL,                   /* 联动通话记录同步 */
    CALL_E_EVT_HUNTGROUP_STATUS_CHANGE,
    CALL_E_EVT_PAGING_INCOMING,
    CALL_E_EVT_PAGING_ENDED,

    CALL_E_EVT_BUTT
} CALL_E_CALL_EVENT;




/** SIP账户注册状态 */
typedef enum tagCALL_E_REG_STATE
{
    CALL_E_REG_STATE_UNREGISTER,     /**< SIP账户未注册 */
    CALL_E_REG_STATE_REGISTERING,    /**< SIP账户注册中 */
    CALL_E_REG_STATE_DEREGISTERING,  /**< SIP账户注销中 */
    CALL_E_REG_STATE_REGISTERED,     /**< SIP账户已注册 */
    CALL_E_REG_STATE_BUTT            /**< SIP账户无效状态 */
} CALL_E_REG_STATE;

/** 呼叫类型 */
typedef enum tagCALL_E_CALL_TYPE
{
    CALL_E_CALL_TYPE_IPAUDIO,        /**< IP语音呼叫 */
    CALL_E_CALL_TYPE_IPVIDEO,         /**< IP视频呼叫 */
    CALL_E_CALL_TYPE_BUTT            /**< 无效类型呼叫 */
} CALL_E_CALL_TYPE;



/** 呼叫基本状态 */
typedef enum tagCALL_E_CALL_STATE
{
    CALL_E_CALL_STATE_IDLE,    /**< 呼叫空闲态 */
    CALL_E_CALL_STATE_IN,       /**< 呼叫呼入态 */
    CALL_E_CALL_STATE_OUT,    /**< 呼叫呼出态 */
    CALL_E_CALL_STATE_LIVE,   /**< 呼叫通话态 */
    CALL_E_CALL_STATE_HOLD,  /**< 呼叫保持态 */
    CALL_E_CALL_STATE_END,    /**< 呼叫结束态 */
    CALL_E_CALL_STATE_BUTT   /**< 呼叫无效态 */
} CALL_E_CALL_STATE;

/** 设备类型 */
typedef enum tagCALL_E_DEVICE_TYPE
{
    CALL_E_CALL_DEVICE_MIC,         /* 麦克风设备 */
    CALL_E_CALL_DEVICE_SPEAK,       /* 扬声器设备 */
    CALL_E_CALL_DEVICE_VIDEO,       /* 视频设备 */
    CALL_E_CALL_DEVICE_BUTT         /* 无效设备 */
} CALL_E_DEVICE_TYPE;

/**振铃类型，add by w0213797 */
typedef enum tagCALL_E_CALL_ALERTTYPE
{
    CALL_E_CALL_ALERTTYPE_COMMON = 0x1,        /**< 普通振铃 */
    CALL_E_CALL_ALERTTYPE_INTERNAL,        /**< 群内 */
    CALL_E_CALL_ALERTTYPE_EXTERNAL,        /**< 群外 */
    CALL_E_CALL_ALERTTYPE_NETWORK,        /**< 网络彩铃 */

    /* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/1/29] [zhanglusha 00219468]]
       修改原因: 经理秘书增强_来电静铃 */
    CALL_E_CALL_ALERTTYPE_SILENCE,        /**< 来电静铃 */
    /* END   add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/1/29] [zhanglusha 00219468]] */
    CALL_E_CALL_ALERTTYPE_WAKEUP,
   /* BEGIN add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] 
      修改原因: huntgroup铃声 */
   CALL_E_CALL_ALERTYPE_HUNTGROUP,
   /* END   add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] */

    CALL_E_CALL_ALERTTYPE_BUTT = 0x0
} CALL_E_CALL_ALERTTYPE;


/** 上报给界面的语言留言类型 */
typedef enum tagCALL_E_MSG_WAIT_TYPE
{
    CALL_E_MSG_WAIT_TYPE_VOICE = 0,    /**< 语音消息 */
    CALL_E_MSG_WAIT_TYPE_VIDEO,        /**< 视频消息 */
    CALL_E_MSG_WAIT_TYPE_FAX,          /**< 传真消息 */
    CALL_E_MSG_WAIT_TYPE_PAGER,        /**< 页面信息 */
    CALL_E_MSG_WAIT_TYPE_MULTIMEDIA,   /**< 媒体消息 */
    CALL_E_MSG_WAIT_TYPE_TEXT,         /**< 文本消息 */
    CALL_E_MSG_WAIT_TYPE_VITRUALVM,    /**< 虚拟语音留言消息 */
    CALL_E_MSG_WAIT_TYPE_BUTT          /**< 未知消息 */
} CALL_E_MSG_WAIT_TYPE;

/* 会议角色 */
typedef enum tagCALL_E_CONF_ROLE
{
    CALL_E_CONF_ROLE_ATTENDEE,         /* 与会者 */
    CALL_E_CONF_ROLE_CHAIRMAN,         /* 主席方 */
    CALL_E_CONF_ROLE_CONFCHAIN,        /* 会议(合并会议业务) */
    CALL_E_CONF_ROLE_BUTT
} CALL_E_CONF_ROLE;

/* 服务器会议与会者状态 */
typedef enum tagCALL_E_CONF_STATE
{
    CALL_E_CONF_ATTENDEE_INVITING,              /* 邀请中  */
    CALL_E_CONF_ATTENDEE_INVITE_FAIL,           /* 邀请失败  */
    CALL_E_CONF_ATTENDEE_ADD_FAIL,              /* 添加失败  */
    CALL_E_CONF_ATTENDEE_INCONF,                /* 会议中  */
    CALL_E_CONF_ATTENDEE_OUT,                   /*DTS2012111404123*/
    CALL_E_CONF_ATTENDEE_STATE_BUTT
} CALL_E_CONF_ATTENDEE_STATE;





/** 业务权限业务列表注意一定要  与CALL_S_SERVICERIGHT_CFG 对应*/
typedef enum tagCALL_E_SERVICE_RIGHT_TYPE
{
    CALL_E_SERVICE_RIGHT_TYPE_NULL = -1,
    CALL_E_SERVICE_RIGHT_TYPE_ABBRDIAL = 0,                                     /**< 缩位拨号 */
    CALL_E_SERVICE_RIGHT_TYPE_CTD,                                           /* 0 点击呼叫 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLDEFLECTION,                               /* 1 呼叫偏转业务 */
    CALL_E_SERVICE_RIGHT_TYPE_ATTENDANT,                                     /* 2 话务员  */
    CALL_E_SERVICE_RIGHT_TYPE_SECRETARYSERVICE,                             /* 3 秘书业务 */
    CALL_E_SERVICE_RIGHT_TYPE_SECRETARYSTATIONSERVICE,                     /* 4 秘书台 */
    /*CALL_E_SERVICE_RIGHT_TYPE_ANONYMOUSCALLREJECTION, */                       /* 匿名呼叫拒绝  */
    CALL_E_SERVICE_RIGHT_TYPE_GROUPPICKUP,                                   /* 5 同组代答 */
    CALL_E_SERVICE_RIGHT_TYPE_DESIGNATEPICKUP,                               /* 6 指定代答 */
    CALL_E_SERVICE_RIGHT_TYPE_ACB,                                            /* 7 自动回叫业务 */
    CALL_E_SERVICE_RIGHT_TYPE_RECORDING,                                     /* 8 录音 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLTRANSFER,                                  /* 9 呼叫转接 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLPARK,                                      /* 10 呼叫预留 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLHOLD,                                      /* 11 呼叫保持 */
    /*CALL_E_SERVICE_RIGHT_TYPE_BARGEININSERT,*/                                /* 强插 */
    /*CALL_E_SERVICE_RIGHT_TYPE_BARGEINDISCONNECT,*/                            /* 强拆  */
    /*CALL_E_SERVICE_RIGHT_TYPE_BARGEINOVERRIDE, */                             /* 强替 */
    /*CALL_E_SERVICE_RIGHT_TYPE_BARGEINMONITOR, */                              /* 【*禁用词汇*】 */
    CALL_E_SERVICE_RIGHT_TYPE_DONOTDISTURB,                                 /* 12 免打扰 */
    CALL_E_SERVICE_RIGHT_TYPE_THREEPARTYCONFERENCE,                         /* 13 三方通话 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_UNCONDITIONAL,                  /* 14 无条件转移 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_ONBUSY,                         /* 15 遇忙转移 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_NOREPLY,                        /* 16 无应答转移 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_OFFLINE,                        /* 17 离线转移 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_UNCONDITIONAL,    /* 18 无条件转语音邮箱 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_ONBUSY,            /* 19 遇忙转语音邮箱 */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_NOREPLY,           /* 20 无应答转语音邮箱 */
    /*CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOFAXMAILBOX_UNCONDITIONAL, */      /* 无条件转传真  */
    CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDINGTOVOICEMAILBOX_OFFLINE,        /* 21 离线转语音邮箱 */
    /*CALL_E_SERVICE_RIGHT_TYPE_DATACONFERENCE, */                                /*  数据会议 */
    /*CALL_E_SERVICE_RIGHT_TYPE_FILETRANSFER, */                                  /*  文件传输 */
    /*CALL_E_SERVICE_RIGHT_TYPE_VIDEOCALL,  */                                    /*  视频通话功能 */
    CALL_E_SERVICE_RIGHT_TYPE_VOICECONFERENCE,                                /* 22 语音会议 */
    CALL_E_SERVICE_RIGHT_TYPE_CORPORATEDIRECTORY,                             /* 23 企业通讯录 */
    CALL_E_SERVICE_RIGHT_TYPE_INDIVIDUALDIRECTORY,                            /* 24 个人通讯录 */
    /*CALL_E_SERVICE_RIGHT_TYPE_INSTANTMESSAGE,*/                                  /* 即时消息 */
    CALL_E_SERVICE_RIGHT_TYPE_TURNPHONE,                                       /* 25 一键转接 */
    CALL_E_SERVICE_RIGHT_TYPE_VOICECALL,                                       /* 26 音频通话功能 */
    /*CALL_E_SERVICE_RIGHT_TYPE_CREATEGROUP,*/                                     /* 创建组     */
    /*CALL_E_SERVICE_RIGHT_TYPE_NOTIFICATION,*/                                    /* 通知     */
    /*CALL_E_SERVICE_RIGHT_TYPE_GROUPMESSAGE,*/                                    /*  群发消息     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MCTC,  */                                          /*  移动终端即时会议     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MCTD,  */                                          /*  移动终端点击呼叫     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEVOICECALL, */                                /*  手机/IPAD客户端语音呼叫     */
    /*CALL_E_SERVICE_RIGHT_TYPE_WEBVOICECALL,    */                                /*  WEB客户端语音呼叫     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEDIGITALCONFERENCE, */                        /* 手机客户端数据会议     */
    /*CALL_E_SERVICE_RIGHT_TYPE_IPADDIGITALCONFERENCE,  */                         /* IPAD客户端数据会议     */
    /*CALL_E_SERVICE_RIGHT_TYPE_WEBDIGITALCONFERENCE, */                           /* WEB客户端数据会议     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEVIDEO,         */                            /*  手机/IPAD客户端视频     */
    /*CALL_E_SERVICE_RIGHT_TYPE_WEBVIDEO,         */                               /*  WEB客户端视频      */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEFILETRANSFER,  */                            /*  手机/IPAD客户端文件传输      */
    /*CALL_E_SERVICE_RIGHT_TYPE_WEBFILETRANSFER,     */                            /*  WEB客户端文件传输      */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEDIRECTORYRELATIONSHIP, */                    /* 手机通信录关联     */
    /*CALL_E_SERVICE_RIGHT_TYPE_MOBILEBOOKINGCONFERENCE,  */                       /* 手机客户端预约会议     */
    /*CALL_E_SERVICE_RIGHT_TYPE_VIDEOCONFERENCE,    */                             /* 视频会议     */
    /*CALL_E_SERVICE_RIGHT_TYPE_BINDOCSCLIENT,      */                             /* 绑定OCS客户端     */
    CALL_E_SERVICE_RIGHT_TYPE_EXTENSIONMOBILITY,                              /* 27 分机携带,AA不推送，WEB上修改 */
    CALL_E_SERVICE_RIGHT_TYPE_SUBREGSTATE,                                     /* 28 分机携带时订阅业务权限,AA不推送，WEB上修改 */
    CALL_E_SERVICE_RIGHT_TYPE_BLF,                                              /* 29 BLF, AA不推送，WEB上修改 */
    /* BEGIN add: [[DTS2012101703429] [2012/10/30] [caoruihong 00205112]] */
    CALL_E_SERVICE_RIGHT_TYPE_PRESENCE,                                             /*30 状态呈现 */
    /* END   add: [[DTS2012101703429] [2012/10/30] [caoruihong 00205112]] */
    CALL_E_SERVICE_RIGHT_TYPE_INTERCOM,                                          /* 31 intercom业务 */

    /* BEGIN add: [[V100R001C50] [IR.IPT.025] [2013/12/3] [WuDingyuan]]
       修改原因: 新需求:拒绝前转来电 */
    CALL_E_SERVICE_RIGHT_TYPE_DICF,                                    /* 拒绝前转来电 */
    /* END   add: [[V100R001C50] [IR.IPT.025] [2013/12/3] [WuDingyuan]] */
    CALL_E_SERVICE_RIGHT_TYPE_ABSENT,                                  /* 缺席业务 */

    /* BEGIN add: [[V100R001C50] [IR.IPT.002] [2013/12/13] [zhanglusha 00219468]]
       修改原因: VM语音邮箱 */
    CALL_E_SERVICE_RIGHT_TYPE_TURN_VM,                                 /* 一键转语音邮箱*/
    /* END   add: [[V100R001C50] [IR.IPT.002] [2013/12/13] [zhanglusha 00219468]] */

    CALL_E_SERVICE_RIGHT_TYPE_HOT_LINE,                                 /* [98]热线业务 */

    /* BEGIN add: [[IR.IPT.034] [2013/12/18] [zhanglusha 00219468]]
       修改原因: 新需求:恶意呼叫跟踪 */
    CALL_E_SERVICE_RIGHT_TYPE_MCID,                                    /* [99]恶意呼叫跟踪 */
    /* END   add: [[IR.IPT.034] [2013/12/18] [zhanglusha 00219468]] */

    /* BEGIN add: [[IR.IPT.013] [2013/12/26] [zhanglusha 00219468]]
       修改原因: 密码限呼业务权限 */
    CALL_E_SERVICE_RIGHT_TYPE_CALL_LIMIT,                               /* [02]密码限呼 */
    /* END   add: [[IR.IPT.013] [2013/12/26] [zhanglusha 00219468]] */

    CALL_E_SERVICE_RIGHT_TYPE_CALL_WAIT,                                /* [28]182呼叫等待 */

    CALL_E_SERVICE_RIGHT_TYPE_VVM,                                      /* [112]可视化语音邮箱 */
    CALL_E_SERVICE_RIGHT_TYPE_BARGE,                                    /* 强插*/
    CALL_E_SERVICE_RIGHT_TYPE_LBS,                                     /* [89]LBS*/

    /* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR-0000159474] [2013/1/18] [zhanglusha 00219468]]
       修改原因: 经理秘书增强 */
    CALL_E_SERVICE_RIGHT_TYPE_PRIVACY,                                 /* privacy业务 */
    CALL_E_SERVICE_RIGHT_TYPE_HOLD_PRIVATE,                            /* 私人保持业务 */
    CALL_E_SERVICE_RIGHT_TYPE_BRIDGE,                                  /* bridge业务 */
    CALL_E_SERVICE_RIGHT_TYPE_RESUME,                                  /* resume业务 */
    /* END   add: [[eSpace 7900 V100R001C02B010] [IR-0000159474] [2013/1/18] [zhanglusha 00219468]] */
    CALL_E_SERVICE_RIGHT_TYPE_VOICE_MAIL,                                    /*[97] Message Waiting */
    /* BEGIN add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] 
       修改原因: huntgroup业务权限 */
    CALL_E_SERVICE_RIGHT_TYPE_HUNTGROUP,                               /** huntgroup权限 */
    CALL_E_SERVICE_RIGHT_TYPE_VIRTUALVM,                               /** 虚拟语音邮箱 */
    /* END   add: [[V200R002C00] [V200R002C00] [2014/3/18] [h00206999]] */
    CALL_E_SERVICE_RIGHT_TYPE_UC2X_VOICECONFERENCE,                    /* 50 UC2.X立即会议 */

#ifdef __ESPACE_7900_C03__
    CALL_E_SERVICE_RIGHT_TYPE_ONENUMBER,                                        /* 一号通 */
    CALL_E_SERVICE_RIGHT_TYPE_ARLERT_SILCNCE,                          /* 来电静铃 */
    CALL_E_SERVICE_RIGHT_TYPE_ANONYMOUS,                               /**匿名呼叫 */
    CALL_E_SERVICE_RIGHT_TYPE_MULTIPLEAPPEARANCESERVICE,               /*[103] Multiple Appearance Service*/
#endif

    CALL_E_SERVICE_RIGHT_TYPE_BUTT
} CALL_E_SERVICE_RIGHT_TYPE;

/*本地信号音枚举*/
typedef enum  enumAUDIO_CompoundVoice
{
    COMPOUND_E_NONE   = 0,  /* 无信号音 */
    COMPOUND_E_BUSY,        /* 忙音 */    
    COMPOUND_E_BACK,        /* 回铃音 */
    COMPOUND_E_DIAL,        /* 拨号音 */
    COMPOUND_E_WAIT,        /* 呼等音 */
    COMPOUND_E_TIP,         /* 提示音 */
    COMPOUND_E_WARN,        /* 警告音 */
    COMPOUND_E_LEAVE,       /* 会场离开音 */
    COMPOUND_E_UFWD,      /* 无条件前转特殊拨号音 */

    COMPOUND_E_DTMF0,   /* dtmf按键0 */
    COMPOUND_E_DTMF1,   /* dtmf按键1 */
    COMPOUND_E_DTMF2,   /* dtmf按键2 */
    COMPOUND_E_DTMF3,   /* dtmf按键3 */
    COMPOUND_E_DTMF4,   /* dtmf按键4 */
    COMPOUND_E_DTMF5,   /* dtmf按键5 */
    COMPOUND_E_DTMF6,   /* dtmf按键6 */
    COMPOUND_E_DTMF7,   /* dtmf按键7 */
    COMPOUND_E_DTMF8,   /* dtmf按键8 */
    COMPOUND_E_DTMF9,   /* dtmf按键9 */ 
    COMPOUND_E_DTMFSTAR, /* dtmf按键'*' */
    COMPOUND_E_DTMFJIN,  /* dtmf按键'#' */
    COMPOUND_E_DTMFA,    /* dtmf按键A */
    COMPOUND_E_DTMFB,    /* dtmf按键B */
    COMPOUND_E_DTMFC,    /* dtmf按键C */
    COMPOUND_E_DTMFD,    /* dtmf按键D */
    COMPOUND_E_DTMFFLASH, /* dtmf按键FLASH */
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

/** 支持的视频协议类型 */
typedef enum tagCALL_E_VIDEO_CAP
{
    CALL_E_VIDEO_CAP_H264 = 0,
    CALL_E_VIDEO_CAP_H263, 
    CALL_E_VIDEO_CAP_BUTT
}CALL_E_VIDEO_CAP;



/** DTMF 传输模式 */
typedef enum
{
    CALL_E_DTMF_MODE_TRANSPARENT = 0,        /**< 透传模式 */
    CALL_E_DTMF_MODE_RFC2833,            /**< RFC2833模式(自动协商) */
    CALL_E_DTMF_MODE_CONST2833,          /**< 强制2833模式 */
    CALL_E_DTMF_MODE_INFO,               /**< INFO模式 */    
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

/**音频音量输出类型*/
typedef enum
{
    CALL_E_AO_DEV_SPEAKER = 0,       /**< 扬声器 */
    CALL_E_AO_DEV_BLUETOOTH,         /**< 蓝牙输出 */
    CALL_E_AO_DEV_EARPIECE,  /**< 手柄输出 */
    CALL_E_AO_DEV_HEADSET,           /**< 3.5mm耳机输出 */
    CALL_E_AO_DEV_HDMI,           /**< HDMI输出 */
    CALL_E_AO_DEV_USB,               /**< USB输出 */
    //MPROC_E_AO_DEV_HEADSET,         /**< 耳麦输出 */
    CALL_E_AO_DEV_SPEAKERRING,       /**< 扬声器铃音(获取音量值时候用到) */
    CALL_E_AO_DEV_BLUETOOTHRING,     /**< 蓝牙输出铃音(获取音量值时候用到) */
    CALL_E_AO_DEV_HDMIRING,           /**< 手柄输出 */
    CALL_E_AO_DEV_USBRING,           /**< USB输出铃音(获取音量值时候用到) */
    CALL_E_AO_DEV_BUTT               /**< 无效值 */
} CALL_E_AO_DEV;


//音频路由同步TUP ENUM_TUP_AUDDEV_ROUTE
typedef enum tagCALL_E_AUDDEV_ROUTE
{
    CALL_E_AUD_DEV_ROUTE_DEFAULT         = 0x0,                    //保留值，设置不生效
    CALL_E_AUD_DEV_ROUTE_LOUDSPEAKER     = 0x1,                    //扬声器 ，支持输入输出
    CALL_E_AUD_DEV_ROUTE_BLUETOOTH       = 0x2,                    //蓝牙耳机 ，支持输入输出
    CALL_E_AUD_DEV_ROUTE_EARPIECE        = 0x3,                    //听筒 手柄设备，支持输入输出
    CALL_E_AUD_DEV_ROUTE_HEADSET         = 0x4,                    //3.5毫米耳机 ，支持输入输出
    CALL_E_AUD_DEV_ROUTE_SUBDEFAULT      = 0x5,                    //保留值，设置不生效
    CALL_E_AUD_DEV_ROUTE_HDMI            = 0x6,                    //HDMI,支持输出
    CALL_E_AUD_DEV_ROUTE_USB             = 0x7,                    //USB耳机 ，支持输入输出
    CALL_E_AUD_DEV_ROUTE_MAX             = 0X8                     //无效值
} CALL_E_AUDDEV_ROUTE;

typedef enum tagCALL_E_REG_FAILOVER_MODE{
    CALL_E_REG_FAILOVER_MODE_REGMASTER,        /**< 主-> 备 */
    CALL_E_REG_FAILOVER_MODE_REGALL,        /**< 主、备同时 */
    CALL_E_REG_FAILOVER_MODE_BUTT
}CALL_E_REG_FAILOVER_MODE;


/** 组网环境, 需要与cmo_enum.h中的HCS_E_SIP_NETWORK_MODE定义保持一致 */
typedef enum tagCALL_E_NET_ENVIRONMENT
{
    CALL_E_NET_UC1X = 0,        /** UC1.0环境*/
    CALL_E_NET_UC2X,            /** UC2.0环境*/
    CALL_E_NET_OTHERS,          /** 其他环境，兼容老版本设为2 */
    CALL_E_NET_ASTERISK,        /** Asterisk环境*/
    CALL_E_NET_BROADSOFT,       /** Broadsoft环境*/
    CALL_E_NET_IPCC,            /** IPCC环境  */
    CALL_E_NET_IMSUC_MIX,       /** IMS+UC */
    CALL_E_NET_TE,              /* 智真 */
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
    CALL_E_SEVICERIGHT_LACK = 0,        /* 没权限 */
    CALL_E_SEVICERIGHT_HAVE         /* 有权限 */
} CALL_E_SEVICERIGHT_STATUS;

typedef enum
{
    CALL_E_SERVERCONF_AUDIO = 1,        /* 会场类型：语音 */
    CALL_E_SERVERCONF_DATA  = 3         /* 会场类型：数据+语音 */
} CALL_E_SERVERCONF_TYPE;


typedef enum tagCALL_E_REFRESHVIEW_MIDEATYPE
{
    CALL_E_REFRESHVIEW_VIDEO = 2,     /**普通视频 */
    CALL_E_REFRESHVIEW_DATA = 3   /**辅流 */
} CALL_E_REFRESHVIEW_MIDEATYPE;


typedef enum tagCALL_E_REFRESHVIEW_EVENT
{
    CALL_E_LOCALVIEW_ADD = 1,     /**本地view添加 */
    CALL_E_LOCALVIEW_REMOVE   /**本地view删除 */
} CALL_E_REFRESHVIEW_EVENT;

/* 来电URI所带类型:普通来电,intercom,paging,需与SIP_E_URI_PARAMTYPE对应 */
typedef enum tagCALL_E_URI_PARAMTYPE
{
    CALL_E_URI_PARAM_NORAML,     /** 不携带参数 */
    CALL_E_URI_PARAM_INTERCOM,   /** intercom=true */
    CALL_E_URI_PARAM_PAGING,     /** paging=true */
    CALL_E_URI_PARAM_APPEARANCE_PRIVATE, /** appearance-private=true */
    CALL_E_URI_PARAM_BUTT
}CALL_E_URI_PARAMTYPE;


typedef enum tagCALL_E_VIDEOWND_TYPE
{
    CALL_E_VIDEOWND_CALLREMOTE = 0,                  /* 通话远端窗口 */
    CALL_E_VIDEOWND_CALLLOCAL,                  /* 通话本地窗口  */
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
    CALL_E_VIDEOWND_DISPLAY_ZOOM = 0,             /* 0:保持比例不变,加黑边,默认为此值 */
    CALL_E_VIDEOWND_DISPLAY_CUT,                  /* 1:保持比例不变,拉伸裁剪   */
    CALL_E_VIDEOWND_DISPLAY_FULL,                 /* 2:全部填满,不加黑边，不做裁剪   */
    CALL_E_VIDEOWND_DISPLAY_BUTT
} CALL_E_VIDEOWND_DISPLAY_TYPE;


/*******************************************************************************
 *   数据结构类型和联合体类型定义
 *******************************************************************************/
/** 装备测试*/
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
    TUP_UINT32 ulSipAccountID;                  /**< SIP账户ID */
    CALL_E_REG_STATE enRegState;                /**< SIP账户注册状态 */
    TUP_UINT32 ulReasonCode;                    /**< 注册失败的原因码 */
    TUP_INT8 acUserNum[CALL_D_MAX_USERNAME_LENGTH];   /**< SIP账户用户名 */
    TUP_INT8 acTelNum[CALL_D_MAX_LENGTH_NUM];   /**< SIP账户号码 */
} CALL_S_SIP_ACCOUNT_INFO;

typedef struct tagCALL_S_CALL_PARAMS
{
    TUP_UINT32 ulLineId;
    TUP_UINT32 ulCallType;
    TUP_UINT32 ulAccountId;
    TUP_UINT32 ulReserved;
    TUP_UINT32 ulCallId; //可做输入输出参数
    TUP_INT8 acTelNum1[CALL_D_MAX_LENGTH_NUM];
    TUP_INT8 acTelNum2[CALL_D_MAX_LENGTH_NUM];
    TUP_VOID* pReserved;
}CALL_S_CALL_PARAMS;

typedef struct tagCALL_S_CALL_STATE_INFO
{
    TUP_UINT32 ulSipAccountID;              /**< 通话所属线路ID */
    TUP_UINT32 ulCallID;                    /**< 通话ID */
    CALL_E_CALL_TYPE enCallType;            /**< 呼叫类型 */
    CALL_E_CALL_STATE enCallState;          /**< 通话状态 */
    TUP_INT8 acTelNum[CALL_D_MAX_LENGTH_NUM];   /**<  来电号码 */
    TUP_INT8 acDisplayName[CALL_D_MAX_DISPLAY_NAME];  /**< 来电姓名 */
    TUP_UINT32 ulReasonCode;       /**< 失败原因码 endcall */ 
    TUP_BOOL bIsIn;                         /**< 标识该路通话是否为呼入 */
    TUP_BOOL bIsPassiveEnd;                 /**< 标识该路呼叫是否远端挂断 */
    CALL_E_CALL_ALERTTYPE enAlertType;        /** 新增振铃类型，add by w00213797 */
    TUP_BOOL bIsAccept;                     /**< 呼叫是否已经接听标志 */
    TUP_BOOL bIsTimeout;                    /**< 呼叫超时标志，用例记录来电超时未接记录 */
    TUP_BOOL bIsInLocalConf;                /**< 标志是否加入本地会议 add by h00206999*/
    TUP_BOOL bIsInBridgeConf;               /**< 标识是否是进入bridge会议状态 */
    TUP_BOOL bCompletedElsewhere;               /**< 标识是否是不用计入未接来电的被结束来电 */
    TUP_BOOL bIsAutoAnswer;                /**新增， 呼叫是否自动接听标志  ，add by w00213797  */
    TUP_UINT32 ulAutoAnswerTime;            /** 新增，呼叫自动接听时间，add by w00213797 */
    TUP_UINT32 ulCause;           /* sip呼叫cause码 */
    TUP_CHAR szPresetMsg[CALL_D_MAX_PRESET_MSG_LENGTH];              /**< 预设消息 */
    TUP_BOOL bIsPaging;
    TUP_BOOL bHaveSDP;            /* 是否带有SDP */
}CALL_S_CALL_STATE_INFO;



typedef struct tagCALL_S_CALL_INFO
{
    CALL_S_CALL_STATE_INFO stCallStateInfo;     /**< 通话状态信息 */

    /* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/1/26] [zhanglusha 00219468]]
       修改原因: intercom业务 */
    CALL_E_URI_PARAMTYPE enUriType;   
    /* END   add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/1/26] [zhanglusha 00219468]] */
    TUP_BOOL bIsFwdCallForbidden;             /**< 服务器指示禁止本地前传,用于对接BROADSOFT服务器*/
    TUP_BOOL bIsFwdCall;
    TUP_INT8 acFwdFromNum[CALL_D_MAX_LENGTH_NUM];  /**<前转者号码 */
    TUP_INT8 acFwdFromName[CALL_D_MAX_DISPLAY_NAME];  /**< 前转者姓名 */

    /*为匹配沙特ATS服务器局内号码显示，解析PAI中的第二个URI（默认为TEL） */
    TUP_INT8 acTelNumTel[CALL_D_MAX_LENGTH_NUM];   /**<  来电号码 */
    TUP_INT8 acDisplayNameTel[CALL_D_MAX_LENGTH_NUM];  /**< 来电姓名 */
    /*为匹配沙特ATS服务器局内号码显示，解析PAI中的第二个URI（默认为TEL） */

    /*others*/
    TUP_BOOL bIsShareLine;
    TUP_UINT32 ulSCALineID;
    TUP_UINT32 ulBossLineID;
    TUP_BOOL   bIsReplace;                        /**< 是否替换线路 */
    TUP_UINT32 ulReplaceID;                     /**<咨询转，被 替换的原呼叫ID */
    TUP_CHAR acBossNum[CALL_D_MAX_LENGTH_NUM];
    TUP_UINT32 ulRmtCtrl;                        /* 是否对端控 */
    TUP_UINT32 ulSwitchId;                      /**PC联动一键切换*/

    TUP_BOOL bIsFocus;            /**是否带isfoucs标识，移动会议场景使用*/  
    TUP_INT8 acServerConfType[CALL_D_MAX_LENGTH_NUM];       /**会议类型，移动会议场景使用*/  
    TUP_INT8 acServerConfID[CALL_D_MAX_LENGTH_NUM];      /**会议ID, 移动会议场景使用*/
    TUP_UINT32 ulOrientType;    /** 移动视频横竖屏情况*/
    TUP_INT8 acLocalAddr[CALL_D_IP_LENGTH];   /**移动上报本地地址*/
    TUP_INT8 acRemoteAddr[CALL_D_IP_LENGTH];    /**移动上报远端地址*/
} CALL_S_CALL_INFO;

/*voice mail notify,*/
typedef struct tagCALL_S_MSG_INFO
{
    CALL_E_MSG_WAIT_TYPE enMsgType;     /**< 留言灯类型 */
    TUP_UINT32 ulNewMsgNum;             /**< 新消息个数 */
    TUP_UINT32 ulOldMsgNum;             /**< 旧消息个数 */
    TUP_UINT32 ulNewEmgMsgNum;          /**< 新紧急消息个数 */
    TUP_UINT32 ulOldEmgMsgNum;          /**< 旧紧急消息个数 */
    TUP_CHAR   aszSubscriber[CALL_D_MAX_LENGTH_NUM];               /**< 隶属的号码 */
} CALL_S_MSG_INFO;

typedef struct tagCALL_S_MSG_WAIT_INFOS
{
    TUP_UINT32 ulMsgCnt;                /**< 消息类型个数 */
    CALL_S_MSG_INFO astMsgInfos[CALL_D_MAX_MSGSUMMARY_NUM];        /**< 消息类型 */
} CALL_S_MSG_WAIT_INFOS;



typedef struct _CALL_CHANNEL_EMODEL_RESULT_STRU
{
    TUP_UINT8  ucSendMOSValidFlag;   /**< 发送方向MOS分有效标志,当通道未收到RTCP RR报文时，如下4个发送方向的MOS分参数都无效 */
    TUP_UINT8  ucRecvMOSValidFlag;   /**< 接收方向MOS分有效标志,当通道未收到任何报文或未达到计算周期(RTCP发送周期，5s)时，如下4个接收方向的MOS分参数都无效 */
    TUP_UINT16 uwResv;               /**< 保留位，保证4字节对齐 */

    TUP_UINT32 ulSendAverageMosQ;    /**< 发送方向MOS分平均值,用整数表示:4000等于4.000，取值范围[1000, 5000], 0xFFFFFFFF表示该参数无效 */
    TUP_UINT32 ulSendMaxMosQ;        /**< 发送方向MOS分最大值,用整数表示:4000等于4.000，取值范围[1000, 5000], 0xFFFFFFFF表示该参数无效 */
    TUP_UINT32 ulSendMinMosQ;        /**< 发送方向MOS分最小值,用整数表示:4000等于4.000，取值范围[1000, 5000], 0xFFFFFFFF表示该参数无效 */
    TUP_UINT32 ulSendCurMosQ;        /**< 发送方向MOS分当前值,用整数表示:4000等于4.000，取值范围[1000, 5000], 0xFFFFFFFF表示该参数无效 */

    TUP_UINT32 ulRecvAverageMosQ;    /**< 接收方向MOS分平均值,用整数表示:4000等于4.000，取值范围[1000, 5000], 0xFFFFFFFF表示该参数无效 */
    TUP_UINT32 ulRecvMaxMosQ;        /**< 接收方向MOS分最大值,用整数表示:4000等于4.000，取值范围[1000, 5000], 0xFFFFFFFF表示该参数无效 */
    TUP_UINT32 ulRecvMinMosQ;        /**< 接收方向MOS分最小值,用整数表示:4000等于4.000，取值范围[1000, 5000], 0xFFFFFFFF表示该参数无效 */
    TUP_UINT32 ulRecvCurMosQ;        /**< 接收方向MOS分当前值,用整数表示:4000等于4.000，取值范围[1000, 5000], 0xFFFFFFFF表示该参数无效 */
} CALL_CHANNEL_EMODEL_RESULT_STRU;

typedef struct tagCALL_S_AUDIO_STREAM_INFO
{
    TUP_BOOL bIsCalling;                        /**< 是否在通话中*/
    TUP_INT8 acEncodeProtocol[CALL_D_PROTOCOL_LENGTH];               /**< 编码协议*/
    TUP_INT8 acDecodeProtocol[CALL_D_PROTOCOL_LENGTH];               /**< 解码协议*/
    TUP_UINT32 ulChannelID;                     /**< 通道ID */
    TUP_UINT32 ulSendBitRate;                   /**< 发送比特率 */
    TUP_UINT32 ulRecvBitRate;                   /**< 接收比特率 */
    TUP_UINT32 ulSendTotalLostPacket;           /**< 发送方累计包损 */
    TUP_FLOAT fSendLossFraction;                /**< 发送方丢包率(%) */
    TUP_FLOAT fSendJitter;                      /**< 发送方平均抖动(ms) */
    TUP_FLOAT fSendDelay;                       /**< 发送方平均时延(ms) */
    TUP_UINT32 ulRecvTotalLostPacket;           /**< 接收方累计包损 */
    TUP_FLOAT fRecvLossFraction;                /**< 接收方丢包率(%) */
    TUP_FLOAT fRecvJitter;                      /**< 接收方平均抖动(ms) */
    TUP_FLOAT fRecvDelay;                       /**< 接收方平均时延(ms) */
    CALL_CHANNEL_EMODEL_RESULT_STRU stMosResult; /**< 语音mos值 */
    //del by chendk
    //HME_CHANNEL_EMODEL_RESULT_STRU  stMosResult;/**< 语音mos值 */
} CALL_S_AUDIO_STREAM_INFO, *CALL_S_AUDIO_STREAM_INFO_PTR;

typedef struct tagCALL_S_VIDEO_STREAM_INFO
{
    TUP_INT8 acEncodeName[CALL_MAX_CODEC_NAME_LEN];        /**< 编码名称*/
    TUP_INT8 acDecodeName[CALL_MAX_CODEC_NAME_LEN];        /**< 解码名称*/
    TUP_INT8 acEncoderSize[CALL_MAX_FRAMESIZE_LEN];        /**< 图像分辨率(编码)*/
    TUP_INT8 acDecoderSize[CALL_MAX_FRAMESIZE_LEN];        /**< 图像分辨率(解码)*/
    TUP_UINT32 ulSendFrameRate;                            /**< 视频帧率(编码)*/
    TUP_UINT32 ulRecvFrameRate;                            /**< 视频帧率(解码)*/
    TUP_UINT32 ulVideoSendBitRate;                        /**< 编码码率*/
    TUP_UINT32 ulVideoRecvBitRate;                        /**< 解码码率*/
    TUP_INT8 acEncoderProfile[CALL_MAX_PROFILE_LEN];        /**< 视频编码格式*/
    TUP_INT8 acDecoderProfile[CALL_MAX_PROFILE_LEN];        /**< 视频解码格式*/
    TUP_FLOAT fVideoSendLossFraction;                    /**< 发送方丢包率(%) */
    TUP_FLOAT fVideoSendJitter;                          /**< 发送方平均抖动(ms) */
    TUP_FLOAT fVideoSendDelay;                           /**< 发送方平均时延(ms) */
    TUP_FLOAT fVideoRecvLossFraction;                    /**< 接收方丢包率(%) */
    TUP_FLOAT fVideoRecvJitter;                          /**< 接收方平均抖动(ms) */
    TUP_FLOAT fVideoRecvDelay;                           /**< 接收方平均时延(ms) */
    TUP_UINT32 ulWidth;                                    /**< 视频分辨率-宽*/
    TUP_UINT32 ulHeight;                                   /**< 视频分辨率-高*/
} CALL_S_VIDEO_STREAM_INFO, *CALL_S_VIDEO_STREAM_INFO_PTR;

//会话中媒体总信息
typedef struct tagCALL_S_MEDIA_STREAM_INFO
{
    TUP_UINT32 uiCt; //会话级带宽 ct
    TUP_CHAR   szAudioCodec[CALL_D_MAX_CODEC_LIST_LEN+1]; /*会话协商出的所支持的音频编解码列表 "G722,PCMA,PCMU,G729,iLBC,telephone-event,red"*/
    TUP_CHAR   szVideoCodec[CALL_D_MAX_CODEC_LIST_LEN+1]; /*会话协商出的所支持的视频编解码列表 预留*/
}CALL_S_MEDIA_STREAM_INFO, *CALL_S_MEDIA_STREAM_INFO_PTR;

typedef struct tagCALL_S_STREAM_INFO
{
    CALL_S_MEDIA_STREAM_INFO stMediaStreamInfo;         /*会话级信息*/
    CALL_S_AUDIO_STREAM_INFO stAudioStreamInfo;         /*音频流信息*/
    CALL_S_VIDEO_STREAM_INFO stVideoStreamInfo;         /*视频流信息*/
    TUP_BOOL bIsIn;                                     /**< 标识该路通话是否为呼入 */
    TUP_BOOL bIsEndCall;                          /**< 标识是否为结束上报 */
    TUP_CHAR acLocalIP[CALL_D_IP_LENGTH];               /*本端IP*/
    TUP_CHAR acRemoteNum[CALL_D_MAX_LENGTH_NUM];        /*远端号码*/
    TUP_CHAR acLocalNum[CALL_D_MAX_LENGTH_NUM];         /*本端号码*/
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
    TUP_UINT32 ulConfID;//会议本地控制id                
    CALL_E_SERVERCONF_TYPE eConfType;  //服务器会场类型
    TUP_UINT32 ulCallID;
    TUP_UINT32 ulSipAccountID;  
    TUP_INT8 acUserNumber[CALL_D_MAX_LENGTH_NUM];
    TUP_INT8 acGroupUri[CALL_D_MAX_LENGTH_NUM];
    
    /** 服务器是否指示自动接听 add by k00175673 */
    TUP_UINT32 ulSvrAutoAnswer;          
    /** 服务器指示自动接听时间 add by k00175673 **/
    TUP_UINT32 ulSvrAutoAnswerTime;
    CALL_S_SCA_CALL_INFO stScaCallInfo; /* 用于在会议来电的时候上报经理秘书信息 */
} CALL_S_CONF_INFO;

//zhubin 202161 会场创建结果
typedef struct tagCALL_S_CONF_CREATE_RESULT
{
    TUP_UINT32 ulConfID;//会议本地控制id
    TUP_UINT32 ulResult;//创会结果
    CALL_E_SERVERCONF_TYPE eConfType;//服务器会场类型
    TUP_CHAR acPasscode[CALL_D_PASSCODE_LENGTH];
} CALL_S_CONF_CREATE_RESULT;

//zhubin 202161 数据会议入会相关参数
typedef struct tagCALL_S_DATACONF_PARAM
{
    TUP_UINT32          ulConfID;/**<会议本地控制id*/
    TUP_UINT32          ulCallID;/* 对应的CallID */
    CALL_E_CONF_ROLE    enRole;  /**<本地用户会议中角色*/
    TUP_CHAR            acDataConfID[CALL_D_DATACONF_PARAM_LENGTH];/**<服务器会场id*/
    TUP_CHAR            acAuthKey[CALL_D_DATACONF_PARAM_LENGTH]; /**<会场鉴权码*/
    TUP_CHAR            acPassCode[CALL_D_MAX_LENGTH_NUM];
    TUP_CHAR            acCmAddr[CALL_D_DATACONF_CMADDR_LENGTH];/**<U19网管地址及端口*/
    TUP_CHAR            acGroupUri[CALL_D_MAX_LENGTH_NUM];
    TUP_CHAR            acCharman[CALL_D_DATACONF_PARAM_LENGTH];         /**< 主持人UC号码*/
    TUP_CHAR            bP2PDataConf;   /* 是否点对点数据会议 */
} CALL_S_DATACONF_PARAM;

/* 与会者信息 */
typedef struct tagCALL_S_CONF_MEMBER
{
    TUP_CHAR acAttendeeNumber[CALL_D_MAX_LENGTH_NUM];   /* 号码 */
    TUP_CHAR acAttendeeFullNumber[CALL_D_MAX_LENGTH_NUM];   /*与会者长 号码 */
    CALL_E_CONF_ROLE enRole;                             /* 角色 */
    CALL_E_CONF_ATTENDEE_STATE enState;                  /* 状态 */
    TUP_UINT32 ulRight;                                  /* 发言权  1有  0无  */
    TUP_UINT32 ulAttendeeID;                             /* 与会者ID , 用于指明使用哪个会议，89 C50C00中暂时不使用*/
} CALL_S_CONF_MEMBER;

/* 最大发言人信息 */
typedef struct tagCALL_S_CONF_SPEAKER
{
    TUP_CHAR acFirstSpeakMem[CALL_D_MAX_LENGTH_NUM];  /* 号码 */
    TUP_CHAR acSecondSpeakMem[CALL_D_MAX_LENGTH_NUM];     /*与会者长 号码 */
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
    TUP_UINT32 ulRender;                 /*窗口句柄*/
    TUP_INT32 ulIndex;                   /*窗口序号*/
    TUP_UINT32 ulSessionID;             /*本地预览session值*/
    TUP_UINT32 ulRefCount;              /*使用引用计数*/
    TUP_UINT32 ulDisplayType;           /*显示模式CALL_E_VIDEOWND_DISPLAY_TYPE*/
    TUP_CHAR  acStartImage[CALL_D_MAX_LENGTH_NUM]; /*视频显示初始图像，必须为jpeg图像，且长宽都是8的倍数*/
} CALL_S_VIDEOWND_INFO, CALL_S_VIDEOCONFWND_INFO;



typedef enum tagCALL_E_VIDEOWND_CTRL_TYPE
{
    CALL_E_VIDEOWND_MOVE,                  /* 窗口移动包括Z序改变隐藏通过改变Z序 */
    CALL_E_VIDEOWND_CLOSE,              /* 窗口关闭  */
    CALL_E_VIDEOWND_ZOOM,               /* 窗口缩放  */
    CALL_E_VIDEOWND_DISPLAYTYPE,         /*显示模式  */
    CALL_E_VIDEOWND_CTRL_BUTT
} CALL_E_VIDEOWND_CTRL_TYPE;


/**CFG:MAJOR_TYPE
In the future, maybe need support multi-account, we can use the first 16bit as account
,use the second 16bit as major type.

*/
typedef enum tagCALL_E_CFG_MAJOR_TYPE
{
    CALL_E_CFG_CALLENV = 1, /*环境变量*/
    CALL_E_CFG_SERVER,      /*服务器地址*/
    CALL_E_CFG_NET,         /*本地网络接口地址*/
    CALL_E_CFG_USERAGENT,
    CALL_E_CFG_SERVRIGHT,   /*业务权限*/
    CALL_E_CFG_DSCP,        /*DSCP*/    
    CALL_E_CFG_SIP,         /*SIP信令配置*/
    CALL_E_CFG_ACCOUNT,
    CALL_E_CFG_COMPATIBLE_PARAM,
    CALL_E_CFG_CONF,        /*会议相关设置*/
    CALL_E_CFG_MEDIA,       /* 媒体全局配置*/
    CALL_E_CFG_AUDIO,       /*音频配置*/
    CALL_E_CFG_VIDEO,       /*视频配置*/
    CALL_E_CFG_DATA,        /*辅流配置*/
    CALL_E_CFG_MOBILE_VOICEMAIL,   /*移动语音邮箱权限*/
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


/* 呼叫相关服务器配置 */
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

/* 环境变量配置 */
#define CALL_D_CFG_ENV_SOLUTION                  CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_INT,0x01,0) 
#define CALL_D_CFG_ENV_DISASTER_RECOVERY_MODE    CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_INT,0x02,0)
#define CALL_D_CFG_ENV_PRODUCT_TYPE              CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_INT,0x03,0) 
#define CALL_D_CFG_ENV_USEAGENT                  CFG_ID_DEF(CALL_E_CFG_CALLENV,CALL_E_CFG_DATA_TYPE_STRING,0x04,0)  

/* 业务相关配置 */
#define CALL_D_CFG_SERVRIGHT_DND        CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_DONOTDISTURB,0)
#define CALL_D_CFG_SERVRIGHT_CFU        CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_UNCONDITIONAL,0)  
#define CALL_D_CFG_SERVRIGHT_CFB        CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_ONBUSY,0)
#define CALL_D_CFG_SERVRIGHT_CFNR       CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_OFFLINE,0)
#define CALL_D_CFG_SERVRIGHT_CFNA       CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALLFORWARDING_NOREPLY,0)
#define CALL_D_CFG_SERVRIGHT_CALLWAIT   CFG_ID_DEF(CALL_E_CFG_SERVRIGHT,CALL_E_CFG_DATA_TYPE_STRUCTURE,CALL_E_SERVICE_RIGHT_TYPE_CALL_WAIT,0)

/* DSCP相关配置 */
#define CALL_D_CFG_DSCP_ENABLE   CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_BOOL,0x1,0)
#define CALL_D_CFG_DSCP_AUDIO    CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_INT,0x2,0)
#define CALL_D_CFG_DSCP_VIDEO    CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_INT,0x3,0)
#define CALL_D_CFG_DSCP_SIP      CFG_ID_DEF(CALL_E_CFG_DSCP,CALL_E_CFG_DATA_TYPE_INT,0x4,0)

/* 会议相关配置 */
#define CALL_E_CFG_CONF_ENABLE_INTERCONF            CFG_ID_DEF(CALL_E_CFG_CONF, CALL_E_CFG_DATA_TYPE_BOOL, 0x1, 0)
#define CALL_E_CFG_CONF_MS_ADDR                     CFG_ID_DEF(CALL_E_CFG_CONF, CALL_E_CFG_DATA_TYPE_STRING, 0x4, 0)
#define CALL_E_CFG_CONF_APPAGENT_ADDR               CFG_ID_DEF(CALL_E_CFG_CONF, CALL_E_CFG_DATA_TYPE_STRING, 0x5, 0)
#define CALL_D_CFG_COMPATIBLE_PARAM_SELFNUM         CFG_ID_DEF(CALL_E_CFG_COMPATIBLE_PARAM,CALL_E_CFG_DATA_TYPE_STRING,0x2,0)/* 设置本端号码 */
#define CALL_D_CFG_COMPATIBLE_PARAM_OUTGOINGCODE    CFG_ID_DEF(CALL_E_CFG_COMPATIBLE_PARAM,CALL_E_CFG_DATA_TYPE_STRING,0x3,0)/* 设置OUTGOING码 */ 

/* sip相关配置 */
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
#define CALL_D_CFG_SIP_ENABLE_REG_SUB       CFG_ID_DEF(CALL_E_CFG_SIP, CALL_E_CFG_DATA_TYPE_BOOL,   0xC, 0) //是否开启订阅注册

/* 全局媒体相关配置 */
#define CALL_D_CFG_MEDIA_SRTPMKI            CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x1,0)  //SRTP mki方式
#define CALL_D_CFG_MEDIA_SRTP_MODE          CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x2,0)  //SRTP模式
#define CALL_D_CFG_MEDIA_MERGE_SRTP_RTP     CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x3,0)  //是否合并SRTP和RTP的m行，TRUE 合并，FALSE 不合并
#define CALL_D_CFG_MEDIA_RTP_PRIORITY       CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x4,0)  //rtp srtp优先顺序 1 rtp优先 2srtp优先
#define CALL_D_CFG_MEDIA_CRYPTOSUITE        CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_STRING,    0x5,0)  //SRTP加密方法优先级
#define CALL_D_CFG_MEDIA_SDP_OLINE_INFO     CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_STRUCTURE, 0x6,0)  //设置SDP O行信息
#define CALL_D_CFG_MEDIA_MOS_TIME           CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x7,0)  //MOS值上报间隔时间
#define CALL_D_CFG_MEDIA_MOS_THRESHOLD      CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_INT,       0x8,0)  //MOS值上报阀值
#define CALL_D_CFG_MEDIA_MOS_SENDINFOSWITCH CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0x9,0)  //UC C50 VQM开关
#define CALL_D_CFG_MEDIA_SENDONLYFREE       CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0xA,0)  //媒体方向为sendonly，是否释放资源
#define CALL_D_CFG_MEDIA_USEPACKMODE        CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_BOOL,      0xB,0)  //H264视频协商时，是否判断打包模式一直
#define CALL_D_CFG_MEDIA_RECORDFILE_INFO    CFG_ID_DEF(CALL_E_CFG_MEDIA,  CALL_E_CFG_DATA_TYPE_STRUCTURE, 0xC,0)  //设置录制文件附加信息

/* 音频配置 */
#define CALL_D_CFG_AUDIO_CODEC              CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_STRING,     0x1, 0) //音频编解码优先级
#define CALL_D_CFG_AUDIO_ANR                CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x2, 0) //噪音抑制 
#define CALL_D_CFG_AUDIO_AEC                CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x3, 0) //回声消除 
#define CALL_D_CFG_AUDIO_AGC                CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x4, 0) //自动增益 
#define CALL_D_CFG_AUDIO_DTMF_MODE          CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x5, 0) //DTMF模式
#define CALL_D_CFG_AUDIO_DTMF_PT            CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x6, 0) //DTMF PT值      
#define CALL_D_CFG_AUDIO_ILBCMODE           CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x7, 0) //ILBC模式 20 或 30    
#define CALL_D_CFG_AUDIO_PACKETTIME         CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0x8, 0) //打包时长
#define CALL_D_CFG_AUDIO_NETATELEVEL        CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,       0x9, 0) //netate冗余级别 0~4
#define CALL_D_CFG_AUDIO_VADFLAG            CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_BOOL,       0xA, 0) //Vad启用标志位  0关闭 1开启
#define CALL_D_CFG_AUDIO_CLOCKRATE          CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0xB, 0) //采样频率
#define CALL_D_CFG_AUDIO_CHANNELS           CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0xC, 0) //声道个数
#define CALL_D_CFG_AUDIO_BITS               CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_INT,        0xD, 0) //样本位数
#define CALL_D_CFG_AUDIO_PORT_RANGE         CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xE, 0) //音频端口范围
#define CALL_D_CFG_AUDIO_PLAYFILE_ADDITIONINFO         CFG_ID_DEF(CALL_E_CFG_AUDIO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xF, 0) //播放音频文件附加信息

/* 视频配置 */
#define CALL_D_CFG_VIDEO_LEVEL              CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x1, 0) //视频解码级别以及具体限制
#define CALL_D_CFG_VIDEO_DEFAULT_IMAGE      CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRING,     0x2, 0) //无视频时使用的图片，图片必须是bmp格式的
#define CALL_D_CFG_VIDEO_ARQ                CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x3, 0) //丢包重传
#define CALL_D_CFG_VIDEO_TACTIC             CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0x4, 0) //视频策略 0 图像质量优先  1 流畅优先
#define CALL_D_CFG_VIDEO_CODEC              CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRING,     0x5, 0) //视频编解码优先级
#define CALL_D_CFG_VIDEO_ERRORCORRECTING    CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x6, 0) //是否开启错误校验功能
#define CALL_D_CFG_VIDEO_FRAMESIZE          CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x7, 0) //视频分辨率
#define CALL_D_CFG_VIDEO_DATARATE           CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0x8, 0) //视频码率
#define CALL_D_CFG_VIDEO_HDACCELERATE       CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x9, 0) //硬件加速
#define CALL_D_CFG_VIDEO_FRAMERATE          CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xA, 0) //帧率
#define CALL_D_CFG_VIDEO_CODER_QUALITY      CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0xB, 0) //编码质量 [0-4]
#define CALL_D_CFG_VIDEO_KEYFRAMEINTERVAL   CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0xC, 0) //关键帧间隔 [1,30] 单位为s
#define CALL_D_CFG_VIDEO_ARS                CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xD, 0) //视频Ars功能设置
#define CALL_D_CFG_VIDEO_CAPTURE_ROTATION   CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,        0xE, 0) //摄像头采集角度
#define CALL_D_CFG_VIDEO_PORT_RANGE         CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_STRUCTURE,  0xF,0) //视频端口范围
#define CALL_D_CFG_VIDEO_FORCE_IDR_INFO     CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_BOOL,       0x10, 0) //是否强制打开info idr请求的收发
#define CALL_D_CFG_VIDEO_DISPLAYTYPE        CFG_ID_DEF(CALL_E_CFG_VIDEO, CALL_E_CFG_DATA_TYPE_INT,       0x11, 0) //视频显示模式

/* 本地地址配置 */
#define CALL_D_CFG_NET_NETADDRESS           CFG_ID_DEF(CALL_E_CFG_NET, CALL_E_CFG_DATA_TYPE_STRUCTURE, 0x1, 0) //sip使用，在媒体没有单独设置时，则媒体也用这个地址
#define CALL_D_CFG_AUDIO_NETADDRESS         CFG_ID_DEF(CALL_E_CFG_NET, CALL_E_CFG_DATA_TYPE_STRING,    0x2, 0) //设置音频使用地址
#define CALL_D_CFG_VDIEO_NETADDRESS         CFG_ID_DEF(CALL_E_CFG_NET, CALL_E_CFG_DATA_TYPE_STRING,    0x3, 0) //设置视频使用地址

/* 账号配置 */
#define CALL_D_CFG_ACCOUNT_AUTH             CFG_ID_DEF(CALL_E_CFG_ACCOUNT, CALL_E_CFG_DATA_TYPE_STRUCTURE, 0x1, 0)


/**移动语音邮箱权限配置*/
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
    TUP_CHAR     acActiveAccessCode[CALL_D_ACCESSCODE_MAX_LENGTH];         /* 登记特征码 */
    TUP_CHAR     acDeactiveAccessCode[CALL_D_ACCESSCODE_MAX_LENGTH];       /*取消登记特征码*/
}CALL_S_SERVICE_RIGHT_CFG;


/** AAC媒体能力集 */
typedef struct
{
     TUP_INT32     bProfileLevel;      /**< 是否有　profile-level 值　*/
     TUP_INT32     lProfileLevel;      /**< profile-level 值　*/
     TUP_UINT32    bMaxBitRate;         /**< 是否有带宽值 */
     TUP_UINT32    ulMaxBitRate;         /**< 带宽值:单位: 1bps*/
     TUP_UINT8     bAudioObjectType;     /**< 是否设置了音频对象类型*/
     TUP_UINT8     ucAudioObjectType;  /**< 音频对象类型 AAC-LC:2,AAC-LD:23 */
     TUP_UINT8     ucAACFormatType;     /**< 增加formattype 区分rawdata和latm:1:raw，2:支持latm，3:既支持raw又支持latm*/
     TUP_UINT8     bConfigPresent;     /**< 音频配置是否带内传送,0为带外传送，1为带内传送*/
     TUP_UINT8     bConfig;             /**< 是否设置了配置字符串 */
     TUP_UINT8     aucReserve[3];      /**< 保留位,用于字节对齐*/
     TUP_UINT32    ulConfig;             /**< 配置字符串的长度 */
     TUP_UINT8     pcMuxConfig[MPROC_D_AAC_CONFIG_LEN];     /**< 配置字符串 */
}MPROC_S_AAC_CAP_SPECIAL, *MPROC_S_AAC_CAP_SPECIAL_PTR;

/** DTMF媒体能力集 */
typedef struct
{
     TUP_UINT32 ulDTMFTransferMode;      /**< 0带内 or 1带外　*/
}MPROC_S_DTMF_CAP_SPECIAL;

 
typedef struct
{
    TUP_BOOL   bEnable;            /**< TUP_TRUE:支持*/
    TUP_UINT32  ulPktLen;           /**< 打包时长ms */
    TUP_UINT32  ulFrameLen;         /**< 帧长ms, iLBC mode*/
    TUP_UINT32   ulSampleRate;       /**< 采样率 */
    TUP_UINT8   ucPayLoad;          /**< 该format对应的pt值*/
    TUP_UINT8   ulBitNum;           /**< 支持的码率个数 */
    TUP_UINT8   ulBitRate[MPROC_D_AUD_RATE_NUM];    /**< 码率和枚举值对应::AUDIO_E_DECODERATE */
    TUP_UINT8   ulPadding[1];                       /**< 字节对齐 */
    union{
        MPROC_S_AAC_CAP_SPECIAL stAacSpecial;   /**< aac*/
        MPROC_S_DTMF_CAP_SPECIAL stDTMFSpecial;   /**< DTMF*/
    }uMedSpecialCap;
}MPROC_S_FORMAT_CAP, *MPROC_S_FORMAT_CAP_PTR;



/*统一IP地址网络接口信息数据结构*/
typedef struct CALL_S_IF_INFO 
{
    CALL_E_IP_PROTOCOL_TYPE  ulType;                     // IP地址类型
    union
    {
        TUP_UINT32 ulIPv4;                              //IPv4地址
        TUP_UINT8  aucIPv6[CALL_D_IP_LENGTH];       //IPv6地址，长度16字节
    }uAddress;
    union
    {
        TUP_UINT32 ulNetMask;                           //IPv4子网掩码
        TUP_UINT8  ulPrefixLen;                         //IPv6地址前缀长度
    }uMask;
    union
    {
        TUP_UINT32 ulIPv4;                              //网关IPv4地址
        TUP_UINT8  aucIPv6[CALL_D_IP_LENGTH];       //网关IPv6地址，长度16字节
    }uGateWay;
} CALL_S_IF_INFO;

typedef struct tagCALL_S_DEVICEINFO
{
    TUP_UINT32 ulIndex;      //设备对应的index
    TUP_CHAR   strName[CALL_D_MAX_DISPLAY_NAME]; //设备名称
} CALL_S_DEVICEINFO;



typedef struct tagCALL_S_REFRESH_VIEW
{
    TUP_UINT32 ulCallID;                  /**通话ID */
    CALL_E_REFRESHVIEW_MIDEATYPE enMeidaType;                /**view刷新媒体类型 */
    CALL_E_REFRESHVIEW_EVENT enEvent;                    /**view刷新事件 */
} CALL_S_REFRESH_VIEW;
 
typedef struct tagCALL_S_VIDEO_LEVEL
{
    TUP_UINT32 ulLevel;              // H264的level {10,11,12,13,20,21,22,30,31,32,40,41,42,50,51}
    TUP_UINT32 ulMaxMBPS;            // H264的max-bmps  0表示使用对应级别的默认值
    TUP_UINT32 ulMaxFS;              // H264的max-fs    0表示使用对应级别的默认值
    TUP_UINT32 ulMaxBR;              // H264的max-br    0表示使用对应级别的默认值
} CALL_S_VIDEO_LEVEL;

//SDP O行信息
typedef struct tagCALL_S_SDP_OLINE_INFO
{
    TUP_CHAR acUserName[CALL_D_MAX_LENGTH_NUM];              // username       "FAST_V2R1"
    TUP_CHAR acSessionId[CALL_D_MAX_LENGTH_NUM];             // session identifier  "2006"
    TUP_CHAR acSessionVersion[CALL_D_MAX_LENGTH_NUM];        // session version     "2006"
} CALL_S_SDP_OLINE_INFO;

//SRTP信息
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
    CALL_E_VIDEOWND_TYPE enRenderType;//窗口类型枚举值 0:远端窗口；1:本端窗口
    TUP_UINT32 ulDisplaytype; //窗口显示模式 0:拉伸模式 1:(不拉伸)黑边模式 2:(不拉伸)裁剪模式
    TUP_UINT32 ulMirrortype;  //窗口镜像模式 0:不做镜像(默认值) 1:上下镜像(目前未支持) 2:左右镜像
}CALL_S_VIDEO_RENDER_INFO;

typedef struct tagCALL_S_VIDEO_ORIENT
{
    TUP_UINT32 ulChoice;         //视频横竖屏情况 1：竖屏；2：横屏；3：反向横屏
    TUP_UINT32 ulPortrait;       //竖屏视频捕获（逆时针旋转）角度 0：0度；1：90度；2：180度；3：270度；
    TUP_UINT32 ulLandscape;      //横屏视频捕获（逆时针旋转）角度 0：0度；1：90度；2：180度；3：270度；
    TUP_UINT32 ulSeascape;       //反向横屏视频捕获（逆时针旋转）角度 0：0度；1：90度；2：180度；3：270度；
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
    CALL_E_TRANSPORTMODE_DEFAULT,    /* 默认使用公用传输方式 */
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
