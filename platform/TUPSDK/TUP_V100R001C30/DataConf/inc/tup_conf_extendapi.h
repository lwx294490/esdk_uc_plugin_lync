#ifndef _TUP_CONF_EXTENDAPI_H_
#define _TUP_CONF_EXTENDAPI_H_

#include "tup_conf_extenddef.h"

#ifdef __cplusplus
	extern "C" {
#endif
	/*************************会议部分*************************/
	/*****************************************************************************
	函 数 名  : tup_conf_setiplist
	功能描述  : 设置MS地址列表
	输入参数  : handle: 会议句柄
				svrlist: IP列表,'|'或';'分割，例如：192.168.1.1|192.168.1.2
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_setiplist(CONF_HANDLE handle, const TUP_CHAR * svrlist);
	
	/*****************************************************************************
	函 数 名  : tup_conf_setipmap
	功能描述  : 设置服务器IP地址映射表
	输入参数  : handle: 会议句柄
				pnatmap：映射表数组指针
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_setipmap(CONF_HANDLE handle,IP_NAT_MAP* pnatmap,TUP_UINT32 count);
	
	/*****************************************************************************
	函 数 名  : tup_conf_setconfig
	功能描述  : 设置网络配置
	输入参数  : handle: 会议句柄
				pconfig: 网络配置信息
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_setconfig(CONF_HANDLE handle, const TC_CONF_INIT_CONFIG* pconfig);
	
	/*****************************************************************************
	函 数 名  : tup_conf_set_qos_option
	功能描述  : 设置QoS（网关数据发送控制选项：如数据发送优先级）值
	输入参数  : handle: 会议句柄
				datatype: 数据类型，枚举值：QOS_TYPE_AUDIO、QOS_TYPE_VIDEO、QOS_TYPE_DATA
				nvalue: QOS值（网络传输质量）
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_set_qos_option(CONF_HANDLE handle, TUP_UINT32 datatype,TUP_UINT32 nvalue);
	
	/*****************************************************************************
	函 数 名  : tup_conf_log_delete
	功能描述  : 删除多少天前的日志，即保留指定天数的日志
	输入参数  : nDay: 预留日志的天数。（例如，如果nDay为1，则保留当天日志）				
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_log_delete(TUP_UINT32 nDay);
	
	/*****************************************************************************
	函 数 名  : tup_conf_get_server_time
	功能描述  : 获取服务器时间
	输入参数  : handle: 会议句柄				
	输出参数  : 无
	返 回 值  : 无
	回调消息  : CONF_MSG_SERVER_TIME
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_get_server_time(CONF_HANDLE handle);
	
	/*****************************************************************************
	函 数 名  : tup_conf_flowcontrol_limit
	功能描述  : 平滑发送各种数据类型的带宽控制
	输入参数  : handle: 会议句柄
				datatype:数据类型，参考LIMIT_DATA_TYPE枚举值
				limitsize: 数据大小，单位：Bytes/s
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_flowcontrol_limit(CONF_HANDLE   handle, TUP_UINT32 datatype,TUP_UINT32 limitsize); 
	
	/*****************************************************************************
	函 数 名  : tup_conf_user_update_info
	功能描述  : 更新用户扩展信息
	输入参数  : handle: 会议句柄
				userid: 用户ID
				pUserInfo: 用户信息
				nInfoLen: 用户信息长度
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_USER_ON_MODIFY_IND
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_user_update_info(CONF_HANDLE handle,TUP_UINT32 userid,TUP_UINT8* pUserInfo,TUP_UINT16 nInfoLen);
	
	/*****************************************************************************
	函 数 名  : tup_conf_send_data
	功能描述  : 发送数据，参数userid为0是为广播数据。该接口最大发送数据广播为8K，
				发送指定人为16K，建议通过该接口发送命令数据，不建议发送大块数据
	输入参数  : handle: 会议句柄
				userid: 用户ID, 0为广播
				msg_id: 用户定义的消息ID。支持范围[0, 85]				
				pbuffer: 数据内容
				len: 数据长度，最大发送数据广播为8K，发送指定人为16K
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_USER_ON_MESSAGE_IND
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_send_data(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT8 msg_id,TUP_UINT8 * pbuffer, TUP_UINT32 len);
	
	/*****************************************************************************
	函 数 名  : tup_conf_update_param
	功能描述  : 创建或更新全局唯一参数，参数采用名称为唯一标识
	输入参数  : handle: 会议句柄
				param_name: 全局参数名称
				pbuffer: 数据内容
				len: 数据长度
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : CONF_MSG_ON_MESSAGE_UPADATE
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_update_param(CONF_HANDLE handle,const TUP_CHAR * param_name, TUP_VOID* pbuffer, TUP_UINT16 len);


	/*************************屏幕共享高级接口*************************/
	/*****************************************************************************
	函 数 名  : tup_conf_as_getapplist
	功能描述  : 获取当前的程序列表
	输入参数  : handle: 会议句柄
	papplist:程序列表(TC_AS_WndInfo* 类型)数组指针
	pappcount: papplist的长度
	输出参数  : papplist: 返回的程序列表(TC_AS_WndInfo* 类型)指针
	pappcount: 返回程序的个数
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_getapplist(CONF_HANDLE handle, TC_AS_WndInfo *papplist , TUP_UINT32 *pappcount);

	/*****************************************************************************
	函 数 名  : tup_conf_as_setsharingapp
	功能描述  : 设置需要共享的程序
	输入参数  : handle: 会议句柄
	pappwnd: 需要操作的窗口句柄
	action: 操作类型。取值（非法值返回失败）：
	AS_ACTION_DELETE	删除操作
	AS_ACTION_ADD		添加操作
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_as_setsharingapp(CONF_HANDLE handle, TUP_VOID* pappwnd, TUP_UINT32 action);

	/*****************************************************************************
	函 数 名  : tup_conf_as_setparam
	功能描述  : 设置屏幕共享或应用程序共享相关参数
	输入参数  : handle: 会议句柄
				param: 参数结构体
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_setparam(CONF_HANDLE handle,TC_AS_PARAM* param);	
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_getparam
	功能描述  : 获取屏幕共享或应用程序共享相关参数
	输入参数  : handle: 会议句柄
				param: 输入需要获取参数的类别
	输出参数  : param: 输出对应参数的值
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_getparam(CONF_HANDLE handle,const TC_AS_PARAM* param);	

		/*****************************************************************************
	函 数 名  : tup_conf_as_startex
	功能描述  : 开始桌面共享或应用程序共享（如果当前设定采集方式为AS_CAPTURE_MD时，
				该接口不会将驱动启动，如果当前驱动没有启动，屏幕共享自动转用
				AS_CAPTURE_GDI采集方式）	
	输入参数  : handle: 会议句柄				
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_startex(CONF_HANDLE handle);
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_stopex
	功能描述  : 停止桌面共享或应用程序共享（如果当前设定采集方式为AS_CAPTURE_MD，
				并且虚拟显卡驱动已经启动时，该接口不会主动将驱动关闭）
	输入参数  : handle: 会议句柄				
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_stopex(CONF_HANDLE handle);
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_pause
	功能描述  : 暂停桌面共享或应用程序共享
	输入参数  : handle: 会议句柄				
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_SHARING_STATE
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_pause(CONF_HANDLE handle,TUP_BOOL pause);
	
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_flushscreendata
	功能描述  : 共享时，在观看端强制刷新一帧
	输入参数  : handle: 会议句柄				
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_SCREEN_DATA
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_flush_screendata(CONF_HANDLE handle);	
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_senduserdata
	功能描述  : 发送用户自定义消息
	输入参数  : handle: 会议句柄
				datatype: 自定义消息类型
				userid: 用户ID,0为广播
				pbuffer: 消息数据
				len: 消息数据长度，最大长度AS_USERDEFINE_MSG_MAX_LEN
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_USERDEFINE_MSG
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_senduserdata( CONF_HANDLE handle,TUP_UINT32 datatype, TUP_UINT32 userid, TUP_VOID* pbuffer, TUP_UINT32 len );
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_lock_screen_data
	功能描述  : 锁定屏幕数据，使用后需要调用tup_conf_as_unlock_screen_data释放。该函数只在tup_conf_init设置独立线程模型下调用
	输入参数  : handle: 会议句柄				
	输出参数  : pscreendata : 返回的屏幕数据
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_lock_screen_data(CONF_HANDLE handle,TC_AS_SCREENDATA* pscreendata);	
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_unlock_screen_data
	功能描述  : 解锁屏幕数据
	输入参数  : handle: 会议句柄				
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_unlock_screen_data(CONF_HANDLE handle);
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_attach
	功能描述  : 屏幕共享中，观看端加入某个数据通道
	输入参数  : handle: 会议句柄
				channel_type: 通道类型。取值：
									AS_CHANNEL_TYPE_NORMAL			//当前只有该值有效
									AS_CHANNEL_TYPE_LOW_QUALITY
									AS_CHANNEL_TYPE_TP
				hwnd: 扩展备用
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_ CHANNEL
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_attach(CONF_HANDLE handle, TUP_INT32 channel_type, TUP_VOID* hwnd);
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_detach
	功能描述  : 屏幕共享中，观看退出某个数据通道
	输入参数  : handle: 会议句柄
				channel_type: 通道类型。取值：
									AS_CHANNEL_TYPE_NORMAL
									AS_CHANNEL_TYPE_LOW_QUALITY
									AS_CHANNEL_TYPE_TP				
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_AS_ON_ CHANNEL
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_detach(CONF_HANDLE handle, TUP_INT32 channel_type);

	
	/*****************************************************************************
	函 数 名  : tup_conf_as_settransparentwindow
	功能描述  : 设置需要被透明的窗口
	输入参数  : handle: 会议句柄
				hwnd: 透明窗口句柄，hwnd必须有效
				action: 
					AS_ACTION_DELETE//释放
					AS_ACTION_ADD//拥有
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_set_transparentwindow(CONF_HANDLE handle, TUP_VOID *hwnd, TUP_UINT32 action);
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_request_keyframe
	功能描述  : 屏幕共享观看端请求全屏帧
	输入参数  : handle: 会议句柄
				reason: 请求原因（保留）
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_request_keyframe(CONF_HANDLE handle, TUP_UINT32 reason);
	
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_getdisplayinfo
	功能描述  : 获取显示器信息
	输入参数  : handle: 会议句柄				
	输出参数  : pdisplay_info:显示器信息 
				ret_count: 当pMonitorInfo为空时，返回数量
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_get_displayinfo(CONF_HANDLE handle, MonitorInfo* pdisplay_info,TUP_UINT32* ret_count);
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_getdisplaythumbnail
	功能描述  : 获取显示器缩略图
	输入参数  : handle: 会议句柄
				index : 显示器索引
				width: 缩略图宽度
				height: 缩略图高度
				pbuffer : 缩略图数据内存, 不带图片头信息
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_get_displaythumbnail(CONF_HANDLE handle, TUP_UINT32  index, TUP_UINT32  width, TUP_UINT32 height, TUP_UINT8* pbuffer);
	
	/*****************************************************************************
	函 数 名  : tup_conf_as_setsharingdisplayindex
	功能描述  : 设置共享的屏幕
	输入参数  : handle: 会议句柄
				index : 显示器索引
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_as_set_sharing_display(CONF_HANDLE handle, TUP_UINT32  index);



	/*********************************************视频高级接口*********************************************/
	
	/*****************************************************************************
	函 数 名  : tup_conf_video_set_max_count
	功能描述  : 设置会议的最大打开视频数（缺省值是6，如果参数nMaxOpenVideo为0，那么
				会设置成缺省值6，最大值16）。一个会议中，只能调用一次，如果有主持人的话，让主
				持人调用
	输入参数  : handle: 会议句柄
				max_count: 会议最大打开视频数
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_VIDEO_ON_MAX_OPENVIDEO
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_set_max_count(CONF_HANDLE handle, TUP_UINT32 max_count);
	
	/*****************************************************************************
	函 数 名  : tup_conf_video_set_lowstream_resolution
	功能描述  : 设置视频双流时低流的分辨率。（缺省的话，由组件设置成QQVGA（160*120））
	输入参数  : handle: 会议句柄				
				width: 应用层设置低流的宽
				height: 应用层设置低流的高
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_set_lowstream_resolution(CONF_HANDLE handle, TUP_UINT32 width, TUP_UINT32 height);
	
	/*****************************************************************************
	函 数 名  : tup_conf_video_set_encode_maxresolution
	功能描述  : 设置编码的最大分辨率，如果未设置那么就采用缺省值。Windows系统为1920*1080，Android和IOS版本为640*480
	输入参数  : handle: 会议句柄
				width: 编码的最大分辨率的宽
				height: 编码的最大分辨率的高
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_set_encode_max_resolution(CONF_HANDLE handle, TUP_UINT32 width, TUP_UINT32 height);
	
	/*****************************************************************************
	函 数 名  : tup_conf_video_pause
	功能描述  : 暂停自己或别人的视频。
				如果暂停自己的视频，则暂停指定视频设备的采集功能；
				如果暂停其它用户的视频，则不接收该用户指定视频设备的视频数据
	输入参数  : handle: 会议句柄
				userid: 用户ID
				deviceid: 暂停视频的设备ID
				bwizard: TRUE：代表向导时的暂停；FALSE代表非向导时的暂停
				例：在会议中视频时，当需要弹出新窗口调整视频设置时，会议中的视频需要调用该接口先暂停，bwizard设为TRUE
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_VIDEO_ON_SWITCH
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_pause(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_BOOL bwizard);
	
	/*****************************************************************************
	函 数 名  : tup_conf_video_resume
	功能描述  : 取消暂停自己或别人的视频
	输入参数  : handle: 会议句柄
				userid: 用户ID
				deviceid: 视频的设备ID
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_VIDEO_ON_SWITCH
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_resume(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT32 deviceid);					

	/*****************************************************************************
	函 数 名  : tup_conf_video_closeall
	功能描述  : 关闭自己的所有视频
	输入参数  : handle: 会议句柄
				userid：用户ID
				deviceid：视频的设备ID
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : COMPT_MSG_VIDEO_ON_SWITCH
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_closeall(CONF_HANDLE handle);
	
	/*****************************************************************************
	函 数 名  : tup_conf_video_setcapture_rotate
	功能描述  : 设置视频旋转的角度（只适用于移动版本）
	输入参数  : handle: 会议句柄
				deviceid: 设备ID
				rotate: 设备旋转的角度
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_set_capture_rotate(CONF_HANDLE handle, TUP_UINT32 deviceid, TUP_INT32 nRotate);	
	
	/*****************************************************************************
	函 数 名  : tup_conf_video_snapshot
	功能描述  : 视频拍照功能。在设备打开状态时使用拍照功能，如果分辨率参数不一致
				（打开视频的分辨率与拍照的分辨率不同），设备会有一个重启的过程
	输入参数  : handle: 会议句柄
				deviceid: 设备ID
				filename: 图片保存的文件路径
				vparam: 拍照参数结构体
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_snapshot(CONF_HANDLE handle, TUP_UINT32 deviceid, const TUP_CHAR* filename, TC_VIDEO_PARAM* vparam); 

	
	/*****************************************************************************
	函 数 名  : tup_conf_video_getdevicestatus
	功能描述  : 允许查看某一设备的当前状态。(打开，关闭，暂停)
	输入参数  : handle: 会议句柄
				userid: 用户ID
				deviceid: 设备ID
	输出参数  : ret_devicetatus: 某一会议某一用户的设备状态，参考VIDEO_OPERATOR_CLSOE枚举值
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_get_devicestatus(CONF_HANDLE handle,TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_UINT32* ret_devicetatus);
	
	/*****************************************************************************
	函 数 名  : tup_conf_video_getdevicebitrate
	功能描述  : 获取视频码率
	输入参数  : handle: 会议句柄
				userid: 用户ID
				deviceid: 设备ID
	输出参数  : vparam: 视频参数结构体
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_get_devicebitrate(CONF_HANDLE handle,TUP_UINT32 userid, TUP_UINT32 deviceid, TC_VIDEO_PARAM* vparam);

	
	/*****************************************************************************
	函 数 名  : tup_conf_video_show_deviceproperty
	功能描述  : 显示设备属性对话框
	输入参数  : handle: 会议句柄
				userid: 用户ID
				deviceid: 设备ID
	输出参数  : parent_hwnd: 模态框(父窗口)句柄
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_show_deviceproperty(CONF_HANDLE handle, TUP_UINT32 userid, TUP_UINT32 deviceid, TUP_VOID* parent_hwnd);
	
	
	/*****************************************************************************
	函 数 名  : tup_conf_video_preview_start
	功能描述  : 启用视频向导，查看自己的某一设备是否能在某一分辨率下正常工作
	输入参数  : deviceid: 设备ID
				pwnd: 需要显示的窗口句柄
				pvparam: 指向视频设备能力结构体的指针
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_preview_start( TUP_UINT32 deviceid,TUP_VOID* pwnd,TC_VIDEO_PARAM* pvparam);
	
	/*****************************************************************************
	函 数 名  : tup_conf_video_preview_stop
	功能描述  : 关闭视频向导
	输入参数  : deviceid: 设备ID				
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_preview_stop( TUP_UINT32 deviceid);
	
	/*****************************************************************************
	函 数 名  : tup_conf_video_preview_setparam
	功能描述  : 设置视频向导的参数
	输入参数  : deviceid: 设备ID
				pvparam: 指向视频设备能力结构体的指针
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_preview_setparam( TUP_UINT32 deviceid, TC_VIDEO_PARAM* pvparam);	

	/*****************************************************************************
	函 数 名  : tup_conf_video_wizstart_runcapture
	功能描述  : 打开在向导中一直运行的Capture
	输入参数  : deviceid: 设备ID
				pvparam: 指向视频设备能力结构体的指针
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_wizstart_runcapture( TUP_UINT32 deviceid, TC_VIDEO_PARAM* pvparam);	

	/*****************************************************************************
	函 数 名  : tup_conf_video_wizclose_runcapture
	功能描述  : 关闭在向导中一直运行的Capture
	输入参数  : deviceid: 设备ID
				
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_wizend_runcapture( TUP_UINT32 deviceid);	

	/*****************************************************************************
	函 数 名  : tup_conf_video_always_runcapture
	功能描述  : 使用一直运行的capture时，必须把wiz传给会议
	输入参数  : 
				
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_video_always_runcapture(CONF_HANDLE handle);	
	
	/*************************文档白板高级接口*************************/
	
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_import
	功能描述  : 将一个保存的白板文件导入到指定的正在共享的白板中，被导入的白板文件所有页面插入到正在共享的白板后面
	输入参数  : handle: 会议句柄
				docid: 文档ID
				filename: 被导入的白板文件全路径（utf8编码字符串）
	输出参数  : 无
	返 回 值  : TC_OK：成功
				TC_FAILURE：会议未创建
				TC_NULL_POINT：参数错误，pszFileName为NULL
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_DS_ERROR_DOC_NOTEXIST：被导入到的文档无效
				TC_DS_ERROR_NOT_VALID_CWP：被导入的文件不是有效的保存的白板文件
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_WB_ON_PAGE_NEW
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_import(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, const TUP_CHAR* filename);
	

	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_load
	功能描述  : 加载一个被保存为私有格式的文档，该接口与tup_conf_ds_open接口打开私
				有格式文档时有相同的功能，但打开文档共享保存的文件时，文档背景不能
				被与会者看到
	输入参数  : handle: 会议句柄
				filename: 要打开的文档的全路径（utf8格式字符串）
	输出参数  : ret_docid: 加载文档成功后通过此参数返回文档的ID，若为NULL则不返回
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；参数错误
	回调消息  : COMPT_MSG_WB_ON_CURRENT_PAGE_IND
				COMPT_MSG_WB_ON_DOC_NEW
				COMPT_MSG_WB_ON_PAGE_NEW
				COMPT_MSG_WB_ON_DRAW_DATA_NOTIFY

	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_load(CONF_HANDLE handle,COMPONENT_IID ciid, const TUP_CHAR* filename, TUP_UINT32* ret_docid);
	
	/*****************************************************************************
	函 数 名  : tup_conf_wb_copy_page
	功能描述  : 复制指定的白板页面，被复制的页面被作为当前指定白板的最后一页，所有与会者都会收到新页面的通知。
	输入参数  : handle: 会议句柄
				docid: 文档ID
				pageid: 页面ID
	输出参数  : new_pageid: 复制成功后返回的新的页面的ID，如果该参数为NULL则不返回
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建
				TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
				TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
				TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
				TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
				TC_ERROR：其它错误
	回调消息  : COMPT_MSG_WB_ON_PAGE_NEW
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_copy_page(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid, TUP_UINT32 pageid, TUP_UINT32* new_pageid);
	

	/*************************文档共享高级接口*************************/
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_lock_surfacebmp
	功能描述  : 锁定文档页面数据
	输入参数  : handle: 会议句柄
				
	输出参数  : width ： 页面宽度
				height: 页面高度
	返 回 值  : 返回文档页面内存指针
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_VOID*  tup_conf_ds_lock_surfacebmp(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32* width, TUP_UINT32* height);
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_unlock_surfacebmp
	功能描述  : 解锁文档页面数据
	输入参数  : handle: 会议句柄				
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_ds_unlock_surfacebmp(CONF_HANDLE handle,COMPONENT_IID ciid);
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_set_surface_outputformat
	功能描述  : 设置输出的渲染图像的格式
	输入参数  : handle: 会议句柄
				format: 要设置的输出格式，Windows平台默认值为SUR_OUTPUT_HDC
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_ds_set_surface_outputformat(CONF_HANDLE handle,COMPONENT_IID ciid,  SurfaceOutputFormat format);
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_get_doc_count
	功能描述  : 获取当前正在共享的文档数量
	输入参数  : handle: 会议句柄				
	输出参数  : count: 用于返回文档数量，如果为NULL则返回错误
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_doc_count(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32* count);
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_get_docid_byindex
	功能描述  : 通过文档的索引获取文档的ID
	输入参数  : handle: 会议句柄
				index: 文档索引，如果小于0或大于等于文档数量，则*id返回0
	输出参数  : docid: 用于返回文档的ID，如果为NULL则返回错误，如果查询的文档不存在，则*id为0，否则为非0
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；参数错误
	回调消息  : 无				
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_docid_byindex(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_INT32 index, TUP_UINT32* docid);	
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_get_docindex_byid
	功能描述  : 通过文档ID获取该文档在文档列表中的索引
	输入参数  : handle: 会议句柄
				docid: 文档的ID
	输出参数  : index: 用于返回文档的索引，如果为NULL则返回错误，如果查询的文档不存在，*index为-1，否则为大于等于0的值
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；参数错误
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_docindex_byid(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_INT* index);	
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_get_page_count
	功能描述  : 获取指定文档的页数
	输入参数  : handle: 会议句柄
				docid:文档的ID
	输出参数  : count: 用于返回页数，如果为NULL则返回错误，如果查询的文档不存在，*count为-1，否则为大于等于0的值
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；参数错误
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_page_count(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32* count);
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_get_pageno_byid
	功能描述  : 通过页面ID获取页码
	输入参数  : handle: 会议句柄
				docid: 白板文档的ID
				pageid: 页面ID
	输出参数  : pageno: 用于返回页码，如果为NULL，则返回错误，如果查询的页面id不存在，*pageNo为-1，否则为大于等于0的值
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；参数错误
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_pageno_byid(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid, TUP_INT* pageno);
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_get_pageid_byno
	功能描述  : 通过页码返回页面ID
	输入参数  : handle: 会议句柄
				docid: 文档的ID
				pageno: 页码
	输出参数  : pageid: 用于返回页面ID，如果为NULL则返回错误，如果查询的页面不存在，*id为0，否则为非0值				
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；参数错误
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_pageid_byno(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_INT32 pageno, TUP_UINT32* pageid);
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_get_pageinfo
	功能描述  : 获取指定页面的信息
	输入参数  : handle: 会议句柄
				docid: 文档的ID
				pageid: 页面ID				
	输出参数  : pageinfo: 通过该参数返回指定页面的信息
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；参数错误
				TC_DS_ERROR_DOC_NOTEXIST：文档不存在
				TC_DS_ERROR_PAGE_NOTEXIST：页面不存在
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_pageinfo(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid, DsPageInfo* pageinfo);
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_get_docinfo
	功能描述  : 获取指定文档的信息
	输入参数  : handle: 会议句柄
				docid: 文档ID
	输出参数  : pdocinfo: 通过该参数返回指定文档的信息
	返 回 值  : TC_OK：成功
				TC_NULL_POINT：会议未创建；参数错误
				TC_DS_ERROR_DOC_NOTEXIST：文档不存在
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_get_docinfo(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, DsDocInfo* pdocinfo);
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_get_thumbnail
	功能描述  : 获取指定文档指定页面的缩略图
	输入参数  : handle: 会议句柄
				docid: 共享文档的ID
				pageid: 页面ID
				width: 要获取的缩略图的宽，TWIPS单位
				height: 要获取的缩略图的高，TWIPS单位
	输出参数  : 无
	返 回 值  : NULL：获取缩略图失败
				非NULL：缩略图数据
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_VOID*  tup_conf_ds_get_thumbnail(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid, TUP_INT32 width, TUP_INT32 height);
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_release_thumbnail
	功能描述  : 释放指定文档指定页面的缩略图
	输入参数  : handle: 会议句柄
				docid: 共享文档的ID
				pageid: 页面ID
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_ds_release_thumbnail(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid);
	
	/*****************************************************************************
	函 数 名  : tup_conf_ds_save
	功能描述  : 保存一个共享文档到本地文件，将文档保存成私有格式，保存文档的后缀名不限，由上层应用决定
	输入参数  : handle: 会议句柄
	docid: 要保存的共享文档的ID
	filename: 保存文档的全路径(utf8编码字符串)
	输出参数  : 无
	返 回 值  : TC_OK：成功
	TC_NULL_POINT：会议未创建；参数错误
	TC_DS_ERROR_DOC_NO_INIT：文档共享模块未被初始化
	TC_DS_ERROR_DOC_NO_SINK：未设置回调对象
	TC_DS_ERROR_DOC_NO_SESSION_JOIN：文档共享会话未加入
	TC_DS_ERROR_DOC_USER_OFFLINE：用户掉线
	TC_DS_ERROR_DOC_NOTEXIST：文档不存在
	TC_ERROR：其它错误
	回调消息  : 无
	*****************************************************************************/  
	TUP_API TUP_RESULT  tup_conf_ds_save(CONF_HANDLE handle,COMPONENT_IID ciid, TUP_UINT32 docid, const char* filename);		

	/*****************************************************************************
	函 数 名  : tup_conf_ds_saveas_picture
	功能描述  : 文档的单页内容保存成JPEG图片
	输入参数  : handle: 会议句柄
				docid:  文档ID
				pageid: 页面ID
				filename: 保存的文件名（完整路径）
	输出参数  : 无
	返 回 值  : 返回TC_OK表示成功，其它表示失败
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_RESULT  tup_conf_ds_saveas_picture(CONF_HANDLE handle,COMPONENT_IID ciid,  TUP_UINT32 docid, TUP_UINT32 pageid, const TUP_CHAR* filename);

	/*****************************************************************************
	函 数 名  : tup_conf_cache_delete
	功能描述  : 删除文档共享cache文件(只适用于iOS)
	输入参数  : 无
	输出参数  : 无
	返 回 值  : 无
	回调消息  : 无
	*****************************************************************************/	
	TUP_API TUP_VOID  tup_conf_cache_delete();

#ifdef __cplusplus
};


#endif

#endif