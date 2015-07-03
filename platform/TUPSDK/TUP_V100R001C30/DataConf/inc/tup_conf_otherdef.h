#ifndef _TUP_CONF_OTHERDEF_H_
#define _TUP_CONF_OTHERDEF_H_

#include "tup_conf_basedef.h"


#if defined(MY_ANDROID) && (defined(TEST_8950) || !(defined CONF_IPPHONE))
typedef TUP_VOID (TUP_STDCALL *conference_callback)(TUP_INT nType, TUP_INT nValue1, TUP_LONG nValue2, TUP_VOID* pMsg, TUP_VOID* pContext, TUP_INT nSize);	
#else
typedef TUP_VOID (TUP_STDCALL *conference_callback)(TUP_INT nType, TUP_INT nValue1, TUP_LONG nValue2, TUP_VOID* pVoid, TUP_INT nSize); 
#endif

typedef TUP_VOID (TUP_STDCALL *component_callback)(TUP_INT nType, TUP_INT nValue1, TUP_LONG nValue2, TUP_VOID* pVoid, TUP_INT nSize);    //����Ļص�����

// URL��ȡ��Ϣ�ṹ
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
// �����������Ͷ���


//////////////////////////////////////////////////////////////////////////
// Phone config info
//   sess_flag:
#define TC_SESS_FLAG_PHONE_ALONE	0x0
#define TC_SESS_FLAG_AUDIO_MIX		0x1
#define TC_SESS_FLAG_VIDEO_MIX		0x2
#define TC_SESS_FLAG_AV_MIX		    0x3
#define TC_MRS_AUDIO				0x4
#define TC_MRS_VIDEO				0x8


typedef struct tag_phone_config_info		/*�绰�������ò���*/
{
	TUP_CHAR    conf_num[TC_MAX_PHONE_CONF_NUM_LEN];   // �绰�����
	TUP_CHAR    conf_id[TC_MAX_PHONE_CONF_NUM_LEN];    // ���ݻ����
	TUP_CHAR    host_pwd[TC_MAX_PHONE_PASS_CODE_LEN];  // �绰����������
	TUP_CHAR    server_url[TC_MAX_PHONE_SVR_URL_LEN];	//���ص�ַ��IPT2.2��ѡ
	TUP_UINT8   sess_flag;                             // �绰����
	TUP_UINT16  attendee_num;                          // �绰�᳡�������

#ifdef __cplusplus
	tag_phone_config_info()
	{
		memset(this, 0 , sizeof(tag_phone_config_info));
	}
#endif
} PHONE_CONFIG_INFO;

//////////////////////////////����ģ�鶨�岿��//////////////////////////////////

#define  GROUP_MAX_LEN                   32			//��������󳤶�
#define  CHAT_MIN_TIME_INTERVAL          200		//��������Ϣʱ�����ʱ���� ��λ����
#define  CHAT_MAX_MSG_LEN                48*1024    //�������Ϣ�ĳ��� 48KB

//��Ϣ���
enum{
	CHAT_TYPE_PUBLIC,		//����
	CHAT_TYPE_GROUP,		//����
	CHAT_TYPE_PRIVATE		//˽��
};
/**************************************************************************/
/*onGroupInfoModifiedInd �ص�
 �鳤���룬�鳤������ԭ�г�Ա���������Ϣ�ص��� Reason = REASON_GROUP_USER_ADD
 �鳤���ˣ��鳤�����ڲ����ߵ���Ա���������Ϣ�ص���Reason = REASON_GROUP_USER_DEL
/**************************************************************************/
enum
{
	REASON_GROUP_USER_NULL,
	REASON_GROUP_USER_ADD,	
	REASON_GROUP_USER_DEL
};

/**************************************************************************/
/*  ��Ա����ԭ��
/**************************************************************************/
enum
{
	REASON_LEAVE_GROUP_SELF,
	REASON_LEAVE_GROUP_KICKED,
	REASON_LEAVE_GROUP_OTHER
};

struct TC_CHAT_MSG	/*������Ϣ����*/
{
	TUP_INT		nMsgType;							//��Ϣ���� �����ģ�CHAT_TYPE_PUBLIC�������ģ�CHAT_TYPE_GROUP����˽�ģ�CHAT_TYPE_PRIVATE��
    TUP_UINT32	nFromUserid;						//��Ϣ�����û���ID
	TUP_UINT16	nSequenceNmuber;					//������Ϣ���кţ�����Ϣ����Ϊ˽��������ʱ�����ֶ�Ϊ0
	TUP_INT		nFromGroupID;						//nMsgType==CHAT_TYPE_GROUPʱ���˲�������Ч����Ϣ���Ե��������ID
	TUP_CHAR*	lpMsg;								//��������
	TUP_UINT32	nMsgLen;							//�������ݳ���
	TUP_INT64	time;								//������Ϣʱ�ķ�����ʱ��
	TUP_CHAR	fromUserName[TC_MAX_USER_NAME_LEN];	//������Ϣ�û����û���
};

/*���������Ϣ*/
typedef struct  
{
	TUP_CHAR groupName[GROUP_MAX_LEN];			//������
	TUP_INT groupID;							//����ID
	TUP_UINT32 ownerID;							//�����ߵ�UserID
	TUP_UINT32* pUserIds;						//�����ڵĳ�Ա�б�
	TUP_UINT32 nUser;							//�����ڵĳ�Ա�б����
}TC_GROUP_INFO;


/////////////////�ļ�����ģ�鶨�岿��///////////////////////////
typedef struct {
	TUP_CHAR fileName[256];							//�����ļ�����ļ���
	TUP_CHAR filePathName[256];						//�����ļ�������ϴ����豸�ϵ�·���ļ���
	TUP_CHAR senderUserName[TC_MAX_USER_NAME_LEN];	//�����ļ�����ϴ��ߵ��û���
	TUP_INT senderUserId;							//�����ļ�����ϴ��ߵ��û�ID
	TUP_INT recieverUserId;							//�����ļ���Ľ����ߵ��û�ID
	TUP_UINT32 size;									//�����ļ�����ֽ���
	TUP_INT status;									//�����ļ����״̬��1-���ϴ���0-�����ϴ�
} TC_FILE_INFO;


///////////////////////////��Ƶģ�鶨�岿��////////////////////////////////////
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
 W  windowsƽ̨֧��
 I  IOSƽ̨֧��
 A  Androidƽ̨֧��
*/
typedef enum		//���������
{
	AUDIO_Codec_PCMA = 0,	//֧�ַ����������Ϳͻ��˻���
	AUDIO_Codec_PCMU,		//֧�ַ����������Ϳͻ��˻���   
 	AUDIO_Codec_AMR,		//�ݲ�֧��
 	AUDIO_Codec_AMRWB,		//�ݲ�֧��
 	AUDIO_Codec_G723,		//�ݲ�֧��
	AUDIO_Codec_G729,	//֧�ַ����������Ϳͻ��˻���
	AUDIO_Codec_iLBC,	//֧�ַ����������Ϳͻ��˻���
	AUDIO_Codec_G722,    
	AUDIO_Codec_Opus,	//ֻ֧�ֿͻ��˻���
	AUDIO_Codec_NUM		//	
}Audio_Codec_Format;

/*
Ĭ�ϱ����������  

2013/1/22  windowsƽ̨
��frameLen==0ʱ���ڲ���ȡ��ЩĬ������
Codec = PCMA, payload = 8, SampleFreq = 8000, iRate = 64000, iPacketSize = 160    
Codec = PCMU, payload = 0, SampleFreq = 8000, iRate = 64000, iPacketSize = 160    
Codec = AMR, payload = 109, SampleFreq = 8000, iRate = 12200, iPacketSize = 160   
Codec = AMRWB, payload = 110, SampleFreq = 16000, iRate = 23850, iPacketSize = 320
Codec = G723, payload = 4, SampleFreq = 8000, iRate = 6300, iPacketSize = 240     
Codec = G729, payload = 18, SampleFreq = 8000, iRate = 8000, iPacketSize = 160    
Codec = iLBC, payload = 98, SampleFreq = 8000, iRate = 15200, iPacketSize = 160   
Codec = opus, payload = 112, SampleFreq = 48000, iRate = 64000, iPacketSize = 960 
*/

typedef struct tagTC_AUDIO_PARAM		//��Ƶ��������
{
	MIX_METHOD			MixMethord;		//�ͻ��˻��� = 1; ���������� = 2;
	TUP_INT				frameLen;		//Ĭ��30ms;��ȡֵΪ0��ʱ�򣬲�ȡĬ�����ã����ϣ�
	TUP_INT				sampleRate;		//Ĭ��8000;
	Audio_Codec_Format	codecName;		//Ĭ�Ͽͻ��˻��� = AUDIO_CODEC_iLBC; ���������� = AUDIO_CODEC_PCMA;
	TUP_INT				EC;				//Ĭ��3; 0���رջ��������㷨;1:ѡ��AEC�㷨ʱ����ʾ��������ʼ��Ϊ�Զ�ģʽ;2:ѡ��AEC�㷨ʱ����ʾ����ģʽ���ʺ϶���ͨ����ģʽ;3:ѡ��AEC�㷨ʱ����ʾ��Ͳģʽ���ʺ�����ͻ�Ͳͨ����ģʽ
	TUP_INT				AGC;			//Ĭ��1;�Զ�������� 0:AGC���ܹر�; 1:����AGC����ģʽ; 2:����AGCģ��ģʽ
	TUP_INT				NR;				//Ĭ��4;�Զ��������� support[0-4]
	TUP_INT             enableTrace;    //�Ƿ񱣴�trace
	TUP_INT				logLevel;		//Ĭ��0x02;��ӡ��־��־, 0x00:����ӡ��־, 0x01:����, 0x02:��ʾ
	TUP_INT				logSize;		//Ĭ��100;��־�ļ���С����λM
	TUP_CHAR			pDLLAddr[NHME_MAX_FILE_PATH];//Ĭ�ϵ�ǰ·������̬��λ��
	TUP_CHAR			pLogPath[NHME_MAX_FILE_PATH];//Ĭ�ϵ�ǰ·����������־��λ��
	TUP_CHAR            cTraceFilePath[NHME_MAX_FILE_PATH];// Trace����·��
	TUP_UINT32			timeSpan;		//ֻ�ڿͻ��˻���ģʽ����Ч������������ͨ��ʱ��������λ��s��
	TUP_CHAR            UAPInfo[128];//����UAP�������Ϣ��ʽΪ: ������ @ ����� @ �������� @ UAP��ַ
}TC_AUDIO_PARAM;

typedef enum{
	AUDIO_OPEN_MIC	=	1,
	AUDIO_CLOSE_MIC,
	AUDIO_MUTE_MIC,
	AUDIO_UNMUTE_MIC,
	AUDIO_PRIVATE_CHAT_ENTER,
	AUDIO_PRIVATE_CHAT_LEAVE,

	AUDIO_OPEN_MIC_TP,	//��������Ĳ���
	AUDIO_CLOSE_MIC_TP,	//��������Ĳ���

	AUDIO_OPEN_SPEAKER_TP,	//��������Ĳ���
	AUDIO_CLOSE_SPEAKER_TP,	//��������Ĳ���
}Audio_CMD;

//��Ƶ�豸����
enum
{
	AUDIO_MIC  =  0,
	AUDIO_SPEAKER
};

//��Ƶ�豸״̬
enum 
{
	AUDIO_STATUS_OPEN = 0,
	AUDIO_STATUS_CLOSE,
	AUDIO_STATUS_MUTE,
	AUDIO_STATUS_NO_DEVICE
};

//��������
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
	TUP_CHAR speakID[32];//˵���ߵ�ID

}SpeakingUser;

//by s00209224  2012/1/29
//��ΪĳЩ�쳣������ܴ���ͬ�����豸�����Ȳ�λص������и��¡��ϲ�Ӧ�ò��ع�ע�˽ṹ�� 
//��Ƶ�Ȳ�� 
 typedef struct tag_HotPlug
 {
 	TUP_UINT32 deviceID; //�豸ID
 	TUP_INT deviceType; //�豸����AUDIO_MIC=0�� AUDIO_SPEAKER=1
 	TUP_INT iActionEvent;//0 ��, 1 ��
 }HotPlug;


#ifdef __APPLE__
/*************************************************************************************************/
// ·������ö��    ��Ӧ��conf_audio_open_speaker�е� �豸ID
/* �ƶ��豸(IOS)·������ */
enum 
{
	TC_AUD_DEV_ROUTE_DEFAULT       = 0x0,   //���϶�����Ĭ��Ϊ��������֮Ϊ��Ͳ
	TC_AUD_DEV_ROUTE_LOUDSPEAKER   = 0x1,   //������
	TC_AUD_DEV_ROUTE_BLUETOOTH     = 0x2,   //����
	TC_AUD_DEV_ROUTE_EARPIECE      = 0x3,   //��Ͳ�����ڻ�ȡ������ʱ���������ش���
	TC_AUD_DEV_ROUTE_HEADSET       = 0x4    //���������ڻ�ȡ������ʱ���������ش���
};
#endif


/***********************¼��ģ�鶨�岿��*****************************/

/***��Ƶ�����ʽ***/
typedef enum tag_RECORD_VIDEO_CODEC
{
	VIDEO_CODEC_NULL = 0,
	VIDEO_CODEC_RGB24
}RECORD_VIDEO_CODEC;

/***��Ƶ¼�Ƶ�֡��***/
enum
{
	Record_Video_FPS_1 = 1,
	Record_Video_FPS_2 = 2,
	Record_Video_FPS_3 = 3,
	Record_Video_FPS_4 = 4,
	Record_Video_FPS_5 = 5
};

/***��Ƶ¼�Ƶı�����***/
enum
{
	Record_Video_BitRate_LOW = 300000,
	Record_Video_BitRate_MID = 400000,
	Record_Video_BitRate_HIG = 500000
};

typedef struct tagVideoRecordParam
{
	RECORD_VIDEO_CODEC codec;		//�����
	TUP_UINT32 uiFrameRate;			//֡��
	TUP_UINT32 uiBitrate;			//������
    TUP_INT quality;                //����0-100
}VideoRecordParam;

/***��Ƶ�����ʽ***/
typedef enum tag_RECORD_AUDIO_CODEC
{
	AUDIO_CODEC_NULL = 0,
	AUDIO_CODEC_PCMA
}RECORD_AUDIO_CODEC;

/***��Ƶ¼��channel��***/
enum
{
	Record_Audio_Channel_Single = 1
};

/***��Ƶ¼�ƵĲ�����***/
enum
{
	Record_Audio_SampleRate_8000 = 8000
};

/***��Ƶ¼�Ʋ���λ��***/
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

/***¼��״̬***/
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

	//˵�������Խ������RECORD_MODE_AUDIO_INTER��RECORD_MODE_AUDIO_OUTER����ͬʱ��
};

/***********************ý�干��ģ�鶨�岿��************************/

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

////////////////////////ͶƱģ�鶨�岿��////////////////////////////////

#define POLLING_INVALID_ID -1
typedef enum {
	QTYPE_SINGLE_CHOICE,	//��ѡ��
	QTYPE_MULTI_CHOICE,		//��ѡ��
	QTYPE_QA,				//�ʴ���
	QTYPE_ERROR,

	QTYPE_COUNT
}QuestionType;


typedef struct {
	TUP_UINT32 id;
	TUP_VOID* pData;
	TUP_INT dataLen;
}ParamUpdateData;


/*******************************SVN������ض���***************************************/

/* �������� */
#define TC_SVN_PROXY_NONE      0      /* ��ʹ�ô���*/
#define TC_SVN_PROXY_HTTP      1      /* ʹ��HTTP���� */
#define TC_SVN_PROXY_SOCKS5    2      /* ʹ��SOCK5���� */
#define TC_SVN_PROXY_UNKNOWN   3      /* ʹ��δ֪���� */

/* �ͻ���֧�ֵ������������Ϣ */
#define TC_SVN_MAX_PROXY_URL_LEN               128     /* ���������IP��󳤶� */
#define TC_SVN_MAX_PROXY_USERNAME_LEN          256     /* �����û�����󳤶� */
#define TC_SVN_MAX_PROXY_USERPWD_LEN           256     /* ����������󳤶� */
#define TC_SVN_MAX_PROXY_DOMAIN_LEN            128     /* ������󳤶� */

/* ������Ϣ */
typedef struct tagTcSVNProxyInfo
{
	TUP_CHAR            acProxyUrl[TC_SVN_MAX_PROXY_URL_LEN];              /* ���������IP��ַ������ */
	TUP_UINT16			usProxyPort;									/* ����������˿� */
	TUP_UINT16			usProxyType;                                    /* �������ͣ�TC_SVN_PROXY_NONE/TC_SVN_PROXY_HTTP/TC_SVN_PROXY_SOCKS5 */
	TUP_CHAR            acProxyUserName[TC_SVN_MAX_PROXY_USERNAME_LEN];    /* �����û��� */
	TUP_CHAR            acProxyPassword[TC_SVN_MAX_PROXY_USERPWD_LEN];     /* �������� */
	TUP_CHAR            acProxyDomain[TC_SVN_MAX_PROXY_DOMAIN_LEN];        /* ��֤���� */
} TC_SVN_PROXY_INFO_S;

/* SVN����֧�ֵ�����û��������볤�� */
#define TC_SVN_MAX_USERNAME_LEN            64      /* SVN�����û�����󳤶� */
#define TC_SVN_MAX_USERPWD_LEN             32      /* SVN����������󳤶� */
#define TC_SVN_MAX_URL_LEN                 128     /* ����������󳤶� */

/* �������ģʽ*/
#define TC_SVN_TUNNEL_MODE_DTLS            0       /* ���ģʽDTLS */
#define TC_SVN_TUNNEL_MODE_TLS             1       /* ���ģʽTLS */
#define TC_SVN_TUNNEL_MODE_UDP             2       /* ���ģʽUDP */
#define TC_SVN_TUNNEL_MODE_UDPS            3       /* ���ģʽTLS + UDPS */

/*ע����Ϣ*/
typedef struct tagTcSVNRegisterInfo
{
	TUP_CHAR                  acServerURL[TC_SVN_MAX_URL_LEN];       /* ���ص�ַ�����磺9.1.1.3 �� www.abc.com */
	TUP_UINT16        usServerPort;							/* ���صĶ˿� */
	TUP_UINT16        usTunnelMode;							/* ���ģʽ */
	TUP_CHAR                  acUserName[TC_SVN_MAX_USERNAME_LEN];   /* ע��SVN�����û��� */
	TUP_CHAR                  acPassword[TC_SVN_MAX_USERPWD_LEN];    /* ע��SVN��������  */
	TC_SVN_PROXY_INFO_S   stProxyInfo;							/* ������Ϣ�ṹ */
} TC_SVN_REGISTER_INFO_S;

/**********************************svn�������********************************************************/

#endif