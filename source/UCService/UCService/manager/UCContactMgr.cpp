#include "StdAfx.h"
#include "Log.h"
#include "UCContactMgr.h"

UCContactMgr::UCContactMgr(void):m_iStaffSize(0)
{
	try
	{
		m_mapStaff.clear();
	}
	catch(...)
	{
	}
	
}

UCContactMgr::~UCContactMgr(void)
{
	try
	{
		m_iStaffSize = 0;
		m_mapStaff.clear();
	}
	catch(...)
	{
	}
}
void UCContactMgr::Init(void)
{
}
void UCContactMgr::Uninit(void)
{
}

int UCContactMgr::getContactByAccount(const std::string& _account, IM_S_USERINFO& _userInfo)
{
	IM_S_QUERY_USERINFO_ARG arg;
	IM_S_QUERY_USERINFO_ACK ack;
	ack.userList = NULL;
	strcpy_s(arg.key, IM_D_MAX_PHONE_LENGTH, _account.c_str());
	arg.type = IM_E_IMUSERQUERYTYPE_BY_ACCOUNT;
	TUP_RESULT tRet = tup_im_queryuserinfo(&arg, &ack);
	if (TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_im_queryuserinfo failed.");
		return UC_SDK_Failed;
	}

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
		if (strcmp(curUserInfo.account, _account.c_str()) == 0)
		{
			_userInfo = curUserInfo;
			bRet = true;
			break;
		}

		pUserList = pUserList->next;
	}

	if(!bRet)
	{
		ERROR_LOG("tup_im_queryuserinfo failed.No result.");
		return UC_SDK_Failed;
	}
	
	return UC_SDK_Success;
}


int UCContactMgr::getContactByNum(const std::string& _phone, IM_S_USERINFO& _userInfo,IM_E_IMUSERQUERYTYPE _type)
{
	IM_S_QUERY_USERINFO_ARG arg;
	IM_S_QUERY_USERINFO_ACK ack;
	strcpy_s(arg.key, IM_D_MAX_PHONE_LENGTH, _phone.c_str());
	arg.type = _type;
	TUP_RESULT tRet = tup_im_queryuserinfo(&arg, &ack);
	if (TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_im_queryuserinfo failed.");
		return UC_SDK_Failed;
	}

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
		if (strcmp(curUserInfo.bindNO, _phone.c_str()) == 0)
		{
			_userInfo = curUserInfo;
			bRet = true;
			break;
		}

		pUserList = pUserList->next;
	}

	if(!bRet)
	{
		ERROR_LOG("tup_im_queryuserinfo failed.No result.");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}

int UCContactMgr::getContactList(const std::string& _strSearchKey, int _fromIndex,int _toIndex, STContactList* _pContactList)
{
	DEBUG_TRACE("");

	if(NULL == _pContactList)
	{
		ERROR_LOG("_pContactList is NULL.");
		return UC_SDK_InvalidPara;
	}
	if(_fromIndex < 0)
	{
		ERROR_LOG("_fromIndex is invalid.");
		return UC_SDK_InvalidPara;
	}

	if(_toIndex < 0)
	{
		ERROR_LOG("_toIndex is invalid.");
		return UC_SDK_InvalidPara;
	}

	if(_toIndex < _fromIndex)
	{
		ERROR_LOG("_fromIndex is bigger than _toIndex.");
		return UC_SDK_InvalidPara;
	}

	int iQuerySize = _toIndex - _fromIndex + 1;
	INFO_LOG("iQuerySize is %d",iQuerySize);

	if(iQuerySize > SEARCH_MAXAMOUNT)
	{
		ERROR_LOG("QuerySize is invalid.");
		return UC_SDK_InvalidPara;
	}

	IM_S_QUERY_ENTADDRESSBOOK_ARG arg = {0};
	arg.deptID = -1;

	strcpy_s(arg.queryKey,IM_D_MAX_DESC_LENGTH,_strSearchKey.c_str());
	arg.offset = _fromIndex;
	arg.orderModel = IM_E_ADDRBOOKQUERY_ORDERMODEL_BY_ASC;
	arg.orderType = IM_E_ADDRBOOKQUERY_ORDERTYPE_BY_STAFFNO;
	arg.isNeedAmount = TUP_TRUE;
	arg.count = iQuerySize;
	
	IM_S_QUERY_ENTADDRESSBOOK_ACK entAck = {0} ;
	TUP_RESULT tRet = tup_im_queryentaddressbook(&arg,&entAck);
	if(TUP_SUCCESS != tRet || entAck.result == TUP_FALSE)
	{
		ERROR_LOG("tup_im_queryentaddressbook failed");
		return UC_SDK_NotFound;
	}

	m_mapStaff.clear();
	m_iStaffSize = entAck.recordAmount;
	INFO_LOG("m_iStaffSize is %d",m_iStaffSize);
	TUP_S_LIST* pUserItem = entAck.userList;
	int i = 0;
	while(NULL != pUserItem)
	{
		IM_S_USERINFO* pUser = (IM_S_USERINFO*)pUserItem->data;
		if(NULL == pUser)
		{
			break;
		}
		IM_S_USERINFO user;
		memcpy(&user,pUser,sizeof(IM_S_USERINFO));
		m_mapStaff[i++]=user;
		pUserItem = pUserItem->next;
	}
	SAFE_DELETE(pUserItem);

	if(_fromIndex>m_iStaffSize)
	{
		ERROR_LOG("_fromIndex is too large.");
		return UC_SDK_InvalidPara;
	}

	_pContactList->iTotal = m_iStaffSize;
	int iRealSize = 0;
	if(m_iStaffSize<_toIndex)
	{
		iRealSize = m_iStaffSize;
	}
	else
	{
		iRealSize = _toIndex+1;
	}

	const int legth = iRealSize-_fromIndex;
	INFO_LOG("legth is %d",legth);
	const int staffSize = m_mapStaff.size();
	INFO_LOG("staffSize is %d",staffSize);
	for(int i=0;(i<legth) &&(i<staffSize) ;i++)
	{
		IM_S_USERINFO cont = m_mapStaff[i];

		memset(_pContactList->stContact[i].address_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].address_,STRING_LENGTH,cont.address,STRING_LENGTH-1);

		memset(_pContactList->stContact[i].avtool_,0,STRING_LENGTH);
		memset(_pContactList->stContact[i].corpName_,0,STRING_LENGTH);
		//std::string unicodeCorpName = eSDKTool::utf82unicode(cont.);
		//memcpy_s(_pContactList->stContact[i].corpName_,unicodeCorpName.c_str(),unicodeCorpName.size());

		memset(_pContactList->stContact[i].deptName_,0,STRING_LENGTH);
		//std::string unicodeDeptName = eSDKTool::utf82unicode(cont.deptNameCn);
		//memcpy_s(_pContactList->stContact[i].deptName_,STRING_LENGTH,cont.deptNameCn,IM_D_MAX_NAME_LENGTH);

		memset(_pContactList->stContact[i].desc_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].desc_,STRING_LENGTH,cont.desc,IM_D_MAX_DESC_LENGTH);

		memset(_pContactList->stContact[i].device_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].device_,cont..c_str(),cont.device_.size());

		memset(_pContactList->stContact[i].duty_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].duty_,STRING_LENGTH,cont.title,IM_D_MAX_DESC_LENGTH);

		memset(_pContactList->stContact[i].email_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].email_,STRING_LENGTH,cont.email,STRING_LENGTH-1);

		memset(_pContactList->stContact[i].fax_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].fax_,STRING_LENGTH,cont.fax,IM_D_MAX_PHONE_LENGTH);

		memset(_pContactList->stContact[i].fullUri_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].fullUri_,cont..c_str(),cont.fullUri_.size());

		memset(_pContactList->stContact[i].gender_,0,STRING_LENGTH);
		if(cont.gender == IM_E_GENDER_MALE)
		{
			memcpy_s(_pContactList->stContact[i].gender_,STRING_LENGTH,"male",strlen("male"));
		}
		else if(cont.gender == IM_E_GENDER_FEMAIL)
		{
			memcpy_s(_pContactList->stContact[i].gender_,STRING_LENGTH,"female",strlen("female"));
		}
		

		memset(_pContactList->stContact[i].homePhone_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].homePhone_,STRING_LENGTH,cont.homePhone,STRING_LENGTH-1);

		memset(_pContactList->stContact[i].id_,0,STRING_LENGTH);
		sprintf_s(_pContactList->stContact[i].id_,"%d",cont.staffID);

		memset(_pContactList->stContact[i].imageID_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].imageID_,STRING_LENGTH,cont.imageID,STRING_LENGTH-1);

		memset(_pContactList->stContact[i].ipphone1_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].ipphone1_,STRING_LENGTH,cont.ipPhone,STRING_LENGTH-1);
		memset(_pContactList->stContact[i].ipphone2_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].ipphone2_,cont.ipphone2_.c_str(),cont.ipphone2_.size());
		memset(_pContactList->stContact[i].location_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].location_,cont..c_str(),cont.location_.size());

		memset(_pContactList->stContact[i].mobile_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].mobile_,STRING_LENGTH,cont.mobile,STRING_LENGTH-1);

		memset(_pContactList->stContact[i].name_,0,STRING_LENGTH);
		std::string unicodename = eSDKTool::utf8str2unicodestr(cont.name);
		memcpy_s(_pContactList->stContact[i].name_,STRING_LENGTH,unicodename.c_str(),STRING_LENGTH-1);

		memset(_pContactList->stContact[i].nickName_,0,STRING_LENGTH);
		//std::string unicodenickname = eSDKTool::utf82unicode(cont.nativeName);
		memcpy_s(_pContactList->stContact[i].nickName_,STRING_LENGTH,cont.nativeName,STRING_LENGTH-1);

		memset(_pContactList->stContact[i].officePhone2_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].officePhone2_,cont.officePhone.c_str(),cont.officePhone.size());

		memset(_pContactList->stContact[i].officePhone_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].officePhone_,STRING_LENGTH,cont.officePhone,STRING_LENGTH-1);
		memset(_pContactList->stContact[i].otherPhone2_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].otherPhone2_,cont.otherPhone2_.c_str(),cont.otherPhone2_.size());
		memset(_pContactList->stContact[i].otherPhone_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].otherPhone_,STRING_LENGTH,cont.otherPhone,STRING_LENGTH-1);

		memset(_pContactList->stContact[i].position_,0,STRING_LENGTH);
		//std::string unicodePostion = eSDKTool::utf82unicode(cont.);
		//memcpy_s(_pContactList->stContact[i].position_,unicodePostion.c_str(),unicodePostion.size());
		memset(_pContactList->stContact[i].qpinyin_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].qpinyin_,cont.qpinyin_.c_str(),cont.qpinyin_.size());

		memset(_pContactList->stContact[i].signature_,0,STRING_LENGTH);
		//std::string unicodeSignture = eSDKTool::utf82unicode(cont.signature);
		memcpy_s(_pContactList->stContact[i].signature_,STRING_LENGTH,cont.signature,STRING_LENGTH-1);
		memset(_pContactList->stContact[i].spinyin_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].spinyin_,cont.spinyin_.c_str(),cont.spinyin_.size());
		memset(_pContactList->stContact[i].staffNo_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].staffNo_,STRING_LENGTH,cont.staffNO,STRING_LENGTH-1);

		memset(_pContactList->stContact[i].terminalType_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].terminalType_,cont.terminalType_.c_str(),cont.terminalType_.size());
		memset(_pContactList->stContact[i].tzone_,0,STRING_LENGTH);
		//memcpy_s(_pContactList->stContact[i].tzone_,cont.tzone_.c_str(),cont.tzone_.size());

		memset(_pContactList->stContact[i].ucAcc_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].ucAcc_,STRING_LENGTH,cont.account,strlen(cont.account));

		memset(_pContactList->stContact[i].uri_,0,STRING_LENGTH);
		std::string unicoduri = eSDKTool::utf8str2unicodestr(cont.account);
		memcpy_s(_pContactList->stContact[i].uri_,STRING_LENGTH,unicoduri.c_str(),unicoduri.size());

		memset(_pContactList->stContact[i].webSite_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].webSite_,STRING_LENGTH,cont.webSite,STRING_LENGTH-1);

		memset(_pContactList->stContact[i].zip_,0,STRING_LENGTH);
		memcpy_s(_pContactList->stContact[i].zip_,STRING_LENGTH,cont.postalcode,STRING_LENGTH-1);
	}

	INFO_LOG("TotalSize=%d,",_pContactList->iTotal);  

	return UC_SDK_Success;
}
