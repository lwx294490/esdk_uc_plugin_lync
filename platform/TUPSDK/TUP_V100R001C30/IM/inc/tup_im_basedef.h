#ifndef _TUP_IM_BASEDEF_H_
#define _TUP_IM_BASEDEF_H_

#include "tup_def.h"
#include "tup_im_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

//--------------------------------------------------------------长度定义 begin--------------------------------------------------------------

#define IM_D_GENEAL_LENGTH   (32)

#define IM_D_ICON_LENGTH      (1024)
/** \brief 帐号长度 */
#define IM_D_MAX_ACCOUNT_LENGTH (32) 

/** \brief 姓名长度 */
#define IM_D_MAX_NAME_LENGTH (512) 

/** \brief 部门名长度 */
#define IM_D_MAX_DEPTNAME_LENGTH (1024) 

/** \brief 密码长度 */
#define IM_D_MAX_PASSWORD_LENGTH (512) 

/** \brief 版本号长度 */
#define IM_D_MAX_VERSION_LENGTH (100) 

/** \brief 时间戳长度 */
#define IM_D_MAX_TIMESTAMP_LENGTH (15) 

/** \brief 号码长度 */
#define IM_D_MAX_PHONE_LENGTH (256) 

/** \brief 生日长度 */
#define IM_D_MAX_BIRTHDAY_LENGTH (64) 

/** \brief 描述文字长度 */
#define IM_D_MAX_DESC_LENGTH (1024) 

/** \brief 状态描述长度 */
#define IM_D_MAX_STATUS_DESCLEN (50)

/** \brief IP地址长度 */
#define IM_D_IP_LENGTH  (16)   

/** \brief 年龄长度 */
#define IM_D_AGE_LENGTH  (8)   

/** \brief 群ID长度 */
#define IM_D_GROUPID_LENGTH  (64)   

/** \brief 即时消息文字长度 */
#define IM_D_MAX_MESSAGE_LENGTH (1024*10) 

/** \brief 插件PROGID */
#define IM_D_MAX_PROGID_LENGTH (1024) 

/** \brief 插件参数长度 */
#define IM_D_MAX_PLUGINPARAM_LENGTH (1024) 

/** \brief 插件服务URL长度 */
#define IM_D_MAX_PLUGINURL_LENGTH (1024) 

/** \brief token 长度 */
#define IM_D_LOGIN_TOKEN_LENGTH (1024)

/** \brief 路径长度 */
#define IM_D_MAX_PATH_LENGTH (1024)

/** \brief 字符串最长 长度 */
#define IM_D_MAX_CHAR_LENGTH (1024*10)
//--------------------------------------------------------------长度定义 end--------------------------------------------------------------

//--------------------------------------------------------------枚举 begin--------------------------------------------------------------

/** \brief 回调同时的事件ID */
typedef enum tagIM_E_EVENT_ID
{
	IM_E_EVENT_IM_ORIGIN	= -1,					/**< 初始化 */
/*******************************************************************基本功能&通知*************************************************************************************/
    IM_E_EVENT_IM_HEARTBEAT_NOTIFY,     /**< 服务器心跳 */
    IM_E_EVENT_IM_SYSURLRET_NOTIFY,     /**< 系统地址返回通知 IM_S_SYSURLS_NOTIFY */
	IM_E_EVENT_IM_SYSTEMBULLETIN_NOTIFY,/**< 系统公告通知	 IM_S_SYSTEMBULLETIN_NOTIFY*/
	IM_E_EVENT_IM_KICKOUT_NOTIFY,		/**< 用户被踢通知	IM_S_CODECHAT_NOTIFY*/
	IM_E_EVENT_IM_SMS_NOTIFY,			/**< 新短信通知		IM_S_SENDSMS_NOTIFY*/
	IM_E_EVENT_IM_LOGOUT_NOTIFY,		/**< 用户退出		IM_S_LOGOUT_NOTIFY*/

/*******************************************************************联系人&好友*************************************************************************************/
    IM_E_EVENT_IM_ADDFRIEND_NOTIFY, 		/**< 对方添加自己好友成功通知 IM_S_ADDFRIEND_NOTIFY */
    IM_E_EVENT_IM_USERSTATUS_NOTIFY, 		/**< 好友状态变化通知 IM_S_USERSTATUS_NOTIFY */
	IM_E_EVENT_IM_USERINFOCHANGE_NOTIFY, 	/**< 好友信息变化通知  IM_S_USERINFOCHANGE_LIST_NOTIFY*/
	IM_E_EVENT_IM_GETIMGROUPDETAIL,			/**< 获取IM群组详情响应消息  IM_S_GETIMGROUPDETAIL_NOTIFY*/

/*******************************************************************固定群组*************************************************************************************/
    IM_E_EVENT_IM_APPLYJOIN_FIXEDGROUP_NOTIFY, 	/**< 群管理员收到用户加入固定群通知 (IM_S_APPLYJOINFIXEDGROUP_NOTIFY) */
    IM_E_EVENT_IM_APPLYJOIN_FIXEDGROUP_RESULT_NOTIFY, 	/**< 群成员收到管理员审批加入固定群通知的响应 IM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_MEMADD_NOTIFY, /**< 固定群添加成员通知 IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_MEMDEL_NOTIFY, /**< 群组中删除成员通知 IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_INFOCHG_NOTIFY, /**< 固定群信息修改通知 IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_FIXEDGROUP_OWNERCHG_NOTIFY, /**< 群组管理员变更通知 IM_S_IMGROUP_NOTIFY */
    IM_E_EVENT_IM_INVITEJOIN_FIXEDGROUPRESULT_NOTIFY, /**< 管理员收到用户对邀请加入固定群审批结果  IM_S_INVITEJOINFIXEDGROUPRESULT_NOTIFY */
	IM_E_EVENT_IM_RECEIVEINVITETO_FIXEDGROUP_NOTIFY, /**< 用户收到管理员邀请通知	IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY*/
	IM_E_EVENT_IM_RECEIVEJOIN_FIXEDGROUP_NOTIFY,	 /**< 管理员收到用户申请加入群组通知	IM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY*/

/*******************************************************************讨论组*************************************************************************************/
	IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_ADDMEMBER_NOTIFY,		/**< 讨论组成员列表添加成员变更消息	 IM_S_DISCUSSGROUP_NOTIFY*/
	IM_E_EVENT_IM_DISCUSSGROUP_MEMLIST_DELMEMBER_NOTIFY,		/**< 讨论组成员列表删除成员变更消息	 IM_S_DISCUSSGROUP_NOTIFY*/
	IM_E_EVENT_IM_DISCUSSGROUP_INFOCHANGE_NOTIFY,				/**< 群组信息更新	IM_S_DISCUSSGROUP_NOTIFY*/
	IM_E_EVENT_IM_DISCUSSGROUP_WASADDEDTOGROUP_NOTIFY,			/**< 被添加到群组通知	IM_S_DISCUSSGROUP_NOTIFY*/
	IM_E_EVENT_IM_DISCUSSGROUP_OWNERCHANGE_NOTIFY,				/**< 群组管理员变更	 IM_S_DISCUSSGROUP_NOTIFY*/

/*******************************************************************文件传输***********************************************************************************/
	IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY, 		/**< 收到文件传输请求	IM_S_P2PFILECHOOSE_NOTIFY*/
	IM_E_EVENT_IM_FILEPROCESS_NOTIFY,			/**< 文件传输进度通知	IM_S_FILEPROCESS_NOTIFY */
	IM_E_EVENT_IM_FILESTATISTIC_NOTIFY,			/**< 上报文件信息	    IM_S_P2PFILESTATISTIC_NOTIFY*/
	IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY, 	/**< 文件传输开始结果	IM_S_P2PFILE_RESULT_NOTIFY*/
	IM_E_EVENT_IM_P2PFILE_STOPTRESULT_NOTIFY, 	/**< 文件传输停止结果	IM_S_P2PFILE_RESULT_NOTIFY*/
	IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY,			/**<文件传输停止通知	IM_S_P2PFILESTATISTIC_NOTIFY*/

/***********************************************************************IM消息*************************************************************************************/
	IM_E_EVENT_IM_SENDIMINPUT_NOTIFY,			/**< 发送IM输入状态消息 	IM_S_SENDIMINPUT_NOTIFY*/	
	IM_E_EVENT_IM_CODECHAT_NOTIFY,				/**< 新即时消息通知 		IM_S_CODECHAT_NOTIFY*/	
	IM_E_EVENT_IM_CHATLIST_NOTIFY,				/**< 新即时消息批量通知(离线) 	IM_S_CHATLIST_NOTIFY*/

}IM_E_EVENT_ID;

/** \brief 登录结果 */
typedef enum tagIM_E_LOGIN_RESUL
{
    IM_E_LOGING_RESULT_TIMEOUT = -100,	/**< 消息超时 */
    IM_E_LOGING_RESULT_INTERNAL_ERROR = -1,   /**< 程序内部错误 */
    IM_E_LOGING_RESULT_SUCCESS = 0,    /**< 登录成功 */
    IM_E_LOGING_RESULT_FAILED = 1,    /**< 登录失败 */
    IM_E_LOGING_RESULT_PASSWORD_ERROR = 2,	/**< 密码错误 */
    IM_E_LOGING_RESULT_ACCOUNT_NOT_EXIST = 3,	/**< 帐号不存在 */
    IM_E_LOGING_RESULT_ALREADY_LOGIN = 4,	/**< 用户已存在 */          //TODO:待讨论这个是否和IM_E_LOING_RESULT_SUCCESS合并到一起
    IM_E_LOGING_RESULT_ACCOUNT_LOCKED = 5,	/**< 帐号已锁定 */
    IM_E_LOGING_RESULT_NEED_NEW_VERSION = 6,	/**< 需要下载新版本才允许登录 */
    IM_E_LOGING_RESULT_NOT_ACTIVE = 7,	/**< 用户未激活 */
    IM_E_LOGING_RESULT_ACCOUNT_SUSPEND = 8,	/**< 用户账号被暂停 */
    IM_E_LOGING_RESULT_ACCOUNT_EXPIRE = 9,	/**< 用户账号过期 */
    IM_E_LOGING_RESULT_DECRYPT_FAILED = 10,	/**< 消息解密失败 */
    IM_E_LOGING_RESULT_CERT_DOWNLOAD_FAILED = 11,	/**< 证书下载失败 */
    IM_E_LOGING_RESULT_CERT_VALIDATE_FAILED = 12,	/**< 证书校验失败 */
    IM_E_LOGING_RESULT_DNS_ERROR = 13	/**< 域名解析错误 */
}IM_E_LOGIN_RESULT;

    /** \brief 性别类型 */
typedef enum tagIM_E_GENDER_TYPE
{
    IM_E_GENDER_MALE = 0,		/**< 男 */
    IM_E_GENDER_FEMAIL = 1,		/**< 女*/
    IM_E_GENDER_UNKNOWN = 2			/**< 未设置 */
}IM_E_GENDER_TYPE;

/** \brief 群组加入权限标记 */
typedef enum tagIM_E_IMGROUP_JOIN_AUTH_FLAG
{
    IM_E_IMGROUP_JOIN_AUTO = 0,			/**< 自动加入 */
    IM_E_IMGROUP_JOIN_NEED_APPROVE = 1,			/**< 需要管理员审批 */
    IM_E_IMGROUP_JOIN_DENY = 2				/**< 不允许加入 */
}IM_E_IMGROUP_JOIN_AUTH_FLAG;

/** \brief 群组加入类型 */
typedef enum tagIM_E_IMGROUP_TYPE
{
    IM_E_IMGROUP_FIXGROUP_TYPE = 0,  /**< 固定群 */
    IM_E_IMGROUP_DISCUSSIONGROUP_TYPE = 1    /**< 讨论组 */
}IM_E_IMGROUP_TYPE;

/** \brief 用户在线状态 */
typedef enum tagIM_E_USER_ONLINESTATUS
{
    IM_E_STATUS_INIT = -1,		/**< 初始状态 */
    IM_E_STATUS_OFFLINE = 0,		/**< 离线 */
    IM_E_STATUS_ONLINE = 1,		/**< 在线 */
    IM_E_STATUS_HIDDEN = 2,		/**< 隐身 */
    IM_E_STATUS_BUSY = 3,		/**< 忙碌 */
    IM_E_STATUS_LEAVE = 4,		/**< 离开 */
    IM_E_STATUS_DONTDISTURB = 5			/**< 请勿打扰 */
}IM_E_USER_ONLINESTATUS;

/** \brief 客户端类型 */
typedef enum tagIM_E_CLIENT_TYPE 
{
	IM_E_CLIENT_TYPE_PC			= 0,		/**< PC终端 */
	IM_E_CLIENT_TYPE_MOBILE		= 1,		/**< 移动手机终端 */
	IM_E_CLIENT_TYPE_WEB		= 2,		/**< web客户端 */
	IM_E_CLIENT_TYPE_MOBLIEHD	= 3			/**< 移动PC终端 */
}IM_E_CLIENT_TYPE;

/** \brief IM消息类型 */
typedef enum tagIM_E_IM_CHAT_TYPE
{
    IM_E_IM_CHAT_TYPE_SINGLE = 0,	/**< 单聊 */
    IM_E_IM_CHAT_TYPE_FIXEDGROUP = 2,	/**< 固定群聊 */
    IM_E_IM_CHAT_TYPE_DISCUSSIONGROUP= 6,	/**< 多人会话讨论组 */
}IM_E_IM_CHAT_TYPE;

/** \brief IM消息发自哪里标记 */
typedef enum tagIM_E_IM_CHAT_SOURCE_FLAG
{
    IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG = 0,	/**< IM聊天窗口 */
    IM_E_IM_CHAT_SOURCE_FLAG_MULTIMEETING = 1,	/**< 数据会议聊天窗口 */
}IM_E_IM_CHAT_SOURCE_FLAG;

/** \brief IM消息内容格式 */
typedef enum tagIM_E_IM_CHAT_CONTENT_TYPE 
{
    IM_E_IM_CHAT_CONTENT_TYPE_TEXT = 0,	/**< 纯文本 */
    IM_E_IM_CHAT_CONTENT_TYPE_RICHTEXT = 1,	/**< 富文本 */
}IM_E_IM_CHAT_CONTENT_TYPE;

/** \brief IM聊天输入状态 */
typedef enum tagIM_E_IM_CHAT_STATUS
{
    IM_E_IM_CHAT_STATUS_CHATTING = 0,	 /**< 正在输入...*/
    IM_E_IM_CHAT_STATUS_STOPPED = 1		/**< 停止输入...*/
}IM_E_IM_CHAT_STATUS;

/** \brief IM消息类型 */
typedef enum tagIM_E_CHAT_TYPE
{
	IM_E_CHAT_TYPE_SINGLE = 0,	/**< 单聊 */
	IM_E_CHAT_TYPE_TEMP = 1,	/**< 临时单聊 */
	IM_E_CHAT_TYPE_FIXEDGROUP = 2,	/**< 固定群聊 */
	IM_E_CHAT_TYPE_TEMPGROUP = 3,	/**< 临时群聊 */
	IM_E_CHAT_TYPE_HELP = 4,	/**< 在线客服 */
	IM_E_CHAT_TYPE_APPNOTIFY = 5,	/**< 提醒信息 */
	IM_E_CHAT_TYPE_DISCUSSIONGROUP = 6,	/**< 多人会话讨论组 */
	IM_E_CHAT_TYPE_FILETRANSFER = 7,	/**< 文件传输通知 */
	IM_E_CHAT_TYPE_SYSTEMNOTIFY	= 10,	/**< 系统通知 */
	IM_E_CHAT_TYPE_SYSTEMAD	= 11,	/**< 系统广告 */
	IM_E_CHAT_TYPE_MULTIMEETINGS = 14,	/**< 融合会议通知 */
	IM_E_CHAT_TYPE_IMNOTIFY	= 20,	/**< IM通知消息 */
	IM_E_CHAT_TYPE_AUTOREPLAY = 101,	/**< 自动回复 */
}IM_E_CHAT_TYPE;

/** \brief IM媒体格式 */
typedef enum tagIM_E_IM_CHATMEDIA_TYPE
{
	tagIM_E_IM_CHATMEDIA_TYPE_TEXT = 0,	 /**< 纯文本 */
	tagIM_E_IM_CHATMEDIA_TYPE_AUDIO = 1, /**< 富媒体 语音 */
	tagIM_E_IM_CHATMEDIA_TYPE_VIDEO = 2, /**< 富媒体 视频 */
	tagIM_E_IM_CHATMEDIA_TYPE_IMAGE = 3, /**< 富媒体 图片 */
}IM_E_IM_CHATMEDIA_TYPE;

/** \brief 历史消息请求消息类型 */
typedef enum tagIM_E_IM_HISTORYMESSAGEMSG_TYPE 
{
	IM_E_IM_HISTORYMESSAGEMSG_TYPE_SINGLECHAT = 0,	/**< 单聊消息 */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE_GROUPCHAT = 1,	/**< 讨论组/固定群消息 */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE_SMS = 2,			/**< 短信消息 */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE_BULLETIN = 3,	/**< 系统公告 */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE_NOTIFY = 4,		/**< 其他（P2P文件传输，好友邀请，群组邀请，群组通知） */
}IM_E_IM_HISTORYMESSAGEMSG_TYPE;

/** \brief 接收到的短信消息的类型 */
typedef enum tagIM_E_SMS_NOTIFY_TYPE
{
	IM_E_SMS_NOTIFY_TYPE_RECVSMS = 0,			/**< 收到短信通知*/
	IM_E_SMS_NOTIFY_TYPE_SENDSMSSUCCESS =1 ,	/**< 发送短信成功通知*/
	IM_E_SMS_NOTIFY_TYPE_SMSRECEIPT = 3,        /**< 短信回执*/
	IM_E_SMS_NOTIFY_TYPE_SMSSENDFAIL = 4,       /**< 短信发送失败*/
	IM_E_SMS_NOTIFY_TYPE_SMSRECEIPTFAIL = 5,    /**< 短信回执失败*/
	IM_E_SMS_NOTIFY_TYPE_SMSSEND = 6,			/**< 发送短信（短信漫游时用）*/
}IM_E_SMS_NOTIFY_TYPE;

/** \brief 历史消息操作类型 */
typedef enum tagIM_E_IM_HISTORYMESSAGEOP_TYPE 
{
	IM_E_IM_HISTORYMESSAGEOP_TYPE_QUERYBEFORE,			/**< 查询MsgID之前的消息 */
	IM_E_IM_HISTORYMESSAGEOP_TYPE_FIRSTQUERY = 1,		/**< 首次查询，不需要MsgID */
}IM_E_IM_HISTORYMESSAGEOP_TYPE ;

/** \brief 群组查询类型 */
typedef enum tagIM_E_IMGROUPQUERYTYPE
{
    IM_E_IMGROUPQUERYTYPE_BY_NAME,       /**< 以名称查询 */
    IM_E_IMGROUPQUERYTYPE_BY_ID,         /**< 以群组ID查询 */
    IM_E_IMGROUPQUERYTYPE_BY_NAME_ID,   /**< 以名称和ID查询 */
}IM_E_IMGROUPQUERYTYPE;

/** \brief 查询用户信息的关键字类型 */
typedef enum tagIM_E_IMUSERQUERYTYPE
{
	IM_E_IMUSERQUERYTYPE_BY_PHONE = 0,    /**< 号码 */
	IM_E_IMUSERQUERYTYPE_BY_ACCOUNT = 1,  /**< 帐号 */
	IM_E_IMUSERQUERYTYPE_BY_BINDNO = 2,   /**< 绑定号码 */
	IM_E_IMUSERQUERYTYPE_BY_EMAIL = 3,    /**< 邮箱 */
	IM_E_IMUSERQUERYTYPE_BY_STAFFNO = 4   /**< 工号 */
}IM_E_IMUSERQUERYTYPE;

/** \brief 群组操作结果 */
typedef enum tagIM_E_FIXEDGROUP_OP_RESULT
{
    //32- 50群组相关
    IM_E_FIXEDGROUP_OP_RESULT_SUCCESS = 0,	/**< 成功 */
    IM_E_FIXEDGROUP_OP_RESULT_FAILED = 1,	/**< 失败 */
    IM_E_FIXEDGROUP_OP_RESULT_REACH_MAXIMUM = 32	/**< 成员群组数目已经达到最大 */,			
    IM_E_FIXEDGROUP_OP_RESULT_MEMBER_REACH_MAXIMUM = 33,	/**< 组内成员达到最大数目 */			
    IM_E_FIXEDGROUP_OP_RESULT_DB_ERROR = 34,	/**< 数据库异常的返回码 */				
}IM_E_FIXEDGROUP_OP_RESULT;

/** \brief 转移分组类型 */
typedef enum tagIM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE
{
    IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE_MOVE = 0,	/**< 移动到新分组 */
    IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE_COPY = 1,	/**< 复制到新分组 */
}IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE;

/** \brief 企业通讯录查询排序类型 */
typedef enum tagIM_E_ADDRBOOKQUERY_ORDERTYPE
{
	IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_PINYIN	= 0,	/**< 按拼音排序 */
	IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_STAFFNO	= 1,	/**< 按工号号排序 */
	IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_NATIVENAME = 3	/**< 按nativename排序  */
}IM_E_ADDRBOOKQUERY_ORDERTYPE;

/** \brief 企业通讯录查询排序方式*/
typedef enum tagIM_E_ADDRBOOKQUERY_ORDERMODEL
{
	IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_ASC	= 0,	/**< 升序 */
	IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_DESC	= 1,	/**< 降序 */
}IM_E_ADDRBOOKQUERY_ORDERMODEL;

/** \brief 群组通知 */
typedef enum tagIM_E_IMGROUP_NOTIFY_TYPE
{
    IM_E_FIXEDGROUP_NOTIFY_ADDMEMBER = 0,	/**< 群组中新增成员通知 */
    IM_E_FIXEDGROUP_NOTIFY_DELMEMBER = 1,	/**< 群组中删除成员 */
    IM_E_FIXEDGROUP_NOTIFY_DISMISS = 2,    /**< 群组解散 */
    IM_E_FIXEDGROUP_NOTIFY_INFOCHANGE = 3,	/**< 群组信息更新 */
    IM_E_FIXEDGROUP_NOTIFY_OWNER_CHANGE = 4,    /**< 群组管理员变更 */
	IM_E_FIXEDGROUP_NOTIFY_WAS_ADDEDTOGROUP = 5, /**< 被添加到群组通知 */
    IM_E_FIXEDGROUP_NOTIFY_ADDPHONEMEMBER = 6, /**< 群组中新增号码成员通知 */
    IM_E_FIXEDGROUP_NOTIFY_DELPHONEMEMBER = 7, /**< 群组中删除号码成员通知 */
}IM_E_IMGROUP_NOTIFY_TYPE;

typedef enum tagIM_E_EXITSTATUS
{
	IM_E_EXITSTATUS_NORMALOFFLINE,     /**<被踢下线 */
	IM_E_EXITSTATUS_PAUSEOFFLINE = 2,  /**<账号被服务端暂停，下线 */
	IM_E_EXITSTATUS_OVERDUEOFFLINE = 3 /**<账号过期下线 */
}IM_E_EXITSTATUS;

typedef enum tagIM_E_SYNC_TYPE
{
	IM_E_SYNC_TYPE_VALID = 0,      /**< 有效 */
	IM_E_SYNC_TYPE_INVALID = 1, /**< 无效 */
}IM_E_SYNC_TYPE;
//--------------------------------------------------------------枚举 end--------------------------------------------------------------

//--------------------------------------------------------------方法入参结构体 begin--------------------------------------------------------------

/** \brief 好友信息 */
typedef struct tagIM_S_USERINFO
{
        TUP_INT64 staffID;									/**< 成员ID */
        TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];			/**< 成员账号 */ 
        TUP_CHAR staffNO[IM_D_MAX_ACCOUNT_LENGTH];			/**< 成员工号 */ 
        TUP_CHAR name[IM_D_MAX_NAME_LENGTH];				/**< 用户名 */
        TUP_CHAR nativeName[IM_D_MAX_NAME_LENGTH];			/**< 本地名字 */
		TUP_CHAR qPinYin[IM_D_MAX_NAME_LENGTH];				/**< 全拼	*/
        IM_E_GENDER_TYPE gender;							/**< 性别 */
        TUP_CHAR birthday[IM_D_MAX_BIRTHDAY_LENGTH];		/**< 生日 */
        TUP_CHAR age[IM_D_AGE_LENGTH];						/**< 年龄 */
        TUP_CHAR bindNO[IM_D_MAX_PHONE_LENGTH];				/**< 绑定号码 */
        TUP_CHAR mobile[IM_D_MAX_PHONE_LENGTH];				/**< 手机号码 */
        TUP_CHAR homePhone[IM_D_MAX_PHONE_LENGTH];			/**< 家庭电话 */
        TUP_CHAR officePhone[IM_D_MAX_PHONE_LENGTH];		/**< 办公电话 */
        TUP_CHAR shortPhone[IM_D_MAX_PHONE_LENGTH];			/**< 短号 */
        TUP_CHAR otherPhone[IM_D_MAX_PHONE_LENGTH];			/**< 其他电话 */
        TUP_CHAR voip[IM_D_MAX_PHONE_LENGTH];				/**< VOIP号码 */
		TUP_CHAR ipPhone[IM_D_MAX_PHONE_LENGTH];			/**< 绑定IPPhone号码 */
        TUP_CHAR fax[IM_D_MAX_PHONE_LENGTH];				/**< 传真 */
        TUP_CHAR email[IM_D_MAX_DESC_LENGTH];				/**< email地址 */
        TUP_CHAR webSite[IM_D_MAX_DESC_LENGTH];				/**< 个人网站 */
        TUP_CHAR signature[IM_D_MAX_DESC_LENGTH];			/**< 用户签名 */
        TUP_CHAR desc[IM_D_MAX_DESC_LENGTH];				/**< 描述 */
        TUP_CHAR address[IM_D_MAX_DESC_LENGTH];				/**< 地址 */
        TUP_CHAR imageID[IM_D_MAX_DESC_LENGTH];				/**< 头像ID */
        TUP_CHAR postalcode[IM_D_MAX_DESC_LENGTH];			/**< 邮政编码 */
		TUP_BOOL isSecrecy;									/**< 是否保密成员 */
        TUP_CHAR title[IM_D_MAX_DESC_LENGTH];				/**< 职务 */
		TUP_INT32 deptID;									/**< 部门ID */
        TUP_CHAR deptNameEn[IM_D_MAX_NAME_LENGTH];			/**< 部门英文名称 */
        TUP_CHAR deptNameCn[IM_D_MAX_NAME_LENGTH];			/**< 部门中文名称 */
        TUP_CHAR imageSyncTime[IM_D_MAX_TIMESTAMP_LENGTH];	/**< 头像同步时间戳 */
        TUP_CHAR oldAccount[IM_D_MAX_ACCOUNT_LENGTH];		/**< 老账号 */
        TUP_CHAR state[IM_D_MAX_DESC_LENGTH];				/**< 同步状态 */
        TUP_CHAR modifyTime[IM_D_MAX_TIMESTAMP_LENGTH];     /**< 最后更新时间 */
}IM_S_USERINFO;

/** \brief 联系人信息 */
typedef struct tagIM_S_CONTACTNFO
{	
    TUP_INT64 id;				/**< 联系人ID */
    TUP_INT64 staffID;		/**< staff ID(与IM_S_USERINFO关联) */
    TUP_CHAR name[IM_D_MAX_NAME_LENGTH];			/**< 姓名 */
    TUP_CHAR nickName[IM_D_MAX_NAME_LENGTH];		/**< 昵称 */
    TUP_CHAR foreignName[IM_D_MAX_NAME_LENGTH];	/**< 英文名 */
    TUP_CHAR birthday[IM_D_MAX_BIRTHDAY_LENGTH];		/**< 生日 */
    IM_E_GENDER_TYPE		gender;			/**< 性别 */
    TUP_CHAR corpName[IM_D_MAX_NAME_LENGTH];		/**< 公司名 */
    TUP_CHAR deptName[IM_D_MAX_NAME_LENGTH];		/**< 部门名称 */
    TUP_CHAR title[IM_D_MAX_DESC_LENGTH];			/**< 头衔 */
    TUP_CHAR mobile[IM_D_MAX_PHONE_LENGTH];			/**< 手机号 */
    TUP_CHAR officePhone[IM_D_MAX_PHONE_LENGTH];	/**< 办公号码 */
    TUP_CHAR homePhone[IM_D_MAX_PHONE_LENGTH];		/**< 家庭电话 */
    TUP_CHAR otherPhone[IM_D_MAX_PHONE_LENGTH];     /**< 其他号码 */
    TUP_CHAR fax[IM_D_MAX_PHONE_LENGTH];			/**< 传真 */
    TUP_CHAR email[IM_D_MAX_DESC_LENGTH];			/**< 电子邮箱 */
    TUP_CHAR webSite[IM_D_MAX_DESC_LENGTH];		/**< 首页 */
    TUP_CHAR imNO[IM_D_MAX_DESC_LENGTH];			/**< 聊天工具号码 */
    TUP_CHAR address[IM_D_MAX_DESC_LENGTH];		/**< 地址 */
    TUP_CHAR desc[IM_D_MAX_DESC_LENGTH];			/**< 描述 */
    TUP_CHAR postalcode[IM_D_MAX_DESC_LENGTH];		/**< 邮编 */
    TUP_CHAR state;			/**< 同步状态(增量同步时用到) */
}IM_S_CONTACTNFO;

/** \brief 分组信息 */
typedef struct tagIM_S_USERGROUPINFO
{
    TUP_INT64 id;	/**< 组ID */
    TUP_CHAR name[IM_D_MAX_NAME_LENGTH];  /**< 组名称 */
    TUP_INT64 index; /**< 组序号 */
    TUP_CHAR state;	 /**< 同步状态(增量同步时用到) */
}IM_S_USERGROUPINFO;

/** \brief 分组和成员对应关系 */
typedef struct tagIM_S_USERGROUPMEMBERINFO
{
    TUP_INT64 groupID;	/**< 组ID(IM_S_USERGROUPINFO的id字段) */
    TUP_INT64 contactID;	/**< 联系人ID(IM_S_CONTACTNFO的id字段)*/
    TUP_CHAR state;		/**< 同步状态(增量同步时用到) */
}IM_S_USERGROUPMEMBERINFO;

/** \brief 固定群信息 */
typedef struct tagIM_S_IMGROUPINFO
{
        TUP_CHAR	id[IM_D_GROUPID_LENGTH];		/**< 群ID */
        TUP_CHAR	name[IM_D_MAX_NAME_LENGTH];			/**< 群名称 */
        TUP_INT32	capacity;		/**< 群大小 */
        TUP_CHAR	manifesto[IM_D_MAX_DESC_LENGTH];		/**< 公告 */
        TUP_CHAR	desc[IM_D_MAX_DESC_LENGTH];			/**< 简介 */
        TUP_CHAR	owner[IM_D_MAX_ACCOUNT_LENGTH];       /**< 管理员 */
        IM_E_IMGROUP_JOIN_AUTH_FLAG	autoJoinFlag;	/**< 加入群是否可以审批 */
}IM_S_IMGROUPINFO;

typedef struct tagIM_S_GroupUserInfo
{
    TUP_INT64 staffID;		/**< 群成员Staff ID */
    TUP_CHAR  state;			/**< 状态 */
    IM_S_USERINFO userInfo;		/**< 成员信息 */
}IM_S_GroupUserInfo;

/** \brief 群组成员列表信息 */
typedef struct tagIM_S_GROUPUSERLIST
{
    TUP_BOOL  isSyncAll;	/**< 是否全量同步 */
    TUP_CHAR  timpstamp[IM_D_MAX_TIMESTAMP_LENGTH];	/**< 同步时间戳，19000000000000（年月日时分秒） */
    TUP_CHAR  groupID[IM_D_GROUPID_LENGTH];		/**< 群ID */
    TUP_S_LIST* memberInfo;		    /**< 成员信息 IM_S_GroupUserInfo */
}IM_S_GROUPUSERLIST;

/** \brief 同步固定群列表时的数据 */
typedef struct tagIM_S_SYNC_IMGROUPINFO
{
    IM_S_IMGROUPINFO groupInfo; /**< 群组信息 */
    IM_E_IMGROUP_TYPE  groupType;      /**< 固定群和讨论组标记 */
    TUP_CHAR			state;			/**< 状态 *///TODO:修改成枚举
}IM_S_SYNC_IMGROUPINFO;

/** \brief 部门信息 */
typedef struct tagIM_S_DEPTINFO
{
    TUP_INT64 deptID;				/**< 部门ID */
    TUP_INT64 parentDeptID;		/**< 上级部门ID */
    TUP_INT64 deptLevel;			/**< 部门层级 */
    TUP_CHAR deptName[IM_D_MAX_DEPTNAME_LENGTH];			/**< 部门名称 */
    TUP_CHAR fullDeptName[IM_D_MAX_DEPTNAME_LENGTH];		/**< 部门全称 */
}IM_S_DEPTINFO;

/** \brief 登录请求数据 */
typedef struct tagIM_S_LOGIN_ARG
 {
	 TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; 	 /**< 帐号(必填) */
	 TUP_CHAR   password[IM_D_MAX_PASSWORD_LENGTH];  /**< 密码(必填) */
     TUP_CHAR   version[IM_D_MAX_VERSION_LENGTH];  /**< 版本号(选填) */
 }IM_S_LOGIN_ARG;

/** \brief 登录响应数据 */
typedef struct tagIM_S_LOGIN_ACK
 {
     TUP_BOOL result; /**< 登录结果 */
	 IM_E_LOGIN_RESULT reason; 	 /**< 登录结果详情（可以在result为false的时候获取失败原因） */
     TUP_INT32 retryTimes;  /**< 登录重试剩余次数(result为IM_E_LOGING_RESULT_ACCOUNT_LOCKED有效) */
     TUP_INT32 lockInterval;  /**< 帐号被锁定剩余时间（单位：分钟） (result为IM_E_LOGING_RESULT_ACCOUNT_LOCKED有效*/
 }IM_S_LOGIN_ACK;

/** \brief 获取通讯录请求 */
typedef struct tagIM_S_GETCONTACTLIST_ARG
 {
	 TUP_BOOL	isSyncAll; 	 /**< 是否增量同步(必填) */
	 TUP_CHAR   timestamp[IM_D_MAX_TIMESTAMP_LENGTH];  /**< 增量同步时间戳，19000000000000（年月日时分秒） (isSyncAll为TUP_TRUE时必填) */
 }IM_S_GETCONTACTLIST_ARG;

/** \brief 获取通讯录请求 */
typedef struct tagIM_S_GETCONTACTLIST_ACK
 {
     TUP_BOOL result; /**< 操作结果 */
	 TUP_BOOL isSyncAll; 	 /**< 本次同步是否是增量同步 */
	 TUP_CHAR   timestamp[IM_D_MAX_TIMESTAMP_LENGTH];  /**< 增量同步时间戳，19000000000000（年月日时分秒） (isSyncAll为TUP_TRUE时有效) */
     TUP_S_LIST* userList; /**< 好友列表，IM_S_USERINFO */
     TUP_S_LIST* contactList;  /**< 自定义联系人列表，IM_S_CONTACTNFO */
     TUP_S_LIST* userGroupList; /**< 好友分组，IM_S_USERGROUPINFO */
     TUP_S_LIST* userGroupMemberList; /**< 好友分组和联系人对应关系，IM_S_USERGROUPMEMBERINFO */
     TUP_S_LIST* imGroupList; /**< 固定群列表 IM_S_IMGROUPINFO*/
 }IM_S_GETCONTACTLIST_ACK;

typedef struct tagIM_S_GETSERVICEPROFILEARG
{
    TUP_BOOL isSyncAll;      /**是否全量同步 */
    TUP_BOOL needIcon;       /**是否需要图标 */
    TUP_BOOL isVpnAccess;    /**是否VPN接入  */
	TUP_CHAR timestamp[IM_D_MAX_TIMESTAMP_LENGTH];  /**< 增量同步时间戳，19000000000000（年月日时分秒） (isSyncAll为TUP_TRUE时有效) */
    TUP_CHAR localIP[IM_D_IP_LENGTH];    /**本地IP地址 */
}IM_S_GETSERVICEPROFILEARG;

typedef struct tagIM_S_CONFIGINFO
{
    TUP_CHAR name[IM_D_GENEAL_LENGTH];		/** \brief 名字 */
    TUP_CHAR value[IM_D_GENEAL_LENGTH];		/** \brief 值 */
}IM_S_CONFIGINFO;

/** \brief 工作台面板信息 */
typedef struct tagIM_S_PANELINFO
{
    TUP_INT64 id;							/**< 面板ID */
    TUP_INT64 indexNO;						/**< 序号 */
    TUP_CHAR name[IM_D_MAX_NAME_LENGTH];	/**< 名称 */
    IM_E_SYNC_TYPE state;					/**< 状态 */
}IM_S_PANELINFO;

/** \brief 组件信息 */
typedef struct tagIM_S_COMPONETINFO
{
    TUP_INT64 id;								/**< 组件ID */
    TUP_INT64 panelID;							/**< 对应面板ID */
    TUP_INT64 functionID;						/**<  对应功能位 */
    TUP_INT64 indexNO;							/**<  序号 */
    TUP_INT64 serverID;							/**< 对应服务ID  */
    TUP_CHAR progID[IM_D_MAX_PROGID_LENGTH];	/**< progid */
    TUP_CHAR name[IM_D_MAX_NAME_LENGTH];		/**< 插件名称 */
    TUP_CHAR type[IM_D_GENEAL_LENGTH];			/**< 插件类型 */
	TUP_CHAR path[IM_D_MAX_PATH_LENGTH];		/**< 插件路径 */
	TUP_CHAR icon[IM_D_ICON_LENGTH];			/**< 插件图标*/
    TUP_CHAR protocol[IM_D_GENEAL_LENGTH];		/**< 协议类型 */
    IM_E_SYNC_TYPE state;						/**< 状态 */
}IM_S_COMPONETINFO;

    /** \brief 插件参数信息 */
typedef struct tagIM_S_COMPONETPARAMINFO
{
    TUP_CHAR progID[IM_D_MAX_PROGID_LENGTH];	/**< progid */
    TUP_CHAR key[IM_D_MAX_PLUGINPARAM_LENGTH];
    TUP_CHAR value[IM_D_MAX_PLUGINPARAM_LENGTH];
}IM_S_COMPONETPARAMINFO;

/** \brief 服务器信息 */
typedef struct tagIM_S_SERVERINFO
{
    TUP_INT64 id;									/**< server ID */
    TUP_CHAR name[IM_D_MAX_NAME_LENGTH];			/**< 名称 */
    TUP_CHAR address[IM_D_MAX_PLUGINURL_LENGTH];	/**< 地址 */
}IM_S_SERVERINFO;

typedef struct tagIM_S_DATACONFADDRINFO
{
    TUP_CHAR dataConfAddr[IM_D_GENEAL_LENGTH];
}IM_S_DATACONFADDRINFO;

typedef struct tagIM_S_SERVICEPROFILEACK
{
    TUP_BOOL syncType;									/**< 是否全量同步 */
    TUP_BOOL isSetIpphone;								/**< 是否设置了IPPhone */
    TUP_BOOL isJointUser;								/**< 是否设置联动 */
    TUP_BOOL bindChange;								/**< IP变化是否绑定切换 */
    TUP_INT32   sipExpires;								/**< sip注册心跳时间 */
    TUP_CHAR    timestamp[IM_D_MAX_TIMESTAMP_LENGTH];	/**< 服务器时间戳 */	
    TUP_CHAR	ipPhone[IM_D_GENEAL_LENGTH];			/**< 绑定IPPhone号码 */
    TUP_CHAR	eConsoleAddr[IM_D_GENEAL_LENGTH];		/**< eConsole地址 */
    TUP_CHAR	sipAccount[IM_D_GENEAL_LENGTH];			/**< sip帐号 */
    TUP_CHAR	sipPassword[IM_D_GENEAL_LENGTH];		/**< sip注册号码 */
    TUP_CHAR	sipServer[IM_D_GENEAL_LENGTH];			/**< sip服务器地址 (含端口)*/
    TUP_CHAR	sipicscfDomainName[IM_D_GENEAL_LENGTH]; /**< ICSCF域名 */
    TUP_CHAR	sipCountryCode[IM_D_GENEAL_LENGTH];		/**< 国家码 */
    TUP_CHAR	sipOutgoingAccCode[IM_D_GENEAL_LENGTH]; /**< 外呼接入码 */
    TUP_CHAR	sipInfoAccCode[IM_D_GENEAL_LENGTH];		/**< 业务接入码 */
    TUP_CHAR	sipUcPassword[IM_D_GENEAL_LENGTH];		/**<   */
    TUP_CHAR	sipNetType[IM_D_GENEAL_LENGTH];			/**< 组网类型（IMS/NGN） */
    TUP_S_LIST* funcIDList;								/**< 功能列表 int */
    TUP_S_LIST* configList;								/**< 配置信息列表 IM_S_CONFIGINFO */
    TUP_S_LIST* panelList;								/**< 面板信息列表 IM_S_PANELINFO */
    TUP_S_LIST* serverList;								/**< 插件服务器列表 IM_S_SERVERINFO */
    TUP_S_LIST* componentList;							/**< 插件信息列表 IM_S_COMPONETINFO*/
    TUP_S_LIST* componentParamList;						/**< 插件参数信息列表 IM_S_COMPONETPARAMINFO */
    TUP_S_LIST* dataConfAddrList;						/**< 数据会议地址列表 IM_S_DATACONFADDRINFO */
}IM_S_SERVICEPROFILEACK;

typedef struct tarIM_S_GETUSERINFOARG
{
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];		/**< 帐号 */
    TUP_INT64 staffID;								/**< staffid */
}IM_S_GETUSERINFOARG;

/** \brief 获取群组列表请求 */
typedef struct tagIM_S_GETIMGROUPLIST_ARG
 {
     TUP_BOOL		   isNeedAmount;					/**< 是否需要返回总数 (必填)*/ 
     TUP_INT32		   offset;							/**< 查询偏移量 (选填)*/ 
     TUP_INT32		   count;							/**< 查询数目(必填) */ 
     TUP_CHAR          queryKey[IM_D_GENEAL_LENGTH] ;	/**< 关键字 (必填)*/ 
     IM_E_IMGROUPQUERYTYPE  queryType;					/**< 群组查询类型 (必填)*/
 }IM_S_GETIMGROUPLIST_ARG;

/** \brief 获取群组列表响应 */
typedef struct tagIM_S_GETIMGROUPLIST_ACK
 {
     TUP_INT32 recordAmount;	/**< 总记录数 */ 
     TUP_INT32 offset;			/**< 查询偏移量 */ 
     TUP_INT32 count;			/**< 查询数目 */ 
     TUP_S_LIST* imGroupList;	/**< 群组列表 IM_S_IMGROUPINFO */ 
 }IM_S_GETIMGROUPLIST_ACK;

/** \brief 添加好友和联系人分组请求 */
typedef struct tagIM_S_ADDUSERGROUP_ARG
 {
        TUP_CHAR name[IM_D_MAX_NAME_LENGTH];  /**< 分组名称(必填) */
        TUP_INT32 index; /**< 序号(必填，如果不需要分组排序，则默认填-1) */
 }IM_S_ADDUSERGROUP_ARG;

/** \brief 添加好友和联系人分组响应 */
typedef struct tagIM_S_ADDUSERGROUP_ACK
 {
     TUP_BOOL result; /**< 操作结果 */
     TUP_INT64 id; /**< 分组号 */
 }IM_S_ADDUSERGROUP_ACK;

/** \brief 修改好友和联系人分组请求 */
typedef struct tagIM_S_MODUSERGROUP_ARG
 {
     TUP_INT64 id; /**< 分组号(必填) */
     TUP_CHAR name[IM_D_MAX_NAME_LENGTH];  /**< 分组名称(必填) */
     TUP_INT32 index; /**< 序号(必填，如果不需要分组排序，则默认填-1) */
 }IM_S_MODUSERGROUP_ARG;

/** \brief 添加好友请求 */
typedef struct tagIM_S_ADDFRIEND_ARG
 {
     TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; /**< 好友帐号 (必填)*/
     TUP_INT64 groupID; /**< 好友分组ID(必填) */
     TUP_CHAR displayName[IM_D_MAX_NAME_LENGTH];  /**< 呈现给好友的显示名(可选) */
 }IM_S_ADDFRIEND_ARG;

/** \brief 添加好友响应 */
typedef struct tagIM_S_ADDFRIEND_ACK
 {
     TUP_BOOL result; /**< 操作结果 */
     TUP_INT64 contactID; /**< 联系人ID */
 }IM_S_ADDFRIEND_ACK;

/** \brief 添加自定义联系人 */
typedef struct tagIM_S_ADDCONTACT_ARG
 {
     IM_S_CONTACTNFO contact; /**< 联系人信息，添加联系人时id_不用填，添加成功后返回 (必填) */
     TUP_INT64 groupID; /**< 添加到的分组ID(必填) */
 }IM_S_ADDCONTACT_ARG;

/** \brief 添加自定义联系人响应 */
typedef struct tagIM_S_ADDCONTACT_ACK
 {
     TUP_BOOL result; /**< 操作结果 */
     TUP_INT64 contactID; /**< 联系人ID */
 }IM_S_ADDCONTACT_ACK;

/** \brief 修改自定义联系人 */
typedef struct tagIM_S_MODCONTACT_ARG
 {
     IM_S_CONTACTNFO contact; /**< 联系人信息，id必填 (必填) */
 }IM_S_MODCONTACT_ARG;

/** \brief 从某一个分组中删除好友或/联系人 */
typedef struct tagIM_S_DELCONTACT_ARG
 {
     TUP_INT64 contactID; /**< 联系人ID(必填) */
     TUP_INT64 groupID; /**< 分组ID(必填) */
 }IM_S_DELCONTACT_ARG;

/** \brief 修改好友/联系人分组 */
typedef struct tagIM_S_MODCONTACTGROUP_ARG
 {
        TUP_INT64 contactID; /**< 联系人ID(必填) */ 
        TUP_INT64 oldGroupID; /**< 原组ID(必填) */ 
        TUP_INT64 newGroupID; /**< 新组ID(必填) */ 
		IM_E_CONTACTGROUP_MOVEUSER_GROUPTYPE type; /**< 移动还是复制 */ 
 }IM_S_MODCONTACTGROUP_ARG;

/** \brief 发送IM消息请求 */
typedef struct tagIM_S_SENDIM_ARG
{
	TUP_INT			regionID;							/**< 区域ID 服务器用 (可选)*/
    IM_E_IM_CHAT_TYPE chatType;							/**< IM消息类型(必填) */
	IM_E_IM_CHAT_SOURCE_FLAG sourceFlag;				/**< IM消息发自哪里(必填) */
	IM_E_IM_CHAT_CONTENT_TYPE contentType;				/**< IM消息内容格式(必填)*/
	TUP_CHAR		origin[IM_D_MAX_ACCOUNT_LENGTH];	/**< 发送方账号(必填)*/
    TUP_CHAR		target[IM_D_MAX_ACCOUNT_LENGTH];	/**< 接收方账号(必填) */
    TUP_CHAR		groupID[IM_D_GROUPID_LENGTH];		/**< 群组ID（固定群和讨论组必填）*/
    TUP_CHAR		content[IM_D_MAX_MESSAGE_LENGTH];	/**< IM消息内容(必填)*/
    TUP_CHAR		displayname[IM_D_MAX_NAME_LENGTH];	/**< 发送方名字(可选) */
    TUP_INT64		utcStamp;							/**< UTC时间 (可选) */
}IM_S_SENDIM_ARG;

/** \brief 已读消息设置请求 */
typedef struct tagIM_S_SETMESSAGEREAD_ARG
{
	TUP_S_LIST* messageinfo;						/**< 已读消息设置消息格式 IM_S_MESSAGEINFO */
}IM_S_SETMESSAGEREAD_ARG;

/** \brief 获取消息漫游请求 */
typedef struct tagIM_S_QUERYHISTORYMESSAGE_ARG
{
	IM_E_IM_HISTORYMESSAGEOP_TYPE opType;					/**< 操作类型 */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE msgType;					/**< 请求的消息类型 */
	TUP_CHAR sender[IM_D_MAX_PHONE_LENGTH];			/**< 消息发送方，msgType为0时填写消息发送者，msgType为1时填写群ID，msgType为2时为短信号码，msgType为3时忽略 */
	TUP_INT64 msgID;								/**< 消息ID，首次查询忽略该字段 */
	TUP_INT count;									/**< 查询的消息条数 */
}IM_S_QUERYHISTORYMESSAGE_ARG;

/** \brief 获取消息漫游响应 */
typedef struct tagIM_S_QUERYHISTORYMESSAGE_ACK
{
	TUP_INT totalCount;						/**< 消息总条数，首次查询时返回 */
	IM_E_IM_HISTORYMESSAGEOP_TYPE opType;	/**< 操作类型 */
	IM_E_IM_HISTORYMESSAGEMSG_TYPE msgType; /**< 请求的消息类型 */
	TUP_CHAR sender[IM_D_MAX_PHONE_LENGTH];	/**< 消息发送方，msgType为0时填写消息发送者，msgType为1时填写群ID，msgType为2时为短信号码，msgType为3时忽略 */
	TUP_S_LIST* chatinfolist;				/**< 消息格式 IM_S_CODECHAT_NOTIFY */
	TUP_S_LIST* smsList;					/**< 短信消息列表 IM_S_SMSINFO*/
}IM_S_QUERYHISTORYMESSAGE_ACK;

/** \brief 短信消息格式  */
typedef struct tagIM_S_SMSINFO
{
	TUP_CHAR origin[IM_D_MAX_PHONE_LENGTH];				/**< 发送方号码*/
	TUP_CHAR target[IM_D_MAX_PHONE_LENGTH];				/**< 接收方号码*/
	TUP_INT64 serverMsgID;								/**< 服务器消息ID*/
	TUP_CHAR clientMsgID[IM_D_MAX_CHAR_LENGTH];			/**< 客户端消息ID*/
	TUP_CHAR content[IM_D_MAX_MESSAGE_LENGTH];			/**< 消息内容*/
	TUP_CHAR sendTime[IM_D_MAX_TIMESTAMP_LENGTH];       /**< 发送时间*/
	IM_E_SMS_NOTIFY_TYPE smsType;						/**< 接收到的短信消息的类型 */
}IM_S_SMSINFO;

/** \brief 已读消息设置消息格式  */
typedef struct tagIM_S_MESSAGEINFO
{
	IM_E_IM_HISTORYMESSAGEMSG_TYPE msgType;			/** \brief 消息类型 */
	TUP_CHAR	sender[IM_D_MAX_PHONE_LENGTH];		/** \brief 发送方 (个人账号、固定群、讨论组ID、短信号码)*/
	TUP_INT64	msgId;								/** \brief 消息ID (serverChatID)*/
}IM_S_MESSAGEINFO;

/** \brief IM消息发送状态请求 */
typedef struct tagIM_S_CHAT_STATUS_ARG
{
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];  /**< 接收方账号(必填) */
    IM_E_IM_CHAT_STATUS type;  /**< 输入状态(必填) */
}IM_S_CHAT_STATUS_ARG;

/** \brief 获取部门列表响应 */
typedef struct tagIM_S_GETDEPTS_ACK
 {
     TUP_BOOL result; /**< 操作结果 */
     TUP_S_LIST* deptList; /**< 部门列表(IM_S_DEPTINFO) */
 }IM_S_GETDEPTS_ACK;

/** \brief 查询企业通讯录请求 */
typedef struct tagIM_S_QUERY_ENTADDRESSBOOK_ARG
{
    TUP_BOOL isNeedAmount;  /**< 是否需要返回总数(必填) */ 
    IM_E_ADDRBOOKQUERY_ORDERTYPE orderType;	/**< 排序的关键字 */ 
    IM_E_ADDRBOOKQUERY_ORDERMODEL orderModel;	/**< 排序的方式 */ 
    TUP_INT32 offset; /**< 查询偏移量(必填) */ 
    TUP_INT32 count; /**< 查询数目(必填) */ 
    TUP_INT64 deptID; /**< 查询部门（必填，如果不指定部门，请填写-1） */ 
    TUP_CHAR queryKey[IM_D_MAX_DESC_LENGTH];		/**< 关键字（可选） */ 
}IM_S_QUERY_ENTADDRESSBOOK_ARG;

/** \brief 查询企业通讯录响应 */
typedef struct tagIM_S_QUERY_ENTADDRESSBOOK_ACK
{
	TUP_BOOL result; /**< 操作结果 */
	TUP_INT32 recordAmount;	/**< 总记录数 */ 
	TUP_S_LIST* userList; /**< 成员列表（IM_S_USERINFO） */ 
}IM_S_QUERY_ENTADDRESSBOOK_ACK;

/** \brief 查询用户信息请求 */
typedef struct tagIM_S_QUERY_USERINFO_ARG
{
	TUP_CHAR key[IM_D_MAX_PHONE_LENGTH];		/**< 关键词内容 */
	IM_E_IMUSERQUERYTYPE type;					/**< 关键词类型 */
}IM_S_QUERY_USERINFO_ARG;

/** \brief 查询用户信息响应 */
typedef struct tagIM_S_QUERY_USERINFO_ACK
{
	TUP_S_LIST* userList;	/**< 成员列表（IM_S_USERINFO） */ 
}IM_S_QUERY_USERINFO_ACK;

/** \brief 添加固定群请求 */
typedef struct tagIM_S_IMGROUP_OP_ARG
{
    IM_S_IMGROUPINFO fixedgroupInfo; /**< 固定群信息（添加时id不填，在ack中返回；修改时需要填写id） */
}IM_S_IMGROUP_OP_ARG;

/** \brief 添加固定群响应 */
typedef struct tagIM_S_ADDIMGROUP_ACK
{
     TUP_BOOL result; /**< 操作结果 */
     TUP_CHAR id[IM_D_GROUPID_LENGTH]; /**< 群组ID  */
     IM_E_FIXEDGROUP_OP_RESULT reason;	/**< 群组操作结果返回值，result为TUP_FALSE时来判断原因 */
}IM_S_ADDIMGROUP_ACK;

/** \brief 添加固定群响应 */
typedef struct tagIM_S_MODFIXEDGROUP_ACK
{
     TUP_BOOL result; /**< 操作结果 */
     IM_E_FIXEDGROUP_OP_RESULT reason;	/**< 群组操作结果返回值，result为TUP_FALSE时来判断原因 */
}IM_S_MODFIXEDGROUP_ACK;

/** \brief 添加固定群成员请求 */
typedef struct tagIM_S_ADDIMGROUPMEMBER_ARG
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< 固定群ID */ 
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; /**< 添加用户帐号 */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH]; /**< 群组名 */ 
    TUP_CHAR displayName[IM_D_MAX_NAME_LENGTH]; /**< 显示名 */ 
}IM_S_ADDIMGROUPMEMBER_ARG;

/** \brief 获取群组(固定群，临时群)成员请求 */
typedef struct tagIM_S_REQUESTIMGROUPMEMBERS_ARG
{
    TUP_BOOL		isSyncAll;		/**< 是否全量同步 */
    TUP_CHAR        groupID[IM_D_GROUPID_LENGTH];   /**< 群ID */
    TUP_CHAR		timpstamp[IM_D_MAX_TIMESTAMP_LENGTH]; /**< 同步时间戳，19000000000000（年月日时分秒)，不填写使用默认时间19000000000000 */
}IM_S_REQUESTIMGROUPMEMBERS_ARG;

/** \brief 删除固定群请求 */
typedef struct tagIM_S_DELIMGROUPMEMBER_ARG
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< 固定群ID */ 
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; /**< 删除用户帐号 */ 
}IM_S_DELIMGROUPMEMBER_ARG;

/** \brief 管理员审批用户申请加入固定群申请，或者用户审批管理员邀请加入固定群 */
typedef struct tagIM_S_CONFIRM_JOINFIXEDGROUP_ARG
{
    TUP_BOOL  agreeJoin;     /**< 管理员是否同意成员的申请 */
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< 固定群ID */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH]; /**< 群组名ID */ 
    TUP_CHAR memberAccount[IM_D_MAX_ACCOUNT_LENGTH]; /**< 申请加入成员帐号 */ 
    TUP_CHAR displayName[IM_D_MAX_NAME_LENGTH]; /**< 管理员显示名 */ 
}IM_S_CONFIRM_JOINFIXEDGROUP_ARG;

/** \brief 申请加入固定群请求 */
typedef struct tagIM_S_JOINFIXEDGROUP_ARG
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< 固定群ID */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH]; /**< 固定群名 */ 
    TUP_CHAR displayName[IM_D_MAX_NAME_LENGTH]; /**< 显示名 */ 
}IM_S_JOINFIXEDGROUP_ARG;

/** \brief 转移固定群请求 */
typedef struct tagIM_S_TRANSFERIMGROUP_ARG
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< 固定群ID */ 
    TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH]; /**< 成员帐号 */ 
}IM_S_TRANSFERIMGROUP_ARG;

/** \brief 讨论组添加号码请求 */
typedef struct tagIM_S_IMGROUPPHONEMEMBER_OP_ARG
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< 固定群ID */ 
    TUP_S_LIST* phonelist; /**< 号码列表 */ 
}IM_S_IMGROUPPHONEMEMBER_OP_ARG;

//--------------------------------------------------------------方法入参结构体 end--------------------------------------------------------------

//--------------------------------------------------------------回调通知结构体 begin--------------------------------------------------------------
/** \brief 系统链接响应*/
typedef struct tagIM_S_SYSURLS
{
    TUP_CHAR userPortalUrl[IM_D_IP_LENGTH];  /**< 个人portal地址 */
    TUP_CHAR updateServerAddr[IM_D_IP_LENGTH]; /**< 自动升级服务器地址 */
}IM_S_SYSURLS_NOTIFY;

/** \brief 系统链接响应*/
typedef struct tagIM_S_LOGOUT_NOTIFY
{
	TUP_BOOL LogOutRet;		/**< 用户退出结果 */
}IM_S_LOGOUT_NOTIFY;

/** \brief 对方添加自己好友成功通知 */
typedef struct tagIM_S_ADDFRIEND_NOTIFY
 {
     TUP_CHAR account[IM_D_MAX_ACCOUNT_LENGTH];		/**< 对方好友帐号 */
     TUP_CHAR displayName[IM_D_MAX_NAME_LENGTH];	/**< 对方显示名 */
	 TUP_INT64 serverMsgID;							/**< 服务器消息ID */
 }IM_S_ADDFRIEND_NOTIFY;

/** \brief 好友状态变化通知 */
typedef struct tagIM_S_USERSTATUS_NOTIFY
 {
	 IM_E_USER_ONLINESTATUS status;					/**< 新状态 */
	 TUP_CHAR	desc[IM_D_MAX_DESC_LENGTH];         /**< 状态描述 */
	 TUP_CHAR	origin[IM_D_MAX_ACCOUNT_LENGTH];    /**< 状态变化成员帐号 */
	 IM_E_CLIENT_TYPE clientType;					/**< 客户端类型 */
	 TUP_CHAR	clientDesc[IM_D_MAX_DESC_LENGTH];   /**< 客户端描述 */
 }IM_S_USERSTATUS_NOTIFY;

/** \brief 好友信息列表 */
typedef struct tagIM_S_USERINFOCHANGE_LIST_NOTIFY
{
	TUP_S_LIST* userInfoList;								/**< 同步状态(增量同步时用到) */
}IM_S_USERINFOCHANGE_LIST_NOTIFY;

/** \brief 群管理员收到用户加入固定群通知 */
typedef struct tagIM_S_APPLYJOINFIXEDGROUP_NOTIFY
{
    TUP_BOOL agreeInvite;		/**< 用户是否同意管理员的邀请 */
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< 固定群ID */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH]; /**< 群组名ID */ 
    TUP_CHAR memberAccount[IM_D_MAX_ACCOUNT_LENGTH]; /**< 被邀请成员的帐号 */ 
    TUP_CHAR memberName[IM_D_MAX_NAME_LENGTH]; /**< 被邀请成员的名称 */ 
}IM_S_APPLYJOINFIXEDGROUP_NOTIFY;

/** \brief 用户收到管理员邀请加入固定群通知 */
typedef struct tagIM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY
{
	TUP_CHAR groupID[IM_D_GROUPID_LENGTH];			/**< 固定群ID */ 
	TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH];		/**< 群组名ID */ 
	TUP_CHAR adminAccount[IM_D_MAX_ACCOUNT_LENGTH]; /**< 管理员帐号 */ 
	TUP_CHAR adminName[IM_D_MAX_NAME_LENGTH];		/**< 管理员名称 */
	TUP_INT64 serverMsgID;							/**< 服务器消息ID */
}IM_S_RECEIVEINVITETOFIXEDGROUP_NOTIFY;

/** \brief 管理员收到用户申请加入群组通知 */
typedef struct tagIM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY
{
	TUP_CHAR groupID[IM_D_GROUPID_LENGTH];				/**< 固定群ID */ 
	TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH];			/**< 群组名ID */ 
	TUP_CHAR memberAccount[IM_D_MAX_ACCOUNT_LENGTH];	/**< 申请者帐号 */ 
	TUP_CHAR memberName[IM_D_MAX_NAME_LENGTH];			/**< 申请者名称 */ 
	TUP_INT64 serverMsgID;								/**< 服务器消息ID */
}IM_S_RECEIVEJOIN_FIXEDGROUP_NOTIFY;

/** \brief IM群组详细信息 */
typedef struct tagIM_S_GETIMGROUPDETAIL_NOTIFY
{
	IM_S_IMGROUPINFO imGroupInfo;   
}IM_S_GETIMGROUPDETAIL_NOTIFY;


/** \brief 群成员收到管理员审批加入固定群通知的响应 */
typedef struct tagIM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY
{
    TUP_BOOL agreeJoin;     /**< 管理员是否同意成员的申请 */
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH]; /**< 固定群ID */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH]; /**< 群组名ID */ 
    TUP_CHAR adminAccount[IM_D_MAX_ACCOUNT_LENGTH]; /**< 管理员的帐号  */ 
    TUP_CHAR adminName[IM_D_MAX_NAME_LENGTH]; /**< 管理员的名称 */ 
}IM_S_APPLYJOINFIXEDGROUPRESULT_NOTIFY;

/** \brief 固定群变更通知 */
typedef struct tagIM_S_IMGROUP_NOTIFY
{
    TUP_CHAR groupID[IM_D_GROUPID_LENGTH];				/**< 固定群ID */ 
    TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH];			/**< 群组名ID */ 
    TUP_CHAR adminAccount[IM_D_MAX_ACCOUNT_LENGTH];		/**< 管理员帐号 */ 
    TUP_CHAR memberAccount[IM_D_MAX_ACCOUNT_LENGTH];	/**< 申请加入成员帐号 */ 
    TUP_CHAR memberName[IM_D_MAX_NAME_LENGTH];			/**< 申请加入成员姓名 */ 
	TUP_INT64  serverMsgID;								/**< 服务器消息ID */
}IM_S_IMGROUP_NOTIFY;

/** \brief 号码 */
typedef struct tagIM_S_PHONENUM
{
    TUP_CHAR phoneNum[IM_D_GENEAL_LENGTH];
}IM_S_PHONENUM;

/** \brief 讨论组变更通知 */
typedef struct tagIM_S_DISCUSSGROUP_NOTIFY
{
	TUP_CHAR groupID[IM_D_GROUPID_LENGTH];				/**< 讨论组ID */ 
	TUP_S_LIST* phonelist;								/**< 号码列表:IM_S_PHONENUM */			
	TUP_CHAR groupName[IM_D_MAX_NAME_LENGTH];			/**< 讨论组名称 */ 
	TUP_CHAR adminAccount[IM_D_MAX_ACCOUNT_LENGTH];		/**< 管理员帐号 */ 
	TUP_CHAR memberAccount[IM_D_MAX_ACCOUNT_LENGTH];	/**< 新增或删除的成员帐号 */ 
	TUP_CHAR memberName[IM_D_MAX_NAME_LENGTH];			/**< 新增或删除的成员姓名 */ 
}IM_S_DISCUSSGROUP_NOTIFY;

/** \brief 聊天信息 */
typedef struct tagIM_S_CHATINFO_NOTIFY
{
	IM_E_CHAT_TYPE	chatType;								/**< IM消息类型 */
	TUP_INT		sourceFlag;									/**< IM消息发自哪里 */
	TUP_INT		contentType;								/**< IM消息内容格式*/
	TUP_INT64	utcStamp;									/**< UTC时间*/
	TUP_CHAR	origin[IM_D_MAX_ACCOUNT_LENGTH];			/**< 发送方账号*/
	TUP_CHAR	target[IM_D_MAX_ACCOUNT_LENGTH];			/**< 接收方账号*/
	TUP_CHAR	groupID[IM_D_GROUPID_LENGTH];				/**< 群组ID*/
	TUP_CHAR	content[IM_D_MAX_MESSAGE_LENGTH];			/**< IM消息内容*/
	TUP_CHAR	name[IM_D_MAX_NAME_LENGTH];					/**< 发送方名字*/
	TUP_INT		regionID;									/**< 区域ID 服务器用 */
	TUP_INT64	clientChatID;								/**< 客户端生成的消息ID */
	TUP_INT64	serverChatID;								/**< 服务器生成的消息ID，客户端发送时不填，接收时服务器填写。 */
	TUP_CHAR	groupName[IM_D_MAX_NAME_LENGTH];			/**< 群组名 */
	IM_E_IM_CHATMEDIA_TYPE mediaType;						/**< 媒体类型 */
}IM_S_CHATINFO_NOTIFY;

/** \brief 讨论组收到系统公告通知 */
typedef struct tagIM_S_SYSTEMBULLETIN_NOTIFY
{
	IM_S_CHATINFO_NOTIFY chatInfo;	/**< 聊天信息 */
}IM_S_SYSTEMBULLETIN_NOTIFY;

/** \brief 发送IM输入状态消息 */
typedef struct tagIM_S_SENDIMINPUT_NOTIFY
{
	TUP_CHAR				account[IM_D_MAX_ACCOUNT_LENGTH];		/** \brief 发送者账号 */
	IM_E_IM_CHAT_STATUS		status;									/** \brief IM聊天输入状态 */
}IM_S_SENDIMINPUT_NOTIFY;

/** \brief 新即时消息通知 */
typedef struct tagIM_S_CODECHAT_NOTIFY
{
	IM_S_CHATINFO_NOTIFY chatInfo;	/**< 聊天信息 */
}IM_S_CODECHAT_NOTIFY;

/** \brief 新即时消息批量通知 */
typedef struct tagIM_S_CHATLIST_NOTIFY
{
	TUP_S_LIST* chatList;		/**< 批量聊天信息 IM_S_CODECHAT_NOTIFY*/
	TUP_INT total;				/**< 未读消息总数 */
	TUP_INT64 minMsgID;			/**< 最小消息ID */
	TUP_INT64 maxMsgID;			/**< 最大消息ID */
}IM_S_CHATLIST_NOTIFY;

typedef struct tagIM_S_IMAGEINFO
{
    TUP_INT length;    /** \brief 头像内容长度 */
    TUP_CHAR* data;	    /** \brief 头像内容 */
}IM_S_IMAGEINFO;

typedef struct tagIM_S_USERIMAGEINFO
{
    IM_S_IMAGEINFO  imagebits;      /**< 头像数据 */
    TUP_CHAR		id[IM_D_MAX_ACCOUNT_LENGTH];				/**< 头像ID */
    TUP_CHAR		timestamp[IM_D_MAX_TIMESTAMP_LENGTH];		/**< 时间戳 */
}IM_S_USERIMAGEINFO;

typedef struct tagIM_S_IMAGEREQARG
{
    TUP_CHAR id[IM_D_MAX_ACCOUNT_LENGTH];				/** \brief 头像ID */
    TUP_CHAR timpstamp[IM_D_MAX_TIMESTAMP_LENGTH];		/** \brief 同步时间戳，19000000000000（年月日时分秒） */
}IM_S_IMAGEREQARG;

typedef struct tagIM_S_STATUSARG
{
    IM_E_USER_ONLINESTATUS status;					/**< 新状态 */
    TUP_CHAR desc[IM_D_MAX_STATUS_DESCLEN];         /**< 状态描述 */
}IM_S_STATUSARG;

/** \brief 用户登录通知 */
typedef struct tagIM_S_LOGIN_NOTIFY
{
	TUP_BOOL	result;										/**< 登录结果 */
	TUP_CHAR	token[IM_D_LOGIN_TOKEN_LENGTH];				/** \brief token */	 
	TUP_INT		regionID;									/** \brief 区域ID */
	TUP_INT		retryTimes;									/** \brief 登录重试剩余次数 */
	TUP_INT		lockInterval;								/** \brief 帐号被锁定剩余时间（单位：分钟） */
	TUP_CHAR	lastLoginIP[IM_D_IP_LENGTH];				/** \brief 上一次登录的服务器IP */
	TUP_CHAR	lastLoginTime[IM_D_MAX_TIMESTAMP_LENGTH];	/** \brief 上一次登录的服务器时间 */
}IM_S_LOGIN_NOTIFY;

/** \brief 用户被踢通知 */
typedef struct tagIM_S_KICKOUT_NOTIFY
{
	TUP_CHAR userAccount[IM_D_MAX_ACCOUNT_LENGTH];
	IM_E_EXITSTATUS exitFlag;
}IM_S_KICKOUT_NOTIFY;
//--------------------------------------------------------------回调通知结构体 end--------------------------------------------------------------

//--------------------------------------------------------------回调函数 begin--------------------------------------------------------------
/**
 * \brief 回调函数
 * \param[in]  eventID 事件ID
 * \param[in] body 消息体
 * \return TUP_VOID
 */
typedef TUP_BOOL (*TUP_IM_FN_CALLBACK_PTR)(IM_E_EVENT_ID eventID, void *body);
//--------------------------------------------------------------回调函数 end--------------------------------------------------------------

#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif//_TUP_IM_BASEDEF_H_