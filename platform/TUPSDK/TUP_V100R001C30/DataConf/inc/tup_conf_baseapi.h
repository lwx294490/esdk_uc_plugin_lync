#ifndef _TUP_CONF_BASEAPI_H_
#define _TUP_CONF_BASEAPI_H_

#include "tup_conf_basedef.h"

//ע�⣺�ӿ��ַ���������UTF8��ʽ

#ifdef __cplusplus
	extern "C" {
#endif
	/*************************��ػ����ӿ�*************************/
	/*****************************************************************************
	�� �� ��  : tup_conf_init
	��������  : ��ʼ����������������߳�ģ�͡�ϵͳ�豸���ͺͲ���ϵͳ���͡�
				���øú������߳�Ϊ��Ϣ�ص��̣߳����������̵߳���
	�������  : selfthread: �߳�ģ�ͣ���Ҫ����
							true����������ڶ����߳����У���ģʽ�²�֧��ý�干��ģ��
							false�����øú������߳�Ϊ��������������̣߳���Ϣ�ص�Ҳ�ڸ��̡߳�
				pinitparam: ��ʼ�������������豸���ͺͲ���ϵͳ����
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
    TUP_API TUP_VOID  tup_conf_init(TUP_BOOL selfthread, TUP_IN const Init_param * pinitparam);

	/*****************************************************************************
	�� �� ��  : tup_conf_uninit
	��������  : �˳�����ǰ�ͷ����л��鼰������Դ��
	�������  : ��
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_uninit(void);

	/*****************************************************************************
	�� �� ��  : tup_conf_new
	��������  : �½�һ���������
	�������  : callback: �����ص������ĺ�����ַ
				pconfinfo: ���������Ϣ
				option: ����ѡ��ο�CONF_OPTIONö��ֵ���������ܴ�CONF_OPTION_USERLIST����
	�������  : ret_handle: ���ػ�������ָ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_new(conference_multi_callback callback, const TC_CONF_INFO* pconfinfo, TUP_UINT32 option, CONF_HANDLE* ret_handle);

    /*****************************************************************************
	�� �� ��  : tup_conf_heart
	��������  : �ṩ��Ϣ��������������ISVӦ�ò�������Ϣѭ����Ϊ�˱�֤��Ϣѭ�������߳���
				˵��: Windowsƽ̨������øýӿڣ��ƶ�ƽ̨������øýӿڡ�
	�������  : handle: ������
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
    TUP_API TUP_VOID  tup_conf_heart(CONF_HANDLE handle);


	/*****************************************************************************
	�� �� ��  : tup_conf_join
	��������  : ����һ������
	�������  : handle: ������
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_ON_CONFERENCE_JOIN  
				CONF_MSG_USER_ON_ENTER_IND 
				CONF_MSG_USER_ON_HOST_CHANGE_IND
				CONF_MSG_USER_ON_PRESENTER_CHANGE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_join(CONF_HANDLE handle); 

	/*****************************************************************************
	�� �� ��  : tup_conf_leave
	��������  : �뿪һ������
	�������  : handle: ������
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_USER_ON_LEAVE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_leave(CONF_HANDLE handle); 

	/*****************************************************************************
	�� �� ��  : tup_conf_lock
	��������  : ����һ�����飬��������������˾Ͳ��ܼ��������
	�������  : handle: ������
				lock:�Ƿ�������TRUEΪ������FALSEΪ����
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_ON_LOCK_RSP
				CONF_MSG_ON_LOCK_REPORT_IND
	*****************************************************************************/  
    TUP_API TUP_RESULT  tup_conf_lock(CONF_HANDLE handle,TUP_BOOL lock); 

	/*****************************************************************************
	�� �� ��  : tup_conf_terminate
	��������  : ����һ������
	�������  : handle: ������
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_ON_CONFERENCE_TERMINATE
	*****************************************************************************/  
    TUP_API TUP_RESULT  tup_conf_terminate(CONF_HANDLE handle);

	/*****************************************************************************
	�� �� ��  : tup_conf_mute
	��������  : �᳡����/ȡ�������������绰��PC�û�
	�������  : handle: ������
				bmute: �᳡������ʶ��ȡֵ��TRUE��������FALSE��ȡ������
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_ON_MUTE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_mute(CONF_HANDLE handle, TUP_BOOL bmute); 

	/*****************************************************************************
	�� �� ��  : tup_conf_release
	��������  : ����һ��������󣬸ú��������tup_conf_new��ͬһ���߳�
	�������  : handle: ������
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
    TUP_API TUP_RESULT  tup_conf_release(CONF_HANDLE handle);
	
	/*****************************************************************************
	�� �� ��  : tup_conf_load_component
	��������  : ����ָ�����
	�������  : handle: ������ ,
				compts : ���ID ����ӦCOMPONENT_IIDö��ֵ���ɻ�����
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_ON_COMPONENT_LOAD
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_load_component(CONF_HANDLE handle, TUP_UINT32 compts);


	/*****************************************************************************
	�� �� ��  : tup_conf_reg_component_callback
	��������  : ע��ָ������Ļص�����
	�������  : handle: ������ ,
				compts : ���ID ����ӦCOMPONENT_IIDö��ֵ
				callback���ص�����
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_reg_component_callback(CONF_HANDLE handle, TUP_UINT32 compt,component_multi_callback callback);


	/*****************************************************************************
	�� �� ��  : tup_conf_user_get_host
	��������  : ��ȡ������ID
	�������  : handle: ������
	�������  : ret_userid��������ID��0��ʾû��������
	�� �� ֵ  : ����TC_OK��ʾ�����˴��ڣ����򲻴���
	�ص���Ϣ  : ��
	*****************************************************************************/  
    TUP_API TUP_RESULT  tup_conf_user_get_host(CONF_HANDLE handle,TUP_UINT32* ret_userid);
 
	/*****************************************************************************
	�� �� ��  : tup_conf_user_get_presenter
	��������  : ��ȡ������ID
	�������  : handle: ������
	�������  : ret_userid��������ID��0��ʾû��������
	�� �� ֵ  : ����TC_OK��ʾ�����˴��ڣ����򲻴���
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_user_get_presenter(CONF_HANDLE handle,TUP_UINT32* ret_userid);
 
	/*****************************************************************************
	�� �� ��  : tup_conf_user_kickout
	��������  : �߳�һ���û�
	�������  : handle: ������
				userid: �û�ID
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_ON_CONFERENCE_LEAVE
				CONF_MSG_USER_ON_LEAVE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_user_kickout(CONF_HANDLE handle,TUP_UINT32 userid);

	/*****************************************************************************
	�� �� ��  : tup_conf_user_set_role
	��������  : �����û���ɫ
	�������  : handle: ������
				userid: �û�ID
				role: �û���ɫ��ȡֵ��	CONF_ROLE_HOST//������
										CONF_ROLE_PRESENTER//������
										CONF_ROLE_GENERAL//��ͨ�����
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_USER_ON_HOST_GIVE_IND
				CONF_MSG_USER_ON_HOST_GIVE_CFM
				CONF_MSG_USER_ON_HOST_CHANGE_IND
				CONF_MSG_USER_ON_PRESENTER_GIVE_IND
				CONF_MSG_USER_ON_PRESENTER_GIVE_CFM
				CONF_MSG_USER_ON_PRESENTER_CHANGE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_user_set_role(CONF_HANDLE handle,TUP_UINT32 userid,TUP_UINT32 role);

	/*****************************************************************************
	�� �� ��  : tup_conf_user_request_role
	��������  : �����û���ɫ������ɹ��Լ����յ�ȷ����Ϣ���������յ���ɫ�����Ϣ��
	�������  : handle: ������
				role:  �û���ɫ��ȡֵ��	CONF_ROLE_HOST//������
										CONF_ROLE_PRESENTER//������
										CONF_ROLE_GENERAL//��ͨ�����
				pszkey: ��ɫ�������룬������һ�㶼��Ҫ���룬�����˲���Ҫ����Чֵ��32λ��\0����β�ַ���
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : CONF_MSG_USER_ON_HOST_CHANGE_CFM
				CONF_MSG_USER_ON_PRESENTER_CHANGE_CFM
				CONF_MSG_USER_ON_HOST_CHANGE_IND
				CONF_MSG_USER_ON_PRESENTER_CHANGE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_user_request_role(CONF_HANDLE handle,TUP_UINT32 role,const char* pszkey);

	/*************************��Ļ��������ӿ�*************************/
	
	/*****************************************************************************
	�� �� ��  : tup_conf_as_set_owner
	��������  : ������Ļ�����ӵ����
	�������  : handle: ������
				userid: �û�ID
				action: ȡֵ���Ƿ�ֵ����ʧ�ܣ���
						 AS_ACTION_DELETE//�ͷ�
						 AS_ACTION_ADD//ӵ��
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_SHARING_SESSION
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_set_owner(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT32 action);				

	/*****************************************************************************
	�� �� ��  : tup_conf_as_set_sharetype
	��������  : ���õ�ǰ�Ĺ�������
	�������  : handle: ������
				sharingtype: ȡֵ���Ƿ�ֵ����ʧ�ܣ���
						 AS_SHARINGTYPE_DESKTOP//���湲��
						 AS_SHARINGTYPE_APP//Ӧ�ó�����
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_set_sharetype(CONF_HANDLE handle, TUP_INT32 sharingtype);

	/*****************************************************************************
	�� �� ��  : tup_conf_as_start
	��������  : ��ʼ���湲���Ӧ�ó�����
	�������  : handle: ������
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_start(CONF_HANDLE handle);

	/*****************************************************************************
	�� �� ��  : tup_conf_as_stop
	��������  : ֹͣ���湲���Ӧ�ó�����
	�������  : handle: ������
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_stop(CONF_HANDLE handle);	

	/*****************************************************************************
	�� �� ��  : tup_conf_as_get_screendata
	��������  : ��ȡ��Ļ����
	�������  : handle: ������
	�������  : pscreendata: ��Ļ����
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_get_screendata(CONF_HANDLE handle,TC_AS_SCREENDATA* pscreendata);	

	/*****************************************************************************
	�� �� ��  : tup_conf_as_request_privilege
	��������  : ����Զ�̿��ƻ��׼Ȩ�ޣ��Է����յ�����֪ͨ
	�������  : handle: ������
				privilege: Ȩ�����͡�ȡֵ���Ƿ�ֵ����ʧ�ܣ���
											AS_PRIVILEGETYPE_CONTROL //Զ�̿���
											AS_PRIVILEGETYPE_ANNOTATION //��ע
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_PRIVILEGE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_request_privilege(CONF_HANDLE handle,TUP_INT8 privilege);	

	/*****************************************************************************
	�� �� ��  : tup_conf_as_set_privilege
	��������  : ����/�ջ�Զ�̿���Ȩ�ޣ��Զ���Ч����֪ͨ�ϲ�
	�������  : handle: ������
				userid: �û�ID
				privilege: Ȩ�����͡�ȡֵ���Ƿ�ֵ����ʧ�ܣ���
											AS_PRIVILEGETYPE_CONTROL //Զ�̿���
											AS_PRIVILEGETYPE_ANNOTATION //��ע
				action: �������͡�ȡֵ���Ƿ�ֵ����ʧ�ܣ���
												AS_ACTION_DELETE //�ջ�
												AS_ACTION_ADD //����
												AS_ACTION_MODIFY //�޸�
												AS_ACTION_REJECT //�ܾ�
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_PRIVILEGE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_set_privilege(CONF_HANDLE handle,TUP_UINT32 userid,TUP_INT8 privilege,TUP_UINT32 action);

	/*****************************************************************************
	�� �� ��  : tup_conf_as_inputwndmsg
	��������  : �������ͼ�����Ϣ������Զ�̿�����;
	�������  : handle: ������
				msgtype: ��Ϣ���ͣ�windows�¶�Ӧmessage
				wparam: ��Ϣ������window�¶�Ӧ��Ϣ��WPARAM����
				lparam: ��Ϣ������window�¶�Ӧ��Ϣ��LPARAM����
				pdata: Ԥ����չ���ݣ�
				datalen: Ԥ����չ���ݳ���				 
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_inputwndmsg(CONF_HANDLE handle,TUP_UINT32 msgtype, TUP_ULONG wparam, TUP_LONG lparam, TUP_VOID* pdata, TUP_UINT32 datalen);

	/*****************************************************************************
	�� �� ��  : tup_conf_as_begin_annotation
	��������  : ��ʼ���湲���Ӧ�ó�����ı�ע����
	�������  : handle: ������
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_begin_annotation(CONF_HANDLE handle);

	/*****************************************************************************
	�� �� ��  : tup_conf_as_end_annotation
	��������  : ֹͣ���湲���Ӧ�ó�����ı�ע����
	�������  : handle: ������
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_end_annotation(CONF_HANDLE handle);
	

	/*************************��Ƶ�����ӿ�*************************/

	
	/*****************************************************************************
	�� �� ��  : tup_conf_video_get_deviceinfo
	��������  : ��ȡ�豸��Ϣ�б�
	�������  : handle: ��������Ϊ0ʱ��������Ƶ��		
	pdevice_info: ָ����Ƶ�豸�б������ָ��
	ret_count: ��pdevice_infoΪ��ʱ����������
	�������  : pDeviceInfo: ָ����Ƶ�豸�б������ָ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_get_deviceinfo(CONF_HANDLE handle,TC_DEVICE_INFO* pdevice_info,TUP_UINT32* ret_count);

	/*****************************************************************************
	�� �� ��  : tup_conf_video_get_devicecapbilityinfo
	��������  : ��ȡָ���豸����������Ϣ�б�
	�������  : handle: ������
				deviceid: ��Ƶ�豸ID
				pcapbility_info: ָ����Ƶ�豸�����ṹ�������ָ��
	�������  : pcapbility_info: ָ����Ƶ�豸�����ṹ�������ָ��
				ret_count:��pcapbility_infoΪ��ʱ����������
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_get_devicecapbilityinfo(CONF_HANDLE handle, TUP_UINT32 deviceid, TC_VIDEO_PARAM* pcapbility_info,TUP_UINT32* ret_count);	

	/*****************************************************************************
	�� �� ��  : tup_conf_video_open
	��������  : ���Լ�������ͷ���ò����������Լ�������ͷ
	�������  : handle: ������
				deviceid: ��Ƶ�豸ID
				preview: �Ƿ���ҪԤ������Ԥ���򲻻�ص�COMPT_MSG_VIDEO_ON_SWITCH��Ϣ
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_VIDEO_ON_SWITCH
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_open(CONF_HANDLE handle, TUP_UINT32 deviceid,TUP_BOOL preview );		

	/*****************************************************************************
	�� �� ��  : tup_conf_video_close
	��������  : �ر��Լ�������ͷ
	�������  : handle: ������
				deviceid: ��Ƶ�豸ID				
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_VIDEO_ON_SWITCH
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_close(CONF_HANDLE handle, TUP_UINT32 deviceid);	

	/*****************************************************************************
	�� �� ��  : tup_conf_video_setparam
	��������  : ������Ƶ����ز���������Ƶ֮ǰ��Ҫ���ã��粻������ô�Ͳ���ȱʡֵ��������
	�������  : handle: ������
				deviceid: ��Ƶ�豸ID
				pvparam: ָ����Ƶ�豸�����ṹ���ָ��
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_setparam(CONF_HANDLE handle, TUP_UINT32 deviceid, TC_VIDEO_PARAM* pvparam);

	/*****************************************************************************
	�� �� ��  : tup_conf_video_getparam
	��������  : ��ȡ��Ƶ����ز���
	�������  : handle: ������
				deviceid: ��Ƶ�豸ID
	�������  : pvparam: ָ����Ƶ�豸�����ṹ���ָ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_getparam(CONF_HANDLE handle, TUP_UINT32 deviceid, TC_VIDEO_PARAM* pvparam);

	/*****************************************************************************
	�� �� ��  : tup_conf_video_notify
	��������  : ֪ͨ��������ߴ򿪻�ر��豸
	�������  : handle: ������
				notifycmd: ֪ͨ���ͣ�ȡֵ��
							VIDEO_NOTIFY_OPEN   //��
							VIDEO_NOTIFY_CLOSE   //�ر�
							VIDEO_NOTIFY_DATA_SENDTO_PHONESESSION   //��Ƶ���ݷ��͸��绰�᳡
				userid: ��֪ͨ���û�ID
				pvparam: ָ����Ƶ�豸�����ṹ���ָ��
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : COMPT_MSG_VIDEO_ON_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_notify(CONF_HANDLE handle, TUP_UINT32 notifycmd,TUP_UINT32 userid,TC_VIDEO_PARAM* pvparam);

	/*****************************************************************************
	�� �� ��  : tup_conf_video_switch_channel
	��������  : ���ڽ��ն���˵���л����������ǵ���(VTM��Ŀ���ÿ�������ӿ�)
	�������  : handle: ������
				userid: �û�ID
				deviceid: ��Ƶ�豸ID
				highchannel: �л�������(TRUE)���ǵ���(FALSE)
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_switch_channel(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_BOOL highchannel );

	/*****************************************************************************
	�� �� ��  : tup_conf_video_attach
	��������  : ָ���û�����Ƶ�봰�ڽ��а�
	�������  : handle: ������
				userid: �û�ID
				deviceid: ��Ƶ�豸ID
				pwnd: ���ھ��
				highchannel: �������(TRUE)���ǵ���(FALSE)(Ĭ�ϸ���)	
				showmode: ��Ƶ�ڴ�����ʾģʽ��ȡֵ:
									0 //��ʾ�������� 
									1 //��ʾ����Ƶ�ı���������ʾ�����ಿ���Ժ�ɫ���
									2 //��ʾ�����ڴ�С���вü�
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_attach(CONF_HANDLE handle,TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_VOID* pwnd, TUP_BOOL highchannel , TUP_UINT8 showmode );

	/*****************************************************************************
	�� �� ��  : tup_conf_video_detach
	��������  : ָ���û���Ƶ�봰�ڽ��н��
	�������  : handle: ������
				userid: �û�ID
				deviceid: ��Ƶ�豸ID
				pwnd: ���ھ��
				bleavechannel: Detach���ڵ�ʱ���Ƿ���Ҫ�뿪channel (Ĭ���ǲ��뿪channel),�뿪channel�򲻽�������
	�������  : ��
	�� �� ֵ  : ����TC_OK��ʾ�ɹ���������ʾʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_detach(CONF_HANDLE handle,TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_VOID* pwnd, TUP_BOOL bleavechannel);



	/*************************�װ�����ӿ�*************************/


	/*****************************************************************************
	�� �� ��  : tup_conf_ds_new_doc
	��������  : �½�һ���յİװ��ĵ���������������߶����յ��½��װ��֪ͨ
	�������  : handle: ������				
	�������  : ret_docid: �½��װ��ĵ��ɹ���ͨ���ò������ذװ��ĵ�ID
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���װ�ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���װ�Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_WB_ON_DOC_NEW
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_new_doc(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32* ret_docid);

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_new_page
	��������  : ��ָ���İװ��ĵ����½��װ�ҳ������½��ɹ����½���ҳ�潫����Ϊ���ĵ������һҳ��������������߶����յ��½�ҳ��֪ͨ
	�������  : handle: ������
				docid: �װ��ĵ���ID
				width: Ҫ������ҳ��Ŀ�ȣ���TWIPSΪ��λ
				height: Ҫ������ҳ��ĸ߶ȣ���TWIPSΪ��λ
	�������  : ret_pageid: ����½�ҳ��ɹ���ͨ���ò���������ҳ���ID������ò���ΪNULL�򲻷���
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_WB_ON_PAGE_NEW
				COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY
				COMPT_MSG_WB_ON_CURRENT_PAGE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_new_page(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_INT32 width, TUP_INT32 height, TUP_UINT32* ret_pageid);	

	/*****************************************************************************
	�� �� ��  : tup_conf_wb_delete_doc
	��������  : ɾ��һ���װ��ĵ���������������߶����յ�ɾ����Ϣ��ִ��ɾ���ĵ��Ĳ���
	�������  : handle: ������
				docid: �װ��ĵ���ID
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���װ�ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���װ�Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_ERROR��ɾ��ʧ��
	�ص���Ϣ  : COMPT_MSG_WB_ON_DOC_DEL
				COMPT_MSG_WB_ON_PAGE_DEL
				COMPT_MSG_WB_ON_CURRENT_PAGE_IND
				COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_delete_doc(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid);

	/*****************************************************************************
	�� �� ��  : tup_conf_wb_delete_page
	��������  :ɾ��ָ���װ��ĵ��е�ָ��ҳ��
	�������  : handle: ������
				docid: �װ��ĵ���ID
				pageid: ָ���װ�ҳ���ID
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_WB_ON_PAGE_DEL
				COMPT_MSG_WB_ON_CURRENT_PAGE_IND
				COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_delete_page(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid);



	/*****************************************************************************
	�� �� ��  : tup_conf_ds_open
	��������  : �򿪹����ĵ����ĵ��ɹ����غ󽫱��ϴ�����������������������߽�����յ����ĵ�������
	�������  : handle: ������
				filename: Ҫ�򿪵Ĺ����ĵ���ȫ·��(utf8�����ַ���)������ΪNULL
				option: ���ĵ�ѡ�ȡֵ��
						DS_OPTION_QUALITY	//�������ȣ����Ȳ���EMF��ʽ
						DS_OPTION_SIZE  	//�������ȣ����Ȳ���JPG��ʽ
	�������  : ret_docid: uint32��ָ�룬�����ΪNULL��ͨ����ֵ���ع����ĵ���ID 
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������������
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_DS_ERROR_DOC_ALREADY_OPEN���ĵ��Ѿ������������ٴι���
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_DS_ON_DOCLOAD_START
				COMPT_MSG_DS_ON_DOC_NEW
				COMPT_MSG_DS_ON_PAGE_NEW
				COMPT_MSG_DS_ON_PAGE_LOADED
				COMPT_MSG_DS_ON_DOCLOAD_FINISH
				COMPT_MSG_DS_ON_CURRENT_PAGE_IND
				COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_open(CONF_HANDLE handle,COMPONENT_IID ciid, const TUP_CHAR* filename, TUP_UINT32 option, TUP_UINT32* ret_docid);

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_close
	��������  : �ر�һ���ĵ���������������߶����յ��ر���Ϣ
	�������  : handle: ������
				docid: Ҫ�رյĹ����ĵ���ID
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û��ѵ���
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_DS_ON_DOC_DEL
				COMPT_MSG_DS_ON_PAGE_DEL
				COMPT_MSG_DS_ON_CURRENT_PAGE_IND
				COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_close(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid);	                            


	/*****************************************************************************
	�� �� ��  : tup_conf_ds_set_current_page
	��������  : ���õ�ǰ��ʾ��ҳ�棬���øýӿں󣬵�ǰ��ʾ��ҳ�潫���л���ָ�����ĵ�ҳ��
				���ָ�����ĵ�IDΪ��Чֵ��ҳ��IDΪ0�����л������ĵ��ϴ���ʾ��ҳ�档�ú�
				����ͬ�����úͷ�ͬ�����֣�ͬ������ʱ��������������߶����յ��л���Ϣ��
				ִ����Ӧ��������ͬ��ʱ��ֻ�б��ط����仯
	�������  : handle: ��������Ϊ0ʱ�������ĵ�Ԥ��
				docid: �ĵ�ID
				pageid: ҳ��ID
				sync: �Ƿ�ͬ�����ã�0����ͬ����1��ͬ��
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_DS_ON_CURRENT_PAGE_IND
				COMPT_MSG_DS_ON_CURRENT_PAGE
				COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_set_current_page(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid, TUP_BOOL sync);	

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_set_dispsize
	��������  : ������ʾ����Ĵ�С���ú�����Ҫ���κ���ʾ����Ĳ���֮ǰ�����ã����򽫲�
				����ʾ�κ����ݣ��������յ��ĵ��������׼���õ���Ϣ����øú�������������ʾ��
				С�����仯ʱ����
	�������  : handle: ��������Ϊ0ʱ�������ĵ�Ԥ��
				size: ��ʾ����Ŀ�ߣ���TWIPSΪ��λ
				redraw: ���ú������Ƿ������ػ棬0�����ػ棬1���ػ�
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_set_canvas_size(CONF_HANDLE handle, COMPONENT_IID ciid,TC_SIZE size, TUP_BOOL redraw);

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_set_pageorg
	��������  : ����ҳ�����ʾ��㣬�ú�����Ҫ��ҳ�����ʾ��㷢���仯ʱ�����ã�ҳ����������ֻ��ָ����ҳ����Ч
	�������  : handle: ��������Ϊ0ʱ�������ĵ�Ԥ��
				docid: �ĵ�ID
				pageid: ҳ���ID
				org: �����õ��µ���ʾ��㣬��TWIPSΪ��λ����ֵ�ǻ������Ͻ������ҳ�����Ͻǵ�ƫ�ƣ���������Ϊ��
				sync: �Ƿ�ͬ����0����ͬ����1��ͬ����ͬ��ʱ��������߶����յ����仯֪ͨ����ͬ��ʱֻ���Լ����淢���仯
				redraw: �Ƿ�ǿ���ػ棬0����ǿ�ƣ�1��ǿ�ƣ����øú���ʱ��������õ�����ԭ���������ͬ���Ҹò���Ϊ0���򲻻��ػ�ҳ�棬�����ػ�
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
				TC_DS_ERROR_PAGE_NOTEXIST��ҳ�治����
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_set_page_origin(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid,TC_POINT org, TUP_BOOL sync, TUP_BOOL redraw);

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_rotate_page
	��������  : ��תָ��ҳ�汳�����ú���ֻ��ת�ĵ��ı���������Ա�ע����Ӱ�죬�ýӿڵ���ֻ��ָ����ҳ�����Ӱ��
	�������  : handle: ��������Ϊ0ʱ�������ĵ�Ԥ��
				docid: �ĵ�ID
				pageid: ҳ���ID
				rftype: ��ת����
				sync: �Ƿ�ͬ����0����ͬ����1��ͬ��
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_rotate_page(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, DsRotateFlipType rftype, TUP_BOOL sync);

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_set_zoom
	��������  : �����ĵ������ţ��ýӿ������ĵ����������ͺ����Űٷ������ýӿڵ��ö�ָ�����ĵ�����Ӱ�죬���óɹ���ָ���ĵ������е�ҳ�涼������ͬ������
	�������  : handle: ��������Ϊ0ʱ�������ĵ�Ԥ��
				docid: �ĵ���ID
				zoomtype: �������ͣ�����ֵΪDS_ZOOM_PAGESIZEʱ��ʵ��ҳ��Ĵ�С������ʾ������ֵΪDS_ZOOM_FITWIDTHʱ��
						  ��������ŵ���ʾ����Ĵ�С����߱ȹ̶���ʾ������ֵΪDS_ZOOM_DISPSIZEʱ��������ʾ�����
						  ������ʾ������ҳ��Ĵ�С������ʾ������ֵΪDS_ZOOM_PERCENTʱ��ֱ�Ӱ���factor�����д���İٷֱȽ�����ʾ��
				factor: �������ӣ��ٷ�ֵ������Ŵ�200%����ò���Ϊ200������zoomType��ֵΪDS_ZOOM_PERCENTʱ��ֵ������
				sync: �Ƿ�ͬ�����ţ�0����ͬ����1��ͬ��
				redraw: �Ƿ���øýӿں�����ˢ�½��棬0���ݲ�ˢ�£�1������ˢ��
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
				TC_ERROR����������
	�ص���Ϣ  : COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_set_zoom(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 zoomtype, TUP_UINT32 factor, TUP_BOOL sync, TUP_BOOL redraw);

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_getdoc_property
	��������  : ��ȡ�ĵ����Լ�/���������ݳ���
	�������  : handle: ��������Ϊ0ʱ�������ĵ�Ԥ��
				docid: �ĵ���ID
				nPropertyID: �ĵ�����ID���ο�ö��ֵDocProperty
				nRetLen: ��Ϊ���ʱ����lpBuf�ĳ���				
	�������  : lpBuf: ���ڱ����������ݵ�buffer��ΪNULLʱͨ��nRetLen����Ҫ��ȡ���ݵĳ���
				nRetLen: �ɹ���ȡ���ݺ�ͨ���ò�������ʵ�����ݵĳ��ȣ����lpBufΪNULL����ͨ���ò�������ʵ�����ݵĳ��ȣ��ò�������ΪNULL
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ���� 
				TC_DS_ERROR_PROP_NOT_EXIT�����Բ�����
				TC_PARAM_ERROR�������������
				TC_BUFFER_TOO_SHORT���ڴ��̫С
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_get_doc_property(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid,TUP_UINT32 nPropertyID,TUP_UINT8* lpBuf,TUP_UINT32* nRetLen);

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_getpage_property
	��������  : ��ȡҳ�����Լ�/���������ݳ���
	�������  : handle: ��������Ϊ0ʱ�������ĵ�Ԥ��
				docid: �ĵ���ID
				pageid: ҳ��ID
				nPropertyID: ҳ������ID
				nRetLen: ��Ϊ���ʱ����lpBuf�ĳ���				
	�������  : lpBuf: ���ڱ����������ݵ�buffer��ΪNULLʱͨ��nRetLen����Ҫ��ȡ���ݵĳ���
				nRetLen: �ɹ���ȡ���ݺ�ͨ���ò�������ʵ�����ݵĳ��ȣ����lpBufΪNULL����ͨ���ò�������ʵ�����ݵĳ��ȣ��ò�������ΪNULL
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ���� 
				TC_DS_ERROR_PROP_NOT_EXIT�����Բ�����
				TC_PARAM_ERROR�������������
				TC_BUFFER_TOO_SHORT���ڴ��̫С
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_get_page_property(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid,TUP_UINT32 pageid,TUP_UINT32 nPropertyID,
														TUP_UINT8* lpBuf,TUP_UINT32* nRetLen);	

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_get_surfacebmp
	��������  : ��ȡ��Ⱦ�õĵ�ǰҳ��ͼ�񣬷���ֵΪ��ͼ�������ָ��
	�������  : handle: ��������Ϊ0ʱ�������ĵ�Ԥ��
	�������  : ret_width: �����ֵ��ΪNULL����ͨ����ֵ����ͼ��Ŀ��(TWIPS)
				ret_height: �����ֵ��ΪNULL����ͨ����ֵ����ͼ��ĸ߶�(TWIPS)
	�� �� ֵ  : NULL����ȡͼ��ʧ�ܣ�
				��NULL���ɹ���ȡ����ͼ�����ݣ����ݸ�ʽ��conf_ds_set_surface_output_format���õ�һ�£����û��������ΪĬ��ֵ��windowsƽ̨ΪHDC��iOSƽ̨ΪBMP
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_VOID* tup_conf_ds_get_surfacebmp(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32* ret_width, TUP_UINT32* ret_height);

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_set_bgcolor
	��������  : �����ĵ�����ģ�黭���ı���ɫ
	�������  : handle: ������
				bgColor: ������ɫֵ
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_VOID  tup_conf_ds_set_bgcolor(CONF_HANDLE handle,COMPONENT_IID ciid,  COLORRGBA bgColor);

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_set_dispmode
	��������  : �����ĵ�����ģ�����ʾģʽ
	�������  : handle: ������
				dispMode: ��ʾģʽ
	�������  : ��
	�� �� ֵ  : ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_VOID  tup_conf_ds_set_dispmode(CONF_HANDLE handle,COMPONENT_IID ciid,  DsDispMode dispMode);

	/*****************************************************************************
	�� �� ��  : tup_conf_ds_get_syncinfo
	��������  : ��ȡ�������ϵĵ�ǰ��Ϣ��һ�������������������ͬ��
	�������  : handle: ������				
	�������  : pInfo: ���ڱ����ȡ���ĵ�ǰ��ǰ��������Ϣ
	�������  : ��
	�� �� ֵ  : TC_OK ��ȡ�ɹ�
				TC_ERROR ��ȡʧ�ܣ�һ������Ϊ���ݿ����δ�������
				TC_FAILURE ����ʧ�ܣ�һ���ǵ���̫�磬����δ����
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_get_syncinfo(CONF_HANDLE handle,COMPONENT_IID ciid,  DsSyncInfo* pInfo);

	
	/*************************��ע�����ӿ�*************************/

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_init_resource
	��������  : ��ʼ�����ر�עͼ����Դ���ýӿ���Ҫ��ģ��׼���ú��类���ã��������Ҫ
				��ʼ��������Դ���Բ����ã�ͨ���ýӿڳ�ʼ������Դ���Ա������õ���ע��ģ
				�������ã���ˣ������ͬ��ģ���в�ͬ����Դ��Ӧ�ò��ڶ����עIDʱ������
				����ͬ������ģ����õ�����ͬ����Դֻ��Ҫ����һ�Ρ�
				ͬһͼ����Դ��ID����ͨ�ͻ��˱���һ�£�ͼ��ע����ʾ��߼�����ƫ����Ҳ��
				����ͬ��������ͬ����ʾֵ��TWIPS��λ����ͼƬ��ԭʼ�ߴ���ͻ��˿��Ը���
				��Ҫ��ƣ�����Ҫע��ߴ�ı�����Ҫ��ͬ��������ܳ��ֲ�ͬ�ͻ�����ͬһ��
				ע����ʾЧ����ͬ����������Ӧ�ò�Э�鷶Χ��Ӧ�ø��ͻ���һ���壬֮��
				�������ģ��Ҹ���ʱ���뿼��ǰ��汾�����ԡ�
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				pitems: ��Դ����
				count: pRes�����Ԫ�ظ���
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_init_resource(CONF_HANDLE handle,COMPONENT_IID ciid, 	Anno_Resource_Item* pitems,TUP_INT32 count);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_reg_customer_type
	��������  : ע���ϲ�Ӧ���Զ���ı�ע���ͣ��ýӿ�ע��ı�ע������DS_ANNOT_TYPE_CUSTOMER
				�������ͣ��Ҷ���ͼƬ��ı�ע���ýӿ���Ҫ����Щ������ı�ע������֮ǰ���ã�
				ͨ���ýӿ�ע��ı�ע���Ϳ��Ա�ͬһӦ�õĲ�ͬģ��ʹ�ã���ˣ������ͬģ��֮
				���в�ͬ�ı�ע����ע��ID��Ҫ�ܹ��໥���֣���ͬ�ı�ע����ֻ�趨��һ�Ρ�
				��ע�����͵Ķ������ͨ�Ŀͻ��˱�����ȫһ������������ID�����ԣ�������Ӧ
				�ò�Э�鷶Χ��Ӧ�ø��ͻ���һ���壬֮���������ģ��Ҹ���ʱ���뿼��ǰ
				��汾�����ԡ�
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				pdefintypes: Ҫע����Զ����ע��������
				nCount: �����Ԫ�ظ���
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_reg_customer_type(CONF_HANDLE handle,COMPONENT_IID ciid, DsDefineAnnot* pdefintypes,TUP_INT32 count);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_set_config
	��������  : ���ñ��ر�ע����ز������װ塢�ĵ�����Ļ��������ģ����ɵ��ô˽ӿڣ�
				��������ã�bSelfLpNotDisp��ֵĬ��Ϊ0�����ײ����Ⱦ�Լ��ļ�����ע
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				config: ��ע�Ĳ���
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_ERROR��ָ��ciidģ�鲻�Ϸ���δ���أ�ʧ��
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_set_config(CONF_HANDLE handle,COMPONENT_IID ciid,	AnnotationConfig config);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_create_start
	��������  : ��ʼ����һ����ע���ýӿ�����DS_ANNOT_TYPE_DRAWING��DS_ANNOT_TYPE_CUSTOMER
				���ֱ�ע�Ĵ������������ע�Ĵ�������ͨ�����øú�����ʼ
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				docid: �ĵ���ID
				pageid: ҳ��ID
				type: ��ע�����ͣ�������ʱֻ��DS_ANNOT_TYPE_DRAWING��DS_ANNOT_TYPE_CUSTOMER����
				subtype: ��ע�����ͣ�����DRAWING�������ͺ�ͨ��conf_annotation_reg_customer_typeע�������
				point: ������ע����㣬һ������갴�µĵ��ͼƬ��ע�����Ͻǣ���TWIPSΪ��λ����
						��ֵ�����������ҳ�����Ͻǲ�������������µ�ֵ����������Ϊ��
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������������
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
				TC_DS_ERROR_PAGE_NOTEXIST��ҳ�治����
				TC_ANNOT_ERROR_CUSTOMERTYPE_NOTEXIST����ע����δ����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_create_start(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid,
													TUP_UINT32 type, TUP_UINT32 subtype, TC_POINT point);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_create_update
	��������  : ��ע���������и������ݣ���Ҫ����DS_ANNOT_TYPE_DRAWING��DS_ANNOT_TYPE_CUSTOMER
				���ֱ�ע�����ݸ��£����øú��������������´��������е����߿򣬲���Ӧ�ò���
				���仯��Ľ�������
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				pdata: �������ݣ�����DS_ANNOT_TYPE_DRAWING��ı�ע����������ΪCreateDrawingData*��
					   ����DS_ANNOT_TYPE_CUSTOMER��ı�ע����������ΪCreateCustomerData*
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������������
				TC_ERROR����������

	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_create_update(CONF_HANDLE handle, COMPONENT_IID ciid,TUP_VOID* pdata);		

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_create_done
	��������  : ��ע������������Ҫ����DS_ANNOT_TYPE_DRAWING��DS_ANNOT_TYPE_CUSTOMER
				���ֱ�ע�������ֱ�ע������øýӿ�����ɴ�������ע������ɺ�
				��������߻��յ�������ע��֪ͨ��
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				bCancel: �����������Ǵ�����ɣ�0����ɴ�����1��ȡ��������
						 ��ɴ�����ñ�ע����ӵ�������ҳ���ϣ�ȡ���������ɾ���ñ�ע
	�������  : ret_annoid: ������ɺ�ͨ���ò������ظñ�ע��ID�����ΪNULL�򲻷���
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_create_done(CONF_HANDLE handle, COMPONENT_IID ciid,TUP_BOOL bCancel,TUP_UINT32* ret_annoid);		

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_laserpointer_start
	��������  : ��ʼ�����
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				dispSize: ��ʾ�ļ����Ĵ�С��TWIPSΪ��λ����bLocalΪ1ʱ����С�������ʼ����Դʱ�������ʾ�����ͬ
				bLocal: �Ƿ�ʹ���Ѿ�ͨ��conf_annotation_init_resource��ʼ������Դ��0����ʹ�ã�1��ʹ��
				localIndex: bLocalΪ1ʱ���ò�����Ч����ʾ��ԴID
				picFormat: bLocalΪ0ʱ��Ч����ʾ�����ͼ���ͼƬ��ʽ
				pData: bLocalΪ0ʱ��Ч��ͼƬ����ָ��
				dataLen: bLocalΪ0ʱ��Ч��ͼƬ���ݵĳ���
				picW: LocalΪ0ʱ��Ч��ͼƬ�Ŀ�����Ϊ��λ
				picH: bLocalΪ0ʱ��Ч��ͼƬ�ĸߣ�����Ϊ��λ
				ptOffset: bLocalΪ0ʱ��Ч����ʾͼƬ���ĵ���������Ͻǵ�ƫ�ƣ���TWIPSΪ��λ��
						  ��ֵ����������¶��ڹ̶���С�ı�ע�����ã�����ʱ���Ը�ֵΪ���ĵ㣬
						  ���¼������ź��ͼƬ���Ͻ���㣬�����Ƕ����Ͻ����ֱ�ӽ������š�
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_laserpointer_start(CONF_HANDLE handle, COMPONENT_IID ciid, 
		TC_SIZE dispSize, TUP_INT bLocal, TUP_INT localIndex, TUP_INT picFormat, TUP_VOID* pData, TUP_INT dataLen, TUP_INT picW, TUP_INT picH, TC_POINT ptOffset);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_laserpointer_moveto
	��������  : 
	�������  : handle: ������ 
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				point: �ƶ����ĵ㣨�������������꣩����TWIPSΪ��λ���Ҹ�ֵ�����������ҳ�����Ͻǲ�������������µ�ֵ����������Ϊ��
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_DS_ERROR_DE_NOTEXIST�������δ����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_laserpointer_moveto(CONF_HANDLE handle,COMPONENT_IID ciid, TC_POINT point);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_laserpointer_stop
	��������  : ��������㣬ֻ�ܽ����Լ��ļ����
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_DS_ERROR_DE_NOTEXIST�������δ����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_laserpointer_stop(CONF_HANDLE handle, COMPONENT_IID ciid);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_text_create
	��������  : �������ֱ�ע
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				docid: �ĵ���ID
				pageid: ҳ��ID
				pInfo: ���ֱ�ע����Ϣ
	�������  : ret_annoid: �����ɹ���ͨ���ò������ش����ɹ��ı�ע��ID������ò���ΪNULL�򲻷���
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_PARAM_ERROR����������
				TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
				TC_DS_ERROR_PAGE_NOTEXIST��ҳ�治����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_text_create(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, 
		DsAnnotTextInfo* pInfo, TUP_UINT32* ret_annoid);	

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_text_update
	��������  : �������ֱ�ע
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				docid: �ĵ���ID
				pageid: ҳ��ID
				annoid: Ҫ���µ����ֱ�ע��ID
				pInfo: ���ֱ�ע����Ϣ
				redraw: ���³ɹ����Ƿ������ػ棬0�����ػ棬1���ػ�
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_PARAM_ERROR����������
				TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
				TC_DS_ERROR_PAGE_NOTEXIST��ҳ�治����
				TC_DS_ERROR_DE_NOTEXIST����ע������
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_text_update(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, TUP_UINT32 annoid, DsAnnotTextInfo* pInfo, TUP_BOOL redraw);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_text_getinfo
	��������  : ��ȡһ�����ֱ�ע����Ϣ
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				docid: �ĵ���ID
				pageid: ҳ��ID
				annoid: ���ֱ�ע��ID
	�������  : pInfo: ͨ���ò������ػ�ȡ�������ֱ�ע��Ϣ�����ΪNULL�򷵻ش���
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_PARAM_ERROR����������
				TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
				TC_DS_ERROR_PAGE_NOTEXIST��ҳ�治����
				TC_DS_ERROR_DE_NOTEXIST����ע������
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_text_getinfo(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, TUP_UINT32 annoid, DsAnnotTextInfo* pInfo);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_edit_start
	��������  : ��ʼ�༭��ע����Ҫָ��ע���ƶ����������
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				docid: �ĵ���ID
				pageid: ҳ��ID
				annotids: Ҫ�༭�ı�עid����
				count:annotids����Ԫ�صĸ���
				refannotid:�����עһ��༭ʱ�õ��ģ���ʾ��ʱ���������ڵı�עID
				edittype: �༭����
				startpoint: �༭��ʼ�ĵ㣬��TWIPSΪ��λ���Ҹ�ֵ�����������ҳ�����Ͻǲ�������������µ�ֵ����������Ϊ��
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
				TC_DS_ERROR_PAGE_NOTEXIST��ҳ�治����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_edit_start(CONF_HANDLE handle, 
		COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, TUP_UINT32* annotids, TUP_INT32 count, 
		TUP_UINT32 refannotid, DS_HITTEST_CODE edittype, TC_POINT startpoint);	

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_edit_update
	��������  : �༭��ע�����е����ݸ���
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				currentpoint: �ƶ����ĵ㣬��TWIPSΪ��λ���Ҹ�ֵ�����������ҳ�����Ͻǲ�������������µ�ֵ����������Ϊ��
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_edit_update(CONF_HANDLE handle, COMPONENT_IID ciid,TC_POINT currentpoint);	

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_edit_done
	��������  : ��ע�༭��ɣ��༭��ע������ô˺������ܽ���
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				cancel: �Ƿ�ȡ��������0����1����
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_edit_done(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_BOOL cancel);					    

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_hittest
	��������  : ����һ�����Ƿ����ڱ�ע�ϣ�������ڱ�ע���򷵻ظñ�ע��ID�����ͼ�����λ��
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				docid: �ĵ���ID
				pageid: ҳ��ID
				pt: Ҫ�жϵĵ㣬��TWIPS�Ե�λ���ұ����������ҳ��ԭ�������ŵ�����
				hitmode: ��������
				userid: �û�ID����hitModeΪDS_HITTEST_MODE_OTHERS��DS_HITTEST_MODE_SOMEONEʱ��Ч
	�������  : selectId: ���Ҫ���Եĵ�ѡ����ĳ����ע��ͨ����ֵ����
				hit_result: ���Խ��
				annotType: ���еı�ע�ı�ע����ͨ���ò�������
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_hittest(CONF_HANDLE handle, 
		COMPONENT_IID ciid, 
		TUP_UINT32 docid, 
		TUP_UINT32 pageid, 
		TC_POINT pt, 
		TUP_INT32 hitmode, 
		TUP_UINT32 userid, 
		TUP_UINT32* selectId, 
		DS_HITTEST_CODE* hit_result, 
		TUP_UINT32* annotType);	

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_hittest_rect
	��������  : ����һ�����ο�����ı�ע�����ر����ο�����ı�עID������
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				docid: �ĵ���ID
				pageid: ҳ��ID
				rect: Ҫ���Եľ���
				hitmode: ��������
				userid: �û�ID����hitModeΪDS_HITTEST_MODE_OTHERS��DS_HITTEST_MODE_SOMEONE��
					    DS_HITTEST_MODE_OTHERS_FORCE��DS_HITTEST_MODE_SOMEONE_FORCEʱ��Ч
	�������  : selectids: ͨ���ò������ر�ѡ�еı�ע������ָ�룬Ӧ�ò㲻���ͷŸ��ڴ�
				count: ͨ���ò�������ѡ�б�ע�����е�Ԫ�ظ���
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_hittest_rect(CONF_HANDLE handle, 
		COMPONENT_IID ciid, 
		TUP_UINT32 docid, 
		TUP_UINT32 pageid, 
		TC_RECT2* rect, 
		TUP_INT32 hitmode, 
		TUP_UINT32 userid, 
		TUP_UINT32** selectids, 
		TUP_INT* count);	

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_setselect
	��������  : ���ñ�ע��ѡ��״̬
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				docid: �ĵ���ID
				pageid: ҳ��ID
				ids: Ҫ���õı�עԪ��id������
				count: ids�е�Ԫ�ظ���
				selectmode: ѡ�е�ģʽ
				userid: �û�ID����selectMode��ֵΪDS_SELECT_MODE_OTHERS��DS_SELECT_MODE_SOMEONEʱ��Ч
				redraw: ����ѡ��״̬���Ƿ������ػ棬1���ǣ�0����
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
				TC_DS_ERROR_PAGE_NOTEXIST��ҳ�治����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_setselect(CONF_HANDLE handle, 
		COMPONENT_IID ciid, 
		TUP_UINT32 docid, 
		TUP_UINT32 pageid, 
		TUP_UINT32* ids, 
		TUP_INT32 count, 
		TUP_INT32 selectmode, 
		TUP_UINT32 userid, 
		TUP_BOOL redraw);	

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_delete
	��������  : ɾ����ע
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				docid: �ĵ���ID
				pageid: ҳ��ID
				ids: Ҫɾ���ı�עԪ��id����
				count: ids�е�Ԫ�ظ���
	�������  : ��
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_DS_ERROR_DOC_NO_INIT���ĵ�����ģ��δ����ʼ��
				TC_DS_ERROR_DOC_NO_SINK��δ���ûص�����
				TC_DS_ERROR_DOC_NO_SESSION_JOIN���ĵ�����Ựδ����
				TC_DS_ERROR_DOC_USER_OFFLINE���û�����
				TC_DS_ERROR_DOC_NOTEXIST���ĵ�������
				TC_DS_ERROR_PAGE_NOTEXIST��ҳ�治����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_delete(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, TUP_UINT32* ids, TUP_INT32 count);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_set_pen
	��������  : ���û�������
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				pentype: Ҫ���õıʵ����ͣ���ͨ�ʻ������
				newpen: Ҫ���õĻ��ʵ�����
	�������  : oldpen: ͨ���ò�������ԭ���Ļ��ʵ����ԣ�����ò���ΪNULL�򲻷���
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_set_pen(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_INT32 pentype, DsPenInfo newpen, DsPenInfo* oldpen);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_set_brush
	��������  : ���û�ˢ����
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				newbrush: Ҫ���õĻ�ˢ������
	�������  : oldbrush: ͨ���ò�������ԭ���Ļ�ˢ�����ԣ�����ò���ΪNULL�򲻷���
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ����
				TC_ERROR����������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_set_brush(CONF_HANDLE handle, COMPONENT_IID ciid, DsBrushInfo newbrush,DsBrushInfo* oldbrush);

	/*****************************************************************************
	�� �� ��  : tup_conf_annotation_get_annotinfo
	��������  : ��ȡָ����ע����Ϣ
	�������  : handle: ������
				ciid: ���ID��Ŀǰ��ע֧���ĵ�����Ͱװ�
				docid: �ĵ���ID
				pageid: ҳ��ID
				annotid: ��עID
	�������  : pannotinfo����ע��Ϣ�ṹ��ָ�룬���ڱ����ȡ���ı�ע��Ϣ���ò�������ΪNULL
	�� �� ֵ  : TC_OK���ɹ�
				TC_NULL_POINT������δ��������pInfo����ΪNULL��
				TC_ERROR��ָ��ciidģ�鲻�Ϸ���δ���أ�ʧ��
				TC_DS_ERROR_DOC_NOTEXIST��ָ���ĵ�������
				TC_DS_ERROR_PAGE_NOTEXIST��ָ��ҳ�治����
				TC_DS_ERROR_DE_NOTEXIST��ָ����ע������
	�ص���Ϣ  : ��
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_get_annotinfo(CONF_HANDLE handle,COMPONENT_IID ciid,TUP_UINT32 docid,TUP_UINT32 pageid,
														TUP_UINT32 annotid,DsAnnotInfo* pannotinfo);	

#ifdef __cplusplus
};


#endif

#endif