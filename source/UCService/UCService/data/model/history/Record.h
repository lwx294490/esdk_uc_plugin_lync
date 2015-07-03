#pragma once

#include <set>
#include "HistoryDataType.h"

#define RECORD_TAB "RecordTab"

// RECORD_CHAT_SMS_FILE
#define RECORD_TYPE_FILTER_CHAT_SMS_FILE 4

// RECORD_CHAT, RECORD_SMS, RECORD_FILE
#define RECORD_TYPE_FILTER_HISTORY_CHAT "< 8 "
#define RECORD_TYPE_FILTER_HISTORY_UMMSG "= 8 "
#define RECORD_TYPE_FILTER_HISTORY_SMS_CHAT_FILE_RECORDINGCHAT "IN (0,1,2,3,6,7,8) " //"IN (0,1,2,3,101) "录音记录不用显示，又专门的地方显示
// RECORD_METTING
#define RECORD_TYPE_FILTER_HISTORY_MEETING "= 9 "
// RECORD_CALL
#define RECORD_TYPE_FILTER_HISTORY_CALL "= 10 "

#define RECORD_TYPE_FILTER_HISTORY_FILE "= 2 "

#define RECORD_TYPE_FILTER_HISTORY_NOT_FILE "!= 2 "

namespace ecs {
  namespace ecsdata {
    namespace history {

class   CreateRecordTabCommand : public DDLBase
{
public:
  CreateRecordTabCommand(const std::string& _dbName = HISTORYDB_NAME) : DDLBase(_dbName) {}

protected:
  virtual void ComposeSQL(std::string & sql);

};

class   CreateRecordTabConversationIDIndexCommand : public DDLBase
{
public:
    CreateRecordTabConversationIDIndexCommand(const std::string& _dbName = HISTORYDB_NAME) : DDLBase(_dbName) {}

protected:
    virtual void ComposeSQL(std::string & sql);

};

class   DeleteRecordTabUniqueIndexCommand : public DDLBase
{
public:
    DeleteRecordTabUniqueIndexCommand(const std::string& _dbName = HISTORYDB_NAME) : DDLBase(_dbName) {}

protected:
    virtual void ComposeSQL(std::string & sql);

};


class   CreateRecordTabUniqueIndexCommand : public DDLBase
{
public:
    CreateRecordTabUniqueIndexCommand(const std::string& _dbName = HISTORYDB_NAME) : DDLBase(_dbName) {}

protected:
    virtual void ComposeSQL(std::string & sql);

};

class   CreateRecordTabRecordTypeIndexCommand : public DDLBase
{
public:
    CreateRecordTabRecordTypeIndexCommand(const std::string& _dbName = HISTORYDB_NAME) : DDLBase(_dbName) {}

protected:
    virtual void ComposeSQL(std::string & sql);

};

class   CreateRecordTabMsgIdIndexCommand : public DDLBase
{
public:
	CreateRecordTabMsgIdIndexCommand(const std::string& _dbName = HISTORYDB_NAME) : DDLBase(_dbName) {}

protected:
	virtual void ComposeSQL(std::string & sql);

};

class   AlterHistoryTabCommand : public DDLBase
{
public:
	AlterHistoryTabCommand(const std::string& _tblName,const std::string& _columnName,const std::string _newSql
        ,const std::string& _dbName = HISTORYDB_NAME)
        : DDLBase(_dbName),tblName_(_tblName),columnName_(_columnName),newSql_(_newSql){
    }
protected:
	virtual void ComposeSQL(std::string & sql);
private:
    std::string columnName_;
    std::string newSql_;
    std::string tblName_;
};

class   QueryCreateTableStmt : public DQLBase<QuerySQLPair>
{

public:
  QueryCreateTableStmt(const std::string& _dbName = HISTORYDB_NAME) : DQLBase<QuerySQLPair>(_dbName) {}

public:

  bool ColumnIsExist(const std::string& _tblName,const std::string& _columnName,const std::string _newSql);

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DQLBase<QuerySQLPair>::ArgObjType & argObj);
  virtual void Extract(IDataManipulation * dm, 
    DQLBase<QuerySQLPair>::ResObjType & resObj)
  { ExtractFromDBSqliteMaster(dm, resObj, 0); }

  static int ExtractFromDBSqliteMaster(IDataManipulation * dm, 
    DQLBase<QuerySQLPair>::ResObjType & resObj, int startIndex);

};

class   InsertRecordCommand 
  : public DMLInsertBase<Record>
{
public:
  InsertRecordCommand(const std::string& _historyName = HISTORYDB_NAME) 
    : DMLInsertBase<Record>(_historyName, RECORD_TAB) {}

  static int BatchInsert(const std::string& _dbName,const ArgCtnType& _resCtn);

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, const 
    DMLInsertBase<Record>::ArgObjType & argObj);

  DEFINE_SINGLE_INSERT_MOTHOD(InsertRecordCommand)

  DEFINE_BATCH_SINGLE_ADD_MOTHOD(InsertRecordCommand)

};

class   UpdateRecordCommand 
  : public DMLBase<Record>
{
public:
  UpdateRecordCommand() : DMLBase<Record>(HISTORYDB_NAME) {}

public:
  static bool UpdateDurationByRecordId(
    const DataRecordId & recordId, int duration);
  static bool UpdateUnreadByRecordId(
    const DataRecordId & recordId, bool rd);
  static bool UpdateImportantByRecordId(
    const DataRecordId & recordId, bool important);
  static bool UpdateBodyByRecordId(
    const DataRecordId & recordId, const std::string & body);
  static bool UpdateTextByRecordId(
    const DataRecordId & recordId, const std::string & text);
  static bool UpdateFlagByRecordId(
    const DataRecordId & recordId, int flag);

  static int UpdateUnreadByConversationId(
    const std::string & cvsId, int rd);
  static int UpdateImportantByConversationId(
    const std::string & cvsId, int important);

  static int UpdateUTCDateTimeByMsgId(
      const std::string & _serverid, const std::string & msgid, const std::string & utcdate, const std::string & utctime);

protected:
  enum
  {
    INVALID, 
    DURATION, 
    UNREAD, 
    IMPORTANT, 
    BODY, 
    TEXT, 
    FLAG, 
    UNREAD_BY_CONVERSATION_ID, 
    IMPORTANT_BY_CONVERSATION_ID,
    MSGID
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<Record>::ArgObjType & argObj);

  DEFINE_SINGLE_EXECUTE_MOTHOD(UpdateRecordCommand, UpdateDuration, DURATION)
  DEFINE_SINGLE_EXECUTE_MOTHOD(UpdateRecordCommand, UpdateUnread, UNREAD)
  DEFINE_SINGLE_EXECUTE_MOTHOD(UpdateRecordCommand, UpdateImportant, IMPORTANT)
  DEFINE_SINGLE_EXECUTE_MOTHOD(UpdateRecordCommand, UpdateBody, BODY)
  DEFINE_SINGLE_EXECUTE_MOTHOD(UpdateRecordCommand, UpdateText, TEXT)
  DEFINE_SINGLE_EXECUTE_MOTHOD(UpdateRecordCommand, UpdateFlag, FLAG)

  DEFINE_SINGLE_EXECUTE_MOTHOD(UpdateRecordCommand, 
    UpdateUnreadByCvsId, UNREAD_BY_CONVERSATION_ID)
  DEFINE_SINGLE_EXECUTE_MOTHOD(UpdateRecordCommand, 
    UpdateImportantByCvsId, IMPORTANT_BY_CONVERSATION_ID)
  DEFINE_SINGLE_EXECUTE_MOTHOD(UpdateRecordCommand, 
    UpdateUTCDateTime, MSGID)
};

class   RemoveRecordCommand 
  : public DMLBase<Record>
{
public:
  RemoveRecordCommand(const std::string& _dbName = HISTORYDB_NAME) : DMLBase<Record>(_dbName) {}

public:
  static int RemoveAll();
  static int RemoveByRecordId(const DataRecordId & recordId);
  static int RemoveByRecordMsgID(const std::string & msgid);
  static int RemoveByRecordType(int recordType);
  static int RemoveByConversationId(const std::string & cvsId);
  static int RemoveHistoryChatRecords();
  static int RemoveHistoryChatRecordsByConversatoinIdAndDate(
    const std::string & cvsId, const std::string & date);
  static int RemoveHistoryChatRecordsByConversatoinId(const std::string & cvsId);

  static int RemoveHistoryCallRecords(const DQLBase<Record>::ArgObjType & argObj);
  static int RemoveRecordBeforeDate(const std::string& _beforeDate);

protected:
  enum
  {
    INVALID, 
    ALL, 
    RECORD_ID, 
    RECORD_MSG_ID, 
    RECORD_TYPE, 
    CONVERSATION_ID, 

    HISTORY_CHAT, 
    HISTORY_CHAT_BY_CONVERSATION_ID_AND_DATE, 

    HISTORY_CALL,
    HISTORY_CHAT_RECORD_BY_CONVERSATION_ID,
	HISTORY_BEFORE_DATE,
  };

private:
  void ComposeSQLHistoryCall(
    const DQLBase<Record>::ArgObjType & argObj, std::string & sql) const;

protected:
  virtual void ComposeSQL(
    const DQLBase<Record>::ArgObjType & argObj, std::string & sql);
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<Record>::ArgObjType & argObj);

};


class   RecordQuery : public DQLBase<Record>
{
  friend class AdvConversationQuery;

public:
  RecordQuery(const std::string& _dbName = HISTORYDB_NAME) : DQLBase<Record>(_dbName) {}

public:
  static bool QueryByRecordId(const DataRecordId & recordId, 
    DQLBase<Record>::ResObjType & resObj,const std::string& _dbName = HISTORYDB_NAME);
  static bool QueryByRecordMsgID(const std::string & msgid,
      DQLBase<Record>::ResObjType & resObj);
  static int QueryAllByRecordType(int recordType, 
    DQLBase<Record>::ResCtnType & resCtn);
  static int QueryAllByConversationId(const std::string & cvsId, 
    DQLBase<Record>::ResCtnType & resCtn);
  static int QueryAllByConversationIdAndRecordType(
    const std::string & cvsId, int recordType, 
    DQLBase<Record>::ResCtnType & resCtn);
  static int QueryChatConversationByConversationId(
    const std::string & cvsId, 
    DQLBase<Record>::ResCtnType & resCtn);
  static int QueryAllByConversationIdBetweenDate(const std::string & cvsId, 
    const std::string & beginDate, const std::string & endDate, 
    DQLBase<Record>::ResCtnType & resCtn);
  static int QueryChatByConversationIdBetweenDate(const std::string & cvsId, 
	  const std::string & beginDate, const std::string & endDate, 
	  DQLBase<Record>::ResCtnType & resCtn);
  static int QueryImportantByConversationId(const std::string & cvsId, 
    DQLBase<Record>::ResCtnType & resCtn);

  static bool QueryLastUnreadMissedCallByConversationId(
    const std::string & cvsId, 
    DQLBase<Record>::ResObjType & resObj);

  static int QueryUnreadAll(DQLBase<Record>::ResCtnType & resCtn);
  static int QueryUnreadAllExceptChatRecord(DQLBase<Record>::ResCtnType & resCtn);
  static int QueryUnreadCount();
  static int QueryConversationCountBetweenDate(
    const std::string & beginDate, const std::string & endDate);
  static int QueryUnreadCountByConversationId(const std::string & cvsId);
  static int QueryUnreadCallByConversationId(const std::string & cvsId);
  static int QueryImportantCountByConversationId(const std::string & cvsId);
  static int QueryRecordOffset(
	  const DataRecordId & recordId, const std::string & cvsId,const std::string& _dbName = HISTORYDB_NAME);

  static int QueryPreRecordsByRcdId(const std::string & cvsId, const DataRecordId rcdId, const int limitcount,
      DQLBase<Record>::ResCtnType & resCtn);

  static int QueryPreRecordsByUTCDateTime(const std::string & cvsId, const std::string strUTCDate, const std::string strUTCTime, const int limitcount,
      DQLBase<Record>::ResCtnType & resCtn);

  static int FilterRecords(const DQLBase<Record>::ArgObjType & argObj, 
	  DQLBase<Record>::ResCtnType & resCtn,const std::string& _dbName = HISTORYDB_NAME);
  static int FilterRecordsCount(const DQLBase<Record>::ArgObjType & argObj,const std::string& _dbName = HISTORYDB_NAME);
  static int QueryCountBeforeDate(const std::string& _lastDate,int& _recordCount);
  static int QueryConvIdBeforeDate(const std::string& _lastDate,std::set<std::string>& _lstConvID);
  static int QueryRecordByPageBeforeDate(const std::string& _date,unsigned int _pageNo,unsigned int _pageSize,
	  DQLBase<Record>::ResCtnType & resCtn);
  static int QueryRecordDateMin(std::string& _minDate);

  static bool QuerySMSRecordByContent(const std::string& content, const std::string& mobile, const int flag, DQLBase<Record>::ResObjType & resObj);

protected:
  enum
  {
    INVALID, 
    ALL, 
    RECORD_ID, 
    RECORD_MSG_ID,
    RECORD_TYPE, 
    ALL_BY_CONVERSATION_ID, 
    ALL_BY_CONVERSATION_ID_AND_RECORD_TYPE, 
    ALL_BY_CONVERSATION_ID_BETWEEN_DATE, 
    UNREAD_BY_CONVERSATION_ID, 
    IMPORTANT_BY_CONVERSATION_ID, 

    LAST_UNREAD_MISSED_CALL, 

    UNREAD_COUNT_BY_CONVERSATION_ID, 
    IMPORTANT_COUNT_BY_CONVERSATION_ID, 
    UNREAD_COUNT_ALL, 
    UNREAD_ALL,
    UNREAD_ALL_EXCEPT_CHATRECORD,
    CONVERSATION_COUNT_BETWEEN_DATE, 
    RECORD_OFFSET, 
    RECORD_OFFSET_BYUTC,

    FILTER, 
    FILTER_COUNT, 

    PRE_RECORD_BY_RECORD_ID,//根据记录id，向前查询指定个数的记录
    PRE_RECORD_BY_UTCDATETIME,//根据记录UTC时间，向前查询指定个数的记录
    CHAT_RECORD_BY_CONVERSATION_ID,
	UNREAD_CALL_BY_CONVERSATION_ID,
	RECORD_COUNT_BEFORE_DATE,
	RECORD_Page_BY_BEFORE_DEATE,
	RECORD_CVSID_BEFORE_DATE,
	RECORD_DATE_MIN,
	CHAT_RECORD_BY_CONVERSATION_ID_BETWEEN_DATE,
	RECORD_SMS_CONTENT
  };

private:
  void ComposeSQLFilter(
    const DQLBase<Record>::ArgObjType & argObj, std::string & sql) const;

  void ComposeSQLPreByUTCDateTimeQuery(
    const DQLBase<Record>::ArgObjType & argObj, std::string & sql) const;

  void ComposeSQLPreQuery(
    const DQLBase<Record>::ArgObjType & argObj, std::string & sql) const;

public:
  static void ComposeSQLCallTypeFilter(
    const DQLBase<Record>::ArgObjType & argObj, std::string & whereClause);
  static void BindCallTypeFilter(IDataManipulation * dm, 
    const DQLBase<Record>::ArgObjType & argObj, int & index);

protected:
  virtual void ComposeSQL(
    const DQLBase<Record>::ArgObjType & argObj, std::string & sql);
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DQLBase<Record>::ArgObjType & argObj);
  virtual void Extract(IDataManipulation * dm, 
    DQLBase<Record>::ResObjType & resObj);

  static int ExtractFromRecordTab(IDataManipulation * dm, 
    DQLBase<Record>::ResObjType & resObj, int startIndex);

};

    } // namespace history
  } // namespace ecsdata
} // namespace ecs
