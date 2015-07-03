/*******************************************************************************
 *               Copyright (C) 2014, Huawei Tech. Co., Ltd.
 *                      ALL RIGHTS RESERVED
 *******************************************************************************/

/** @defgroup Module Nume: call control interface
 *  @brief   呼叫子系统对外接口接口、宏定义
 *  @author  x00111629
 *  @version 1.0
 *  @date    2014/4/3
 *
 *
 *  
 */

#ifndef __CALL_ADVANCED_DEF_H__
#define __CALL_ADVANCED_DEF_H__

/*******************************************************************************
 *   本文件需要包含的其它头文件
 *******************************************************************************/
#include "tup_def.h"
#include "call_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */




/*******************************************************************************
 *   宏开关定义区（例如编译、调试、打印开关）
 *******************************************************************************/







/*******************************************************************************
 *   宏常量定义区
 *******************************************************************************/


#define CALL_D_MAX_STR_LENGTH     (256)                   /** SIP字符串最大长 */

#define CALL_D_512_STR_LENGTH     (512)                  /** 512字节长度 */
#define CALL_D_256_STR_LENGTH     (256)                  /** 256字节长度 */
#define CALL_D_128_STR_LENGTH     (128)                 /** 128字节长度 */
#define CALL_D_64_STR_LENGTH      (64)                    /** 64字节长度 */
#define CALL_D_32_STR_LENGTH      (32)                    /** 32字节长度 */
#define CALL_D_16_STR_LENGTH     (16)                   /** 16字节长度 */


#define CALL_D_AUDIO_EQ_MAX_BANDS (10)
#define CALL_D_MAX_LOCAL_CONFER_CALL_NUM (5)        /**< 最大会议路数*/

#define CALL_D_MAXNUM_GET_MEETING_INFO_PER_PAGE (10)       /**GET CONF LIST 每次获得的最大MEETING 信息个数*/
#define CALL_D_CONF_MAX_PW_LEN        (10)                 /** 会议与会者密码最大长度 */
#define CALL_D_MAX_BITFLAG_LEN        (33)                 /** 会议扩展标识长度 */
#define CALL_D_MAX_SERVERCONF_ATTENDEE (20)             /** 与会者最大个数 */



#define CALL_D_MAX_HISTORY_NUM        (5)  /* IMS forward*/
#define CALL_D_MAX_FOWARD_NUM        (24)  /**< 最大前转控制块处理个数*/


#define  CALL_D_MAX_UM_MSG_LENGTH          (4 * 1024) /**< UM消息最大字节长度*/


    /* paging组最大值 */
#define CALL_D_MAX_PAGING_NUM (10)

#define CALL_D_MAX_HUNTGROUP_NUM (10)

#define CALL_D_MAX_PRESET_MSG_LENGTH     (100)             /** 预设消息字符串最大长 */
#define CALL_D_MAX_NAMESPACE             (12)

/* BEGIN modify: [[DTS2012102902012] [2012/11/8] [yuxiating y00217218]]
   修改原因: 字段长度和本地地址本统一 */
/* see [eaddr_interface.h] */
#define CALL_D_EADDR_ENTERPRISE_STAFFNO_LEN 32
#define CALL_D_EADDR_ENTERPRISE_STAFFACCOUNT_LEN 128
#define CALL_D_EADDR_ENTERPRISE_NAME_LEN 128
#define CALL_D_EADDR_ENTERPRISE_NUM_LEN 33
#define CALL_D_EADDR_ENTERPRISE_DEPT_LEN 256
#define CALL_D_EADDR_ENTERPRISE_COMMON_LEN 128
#define CALL_D_EADDR_ENTERPRISE_EMAIL_LEN  256
#define CALL_D_EADDR_ENTERPRISE_URI_LEN 128
//add by c00188407 for DTS2012092802549
#define CALL_D_EADDR_ENTERPRISE_AVATARID_LEN  (144)       /* 头像ID最大长度 */
#define CALL_D_EADDR_ENTERPRISE_ADDRESS_LEN 256

#define CALL_CONF_SUBJECT_MAX_STR_LEN (1024)


/*******************************************************************************
 *   宏操作定义区
 *******************************************************************************/

/*******************************************************************************
 *   枚举类型定义区
 *******************************************************************************/


/** 设置视频会议预览时，使用的结构体*/
typedef struct tagCALL_S_VIDEOCONF_VIDEO_PARAM
{
    TUP_UINT32 xResolution;     //x分辨率(宽)
    TUP_UINT32 yResolution;     //y分辨率(高)
    TUP_UINT32 nBitRate;        //码流
} CALL_S_VIDEOCONF_VIDEO_PARAM;

/** 视频会议设备拔插*/
typedef enum tagCALL_E_VIDEOCONF_DEVICE_INPUT_STATUS
{
    CALL_E_VIDEOCONF_DEVICE_INPUT_STATUS_START,       //0 无效
    CALL_E_VIDEOCONF_DEVICE_INPUT_STATUS_INPUT,     //插入
    CALL_E_VIDEOCONF_DEVICE_INPUT_STATUS_OUTPUT,   //拔出
    CALL_E_VIDEOCONF_DEVICE_INPUT_STATUS_BUTT
} CALL_E_VIDEOCONF_DEVICE_INPUT_STATUS;

/** 视频会议设备状态*/
typedef enum tagCALL_E_VIDEOCONF_DEVICE_STATUS
{
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_CLOSE = 0,       //关闭状态
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_OPEN = 1,      //打开状态
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_RESUME = 2,   //恢复
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_PAUSE = 4,     //暂停
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_ERROR = 5,     //错误状态
    CALL_E_VIDEOCONF_DEVICE_LOCAL_STATUS_BUTT
} CALL_E_VIDEOCONF_DEVICE_STATUS;


typedef struct tagCALL_S_VIDEOCONF_DOUBLESTREAM_STATUS
{
    TUP_CHAR szAttendNum[CALL_D_MAX_STR_LENGTH];
    TUP_UINT32 xResolution; //x分辨率(宽)
    TUP_UINT32  yResolution;//y分辨率(高)

    TUP_UINT32 bHighOrLowChannel;//当前加入到高流还是低流
    TUP_UINT32  bDoubleStream;  //是否双流
    TUP_BOOL bOwnLowStream;     //是否还拥有低流
    TUP_BOOL bFlowCtrl;         //是否是流控告警引起
} CALL_S_VIDEOCONF_DOUBLESTREAM_STATUS;


/** 业务的能力集描述 */
typedef struct tagCALL_S_SERVICE_INFO
{
    TUP_UINT32   ulRight;            /**< 见CALL_E_SEVICERIGHT_STATUS */
    TUP_UINT32   ulRegister;            /**< 见CALL_E_SEVICEREGISTER_STATUS */
    TUP_CHAR     acActiveAccessCode[CALL_D_ACCESSCODE_MAX_LENGTH];         /* 登记特征码 */
    TUP_CHAR     acDeactiveAccessCode[CALL_D_ACCESSCODE_MAX_LENGTH];       /* 注销特征码 */
} CALL_S_SERVICE_INFO;



/* 业务配置的号码 */
typedef struct tagCALL_S_SERVICE_PARAM
{
    TUP_CHAR         acCallForwardUnconditionNum[CALL_D_MAX_LENGTH_NUM];
    TUP_CHAR         acCallForwardOnBusyNum[CALL_D_MAX_LENGTH_NUM];
    TUP_CHAR         acCallForwardNoReplyNum[CALL_D_MAX_LENGTH_NUM];
    TUP_CHAR         acCallForwardOfflineNum[CALL_D_MAX_LENGTH_NUM];
    TUP_CHAR         acVoiceMailGetNum[CALL_D_MAX_LENGTH_NUM];
    TUP_CHAR         acTurnPhoneNum[CALL_D_MAX_LENGTH_NUM];         //手机分机:转移到话机接入码
    TUP_CHAR         acTurnMobileNum[CALL_D_MAX_LENGTH_NUM];        //手机分机:转移到手机接入码
    TUP_UINT32       ulEaddrSearchType;
    /* BEGIN add: [[V100R001C50] [IR.IPT.014] [2013/12/5] [WuDingyuan]]
       修改原因: 缩位拨号，理论上不需要CALL_D_MAX_STR_LENGTH这么长的字串，与特征码保持一致 */
    TUP_CHAR        acAbbrDial[CALL_D_ACCESSCODE_MAX_LENGTH];              /** 缩位拨号 */
    /* END   add: [[V100R001C50] [IR.IPT.014] [2013/12/5] [WuDingyuan]] */
    TUP_UINT32       ulVoiceMailSupportType;                        //是否支持VVM
    TUP_CHAR         acVoiceMailNumber[CALL_D_MAX_LENGTH_NUM];      //mailbox号码
    TUP_CHAR         acVoiceMailSPIN[CALL_D_MAX_LENGTH_NUM];        //语音邮箱提取的SPIN号码
    TUP_UINT32       ulVVMHttpsSupport;                             //vvm是否支持https

    TUP_UINT32      ulCallLimitType;                              /** 密码限呼类型 */
    TUP_CHAR        acCallLimitCode[CALL_D_MAX_LENGTH_NUM];       /** 密码限呼接入码 */

    /* add by zhangls 00219468 for hotline */
    TUP_UINT32      ulHotLineEnable;                              /** 热线使能标识 */
    TUP_CHAR        acHotLineNumber[CALL_D_128_STR_LENGTH];       /** 热线号码 */
    TUP_UINT32      ulHotLineDelayTime;                           /** 热线时延 */
    TUP_UINT32      ulHotLineType;                                /** 热线类型 */

    /* BEGIN add: [[eSpace 7900 V100R001C50B010] [IR.IPT.004] [2013/12/4] [yuanmeijuan]]
       修改原因: 增加标志位，当前是否可配置无条件前转号码 */
    TUP_BOOL         bIsChangeCFUNum;
    /* END   add: [[eSpace 7900 V100R001C50B010] [IR.IPT.004] [2013/12/4] [yuanmeijuan]] */

} CALL_S_SERVICE_PARAM;


/***************************
message 推送 会议信息
<? xml version = "1.0" encoding = "UTF-8"?>
<TOPIC>meeeting topic : Huawei UC & C < / TOPIC >
<MeetingTime>2013 - 05 - 22 10 : 22 : 00--2013 - 05 - 22 12 : 22 : 00(GMT + 08 : 00) < / MeetingTime >
<Convener>储成 < / Convener >
<Attendee>c00188407, y00204551, z00190894 < / Attendee >
<AccessNumber>1731732 < / AccessNumber >
<Host>储成 < / Host >
<SecurityCode>636474141 < / SecurityCode >
<IsCycle> -1 < / IsCycle >
<StartDate>2013 - 05 - 22 10 : 22 : 00--2013 - 05 - 22 12 : 22 : 00(GMT + 08 : 00) < / StartDate >
<ValidityPeriod>2013 - 05 - 22 10 : 22 : 00--2013 - 05 - 22 12 : 22 : 00 < / ValidityPeriod >
<ConfID>sip : 01000011322@example.com < / ConfID >
<EmceeID> < / EmceeID >
<HostID>c00188407 < / HostID >
<IMContent>
< / IMContent >

content - type              汉字使用UTF - 8编码，需要辨识UTF - 8关键字
content - transfer - encoding            base64，内容经过了base64压缩，需要辨识base64
TOPIC    会议主题        meeeting topic :
MeetingTime 会议召开时间
Convener    召集人
Attendee    与会者        多个与会者之间用逗号隔开
AccessNumber    会议接入号
SecurityCode    主持人会议密码
ValidityPeriod    会议有效期
StartDate    会议召开日期
ConfID    会议id
*****************************/
/** 呼控将接收到的message 解析出的meeting 消息转发给界面处理*/
typedef struct tagCALL_S_UM_MEETING_MSG
{
    TUP_CHAR acMeetingTopic[CALL_D_MAX_STR_LENGTH];     /** 会议主题*/
    TUP_CHAR acMeetingTime[CALL_D_64_STR_LENGTH];     /** 会议时间*/
    TUP_CHAR acConvener[CALL_D_64_STR_LENGTH];     /** 会议召集人*/
    TUP_CHAR acAttendee[CALL_D_MAX_SERVERCONF_ATTENDEE* CALL_D_64_STR_LENGTH];      /** 会议与会者,最大20人*/
    TUP_CHAR acHost[CALL_D_64_STR_LENGTH];          /** 主持人*/
    TUP_CHAR acHostID[CALL_D_64_STR_LENGTH];          /** 主持人id*/
    TUP_CHAR acConfID[CALL_D_128_STR_LENGTH];          /** 会议id*/
    TUP_CHAR acAccessNumber[CALL_D_64_STR_LENGTH];          /** 会议接入码*/
    TUP_CHAR acSecurityCode[CALL_D_64_STR_LENGTH];       /** 会议安全号，主席密码*/
    TUP_CHAR acStartDate[CALL_D_64_STR_LENGTH];     /** 会议开始时间*/
    TUP_CHAR acValidityPeriodDate[CALL_D_64_STR_LENGTH];     /** 会议有效时间*/
    TUP_CHAR acIMContent[CALL_D_MAX_STR_LENGTH * 2]; /** 会议内容*/
} CALL_S_UM_MEETING_MSG;

/** 业务权限能力集注意一定要与CALL_E_SERVICE_RIGHT_TYPE 对应 */
typedef struct tagCALL_S_SERVICERIGHT_CFG
{
    CALL_S_SERVICE_INFO   astSrvInfo[CALL_E_SERVICE_RIGHT_TYPE_BUTT];
    CALL_S_SERVICE_PARAM  stServiceParam;

    /* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/2/1] [zhanglusha 00219468]]
       修改原因: intercom业务 */
    TUP_CHAR acIntercomNum[CALL_D_MAX_LENGTH_NUM];                              /* intercom号码 */
    /* END   add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/2/1] [zhanglusha 00219468]] */
} CALL_S_SERVICERIGHT_CFG;



/* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/2/7] [zhanglusha 00219468]]
   修改原因: 经理秘书增强 */

/**共享线路状态*/
typedef enum tagCALL_E_SCASTATE
{
    CALL_E_SCASTATE_IDLE,                /**<空闲状态 */
    CALL_E_SCASTATE_SEIZED,              /**< 占用状态*/
    CALL_E_SCASTATE_ALERTING,            /**< 来电振铃中 */
    CALL_E_SCASTATE_ACTIVE,              /**< 通话中 */
    CALL_E_SCASTATE_PROGRESSING,         /**<呼出中 */
    CALL_E_SCASTATE_HELD,                /**<保持状态 */
    CALL_E_SCASTATE_HELD_PRIVATE,        /**<私人保持状态 */
    CALL_E_SCASTATE_BRIDGE_ACTIVE,       /**<bridge会议状态 */
    CALL_E_SCASTATE_LOCK,                /**<私有化状态 */
    CALL_E_SCASTATE_TERM,                /**< 订阅终结*/
    CALL_E_SCASTATE_BUTT
} CALL_E_SCASTATE;

/* END   add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/2/7] [zhanglusha 00219468]] */



/** 本地会议会场状态 add by h00206999*/
typedef enum tagCALL_E_LOCAL_CONF_STATE
{
    CALL_E_LOCAL_CONF_STATE_IDLE,        /**< 会议空闲态 */
    CALL_E_LOCAL_CONF_STATE_INIT,        /**< 会议初始态 */
    CALL_E_LOCAL_CONF_STATE_LIVE,        /**< 会议激活态 */
    CALL_E_LOCAL_CONF_STATE_HOLD,        /**< 会议保持态 */
    CALL_E_LOCAL_CONF_STATE_END,         /**< 会议结束态 */
    CALL_E_LOCAL_CONF_STATE_BUTT         /**< 会议无效态 */
} CALL_E_LOCAL_CONF_STATE;

/*本地会议的会议类型 added by s00193874 */
typedef enum tagCALL_E_LOCAL_CONF_TYPE
{
    CALL_E_LOCAL_CONFTYPE_HOLD,         /**< 添加与会者时会场被保持*/
    CALL_E_LOCAL_CONFTYPE_NOHOLD,       /**< 添加与会者时会场照常开会*/
    CALL_E_LOCAL_CONF_BUTT
} CALL_E_LOCAL_CONF_TYPE_ENUM;

/** 与会者发言状态 */
typedef enum tagCALL_E_LOCAL_CONFREE_TALK_STATE
{
    CALL_E_LOCAL_CONFREE_TALK_STATE_IDLE,              /**< 空闲态 */
    CALL_E_LOCAL_CONFREE_TALK_STATE_SPEAKING,          /**< 发言态 */
    CALL_E_LOCAL_CONFREE_STATE_BUTT                    /**< 无效态 */
} CALL_E_LOCAL_CONFREE_TALK_STATE;


/** 密码限呼类型 */
typedef enum tagCALL_E_CALL_LIMIT_TYPE
{
    CALL_E_CALL_LIMIT_NONE,         /** 不受限 */
    CALL_E_CALL_LIMIT_HOME,         /** 国内限呼 */
    CALL_E_CALL_LIMIT_INTERNATIONAL,/** 国际限呼 */
    CALL_E_CALL_LIMIT_BOTH,         /** 国内限呼+国际限呼 */
    CALL_E_CALL_LIMIT_BUTT
} CALL_E_CALL_LIMIT_TYPE;


/**状态类型, refer to structure SIP_S_STATUS */
typedef enum  tagCALL_E_CONTACT_STATUS
{
    /** presence->tuple->note */
    CALL_E_CONTACT_STATUS_OFFLINE,       /**< 离线，出现场景---软终端、硬终端、CC上报、BLF(Subscription-State: terminated;reason=probation) */
    CALL_E_CONTACT_STATUS_ONLINE,        /**< 空闲，出现场景---软终端、硬终端、BLF(terminated) */
    CALL_E_CONTACT_STATUS_BUSY,          /**< 忙碌，出现场景---软终端 */
    CALL_E_CONTACT_STATUS_LEAVE,         /**< 离开，出现场景---软终端 */
    CALL_E_CONTACT_STATUS_DND,           /**< DND ，出现场景---软终端、硬终端 */
    CALL_E_CONTACT_STATUS_CALLING,      /**<通话中，出现场景---软终端、硬终端、CC上报、BLF(confirmed) */
    CALL_E_CONTACT_STATUS_BUSY_CALLING,  /**<呼叫中，出现场景---待定 */
    /* BEGIN add: [[DTS2013060900807 ] [2013/6/14] [zhanglusha 00219468]]
       修改原因: 服务器会议状态,也需上报 */
    CALL_E_CONTACT_STATUS_BUSY_MEETING,   /**<服务器会议中 */
    /* END   add: [[DTS2013060900807 ] [2013/6/14] [zhanglusha 00219468]] */

    /** presence->tuple->ctiphonestatus */
    CALL_E_CONTACT_STATUS_RINGING,        /**<振铃响铃，出现场景---CC上报、BLF(early) */
    CALL_E_CONTACT_STATUS_DAILNUM,        /**<摘机拨号，出现场景---CC上报 */
    CALL_E_CONTACT_STATUS_OFFHOOK,       /**<摘机，出现场景---CC上报 */
    CALL_E_CONTACT_STATUS_ONHOOK,        /**<挂机，出现场景---CC上报 */

    CALL_E_CONTACT_STATUS_UNDND,           /**< 取消DND ，出现场景---软终端、硬终端，不用于发布! */
    CALL_E_CONTACT_STATUS_UNBUSY,          /**< 取消忙碌，不用与发布! */

    CALL_E_CONTACT_STATUS_UNKNOWN,       /**< 未知状态  */
    CALL_E_CONTACT_STATUS_PHONE_ONLINE,  /**< 话机在线  */
    CALL_E_CONTACT_STATUS_BUTT           /**< 无效状态 */
} CALL_E_CONTACT_STATUS;


/** 服务器会议类型 */
typedef enum tagCALL_E_CONFTYPE
{
    CALL_E_CONFTYPE_PRERECE_VOICE = 10,            /** 融合会议语音*/
    CALL_E_CONFTYPE_PRERECE_VIDEO,            /** 融合会议视频*/
    CALL_E_CONFTYPE_PRERECE_MULTIMEDIA,       /** 融合会议多媒体*/
    CALL_E_CONFTYPE_UC_VOICE,                 /**UC语音会议*/
    CALL_E_CONFTYPE_UC_VIDEO,                 /** UC及时视频会议*/
    CALL_E_CONFTYPE_UC_MULTIMEDIA,            /**UC 多媒体会议*/
    CALL_E_CONFTYPE_BUTT
} CALL_E_CONFTYPE;


/** 是否显示软终端号码 */
typedef enum tagCALL_E_LINKAGE_STATE 
{
    CALL_E_LINKAGE_STATE_DISPSOFTTEL,      /**< 显示 */
    CALL_E_LINKAGE_STATE_NOT_DISPSOFTTEL,  /**< 不显示 */
    CALL_E_LINKAGE_STATE_BUTT       
}CALL_E_LINKAGE_STATE;

/* BEGIN modify: [[SWED0000] [2012/9/28] [c00188407]]
   Description    : DTS2012092701233  */
typedef struct tagCALL_S_CONTACT_INFO
{
    TUP_UINT32  ulIndex;                                      /* 当前查找线路标识 */
    TUP_INT8    StaffAccount[CALL_D_EADDR_ENTERPRISE_STAFFACCOUNT_LEN]; /* UC账号 */
    TUP_INT8    PersonName[CALL_D_EADDR_ENTERPRISE_NAME_LEN];      /* 姓名 */
    TUP_UINT32  Sex;                                          /* 性别 */
    TUP_INT8    Staffno[CALL_D_EADDR_ENTERPRISE_STAFFNO_LEN] ;     /* 工号 */
    TUP_INT8    IPNum[CALL_D_EADDR_ENTERPRISE_NUM_LEN];            /* IP号码 */
    TUP_INT8    DeptName[CALL_D_EADDR_ENTERPRISE_DEPT_LEN];        /* 部门名字 */
    TUP_INT8    Title[CALL_D_EADDR_ENTERPRISE_COMMON_LEN];         /* 职务 */
    TUP_INT8    CellPhone[CALL_D_EADDR_ENTERPRISE_NUM_LEN];        /* 手机号码 */
    TUP_INT8    Seatphone[CALL_D_EADDR_ENTERPRISE_NUM_LEN];        /* 座机号码 */
    TUP_INT8    Otherphone[CALL_D_EADDR_ENTERPRISE_NUM_LEN];       /* 其余号码 */
    TUP_INT8    Otherphone2[CALL_D_EADDR_ENTERPRISE_NUM_LEN];      /* 其余号码2 */
    TUP_INT8    homephone[CALL_D_EADDR_ENTERPRISE_NUM_LEN];        /* 家庭号码 */
    TUP_INT8    Email[CALL_D_EADDR_ENTERPRISE_EMAIL_LEN];          /* email */
    TUP_INT8    Address[CALL_D_EADDR_ENTERPRISE_ADDRESS_LEN];      /* 地址 */
    TUP_UINT32  ulState;                                      /* 在线状态 */
    TUP_INT8    acuriDomain[CALL_D_EADDR_ENTERPRISE_URI_LEN];
    TUP_INT8    acAvatarID[CALL_D_EADDR_ENTERPRISE_AVATARID_LEN];  /* 头像ID */  //add for DTS2012092802549 by c00188407
    CALL_E_LINKAGE_STATE    enLinkageState;                    /* add by z00219468 for 软终端号码显示 */
} CALL_S_CONTACT_INFO, *CALL_S_CONTACT_INFO_PTR;
/* END   modify: [[SWED0000] [2012/9/28] [c00188407]] */

/**< 联系人及其状态信息 */
typedef struct tagCALL_S_CONTACT_STATUS
{
    TUP_UINT32 ulSipAccountID;
    /* BEGIN mod: [[DTS2012103002451] [2012/11/1] [caoruihong 00205112]] */
    TUP_CHAR acNo[33];       /**< 号码 */
    /* END   mod: [[DTS2012103002451] [2012/11/1] [caoruihong 00205112]] */
    CALL_E_CONTACT_STATUS enContactStatus;    /**< 状态 */
} CALL_S_CONTACT_STATUS, *CALL_S_CONTACT_STATUS_PTR;

/** 状态信息 */
typedef struct tagCALL_S_STATUS
{
    TUP_UINT32 ulNum;                        /* 状态个数 */
    CALL_S_CONTACT_STATUS* pstStatus;       /* 状态 */
} CALL_S_STATUS, *CALL_S_STATUS_PTR;


/* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR.Acc.001] [2013/1/24] [jiangtao/00196674]]
    修改原因: 同组振铃上报消息中包含主叫号码和振铃号码两个字符串，但消息中只能上报一个指针参数
             ，因此要将它们打包成一个结构体，以此来上报结构体指针参数 */
typedef struct tagCALL_S_TIPINFO
{
    TUP_CHAR acCallerNo[CALL_D_MAX_STR_LENGTH];   /* 主叫号码 */
    TUP_CHAR acRingNo[CALL_D_MAX_STR_LENGTH];     /* 振铃号码 */
} CALL_S_TIPINFO, *CALL_S_TIPINFO_PTR;
/* END   add: [[eSpace 7900 V100R001C02B010] [IR.Acc.001] [2013/1/24] [jiangtao/00196674]] */




/*联动命令信息*/
typedef struct tagCALL_S_JOINT_CMD_INFOS
{
    TUP_UINT32 ulSipAccountID;
    TUP_UINT32 ulCallID;
    TUP_UINT32 ulTransferOriginID;
    TUP_UINT32 ulConfID;
    TUP_UINT32 ulLineID;
    CALL_E_CALL_EVENT enJointCmdMsg;        /**< 消息类型 */
    TUP_CHAR acCallNum[CALL_D_MAX_STR_LENGTH];      /* 电话号码 */
    TUP_UINT32  ulCallNumLen;                       /* 电话号码长度 */
    TUP_UINT32 ulResult; /*0 : 成功，其他: 失败*/
} CALL_S_JOINT_CMD_INFOS;

#define CALL_D_CTD_BIND_NUM_MAX_LEN 255

typedef struct tagCALL_S_CTD_INFO_BODY
{
    TUP_UINT32   ulServiceType;
    TUP_UINT32   ulCmdType; 
    TUP_UINT32   ulCtdCallId;
    TUP_CHAR     acAttendeeEid[64][CALL_D_CTD_BIND_NUM_MAX_LEN + 1]; 
    TUP_UINT32 ulAttendeeNum;
    TUP_CHAR     acCtdCallerNum[CALL_D_CTD_BIND_NUM_MAX_LEN + 1];
    TUP_CHAR     acCtdCalleeNum[CALL_D_CTD_BIND_NUM_MAX_LEN + 1];
}CALL_S_CTD_INFO_BODY;


typedef enum tagCALL_E_EQ_PARAMS_DIRECTION
{
    CALL_E_EQ_PARAMS_DIRECTION_NONE = 0x00,
    CALL_E_EQ_PARAMS_DIRECTION_UP   = 0x01,       //上行方向参数
    CALL_E_EQ_PARAMS_DIRECTION_DOWN = 0x02,       //下行方向参数

    CALL_E_EQ_PARAMS_DIRECTION_INVALID = 0xff
}CALL_E_EQ_PARAMS_DIRECTION;

typedef struct tagCALL_S_AUDIO_EQ_PARAMS
{
    TUP_INT32 iSampleRate;                           /**<  采样率，支持8000、16000、48000三种采样率*/

    TUP_INT32 iBand_Q[CALL_D_AUDIO_EQ_MAX_BANDS];           /**<  频率宽度，此数值为滤波器Q值对应的Q26定点值，要求如下
                                                      1、第一个滤波器与最后一个滤波器必须为搁架滤波器，中间为峰值滤波器
                                                      2、搁架滤波器Q值设置范围[0.03125, 0.70711]，对应Q26定点值[94906266, 2147483647]
                                                      3、峰值滤波器Q值设置范围[0.03125, 64]，对应Q26定点值[1048576, 2147483647]*/
    TUP_INT16 sBand_f0[CALL_D_AUDIO_EQ_MAX_BANDS];          /**<  可调频段中心频率，不同采样率、不同滤波器范围不同，要求如下:
                                                      采样率8K:低频搁架滤波器（第一频段）中心频率范围为:10Hz~2000Hz
                                                               峰值滤波器（中间频段）中心频率范围为:60Hz~3000Hz
                                                               高频搁架滤波器（最后频段）中心频率范围为:1000Hz~3800Hz
                                                      采样率16K:低频搁架滤波器（第一频段）中心频率范围为:10Hz~4000Hz
                                                               峰值滤波器（中间频段）中心频率范围为:60Hz~6000Hz
                                                               高频搁架滤波器（最后频段）中心频率范围为:1000Hz~7800Hz
                                                      采样率48K:低频搁架滤波器（第一频段）中心频率范围为:10Hz~8000Hz
                                                               峰值滤波器（中间频段）中心频率范围为:60Hz~16000Hz
                                                               高频搁架滤波器（最后频段）中心频率范围为:1000Hz~22000Hz */
    TUP_INT16 sDBgain[CALL_D_AUDIO_EQ_MAX_BANDS];           /**<  可调频段增益，设置范围[-24, 24]dB*/
                                                          
    TUP_INT32 iNBand;                                /**<  频段数，设置范围[0, 10]，0代表关闭EQ*/

    TUP_INT32 iACLPEnabled;                          /**<  削波模块标志: 1表示开启，0表示关闭*/

}CALL_S_AUDIO_EQ_PARAMS;

typedef struct tagCALL_S_AUDIO_AEC_PARAMS
{
    TUP_UINT8   ucCngMode;              /**<   舒适噪声模式:零关闭，非零打开，默认打开 */  
    TUP_UINT8   ucPureDelay;            /**<   纯迟延默认为0ms, 【0:0ms, 1:10ms, 2:20ms, 3:30ms, 4:40ms, 5:50ms, 6:60ms】*/
    TUP_UINT16  usNearAllPassEnergy;   /**<   判断近端是否透传的远端能量阈值, 默认为1,【0:-59dBm0, 1:-49dBm0, 2:-39dBm0】 */
    TUP_UINT8   ucNearCleanSupEnergy;   /**<   判断近端是否为纯回声帧的阈值, 默认为2, 【0:12dB, 1:15dB, 2:18dB】 */
    TUP_UINT8   ucMode;                 /**<   话机模式, 默认为听筒模式【0:听筒, 1:免提】 */
    TUP_UINT8   ucSampleRate;           /**<   采样率, 默认为48K, 目前不支持24K采样率【0:8K,1:16K,2:24K,3:48K】 */
}CALL_S_AUDIO_AEC_PARAMS;


typedef struct tagCALL_S_AUDIO_EQ_CONFIG
{
    CALL_E_EQ_PARAMS_DIRECTION   eParamsDirection;   /**<  参数标志位，上行or下行 CALL_E_EQ_PARAMS_DIRECTION*/

    TUP_INT32 iMode;                                /**<  EQ状态，非0表示打开EQ，0表示关闭EQ */
    
    CALL_S_AUDIO_EQ_PARAMS stEqCfg_8K;                 /**<  采样率为8K时，EQ参数列表 */
    
    CALL_S_AUDIO_EQ_PARAMS stEqCfg_16K;                /**<  采样率为16K时，EQ参数列表 */
    
    CALL_S_AUDIO_EQ_PARAMS stEqCfg_48K;                /**<  采样率为48K时，EQ参数列表 */
    
    TUP_CHAR acVolMap[CALL_D_MAX_STR_LENGTH];          /**< 输出音量的调节范围映射表，用逗号分开每个值 */

    TUP_UINT32 ulMicVolume;                                /**<  MIC音量设置[0-10000] */
}CALL_S_AUDIO_EQ_CONFIG;



typedef struct tagCALL_S_CURRENT_SIPSERVER
{
    TUP_CHAR acCurrentRegAddress[CALL_D_MAX_STR_LENGTH];    /**< 当前使用的SIP注册服务器地址 */
    TUP_UINT32 ulCurrentRegPort;                            /**< 当前使用的SIP注册服务器端口 */

    TUP_CHAR acCurrentProxyAddress[CALL_D_MAX_STR_LENGTH];  /**< 当前使用的代理服务器地址 */
    TUP_UINT32 ulCurrentProxyPort;                          /**< 当前使用的代理服务器端口 */
} CALL_S_CURRENT_SIPSERVER;

typedef struct tagCALL_S_SIP_ADDR_INFO
{
    TUP_CHAR acSipAddress[CALL_D_64_STR_LENGTH];
    TUP_INT32 iPort;
} CALL_S_SIP_ADDR_INFO;


typedef struct tagCALL_S_CONFEREE_INFO
{
    TUP_UINT32 ulCallID;                              /**< 与会者线路通话ID*/
    TUP_BOOL bIsMuted;                                /**< 与会者是否被静音 */
    CALL_E_LOCAL_CONFREE_TALK_STATE enTalkState;      /**< 与会者说话状态 */
} CALL_S_CONFEREE_INFO;



/** 与会者线路列表 add by h00206999*/
typedef struct tagCALL_S_CONFER_CALLID_LIST
{
    CALL_S_CONFEREE_INFO astConfereeList[CALL_D_MAX_LOCAL_CONFER_CALL_NUM];      /**< 与会者列表，无效ID为0xFFFFFFFF */
    TUP_UINT32 ulCnt;                                                           /**< 与会者人数 */
} CALL_S_CONFER_CALLID_LIST;



typedef struct tagCALL_S_CONFER_LOCAL_INFO
{
    TUP_UINT32 ulConfID;                          /**< 本地会议会场ID */
    TUP_UINT32 ulSipAccountID;                    /**< 本地会议主席SipID */
    TUP_UINT32 ulCreatorCallID;                   /**< 创建会场线路的CallID */
    TUP_UINT32 ulCreatorLineID;                   /**< 会议创建线路的ID */
    CALL_E_LOCAL_CONF_STATE   enConfState;        /**< 会场状态 */
    CALL_E_LOCAL_CONF_TYPE_ENUM enLocConfType;    /**< 本地会议类型*/
    CALL_S_CONFER_CALLID_LIST stConfCallIDList;   /**< 与会者CallID列表*/
} CALL_S_CONFER_LOCAL_INFO;


typedef struct tagDesktop_Menu_Cfg
{
    TUP_UINT32 ulMessageButton;
    TUP_UINT32 ulEnableLogout;
} CALL_S_SERVICE_EXTENSION_CFG;






/**IMS话机被前转时，保存被前转到的目的号码***/

//todo chenyake
//typedef TUP_CHAR HistoryInfoNum[2 * CALL_D_MAX_LENGTH_NUM + 4]; /**与SIP_D_MAX_URI_LENGTH一致*/

typedef struct tagCALL_S_PICKUP_REMOTE_INFO
{
    TUP_CHAR acTelNum[CALL_D_MAX_STR_LENGTH];   /**<  指定代答主叫方号码 */
    TUP_CHAR acDisplayName[CALL_D_64_STR_LENGTH];  /**< 指定代答主叫方显示名称 */
} CALL_S_PICKUP_REMOTE_INFO;

/* BEGIN add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/1/31] [zhanglusha 00219468]]
   修改原因: 经理秘书增强 */

typedef enum tagCALL_E_CALLINFO_ORIGINATE{
    CALL_E_CALLINFO_ORIGINATE_FROM,                      /**< 共享线状态为外线呼入 */
    CALL_E_CALLINFO_ORIGINATE_TO,                        /**< 共享线状态为共享线呼出 */
    CALL_E_CALLINFO_ORIGINATE_BUTT,                      /**< 共享线状态来源未知 */
}CALL_E_CALLINFO_ORIGINATE;


typedef struct tagCALL_S_SCA_CALLINFO
{
    TUP_UINT32 ulSipAccountID;      /** 账户ID */
    TUP_UINT32 ulAppearanceIndex;   /** 线路号 */
    TUP_UINT32 ulAppearanceState;   /**线路状态 见SIP_E_SCASTATE*/
    CALL_E_CALLINFO_ORIGINATE enOriginateType; /**< 共享线状态来源 */
    TUP_CHAR acDisplayName[CALL_D_MAX_DISPLAY_NAME]; /**<共享线通话信息显示名称 */
    TUP_CHAR acDisplayNum[CALL_D_MAX_LENGTH_NUM];    /**<共享线通话信息显示号码 */
} CALL_S_SCA_CALLINFO;



/* END   add: [[eSpace 7900 V100R001C02B010] [IR.IPT.001] [2013/1/31] [zhanglusha 00219468]] */

typedef enum
{
    CALL_E_REINVITE_PNOTIFICATION_NONE,
    CALL_E_REINVITE_PNOTIFICATION_HOLD,
    CALL_E_REINVITE_PNOTIFICATION_UNHOLD,
    CALL_E_REINVITE_PNOTIFICATION_BUTT
} CALL_E_REINVITE_TYPE;

/* BEGIN add: [[IR.IPT.013] [2014/1/27] [zhanglusha 00219468]]
   修改原因: 密码限呼需要在登记失败时区分原因码 */
typedef enum tagCALL_E_CAUSE_RESON
{
    CALL_E_CAUSE_NORMAL = 0,     /* 成功 */
    CALL_E_CAUSE_FAILURE,         /* 失败 */
    CALL_E_CAUSE_LOCKED,          /* 锁定 */
    CALL_E_CAUSE_NOLINE,          /* 无可用线路 */
    CALL_E_CAUSE_BUSY,            /* 用户忙 */
    CALL_E_CAUSE_BUTT
} CALL_E_CAUSE_RESON;
/* END   add: [[IR.IPT.013] [2014/1/27] [zhanglusha 00219468]] */



typedef struct tagCALL_S_ACB_INFO
{
    TUP_UINT32 ulTime1;                             /**<服务设置的回呼超时时间*/
    TUP_CHAR acCalleeNum[CALL_D_MAX_STR_LENGTH];    /**< 回呼号码 */
    TUP_UINT32 ulOverTime;                          /**< 回呼剩余时间 */
} CALL_S_ACB_INFO;

/* BEGIN add: [[SR.RECORD.001] [2014/2/18] [s00193874]] 
   修改原因: 上报给界面录音信息对应的结构体 */
typedef struct tagCALL_S_RECORD_INFO
{
    TUP_BOOL bRecordStatus;
    TUP_BOOL bRecordRight;
}CALL_S_RECORD_INFO;
/* END   add: [[SR.RECORD.001] [2014/2/18] [s00193874]] */



typedef enum
{
    CALL_E_SEVICEREGISTER_LACK = 0,     /* 没登记 */
    CALL_E_SEVICEREGISTER_HAVE      /* 有登记 */
} CALL_E_SEVICEREGISTER_STATUS;


/*******************************************************************************
 *   订阅枚举类型定义
 *******************************************************************************/
/**< 订阅状态 */
typedef enum tagCALL_E_SUB_STATE          /**< add by chenDK */
{
    CALL_E_SUB_STATE_UNSUB,     /**<未订阅 */
    CALL_E_SUB_STATE_SUBING,    /**<订阅中 */
    CALL_E_SUB_STATE_DESUBING,  /**<去订阅中 */
    CALL_E_SUB_STATE_SUBED,     /**< 已订阅 */
    CALL_E_SUB_STATE_BUTT            /**<订阅无效状态 */
} CALL_E_SUB_STATE;

//add by chendk for sca
typedef enum tagCALL_E_LINETYPE
{
    CALL_E_LINETYPE_NORMAL,             /* 普通呼叫 */
    CALL_E_LINETYPE_SCA,                     /*共享线路发起呼叫*/
    CALL_E_LINETYPE_BUTT
} CALL_E_LINE_TYPE;


typedef struct tagCALL_S_HARDWARE_PARAMS
{
    TUP_UINT32 ulBright;    //亮度 [1,100]默认50
    TUP_UINT32 ulContrast;  //对比度 [1,100]默认50
    TUP_UINT32 ulDigitalZoom;  //数字变倍 [1,100]默认50

} CALL_S_HARDWARE_PARAMS;

/*BEGIN:add by l00214300@2014-1-14 for: 批量登记IPT业务*/
/** ACB登记业务数据 */
typedef struct tagCALL_S_ACB_SERVICE_DATA
{
    TUP_CHAR   acACBCallNum[CALL_D_MAX_STR_LENGTH];      /**< 回呼号码 */
    TUP_UINT32 ulACBCallNumLenl;                         /**< 回呼号码长度 */
} CALL_S_ACB_SERVICE_DATA;

/* BEGIN add: [[IR.IPT.013] [2013/12/25] [zhanglusha 00219468]]
   修改原因: 密码限呼 */

/** 密码限呼登记业务数据 */
typedef struct tagCALL_S_CALL_BARRING_SERVICE_DATA
{
    TUP_CHAR   aszPassword[CALL_D_MAX_STR_LENGTH];    /**< 密码限呼的密码 */
    TUP_UINT32 ulPasswordLen;                         /**< 密码长度 */
    TUP_UINT32 ulLimitType;                           /**< 密码限呼的类型 */
} CALL_S_CALL_BARRING_SERVICE_DATA;

/* END   add: [[IR.IPT.013] [2013/12/25] [zhanglusha 00219468]] */





/*for IMS forward*/
typedef struct tagCALL_S_HISTORY_INFO
{
    TUP_UINT32 ulCnt;
    TUP_CHAR   aszHistoryNum[CALL_D_MAX_HISTORY_NUM][CALL_D_128_STR_LENGTH];
} CALL_S_HISTORY_INFO;

typedef struct tagCALL_S_PAGING_GROUP
{
    TUP_CHAR aszGroupName[CALL_D_MAX_LENGTH_NUM];
    TUP_CHAR aszGroupNumber[CALL_D_MAX_LENGTH_NUM];
}CALL_S_PAGING_GROUP;

 /*add by l00214300@2014-3-7 for: DND模式*/
 typedef enum tagCALL_E_DND_TYPE
 {
     CALL_E_DND_TYPE_SERVER = 0,    /** 服务器DND */
     CALL_E_DND_TYPE_LOCAL,         /** 本地DND */
     CALL_E_DND_TYPE_BUTT
 } CALL_E_DND_TYPE;
 
 /**add by l00214300@2014-3-7 for: LOCAL DND处理模式*/
 typedef enum tagCALL_E_LOCALDND_TYPE
 {
     CALL_E_LOCALDND_TYPE_REJECT = 0,     /** 来电拒接 */
     CALL_E_LOCALDND_TYPE_RINGOFF,         /** 来电不振铃 */
     CALL_E_LOCALDND_TYPE_BUTT
 } CALL_E_LOCALDND_TYPE;


 /*DND数据结构*/
 typedef struct tagCALL_S_CALL_DND_DATA
 {
     TUP_BOOL bSwitch;                 /*是否是切换DND而发起的批量登记*/
     TUP_BOOL bNeedStartLocalDND;      /*批量发起成功后是否需要发起本地DND登记*/
     TUP_BOOL bSetenableLocalDND;      /*是否需要设置enableLocalDND*/
     CALL_E_LOCALDND_TYPE enLocalDNDType; /*本地DND类型*/
     TUP_CHAR acRecvNotifyApp[CALL_D_MAX_NAMESPACE];  
 } CALL_S_CALL_DND_DATA;



 /**前转类型*/
 typedef enum tatCALL_E_FORWARD_TYPE
 {
     CALL_E_FORWARD_TYPE_UNCONDITION,      /**无条件前转*/
     CALL_E_FORWARD_TYPE_ONBUSY,          /**遇忙前转*/
     CALL_E_FORWARD_TYPE_NOREPLY,          /**无应答前转*/
     CALL_E_FORWARD_TYPE_OFFLINE,           /**离线前转*/
     CALL_E_FORWARD_TYPE_BUTT
 } CALL_E_FORWARD_TYPE;
 
 /**前转目的类型定义*/
 typedef enum tagCALL_E_FORWARD_DEST_TYPE
 {
     CALL_E_FORWARD_DEST_TYPE_PHONENUM = 0,    /**号码*/
     CALL_E_FORWARD_DEST_TYPE_VOICEMAIL,   /**语音邮箱*/
     CALL_E_FORWARD_DEST_TYPE_BUTT
 } CALL_E_FORWARD_DEST_TYPE;
 
 /**前转开启关闭*/
 typedef enum tagCALL_E_FORWARD_ONOFF_TYPE
 {
     CALL_E_FORWARD_ONOFF_TYPE_ON = 0,
     CALL_E_FORWARD_ONOFF_TYPE_OFF,
     CALL_E_FORWARD_ONOFF_TYPE_BUTT
 } CALL_E_FORWARD_ONOFF_TYPE;

 /*前转信息结构体--界面传参数用*/
 typedef struct tagCALL_S_FORWARD_INFO
 {
     TUP_UINT32 ulSipAccountID;                               /*账户ID*/
     CALL_E_FORWARD_TYPE  enFwdType;                          /*前转类型*/
     CALL_E_FORWARD_ONOFF_TYPE enOnOff;                       /*开启或关闭    0开启 1关闭*/
     CALL_E_FORWARD_DEST_TYPE enDstType;                      /*目的类型  0号码  1语音邮箱*/
     TUP_CHAR    acDestNum[CALL_D_MAX_LENGTH_NUM];              /*前转目的号码 如果为语音邮箱，此项为空*/
     TUP_UINT32  ulResult;                                       /*前传结果，0成功，1失败，1初始值*/
 } CALL_S_FORWARD_INFO , *CALL_S_FORWARD_INFO_PTR;
 
 
 /**服务器订阅/取消 每个前转呼叫结果的结构*/
 typedef struct tagCALL_S_FORWARD_RESULT_INFO
 {
     TUP_UINT32 ulSipAccountID;                               /*账户ID*/
     TUP_UINT32 ulCallId;                                      /*呼叫ID*/
     CALL_E_FORWARD_TYPE  enFwdType;                          /*前转类型*/
     CALL_E_FORWARD_DEST_TYPE enDstType;                     /*目的类型*/
     CALL_E_FORWARD_ONOFF_TYPE enOnOff;                       /*开启或关闭    0开启 1关闭*/
     TUP_CHAR    acDestNum[CALL_D_MAX_LENGTH_NUM];              /*前转目的号码 如果为语音邮箱，此项为空*/
     TUP_UINT32  ulResult;                                       /*前传结果，0成功，1失败，1初始值*/
 } CALL_S_FORWARD_RESULT_INFO;


/* 服务器前转结果数据结构 ----返回给界面的数据*/
typedef struct tagCALL_S_FORWARD_SERVICE
{
    TUP_CHAR acRecvNotifyApp[CALL_D_MAX_NAMESPACE];                                          /*发送结果的目的地模块ID*/

    TUP_UINT32  ulFwdNum;                                                /**< 前转呼叫的个数 */
    CALL_S_FORWARD_RESULT_INFO  pstFwdResult[CALL_D_MAX_FOWARD_NUM];    /**< 前转结果 0成功 1失败 1为初始值*/
} CALL_S_FORWARD_SERVICE , *CALL_S_FORWARD_SERVICE_PTR;



typedef struct tagCALL_S_ACBCALL_REQ_INFO
{
    TUP_UINT32 ulSipAccountID;
    TUP_CHAR acRemoteNum[CALL_D_MAX_STR_LENGTH];  
}CALL_S_ACB_REQ_INFO;

 
 
 /*前转数据结构*/
 typedef struct tagCALL_S_CALL_FORWARD_SERVICE_DATA
 {
     TUP_CHAR    astDestNum[CALL_D_MAX_LENGTH_NUM];      /**< 前转号码*/
     TUP_UINT32 ulDestNumLen;                          /**< 前转号码长度*/
 } CALL_S_CALL_FORWARD_SERVICE_DATA;
 
 typedef struct tagCALL_S_HUNTGROUP_DATA
 {
     TUP_CHAR   aszGroupNumber[CALL_D_MAX_LENGTH_NUM]; 
 }CALL_S_HUNTGROUP_DATA;



 /* IPT业务数据联合体add by l00214300@2014-1-14 */
 typedef union tagCALL_U_IPT_DATA
 {
     CALL_S_ACB_SERVICE_DATA stACBData;
     CALL_S_CALL_BARRING_SERVICE_DATA stCallBarringData;
     CALL_S_CALL_FORWARD_SERVICE_DATA stCallForwardData;
     CALL_S_CALL_DND_DATA stDNDData; /*add by l00214300@2014-3-10 for DND*/
     CALL_S_HUNTGROUP_DATA stHuntGroupData;
 } CALL_U_IPT_DATA;
 
 /** IPT业务数据 */
 typedef struct tagCALL_S_IPT_DATA
 {
     TUP_CHAR  acRecvNotifyApp[CALL_D_MAX_NAMESPACE];
     CALL_E_SERVICE_CALL_TYPE enIPTServiceType; /**< IPT业务类型 */
     CALL_U_IPT_DATA unIPTData;                 /**< 业务数据联合体 */
     TUP_BOOL bCancelNextOpIfFail;              /**< 登记失败时是否取消下一个IPT业务 */
 } CALL_S_IPT_DATA;
 
 
 typedef struct tag_CALL_VVM_QUERY_MSG
 {
     TUP_UINT32 ulSipAccountID;
     TUP_UINT32 ulPageLimit;
     TUP_UINT32 ulOrderType;
     TUP_CHAR acPrevMsgID[CALL_D_64_STR_LENGTH];
 } CALL_S_VVM_QUERY_MSG;
 
 
 typedef struct tag_CALL_VVM_FWD_MSG
 {
     TUP_UINT32 ulSipAccountID;
     TUP_CHAR acMsgID[CALL_D_64_STR_LENGTH];
     TUP_CHAR acDstNum[CALL_D_MAX_LENGTH_NUM];
 } CALL_S_VVM_FWD_MSG;
 
 typedef struct tag_CALL_VVM_DEL_MSG
 {
     TUP_UINT32 ulSipAccountID;
     TUP_BOOL bIsDelAllMsg;
     TUP_CHAR acMsgID[CALL_D_64_STR_LENGTH];
 } CALL_S_VVM_DEL_MSG;

 /*信号音类型 */
typedef enum tagCALL_E_SIGTONE_TYPE
{
    CALL_E_SIGNAL_DIAL,    /**< 拨号音 */
    CALL_E_SIGNAL_BACK,    /**< 回铃音 */
    CALL_E_SIGNAL_BUSY,    /**< 忙音 */
    CALL_E_SIGNAL_ALERT,   /**< 告警音 */
    CALL_E_SIGNAL_WAIT,    /**< 呼等提示音 */
    CALL_E_SIGNAL_BUTT     /**< 未知类型 */
} CALL_E_SIGTONE_TYPE;
 

/** 呼控将接收到的UM 消息时通知界面该消息是UM事件*/
typedef enum tagCALL_E_UM_MSG_TYPE
{
    CALL_E_UM_TYPE_IM,                                     /**IM信息*/
    CALL_E_UM_TYPE_CONF,                                   /**会议信息*/
    CALL_E_UM_TYPE_BUTT
} CALL_E_UM_MSG_TYPE;


/** 呼控将接收到的UM IM消息转发给界面处理*/
typedef struct tagCALL_S_UM_MSG
{
    CALL_E_UM_MSG_TYPE  eMsgType;                       /** 该消息类型, 此类型可能以后会扩展*/
    TUP_UINT32 ulSipAccountID;                          /**< 接收该IM消息的账号ID */
    TUP_UINT32 ulUMContextLen;                          /**UM 消息Context长度 */
    TUP_CHAR szFromUserNum[CALL_D_MAX_STR_LENGTH];     /**UM 消息来源号码  */
    TUP_CHAR szSrcPrority[CALL_D_MAX_STR_LENGTH];       /** MsgExt.SrcPrority 字??段?*/
    TUP_CHAR szHasAttachment[CALL_D_MAX_STR_LENGTH];    /** MsgExt.HasAttachment 字段*/
    TUP_CHAR szHistoryMsgNotify[CALL_D_MAX_STR_LENGTH]; /*HistoryMsgNotify 字段*/
    TUP_CHAR acLocalMsgID [CALL_D_MAX_STR_LENGTH];     /** MsgExt.localMsgID 字段*/
    TUP_CHAR acMsgSvcType [CALL_D_MAX_STR_LENGTH];        /**< MsgExt.msgSvcType 值 */
    TUP_CHAR acMsgSort [CALL_D_MAX_STR_LENGTH];        /**< MsgExt.msgSort 值 */
    TUP_CHAR acMsgExt [CALL_D_MAX_STR_LENGTH];          /**< MsgExt字段 */
    TUP_CHAR acValidTime[CALL_D_MAX_STR_LENGTH];        /**< ValidTime字段 */
    TUP_CHAR acSubmitTime [CALL_D_MAX_STR_LENGTH];      /**< submitTime字段 */
    TUP_CHAR acAnonMsg [CALL_D_MAX_STR_LENGTH];         /**< anonMsg字段 */
    TUP_CHAR acNsImdn [CALL_D_MAX_STR_LENGTH];         /**< Ns:Imdn字段 */
    TUP_CHAR acMessageID [CALL_D_MAX_STR_LENGTH];       /**< imdn.Message-ID字段 */
    TUP_CHAR acContentType [CALL_D_MAX_STR_LENGTH];     /** content-type字段*/
    TUP_CHAR acEncode[CALL_D_MAX_STR_LENGTH];           /**< content-transfer-encoding字段 */
    TUP_CHAR acUMContext[CALL_D_MAX_UM_MSG_LENGTH];     /*UM内容*/
} CALL_S_UM_MSG;



/* BEGIN add: [eSpace 7900 V100R001C02B010] [IR.VoIP.007] [2013/1/18] [jiangtao/00196674]] 
   修改原因: 拒接回复信令类型宏定义 */
/* 拒接回复信令类型 */
typedef enum tagCALL_E_REJECTCALL_TYPE
{
    CALL_D_REJECTTYPE_486 = 1,
    CALL_D_REJECTTYPE_603,
    CALL_D_REJECTTYPE_404,
    CALL_D_REJECTTYPE_480,
    CALL_D_REJECTTYPE_BUTT    
}CALL_E_REJECTCALL_TYPE;
/* END   add: [eSpace 7900 V100R001C02B010] [IR.VoIP.007] [2013/1/18] [jiangtao/00196674]] */


typedef struct tagCALL_S_CONF_SUBJECT
{
    TUP_UINT32 ulConfID;
    TUP_CHAR acSubject[CALL_CONF_SUBJECT_MAX_STR_LEN];
}CALL_S_CONF_SUBJECT;

typedef struct tagCALL_S_CONF_CONNECT_RESULT
{
    TUP_UINT32 ulConfID;
    TUP_UINT32 ulResult;
}CALL_S_CONF_CONNECT_RESULT;


typedef struct tagCALL_S_CONF_ADDATTENDEE_RESULT
{
    TUP_UINT32 ulConfID;
    TUP_UINT32 ulResult;
    TUP_UINT32 ulAttendeeCount;
    TUP_CHAR *pcAttendee;
}CALL_S_CONF_ADDATTENDEE_RESULT;


typedef struct tagCALL_S_CONF_BETRANSFERTOCONF
{
    TUP_UINT32 ulConfID;
    TUP_UINT32 ulCallID;
    TUP_INT8 acGroupUri[CALL_D_MAX_LENGTH_NUM];
    CALL_E_SERVERCONF_TYPE eConfType;
}CALL_S_CONF_BETRANSFERTOCONF;




typedef struct tagCALL_S_CONF_TRANSFERTOCONF_RESULT
{
    TUP_UINT32 ulConfID;
    TUP_UINT32 ulCallID;
    TUP_UINT32 ulResult;
}CALL_S_CONF_TRANSFERTOCONF_RESULT;


typedef struct tagCALL_S_ONEKEY_TO_CONF_RESULT
{
    TUP_UINT32 ulCallID;
    TUP_UINT32 ulResult;
    CALL_E_CONFTYPE eConfType;
}CALL_S_ONEKEY_TO_CONF_RESULT,CALL_S_CONF_CONNECT_ONEKEY_TO_CONF_RESULT;


//媒体模式
typedef enum tagCALL_E_AUDIO_MODE
{
    CALL_AUDIO_MODE_NONE     =   0x00,
    CALL_AUDIO_MODE_LOCAL    =   0x01,   //pc本地模式
    CALL_AUDIO_MODE_VM_LOCAL =   0x02,   //云上本地音频模式
    CALL_AUDIO_MODE_TC       =   0x04,   //tc模式

    CALL_AUDIO_MODE_INVALID  =   0xFF
}CALL_E_AUDIO_MODE;

//TC文件播放值，每个值对应一个固定的文件，与瘦客户端值一一对应
typedef enum tagCALL_E_TC_FILE_VALUE
{
    CALL_TC_FILE_INCOMINGIM,        //来IM消息声音 incomingim
    CALL_TC_FILE_INCOMINGCALL,      //来电本地放音 incomingcall
    CALL_TC_FILE_CALLHOLD,          //保持本地放音 callhold
    CALL_TC_FILE_RINGBACKTONE,      //ringbacktone
    CALL_TC_FILE_NUM0,              //num0 0
    CALL_TC_FILE_NUM1,              //num1 1
    CALL_TC_FILE_NUM2,              //num2 2
    CALL_TC_FILE_NUM3,              //num3 3
    CALL_TC_FILE_NUM4,              //num4 4
    CALL_TC_FILE_NUM5,              //num5 5
    CALL_TC_FILE_NUM6,              //num6 6
    CALL_TC_FILE_NUM7,              //num7 7
    CALL_TC_FILE_NUM8,              //num8 8
    CALL_TC_FILE_NUM9,              //num9 9
    CALL_TC_FILE_NUMXING,           //numxin *
    CALL_TC_FILE_NUMJING,           //numjin #
    CALL_TC_FILE_CALLOUT,           //callout,
    CALL_TC_FILE_ROLLBACK           //rollback 回铃音
}CALL_E_TC_FILE_VALUE;


/* digitmap */
#define DM_MAX_DIALNUMBER_LEN            32        //号码最大长度

typedef struct tagDMRESULT
{
    TUP_UINT32 uiLength;    //匹配的长度或者替换后的号码长度
    TUP_CHAR pszNUM[DM_MAX_DIALNUMBER_LEN];  //替换后的号码，
}DMRESULT;


typedef struct tagCALL_S_VIDEOCONTROL
{
    TUP_UINT32 ulCallID;
    TUP_UINT32 ulOperation;
    TUP_UINT32 ulModule;
}CALL_S_VIDEOCONTROL;


typedef enum  tagCALL_E_MOBILE_AUIDO_ROUTE
{
    CALL_MBOILE_AUDIO_ROUTE_DEFAULT = 0,    /**< 蓝牙耳机>有线耳机>听筒 */
    CALL_MOBILE_AUDIO_ROUTE_LOUDSPEAKER = 1,     /**< 扬声器 */
    CALL_MOBILE_AUDIO_ROUTE_BLUETOOTH = 2,  /**< 蓝牙 */
    CALL_MOBILE_AUDIO_ROUTE_EARPIECE = 3,   /**< 听筒，用于获取，设置时保留，返回错误 */
    CALL_MOBILE_AUDIO_ROUTE_HEADSET = 4     /**< 耳机，用于获取，设置时保留，返回错误 */
}CALL_E_MOBILE_AUIDO_ROUTE;



typedef struct tagCALL_S_NETQUALITY_CHANGE
{
    TUP_UINT32 ulCallID;
    TUP_UINT32 uLNetError;  // 网络错误 0 : 没有错误 1 : 网络发端错误 2 : 网络收端错误 3 : 网络收发均错误。
    TUP_UINT32 ulNetLevel;  //网络质量等级，当net-error为0此值有效 [0,5]
}CALL_S_NETQUALITY_CHANGE;


typedef struct tagCALL_S_STATISTIC_NETINFO
{
    TUP_UINT32 ulCallID;
    TUP_UINT32 ulLost;  //丢包率 分子
    TUP_UINT32 ulDelay; //时延 毫秒
    TUP_UINT32 ulJitter;    //抖动 毫秒
}CALL_S_STATISTIC_NETINFO;


typedef enum  tagCALL_E_FILE_FORMAT
{
    CALL_FILE_FORMAT_PCM = 0,   //PCM文件格式
    CALL_FILE_FORMAT_WAV = 1,   //WAV文件格式，目前支持PCM_ALAW、PCM_ULAW、PCM
    CALL_FILE_FORMAT_AMR = 2,   //AMR文件格式，目前支持单通道AMR-NB
}CALL_E_FILE_FORMAT;

typedef struct tagCALL_S_AUDIO_PLAYFILE_ADDITIONINFO
{
    CALL_E_FILE_FORMAT enFileFormat;
} CALL_S_AUDIO_PLAYFILE_ADDITIONINFO;


typedef enum tagCALL_E_PRESET_EQ_TYPE
{
    CALL_E_PRESET_EQ_TYPE_RECOMMEND, /*推荐音效*/
    CALL_E_PRESET_EQ_TYPE_NORTHAMERICA,  /*北美音效*/
    CALL_E_PRESET_EQ_TYPE_AUSTRALIA, /*澳洲音效*/
    CALL_E_PRESET_EQ_TYPE_TIA920, /*TIA920音效*/
    CALL_E_PRESET_EQ_TYPE_BUTT
}CALL_E_PRESET_EQ_TYPE;


typedef struct tagCALL_S_VIDEO_OPERATION
{
    TUP_UINT32 ulCallID;
    TUP_UINT32 ulOperation;     //视频操作
    TUP_UINT32 ulRenderHanle;   //被操作的视频窗口句柄
    TUP_UINT32 ulType;            //远端或者本地 1：本地 2：远端
}CALL_S_VIDEO_OPERATION;


typedef struct tagCALL_S_VIDEO_FRAMESIZE_CHANGE
{
    TUP_UINT32 ulCallID;
    TUP_UINT32 ulWidth;     //解码宽
    TUP_UINT32 ulHeight;    //解码高
}CALL_S_VIDEO_FRAMESIZE_CHANGE;

typedef struct tagCALL_S_SESSION_CODEC
{
    TUP_UINT32 ulCallID;
    TUP_UINT32 ulMediaType;         //媒体类型：  0 : 未知类型。1 : 音频。  2 : 视频。 3 : 辅流
    TUP_UINT32 ulCodecType;         // codec类型： 0 : 未知类型。 1 : 编码器。2 : 解码器。
    TUP_CHAR   acCodecName[CALL_MAX_CODEC_NAME_LEN]; //编解码名称
}CALL_S_SESSION_CODEC;


typedef struct tagCALL_S_RECORDFILE_INFO
{
    TUP_UINT32 ulCaptureIndex;   //本地录音输入设备索引
    TUP_UINT32 ulFileSize;      //录制文件大小提示告警，如果录制文件超过改大小，会上抛通知，不影响录制，默认100M,视频录制需要
    TUP_UINT32 ulSampleFreq;    //录音采样率
    TUP_UINT32 ulRate;          //录音码率
    TUP_INT8   acCodecName[CALL_MAX_CODEC_NAME_LEN];   //录音编码
}CALL_S_RECORDFILE_INFO;


typedef struct tagCALL_S_SESSION_MODIFIED
{
    TUP_UINT32 ulCallID;
    TUP_BOOL bIsFocus;            /**是否带isfoucs标识，移动会议场景使用*/  
    TUP_INT8 acServerConfType[CALL_D_MAX_LENGTH_NUM];       /**会议类型，移动会议场景使用*/  
    TUP_INT8 acServerConfID[CALL_D_MAX_LENGTH_NUM];      /**会议ID, 移动会议场景使用*/
    TUP_UINT32 ulOrientType;    /** 移动视频横竖屏情况*/
    TUP_INT8 acLocalAddr[CALL_D_IP_LENGTH];   /**移动上报本地地址*/
    TUP_INT8 acRemoteAddr[CALL_D_IP_LENGTH];    /**移动上报远端地址*/
    CALL_E_REINVITE_TYPE enHoldType;    /**被叫控收到reinvie类型*/
}CALL_S_SESSION_MODIFIED;

typedef struct tagCALL_S_ACCOUNT_USER_NAME
{
    TUP_UINT32 ulAccountID;     /* 账户ID */
    TUP_CHAR acUserName[CALL_D_128_STR_LENGTH];  /* 用户名,用于入会时,没有UC账号的情况下上报 */
}CALL_S_ACCOUNT_USER_NAME;


#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif  /* __CALL_ADVANCED_DEF_H__*/

/** @}*/
