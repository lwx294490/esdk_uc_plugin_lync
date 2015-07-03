#ifndef _TUP_CONF_BASEDEF_H_
#define _TUP_CONF_BASEDEF_H_

#include "tup_def.h"

//using std lib(c++)
#include <string>


#define TC_SDK_VERSION			113
#define TC_SDK_VERSION_STRING		"TUP Conf V001R001C300B023"
#define IMCC_USERDEVICE_H323_MCU      0x00100000  //必须与服务器定义保持一致

typedef TUP_UINT32	CONF_HANDLE;

typedef enum	//组件ID定义
{
	IID_COMPONENT_BASE      = 0x0000,	//会议控制
	IID_COMPONENT_DS		= 0x0001,	//文档共享
	IID_COMPONENT_AS		= 0x0002,	//屏幕共享
	IID_COMPONENT_AUDIO		= 0x0004,	//音频
	IID_COMPONENT_VIDEO		= 0x0008,	//视频
	IID_COMPONENT_RECORD	= 0x0010,	//录制
	IID_COMPONENT_CHAT		= 0x0020,	//聊天
	IID_COMPONENT_POLLING	= 0x0040,	//投票
	IID_COMPONENT_MS		= 0x0080,	//媒体共享
	IID_COMPONENT_FT		= 0x0100,	//文件传输
    IID_COMPONENT_WB		= 0x0200,	// 白板
} COMPONENT_IID;

typedef enum 
{
	JOIN_CONF_TYPE_NONE,
	JOIN_CONF_TYPE_PRIORITY_MS,
	JOIN_CONF_TYPE_PING
} JOIN_CONF_TYPE;//只适用于华为UC priority_ms方式入会

enum //用户类型定义
{
    CONF_ROLE_HOST          = 0x0001, //主持人
    CONF_ROLE_PRESENTER     = 0x0002, //主讲人
    CONF_ROLE_GENERAL       = 0x0008, //普通参与者
};

enum //日志级别
{
	LOG_LEVEL_ERROR = 0,		//错误级别
	LOG_LEVEL_WARNING,			//警告级别
	LOG_LEVEL_INFO,				//一般级别
	LOG_LEVEL_DEBUG				//调试级别	
};

typedef enum //会议控制选项
{
	CONF_OPTION_BASE           = 0x0000,		//只提供会议基本功能
	CONF_OPTION_USERLIST       = 0x0001,		//支持用户数据内部维护
    CONF_OPTION_LOAD_BALANCING = 0x0002,		//最优服务器登录
    CONF_OPTION_PHONE          = 0x0004,		//支持电话
	CONF_OPTION_NET_LIMIT	   = 0x0008,		//带宽限制模式：该模式下，启动屏幕共享时，会自动降低视频的码流，一段时间后恢复
	CONF_OPTION_VIDEO_DOUBLE_STREAM = 0x0010,	//视频支持双流
	CONF_OPTION_VIDEO_UDP		= 0x0020,		//视频采用UDP
	CONF_OPTION_QOS				= 0x0040,		//设置Qos
	CONF_OPTION_FLOW_CONTROL	= 0x0100,		//流控，平滑发送
	CONF_OPTION_SUPER_CONF		= 0x0200,		//超大会议
    CONF_OPTION_HOST_NO_GRAB    = 0x0400,       //不主动抢占主持人
    CONF_OPTION_PRESENTER_GRAB  = 0x0800,		//主动抢占主讲人

	CONF_OPTION_HWUC			= 0x1000,		//兼容老版本华为UC，临时选项，包括该选项将只能使用基本的会控功能和屏幕共享功能，华为UC升级完毕后该选项可以废弃
	CONF_OPTION_UC_AUDIO        = 0x2000,       //UC客户端，要带这个标记，音频模块对UC有特殊处理
	CONF_OPTION_AUDIO_TCP		= 0x4000,		//音频采用TCP
	CONF_OPTION_CLOUD_SYSTERM	= 0x8000,		//登录系统为云系统，置上这个标志后，视频模块不枚举云上的本地视频

	CONF_OPTION_DLL_NOT_FREE	= 0x00010000,	//不动态释放动态库

	CONF_OPTION_VIDEO_RUNCAPTURE= 0x00100000,	//视频一直打开Capture的模式
	CONF_OPTION_USE_PRIORITY_SVR= 0x00200000,	//优先使用ConfInfo内的服务器IP
	CONF_OPTION_CLOUD_MODE		= 0x10000000,	//云模式，胖瘦分离，UserID最高位为1时表示是瘦客户端
}CONF_OPTION;

typedef enum	//操作系统类型
{
    CONF_OS_UNKNOWN = 0,
    CONF_OS_WIN     = 1,
    CONF_OS_LINUX   = 2,
    CONF_OS_MACOS   = 3,
	CONF_OS_IOS		= 4,
	CONF_OS_ANDROID	= 5,

    CONF_MAX_OS_CODE			//无含义，只是表示枚举数量
} CONF_OS_TYPE;

typedef enum	//终端硬件类型
{
    CONF_DEV_UNKNOWN	= 0,
    CONF_DEV_PC			= 1,	//PC
    CONF_DEV_PDA		= 2,	//个人数字助理，已不支持
    CONF_DEV_PHONE		= 3,	//手机
	CONF_DEV_PAD		= 4,	//平板电脑
    CONF_DEV_GATEWAY    = 5,    //MGW用户，内部保留，外部不可见
	CONF_DEV_IPPHONE	= 6,	//带会议功能的IP电话
	CONF_DEV_TC			= 7,	//瘦客户端

    CONF_MAX_DEV_CODE			//无含义，只是表示枚举数量
} CONF_DEVICE_TYPE;

/*** 返回值定义 ***/
enum{
	TC_OK                                   = 0,
	TC_WARNING                              = 1,
	TC_ERROR                                = 2,		//
	TC_FAILURE                              = 3,		//一般错误
	TC_NULL_POINT							= 4,		//空指针
	TC_CALL_TIMEOUT							= 5,		//调用超时
	TC_PARAM_ERROR							= 6,		//参数错误
	TC_BUFFER_TOO_SHORT						= 7,		//内存太小
	TC_XML_PARAM_ERROR						= 8,		//xml参数错误
	TC_NO_PRIVILEGE							= 9,		//没有权限
	TC_FUNC_NOT_SUPPORT						= 10,		//调用的接口不支持或未实现
	TC_MODULE_NOT_LOAD						= 11,		//模块没有加载

    // 如果是IMCC层返回的错误码，则要减掉该基数
	TC_IMCC_RESULT_BASE                     = 100,
	TC_IMCC_RESULT_USER_REJECTED			= 101,		//拒绝用户请求
	TC_IMCC_RESULT_NETWORK_ERROR			= 102,		//网络错误
	TC_IMCC_RESULT_VERSION_NOT_MATCH		= 103,		//版本不支持
	TC_IMCC_RESULT_PROTOCOL_NOT_RIGHT		= 104,		//通信协议错误
	TC_IMCC_RESULT_TOO_MANY_CONNECTIONS		= 105,		//服务器超出最大连接数
	TC_IMCC_RESULT_EXPIRED					= 106,		//license过期
	TC_IMCC_RESULT_DOMAIN_TERMINATED		= 107,		//会议已结束
	TC_IMCC_RESULT_SERVER_CONN_FAILED		= 108,		//
	TC_IMCC_RESULT_SYS_SHUTINGDOWN			= 109,		//连接断开
	TC_IMCC_RESULT_DOMAIN_MERGING			= 110,		//
	TC_IMCC_RESULT_NO_SUCH_USER				= 111,		//鉴权时发现该用户不存在
	TC_IMCC_RESULT_CHANNEL_NOT_AVAILABLE	= 112,		//会议中channel达到阈值
	TC_IMCC_RESULT_TOKEN_NOT_POSSESSED		= 113,		//
	TC_IMCC_RESULT_TOKEN_NOT_AVAILABLE		= 114,		//
	TC_IMCC_RESULT_TOKEN_AUTH_FAIL			= 115,		//
	TC_IMCC_RESULT_TOO_MANY_TOKENS			= 116,		//
	TC_IMCC_RESULT_REG_KEY_NOT_EXIST		= 117,		//
	TC_IMCC_RESULT_REG_KEY_ALREADY_EXIST	= 118,		//
	TC_IMCC_RESULT_REG_PARENT_KEY_NOT_EXIST	= 119,		//
	TC_IMCC_RESULT_REG_OBJECT_ALREADY_EXIST	= 120,		//
	TC_IMCC_RESULT_REG_OBJECT_NOT_EXIST		= 121,		//
	TC_IMCC_RESULT_REG_TABLE_ID_TOO_LARGE	= 122,		//
	TC_IMCC_RESULT_REG_TABLE_ID_DUPLICATED	= 123,
	TC_IMCC_RESULT_POOL_NOT_AVAILABLE		= 124,
	TC_IMCC_RESULT_POOL_ALREADY_GRABBBED	= 125,
	TC_IMCC_RESULT_AUTH_FAILED				= 126,		//鉴权失败
	TC_IMCC_RESULT_UNKNOWN					= 127,		//未知错误
	TC_IMCC_RESULT_AUTH_REDIRECT			= 128,
	TC_IMCC_RESULT_QUERY_PARENT_OR_TOP_AGENT_EXPIRED = 129, 
	TC_IMCC_RESULT_DOMAIN_LOCKED           = 130,
	TC_IMCC_RESULT_AUTH_TIMEOUT            = 131,           
	TC_IMCC_RESULT_AUTH_KEY_NOT_AVAILABLE  = 132,
	TC_IMCC_RESULT_TOO_MANY_CONFERENCE     = 133,           
	TC_IMCC_RESULT_TOO_MANY_CONFERENCE_USER = 134,
	TC_IMCC_RESULT_NOT_DATA_USER_LICENSE    = 135,
	TC_IMCC_RESULT_AUTH_LINCENSE_TIMEOUT    = 136,//鉴权License超时，不允许入会
	TC_IMCC_RESULT_SVR_NOT_ALLOW            = 137,//服务器区域不允许，不允许入会
	TC_IMCC_RESULT_USER_NOT_ALLOW           = 138,//用户重复入会，不允许入会

	//copy from IMCC_ERROR
	TC_IMCC_ERROR_BASE                      = 200,
	TC_IMCC_ERROR_ALREADY_REGISTERED	    = 201,
	TC_IMCC_ERROR_NOT_REGISTERED		    = 202,
	TC_IMCC_ERROR_DOMAIN_ALREADY_EXIST      = 203,
	TC_IMCC_ERROR_DOMAIN_NOT_EXIST		    = 204,
	TC_IMCC_ERROR_DOMAIN_NUM_OVERFLOW	    = 205,
	TC_IMCC_ERROR_DOMAIN_MERGING		    = 206,
	TC_IMCC_ERROR_DOMAIN_CLOSEING		    = 207,
	TC_IMCC_ERROR_CONNECTION_NOT_EXIST	    = 208,
	TC_IMCC_ERROR_TOO_MANY_CONNECTIONS	    = 209,
	TC_IMCC_ERROR_INVALID_PARAMETERS	    = 210,
	TC_IMCC_ERROR_DATA_SIZE_EXCEEDED	    = 211,
	TC_IMCC_ERROR_NOT_AUTHORISED		    = 212,
	TC_IMCC_ERROR_TRANSMIT_BUFFER_FULL	    = 213,
	TC_IMCC_ERROR_VERSION_NOT_SUPPORTED	    = 214,
	TC_IMCC_ERROR_NETLAYER_FAIL			    = 215,
	TC_IMCC_ERROR_INSUFICIENT_MEMORY	    = 216,
	TC_IMCC_ERROR_USER_CLOSEING			    = 217,
	TC_IMCC_ERROR_UNKNOWN_ERROR			    = 218,
	TC_IMCC_ERROR_INVALID_STATE			    = 219,
	TC_IMCC_ERROR_NET_FAILED			    = 220,
	TC_IMCC_ERROR_USER_REFCNT				= 221,

	//copy from IMCC_REASON
    TC_IMCC_REASON_BASE                 = 300,
	TC_IMCC_REASON_USER_INITIATED		= TC_IMCC_REASON_BASE,
	TC_IMCC_REASON_USER_EJECTED			= 301,
	TC_IMCC_REASON_TOKEN_PURGED			= 302,	
	TC_IMCC_REASON_SYS_SHUTTINGDOWN		= 303,
	TC_IMCC_REASON_NETWORK_ERROR		= 304,
	TC_IMCC_REASON_TIME_OUT				= 305,
	TC_IMCC_REASON_UNKNOWN				= 306,
	TC_IMCC_REASON_EXTEND_MAX_LICENSE	= 307,
	TC_IMCC_REASON_SYSTEM_ERROR			= 308,
	TC_IMCC_REASON_USER_OFFLINE			= 309,

    // 会议错误信息定义
    TC_CONF_ERROR_NO_INIT               = 400,	//未初始化
    TC_CONF_ERROR_REPEAT_INIT           = 401,	//重复初始化
    TC_CONF_ERROR_REPEAT_JOIN           = 402,	//重复入会
    TC_CONF_ERROR_NO_JOIN               = 403,	
    TC_CONF_ERROR_NO_LOAD_COM           = 404,
    TC_CONF_ERROR_DATA_TOO_LAGE         = 405,
    TC_CONF_ERROR_SEND_TOO_FAST         = 406,
    TC_CONF_ERROR_ALREADY_TERMINATE     = 407,
    TC_CONF_ERROR_ALREADY_LEAVE         = 408,
    TC_CONF_ERROR_COM_LOADED            = 409,
    TC_CONF_ERROR_CON_UNLOADED          = 410,
    TC_CONF_ERROR_DISCONNECT_EXC        = 411,
    TC_CONF_ERROR_CONF_INFO             = 412, //参数错误
    TC_CONF_ERROR_CONF_NOT_INIT         = 413, //会议环境尚未初始化完成
    TC_CONF_ERROR_SELF_PRESENTER        = 414, //自己已经是主讲人
    TC_CONF_ERROR_PHONE_INIT            = 415, //电话未初始化
    TC_CONF_ERROR_PHONE_JOIN            = 416, //加入电话会议失败
    TC_CONF_ERROR_NO_MEMORY             = 417, //申请内存失败
    TC_CONF_ERROR_PARAM_INVALID         = 418, //参数无效
	TC_CONF_ERROR_ALREADY_NEW			= 419, //相同的会议已经存在

    // 聊天错误码基数
	TC_CHAT_ERROR_BASE	                = 1000,
	TC_CHAT_ERROR_INVALIDSESSION        = 1001,
	TC_CHAT_ERROR_INVALIDUSERID         = 1002,
	TC_CHAT_ERROR_INVALIDGROUPID        = 1003,
	TC_CHAT_ERROR_TOO_MANY_CHAR         = 1004,
	TC_CHAT_ERROR_TOO_MIN_INTERVAL      = 1005,


    // 文档共享错误码基数
	TC_DS_ERROR_BASE                    = 1100,
	TC_DS_ERROR_DOC_NOTEXIST			= 1101,	//文档不存在
	TC_DS_ERROR_PAGE_NOTEXIST			= 1102,	//页面不存在
	TC_DS_ERROR_PARAM_NOTEXIST			= 1103,	//用户参数不存在
	TC_DS_ERROR_DE_NOTEXIST				= 1104,	//DE不存在
	TC_DS_ERROR_DOC_ALREADYEXIST		= 1105,	//文档已经存在,重复创建时会有此错误
	TC_DS_ERROR_PAGE_ALREADYEXIST		= 1106,	//页面已存在
	TC_DS_ERROR_NOT_VALID_CWP			= 1107,	//给定的文件不是一个有效的CWP文件
	TC_ANNOT_ERROR_CUSTOMERTYPE_NOTEXIST = 1108,
	TC_DS_ERROR_PROP_NOT_EXIT			= 1109,
	TC_DS_ERROR_DOC_ALREADY_OPEN		= 1110,	//文档已经打开
    TC_DS_ERROR_DOC_NO_INIT             = 1111,	//模块未初始化
    TC_DS_ERROR_DOC_NO_SINK             = 1112,	//
    TC_DS_ERROR_DOC_NO_SESSION_JOIN     = 1113,	//
    TC_DS_ERROR_DOC_USER_OFFLINE        = 1114,	//
    TC_DS_ERROR_DOC_PRINTING            = 1115, //文档正在打印中
    TC_DS_ERROR_DOC_PAGE_DOWN           = 1116, //文档页面数据正在下载中
	TC_DS_ERROR_DOC_FORMAT_ERROR		= 1117,	//在文档共享时打开了保存的白板文件，或在白板共享时加载了保存的文档共享文档
	TC_DS_ERROR_DOC_PAGE_NOT_UPLOAD		= 1118, //页面数据没有上传到服务器，并且此时共享者已不在会议中
	

	TC_DS_LOADER_ERROR_COM				= 1121,			//COM调用失败
	TC_DS_LOADER_ERROR_NO_PAGE			= 1122,			//该文档0页
	TC_DS_LOADER_CANCELED				= 1123,			//取消打印
	TC_DS_LOADER_NOT_SUPPORT			= 1124,			//文档格式不支持
	TC_DS_LOADER_OFFICE_NOT_SUPPORT		= 1125,			//Office版本不支持
	TC_DS_LOADER_ERROR_TRANSFORM		= 1126,			//转换失败
	TC_DS_LOADER_FILE_EMPTY				= 1127,			//文件为空
	TC_DS_LOADER_FORMAT_ERROR			= 1128,			//文件格式错误
	TC_DS_LOADER_TIMEOUT				= 1129,			//打印超时
	TC_DS_LOADER_PRINTER_UNINSTALL		= 1130,			//打印机未安装
	TC_DS_LOADER_PPT_THREAD_ERROR		= 1131,			//PPT错误
	TC_DS_LOADER_PPT_LOAD_ERROR			= 1132,			//PPT加载错误
	TC_DS_LOADER_PAGE_OVER_MAX			= 1133,			//超出最大页数
	TC_DS_LOADER_PRINTER_ERROR			= 1134,			//打印机错误
	TC_DS_LOADER_SERVICE_ERROR			= 1135,			//打印服务出现错误
	TC_DS_LOADER_PPT2003_RUNNING		= 1136,			//PowerPoint2003运行中，不能加载
	TC_DS_LOADER_NO_PERMISSION			= 1137,			//没有权限打开

	TC_ANNOT_ERROR_LASER_EXIST			= 1140,			//激光点已经存在
	
    // 屏幕共享错误码基数 app share
	TC_AS_ERROR_BASE					= 1200,	//AS错误起始
	TC_AS_ERROR_UNKNOW					= 1201,	//未知错误
	TC_AS_ERROR_INVALIDPARA				= 1202,	//参数异常
	TC_AS_ERROR_INVALIDUSER				= 1203,	//角色异常
	TC_AS_ERROR_INVALIDSESSION			= 1204,	//通道异常
	TC_AS_ERROR_NULLCOMHANDLE			= 1205,	//模块句柄异常
	TC_AS_ERROR_INVALIDSTATE			= 1206,	//共享状态异常
	TC_AS_ERROR_INVALIDWND				= 1207,	//窗口句柄设置异常
	TC_AS_ERROR_CREATETASKFAIL			= 1208,	//创建共享进程异常
	TC_AS_ERROR_USERDROPPED				= 1209,	//用户已掉线
	TC_AS_ERROR_XMLERROR				= 1210,	//XML读写异常
	TC_AS_ERROR_MODULELOCKED			= 1211,	//模块被锁定
	TC_AS_ERROR_WAITFIRSTFRAME			= 1212,	//等待首帧发送
	TC_AS_ERROR_UNSUPPORT				= 1213, //当前版本不支持
	TC_AS_ERROR_FORBID_SCALE			= 1214, //不支持放大
	TC_AS_ERROR_MEM_ALLOC_FAILED		= 1215, //内存分配失败
	TC_AS_ERROR_NULLCTRLHANDLE			= 1216, //空屏幕共享句柄
	TC_AS_ERROR_INVALIDCHANNEL			= 1217, //非法数据通道
	TC_AS_ERROR_GDI_ALLOC_FAILED		= 1218, //GDI对象申请失败

	TC_AS_ERROR_ANNOT_BASE				= 1250,	//AS标注错误起始
	TC_AS_ERROR_ANNOT_DOC_NOTEXIST		= 1251,	//文档不存在
	TC_AS_ERROR_ANNOT_PAGE_NOTEXIST		= 1252,	//页面不存在
	TC_AS_ERROR_ANNOT_PARAM_NOTEXIST	= 1253,	//属性不存在
	TC_AS_ERROR_ANNOT_DE_NOTEXIST		= 1254,	//页面元素不存在
	TC_AS_ERROR_ANNOT_DOC_ALREADYEXIST	= 1255,	//文档已经存在
	TC_AS_ERROR_ANNOT_PAGE_ALREADYEXIST	= 1256,	//页面已存在
	TC_AS_ERROR_ANNOT_NOT_VALID_CWP		= 1257,	//给定的文件不是一个有效的CWP文件
	TC_AS_ERROR_ANNOT_CUSTOMERTYPE_NOTEXIST = 1258,	//用户自定义类型不存在

	TC_AS_ERROR_SC_BASE					= 1270, //AS采集错误起始
	TC_AS_ERROR_SC_UNKNOW				= 1271, //采集未知错误
	TC_AS_ERROR_SC_GDI_OBJECT			= 1272, //创建GDI对象失败

    // 视频错误码基数
	TC_VIDEO_ERROR_BASE                 = 1300,
	TC_VIDEO_ERROR_WND_NULL             = 1301,		//窗口为空
	TC_VIDEO_ERROR_WND_ISUSED           = 1302,		//窗口已经被使用
	TC_VIDEO_ERROR_DISCONNECT           = 1303,		//视频正在断线中
	TC_VIDEO_ERROR_CREATE_ENGINE        = 1305,		//创建Engine失败
	TC_VIDEO_ERROR_NO_SESSION	        = 1306,		//视频没有Session
	TC_VIDEO_ERROR_NO_VIDEO_OBJ	        = 1307,		//视频没有Obj对象
	TC_VIDEO_ERROR_NO_TABLE		        = 1308,		//视频没有空闲的Table表
	TC_VIDEO_ERROR_ALREADY_EXIST_OPENLIST  = 1309,	//打开设备时，此设备已经在正在打开的列表中
	TC_VIDEO_ERROR_COMPONENT_NOTREADY   = 1310,		//视频组件还没有准备好
	TC_VIDEO_ERROR_DLL_UNLOAD			= 1311,		//视频库已经被卸载掉了
	TC_VIDEO_ERROR_NOTIN_RESOLUTION_RANGE= 1312,	//分辨率不在使用范围之内
	TC_VIDEO_ERROR_RESOLUTION_NOTSUPPORT= 1313,		//分辨率超过设备本身的最大能力范围
	TC_VIDEO_ERROR_OVER_MAX_OPENVIDEO	= 1314,		//超过最大的打开视频路数
	TC_VIDEO_ERROR_SAME_CAPBILITY_USED	= 1320,		//此设备相同的能力已经在使用中
	TC_VIDEO_ERROR_STATUS_UNINIT		= 1321,		//视频组件当前是释放状态
	TC_VIDEO_ERROR_NOT_FIND_WNDCELL		= 1322,		//视频打不到相此用户设备的对应Cell
	TC_VIDEO_ERROR_NOTIN_MAXOPEN_RANGE	= 1323,		//超过最大的打开视频路数
	TC_VIDEO_ERROR_ALLREADY_PAUSE		= 1324,		//此视频已经处于暂停状态
	TC_VIDEO_ERROR_NOT_PAUSE_STATUS		= 1325,		//此视频未处于暂停状态
	TC_VIDEO_ERROR_SWITCH_STREAM_STATUS	= 1326,		//切换高低流时错误(不是Decode方，或是处于暂停状态)
	TC_VIDEO_ERROR_OPERATE_STATUS		= 1327,		//操作视频错误(数据Table表值已经不正常)
	TC_VIDEO_ERROR_ANDROID_LOCALVIEW_NO_RENDER = 1328,	//Android的话，是不需要创建本地Render
	TC_VIDEO_ERROR_RESOLUTION_NOTFIT	= 1329,		//设置分辨率跟能力分辨率不一致(针对外部采集设备)
	TC_VIDEO_ERROR_FLOWCTRL				= 1330,		//正在进行流控
	TC_VIDEO_ERROR_OUTSIDE_FLOWCTRL		= 1331,		//正在进行外部流控


	TC_VIDEO_ERROR_DEVICE_OPENED        = 1340,		//视频设备已经在使用中
	TC_VIDEO_ERROR_DEVICE_WIZARD_USED	= 1341,		//视频设备已经被向导使用中

	TC_VIDEO_ERROR_WIZARD_NOTSAME_DEVICE= 1342,		//向导设置参数时，不是同一个设备
	TC_VIDEO_ERROR_WIZARD_SAME_PARAM	= 1343,		//向导设置参数时，已有相同的参数

	TC_VIDEO_ERROR_MY_NODEID			= 1344,		//使用了自己的NodeID
	TC_VIDEO_ERROR_DEVICE_NOT_OPENED	= 1345,		//设备还没有打开


	TC_VIDEO_ERROR_NOT_MYDEVICE			= 1350,		//此视频设备不是当前用户的设备
	TC_VIDEO_ERROR_TOOLONG_FILENAME		= 1351,		//视频的文件名太长

	TC_VIDEO_ERROR_RENDER_DISPLAY_PARAM = 1352,		//视频Render参数出错
	TC_VIDEO_ERROR_ROTATE				= 1353,		//视频旋转参数出错
	TC_VIDEO_ERROR_PC_MOBILE_VERSION_API= 1354,		//PC与移动版本API错用

	TC_VIDEO_ERROR_NOT_WND				= 1355,		//窗口不是IsWindow()
	TC_VIDEO_ERROR_OVER_CAPTURECAPBILITY= 1356,		//此设备设置的能力超出Capture的能力
	TC_VIDEO_ERROR_NOT_WND_NOTFIT		= 1357,		//窗口在使用过程中(比如Detach时)，跟刚才Attach时的窗口不一致

	TC_VIDEO_ERROR_MULCONF_CANNOT_USERHME = 1358,	//多会议时不能使用VIDEOHME，另一个会议正在使用HME中
	TC_VIDEO_ERROR_MULCONF_HANGUP		= 1359,		//多会议时，此会议正在挂起状态

	TC_VIDEO_ERROR_IS_THIRDCAPTURE_DEVICE = 1360,		//此设备是第三方设备
	TC_VIDEO_ERROR_ISNOT_THIRDCAPTURE_DEVICE = 1361,	//此设备不是第三方设备

	TC_VIDEO_ERROR_BITRATE_RANGE		= 1362,		//码率不在正常的范围之内
	TC_VIDEO_ERROR_NOT_DOUBLESTREAM		= 1363,		//当前不是双流
	TC_VIDEO_ERROR_NOT_FIND_THIRDCARD	= 1364,		//找不到第三方的采集卡

	TC_VIDEO_ERROR_VIDEO_NOTOPEN		= 1365,		//视频还没被打开
	TC_VIDEO_ERROR_VIDEO_RECORDING		= 1366,		//视频正在录制中
	TC_VIDEO_ERROR_VIDEO_RECOREND		= 1367,		//视频录制已经结束

    // 音频错误码基数
	TC_AUDIO_ERROR_BASE                 = 1400,
	TC_AUDIO_ERROR_NOT_INITIALIZATION   = 1401,		//未初始化
	TC_AUDIO_ERROR_PARAM_NOTEXIST		= 1402,		//参数不存在
	TC_AUDIO_ERROR_FILE_NOT_SUPPORT		= 1403,
	//TC_AUDIO_NEGOTIATE_CODEC_FAIL		= 1404,
	TC_AUDIO_CREATE_SEND_THREAD_FAIL	= 1405,
	TC_AUDIO_PARAM_WRONG				= 1406,
	TC_AUDIO_FUNC_ALREADY_CALLED		= 1407,
	TC_AUDIO_ENGINE_INIT_FAILED			= 1408,
	TC_AUDIO_PARAM_NOT_INITIALIZATION   = 1409,		//未调用conf_audio_setParam设置参数
	TC_AUDIO_ERROR_SESSION_NOT_READY    = 1410,
	TC_AUDIO_ERROR_MIC_NOT_OPEN			= 1411,		//麦克风未打开
	TC_AUDIO_ERROR_SPEAKER_NOT_OPEN     = 1412,		//
	TC_AUDIO_MIC_ALREADY_OPEN			= 1413,		//
	TC_AUDIO_MIC_ALREADY_MUTE           = 1414,		//
	TC_AUDIO_MIC_ALREADY_UMUTE          = 1415,		//
	TC_AUDIO_OVER_MAX_DEVICE_OPEN		= 1416,		//超过容许的打开设备上限
	TC_AUDIO_SPEAKER_ALREADY_OPEN       = 1417,		//
	TC_AUDIO_SPEAKER_ALREADY_MUTE       = 1418,
	TC_AUDIO_SPEAKER_ALREADY_UMUTE      = 1419,
	TC_AUDIO_IS_NOT_SUPPORTED           = 1420,		//接口不被支持
	TC_AUDIO_ERROR_ALREADY_IN_PRIVATE   = 1421,
	TC_AUDIO_ERROR_ALREADY_NOT_IN_PRIVATE = 1422,
	TC_AUDIO_ERROR_DEVICE_INOPERABLE    = 1423,		//多会议中，设备被其他会议占用
	TC_AUDIO_ERROR_CONF_SUPPEND         = 1424,
	TC_AUDIO_ERROR_PHONE_MGW_CODEC_FAIL = 1425,
	TC_AUDIO_ERROR_PHONE_MGW_VA_ALREADY_NOTIFY = 1426,
	TC_AUDIO_ERROR_PHONE_MGW_VA_ALREADY_TALK = 1427,
	TC_AUDIO_ERROR_PHONE_SESSION_NOT_READY    = 1428,

	TC_AUDIO_ERROR_PHONE_MGW_VA_NOT_NOTIFY = 1429,
	TC_AUDIO_ERROR_PHONE_MGW_NOT_RESPONSE = 1430,
	TC_AUDIO_ERROR_TRY_LATER             = 1431,
	TC_AUDIO_ERROR_MGW_CODEC_ALREADY_SUCCESS = 1432,
	TC_AUDIO_ERROR_SAME_VALUE = 1433,
	

    // 媒体共享错误码基数
	TC_MS_ERROR_BASE                    = 1500,
	TC_MS_ERROR_BITRATE_TO_HIGH         = 1501,
	TC_MS_BITRATE_512_1024              = 1502,

    // 投票错误码基数
	TC_POLLING_ERROR_BASE               = 1600,

    // 录制错误码基数
	TC_RECORD_ERROR_BASE					= 1700,
	TC_RECORD_ERROR_INOPERABLE				= 1701,
	TC_RECORD_ERROR_PATH_NOT_FOUND			= 1702,		//路径错误
	TC_RECORD_ERROR_WAIT_TIME_OUT			= 1703,
	TC_RECORD_ERROR_SYSTEM_NOT_SUPPORT_WMF  = 1704,		//本地不支持WMV录制

	// 文件传输错误码基数
	TC_FT_ERROR_BASE                    = 1800,
	TC_FT_ERROR_CREATE_FILE_FAIL        = 1801,  //不能创建指定文件
	TC_FT_ERROR_DOWNLOADING_CANCELED    = 1802,  //下载已被取消
	TC_FT_ERROR_INVALID_FILE_HANDLE     = 1803,  //无效文件句柄
	TC_FT_ERROR_INVALID_STATE           = 1804,  //无效组件状态
	TC_FT_ERROR_INVALID_FILE            = 1805,  //文件路径名没有对应一个有效文件
	TC_FT_ERROR_EMPTY_FILE              = 1806,  //文件为空(不能上传)
	TC_FT_ERROR_UPLOADING_TIMEOUT       = 1807,  //文件上传超时
	TC_FT_ERROR_ALREADY_DOWNLOADING     = 1808,  //文件已经正在下载

};

/*** 回调消息定义 ***/
enum{
    //会议消息 
    CONF_MSG_ON_CONFERENCE_JOIN			= 1001,	//加入会议通知
    CONF_MSG_ON_CONFERENCE_TERMINATE	= 1002, //会议结束通知
    CONF_MSG_ON_CONFERENCE_LEAVE        = 1003,	//断开会议连接
    CONF_MSG_ON_COM_STATUS_UPDATE       = 1004,	//通知组件切换
    CONF_MSG_ON_PRIVILEGE_UPDATE        = 1005,	//权限变更
    CONF_MSG_ON_CONF_MODEL_UPDATE       = 1006,	//同步会议模式
    CONF_MSG_ON_LAYOUT_UPDATE           = 1007,	//同步会议布局
    CONF_MSG_ON_MESSAGE_UPADATE         = 1008, //会议Param变更
    CONF_MSG_ON_COM_FULL_SCREEN         = 1009,	//全屏切换

    CONF_MSG_ON_FLOW_CONTROL            = 1010,	//会议流控通知
    CONF_MSG_ON_LOCK_RSP                = 1011,	//请求会议锁定结果通知
    CONF_MSG_ON_LOCK_REPORT_IND         = 1012,	//会议锁定通知
    CONF_MSG_ON_REG_TOKEN_IND           = 1013,	//注册Token通知
    CONF_MSG_ON_EXTEND_RSP              = 1014,	//会议延时请求结果通知
    CONF_MSG_ON_EXTEND_IND              = 1015,	//会议延时通知

    CONF_MSG_ON_TIME_REMAINING_IND      = 1016, //会议结束时间通知
    CONF_MSG_ON_APPSVR_INVITE_CFM       = 1017, //

    CONF_MSG_ON_TABLE_INSERT_IND        = 1018,	//会议数据类型表创建通知
    CONF_MSG_ON_TABLE_DELETE_IND        = 1019,	//会议数据类型表删除通知
    CONF_MSG_ON_PING_COMPLETE           = 1020,	//会议ping结果通知
    CONF_MSG_ON_PING_PROGRESS_REPORT    = 1021,	//会议ping进度通知

    CONF_MSG_ON_DISCONNECT              = 1022, // 网络断线
    CONF_MSG_ON_RECONNECT               = 1023, // 网络重连成功

    CONF_MSG_ON_COMPONENT_LOAD          = 1031,	//组件加载成功通知
    CONF_MSG_ON_NOTICE_IND              = 1032, //公告数据通知
    CONF_MSG_ON_MAX_VOICE               = 1033, //语音激励消息
    CONF_MSG_SERVER_TIME                = 1034, //请求服务器时间

	CONF_MSG_ON_MUTE					= 1041,	//静音
	CONF_MSG_ON_NETSTATUS_REPORT		= 1051,	//网络状态报告，五种状态

    //////////////////////////////////////////////////////////////////////////
    // 会议用户消息
    CONF_MSG_USER_ON_HOST_CHANGE_IND       = 1101, //主持人变更，所有人都能收到
    CONF_MSG_USER_ON_HOST_CHANGE_CFM       = 1102, //主持人变更，主动申请者收到
    CONF_MSG_USER_ON_HOST_GIVE_IND         = 1103, //主持人变更，被给予者会收到
    CONF_MSG_USER_ON_HOST_GIVE_CFM         = 1104, //主持人变更，设置者会收到

    CONF_MSG_USER_ON_PRESENTER_CHANGE_IND  = 1105, //主讲人变更，所有人都能收到
    CONF_MSG_USER_ON_PRESENTER_CHANGE_CFM  = 1106, //主讲人变更，主动申请者收到
    CONF_MSG_USER_ON_PRESENTER_GIVE_IND    = 1107, //主讲人变更，被给予者会收到
    CONF_MSG_USER_ON_PRESENTER_GIVE_CFM    = 1108, //主讲人变更，设置者会收到

    CONF_MSG_USER_ON_ENTER_IND             = 1109, //用户加入
    CONF_MSG_USER_ON_LEAVE_IND             = 1110, //用户离开
    CONF_MSG_USER_ON_MODIFY_IND            = 1111, //用户信息变更
    CONF_MSG_USER_ON_MESSAGE_IND           = 1112, //用户消息通知
    CONF_MSG_USER_ON_OFFLINE_IND           = 1113, //用户离线通知
    CONF_MSG_USER_ON_RECONNECT_IND         = 1114, //用户离线恢复通知

    CONF_MSG_ON_PHONE_ENTER_IND	           = 1201,	//电话用户接入
    CONF_MSG_ON_PHONE_LEAVE_IND            = 1202,	//电话用户离开
    CONF_MSG_ON_PHONE_STATUS_IND           = 1203,	//电话状态变化
    CONF_MSG_ON_PHONE_SESSION_JOIN         = 1204,	//电话模块加入通知
    CONF_MSG_ON_PHONE_SESSION_OPEN         = 1205,	//电话模块打开通知
    CONF_MSG_ON_PHONE_SESSION_CLOSE        = 1206,	//电话模块关闭通知
    CONF_MSG_ON_PHONE_MUTE_STATUS_IND      = 1207,	//电话静音通知
    CONF_MSG_ON_PHONE_CALL_NID_IND         = 1208,	//
    CONF_MSG_ON_PHONE_CALL_MUTE_IND        = 1209,
    CONF_MSG_ON_PHONE_CALL_NAME_IND        = 1210,
    CONF_MSG_ON_PHONE_CALL_PIN_NUM_IND     = 1211,	//Pin码返回通知
    CONF_MSG_ON_PHONE_CALL_VIDEO_OPEN_STATUS_IND = 1212,
    CONF_MSG_ON_PHONE_CALL_USER_STATUS_IND       = 1213,
    CONF_MSG_ON_PHONE_CALL_USER_TYPE_IND         = 1214,
    CONF_MSG_ON_PHONE_CALL_VIDEO_CAPABLE_IND     = 1215,
    CONF_MSG_ON_PHONE_PC_USER_MIC_MUTE_REQ       = 1216,
    CONF_MSG_ON_PHONE_PC_USER_CAMERA_OPEN_REQ    = 1217,

	CONF_MSG_ON_PHONE_ON_XML_STATUS_GET          = 1218,
    CONF_MSG_ON_PHONE_IVR_REQ_IND                = 1219,
    CONF_MSG_ON_PHONE_MGW_MESSAGE_IND            = 1220,	//MGW 消息
	CONF_MSG_ON_PHONE_GET_PIN		             = 1221,	//用户获取PIN码
	CONF_MSG_ON_PHONE_CALL_FAILED				 = 1222,	//呼叫电话成功通知
	CONF_MSG_ON_PHONE_CALL_SUCCESSED			 = 1223,	//呼叫电话失败通知

	CONF_MSG_ON_PHONE_EXTEND					 = 1224,
	CONF_MSG_ON_PHONE_ROLLCALL_IND               = 1225,    //点名开启或禁用通知 nvalue1 == 1为开启，nvalue1 == 0为禁用


    //////////////////////////////////////////////////////////////////////////
    // VIDEO MESSAGE
    COMPT_MSG_VIDEO_ON_SWITCH					= 2001,		//视频状态相关:1:打开 0:关闭  2.Resume 4.Pause
    COMPT_MSG_VIDEO_ON_DEVICE_CHANGE			= 2002,		//设备插拨:(自己设备的插拨)

	COMPT_MSG_VIDEO_ON_DEVICE_INFO				= 2003,		//设备添加或是删除:(包括自己和别人)
	COMPT_MSG_VIDEO_ON_DEVICE_CAPBILITY			= 2004,		//设备能力信息(暂不使用)
	COMPT_MSG_VIDEO_ON_DISCONNECT				= 2005,		//视频模块是否闪断
	COMPT_MSG_VIDEO_ON_RECONNECT				= 2006,		//视频模块是否重新连上
	COMPT_MSG_VIDEO_ON_USER_STATUSCHANGE		= 2007,		//用户状态改变(暂不使用)
	COMPT_MSG_VIDEO_ON_USERDEVICE_STATUSCHANGE	= 2008,		//视频发送者的状态改变:(暂停，取消暂停)
	COMPT_MSG_VIDEO_ON_MAX_OPENVIDEO			= 2009,		//最大打开视频数

	COMPT_MSG_VIDEO_ON_NOTIFY					= 2010,		//收到别人发出的命令通知：打开命令，关闭命令

	COMPT_MSG_VIDEO_FLOWCONTROL_NOTIFY			= 2011,		//视频流控后，切换视频参数通知
	COMPT_MSG_VIDEO_WARNING_FLOWCONTROL			= 2012,		//视频流控警告，表明该网络条件下视频质量已经达到最小了

//for  Android
	COMPT_MSG_VIDEO_ON_GETDEVICE_NUM			= 2013,		//取得自己的设备个数
	COMPT_MSG_VIDEO_ON_GETDEVICE_INFO			= 2014,		//取得自己的设备信息

	COMPT_MSG_VIDEO_GETPARAM					= 2015,		//得到设置的视频参数

	COMPT_MSG_VIDEO_ON_SWITCH_MOREINFO			= 2021,		//视频状态相关:1:打开 0:关闭  2.Resume 4.Pause,更加详细的信息(主要是双流)
	COMPT_MSG_VIDEO_ON_JOINCHANNEL				= 2022,		//视频加入到哪个流
	COMPT_MSG_VIDEO_ON_LOAD_THIRDCAPTUREDLL		= 2023,		//加载第三方库

	COMPT_MSG_VIDEO_ON_DEVICECAPBILITY_NUM		= 2024,		//设备能力个数
	COMPT_MSG_VIDEO_ON_DEVICECAPBILITY_INFO		= 2025,		//设备能力信息

	COMPT_MSG_VIDEO_ON_FIRST_KEYFRAME			= 2026,		//返回解码后的第一个关键帧

	//For VTM Record
	COMPT_MSG_VIDEO_STARTRECORD_RESULT			= 2027,		//录制是否成功
	COMPT_MSG_VIDEO_ENDRECORD_RESULT			= 2028,		//结束录制是否成功

    COMPT_MSG_VIDEO_ON_DATA						= 2099,		//收到数据通知(暂不使用)

    //desktop share component, app share
	COMPT_MSG_AS_BASE					= 2100,	// 桌面共享消息起始
	
	COMPT_MSG_AS_ON_SCREEN_BASE			= 2110,	// 
	COMPT_MSG_AS_ON_SCREEN_DATA			= 2111,	//屏幕数据更新通知
	COMPT_MSG_AS_ON_SCREEN_SIZE			= 2112,	//屏幕大小变更通知 
	COMPT_MSG_AS_ON_SCREEN_BOND			= 2113,	// 
	COMPT_MSG_AS_ON_SCREEN_BORDER		= 2114,	// 屏幕黑边通知
	COMPT_MSG_AS_ON_SCREEN_KEYFRAME		= 2115,	// 屏幕关键帧通知

	COMPT_MSG_AS_ON_SHARING_BASE		= 2120,	// 
	COMPT_MSG_AS_ON_SHARING_STATE		= 2121,	//共享状态通知 
	COMPT_MSG_AS_ON_SHARING_SESSION		= 2122,	//共享通道通知 
	COMPT_MSG_AS_ON_PRIVILEGE			= 2123,	//共享权限通知 
	COMPT_MSG_AS_ON_MODULE				= 2124,	//共享权限通知 //(SHCBK_STATE_MODULE,0, State, NULL), 
	COMPT_MSG_AS_ON_VERSION				= 2125,	//共享权限通知 //(SHCBK_STATE_VERSION,0, version, NULL)
	COMPT_MSG_AS_ON_CHANNEL				= 2126,	//共享权限通知 //(SHCBK_STATE_CHANNEL,NodeID, Type, Action)

	COMPT_MSG_AS_ON_ANNOTATION_BASE		= 2130,	//屏幕共享标注消息起始(暂未使用)

	COMPT_MSG_AS_ON_USERDEFINE_BASE			= 2150,	//用户自定义内容起始 
	COMPT_MSG_AS_ON_USERDEFINE_MSG			= 2151,	//用户自定义消息通知 
	COMPT_MSG_AS_ON_USERDEFINE_REMOTE_SHARE	= 2152,	//远程邀请屏幕共享
	COMPT_MSG_AS_ON_USERDEFINE_CONTROL		= 2153,	//远程控制回调
	COMPT_MSG_AS_ON_ERROR					= 2154,	//屏幕共享异常消息

	COMPT_MSG_AS_ON_XML_GET_PARAM       = 2160,

   //document share component
    COMPT_MSG_DS_ON_DOC_NEW	= 2201,		//新建一个文档
    COMPT_MSG_DS_ON_DOC_DEL	= 2202,		//删除一个文档

    COMPT_MSG_DS_ON_PAGE_NEW = 2203,	//新建一页
    COMPT_MSG_DS_ON_PAGE_DEL = 2204,	//删除一页

    COMPT_MSG_DS_ON_CURRENT_PAGE_IND = 2205,    //同步翻页预先通知
    COMPT_MSG_DS_ON_CURRENT_PAGE     = 2206,	//同步翻页成功

	COMPT_MSG_DS_ON_DOCLOAD_START    = 2207,	//开始加载文档
	COMPT_MSG_DS_ON_PAGE_LOADED      = 2208,	//成功加载一页
	COMPT_MSG_DS_ON_DOCLOAD_FINISH   = 2209,	//加载文档结束

	COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY = 2210,	//文档界面数据
	COMPT_MSG_DS_XML_ON_OPEN = 2211,			//android下打开文档，异步返回的ID号	
    COMPT_MSG_DS_PAGE_DATA_DOWNLOAD = 2212,     //文档页面数据已经下载通知

	COMPT_MSG_DS_THUMBNAIL_UPDATE	= 2213,		//缩略图更新

	COMPT_MSG_DS_PAGEINFO_UPDATE	= 2214,		//页面信息更新（如是否被电子笔操作过）

	COMPT_MSG_DS_ANDROID_DOC_COUNT	= 2215,		//android使用，文档数量

	COMPT_MSG_DS_ANDROID_PIC_TOO_BIG = 2216,	//android使用，页面图片标注过多或过大，超过内存限制的部分不显示，通知上层
	COMPT_MSG_DS_ANDROID_PIC_NORMAL = 2217,		//android使用，页面图片标注由过多或过大状态回归正常（被删除），通知上层

	COMPT_MSG_DS_MAX = 2299,							//文档最大消息，没有实际意义
    //File Transfer
    COMPT_MSG_FT_ON_FILE_REMOVE = 2301,		//文件项删除
    COMPT_MSG_FT_ON_FILE_INFO,	            //文件项增加或状态更新
    COMPT_MSG_FT_ON_PROGRESS,			    //文件接收或发送进度
    COMPT_MSG_FT_ON_END,				    //发送或接收完成，或异常终止
    COMPT_MSG_FT_ON_READLY,					//文件模块

    //chat
	COMPT_MSG_CHAT_ON_GROUP_CREATE = 2400,	 //聊天群创建成功通知
	COMPT_MSG_CHAT_ON_GROUP_INFO_MODIFIED,	 //聊天群信息修改通知
    COMPT_MSG_CHAT_ON_GROUP_INVITE,			 //收到邀请群聊的通知
    COMPT_MSG_CHAT_ON_GROUP_KICKOUT ,		 //收到被踢出群聊的通知
	COMPT_MSG_CHAT_ON_GROUP_DESTROY,		 //创建者主动销毁组聊时通知

	COMPT_MSG_CHAT_ON_GROUP_USER_ONLINE,	//组聊中用户上线
	COMPT_MSG_CHAT_ON_GROUP_USER_OFFLINE,   //组聊中用户下线
	COMPT_MSG_CHAT_ON_GROUP_USER_LEAVE,		//组聊中用户退出

    COMPT_MSG_CHAT_ON_RECV_MSG,				//收到聊天消息
	COMPT_MSG_CHAT_ON_PUBLIC_MSG_REMOVE,    //删除公聊消息通知

	//mediashare
	COMPT_MSG_MS_ON_STARTPLAY = 2501,		//
	COMPT_MSG_MS_ON_PAUSEPLAY,
	COMPT_MSG_MS_ON_RESUMEPLAY,
	COMPT_MSG_MS_ON_STOPPLAY,
	COMPT_MSG_MS_ON_SEEKPLAY,
	COMPT_MSG_MS_ON_MIDPLAY,
	COMPT_MSG_MS_ON_PLAYERSTATE_CHANGE,
	COMPT_MSG_MS_ON_MEDIA_INFO,


	//polling
	COMPT_MSG_POLLING_ON_COMP_READY = 2601,		//投票组件准备好
	COMPT_MSG_POLLING_ON_RECV_POLL,				//收到新的问卷
	COMPT_MSG_POLLING_ON_RECV_ANSWER,			//收到新的答案
	COMPT_MSG_POLLING_ON_DELETE_POLL,			//收到删除问卷指令
	COMPT_MSG_POLLING_ON_POLL_ID_CHANGED,		//问卷ID发生变化
	COMPT_MSG_POLLING_ON_GLOBAL_PARAM_UPDATE,	//全局参数发生变化
	COMPT_MSG_POLLING_ON_POLL_PARAM_UPDATE = 2607,		//问卷参数更新消息
	//for android
	COMPT_MSG_POLLING_XML_ON_NEW_POLL = 2610,			//创建新问卷，返回问卷ID
	COMPT_MSG_POLLING_XML_ON_NEW_QUESTION,		//创建新问题，返回问题ID
	COMPT_MSG_POLLING_XML_ON_GET_POLL_TITLE,	//获取问卷标题
	COMPT_MSG_POLLING_XML_ON_GET_POLL_USERDATA, //获取问卷用户数据
	COMPT_MSG_POLLING_XML_ON_GET_POLL_COUNT,	//获取问卷数量
	COMPT_MSG_POLLING_XML_ON_GET_POLLID_BYINDEX,//根据索引获取问卷ID
	COMPT_MSG_POLLING_XML_ON_GET_CREATOR_USERID,//获取问卷创建者用户ID
	COMPT_MSG_POLLING_XML_ON_GET_QUESTION_COUNT,//获取某问卷问题数量
	COMPT_MSG_POLLING_XML_ON_GET_QUESTION,		//获取某问卷问题类型、问题内容、问题选项
	COMPT_MSG_POLLING_XML_ON_GET_QUESTION_USERDATA,//获取问题用户数据
	COMPT_MSG_POLLING_XML_ON_GET_QUESTIONID_BYINDEX,//根据索引获取问题ID
	COMPT_MSG_POLLING_XML_ON_GET_QUESTION_ANSWER, //获取问题答案
	COMPT_MSG_POLLING_XML_ON_GET_QUESTION_ANSWER_USERDATA,//获取问题答案用户数据
	COMPT_MSG_POLLING_XML_ON_LOAD_FROM_FILE, //获取加载的问卷数量以及问卷ID

	//audio
	COMPT_MSG_AUDIO_ON_AUDIO_MUTE_ALL_ATTENDEE = 2701,//收到会场静音消息

	COMPT_MSG_AUDIO_ON_ENGINE_DEVICE_CHANGE,     //音频设备热插拔
	COMPT_MSG_AUDIO_ON_ENGINE_RUNNING_ERR_NOTIFY,    //引擎系统运行时错误
	COMPT_MSG_AUDIO_ON_ENGINE_DEV_PLUGIN_NOTIFY, //有线耳机或者蓝牙耳机连接状态发生变化（android），该通知在引擎启动后生效
	COMPT_MSG_AUDIO_ON_ENGINE_ROUTE_CHANGE_NOTIFY,   //移动路由状态发生变化（移动平台）

	COMPT_MSG_AUDIO_ON_AUDIO_NEGOTIATE_CODEC,   //与服务器协商编解码结果
	COMPT_MSG_AUDIO_ON_AUDIO_ACTION,		    //收到mic控制命令,以及进入私聊命令与离开私聊通知
	COMPT_MSG_AUDIO_ON_AUDIO_MAX_OPEN_DEVICE,	//最大容许打开的设备数量
	COMPT_MSG_AUDIO_ON_AUDIO_DEVICE_STATUS_CHANGE,//音频设备状态通知 mic
	COMPT_MSG_AUDIO_ON_AUDIO_MGW_EXCEPTION,      //MGW异常
	COMPT_MSG_AUDIO_ON_AUDIO_MGWVA_NEGOTIATE_CODEC, //语音助理
	COMPT_MSG_AUDIO_ON_AUDIO_OPEN_MIC, //异步打开mic结果

	COMPT_MSG_AUDIO_ON_SYSTEM_SPEAKER_VOLUME,    //系统扬声器音量改变通知
	COMPT_MSG_AUDIO_ON_SYSTEM_MIC_VOLUME,        //系统麦克风音量改变通知

	COMPT_MSG_AUDIO_ON_XML_MIC_VOLUME  = 2780,	//Mic音量变更通知
	COMPT_MSG_AUDIO_ON_XML_SPEAKER_VOLUME,		//扬声器音量变更通知


	//white board
	COMPT_MSG_WB_ON_DOC_NEW	= 2801,		//新建一个文档
	COMPT_MSG_WB_ON_DOC_DEL	= 2802,		//删除一个文档

	COMPT_MSG_WB_ON_PAGE_NEW = 2803,	//新建一页
	COMPT_MSG_WB_ON_PAGE_DEL = 2804,	//删除一页

    COMPT_MSG_WB_ON_CURRENT_PAGE_IND = 2805, //翻页前预先通知
	COMPT_MSG_WB_ON_CURRENT_PAGE = 2806,	 //翻页成功通知
	COMPT_MSG_WB_ON_PAGE_DATA = 2807,	//

	COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY = 2808,	//白板界面数据
    COMPT_MSG_WB_PAGE_DATA_DOWNLOAD = 2809,            //文档页面数据已经下载通知

	COMPT_MSG_WB_XML_ON_NEW_DOC = 2810,				//android下new doc后返回
	COMPT_MSG_WB_XML_ON_NEW_PAGE = 2811,				//android下new page后返回
	COMPT_MSG_WB_XML_ON_COPY_PAGE = 2812,				//android下copy page后返回

	COMPT_MSG_WB_THUMBNAIL_UPDATE	= 2813,		//缩略图更新

	COMPT_MSG_WB_PAGEINFO_UPDATE	= 2814,		//页面信息更新

	COMPT_MSG_WB_ANDROID_DOC_COUNT	= 2815,		//android使用，文档数量

	COMPT_MSG_WB_ANDROID_PIC_TOO_BIG = 2816,	//android使用，页面图片标注过多或过大，超过内存限制的部分不显示，通知上层
	COMPT_MSG_WB_ANDROID_PIC_NORMAL = 2817,		//android使用，页面图片标注由过多或过大状态回归正常（被删除），通知上层

	COMPT_MSG_WB_MAX,							//白板最大消息，没有实际意义

	//annotation 2014 0303
	COMPT_MSG_ANNO_CREATE_NEWID		= 2901,			//新建一个ANNO

	COMPT_MSG_ANNO_TEXTCREATE_NEWID	= 2902,			//新建一个Text
	COMPT_MSG_ANNO_TEXT_GETINFO		= 2903,			//得到Text_Anno信息

	COMPT_MSG_ANNO_HITTEST			= 2904,			
	COMPT_MSG_ANNO_HITTEST2			= 2905,			
	COMPT_MSG_ANNO_GETINFO			= 2906,

	COMPT_MSG_ANNO_MAX,							//ANNOTATION最大消息，没有实际意义
};

#define TC_MAX_PATH	 256

#define TC_MAX_PHONE_CONF_NUM_LEN	16
#define TC_MAX_PHONE_PASS_CODE_LEN	32
#define TC_MAX_PHONE_USER_NAME_LEN	64
#define TC_MAX_PHONE_SVR_URL_LEN	128

#define TC_MAX_CONF_SERVER_IP       128			//IP地址要长一些
#define TC_MAX_CONF_SITE_ID_LEN	    16
#define TC_MAX_HOST_KEY_LEN	        32
#define TC_MAX_ENCRYPTION_KEY       32
#define TC_MAX_USER_NAME_LEN	    64
#define TC_MAX_TABLE_NAME_LEN       64
#define TC_MAX_URI_LEN			    128
#define TC_MAX_CONF_TITLE_LEN       128
#define TC_MAX_USER_LOG_URI_LEN     128
#define TC_MAX_CONF_USER_INFO_LEN   256
#define TC_MAX_SITE_URL_LEN         256

#define TC_MAX_ANNO_LEN				128

#define TC_IMCC_REULT_TRANCEFROM(param) ((param == TC_OK) ? TC_OK : TC_IMCC_RESULT_BASE + param)
#define TC_IMCC_ERROR_TRANCEFROM(param) ((param == TC_OK) ? TC_OK : TC_IMCC_ERROR_BASE + param)
#define TC_IMCC_REASON_TRANCEFROM(param) ((param == TC_OK) ? TC_OK : TC_IMCC_REASON_BASE + param)


// 对应服务器类型定义
typedef TUP_UINT32  TC_Time;
typedef TUP_UINT32	TC_Conf_User_Status;
typedef TUP_UINT16	TC_Conf_Presence_Flag;
typedef TUP_UINT32  TC_Conf_Capability;

//////////////////////////////////////////////////////////////////////////
/*用户信息数据*/
typedef struct tag_conf_user_record
{
    TUP_UINT32					user_alt_id;			//用户ID
    TUP_UINT8					device_type;			//设备类型
    TUP_UINT8					os_type;				//操作系统类型
    TC_Conf_Presence_Flag		user_presence_flag;		//用户状态
    TC_Conf_Capability			user_capability;		//用户能力，由应用层控制
    TC_Conf_User_Status			user_status;			//用户权限信息，暂不用
    TUP_CHAR					user_name[TC_MAX_USER_NAME_LEN];		//用户名称
    TUP_CHAR					user_alt_uri[TC_MAX_USER_LOG_URI_LEN];		//用户统一标识
    TUP_UINT8*					user_info;
    TUP_UINT16					user_info_len;
	TUP_CHAR					server_ip[TC_MAX_CONF_SERVER_IP];

#ifdef __cplusplus
	tag_conf_user_record()
	{
		memset(this, 0, sizeof(tag_conf_user_record));
	}
#endif
} TC_Conf_User_Record;


#if defined(WIN32) 
	#define TUP_STDCALL __stdcall
#else
	#define TUP_STDCALL
#endif

// 回调函数类型定义
#if defined(MY_ANDROID) && (defined(TEST_8950) || !(defined CONF_IPPHONE))
	typedef TUP_VOID (TUP_STDCALL *conference_multi_callback)(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pMsg, TUP_VOID* pContext, TUP_INT nSize);	
#else
	//conference_multi_callback 和 component_multi_callback用于多会议场景
	typedef TUP_VOID (TUP_STDCALL *conference_multi_callback)(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pVoid, TUP_INT nSize);   //会议的回调函数	
#endif
   
//多会议组件的回调函数
typedef TUP_VOID (TUP_STDCALL *component_multi_callback)(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pVoid, TUP_INT nSize);    //组件的回调函数

//////////////////////////////////////////////////////////////////////////
// 会议初始参数
typedef struct tag_init_paramter
{
    CONF_OS_TYPE        os_type;					//操作系统类型
    CONF_DEVICE_TYPE    dev_type;					//物理设备类型
	TUP_UINT8			media_log_level;			//媒体日志级别
	TUP_UINT8			sdk_log_level;				//组件日志级别
	TUP_CHAR			log_path[TC_MAX_PATH];		//日志目录，可选
	TUP_CHAR			temp_path[TC_MAX_PATH];		//临时目录，可选
	TUP_UINT32          dev_dpi_x;					//设备横向DDI，android平台需要设置，其他平台可设置为0
	TUP_UINT32          dev_dpi_y;					//设备纵向DDI，android平台需要设置，其他平台可设置为0

#ifdef __cplusplus
	tag_init_paramter()
	{
		memset(this, 0, sizeof(tag_init_paramter));
	}
#endif
} Init_param;

//////////////////////////////////////////////////////////////////////////
//会议参数
typedef struct tag_conf_info
{
	TUP_UINT32              conf_id;			//会议ID，一般需要服务器创建后提供，必选
	TUP_UINT32              user_id;			//用户ID，会议中用户的唯一标识，外部定义，必选
    TUP_UINT32              user_type;			//用户类型，必选：主持人 1、主讲人2 和普通与会者8
    TUP_UINT32              user_capability;	//用户能力，应用层定义，可选
    TUP_INT64               sever_timer;		//time_t 日历时间：从一个时间点(一般是1970年1月1日0时0分0秒)到那时的秒数，可以为0

    TUP_CHAR                host_key[TC_MAX_HOST_KEY_LEN];		    //主持人密码：主持人入会必须设置，其他情况不需要
    TUP_CHAR                site_url[TC_MAX_SITE_URL_LEN];		    //会议网站地址，IPT方案中为U19的地址，可选，可以为空
    TUP_CHAR                site_id[TC_MAX_CONF_SITE_ID_LEN];	    //站点ID，可选，可以为空
    TUP_CHAR                user_name[TC_MAX_USER_NAME_LEN];        //用户名称
    TUP_CHAR                conf_title[TC_MAX_CONF_TITLE_LEN];	    //会议主题名称
    TUP_CHAR                ms_server_ip[TC_MAX_CONF_SERVER_IP];    //会议服务器地址，单个地址或URL
    TUP_CHAR                encryption_key[TC_MAX_ENCRYPTION_KEY];  //会议鉴权密码，必选
    TUP_CHAR                user_log_uri[TC_MAX_USER_LOG_URI_LEN];  //用户统一描述符，一般用于和其他系统集成时用户绑定，可选

	CONF_OS_TYPE			os_type;
	CONF_DEVICE_TYPE		dev_type;
    TUP_UINT8*		        user_info;			 //用户附带信息，可选
    TUP_UINT16		        user_info_len;		 //用户附带信息长度，可选

#ifdef __cplusplus
	tag_conf_info()
	{
		memset(this, 0, sizeof(tag_conf_info));
        user_type = CONF_ROLE_GENERAL;
	}

    ~tag_conf_info()
    {
        if (user_info_len > 0 && user_info)
        {
            delete[] user_info;
            user_info = NULL;
        }
    }

    tag_conf_info(const struct tag_conf_info & conf_info)
    {
        *this = conf_info;
    }

	tag_conf_info & operator = (const tag_conf_info & confInfo)
	{		
		if(this == &confInfo) {
			return *this;
		}

        memcpy(this, &confInfo, sizeof(tag_conf_info));

        user_info = NULL;
        if (confInfo.user_info && confInfo.user_info_len)
        {
			user_info = new(std::nothrow) TUP_UINT8[confInfo.user_info_len];
			if (user_info)
			{
				memcpy(user_info, confInfo.user_info, confInfo.user_info_len);
			}
        }
	
		return *this;
	}
#endif

} TC_CONF_INFO;

//CONF_MSG_USER_ON_MODIFY_IND时对应的更新对象
#define TC_USER_MODIFY_PF        0x04	//presence_flag更新
#define TC_USER_MODIFY_PS        0x08	//user_status更新
#define TC_USER_MODIFY_PC        0x10	//user_capability更新
#define TC_USER_MODIFY_PD        0x20   //
#define TC_USER_MODIFY_PU        0x40   //user_info更新

////////////////////////////////Base Define/////////////////////////////////

typedef TUP_UINT32  COLORRGBA;


//点的定义
typedef struct tagTcPoint
{
	TUP_INT	x;
	TUP_INT	y;
}TC_POINT;

//尺寸定义
typedef struct tagTcSize
{
	TUP_INT	cx;
	TUP_INT	cy;
}TC_SIZE;

//矩形定义
typedef struct tagTcRect
{
	TUP_INT nX;
	TUP_INT nY;
	TUP_INT nWidth;
	TUP_INT nHeight;
}TC_RECT;

//矩形定义
typedef struct tagTcRect2
{
	TUP_INT	left;
	TUP_INT	top;
	TUP_INT	right;
	TUP_INT	bottom;
}TC_RECT2;

enum	//图像格式
{
	Bitmap_Format_Pal1,
	Bitmap_Format_Pal2,
	Bitmap_Formatt_Pal4,
	Bitmap_Format_Pal8,	
	Bitmap_Format_RGB565,
	Bitmap_Format_RGB888,
	Bitmap_Format_XRGB8888,
};

//返回的图片数据
struct TC_BITMAP
{
    TUP_LONG        bmType;
    TUP_LONG        bmWidth;
    TUP_LONG        bmHeight;
    TUP_LONG        bmWidthBytes;

    TUP_UINT16      bmPlanes;
    TUP_UINT16      bmBitsPixel;
    TUP_VOID*       bmBits;			//图片数据
};

//////////////////////////////视频模块定义部分/////////////////////////////////

typedef enum	//视频分辨率
{
	VIDEO_SIZE_160_120  =  0x00000000,      // 160 x 120  
	VIDEO_SIZE_176_144,                     // 176 x 144 
	VIDEO_SIZE_320_240,                     // 320 x 240	
	VIDEO_SIZE_352_288,                     // 352 x 288
	VIDEO_SIZE_640_480,                     // 640 x 480
	VIDEO_SIZE_704_576,                     // 704 x 576	
	VIDEO_SIZE_960_720,                     // 960 x 720
	VIDEO_SIZE_1280_720,                    // 1280 x 720	
	VIDEO_SIZE_1920_1080,                   // 1920 x 1080
	VIDEO_SIZE_COUNT
}ENUM_VIDEO_SIZE;

#ifdef __cplusplus
const  TUP_CHAR g_ArrayVideoResolutionString[VIDEO_SIZE_COUNT][16] =
{
	{"160 X 120"},
	{"176 X 144"},
	{"320 X 240"},
	{"352 X 288"},
	{"640 X 480"},
	{"704 X 576"},
	{"960 X 720"},
	{"1280 X 720"},
	{"1920 X 1080"}
};

const TC_SIZE g_ArrayVideoResolution[VIDEO_SIZE_COUNT] = 
{
	{160,	120}, 	
	{176,	144}, 
	{320,	240}, 
	{352,	288},
	{640,	480}, 
	{704,	576}, 
	{960,	720},
	{1280,	720}, 
	{1920,	1080}
};
#endif

typedef enum
{
	VIDEO_DEVICE_PC		= 1,	//PC
	VIDEO_DEVICE_PHONE	= 2,	//电话
	VIDEO_DEVICE_ZZTP	= 3		//智真TP
}ENUM_VIDEO_DEVICE_TYPE;


//视频设备定义
typedef struct tagTC_DEVICE_INFO
{
	TUP_UINT32	_UserID;			//组件是当作NodeID,UI层当作是UserID
	TUP_UINT32	_DeviceID;			//设备ID
	TUP_UINT32	_RecordID;			//表序，对应用层无用
	TUP_CHAR	_szName[256];		//设备名字
	TUP_INT		_status;			//设备状态 (现无用)	 [2013 0627 当前用来表示Android名字后面的转向]
	TUP_UINT16	_Version;			//版本
	TUP_UINT16	_DeviceType;		//设备的类型(摄像头，智真，电话)

#ifdef __cplusplus
	tagTC_DEVICE_INFO()
	{
		_UserID		= 0;
		_DeviceID	= 0;
		_RecordID	= 0;
		memset(_szName, 0, sizeof(_szName));
		_status		= 0;
		_DeviceType	= VIDEO_DEVICE_PC;
		_Version = 0;
	}

	tagTC_DEVICE_INFO & operator = (const tagTC_DEVICE_INFO & tcInfo)
	{
		if(this == &tcInfo) 
		{
			return *this;
		}

		_UserID		= tcInfo._UserID;
		_DeviceID	= tcInfo._DeviceID;
		_RecordID	= tcInfo._RecordID;

#ifdef WIN32
		strncpy_s(_szName,tcInfo._szName, sizeof(_szName) - 1);
#else
		strncpy(_szName,tcInfo._szName, sizeof(_szName) - 1);
#endif
		_szName[sizeof(_szName) - 1] = 0;

		_status		= tcInfo._status;
		_DeviceType	= tcInfo._DeviceType;

		return *this;
	}

	TUP_BOOL operator == (const tagTC_DEVICE_INFO & tcInfo)
	{
		if(this == &tcInfo) 
		{
			return TRUE;
		}

		if ( (strcmp(_szName, tcInfo._szName) == 0) && (_DeviceID == tcInfo._DeviceID) && (_UserID == tcInfo._UserID) && (_DeviceType == tcInfo._DeviceType) )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
#endif	
}TC_DEVICE_INFO; 

//视频设置参数定义
typedef struct tagTC_VIDEO_PARAM
{
	TUP_UINT32	dwUserID;			//用户ID (对于应用层来说是UserID,对于组件层来说是NodeID)
	TUP_UINT32	dwDeviceID;			//设备ID
	TUP_UINT32	xResolution;		//x分辨率(宽)
	TUP_UINT32	yResolution;		//y分辨率(高)
	TUP_UINT32	nFrameRate;			//帧率
	TUP_UINT32	nBitRate;			//码流
	TUP_UINT32	nRawtype;			//视频格式：如YUV，当前无效
	TUP_UINT32	nFecValue;			//FEC的百分比

#ifdef __cplusplus
	tagTC_VIDEO_PARAM()
	{
		dwUserID	= 0;
		dwDeviceID	= 0;
		xResolution = 0;
		yResolution = 0;
		nFrameRate	= 0;
		nBitRate	= 0;
		nRawtype	= 0;
		nFecValue	= 0;
	}
#endif	
}TC_VIDEO_PARAM;

//第三方采集卡属性定义
typedef struct tagTC_VIDEO_THIRDCAPTURE_PROPERTY
{
	TUP_UINT32	dwUserID;			//用户ID (对于应用层来说是UserID,对于组件层来说是NodeID)
	TUP_UINT32	dwDeviceID;			//设备ID
	TUP_UINT32	dwDeviceType;		//设备类型
	TUP_UINT32	nBrightness;		//亮度值（0-255）
	TUP_UINT32	nContrast;			//对比度（0-127）
	TUP_UINT32	nSaturation;		//饱和度（0-127）
	TUP_UINT32	nHue;				//色调（0-255）

#ifdef __cplusplus
	tagTC_VIDEO_THIRDCAPTURE_PROPERTY()
	{
		dwUserID		= 0;
		dwDeviceID		= 0;
		dwDeviceType	= 0;
		nBrightness		= 0;
		nContrast		= 0;
		nSaturation		= 0;
		nHue			= 0;
	}
#endif	
}TC_VIDEO_THIRDCAPTURE_PROPERTY;

//双流状态定义
typedef struct tagTC_VIDEO_DOUBLESTREAM_STATUS
{
	TUP_UINT32	dwUserID;			//用户ID (对于应用层来说是UserID,对于组件层来说是NodeID)
	TUP_UINT32	dwDeviceID;			//设备ID

	TUP_UINT32	xResolution;		//x分辨率(宽)
	TUP_UINT32	yResolution;		//y分辨率(高)

	TUP_BOOL	bHighOrLowChannel;	//当前加入到高流还是低流
	TUP_BOOL	bDoubleStream;		//是否双流
	TUP_BOOL	bOwnLowStream;		//是否还拥有低流	
	TUP_BOOL	bFlowCtrl;			//是否是流控告警引起

#ifdef __cplusplus
	tagTC_VIDEO_DOUBLESTREAM_STATUS()
	{
		dwUserID			= 0;
		dwDeviceID			= 0;
		xResolution			= 0;
		yResolution			= 0;

		bHighOrLowChannel	= false;
		bDoubleStream		= false;
		bOwnLowStream		= false;

		bFlowCtrl			= false;
	}
#endif	
}TC_VIDEO_DOUBLESTREAM_STATUS;

typedef enum
{
	THIRDCAPTURE_NULL = 0,
	THIRDCAPTURE_HIKVISION = 1,
	THIRDCAPTURE_FRANCE = 2

}THIRDCAPTURE_TYPE;

enum{
	VIDEO_CHANGE_ADD	= 1,
	VIDEO_CHANGE_REMOVE,
	VIDEO_CHANGE_UPDATE,
};

enum{
	DEVICE_CHANGE_REMOVE = 0,
	DEVICE_CHANGE_ADD = 1,
};

enum{
	VIDEO_NOTIFY_OPEN = 1,							//通知其它人打开视频
	VIDEO_NOTIFY_CLOSE,								//通知其它人关闭视频
	VIDEO_NOTIFY_DATA_SENDTO_PHONESESSION,			//视频数据发送给PHONESESSION
	VIDEO_NOTIFY_NULLDATA_SENDTO_PHONESESSION,		//电话的数据自己发送给PHONESESSION
	VIDEO_NOTIFY_DATA_SENDTO_MCUSESSION,			//视频数据发送给MCUSESSION 智真
	VIDEO_NOTIFY_NULLDATA_SENDTO_MCUSESSION,		//电话的数据自己发送给MCUSESSION 智真
};

//OnVideoChange, 为了与IPAD状态统一，所以设成一致的
//IPAD的状态设置，为了统一，所以设成一致的
enum {
	VIDEO_OPERATOR_CLSOE			=	0,			//关闭状态
	VIDEO_OPERATOR_OPEN				=	1,			//打开状态
	VIDEO_OPERATOR_RESUME 			=	2,			//取消暂停状态
	VIDEO_OPERATOR_PAUSE			=	4,			//暂停状态
	VIDEO_OPERATOR_ERROR			=	5,			//错误状态
};

/**< 图像旋转的类型 */
enum
{
    VIDEO_ROTATE_0   = 0  ,  						//视频不旋转
    VIDEO_ROTATE_90  = 90 ,  						//视频逆时针旋转90度
    VIDEO_ROTATE_180 = 180,  						//视频逆时针旋转180度
    VIDEO_ROTATE_270 = 270   						//视频逆时针旋转270度
};

//for VTM record
//某一路视频录制的相关信息
typedef struct ST_VideoRecord_Info
{
	TUP_CHAR*	cRecordFileName;				//录制文件名
	TUP_INT		iRecordFileNameLen;				//录制文件名长度
	TUP_BOOL	bHighOrLow;						//是否是高流或低流（只限于发送方可以传高流或低流，对接收方此参数无效）
	TUP_INT		Width;							//宽	(待用，适用于MGW与VideoE交互)
	TUP_INT		Height;							//高  (待用，适用于MGW与VideoE交互)
	TUP_INT		FrameRate;						//帧率(待用，适用于MGW与VideoE交互)
} VideoRecord_Info;

//////////////////屏幕共享模块定义部分///////////////////////
//app share
//sharing callback
//screen data
#define AS_CBK_SCREEN_DATA				0x00010001	//(SHCBK_SCREEN_DATA, null, null, &rc)
#define AS_CBK_SCREEN_SIZE				0x00010002	//(SHCBK_SCREEN_SIZE, SrcID, 0, &stRemote)
#define AS_CBK_SCREEN_BOND				0x00010003
#define AS_CBK_SCREEN_BORDER			0x00010004	//(SHCBK_SCREEN_BORDER, null, null, &rc)
//annotation data
#define AS_CBK_ANNOTA_DATA				0x00020001
//sharing state
#define AS_CBK_STATE_SHARINGSTATE		0x00040001	//(SHCBK_STATE_SHARINGSTATE, NULL, State, NULL)
#define AS_CBK_STATE_SESSION			0x00040002	//(SHCBK_STATE_CHANNEL,SHACTION_MODIFY, m_SessionOwnerID, NULL), (SHCBK_STATE_CHANNEL,SHACTION_ADD, NULL, NULL)
#define AS_CBK_STATE_PRIVILEGE			0x00040003	//(SHCBK_STATE_PRIVILEGE, type, action, ID)
#define AS_CBK_STATE_MODULE				0x00040004	//(SHCBK_STATE_MODULE,0, State, NULL), 
#define AS_CBK_STATE_VERSION			0x00040005  //(SHCBK_STATE_VERSION,0, version, NULL)
#define AS_CBK_STATE_CHANNEL			0x00040006  //(SHCBK_STATE_CHANNEL,NodeID, Type, Action)
//user define message
#define AS_USER_DEFINE_DATA				0x0001	//(SHCBK_USER_DEFINE_DATA, msgType, src, data)
#define AS_USER_DEFINE_REMOTE_SHARE		0x0002
#define AS_USER_DEFINE_CONTROL			0x0003	//(SHCBK_USER_DEFINE_CONTROL, ControlType, msgType, data)
#define AS_USER_DEFINE_CORE_ERROR		0x0004	//(SHCBK_USER_DEFINE_CORE_ERROR, msgType, src, data)
//error type
#define AS_CBK_ERROR_UNKNOW				0x0000	//屏幕共享异常消息起始
#define AS_CBK_ERROR_PDU_DATA			0x0001	//收到异常RECT消息
#define AS_CBK_ERROR_CAP				0x0002	//采集数据异常消息
#define AS_CBK_ERROR_GDI				0x0003	//GDI句柄异常消息
#define AS_CBK_ERROR_CORE				0x0004	//CORE异常消息
//remote share action
#define	REMOTESHARE_ACTION_SHARE		0x0001
#define	REMOTESHARE_ACTION_STOP			0x0002
#define	REMOTESHARE_ACTION_REJECT		0x0003
//sharing camera
#define AS_CBK_CAMERA_GETINFO			0x00080001
//sharing state
#define AS_STATE_NULL					0x0000	//无活动
#define AS_STATE_VIEW					0x0001	//观看端观看
#define AS_STATE_START					0x0002	//共享端共享
#define AS_STATE_PAUSE					0x0003	//共享端暂停
#define AS_STATE_PAUSEVIEW				0x0004	//观看端暂停
//sharing sub state
#define AS_STATE_SUB_NORMAL				0x0000	//普通状态
#define AS_STATE_SUB_CONTROL			0x0100	//控制状态（未启用）
#define AS_STATE_SUB_ANNOTATION			0x0200	//标注状态
//sharing Type
#define AS_SHARINGTYPE_DESKTOP			0x0000	//share desktop
#define AS_SHARINGTYPE_APP				0x0001	//share applications
//sharing session
#define AS_SESSION_CONNECT				0x0000	//session连接消息
#define AS_SESSION_OWNER				0x0001	//共享端转移消息
#define AS_SESSION_FLOWCONTROL			0x0002	//流控告警消息
//sharing channel type
#define AS_CHANNEL_TYPE_NULL			0x0000	//for NULL
#define AS_CHANNEL_TYPE_NORMAL			0x0001	//for PC
#define AS_CHANNEL_TYPE_LOW_QUALITY		0x0002	//for mobile device
#define AS_CHANNEL_TYPE_TP				0x0003	//for TV
//sharing session state
#define AS_SESSION_DISCONNECT			0x0000	//连接断开
#define AS_SESSION_CONNECTED			0x0001	//连接连通
#define AS_SESSION_CONNECTING			0x0002	//连接中
//sharing privilege
#define AS_PRIVILEGETYPE_CONTROL		0x0001	//远程控制权限
#define AS_PRIVILEGETYPE_ANNOTATION		0x0002	//标注权限
//sharing action
#define AS_ACTION_DELETE				0x0000
#define AS_ACTION_ADD					0x0001
#define AS_ACTION_MODIFY				0x0002
#define AS_ACTION_REQUEST				0x0003
#define AS_ACTION_REJECT				0x0004
#define AS_ACTION_DELETE_SPEC			0x0006
#define AS_ACTION_ADD_SPEC				0x0007
//sharing prop
#define AS_PROP_TIMEINTERVAL			0x0001	//帧时间间隔，单位：ms，格式：dword
#define AS_PROP_MAXBITRATE				0x0002	//最大平均带宽，单位：Byte，格式：dword
#define AS_PROP_PICTUREQUALITY			0x0003	//图像质量，单位：百分比，格式：dword
#define AS_PROP_VIEW_SIZE				0x0006	//显示区域尺寸，单位：pixel，格式：size
#define AS_PROP_VIEW_ORIGIN_POINT		0x0007	//显示区域便宜（未启用），单位：pixel，格式：point
#define AS_PROP_DEFAULT_CAP_TYPE		0x0009	//采取方式，单位：无，格式：dword
#define AS_PROP_VIEW_FACTOR				0x000a	//观看端缩放比例，单位：无，格式：double
#define AS_PROP_REMOTESCREEN_SIZE		0x000c	//共享端尺寸，单位：pixel，格式：size
#define AS_PROP_BORDER_SEARCH			0x000e	//黑边剔除开关，单位：无，格式：dword
#define AS_PROP_DUMP_DATA				0x000f	//共享数据dump（未启用），单位：无，格式：dword
#define AS_PROP_DATA_CHANNEL			0x0010	//共享数据通道，单位：无，格式：dword
#define AS_PROP_DEFAULT_BORDER_WIDTH	0x0011	//默认边界宽度，单位：pixel，格式：dword，最大宽度<300
#define AS_PROP_FIRST_KEY_FRAME_DELAY	0x0012	//首帧延迟时间，单位：ms，格式：dword
#define AS_PROP_REMOTE_PPI				0x0013	//共享端PPI，单位：无，格式：dword
#define AS_PROP_SAMPLING				0x0014	//共享下采样缩小倍率，单位：无，格式：dword
#define AS_PROP_SHARING_RECT			0x0015	//共享区域，单位：pixel，格式：rect
#define AS_PROP_SCALE_QUALITY			0x0016	//放大质量，单位：无，格式：dword
#define AS_PROP_CONTROL_TIMEINTERVAL	0x0017	//远程控制时帧间隔，单位：ms，格式：dword	
#define AS_PROP_COLOR_SPACE				0x0018	//共享端颜色格式，单位：无，格式：dword
#define AS_PROP_P2P_COUNT				0x0019	//P2P共享阈值，单位：个，格式：dword

//capture type
#define AS_CAPTURE_GDI					0x0000	//capture with windows GDI
#define AS_CAPTURE_MD					0x0001	//capture with windows Mirror Driver
#define AS_CAPTURE_GDIEX				0x0002	//capture with windows GDIEX
#define AS_CAPTURE_MAG					0x0003	//capture with windows Magnification
#define AS_CAPTURE_MAC					0x0004	//capture for MAC
#define AS_CAPTURE_ANDROID				0x0005	//capture for Android 
#define AS_CAPTURE_VIEW					0x0006	//capture form App view 
//sharing screen data update format
#define AS_SCREENDATAFORMAT_DDB			0x0000	//windows DDB
#define AS_SCREENDATAFORMAT_DIB			0x0001	//Bitmap
#define AS_SCREENDATAFORMAT_DC			0x0002	//windows HDC
//the max length of user define message
#define AS_USERDEFINE_MSG_MAX_LEN		1024
//lock data
#define AS_LOCK_SCREENDATA_LOCK			0x0000	//锁定数据				
#define AS_LOCK_SCREENDATA_UNLOCK		0x0001	//解锁数据
//border delete
#define AS_BORDER_SEARCH_OFF			0x0000	//关闭黑边剔除				
#define AS_BORDER_SEARCH_ON				0x0001	//开启黑边剔除
//switch
#define AS_SWITCH_OFF					0x0000	//关闭配置项				
#define AS_SWITCH_ON					0x0001	//开启配置项
//data channel
#define AS_DATA_CHANNEL_NORMAL			0x0000	//AS共享数据独立通道	
#define AS_DATA_CHANNEL_SESSION			0x0001	//AS共享数据共用控制命令通道
//screen data information mask
#define SH_SCREEN_DATA_INFO_MASK_BORDER	0x0001
#define SH_SCREEN_DATA_INFO_MASK_UPDATE	0x0002

typedef struct tagASParam{
	TUP_UINT32	ulPorpType;			//参数类型
	TUP_UINT32	ulDataLen;			//参数数据长度
	TUP_VOID*	pData;				//参数数据
}TC_AS_PARAM;

typedef struct tagASWndInfo{
	TUP_VOID*		hWnd;			//应用程序窗口句柄
	TUP_UINT16		*pWndTitle;		//窗口名称
	TUP_VOID*		hSmallIcon;		//ICON图标Handle
	TUP_BOOL		bChecked;		//是否被选中
}TC_AS_WndInfo;

typedef struct tagASSScreenData{
	TUP_UINT8			ucDataType;		//屏幕数据格式
	TUP_VOID*			pUpdateInfo;	//留待扩展使用
	TUP_VOID*			pData;			//屏幕数据
}TC_AS_SCREENDATA;

typedef struct tagASSScreenDataInfo{
	TUP_UINT8			dwDataType;		//有效字段标志位
	TUP_INT				rcBorder[4];	//黑边位置
	TUP_INT				rcUpdate[4];	//更新区域，待扩展
}TC_AS_ScreenDataInfo;

typedef struct tagASMouseEvent{
	TUP_UINT32	ulEventFlag;	//消息事件type
	TUP_UINT32	ulParam;		//消息事件wParam
	TUP_LONG	lParam;			//消息事件lParam
}TC_AS_MouseEvent;

////////////////////////////////// 文档共享模块定义部分 ////////////////////////////
#define	dsNullID	((TUP_UINT32)(0))
#define dsNullOffset ((TUP_UINT32)(-1))

typedef struct tagAnno_Resource_Item
{
	TUP_UINT16 resIndex;			//自定义标注资源索引
	TUP_UINT16 reserved;			//保留字
	TUP_VOID* pData;			//自定义标注数据
	TUP_UINT32 dataLen;			//自定义标注数据长度
	TUP_INT format;				//自定义标注格式
	TUP_UINT16 picWidth;			//图片宽度
	TUP_UINT16 picHeight;			//图片高度
	TC_POINT ptOffset;
} Anno_Resource_Item;


#define DS_OPTION_QUALITY	1		//质量优先
#define DS_OPTION_SIZE		2		//带宽优先
#define DS_OPTION_DOUBLE	3		//双流方式 EMF+JPG


//定义页面标注的类型
#define DS_ANNOT_TYPE_LASERPOINTER	11 // Like laser pointer which moves as mouse moves
#define	DS_ANNOT_TYPE_DRAWING   	12 // Hilight belongs to drawing
#define	DS_ANNOT_TYPE_CUSTOMER		13 	
#define	DS_ANNOT_TYPE_TEXT			14


//定义页面标注的子类型
#define	DS_ANNOTDRAWING_TYPE_FREEHAND				1
#define	DS_ANNOTDRAWING_TYPE_HILIGHT				2
#define	DS_ANNOTDRAWING_TYPE_RECTANGLE				3	
#define	DS_ANNOTDRAWING_TYPE_FILLRECTANGLE			4
#define	DS_ANNOTDRAWING_TYPE_ROUNDRECTANGLE			5
#define	DS_ANNOTDRAWING_TYPE_FILLROUNDRECTANGLE		6
#define	DS_ANNOTDRAWING_TYPE_ELLIPSE				7
#define	DS_ANNOTDRAWING_TYPE_FILLELLIPSE			8
#define	DS_ANNOTDRAWING_TYPE_LINE					9
#define	DS_ANNOTDRAWING_TYPE_LINEARROW				10
#define	DS_ANNOTDRAWING_TYPE_LINEDOUBLEARROW		11
#define	DS_ANNOTDRAWING_TYPE_WBPEN					12
#define	DS_ANNOTDRAWING_TYPE_WBERASE				13
#define DS_ANNOTDRAWING_TYPE_PAGEFRAME				14


typedef enum
{
	DS_HITTEST_CODE_ERROR = 0, 
	DS_HITTEST_CODE_INSIDE,
	DS_HITTEST_CODE_RESIZE_UPPERLEFT,
	DS_HITTEST_CODE_RESIZE_UPPERMIDDLE,
	DS_HITTEST_CODE_RESIZE_UPPERRIGHT,
	DS_HITTEST_CODE_RESIZE_MIDDLERIGHT,
	DS_HITTEST_CODE_RESIZE_BOTTOMRIGHT,
	DS_HITTEST_CODE_RESIZE_BOTTOMMIDDLE,
	DS_HITTEST_CODE_RESIZE_BOTTOMLEFT,
	DS_HITTEST_CODE_RESIZE_MIDDLELEFT
} DS_HITTEST_CODE;


//zoom type
#define DS_ZOOM_PAGESIZE	1	//实际大小，不缩放
#define DS_ZOOM_DISPSIZE	2	//显示区域大小
#define DS_ZOOM_FITWIDTH	3	//适应显示宽度
#define DS_ZOOM_PERCENT		4	//以实际百分比缩放

typedef enum
{
	DsRotateFlipBase	 = 0,

	DsRotateNoneFlipNone = 0,	//未旋转，未翻转
	DsRotate90FlipNone  = 1,	//旋转90度，未翻转
	DsRotate180FlipNone = 2,	//旋转180度，未翻转
	DsRotate270FlipNone = 3,	//旋转270度，未翻转

	DsRotateNoneFlipX   = 4,
	DsRotate90FlipX     = 5,
	DsRotate180FlipX    = 6,
	DsRotate270FlipX    = 7,

	DsRotateNoneFlipY   = DsRotate180FlipX,
	DsRotate90FlipY     = DsRotate270FlipX,
	DsRotate180FlipY    = DsRotateNoneFlipX,
	DsRotate270FlipY    = DsRotate90FlipX,

	DsRotateNoneFlipXY  = DsRotate180FlipNone,
	DsRotate90FlipXY    = DsRotate270FlipNone,
	DsRotate180FlipXY   = DsRotateNoneFlipNone,
	DsRotate270FlipXY   = DsRotate90FlipNone,

	DsRotateFlipMax		= 8
}DsRotateFlipType;

typedef struct {
	TUP_UINT16 zoomType;
	TUP_UINT16 zoomPercent;
	TUP_UCHAR bWb;	//是否白板，0：文档，1：白板
	TUP_UCHAR reserved;
	TUP_UINT32 currentPage;	//该文档的当前页
}DsDocInfo;

//页面信息定义
typedef struct {
	TUP_INT width;				//页面宽
	TUP_INT height;				//页面高
	TUP_INT orgX;				//显示起点X
	TUP_INT orgY;				//显示起点Y
	DsRotateFlipType rfType;	//该页面的旋转类型
	TUP_UINT16 zoomPercent;		//当前文档缩放类型下，该页面显示时的缩放比例
	TUP_UCHAR bCopied;	//是否是复制的页面：0否，1是
	TUP_UCHAR bEPenDrawn;	//是否被电子笔画过：0否，1是
	float floatZoomPercent;	//精确的文档缩放比例
	TUP_INT pageNo;				//页码
}DsPageInfo;

//文档同步信息定义
typedef struct {
	TUP_UINT32 docId;				//服务器上的当前文档ID
	TUP_UINT32 pageId;				//服务器上的当前页ID
	TUP_INT width;					//当前页的宽
	TUP_INT height;					//当前页的高
	TUP_INT orgX;					//服务器上的该页起点X
	TUP_INT orgY;					//服务器上的该页起点Y
	DsRotateFlipType rfType;	//服务器上的该页旋转类型
	float zoomPercent;			//该页的缩放比例
	TUP_UCHAR bCopied;		//该页是否复制的页
	TUP_UCHAR bEPenDrawn;	//该页是否被电子白板画过
}DsSyncInfo;

//annotation hittest mode
#define DS_HITTEST_MODE_ALL				0		//区域内的全部annot,
#define DS_HITTEST_MODE_OTHERS			1		//除某人外的全部annot
#define DS_HITTEST_MODE_SOMEONE			2		//某人的annot
//下面的三种模式对应上面的三种模式，不同之处在于下面的会将所有区域内的标注全部返回，包括没有指定DS_ANNOT_FLAG_CANBESELECTED属性的标注
//只在hittest2接口中起作用，不要在hittest接口中使用
#define DS_HITTEST_MODE_ALL_FORCE		3		//区域内的全部annot
#define DS_HITTEST_MODE_OTHERS_FORCE 	4		//除某人外的全部annot
#define DS_HITTEST_MODE_SOMEONE_FORCE	5		//某人的annot


//annotation select mode
#define DS_SELECT_MODE_UNSELECT		0		//取消选择
#define DS_SELECT_MODE_ALL			1		//全选
#define DS_SELECT_MODE_OTHERS		2		//选择除某人之外的
#define DS_SELECT_MODE_SOMEONE		3		//选择某个用户的

typedef struct {
	TC_POINT pt;
} CreateDrawingData;


#define DS_PIC_FORMAT_JPG	1000
#define DS_PIC_FORMAT_PNG	1001
#define DS_PIC_FORMAT_BMP	1002

typedef struct tagCreateCustomerData
{
    TUP_UINT16 bLocal;            //是否本地化图片（即由客户端固化打包，不需要经过网络传输）,0表示普通图片，1表示本地化图片
    TUP_UINT16 localIndex;        //当bLocal为1时有效，表示对应的本地化图片的索引，该索引用于底层向上层取数据
    TUP_INT picFormat;          //当bLocal为0时有效，表示图片格式
    TUP_VOID* pData;            //当bLocal为0时有效，存放普通图片的数据，bLocal为1时，可以为NULL
    TUP_UINT32 dataLen;         //当bLocal为0时有效，存放图片数据的长度
    TUP_INT picW;               //当bLocal为0时有效，图片宽
    TUP_INT picH;               //当bLocal为0时有效，图片高
    TC_RECT2 dispRect;      //图片显示区域
    TC_POINT ptOffset;      //相对于图片左上角的偏移，TWIP为单位，用于缩放时用于计算图片位置的参照点
} CreateCustomerData;


typedef struct tagAnnotationConfig
{
    TUP_INT bSelfLpNotDisp;     //是否渲染自己的激光点，为0时表示渲染，为1时底层不渲染，上层需要自己显示激光点
} AnnotationConfig;

typedef struct tagDsDrawDataNotify
{
    TUP_VOID* pData;			//数据
    TUP_INT nWidth;				//宽度
    TUP_INT nHeight;			//高度
    TC_RECT2* drawRect;			//
} DsDrawDataNotify;


//标注属性
#define  DS_ANNOT_FLAG_EXCLUSIVE			0x01 // 排他的，唯一的
#define  DS_ANNOT_FLAG_EXCLUSIVEPERUSER		0x02 // 每个用户唯一的
#define	 DS_ANNOT_FLAG_OUTLINEFEEDBACK		0x04 // 创建过程中显示标注虚线框，没有此标志则显示实际标注
#define  DS_ANNOT_FLAG_FIXEDSIZE			0x08 // 固定大小的，不随缩放改变大小
#define	 DS_ANNOT_FLAG_CANBESELECTED		0x10 // 可以被选中
#define  DS_ANNOT_FLAG_CANBEMOVED			0x20 // 可以被移动
#define  DS_ANNOT_FLAG_PAGEFRAME			0x40 // 白板边缘的边框（特殊，外部不要用）

//用户自定义标注类型，自定义的类型都是AnnotCustomer的子类型
typedef struct tagDsDefineAnnot
{
	TUP_UINT16 extendType;
	TUP_UINT16 flag;
}DsDefineAnnot;

/* Brush Styles */
#define	DS_BRUSH_STYLE_NULL			0		//空画刷
#define	DS_BRUSH_STYLE_SOLID		1		//实体画刷
#define	DS_BRUSH_STYLE_GRADIENT		2		//渐变画刷
#define	DS_BRUSH_STYLE_HATCH		3		//阴影画刷
#define	DS_BRUSH_STYLE_PATTERN		4		//图形画刷


/* Pen Styles */
#define DS_PEN_STYLE_SOLID            0	
#define DS_PEN_STYLE_DASH             1       /* -------  */
#define DS_PEN_STYLE_DOT              2       /* .......  */
#define DS_PEN_STYLE_DASHDOT          3       /* _._._._  */
#define DS_PEN_STYLE_DASHDOTDOT       4       /* _.._.._  */
#define DS_PEN_STYLE_NULL             5
#define DS_PEN_STYLE_INSIDEFRAME      6
#define DS_PEN_STYLE_USERSTYLE        7
#define DS_PEN_STYLE_ALTERNATE        8

typedef struct {
	TC_RECT2*   bounds;		//外接矩形
	TUP_UINT8*      pString;	//utf8字符串
	TUP_UINT8*      pFont;		//字体名
	COLORRGBA   color;		//文字颜色
	TUP_UINT16        size;		//字体大小
	TUP_UINT16        reserve;	//字节对齐，保留
}DsAnnotTextInfo;

typedef struct {
	TC_RECT2		bounds;		//外接矩形
	TUP_UINT16		type;		//标注类型
	TUP_UINT16		subtype;	//标注子类型
	TUP_UINT32		creator;	//创建者user id
	TUP_UINT16		flag;		//属性
}DsAnnotInfo;

typedef struct {
	TUP_INT			style;		//线的样式
	COLORRGBA		color;		//画笔颜色
	TUP_INT			width;		//画笔宽度
}DsPenInfo;

typedef struct {
	TUP_INT			style;		//刷子样式
	COLORRGBA		color;		//刷子颜色
}DsBrushInfo;

#define DS_PEN_TYPE_NORMAL		1	//普通画笔
#define DS_PEN_TYPE_HILIGHT		2	//高亮画笔

typedef enum {
	SUR_OUTPUT_HDC,			//windows only
	SUR_OUTPUT_HBITMAP		//windows only
}SurfaceOutputFormat;

//显示模式
typedef enum {
	DS_DISP_MODE_FREE,		//default mode
	DS_DISP_MODE_CENTER,	//居中显示，此时不响应setdisporg

	DS_DISP_MODE_COUNT		//无含义，只是表示显示模式个数
}DsDispMode;

//定义文档属性ID,10000以内的ID预留给底层使用,
//10000以上的作为用户自定义属性,底层提供保存和传输的能力,具体数据如何处理由应用层决定
typedef enum {
	DOCPROP_SYSTEM_BASE     = 0,
    DOC_PROPERTY_FULLNAME   = 1,	// 文档全路径名称
    DOC_PROPERTY_ORDER      = 2,	// 文档序号
    DOC_PROPERTY_COMPLETE   = 3,	// 文档是否完成加载
	DOC_PROPERTY_TYPE		= 4,	// 属性值为1时为JPEG，否则为EMF
	DOC_PROPERTY_DATA_READY = 5,	// 文档是否数据已准备好

	DOCPROP_USER_BASE       = 10000
}DocProperty;

//定义页面属性ID,10000以内的ID预留给底层使用,
//10000以上的作为用户自定义属性,底层提供保存和传输的能力,具体数据如何处理由应用层决定
enum {
	PAGEPROP_SYSTEM_BASE    = 0,
	PAGEPROP_TITLE,

	PAGEPROP_USER_BASE      = 10000,
};


#endif