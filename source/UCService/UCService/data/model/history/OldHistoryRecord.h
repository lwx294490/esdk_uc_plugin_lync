#pragma once

namespace ecs{
	namespace ecsdata{
		namespace history{

class   OldHistoryAnalyze : public DQLBase<OldHistoryAnalyzeData>
{
	typedef DQLBase<OldHistoryAnalyzeData> ParentType;
public:
    OldHistoryAnalyze() : ParentType("") {}
    OldHistoryAnalyze(const std::string& _dbName) : ParentType(_dbName) {}

public:
	static int QueryIMByPeer(const std::string& _dbName,ParentType::ResCtnType & _ctnObj);
	static int QueryGroupIMByID(const std::string& _dbName,ParentType::ResCtnType & _ctnObj,bool _isArchive = false);
	static int QuerySMSByPeer(const std::string& _dbName,ParentType::ResCtnType & _ctnObj,bool _isArchive = false);
	static int QueryCallByPeer(const std::string& _dbName,ParentType::ResCtnType & _ctnObj);
	static int QueryAudioConfByID(const std::string& _dbName,ParentType::ResCtnType & _ctnObj);

private:
	static int QueryConvByType(const std::string& _dbName,ParentType::ResCtnType & _ctnObj,int _enumType);
protected:
	enum{
		SINGLE_RECORD_TYPE,
		GROUP_RECORD_TYPE,
		ARCHIVE_GROUP_RECORD_TYPE,
		SMS_RECORD_TYPE,
		ARCHIVE_SMS_RECORD_TYPE,
		CALL_RECORD_TYPE,
		CONF_RECORD_TYPE
	};
	virtual void ComposeSQL(std::string & _sql);
	virtual void Bind(IDataManipulation * _dm, const ParentType::ArgObjType & _argObj);
	virtual void Extract(IDataManipulation * _dm, ParentType::ResObjType & _resObj);
};

class   OldHistoryQuery : public DQLBase<OldHistoryRecord>
{
	typedef DQLBase<OldHistoryRecord> ParentType;
public:
    OldHistoryQuery() : ParentType(""){}
    OldHistoryQuery(const std::string& _dbName) : ParentType(_dbName) {}

public:
	static int QuerySingleChat(const std::string& _dbName,const std::string& _peerAccount
		,ParentType::ResCtnType & _ctnObj);
	static int QueryGroupChat(const std::string& _dbName,const std::string& _groupID
		,ParentType::ResCtnType & _ctnObj,bool _isArchive = false);
	static int QuerySMSChat(const std::string& _dbName,ParentType::ResCtnType& _ctnObj,bool _isArchive = false);
	static int QuerySystemNotify(const std::string& _dbName,ParentType::ResCtnType& _ctnObj,bool _isArchive = false);
	static int QuerySingleCall(const std::string& _dbName,ParentType::ResCtnType& _ctnObj);
	static int QueryAudioConf(const std::string& _dbName,ParentType::ResCtnType& _ctnObj);
public:
	static int QueryRecordsByKey(const std::string& _dbName,const std::string _key
		,ParentType::ResCtnType & _ctnObj,int _enumType);
	static int QueryRecords(const std::string& _dbName,ParentType::ResCtnType& _ctnObj,int _enumType);
protected:
	enum{
		SINGLE_RECORD_TYPE,
		GROUP_RECORD_TYPE,
		ARCHIVE_GROUP_RECORD_TYPE,
		SIP_RECORD_TYPE,
		SMS_RECORD_TYPE,
		ARCHIVE_SMS_RECORD_TYPE,
		SYSTEM_RECORD_TYPE,
		ARCHIVE_SYSTEM_RECORD_TYPE,
		HOTLINE_RECORD_TYPE,
		CONF_RECORD_TYPE
	};
	virtual void ComposeSQL(std::string & _sql);
	virtual void Bind(IDataManipulation * _dm, const ParentType::ArgObjType & _argObj);
	virtual void Extract(IDataManipulation * _dm, ParentType::ResObjType & _resObj);
};

class   OldUserAndGroupQuery : public DQLBase<std::string,PeerAllInfo>
{
	typedef DQLBase<std::string,PeerAllInfo> ParentType;
public:
    OldUserAndGroupQuery() : ParentType(""){}
    OldUserAndGroupQuery(const std::string& _dbName) : ParentType(_dbName) {}

public:
	static int QueryFixGroupMembers(const std::string& _dbName,const std::string& _groupID
		,ParentType::ResCtnType & _ctnObj,bool _isArchive = false);
	static int QueryLoginList(const std::string& _dbName,ParentType::ResCtnType & _ctnObj);
	static int QueryTempGroupName(const std::string& _dbName,const std::string& _groupID
		,ParentType::ResObjType & _resObj,bool _isArchive = false);
	static int QueryAudioConfMembers(const std::string& _dbName,const std::string& _confID
		,ParentType::ResCtnType& _ctnObj);
	static int QueryArchivePath(const std::string& _dbName,std::string& _archivePath);

protected:
	enum{
		FIXGROUP_MEMBER_TYPE,
		ARCHIVE_FIXGROUP_MEMBER_TYPE,
		LOGIN_LIST_TYPE,
		TEMPGROUP_NAME_TYPE,
		ARCHIVE_TEMPGROUP_NAME_TYPE,
		AUDIO_CONF_MEMBER,
		OLD_ARCHIVE_PATH
	};
	virtual void ComposeSQL(std::string & _sql);
	virtual void Bind(IDataManipulation * _dm, const ParentType::ArgObjType & _argObj);
	virtual void Extract(IDataManipulation * _dm, ParentType::ResObjType & _resObj);
};

class   QueryOldTransferPgsCmd : public DQLBase<OldHistoryProgress>
{
	typedef DQLBase<OldHistoryProgress> ParentType;
public:
    QueryOldTransferPgsCmd() : ParentType(""){}
	QueryOldTransferPgsCmd(const std::string& _dbName) : DQLBase<OldHistoryProgress>(_dbName) {}
	static int QueryAll(const std::string& _dbName,ParentType::ResCtnType & _ctnObj);
protected:
	virtual void ComposeSQL(std::string & _sql);
	virtual void Bind(IDataManipulation * _dm, const ParentType::ArgObjType & _argObj);
	virtual void Extract(IDataManipulation * _dm, ParentType::ResObjType & _resObj);
};

class   AddOldTransferPgsCmd 
    : public DMLBase<OldHistoryProgress>
{
public:
    AddOldTransferPgsCmd() : DMLBase<OldHistoryProgress>(""){}
	AddOldTransferPgsCmd(const std::string& _dbName) : DMLBase<OldHistoryProgress>(_dbName) {}
	static int Add(const std::string& _dbName,const ArgObjType & argObj);

protected:
    virtual void ComposeSQL(std::string & sql);
    virtual void Bind(IDataManipulation * dm, 
        const DMLBase<OldHistoryProgress>::ArgObjType & argObj);
};

    } // namespace history
  } // namespace ecsdata
} // namespace ecs
