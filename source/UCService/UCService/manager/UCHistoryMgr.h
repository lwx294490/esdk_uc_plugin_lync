#pragma once
#include <map>
#include "data/model/history/HistoryDataType.h"

using namespace ecs::ecsdata::history;

namespace historydata 
{

	// conversation type
	enum CvsType
	{
		CVS_INIT = -1,
		CVS_SINGLE = 0, 
		CVS_FIXEDGROUP, 
		CVS_TEMPGROUP, 
		CVS_DISCUSSGROUP,
		CVS_SYSTEM, 
		CVS_MEETING,
		CVS_BOOKCONF
	};

	// call type
	enum CallType
	{
		CALL_ALL, 
		CALL_MISSED, 
		CALL_ANSWERED, 
		CALL_DIALED, 
	};

	enum RecordType
	{
		RECORD_CHAT, 
		RECORD_SMS, 
		RECORD_FILE, 
		RECORD_OFFLINEFILE, 
		RECORD_CHAT_SMS_FILE = 4, // 暂时没有用，仅作为查询的类型参数
		RECORD_SYSTEM = 5, 
		RECORD_VOICEMSG = 6, 
		RECORD_VIDEOMSG = 7,
		RECORD_UMMSG = 8,
		RECORD_MEETING = 9,
		RECORD_CALL = 10, 
		RECORD_MEMBER = 100, 
		RECORD_RECORDING = 101, 
	};

	struct Date
	{
		int year;
		int month;
		int day;

		Date(int y = 0, int m = 0, int d = 0) : year(y), month(m), day(d) {}
		std::string ToString() const;
		std::string ToUTCDateString(std::string strtime) const;
		bool FromString(const std::string & str);

		bool operator==(const Date & date) const
		{
			return year == date.year && month == date.month && day == date.day;
		}

	};

	struct Time
	{
		int hour;
		int minute;
		int second;

		Time(int h = 0, int m = 0, int s = 0) : hour(h), minute(m), second(s) {}
		std::string ToString() const;
		std::string ToUTCTimeString(std::string strdate) const;
		bool FromString(const std::string & str);

		bool operator==(const Time & date)
		{
			return hour == date.hour && minute == date.minute && second == date.second;
		}
	};

	typedef long long RecordId;
	class Record
	{
	public:
		int recordType; // enum RecordType
		std::string msgId;
		std::string target;
		RecordId recordId;

		int cvsType; // enum CvsType
		std::string cvsId; // staff uri or fixed group id or (temp group) conversation id
		std::string oldCvsId; // old Staff uri

		std::string peerId;
		std::string peerName; // peer name or peer number (for call)
		bool sent; // sent or received ?

		Date date;
		Time time;
		int duration; // -1 : missed call, chat, ... //for UM Message, means if the msg has been played.

		bool read; // Has chat been read or is it a missed call ?
		bool important; // is it important ?

		std::string body; // with format info
		std::string text; // no format info, pure text
		std::string extparam1; //additional param1
		int recordFlag;
		bool isSrvHistoryRecord; //get this msg record by server

		Record(int record_type = -1, int cvs_type = -1);

	public:
		bool MarkRead() { return SetRead(true); }
		bool ClearRead() { return SetRead(false); }
		bool MarkImportant() { return SetImportant(true); }
		bool ClearImportant() { return SetImportant(false); }
		bool DeleteRecentRecord();
	private:
		bool SetRead(bool set);
		bool SetImportant(bool set);

	public:
		bool ModifyDuration(int duration);
		bool ModifyBody(const std::string & bd);
		bool ModifyText(const std::string & tx);
		bool ModifyFlag(int record_flag);
		bool ModifyUTCDateTime(const std::string & _serverid, const std::string & _utcdate, const std::string & _utctime) const;

	public:
		bool IsMissedCall() const {
			return RECORD_CALL == recordType && -1 == duration;
		}

	}; // struct Record

	class Conversation
	{
	public:
		int cvsType; // enum CvsType
		std::string cvsId;

		std::string groupId;
		std::string groupName;
		std::string originator;
		std::string participants;

		Date date;
		Time time;

		bool hided;

		Conversation() 
			: cvsType(-1), hided(false)
		{
		}

	public:
		bool MarkHided() { return SetHided(true); }
		bool ClearHided() { return SetHided(false); }
		bool DeleteRecentRecord() const ;

	private:
		bool SetHided(bool set);

	public:
		// compute indirectly
		int GetImportant() const;
		int GetUnreadChat() const;

		int MarkRead() const;
		int ClearImportant() const;

	public:
		int QueryUnreadCount() const;
		int QueryUnreadCallCount() const;
		int QueryImportantCount() const;
		int GetImportantRecords(std::vector<Record> & records) const;

	public:
		bool SetParticipants(const std::string & part);
		bool SetConversationName(const std::string & newname);
		bool SetUnReadMsgTotal(const int total);
		bool SetMinMsgId(const std::string& strMinMsgId);

	public:
		bool CreateRecvChatRecord(Record & record, 
			const std::string & body, const std::string & text, 
			const Date & date, const Time & time, 
			const std::string & peer_id, const std::string & peer_name) const;
		bool CreateSentChatRecord(Record & record, 
			const std::string & body, const std::string & text, 
			const Date & date, const Time & time) const;

		bool CreateRecvUMChatRecord(Record & record, 
			const std::string & body, const std::string & text, 
			const Date & date, const Time & time, 
			const std::string & peer_id, const std::string & peer_name) const;
		bool CreateSentUMChatRecord(Record & record, 
			const std::string & body, const std::string & text, 
			const Date & date, const Time & time) const;
	public:
		bool CreateIncommingCallRecord(Record & record, 
			const Date & date, const Time & time, 
			const std::string & peer_id, const std::string & peer_name) const;
		bool CreateOutgoingCallRecord(Record & record, 
			const Date & date, const Time & time, 
			const std::string & peer_id, const std::string & peer_name) const;
	public:
		bool CreateRecvSMSRecord(Record & record, 
			const std::string & body, const Date & date, const Time & time, 
			const std::string & peer_id, const std::string & peer_name) const;
		bool CreateSentSMSRecord(Record & record, 
			const std::string & body, const Date & date, const Time & time, 
			const std::string & peer_id, const std::string & peer_name) const;
	public:
		bool CreateRecvFileRecord(Record & record, 
			const std::string & body, const Date & date, const Time & time, 
			const std::string & peer_id, const std::string & peer_name, bool isOffline = false) const;
		bool CreateSentFileRecord(Record & record, 
			const std::string & body, const Date & date, const Time & time) const;

		bool CreateRecvAudioRecord(Record & record, 
			const std::string & body, const Date & date, const Time & time, 
			const std::string & peer_id, const std::string & peer_name, 
			const std::string & extparam = "") const;
		bool CreateSentAudioRecord(Record & record, 
			const std::string & body, const Date & date, const Time & time,
			const std::string & extparam = "") const;

		bool CreateRecvVideoRecord(Record & record, 
			const std::string & body, const Date & date, const Time & time, 
			const std::string & peer_id, const std::string & peer_name,
			const std::string & extparam = "") const;
		bool CreateSentVideoRecord(Record & record, 
			const std::string & body, const Date & date, const Time & time,
			const std::string & extparam = "") const;
		bool CreateGroupNotifyReadRecord(const std::string& msgId) const;
		bool CreateOfflineFileReadRecord(const std::string& msgId, const std::string sender) const;

	public:
		bool CreateSystemRecord(Record & record, 
			const std::string & peer_id, const std::string & body, 
			const Date & date, const Time & time) const;
	public:
		bool CreateVoiceMessageRecord(Record & record, 
			const std::string & peer_id, const std::string & body, 
			const Date & date, const Time & time) const;
	public:
		bool CreateMemberRecord(Record & record, 
			const std::string & body, const Date & date, const Time & time) const;
	public:
		bool CreateRecordingRecord(Record & record, 
			const std::string & body, const Date & date, const Time & time) const;
	private:
		bool CreateRecord(Record & record, int record_type, 
			const std::string & peer_id, const std::string & peer_name, bool sent, 
			const Date & date, const Time & time, 
			const std::string & body, const std::string & text = "", const std::string& extparam = "") const;
		//bool CreateCvsUnReadRecord(const Record & record, const std::string & peer_id, int type = CVS_INIT) const; //type enum CvsMsgIdType
	public:
		bool GetLastUnreadMissedCallRecord(Record & record) const;
		bool CheckSameRecord(Record & record) const;

	public:
		int GetAllRecords(std::vector<Record> & records) const;
		int GetAllChatRecords(std::vector<Record> & records) const;
		int GetAllCallRecords(std::vector<Record> & records) const;
		int GetAllFileTransferRecords(std::vector<Record> & records) const;
		int GetAllRecordsByRecordType(std::vector<Record> & records, int record_type) const;
		int GetChatRecordsByRecordType(std::vector<Record> & records) const;
		int GetRecordsBetweenDate(std::vector<Record> & records, 
			const Date & beginDate, const Date & endDate) const; // [beginDate, endDate)
		int GetChatRecordsBetweenDate(std::vector<Record> & records, 
			const Date & beginDate, const Date & endDate) const; // [beginDate, endDate)

	public:
		int MarkMsgIdRead() const;
		int MarkMsgIdDeleting() const;
		std::string GetLastMsgIds() const;
		int RemoveMsgIds() const;
	}; // struct Conversation

	class TypeConvert
	{
	public:
		static void APIConversation2DataConversation(
			const historydata::Conversation & apiObj, 
			ecs::ecsdata::history::Cvs & dataObj);
		static void APIRecord2DataRecord(
			const historydata::Record & apiObj, 
			ecs::ecsdata::history::Record & dataObj);
		static void DataConversation2APIConversation(
			const ecs::ecsdata::history::Cvs & dataObj, 
			historydata::Conversation & apiObj);
		static void DataConversation2APIConversationBatch(
			const std::vector<ecs::ecsdata::history::Cvs> & dataObjs, 
			std::vector<historydata::Conversation> & apiObjs);
		static void DataRecord2APIRecord(
			const ecs::ecsdata::history::Record & dataObj, 
			historydata::Record & apiObj);
		static void DataRecord2APIRecordBatch(
			const std::vector<ecs::ecsdata::history::Record> & dataObjs, 
			std::vector<historydata::Record> & apiObjs);
	};

}





class UCHistoryMgr
{
	struct DBDate
	{
		std::string beginDate_;
		std::string endDate_;
	};
public:
	UCHistoryMgr(void);
	~UCHistoryMgr(void);
public:
	static inline UCHistoryMgr& Instance()
	{
		static UCHistoryMgr inst;
		return inst;
	}
public:
	void Init(const std::string& path);
	void Uninit(void);
	void InitUserData(const std::string& path);
	void UninitUserData();
public:
	int QueryCallHistory(int _CallType,int _FromIndex,int _toIndex,STCallHistroyData* _queryResult);
	int ClearCallHistory(int _CallType)const;
	int QueryConvHistory(int _FromIndex,int _toIndex,STConvHistroyData* _queryResult);
	int QueryHisConvPartByID(const std::string& _groupurl,int _FromIndex,int _toIndex,STConfPartData* _queryResult);
	int ClearConvHistory();
public:
	int InsertCallHistory(int _CallType,const std::string& _url,const std::string& _name,int _duration);
	int InsertConvHistory(const std::string& _convID,
		const std::string& _leaderAccount,
		const std::string& _leaderName,
		int duration);
	int InsertConvHistoryPart(const std::string& _convID,
		const std::string& _partAccount,
		const std::string& _partName);
public:
	int DeleteCallHistory(int ircdID)const;
	int DeleteConvHistory(std::string strConvID)const;
private:
	int ConvertCallType(int _CallType,historydata::CallType& _sdkCallType)const;//转换呼叫类型

public:
	bool CreateSingleConversation(historydata::Conversation & cvs, 
		const std::string & peer_id, 
		const historydata::Date & date, 
		const historydata::Time & time);
	bool CreateTempGroupConversation(historydata::Conversation & cvs, 
		const std::string & cvs_id, 
		const std::string & group_id,
		const std::string & group_name,
		const historydata::Date & date,
		const historydata::Time & time, 
		const std::string & orig, 
		const std::string & pati);
	bool GetConversationByConversationId(
		historydata::Conversation & cvs, 
		const std::string & cvsId);

	int FilterCallRecords(std::vector<historydata::Record> & records, 
		int startIndex/* = -1*/, int amount/* = -1*/, 
		historydata::CallType callType/* = CALL_ALL*/, int reservedInt1 = 0);


	int FilterRecords(std::vector<historydata::Record> & records, 
		ecs::ecsdata::history::Record & dataRecordArg) const;

	int RemoveCallRecords(historydata::CallType callType/* = CALL_ALL*/) const;
	int FilterMeetingRecords(std::vector<historydata::Record> & records, 
		int startIndex = -1, int amount = -1) ;
	int RemoveRecordsByRecordType(int recordType) const ;
	int GetTempGroupConversations(
		std::vector<historydata::Conversation> & conversations);

	int RemoveRecordsByRecordId(const historydata::RecordId & recordId) const;
	int RemoveConversationById(const std::string & cvsId) const;
	int RemoveRecordsByConversationId(const std::string & cvsId) const;


private:
	bool AddConversationRecord(const historydata::Conversation & cvs) const;

	void ComposeDataRecordArg(ecs::ecsdata::history::Record & dataRecordArg, 
		historydata::RecordType recordType, int startIndex, int amount, int reservedInt1 = 0) const;

	bool ComposeDataRecordArgByCallType(
		ecs::ecsdata::history::Record & dataRecordArg, historydata::CallType callType) const;

	std::map<std::string,DBDate> mapArchiveDBFiles_;

	int FilterHisRecords(std::vector<historydata::Record> & records, 
		const ecs::ecsdata::history::Record & dataRecordArg,const std::string& _dbName = HISTORYDB_NAME) const;

};
