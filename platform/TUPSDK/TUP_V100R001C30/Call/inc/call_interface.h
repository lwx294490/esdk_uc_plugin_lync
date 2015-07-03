/*******************************************************************************
 *               Copyright (C) 2011, Huawei Tech. Co., Ltd.
 *                      ALL RIGHTS RESERVED
 *******************************************************************************/

/**
 *
 *  @{
 */

#ifndef __CALL_INTERFACE_H__
#define __CALL_INTERFACE_H__

/*******************************************************************************
 *   ���ļ���Ҫ����������ͷ�ļ�
 *******************************************************************************/
#include "tup_def.h"
#include "call_def.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/**
 * <b>Description:</b> This method is used to initialize the call component.
 * <br><b>Purpose:</b> This function is invoked to initialize interfaces of the call component before an audio or video call service is used.
 * Generally, it is invoked during system initialization.
 */
TUP_API TUP_RESULT tup_call_init(TUP_VOID);


/**
 * <b>Description:</b> This method is used to destroy the call component.
 * <br><b>Purpose:</b> Generally, the UI doesn't need to invoke this function.
 */
TUP_API TUP_RESULT tup_call_uninit(TUP_VOID);


/**
 * <b>Description:</b> This method is used to register the handle function of a notification,
 * which will be invoked as the notification.
 * <br><b>Purpose:</b> During the initialization, UI invoke this interface to set the handle function of a notification,
 * when receiving the notification, it will perform the function.*/

/*This function  will create one thread*/
TUP_API TUP_RESULT tup_call_register_process_notifiy(CALL_FN_CALLBACK_PTR callback_process_notify);


/**
 * <b>Description:</b> This method is used to register the log function .
 * <br><b>Purpose:</b> During the initialization, UI invoke this interface to set the log function 
 */
TUP_API TUP_VOID   tup_call_register_logfun(CALL_FN_DEBUG_CALLBACK_PTR callback_log);


/**
 * <b>Description:</b> This method is used to register to call server
 * <br><b>Purpose:</b> 
 * 
 * @param [in] number Specifies the phone number
 * @param [in] name Specifies the user name for authentication,only used in IMS now
 * @param [in] password Specifies the password of */

TUP_API TUP_RESULT tup_call_register(const TUP_CHAR* number, const TUP_CHAR* name, const TUP_CHAR* password);


/**
 * <b>Description:</b> This method is used to deregister from call server.
 * <br><b>Purpose:</b> The UI invokes this method to deregister from the call server when the UI exits the program
 * and changes the account.
  */
TUP_API TUP_RESULT tup_call_deregister(const TUP_CHAR* number);


/**
 * <b>Description:</b> This method is used to initiate a VoIP call.
 * <br><b>Purpose:</b> The UI invokes this method to initiate a VoIP call. For example, when a user initiates a VoIP call
 * the UI invokes this method and then switches the dialing page to the calling page.
 * @param [in] callee_number Specifies the callee number.
 * @param [in] call_type Specifies the call is audio or vedio.
 * @param [out ]  callid   Indicates the Call ID
 */
TUP_API TUP_RESULT tup_call_start_call(TUP_UINT32 *callid,CALL_E_CALL_TYPE call_type,const TUP_CHAR* callee_number);

TUP_API TUP_RESULT tup_call_start_call_ex(CALL_S_CALL_PARAMS* pstCallParams);

TUP_API TUP_RESULT tup_call_start_call_bycallid_ex(const CALL_S_CALL_PARAMS* pstCallParams);

/**
 * <b>Description:</b> This method is used to answer an audio or video call.
 * <br><b>Purpose:</b> When receiving an audio or video call, the UI invokes this method to answer the call. 
 * @param [in] callid Specifies the CALL ID coming from 
 * @param [in] is_video  If the incoming call is  is a video call, is_video  is used to indicate if connect the call with video, if TURE,
 *   the UI need to create the local video view and the remote video view before invoking this method.
 * 
 */

TUP_API TUP_RESULT tup_call_accept_call(TUP_UINT32 callid,TUP_BOOL is_video);

/**
 * <b>Description:</b> This method is used to terminate a call.
 * <br><b>Purpose:</b> The UI invokes this method to terminate a call. The UI can invoke this method to cancel an outgoing call,
 * decline an incoming call or terminate a connected call. 
 * @param [in] callid Specifies the CALL ID 
 */
TUP_API TUP_RESULT tup_call_end_call(TUP_UINT32 callid);


/**
 * <b>Description:</b> This method is used to alerting a call and tell the peer I am ringing now
 * <br><b>Purpose:</b> The UI invokes this method after play ringtone when  received a incoming call, to terminate a call. l,
 * @param [in] callid Specifies the CALL ID 
 */

TUP_API TUP_RESULT tup_call_alerting_call(TUP_UINT32 callid);


/**
 * <b>Description:</b> This method is used to get the connetted call's statics information
 * <br><b>Purpose:</b>
 * @param [out] statics specifies the call statics information
 */
TUP_API TUP_RESULT tup_call_get_callstatics(CALL_S_STREAM_INFO* statics);


/**
 * <b>Description:</b> This method is used to get the connetted call's media statics information
 * <br><b>Purpose:</b>
 * @param [out] statics specifies the call's media session statics information
 */
TUP_API TUP_RESULT tup_call_get_channelinfo(TUP_UINT32 accountid, CALL_S_STREAM_INFO* streaminfo);


/**
 * <b>Description:</b> This method is used to send a DTMF character.
 * <br><b>Purpose:</b> When a character is entered on the DTMF keyboard during an audio or video call, the UI invokes this method to
 * send the character to the server.
 * @param [in] callid Specifies the CALL ID.
 * @param [in] tone Specifies DTMF type (i.e. the entered DTMF character).

 */
TUP_API TUP_RESULT tup_call_send_DTMF(TUP_UINT32 callid,CALL_E_DTMF_TONE tone);


/**
 * <b>Description:</b> This method is used to hold an audio call.
 * <br><b>Purpose:</b> The UI invokes this method to hold an audio call. Before this method is invoked, the current call status
 * must be @ref EN_CAAS_CALL_STATUS_CONNECTED and the call type must be @ref EN_CAAS_CALL_TYPE_AUDIO. After this method is invoked,
 * the two parties cannot talk with each other or hear each other, and the one held can hear a tone played by the server.
 * @param [in] dwCallId Specifies the CALL ID.
 * @param [in] dwCookie Specifies the cookie of the UI. It may be used to store anything, which is then passed back in notifications.
 * If the UI doesn't need to store anything, it can enter a zero here.
 * @return CAAS_OK Indicates operation succeeds
 *     <br>CAAS_FAILED Indicates operation fails
 * @see CAAS_CallUnHold
 */
TUP_API TUP_RESULT tup_call_hold_call(TUP_UINT32 callid);

/**
 * <b>Description:</b> This method is used to resume the held call.
 * <br><b>Purpose:</b> The UI invokes this method to resume a held audio call. Before this method is invoked, the current call status
 * must be @ref EN_CAAS_CALL_STATUS_CONNECTED and the call type must be @ref EN_CAAS_CALL_TYPE_AUDIO. After this method is invoked,
 * the held call resumes (the two parties can talk with each other).
 * @param [in] dwCallId Specifies the CALL ID
 * @param [in] dwCookie Specifies the cookie of the UI. It may be used to store anything, which is then passed back in notifications.
 * If the UI doesn't need to store anything, it can enter a zero here.
 * @return CAAS_OK Indicates operation succeeds
 *     <br>CAAS_FAILED Indicates operation fails
 * @see CAAS_CallHold
 */
TUP_API TUP_RESULT tup_call_unhold_call(TUP_UINT32 callid);


TUP_API TUP_RESULT tup_call_create_video_window(TUP_UINT32 Count, const CALL_S_VIDEOWND_INFO* window);

TUP_API TUP_RESULT tup_call_destroy_video_window(CALL_E_VIDEOWND_TYPE wndtype);


/* ˢ����Ƶ���� */
TUP_API TUP_RESULT tup_call_update_video_window(TUP_UINT32 count, const CALL_S_VIDEOWND_INFO * window, TUP_UINT32 ulCallID);


TUP_API TUP_RESULT tup_call_change_video_window_pos(CALL_E_VIDEOWND_TYPE wndtype, const TUP_INT32 coordinate[CALL_E_COORDINATE_BUTT]);
TUP_API TUP_RESULT tup_call_change_video_window_type(CALL_E_VIDEOWND_TYPE wndtype, TUP_UINT32 displaytype);

/**
 * <b>Description:</b> This method is used to accept or reject  the request for switching an audio call to a video call.
 * <br><b>Purpose:</b> During an audio call, the UI invokes this method to accept or reject the request for switching an audio call to
 * a video call. 
 * @param [in] callid Specifies the CALL ID.
 * @param [in] is_accept Specifies if accept the add video request
 */
TUP_API TUP_RESULT tup_call_reply_add_video(TUP_UINT32 callid,TUP_BOOL is_accept);

/**
 * <b>Description:</b> This method is used to accept or reject  the request for switching an video call to a audio call.
 * <br><b>Purpose:</b> During an video call, the UI invokes this method to accept or reject the request for switching an video call to
 * a audio call. 
 * @param [in] callid Specifies the CALL ID.
 * @param [in] is_accept Specifies if accept the delete video request
 */
TUP_API TUP_RESULT tup_call_reply_del_video(TUP_UINT32 callid,TUP_BOOL is_accept);


/**
 * <b>Description:</b> This method is used to request for switching an audio call to a video call.
 * <br><b>Purpose:</b> During an audio call, the UI invokes this method to request the peer party to switch to a video call.
 * @param [in] callid Specifies the CALL ID.
 */
TUP_API TUP_RESULT tup_call_add_video(TUP_UINT32 callid);

/**
 * <b>Description:</b> This method is used to switch a video call to an audio call.
 * <br><b>Purpose:</b> During a video call, the UI invokes this method to switch a video call to an audio call.
 * @param [in] callid Specifies the CALL ID.
 */
TUP_API TUP_RESULT tup_call_del_video(TUP_UINT32 callid);


/*��������Ԥ�����ڲ���*/
/**
 * <b>Description:</b> This method is used to create the preview window and open it.
 * <br><b>Purpose:</b> .
 */
TUP_API TUP_RESULT tup_call_open_preview(TUP_UINT32 ulHandle, TUP_UINT32 ulIndex);


/*�رձ���Ԥ�����ڲ�ɾ��*/
/**
 * <b>Description:</b> This method is used to close the preview window and delete it.
 * <br><b>Purpose:</b> .
 */
TUP_API TUP_RESULT tup_call_close_preview(TUP_VOID);

/*�����������*/
TUP_API TUP_RESULT tup_call_media_set_speak_volume(CALL_E_AO_DEV dev, TUP_UINT32 volume);


/*������Ƶ����豸*/
TUP_API TUP_RESULT tup_call_media_set_audio_outdev(CALL_E_AUDDEV_ROUTE route_dev);


/*������Ƶ�����豸*/
TUP_API TUP_RESULT tup_call_media_set_audio_indev(CALL_E_AUDDEV_ROUTE route_dev);

/*���� �����豸*/
TUP_API TUP_RESULT tup_call_media_mute_mic(TUP_UINT32 callid, TUP_BOOL is_on);

/*�� ��Ƶ*/
TUP_API TUP_RESULT tup_call_media_mute_video(TUP_UINT32 callid,TUP_BOOL is_on);

/* ��������¼�� */
TUP_API TUP_RESULT tup_call_media_startrecord(TUP_UINT32 callid, const TUP_CHAR* pcFileName, TUP_BOOL bIsVideo);

/* ֹͣ����¼�� */
TUP_API TUP_RESULT tup_call_media_stoprecord(TUP_UINT32 callid);

/* �������� */
TUP_API TUP_RESULT tup_call_media_startplay(TUP_UINT32 ulLoops, const TUP_CHAR* pcPlayFile, TUP_INT32* plPlayHandle);

/* ����TC���� */
TUP_API TUP_RESULT tup_call_media_startTcplay(TUP_INT32 iTcFileValue, TUP_INT32* plPlayHandle);

/* ֹͣ�������� */
TUP_API TUP_RESULT tup_call_media_stopplay(TUP_INT32 lPlayHandle);

/* ����ʹ�õ���˷��豸 */
TUP_API TUP_RESULT tup_call_media_set_mic_index(TUP_UINT32 index);

/* ����ʹ�õ��������豸 */
TUP_API TUP_RESULT tup_call_media_set_speak_index(TUP_UINT32 index);

/* ����ʹ�õ���Ƶ�豸 */
TUP_API TUP_RESULT tup_call_media_set_video_index(TUP_UINT32 index);

TUP_API TUP_RESULT tup_call_media_get_mic_index(TUP_UINT32* pulIndex);

TUP_API TUP_RESULT tup_call_media_get_speak_index(TUP_UINT32* pulIndex);

TUP_API TUP_RESULT tup_call_media_get_video_index(TUP_UINT32* pulIndex);

/*****************************************************************************
 �� �� ��  : tup_call_media_get_devices
 ��������  : ��ȡ�豸�б�
 �������  : CALL_E_DEVICE_TYPE eDeviceType
            CALL_E_CALL_DEVICE_MIC,         ��˷��豸
            CALL_E_CALL_DEVICE_SPEAK,       �������豸
            CALL_E_CALL_DEVICE_VIDEO,       ��Ƶ�豸
            CALL_E_CALL_DEVICE_BUTT         ��Ч�豸 
 �������  : CALL_S_DEVICEINFO*    �豸���ݽṹ����ڴ�ָ�룬���ڴ�������ϲ����

 �������������TUP_UINT32* puiNum    ���룺�ϲ������豸����
                                     �������ȡ�����豸����

 �� �� ֵ  : TUP_RESULT
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��11��
    ��    ��   : liangxinlian 00206336
    �޸�����   : �����ɺ���
*****************************************************************************/
TUP_API TUP_RESULT tup_call_media_get_devices(TUP_UINT32* puiNum, CALL_S_DEVICEINFO* pstDeviceInfo, CALL_E_DEVICE_TYPE eDeviceType);

/*�������ƫת����
ƫת: �û������в�����ͨ����ϵ��������ֱ��ת���������û�*/


/**
 * <b>Description:</b> This method is used to divert the incoming call.
 * <br><b>Purpose:</b> 
 * @param [in] callid Specifies the incoming Call ID
 * @param [in] divert_number Specifies the number to divert.
 */
TUP_API TUP_RESULT tup_call_divert_call(TUP_UINT32 callid,const TUP_CHAR* divert_number);


/**
 * <b>Description:</b> This method is used to blind transfer to other number.
 * <br><b>Purpose:</b> 
 * @param [in] callid Specifies the Call ID
 * @param [in] transto_number Specifies the number to transfer.
 */
TUP_API TUP_RESULT tup_call_blind_transfer(TUP_UINT32 callid,const TUP_CHAR* transto_number);


/**
 * <b>Description:</b> This method is used to consult transfer to other number.
 * <br><b>Purpose:</b> 
 * @param [in] callid Specifies the Call ID
 * @param [in] transto_number Specifies the number to transfer.
 */
TUP_API TUP_RESULT tup_call_consult_transfer(TUP_UINT32 callid,const TUP_UINT32 transto_callid);

/*�Ǽ�ҵ��*/
TUP_API TUP_RESULT tup_call_set_IPTservice(CALL_E_SERVICE_CALL_TYPE type,void* data);

/*ctd service*/
TUP_API TUP_RESULT tup_call_ctd_get_list(TUP_VOID);

/*****************************************************************************
 ��������  : �Ǽ�privacyҵ��
*****************************************************************************/
TUP_API TUP_RESULT  tup_call_set_privacy_on(TUP_UINT32 account_id);

/*****************************************************************************
 ��������  : ע��privacyҵ��
*****************************************************************************/
TUP_API TUP_RESULT  tup_call_set_privacy_off(TUP_UINT32 account_id);


/**
 * <b>Description:</b> This method is used to set configuration information.
 * <br><b>Purpose:</b> The UI invokes this method to set configuration information based on different parameters. The configuration
 * takes effect after call tup_call_commit_cfg.
 * @param [in] major  Specifies Major type 
 * @param [in] minor  Specifies Minor type 
 * @param [in] value  Specifies The value.
 * @param [in] size  Specifies The value size. 
 */

TUP_API TUP_RESULT tup_call_set_cfg(TUP_UINT32 cfgid, TUP_VOID * val);



/**
 * <b>Description:</b> This method is used to get configuration information.
 * <br><b>Purpose:</b> The UI invokes this method to set configuration information based on different parameters. The configuration
 * takes effect on subsequent calls.
 * @param [in] major  Specifies Major type 
 * @param [in] minor  Specifies Minor type 
 * @param [in] value  Specifies The value.
 * @param [in] size  Specifies The value size. 
 */

TUP_API TUP_RESULT tup_call_get_cfg(TUP_UINT32 cfgid,TUP_VOID* val,  TUP_UINT32 size);

TUP_API TUP_RESULT tup_call_commit_cfg(TUP_VOID);

//////////////////////////////////////////////////////////////////////////
//PC�˵��õ�������ؽӿ� - ά��������zhubin

/*������������*/
TUP_API TUP_RESULT tup_call_joint_setting(TUP_UINT32 accountid, TUP_BOOL right, const char* linkage_number);

/*��������*/
TUP_API TUP_RESULT tup_call_joint_start(TUP_VOID);

/*�ر�����*/
TUP_API TUP_RESULT tup_call_joint_stop(TUP_VOID);

/*���������л�*/
TUP_API TUP_RESULT tup_call_joint_switch(TUP_VOID);

/*ͨ��ת����*/
TUP_API TUP_RESULT tup_call_joint_uptoconference(TUP_VOID);

/*�򻰻�֪ͨ������*/
TUP_API TUP_RESULT tup_call_joint_conf_result(TUP_UINT32 result);

//////////////////////////////////////////////////////////////////////////
//������������ؽӿ� - ά��������zhubin

/*�½�����id*/
/**
 * <b>Description:</b> This method is used to create confid and callid.
 * <br><b>Purpose:</b> The UI invokes this method to create a conference id and its corresponding call id. 
 * @param [out] *confid Indicates the Conference ID.
 * @param [out] *callid Indicates the Call ID.
 */
TUP_API TUP_RESULT tup_call_serverconf_create_confid(TUP_UINT32 *confid, TUP_UINT32 *callid);

/*���û������� - ������ʹ�ã��ڴ���֮ǰ����,�Կ��ƴ������������*/
/**
 * <b>Description:</b> This method is used to set conference type to be created.
 * <br><b>Purpose:</b> This method is for IPPhone to invoke before creating conference.
 * @param [in] confid Specifies the conference.
 * @param [in] type Specifies the conference type.
 */
TUP_API TUP_RESULT tup_call_serverconf_set_type(TUP_UINT32 confid, CALL_E_SERVERCONF_TYPE type);

/*���ݻ���id�½�����*/
/**
 * <b>Description:</b> This method is used to create conference by confid.
 * <br><b>Purpose:</b> This method is for IPPhone to invoke to create conference.
 * @param [in] confid Specifies the conference.
 * @param [in] *groupuri Specifies group URI if group is exist.
 */
TUP_API TUP_RESULT tup_call_serverconf_create_by_confid(TUP_UINT32 confid, const TUP_CHAR *groupuri);

/*�½����飬�ۺ����������ӿ�*/
/**
 * <b>Description:</b> This method is used to create conference directly, no need to invoke tup_call_serverconf_create_confid and tup_call_serverconf_create_by_confid separately.
 * <br><b>Purpose:</b> The UI invokes this method to create a conference id and its corresponding call id.
 * @param [out] *confid Indicates the Conference ID.
 * @param [out] *callid Indicates the Call ID.
 * @param [in] *groupuri Specifies group URI if group is exist.
 */
TUP_API TUP_RESULT tup_call_serverconf_create(TUP_UINT32 *confid, TUP_UINT32 *callid, const TUP_CHAR *groupuri);

/*����*/
/**
 * <b>Description:</b> This method is used add attendees for chairman after conference is joined.
 * <br><b>Purpose:</b> The UI invokes this method to add attendees to the conference.
 * @param [in] confid Specifies the conference.
 * @param [in] count Specifies the count of attendees to add.
 * @param [in] *number Specifies memory point which store the attendee number. the space of is is count*persize.
 * @param [in] persize Specifies max size of each attendee number.
 */
TUP_API TUP_RESULT tup_call_serverconf_add_attendee(TUP_UINT32 confid,TUP_UINT32 count,const TUP_CHAR *number,TUP_UINT32 persize);

/*����*/
/**
 * <b>Description:</b> This method is used for chairman to kick a attendee already in conference.
 * <br><b>Purpose:</b> The UI invokes this method to kick a attendee.
 * @param [in] confid Specifies the conference.
 * @param [in] *number Specifies memory point which store the attendee number to be kicked.
 */
TUP_API TUP_RESULT tup_call_serverconf_kick_attendee(TUP_UINT32 confid,const TUP_CHAR* number);

/*�޸�����߷���Ȩ��*/
/**
 * <b>Description:</b> This method is used for chairman to modify the speaking right of a attendee already in conference.
 * <br><b>Purpose:</b> The UI invokes this method to modify the attendee's speaking right.
 * @param [in] confid Specifies the conference.
 * @param [in] *number Specifies memory point which store the attendee number to be kicked.
 * @param [in] right Specifies the speaking right, 0 is no right to speak.
 */
TUP_API TUP_RESULT tup_call_serverconf_modify_right(TUP_UINT32 confid,const TUP_CHAR* number,TUP_UINT32 right);

/*�᳡������ȡ���᳡����*/
/**
 * <b>Description:</b> This method is used for chairman to modify conference mute status.
 * <br><b>Purpose:</b> The UI invokes this method to change conference mute status.
 * @param [in] confid Specifies the conference.
 * @param [in] muted Specifies the conference muted status, 0 is unmuted and 1 is muted.
 */
TUP_API TUP_RESULT tup_call_serverconf_mute(TUP_UINT32 confid, TUP_BOOL muted);

/*�᳡������ȡ���᳡����*/
/**
 * <b>Description:</b> This method is used for chairman to modify conference locked status.
 * <br><b>Purpose:</b> The UI invokes this method to change conference lock status.
 * @param [in] confid Specifies the conference.
 * @param [in] locked Specifies the conference locked status, 0 is unlocked and 1 is locked.
 */
TUP_API TUP_RESULT tup_call_serverconf_lock(TUP_UINT32 confid, TUP_BOOL locked);

/*�뿪����*/
/**
 * <b>Description:</b> This method is used to leave conference.
 * <br><b>Purpose:</b> The UI invokes this method to leave conference.
 * @param [in] confid Specifies the conference.
 */
TUP_API TUP_RESULT tup_call_serverconf_leave(TUP_UINT32 confid);

/*��������*/
/**
 * <b>Description:</b> This method is used for chairman to end the conference.
 * <br><b>Purpose:</b> The UI invokes this method to end the conference.
 * @param [in] confid Specifies the conference.
 */
TUP_API TUP_RESULT tup_call_serverconf_end(TUP_UINT32 confid);

/*������������*/
/**
 * <b>Description:</b> This method is used to accept a conference calling.
 * <br><b>Purpose:</b> The UI invokes this method to accept a conference calling.
 * @param [in] confid Specifies the conference.
 */
TUP_API TUP_RESULT tup_call_serverconf_accept(TUP_UINT32 confid); 

/*���ֻ���*/
/**
 * <b>Description:</b> This method is used to hold a conference.
 * <br><b>Purpose:</b> The UI invokes this method to hold a conference.
 * @param [in] confid Specifies the conference.
 */
TUP_API TUP_RESULT tup_call_serverconf_hold(TUP_UINT32 confid); 

/*ȡ������*/
/**
 * <b>Description:</b> This method is used to unhold a conference.
 * <br><b>Purpose:</b> The UI invokes this method to accept a conference.
 * @param [in] confid Specifies the conference.
 */
TUP_API TUP_RESULT tup_call_serverconf_unhold(TUP_UINT32 confid);

/*2��ͨ��ת����*/
/**
 * <b>Description:</b> This method is used to transfer a call to a conference, you need create conference first.
 * <br><b>Purpose:</b> 
 * @param [in] confid Specifies the conference.
 * @param [in] callid Specifies the call need to be transfered.
 */
TUP_API TUP_RESULT tup_call_serverconf_transferto_conf(TUP_UINT32 confid,TUP_UINT32 callid);

/*��refer���̵�2��ͨ��ת����*/
/**
 * <b>Description:</b> This method is used to transfer a call to a conference.
 * <br><b>Purpose:</b> 
 * @param [in] callid Specifies the call need to be transfered.
 * @param [out] *confid Indicates the Conference ID which has been created.
 * @param [in] *groupuri Specifies group URI if group is exist.
 * @deprecated this method is transitive for compatibility between USM and PC terminal. 
 */
TUP_API TUP_RESULT tup_call_serverconf_transferto_conf_non_refer(TUP_UINT32 callid, TUP_UINT32 *confid, const TUP_CHAR *groupuri);

/*��������ת���ݻ���*/
/**
 * <b>Description:</b> This method is used to transfer a audio conference to a data conference.
 * <br><b>Purpose:</b> 
 * @param [in] confid Specifies the conference.
 */
TUP_API TUP_RESULT tup_call_serverconf_transferto_dataconf(TUP_UINT32 confid);

/* ��Ե�ֱ��ת��ý����� */
/**
 * <b>Description:</b> This method is used to transfer a p2p audio call to a data conference, the p2p audio is still keeping.
 * <br><b>Purpose:</b> 
 * @param [out] *callid Indicates the Call ID responding the conference.
 * @param [out] *confid Indicates the Conference ID which has been created.
 * @param [in] p2p_callid Specifies p2p call.
 * @param [in] *groupuri Specifies group URI if group is exist.
 */
TUP_API TUP_RESULT tup_call_serverconf_p2p_transferto_dataconf(TUP_UINT32* confid, TUP_UINT32* callid, TUP_UINT32 p2p_callid, const TUP_CHAR* groupuri);

/*����ԤԼ����*/
/**
 * <b>Description:</b> This method is used to access a reserved conference.
 * <br><b>Purpose:</b> 
 * @param [out] *callid Indicates the Call ID responding the reserved conference.
 * @param [in] *accesscode Specifies the conference access code, which is combined with access number(e.g. 123456), 
                conference number(e.g.888888) and security number(e.g.999999), e.g. accesscode(123456888888*999999#)
 */
TUP_API TUP_RESULT tup_call_serverconf_access_reservedconf(TUP_UINT32 *callid, const TUP_CHAR *accesscode/*, CALL_E_CALL_TYPE call_type*/);

/*ֱ�ӽ���ԤԼ���飬����Ҫ����callid���ṩ���������ʺŵ������ʹ��*/
/**
 * <b>Description:</b> This method is used to access a reserved conference for IPPhone.
 * <br><b>Purpose:</b> 
 * @param [in] callid Indicates the Call ID, which is already created .
 * @param [in] *accesscode Specifies the conference access code, which is combined with access number(e.g. 123456), 
                conference number(e.g.888888) and security number(e.g.999999), e.g. accesscode(123456888888*999999#)
 */
TUP_API TUP_RESULT tup_call_serverconf_access_reserved_conf_directly(TUP_UINT32 callid, const TUP_CHAR *accesscode);

/*���û�������*/
/**
 * <b>Description:</b> This method is used to set conference subject.
 * <br><b>Purpose:</b> 
 * @param [in] confid Specifies the conference.
 */
TUP_API TUP_RESULT tup_call_serverconf_set_confsubject(TUP_UINT32 confid, const TUP_CHAR* confsubject);

/*��ȡԤԼ�����б�*/
/**
 * <b>Description:</b> This method is used to get conference list for all accounts.
 * <br><b>Purpose:</b> 
 * @param [in] confid Specifies the conference.
 */
TUP_API TUP_RESULT tup_call_get_all_conf_list(TUP_VOID);

/**
 * <b>Description:</b> This method is used to get conference list for a special account.
 * <br><b>Purpose:</b> 
 * @param [in] accountid Specifies the account to query.
 * @param [in] pagesize Specifies the max number of a conference list page.
 * @param [in] curpage Specifies current page index.
 */
TUP_API TUP_RESULT tup_call_get_conf_list_for_account(TUP_UINT32 accountid, TUP_UINT32 pagesize, TUP_UINT32 curpage);

/**
 * <b>Description:</b> This function is used to start log
 * <br><b>Purpose:</b> 
 * 
 * @param [in] logLevel Specifies the account to query.
 * @param [in] lMaxSizeKB Specifies the max size of log file.
 * @param [in] lFileCount Specifies the max number of one log file.
 * @param [in] pcLogPath Specifies the path of log.
 */
TUP_API TUP_VOID tup_call_log_start(TUP_INT32 logLevel, TUP_INT32 lMaxSizeKB, TUP_INT32 lFileCount, const TUP_CHAR* pcLogPath);

/**
 * <b>Description:</b> This function is used to stop log
 * <br><b>Purpose:</b>
 */
TUP_API TUP_VOID tup_call_log_stop(TUP_VOID);

TUP_API const TUP_CHAR* tup_call_get_err_description(TUP_UINT32 errornum);


#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif  /* __CALL_INTERFACE_H__ */

/** @}*/
