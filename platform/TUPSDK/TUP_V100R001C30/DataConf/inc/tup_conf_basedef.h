#ifndef _TUP_CONF_BASEDEF_H_
#define _TUP_CONF_BASEDEF_H_

#include "tup_def.h"

//using std lib(c++)
#include <string>


#define TC_SDK_VERSION			113
#define TC_SDK_VERSION_STRING		"TUP Conf V001R001C300B023"
#define IMCC_USERDEVICE_H323_MCU      0x00100000  //��������������屣��һ��

typedef TUP_UINT32	CONF_HANDLE;

typedef enum	//���ID����
{
	IID_COMPONENT_BASE      = 0x0000,	//�������
	IID_COMPONENT_DS		= 0x0001,	//�ĵ�����
	IID_COMPONENT_AS		= 0x0002,	//��Ļ����
	IID_COMPONENT_AUDIO		= 0x0004,	//��Ƶ
	IID_COMPONENT_VIDEO		= 0x0008,	//��Ƶ
	IID_COMPONENT_RECORD	= 0x0010,	//¼��
	IID_COMPONENT_CHAT		= 0x0020,	//����
	IID_COMPONENT_POLLING	= 0x0040,	//ͶƱ
	IID_COMPONENT_MS		= 0x0080,	//ý�干��
	IID_COMPONENT_FT		= 0x0100,	//�ļ�����
    IID_COMPONENT_WB		= 0x0200,	// �װ�
} COMPONENT_IID;

typedef enum 
{
	JOIN_CONF_TYPE_NONE,
	JOIN_CONF_TYPE_PRIORITY_MS,
	JOIN_CONF_TYPE_PING
} JOIN_CONF_TYPE;//ֻ�����ڻ�ΪUC priority_ms��ʽ���

enum //�û����Ͷ���
{
    CONF_ROLE_HOST          = 0x0001, //������
    CONF_ROLE_PRESENTER     = 0x0002, //������
    CONF_ROLE_GENERAL       = 0x0008, //��ͨ������
};

enum //��־����
{
	LOG_LEVEL_ERROR = 0,		//���󼶱�
	LOG_LEVEL_WARNING,			//���漶��
	LOG_LEVEL_INFO,				//һ�㼶��
	LOG_LEVEL_DEBUG				//���Լ���	
};

typedef enum //�������ѡ��
{
	CONF_OPTION_BASE           = 0x0000,		//ֻ�ṩ�����������
	CONF_OPTION_USERLIST       = 0x0001,		//֧���û������ڲ�ά��
    CONF_OPTION_LOAD_BALANCING = 0x0002,		//���ŷ�������¼
    CONF_OPTION_PHONE          = 0x0004,		//֧�ֵ绰
	CONF_OPTION_NET_LIMIT	   = 0x0008,		//��������ģʽ����ģʽ�£�������Ļ����ʱ�����Զ�������Ƶ��������һ��ʱ���ָ�
	CONF_OPTION_VIDEO_DOUBLE_STREAM = 0x0010,	//��Ƶ֧��˫��
	CONF_OPTION_VIDEO_UDP		= 0x0020,		//��Ƶ����UDP
	CONF_OPTION_QOS				= 0x0040,		//����Qos
	CONF_OPTION_FLOW_CONTROL	= 0x0100,		//���أ�ƽ������
	CONF_OPTION_SUPER_CONF		= 0x0200,		//�������
    CONF_OPTION_HOST_NO_GRAB    = 0x0400,       //��������ռ������
    CONF_OPTION_PRESENTER_GRAB  = 0x0800,		//������ռ������

	CONF_OPTION_HWUC			= 0x1000,		//�����ϰ汾��ΪUC����ʱѡ�������ѡ�ֻ��ʹ�û����Ļ�ع��ܺ���Ļ�����ܣ���ΪUC������Ϻ��ѡ����Է���
	CONF_OPTION_UC_AUDIO        = 0x2000,       //UC�ͻ��ˣ�Ҫ�������ǣ���Ƶģ���UC�����⴦��
	CONF_OPTION_AUDIO_TCP		= 0x4000,		//��Ƶ����TCP
	CONF_OPTION_CLOUD_SYSTERM	= 0x8000,		//��¼ϵͳΪ��ϵͳ�����������־����Ƶģ�鲻ö�����ϵı�����Ƶ

	CONF_OPTION_DLL_NOT_FREE	= 0x00010000,	//����̬�ͷŶ�̬��

	CONF_OPTION_VIDEO_RUNCAPTURE= 0x00100000,	//��Ƶһֱ��Capture��ģʽ
	CONF_OPTION_USE_PRIORITY_SVR= 0x00200000,	//����ʹ��ConfInfo�ڵķ�����IP
	CONF_OPTION_CLOUD_MODE		= 0x10000000,	//��ģʽ�����ݷ��룬UserID���λΪ1ʱ��ʾ���ݿͻ���
}CONF_OPTION;

typedef enum	//����ϵͳ����
{
    CONF_OS_UNKNOWN = 0,
    CONF_OS_WIN     = 1,
    CONF_OS_LINUX   = 2,
    CONF_OS_MACOS   = 3,
	CONF_OS_IOS		= 4,
	CONF_OS_ANDROID	= 5,

    CONF_MAX_OS_CODE			//�޺��壬ֻ�Ǳ�ʾö������
} CONF_OS_TYPE;

typedef enum	//�ն�Ӳ������
{
    CONF_DEV_UNKNOWN	= 0,
    CONF_DEV_PC			= 1,	//PC
    CONF_DEV_PDA		= 2,	//�������������Ѳ�֧��
    CONF_DEV_PHONE		= 3,	//�ֻ�
	CONF_DEV_PAD		= 4,	//ƽ�����
    CONF_DEV_GATEWAY    = 5,    //MGW�û����ڲ��������ⲿ���ɼ�
	CONF_DEV_IPPHONE	= 6,	//�����鹦�ܵ�IP�绰
	CONF_DEV_TC			= 7,	//�ݿͻ���

    CONF_MAX_DEV_CODE			//�޺��壬ֻ�Ǳ�ʾö������
} CONF_DEVICE_TYPE;

/*** ����ֵ���� ***/
enum{
	TC_OK                                   = 0,
	TC_WARNING                              = 1,
	TC_ERROR                                = 2,		//
	TC_FAILURE                              = 3,		//һ�����
	TC_NULL_POINT							= 4,		//��ָ��
	TC_CALL_TIMEOUT							= 5,		//���ó�ʱ
	TC_PARAM_ERROR							= 6,		//��������
	TC_BUFFER_TOO_SHORT						= 7,		//�ڴ�̫С
	TC_XML_PARAM_ERROR						= 8,		//xml��������
	TC_NO_PRIVILEGE							= 9,		//û��Ȩ��
	TC_FUNC_NOT_SUPPORT						= 10,		//���õĽӿڲ�֧�ֻ�δʵ��
	TC_MODULE_NOT_LOAD						= 11,		//ģ��û�м���

    // �����IMCC�㷵�صĴ����룬��Ҫ�����û���
	TC_IMCC_RESULT_BASE                     = 100,
	TC_IMCC_RESULT_USER_REJECTED			= 101,		//�ܾ��û�����
	TC_IMCC_RESULT_NETWORK_ERROR			= 102,		//�������
	TC_IMCC_RESULT_VERSION_NOT_MATCH		= 103,		//�汾��֧��
	TC_IMCC_RESULT_PROTOCOL_NOT_RIGHT		= 104,		//ͨ��Э�����
	TC_IMCC_RESULT_TOO_MANY_CONNECTIONS		= 105,		//�������������������
	TC_IMCC_RESULT_EXPIRED					= 106,		//license����
	TC_IMCC_RESULT_DOMAIN_TERMINATED		= 107,		//�����ѽ���
	TC_IMCC_RESULT_SERVER_CONN_FAILED		= 108,		//
	TC_IMCC_RESULT_SYS_SHUTINGDOWN			= 109,		//���ӶϿ�
	TC_IMCC_RESULT_DOMAIN_MERGING			= 110,		//
	TC_IMCC_RESULT_NO_SUCH_USER				= 111,		//��Ȩʱ���ָ��û�������
	TC_IMCC_RESULT_CHANNEL_NOT_AVAILABLE	= 112,		//������channel�ﵽ��ֵ
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
	TC_IMCC_RESULT_AUTH_FAILED				= 126,		//��Ȩʧ��
	TC_IMCC_RESULT_UNKNOWN					= 127,		//δ֪����
	TC_IMCC_RESULT_AUTH_REDIRECT			= 128,
	TC_IMCC_RESULT_QUERY_PARENT_OR_TOP_AGENT_EXPIRED = 129, 
	TC_IMCC_RESULT_DOMAIN_LOCKED           = 130,
	TC_IMCC_RESULT_AUTH_TIMEOUT            = 131,           
	TC_IMCC_RESULT_AUTH_KEY_NOT_AVAILABLE  = 132,
	TC_IMCC_RESULT_TOO_MANY_CONFERENCE     = 133,           
	TC_IMCC_RESULT_TOO_MANY_CONFERENCE_USER = 134,
	TC_IMCC_RESULT_NOT_DATA_USER_LICENSE    = 135,
	TC_IMCC_RESULT_AUTH_LINCENSE_TIMEOUT    = 136,//��ȨLicense��ʱ�����������
	TC_IMCC_RESULT_SVR_NOT_ALLOW            = 137,//�����������������������
	TC_IMCC_RESULT_USER_NOT_ALLOW           = 138,//�û��ظ���ᣬ���������

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

    // ���������Ϣ����
    TC_CONF_ERROR_NO_INIT               = 400,	//δ��ʼ��
    TC_CONF_ERROR_REPEAT_INIT           = 401,	//�ظ���ʼ��
    TC_CONF_ERROR_REPEAT_JOIN           = 402,	//�ظ����
    TC_CONF_ERROR_NO_JOIN               = 403,	
    TC_CONF_ERROR_NO_LOAD_COM           = 404,
    TC_CONF_ERROR_DATA_TOO_LAGE         = 405,
    TC_CONF_ERROR_SEND_TOO_FAST         = 406,
    TC_CONF_ERROR_ALREADY_TERMINATE     = 407,
    TC_CONF_ERROR_ALREADY_LEAVE         = 408,
    TC_CONF_ERROR_COM_LOADED            = 409,
    TC_CONF_ERROR_CON_UNLOADED          = 410,
    TC_CONF_ERROR_DISCONNECT_EXC        = 411,
    TC_CONF_ERROR_CONF_INFO             = 412, //��������
    TC_CONF_ERROR_CONF_NOT_INIT         = 413, //���黷����δ��ʼ�����
    TC_CONF_ERROR_SELF_PRESENTER        = 414, //�Լ��Ѿ���������
    TC_CONF_ERROR_PHONE_INIT            = 415, //�绰δ��ʼ��
    TC_CONF_ERROR_PHONE_JOIN            = 416, //����绰����ʧ��
    TC_CONF_ERROR_NO_MEMORY             = 417, //�����ڴ�ʧ��
    TC_CONF_ERROR_PARAM_INVALID         = 418, //������Ч
	TC_CONF_ERROR_ALREADY_NEW			= 419, //��ͬ�Ļ����Ѿ�����

    // ������������
	TC_CHAT_ERROR_BASE	                = 1000,
	TC_CHAT_ERROR_INVALIDSESSION        = 1001,
	TC_CHAT_ERROR_INVALIDUSERID         = 1002,
	TC_CHAT_ERROR_INVALIDGROUPID        = 1003,
	TC_CHAT_ERROR_TOO_MANY_CHAR         = 1004,
	TC_CHAT_ERROR_TOO_MIN_INTERVAL      = 1005,


    // �ĵ�������������
	TC_DS_ERROR_BASE                    = 1100,
	TC_DS_ERROR_DOC_NOTEXIST			= 1101,	//�ĵ�������
	TC_DS_ERROR_PAGE_NOTEXIST			= 1102,	//ҳ�治����
	TC_DS_ERROR_PARAM_NOTEXIST			= 1103,	//�û�����������
	TC_DS_ERROR_DE_NOTEXIST				= 1104,	//DE������
	TC_DS_ERROR_DOC_ALREADYEXIST		= 1105,	//�ĵ��Ѿ�����,�ظ�����ʱ���д˴���
	TC_DS_ERROR_PAGE_ALREADYEXIST		= 1106,	//ҳ���Ѵ���
	TC_DS_ERROR_NOT_VALID_CWP			= 1107,	//�������ļ�����һ����Ч��CWP�ļ�
	TC_ANNOT_ERROR_CUSTOMERTYPE_NOTEXIST = 1108,
	TC_DS_ERROR_PROP_NOT_EXIT			= 1109,
	TC_DS_ERROR_DOC_ALREADY_OPEN		= 1110,	//�ĵ��Ѿ���
    TC_DS_ERROR_DOC_NO_INIT             = 1111,	//ģ��δ��ʼ��
    TC_DS_ERROR_DOC_NO_SINK             = 1112,	//
    TC_DS_ERROR_DOC_NO_SESSION_JOIN     = 1113,	//
    TC_DS_ERROR_DOC_USER_OFFLINE        = 1114,	//
    TC_DS_ERROR_DOC_PRINTING            = 1115, //�ĵ����ڴ�ӡ��
    TC_DS_ERROR_DOC_PAGE_DOWN           = 1116, //�ĵ�ҳ����������������
	TC_DS_ERROR_DOC_FORMAT_ERROR		= 1117,	//���ĵ�����ʱ���˱���İװ��ļ������ڰװ干��ʱ�����˱�����ĵ������ĵ�
	TC_DS_ERROR_DOC_PAGE_NOT_UPLOAD		= 1118, //ҳ������û���ϴ��������������Ҵ�ʱ�������Ѳ��ڻ�����
	

	TC_DS_LOADER_ERROR_COM				= 1121,			//COM����ʧ��
	TC_DS_LOADER_ERROR_NO_PAGE			= 1122,			//���ĵ�0ҳ
	TC_DS_LOADER_CANCELED				= 1123,			//ȡ����ӡ
	TC_DS_LOADER_NOT_SUPPORT			= 1124,			//�ĵ���ʽ��֧��
	TC_DS_LOADER_OFFICE_NOT_SUPPORT		= 1125,			//Office�汾��֧��
	TC_DS_LOADER_ERROR_TRANSFORM		= 1126,			//ת��ʧ��
	TC_DS_LOADER_FILE_EMPTY				= 1127,			//�ļ�Ϊ��
	TC_DS_LOADER_FORMAT_ERROR			= 1128,			//�ļ���ʽ����
	TC_DS_LOADER_TIMEOUT				= 1129,			//��ӡ��ʱ
	TC_DS_LOADER_PRINTER_UNINSTALL		= 1130,			//��ӡ��δ��װ
	TC_DS_LOADER_PPT_THREAD_ERROR		= 1131,			//PPT����
	TC_DS_LOADER_PPT_LOAD_ERROR			= 1132,			//PPT���ش���
	TC_DS_LOADER_PAGE_OVER_MAX			= 1133,			//�������ҳ��
	TC_DS_LOADER_PRINTER_ERROR			= 1134,			//��ӡ������
	TC_DS_LOADER_SERVICE_ERROR			= 1135,			//��ӡ������ִ���
	TC_DS_LOADER_PPT2003_RUNNING		= 1136,			//PowerPoint2003�����У����ܼ���
	TC_DS_LOADER_NO_PERMISSION			= 1137,			//û��Ȩ�޴�

	TC_ANNOT_ERROR_LASER_EXIST			= 1140,			//������Ѿ�����
	
    // ��Ļ������������ app share
	TC_AS_ERROR_BASE					= 1200,	//AS������ʼ
	TC_AS_ERROR_UNKNOW					= 1201,	//δ֪����
	TC_AS_ERROR_INVALIDPARA				= 1202,	//�����쳣
	TC_AS_ERROR_INVALIDUSER				= 1203,	//��ɫ�쳣
	TC_AS_ERROR_INVALIDSESSION			= 1204,	//ͨ���쳣
	TC_AS_ERROR_NULLCOMHANDLE			= 1205,	//ģ�����쳣
	TC_AS_ERROR_INVALIDSTATE			= 1206,	//����״̬�쳣
	TC_AS_ERROR_INVALIDWND				= 1207,	//���ھ�������쳣
	TC_AS_ERROR_CREATETASKFAIL			= 1208,	//������������쳣
	TC_AS_ERROR_USERDROPPED				= 1209,	//�û��ѵ���
	TC_AS_ERROR_XMLERROR				= 1210,	//XML��д�쳣
	TC_AS_ERROR_MODULELOCKED			= 1211,	//ģ�鱻����
	TC_AS_ERROR_WAITFIRSTFRAME			= 1212,	//�ȴ���֡����
	TC_AS_ERROR_UNSUPPORT				= 1213, //��ǰ�汾��֧��
	TC_AS_ERROR_FORBID_SCALE			= 1214, //��֧�ַŴ�
	TC_AS_ERROR_MEM_ALLOC_FAILED		= 1215, //�ڴ����ʧ��
	TC_AS_ERROR_NULLCTRLHANDLE			= 1216, //����Ļ������
	TC_AS_ERROR_INVALIDCHANNEL			= 1217, //�Ƿ�����ͨ��
	TC_AS_ERROR_GDI_ALLOC_FAILED		= 1218, //GDI��������ʧ��

	TC_AS_ERROR_ANNOT_BASE				= 1250,	//AS��ע������ʼ
	TC_AS_ERROR_ANNOT_DOC_NOTEXIST		= 1251,	//�ĵ�������
	TC_AS_ERROR_ANNOT_PAGE_NOTEXIST		= 1252,	//ҳ�治����
	TC_AS_ERROR_ANNOT_PARAM_NOTEXIST	= 1253,	//���Բ�����
	TC_AS_ERROR_ANNOT_DE_NOTEXIST		= 1254,	//ҳ��Ԫ�ز�����
	TC_AS_ERROR_ANNOT_DOC_ALREADYEXIST	= 1255,	//�ĵ��Ѿ�����
	TC_AS_ERROR_ANNOT_PAGE_ALREADYEXIST	= 1256,	//ҳ���Ѵ���
	TC_AS_ERROR_ANNOT_NOT_VALID_CWP		= 1257,	//�������ļ�����һ����Ч��CWP�ļ�
	TC_AS_ERROR_ANNOT_CUSTOMERTYPE_NOTEXIST = 1258,	//�û��Զ������Ͳ�����

	TC_AS_ERROR_SC_BASE					= 1270, //AS�ɼ�������ʼ
	TC_AS_ERROR_SC_UNKNOW				= 1271, //�ɼ�δ֪����
	TC_AS_ERROR_SC_GDI_OBJECT			= 1272, //����GDI����ʧ��

    // ��Ƶ���������
	TC_VIDEO_ERROR_BASE                 = 1300,
	TC_VIDEO_ERROR_WND_NULL             = 1301,		//����Ϊ��
	TC_VIDEO_ERROR_WND_ISUSED           = 1302,		//�����Ѿ���ʹ��
	TC_VIDEO_ERROR_DISCONNECT           = 1303,		//��Ƶ���ڶ�����
	TC_VIDEO_ERROR_CREATE_ENGINE        = 1305,		//����Engineʧ��
	TC_VIDEO_ERROR_NO_SESSION	        = 1306,		//��Ƶû��Session
	TC_VIDEO_ERROR_NO_VIDEO_OBJ	        = 1307,		//��Ƶû��Obj����
	TC_VIDEO_ERROR_NO_TABLE		        = 1308,		//��Ƶû�п��е�Table��
	TC_VIDEO_ERROR_ALREADY_EXIST_OPENLIST  = 1309,	//���豸ʱ�����豸�Ѿ������ڴ򿪵��б���
	TC_VIDEO_ERROR_COMPONENT_NOTREADY   = 1310,		//��Ƶ�����û��׼����
	TC_VIDEO_ERROR_DLL_UNLOAD			= 1311,		//��Ƶ���Ѿ���ж�ص���
	TC_VIDEO_ERROR_NOTIN_RESOLUTION_RANGE= 1312,	//�ֱ��ʲ���ʹ�÷�Χ֮��
	TC_VIDEO_ERROR_RESOLUTION_NOTSUPPORT= 1313,		//�ֱ��ʳ����豸��������������Χ
	TC_VIDEO_ERROR_OVER_MAX_OPENVIDEO	= 1314,		//�������Ĵ���Ƶ·��
	TC_VIDEO_ERROR_SAME_CAPBILITY_USED	= 1320,		//���豸��ͬ�������Ѿ���ʹ����
	TC_VIDEO_ERROR_STATUS_UNINIT		= 1321,		//��Ƶ�����ǰ���ͷ�״̬
	TC_VIDEO_ERROR_NOT_FIND_WNDCELL		= 1322,		//��Ƶ�򲻵�����û��豸�Ķ�ӦCell
	TC_VIDEO_ERROR_NOTIN_MAXOPEN_RANGE	= 1323,		//�������Ĵ���Ƶ·��
	TC_VIDEO_ERROR_ALLREADY_PAUSE		= 1324,		//����Ƶ�Ѿ�������ͣ״̬
	TC_VIDEO_ERROR_NOT_PAUSE_STATUS		= 1325,		//����Ƶδ������ͣ״̬
	TC_VIDEO_ERROR_SWITCH_STREAM_STATUS	= 1326,		//�л��ߵ���ʱ����(����Decode�������Ǵ�����ͣ״̬)
	TC_VIDEO_ERROR_OPERATE_STATUS		= 1327,		//������Ƶ����(����Table��ֵ�Ѿ�������)
	TC_VIDEO_ERROR_ANDROID_LOCALVIEW_NO_RENDER = 1328,	//Android�Ļ����ǲ���Ҫ��������Render
	TC_VIDEO_ERROR_RESOLUTION_NOTFIT	= 1329,		//���÷ֱ��ʸ������ֱ��ʲ�һ��(����ⲿ�ɼ��豸)
	TC_VIDEO_ERROR_FLOWCTRL				= 1330,		//���ڽ�������
	TC_VIDEO_ERROR_OUTSIDE_FLOWCTRL		= 1331,		//���ڽ����ⲿ����


	TC_VIDEO_ERROR_DEVICE_OPENED        = 1340,		//��Ƶ�豸�Ѿ���ʹ����
	TC_VIDEO_ERROR_DEVICE_WIZARD_USED	= 1341,		//��Ƶ�豸�Ѿ�����ʹ����

	TC_VIDEO_ERROR_WIZARD_NOTSAME_DEVICE= 1342,		//�����ò���ʱ������ͬһ���豸
	TC_VIDEO_ERROR_WIZARD_SAME_PARAM	= 1343,		//�����ò���ʱ��������ͬ�Ĳ���

	TC_VIDEO_ERROR_MY_NODEID			= 1344,		//ʹ�����Լ���NodeID
	TC_VIDEO_ERROR_DEVICE_NOT_OPENED	= 1345,		//�豸��û�д�


	TC_VIDEO_ERROR_NOT_MYDEVICE			= 1350,		//����Ƶ�豸���ǵ�ǰ�û����豸
	TC_VIDEO_ERROR_TOOLONG_FILENAME		= 1351,		//��Ƶ���ļ���̫��

	TC_VIDEO_ERROR_RENDER_DISPLAY_PARAM = 1352,		//��ƵRender��������
	TC_VIDEO_ERROR_ROTATE				= 1353,		//��Ƶ��ת��������
	TC_VIDEO_ERROR_PC_MOBILE_VERSION_API= 1354,		//PC���ƶ��汾API����

	TC_VIDEO_ERROR_NOT_WND				= 1355,		//���ڲ���IsWindow()
	TC_VIDEO_ERROR_OVER_CAPTURECAPBILITY= 1356,		//���豸���õ���������Capture������
	TC_VIDEO_ERROR_NOT_WND_NOTFIT		= 1357,		//������ʹ�ù�����(����Detachʱ)�����ղ�Attachʱ�Ĵ��ڲ�һ��

	TC_VIDEO_ERROR_MULCONF_CANNOT_USERHME = 1358,	//�����ʱ����ʹ��VIDEOHME����һ����������ʹ��HME��
	TC_VIDEO_ERROR_MULCONF_HANGUP		= 1359,		//�����ʱ���˻������ڹ���״̬

	TC_VIDEO_ERROR_IS_THIRDCAPTURE_DEVICE = 1360,		//���豸�ǵ������豸
	TC_VIDEO_ERROR_ISNOT_THIRDCAPTURE_DEVICE = 1361,	//���豸���ǵ������豸

	TC_VIDEO_ERROR_BITRATE_RANGE		= 1362,		//���ʲ��������ķ�Χ֮��
	TC_VIDEO_ERROR_NOT_DOUBLESTREAM		= 1363,		//��ǰ����˫��
	TC_VIDEO_ERROR_NOT_FIND_THIRDCARD	= 1364,		//�Ҳ����������Ĳɼ���

	TC_VIDEO_ERROR_VIDEO_NOTOPEN		= 1365,		//��Ƶ��û����
	TC_VIDEO_ERROR_VIDEO_RECORDING		= 1366,		//��Ƶ����¼����
	TC_VIDEO_ERROR_VIDEO_RECOREND		= 1367,		//��Ƶ¼���Ѿ�����

    // ��Ƶ���������
	TC_AUDIO_ERROR_BASE                 = 1400,
	TC_AUDIO_ERROR_NOT_INITIALIZATION   = 1401,		//δ��ʼ��
	TC_AUDIO_ERROR_PARAM_NOTEXIST		= 1402,		//����������
	TC_AUDIO_ERROR_FILE_NOT_SUPPORT		= 1403,
	//TC_AUDIO_NEGOTIATE_CODEC_FAIL		= 1404,
	TC_AUDIO_CREATE_SEND_THREAD_FAIL	= 1405,
	TC_AUDIO_PARAM_WRONG				= 1406,
	TC_AUDIO_FUNC_ALREADY_CALLED		= 1407,
	TC_AUDIO_ENGINE_INIT_FAILED			= 1408,
	TC_AUDIO_PARAM_NOT_INITIALIZATION   = 1409,		//δ����conf_audio_setParam���ò���
	TC_AUDIO_ERROR_SESSION_NOT_READY    = 1410,
	TC_AUDIO_ERROR_MIC_NOT_OPEN			= 1411,		//��˷�δ��
	TC_AUDIO_ERROR_SPEAKER_NOT_OPEN     = 1412,		//
	TC_AUDIO_MIC_ALREADY_OPEN			= 1413,		//
	TC_AUDIO_MIC_ALREADY_MUTE           = 1414,		//
	TC_AUDIO_MIC_ALREADY_UMUTE          = 1415,		//
	TC_AUDIO_OVER_MAX_DEVICE_OPEN		= 1416,		//��������Ĵ��豸����
	TC_AUDIO_SPEAKER_ALREADY_OPEN       = 1417,		//
	TC_AUDIO_SPEAKER_ALREADY_MUTE       = 1418,
	TC_AUDIO_SPEAKER_ALREADY_UMUTE      = 1419,
	TC_AUDIO_IS_NOT_SUPPORTED           = 1420,		//�ӿڲ���֧��
	TC_AUDIO_ERROR_ALREADY_IN_PRIVATE   = 1421,
	TC_AUDIO_ERROR_ALREADY_NOT_IN_PRIVATE = 1422,
	TC_AUDIO_ERROR_DEVICE_INOPERABLE    = 1423,		//������У��豸����������ռ��
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
	

    // ý�干����������
	TC_MS_ERROR_BASE                    = 1500,
	TC_MS_ERROR_BITRATE_TO_HIGH         = 1501,
	TC_MS_BITRATE_512_1024              = 1502,

    // ͶƱ���������
	TC_POLLING_ERROR_BASE               = 1600,

    // ¼�ƴ��������
	TC_RECORD_ERROR_BASE					= 1700,
	TC_RECORD_ERROR_INOPERABLE				= 1701,
	TC_RECORD_ERROR_PATH_NOT_FOUND			= 1702,		//·������
	TC_RECORD_ERROR_WAIT_TIME_OUT			= 1703,
	TC_RECORD_ERROR_SYSTEM_NOT_SUPPORT_WMF  = 1704,		//���ز�֧��WMV¼��

	// �ļ�������������
	TC_FT_ERROR_BASE                    = 1800,
	TC_FT_ERROR_CREATE_FILE_FAIL        = 1801,  //���ܴ���ָ���ļ�
	TC_FT_ERROR_DOWNLOADING_CANCELED    = 1802,  //�����ѱ�ȡ��
	TC_FT_ERROR_INVALID_FILE_HANDLE     = 1803,  //��Ч�ļ����
	TC_FT_ERROR_INVALID_STATE           = 1804,  //��Ч���״̬
	TC_FT_ERROR_INVALID_FILE            = 1805,  //�ļ�·����û�ж�Ӧһ����Ч�ļ�
	TC_FT_ERROR_EMPTY_FILE              = 1806,  //�ļ�Ϊ��(�����ϴ�)
	TC_FT_ERROR_UPLOADING_TIMEOUT       = 1807,  //�ļ��ϴ���ʱ
	TC_FT_ERROR_ALREADY_DOWNLOADING     = 1808,  //�ļ��Ѿ���������

};

/*** �ص���Ϣ���� ***/
enum{
    //������Ϣ 
    CONF_MSG_ON_CONFERENCE_JOIN			= 1001,	//�������֪ͨ
    CONF_MSG_ON_CONFERENCE_TERMINATE	= 1002, //�������֪ͨ
    CONF_MSG_ON_CONFERENCE_LEAVE        = 1003,	//�Ͽ���������
    CONF_MSG_ON_COM_STATUS_UPDATE       = 1004,	//֪ͨ����л�
    CONF_MSG_ON_PRIVILEGE_UPDATE        = 1005,	//Ȩ�ޱ��
    CONF_MSG_ON_CONF_MODEL_UPDATE       = 1006,	//ͬ������ģʽ
    CONF_MSG_ON_LAYOUT_UPDATE           = 1007,	//ͬ�����鲼��
    CONF_MSG_ON_MESSAGE_UPADATE         = 1008, //����Param���
    CONF_MSG_ON_COM_FULL_SCREEN         = 1009,	//ȫ���л�

    CONF_MSG_ON_FLOW_CONTROL            = 1010,	//��������֪ͨ
    CONF_MSG_ON_LOCK_RSP                = 1011,	//��������������֪ͨ
    CONF_MSG_ON_LOCK_REPORT_IND         = 1012,	//��������֪ͨ
    CONF_MSG_ON_REG_TOKEN_IND           = 1013,	//ע��Token֪ͨ
    CONF_MSG_ON_EXTEND_RSP              = 1014,	//������ʱ������֪ͨ
    CONF_MSG_ON_EXTEND_IND              = 1015,	//������ʱ֪ͨ

    CONF_MSG_ON_TIME_REMAINING_IND      = 1016, //�������ʱ��֪ͨ
    CONF_MSG_ON_APPSVR_INVITE_CFM       = 1017, //

    CONF_MSG_ON_TABLE_INSERT_IND        = 1018,	//�����������ͱ���֪ͨ
    CONF_MSG_ON_TABLE_DELETE_IND        = 1019,	//�����������ͱ�ɾ��֪ͨ
    CONF_MSG_ON_PING_COMPLETE           = 1020,	//����ping���֪ͨ
    CONF_MSG_ON_PING_PROGRESS_REPORT    = 1021,	//����ping����֪ͨ

    CONF_MSG_ON_DISCONNECT              = 1022, // �������
    CONF_MSG_ON_RECONNECT               = 1023, // ���������ɹ�

    CONF_MSG_ON_COMPONENT_LOAD          = 1031,	//������سɹ�֪ͨ
    CONF_MSG_ON_NOTICE_IND              = 1032, //��������֪ͨ
    CONF_MSG_ON_MAX_VOICE               = 1033, //����������Ϣ
    CONF_MSG_SERVER_TIME                = 1034, //���������ʱ��

	CONF_MSG_ON_MUTE					= 1041,	//����
	CONF_MSG_ON_NETSTATUS_REPORT		= 1051,	//����״̬���棬����״̬

    //////////////////////////////////////////////////////////////////////////
    // �����û���Ϣ
    CONF_MSG_USER_ON_HOST_CHANGE_IND       = 1101, //�����˱���������˶����յ�
    CONF_MSG_USER_ON_HOST_CHANGE_CFM       = 1102, //�����˱���������������յ�
    CONF_MSG_USER_ON_HOST_GIVE_IND         = 1103, //�����˱�����������߻��յ�
    CONF_MSG_USER_ON_HOST_GIVE_CFM         = 1104, //�����˱���������߻��յ�

    CONF_MSG_USER_ON_PRESENTER_CHANGE_IND  = 1105, //�����˱���������˶����յ�
    CONF_MSG_USER_ON_PRESENTER_CHANGE_CFM  = 1106, //�����˱���������������յ�
    CONF_MSG_USER_ON_PRESENTER_GIVE_IND    = 1107, //�����˱�����������߻��յ�
    CONF_MSG_USER_ON_PRESENTER_GIVE_CFM    = 1108, //�����˱���������߻��յ�

    CONF_MSG_USER_ON_ENTER_IND             = 1109, //�û�����
    CONF_MSG_USER_ON_LEAVE_IND             = 1110, //�û��뿪
    CONF_MSG_USER_ON_MODIFY_IND            = 1111, //�û���Ϣ���
    CONF_MSG_USER_ON_MESSAGE_IND           = 1112, //�û���Ϣ֪ͨ
    CONF_MSG_USER_ON_OFFLINE_IND           = 1113, //�û�����֪ͨ
    CONF_MSG_USER_ON_RECONNECT_IND         = 1114, //�û����߻ָ�֪ͨ

    CONF_MSG_ON_PHONE_ENTER_IND	           = 1201,	//�绰�û�����
    CONF_MSG_ON_PHONE_LEAVE_IND            = 1202,	//�绰�û��뿪
    CONF_MSG_ON_PHONE_STATUS_IND           = 1203,	//�绰״̬�仯
    CONF_MSG_ON_PHONE_SESSION_JOIN         = 1204,	//�绰ģ�����֪ͨ
    CONF_MSG_ON_PHONE_SESSION_OPEN         = 1205,	//�绰ģ���֪ͨ
    CONF_MSG_ON_PHONE_SESSION_CLOSE        = 1206,	//�绰ģ��ر�֪ͨ
    CONF_MSG_ON_PHONE_MUTE_STATUS_IND      = 1207,	//�绰����֪ͨ
    CONF_MSG_ON_PHONE_CALL_NID_IND         = 1208,	//
    CONF_MSG_ON_PHONE_CALL_MUTE_IND        = 1209,
    CONF_MSG_ON_PHONE_CALL_NAME_IND        = 1210,
    CONF_MSG_ON_PHONE_CALL_PIN_NUM_IND     = 1211,	//Pin�뷵��֪ͨ
    CONF_MSG_ON_PHONE_CALL_VIDEO_OPEN_STATUS_IND = 1212,
    CONF_MSG_ON_PHONE_CALL_USER_STATUS_IND       = 1213,
    CONF_MSG_ON_PHONE_CALL_USER_TYPE_IND         = 1214,
    CONF_MSG_ON_PHONE_CALL_VIDEO_CAPABLE_IND     = 1215,
    CONF_MSG_ON_PHONE_PC_USER_MIC_MUTE_REQ       = 1216,
    CONF_MSG_ON_PHONE_PC_USER_CAMERA_OPEN_REQ    = 1217,

	CONF_MSG_ON_PHONE_ON_XML_STATUS_GET          = 1218,
    CONF_MSG_ON_PHONE_IVR_REQ_IND                = 1219,
    CONF_MSG_ON_PHONE_MGW_MESSAGE_IND            = 1220,	//MGW ��Ϣ
	CONF_MSG_ON_PHONE_GET_PIN		             = 1221,	//�û���ȡPIN��
	CONF_MSG_ON_PHONE_CALL_FAILED				 = 1222,	//���е绰�ɹ�֪ͨ
	CONF_MSG_ON_PHONE_CALL_SUCCESSED			 = 1223,	//���е绰ʧ��֪ͨ

	CONF_MSG_ON_PHONE_EXTEND					 = 1224,
	CONF_MSG_ON_PHONE_ROLLCALL_IND               = 1225,    //�������������֪ͨ nvalue1 == 1Ϊ������nvalue1 == 0Ϊ����


    //////////////////////////////////////////////////////////////////////////
    // VIDEO MESSAGE
    COMPT_MSG_VIDEO_ON_SWITCH					= 2001,		//��Ƶ״̬���:1:�� 0:�ر�  2.Resume 4.Pause
    COMPT_MSG_VIDEO_ON_DEVICE_CHANGE			= 2002,		//�豸�岦:(�Լ��豸�Ĳ岦)

	COMPT_MSG_VIDEO_ON_DEVICE_INFO				= 2003,		//�豸��ӻ���ɾ��:(�����Լ��ͱ���)
	COMPT_MSG_VIDEO_ON_DEVICE_CAPBILITY			= 2004,		//�豸������Ϣ(�ݲ�ʹ��)
	COMPT_MSG_VIDEO_ON_DISCONNECT				= 2005,		//��Ƶģ���Ƿ�����
	COMPT_MSG_VIDEO_ON_RECONNECT				= 2006,		//��Ƶģ���Ƿ���������
	COMPT_MSG_VIDEO_ON_USER_STATUSCHANGE		= 2007,		//�û�״̬�ı�(�ݲ�ʹ��)
	COMPT_MSG_VIDEO_ON_USERDEVICE_STATUSCHANGE	= 2008,		//��Ƶ�����ߵ�״̬�ı�:(��ͣ��ȡ����ͣ)
	COMPT_MSG_VIDEO_ON_MAX_OPENVIDEO			= 2009,		//������Ƶ��

	COMPT_MSG_VIDEO_ON_NOTIFY					= 2010,		//�յ����˷���������֪ͨ��������ر�����

	COMPT_MSG_VIDEO_FLOWCONTROL_NOTIFY			= 2011,		//��Ƶ���غ��л���Ƶ����֪ͨ
	COMPT_MSG_VIDEO_WARNING_FLOWCONTROL			= 2012,		//��Ƶ���ؾ��棬������������������Ƶ�����Ѿ��ﵽ��С��

//for  Android
	COMPT_MSG_VIDEO_ON_GETDEVICE_NUM			= 2013,		//ȡ���Լ����豸����
	COMPT_MSG_VIDEO_ON_GETDEVICE_INFO			= 2014,		//ȡ���Լ����豸��Ϣ

	COMPT_MSG_VIDEO_GETPARAM					= 2015,		//�õ����õ���Ƶ����

	COMPT_MSG_VIDEO_ON_SWITCH_MOREINFO			= 2021,		//��Ƶ״̬���:1:�� 0:�ر�  2.Resume 4.Pause,������ϸ����Ϣ(��Ҫ��˫��)
	COMPT_MSG_VIDEO_ON_JOINCHANNEL				= 2022,		//��Ƶ���뵽�ĸ���
	COMPT_MSG_VIDEO_ON_LOAD_THIRDCAPTUREDLL		= 2023,		//���ص�������

	COMPT_MSG_VIDEO_ON_DEVICECAPBILITY_NUM		= 2024,		//�豸��������
	COMPT_MSG_VIDEO_ON_DEVICECAPBILITY_INFO		= 2025,		//�豸������Ϣ

	COMPT_MSG_VIDEO_ON_FIRST_KEYFRAME			= 2026,		//���ؽ����ĵ�һ���ؼ�֡

	//For VTM Record
	COMPT_MSG_VIDEO_STARTRECORD_RESULT			= 2027,		//¼���Ƿ�ɹ�
	COMPT_MSG_VIDEO_ENDRECORD_RESULT			= 2028,		//����¼���Ƿ�ɹ�

    COMPT_MSG_VIDEO_ON_DATA						= 2099,		//�յ�����֪ͨ(�ݲ�ʹ��)

    //desktop share component, app share
	COMPT_MSG_AS_BASE					= 2100,	// ���湲����Ϣ��ʼ
	
	COMPT_MSG_AS_ON_SCREEN_BASE			= 2110,	// 
	COMPT_MSG_AS_ON_SCREEN_DATA			= 2111,	//��Ļ���ݸ���֪ͨ
	COMPT_MSG_AS_ON_SCREEN_SIZE			= 2112,	//��Ļ��С���֪ͨ 
	COMPT_MSG_AS_ON_SCREEN_BOND			= 2113,	// 
	COMPT_MSG_AS_ON_SCREEN_BORDER		= 2114,	// ��Ļ�ڱ�֪ͨ
	COMPT_MSG_AS_ON_SCREEN_KEYFRAME		= 2115,	// ��Ļ�ؼ�֪֡ͨ

	COMPT_MSG_AS_ON_SHARING_BASE		= 2120,	// 
	COMPT_MSG_AS_ON_SHARING_STATE		= 2121,	//����״̬֪ͨ 
	COMPT_MSG_AS_ON_SHARING_SESSION		= 2122,	//����ͨ��֪ͨ 
	COMPT_MSG_AS_ON_PRIVILEGE			= 2123,	//����Ȩ��֪ͨ 
	COMPT_MSG_AS_ON_MODULE				= 2124,	//����Ȩ��֪ͨ //(SHCBK_STATE_MODULE,0, State, NULL), 
	COMPT_MSG_AS_ON_VERSION				= 2125,	//����Ȩ��֪ͨ //(SHCBK_STATE_VERSION,0, version, NULL)
	COMPT_MSG_AS_ON_CHANNEL				= 2126,	//����Ȩ��֪ͨ //(SHCBK_STATE_CHANNEL,NodeID, Type, Action)

	COMPT_MSG_AS_ON_ANNOTATION_BASE		= 2130,	//��Ļ�����ע��Ϣ��ʼ(��δʹ��)

	COMPT_MSG_AS_ON_USERDEFINE_BASE			= 2150,	//�û��Զ���������ʼ 
	COMPT_MSG_AS_ON_USERDEFINE_MSG			= 2151,	//�û��Զ�����Ϣ֪ͨ 
	COMPT_MSG_AS_ON_USERDEFINE_REMOTE_SHARE	= 2152,	//Զ��������Ļ����
	COMPT_MSG_AS_ON_USERDEFINE_CONTROL		= 2153,	//Զ�̿��ƻص�
	COMPT_MSG_AS_ON_ERROR					= 2154,	//��Ļ�����쳣��Ϣ

	COMPT_MSG_AS_ON_XML_GET_PARAM       = 2160,

   //document share component
    COMPT_MSG_DS_ON_DOC_NEW	= 2201,		//�½�һ���ĵ�
    COMPT_MSG_DS_ON_DOC_DEL	= 2202,		//ɾ��һ���ĵ�

    COMPT_MSG_DS_ON_PAGE_NEW = 2203,	//�½�һҳ
    COMPT_MSG_DS_ON_PAGE_DEL = 2204,	//ɾ��һҳ

    COMPT_MSG_DS_ON_CURRENT_PAGE_IND = 2205,    //ͬ����ҳԤ��֪ͨ
    COMPT_MSG_DS_ON_CURRENT_PAGE     = 2206,	//ͬ����ҳ�ɹ�

	COMPT_MSG_DS_ON_DOCLOAD_START    = 2207,	//��ʼ�����ĵ�
	COMPT_MSG_DS_ON_PAGE_LOADED      = 2208,	//�ɹ�����һҳ
	COMPT_MSG_DS_ON_DOCLOAD_FINISH   = 2209,	//�����ĵ�����

	COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY = 2210,	//�ĵ���������
	COMPT_MSG_DS_XML_ON_OPEN = 2211,			//android�´��ĵ����첽���ص�ID��	
    COMPT_MSG_DS_PAGE_DATA_DOWNLOAD = 2212,     //�ĵ�ҳ�������Ѿ�����֪ͨ

	COMPT_MSG_DS_THUMBNAIL_UPDATE	= 2213,		//����ͼ����

	COMPT_MSG_DS_PAGEINFO_UPDATE	= 2214,		//ҳ����Ϣ���£����Ƿ񱻵��ӱʲ�������

	COMPT_MSG_DS_ANDROID_DOC_COUNT	= 2215,		//androidʹ�ã��ĵ�����

	COMPT_MSG_DS_ANDROID_PIC_TOO_BIG = 2216,	//androidʹ�ã�ҳ��ͼƬ��ע�������󣬳����ڴ����ƵĲ��ֲ���ʾ��֪ͨ�ϲ�
	COMPT_MSG_DS_ANDROID_PIC_NORMAL = 2217,		//androidʹ�ã�ҳ��ͼƬ��ע�ɹ�������״̬�ع���������ɾ������֪ͨ�ϲ�

	COMPT_MSG_DS_MAX = 2299,							//�ĵ������Ϣ��û��ʵ������
    //File Transfer
    COMPT_MSG_FT_ON_FILE_REMOVE = 2301,		//�ļ���ɾ��
    COMPT_MSG_FT_ON_FILE_INFO,	            //�ļ������ӻ�״̬����
    COMPT_MSG_FT_ON_PROGRESS,			    //�ļ����ջ��ͽ���
    COMPT_MSG_FT_ON_END,				    //���ͻ������ɣ����쳣��ֹ
    COMPT_MSG_FT_ON_READLY,					//�ļ�ģ��

    //chat
	COMPT_MSG_CHAT_ON_GROUP_CREATE = 2400,	 //����Ⱥ�����ɹ�֪ͨ
	COMPT_MSG_CHAT_ON_GROUP_INFO_MODIFIED,	 //����Ⱥ��Ϣ�޸�֪ͨ
    COMPT_MSG_CHAT_ON_GROUP_INVITE,			 //�յ�����Ⱥ�ĵ�֪ͨ
    COMPT_MSG_CHAT_ON_GROUP_KICKOUT ,		 //�յ����߳�Ⱥ�ĵ�֪ͨ
	COMPT_MSG_CHAT_ON_GROUP_DESTROY,		 //������������������ʱ֪ͨ

	COMPT_MSG_CHAT_ON_GROUP_USER_ONLINE,	//�������û�����
	COMPT_MSG_CHAT_ON_GROUP_USER_OFFLINE,   //�������û�����
	COMPT_MSG_CHAT_ON_GROUP_USER_LEAVE,		//�������û��˳�

    COMPT_MSG_CHAT_ON_RECV_MSG,				//�յ�������Ϣ
	COMPT_MSG_CHAT_ON_PUBLIC_MSG_REMOVE,    //ɾ��������Ϣ֪ͨ

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
	COMPT_MSG_POLLING_ON_COMP_READY = 2601,		//ͶƱ���׼����
	COMPT_MSG_POLLING_ON_RECV_POLL,				//�յ��µ��ʾ�
	COMPT_MSG_POLLING_ON_RECV_ANSWER,			//�յ��µĴ�
	COMPT_MSG_POLLING_ON_DELETE_POLL,			//�յ�ɾ���ʾ�ָ��
	COMPT_MSG_POLLING_ON_POLL_ID_CHANGED,		//�ʾ�ID�����仯
	COMPT_MSG_POLLING_ON_GLOBAL_PARAM_UPDATE,	//ȫ�ֲ��������仯
	COMPT_MSG_POLLING_ON_POLL_PARAM_UPDATE = 2607,		//�ʾ����������Ϣ
	//for android
	COMPT_MSG_POLLING_XML_ON_NEW_POLL = 2610,			//�������ʾ������ʾ�ID
	COMPT_MSG_POLLING_XML_ON_NEW_QUESTION,		//���������⣬��������ID
	COMPT_MSG_POLLING_XML_ON_GET_POLL_TITLE,	//��ȡ�ʾ����
	COMPT_MSG_POLLING_XML_ON_GET_POLL_USERDATA, //��ȡ�ʾ��û�����
	COMPT_MSG_POLLING_XML_ON_GET_POLL_COUNT,	//��ȡ�ʾ�����
	COMPT_MSG_POLLING_XML_ON_GET_POLLID_BYINDEX,//����������ȡ�ʾ�ID
	COMPT_MSG_POLLING_XML_ON_GET_CREATOR_USERID,//��ȡ�ʾ������û�ID
	COMPT_MSG_POLLING_XML_ON_GET_QUESTION_COUNT,//��ȡĳ�ʾ���������
	COMPT_MSG_POLLING_XML_ON_GET_QUESTION,		//��ȡĳ�ʾ��������͡��������ݡ�����ѡ��
	COMPT_MSG_POLLING_XML_ON_GET_QUESTION_USERDATA,//��ȡ�����û�����
	COMPT_MSG_POLLING_XML_ON_GET_QUESTIONID_BYINDEX,//����������ȡ����ID
	COMPT_MSG_POLLING_XML_ON_GET_QUESTION_ANSWER, //��ȡ�����
	COMPT_MSG_POLLING_XML_ON_GET_QUESTION_ANSWER_USERDATA,//��ȡ������û�����
	COMPT_MSG_POLLING_XML_ON_LOAD_FROM_FILE, //��ȡ���ص��ʾ������Լ��ʾ�ID

	//audio
	COMPT_MSG_AUDIO_ON_AUDIO_MUTE_ALL_ATTENDEE = 2701,//�յ��᳡������Ϣ

	COMPT_MSG_AUDIO_ON_ENGINE_DEVICE_CHANGE,     //��Ƶ�豸�Ȳ��
	COMPT_MSG_AUDIO_ON_ENGINE_RUNNING_ERR_NOTIFY,    //����ϵͳ����ʱ����
	COMPT_MSG_AUDIO_ON_ENGINE_DEV_PLUGIN_NOTIFY, //���߶�������������������״̬�����仯��android������֪ͨ��������������Ч
	COMPT_MSG_AUDIO_ON_ENGINE_ROUTE_CHANGE_NOTIFY,   //�ƶ�·��״̬�����仯���ƶ�ƽ̨��

	COMPT_MSG_AUDIO_ON_AUDIO_NEGOTIATE_CODEC,   //�������Э�̱������
	COMPT_MSG_AUDIO_ON_AUDIO_ACTION,		    //�յ�mic��������,�Լ�����˽���������뿪˽��֪ͨ
	COMPT_MSG_AUDIO_ON_AUDIO_MAX_OPEN_DEVICE,	//�������򿪵��豸����
	COMPT_MSG_AUDIO_ON_AUDIO_DEVICE_STATUS_CHANGE,//��Ƶ�豸״̬֪ͨ mic
	COMPT_MSG_AUDIO_ON_AUDIO_MGW_EXCEPTION,      //MGW�쳣
	COMPT_MSG_AUDIO_ON_AUDIO_MGWVA_NEGOTIATE_CODEC, //��������
	COMPT_MSG_AUDIO_ON_AUDIO_OPEN_MIC, //�첽��mic���

	COMPT_MSG_AUDIO_ON_SYSTEM_SPEAKER_VOLUME,    //ϵͳ�����������ı�֪ͨ
	COMPT_MSG_AUDIO_ON_SYSTEM_MIC_VOLUME,        //ϵͳ��˷������ı�֪ͨ

	COMPT_MSG_AUDIO_ON_XML_MIC_VOLUME  = 2780,	//Mic�������֪ͨ
	COMPT_MSG_AUDIO_ON_XML_SPEAKER_VOLUME,		//�������������֪ͨ


	//white board
	COMPT_MSG_WB_ON_DOC_NEW	= 2801,		//�½�һ���ĵ�
	COMPT_MSG_WB_ON_DOC_DEL	= 2802,		//ɾ��һ���ĵ�

	COMPT_MSG_WB_ON_PAGE_NEW = 2803,	//�½�һҳ
	COMPT_MSG_WB_ON_PAGE_DEL = 2804,	//ɾ��һҳ

    COMPT_MSG_WB_ON_CURRENT_PAGE_IND = 2805, //��ҳǰԤ��֪ͨ
	COMPT_MSG_WB_ON_CURRENT_PAGE = 2806,	 //��ҳ�ɹ�֪ͨ
	COMPT_MSG_WB_ON_PAGE_DATA = 2807,	//

	COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY = 2808,	//�װ��������
    COMPT_MSG_WB_PAGE_DATA_DOWNLOAD = 2809,            //�ĵ�ҳ�������Ѿ�����֪ͨ

	COMPT_MSG_WB_XML_ON_NEW_DOC = 2810,				//android��new doc�󷵻�
	COMPT_MSG_WB_XML_ON_NEW_PAGE = 2811,				//android��new page�󷵻�
	COMPT_MSG_WB_XML_ON_COPY_PAGE = 2812,				//android��copy page�󷵻�

	COMPT_MSG_WB_THUMBNAIL_UPDATE	= 2813,		//����ͼ����

	COMPT_MSG_WB_PAGEINFO_UPDATE	= 2814,		//ҳ����Ϣ����

	COMPT_MSG_WB_ANDROID_DOC_COUNT	= 2815,		//androidʹ�ã��ĵ�����

	COMPT_MSG_WB_ANDROID_PIC_TOO_BIG = 2816,	//androidʹ�ã�ҳ��ͼƬ��ע�������󣬳����ڴ����ƵĲ��ֲ���ʾ��֪ͨ�ϲ�
	COMPT_MSG_WB_ANDROID_PIC_NORMAL = 2817,		//androidʹ�ã�ҳ��ͼƬ��ע�ɹ�������״̬�ع���������ɾ������֪ͨ�ϲ�

	COMPT_MSG_WB_MAX,							//�װ������Ϣ��û��ʵ������

	//annotation 2014 0303
	COMPT_MSG_ANNO_CREATE_NEWID		= 2901,			//�½�һ��ANNO

	COMPT_MSG_ANNO_TEXTCREATE_NEWID	= 2902,			//�½�һ��Text
	COMPT_MSG_ANNO_TEXT_GETINFO		= 2903,			//�õ�Text_Anno��Ϣ

	COMPT_MSG_ANNO_HITTEST			= 2904,			
	COMPT_MSG_ANNO_HITTEST2			= 2905,			
	COMPT_MSG_ANNO_GETINFO			= 2906,

	COMPT_MSG_ANNO_MAX,							//ANNOTATION�����Ϣ��û��ʵ������
};

#define TC_MAX_PATH	 256

#define TC_MAX_PHONE_CONF_NUM_LEN	16
#define TC_MAX_PHONE_PASS_CODE_LEN	32
#define TC_MAX_PHONE_USER_NAME_LEN	64
#define TC_MAX_PHONE_SVR_URL_LEN	128

#define TC_MAX_CONF_SERVER_IP       128			//IP��ַҪ��һЩ
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


// ��Ӧ���������Ͷ���
typedef TUP_UINT32  TC_Time;
typedef TUP_UINT32	TC_Conf_User_Status;
typedef TUP_UINT16	TC_Conf_Presence_Flag;
typedef TUP_UINT32  TC_Conf_Capability;

//////////////////////////////////////////////////////////////////////////
/*�û���Ϣ����*/
typedef struct tag_conf_user_record
{
    TUP_UINT32					user_alt_id;			//�û�ID
    TUP_UINT8					device_type;			//�豸����
    TUP_UINT8					os_type;				//����ϵͳ����
    TC_Conf_Presence_Flag		user_presence_flag;		//�û�״̬
    TC_Conf_Capability			user_capability;		//�û���������Ӧ�ò����
    TC_Conf_User_Status			user_status;			//�û�Ȩ����Ϣ���ݲ���
    TUP_CHAR					user_name[TC_MAX_USER_NAME_LEN];		//�û�����
    TUP_CHAR					user_alt_uri[TC_MAX_USER_LOG_URI_LEN];		//�û�ͳһ��ʶ
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

// �ص��������Ͷ���
#if defined(MY_ANDROID) && (defined(TEST_8950) || !(defined CONF_IPPHONE))
	typedef TUP_VOID (TUP_STDCALL *conference_multi_callback)(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pMsg, TUP_VOID* pContext, TUP_INT nSize);	
#else
	//conference_multi_callback �� component_multi_callback���ڶ���鳡��
	typedef TUP_VOID (TUP_STDCALL *conference_multi_callback)(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pVoid, TUP_INT nSize);   //����Ļص�����	
#endif
   
//���������Ļص�����
typedef TUP_VOID (TUP_STDCALL *component_multi_callback)(CONF_HANDLE confHandle, TUP_INT nType, TUP_UINT nValue1, TUP_ULONG nValue2, TUP_VOID* pVoid, TUP_INT nSize);    //����Ļص�����

//////////////////////////////////////////////////////////////////////////
// �����ʼ����
typedef struct tag_init_paramter
{
    CONF_OS_TYPE        os_type;					//����ϵͳ����
    CONF_DEVICE_TYPE    dev_type;					//�����豸����
	TUP_UINT8			media_log_level;			//ý����־����
	TUP_UINT8			sdk_log_level;				//�����־����
	TUP_CHAR			log_path[TC_MAX_PATH];		//��־Ŀ¼����ѡ
	TUP_CHAR			temp_path[TC_MAX_PATH];		//��ʱĿ¼����ѡ
	TUP_UINT32          dev_dpi_x;					//�豸����DDI��androidƽ̨��Ҫ���ã�����ƽ̨������Ϊ0
	TUP_UINT32          dev_dpi_y;					//�豸����DDI��androidƽ̨��Ҫ���ã�����ƽ̨������Ϊ0

#ifdef __cplusplus
	tag_init_paramter()
	{
		memset(this, 0, sizeof(tag_init_paramter));
	}
#endif
} Init_param;

//////////////////////////////////////////////////////////////////////////
//�������
typedef struct tag_conf_info
{
	TUP_UINT32              conf_id;			//����ID��һ����Ҫ�������������ṩ����ѡ
	TUP_UINT32              user_id;			//�û�ID���������û���Ψһ��ʶ���ⲿ���壬��ѡ
    TUP_UINT32              user_type;			//�û����ͣ���ѡ�������� 1��������2 ����ͨ�����8
    TUP_UINT32              user_capability;	//�û�������Ӧ�ò㶨�壬��ѡ
    TUP_INT64               sever_timer;		//time_t ����ʱ�䣺��һ��ʱ���(һ����1970��1��1��0ʱ0��0��)����ʱ������������Ϊ0

    TUP_CHAR                host_key[TC_MAX_HOST_KEY_LEN];		    //���������룺���������������ã������������Ҫ
    TUP_CHAR                site_url[TC_MAX_SITE_URL_LEN];		    //������վ��ַ��IPT������ΪU19�ĵ�ַ����ѡ������Ϊ��
    TUP_CHAR                site_id[TC_MAX_CONF_SITE_ID_LEN];	    //վ��ID����ѡ������Ϊ��
    TUP_CHAR                user_name[TC_MAX_USER_NAME_LEN];        //�û�����
    TUP_CHAR                conf_title[TC_MAX_CONF_TITLE_LEN];	    //������������
    TUP_CHAR                ms_server_ip[TC_MAX_CONF_SERVER_IP];    //�����������ַ��������ַ��URL
    TUP_CHAR                encryption_key[TC_MAX_ENCRYPTION_KEY];  //�����Ȩ���룬��ѡ
    TUP_CHAR                user_log_uri[TC_MAX_USER_LOG_URI_LEN];  //�û�ͳһ��������һ�����ں�����ϵͳ����ʱ�û��󶨣���ѡ

	CONF_OS_TYPE			os_type;
	CONF_DEVICE_TYPE		dev_type;
    TUP_UINT8*		        user_info;			 //�û�������Ϣ����ѡ
    TUP_UINT16		        user_info_len;		 //�û�������Ϣ���ȣ���ѡ

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

//CONF_MSG_USER_ON_MODIFY_INDʱ��Ӧ�ĸ��¶���
#define TC_USER_MODIFY_PF        0x04	//presence_flag����
#define TC_USER_MODIFY_PS        0x08	//user_status����
#define TC_USER_MODIFY_PC        0x10	//user_capability����
#define TC_USER_MODIFY_PD        0x20   //
#define TC_USER_MODIFY_PU        0x40   //user_info����

////////////////////////////////Base Define/////////////////////////////////

typedef TUP_UINT32  COLORRGBA;


//��Ķ���
typedef struct tagTcPoint
{
	TUP_INT	x;
	TUP_INT	y;
}TC_POINT;

//�ߴ綨��
typedef struct tagTcSize
{
	TUP_INT	cx;
	TUP_INT	cy;
}TC_SIZE;

//���ζ���
typedef struct tagTcRect
{
	TUP_INT nX;
	TUP_INT nY;
	TUP_INT nWidth;
	TUP_INT nHeight;
}TC_RECT;

//���ζ���
typedef struct tagTcRect2
{
	TUP_INT	left;
	TUP_INT	top;
	TUP_INT	right;
	TUP_INT	bottom;
}TC_RECT2;

enum	//ͼ���ʽ
{
	Bitmap_Format_Pal1,
	Bitmap_Format_Pal2,
	Bitmap_Formatt_Pal4,
	Bitmap_Format_Pal8,	
	Bitmap_Format_RGB565,
	Bitmap_Format_RGB888,
	Bitmap_Format_XRGB8888,
};

//���ص�ͼƬ����
struct TC_BITMAP
{
    TUP_LONG        bmType;
    TUP_LONG        bmWidth;
    TUP_LONG        bmHeight;
    TUP_LONG        bmWidthBytes;

    TUP_UINT16      bmPlanes;
    TUP_UINT16      bmBitsPixel;
    TUP_VOID*       bmBits;			//ͼƬ����
};

//////////////////////////////��Ƶģ�鶨�岿��/////////////////////////////////

typedef enum	//��Ƶ�ֱ���
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
	VIDEO_DEVICE_PHONE	= 2,	//�绰
	VIDEO_DEVICE_ZZTP	= 3		//����TP
}ENUM_VIDEO_DEVICE_TYPE;


//��Ƶ�豸����
typedef struct tagTC_DEVICE_INFO
{
	TUP_UINT32	_UserID;			//����ǵ���NodeID,UI�㵱����UserID
	TUP_UINT32	_DeviceID;			//�豸ID
	TUP_UINT32	_RecordID;			//���򣬶�Ӧ�ò�����
	TUP_CHAR	_szName[256];		//�豸����
	TUP_INT		_status;			//�豸״̬ (������)	 [2013 0627 ��ǰ������ʾAndroid���ֺ����ת��]
	TUP_UINT16	_Version;			//�汾
	TUP_UINT16	_DeviceType;		//�豸������(����ͷ�����棬�绰)

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

//��Ƶ���ò�������
typedef struct tagTC_VIDEO_PARAM
{
	TUP_UINT32	dwUserID;			//�û�ID (����Ӧ�ò���˵��UserID,�����������˵��NodeID)
	TUP_UINT32	dwDeviceID;			//�豸ID
	TUP_UINT32	xResolution;		//x�ֱ���(��)
	TUP_UINT32	yResolution;		//y�ֱ���(��)
	TUP_UINT32	nFrameRate;			//֡��
	TUP_UINT32	nBitRate;			//����
	TUP_UINT32	nRawtype;			//��Ƶ��ʽ����YUV����ǰ��Ч
	TUP_UINT32	nFecValue;			//FEC�İٷֱ�

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

//�������ɼ������Զ���
typedef struct tagTC_VIDEO_THIRDCAPTURE_PROPERTY
{
	TUP_UINT32	dwUserID;			//�û�ID (����Ӧ�ò���˵��UserID,�����������˵��NodeID)
	TUP_UINT32	dwDeviceID;			//�豸ID
	TUP_UINT32	dwDeviceType;		//�豸����
	TUP_UINT32	nBrightness;		//����ֵ��0-255��
	TUP_UINT32	nContrast;			//�Աȶȣ�0-127��
	TUP_UINT32	nSaturation;		//���Ͷȣ�0-127��
	TUP_UINT32	nHue;				//ɫ����0-255��

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

//˫��״̬����
typedef struct tagTC_VIDEO_DOUBLESTREAM_STATUS
{
	TUP_UINT32	dwUserID;			//�û�ID (����Ӧ�ò���˵��UserID,�����������˵��NodeID)
	TUP_UINT32	dwDeviceID;			//�豸ID

	TUP_UINT32	xResolution;		//x�ֱ���(��)
	TUP_UINT32	yResolution;		//y�ֱ���(��)

	TUP_BOOL	bHighOrLowChannel;	//��ǰ���뵽�������ǵ���
	TUP_BOOL	bDoubleStream;		//�Ƿ�˫��
	TUP_BOOL	bOwnLowStream;		//�Ƿ�ӵ�е���	
	TUP_BOOL	bFlowCtrl;			//�Ƿ������ظ澯����

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
	VIDEO_NOTIFY_OPEN = 1,							//֪ͨ�����˴���Ƶ
	VIDEO_NOTIFY_CLOSE,								//֪ͨ�����˹ر���Ƶ
	VIDEO_NOTIFY_DATA_SENDTO_PHONESESSION,			//��Ƶ���ݷ��͸�PHONESESSION
	VIDEO_NOTIFY_NULLDATA_SENDTO_PHONESESSION,		//�绰�������Լ����͸�PHONESESSION
	VIDEO_NOTIFY_DATA_SENDTO_MCUSESSION,			//��Ƶ���ݷ��͸�MCUSESSION ����
	VIDEO_NOTIFY_NULLDATA_SENDTO_MCUSESSION,		//�绰�������Լ����͸�MCUSESSION ����
};

//OnVideoChange, Ϊ����IPAD״̬ͳһ���������һ�µ�
//IPAD��״̬���ã�Ϊ��ͳһ���������һ�µ�
enum {
	VIDEO_OPERATOR_CLSOE			=	0,			//�ر�״̬
	VIDEO_OPERATOR_OPEN				=	1,			//��״̬
	VIDEO_OPERATOR_RESUME 			=	2,			//ȡ����ͣ״̬
	VIDEO_OPERATOR_PAUSE			=	4,			//��ͣ״̬
	VIDEO_OPERATOR_ERROR			=	5,			//����״̬
};

/**< ͼ����ת������ */
enum
{
    VIDEO_ROTATE_0   = 0  ,  						//��Ƶ����ת
    VIDEO_ROTATE_90  = 90 ,  						//��Ƶ��ʱ����ת90��
    VIDEO_ROTATE_180 = 180,  						//��Ƶ��ʱ����ת180��
    VIDEO_ROTATE_270 = 270   						//��Ƶ��ʱ����ת270��
};

//for VTM record
//ĳһ·��Ƶ¼�Ƶ������Ϣ
typedef struct ST_VideoRecord_Info
{
	TUP_CHAR*	cRecordFileName;				//¼���ļ���
	TUP_INT		iRecordFileNameLen;				//¼���ļ�������
	TUP_BOOL	bHighOrLow;						//�Ƿ��Ǹ����������ֻ���ڷ��ͷ����Դ�������������Խ��շ��˲�����Ч��
	TUP_INT		Width;							//��	(���ã�������MGW��VideoE����)
	TUP_INT		Height;							//��  (���ã�������MGW��VideoE����)
	TUP_INT		FrameRate;						//֡��(���ã�������MGW��VideoE����)
} VideoRecord_Info;

//////////////////��Ļ����ģ�鶨�岿��///////////////////////
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
#define AS_CBK_ERROR_UNKNOW				0x0000	//��Ļ�����쳣��Ϣ��ʼ
#define AS_CBK_ERROR_PDU_DATA			0x0001	//�յ��쳣RECT��Ϣ
#define AS_CBK_ERROR_CAP				0x0002	//�ɼ������쳣��Ϣ
#define AS_CBK_ERROR_GDI				0x0003	//GDI����쳣��Ϣ
#define AS_CBK_ERROR_CORE				0x0004	//CORE�쳣��Ϣ
//remote share action
#define	REMOTESHARE_ACTION_SHARE		0x0001
#define	REMOTESHARE_ACTION_STOP			0x0002
#define	REMOTESHARE_ACTION_REJECT		0x0003
//sharing camera
#define AS_CBK_CAMERA_GETINFO			0x00080001
//sharing state
#define AS_STATE_NULL					0x0000	//�޻
#define AS_STATE_VIEW					0x0001	//�ۿ��˹ۿ�
#define AS_STATE_START					0x0002	//����˹���
#define AS_STATE_PAUSE					0x0003	//�������ͣ
#define AS_STATE_PAUSEVIEW				0x0004	//�ۿ�����ͣ
//sharing sub state
#define AS_STATE_SUB_NORMAL				0x0000	//��ͨ״̬
#define AS_STATE_SUB_CONTROL			0x0100	//����״̬��δ���ã�
#define AS_STATE_SUB_ANNOTATION			0x0200	//��ע״̬
//sharing Type
#define AS_SHARINGTYPE_DESKTOP			0x0000	//share desktop
#define AS_SHARINGTYPE_APP				0x0001	//share applications
//sharing session
#define AS_SESSION_CONNECT				0x0000	//session������Ϣ
#define AS_SESSION_OWNER				0x0001	//�����ת����Ϣ
#define AS_SESSION_FLOWCONTROL			0x0002	//���ظ澯��Ϣ
//sharing channel type
#define AS_CHANNEL_TYPE_NULL			0x0000	//for NULL
#define AS_CHANNEL_TYPE_NORMAL			0x0001	//for PC
#define AS_CHANNEL_TYPE_LOW_QUALITY		0x0002	//for mobile device
#define AS_CHANNEL_TYPE_TP				0x0003	//for TV
//sharing session state
#define AS_SESSION_DISCONNECT			0x0000	//���ӶϿ�
#define AS_SESSION_CONNECTED			0x0001	//������ͨ
#define AS_SESSION_CONNECTING			0x0002	//������
//sharing privilege
#define AS_PRIVILEGETYPE_CONTROL		0x0001	//Զ�̿���Ȩ��
#define AS_PRIVILEGETYPE_ANNOTATION		0x0002	//��עȨ��
//sharing action
#define AS_ACTION_DELETE				0x0000
#define AS_ACTION_ADD					0x0001
#define AS_ACTION_MODIFY				0x0002
#define AS_ACTION_REQUEST				0x0003
#define AS_ACTION_REJECT				0x0004
#define AS_ACTION_DELETE_SPEC			0x0006
#define AS_ACTION_ADD_SPEC				0x0007
//sharing prop
#define AS_PROP_TIMEINTERVAL			0x0001	//֡ʱ��������λ��ms����ʽ��dword
#define AS_PROP_MAXBITRATE				0x0002	//���ƽ��������λ��Byte����ʽ��dword
#define AS_PROP_PICTUREQUALITY			0x0003	//ͼ����������λ���ٷֱȣ���ʽ��dword
#define AS_PROP_VIEW_SIZE				0x0006	//��ʾ����ߴ磬��λ��pixel����ʽ��size
#define AS_PROP_VIEW_ORIGIN_POINT		0x0007	//��ʾ������ˣ�δ���ã�����λ��pixel����ʽ��point
#define AS_PROP_DEFAULT_CAP_TYPE		0x0009	//��ȡ��ʽ����λ���ޣ���ʽ��dword
#define AS_PROP_VIEW_FACTOR				0x000a	//�ۿ������ű�������λ���ޣ���ʽ��double
#define AS_PROP_REMOTESCREEN_SIZE		0x000c	//����˳ߴ磬��λ��pixel����ʽ��size
#define AS_PROP_BORDER_SEARCH			0x000e	//�ڱ��޳����أ���λ���ޣ���ʽ��dword
#define AS_PROP_DUMP_DATA				0x000f	//��������dump��δ���ã�����λ���ޣ���ʽ��dword
#define AS_PROP_DATA_CHANNEL			0x0010	//��������ͨ������λ���ޣ���ʽ��dword
#define AS_PROP_DEFAULT_BORDER_WIDTH	0x0011	//Ĭ�ϱ߽��ȣ���λ��pixel����ʽ��dword�������<300
#define AS_PROP_FIRST_KEY_FRAME_DELAY	0x0012	//��֡�ӳ�ʱ�䣬��λ��ms����ʽ��dword
#define AS_PROP_REMOTE_PPI				0x0013	//�����PPI����λ���ޣ���ʽ��dword
#define AS_PROP_SAMPLING				0x0014	//�����²�����С���ʣ���λ���ޣ���ʽ��dword
#define AS_PROP_SHARING_RECT			0x0015	//�������򣬵�λ��pixel����ʽ��rect
#define AS_PROP_SCALE_QUALITY			0x0016	//�Ŵ���������λ���ޣ���ʽ��dword
#define AS_PROP_CONTROL_TIMEINTERVAL	0x0017	//Զ�̿���ʱ֡�������λ��ms����ʽ��dword	
#define AS_PROP_COLOR_SPACE				0x0018	//�������ɫ��ʽ����λ���ޣ���ʽ��dword
#define AS_PROP_P2P_COUNT				0x0019	//P2P������ֵ����λ��������ʽ��dword

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
#define AS_LOCK_SCREENDATA_LOCK			0x0000	//��������				
#define AS_LOCK_SCREENDATA_UNLOCK		0x0001	//��������
//border delete
#define AS_BORDER_SEARCH_OFF			0x0000	//�رպڱ��޳�				
#define AS_BORDER_SEARCH_ON				0x0001	//�����ڱ��޳�
//switch
#define AS_SWITCH_OFF					0x0000	//�ر�������				
#define AS_SWITCH_ON					0x0001	//����������
//data channel
#define AS_DATA_CHANNEL_NORMAL			0x0000	//AS�������ݶ���ͨ��	
#define AS_DATA_CHANNEL_SESSION			0x0001	//AS�������ݹ��ÿ�������ͨ��
//screen data information mask
#define SH_SCREEN_DATA_INFO_MASK_BORDER	0x0001
#define SH_SCREEN_DATA_INFO_MASK_UPDATE	0x0002

typedef struct tagASParam{
	TUP_UINT32	ulPorpType;			//��������
	TUP_UINT32	ulDataLen;			//�������ݳ���
	TUP_VOID*	pData;				//��������
}TC_AS_PARAM;

typedef struct tagASWndInfo{
	TUP_VOID*		hWnd;			//Ӧ�ó��򴰿ھ��
	TUP_UINT16		*pWndTitle;		//��������
	TUP_VOID*		hSmallIcon;		//ICONͼ��Handle
	TUP_BOOL		bChecked;		//�Ƿ�ѡ��
}TC_AS_WndInfo;

typedef struct tagASSScreenData{
	TUP_UINT8			ucDataType;		//��Ļ���ݸ�ʽ
	TUP_VOID*			pUpdateInfo;	//������չʹ��
	TUP_VOID*			pData;			//��Ļ����
}TC_AS_SCREENDATA;

typedef struct tagASSScreenDataInfo{
	TUP_UINT8			dwDataType;		//��Ч�ֶα�־λ
	TUP_INT				rcBorder[4];	//�ڱ�λ��
	TUP_INT				rcUpdate[4];	//�������򣬴���չ
}TC_AS_ScreenDataInfo;

typedef struct tagASMouseEvent{
	TUP_UINT32	ulEventFlag;	//��Ϣ�¼�type
	TUP_UINT32	ulParam;		//��Ϣ�¼�wParam
	TUP_LONG	lParam;			//��Ϣ�¼�lParam
}TC_AS_MouseEvent;

////////////////////////////////// �ĵ�����ģ�鶨�岿�� ////////////////////////////
#define	dsNullID	((TUP_UINT32)(0))
#define dsNullOffset ((TUP_UINT32)(-1))

typedef struct tagAnno_Resource_Item
{
	TUP_UINT16 resIndex;			//�Զ����ע��Դ����
	TUP_UINT16 reserved;			//������
	TUP_VOID* pData;			//�Զ����ע����
	TUP_UINT32 dataLen;			//�Զ����ע���ݳ���
	TUP_INT format;				//�Զ����ע��ʽ
	TUP_UINT16 picWidth;			//ͼƬ���
	TUP_UINT16 picHeight;			//ͼƬ�߶�
	TC_POINT ptOffset;
} Anno_Resource_Item;


#define DS_OPTION_QUALITY	1		//��������
#define DS_OPTION_SIZE		2		//��������
#define DS_OPTION_DOUBLE	3		//˫����ʽ EMF+JPG


//����ҳ���ע������
#define DS_ANNOT_TYPE_LASERPOINTER	11 // Like laser pointer which moves as mouse moves
#define	DS_ANNOT_TYPE_DRAWING   	12 // Hilight belongs to drawing
#define	DS_ANNOT_TYPE_CUSTOMER		13 	
#define	DS_ANNOT_TYPE_TEXT			14


//����ҳ���ע��������
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
#define DS_ZOOM_PAGESIZE	1	//ʵ�ʴ�С��������
#define DS_ZOOM_DISPSIZE	2	//��ʾ�����С
#define DS_ZOOM_FITWIDTH	3	//��Ӧ��ʾ���
#define DS_ZOOM_PERCENT		4	//��ʵ�ʰٷֱ�����

typedef enum
{
	DsRotateFlipBase	 = 0,

	DsRotateNoneFlipNone = 0,	//δ��ת��δ��ת
	DsRotate90FlipNone  = 1,	//��ת90�ȣ�δ��ת
	DsRotate180FlipNone = 2,	//��ת180�ȣ�δ��ת
	DsRotate270FlipNone = 3,	//��ת270�ȣ�δ��ת

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
	TUP_UCHAR bWb;	//�Ƿ�װ壬0���ĵ���1���װ�
	TUP_UCHAR reserved;
	TUP_UINT32 currentPage;	//���ĵ��ĵ�ǰҳ
}DsDocInfo;

//ҳ����Ϣ����
typedef struct {
	TUP_INT width;				//ҳ���
	TUP_INT height;				//ҳ���
	TUP_INT orgX;				//��ʾ���X
	TUP_INT orgY;				//��ʾ���Y
	DsRotateFlipType rfType;	//��ҳ�����ת����
	TUP_UINT16 zoomPercent;		//��ǰ�ĵ����������£���ҳ����ʾʱ�����ű���
	TUP_UCHAR bCopied;	//�Ƿ��Ǹ��Ƶ�ҳ�棺0��1��
	TUP_UCHAR bEPenDrawn;	//�Ƿ񱻵��ӱʻ�����0��1��
	float floatZoomPercent;	//��ȷ���ĵ����ű���
	TUP_INT pageNo;				//ҳ��
}DsPageInfo;

//�ĵ�ͬ����Ϣ����
typedef struct {
	TUP_UINT32 docId;				//�������ϵĵ�ǰ�ĵ�ID
	TUP_UINT32 pageId;				//�������ϵĵ�ǰҳID
	TUP_INT width;					//��ǰҳ�Ŀ�
	TUP_INT height;					//��ǰҳ�ĸ�
	TUP_INT orgX;					//�������ϵĸ�ҳ���X
	TUP_INT orgY;					//�������ϵĸ�ҳ���Y
	DsRotateFlipType rfType;	//�������ϵĸ�ҳ��ת����
	float zoomPercent;			//��ҳ�����ű���
	TUP_UCHAR bCopied;		//��ҳ�Ƿ��Ƶ�ҳ
	TUP_UCHAR bEPenDrawn;	//��ҳ�Ƿ񱻵��Ӱװ廭��
}DsSyncInfo;

//annotation hittest mode
#define DS_HITTEST_MODE_ALL				0		//�����ڵ�ȫ��annot,
#define DS_HITTEST_MODE_OTHERS			1		//��ĳ�����ȫ��annot
#define DS_HITTEST_MODE_SOMEONE			2		//ĳ�˵�annot
//���������ģʽ��Ӧ���������ģʽ����֮ͬ����������ĻὫ���������ڵı�עȫ�����أ�����û��ָ��DS_ANNOT_FLAG_CANBESELECTED���Եı�ע
//ֻ��hittest2�ӿ��������ã���Ҫ��hittest�ӿ���ʹ��
#define DS_HITTEST_MODE_ALL_FORCE		3		//�����ڵ�ȫ��annot
#define DS_HITTEST_MODE_OTHERS_FORCE 	4		//��ĳ�����ȫ��annot
#define DS_HITTEST_MODE_SOMEONE_FORCE	5		//ĳ�˵�annot


//annotation select mode
#define DS_SELECT_MODE_UNSELECT		0		//ȡ��ѡ��
#define DS_SELECT_MODE_ALL			1		//ȫѡ
#define DS_SELECT_MODE_OTHERS		2		//ѡ���ĳ��֮���
#define DS_SELECT_MODE_SOMEONE		3		//ѡ��ĳ���û���

typedef struct {
	TC_POINT pt;
} CreateDrawingData;


#define DS_PIC_FORMAT_JPG	1000
#define DS_PIC_FORMAT_PNG	1001
#define DS_PIC_FORMAT_BMP	1002

typedef struct tagCreateCustomerData
{
    TUP_UINT16 bLocal;            //�Ƿ񱾵ػ�ͼƬ�����ɿͻ��˹̻����������Ҫ�������紫�䣩,0��ʾ��ͨͼƬ��1��ʾ���ػ�ͼƬ
    TUP_UINT16 localIndex;        //��bLocalΪ1ʱ��Ч����ʾ��Ӧ�ı��ػ�ͼƬ�����������������ڵײ����ϲ�ȡ����
    TUP_INT picFormat;          //��bLocalΪ0ʱ��Ч����ʾͼƬ��ʽ
    TUP_VOID* pData;            //��bLocalΪ0ʱ��Ч�������ͨͼƬ�����ݣ�bLocalΪ1ʱ������ΪNULL
    TUP_UINT32 dataLen;         //��bLocalΪ0ʱ��Ч�����ͼƬ���ݵĳ���
    TUP_INT picW;               //��bLocalΪ0ʱ��Ч��ͼƬ��
    TUP_INT picH;               //��bLocalΪ0ʱ��Ч��ͼƬ��
    TC_RECT2 dispRect;      //ͼƬ��ʾ����
    TC_POINT ptOffset;      //�����ͼƬ���Ͻǵ�ƫ�ƣ�TWIPΪ��λ����������ʱ���ڼ���ͼƬλ�õĲ��յ�
} CreateCustomerData;


typedef struct tagAnnotationConfig
{
    TUP_INT bSelfLpNotDisp;     //�Ƿ���Ⱦ�Լ��ļ���㣬Ϊ0ʱ��ʾ��Ⱦ��Ϊ1ʱ�ײ㲻��Ⱦ���ϲ���Ҫ�Լ���ʾ�����
} AnnotationConfig;

typedef struct tagDsDrawDataNotify
{
    TUP_VOID* pData;			//����
    TUP_INT nWidth;				//���
    TUP_INT nHeight;			//�߶�
    TC_RECT2* drawRect;			//
} DsDrawDataNotify;


//��ע����
#define  DS_ANNOT_FLAG_EXCLUSIVE			0x01 // �����ģ�Ψһ��
#define  DS_ANNOT_FLAG_EXCLUSIVEPERUSER		0x02 // ÿ���û�Ψһ��
#define	 DS_ANNOT_FLAG_OUTLINEFEEDBACK		0x04 // ������������ʾ��ע���߿�û�д˱�־����ʾʵ�ʱ�ע
#define  DS_ANNOT_FLAG_FIXEDSIZE			0x08 // �̶���С�ģ��������Ÿı��С
#define	 DS_ANNOT_FLAG_CANBESELECTED		0x10 // ���Ա�ѡ��
#define  DS_ANNOT_FLAG_CANBEMOVED			0x20 // ���Ա��ƶ�
#define  DS_ANNOT_FLAG_PAGEFRAME			0x40 // �װ��Ե�ı߿����⣬�ⲿ��Ҫ�ã�

//�û��Զ����ע���ͣ��Զ�������Ͷ���AnnotCustomer��������
typedef struct tagDsDefineAnnot
{
	TUP_UINT16 extendType;
	TUP_UINT16 flag;
}DsDefineAnnot;

/* Brush Styles */
#define	DS_BRUSH_STYLE_NULL			0		//�ջ�ˢ
#define	DS_BRUSH_STYLE_SOLID		1		//ʵ�廭ˢ
#define	DS_BRUSH_STYLE_GRADIENT		2		//���仭ˢ
#define	DS_BRUSH_STYLE_HATCH		3		//��Ӱ��ˢ
#define	DS_BRUSH_STYLE_PATTERN		4		//ͼ�λ�ˢ


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
	TC_RECT2*   bounds;		//��Ӿ���
	TUP_UINT8*      pString;	//utf8�ַ���
	TUP_UINT8*      pFont;		//������
	COLORRGBA   color;		//������ɫ
	TUP_UINT16        size;		//�����С
	TUP_UINT16        reserve;	//�ֽڶ��룬����
}DsAnnotTextInfo;

typedef struct {
	TC_RECT2		bounds;		//��Ӿ���
	TUP_UINT16		type;		//��ע����
	TUP_UINT16		subtype;	//��ע������
	TUP_UINT32		creator;	//������user id
	TUP_UINT16		flag;		//����
}DsAnnotInfo;

typedef struct {
	TUP_INT			style;		//�ߵ���ʽ
	COLORRGBA		color;		//������ɫ
	TUP_INT			width;		//���ʿ��
}DsPenInfo;

typedef struct {
	TUP_INT			style;		//ˢ����ʽ
	COLORRGBA		color;		//ˢ����ɫ
}DsBrushInfo;

#define DS_PEN_TYPE_NORMAL		1	//��ͨ����
#define DS_PEN_TYPE_HILIGHT		2	//��������

typedef enum {
	SUR_OUTPUT_HDC,			//windows only
	SUR_OUTPUT_HBITMAP		//windows only
}SurfaceOutputFormat;

//��ʾģʽ
typedef enum {
	DS_DISP_MODE_FREE,		//default mode
	DS_DISP_MODE_CENTER,	//������ʾ����ʱ����Ӧsetdisporg

	DS_DISP_MODE_COUNT		//�޺��壬ֻ�Ǳ�ʾ��ʾģʽ����
}DsDispMode;

//�����ĵ�����ID,10000���ڵ�IDԤ�����ײ�ʹ��,
//10000���ϵ���Ϊ�û��Զ�������,�ײ��ṩ����ʹ��������,����������δ�����Ӧ�ò����
typedef enum {
	DOCPROP_SYSTEM_BASE     = 0,
    DOC_PROPERTY_FULLNAME   = 1,	// �ĵ�ȫ·������
    DOC_PROPERTY_ORDER      = 2,	// �ĵ����
    DOC_PROPERTY_COMPLETE   = 3,	// �ĵ��Ƿ���ɼ���
	DOC_PROPERTY_TYPE		= 4,	// ����ֵΪ1ʱΪJPEG������ΪEMF
	DOC_PROPERTY_DATA_READY = 5,	// �ĵ��Ƿ�������׼����

	DOCPROP_USER_BASE       = 10000
}DocProperty;

//����ҳ������ID,10000���ڵ�IDԤ�����ײ�ʹ��,
//10000���ϵ���Ϊ�û��Զ�������,�ײ��ṩ����ʹ��������,����������δ�����Ӧ�ò����
enum {
	PAGEPROP_SYSTEM_BASE    = 0,
	PAGEPROP_TITLE,

	PAGEPROP_USER_BASE      = 10000,
};


#endif