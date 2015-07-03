#include "stdafx.h"
#include "OldHistoryRecord.h"
#include "Log.h"

namespace ecs {
  namespace ecsdata {
    namespace history {

int OldHistoryAnalyze::QueryIMByPeer(const std::string& _dbName,ParentType::ResCtnType & _ctnObj)
{
	return QueryConvByType(_dbName,_ctnObj,SINGLE_RECORD_TYPE);
}

int OldHistoryAnalyze::QuerySMSByPeer(const std::string& _dbName,ParentType::ResCtnType & _ctnObj,bool _isArchive)
{
	return QueryConvByType(_dbName,_ctnObj,_isArchive ? ARCHIVE_SMS_RECORD_TYPE : SMS_RECORD_TYPE); 
}

int OldHistoryAnalyze::QueryCallByPeer(const std::string& _dbName,ParentType::ResCtnType & _ctnObj)
{
	return QueryConvByType(_dbName,_ctnObj,CALL_RECORD_TYPE);
}

int OldHistoryAnalyze::QueryGroupIMByID(const std::string& _dbName,ParentType::ResCtnType & _ctnObj,bool _isArchive)
{
	return QueryConvByType(_dbName, _ctnObj, _isArchive ? ARCHIVE_GROUP_RECORD_TYPE : GROUP_RECORD_TYPE);
}

int OldHistoryAnalyze::QueryAudioConfByID(const std::string& _dbName,ParentType::ResCtnType & _ctnObj)
{
	return QueryConvByType(_dbName,_ctnObj,CONF_RECORD_TYPE);
}


int OldHistoryAnalyze::QueryConvByType(const std::string& _dbName,ParentType::ResCtnType & _ctnObj,int _enumType)
{
	if(_dbName.empty())
	{
		return 0;
	}
	ParentType::ArgObjType argObj;
	OldHistoryAnalyze peersQuery(_dbName);
	peersQuery.BatchExecute(_enumType,argObj,_ctnObj);

	DEBUG_LOG("_dbName=%s,peersQuery.count=%d",_dbName.c_str(),peersQuery.count);
    return peersQuery.count;
}

void OldHistoryAnalyze::ComposeSQL(std::string & _sql)
{
	switch (type_)
	{
	case SINGLE_RECORD_TYPE:
		_sql = "SELECT ACCOUNT,COUNT(*),NAME FROM IMRECORDTAB GROUP BY ACCOUNT;";
		break;
	case SMS_RECORD_TYPE:
		_sql = "SELECT ACCOUNT,COUNT(*),NAME FROM SMRECORDTAB GROUP BY ACCOUNT;";
		break;
	case ARCHIVE_SMS_RECORD_TYPE:
		_sql = "SELECT ACCOUNT,COUNT(*),NAME FROM SMSRECORDTAB GROUP BY ACCOUNT;";
		break;
	case CALL_RECORD_TYPE:
		_sql = "SELECT ACCOUNT,COUNT(*),NAME,MOBILE FROM SIPRECORDTAB GROUP BY MOBILE;";
		break;
	case GROUP_RECORD_TYPE:
		_sql = "SELECT GROUPID,COUNT(*) FROM IMGROUPRECORDTAB GROUP BY GROUPID";
		break;
	case ARCHIVE_GROUP_RECORD_TYPE:
		_sql = "SELECT GROUPID,COUNT(*) FROM GROUPRECORDTAB GROUP BY GROUPID";
		break;
	case CONF_RECORD_TYPE:
		_sql = "SELECT ID,COUNT(*) FROM CONFRECORDTAB GROUP BY ID";
		break;
	default:
		break;
	}
}
void OldHistoryAnalyze::Bind(IDataManipulation * , const ParentType::ArgObjType & )
{
}
void OldHistoryAnalyze::Extract(IDataManipulation * _dm, ParentType::ResObjType & _resObj)
{
	int index = -1;

	switch (type_)
	{
	case SINGLE_RECORD_TYPE:
	case SMS_RECORD_TYPE:
	case ARCHIVE_SMS_RECORD_TYPE:
		_dm->GetValue(++index,_resObj.key_);
		_dm->GetValue(++index,_resObj.totalCount_);
		_dm->GetValue(++index,_resObj.name_);
		break;
	case CALL_RECORD_TYPE:
		_dm->GetValue(++index,_resObj.key_);
		_dm->GetValue(++index,_resObj.totalCount_);
		_dm->GetValue(++index,_resObj.name_);
		_dm->GetValue(++index,_resObj.mobile_);
		break;
	case GROUP_RECORD_TYPE:
	case ARCHIVE_GROUP_RECORD_TYPE:
		_dm->GetValue(++index,_resObj.key_);
		_dm->GetValue(++index,_resObj.totalCount_);
		break;
	case CONF_RECORD_TYPE:
		{
			int confID = 0;
			_dm->GetValue(++index,confID);
			_resObj.key_ = eSDKTool::num2str(confID);
			_dm->GetValue(++index,_resObj.totalCount_);
		}
		break;
	default:
		break;
	}
}

int OldHistoryQuery::QuerySingleChat(const std::string& _dbName,const std::string& _peerAccount
									 ,ParentType::ResCtnType & _ctnObj)
{
	return QueryRecordsByKey(_dbName,_peerAccount,_ctnObj,SINGLE_RECORD_TYPE);
}
int OldHistoryQuery::QueryGroupChat(const std::string& _dbName,const std::string& _groupID
									,ParentType::ResCtnType & _ctnObj,bool _isArchive)
{
	return QueryRecordsByKey(_dbName,_groupID,_ctnObj,_isArchive ? ARCHIVE_GROUP_RECORD_TYPE : GROUP_RECORD_TYPE);
}

int OldHistoryQuery::QuerySMSChat(const std::string& _dbName,ParentType::ResCtnType& _ctnObj,bool _isArchive)
{
	return QueryRecords(_dbName,_ctnObj,_isArchive ? ARCHIVE_SMS_RECORD_TYPE : SMS_RECORD_TYPE);
}

int OldHistoryQuery::QuerySystemNotify(const std::string& _dbName,ParentType::ResCtnType& _ctnObj,bool _isArchive)
{
	return QueryRecords(_dbName,_ctnObj,_isArchive ? ARCHIVE_SYSTEM_RECORD_TYPE : SYSTEM_RECORD_TYPE);
}

int OldHistoryQuery::QueryAudioConf(const std::string& _dbName,ParentType::ResCtnType& _ctnObj)
{
	return QueryRecords(_dbName,_ctnObj,CONF_RECORD_TYPE);
}

int OldHistoryQuery::QuerySingleCall(const std::string& _dbName,ParentType::ResCtnType& _ctnObj)
{
	return QueryRecords(_dbName,_ctnObj,SIP_RECORD_TYPE);
}

int OldHistoryQuery::QueryRecordsByKey(const std::string& _dbName,const std::string _key
									 ,ParentType::ResCtnType & _ctnObj,int _enumType)
{
	if(_dbName.empty())
	{
		return 0;
	}
	ParentType::ArgObjType argObj;
	if(_enumType == SINGLE_RECORD_TYPE)
	{
		argObj.peerInfo_.peerAccount = _key;
	}
	if(_enumType == ARCHIVE_GROUP_RECORD_TYPE || _enumType == GROUP_RECORD_TYPE)
	{
		argObj.groupInfo_.groupID_ = _key;
	}
	OldHistoryQuery qry(_dbName);
	qry.BatchExecute(_enumType,argObj,_ctnObj);

	DEBUG_LOG("_dbName=%s,qry.count=%d",_dbName.c_str(),qry.count);
    return qry.count;
}

int OldHistoryQuery::QueryRecords(const std::string& _dbName,ParentType::ResCtnType& _ctnObj,int _enumType)
{
	ParentType::ArgObjType argObj;
	OldHistoryQuery qry(_dbName);
	qry.BatchExecute(_enumType,argObj,_ctnObj);

	DEBUG_LOG("_dbName=%s,qry.count=%d",_dbName.c_str(),qry.count);
    return qry.count;
}

void OldHistoryQuery::ComposeSQL(std::string & _sql)
{
	switch (type_)
	{
	case SINGLE_RECORD_TYPE:
		_sql = "SELECT ACCOUNT,NAME,FORMAT,CONTENT,DATETIME,FLAG,TYPE,UTCDATETIME FROM IMRECORDTAB WHERE ACCOUNT=?;";
		break;
	case GROUP_RECORD_TYPE:
		_sql = "SELECT GROUPID,ACCOUNT,NAME,FORMAT,CONTENT,DATETIME,FLAG,TYPE,ISREAD,UTCDATETIME FROM IMGROUPRECORDTAB WHERE GROUPID=?;";
		break;
	case ARCHIVE_GROUP_RECORD_TYPE:
		_sql = "SELECT GROUPID,ACCOUNT,NAME,FORMAT,CONTENT,DATETIME,FLAG,TYPE,ISREAD,UTCDATETIME FROM GROUPRECORDTAB WHERE GROUPID=?;";
		break;
	case SIP_RECORD_TYPE:
		_sql = "SELECT ACCOUNT,MOBILE,NAME,DURATION,DATETIME,FLAG,TYPE,UTCDATETIME FROM SIPRECORDTAB;";
		break;
	case SMS_RECORD_TYPE:
		_sql = "SELECT ACCOUNT,MOBILE,NAME,CONTENT,DATETIME,FLAG,TYPE,UTCDATETIME FROM SMRECORDTAB;";
		break;
	case ARCHIVE_SMS_RECORD_TYPE:
		_sql = "SELECT ACCOUNT,MOBILE,NAME,CONTENT,DATETIME,FLAG,TYPE,UTCDATETIME FROM SMSRECORDTAB;";
		break;
	case SYSTEM_RECORD_TYPE:
		_sql = "SELECT TITLE,CONTENT,DATETIME FROM BCRECORDTAB;";
		break;
	case ARCHIVE_SYSTEM_RECORD_TYPE:
		_sql = "SELECT TITLE,CONTENT,DATETIME FROM SYSRECORDTAB;";
		break;
	case CONF_RECORD_TYPE:
		_sql = "SELECT ID,ACCOUNT,NAME,SUBJECT,DURATION,DATETIME,UTCDATETIME FROM CONFRECORDTAB;";
		break;
	default:
		break;
	}
}
void OldHistoryQuery::Bind(IDataManipulation * _dm, const ParentType::ArgObjType & _argObj)
{
	int index = 0;
	switch (type_)
	{
	case SINGLE_RECORD_TYPE:
		_dm->Bind(++index,_argObj.peerInfo_.peerAccount);
		break;
	case GROUP_RECORD_TYPE:
	case ARCHIVE_GROUP_RECORD_TYPE:
		_dm->Bind(++index,_argObj.groupInfo_.groupID_);
		break;
	default:
		break;
	}
}
void OldHistoryQuery::Extract(IDataManipulation * _dm, ParentType::ResObjType & _resObj)
{
	int index = -1;
	switch (type_)
	{
	case SINGLE_RECORD_TYPE:
		_dm->GetValue(++index,_resObj.peerInfo_.peerAccount);
		_dm->GetValue(++index,_resObj.peerInfo_.peerName_);
		_dm->GetValue(++index,_resObj.format_);
		_dm->GetValue(++index,_resObj.content_);
		_dm->GetValue(++index,_resObj.datetime_);
		_dm->GetValue(++index,_resObj.flag_);
		_dm->GetValue(++index,_resObj.type_);
		_dm->GetValue(++index,_resObj.uctDatetime_);
		break;
	case GROUP_RECORD_TYPE:
	case ARCHIVE_GROUP_RECORD_TYPE:
		_dm->GetValue(++index,_resObj.groupInfo_.groupID_);
		_dm->GetValue(++index,_resObj.peerInfo_.peerAccount);
		_dm->GetValue(++index,_resObj.peerInfo_.peerName_);
		_dm->GetValue(++index,_resObj.format_);
		_dm->GetValue(++index,_resObj.content_);
		_dm->GetValue(++index,_resObj.datetime_);
		_dm->GetValue(++index,_resObj.flag_);
		_dm->GetValue(++index,_resObj.type_);
		_dm->GetValue(++index,_resObj.unRead_);
		_dm->GetValue(++index,_resObj.uctDatetime_);
		break;
	case SIP_RECORD_TYPE:
		_dm->GetValue(++index,_resObj.peerInfo_.peerAccount);
		_dm->GetValue(++index,_resObj.mobile_);
		_dm->GetValue(++index,_resObj.peerInfo_.peerName_);
		_dm->GetValue(++index,_resObj.duration_);
		_dm->GetValue(++index,_resObj.datetime_);
		_dm->GetValue(++index,_resObj.flag_);
		_dm->GetValue(++index,_resObj.type_);
		_dm->GetValue(++index,_resObj.uctDatetime_);
		break;
	case SMS_RECORD_TYPE:
		_dm->GetValue(++index,_resObj.peerInfo_.peerAccount);
		_dm->GetValue(++index,_resObj.mobile_);
		_dm->GetValue(++index,_resObj.peerInfo_.peerName_);
		_dm->GetValue(++index,_resObj.content_);
		_dm->GetValue(++index,_resObj.datetime_);
		_dm->GetValue(++index,_resObj.flag_);
		_dm->GetValue(++index,_resObj.type_);
		_dm->GetValue(++index,_resObj.uctDatetime_);
		break;
	case SYSTEM_RECORD_TYPE:
	case ARCHIVE_SYSTEM_RECORD_TYPE:
		_dm->GetValue(++index,_resObj.format_);
		_dm->GetValue(++index,_resObj.content_);
		_dm->GetValue(++index,_resObj.datetime_);
		break;
	case CONF_RECORD_TYPE:
		{
		int confID = 0;
		_dm->GetValue(++index,confID);
		_resObj.groupInfo_.groupID_ = eSDKTool::num2str(confID);
		_dm->GetValue(++index,_resObj.peerInfo_.peerAccount);
		_dm->GetValue(++index,_resObj.peerInfo_.peerName_);
		_dm->GetValue(++index,_resObj.groupInfo_.groupName_);
		_dm->GetValue(++index,_resObj.duration_);
		_dm->GetValue(++index,_resObj.datetime_);
		_dm->GetValue(++index,_resObj.uctDatetime_);
		}
		break;
	default:
		break;
	}
}

int OldUserAndGroupQuery::QueryFixGroupMembers(const std::string& _dbName,const std::string& _groupID
	,ParentType::ResCtnType & _ctnObj,bool _isArchive)
{
	if(_dbName.empty() || _groupID.empty())
	{
		return 0;
	}
	ParentType::ArgObjType argObj = _groupID;
	OldUserAndGroupQuery qry(_dbName);
	qry.BatchExecute(_isArchive ? ARCHIVE_FIXGROUP_MEMBER_TYPE : FIXGROUP_MEMBER_TYPE,argObj,_ctnObj);

	DEBUG_LOG("_dbName=%s,_groupID=%s,qry.count=%d",_dbName.c_str(),_groupID.c_str(),qry.count);
    return qry.count;
}

int OldUserAndGroupQuery::QueryLoginList(const std::string& _dbName,ParentType::ResCtnType & _ctnObj)
{
	if(_dbName.empty())
	{
		return 0;
	}
	ParentType::ArgObjType argObj;
	OldUserAndGroupQuery qry(_dbName);
	qry.BatchExecute(LOGIN_LIST_TYPE,argObj,_ctnObj);

	DEBUG_LOG("_dbName=%s,qry.count=%d",_dbName.c_str(),qry.count);
    return qry.count;
}

int OldUserAndGroupQuery::QueryArchivePath(const std::string& _dbName,std::string& _archivePath)
{
	if(_dbName.empty())
	{
		return 0;
	}
	ParentType::ArgObjType argObj;
	ParentType::ResObjType resObj;
	OldUserAndGroupQuery qry(_dbName);
	(void)qry.SingleExecute(OLD_ARCHIVE_PATH,argObj,resObj);
	_archivePath = resObj.callNo_;

	DEBUG_LOG("_dbName=%s,_archivePath=%s,qry.count=%d",_dbName.c_str(),_archivePath.c_str(),qry.count);
    return qry.count;
}

int OldUserAndGroupQuery::QueryTempGroupName(const std::string& _dbName,const std::string& _groupID
		,ParentType::ResObjType & _resObj,bool _isArchive)
{
	if(_dbName.empty() || _groupID.empty())
	{
		return 0;
	}
	ParentType::ArgObjType argObj = _groupID;
	OldUserAndGroupQuery qry(_dbName);
	(void)qry.SingleExecute(_isArchive ? ARCHIVE_TEMPGROUP_NAME_TYPE:TEMPGROUP_NAME_TYPE,argObj,_resObj);

	DEBUG_LOG("_dbName=%s,_groupID=%s,qry.count=%d",_dbName.c_str(),_groupID.c_str(),qry.count);
    return qry.count;
}

int OldUserAndGroupQuery::QueryAudioConfMembers(const std::string& _dbName,const std::string& _confID
	,ParentType::ResCtnType& _ctnObj)
{
	if(_dbName.empty() || _confID.empty())
	{
		return 0;
	}
	ParentType::ArgObjType argObj = _confID;
	OldUserAndGroupQuery qry(_dbName);
	qry.BatchExecute(AUDIO_CONF_MEMBER,argObj,_ctnObj);

	DEBUG_LOG("_dbName=%s,_confID=%s,qry.count=%d",_dbName.c_str(),_confID.c_str(),qry.count);
    return qry.count;
}

void OldUserAndGroupQuery::ComposeSQL(std::string & _sql)
{
	switch (type_)
	{
	case FIXGROUP_MEMBER_TYPE:
		_sql = "SELECT A.ACCOUNT,A.NAME,C.GROUPNAME,C.GROUPID,C.OWNER,C.FLAG FROM STAFFTAB A,IMGROUPMEMBERTAB B,IMGROUPTAB C \
			WHERE A.STAFFID=B.STAFFID AND B.GROUPID=C.GROUPID AND B.GROUPID=?;";
		break;
	case ARCHIVE_FIXGROUP_MEMBER_TYPE:
		_sql = "SELECT A.ACCOUNT,A.NAME,C.GROUPNAME,C.GROUPID,C.OWNER,C.FLAG FROM STAFFTAB A,FIXEDGROUPMEMBERTAB B,FIXEDGROUPTAB C \
			WHERE A.STAFFID=B.STAFFID AND B.GROUPID=C.GROUPID AND B.GROUPID=?;";
		break;
	case LOGIN_LIST_TYPE:
		_sql = "SELECT LOGINACCOUNT,PASSWORD FROM LOGINLISTTAB;";
		break;
	case OLD_ARCHIVE_PATH:
		_sql = "SELECT VALUE FROM USERCONFIGTAB WHERE KEY='ArchivePath';";
		break;
	case TEMPGROUP_NAME_TYPE:
		//临时群表里的owner为空,群组成语为空
		_sql = "SELECT GROUPNAME FROM IMTEMPGROUPTAB WHERE GROUPID=?;";
		break;
	case ARCHIVE_TEMPGROUP_NAME_TYPE:
		//临时群表里的owner为空,群组成员为空
		_sql = "SELECT GROUPNAME FROM TEMPGROUPTAB WHERE GROUPID=?;";
		break;
	case AUDIO_CONF_MEMBER:
		//
		_sql = "SELECT ACCOUNT,NAME,NUMBER FROM CONFATTENDERRECORDTAB WHERE CONFID=?;";
		break;
	default:
		break;
	}
}
void OldUserAndGroupQuery::Bind(IDataManipulation * _dm, const ParentType::ArgObjType & _argObj)
{
	int index = 0;
	switch (type_)
	{
	case FIXGROUP_MEMBER_TYPE:
	case ARCHIVE_FIXGROUP_MEMBER_TYPE:
		_dm->Bind(++index,_argObj);
		break;
	case LOGIN_LIST_TYPE:
		break;
	case TEMPGROUP_NAME_TYPE:
	case ARCHIVE_TEMPGROUP_NAME_TYPE:
		_dm->Bind(++index,_argObj);
		break;
	case AUDIO_CONF_MEMBER:
		{
		int confID = eSDKTool::str2num(_argObj);
		_dm->Bind(++index,confID);
		}
		break;
	default:
		break;
	}
}
void OldUserAndGroupQuery::Extract(IDataManipulation * _dm, ParentType::ResObjType & _resObj)
{
	int index = -1;
	switch (type_)
	{
	case FIXGROUP_MEMBER_TYPE:
	case ARCHIVE_FIXGROUP_MEMBER_TYPE:
		_dm->GetValue(++index,_resObj.peerInfo_.peerAccount);
		_dm->GetValue(++index,_resObj.peerInfo_.peerName_);
		_dm->GetValue(++index,_resObj.groupName_);
		_dm->GetValue(++index,_resObj.groupID_);
		_dm->GetValue(++index,_resObj.groupOwner_);
		_dm->GetValue(++index,_resObj.groupType_);
		break;
	case LOGIN_LIST_TYPE:
		_dm->GetValue(++index,_resObj.peerInfo_.peerAccount);
		_dm->GetValue(++index,_resObj.passWord_);
		break;
	case OLD_ARCHIVE_PATH:
		_dm->GetValue(++index,_resObj.callNo_);
		break;
	case TEMPGROUP_NAME_TYPE:
	case ARCHIVE_TEMPGROUP_NAME_TYPE:
		_dm->GetValue(++index,_resObj.groupName_);
		break;
	case AUDIO_CONF_MEMBER:
		_dm->GetValue(++index,_resObj.peerInfo_.peerAccount);
		_dm->GetValue(++index,_resObj.peerInfo_.peerName_);
		_dm->GetValue(++index,_resObj.callNo_);
		break;
	default:
		break;
	}
}

int QueryOldTransferPgsCmd::QueryAll(const std::string& _dbName,ParentType::ResCtnType & _ctnObj)
{
	QueryOldTransferPgsCmd cls(_dbName);
	ParentType::ResObjType resObj;
	cls.BatchExecute(0,resObj,_ctnObj);
	return cls.count;
}
void QueryOldTransferPgsCmd::ComposeSQL(std::string & _sql)
{
	_sql = "SELECT KEY,VALUE FROM SYSCONFIGTAB";
}
void QueryOldTransferPgsCmd::Bind(IDataManipulation * , const ParentType::ArgObjType & )
{
}
void QueryOldTransferPgsCmd::Extract(IDataManipulation * _dm, ParentType::ResObjType & _resObj)
{
	int index = -1;
	_dm->GetValue(++index,_resObj.keyName_);
	_dm->GetValue(++index,_resObj.value_);
}

int AddOldTransferPgsCmd::Add(const std::string& _dbName,const ArgObjType & argObj)
{ 
	AddOldTransferPgsCmd cmd(_dbName); 
	cmd.SingleExecute(0, argObj); 
	return cmd.changed; 
}
void AddOldTransferPgsCmd::ComposeSQL(std::string & sql)
{
	sql = "INSERT INTO SYSCONFIGTAB(KEY,VALUE) VALUES (?,?)";
}
void AddOldTransferPgsCmd::Bind(IDataManipulation * dm, const DMLBase<OldHistoryProgress>::ArgObjType & argObj)
{
	int index = 0;
	dm->Bind(++index,argObj.keyName_);
	dm->Bind(++index,argObj.value_);
}

    } // namespace history
  } // namespace ecsdata
} // namespace ecs

