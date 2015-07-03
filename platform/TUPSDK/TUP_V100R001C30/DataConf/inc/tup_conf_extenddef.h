#ifndef _TUP_CONF_EXTENDDEF_H_
#define _TUP_CONF_EXTENDDEF_H_

#include "tup_conf_basedef.h"


typedef enum  //电话服务状态
{
	PHONE_MCPCS_IDLE = 0,			// conference not start
	PHONE_MCPCS_OPEN_READY,			// conference is ready, mgw not connected.
	PHONE_MCPCS_OPEN_RESET,			// conference is open. phnagt is leave!
	PHONE_MCPCS_OPEN_PENDING,		// conference is starting
	PHONE_MCPCS_OPEN_FAILED,	    // conference start failed
	PHONE_MCPCS_OPEN,				// conference started successfully. ready to use
	PHONE_MCPCS_CLOSED,				// conference is alrady closed
    PHONE_MCPCS_NO_CONF_RESOURCE,	// not phone conference resource
} PHONE_MCP_CONF_STATUS;

typedef enum  //QOS类型
{ 
	QOS_TYPE_AUDIO = 1,		//音频数据	
	QOS_TYPE_VIDEO,			//视频数据
	QOS_TYPE_DATA,			//其他数据
}QOS_TYPE;

typedef enum{  //流控类型，可指定各种类型的最高带宽
	LIMIT_DATA_CHAT = 2,
	LIMIT_DATA_AUDIO ,
	LIMIT_DATA_SCREEN ,		//屏幕共享数据
	LIMIT_DATA_CACHE ,		//
	LIMIT_DATA_VIDEO ,		//视频数据
	LIMIT_DATA_DOC,		
}LIMIT_DATA_TYPE;

typedef enum	//Ping状态
{
	PING_RET_STATUS = 1,	//Ping状态通知
	PING_RET_COMPLETE,		//Ping完成通知
	PING_RET_TIMEOUT,		//Ping超时通知
}PING_RET;

typedef enum{
	PING_STATUS_SUCCESS			=0,
	PING_STATUS_CANCELED		=1,
	PING_STATUS_TIMEOUT			=2,
	PING_STATUS_CONNECT_FAILURE	=3,
	PING_STATUS_LICENSE_OUT		=4,
	PING_STATUS_THRUPUT_OUT		=5,
	PING_STATUS_UNAVAILABLE		=6
}PING_STATUS;

//////////////////////////////////////////////////////////////////////////
// 会议数据类型定义

/*用户发送数据信息*/
typedef struct tag_user_data {
    TUP_UINT16			data_length;
    TUP_UINT8*			data;
} TC_IMCC_User_Data;

typedef struct tag_tc_table_record
{
    TUP_UINT16              record_id;
    TUP_UINT32			    record_tag;
    TUP_UINT8			    record_fields_count;
    TC_IMCC_User_Data *		record_fields;
} TC_IMCC_Table_Record;

typedef struct tag_tc_table_insert
{
    TUP_CHAR TName[TC_MAX_TABLE_NAME_LEN];
    TC_IMCC_Table_Record Record;
} TC_IMCC_Table_Insert;


/*全局参数信息*/
typedef struct tag_conf_param_update
{
    TUP_CHAR msg_name[TC_MAX_USER_NAME_LEN];		//参数名称
    TUP_VOID * msg;									//全局数据内容
    TUP_UINT16 msg_len;								//全局数据内容长度
} TC_CONF_Param_Update;

typedef struct tag_conf_ping_complete
{
    TUP_CHAR src_addr[TC_MAX_CONF_SERVER_IP];
    TUP_CHAR dst_addr[TC_MAX_CONF_SERVER_IP];
} TC_CONF_Ping_Complete;


/*公告信息*/
typedef struct tag_notice_item 
{
    TUP_UINT16 item_num;			//公告编号
    TUP_UINT32 item_tag;
    TUP_UINT16 nLen;				//公告数据长度
    TUP_UINT8 * pchInfo;			//公告数据内容
} TC_CONF_Notice_Item;



// 电话用户信息
typedef struct tag_conf_phone_record
{
    TUP_UINT16	m_record_id;			// 电话记录ID
    TUP_CHAR	m_uri[TC_MAX_URI_LEN];	// 电话URL
    TUP_UINT32	m_phone_user_id;		//电话
    TUP_UINT8	m_phone_user_type;
    TUP_UINT8	m_phone_status;			//电话状态
    TUP_CHAR	m_phone_user_name[TC_MAX_PHONE_USER_NAME_LEN];
    TUP_UINT8	m_audio_mute_status;
    TUP_UINT8	m_video_dev_capable;
    TUP_UINT8	m_video_open_status;
    TUP_UINT32	m_pin_num;
    TUP_UINT32	m_binding_nid;
    TUP_UINT32  m_nDeviceID;
} TC_Conf_Phone_Record;

// 用于on_conf_user_message_ind消息
typedef struct tag_user_message_ind
{
    TUP_UINT32 from_user_id;
    TUP_UINT16 msg_type;
    TUP_UINT16 msg_data_length;
    TUP_UINT8* msg_data;
} USER_Message_Ind;


typedef enum
{
	NET_REPORT_DISCONNECT         = 0,		//网络极差
	NET_REPORT_BAD                = 1,		//网络较差
	NET_REPORT_NOMAL              = 2,		//网络普通
	NET_REPORT_GOOD               = 3,		//网络良好
	NET_REPORT_EXCELLENCE         = 4,		//网络极好
}NET_REPORT;

//IP映射表格
typedef struct tagIpNatMap
{
	TUP_CHAR inter_ip[TC_MAX_CONF_SERVER_IP];	//内部IP地址和端口
	TUP_CHAR outer_ip[TC_MAX_CONF_SERVER_IP];	//对外映射的IP地址和端口
}IP_NAT_MAP;


/**************************************************************************
/* conference net options
**************************************************************************/
#define NET_OPT_MAC_CONN_NUM				0x0001	//buf: TUP_UINT32*
#define NET_OPT_NID						    0x0002	//buf: TUP_UINT32*
#define NET_OPT_NTYPE						0x0003	//buf: TUP_UINT16*
#define NET_OPT_EXP_TIME					0x0004	//buf: TUP_UINT32*
#define NET_DOMAIN_OPT_ENABLE_UDP			0x0101	//buf: boolean*
#define NET_DOMAIN_OPT_INDEX				0x0102	//buf: TUP_UINT16*
#define NET_DOMAIN_OPT_ENABLE_UDP_AUTOCTRL	0x0103	//buf: boolean*
#define NET_DOMAIN_OPT_ENABLE_MULTICAST	    0x0104	//buf: boolean*
#define NET_DOMAIN_OPT_SET_ENCRYPTION_KEY	0x0105	//buf: TUP_UINT8*
#define NET_DOMAIN_OPT_ENABLE_AUTO_RECONN	0x0106	//buf: boolean*
/*************************************************************************/

#if !defined(boolean)
	typedef TUP_UINT8 boolean;
#endif
// 网络配置项
typedef  struct tag_conf_net_opt 
{
    boolean net_opt_mac_conn_num;
    boolean net_opt_nid;
    boolean net_opt_ntype;
    boolean net_opt_exp_time;
    boolean net_domain_opt_enable_udp;
    boolean net_domain_opt_index;
    boolean net_domain_opt_enable_udp_autoctrl;
    boolean net_domain_opt_enable_multicast;
    boolean net_domain_opt_set_encryption_key;
    boolean net_domain_opt_enable_auto_reconn;
}st_conf_net_opt ;


/*会议初始配置信息*/
typedef struct tag_conf_config
{
    TUP_UINT32 init_users_privilege;  //会议用户初始权限
    TUP_UINT32 init_conf_layoutmodel; //会议初始布局模式
    TUP_UINT32 init_conf_model;       //会议初始模式：主持人控制模式、自由模式
    TUP_UINT32  doc_background_color;  //文档共享需要绘制的背景颜色

    // 网络配置选项
    st_conf_net_opt conf_net_opt;
	
#ifdef __cplusplus
    tag_conf_config()
    {
        init_users_privilege  = 0;
        init_conf_layoutmodel = 0;
        init_conf_model       = 0;
        doc_background_color  = 0;

        memset(&conf_net_opt, 0, sizeof(struct tag_conf_net_opt));
    }
#endif
} TC_CONF_INIT_CONFIG;


////////////////////////////////////////////////////////
typedef struct tagMonitroInfo
{
	TUP_UINT16 xResolution;
	TUP_UINT16 yResolution;
	TUP_UINT16 bitcount;
	TUP_UINT16 index;
}MonitorInfo;

#endif