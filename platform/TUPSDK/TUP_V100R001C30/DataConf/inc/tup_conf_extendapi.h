#ifndef _TUP_CONF_EXTENDAPI_H_
#define _TUP_CONF_EXTENDAPI_H_

#include "tup_conf_extenddef.h"

#ifdef __cplusplus
	extern "C" {
#endif
	/*************************���鲿��*************************/
	/*****************************************************************************
	�� �� ��  : tup_conf_setiplist
	��������  : ����MS��ַ�б�
	�������  : handle: ������
				svrlist: IP�б�,'|'��';'�ָ���磺192.168.1.1|192.168.1.2
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_setiplist(CONF_HANDLE handle, const TUP_CHAR * svrlist);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_setipmap
	��������  : ���÷�����IP��ַӳ���
	�������  : handle: ������
				pnatmap��ӳ�������ָ��
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_setipmap(CONF_HANDLE handle,IP_NAT_MAP* pnatmap,TUP_UINT32 count);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_setconfig
	��������  : ������������
	�������  : handle: ������
				pconfig: ����������Ϣ
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_setconfig(CONF_HANDLE handle, const TC_CONF_INIT_CONFIG* pconfig);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_set_qos_option
	��������  : ����QoS���������ݷ��Ϳ���ѡ������ݷ������ȼ���ֵ
	�������  : handle: ������
				datatype: �������ͣ�ö��ֵ��QOS_TYPE_AUDIO��QOS_TYPE_VIDEO��QOS_TYPE_DATA
				nvalue: QOSֵ�����紫��������
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_set_qos_option(CONF_HANDLE handle, TUP_UINT32 datatype,TUP_UINT32 nvalue);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_log_delete
	��������  : ɾ��������ǰ����־��������ָ����������־
	�������  : nDay: Ԥ����־�������������磬���nDayΪ1������������־��				
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_log_delete(TUP_UINT32 nDay);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_get_server_time
	��������  : ��ȡ������ʱ��
	�������  : handle: ������				
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : CONF_MSG_SERVER_TIME
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_get_server_time(CONF_HANDLE handle);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_flowcontrol_limit
	��������  : ƽ�����͸����������͵Ĵ������
	�������  : handle: ������
				datatype:�������ͣ��ο�LIMIT_DATA_TYPEö��ֵ
				limitsize: ���ݴ�С����λ��Bytes/s
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_flowcontrol_limit(CONF_HANDLE   handle, TUP_UINT32 datatype,TUP_UINT32 limitsize); 
	
	/*****************************************************************************
	�� �� ��  : tup_conf_user_update_info
	��������  : �����û���չ��Ϣ
	�������  : handle: ������
				userid: �û�ID
				pUserInfo: �û���Ϣ
				nInfoLen: �û���Ϣ����
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_USER_ON_MODIFY_IND
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_user_update_info(CONF_HANDLE handle,TUP_UINT32 userid,TUP_UINT8* pUserInfo,TUP_UINT16 nInfoLen);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_send_data
	��������  : �������ݣ�����useridΪ0��Ϊ�㲥���ݡ��ýӿ���������ݹ㲥Ϊ8K��
				����ָ����Ϊ16K������ͨ���ýӿڷ����������ݣ������鷢�ʹ������
	�������  : handle: ������
				userid: �û�ID, 0Ϊ�㲥
				msg_id: �û��������ϢID��֧�ַ�Χ[0, 85]				
				pbuffer: ��������
				len: ���ݳ��ȣ���������ݹ㲥Ϊ8K������ָ����Ϊ16K
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_USER_ON_MESSAGE_IND
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_send_data(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT8 msg_id,TUP_UINT8 * pbuffer, TUP_UINT32 len);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_update_param
	��������  : ���������ȫ��Ψһ������������������ΪΨһ��ʶ
	�������  : handle: ������
				param_name: ȫ�ֲ�������
				pbuffer: ��������
				len: ���ݳ���
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_ON_MESSAGE_UPADATE
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_update_param(CONF_HANDLE handle,const TUP_CHAR * param_name, TUP_VOID* pbuffer, TUP_UINT16 len);


	/*************************��Ļ����߼��ӿ�*************************/
	/*****************************************************************************
	�� �� ��  : tup_conf_as_getapplist
	��������  : ��ȡ��ǰ�ĳ����б�
	�������  : handle: ������
	papplist:�����б�(TC_AS_WndInfo* ����)����ָ��
	pappcount: papplist�ĳ���
	�������  : papplist: ���صĳ����б�(TC_AS_WndInfo* ����)ָ��
	pappcount: ���س���ĸ���
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_getapplist(CONF_HANDLE handle, TC_AS_WndInfo *papplist , TUP_UINT32 *pappcount);

	/*****************************************************************************
	�� �� ��  : tup_conf_as_setsharingapp
	��������  : ������Ҫ����ĳ���
	�������  : handle: ������
	pappwnd: ��Ҫ�����Ĵ��ھ��
	action: �������͡�ȡֵ���Ƿ�ֵ����ʧ�ܣ���
	AS_ACTION_DELETE	ɾ������
	AS_ACTION_ADD		��Ӳ���
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_setsharingapp(CONF_HANDLE handle, TUP_VOID* pappwnd, TUP_UINT32 action);

	/*****************************************************************************
	�� �� ��  : tup_conf_as_setparam
	��������  : ������Ļ�����Ӧ�ó�������ز���
	�������  : handle: ������
				param: �����ṹ��
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_setparam(CONF_HANDLE handle,TC_AS_PARAM* param);	
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_getparam
	��������  : ��ȡ��Ļ�����Ӧ�ó�������ز���
	�������  : handle: ������
				param: ������Ҫ��ȡ���������
	�������  : param: �����Ӧ������ֵ
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_getparam(CONF_HANDLE handle,const TC_AS_PARAM* param);	

		/*****************************************************************************
	�� �� ��  : tup_conf_as_startex
	��������  : ��ʼ���湲���Ӧ�ó����������ǰ�趨�ɼ���ʽΪAS_CAPTURE_MDʱ��
				�ýӿڲ��Ὣ���������������ǰ����û����������Ļ�����Զ�ת��
				AS_CAPTURE_GDI�ɼ���ʽ��	
	�������  : handle: ������				
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_startex(CONF_HANDLE handle);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_stopex
	��������  : ֹͣ���湲���Ӧ�ó����������ǰ�趨�ɼ���ʽΪAS_CAPTURE_MD��
				���������Կ������Ѿ�����ʱ���ýӿڲ��������������رգ�
	�������  : handle: ������				
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_stopex(CONF_HANDLE handle);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_pause
	��������  : ��ͣ���湲���Ӧ�ó�����
	�������  : handle: ������				
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_pause(CONF_HANDLE handle,TUP_BOOL pause);
	
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_flushscreendata
	��������  : ����ʱ���ڹۿ���ǿ��ˢ��һ֡
	�������  : handle: ������				
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_SCREEN_DATA
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_flush_screendata(CONF_HANDLE handle);	
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_senduserdata
	��������  : �����û��Զ�����Ϣ
	�������  : handle: ������
				datatype: �Զ�����Ϣ����
				userid: �û�ID,0Ϊ�㲥
				pbuffer: ��Ϣ����
				len: ��Ϣ���ݳ��ȣ���󳤶�AS_USERDEFINE_MSG_MAX_LEN
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_USERDEFINE_MSG
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_senduserdata( CONF_HANDLE handle,TUP_UINT32 datatype, TUP_UINT32 userid, TUP_VOID* pbuffer, TUP_UINT32 len );
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_lock_screen_data
	��������  : ������Ļ���ݣ�ʹ�ú���Ҫ����tup_conf_as_unlock_screen_data�ͷš��ú���ֻ��tup_conf_init���ö����߳�ģ���µ���
	�������  : handle: ������				
	�������  : pscreendata : ���ص���Ļ����
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_lock_screen_data(CONF_HANDLE handle,TC_AS_SCREENDATA* pscreendata);	
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_unlock_screen_data
	��������  : ������Ļ����
	�������  : handle: ������				
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_unlock_screen_data(CONF_HANDLE handle);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_attach
	��������  : ��Ļ�����У��ۿ��˼���ĳ������ͨ��
	�������  : handle: ������
				channel_type: ͨ�����͡�ȡֵ��
									AS_CHANNEL_TYPE_NORMAL			//��ǰֻ�и�ֵ��Ч
									AS_CHANNEL_TYPE_LOW_QUALITY
									AS_CHANNEL_TYPE_TP
				hwnd: ��չ����
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_ CHANNEL
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_attach(CONF_HANDLE handle, TUP_INT32 channel_type, TUP_VOID* hwnd);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_detach
	��������  : ��Ļ�����У��ۿ��˳�ĳ������ͨ��
	�������  : handle: ������
				channel_type: ͨ�����͡�ȡֵ��
									AS_CHANNEL_TYPE_NORMAL
									AS_CHANNEL_TYPE_LOW_QUALITY
									AS_CHANNEL_TYPE_TP				
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_ CHANNEL
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_detach(CONF_HANDLE handle, TUP_INT32 channel_type);

	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_settransparentwindow
	��������  : ������Ҫ��͸���Ĵ���
	�������  : handle: ������
				hwnd: ͸�����ھ����hwnd������Ч
				action: 
					AS_ACTION_DELETE//�ͷ�
					AS_ACTION_ADD//ӵ��
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_set_transparentwindow(CONF_HANDLE handle, TUP_VOID *hwnd, TUP_UINT32 action);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_request_keyframe
	��������  : ��Ļ����ۿ�������ȫ��֡
	�������  : handle: ������
				reason: ����ԭ�򣨱�����
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_request_keyframe(CONF_HANDLE handle, TUP_UINT32 reason);
	
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_getdisplayinfo
	��������  : ��ȡ��ʾ����Ϣ
	�������  : handle: ������				
	�������  : pdisplay_info:��ʾ����Ϣ 
				ret_count: ��pMonitorInfoΪ��ʱ����������
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_get_displayinfo(CONF_HANDLE handle, MonitorInfo* pdisplay_info,TUP_UINT32* ret_count);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_getdisplaythumbnail
	��������  : ��ȡ��ʾ������ͼ
	�������  : handle: ������
				index : ��ʾ������
				width: ����ͼ���
				height: ����ͼ�߶�
				pbuffer : ����ͼ�����ڴ�, ����ͼƬͷ��Ϣ
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_get_displaythumbnail(CONF_HANDLE handle, TUP_UINT32  index, TUP_UINT32  width, TUP_UINT32 height, TUP_UINT8* pbuffer);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_setsharingdisplayindex
	��������  : ���ù������Ļ
	�������  : handle: ������
				index : ��ʾ������
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_set_sharing_display(CONF_HANDLE handle, TUP_UINT32  index);



	/*********************************************��Ƶ�߼��ӿ�*********************************************/
	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_set_max_count
	��������  : ���û����������Ƶ����ȱʡֵ��6���������nMaxOpenVideoΪ0����ô
				�����ó�ȱʡֵ6�����ֵ16����һ�������У�ֻ�ܵ���һ�Σ�����������˵Ļ�������
				���˵���
	�������  : handle: ������
				max_count: ����������Ƶ��
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_VIDEO_ON_MAX_OPENVIDEO
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_set_max_count(CONF_HANDLE handle, TUP_UINT32 max_count);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_set_lowstream_resolution
	��������  : ������Ƶ˫��ʱ�����ķֱ��ʡ���ȱʡ�Ļ�����������ó�QQVGA��160*120����
	�������  : handle: ������				
				width: Ӧ�ò����õ����Ŀ�
				height: Ӧ�ò����õ����ĸ�
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_set_lowstream_resolution(CONF_HANDLE handle, TUP_UINT32 width, TUP_UINT32 height);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_set_encode_maxresolution
	��������  : ���ñ�������ֱ��ʣ����δ������ô�Ͳ���ȱʡֵ��WindowsϵͳΪ1920*1080��Android��IOS�汾Ϊ640*480
	�������  : handle: ������
				width: ��������ֱ��ʵĿ�
				height: ��������ֱ��ʵĸ�
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_set_encode_max_resolution(CONF_HANDLE handle, TUP_UINT32 width, TUP_UINT32 height);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_pause
	��������  : ��ͣ�Լ�����˵���Ƶ��
				�����ͣ�Լ�����Ƶ������ָͣ����Ƶ�豸�Ĳɼ����ܣ�
				�����ͣ�����û�����Ƶ���򲻽��ո��û�ָ����Ƶ�豸����Ƶ����
	�������  : handle: ������
				userid: �û�ID
				deviceid: ��ͣ��Ƶ���豸ID
				bwizard: TRUE��������ʱ����ͣ��FALSE�������ʱ����ͣ
				�����ڻ�������Ƶʱ������Ҫ�����´��ڵ�����Ƶ����ʱ�������е���Ƶ��Ҫ���øýӿ�����ͣ��bwizard��ΪTRUE
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_VIDEO_ON_SWITCH
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_pause(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_BOOL bwizard);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_resume
	��������  : ȡ����ͣ�Լ�����˵���Ƶ
	�������  : handle: ������
				userid: �û�ID
				deviceid: ��Ƶ���豸ID
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_VIDEO_ON_SWITCH
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_resume(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT32 deviceid);					

	/*****************************************************************************
	�� �� ��  : tup_conf_video_closeall
	��������  : �ر��Լ���������Ƶ
	�������  : handle: ������
				userid���û�ID
				deviceid����Ƶ���豸ID
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_VIDEO_ON_SWITCH
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_closeall(CONF_HANDLE handle);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_setcapture_rotate
	��������  : ������Ƶ��ת�ĽǶȣ�ֻ�������ƶ��汾��
	�������  : handle: ������
				deviceid: �豸ID
				rotate: �豸��ת�ĽǶ�
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_set_capture_rotate(CONF_HANDLE handle, TUP_UINT32 deviceid, TUP_INT32 nRotate);	
	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_snapshot
	��������  : ��Ƶ���չ��ܡ����豸��״̬ʱʹ�����չ��ܣ�����ֱ��ʲ�����һ��
				������Ƶ�ķֱ��������յķֱ��ʲ�ͬ�����豸����һ�������Ĺ���
	�������  : handle: ������
				deviceid: �豸ID
				filename: ͼƬ������ļ�·��
				vparam: ���ղ����ṹ��
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_snapshot(CONF_HANDLE handle, TUP_UINT32 deviceid, const TUP_CHAR* filename, TC_VIDEO_PARAM* vparam); 

	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_getdevicestatus
	��������  : ����鿴ĳһ�豸�ĵ�ǰ״̬��(�򿪣��رգ���ͣ)
	�������  : handle: ������
				userid: �û�ID
				deviceid: �豸ID
	�������  : ret_devicetatus: ĳһ����ĳһ�û����豸״̬���ο�VIDEO_OPERATOR_CLSOEö��ֵ
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_get_devicestatus(CONF_HANDLE handle,TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_UINT32* ret_devicetatus);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_getdevicebitrate
	��������  : ��ȡ��Ƶ����
	�������  : handle: ������
				userid: �û�ID
				deviceid: �豸ID
	�������  : vparam: ��Ƶ�����ṹ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_get_devicebitrate(CONF_HANDLE handle,TUP_UINT32 userid, TUP_UINT32 deviceid, TC_VIDEO_PARAM* vparam);

	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_show_deviceproperty
	��������  : ��ʾ�豸���ԶԻ���
	�������  : handle: ������
				userid: �û�ID
				deviceid: �豸ID
	�������  : parent_hwnd: ģ̬��(������)���
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_show_deviceproperty(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_VOID* parent_hwnd);
	
	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_preview_start
	��������  : ������Ƶ�򵼣��鿴�Լ���ĳһ�豸�Ƿ�����ĳһ�ֱ�������������
	�������  : deviceid: �豸ID
				pwnd: ��Ҫ��ʾ�Ĵ��ھ��
				pvparam: ָ����Ƶ�豸�����ṹ���ָ��
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_preview_start( TUP_UINT32 deviceid,TUP_VOID* pwnd,TC_VIDEO_PARAM* pvparam);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_preview_stop
	��������  : �ر���Ƶ��
	�������  : deviceid: �豸ID				
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_preview_stop( TUP_UINT32 deviceid);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_preview_setparam
	��������  : ������Ƶ�򵼵Ĳ���
	�������  : deviceid: �豸ID
				pvparam: ָ����Ƶ�豸�����ṹ���ָ��
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_preview_setparam( TUP_UINT32 deviceid, TC_VIDEO_PARAM* pvparam);	

	/*****************************************************************************
	�� �� ��  : tup_conf_video_wizstart_runcapture
	��������  : ��������һֱ���е�Capture
	�������  : deviceid: �豸ID
				pvparam: ָ����Ƶ�豸�����ṹ���ָ��
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_wizstart_runcapture( TUP_UINT32 deviceid, TC_VIDEO_PARAM* pvparam);	

	/*****************************************************************************
	�� �� ��  : tup_conf_video_wizclose_runcapture
	��������  : �ر�������һֱ���е�Capture
	�������  : deviceid: �豸ID
				
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_wizend_runcapture( TUP_UINT32 deviceid);	

	/*****************************************************************************
	�� �� ��  : tup_conf_video_always_runcapture
	��������  : ʹ��һֱ���е�captureʱ�������wiz��������
	�������  : 
				
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_always_runcapture(CONF_HANDLE handle);	
	
	/*************************�ĵ��װ�߼��ӿ�*************************/
	
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_import
	��������  : ��һ������İװ��ļ����뵽ָ�������ڹ���İװ��У�������İװ��ļ�����ҳ����뵽���ڹ���İװ����
	�������  : handle: ������
				docid: �ĵ�ID
				filename: ������İװ��ļ�ȫ·����utf8�����ַ�����
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_FAILURE������δ����
				TC_NULL_POINT����������pszFileNameΪNULL
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_DS_ERROR_DOC_NOTEXIST�������뵽���ĵ���Ч
				TC_DS_ERROR_NOT_VALID_CWP����������ļ�������Ч�ı���İװ��ļ�
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_WB_ON_PAGE_NEW
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_import(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, const TUP_CHAR* filename);
	

	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_load
	��������  : ����һ��������Ϊ˽�и�ʽ���ĵ����ýӿ���tup_conf_ds_open�ӿڴ�˽
				�и�ʽ�ĵ�ʱ����ͬ�Ĺ��ܣ������ĵ���������ļ�ʱ���ĵ���������
				������߿���
	�������  : handle: ������
				filename: Ҫ�򿪵��ĵ���ȫ·����utf8��ʽ�ַ�����
	�������  : ret_docid: �����ĵ��ɹ���ͨ���˲��������ĵ���ID����ΪNULL�򲻷���
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������������
	�ص���Ϣ  : COMPT_MSG_WB_ON_CURRENT_PAGE_IND
				COMPT_MSG_WB_ON_DOC_NEW
				COMPT_MSG_WB_ON_PAGE_NEW
				COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY

	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_load(CONF_HANDLE handle,COMPONENT_IID ciid, const TUP_CHAR* filename, TUP_UINT32* ret_docid);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_wb_copy_page
	��������  : ����ָ���İװ�ҳ�棬�����Ƶ�ҳ�汻��Ϊ��ǰָ���װ�����һҳ����������߶����յ���ҳ���֪ͨ��
	�������  : handle: ������
				docid: �ĵ�ID
				pageid: ҳ��ID
	�������  : new_pageid: ���Ƴɹ��󷵻ص��µ�ҳ���ID������ò���ΪNULL�򲻷���
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_WB_ON_PAGE_NEW
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_copy_page(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, TUP_UINT32* new_pageid);
	

	/*************************�ĵ�����߼��ӿ�*************************/
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_lock_surfacebmp
	��������  : �����ĵ�ҳ������
	�������  : handle: ������
				
	�������  : width �� ҳ����
				height: ҳ��߶�
	�� �� ֵ  : �����ĵ�ҳ���ڴ�ָ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_VOID*  tup_conf_ds_lock_surfacebmp(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32* width, TUP_UINT32* height);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_unlock_surfacebmp
	��������  : �����ĵ�ҳ������
	�������  : handle: ������				
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_ds_unlock_surfacebmp(CONF_HANDLE handle,COMPONENT_IID ciid);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_set_surface_outputformat
	��������  : �����������Ⱦͼ��ĸ�ʽ
	�������  : handle: ������
				format: Ҫ���õ������ʽ��Windowsƽ̨Ĭ��ֵΪSUR_OUTPUT_HDC
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_ds_set_surface_outputformat(CONF_HANDLE handle,COMPONENT_IID ciid,  SurfaceOutputFormat format);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_get_doc_count
	��������  : ��ȡ��ǰ���ڹ�����ĵ�����
	�������  : handle: ������				
	�������  : count: ���ڷ����ĵ����������ΪNULL�򷵻ش���
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_doc_count(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32* count);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_get_docid_byindex
	��������  : ͨ���ĵ���������ȡ�ĵ���ID
	�������  : handle: ������
				index: �ĵ����������С��0����ڵ����ĵ���������*id����0
	�������  : docid: ���ڷ����ĵ���ID�����ΪNULL�򷵻ش��������ѯ���ĵ������ڣ���*idΪ0������Ϊ��0
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������������
	�ص���Ϣ  : ��				
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_docid_byindex(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_INT32 index, TUP_UINT32* docid);	
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_get_docindex_byid
	��������  : ͨ���ĵ�ID��ȡ���ĵ����ĵ��б��е�����
	�������  : handle: ������
				docid: �ĵ���ID
	�������  : index: ���ڷ����ĵ������������ΪNULL�򷵻ش��������ѯ���ĵ������ڣ�*indexΪ-1������Ϊ���ڵ���0��ֵ
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������������
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_docindex_byid(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_INT* index);	
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_get_page_count
	��������  : ��ȡָ���ĵ���ҳ��
	�������  : handle: ������
				docid:�ĵ���ID
	�������  : count: ���ڷ���ҳ�������ΪNULL�򷵻ش��������ѯ���ĵ������ڣ�*countΪ-1������Ϊ���ڵ���0��ֵ
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������������
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_page_count(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32* count);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_get_pageno_byid
	��������  : ͨ��ҳ��ID��ȡҳ��
	�������  : handle: ������
				docid: �װ��ĵ���ID
				pageid: ҳ��ID
	�������  : pageno: ���ڷ���ҳ�룬���ΪNULL���򷵻ش��������ѯ��ҳ��id�����ڣ�*pageNoΪ-1������Ϊ���ڵ���0��ֵ
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������������
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_pageno_byid(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid, TUP_INT* pageno);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_get_pageid_byno
	��������  : ͨ��ҳ�뷵��ҳ��ID
	�������  : handle: ������
				docid: �ĵ���ID
				pageno: ҳ��
	�������  : pageid: ���ڷ���ҳ��ID�����ΪNULL�򷵻ش��������ѯ��ҳ�治���ڣ�*idΪ0������Ϊ��0ֵ				
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������������
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_pageid_byno(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_INT32 pageno, TUP_UINT32* pageid);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_get_pageinfo
	��������  : ��ȡָ��ҳ�����Ϣ
	�������  : handle: ������
				docid: �ĵ���ID
				pageid: ҳ��ID				
	�������  : pageinfo: ͨ���ò�������ָ��ҳ�����Ϣ
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������������
				TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
				TC_DS_ERROR_PAGE_NOTEXIST��ҳ�治����
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_pageinfo(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid, DsPageInfo* pageinfo);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_get_docinfo
	��������  : ��ȡָ���ĵ�����Ϣ
	�������  : handle: ������
				docid: �ĵ�ID
	�������  : pdocinfo: ͨ���ò�������ָ���ĵ�����Ϣ
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������������
				TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_docinfo(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, DsDocInfo* pdocinfo);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_get_thumbnail
	��������  : ��ȡָ���ĵ�ָ��ҳ�������ͼ
	�������  : handle: ������
				docid: �����ĵ���ID
				pageid: ҳ��ID
				width: Ҫ��ȡ������ͼ�Ŀ�TWIPS��λ
				height: Ҫ��ȡ������ͼ�ĸߣ�TWIPS��λ
	�������  : ��
	�� �� ֵ  : NULL����ȡ����ͼʧ��
				��NULL������ͼ����
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_VOID*  tup_conf_ds_get_thumbnail(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid, TUP_INT32 width, TUP_INT32 height);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_release_thumbnail
	��������  : �ͷ�ָ���ĵ�ָ��ҳ�������ͼ
	�������  : handle: ������
				docid: �����ĵ���ID
				pageid: ҳ��ID
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_ds_release_thumbnail(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_ds_save
	��������  : ����һ�������ĵ��������ļ������ĵ������˽�и�ʽ�������ĵ��ĺ�׺�����ޣ����ϲ�Ӧ�þ���
	�������  : handle: ������
	docid: Ҫ����Ĺ����ĵ���ID
	filename: �����ĵ���ȫ·��(utf8�����ַ���)
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
	TC_NULL_POINT������δ��������������
	TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
	TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
	TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
	TC_DS_ERROR_DOC_USER_OFFLINE���û�����
	TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
	TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_save(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid, const char* filename);		

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_saveas_picture
	��������  : �ĵ��ĵ�ҳ���ݱ����JPEGͼƬ
	�������  : handle: ������
				docid:  �ĵ�ID
				pageid: ҳ��ID
				filename: ������ļ���������·����
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_saveas_picture(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid, const TUP_CHAR* filename);

	/*****************************************************************************
	�� �� ��  : tup_conf_cache_delete
	��������  : ɾ���ĵ�����cache�ļ�(ֻ������iOS)
	�������  : ��
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_cache_delete();

#ifdef __cplusplus
};


#endif

#endif