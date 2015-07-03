#ifndef _TUP_CONF_BASEAPI_H_
#define _TUP_CONF_BASEAPI_H_

#include "tup_conf_basedef.h"

//注意：接口字符串都采用UTF8格式

#ifdef __cplusplus
	extern "C" {
#endif
	/*************************会控基本接口*************************/
	/*****************************************************************************
	函 数 名  : tup_conf_init
	功能描述  : 初始化会议组件，设置线程模型、系统设备类型和操作系统类型。
				调用该函数的线程为消息回调线程，建议在主线程调用
	输入参数  : selfthread: 线程模型（重要）。
							true：会议组件在独立线程运行，该模式下不支持媒体共享模块
							false：调用该函数的线程为会议组件的运行线程，消息回调也在该线程。
				pinitparam: 初始化参数，包括设备类型和操作系统类型
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/	
    TUP_API TUP_VOID  tup_conf_init(TUP_BOOL selfthread, TUP_IN const Init_param * pinitparam);

	/*****************************************************************************
	函 数 名  : tup_conf_uninit
	功能描述  : 退出程序前释放所有会议及所有资源。
	输入参数  : 无
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_uninit(void);

	/*****************************************************************************
	函 数 名  : tup_conf_new
	功能描述  : 新建一个会议对象。
	输入参数  : callback: 多会议回调函数的函数地址
				pconfinfo: 会议相关信息
				option: 会议选项，参考CONF_OPTION枚举值，基本功能传CONF_OPTION_USERLIST即可
	输出参数  : ret_handle: 返回会议句柄的指针
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_new(conference_multi_callback callback, const TC_CONF_INFO* pconfinfo, TUP_UINT32 option, CONF_HANDLE* ret_handle);

    /*****************************************************************************
	函 数 名  : tup_conf_heart
	功能描述  : 提供消息驱动的心跳，让ISV应用层驱动消息循环是为了保证消息循环在主线程中
				说明: Windows平台无需调用该接口，移动平台必须调用该接口。
	输入参数  : handle: 会议句柄
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/	
    TUP_API TUP_VOID  tup_conf_heart(CONF_HANDLE handle);


	/*****************************************************************************
	函 数 名  : tup_conf_join
	功能描述  : 加入一个会议
	输入参数  : handle: 会议句柄
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_ON_CONFERENCE_JOIN  
				CONF_MSG_USER_ON_ENTER_IND 
				CONF_MSG_USER_ON_HOST_CHANGE_IND
				CONF_MSG_USER_ON_PRESENTER_CHANGE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_join(CONF_HANDLE handle); 

	/*****************************************************************************
	函 数 名  : tup_conf_leave
	功能描述  : 离开一个会议
	输入参数  : handle: 会议句柄
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_USER_ON_LEAVE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_leave(CONF_HANDLE handle); 

	/*****************************************************************************
	函 数 名  : tup_conf_lock
	功能描述  : 锁定一个会议，锁定会议后其他人就不能加入会议了
	输入参数  : handle: 会议句柄
				lock:是否锁定，TRUE为锁定，FALSE为解锁
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_ON_LOCK_RSP
				CONF_MSG_ON_LOCK_REPORT_IND
	*****************************************************************************/  
    TUP_API TUP_RESULT  tup_conf_lock(CONF_HANDLE handle,TUP_BOOL lock); 

	/*****************************************************************************
	函 数 名  : tup_conf_terminate
	功能描述  : 结束一个会议
	输入参数  : handle: 会议句柄
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_ON_CONFERENCE_TERMINATE
	*****************************************************************************/  
    TUP_API TUP_RESULT  tup_conf_terminate(CONF_HANDLE handle);

	/*****************************************************************************
	函 数 名  : tup_conf_mute
	功能描述  : 会场静音/取消静音，包括电话和PC用户
	输入参数  : handle: 会议句柄
				bmute: 会场静音标识。取值：TRUE：静音；FALSE：取消静音
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_ON_MUTE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_mute(CONF_HANDLE handle, TUP_BOOL bmute); 

	/*****************************************************************************
	函 数 名  : tup_conf_release
	功能描述  : 销毁一个会议对象，该函数必须和tup_conf_new在同一个线程
	输入参数  : handle: 会议句柄
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/  
    TUP_API TUP_RESULT  tup_conf_release(CONF_HANDLE handle);
	
	/*****************************************************************************
	函 数 名  : tup_conf_load_component
	功能描述  : 加载指定组件
	输入参数  : handle: 会议句柄 ,
				compts : 组件ID ，对应COMPONENT_IID枚举值，可或运算
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_ON_COMPONENT_LOAD
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_load_component(CONF_HANDLE handle, TUP_UINT32 compts);


	/*****************************************************************************
	函 数 名  : tup_conf_reg_component_callback
	功能描述  : 注册指定组件的回调函数
	输入参数  : handle: 会议句柄 ,
				compts : 组件ID ，对应COMPONENT_IID枚举值
				callback：回调函数
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_reg_component_callback(CONF_HANDLE handle, TUP_UINT32 compt,component_multi_callback callback);


	/*****************************************************************************
	函 数 名  : tup_conf_user_get_host
	功能描述  : 获取主持人ID
	输入参数  : handle: 会议句柄
	输出参数  : ret_userid：主持人ID，0表示没有主持人
	返 回 值  : 返回TC_OK表示主持人存在，否则不存在
	回调消息  : 无
	*****************************************************************************/  
    TUP_API TUP_RESULT  tup_conf_user_get_host(CONF_HANDLE handle,TUP_UINT32* ret_userid);
 
	/*****************************************************************************
	函 数 名  : tup_conf_user_get_presenter
	功能描述  : 获取主讲人ID
	输入参数  : handle: 会议句柄
	输出参数  : ret_userid：主持人ID，0表示没有主讲人
	返 回 值  : 返回TC_OK表示主讲人存在，否则不存在
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_user_get_presenter(CONF_HANDLE handle,TUP_UINT32* ret_userid);
 
	/*****************************************************************************
	函 数 名  : tup_conf_user_kickout
	功能描述  : 踢除一个用户
	输入参数  : handle: 会议句柄
				userid: 用户ID
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_ON_CONFERENCE_LEAVE
				CONF_MSG_USER_ON_LEAVE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_user_kickout(CONF_HANDLE handle,TUP_UINT32 userid);

	/*****************************************************************************
	函 数 名  : tup_conf_user_set_role
	功能描述  : 设置用户角色
	输入参数  : handle: 会议句柄
				userid: 用户ID
				role: 用户角色，取值：	CONF_ROLE_HOST//主持人
										CONF_ROLE_PRESENTER//主讲人
										CONF_ROLE_GENERAL//普通与会者
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_USER_ON_HOST_GIVE_IND
				CONF_MSG_USER_ON_HOST_GIVE_CFM
				CONF_MSG_USER_ON_HOST_CHANGE_IND
				CONF_MSG_USER_ON_PRESENTER_GIVE_IND
				CONF_MSG_USER_ON_PRESENTER_GIVE_CFM
				CONF_MSG_USER_ON_PRESENTER_CHANGE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_user_set_role(CONF_HANDLE handle,TUP_UINT32 userid,TUP_UINT32 role);

	/*****************************************************************************
	函 数 名  : tup_conf_user_request_role
	功能描述  : 申请用户角色，申请成功自己会收到确认消息，其他人收到角色变更消息。
	输入参数  : handle: 会议句柄
				role:  用户角色，取值：	CONF_ROLE_HOST//主持人
										CONF_ROLE_PRESENTER//主讲人
										CONF_ROLE_GENERAL//普通与会者
				pszkey: 角色申请密码，主持人一般都需要密码，主讲人不需要，有效值：32位’\0’结尾字符串
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_USER_ON_HOST_CHANGE_CFM
				CONF_MSG_USER_ON_PRESENTER_CHANGE_CFM
				CONF_MSG_USER_ON_HOST_CHANGE_IND
				CONF_MSG_USER_ON_PRESENTER_CHANGE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_user_request_role(CONF_HANDLE handle,TUP_UINT32 role,const char* pszkey);

	/*************************屏幕共享基本接口*************************/
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_set_owner
	功能描述  : 设置屏幕共享的拥有者
	输入参数  : handle: 会议句柄
				userid: 用户ID
				action: 取值（非法值返回失败）：
						 AS_ACTION_DELETE//释放
						 AS_ACTION_ADD//拥有
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_SHARING_SESSION
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_set_owner(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT32 action);				

	/*****************************************************************************
	函 数 名  : tup_conf_as_set_sharetype
	功能描述  : 设置当前的共享类型
	输入参数  : handle: 会议句柄
				sharingtype: 取值（非法值返回失败）：
						 AS_SHARINGTYPE_DESKTOP//桌面共享
						 AS_SHARINGTYPE_APP//应用程序共享
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_set_sharetype(CONF_HANDLE handle, TUP_INT32 sharingtype);

	/*****************************************************************************
	函 数 名  : tup_conf_as_start
	功能描述  : 开始桌面共享或应用程序共享
	输入参数  : handle: 会议句柄
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_start(CONF_HANDLE handle);

	/*****************************************************************************
	函 数 名  : tup_conf_as_stop
	功能描述  : 停止桌面共享或应用程序共享
	输入参数  : handle: 会议句柄
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_stop(CONF_HANDLE handle);	

	/*****************************************************************************
	函 数 名  : tup_conf_as_get_screendata
	功能描述  : 获取屏幕数据
	输入参数  : handle: 会议句柄
	输出参数  : pscreendata: 屏幕数据
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_get_screendata(CONF_HANDLE handle,TC_AS_SCREENDATA* pscreendata);	

	/*****************************************************************************
	函 数 名  : tup_conf_as_request_privilege
	功能描述  : 申请远程控制或标准权限，对方会收到请求通知
	输入参数  : handle: 会议句柄
				privilege: 权限类型。取值（非法值返回失败）：
											AS_PRIVILEGETYPE_CONTROL //远程控制
											AS_PRIVILEGETYPE_ANNOTATION //标注
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_PRIVILEGE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_request_privilege(CONF_HANDLE handle,TUP_INT8 privilege);	

	/*****************************************************************************
	函 数 名  : tup_conf_as_set_privilege
	功能描述  : 赋予/收回远程控制权限，自动生效，不通知上层
	输入参数  : handle: 会议句柄
				userid: 用户ID
				privilege: 权限类型。取值（非法值返回失败）：
											AS_PRIVILEGETYPE_CONTROL //远程控制
											AS_PRIVILEGETYPE_ANNOTATION //标注
				action: 操作类型。取值（非法值返回失败）：
												AS_ACTION_DELETE //收回
												AS_ACTION_ADD //赋予
												AS_ACTION_MODIFY //修改
												AS_ACTION_REJECT //拒绝
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_PRIVILEGE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_set_privilege(CONF_HANDLE handle,TUP_UINT32 userid,TUP_INT8 privilege,TUP_UINT32 action);

	/*****************************************************************************
	函 数 名  : tup_conf_as_inputwndmsg
	功能描述  : 输入鼠标和键盘消息，用于远程控制用途
	输入参数  : handle: 会议句柄
				msgtype: 消息类型，windows下对应message
				wparam: 消息参数，window下对应消息的WPARAM参数
				lparam: 消息参数，window下对应消息的LPARAM参数
				pdata: 预留扩展数据，
				datalen: 预留扩展数据长度				 
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_inputwndmsg(CONF_HANDLE handle,TUP_UINT32 msgtype, TUP_ULONG wparam, TUP_LONG lparam, TUP_VOID* pdata, TUP_UINT32 datalen);

	/*****************************************************************************
	函 数 名  : tup_conf_as_begin_annotation
	功能描述  : 开始桌面共享或应用程序共享的标注功能
	输入参数  : handle: 会议句柄
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_begin_annotation(CONF_HANDLE handle);

	/*****************************************************************************
	函 数 名  : tup_conf_as_end_annotation
	功能描述  : 停止桌面共享或应用程序共享的标注功能
	输入参数  : handle: 会议句柄
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_end_annotation(CONF_HANDLE handle);
	

	/*************************视频基本接口*************************/

	
	/*****************************************************************************
	函 数 名  : tup_conf_video_get_deviceinfo
	功能描述  : 获取设备信息列表
	输入参数  : handle: 会议句柄。为0时，用于视频向导		
	pdevice_info: 指向视频设备列表数组的指针
	ret_count: 当pdevice_info为空时，返回数量
	输出参数  : pDeviceInfo: 指向视频设备列表数组的指针
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_get_deviceinfo(CONF_HANDLE handle,TC_DEVICE_INFO* pdevice_info,TUP_UINT32* ret_count);

	/*****************************************************************************
	函 数 名  : tup_conf_video_get_devicecapbilityinfo
	功能描述  : 获取指定设备的能力集信息列表
	输入参数  : handle: 会议句柄
				deviceid: 视频设备ID
				pcapbility_info: 指向视频设备能力结构体数组的指针
	输出参数  : pcapbility_info: 指向视频设备能力结构体数组的指针
				ret_count:当pcapbility_info为空时，返回数量
	返 回 值  : 返回TC_OK表示成功，其他表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_get_devicecapbilityinfo(CONF_HANDLE handle, TUP_UINT32 deviceid, TC_VIDEO_PARAM* pcapbility_info,TUP_UINT32* ret_count);	

	/*****************************************************************************
	函 数 名  : tup_conf_video_open
	功能描述  : 打开自己的摄像头，该操作会启用自己的摄像头
	输入参数  : handle: 会议句柄
				deviceid: 视频设备ID
				preview: 是否需要预览，不预览则不会回调COMPT_MSG_VIDEO_ON_SWITCH消息
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其他表示失败
	回调消息  : COMPT_MSG_VIDEO_ON_SWITCH
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_open(CONF_HANDLE handle, TUP_UINT32 deviceid,TUP_BOOL preview );		

	/*****************************************************************************
	函 数 名  : tup_conf_video_close
	功能描述  : 关闭自己的摄像头
	输入参数  : handle: 会议句柄
				deviceid: 视频设备ID				
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其他表示失败
	回调消息  : COMPT_MSG_VIDEO_ON_SWITCH
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_close(CONF_HANDLE handle, TUP_UINT32 deviceid);	

	/*****************************************************************************
	函 数 名  : tup_conf_video_setparam
	功能描述  : 设置视频的相关参数，打开视频之前需要设置，如不设置那么就采用缺省值进行设置
	输入参数  : handle: 会议句柄
				deviceid: 视频设备ID
				pvparam: 指向视频设备能力结构体的指针
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其他表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_setparam(CONF_HANDLE handle, TUP_UINT32 deviceid, TC_VIDEO_PARAM* pvparam);

	/*****************************************************************************
	函 数 名  : tup_conf_video_getparam
	功能描述  : 获取视频的相关参数
	输入参数  : handle: 会议句柄
				deviceid: 视频设备ID
	输出参数  : pvparam: 指向视频设备能力结构体的指针
	返 回 值  : 返回TC_OK表示成功，其他表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_getparam(CONF_HANDLE handle, TUP_UINT32 deviceid, TC_VIDEO_PARAM* pvparam);

	/*****************************************************************************
	函 数 名  : tup_conf_video_notify
	功能描述  : 通知其它与会者打开或关闭设备
	输入参数  : handle: 会议句柄
				notifycmd: 通知类型，取值：
							VIDEO_NOTIFY_OPEN   //打开
							VIDEO_NOTIFY_CLOSE   //关闭
							VIDEO_NOTIFY_DATA_SENDTO_PHONESESSION   //视频数据发送给电话会场
				userid: 被通知的用户ID
				pvparam: 指向视频设备能力结构体的指针
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其他表示失败
	回调消息  : COMPT_MSG_VIDEO_ON_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_notify(CONF_HANDLE handle, TUP_UINT32 notifycmd,TUP_UINT32 userid,TC_VIDEO_PARAM* pvparam);

	/*****************************************************************************
	函 数 名  : tup_conf_video_switch_channel
	功能描述  : 对于接收端来说，切换到高流或是低流(VTM项目不用考虑这个接口)
	输入参数  : handle: 会议句柄
				userid: 用户ID
				deviceid: 视频设备ID
				highchannel: 切换到高流(TRUE)或是低流(FALSE)
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其他表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_switch_channel(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_BOOL highchannel );

	/*****************************************************************************
	函 数 名  : tup_conf_video_attach
	功能描述  : 指定用户的视频与窗口进行绑定
	输入参数  : handle: 会议句柄
				userid: 用户ID
				deviceid: 视频设备ID
				pwnd: 窗口句柄
				highchannel: 加入高流(TRUE)或是低流(FALSE)(默认高流)	
				showmode: 视频在窗口显示模式，取值:
									0 //表示布满窗口 
									1 //表示按视频的比例进行显示，其余部分以黑色填充
									2 //表示按窗口大小进行裁剪
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其他表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_attach(CONF_HANDLE handle,TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_VOID* pwnd, TUP_BOOL highchannel , TUP_UINT8 showmode );

	/*****************************************************************************
	函 数 名  : tup_conf_video_detach
	功能描述  : 指定用户视频与窗口进行解绑
	输入参数  : handle: 会议句柄
				userid: 用户ID
				deviceid: 视频设备ID
				pwnd: 窗口句柄
				bleavechannel: Detach窗口的时候，是否需要离开channel (默认是不离开channel),离开channel则不接收数据
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其他表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_video_detach(CONF_HANDLE handle,TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_VOID* pwnd, TUP_BOOL bleavechannel);



	/*************************白板基本接口*************************/


	/*****************************************************************************
	函 数 名  : tup_conf_ds_new_doc
	功能描述  : 新建一个空的白板文档，其他所有与会者都会收到新建白板的通知
	输入参数  : handle: 会议句柄				
	输出参数  : ret_docid: 新建白板文档成功后通过该参数返回白板文档ID
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：白板模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：白板会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_WB_ON_DOC_NEW
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_new_doc(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32* ret_docid);

	/*****************************************************************************
	函 数 名  : tup_conf_ds_new_page
	功能描述  : 在指定的白板文档中新建白板页，如果新建成功，新建的页面将被作为该文档的最后一页，其他所有与会者都会收到新建页的通知
	输入参数  : handle: 会议句柄
				docid: 白板文档的ID
				width: 要创建的页面的宽度，以TWIPS为单位
				height: 要创建的页面的高度，以TWIPS为单位
	输出参数  : ret_pageid: 如果新建页面成功，通过该参数返回新页面的ID，如果该参数为NULL则不返回
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_WB_ON_PAGE_NEW
				COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY
				COMPT_MSG_WB_ON_CURRENT_PAGE_IND
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_new_page(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_INT32 width, TUP_INT32 height, TUP_UINT32* ret_pageid);	

	/*****************************************************************************
	函 数 名  : tup_conf_wb_delete_doc
	功能描述  : 删除一个白板文档，其他所有与会者都会收到删除消息并执行删除文档的操作
	输入参数  : handle: 会议句柄
				docid: 白板文档的ID
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：白板模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：白板会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_ERROR：删除失败
	回调消息  : COMPT_MSG_WB_ON_DOC_DEL
				COMPT_MSG_WB_ON_PAGE_DEL
				COMPT_MSG_WB_ON_CURRENT_PAGE_IND
				COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_delete_doc(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid);

	/*****************************************************************************
	函 数 名  : tup_conf_wb_delete_page
	功能描述  :删除指定白板文档中的指定页面
	输入参数  : handle: 会议句柄
				docid: 白板文档的ID
				pageid: 指定白板页面的ID
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_WB_ON_PAGE_DEL
				COMPT_MSG_WB_ON_CURRENT_PAGE_IND
				COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_delete_page(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid);



	/*****************************************************************************
	函 数 名  : tup_conf_ds_open
	功能描述  : 打开共享文档，文档成功加载后将被上传到服务器，其他所有与会者将会接收到该文档的内容
	输入参数  : handle: 会议句柄
				filename: 要打开的共享文档的全路径(utf8编码字符串)，不能为NULL
				option: 打开文档选项，取值：
						DS_OPTION_QUALITY	//质量优先，优先采用EMF格式
						DS_OPTION_SIZE  	//带宽优先，优先采用JPG格式
	输出参数  : ret_docid: uint32型指针，如果不为NULL，通过此值返回共享文档的ID 
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；参数错误
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_DS_ERROR_DOC_ALREADY_OPEN：文档已经被共享，不能再次共享
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_DS_ON_DOCLOAD_START
				COMPT_MSG_DS_ON_DOC_NEW
				COMPT_MSG_DS_ON_PAGE_NEW
				COMPT_MSG_DS_ON_PAGE_LOADED
				COMPT_MSG_DS_ON_DOCLOAD_FINISH
				COMPT_MSG_DS_ON_CURRENT_PAGE_IND
				COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_open(CONF_HANDLE handle,COMPONENT_IID ciid, const TUP_CHAR* filename, TUP_UINT32 option, TUP_UINT32* ret_docid);

	/*****************************************************************************
	函 数 名  : tup_conf_ds_close
	功能描述  : 关闭一个文档，其他所有与会者都会收到关闭消息
	输入参数  : handle: 会议句柄
				docid: 要关闭的共享文档的ID
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户已掉线
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_DS_ON_DOC_DEL
				COMPT_MSG_DS_ON_PAGE_DEL
				COMPT_MSG_DS_ON_CURRENT_PAGE_IND
				COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_close(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid);	                            


	/*****************************************************************************
	函 数 名  : tup_conf_ds_set_current_page
	功能描述  : 设置当前显示的页面，调用该接口后，当前显示的页面将被切换到指定的文档页，
				如果指定的文档ID为有效值而页面ID为0，则切换到该文档上次显示的页面。该函
				数有同步设置和非同步两种，同步设置时，其他所有与会者都会收到切换消息并
				执行相应操作，非同步时，只有本地发生变化
	输入参数  : handle: 会议句柄。为0时，用于文档预览
				docid: 文档ID
				pageid: 页面ID
				sync: 是否同步设置，0：非同步；1：同步
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_DS_ON_CURRENT_PAGE_IND
				COMPT_MSG_DS_ON_CURRENT_PAGE
				COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_set_current_page(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid, TUP_BOOL sync);	

	/*****************************************************************************
	函 数 名  : tup_conf_ds_set_dispsize
	功能描述  : 设置显示区域的大小，该函数需要在任何显示界面的操作之前被调用，否则将不
				能显示任何内容，建议在收到文档共享组件准备好的消息后调用该函数，或者在显示大
				小发生变化时调用
	输入参数  : handle: 会议句柄。为0时，用于文档预览
				size: 显示区域的宽高，以TWIPS为单位
				redraw: 调用函数后是否立刻重绘，0：不重绘，1：重绘
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_set_canvas_size(CONF_HANDLE handle, COMPONENT_IID ciid,TC_SIZE size, TUP_BOOL redraw);

	/*****************************************************************************
	函 数 名  : tup_conf_ds_set_pageorg
	功能描述  : 设置页面的显示起点，该函数需要在页面的显示起点发生变化时被调用，页面起点的设置只对指定的页面有效
	输入参数  : handle: 会议句柄。为0时，用于文档预览
				docid: 文档ID
				pageid: 页面的ID
				org: 被设置的新的显示起点，以TWIPS为单位，该值是画布左上角相对于页面左上角的偏移，向下向右为正
				sync: 是否同步，0：非同步，1：同步，同步时所有与会者都会收到起点变化通知，非同步时只有自己界面发生变化
				redraw: 是否强制重绘，0：不强制，1：强制，调用该函数时，如果设置的起点和原来的起点相同，且该参数为0，则不会重绘页面，否则重绘
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_DS_ERROR_DOC_NOTEXIST：文档不存在
				TC_DS_ERROR_PAGE_NOTEXIST：页面不存在
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_set_page_origin(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid,TC_POINT org, TUP_BOOL sync, TUP_BOOL redraw);

	/*****************************************************************************
	函 数 名  : tup_conf_ds_rotate_page
	功能描述  : 旋转指定页面背景，该函数只旋转文档的背景，不会对标注产生影响，该接口调用只对指定的页面产生影响
	输入参数  : handle: 会议句柄。为0时，用于文档预览
				docid: 文档ID
				pageid: 页面的ID
				rftype: 旋转类型
				sync: 是否同步，0：非同步，1：同步
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_rotate_page(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, DsRotateFlipType rftype, TUP_BOOL sync);

	/*****************************************************************************
	函 数 名  : tup_conf_ds_set_zoom
	功能描述  : 设置文档的缩放，该接口设置文档的缩放类型和缩放百分数，该接口调用对指定的文档产生影响，调用成功后，指定文档中所有的页面都具有相同的缩放
	输入参数  : handle: 会议句柄。为0时，用于文档预览
				docid: 文档的ID
				zoomtype: 缩放类型，当该值为DS_ZOOM_PAGESIZE时以实际页面的大小进行显示；当该值为DS_ZOOM_FITWIDTH时，
						  将宽度缩放到显示区域的大小，宽高比固定显示；当该值为DS_ZOOM_DISPSIZE时，按照显示区域刚
						  好能显示下整个页面的大小进行显示；当该值为DS_ZOOM_PERCENT时，直接按照factor参数中传入的百分比进行显示。
				factor: 缩放因子，百分值，比如放大到200%，则该参数为200，仅当zoomType的值为DS_ZOOM_PERCENT时该值起作用
				sync: 是否同步缩放，0：非同步；1：同步
				redraw: 是否调用该接口后立即刷新界面，0：暂不刷新，1：立即刷新
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_DS_ERROR_DOC_NOTEXIST：文档不存在
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_DS_ON_DRAW_DATA_NOTIFY
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_set_zoom(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 zoomtype, TUP_UINT32 factor, TUP_BOOL sync, TUP_BOOL redraw);

	/*****************************************************************************
	函 数 名  : tup_conf_ds_getdoc_property
	功能描述  : 获取文档属性及/或属性数据长度
	输入参数  : handle: 会议句柄。为0时，用于文档预览
				docid: 文档的ID
				nPropertyID: 文档属性ID，参考枚举值DocProperty
				nRetLen: 作为入参时传入lpBuf的长度				
	输出参数  : lpBuf: 用于保存属性数据的buffer，为NULL时通过nRetLen返回要获取数据的长度
				nRetLen: 成功获取数据后通过该参数返回实际数据的长度，如果lpBuf为NULL，则通过该参数返回实际数据的长度，该参数不能为NULL
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建 
				TC_DS_ERROR_PROP_NOT_EXIT：属性不存在
				TC_PARAM_ERROR：输入参数错误
				TC_BUFFER_TOO_SHORT：内存块太小
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_get_doc_property(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid,TUP_UINT32 nPropertyID,TUP_UINT8* lpBuf,TUP_UINT32* nRetLen);

	/*****************************************************************************
	函 数 名  : tup_conf_ds_getpage_property
	功能描述  : 获取页面属性及/或属性数据长度
	输入参数  : handle: 会议句柄。为0时，用于文档预览
				docid: 文档的ID
				pageid: 页面ID
				nPropertyID: 页面属性ID
				nRetLen: 作为入参时传入lpBuf的长度				
	输出参数  : lpBuf: 用于保存属性数据的buffer，为NULL时通过nRetLen返回要获取数据的长度
				nRetLen: 成功获取数据后通过该参数返回实际数据的长度，如果lpBuf为NULL，则通过该参数返回实际数据的长度，该参数不能为NULL
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建 
				TC_DS_ERROR_PROP_NOT_EXIT：属性不存在
				TC_PARAM_ERROR：输入参数错误
				TC_BUFFER_TOO_SHORT：内存块太小
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_get_page_property(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid,TUP_UINT32 pageid,TUP_UINT32 nPropertyID,
														TUP_UINT8* lpBuf,TUP_UINT32* nRetLen);	

	/*****************************************************************************
	函 数 名  : tup_conf_ds_get_surfacebmp
	功能描述  : 获取渲染好的当前页面图像，返回值为该图像的数据指针
	输入参数  : handle: 会议句柄。为0时，用于文档预览
	输出参数  : ret_width: 如果该值不为NULL，则通过该值返回图像的宽度(TWIPS)
				ret_height: 如果该值不为NULL，则通过该值返回图像的高度(TWIPS)
	返 回 值  : NULL：获取图像失败；
				非NULL：成功获取到的图像数据，数据格式与conf_ds_set_surface_output_format设置的一致，如果没有设置则为默认值：windows平台为HDC，iOS平台为BMP
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_VOID* tup_conf_ds_get_surfacebmp(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32* ret_width, TUP_UINT32* ret_height);

	/*****************************************************************************
	函 数 名  : tup_conf_ds_set_bgcolor
	功能描述  : 设置文档共享模块画布的背景色
	输入参数  : handle: 会议句柄
				bgColor: 背景颜色值
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_VOID  tup_conf_ds_set_bgcolor(CONF_HANDLE handle,COMPONENT_IID ciid,  COLORRGBA bgColor);

	/*****************************************************************************
	函 数 名  : tup_conf_ds_set_dispmode
	功能描述  : 设置文档共享模块的显示模式
	输入参数  : handle: 会议句柄
				dispMode: 显示模式
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_VOID  tup_conf_ds_set_dispmode(CONF_HANDLE handle,COMPONENT_IID ciid,  DsDispMode dispMode);

	/*****************************************************************************
	函 数 名  : tup_conf_ds_get_syncinfo
	功能描述  : 获取服务器上的当前信息，一般用于与会者向主讲人同步
	输入参数  : handle: 会议句柄				
	输出参数  : pInfo: 用于保存获取到的当前当前服务器信息
	输出参数  : 无
	返 回 值  : TC_OK 获取成功
				TC_ERROR 获取失败，一般是因为数据库对象未创建完成
				TC_FAILURE 调用失败，一般是调用太早，会议未创建
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_get_syncinfo(CONF_HANDLE handle,COMPONENT_IID ciid,  DsSyncInfo* pInfo);

	
	/*************************标注基本接口*************************/

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_init_resource
	功能描述  : 初始化本地标注图标资源，该接口需要在模块准备好后尽早被调用，如果不需要
				初始化本地资源可以不调用，通过该接口初始化的资源可以被所有用到标注的模
				块所共用，因此，如果不同的模块有不同的资源，应用层在定义标注ID时不能重
				复，同样，各模块间用到的相同的资源只需要定义一次。
				同一图标资源的ID各互通客户端必须一致，图标注的显示宽高及基点偏移量也必
				须相同（具有相同的显示值，TWIPS单位，但图片的原始尺寸各客户端可以根据
				需要设计，但需要注意尺寸的比例需要相同，否则可能出现不同客户端上同一标
				注的显示效果不同），这属于应用层协议范围，应该各客户端一起定义，之后不
				能随便更改，且更改时必须考虑前后版本兼容性。
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				pitems: 资源数组
				count: pRes数组的元素个数
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_init_resource(CONF_HANDLE handle,COMPONENT_IID ciid, 	Anno_Resource_Item* pitems,TUP_INT32 count);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_reg_customer_type
	功能描述  : 注册上层应用自定义的标注类型，该接口注册的标注都属于DS_ANNOT_TYPE_CUSTOMER
				的子类型，且都是图片类的标注，该接口需要在这些被定义的标注被创建之前调用，
				通过该接口注册的标注类型可以被同一应用的不同模块使用，因此，如果不同模块之
				间有不同的标注，标注的ID需要能够相互区分，相同的标注类型只需定义一次。
				标注子类型的定义各互通的客户端必须完全一样，包括类型ID和属性，这属于应
				用层协议范围，应该各客户端一起定义，之后不能随便更改，且更改时必须考虑前
				后版本兼容性。
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				pdefintypes: 要注册的自定义标注类型数组
				nCount: 数组的元素个数
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_reg_customer_type(CONF_HANDLE handle,COMPONENT_IID ciid, DsDefineAnnot* pdefintypes,TUP_INT32 count);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_set_config
	功能描述  : 设置本地标注的相关参数，白板、文档、屏幕共享三个模块均可调用此接口，
				如果不调用，bSelfLpNotDisp的值默认为0，即底层会渲染自己的激光点标注
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				config: 标注的参数
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_ERROR：指定ciid模块不合法或未加载；失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_set_config(CONF_HANDLE handle,COMPONENT_IID ciid,	AnnotationConfig config);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_create_start
	功能描述  : 开始创建一个标注，该接口用于DS_ANNOT_TYPE_DRAWING和DS_ANNOT_TYPE_CUSTOMER
				两种标注的创建，这两类标注的创建必须通过调用该函数开始
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				docid: 文档的ID
				pageid: 页面ID
				type: 标注主类型，这里暂时只有DS_ANNOT_TYPE_DRAWING和DS_ANNOT_TYPE_CUSTOMER两种
				subtype: 标注子类型，包括DRAWING的子类型和通过conf_annotation_reg_customer_type注册的类型
				point: 创建标注的起点，一般是鼠标按下的点或图片标注的左上角，以TWIPS为单位，且
						该值必须是相对于页面左上角并且无缩放情况下的值，向下向右为正
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；参数错误
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_DS_ERROR_DOC_NOTEXIST：文档不存在
				TC_DS_ERROR_PAGE_NOTEXIST：页面不存在
				TC_ANNOT_ERROR_CUSTOMERTYPE_NOTEXIST：标注类型未定义
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_create_start(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid,
													TUP_UINT32 type, TUP_UINT32 subtype, TC_POINT point);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_create_update
	功能描述  : 标注创建过程中更新数据，主要用于DS_ANNOT_TYPE_DRAWING和DS_ANNOT_TYPE_CUSTOMER
				两种标注的数据更新，调用该函数后，组件将会更新创建过程中的虚线框，并向应用层提
				供变化后的界面数据
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				pdata: 更新数据，对于DS_ANNOT_TYPE_DRAWING类的标注，数据类型为CreateDrawingData*；
					   对于DS_ANNOT_TYPE_CUSTOMER类的标注，数据类型为CreateCustomerData*
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；参数错误
				TC_ERROR：其它错误

	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_create_update(CONF_HANDLE handle, COMPONENT_IID ciid,TUP_VOID* pdata);		

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_create_done
	功能描述  : 标注创建结束，主要用于DS_ANNOT_TYPE_DRAWING和DS_ANNOT_TYPE_CUSTOMER
				两种标注，这两种标注必须调用该接口来完成创建，标注创建完成后，
				其他与会者会收到创建标注的通知。
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				bCancel: 消创建，还是创建完成，0：完成创建，1：取消创建，
						 完成创建则该标注被添加到创建的页面上，取消创建则会删除该标注
	输出参数  : ret_annoid: 创建完成后通过该参数返回该标注的ID，如果为NULL则不返回
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_create_done(CONF_HANDLE handle, COMPONENT_IID ciid,TUP_BOOL bCancel,TUP_UINT32* ret_annoid);		

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_laserpointer_start
	功能描述  : 开始激光点
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				dispSize: 显示的激光点的大小，TWIPS为单位，当bLocal为1时，大小必须与初始化资源时传入的显示宽高相同
				bLocal: 是否使用已经通过conf_annotation_init_resource初始化的资源，0：不使用，1：使用
				localIndex: bLocal为1时，该参数有效，表示资源ID
				picFormat: bLocal为0时有效，表示激光点图标的图片格式
				pData: bLocal为0时有效，图片数据指针
				dataLen: bLocal为0时有效，图片数据的长度
				picW: Local为0时有效，图片的宽，像素为单位
				picH: bLocal为0时有效，图片的高，像素为单位
				ptOffset: bLocal为0时有效，表示图片中心点相对于左上角的偏移，以TWIPS为单位，
						  该值在缩放情况下对于固定大小的标注起作用，缩放时会以该值为中心点，
						  重新计算缩放后的图片左上角起点，而不是对左上角起点直接进行缩放。
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_laserpointer_start(CONF_HANDLE handle, COMPONENT_IID ciid, 
		TC_SIZE dispSize, TUP_INT bLocal, TUP_INT localIndex, TUP_INT picFormat, TUP_VOID* pData, TUP_INT dataLen, TUP_INT picW, TUP_INT picH, TC_POINT ptOffset);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_laserpointer_moveto
	功能描述  : 
	输入参数  : handle: 会议句柄 
				ciid: 组件ID，目前标注支持文档共享和白板
				point: 移动到的点（激光点的中心坐标），以TWIPS为单位，且该值必须是相对于页面左上角并且无缩放情况下的值，向下向右为正
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_DS_ERROR_DE_NOTEXIST：激光点未创建
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_laserpointer_moveto(CONF_HANDLE handle,COMPONENT_IID ciid, TC_POINT point);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_laserpointer_stop
	功能描述  : 结束激光点，只能结束自己的激光点
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_DS_ERROR_DE_NOTEXIST：激光点未创建
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_laserpointer_stop(CONF_HANDLE handle, COMPONENT_IID ciid);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_text_create
	功能描述  : 创建文字标注
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				docid: 文档的ID
				pageid: 页面ID
				pInfo: 文字标注的信息
	输出参数  : ret_annoid: 创建成功后通过该参数返回创建成功的标注的ID，如果该参数为NULL则不返回
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_PARAM_ERROR：参数错误
				TC_DS_ERROR_DOC_NOTEXIST：文档不存在
				TC_DS_ERROR_PAGE_NOTEXIST：页面不存在
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_text_create(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, 
		DsAnnotTextInfo* pInfo, TUP_UINT32* ret_annoid);	

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_text_update
	功能描述  : 更新文字标注
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				docid: 文档的ID
				pageid: 页面ID
				annoid: 要更新的文字标注的ID
				pInfo: 文字标注的信息
				redraw: 更新成功后是否立刻重绘，0：不重绘，1：重绘
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_PARAM_ERROR：参数错误
				TC_DS_ERROR_DOC_NOTEXIST：文档不存在
				TC_DS_ERROR_PAGE_NOTEXIST：页面不存在
				TC_DS_ERROR_DE_NOTEXIST：标注不存在
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_text_update(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, TUP_UINT32 annoid, DsAnnotTextInfo* pInfo, TUP_BOOL redraw);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_text_getinfo
	功能描述  : 获取一个文字标注的信息
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				docid: 文档的ID
				pageid: 页面ID
				annoid: 文字标注的ID
	输出参数  : pInfo: 通过该参数返回获取到的文字标注信息，如果为NULL则返回错误
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_PARAM_ERROR：参数错误
				TC_DS_ERROR_DOC_NOTEXIST：文档不存在
				TC_DS_ERROR_PAGE_NOTEXIST：页面不存在
				TC_DS_ERROR_DE_NOTEXIST：标注不存在
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_text_getinfo(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, TUP_UINT32 annoid, DsAnnotTextInfo* pInfo);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_edit_start
	功能描述  : 开始编辑标注，主要指标注的移动和拉伸操作
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				docid: 文档的ID
				pageid: 页面ID
				annotids: 要编辑的标注id数组
				count:annotids数组元素的个数
				refannotid:多个标注一起编辑时用到的，表示当时鼠标落点所在的标注ID
				edittype: 编辑类型
				startpoint: 编辑开始的点，以TWIPS为单位，且该值必须是相对于页面左上角并且无缩放情况下的值，向下向右为正
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_DS_ERROR_DOC_NOTEXIST：文档不存在
				TC_DS_ERROR_PAGE_NOTEXIST：页面不存在
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_edit_start(CONF_HANDLE handle, 
		COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, TUP_UINT32* annotids, TUP_INT32 count, 
		TUP_UINT32 refannotid, DS_HITTEST_CODE edittype, TC_POINT startpoint);	

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_edit_update
	功能描述  : 编辑标注过程中的数据更新
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				currentpoint: 移动到的点，以TWIPS为单位，且该值必须是相对于页面左上角并且无缩放情况下的值，向下向右为正
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_edit_update(CONF_HANDLE handle, COMPONENT_IID ciid,TC_POINT currentpoint);	

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_edit_done
	功能描述  : 标注编辑完成，编辑标注必须调用此函数才能结束
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				cancel: 是否取消操作，0：否，1：是
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_edit_done(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_BOOL cancel);					    

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_hittest
	功能描述  : 测试一个点是否落在标注上，如果落在标注上则返回该标注的ID、类型及落点的位置
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				docid: 文档的ID
				pageid: 页面ID
				pt: 要判断的点，以TWIPS以单位，且必须是相对于页面原点无缩放的坐标
				hitmode: 测试条件
				userid: 用户ID，当hitMode为DS_HITTEST_MODE_OTHERS或DS_HITTEST_MODE_SOMEONE时有效
	输出参数  : selectId: 如果要测试的点选中了某个标注，通过该值返回
				hit_result: 测试结果
				annotType: 点中的标注的标注类型通过该参数返回
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_ERROR：其它错误
	回调消息  : 无
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
	函 数 名  : tup_conf_annotation_hittest_rect
	功能描述  : 测试一个矩形框包括的标注，返回被矩形框包括的标注ID及数量
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				docid: 文档的ID
				pageid: 页面ID
				rect: 要测试的矩形
				hitmode: 测试条件
				userid: 用户ID，当hitMode为DS_HITTEST_MODE_OTHERS、DS_HITTEST_MODE_SOMEONE、
					    DS_HITTEST_MODE_OTHERS_FORCE或DS_HITTEST_MODE_SOMEONE_FORCE时有效
	输出参数  : selectids: 通过该参数返回被选中的标注的数组指针，应用层不能释放该内存
				count: 通过该参数返回选中标注数组中的元素个数
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_ERROR：其它错误
	回调消息  : 无
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
	函 数 名  : tup_conf_annotation_setselect
	功能描述  : 设置标注的选中状态
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				docid: 文档的ID
				pageid: 页面ID
				ids: 要设置的标注元素id的数组
				count: ids中的元素个数
				selectmode: 选中的模式
				userid: 用户ID，当selectMode的值为DS_SELECT_MODE_OTHERS或DS_SELECT_MODE_SOMEONE时有效
				redraw: 设置选中状态后是否立刻重绘，1：是，0：否
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NOTEXIST：文档不存在
				TC_DS_ERROR_PAGE_NOTEXIST：页面不存在
				TC_ERROR：其它错误
	回调消息  : 无
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
	函 数 名  : tup_conf_annotation_delete
	功能描述  : 删除标注
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				docid: 文档的ID
				pageid: 页面ID
				ids: 要删除的标注元素id数组
				count: ids中的元素个数
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_DS_ERROR_DOC_NOTEXIST：文档不存在
				TC_DS_ERROR_PAGE_NOTEXIST：页面不存在
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_delete(CONF_HANDLE handle, COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, TUP_UINT32* ids, TUP_INT32 count);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_set_pen
	功能描述  : 设置画笔属性
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				pentype: 要设置的笔的类型，普通笔或高亮笔
				newpen: 要设置的画笔的属性
	输出参数  : oldpen: 通过该参数返回原来的画笔的属性，如果该参数为NULL则不返回
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_set_pen(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_INT32 pentype, DsPenInfo newpen, DsPenInfo* oldpen);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_set_brush
	功能描述  : 设置画刷属性
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				newbrush: 要设置的画刷的属性
	输出参数  : oldbrush: 通过该参数返回原来的画刷的属性，如果该参数为NULL则不返回
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_set_brush(CONF_HANDLE handle, COMPONENT_IID ciid, DsBrushInfo newbrush,DsBrushInfo* oldbrush);

	/*****************************************************************************
	函 数 名  : tup_conf_annotation_get_annotinfo
	功能描述  : 获取指定标注的信息
	输入参数  : handle: 会议句柄
				ciid: 组件ID，目前标注支持文档共享和白板
				docid: 文档的ID
				pageid: 页面ID
				annotid: 标注ID
	输出参数  : pannotinfo：标注信息结构体指针，用于保存获取到的标注信息，该参数不能为NULL
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；或pInfo参数为NULL；
				TC_ERROR：指定ciid模块不合法或未加载；失败
				TC_DS_ERROR_DOC_NOTEXIST：指定文档不存在
				TC_DS_ERROR_PAGE_NOTEXIST：指定页面不存在
				TC_DS_ERROR_DE_NOTEXIST：指定标注不存在
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_annotation_get_annotinfo(CONF_HANDLE handle,COMPONENT_IID ciid,TUP_UINT32 docid,TUP_UINT32 pageid,
														TUP_UINT32 annotid,DsAnnotInfo* pannotinfo);	

#ifdef __cplusplus
};


#endif

#endif