#include "StdAfx.h"
#include "UCHistoryMgr.h"
#include "eSDKTool.h"
#include "Log.h"
#include "data/ECSData.h"
#include <algorithm>
#include "data/model/history/Conversation.h"
#include "data/model/history/Record.h"

namespace historydata {

	std::string Date::ToString() const
	{
		char str[16];
#ifdef WIN32
		(void)::_snprintf_s(str, 16, _TRUNCATE, "%04d-%02d-%02d", year, month, day);
#else//_APPLE_
		//::sprintf(str, "%04d-%02d-%02d", year, month, day);
#endif
		return str;
	}

	std::string Date::ToUTCDateString(std::string strtime) const
	{
		int hour;
		int minute;
		int second;
		(void)::sscanf_s(strtime.c_str(), "%d:%d:%d", &hour, &minute, &second);

		TIME_ZONE_INFORMATION *lpTimeZone = new TIME_ZONE_INFORMATION;//参数1，时区
		(void)GetTimeZoneInformation(lpTimeZone);

		SYSTEMTIME sysTimeLocal;//参数2，本地时间，入参
		memset(&sysTimeLocal, 0, sizeof(SYSTEMTIME));
		sysTimeLocal.wYear = (WORD)year;
		sysTimeLocal.wMonth = (WORD)month;
		sysTimeLocal.wDay = (WORD)day;
		sysTimeLocal.wHour = (WORD)hour;
		sysTimeLocal.wMinute = (WORD)minute;
		sysTimeLocal.wSecond = (WORD)second;

		SYSTEMTIME sysTimeUTC;//参数3，UTC时间，出参
		memset(&sysTimeUTC, 0, sizeof(SYSTEMTIME));
		(void)TzSpecificLocalTimeToSystemTime(lpTimeZone,&sysTimeLocal,&sysTimeUTC);//本地时间转UTC

		delete lpTimeZone;

		char str[16];
#ifdef WIN32
		(void)::sprintf_s(str, 16, "%04d-%02d-%02d", sysTimeUTC.wYear, sysTimeUTC.wMonth, sysTimeUTC.wDay);
#else//_APPLE_
		//::sprintf(str, "%04d-%02d-%02d", sysTimeUTC.wYear, sysTimeUTC.wMonth, sysTimeUTC.wDay);
#endif
		return str;
	}

	bool Date::FromString(const std::string & str)
	{

#ifdef WIN32
		int scanRet = ::sscanf_s(str.c_str(), "%d-%d-%d", 
			&year, &month, &day);
#else
		int scanRet = ::sscanf_s(str.c_str(), "%d-%d-%d", 
			&year, &month, &day);

#endif
		return scanRet == 3;
	}

	std::string Time::ToString() const
	{
		char str[16];
#ifdef WIN32
		(void)::sprintf_s(str, 16, "%02d:%02d:%02d", hour, minute, second);
#else//_APPLE_
		//::sprintf(str, "%02d:%02d:%02d", hour, minute, second);
#endif
		return str;
	}

	std::string Time::ToUTCTimeString(std::string strdate) const
	{
		int year;
		int month;
		int day;
		(void)::sscanf_s(strdate.c_str(), "%d-%d-%d", &year, &month, &day);

		TIME_ZONE_INFORMATION *lpTimeZone = new TIME_ZONE_INFORMATION;//参数1，时区
		(void)GetTimeZoneInformation(lpTimeZone);

		SYSTEMTIME sysTimeLocal;//参数2，本地时间，入参
		memset(&sysTimeLocal, 0, sizeof(SYSTEMTIME));
		sysTimeLocal.wYear = (WORD)year;
		sysTimeLocal.wMonth = (WORD)month;
		sysTimeLocal.wDay = (WORD)day;
		sysTimeLocal.wHour = (WORD)hour;
		sysTimeLocal.wMinute = (WORD)minute;
		sysTimeLocal.wSecond = (WORD)second;

		SYSTEMTIME sysTimeUTC;//参数3，UTC时间，出参
		memset(&sysTimeUTC, 0, sizeof(SYSTEMTIME));
		(void)TzSpecificLocalTimeToSystemTime(lpTimeZone,&sysTimeLocal,&sysTimeUTC);//本地时间转UTC

		delete lpTimeZone;

		char str[16];
#ifdef WIN32
		(void)::sprintf_s(str, 16, "%02d:%02d:%02d", sysTimeUTC.wHour, sysTimeUTC.wMinute, sysTimeUTC.wSecond);
#else//_APPLE_
		//::sprintf(str, "%02d:%02d:%02d", sysTimeUTC.wHour, sysTimeUTC.wMinute, sysTimeUTC.wSecond);
#endif
		return str;
	}

	bool Time::FromString(const std::string & str)
	{
#ifdef WIN32
		int scanRet = ::sscanf_s(str.c_str(),  "%d:%d:%d", 
			&hour, &minute, &second);
#else
		int scanRet = ::sscanf_s(str.c_str(),  "%d:%d:%d", 
			&hour, &minute, &second);  
#endif
		return scanRet == 3;
	}

	Record::Record(int record_type, int cvs_type)
		: recordType(record_type)
		, msgId("")
		, recordId(0)
		, cvsType(cvs_type)
		, cvsId("")
		, oldCvsId("")
		, peerId("")
		, peerName("")
		, sent(false)
		, date()
		, time()
		, duration(-1)
		, read(true)
		, important(false)
		, body("")
		, text("")
		, extparam1("")
		, recordFlag(0)
		, isSrvHistoryRecord(false)
	{
	}

	bool Record::SetRead(bool set)
	{
		if ((int)set == (int)read)
		{
			return true;
		}
		else
		{
			if (ecs::ecsdata::history::UpdateRecordCommand
				::UpdateUnreadByRecordId(recordId, !set))
			{
				read = set;
				return true;
			}
		}

		return false;
	}

	bool Record::SetImportant(bool set)
	{
		if ((int)set == (int)important)
		{
			return true;
		}
		else
		{
			if (ecs::ecsdata::history::UpdateRecordCommand
				::UpdateImportantByRecordId(recordId, set))
			{
				important = set;
				return true;
			}
		}

		return false;
	}

	bool Record::ModifyDuration(int dura)
	{
		if (ecs::ecsdata::history::UpdateRecordCommand
			::UpdateDurationByRecordId(recordId, dura))
		{
			this->duration = dura;
			return true;
		} 
		else
		{
			return false;
		}
	}

	bool Record::ModifyBody(const std::string & bd)
	{
		if (ecs::ecsdata::history::UpdateRecordCommand
			::UpdateBodyByRecordId(recordId, bd))
		{
			body = bd;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Record::ModifyText(const std::string & tx)
	{
		if (ecs::ecsdata::history::UpdateRecordCommand
			::UpdateTextByRecordId(recordId, tx))
		{
			text = tx;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Record::ModifyFlag(int record_flag)
	{
		if (ecs::ecsdata::history::UpdateRecordCommand
			::UpdateFlagByRecordId(recordId, record_flag))
		{
			recordFlag = record_flag;
			return true;
		} 
		else
		{
			return false;
		}
	}

	bool Record::ModifyUTCDateTime(const std::string & _serverid, const std::string & _utcdate, const std::string & _utctime) const
	{
		INFO_LOG("msgId=%s,_serverid=%s,_utcdate=%s,_utctime=%s",msgId.c_str(),_serverid.c_str(),_utcdate.c_str(),_utctime.c_str());
		if (ecs::ecsdata::history::UpdateRecordCommand
			::UpdateUTCDateTimeByMsgId(msgId,_serverid,_utcdate,_utctime))
		{
			return true;
		} 
		else
		{
			return false;
		}
	}


	bool Conversation::CreateRecord(Record & record, int record_type, const std::string & peer_id, const std::string & peer_name, bool sent, 
		const Date & dt, const Time & t, const std::string & body, const std::string & text /* = "" */, 
		const std::string& extparam /* = "" */) const
	{
		record.recordId = -1; // initially set an invalid value
		record.recordType = record_type;
		record.cvsType = this->cvsType;
		record.cvsId = this->cvsId;
		record.peerId = peer_id;
		record.peerName = peer_name;
		record.sent = sent;
		record.date = dt;
		record.time = t;
		record.body = body;
		record.text = text;
		//增加个附加字段
		record.extparam1 = extparam;
		ecs::ecsdata::history::Record dataRec;
		TypeConvert::APIRecord2DataRecord(record, dataRec);
		record.recordId = ecs::ecsdata::history::InsertRecordCommand::SingleInsert(dataRec);

		if (record.recordId <= 0)
		{
			return false;
		}

		//漫游消息不刷新最近对话
		if (record.isSrvHistoryRecord)
		{
			return true;
		}
		return true;
	}

	bool Conversation::CreateIncommingCallRecord(Record & record, 
		const Date & dt, const Time & t, 
		const std::string & peer_id, const std::string & peer_name) const
	{
		return CreateRecord(record, 
			CVS_SINGLE == cvsType ? RECORD_CALL : RECORD_MEETING, 
			peer_id, peer_name, false, dt, t, "");
	}

	bool Conversation::CreateOutgoingCallRecord(Record & record, 
		const Date & dt, const Time & t, 
		const std::string & peer_id, const std::string & peer_name) const
	{
		return CreateRecord(record, 
			CVS_SINGLE == cvsType ? RECORD_CALL : RECORD_MEETING, 
			peer_id, peer_name, true, dt, t, "");
	}

	bool Conversation::SetParticipants(const std::string & part)
	{
		if (ecs::ecsdata::history::UpdateConversationCommand
			::UpdateParticipantsByConversationId(cvsId, part))
		{
			participants = part;
			return true;
		} 
		else
		{
			return false;
		}
	}

	void TypeConvert::APIConversation2DataConversation(
		const historydata::Conversation & apiObj, 
		ecs::ecsdata::history::Cvs & dataObj)
	{
		dataObj.cvsId = apiObj.cvsId;
		dataObj.cvsType = apiObj.cvsType;
		dataObj.groupId = apiObj.groupId;
		dataObj.groupName = apiObj.groupName;
		dataObj.originator = apiObj.originator;
		dataObj.participants = apiObj.participants;
	}

	void TypeConvert::APIRecord2DataRecord(
		const historydata::Record & apiObj, 
		ecs::ecsdata::history::Record & dataObj)
	{
		dataObj.recordId = apiObj.recordId;
		dataObj.recordType = apiObj.recordType;
		dataObj.cvsId = apiObj.cvsId;
		dataObj.oldCvsId = apiObj.oldCvsId;
		dataObj.sent = apiObj.sent;
		dataObj.peerId = apiObj.peerId;
		dataObj.reservedStr2 = apiObj.msgId;
		dataObj.peerName = apiObj.peerName;
		dataObj.date = apiObj.date.ToString();
		dataObj.time = apiObj.time.ToString();
		dataObj.duration = apiObj.duration;
		dataObj.utcdate = apiObj.date.ToUTCDateString(dataObj.time);
		dataObj.utctime = apiObj.time.ToUTCTimeString(dataObj.date);
		dataObj.unread = !apiObj.read;
		dataObj.important = apiObj.important;
		dataObj.body = apiObj.body;
		dataObj.text = apiObj.text;
		dataObj.flag = apiObj.recordFlag;
		dataObj.reservedStr3 = apiObj.extparam1;
	}
	void TypeConvert::DataConversation2APIConversation(
		const ecs::ecsdata::history::Cvs & dataObj, 
		historydata::Conversation & apiObj)
	{
		apiObj.cvsId = dataObj.cvsId;
		apiObj.cvsType = dataObj.cvsType;
		apiObj.groupId = dataObj.groupId;
		apiObj.groupName = dataObj.groupName;
		apiObj.originator = dataObj.originator;
		apiObj.participants = dataObj.participants;
	}

	void TypeConvert::DataConversation2APIConversationBatch(
		const std::vector<ecs::ecsdata::history::Cvs> & dataObjs, 
		std::vector<historydata::Conversation> & apiObjs)
	{
		std::vector<ecs::ecsdata::history::Cvs>::const_iterator 
			itor = dataObjs.begin();
		while (itor != dataObjs.end())
		{
			historydata::Conversation apiObj;
			DataConversation2APIConversation(*itor, apiObj);
			apiObjs.push_back(apiObj);
			itor++;
		}
	}

	//static 
	void TypeConvert::DataRecord2APIRecord(
		const ecs::ecsdata::history::Record & dataObj, 
		historydata::Record & apiObj)
	{
		apiObj.recordId = dataObj.recordId;
		apiObj.recordType = dataObj.recordType;
		apiObj.cvsId = dataObj.cvsId;
		apiObj.oldCvsId = dataObj.oldCvsId;
		apiObj.sent = dataObj.sent != 0;
		apiObj.peerId = dataObj.peerId;
		apiObj.msgId = dataObj.reservedStr2;//保留字段2用于保存msgid
		apiObj.peerName = dataObj.peerName;
		(void)apiObj.date.FromString(dataObj.date);
		(void)apiObj.time.FromString(dataObj.time);
		apiObj.duration = dataObj.duration;
		apiObj.read = dataObj.unread == 0;
		apiObj.important = dataObj.important != 0;
		apiObj.body = dataObj.body;
		apiObj.text = dataObj.text;
		apiObj.recordFlag = dataObj.flag;
	}

	//static 
	void TypeConvert::DataRecord2APIRecordBatch(
		const std::vector<ecs::ecsdata::history::Record> & dataObjs, 
		std::vector<historydata::Record> & apiObjs)
	{
		apiObjs.reserve(apiObjs.size() + dataObjs.size());

		std::vector<ecs::ecsdata::history::Record>::const_iterator 
			itor = dataObjs.begin();
		while (itor != dataObjs.end())
		{
			historydata::Record apiObj;
			DataRecord2APIRecord(*itor, apiObj);
			apiObjs.push_back(apiObj);
			itor++;
		}
	}

}

UCHistoryMgr::UCHistoryMgr(void)
{
}

UCHistoryMgr::~UCHistoryMgr(void)
{
}
void UCHistoryMgr::Init(const std::string& path)
{
	DEBUG_TRACE("");
	std::string strSysDBPath = path+"\\sys.db";
	ECSDATA()->InitializeSysData(strSysDBPath);

}
void UCHistoryMgr::Uninit(void)
{
	DEBUG_TRACE("");
	ECSDATA()->FinalizeSysData();
	ECSDATA()->Finalize();
}
void UCHistoryMgr::InitUserData(const std::string& path)
{
	ECSDATA()->Initialize(path);
	std::wstring strUserPath = eSDKTool::utf82unicode(path + "user.db");
	if(::PathFileExists(strUserPath.c_str()))
	{
		INFO_LOG("UpdateUserData");
		if(!ECSDATA()->UpdateUserData("user.db"))
		{
			ECSDATA()->FinalizeUserData();
			(void)eSDKTool::RenameFile(path + "user.db",path + "uc1_user.db");
			INFO_LOG("ReInitializeUserData, DeleteUserDb retVal : %d",::GetLastError()) ;
			(void)ECSDATA()->InitializeUserData("user.db");
		}
	}
	else
	{
		INFO_LOG("InitializeUserData");
		(void)ECSDATA()->InitializeUserData("user.db");
	}
	ECSDATA()->InitialAllArchive();
	ECSDATA()->DecideUseWhichDB("history.db", "history.db.bak");
	(void)ECSDATA()->UpdateHistoryData("history.db");
	(void)ECSDATA()->InitializeHistoryData("history.db");
	(void)ECSDATA()->InitializeHistoryData_BK("history.db.bak");
}
void UCHistoryMgr::UninitUserData()
{
	ECSDATA()->FinalizeUserData();
}

int UCHistoryMgr::InsertCallHistory(int _CallType,const std::string& _account,const std::string& _name,int _duration)
{

	//获取开始时间
	historydata::Date startdate;
	historydata::Time starttime;
	if(0 > _duration)
	{
		eSDKTool::GetStartTime(startdate,starttime,0);
	}
	else
	{
		eSDKTool::GetStartTime(startdate,starttime,(unsigned int)_duration);
	}
	//增加到历史记录
	historydata::Conversation historyConv;
	CreateSingleConversation(historyConv,_account,startdate,starttime);

	historydata::Record rcd;
	if(_CallType == HISTORY_CALL_DIALED)
	{
		historyConv.CreateOutgoingCallRecord(rcd, startdate, starttime, _account,_name);
		rcd.ModifyDuration(_duration);
		return UC_SDK_Success;
	}
	else if(_CallType == HISTORY_CALL_ANSWERED)
	{
		historyConv.CreateIncommingCallRecord(rcd, startdate, starttime, _account,_name);
		rcd.ModifyDuration(_duration);
		return UC_SDK_Success;
	}
	else if(_CallType == HISTORY_CALL_MISSED)
	{
		historyConv.CreateIncommingCallRecord(rcd, startdate, starttime, _account,_name);
		return UC_SDK_Success;
	}

	ERROR_LOG("callType is invalid");
	return UC_SDK_InvalidPara;
}

int UCHistoryMgr::InsertConvHistory(const std::string& _convID,
									const std::string& _leaderAccount,
									const std::string& _leaderName,
									int duration)
{
	INFO_LOG("_convID=%s,_leaderAccount=%s,duration=%d",_convID.c_str(),_leaderAccount.c_str(),duration);
	//获取开始时间
	historydata::Date startdate;
	historydata::Time starttime;
	if(0 > duration)
	{
		eSDKTool::GetStartTime(startdate,starttime,0);
	}
	else
	{
		eSDKTool::GetStartTime(startdate,starttime,(unsigned int)duration);
	}
	//增加到历史记录
	historydata::Conversation historyConv;
	bool bRet = CreateTempGroupConversation(historyConv,_convID,_convID,"Default Chat",startdate,starttime,_leaderAccount,_leaderName);
	if(!bRet)
	{
		ERROR_LOG("insert conv history failed.");
		return UC_SDK_Failed;
	}
	historydata::Record rcd;
	historyConv.CreateIncommingCallRecord(rcd,startdate,starttime,_leaderAccount,_leaderName);
	historyConv.SetParticipants("");
	rcd.ModifyDuration(duration);

	return UC_SDK_Success;
}

int UCHistoryMgr::InsertConvHistoryPart(const std::string& _historyID,
						  const std::string& _partAccount,
						  const std::string& _partName)
{
	INFO_LOG("_historyID=%s,_partAccount=%s,_partName=%s",_historyID.c_str(),_partAccount.c_str(),_partName.c_str());

	historydata::Conversation historyConv;
	bool bRet = GetConversationByConversationId(historyConv,_historyID);
	if(!bRet)
	{
		ERROR_LOG("historyId is inexistent.");
		return UC_SDK_Failed;
	}
	std::string strPart = historyConv.participants;
	strPart.append(_partAccount);
	strPart.append(",");
	historyConv.SetParticipants(strPart);
	return UC_SDK_Success;
}

int UCHistoryMgr::QueryCallHistory(int _CallType,int _FromIndex,int _toIndex, STCallHistroyData* _queryResult)
{
	if(NULL == _queryResult)
	{
		ERROR_LOG("queryResult is NULL");
		return UC_SDK_NullPtr;
	}

	INFO_LOG("_CallType=%d,_queryResult=0x%x",_CallType,_queryResult);

	if(_FromIndex > _toIndex)
	{
		ERROR_LOG("index is invalid");
		return UC_SDK_InvalidPara;
	}

	historydata::CallType type_= historydata::CALL_ALL;
	int iRet = ConvertCallType(_CallType,type_);
	if(UC_SDK_Success != iRet)
	{
		ERROR_LOG("CallType is invalid");
		return iRet;
	}

	//查询所有
	std::vector<historydata::Record> lstCall;
	_queryResult->iTotal =  FilterCallRecords(lstCall, -1, 0,type_);	
	if(0 >= _queryResult->iTotal)
	{
		INFO_LOG("Total Size is %d",_queryResult->iTotal);
		return UC_SDK_Success;
	}
	if(_queryResult->iTotal < _FromIndex)
	{
		WARN_LOG("FromIndex is too large");
		return UC_SDK_InvalidPara;
	}

	lstCall.clear();
	int iSize = _queryResult->iTotal;
	(void)FilterCallRecords(lstCall, 0, iSize,type_);
	_queryResult->iTotal = (int)lstCall.size();
	_queryResult->iFrom = _FromIndex;
	if(_toIndex > _queryResult->iTotal )
	{
		_queryResult->iTo = _queryResult->iTotal-1;
	}
	else
	{
		_queryResult->iTo = _toIndex;
	}

	std::reverse(lstCall.begin(), lstCall.end());
	unsigned int resultSize = (unsigned int)(_queryResult->iTo-_queryResult->iFrom) + 1;	
	for(unsigned int i=0;i<resultSize;++i)
	{
		historydata::Record recd = lstCall.at((i+(unsigned int)_FromIndex));

		//duration
		_queryResult->stCallHistory[i].duration = recd.duration;

		//calltype
		if(recd.sent)
		{
			_queryResult->stCallHistory[i].callType = HISTORY_CALL_DIALED;
		}
		else
		{
			if(recd.duration > -1)
			{
				_queryResult->stCallHistory[i].callType = HISTORY_CALL_ANSWERED;
			}
			else
			{
				_queryResult->stCallHistory[i].callType = HISTORY_CALL_MISSED;
			}			
		}

		//recordID
		_queryResult->stCallHistory[i].recordID = (int)recd.recordId;

		//starttime
		_queryResult->stCallHistory[i].startTime.year = recd.date.year;
		_queryResult->stCallHistory[i].startTime.month = recd.date.month;
		_queryResult->stCallHistory[i].startTime.day = recd.date.day;
		_queryResult->stCallHistory[i].startTime.hour = recd.time.hour;
		_queryResult->stCallHistory[i].startTime.minute = recd.time.minute;
		_queryResult->stCallHistory[i].startTime.second = recd.time.second;

		//callname
		memset(_queryResult->stCallHistory[i].CallName,0,STRING_LENGTH);
		memcpy_s(_queryResult->stCallHistory[i].CallName,STRING_LENGTH,recd.peerName.c_str(),(recd.peerName.size()<(STRING_LENGTH)) ? (recd.peerName.size()) : (STRING_LENGTH-1));

		//account
		std::string account = recd.peerId;
		memset(_queryResult->stCallHistory[i].ucAccount,0,STRING_LENGTH);
		memcpy_s(_queryResult->stCallHistory[i].ucAccount,STRING_LENGTH,account.c_str(),(account.size()<(STRING_LENGTH)) ? (account.size()) : (STRING_LENGTH-1));

		//callNum，这里使用peerId，是因为当记录创建时，如果是IPphone呼叫就会创建号码
		std::string bindNum = recd.peerId;
		memset(_queryResult->stCallHistory[i].CallNum,0,STRING_LENGTH);
		memcpy_s(_queryResult->stCallHistory[i].CallNum,STRING_LENGTH,bindNum.c_str(),(bindNum.size()<(STRING_LENGTH)) ? (bindNum.size()) : (STRING_LENGTH-1));
	}
	return UC_SDK_Success;
}

int UCHistoryMgr::ClearCallHistory(int _CallType)const
{
	historydata::CallType sdkCalltype_= historydata::CALL_ALL;

	int iRet = ConvertCallType(_CallType,sdkCalltype_);
	if(UC_SDK_Success != iRet)
	{
		ERROR_LOG("_CallType is invalid");
		return iRet;
	}	

	RemoveCallRecords(sdkCalltype_);

	return UC_SDK_Success;
}

int UCHistoryMgr::QueryConvHistory(int _FromIndex,
								   int _toIndex,
								   STConvHistroyData* _queryResult)
{

	if(NULL == _queryResult)
	{
		ERROR_LOG("queryResult is NULL");
		return UC_SDK_NullPtr;
	}

	INFO_LOG("_FromIndex=%d,_toIndex=%d,_queryResult=0x%x",_FromIndex,_toIndex,_queryResult);

	if(_FromIndex > _toIndex)
	{
		ERROR_LOG("index is invalid");
		return UC_SDK_InvalidPara;
	}

	//先查总数
	std::vector<historydata::Record> lstTempGroup;	
	_queryResult->iTotal = FilterMeetingRecords(lstTempGroup);
	if(0 >= _queryResult->iTotal)
	{
		return UC_SDK_Success;
	}

	//再查所有
	lstTempGroup.clear();
	int iSize = _queryResult->iTotal;
	(void)FilterMeetingRecords(lstTempGroup,0,iSize);

	//翻转，设置查找的范围
	std::reverse(lstTempGroup.begin(), lstTempGroup.end());
	_queryResult->iTotal = (int)lstTempGroup.size();
	_queryResult->iFrom = _FromIndex;
	if(_toIndex > _queryResult->iTotal )
	{
		_queryResult->iTo = _queryResult->iTotal-1;
	}
	else
	{
		_queryResult->iTo = _toIndex;
	}

	//去除需要返回的部分
	unsigned int uiresultSize = (unsigned int)(_queryResult->iTo-_queryResult->iFrom) + 1;	
	for(unsigned int i=0;i<uiresultSize;++i)
	{
		historydata::Record rcd = lstTempGroup.at((i+(unsigned int)_FromIndex));
		historydata::Conversation cvs;
		bool bRet = GetConversationByConversationId(cvs,rcd.cvsId);
		if(!bRet)
		{
			WARN_LOG("GetConversationByConversationId [ %s ] failed.",rcd.cvsId.c_str());
			continue;
		}
		std::string stdParts = cvs.participants;
		std::vector<std::string> strList;
		eSDKTool::SplitString(stdParts,strList);

		_queryResult->stConvHistory[i].partcipantNum = (int)strList.size();
		_queryResult->stConvHistory[i].duration = rcd.duration;

		_queryResult->stConvHistory[i].startTime.year = rcd.date.year;
		_queryResult->stConvHistory[i].startTime.month = rcd.date.month;
		_queryResult->stConvHistory[i].startTime.day = rcd.date.day;
		_queryResult->stConvHistory[i].startTime.hour = rcd.time.hour;
		_queryResult->stConvHistory[i].startTime.minute = rcd.time.minute;
		_queryResult->stConvHistory[i].startTime.second = rcd.time.second;


		memset(_queryResult->stConvHistory[i].convID,0,STRING_LENGTH);
		memcpy_s(_queryResult->stConvHistory[i].convID,STRING_LENGTH,cvs.cvsId.c_str(),(cvs.cvsId.size()<(STRING_LENGTH)) ? (cvs.cvsId.size()) : (STRING_LENGTH-1));
		memset(_queryResult->stConvHistory[i].compereAccount,0,STRING_LENGTH);
		memcpy_s(_queryResult->stConvHistory[i].compereAccount,STRING_LENGTH,cvs.originator.c_str(),(cvs.originator.size()<(STRING_LENGTH)) ? (cvs.originator.size()) : (STRING_LENGTH-1));
		memset(_queryResult->stConvHistory[i].compereName,0,STRING_LENGTH);
		memcpy_s(_queryResult->stConvHistory[i].compereName,STRING_LENGTH,cvs.originator.c_str(),(cvs.originator.size()<(STRING_LENGTH)) ? (cvs.originator.size()) : (STRING_LENGTH-1));

	}

	return UC_SDK_Success;
}

int UCHistoryMgr::QueryHisConvPartByID(const std::string& _convID,
									   int _FromIndex,
									   int _toIndex,
									   STConfPartData* _queryResult)
{
	if(NULL == _queryResult)
	{
		ERROR_LOG("queryResult is NULL");
		return UC_SDK_NullPtr;
	}

	INFO_LOG("_convID=%s,_FromIndex=%d,_toIndex=%d,_queryResult=0x%x",_convID.c_str(),_FromIndex,_toIndex,_queryResult);

	if(_FromIndex > _toIndex)
	{
		ERROR_LOG("index is invalid");
		return UC_SDK_InvalidPara;
	}

	historydata::Conversation conv;
	bool bRet = GetConversationByConversationId(conv,_convID);
	if(!bRet)
	{
		ERROR_LOG("convID is not existed");
		return UC_SDK_Failed;
	}

	std::string strPart = conv.participants;

	std::vector<std::string> strList;
	eSDKTool::SplitString(strPart,strList);

	unsigned int iSize = strList.size();
	_queryResult->partNum = (int)iSize;

	for(unsigned int i = 0;i<iSize;++i)
	{
		memset(_queryResult->stConfPart[i].partAccount,0,STRING_LENGTH);
		memcpy_s(_queryResult->stConfPart[i].partAccount,STRING_LENGTH,strList.at(i).c_str(),(strList.at(i).size()<(STRING_LENGTH)) ? (strList.at(i).size()) : (STRING_LENGTH-1));
		memset(_queryResult->stConfPart[i].partName,0,STRING_LENGTH);
		memcpy_s(_queryResult->stConfPart[i].partName,STRING_LENGTH,strList.at(i).c_str(),(strList.at(i).size()<(STRING_LENGTH)) ? (strList.at(i).size()) : (STRING_LENGTH-1));
	}

	return UC_SDK_Success;
}

int UCHistoryMgr::ClearConvHistory()
{	
	std::vector<historydata::Conversation> listConv;
	GetTempGroupConversations(listConv);
	unsigned int uiSize = listConv.size();
	for(unsigned int i=0;i<uiSize;++i)
	{
		//清除会话
		RemoveConversationById(listConv.at(i).cvsId);
		RemoveRecordsByConversationId(listConv.at(i).cvsId);
	}

	RemoveRecordsByRecordType(historydata::RECORD_MEETING);
	return UC_SDK_Success;
}

int UCHistoryMgr::DeleteCallHistory( int ircdID)const
{
	if (ircdID < 0)	
	{
		ERROR_LOG("ircdID is invalid");
		return UC_SDK_InvalidPara;
	}

	(void)RemoveRecordsByRecordId((historydata::RecordId)ircdID);

	return UC_SDK_Success;
}
int UCHistoryMgr::DeleteConvHistory(std::string strConvID)const
{
	if (strConvID.empty())	
	{
		ERROR_LOG("iIndex is invalid");
		return UC_SDK_InvalidPara;
	}

	(void)RemoveConversationById(strConvID);
	(void)RemoveRecordsByConversationId(strConvID);

	return UC_SDK_Success;
}



int UCHistoryMgr::ConvertCallType(int _CallType,historydata::CallType& _sdkCallType)const
{
	switch (_CallType)
	{
	case HISTORY_CALL_ALL:
		{
			_sdkCallType = historydata::CALL_ALL;
			break;
		}
	case HISTORY_CALL_ANSWERED:
		{
			_sdkCallType = historydata::CALL_ANSWERED;
			break;
		}
	case HISTORY_CALL_MISSED:
		{
			_sdkCallType = historydata::CALL_MISSED;
			break;
		}
	case HISTORY_CALL_DIALED:
		{
			_sdkCallType = historydata::CALL_DIALED;
			break;
		}
	default:
		{
			return UC_SDK_InvalidPara;
		}
	}
	return UC_SDK_Success;
}

bool UCHistoryMgr::CreateSingleConversation(historydata::Conversation & cvs, 
												  const std::string & peer_id, 
												  const historydata::Date & d, 
												  const historydata::Time & t)
{
	cvs.cvsType = historydata::CVS_SINGLE;
	cvs.cvsId = peer_id;
	cvs.date = d;
	cvs.time = t;

	return AddConversationRecord(cvs);
}
bool UCHistoryMgr::CreateTempGroupConversation(historydata::Conversation & cvs, 
													 const std::string & cvs_id, 
													 const std::string & group_id, 
													 const std::string & group_name, 
													 const historydata::Date & dt, 
													 const historydata::Time & t, 
													 const std::string & orig, 
													 const std::string & pati)
{
	cvs.cvsType = historydata::CVS_TEMPGROUP;
	cvs.cvsId = cvs_id;
	cvs.groupId = group_id;
	cvs.groupName = group_name;
	cvs.date = dt;
	cvs.time = t;
	cvs.originator = orig;
	cvs.participants = pati;

	return AddConversationRecord(cvs);
}

bool UCHistoryMgr::GetConversationByConversationId(
	historydata::Conversation & cvs, 
	const std::string & cvsId)
{
	ecs::ecsdata::history::Cvs dataCvs;
	if (ecs::ecsdata::history::ConversationQuery
		::QueryByConversationId(cvsId, dataCvs)) 
	{
		historydata::TypeConvert::DataConversation2APIConversation(dataCvs, cvs);
		return true;
	} 
	else 
	{
		return false;
	}
}
int UCHistoryMgr::FilterHisRecords(std::vector<historydata::Record> & records, 
								   const ecs::ecsdata::history::Record & dataRecordArg,
								   const std::string& _dbName) const
{
	std::vector<ecs::ecsdata::history::Record> dataRecords;
	dataRecords.reserve(50);
	int resultSize = ecs::ecsdata::history::RecordQuery::FilterRecords(dataRecordArg, dataRecords,_dbName);
	if (resultSize > 0)
	{
		if(dataRecordArg.reservedInt1 < 0) //reverse
		{
			std::vector<historydata::Record> recordsTemp;
			recordsTemp.reserve(dataRecords.size());
			historydata::TypeConvert::DataRecord2APIRecordBatch(dataRecords, recordsTemp);
			std::vector<historydata::Record>::reverse_iterator itBegin = recordsTemp.rbegin();
			std::vector<historydata::Record>::reverse_iterator itEnd = recordsTemp.rend();
			(void)std::copy(itBegin, itEnd, back_inserter(records));
		}
		else
		{
			historydata::TypeConvert::DataRecord2APIRecordBatch(dataRecords, records);
		}
	}
	return resultSize;
}


int UCHistoryMgr::FilterRecords(std::vector<historydata::Record> & records, 
									  ecs::ecsdata::history::Record & dataRecordArg) const
{
	int resultSize = 0;

	if (dataRecordArg.important != 0)
	{
		std::vector<ecs::ecsdata::history::Record> dataRecords;
		resultSize = ecs::ecsdata::history::RecordQuery::FilterRecords(dataRecordArg, dataRecords);
		if (resultSize > 0)
		{
			if(dataRecordArg.reservedInt1 < 0) //reverse
			{
				std::vector<historydata::Record> recordsTemp;
				historydata::TypeConvert::DataRecord2APIRecordBatch(dataRecords, recordsTemp);
				(void)std::copy(recordsTemp.rbegin(), recordsTemp.rend(), back_inserter(records));
			}
			else
			{
				historydata::TypeConvert::DataRecord2APIRecordBatch(dataRecords, records);
			}
		}
	}
	else
	{
		resultSize = ecs::ecsdata::history::RecordQuery::FilterRecordsCount(dataRecordArg);
	}

	return resultSize;
}
//新增: 利用reservedInt1扩展字段来对过滤的结果根据recordId进行升序降序:<0为降序，默认为升序。
int UCHistoryMgr::FilterCallRecords(std::vector<historydata::Record> & records, 
										  int startIndex/* = -1*/, int amount/* = -1*/, 
										  historydata::CallType callType/* = CALL_ALL*/, int reservedInt1 /*=0*/)
{
	ecs::ecsdata::history::Record dataRecordArg;
	ComposeDataRecordArg(dataRecordArg, historydata::RECORD_CALL, startIndex, amount, reservedInt1);
	if (ComposeDataRecordArgByCallType(dataRecordArg, callType))
	{
		return FilterRecords(records,dataRecordArg);
	}
	else
	{
		return 0;
	}
}

int UCHistoryMgr::RemoveCallRecords(historydata::CallType callType/* = CALL_ALL*/) const
{
	ecs::ecsdata::history::Record dataRecordArg;
	if (!ComposeDataRecordArgByCallType(dataRecordArg, callType))
	{
		return 0;
	}
	else
	{
		return ecs::ecsdata::history::RemoveRecordCommand
			::RemoveHistoryCallRecords(dataRecordArg);
	}
}

int UCHistoryMgr::FilterMeetingRecords(std::vector<historydata::Record> & records, 
											 int startIndex/* = -1*/, int amount/* = -1*/) 
{
	INFO_LOG("startIndex=%d, amount=%d",startIndex, amount);

	ecs::ecsdata::history::Record dataRecordArg;
	ComposeDataRecordArg(dataRecordArg, historydata::RECORD_MEETING, startIndex, amount);

	return FilterRecords(records,dataRecordArg);
}

int UCHistoryMgr::RemoveRecordsByRecordType(int recordType) const
{
	return ecs::ecsdata::history::RemoveRecordCommand
		::RemoveByRecordType(recordType);
}

int UCHistoryMgr::GetTempGroupConversations(
	std::vector<historydata::Conversation> & conversations)
{
	std::vector<ecs::ecsdata::history::Cvs> dataCvs;
	int resultCount = ecs::ecsdata::history::ConversationQuery
		::QueryByConversationType(historydata::CVS_TEMPGROUP, dataCvs);
	if (resultCount > 0)
	{
		historydata::TypeConvert::DataConversation2APIConversationBatch(dataCvs, conversations);
	}

	return resultCount;
}


int UCHistoryMgr::RemoveRecordsByRecordId(const historydata::RecordId & recordId) const
{
	return ecs::ecsdata::history::RemoveRecordCommand
		::RemoveByRecordId(recordId);
}
int UCHistoryMgr::RemoveConversationById(
	const std::string & cvsId) const
{
	return ecs::ecsdata::history::RemoveConversationCommand
		::RemoveByConversationId(cvsId);
}

int UCHistoryMgr::RemoveRecordsByConversationId(const std::string & cvsId) const
{
	return ecs::ecsdata::history::RemoveRecordCommand
		::RemoveByConversationId(cvsId);
}

bool UCHistoryMgr::ComposeDataRecordArgByCallType(
	ecs::ecsdata::history::Record & dataRecordArg, historydata::CallType callType) const
{
	switch (callType)
	{
	case historydata::CALL_ALL:
		dataRecordArg.sent = -1;
		dataRecordArg.duration = 0;
		break;
	case historydata::CALL_MISSED:
		dataRecordArg.sent = 0;
		dataRecordArg.duration = -1;
		break;
	case historydata::CALL_ANSWERED:
		dataRecordArg.sent = 0;
		dataRecordArg.duration = 1;
		break;
	case historydata::CALL_DIALED:
		dataRecordArg.sent = 1;
		dataRecordArg.duration = 0;
		break;
	default:
		return false;
	}

	return true;
}


bool UCHistoryMgr::AddConversationRecord(const historydata::Conversation & cvs) const
{
	//获取原未读消息总数和最早未读消息MsgId
	int numUnReadMsgTotal = 0; 
	std::string strMinMsgId = "";

	ecs::ecsdata::history::Cvs cvsRec;
	historydata::TypeConvert::APIConversation2DataConversation(cvs, cvsRec);
	cvsRec.reservedInt1 = numUnReadMsgTotal;
	cvsRec.reservedStr1 = strMinMsgId;

	return ecs::ecsdata::history::AddConversationCommand::SingleAdd(cvsRec) == 1;
}

void UCHistoryMgr::ComposeDataRecordArg(
	ecs::ecsdata::history::Record & dataRecordArg, 
	historydata::RecordType recordType, int startIndex, int amount, int reservedInt1 /* = 0 */) const
{
	dataRecordArg.recordType = recordType;
	dataRecordArg.unread = startIndex;
	dataRecordArg.important = amount;
	dataRecordArg.reservedInt1 = reservedInt1;

	// 默认忽略的参数
	dataRecordArg.sent = -1;
	dataRecordArg.duration = 0;
}

