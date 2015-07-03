#ifndef _TUP_IM_BASEAPI_H_
#define _TUP_IM_BASEAPI_H_

#include "tup_im_basedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/**
 * \brief ��ʼ��im��
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_init();

/**
 * \brief ж��im��
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_uninit();

/**
 * \brief ���÷�������ַ
 * \param[in]  ip ��������ַ
 * \param[in]  port �������˿�
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_setserveraddress(const TUP_CHAR* ip, TUP_UINT16 port);

/**
 * \brief ����������Ϣ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_sendheartbeat();

/**
 * \brief ��¼��ͬ���ӿڣ�
 * \param[in]  arg ��¼����
 * \param[out] ack ��¼���
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_login(const IM_S_LOGIN_ARG* arg,  IM_S_LOGIN_ACK* ack);

/**
 * \brief �˳����첽�ӿڣ�
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_logout();

/**
 * \brief ע��ص���ͬ���ӿڣ�
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_register_callback(TUP_IM_FN_CALLBACK_PTR callback);

/**
* \brief ֪ͨIM��������״̬��ͬ���ӿڣ�
* \param[in]  arg ����
* \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
*/
TUP_API TUP_RESULT tup_im_notifyiminputting(const IM_S_CHAT_STATUS_ARG* arg);

/**
 * \brief ��ȡ��ϵ���б�ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_getcontactlist(const IM_S_GETCONTACTLIST_ARG* arg, IM_S_GETCONTACTLIST_ACK* ack);

/**
* \brief ��ȡҵ��������������ͬ���ӿڣ�
* \param[in]  arg ����
* \param[out] ack ��Ӧ
* \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
*/
TUP_API TUP_RESULT tup_im_getserviceprofile(const IM_S_GETSERVICEPROFILEARG* arg,IM_S_SERVICEPROFILEACK* ack);

/**
* \brief ��ȡ�û���Ϣ���󣨾�ȷ��ѯ��
* \note �ʺź�staffid���ʺ�����
* \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
*/
TUP_API TUP_RESULT tup_im_getuserinfo(const IM_S_GETUSERINFOARG* arg,IM_S_USERINFO* ack);

/**
 * \brief ��Ӻ��Ѻ���ϵ�˷��� ��ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_addusergroup(const IM_S_ADDUSERGROUP_ARG* arg, IM_S_ADDUSERGROUP_ACK* ack);

/**
 * \brief �޸ĺ��Ѻ���ϵ�˷��� ��ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] result �������
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_modusergroup(const IM_S_MODUSERGROUP_ARG* arg, TUP_BOOL* result);

/**
 * \brief ɾ�����Ѻ���ϵ�˷��� ��ͬ���ӿڣ�
 * \param[in]  id ����ID
 * \param[out] result �������
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_delusergroup(TUP_INT64 id, TUP_BOOL* result);

/**
 * \brief ��Ӻ��ѣ�����Ҫ�Է���Ӧ ��ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_addfriend(const IM_S_ADDFRIEND_ARG* arg,  IM_S_ADDFRIEND_ACK* ack);

/**
 * \brief ɾ�����ѻ�����ϵ�ˣ�ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] result �������
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_delfriendorcontact(const IM_S_DELCONTACT_ARG* arg,  TUP_BOOL* result);

/**
 * \brief �����ϵ�� ��ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_addcontact(const IM_S_ADDCONTACT_ARG* arg,  IM_S_ADDCONTACT_ACK* ack);

/**
 * \brief �޸���ϵ�� ��ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] result �������
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_modcontact(const IM_S_MODCONTACT_ARG* arg,  TUP_BOOL* result);

/**
 * \brief �ƶ���ϵ��/���ѷ��� ��ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] result �������
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_movecontactgroup(const IM_S_MODCONTACTGROUP_ARG* arg,  TUP_BOOL* result);


/**
 * \brief ̽���û�״̬ ���첽�ӿڣ�����û����ߣ�������IM_E_EVENT_USERSTATUS_NOTIFY�¼�֪ͨ���������û����������¼���������
 * \param[in]  arg �ʺ��б� arg->data TUP_CHAR[]
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_detectuserstatus(const TUP_S_LIST* arg);

/**
 * \brief ���ķǺ����û�״̬ ���첽�ӿڣ�
 * \param[in]  arg �ʺ��б� arg->data TUP_CHAR[]
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_subscribeuserstatus(const TUP_S_LIST* arg);

/**
 * \brief ȡ�����ķǺ����û�״̬ ���첽�ӿڣ�
 * \param[in]  arg �ʺ��б�  arg->data TUP_CHAR[]
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_unsubscribeuserstatus(const TUP_S_LIST* arg);


/**
 * \brief ����im��Ϣ ���첽�ӿڣ�
 * \param[in]  arg ������Ϣ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_sendim(const IM_S_SENDIM_ARG* arg);

/**
 * \brief �Ѷ���Ϣ���� ��ͬ���ӿڣ�
 * \param[in]  arg ������Ϣ
 * \parm[out]  ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_setmessageread(IM_S_SETMESSAGEREAD_ARG* arg);

/**
 * \brief ��ȡ������Ϣ ��ͬ���ӿڣ�
 * \param[in]  arg ������Ϣ
 * \parm[out]  ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_queryHistoryMessage(const IM_S_QUERYHISTORYMESSAGE_ARG* arg, IM_S_QUERYHISTORYMESSAGE_ACK* ack);

/**
 * \brief ��ȡ�����б� ��ͬ���ӿڣ�
 * \param[in]  deptid ����ID����ȡһ������ʱ��-1
 * \param[out] ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_getdepts(TUP_INT64 deptID,  IM_S_GETDEPTS_ACK* ack);

/**
 * \brief ��ѯ��ҵͨѶ¼ ��ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_queryentaddressbook(const IM_S_QUERY_ENTADDRESSBOOK_ARG* arg, IM_S_QUERY_ENTADDRESSBOOK_ACK* ack);

/**
 * \brief ��ѯ�û���Ϣ ��ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_queryuserinfo(const IM_S_QUERY_USERINFO_ARG* arg, IM_S_QUERY_USERINFO_ACK* ack);

/**
 * \brief ��ӹ̶�Ⱥ ��ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_addfixedgroup(const IM_S_IMGROUP_OP_ARG* arg, IM_S_ADDIMGROUP_ACK* ack);

/**
 * \brief �޸Ĺ̶�Ⱥ ��ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_modfixedgroup(const IM_S_IMGROUP_OP_ARG* arg, IM_S_MODFIXEDGROUP_ACK* ack);

/**
 * \brief ɾ���̶�Ⱥ ��ͬ���ӿڣ�
 * \param[in]  id ȺID
 * \param[out] result �������
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_delfixedgroup(const TUP_CHAR* id,  TUP_BOOL* result);

/**
 * \brief �̶�Ⱥ��ӳ�Ա ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_addfixedgroupmember(const IM_S_ADDIMGROUPMEMBER_ARG* arg);

/**
 * \brief �̶�Ⱥɾ����Ա ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_delfixedgroupmember(const IM_S_DELIMGROUPMEMBER_ARG* arg);

/**
 * \brief ����Ա�����û��������̶�Ⱥ���� ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_confirmfixedgroupapply(const IM_S_CONFIRM_JOINFIXEDGROUP_ARG* arg);

/**
 * \brief �û���������Ա�������̶�Ⱥ ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_confirmfixedgroupinvite(const IM_S_CONFIRM_JOINFIXEDGROUP_ARG* arg);

/**
 * \brief �������̶�Ⱥ ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_joinfixedgroup(const IM_S_JOINFIXEDGROUP_ARG* arg);

/**
 * \brief �˳�����̶�Ⱥ ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_leavefixedgroup(const TUP_CHAR* arg);

/**
 * \brief ת�ƹ̶�Ⱥ ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_transferfixedgroup(const IM_S_TRANSFERIMGROUP_ARG* arg);

/**
* \brief ��ȡȺ������ ��ͬ���ӿڣ�
* \param[in]  arg ����Ⱥ��ID
* \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
*/
TUP_API TUP_RESULT tup_im_getfixedgroupdetail(const TUP_CHAR* arg,IM_S_IMGROUPINFO* ack);

/**
* \brief ��ȡȺ���Ա ��ͬ���ӿڣ�
* \param[in]  arg ����
* \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
*/
TUP_API TUP_RESULT tup_im_getfixedgroupmembers(const IM_S_REQUESTIMGROUPMEMBERS_ARG* arg,IM_S_GROUPUSERLIST* ack);

/**
* \brief ��ȡ�̶�Ⱥ�б����� ��ͬ���ӿڣ�
* \param[in]  arg ����
* \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
*/
TUP_API TUP_RESULT tup_im_getfixedgroups(const IM_S_GETIMGROUPLIST_ARG* arg,IM_S_GETIMGROUPLIST_ACK* ack);

/**
 * \brief ��������飨ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] ack ��Ӧ
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_adddiscussiongroup(const IM_S_IMGROUP_OP_ARG* arg, IM_S_ADDIMGROUP_ACK* ack);

/**
 * \brief �޸������� ��ͬ���ӿڣ�
 * \param[in]  arg ����
 * \param[out] result �������
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_moddiscussiongroup(const IM_S_IMGROUP_OP_ARG* arg,  TUP_BOOL* result);

/**
 * \brief ɾ�������� ��ͬ���ӿڣ�
 * \param[in]  id ȺID
 * \param[out] result �������
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_deldiscussiongroup(const TUP_CHAR* id,  TUP_BOOL* result);

/**
 * \brief ��������ӳ�Ա ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_adddiscussiongroupmember(const IM_S_ADDIMGROUPMEMBER_ARG* arg);

/**
 * \brief ������ɾ����Ա ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_deldiscussiongroupmember(const IM_S_DELIMGROUPMEMBER_ARG* arg);

/**
 * \brief ��������ӳ�Ա ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_adddiscussiongroupphonemember(const IM_S_IMGROUPPHONEMEMBER_OP_ARG* arg);

/**
 * \brief ������ɾ����Ա ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_deldiscussiongroupphonemember(const IM_S_IMGROUPPHONEMEMBER_OP_ARG* arg);

/**
 * \brief �˳����������� ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_leavediscussiongroup(const TUP_CHAR* arg);

/**
 * \brief ת�������� ���첽�ӿڣ�
 * \param[in]  arg ����
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_transferdiscussiongroup(const IM_S_TRANSFERIMGROUP_ARG* arg);

/**
 * \brief ͬ���ӿ������ڵȴ��У��˳��ͻ��ˡ��ڶ����߳���֪ͨ�ͻ����Լ���Ҫ�ٵȴ��ӿڷ�����Ϣ ���첽�ӿڣ�
 * \param[in] ��
 * \return �ӿڵ����Ƿ�ɹ�������TUP_SUCCESS �ɹ�������ʧ��
 */
TUP_API TUP_RESULT tup_im_setcancelsendingmessage();

TUP_API TUP_RESULT tup_im_setdispatchmessage(TUP_BOOL isDispatch);

// �����������
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