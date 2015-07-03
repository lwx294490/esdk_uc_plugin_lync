#ifndef _TUP_IM_BASEAPI_H_
#define _TUP_IM_BASEAPI_H_

#include "tup_im_basedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/**
 * \brief 初始化im库
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_init();

/**
 * \brief 卸载im库
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_uninit();

/**
 * \brief 设置服务器地址
 * \param[in]  ip 服务器地址
 * \param[in]  port 服务器端口
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_setserveraddress(const TUP_CHAR* ip, TUP_UINT16 port);

/**
 * \brief 发送心跳消息
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_sendheartbeat();

/**
 * \brief 登录（同步接口）
 * \param[in]  arg 登录请求
 * \param[out] ack 登录结果
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_login(const IM_S_LOGIN_ARG* arg,  IM_S_LOGIN_ACK* ack);

/**
 * \brief 退出（异步接口）
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_logout();

/**
 * \brief 注册回调（同步接口）
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_register_callback(TUP_IM_FN_CALLBACK_PTR callback);

/**
* \brief 通知IM输入输入状态（同步接口）
* \param[in]  arg 请求
* \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
*/
TUP_API TUP_RESULT tup_im_notifyiminputting(const IM_S_CHAT_STATUS_ARG* arg);

/**
 * \brief 获取联系人列表（同步接口）
 * \param[in]  arg 请求
 * \param[out] ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_getcontactlist(const IM_S_GETCONTACTLIST_ARG* arg, IM_S_GETCONTACTLIST_ACK* ack);

/**
* \brief 获取业务配置数据请求（同步接口）
* \param[in]  arg 请求
* \param[out] ack 响应
* \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
*/
TUP_API TUP_RESULT tup_im_getserviceprofile(const IM_S_GETSERVICEPROFILEARG* arg,IM_S_SERVICEPROFILEACK* ack);

/**
* \brief 获取用户信息请求（精确查询）
* \note 帐号和staffid以帐号优先
* \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
*/
TUP_API TUP_RESULT tup_im_getuserinfo(const IM_S_GETUSERINFOARG* arg,IM_S_USERINFO* ack);

/**
 * \brief 添加好友和联系人分组 （同步接口）
 * \param[in]  arg 请求
 * \param[out] ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_addusergroup(const IM_S_ADDUSERGROUP_ARG* arg, IM_S_ADDUSERGROUP_ACK* ack);

/**
 * \brief 修改好友和联系人分组 （同步接口）
 * \param[in]  arg 请求
 * \param[out] result 操作结果
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_modusergroup(const IM_S_MODUSERGROUP_ARG* arg, TUP_BOOL* result);

/**
 * \brief 删除好友和联系人分组 （同步接口）
 * \param[in]  id 分组ID
 * \param[out] result 操作结果
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_delusergroup(TUP_INT64 id, TUP_BOOL* result);

/**
 * \brief 添加好友，不需要对方响应 （同步接口）
 * \param[in]  arg 请求
 * \param[out] ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_addfriend(const IM_S_ADDFRIEND_ARG* arg,  IM_S_ADDFRIEND_ACK* ack);

/**
 * \brief 删除好友或者联系人（同步接口）
 * \param[in]  arg 请求
 * \param[out] result 操作结果
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_delfriendorcontact(const IM_S_DELCONTACT_ARG* arg,  TUP_BOOL* result);

/**
 * \brief 添加联系人 （同步接口）
 * \param[in]  arg 请求
 * \param[out] ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_addcontact(const IM_S_ADDCONTACT_ARG* arg,  IM_S_ADDCONTACT_ACK* ack);

/**
 * \brief 修改联系人 （同步接口）
 * \param[in]  arg 请求
 * \param[out] result 操作结果
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_modcontact(const IM_S_MODCONTACT_ARG* arg,  TUP_BOOL* result);

/**
 * \brief 移动联系人/好友分组 （同步接口）
 * \param[in]  arg 请求
 * \param[out] result 操作结果
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_movecontactgroup(const IM_S_MODCONTACTGROUP_ARG* arg,  TUP_BOOL* result);


/**
 * \brief 探测用户状态 （异步接口，如果用户在线，则会产生IM_E_EVENT_USERSTATUS_NOTIFY事件通知结果，如果用户离线则无事件产生。）
 * \param[in]  arg 帐号列表 arg->data TUP_CHAR[]
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_detectuserstatus(const TUP_S_LIST* arg);

/**
 * \brief 订阅非好友用户状态 （异步接口）
 * \param[in]  arg 帐号列表 arg->data TUP_CHAR[]
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_subscribeuserstatus(const TUP_S_LIST* arg);

/**
 * \brief 取消订阅非好友用户状态 （异步接口）
 * \param[in]  arg 帐号列表  arg->data TUP_CHAR[]
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_unsubscribeuserstatus(const TUP_S_LIST* arg);


/**
 * \brief 发送im消息 （异步接口）
 * \param[in]  arg 请求消息
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_sendim(const IM_S_SENDIM_ARG* arg);

/**
 * \brief 已读消息设置 （同步接口）
 * \param[in]  arg 请求消息
 * \parm[out]  ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_setmessageread(IM_S_SETMESSAGEREAD_ARG* arg);

/**
 * \brief 获取漫游消息 （同步接口）
 * \param[in]  arg 请求消息
 * \parm[out]  ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_queryHistoryMessage(const IM_S_QUERYHISTORYMESSAGE_ARG* arg, IM_S_QUERYHISTORYMESSAGE_ACK* ack);

/**
 * \brief 获取部门列表 （同步接口）
 * \param[in]  deptid 部门ID，获取一级部门时传-1
 * \param[out] ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_getdepts(TUP_INT64 deptID,  IM_S_GETDEPTS_ACK* ack);

/**
 * \brief 查询企业通讯录 （同步接口）
 * \param[in]  arg 请求
 * \param[out] ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_queryentaddressbook(const IM_S_QUERY_ENTADDRESSBOOK_ARG* arg, IM_S_QUERY_ENTADDRESSBOOK_ACK* ack);

/**
 * \brief 查询用户信息 （同步接口）
 * \param[in]  arg 请求
 * \param[out] ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_queryuserinfo(const IM_S_QUERY_USERINFO_ARG* arg, IM_S_QUERY_USERINFO_ACK* ack);

/**
 * \brief 添加固定群 （同步接口）
 * \param[in]  arg 请求
 * \param[out] ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_addfixedgroup(const IM_S_IMGROUP_OP_ARG* arg, IM_S_ADDIMGROUP_ACK* ack);

/**
 * \brief 修改固定群 （同步接口）
 * \param[in]  arg 请求
 * \param[out] ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_modfixedgroup(const IM_S_IMGROUP_OP_ARG* arg, IM_S_MODFIXEDGROUP_ACK* ack);

/**
 * \brief 删除固定群 （同步接口）
 * \param[in]  id 群ID
 * \param[out] result 操作结果
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_delfixedgroup(const TUP_CHAR* id,  TUP_BOOL* result);

/**
 * \brief 固定群添加成员 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_addfixedgroupmember(const IM_S_ADDIMGROUPMEMBER_ARG* arg);

/**
 * \brief 固定群删除成员 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_delfixedgroupmember(const IM_S_DELIMGROUPMEMBER_ARG* arg);

/**
 * \brief 管理员审批用户申请加入固定群申请 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_confirmfixedgroupapply(const IM_S_CONFIRM_JOINFIXEDGROUP_ARG* arg);

/**
 * \brief 用户审批管理员邀请加入固定群 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_confirmfixedgroupinvite(const IM_S_CONFIRM_JOINFIXEDGROUP_ARG* arg);

/**
 * \brief 申请加入固定群 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_joinfixedgroup(const IM_S_JOINFIXEDGROUP_ARG* arg);

/**
 * \brief 退出加入固定群 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_leavefixedgroup(const TUP_CHAR* arg);

/**
 * \brief 转移固定群 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_transferfixedgroup(const IM_S_TRANSFERIMGROUP_ARG* arg);

/**
* \brief 获取群组详情 （同步接口）
* \param[in]  arg 请求群组ID
* \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
*/
TUP_API TUP_RESULT tup_im_getfixedgroupdetail(const TUP_CHAR* arg,IM_S_IMGROUPINFO* ack);

/**
* \brief 获取群组成员 （同步接口）
* \param[in]  arg 请求
* \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
*/
TUP_API TUP_RESULT tup_im_getfixedgroupmembers(const IM_S_REQUESTIMGROUPMEMBERS_ARG* arg,IM_S_GROUPUSERLIST* ack);

/**
* \brief 获取固定群列表请求 （同步接口）
* \param[in]  arg 请求
* \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
*/
TUP_API TUP_RESULT tup_im_getfixedgroups(const IM_S_GETIMGROUPLIST_ARG* arg,IM_S_GETIMGROUPLIST_ACK* ack);

/**
 * \brief 添加讨论组（同步接口）
 * \param[in]  arg 请求
 * \param[out] ack 响应
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_adddiscussiongroup(const IM_S_IMGROUP_OP_ARG* arg, IM_S_ADDIMGROUP_ACK* ack);

/**
 * \brief 修改讨论组 （同步接口）
 * \param[in]  arg 请求
 * \param[out] result 操作结果
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_moddiscussiongroup(const IM_S_IMGROUP_OP_ARG* arg,  TUP_BOOL* result);

/**
 * \brief 删除讨论组 （同步接口）
 * \param[in]  id 群ID
 * \param[out] result 操作结果
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_deldiscussiongroup(const TUP_CHAR* id,  TUP_BOOL* result);

/**
 * \brief 讨论组添加成员 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_adddiscussiongroupmember(const IM_S_ADDIMGROUPMEMBER_ARG* arg);

/**
 * \brief 讨论组删除成员 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_deldiscussiongroupmember(const IM_S_DELIMGROUPMEMBER_ARG* arg);

/**
 * \brief 讨论组添加成员 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_adddiscussiongroupphonemember(const IM_S_IMGROUPPHONEMEMBER_OP_ARG* arg);

/**
 * \brief 讨论组删除成员 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_deldiscussiongroupphonemember(const IM_S_IMGROUPPHONEMEMBER_OP_ARG* arg);

/**
 * \brief 退出加入讨论组 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_leavediscussiongroup(const TUP_CHAR* arg);

/**
 * \brief 转移讨论组 （异步接口）
 * \param[in]  arg 请求
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_transferdiscussiongroup(const IM_S_TRANSFERIMGROUP_ARG* arg);

/**
 * \brief 同步接口请求在等待中，退出客户端。在独立线程中通知客户端自己不要再等待接口返回消息 （异步接口）
 * \param[in] 无
 * \return 接口调用是否成功。返回TUP_SUCCESS 成功，否则失败
 */
TUP_API TUP_RESULT tup_im_setcancelsendingmessage();

TUP_API TUP_RESULT tup_im_setdispatchmessage(TUP_BOOL isDispatch);

// 个人设置相关
TUP_API TUP_RESULT tup_im_setselfdefineimage(const IM_S_IMAGEINFO* image);

TUP_API TUP_RESULT tup_im_setsystemimage(const TUP_CHAR* imageID);

TUP_API TUP_RESULT tup_im_setuserinfo(IM_S_USERINFO* destData);

TUP_API TUP_RESULT tup_im_getuserdefineimage(const IM_S_IMAGEREQARG* arg,IM_S_USERIMAGEINFO* ack);

TUP_API TUP_RESULT tup_im_publishstatus(const IM_S_STATUSARG* arg);

#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif //_TUP_IM_BASEAPI_H_