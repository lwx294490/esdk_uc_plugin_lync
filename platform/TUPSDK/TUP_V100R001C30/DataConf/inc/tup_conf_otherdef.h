#ifndef _TUP_CONF_OTHERDEF_H_
#define _TUP_CONF_OTHERDEF_H_

#include "tup_conf_basedef.h"


#if defined(MY_ANDROID) && (defined(TEST_8950) || !(defined CONF_IPPHONE))
typedef TUP_VOID (TUP_STDCALL *conference_callback)(TUP_INT nType, TUP_INT nValue1, TUP_LONG nValue2, TUP_VOID* pMsg, TUP_VOID* pContext, TUP_INT nSize);	
#else
typedef TUP_VOID (TUP_STDCALL *conference_callback)(TUP_INT nType, TUP_INT nValue1, TUP_LONG nValue2, TUP_VOID* pVoid, TUP_INT nSize); 
#endif

typedef TUP_VOID (TUP_STDCALL *component_callback)(TUP_INT nType, TUP_INT nValue1, TUP_LONG nValue2, TUP_VOID* pVoid, TUP_INT nSize);    //组件的回调函数

// URL获取信息结构
typedef struct tag_MC_Buffers
{
	TUP_UINT8*			data;
	TUP_UINT32			data_length;
	TUP_VOID* 			next;
} TC_Buffers;

// TUP_INT on_ping_progress_report(TUP_CHAR* src_addr, TUP_CHAR* dst_addr, TUP_UINT16 rtt, TUP_UINT16 jitter, TUP_UINT16 svr_status);
typedef struct tag_ping_progress_report
{
	TUP_CHAR src_addr[TC_MAX_CONF_SERVER_IP];
	TUP_CHAR dst_addr[TC_MAX_CONF_SERVER_IP];
	TUP_UINT16 rtt;
	TUP_UINT16 jitter;
	TUP_UINT16 svr_status;
} Ping_Progress_Report;


typedef TUP_VOID (TUP_STDCALL *url_async_callback)(TUP_INT dwMsgID, TUP_INT result, TC_Buffers * return_buffers);
typedef TUP_VOID (TUP_STDCALL *ping_callback)(TUP_INT nPingID,TUP_CHAR* dst_addr,TUP_UINT8 nType, TUP_UINT16 rtt, TUP_UINT16 jitter, TUP_UINT16 svr_status);
//////////////////////////////////////////////////////////////////////////
// 会议数据类型定义


//////////////////////////////////////////////////////////////////////////
// Phone config info
//   sess_flag:
#define TC_SESS_FLAG_PHONE_ALONE	0x0
#define TC_SESS_FLAG_AUDIO_MIX		0x1
#define TC_SESS_FLAG_VIDEO_MIX		0x2
#define TC_SESS_FLAG_AV_MIX		    0x3
#define TC_MRS_AUDIO				0x4
#define TC_MRS_VIDEO				0x8


typedef struct tag_phone_config_info		/*电话会议配置参数*/
{
	TUP_CHAR    conf_num[TC_MAX_PHONE_CONF_NUM_LEN];   // 电话会议号
	TUP_CHAR    conf_id[TC_MAX_PHONE_CONF_NUM_LEN];    // 数据会议号
	TUP_CHAR    host_pwd[TC_MAX_PHONE_PASS_CODE_LEN];  // 电话主持人密码
	TUP_CHAR    server_url[TC_MAX_PHONE_SVR_URL_LEN];	//网关地址，IPT2.2必选
	TUP_UINT8   sess_flag;                             // 电话类型
	TUP_UINT16  attendee_num;                          // 电话会场最大人数

#ifdef __cplusplus
	tag_phone_config_info()
	{
		memset(this, 0 , sizeof(tag_phone_config_info));
	}
#endif
} PHONE_CONFIG_INFO;

//////////////////////////////聊天模块定义部分//////////////////////////////////

#define  GROUP_MAX_LEN                   32			//组名的最大长度
#define  CHAT_MIN_TIME_INTERVAL          200		//送聊天信息时的最短时间间隔 单位毫秒
#define  CHAT_MAX_MSG_LEN                48*1024    //最大发送消息的长度 48KB

//信息类别
enum{
	CHAT_TYPE_PUBLIC,		//公聊
	CHAT_TYPE_GROUP,		//组聊
	CHAT_TYPE_PRIVATE		//私聊
};
/**************************************************************************/
/*onGroupInfoModifiedInd 回调
 组长邀请，组长和组内原有成员会有这个消息回调， Reason = REASON_GROUP_USER_ADD
 组长踢人，组长和组内不被踢的组员会有这个消息回调，Reason = REASON_GROUP_USER_DEL
/**************************************************************************/
enum
{
	REASON_GROUP_USER_NULL,
	REASON_GROUP_USER_ADD,	
	REASON_GROUP_USER_DEL
};

/**************************************************************************/
/*  组员离组原因
/**************************************************************************/
enum
{
	REASON_LEAVE_GROUP_SELF,
	REASON_LEAVE_GROUP_KICKED,
	REASON_LEAVE_GROUP_OTHER
};

struct TC_CHAT_MSG	/*聊天消息内容*/
{
	TUP_INT		nMsgType;							//消息类型 ：公聊（CHAT_TYPE_PUBLIC），组聊（CHAT_TYPE_GROUP），私聊（CHAT_TYPE_PRIVATE）
    TUP_UINT32	nFromUserid;						//消息发自用户的ID
	TUP_UINT16	nSequenceNmuber;					//公聊消息序列号，当消息类型为私聊与组聊时，此字段为0
	TUP_INT		nFromGroupID;						//nMsgType==CHAT_TYPE_GROUP时，此参数才有效。消息发自的聊天组的ID
	TUP_CHAR*	lpMsg;								//聊天内容
	TUP_UINT32	nMsgLen;							//聊天内容长度
	TUP_INT64	time;								//发送消息时的服务器时间
	TUP_CHAR	fromUserName[TC_MAX_USER_NAME_LEN];	//发送消息用户的用户名
};

/*聊天分组信息*/
typedef struct  
{
	TUP_CHAR groupName[GROUP_MAX_LEN];			//分组名
	TUP_INT groupID;							//分组ID
	TUP_UINT32 ownerID;							//创建者的UserID
	TUP_UINT32* pUserIds;						//分组内的成员列表
	TUP_UINT32 nUser;							//分组内的成员列表个数
}TC_GROUP_INFO;


/////////////////文件共享模块定义部分///////////////////////////
typedef struct {
	TUP_CHAR fileName[256];							//共享文件项的文件名
	TUP_CHAR filePathName[256];						//共享文件项的在上传者设备上的路径文件名
	TUP_CHAR senderUserName[TC_MAX_USER_NAME_LEN];	//共享文件项的上传者的用户名
	TUP_INT senderUserId;							//共享文件项的上传者的用户ID
	TUP_INT recieverUserId;							//共享文件项的接受者的用户ID
	TUP_UINT32 size;									//共享文件项的字节数
	TUP_INT status;									//共享文件项的状态，1-已上传，0-正在上传
} TC_FILE_INFO;


///////////////////////////音频模块定义部分////////////////////////////////////
//203857 2011-12-22
#define TC_AUDIO_DEVICE_NAME_MAX_LEN	256
#define NHME_MAX_FILE_PATH				260

typedef struct tagTC_AUDIO_DEVICE_INFO
{
	TUP_CHAR	_szName[TC_AUDIO_DEVICE_NAME_MAX_LEN];
	TUP_UINT32 	_DeviceID;
}TC_AUDIO_DEVICE_INFO; 

typedef enum
{
	AUDIO_MIX_METHOD_CLIENT = 1,
	AUDIO_MIX_METHOD_MRS = 2
}MIX_METHOD;

/*
 W  windows平台支持
 I  IOS平台支持
 A  Android平台支持
*/
typedef enum		//编解码类型
{
	AUDIO_Codec_PCMA = 0,	//支持服务器混音和客户端混音
	AUDIO_Codec_PCMU,		//支持服务器混音和客户端混音   
 	AUDIO_Codec_AMR,		//暂不支持
 	AUDIO_Codec_AMRWB,		//暂不支持
 	AUDIO_Codec_G723,		//暂不支持
	AUDIO_Codec_G729,	//支持服务器混音和客户端混音
	AUDIO_Codec_iLBC,	//支持服务器混音和客户端混音
	AUDIO_Codec_G722,    
	AUDIO_Codec_Opus,	//只支持客户端混音
	AUDIO_Codec_NUM		//	
}Audio_Codec_Format;

/*
默认编解码器配置  

2013/1/22  windows平台
当frameLen==0时，内部会取这些默认配置
Codec = PCMA, payload = 8, SampleFreq = 8000, iRate = 64000, iPacketSize = 160    
Codec = PCMU, payload = 0, SampleFreq = 8000, iRate = 64000, iPacketSize = 160    
Codec = AMR, payload = 109, SampleFreq = 8000, iRate = 12200, iPacketSize = 160   
Codec = AMRWB, payload = 110, SampleFreq = 16000, iRate = 23850, iPacketSize = 320
Codec = G723, payload = 4, SampleFreq = 8000, iRate = 6300, iPacketSize = 240     
Codec = G729, payload = 18, SampleFreq = 8000, iRate = 8000, iPacketSize = 160    
Codec = iLBC, payload = 98, SampleFreq = 8000, iRate = 15200, iPacketSize = 160   
Codec = opus, payload = 112, SampleFreq = 48000, iRate = 64000, iPacketSize = 960 
*/

typedef struct tagTC_AUDIO_PARAM		//音频参数设置
{
	MIX_METHOD			MixMethord;		//客户端混音 = 1; 服务器混音 = 2;
	TUP_INT				frameLen;		//默认30ms;当取值为0的时候，采取默认配置（如上）
	TUP_INT				sampleRate;		//默认8000;
	Audio_Codec_Format	codecName;		//默认客户端混音 = AUDIO_CODEC_iLBC; 服务器混音 = AUDIO_CODEC_PCMA;
	TUP_INT				EC;				//默认3; 0：关闭回声消除算法;1:选择AEC算法时，表示开启并初始化为自动模式;2:选择AEC算法时，表示耳机模式，适合耳机通话的模式;3:选择AEC算法时，表示话筒模式，适合音箱和话筒通话的模式
	TUP_INT				AGC;			//默认1;自动增益控制 0:AGC功能关闭; 1:开启AGC数字模式; 2:开启AGC模拟模式
	TUP_INT				NR;				//默认4;自动噪声抑制 support[0-4]
	TUP_INT             enableTrace;    //是否保存trace
	TUP_INT				logLevel;		//默认0x02;打印日志标志, 0x00:不打印日志, 0x01:错误, 0x02:提示
	TUP_INT				logSize;		//默认100;日志文件大小，单位M
	TUP_CHAR			pDLLAddr[NHME_MAX_FILE_PATH];//默认当前路径，动态库位置
	TUP_CHAR			pLogPath[NHME_MAX_FILE_PATH];//默认当前路径，保存日志的位置
	TUP_CHAR            cTraceFilePath[NHME_MAX_FILE_PATH];// Trace保存路径
	TUP_UINT32			timeSpan;		//只在客户端混音模式下有效，语音激励的通报时间间隔（单位：s）
	TUP_CHAR            UAPInfo[128];//传给UAP的相关信息格式为: 接入码 @ 会议号 @ 会议密码 @ UAP地址
}TC_AUDIO_PARAM;

typedef enum{
	AUDIO_OPEN_MIC	=	1,
	AUDIO_CLOSE_MIC,
	AUDIO_MUTE_MIC,
	AUDIO_UNMUTE_MIC,
	AUDIO_PRIVATE_CHAT_ENTER,
	AUDIO_PRIVATE_CHAT_LEAVE,

	AUDIO_OPEN_MIC_TP,	//来自智真的操作
	AUDIO_CLOSE_MIC_TP,	//来自智真的操作

	AUDIO_OPEN_SPEAKER_TP,	//来自智真的操作
	AUDIO_CLOSE_SPEAKER_TP,	//来自智真的操作
}Audio_CMD;

//音频设备类型
enum
{
	AUDIO_MIC  =  0,
	AUDIO_SPEAKER
};

//音频设备状态
enum 
{
	AUDIO_STATUS_OPEN = 0,
	AUDIO_STATUS_CLOSE,
	AUDIO_STATUS_MUTE,
	AUDIO_STATUS_NO_DEVICE
};

//语音激励
typedef enum
{
	SPEAKER_STATUS_NULL,
	SPEAKER_STATUS_PC,
	SPEAKER_STATUS_TELLER,
	SPEAKER_STATUS_WISDOM
}SpeakerStatus;

//"tel:456;sip:*00110011@huawei.com;sip:pc_28508291@10.166.37.69:11010";
typedef struct tag_SpeakingUser
{
	SpeakerStatus status;
	TUP_CHAR speakID[32];//说话者的ID

}SpeakingUser;

//by s00209224  2012/1/29
//因为某些异常情况可能存在同名的设备，故热插拔回调参数有更新。上层应用不必关注此结构体 
//音频热插拔 
 typedef struct tag_HotPlug
 {
 	TUP_UINT32 deviceID; //设备ID
 	TUP_INT deviceType; //设备类型AUDIO_MIC=0或 AUDIO_SPEAKER=1
 	TUP_INT iActionEvent;//0 插, 1 拔
 }HotPlug;


#ifdef __APPLE__
/*************************************************************************************************/
// 路由设置枚举    对应于conf_audio_open_speaker中的 设备ID
/* 移动设备(IOS)路由设置 */
enum 
{
	TC_AUD_DEV_ROUTE_DEFAULT       = 0x0,   //连上耳机，默认为耳机；反之为听筒
	TC_AUD_DEV_ROUTE_LOUDSPEAKER   = 0x1,   //扬声器
	TC_AUD_DEV_ROUTE_BLUETOOTH     = 0x2,   //蓝牙
	TC_AUD_DEV_ROUTE_EARPIECE      = 0x3,   //听筒，用于获取，设置时保留，返回错误
	TC_AUD_DEV_ROUTE_HEADSET       = 0x4    //耳机，用于获取，设置时保留，返回错误
};
#endif


/***********************录制模块定义部分*****************************/

/***视频编码格式***/
typedef enum tag_RECORD_VIDEO_CODEC
{
	VIDEO_CODEC_NULL = 0,
	VIDEO_CODEC_RGB24
}RECORD_VIDEO_CODEC;

/***视频录制的帧率***/
enum
{
	Record_Video_FPS_1 = 1,
	Record_Video_FPS_2 = 2,
	Record_Video_FPS_3 = 3,
	Record_Video_FPS_4 = 4,
	Record_Video_FPS_5 = 5
};

/***视频录制的比特率***/
enum
{
	Record_Video_BitRate_LOW = 300000,
	Record_Video_BitRate_MID = 400000,
	Record_Video_BitRate_HIG = 500000
};

typedef struct tagVideoRecordParam
{
	RECORD_VIDEO_CODEC codec;		//编解码
	TUP_UINT32 uiFrameRate;			//帧率
	TUP_UINT32 uiBitrate;			//比特率
    TUP_INT quality;                //质量0-100
}VideoRecordParam;

/***音频编码格式***/
typedef enum tag_RECORD_AUDIO_CODEC
{
	AUDIO_CODEC_NULL = 0,
	AUDIO_CODEC_PCMA
}RECORD_AUDIO_CODEC;

/***音频录制channel数***/
enum
{
	Record_Audio_Channel_Single = 1
};

/***音频录制的采样率***/
enum
{
	Record_Audio_SampleRate_8000 = 8000
};

/***音频录制采样位数***/
enum
{
	Record_Audio_BitPerSample_16 = 16
};

typedef struct tagAudioRecordParam
{
	RECORD_AUDIO_CODEC codec;
	TUP_UINT32 uiNumChannels;
	TUP_UINT32 uiSampleRate;
	TUP_UINT32 uiBitsPerSample;
}AudioRecordParam;

/***录制状态***/
typedef enum tag_RECORD_STATUS
{
	RECORD_STATUS_NULL = 0,
	RECORD_STATUS_RECORDING,
	RECORD_STATUS_PAUSE
}RECORD_STATUS;


enum{
	RECORD_MODE_VIDEO		= 0x01,	
	RECORD_MODE_AUDIO_INTER = 0x02,
	RECORD_MODE_AUDIO_OUTER = 0x04,

	//说明：可以进行与或，RECORD_MODE_AUDIO_INTER和RECORD_MODE_AUDIO_OUTER不能同时有
};

/***********************媒体共享模块定义部分************************/

typedef enum tagPLAYER_STATUS
{
	PLAYER_STATUS_NONE			  = 0,
	PLAYER_STATUS_CLOSED	  	= 1,
	PLAYER_STATUS_STOPED		  = 2,
	PLAYER_STATUS_PLAYING		= 3,
	PLAYER_STATUS_PAUSED		  = 4,
	PLAYER_STATUS_BUFFERING	= 5,
	PLAYER_STATUS_ERROR		  = 6,
	PLAYER_STATUS_MEDIAEND   = 7,
	PLAYER_STATUS_CONECTING  = 8,
	PLAYER_STATUS_SEEKING    = 9,
	PLAYER_STATUS_MAX        = 10
}PLAYER_STATUS;

typedef struct tag_PlayerStateChangeParam
{
	PLAYER_STATUS oldstate;
	PLAYER_STATUS newstate;
}PlayerStateChangeParam;

typedef struct tag_MidPlayParam
{
	double lfPos;
	TUP_CHAR fileName[256];
} MidPlayParam;

////////////////////////投票模块定义部分////////////////////////////////

#define POLLING_INVALID_ID -1
typedef enum {
	QTYPE_SINGLE_CHOICE,	//单选题
	QTYPE_MULTI_CHOICE,		//复选题
	QTYPE_QA,				//问答题
	QTYPE_ERROR,

	QTYPE_COUNT
}QuestionType;


typedef struct {
	TUP_UINT32 id;
	TUP_VOID* pData;
	TUP_INT dataLen;
}ParamUpdateData;


/*******************************SVN功能相关定义***************************************/

/* 代理类型 */
#define TC_SVN_PROXY_NONE      0      /* 不使用代理　*/
#define TC_SVN_PROXY_HTTP      1      /* 使用HTTP代理 */
#define TC_SVN_PROXY_SOCKS5    2      /* 使用SOCK5代理 */
#define TC_SVN_PROXY_UNKNOWN   3      /* 使用未知代理 */

/* 客户端支持的最大代理相关信息 */
#define TC_SVN_MAX_PROXY_URL_LEN               128     /* 代理服务器IP最大长度 */
#define TC_SVN_MAX_PROXY_USERNAME_LEN          256     /* 代理用户名最大长度 */
#define TC_SVN_MAX_PROXY_USERPWD_LEN           256     /* 代理密码最大长度 */
#define TC_SVN_MAX_PROXY_DOMAIN_LEN            128     /* 域名最大长度 */

/* 代理信息 */
typedef struct tagTcSVNProxyInfo
{
	TUP_CHAR            acProxyUrl[TC_SVN_MAX_PROXY_URL_LEN];              /* 代理服务器IP地址或域名 */
	TUP_UINT16			usProxyPort;									/* 代理服务器端口 */
	TUP_UINT16			usProxyType;                                    /* 代理类型，TC_SVN_PROXY_NONE/TC_SVN_PROXY_HTTP/TC_SVN_PROXY_SOCKS5 */
	TUP_CHAR            acProxyUserName[TC_SVN_MAX_PROXY_USERNAME_LEN];    /* 代理用户名 */
	TUP_CHAR            acProxyPassword[TC_SVN_MAX_PROXY_USERPWD_LEN];     /* 代理密码 */
	TUP_CHAR            acProxyDomain[TC_SVN_MAX_PROXY_DOMAIN_LEN];        /* 认证域名 */
} TC_SVN_PROXY_INFO_S;

/* SVN网关支持的最大用户名和密码长度 */
#define TC_SVN_MAX_USERNAME_LEN            64      /* SVN网关用户名最大长度 */
#define TC_SVN_MAX_USERPWD_LEN             32      /* SVN网关密码最大长度 */
#define TC_SVN_MAX_URL_LEN                 128     /* 虚拟网关最大长度 */

/* 隧道传输模式*/
#define TC_SVN_TUNNEL_MODE_DTLS            0       /* 隧道模式DTLS */
#define TC_SVN_TUNNEL_MODE_TLS             1       /* 隧道模式TLS */
#define TC_SVN_TUNNEL_MODE_UDP             2       /* 隧道模式UDP */
#define TC_SVN_TUNNEL_MODE_UDPS            3       /* 隧道模式TLS + UDPS */

/*注册信息*/
typedef struct tagTcSVNRegisterInfo
{
	TUP_CHAR                  acServerURL[TC_SVN_MAX_URL_LEN];       /* 网关地址，例如：9.1.1.3 或 www.abc.com */
	TUP_UINT16        usServerPort;							/* 网关的端口 */
	TUP_UINT16        usTunnelMode;							/* 隧道模式 */
	TUP_CHAR                  acUserName[TC_SVN_MAX_USERNAME_LEN];   /* 注册SVN网关用户名 */
	TUP_CHAR                  acPassword[TC_SVN_MAX_USERPWD_LEN];    /* 注册SVN网关密码  */
	TC_SVN_PROXY_INFO_S   stProxyInfo;							/* 代理信息结构 */
} TC_SVN_REGISTER_INFO_S;

/**********************************svn定义结束********************************************************/

#endif