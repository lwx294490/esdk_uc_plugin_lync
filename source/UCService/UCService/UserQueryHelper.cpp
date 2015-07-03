#include "StdAfx.h"
#include "UserQueryHelper.h"


bool CUserQueryHelper::GetUserInfoFromList(const IM_S_QUERY_USERINFO_ACK& ack
										   , const TUP_INT8 acTelNum[]
											, IM_S_USERINFO& userInfo)const 
{
	bool bRet = false;
	TUP_S_LIST* pUserList = ack.userList;
	while(NULL != pUserList)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserList->data;
		if(NULL == pUser)
		{
			continue;
		}

		IM_S_USERINFO curUserInfo;
		memcpy(&curUserInfo, pUser, sizeof(IM_S_USERINFO));

		//accurate search
		if (strcmp(curUserInfo.bindNO, acTelNum) == 0)
		{
			userInfo = curUserInfo;
			bRet = true;
			break;
		}

		pUserList = pUserList->next;
	}

	return bRet;
}

bool CUserQueryHelper::GetTargetUserInfo(const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo)const
{
	IM_S_QUERY_USERINFO_ARG arg;
	IM_S_QUERY_USERINFO_ACK ack;
	strcpy_s(arg.key, IM_D_MAX_PHONE_LENGTH, acTelNum);
	arg.type = IM_E_IMUSERQUERYTYPE_BY_BINDNO;
	TUP_RESULT tRet = tup_im_queryuserinfo(&arg, &ack);
	if (TUP_SUCCESS != tRet)
	{
		return false;
	}

	IM_S_USERINFO userQueryAck;
	if(!GetUserInfoFromList(ack, acTelNum, userQueryAck))
	{
		return false;
	}

	userInfo = userQueryAck;
	return true;
}






