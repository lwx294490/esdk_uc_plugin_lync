
/*******************************************************************************
 *               Copyright (C) 2011, Huawei Tech. Co., Ltd.
 *                      ALL RIGHTS RESERVED
 *******************************************************************************/


/** @defgroup Module Nume: call control interface
 *  @brief   呼叫控制对UI 接口、消息、事件
 *  @author  x00111629
 *  @version 1.0
 *  @date    2011/4/3
 *
 *  \b 修订记录:
 *          -# 2011/4/3, x00111629, create this file
 *
 *  \b 模块说明:
 *
 *  此模块的详细描述...
 *
 *  @{
 */

#ifndef __CALL_ADVANCED_INTERFACE_H__
#define __CALL_ADVANCED_INTERFACE_H__


/*******************************************************************************
 *   本文件需要包含的其它头文件
 *******************************************************************************/

#include "call_advanced_def.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/*******************************************************************************
 *   宏常量定义区
*******************************************************************************/

#define IN
#define OUT



/**tup_call_digitmap_create_handle 第一个参数type取值范围*/
#define TUP_COMMON_DIGITMAP_INDEX   (0)    //立即匹配数图索引
#define TUP_REPLACE_DIGITMAP_INDEX  (1)    //替换匹配数图索引


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_digitmap_create_handle(const TUP_INT32 type, const TUP_CHAR *digit_map, TUP_INT32 *handle);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_digitmap_destroy_handle(const TUP_INT32 handle);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_digitmap_match(const TUP_INT32 handle, const char *input_num, DMRESULT *dm_result);

/*移动rsa加密功能*/

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_rsa_public_encrypt(const TUP_CHAR *src_data, const TUP_CHAR *public_key_path, TUP_CHAR **encrypt_data, TUP_INT *encrypt_len);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_VOID tup_rsa_free_public_encrypt_data(TUP_CHAR *encrypt_data);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_service_code(TUP_UINT32 ulSipAccountID, CALL_S_IPT_DATA *pstIPTData, TUP_CHAR aszCode[], TUP_UINT32 ulSize);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_register_for_account(TUP_UINT32 accountid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_deregister_for_account(TUP_UINT32 accountid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_contact_removed_indicate(TUP_UINT32 account_id, const TUP_CHAR* contact_number);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_sipserver_link_status(TUP_UINT8 serverindex);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_account_info(CALL_S_SIP_ACCOUNT_INFO* accountinfo, TUP_UINT32* count);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_account_callids(TUP_UINT32 accountid, TUP_UINT32* callids, TUP_UINT32* callsnum);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_create_callid(TUP_UINT32 account_id,  CALL_E_LINE_TYPE line_type, TUP_UINT32 lineid, TUP_UINT32* callid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_start_call_bycallid(TUP_UINT32 callid, CALL_E_CALL_TYPE call_type, const TUP_CHAR* callee_number);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_emergency_call(TUP_UINT32 callid, const TUP_CHAR* callee_number);


/*****add by l00214300:对单个 账号登记DND业务**********************/

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_DND_for_account(TUP_UINT32 accountid);


/*******add by l00214300:对单个 账号注销DNDN业务*******************/

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_cancel_DND_for_account(TUP_UINT32 accountid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_alertsilence_on(TUP_UINT32 accountid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_alertsilence_off(TUP_UINT32 account_id);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_privacy_on(TUP_UINT32 account_id);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_privacy_off(TUP_UINT32 account_id);
/* 发起reinvite重协商 */

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_reinvite(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_divert_call(TUP_UINT32 callid,const TUP_CHAR* divert_number);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_accept_call_with_lineid(TUP_UINT32 callid, TUP_UINT32 lineid, TUP_BOOL is_video);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_end_call(TUP_UINT32 callid);

//CALL_E_CAUSE_RESON

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_end_call_with_cause(TUP_UINT32 ulCallID, TUP_UINT32 ulCause);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_end_allcall(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_ctd_destroy_call(TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_all_callinfo(TUP_UINT32 callid, CALL_S_CALL_INFO* pstcallinfo);



/**
 * <b>Description:</b> This function is used to get channel info corresponding account
 * <br><b>Purpose:</b> The UI use this function to getting the calling stream info
 * 
 * @accountid [in] user login account ID 
 * @streaminfo [in] the calling stream info
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_get_channelinfo
 */
TUP_API TUP_RESULT tup_call_get_channelinfo(TUP_UINT32 accountid, CALL_S_STREAM_INFO* streaminfo);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_send_DTMF(TUP_UINT32 callid, CALL_E_DTMF_TONE tone);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_play_signaltone(TUP_UINT32 callid, CALL_E_SIGTONE_TYPE tone);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_stop_signaltone(TUP_UINT32 callid);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_hold_call(TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_unhold_call(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_pnotification_holdcall(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_pnotification_unholdcall(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_server_recordcall_on(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_server_recordcall_off(TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to record audio or video
 * <br><b>Purpose:</b> The UI use this function to record audio or video when calling.
 * 
 * @callid [in] call ID
 * @pcFileName [in] the record file name 
 * @bIsVideo [in] TUP_TRUE, record video; Otherwise, record audio.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_startrecord
 */
TUP_API TUP_RESULT tup_call_media_startrecord(TUP_UINT32 callid, const TUP_CHAR* pcFileName, TUP_BOOL bIsVideo);


/**
 * <b>Description:</b> This function is used to stop recording audio or video
 * <br><b>Purpose:</b> The UI use this function to stop recording audio or video when calling.
 * 
 * @callid [in] call ID
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_stoprecord
 */
TUP_API TUP_RESULT tup_call_media_stoprecord(TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to play the ring tone
 * <br><b>Purpose:</b> The UI use this function to play the ring tone.
 * 
 * @ulLoops [in] the loop number that the file would be played
 * @pcPlayFile [in] file name of the ring tone
 * @plPlayHandle [in, out] play handle
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_startplay
 */
TUP_API TUP_RESULT tup_call_media_startplay
(
    TUP_UINT32 ulLoops,
    const TUP_CHAR* pcPlayFile,
    TUP_INT32* plPlayHandle
);


/**
 * <b>Description:</b> This function is used to play the TC(Thin Computer) ring tone
 * <br><b>Purpose:</b> The UI use this function to play the TC ring tone.
 * 
 * @iTcFileValue [in] enum value of file. Reference the define of ENUM_TCFILE_VALUE
 * @plPlayHandle [in, out] play handle
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_startTcplay
 */
TUP_API TUP_RESULT tup_call_media_startTcplay(TUP_INT32 iTcFileValue, TUP_INT32* plPlayHandle);


/**
 * <b>Description:</b> This function is used to stop playing the TC(Thin Computer) ring tone
 * <br><b>Purpose:</b> The UI use this function to stop playing the TC ring tone.
 * 
 * @lPlayHandle [in] play handle
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_stopplay
 */
TUP_API TUP_RESULT tup_call_media_stopplay(TUP_INT32 lPlayHandle);


/**
 * <b>Description:</b> This function is used to set effective mic
 * <br><b>Purpose:</b> The UI use this function to set effective mic
 * 
 * @index [in] the mic index that would be effective
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_set_mic_index
 */
TUP_API TUP_RESULT tup_call_media_set_mic_index(TUP_UINT32 index);


/**
 * <b>Description:</b> This function is used to set effective speaker
 * <br><b>Purpose:</b> The UI use this function to set effective speaker
 * 
 * @index [in] the speaker index that would be effective
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_set_speak_index
 */
TUP_API TUP_RESULT tup_call_media_set_speak_index(TUP_UINT32 index);


/**
 * <b>Description:</b> This function is used to set effective camera
 * <br><b>Purpose:</b> The UI use this function to set effective camera
 * 
 * @index [in] the camera index that would be effective
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_set_video_index
 */
TUP_API TUP_RESULT tup_call_media_set_video_index(TUP_UINT32 index);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_tc_ipaddr(CALL_S_IF_INFO* pInetAddr);


/**
 * <b>Description:</b> This function is used to get audio mode
 * <br><b>Purpose:</b> The UI used this function to get audio mode
 * 
 * @puiAuidoMode [in, out] Recieve audio mode. See CALL_E_AUDIO_MODE.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_get_audio_mode
 */
TUP_API TUP_RESULT tup_call_get_audio_mode(TUP_UINT32* puiAuidoMode);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_tc_log(TUP_VOID);


/**
 * <b>Description:</b> This function is used to set mic mute
 * <br><b>Purpose:</b> The UI used this function to set mic mute
 * 
 * @iMute [in] Not zero, mute; Otherwise, not mute.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_set_micdev_mute
 */
TUP_API TUP_RESULT tup_call_set_micdev_mute(TUP_INT32 iMute);


/**
 * <b>Description:</b> This function is used to set speaker mute
 * <br><b>Purpose:</b> The UI used this function to set speaker mute
 * 
 * @iMute [in] Not zero, mute; Otherwise, not mute.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_set_spkdev_mute
 */
TUP_API TUP_RESULT tup_call_set_spkdev_mute(TUP_INT32 iMute);


/**
 * <b>Description:</b> This function is used to get all media devices, include mic, speaker, camera.
 * <br><b>Purpose:</b> The UI use this function to get all media devices
 * 
 * @puiNum [in, out] the device number
 * @deviceinfo [in, out] the device info
 * @devicetype [in, out] the device type
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_get_devices
 */
TUP_API TUP_RESULT tup_call_media_get_devices
(
    TUP_UINT32* puiNum, 
    CALL_S_DEVICEINFO* deviceinfo,
    CALL_E_DEVICE_TYPE devicetype
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_callback(TUP_UINT32 sipaccount_id, const TUP_CHAR* pcalleenumber);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_cancel_callback(TUP_UINT32 sipaccount_id, const TUP_CHAR* pcalleenumber);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_callpark(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_direct_callpark(TUP_UINT32 callid, const TUP_CHAR* pszdirectnum);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_callpark(TUP_UINT32 callid, CALL_E_CALL_TYPE call_type, const TUP_CHAR* pszparknum);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_blind_transfer(TUP_UINT32 callid,const TUP_CHAR* transto_number);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_consult_transfer(TUP_UINT32 callid,const TUP_UINT32 transto_callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_mobile_extend(TUP_UINT32 callid,const TUP_CHAR* MPnum);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_sipserver_info(TUP_UINT32 callid, CALL_S_CURRENT_SIPSERVER* sipserverinfo);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_sipserver_addrlist
(
    TUP_UINT32 accountid,
    TUP_UINT32* addrnum, 
    CALL_S_SIP_ADDR_INFO* sipaddrinfo
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_SCA_in_bridgeconf(TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_alerting_call(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_progkey_modify_ind(TUP_INT32 broadID, const TUP_INT32* keys, TUP_INT32 number);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_contact_status(TUP_UINT32 number, CALL_S_CONTACT_STATUS status[]);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_subscribe_contact(TUP_UINT32 accountid, TUP_UINT32 contact_type, const TUP_CHAR* contactnum);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_unsubscribe_contact(TUP_UINT32 accountid, const TUP_CHAR* contactnum);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_subscriber_RLS(TUP_UINT32 accountid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_unsubscriber_RLS(TUP_UINT32 accountid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_SCA_private(TUP_UINT32 accountid, CALL_E_SERVICE_CALL_TYPE calltype);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_reload_serviceright(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_update_serviceright(TUP_UINT32 accountid, const CALL_S_SERVICERIGHT_CFG* servicecfg);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_service_register
(
    TUP_UINT32 accountid,
    CALL_E_SERVICE_RIGHT_TYPE servicetype,
    TUP_UINT32 reg,
    const TUP_CHAR* param
);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_serviceright(TUP_UINT32 accountid, CALL_S_SERVICERIGHT_CFG* servicecfg);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_authorize_account(const TUP_CHAR* number, const TUP_CHAR* name, const TUP_CHAR* password);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_create_confid(TUP_UINT32 *confid, TUP_UINT32 *callid);

//根据已有的callid创建会议id

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_create_confid_ex
 (
    TUP_UINT32 accountid,
    TUP_UINT32 incallid ,
    TUP_UINT32* confid,
    TUP_UINT32* outcallid
);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_set_type(TUP_UINT32 confid, CALL_E_SERVERCONF_TYPE type);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_create_by_confid(TUP_UINT32 confid, const TUP_CHAR* groupuri);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_create(TUP_UINT32 *confid, TUP_UINT32 *callid, const TUP_CHAR *groupuri);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_add_attendee(TUP_UINT32 confid, TUP_UINT32 attendeecount, const TUP_CHAR* attendeenumber, TUP_UINT32 persize);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_kick_attendee(TUP_UINT32 confid, const TUP_CHAR* attendnum);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_modify_attendee(TUP_UINT32 confid, const TUP_CHAR* attendnum, TUP_UINT32 right);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_modify_right(TUP_UINT32 confid,const TUP_CHAR*number,TUP_UINT32 right);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_mute(TUP_UINT32 confid, TUP_BOOL muted);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_lock(TUP_UINT32 confid, TUP_BOOL locked);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_leave(TUP_UINT32 confid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_end(TUP_UINT32 confid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_accept_with_lineid(TUP_UINT32 confid, TUP_UINT32 lineid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_accept(TUP_UINT32 confid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_hold(TUP_UINT32 confid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_unhold(TUP_UINT32 confid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_transferto_conf(TUP_UINT32 confid, TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_transferto_conf_non_refer(TUP_UINT32 callid, TUP_UINT32 *confid, const TUP_CHAR *groupuri);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_transferto_dataconf(TUP_UINT32 confid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_p2p_transferto_dataconf(TUP_UINT32* confid, TUP_UINT32* callid, TUP_UINT32 p2p_callid, const TUP_CHAR* groupuri);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_access_reservedconf(TUP_UINT32 *callid, const TUP_CHAR *accesscode/*, CALL_E_CALL_TYPE call_type*/);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_access_reserved_conf_directly(TUP_UINT32 callid, const TUP_CHAR *accesscode);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_add_extra_num(TUP_UINT32 confid, const TUP_CHAR *number);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_reject_p2pdataconf(TUP_UINT32 confid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_get_conferstate(CALL_S_CONFER_LOCAL_INFO* confinfo);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_create_conf(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_join_confer(TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_drop_confer(TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_mute_self(TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_unmute_self(TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_mute_confer(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_unmute_confer(TUP_UINT32 callid);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_hold(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_unhold(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_end_conf(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_group_pickup(TUP_UINT32 callid, CALL_E_CALL_TYPE call_type);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_add_point_pickup(TUP_UINT32 callid, CALL_E_CALL_TYPE call_type, const TUP_CHAR* calleenumber);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_forward_config(const CALL_S_FORWARD_INFO* fwdconfig , TUP_UINT32 configcount);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_intercom_call(TUP_UINT32 callid, const TUP_CHAR* calleenumber);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_pickup_intercom_call(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_VVM_listen(TUP_UINT32 callid,  const TUP_CHAR* callee_number);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_VVM_query(const CALL_S_VVM_QUERY_MSG* query);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_VVM_forward(const CALL_S_VVM_FWD_MSG* fwd);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_VVM_delete(const CALL_S_VVM_DEL_MSG* del);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_VVM_pausal(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_VVM_fast_forward(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_VVM_rewind(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_set_linked(TUP_UINT32 callid, TUP_BOOL islink);

/* BEGIN add: [[CR20130326013 登录过程中增加可取消功能] [2013/3/26] [suijun 193874]] */

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_cancel_login(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_send_DTMF(TUP_UINT32 confid, CALL_E_DTMF_TONE keyevt);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_add_p2p_to_dataconf(TUP_UINT32 confid, const TUP_CHAR* p2pNumber);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_create_linkage_conf
(
    TUP_UINT32 confid,
    TUP_UINT32 attendcount,
    const  TUP_CHAR* attendnumber,
    TUP_UINT32 pernumsize
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_DICF_switct(TUP_UINT32 accountid, TUP_BOOL switches);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_abbr_dial_call(TUP_UINT32 callid, CALL_E_CALL_TYPE calltype, const TUP_CHAR* calleenumber);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_all_account_DND_on(TUP_VOID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_all_account_DND_off(TUP_VOID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_all_account_absent_on(TUP_VOID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_all_account_absent_off(TUP_VOID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_MCID(TUP_UINT32 accountid);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_IPTservice_batch(const CALL_S_IPT_DATA* IPTdata);

/*one count interface*/

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_IPTservice_for_accout
(
    TUP_UINT32 accountid, 
    CALL_S_IPT_DATA* IPTdata
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_callbarring_for_account(TUP_UINT32 accountid, const CALL_S_IPT_DATA* IPTdata);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_cancel_callbarring_for_account(TUP_UINT32 accountid, const CALL_S_IPT_DATA* IPTdata);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_merger(TUP_UINT32 confid, const TUP_CHAR* securityconfnum);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_split(TUP_UINT32 confid, const TUP_CHAR* securityconfnum);




/**
 * <b>Description:</b> This function is used to create video window 
 * <br><b>Purpose:</b> The UI used this function to create video window
 * 
 * @count [in] number Specifies the number of window that the UI want to create
 * @window [in] pointer Specifies structs of the windows
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_create_video_window
 */
TUP_API TUP_RESULT tup_call_create_video_window(TUP_UINT32 count,const CALL_S_VIDEOWND_INFO * window);


/**
 * <b>Description:</b> This function is used to update video window 
 * <br><b>Purpose:</b> The UI used this function to update video window
 * 
 * @count [in] count Specifies the number of window that the UI want to update
 * @window [in] pointer Specifies structs of the windows
 * @ulCallID [in] call ID of the windows
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_update_video_window
 */
TUP_API TUP_RESULT tup_call_update_video_window(TUP_UINT32 count, const CALL_S_VIDEOWND_INFO * window, TUP_UINT32 ulCallID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_change_video_window(TUP_UINT32 ulCtrlType, const CALL_S_VIDEOWND_INFO* window);


/**
 * <b>Description:</b> This function is used to destroy video window 
 * <br><b>Purpose:</b> The UI used this function to destroy video window
 * 
 * @wndtype [in] type Specifies the window that the UI want to destroy
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_destroy_video_window
 */
TUP_API TUP_RESULT tup_call_destroy_video_window(CALL_E_VIDEOWND_TYPE wndtype);


/**
 * <b>Description:</b> This function is used to change position of video window 
 * <br><b>Purpose:</b> The UI used this function to change position of video window 
 * 
 * @wndtype [in] type Specifies the window that the UI want to change
 * @coordinate [in] coordinate Specifies the window that would be moved to
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_change_video_window_pos
 */
TUP_API TUP_RESULT tup_call_change_video_window_pos(CALL_E_VIDEOWND_TYPE wndtype, const TUP_INT32 coordinate[CALL_E_COORDINATE_BUTT]);


/**
 * <b>Description:</b> This function is used to change the type of video window 
 * <br><b>Purpose:</b> The UI used this function to change the type of video window 
 * 
 * @wndtype [in] type Specifies the window that the UI want to change
 * @displaytype [in] display type of video window that UI wanted to change to
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_change_video_window_type
 */
TUP_API TUP_RESULT tup_call_change_video_window_type(CALL_E_VIDEOWND_TYPE wndtype, TUP_UINT32 displaytype);


/**
 * <b>Description:</b> This function is used to notify the other end whether adding video or not 
 * <br><b>Purpose:</b>When the request of adding video for the voice call was received, the UI used this function to notify the other end whether the request was approved
 * 
 * @callid [in] call ID
 * @is_accept [in] whether adding video or not for the call. TUP_TRUE, adding video; Otherwise, not.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_reply_add_video
 */
TUP_API TUP_RESULT tup_call_reply_add_video(TUP_UINT32 callid,TUP_BOOL is_accept);


/**
 * <b>Description:</b> This function is used to delete video or not 
 * <br><b>Purpose:</b> The UI used this function to delete video or not for the call
 * 
 * @callid [in] call ID
 * @is_accept [in] whether deleting video or not for the call. TUP_TRUE, deleting video; Otherwise, not.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_reply_del_video
 */
TUP_API TUP_RESULT tup_call_reply_del_video(TUP_UINT32 callid,TUP_BOOL is_accept);//已废弃


/**
 * <b>Description:</b> This function is used to request to add video for a voice call 
 * <br><b>Purpose:</b> The UI used this function to request to add video for a voice call 
 * 
 * @callid [in] call ID
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_add_video
 */
TUP_API TUP_RESULT tup_call_add_video(TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to request to delete video for a voice call 
 * <br><b>Purpose:</b> The UI used this function to request to delete video for a voice call 
 * 
 * @callid [in] call ID
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_del_video
 */
TUP_API TUP_RESULT tup_call_del_video(TUP_UINT32 callid);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_open_local_preview_in_dialog(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_close_local_preview_in_dialog(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_open_remote_preview_in_dialog(TUP_UINT32 callid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_close_remote_preview_in_dialog(TUP_UINT32 callid);


/**
 * <b>Description:</b> This function is used to test local mic and speaker
 * <br><b>Purpose:</b> The UI used this function to test local mic and speaker. The user speaks before mic first, and then checks whether the voice was sent out from speaker.
 * 
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_open_audio_preview
 */
TUP_API TUP_RESULT tup_call_open_audio_preview(TUP_VOID);


/**
 * <b>Description:</b> This function is used to close the testing local mic and speaker
 * <br><b>Purpose:</b> The UI used this function to close the testing local mic and speaker
 * 
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_close_audio_preview
 */
TUP_API TUP_RESULT tup_call_close_audio_preview(TUP_VOID);


/**
 * <b>Description:</b> This function is used to open local camera and create preview window
 * <br><b>Purpose:</b> The UI used this function to test local camera
 * 
 * @ulHandle [in] handle of the window
 * @ulIndex [in] index of camera
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_open_preview
 */
TUP_API TUP_RESULT tup_call_open_preview(TUP_UINT32 ulHandle, TUP_UINT32 ulIndex);


/**
 * <b>Description:</b> This function is used to close local camera and destroy preview window
 * <br><b>Purpose:</b> The UI used this function to end local camera test
 * 
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_close_preview
 */
TUP_API TUP_RESULT tup_call_close_preview(TUP_VOID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_absent_for_account(TUP_UINT32 accountid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_cancel_absent_for_account(TUP_UINT32 accountid);

/**
 * <b>Description:</b> This function is used to publish account's status
 * <br><b>Purpose:</b> The UI used this function to publish account's status
 * 
 * @ulSipAccountID [in] the sip account id that need publish status
 * @ulStatusType [in] the status to be published
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_get_contact_status
 */
TUP_API TUP_RESULT tup_call_publish_setting_status(IN TUP_UINT32 ulSipAccountID, IN TUP_UINT32 ulStatusType);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_mobile_extend_call(TUP_UINT32 ulCallID, const TUP_CHAR* pszMPNum);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_answer_intercom_call(TUP_UINT32 ulCallID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_direct_callpark(TUP_UINT32 ulCallID, const TUP_CHAR* pszDirectNum);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_callpark(TUP_UINT32 ulCallID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_private_hold_call (TUP_UINT32 ulCallID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_abbrdial_Call(TUP_UINT32 ulCallID, CALL_E_CALL_TYPE enCallType, const TUP_CHAR* pszCalleeNumber);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_point_pickup(TUP_UINT32 ulCallID, CALL_E_CALL_TYPE call_type, const TUP_CHAR* pcCalleeNumber);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_create(TUP_UINT32 ulCallID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_join(TUP_UINT32 ulCallID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_drop_conferee(TUP_UINT32 ulCallID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_mute_conferee(TUP_UINT32 ulCallID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_unmute_conferee(TUP_UINT32 ulCallID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_localconf_end(TUP_VOID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_SCA_insert (TUP_UINT32 ulCallID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_SCA_retrieve (TUP_UINT32 ulCallID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_SCA_sub_state(TUP_UINT32 ulSipAccountID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_SCA_offhook (TUP_UINT32 ulSipAccountID, TUP_UINT32 ulSCALineID);


/**
 * <b>Description:</b> This function is used to stop playing signal tone
 * <br><b>Purpose:</b> The UI used this function to stop playing signal tone
 * 
 * @sender_handle [in] handle specified UI, generated by UI.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_stop_signal_tone
 */
TUP_API TUP_RESULT tup_call_media_stop_signal_tone(TUP_UINT32 sender_handle);


/**
 * <b>Description:</b> This function is used to stop playing signal tone
 * <br><b>Purpose:</b> The UI used this function to stop playing signal tone
 * 
 * @toneid [in] ring tone ID. See AUDIO_E_COMPOUNT_VOICE.
 * @is_cycle [in] TUP_TRUE, loop; Otherwise, play once.
 * @sender_handle [in] handle specified UI, generated by UI.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_play_signal_tone
 */
TUP_API TUP_RESULT tup_call_media_play_signal_tone
(
    TUP_UINT32 toneid, 
    TUP_BOOL is_cycle, 
    TUP_UINT32 sender_handle
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_media_play_signal_tone_to_conf
(
    TUP_UINT32 toneid,
    TUP_BOOL iscycle, 
    TUP_UINT32 senderhandle
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_media_stop_signal_tone_to_conf(TUP_UINT32 senderhandle);


/**
 * <b>Description:</b> This function is used to set speaker volume
 * <br><b>Purpose:</b> The UI used this function to set speaker volume
 * 
 * @dev [in] CALL_E_AO_DEV_SPEAKER specified speaker
 * @volume [in] speaker volume, 0-100.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_set_speak_volume
 */
TUP_API TUP_RESULT tup_call_media_set_speak_volume(CALL_E_AO_DEV dev, TUP_UINT32 volume);


/**
 * <b>Description:</b> This function is used to set mic volume
 * <br><b>Purpose:</b> The UI used this function to set mic volume
 * 
 * @enAudDirection [in] audio route. reference the define of CALL_E_AUDDEV_ROUTE.
 * @ulVolume [in] mic volume, 0-100.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_set_mic_volume
 */
TUP_API TUP_RESULT tup_call_media_set_mic_volume
(
    CALL_E_AUDDEV_ROUTE enAudDirection,
    TUP_UINT32 ulVolume
);

/* 获取输出音量 */

/**
 * <b>Description:</b> This function is used to get speaker volume
 * <br><b>Purpose:</b> The UI used this function to get speaker volume
 * 
 * @volume [in, out] speaker volume. 
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_get_speak_volume
 */
TUP_API TUP_RESULT tup_call_media_get_speak_volume(TUP_UINT32* volume);

/* 获取输出能量 */

/**
 * <b>Description:</b> This function is used to get speaker power level
 * <br><b>Purpose:</b> The UI used this function to get speaker power level
 * 
 * @level [in, out] speaker power level. 
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_get_speak_level
 */
TUP_API TUP_RESULT tup_call_media_get_speak_level(TUP_UINT32* level);

/* 获取输入音量 */

/**
 * <b>Description:</b> This function is used to get mic volume
 * <br><b>Purpose:</b> The UI used this function to get mic volume
 * 
 * @volume [in, out] mic volume. 
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_get_mic_volume
 */
TUP_API TUP_RESULT tup_call_media_get_mic_volume(TUP_UINT32* volume);

/* 获取输入能量 */

/**
 * <b>Description:</b> This function is used to get mic power level
 * <br><b>Purpose:</b> The UI used this function to get mic power level
 * 
 * @level [in, out] mic power level. 
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_get_mic_level
 */
TUP_API TUP_RESULT tup_call_media_get_mic_level(TUP_UINT32* level);

/* 获取系统静音状态 */

/**
 * <b>Description:</b> This function is used to get speaker mute state
 * <br><b>Purpose:</b> The UI used this function to get speaker mute state
 * 
 * @pMute [in, out] Recieve speaker mute state
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_get_sys_spk_mute
 */
TUP_API TUP_RESULT tup_call_media_get_sys_spk_mute(TUP_BOOL* pMute);

/* 获取系统麦克风静音状态 */

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_media_get_sys_mic_mute(TUP_BOOL* pMute);



/**
 * <b>Description:</b> This function is used to get the index of effective mic
 * <br><b>Purpose:</b> The UI used this function to set get the index of effective mic
 * 
 * @index [in, out] The index of effective mic
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_get_mic_index
 */
TUP_API TUP_RESULT tup_call_media_get_mic_index(TUP_UINT32* index);


/**
 * <b>Description:</b> This function is used to get the index of effective speaker
 * <br><b>Purpose:</b> The UI used this function to set get the index of effective speaker
 * 
 * @index [in, out] The index of effective speaker
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_get_speak_index
 */
TUP_API TUP_RESULT tup_call_media_get_speak_index(TUP_UINT32* index);


/**
 * <b>Description:</b> This function is used to get the index of effective camera
 * <br><b>Purpose:</b> The UI used this function to set get the index of effective camera
 * 
 * @index [in, out] The index of effective camera
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_get_video_index
 */
TUP_API TUP_RESULT tup_call_media_get_video_index(TUP_UINT32* index);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_media_play_ring_tone
(
    const TUP_INT8* ringfile,
    TUP_UINT32 senderhandler
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_media_stop_ring_tone(TUP_UINT32 senderhandler);


/**
 * <b>Description:</b> This function is used to set the out device of audio
 * <br><b>Purpose:</b> The UI used this function to set the out device of audio
 * 
 * @route_dev [in] The audio out device that wanted to be. reference the define of CALL_E_AUDDEV_ROUTE.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_set_audio_outdev
 */
TUP_API TUP_RESULT tup_call_media_set_audio_outdev(CALL_E_AUDDEV_ROUTE route_dev);


/**
 * <b>Description:</b> This function is used to set the in device of audio
 * <br><b>Purpose:</b> The UI used this function to set the in device of audio
 * 
 * @route_dev [in] The audio in device that wanted to be. reference the define of CALL_E_AUDDEV_ROUTE.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_set_audio_indev
 */
TUP_API TUP_RESULT tup_call_media_set_audio_indev(CALL_E_AUDDEV_ROUTE route_dev);


/**
 * <b>Description:</b> This function is used to mute speaker
 * <br><b>Purpose:</b> The UI used this function to  mute speaker
 * 
 * @callid [in] call ID
 * @is_on [in] TUP_TRUE, mute; ohterwise, not mute.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_mute_speak
 */
TUP_API TUP_RESULT tup_call_media_mute_speak(TUP_UINT32 callid, TUP_BOOL is_on);


/**
 * <b>Description:</b> This function is used to mute mic
 * <br><b>Purpose:</b> The UI used this function to  mute mic
 * 
 * @callid [in] call ID
 * @is_on [in] TUP_TRUE, mute; ohterwise, not mute.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_mute_mic
 */
TUP_API TUP_RESULT tup_call_media_mute_mic(TUP_UINT32 callid, TUP_BOOL is_on);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_hardware_params(const CALL_S_HARDWARE_PARAMS* hardwareparams);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_hardware_params(CALL_S_HARDWARE_PARAMS* hardwareparams);


/**
 * <b>Description:</b> This function is used to mute video
 * <br><b>Purpose:</b> The UI used this function to  mute video
 * 
 * @callid [in] call ID
 * @is_on [in] TUP_TRUE, mute; ohterwise, not mute.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_media_mute_video
 */
TUP_API TUP_RESULT tup_call_media_mute_video(TUP_UINT32 callid,TUP_BOOL is_on);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_get_securitynum
(
    TUP_UINT32 confid,
    TUP_CHAR* securitynum,
    TUP_UINT32 numsize
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_onekey_transferto_VM
(
    TUP_UINT32 callid,
    const TUP_CHAR* divertnumber,
    TUP_BOOL iscallpicked
);
//////////////////////////////////////////////////////////////////////////
// zhubin：call内置视频会议相关接口

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_create_wnd
(
    TUP_UINT32 confid,
    const CALL_S_VIDEOWND_INFO* videowndinfo, 
    TUP_UINT32 wndnum
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_destroy_wnd(TUP_UINT32 confid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_open_self_video(TUP_UINT32 confid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_close_self_video(TUP_UINT32 confid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_notify_attend_open_video
(
    TUP_UINT32 confid,
    const TUP_CHAR* attendnum
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_notify_attend_close_video
(
    TUP_UINT32 confid,
    const TUP_CHAR* attendnum
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_attach_attend_video_to_wnd
(
 TUP_UINT32 confid,
 const TUP_CHAR* attendnum,
 TUP_UINT32 wndid,
 TUP_UINT32 ishighstream
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_detach_attend_video_from_wnd
(
 TUP_UINT32 confid,
 const TUP_CHAR* attendnum,
 TUP_UINT32 wndid
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_change_wnd_size
(
    TUP_UINT32 confid,
    TUP_UINT32 wndid,
    const CALL_S_VIDEOWND_INFO* wndinfo
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_switch_attend_video_resolution
(
    TUP_UINT32 confid,
    const TUP_CHAR* attendnum,
    TUP_UINT32 ishighresolution
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_close_self_all_video(TUP_UINT32 confid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_pause_attend_local_video
(
    TUP_UINT32 confid,
    const TUP_CHAR* attendnum
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_resume_attend_local_video
(
    TUP_UINT32 confid,
    const TUP_CHAR* attendnum
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_change_wnd_zorder
(
    TUP_UINT32 confid,
    TUP_UINT32 Zorder,
    TUP_UINT32 wndid
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_voiceconf_tranfto_videoconf
(
    TUP_UINT32 confid
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_change_wnd_pos
(
    TUP_UINT32 confid,
    const CALL_S_VIDEOWND_INFO* videoinfo,
    TUP_UINT32 infocount
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_all_conf_list(TUP_VOID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_conf_list_for_account
(
    TUP_UINT32 accountid, 
    TUP_UINT32 pagesize, 
    TUP_UINT32 curpage
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_open_preview
(
    TUP_UINT32 confid,
    TUP_UINT32 wndid, 
    const CALL_S_VIDEOCONF_VIDEO_PARAM* videoparam
);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_close_preview(TUP_UINT32 confid);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_videoconf_get_video_device_status
(
    TUP_UINT32 confid,
    const TUP_CHAR* attendnum
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_eqpt_test_start_record
(
    CALL_E_AUDDEV_ROUTE audioinputdev,
    TUP_UINT32 volume,
    TUP_UINT32 samplefreq,
    TUP_UINT32 bitwide,
    TUP_UINT32 recordtime,
    TUP_UINT32 audiotype
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_eqpt_test_stop_record
(
    CALL_E_AUDDEV_ROUTE audioinputdev
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_eqpt_test_start_play
(
    CALL_E_AUDDEV_ROUTE audiooutputdev,
    TUP_UINT32 volume,
    TUP_UINT32 samplefreq,
    TUP_UINT32 bitwide,
    TUP_UINT32 AMPtype
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_eqpt_test_stop_play
(
    CALL_E_AUDDEV_ROUTE audiooutputdev
);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_switch_DND_type
(
    TUP_UINT32 DNDtype,
    TUP_UINT32 localDNDtype
);


/**
 * <b>Description:</b> This function is used to set audio device parameter
 * <br><b>Purpose:</b> The UI used this function to set audio device parameter
 * 
 * @anc [in] active noise cancellation. [0,4] 0, noise cancellation off; [1,4], on. Value is 4, the maximum effect. Default is 0.
 * @aec [in] acoustic echo cancellation. 1, echo cancellation on; 0, off.
 * @agc [in] automatic gain control. 1, automatic gain control on; 0, off.
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_set_audio_dev_options
 */
TUP_API TUP_RESULT tup_call_set_audio_dev_options
(
    TUP_UINT32 anc,
    TUP_UINT32 aec,
    TUP_UINT32 agc
);


/**
 * <b>Description:</b> This function is used to set audio AEC parameter
 * <br><b>Purpose:</b> The UI used this function to set audio AEC parameter
 * 
 * @pstAecParams [in] pointer specifies audio AEC parameter
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_set_AEC_params
 */
TUP_API TUP_RESULT tup_call_set_AEC_params(const CALL_S_AUDIO_AEC_PARAMS* pstAecParams);


/**
 * <b>Description:</b> This function is used to set audio EQ parameter
 * <br><b>Purpose:</b> The UI used this function to set audio EQ parameter
 * 
 * @pstEqConfig [in] pointer specifies audio EQ parameter
 * @enAudDirection [in] upstream/downstream. 
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_set_EQ_param
 */
TUP_API TUP_RESULT tup_call_set_EQ_param(const CALL_S_AUDIO_EQ_CONFIG* pstEqConfig, CALL_E_AO_DEV enAudDirection);


/**
 * <b>Description:</b> This function is used to get audio EQ parameter
 * <br><b>Purpose:</b> The UI used this function to get audio EQ parameter
 * 
 * @pstEqConfig [in, out] pointer specifies audio EQ parameter
 * @enAudDirection [in] upstream/downstream. 
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_get_EQ_param
 */
TUP_API TUP_RESULT tup_call_get_EQ_param(CALL_S_AUDIO_EQ_CONFIG* pstEqConfig, CALL_E_AO_DEV enAudDirection);


/**
 * <b>Description:</b> This function is used to preset audio EQ type
 * <br><b>Purpose:</b> The UI used this function to preset audio EQ type
 * 
 * @enPresetEqType [in] audio EQ type
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_set_preset_EQ_param
 */
TUP_API TUP_RESULT tup_call_set_preset_EQ_param(CALL_E_PRESET_EQ_TYPE enPresetEqType);






/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_register
(
    const TUP_CHAR* number, 
    const TUP_CHAR* name, 
    const TUP_CHAR* password
);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_deregister(const TUP_CHAR* number);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_start_call
(
    TUP_UINT32 *callid,
    CALL_E_CALL_TYPE call_type,
    const TUP_CHAR* callee_number
);

//其他呼叫方式(比如CTD呼叫)

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_start_call_ex(CALL_S_CALL_PARAMS* pstCallParams);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_start_call_bycallid_ex(const CALL_S_CALL_PARAMS* pstCallParams);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_IPTservice
(
    CALL_E_SERVICE_CALL_TYPE type,
    TUP_VOID* data
);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_accept_call(TUP_UINT32 callid,TUP_BOOL is_video);



/*CALL_S_STREAM_INFO  TODO*/

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_get_callstatics(CALL_S_STREAM_INFO* statics);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_ctd_get_list(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_joint_setting
(
    TUP_UINT32 accountid, 
    TUP_BOOL right,
    const TUP_CHAR* linkage_number
);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_joint_start(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_joint_stop(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_joint_switch(TUP_VOID);


/**
 * <b>Description:</b> This function is used to set config
 * <br><b>Purpose:</b> The UI used this function to set config
 * 
 * @cfgid [in] Specify which parameter would to be set
 * @val [in] parameter would be set into
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_set_cfg
 */
TUP_API TUP_RESULT tup_call_set_cfg(TUP_UINT32 cfgid, TUP_VOID * val);

/*支持版本号*/

/**
 * <b>Description:</b> This function is used to get config
 * <br><b>Purpose:</b> The UI used this function to get config
 * 
 * @cfgid [in] Specify which parameter would to be get
 * @val [in, out] parameter would be get
 * @size [in] size of val in byte
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_get_cfg
 */
TUP_API TUP_RESULT tup_call_get_cfg(TUP_UINT32 cfgid,TUP_VOID *val,  TUP_UINT32 size);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_commit_cfg(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_joint_uptoconference(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_joint_conf_result(TUP_UINT32 result);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_serverconf_set_confsubject(TUP_UINT32 confid, const TUP_CHAR* subject);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_VOID* tup_call_get_notifiy_msg_by_msgbody(TUP_UINT8* msgbody);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_VOID tup_call_set_client_name(const TUP_CHAR* client_name);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_notify_client_name(const TUP_CHAR* client_name, TUP_BOOL bIsUI, TUP_BOOL bIsReg);


/*This function  will create one msg thread.
bNeedNotify:  For IP Phone, UI shoud set TRUE, WEB should set FALSE 

*/

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_register_process_notifiy(CALL_FN_CALLBACK_PTR callback_process_notify);

//注册回调函数(非主回调函数)

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_register_process_notifiy_ex(CALL_FN_CALLBACK_PTR callback_process_notify);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_deregister_process_notifiy_ex(TUP_VOID);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_VOID tup_call_register_logfun(CALL_FN_DEBUG_CALLBACK_PTR callback_log);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_VOID tup_call_log_start(TUP_INT32 logLevel, TUP_INT32 lMaxSizeKB, TUP_INT32 lFileCount, const TUP_CHAR* pcLogPath);


/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_VOID tup_call_log_stop(TUP_VOID);

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API const TUP_CHAR* tup_call_get_err_description(TUP_UINT32 errornum);

/**
 * <b>Description:</b> This function is used to signin huntgroup
 * <br><b>Purpose:</b> The UI used this function to signin a huntgroup
 * 
 * @ulCallID [in] callid created by using function tup_call_create_callid
 * @pcGroupNumber [in] the huntgroup number(Usually refers to the Access Code of huntgroup) need to signin
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_create_callid
 * @see  tup_call_huntgroup_signout
 */
TUP_API TUP_RESULT tup_call_huntgroup_signin(TUP_UINT32 ulCallID, const TUP_CHAR *pcGroupNumber);

/**
 * <b>Description:</b> This function is used to signout huntgroup
 * <br><b>Purpose:</b> The UI used this function to signout a huntgroup
 * 
 * @ulCallID [in] callid created by using function tup_call_create_callid
 * @pcGroupNumber [in] the huntgroup number(Usually refers to the Access Code of huntgroup) need to signout
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_create_callid
 * @see  tup_call_huntgroup_signin
 */
TUP_API TUP_RESULT tup_call_huntgroup_signout(TUP_UINT32 ulCallID, const TUP_CHAR *pcGroupNumber);

/**
 * <b>Description:</b> This function is used to get the status of huntgroup
 * <br><b>Purpose:</b> The UI used this function to get the status of a huntgroup
 * 
 * @ulSipAccountID [in] sip account id that Associated with the huntgroup number specified in parameter pstStatus
 * @pstStatus [in/out] pointer to CALL_S_CONTACT_STATUS
 * typedef struct tagCALL_S_CONTACT_STATUS
 * {
 *    TUP_UINT32 ulSipAccountID;            //sip account id that Associated with the huntgroup number
 *    TUP_CHAR acNo[33];                    //refers to huntgroup number
 *    CALL_E_CONTACT_STATUS enContactStatus;//refers to the status of huntgroup, this is the out parameter of this function
 * } CALL_S_CONTACT_STATUS, *CALL_S_CONTACT_STATUS_PTR;
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_huntgroup_getstatus(TUP_UINT32 ulSipAccountID, CALL_S_CONTACT_STATUS *pstStatus);

/**
 * <b>Description:</b> This function is used to accept paging call
 * <br><b>Purpose:</b> The UI used this function to accept an incomming paging call
 * 
 * @ulGroupID [in] paging group id
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  CALL_E_EVT_PAGING_INCOMING
 * @see  CALL_E_EVT_PAGING_ENDED
 */
TUP_API TUP_RESULT tup_call_paging_accept(TUP_UINT32 ulGroupID);

/**
 * <b>Description:</b> This function is used to end paging call
 * <br><b>Purpose:</b> The UI used this function to end a paging call
 * 
 * @ulGroupID [in] paging group id
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_paging_accept
 * @see  CALL_E_EVT_PAGING_ENDED
 */
TUP_API TUP_RESULT tup_call_paging_end(TUP_UINT32 ulGroupID);



/**
 * <b>Description:</b> This function is used to 
 * <br><b>Purpose:</b> The UI used this function to 
 * 
 * @pstVideoControl [in] Pointer specify 
 * #define OPERATION_OPEN          0x01    //open
 * #define OPERATION_CLOSE         0x02    //close
 * #define OPERATION_START         0x04    //start
 * #define OPERATION_STOP          0x08    //stop
 * #define MODULE_REMOTE_RENDER    0x01    //window which shows the remote
 * #define MODULE_LOCAL_RENDER     0x02    //window which shows the local
 * #define MODULE_CAPTURE          0x04    //camera
 * #define MODULE_ENCODER          0x08    //encoder
 * #define MODULE_DECODER          0x10    //decoder
 * 
 *  typedef struct tagCALL_S_VIDEOCONTROL
 *  {
 *      TUP_UINT32 ulCallID;    //call ID 
 *      TUP_UINT32 ulOperation; //It can be the value of OPERATION_OPEN/OPERATION_CLOSE/OPERATION_START/OPERATION_STOP. We can use logical '|' between OPERATION_OPEN and OPERATION_START; also between OPERATION_CLOSE and OPERATION_STOP.
 *      TUP_UINT32 ulModule;    //It can be the value of MODULE_REMOTE_RENDER/MODULE_LOCAL_RENDER/MODULE_CAPTURE/MODULE_ENCODER/MODULE_DECODER.
 *  }CALL_S_VIDEOCONTROL;
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_vedio_control
 */
TUP_API TUP_RESULT tup_call_video_control(CALL_S_VIDEOCONTROL *pstVideoControl);


/**
 * <b>Description:</b> This function is used to set audio route on mobile device
 * <br><b>Purpose:</b> The UI used this function to set audio route on mobile device
 * 
 * @route [in] audio route enum value
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_set_mobile_audio_route
 */
TUP_API TUP_RESULT tup_call_set_mobile_audio_route(CALL_E_MOBILE_AUIDO_ROUTE route);


/**
 * <b>Description:</b> This function is used to get audio route on mobile device
 * <br><b>Purpose:</b> The UI used this function to get audio route on mobile device
 * 
 * @pulRoute [in, out] Recieve audio route enum value
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_get_mobile_audio_route
 */
TUP_API TUP_RESULT tup_call_get_mobile_audio_route(CALL_E_MOBILE_AUIDO_ROUTE *pulRoute);


/**
 * <b>Description:</b> This function is used to 
 * <br><b>Purpose:</b> The UI used this function to 
 * 
 * @ulCallID [in] call ID
 * @uiIndex [in] the camera device index 
 * @pstVideoOrient [in] pointer to CALL_S_VIDEO_ORIENT.
 *     typedef struct tagCALL_S_VIDEO_ORIENT
 *     {
 *         TUP_UINT32 ulChoice;         //Orient video by UI. 1:portrait; 2:landscape; 3:seascape. It will be used in sip sdp.
 *         TUP_UINT32 ulPortrait;       //Video rotation angle(Counterclockwise) when portrait. 0:0 degree; 1:90 degree; 2:180 degree; 3:270 degree.
 *         TUP_UINT32 ulLandscape;      //Video rotation angle(Counterclockwise) when landscape. 0:0 degree; 1:90 degree; 2:180 degree; 3:270 degree.
 *         TUP_UINT32 ulSeascape;       //Video rotation angle(Counterclockwise) when seascape. 0:0 degree; 1:90 degree; 2:180 degree; 3:270 degree.
 *     }CALL_S_VIDEO_ORIENT;
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_set_mboile_video_orient
 */
TUP_API TUP_RESULT tup_call_set_mboile_video_orient(TUP_UINT32 ulCallID, TUP_UINT32 uiIndex, const CALL_S_VIDEO_ORIENT *pstVideoOrient);


/**
 * <b>Description:</b> This function is used to 
 * <br><b>Purpose:</b> The UI used this function to 
 * 
 * @ulCallID [in] call ID
 * @pstRender [in] pointer to CALL_S_VIDEO_RENDER_INFO.
 *      typedef struct tagCALL_S_VIDEO_RENDER_INFO
 *      {
 *          CALL_E_VIDEOWND_TYPE enRenderType;  //窗口类型枚举值 0:远端窗口；1:本端窗口
 *          TUP_UINT32 ulDisplaytype;           //窗口显示模式 0:拉伸模式 1:(不拉伸)黑边模式 2:(不拉伸)裁剪模式
 *          TUP_UINT32 ulMirrortype;            //窗口镜像模式 0:不做镜像(默认值) 1:上下镜像(目前未支持) 2:左右镜像
 *       }CALL_S_VIDEO_RENDER_INFO;
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_set_mobile_video_render
 */
TUP_API TUP_RESULT tup_call_set_mobile_video_render(TUP_UINT32 ulCallID, const CALL_S_VIDEO_RENDER_INFO* pstRender);


//H.264视频B帧开关

/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_vpuorder_enable(TUP_BOOL bEnable);



/**
 * <b>Description:</b> This function is used to TODO
 * <br><b>Purpose:</b> The UI used this function to TODO
 * 
 * @TODO [in/out] TODO
 * @return TUP_SUCCESS  Indicates operation succeeds
 *      <br>Others value Indicates operation fails
 * @see  tup_call_TODO
 */
TUP_API TUP_RESULT tup_call_set_user_name(CALL_S_ACCOUNT_USER_NAME* pstUserName, TUP_UINT32 ulDataNum);





#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif  /* __CALL_ADVANCED_INTERFACE_H__ */


/** @}*/
