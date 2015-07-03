#include "stdafx.h"
#include "data/model/history/Record.h"
#include "Log.h"

using namespace std;

namespace ecs {
  namespace ecsdata {
    namespace history {

///////////////////////////////////////////////////////////////////////////
void CreateRecordTabCommand::ComposeSQL(std::string & sql)
{
    sql = 
      "CREATE TABLE IF NOT EXISTS "RECORD_TAB
      "( RECORD_ID INTEGER PRIMARY KEY AUTOINCREMENT"
      ", RECORD_TYPE INTEGER NOT NULL"

      ", CONVERSATION_ID VARCHAR(128) NOT NULL"

      ", PEER_ID VARCHAR(128)"
      ", PEER_NAME VARCHAR(32)"
      ", SENT BOOLEAN NOT NULL"

      ", BEGINDATE DATE NOT NULL"
      ", BEGINTIME TIME NOT NULL"

      ", UTCDATE DATE"
      ", UTCTIME TIME"

      ", DURATION INTEGER NOT NULL DEFAULT(-1)"
      ", UNREAD BOOLEAN NOT NULL DEFAULT(0)"
      ", IMPORTANT BOOLEAN NOT NULL DEFAULT(0)"

      ", BODY VARCHAR(20480)"
      ", TEXT VARCHAR(10240)"

      ", FLAG INTEGER NOT NULL DEFAULT(0)"

      ", RESERVED_INT1 INTEGER NOT NULL DEFAULT(0)"
      ", RESERVED_INT2 INTEGER NOT NULL DEFAULT(0)"
      ", RESERVED_INT3 INTEGER NOT NULL DEFAULT(0)"
      ", RESERVED_STR1 VARCHAR(1024)"
      ", RESERVED_STR2 VARCHAR(1024)"
      ", RESERVED_STR3 VARCHAR(1024)"
      ");";
}

///////////////////////////////////////////////////////////////////////////

void CreateRecordTabConversationIDIndexCommand::ComposeSQL(std::string & sql)
{
    sql = 
        "CREATE INDEX IF NOT EXISTS RecordTab_INDEX_3 ON RecordTab (CONVERSATION_ID);";
}

void DeleteRecordTabUniqueIndexCommand::ComposeSQL(std::string & sql)
{
    sql = 
        "DROP INDEX IF EXISTS RecordTab_UNIQUE_INDEX;";
}

void CreateRecordTabUniqueIndexCommand::ComposeSQL(std::string & sql)
{
    sql = 
        "CREATE UNIQUE INDEX IF NOT EXISTS RecordTab_UNIQUE_INDEX ON RecordTab (RECORD_TYPE,CONVERSATION_ID\
		,PEER_ID,BEGINDATE,BEGINTIME,BODY,TEXT,RESERVED_STR2);";
}

void CreateRecordTabRecordTypeIndexCommand::ComposeSQL(std::string & sql)
{
    sql = 
        "CREATE INDEX IF NOT EXISTS RecordTab_INDEX_2 ON RecordTab (RECORD_TYPE);";
}

void CreateRecordTabMsgIdIndexCommand::ComposeSQL(std::string & sql)
{
	sql = 
		"CREATE INDEX IF NOT EXISTS RecordTab_INDEX_MsgId ON RecordTab (RESERVED_STR2);";
}

void AlterHistoryTabCommand::ComposeSQL(std::string & sql)
{
    sql = "ALTER TABLE " + tblName_ + " ADD COLUMN " + columnName_ + " " + newSql_+";";
}

int InsertRecordCommand::BatchInsert(const std::string& _dbName,const ArgCtnType& _resCtn)
{
	InsertRecordCommand cmd(_dbName);
	cmd.BatchExecute(0,_resCtn);
	return cmd.changed;
}

void InsertRecordCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "REPLACE INTO "RECORD_TAB
    "( RECORD_TYPE"

    ", CONVERSATION_ID"

    ", PEER_ID"
    ", PEER_NAME"
    ", SENT"

    ", BEGINDATE"
    ", BEGINTIME"

    ", UTCDATE"
    ", UTCTIME"

    ", DURATION"
    ", UNREAD"

    ", BODY"
    ", TEXT"

    ", FLAG"
    ", RESERVED_INT1"
    ", RESERVED_INT2"
    ", RESERVED_INT3"
    ", RESERVED_STR1"
    ", RESERVED_STR2"
    ", RESERVED_STR3"

    ") VALUES( ?, ?, ?, ?, ?, date(?), time(?), date(?), time(?), ?, ?, ?, ?"
    ", ?, ?, ?, ?, ?, ?, ? );";
}

void InsertRecordCommand::Bind(IDataManipulation * dm, 
  const DMLInsertBase<Record>::ArgObjType & argObj)
{
	INFO_LOG("argObj.recordType=%d, argObj.cvsId=%s,argObj.peerId=%s, argObj.peerName=%s, argObj.sent=%d"
		, argObj.recordType
		, argObj.cvsId.c_str()
		, argObj.peerId.c_str()
		, argObj.peerName.c_str()
		, argObj.sent);

  int i = 0;

  dm->Bind(++i, argObj.recordType);
  dm->Bind(++i, argObj.cvsId);
  dm->Bind(++i, argObj.peerId);
  dm->Bind(++i, argObj.peerName);
  dm->Bind(++i, argObj.sent);
  dm->Bind(++i, argObj.date);
  dm->Bind(++i, argObj.time);
  dm->Bind(++i, argObj.utcdate);
  dm->Bind(++i, argObj.utctime);
  dm->Bind(++i, argObj.duration);
  dm->Bind(++i, argObj.unread);
  dm->Bind(++i, argObj.body);
  dm->Bind(++i, argObj.text);
  dm->Bind(++i, argObj.flag);
  dm->Bind(++i, argObj.reservedInt1);
  dm->Bind(++i, argObj.reservedInt2);
  dm->Bind(++i, argObj.reservedInt3);
  dm->Bind(++i, argObj.reservedStr1);
  dm->Bind(++i, argObj.reservedStr2);
  dm->Bind(++i, argObj.reservedStr3);
}

///////////////////////////////////////////////////////////////////////////
void UpdateRecordCommand::ComposeSQL(std::string & sql)
{
  sql = "UPDATE "RECORD_TAB" SET ";
  
  switch (type_)
  {
  case DURATION:
    (void)sql.append("DURATION = ? ");
    break;
  case UNREAD:
  case UNREAD_BY_CONVERSATION_ID:
    (void)sql.append("UNREAD = ? ");
    break;
  case IMPORTANT:
  case IMPORTANT_BY_CONVERSATION_ID:
    (void)sql.append("IMPORTANT = ? ");
    break;
  case BODY:
    (void)sql.append("BODY = ? ");
    break;
  case TEXT:
    (void)sql.append("TEXT = ? ");
    break;
  case FLAG:
    (void)sql.append("FLAG = ? ");
    break;
  case MSGID:
    (void)sql.append("UTCDATE = ? , UTCTIME = ? , BEGINDATE = ? , BEGINTIME = ? , RESERVED_STR2 = ? ");
    break;     
  default:
    sql.clear();
    WARN_LOG("unknown type : %d" ,type_);
    return;
  }

  if(UNREAD_BY_CONVERSATION_ID == type_)
  {
      (void)sql.append("WHERE CONVERSATION_ID = ? AND UNREAD=1;");
  }
  else if (IMPORTANT_BY_CONVERSATION_ID == type_)
  {
    (void)sql.append("WHERE CONVERSATION_ID = ?;");
  }
  else if(MSGID == type_)
  {
    (void)sql.append("WHERE RESERVED_STR2 = ?;");
  }
  else
  {
    (void)sql.append("WHERE RECORD_ID = ?;");
  }
}

void UpdateRecordCommand::Bind(IDataManipulation * dm, 
                               const DMLBase<Record>::ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case DURATION:
    //INFO_PARAM2(argObj.recordId, argObj.duration);
    dm->Bind(++i, argObj.duration);
    break;
  case UNREAD:
  case UNREAD_BY_CONVERSATION_ID:
    //INFO_PARAM2(argObj.cvsId, argObj.unread);
    dm->Bind(++i, argObj.unread);
    break;
  case IMPORTANT:
  case IMPORTANT_BY_CONVERSATION_ID:
    //INFO_PARAM2(argObj.cvsId, argObj.important);
    dm->Bind(++i, argObj.important);
    break;
  case BODY:
    //INFO_PARAM1(argObj.recordId);
    dm->Bind(++i, argObj.body);
    break;
  case TEXT:
    //INFO_PARAM1(argObj.recordId);
    dm->Bind(++i, argObj.text);
    break;
  case FLAG:
    //INFO_PARAM2(argObj.recordId, argObj.flag);
    dm->Bind(++i, argObj.flag);
    break;
  case MSGID:
    //INFO_PARAM5(argObj.utcdate, argObj.utctime,argObj.date,argObj.time,argObj.tmpStr);
    dm->Bind(++i, argObj.utcdate);
    dm->Bind(++i, argObj.utctime);
    dm->Bind(++i, argObj.date);
    dm->Bind(++i, argObj.time);
    dm->Bind(++i, argObj.tmpStr);
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    return;
  }

  if (UNREAD_BY_CONVERSATION_ID == type_ 
    || IMPORTANT_BY_CONVERSATION_ID == type_)
  {
    dm->Bind(++i, argObj.cvsId);
  }
  else if(MSGID == type_)
  {
    dm->Bind(++i, argObj.reservedStr2);
  }
  else
  {
    dm->Bind(++i, argObj.recordId);
  }
}

//static 
bool UpdateRecordCommand::UpdateDurationByRecordId(
  const DataRecordId & recordId, int duration)
{
  //INFO_PARAM2(recordId, duration);

  Record argObj;
  argObj.recordId = recordId;
  argObj.duration = duration;

  int nChanged = UpdateRecordCommand::UpdateDuration(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged == 1;
}

//static 
bool UpdateRecordCommand::UpdateUnreadByRecordId(
  const DataRecordId & recordId, bool unrd)
{
  //INFO_PARAM2(recordId, unrd);

  Record argObj;
  argObj.recordId = recordId;
  argObj.unread = unrd;

  int nChanged = UpdateRecordCommand::UpdateUnread(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged == 1;
}

//static 
bool UpdateRecordCommand::UpdateImportantByRecordId(
  const DataRecordId & recordId, bool important)
{
  //INFO_PARAM2(recordId, important);

  Record argObj;
  argObj.recordId = recordId;
  argObj.important = important;

  int nChanged = UpdateRecordCommand::UpdateImportant(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged == 1;
}

//static 
bool UpdateRecordCommand::UpdateBodyByRecordId(
  const DataRecordId & recordId, const std::string & body)
{
  //INFO_PARAM2(recordId, body);

  Record argObj;
  argObj.recordId = recordId;
  argObj.body = body;

  int nChanged = UpdateRecordCommand::UpdateBody(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged == 1;
}

//static 
bool UpdateRecordCommand::UpdateTextByRecordId(
  const DataRecordId & recordId, const std::string & text)
{
  //INFO_PARAM1(recordId);

  Record argObj;
  argObj.recordId = recordId;
  argObj.text = text;

  int nChanged = UpdateRecordCommand::UpdateText(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged == 1;
}

//static 
bool UpdateRecordCommand::UpdateFlagByRecordId(
  const DataRecordId & recordId, int flag)
{
  //INFO_PARAM2(recordId, flag);

  Record argObj;
  argObj.recordId = recordId;
  argObj.flag = flag;

  int nChanged = UpdateRecordCommand::UpdateFlag(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged == 1;
}

//static 
int UpdateRecordCommand::UpdateUnreadByConversationId(
  const std::string & cvsId, int rd)
{
  //INFO_PARAM2(cvsId, rd);

  Record argObj;
  argObj.cvsId = cvsId;
  argObj.unread = rd;

  int nChanged = UpdateRecordCommand::UpdateUnreadByCvsId(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged;
}

//static 
int UpdateRecordCommand::UpdateImportantByConversationId(
  const std::string & cvsId, int important)
{
  //INFO_PARAM2(cvsId, important);

  Record argObj;
  argObj.cvsId = cvsId;
  argObj.important = important;

  int nChanged = UpdateRecordCommand::UpdateImportantByCvsId(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged;
}

//static
int UpdateRecordCommand::UpdateUTCDateTimeByMsgId(
      const std::string & msgid, const std::string & serverid, const std::string & utcdate, const std::string & utctime)
{

  Record argObj;
  argObj.reservedStr2 = msgid;
  argObj.utcdate = utcdate;
  argObj.utctime = utctime;
  eSDKTool::UTCTime2LocalTime(utcdate, utctime, argObj.date, argObj.time);
  argObj.tmpStr = serverid;
  int nChanged = UpdateRecordCommand::UpdateUTCDateTime(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged;
}
///////////////////////////////////////////////////////////////////////////
void RemoveRecordCommand::ComposeSQL(
  const DQLBase<Record>::ArgObjType & argObj, std::string & sql)
{
  switch (type_)
  {
  case HISTORY_CALL:
    ComposeSQLHistoryCall(argObj, sql);
    break;
  default:
    ComposeSQL(sql);
  }
}

void RemoveRecordCommand::ComposeSQL(std::string & sql)
{
  const std::string DELETE_RECORD = "DELETE FROM "RECORD_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case RECORD_ID:
    (void)whereClause.append("RECORD_ID = ?");
    break;
  case RECORD_MSG_ID:
    (void)whereClause.append("RESERVED_STR2 = ?");
    break;
  case RECORD_TYPE:
    (void)whereClause.append("RECORD_TYPE = ?");
    break;
  case CONVERSATION_ID:
    (void)whereClause.append("CONVERSATION_ID = ?");
    break;
  case HISTORY_CHAT:
    (void)whereClause.append("RECORD_TYPE "RECORD_TYPE_FILTER_HISTORY_CHAT);
    break;
  case HISTORY_CHAT_BY_CONVERSATION_ID_AND_DATE:
    (void)whereClause.append("CONVERSATION_ID = ? AND ");
    (void)whereClause.append("BEGINDATE = date(?) AND ");
    (void)whereClause.append("RECORD_TYPE "RECORD_TYPE_FILTER_HISTORY_CHAT);
    break;
  case HISTORY_CHAT_RECORD_BY_CONVERSATION_ID:
    (void)whereClause.append("CONVERSATION_ID = ? AND ");
    (void)whereClause.append("RECORD_TYPE "RECORD_TYPE_FILTER_HISTORY_CHAT "OR RECORD_TYPE "RECORD_TYPE_FILTER_HISTORY_UMMSG);
    break;
  case HISTORY_BEFORE_DATE:
	(void)whereClause.append("BEGINDATE < DATE(?)");
	break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    sql = "";
    return;
  }

  sql = DELETE_RECORD + whereClause + ";";
}

void RemoveRecordCommand::ComposeSQLHistoryCall(
  const DQLBase<Record>::ArgObjType & argObj, std::string & sql) const
{
  const std::string DELETE_RECORD = "DELETE FROM "RECORD_TAB;

  std::string whereClause = " WHERE ";
  (void)whereClause.append("RECORD_TYPE "RECORD_TYPE_FILTER_HISTORY_CALL);
  RecordQuery::ComposeSQLCallTypeFilter(argObj, whereClause);

  sql = DELETE_RECORD + whereClause + ";";
}

void RemoveRecordCommand::Bind(IDataManipulation * dm, 
                               const DMLBase<Record>::ArgObjType & argObj)
{
  int i = 0;

  switch (type_)
  {
  case ALL:
    break;
  case RECORD_ID:
    dm->Bind(++i, argObj.recordId);
    break;
  case RECORD_MSG_ID:
    dm->Bind(++i, argObj.reservedStr2);
    break;
  case RECORD_TYPE:
    dm->Bind(++i, argObj.recordType);
    break;
  case CONVERSATION_ID:
    dm->Bind(++i, argObj.cvsId);
    break;
  case HISTORY_CHAT:
    break;
  case HISTORY_CHAT_BY_CONVERSATION_ID_AND_DATE:
    dm->Bind(++i, argObj.cvsId);
    dm->Bind(++i, argObj.date);
    break;
  case HISTORY_CHAT_RECORD_BY_CONVERSATION_ID:
    dm->Bind(++i, argObj.cvsId);
    break;
  case HISTORY_CALL:
    RecordQuery::BindCallTypeFilter(dm, argObj, i);
    break;
  case HISTORY_BEFORE_DATE:
	dm->Bind(++i, argObj.date);
	break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    break;
  }
}

//static 
int RemoveRecordCommand::RemoveAll()
{
  //TRACE_FUNC();

  Record argObj;

  RemoveRecordCommand cmd;
  cmd.SingleExecute(ALL, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed;
}

//static 
int RemoveRecordCommand::RemoveByRecordId(const DataRecordId & recordId)
{
  //TRACE_FUNC1(recordId);

  Record argObj;
  argObj.recordId = recordId;

  RemoveRecordCommand cmd;
  cmd.SingleExecute(RECORD_ID, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed;
}

//static
int RemoveRecordCommand::RemoveByRecordMsgID(const std::string & msgid)
{
    //TRACE_FUNC1(msgid);

    Record argObj;
    argObj.reservedStr2 = msgid;

    RemoveRecordCommand cmd;
    cmd.SingleExecute(RECORD_MSG_ID, argObj);

    //INFO_PARAM1(cmd.changed);
    return cmd.changed;
}

//static 
int RemoveRecordCommand::RemoveByRecordType(int recordType)
{
  //TRACE_FUNC1(recordType);

  Record argObj;
  argObj.recordType = recordType;

  RemoveRecordCommand cmd;
  cmd.SingleExecute(RECORD_TYPE, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed;
}

//static 
int RemoveRecordCommand::RemoveByConversationId(const std::string & cvsId)
{
  //TRACE_FUNC1(cvsId);

  Record argObj;
  argObj.cvsId = cvsId;

  RemoveRecordCommand cmd;
  cmd.SingleExecute(CONVERSATION_ID, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed;
}

//static 
int RemoveRecordCommand::RemoveHistoryChatRecords()
{
  //TRACE_FUNC();

  Record argObj;

  RemoveRecordCommand cmd;
  cmd.SingleExecute(HISTORY_CHAT, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed;
}

//static 
int RemoveRecordCommand::RemoveHistoryChatRecordsByConversatoinIdAndDate(
  const std::string & cvsId, const std::string & date)
{
  //TRACE_FUNC2(cvsId, date);

  Record argObj;
  argObj.cvsId = cvsId;
  argObj.date = date;

  RemoveRecordCommand cmd;
  cmd.SingleExecute(HISTORY_CHAT_BY_CONVERSATION_ID_AND_DATE, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed;
}

int RemoveRecordCommand::RemoveHistoryChatRecordsByConversatoinId(const std::string & cvsId)
{
  //TRACE_FUNC();

  Record argObj;
  argObj.cvsId = cvsId;

  RemoveRecordCommand cmd;
  cmd.SingleExecute(HISTORY_CHAT_RECORD_BY_CONVERSATION_ID, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed;
}

//static 
int RemoveRecordCommand::RemoveHistoryCallRecords(
  const DQLBase<Record>::ArgObjType & argObj)
{
  RemoveRecordCommand cmd;
  cmd.SingleExecute(HISTORY_CALL, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed;
}

int RemoveRecordCommand::RemoveRecordBeforeDate(const std::string& _beforeDate)
{
	RemoveRecordCommand cmd;
	Record argObj;
	argObj.date = _beforeDate;
	cmd.SingleExecute(HISTORY_BEFORE_DATE, argObj);

	//INFO_PARAM1(cmd.changed);
	return cmd.changed;
}

///////////////////////////////////////////////////////////////////////////
void RecordQuery::ComposeSQL(
  const DQLBase<Record>::ArgObjType & argObj, std::string & sql)
{
  switch (type_)
  {
  case FILTER:
  case FILTER_COUNT:
    ComposeSQLFilter(argObj, sql);
    break;
  case PRE_RECORD_BY_RECORD_ID:
    ComposeSQLPreQuery(argObj, sql);
    break;
  case PRE_RECORD_BY_UTCDATETIME:
    ComposeSQLPreByUTCDateTimeQuery(argObj, sql);
    break;
  default:
    ComposeSQL(sql);
  }
}

void RecordQuery::ComposeSQL(std::string & sql)
{
  const std::string QUERY_RECORD = 
    "SELECT RECORD_ID,RECORD_TYPE,CONVERSATION_ID,PEER_ID,PEER_NAME,SENT,BEGINDATE,BEGINTIME,UTCDATE,UTCTIME,DURATION,UNREAD,IMPORTANT,BODY,TEXT\
	,FLAG,RESERVED_INT1,RESERVED_INT2,RESERVED_INT3,RESERVED_STR1,RESERVED_STR2,RESERVED_STR3 FROM "RECORD_TAB;
  const std::string QUERY_RECORD_COUNT = 
    "SELECT COUNT(*) FROM "RECORD_TAB;
  const std::string QUERY_UNREAD_COUNT = 
    "SELECT SUM(UNREAD) FROM "RECORD_TAB;
  const std::string QUERY_IMPORTANT_COUNT = 
    "SELECT SUM(IMPORTANT) FROM "RECORD_TAB;
  const std::string QUERY_RECORD_COUNT_DISTINCT_CONVERSATION_ID = 
    "SELECT COUNT(DISTINCT CONVERSATION_ID) FROM "RECORD_TAB;
  sql = QUERY_RECORD;
  std::string whereClause = " WHERE ";

  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case UNREAD_COUNT_ALL:
      sql = QUERY_UNREAD_COUNT;
      whereClause = "";
      break;
  case RECORD_ID:
    (void)whereClause.append("RECORD_ID = ?");
    break;
  case RECORD_MSG_ID:
    (void)whereClause.append("RESERVED_STR2 = ?");
    break;
  case RECORD_TYPE:
    (void)whereClause.append("RECORD_TYPE = ?");
    break;
  case ALL_BY_CONVERSATION_ID:
    (void)whereClause.append("(CONVERSATION_ID = ? OR CONVERSATION_ID = ?) ORDER BY UTCDATE ASC,UTCTIME ASC,BEGINDATE ASC,BEGINTIME ASC,RESERVED_STR2 ASC");
    break;
  case ALL_BY_CONVERSATION_ID_AND_RECORD_TYPE:
    (void)whereClause.append("(CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND RECORD_TYPE = ?");
    break;
  case CHAT_RECORD_BY_CONVERSATION_ID:
    (void)whereClause.append("(CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND RECORD_TYPE <= 8");
    break;
  case ALL_BY_CONVERSATION_ID_BETWEEN_DATE:
    (void)whereClause.append(
      "((CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND (BEGINDATE BETWEEN date(?) AND date(?))) ORDER BY UTCDATE ASC,UTCTIME ASC,BEGINDATE ASC,BEGINTIME ASC,RESERVED_STR2 ASC");
    break;
  case CHAT_RECORD_BY_CONVERSATION_ID_BETWEEN_DATE:
	 (void)whereClause.append(
		  "(CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND (BEGINDATE BETWEEN date(?) AND date(?)) AND (RECORD_TYPE <= 8)");
	  break;
  case LAST_UNREAD_MISSED_CALL:
    (void)whereClause.append(
		"(CONVERSATION_ID = ? OR CONVERSATION_ID = ?)"
      "AND (RECORD_TYPE"RECORD_TYPE_FILTER_HISTORY_CALL
      "OR RECORD_TYPE"RECORD_TYPE_FILTER_HISTORY_MEETING") "
      "AND UNREAD = 1 AND DURATION = -1");
    break;
  case UNREAD_BY_CONVERSATION_ID:
    (void)whereClause.append("(CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND UNREAD = 1");
    break;
  case UNREAD_CALL_BY_CONVERSATION_ID:
    sql = QUERY_UNREAD_COUNT;
    (void)whereClause.append("(CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND RECORD_TYPE = 10 AND UNREAD = 1");
    break;
  case IMPORTANT_BY_CONVERSATION_ID:
    (void)whereClause.append("(CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND IMPORTANT = 1");
    break;
  case UNREAD_COUNT_BY_CONVERSATION_ID:
  case IMPORTANT_COUNT_BY_CONVERSATION_ID:
    sql = UNREAD_COUNT_BY_CONVERSATION_ID == type_ 
      ? QUERY_UNREAD_COUNT : QUERY_IMPORTANT_COUNT;
    (void)whereClause.append("(CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND RECORD_TYPE != 10");
    break;
  case CONVERSATION_COUNT_BETWEEN_DATE:
    sql = QUERY_RECORD_COUNT_DISTINCT_CONVERSATION_ID;
    (void)whereClause.append(
      "BEGINDATE BETWEEN date(?) AND date(?)");
    break;
  case RECORD_OFFSET:
    sql = QUERY_RECORD_COUNT;
    (void)whereClause.append(
    //  "RECORD_ID <= ? AND (CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND RECORD_TYPE ");
        "(BEGINDATE < date(?) OR  (BEGINDATE = date(?) AND BEGINTIME < time(?))) AND (CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND RECORD_TYPE ");
    (void)whereClause.append(RECORD_TYPE_FILTER_HISTORY_SMS_CHAT_FILE_RECORDINGCHAT);
    break;
  case RECORD_OFFSET_BYUTC:
    sql = QUERY_RECORD_COUNT;
    (void)whereClause.append(
    //  "RECORD_ID <= ? AND (CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND RECORD_TYPE ");
        "(UTCDATE < date(?) OR  (UTCDATE = date(?) AND UTCTIME < time(?))) AND (CONVERSATION_ID = ? OR CONVERSATION_ID = ?) AND RECORD_TYPE ");
    (void)whereClause.append(RECORD_TYPE_FILTER_HISTORY_SMS_CHAT_FILE_RECORDINGCHAT);
    break;
  case UNREAD_ALL:
      sql = QUERY_RECORD;
      (void)whereClause.append("UNREAD != 0");
      break;
  case UNREAD_ALL_EXCEPT_CHATRECORD:
      sql = QUERY_RECORD;
      (void)whereClause.append("UNREAD != 0 AND RECORD_TYPE NOT IN (0,8)");
      break;
  case RECORD_COUNT_BEFORE_DATE:
	  sql = "SELECT COUNT(*) FROM RECORDTAB WHERE BEGINDATE < DATE(?)";
	  return;
  case RECORD_CVSID_BEFORE_DATE:
	  sql = "SELECT DISTINCT CONVERSATION_ID FROM RECORDTAB WHERE BEGINDATE < DATE(?)";
	  return;
  case RECORD_Page_BY_BEFORE_DEATE:
	  sql = QUERY_RECORD;
	  (void)whereClause.append("BEGINDATE < DATE(?) ORDER BY BEGINDATE ASC LIMIT ? OFFSET ?");
	  break;
  case RECORD_DATE_MIN:
	  sql = "SELECT MIN(BEGINDATE) FROM RECORDTAB";
	  return;

  case RECORD_SMS_CONTENT:
	  sql = QUERY_RECORD;
	  (void)whereClause.append("TEXT LIKE ? AND PEER_ID LIKE ? AND FLAG = ?");
	  break;

  default:
    WARN_LOG("unknown type : %d" ,type_);
    sql = "";
    return;
  }

  (void)sql.append(whereClause).append(";");
}

void RecordQuery::ComposeSQLPreByUTCDateTimeQuery(const DQLBase<Record>::ArgObjType & argObj, std::string & sql) const
{
    const std::string QUERY_RECORD = "SELECT RECORD_ID,RECORD_TYPE,CONVERSATION_ID,PEER_ID,PEER_NAME,SENT,BEGINDATE,BEGINTIME,UTCDATE,UTCTIME,DURATION,UNREAD,IMPORTANT,BODY,TEXT\
	,FLAG,RESERVED_INT1,RESERVED_INT2,RESERVED_INT3,RESERVED_STR1,RESERVED_STR2,RESERVED_STR3  FROM "RECORD_TAB;

    std::string whereClause = " WHERE ";

    sql = QUERY_RECORD;
    (void)whereClause.append("(CONVERSATION_ID = ? OR CONVERSATION_ID = ?)");
    if (!argObj.utcdate.empty() && !argObj.utctime.empty())//recordId??1时，查询所??
    {
        (void)whereClause.append(" AND (UTCDATE < date(?) OR  (UTCDATE = date(?) AND UTCTIME < time(?))) ");
    }

    if (argObj.important)//limitcount大于0
    {
        (void)whereClause.append("ORDER BY UTCDATE DESC,UTCTIME DESC,RESERVED_STR2 DESC LIMIT ?");
    }

    (void)sql.append(whereClause).append(";");
}

void RecordQuery::ComposeSQLPreQuery(const DQLBase<Record>::ArgObjType & argObj, std::string & sql) const
{
    const std::string QUERY_RECORD = "SELECT RECORD_ID,RECORD_TYPE,CONVERSATION_ID,PEER_ID,PEER_NAME,SENT,BEGINDATE,BEGINTIME,UTCDATE,UTCTIME,DURATION,UNREAD,IMPORTANT,BODY,TEXT\
	,FLAG,RESERVED_INT1,RESERVED_INT2,RESERVED_INT3,RESERVED_STR1,RESERVED_STR2,RESERVED_STR3  FROM "RECORD_TAB;

    std::string whereClause = " WHERE ";

    //组合查询条件
    //select * from RecordTab where CONVERSATION_ID = ? AND RECORD_ID < ?
    //ORDER BY RECORD_ID DESC LIMIT ?;
    sql = QUERY_RECORD;
    (void)whereClause.append("(CONVERSATION_ID = ? OR CONVERSATION_ID = ?)");
    if (argObj.recordId > 0)//recordId??1时，查询所??
    {
        (void)whereClause.append(" AND RECORD_ID < ?");
    }

    if (argObj.important)//limitcount大于0
    {
        (void)whereClause.append("ORDER BY RECORD_ID DESC LIMIT ?");
    }

    (void)sql.append(whereClause).append(";");
}

void RecordQuery::ComposeSQLFilter(
  const DQLBase<Record>::ArgObjType & argObj, std::string & sql) const
{
  const std::string FILTER_MAIN = 
    "SELECT RECORD_ID,RECORD_TYPE,CONVERSATION_ID,PEER_ID,PEER_NAME,SENT,BEGINDATE,BEGINTIME,UTCDATE,UTCTIME,DURATION,UNREAD,IMPORTANT,BODY,TEXT\
	,FLAG,RESERVED_INT1,RESERVED_INT2,RESERVED_INT3,RESERVED_STR1,RESERVED_STR2,RESERVED_STR3 FROM "RECORD_TAB;
  const std::string FILTER_COUNT_MAIN = 
    "SELECT COUNT(*) FROM "RECORD_TAB;

  // 查询主句
  sql = (type_ == FILTER ? FILTER_MAIN : FILTER_COUNT_MAIN);

  // where子句
  std::string whereClause = " WHERE RECORD_TYPE ";
  if (argObj.recordType == RECORD_TYPE_FILTER_CHAT_SMS_FILE)
  {
    //whereClause.append(RECORD_TYPE_FILTER_HISTORY_CHAT).append(" ");
    (void)whereClause.append(RECORD_TYPE_FILTER_HISTORY_SMS_CHAT_FILE_RECORDINGCHAT).append(" ");
  }
  else
  {
	char strFormat[10] = {0};
	sprintf_s(strFormat,9,"= %d",argObj.recordType);
    (void)whereClause.append(strFormat).append(" ");
  }

  if (!argObj.cvsId.empty())
  {
    (void)whereClause.append("AND (CONVERSATION_ID = ? ");
	if(!argObj.oldCvsId.empty())
	{
	    (void)whereClause.append("OR CONVERSATION_ID = ? ");
	}
	(void)whereClause.append(")");
  }

  if (!argObj.text.empty())
  {
    (void)whereClause.append("AND ((TEXT LIKE ? ");
	(void)whereClause.append("AND RECORD_TYPE"RECORD_TYPE_FILTER_HISTORY_NOT_FILE")");
	(void)whereClause.append(" OR (PEER_NAME LIKE ? ");
    (void)whereClause.append("AND RECORD_TYPE"RECORD_TYPE_FILTER_HISTORY_NOT_FILE")");
    (void)whereClause.append(" OR (RESERVED_STR1 LIKE ?");
    (void)whereClause.append("AND RECORD_TYPE"RECORD_TYPE_FILTER_HISTORY_FILE"))");
  }

  if (!argObj.date.empty() && !argObj.time.empty())
  {
    (void)whereClause.append("AND (BEGINDATE BETWEEN date(?) AND date(?)) ");
  }

  ComposeSQLCallTypeFilter(argObj, whereClause);

  (void)sql.append(whereClause);

  if(argObj.reservedInt1 < 0)
  {
    (void)sql.append("ORDER BY RECORD_ID DESC ");
  }

  (void)sql.append("ORDER BY UTCDATE,UTCTIME,BEGINDATE,BEGINTIME,RESERVED_STR2").append(" ");
  // 查询限定
  if (argObj.important > 0)
  {
    (void)sql.append("LIMIT ? ");
  }
    
  if (argObj.unread >= 0)
  {
    (void)sql.append("OFFSET ? ");
  }

  DEBUG_LOG("sql=%s",sql.c_str());
}

//static 
void RecordQuery::ComposeSQLCallTypeFilter(
  const DQLBase<Record>::ArgObjType & argObj, std::string & whereClause)
{
  if (argObj.sent == 0 || argObj.sent == 1)
  {
    (void)whereClause.append("AND SENT = ? ");
  }

  if (argObj.duration < 0)
  {
    (void)whereClause.append("AND DURATION < 0 ");
  }
  else if (argObj.duration > 0)
  {
    (void)whereClause.append("AND DURATION >= 0 ");
  }
  else
  {
      // do nothing
  }
}

//static 
void RecordQuery::BindCallTypeFilter(IDataManipulation * dm, 
  const DQLBase<Record>::ArgObjType & argObj, int & index)
{
  if (argObj.sent == 0 || argObj.sent == 1)
  {
    dm->Bind(++index, argObj.sent);
  }
}

void RecordQuery::Bind(IDataManipulation * dm, 
                       const DQLBase<Record>::ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case UNREAD_ALL:
      break;
  case UNREAD_ALL_EXCEPT_CHATRECORD:
      break;
  case RECORD_ID:
    ////INFO_PARAM1(argObj.recordId);
    dm->Bind(++i, argObj.recordId);
    break;
  case RECORD_TYPE:
    ////INFO_PARAM1(argObj.recordType);
    dm->Bind(++i, argObj.recordType);
    break;
  case RECORD_MSG_ID:
    dm->Bind(++i, argObj.reservedStr2);
    break;
  case ALL_BY_CONVERSATION_ID:
    ////INFO_PARAM1(argObj.cvsId);
    dm->Bind(++i, argObj.cvsId);
	dm->Bind(++i, argObj.oldCvsId);
    break;
  case ALL_BY_CONVERSATION_ID_AND_RECORD_TYPE:
    ////INFO_PARAM2(argObj.cvsId, argObj.recordType);
    dm->Bind(++i, argObj.cvsId);
	dm->Bind(++i, argObj.oldCvsId);
    dm->Bind(++i, argObj.recordType);
    break;
  case CHAT_RECORD_BY_CONVERSATION_ID:
    dm->Bind(++i, argObj.cvsId);
	dm->Bind(++i, argObj.oldCvsId);
    break;
  case ALL_BY_CONVERSATION_ID_BETWEEN_DATE:
    ////INFO_PARAM3(argObj.cvsId, argObj.date, argObj.time);
    dm->Bind(++i, argObj.cvsId);
	dm->Bind(++i, argObj.oldCvsId);
    dm->Bind(++i, argObj.date); // use date field as beginDate
    dm->Bind(++i, argObj.time); // use time field as endDate
    break;
  case CHAT_RECORD_BY_CONVERSATION_ID_BETWEEN_DATE:
    dm->Bind(++i, argObj.cvsId);
	dm->Bind(++i, argObj.oldCvsId);
	dm->Bind(++i, argObj.date); // use date field as beginDate
	dm->Bind(++i, argObj.time); // use time field as endDate
	break;
  case LAST_UNREAD_MISSED_CALL:
    ////INFO_PARAM1(argObj.cvsId);
    dm->Bind(++i, argObj.cvsId);
	dm->Bind(++i, argObj.oldCvsId);
    break;
  case UNREAD_COUNT_ALL:
    break;
  case UNREAD_COUNT_BY_CONVERSATION_ID:
    ////INFO_PARAM1(argObj.cvsId);
    dm->Bind(++i, argObj.cvsId);
	dm->Bind(++i, argObj.oldCvsId);
    break;
  case UNREAD_CALL_BY_CONVERSATION_ID:
	dm->Bind(++i, argObj.cvsId);
	dm->Bind(++i, argObj.oldCvsId);
	break;
  case IMPORTANT_COUNT_BY_CONVERSATION_ID:
    ////INFO_PARAM1(argObj.cvsId);
    dm->Bind(++i, argObj.cvsId);
	dm->Bind(++i, argObj.oldCvsId);
    break;
  case CONVERSATION_COUNT_BETWEEN_DATE:
    ////INFO_PARAM2(argObj.date, argObj.time);
    dm->Bind(++i, argObj.date); // use date field as beginDate
    dm->Bind(++i, argObj.time); // use time field as endDate
    break;
  case RECORD_OFFSET:
    dm->Bind(++i, argObj.date);
    dm->Bind(++i, argObj.date);
    dm->Bind(++i, argObj.time);
    dm->Bind(++i, argObj.cvsId);
	dm->Bind(++i, argObj.oldCvsId);
    break;
  case RECORD_OFFSET_BYUTC:
    dm->Bind(++i, argObj.utcdate);
    dm->Bind(++i, argObj.utcdate);
    dm->Bind(++i, argObj.utctime);
    dm->Bind(++i, argObj.cvsId);
	dm->Bind(++i, argObj.oldCvsId);
    break;
  case FILTER:
  case FILTER_COUNT:
    if (!argObj.cvsId.empty())
    {
        dm->Bind(++i, argObj.cvsId);
	    if(!argObj.oldCvsId.empty())
        {
	        dm->Bind(++i, argObj.oldCvsId);
        }
    }
    if (!argObj.text.empty())
    {
      dm->Bind(++i, "%" + argObj.text + "%");
	  dm->Bind(++i, "%" + argObj.text + "%");
      dm->Bind(++i, "%" + argObj.text + "%");//用以根据保留字段搜索文件名称
    }
    if (!argObj.date.empty() && !argObj.time.empty())
    {
      dm->Bind(++i, argObj.date);
      dm->Bind(++i, argObj.time);
    }
    BindCallTypeFilter(dm, argObj, i);
    if (argObj.important > 0)
    {
      dm->Bind(++i, argObj.important);
    }
    if (argObj.unread >= 0)
    {
      dm->Bind(++i, argObj.unread);
    }
    break;
  case PRE_RECORD_BY_RECORD_ID:
      if (!argObj.cvsId.empty())
      {
          dm->Bind(++i, argObj.cvsId);
		  dm->Bind(++i, argObj.oldCvsId);
      }
      if (argObj.recordId > 0)
      {
          dm->Bind(++i, argObj.recordId);
      }
      if (argObj.important > 0)//limitcount大于0
      {
          dm->Bind(++i, argObj.important);
      }
      break;
  case PRE_RECORD_BY_UTCDATETIME:
      if (!argObj.cvsId.empty())
      {
          dm->Bind(++i, argObj.cvsId);
		  dm->Bind(++i, argObj.oldCvsId);
      }
      if (!argObj.utcdate.empty() && !argObj.utctime.empty())
      {
          dm->Bind(++i, argObj.utcdate);
          dm->Bind(++i, argObj.utcdate);
          dm->Bind(++i, argObj.utctime);
      }
      if (argObj.important > 0)//limitcount大于0
      {
          dm->Bind(++i, argObj.important);
      }
      break;
  case RECORD_COUNT_BEFORE_DATE:
	  dm->Bind(++i,argObj.date);
	  break;
  case RECORD_CVSID_BEFORE_DATE:
	  dm->Bind(++i,argObj.date);
	  break;
  case RECORD_Page_BY_BEFORE_DEATE:
	  dm->Bind(++i,argObj.date);
	  dm->Bind(++i,argObj.reservedInt1);
	  dm->Bind(++i,argObj.reservedInt2);
	  break;
  case RECORD_SMS_CONTENT:
	  dm->Bind(++i, "%" + argObj.text + "%");
	  dm->Bind(++i, "%" + argObj.peerId + "%");
	  dm->Bind(++i,argObj.flag);
	  break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    break;
  }
}

void RecordQuery::Extract(IDataManipulation * dm, 
  DQLBase<Record>::ResObjType & resObj)
{
  switch (type_)
  {
  case UNREAD_COUNT_ALL:
  case UNREAD_COUNT_BY_CONVERSATION_ID:
    dm->GetValue(0, resObj.unread);
    break;
  case UNREAD_CALL_BY_CONVERSATION_ID:
    dm->GetValue(0, resObj.unreadCall);
	break;
  case IMPORTANT_COUNT_BY_CONVERSATION_ID:
    dm->GetValue(0, resObj.important);
    break;
  case CONVERSATION_COUNT_BETWEEN_DATE:
  case RECORD_OFFSET:
  case FILTER_COUNT:
    dm->GetValue(0, resObj.recordId);
    break;
  case RECORD_COUNT_BEFORE_DATE:
	  dm->GetValue(0,resObj.reservedInt1);
	break;
  case RECORD_CVSID_BEFORE_DATE:
	  dm->GetValue(0,resObj.cvsId);
	break;
  case RECORD_DATE_MIN:
	  dm->GetValue(0,resObj.date);
	break;
  default:
    (void)ExtractFromRecordTab(dm, resObj, 0);
    break;
  }
}

//static 
int RecordQuery::ExtractFromRecordTab(IDataManipulation * dm, 
  DQLBase<Record>::ResObjType & resObj, int startIndex)
{
  int i = 0;

  dm->GetValue(startIndex + i++, resObj.recordId);
  dm->GetValue(startIndex + i++, resObj.recordType);
  dm->GetValue(startIndex + i++, resObj.cvsId);
  dm->GetValue(startIndex + i++, resObj.peerId);
  dm->GetValue(startIndex + i++, resObj.peerName);
  dm->GetValue(startIndex + i++, resObj.sent);
  dm->GetValue(startIndex + i++, resObj.date);
  dm->GetValue(startIndex + i++, resObj.time);
  dm->GetValue(startIndex + i++, resObj.utcdate);
  dm->GetValue(startIndex + i++, resObj.utctime);
  dm->GetValue(startIndex + i++, resObj.duration);
  dm->GetValue(startIndex + i++, resObj.unread);
  dm->GetValue(startIndex + i++, resObj.important);
  dm->GetValue(startIndex + i++, resObj.body);
  dm->GetValue(startIndex + i++, resObj.text);
  dm->GetValue(startIndex + i++, resObj.flag);
  dm->GetValue(startIndex + i++, resObj.reservedInt1);
  dm->GetValue(startIndex + i++, resObj.reservedInt2);
  dm->GetValue(startIndex + i++, resObj.reservedInt3);
  dm->GetValue(startIndex + i++, resObj.reservedStr1);
  dm->GetValue(startIndex + i++, resObj.reservedStr2);
  dm->GetValue(startIndex + i++, resObj.reservedStr3);

  return i;
}

//static 
bool RecordQuery::QueryByRecordId(const DataRecordId & recordId, 
                                  DQLBase<Record>::ResObjType & resObj,const std::string& _dbName)
{
  Record argObj;
  argObj.recordId = recordId;

  RecordQuery qry(_dbName);
  bool ret = qry.SingleExecute(RECORD_ID, argObj, resObj);

  DEBUG_LOG("recordId=%d, qry.count=%d",recordId, qry.count);
  return ret;
}

//static
bool RecordQuery::QueryByRecordMsgID(const std::string & msgid, 
                                     DQLBase<Record>::ResObjType & resObj)
{
    Record argObj;
    argObj.reservedStr2 = msgid;

    RecordQuery qry;
    bool ret = qry.SingleExecute(RECORD_MSG_ID, argObj, resObj);

    //INFO_PARAM2(msgid, qry.count);
    return ret;
}

//static 
int RecordQuery::QueryAllByRecordType(int recordType, 
                                      DQLBase<Record>::ResCtnType & resCtn)
{
  Record argObj;
  argObj.recordType = recordType;

  RecordQuery qry;
  qry.BatchExecute(RECORD_TYPE, argObj, resCtn);

  DEBUG_LOG("recordType=%d, qry.count=%d",recordType, qry.count);
  return qry.count;
}

//static 
int RecordQuery::QueryAllByConversationId(const std::string & cvsId, 
                                          DQLBase<Record>::ResCtnType & resCtn)
{
  Record argObj;
  argObj.cvsId = cvsId;

  RecordQuery qry;
  qry.BatchExecute(ALL_BY_CONVERSATION_ID, argObj, resCtn);

  DEBUG_LOG("cvsId=%s, qry.count=%d",cvsId.c_str(), qry.count);
  return qry.count;
}

//static 
int RecordQuery::QueryAllByConversationIdAndRecordType(
  const std::string & cvsId, int recordType, 
  DQLBase<Record>::ResCtnType & resCtn)
{
  Record argObj;
  argObj.cvsId = cvsId;
  argObj.recordType = recordType;

  RecordQuery qry;
  qry.BatchExecute(ALL_BY_CONVERSATION_ID_AND_RECORD_TYPE, argObj, resCtn);

  DEBUG_LOG("cvsId=%s, recordType=%d, qry.count=%d",cvsId.c_str(), recordType, qry.count);
  return qry.count;
}

int RecordQuery::QueryChatConversationByConversationId(
  const std::string & cvsId, 
  DQLBase<Record>::ResCtnType & resCtn)
{
  Record argObj;
  argObj.cvsId = cvsId;

  RecordQuery qry;
  qry.BatchExecute(CHAT_RECORD_BY_CONVERSATION_ID, argObj, resCtn);

  DEBUG_LOG("cvsId=%s, qry.count=%d",cvsId.c_str(), qry.count);
  return qry.count;
}

//static 
int RecordQuery::QueryAllByConversationIdBetweenDate(const std::string & cvsId, 
  const std::string & beginDate, const std::string & endDate, 
  DQLBase<Record>::ResCtnType & resCtn)
{
  Record argObj;
  argObj.cvsId = cvsId;
  argObj.date = beginDate;
  argObj.time = endDate;

  RecordQuery qry;
  qry.BatchExecute(ALL_BY_CONVERSATION_ID_BETWEEN_DATE, argObj, resCtn);

  DEBUG_LOG("cvsId=%s, beginDate=%s, endDate=%s, qry.count=%d"
	  , cvsId.c_str()
	  , beginDate.c_str()
	  , endDate.c_str()
	  , qry.count);
  return qry.count;
}
	
int RecordQuery::QueryChatByConversationIdBetweenDate(const std::string & cvsId, 
	const std::string & beginDate, const std::string & endDate, 
	DQLBase<Record>::ResCtnType & resCtn)
{
	Record argObj;
	argObj.cvsId = cvsId;
	argObj.date = beginDate;
	argObj.time = endDate;

	RecordQuery qry;
	qry.BatchExecute(CHAT_RECORD_BY_CONVERSATION_ID_BETWEEN_DATE, argObj, resCtn);

	DEBUG_LOG("cvsId=%s, beginDate=%s, endDate=%s, qry.count=%d",cvsId.c_str(), beginDate.c_str(), endDate.c_str(), qry.count);
	return qry.count;
}
//static 
int RecordQuery::QueryImportantByConversationId(const std::string & cvsId, 
                                                DQLBase<Record>::ResCtnType & resCtn)
{
  Record argObj;
  argObj.cvsId = cvsId;

  RecordQuery qry;
  qry.BatchExecute(IMPORTANT_BY_CONVERSATION_ID, argObj, resCtn);

  DEBUG_LOG("argObj.cvsId=%s, argObj.date=%s, argObj.time=%s, qry.count=%d"
	  , argObj.cvsId.c_str()
	  , argObj.date.c_str()
	  , argObj.time.c_str()
	  , qry.count);
  return qry.count;
}

//static 
int RecordQuery::QueryUnreadAll(DQLBase<Record>::ResCtnType & resCtn)
{
    Record argObj;
    RecordQuery qry;

    qry.BatchExecute(UNREAD_ALL, argObj, resCtn);

    DEBUG_LOG("qry.count=%d",qry.count);
    return qry.count;
}

//static 
int RecordQuery::QueryUnreadAllExceptChatRecord(DQLBase<Record>::ResCtnType & resCtn)
{
    Record argObj;
    RecordQuery qry;

    qry.BatchExecute(UNREAD_ALL_EXCEPT_CHATRECORD, argObj, resCtn);

    DEBUG_LOG("qry.count=%d",qry.count);
    return qry.count;
}

//static 
bool RecordQuery::QueryLastUnreadMissedCallByConversationId(
  const std::string & cvsId, 
  DQLBase<Record>::ResObjType & resObj)
{
  Record argObj;
  argObj.cvsId = cvsId;

  RecordQuery qry;
  bool ret = qry.SingleExecute(LAST_UNREAD_MISSED_CALL, argObj, resObj);

  DEBUG_LOG("cvsId=%s, qry.count=%d",cvsId.c_str(), qry.count);
  return ret;
}

//static 
int RecordQuery::QueryUnreadCount()
{
  Record argObj;

  RecordQuery qry;
  Record resObj;
  (void)qry.SingleExecute(UNREAD_COUNT_ALL, argObj, resObj);

  DEBUG_LOG("resObj.unread=%d",resObj.unread);
  return resObj.unread;
}

//static 
int RecordQuery::QueryConversationCountBetweenDate(
  const std::string & beginDate, const std::string & endDate)
{
  Record argObj;
  argObj.date = beginDate;
  argObj.time = endDate;

  RecordQuery qry;
  Record resObj;
  (void)qry.SingleExecute(CONVERSATION_COUNT_BETWEEN_DATE, argObj, resObj);

  DEBUG_LOG("beginDate=%s, endDate=%s, resObj.recordId=%d",beginDate.c_str(), endDate.c_str(), resObj.recordId);
  return (int)resObj.recordId;
}

//static 
int RecordQuery::QueryUnreadCountByConversationId(const std::string & cvsId)
{
  Record argObj;
  argObj.cvsId = cvsId;

  RecordQuery qry;
  Record resObj;
  (void)qry.SingleExecute(UNREAD_COUNT_BY_CONVERSATION_ID, argObj, resObj);

  DEBUG_LOG("cvsId=%s, resObj.unread=%d",cvsId.c_str(), resObj.unread);
  return resObj.unread;
}
//static 
int RecordQuery::QueryUnreadCallByConversationId(const std::string & cvsId)
{
    Record argObj;
    argObj.cvsId = cvsId;

    RecordQuery qry;
    Record resObj;
    (void)qry.SingleExecute(UNREAD_CALL_BY_CONVERSATION_ID, argObj, resObj);

    DEBUG_LOG("cvsId=%s, resObj.unreadCall=%d",cvsId.c_str(), resObj.unreadCall);

    return resObj.unreadCall;
}
//static 
int RecordQuery::QueryImportantCountByConversationId(const std::string & cvsId)
{
  Record argObj;
  argObj.cvsId = cvsId;

  RecordQuery qry;
  Record resObj;
  (void)qry.SingleExecute(IMPORTANT_COUNT_BY_CONVERSATION_ID, argObj, resObj);

  DEBUG_LOG("cvsId=%s, resObj.important=%d",cvsId.c_str(), resObj.important);

  return resObj.important;
}

//static 
int RecordQuery::QueryRecordOffset(
  const DataRecordId & recordId, const std::string & cvsId,const std::string& _dbName)
{
    //根据recordid获取那条记录的UTC时间
    Record tmpArgObj;
    tmpArgObj.recordId = recordId;
    Record tmpResObj;

    RecordQuery tmpQry(_dbName);
    bool ret = tmpQry.SingleExecute(RECORD_ID, tmpArgObj, tmpResObj);
    if(!ret)
    {
        INFO_LOG("not found record by history !");
        return -1;
    }

    Record argObj;
    argObj.cvsId = cvsId;   
    argObj.date = tmpResObj.date;
    argObj.time = tmpResObj.time;   
    Record resObj;   
    RecordQuery qry(_dbName);
    (void)qry.SingleExecute(RECORD_OFFSET, argObj, resObj);

    //if(tmpResObj.utcdate.empty() || tmpResObj.utctime.empty())
    //{
    //    argObj.date = tmpResObj.date;
    //    argObj.time = tmpResObj.time;

    //    (void)qry.SingleExecute(RECORD_OFFSET, argObj, resObj);
    //}
    //else
    //{
    //    argObj.utcdate = tmpResObj.utcdate;
    //    argObj.utctime = tmpResObj.utctime;

    //    (void)qry.SingleExecute(RECORD_OFFSET_BYUTC, argObj, resObj);
    //}
    DEBUG_LOG("recordId=%d, cvsId=%s, resObj.recordId+1=%d",recordId, cvsId.c_str(), resObj.recordId+1);

    return (int)resObj.recordId+1;
}

//static 
int RecordQuery::QueryPreRecordsByUTCDateTime(const std::string & cvsId, const std::string strUTCDate, const std::string strUTCTime, const int limitcount,
                                        DQLBase<Record>::ResCtnType & resCtn)
{
    Record argObj;
    argObj.utcdate = strUTCDate;
    argObj.utctime = strUTCTime;
    argObj.cvsId = cvsId;
    argObj.important = limitcount;//暂时保存limit信息

    RecordQuery qry;
    qry.BatchExecute(PRE_RECORD_BY_UTCDATETIME, argObj, resCtn);

    return qry.count;
}

//static
int RecordQuery::QueryPreRecordsByRcdId(const std::string & cvsId, const DataRecordId rcdId, const int limitcount,
                                        DQLBase<Record>::ResCtnType & resCtn)
{
    Record argObj;
    argObj.recordId = rcdId;
    argObj.cvsId = cvsId;
    argObj.important = limitcount;//暂时保存limit信息

    RecordQuery qry;
    qry.BatchExecute(PRE_RECORD_BY_RECORD_ID, argObj, resCtn);
    
    DEBUG_LOG("argObj.cvsId=%s, argObj.recordId=%d, argObj.important=%d, qry.count=%d"
		,argObj.cvsId.c_str()
		, argObj.recordId
		, argObj.important
		, qry.count);

    return qry.count;
}

//static 
int RecordQuery::FilterRecords(const DQLBase<Record>::ArgObjType & argObj, 
  DQLBase<Record>::ResCtnType & resCtn,const std::string& _dbName)
{
  //assert(argObj.important != 0);

  RecordQuery qry(_dbName);
  qry.BatchExecute(FILTER, argObj, resCtn);

  DEBUG_LOG("argObj.recordType=%d, argObj.unread=%d, argObj.important=%d, qry.count=%d",argObj.recordType
	  , argObj.unread, argObj.important, qry.count);
  return qry.count;
}

//static 
int RecordQuery::FilterRecordsCount(const DQLBase<Record>::ArgObjType & argObj,const std::string& _dbName)
{
  RecordQuery qry(_dbName);
  Record resObj;
  (void)qry.SingleExecute(FILTER_COUNT, argObj, resObj);

  DEBUG_LOG("argObj.recordType=%d, argObj.unread=%d, argObj.important=%d, resObj.recordId=%d",argObj.recordType
	  , argObj.unread
	  , argObj.important
	  , resObj.recordId);

  return (int)resObj.recordId;
}

int RecordQuery::QueryCountBeforeDate(const std::string& _lastDate,int& _recordCount)
{
  RecordQuery qry;
  DQLBase<Record>::ArgObjType argObj;
  argObj.date = _lastDate;
  DQLBase<Record>::ResObjType  resObj;
  (void)qry.SingleExecute(RECORD_COUNT_BEFORE_DATE, argObj, resObj);
  _recordCount = resObj.reservedInt1;
  
  DEBUG_LOG("_lastDate=%s, _recordCount=%d, qry.count=%d",_lastDate.c_str(), _recordCount, qry.count);
  return qry.count;
}

int RecordQuery::QueryRecordByPageBeforeDate(const std::string& _date,unsigned int _pageNo,unsigned int _pageSize,
	  DQLBase<Record>::ResCtnType & resCtn)
{
  RecordQuery qry;
  DQLBase<Record>::ArgObjType argObj;
  argObj.date = _date;
  argObj.reservedInt1 = (int)_pageSize;
  argObj.reservedInt2 = (int)_pageNo;
  qry.BatchExecute(	RECORD_Page_BY_BEFORE_DEATE, argObj, resCtn);
  
  INFO_LOG("_date=%s, _pageNo=%d, _pageSize=%d, qry.count=%d",_date.c_str(), _pageNo, _pageSize, qry.count);
  return qry.count;
}

int RecordQuery::QueryConvIdBeforeDate(const std::string& _lastDate,std::set<std::string>& _lstConvID)
{
  RecordQuery qry;
  DQLBase<Record>::ArgObjType argObj;
  argObj.date = _lastDate;
  DQLBase<Record>::ResCtnType resCtn;
  qry.BatchExecute(	RECORD_CVSID_BEFORE_DATE, argObj, resCtn);
  DQLBase<Record>::ResCtnType::iterator itor = resCtn.begin();
  while(itor != resCtn.end())
  {
	(void)_lstConvID.insert(itor->cvsId);
	++itor;
  }
  
  DEBUG_LOG("_lastDate=%s, qry.count=%d",_lastDate.c_str(), qry.count);
  return qry.count;
}

int RecordQuery::QueryRecordDateMin(std::string& _minDate)
{
  RecordQuery qry;
  DQLBase<Record>::ArgObjType argObj;
  DQLBase<Record>::ResObjType resObj;
  (void)qry.SingleExecute(RECORD_DATE_MIN, argObj, resObj);
  _minDate = resObj.date;
  DEBUG_LOG("_minDate=%s, qry.count=%d",_minDate.c_str(), qry.count);
  return qry.count;
}

bool RecordQuery::QuerySMSRecordByContent(const std::string& content, const std::string& mobile, const int flag, DQLBase<Record>::ResObjType & resObj)
{
	Record argObj;
	argObj.text = content;
	argObj.peerId = mobile;
	argObj.flag = flag;

	RecordQuery qry;
	bool ret = qry.SingleExecute(RECORD_SMS_CONTENT, argObj, resObj);

	return ret;
}

void QueryCreateTableStmt::ComposeSQL(std::string & sql)
{
  sql = "select sql from sqlite_master where name = ?;";
}

void QueryCreateTableStmt::Bind(IDataManipulation * dm, 
                          const DQLBase<QuerySQLPair>::ArgObjType & argObj)
{
  int i = 0;

  dm->Bind(++i, argObj.strTableName);

}
//static 
int QueryCreateTableStmt::ExtractFromDBSqliteMaster(IDataManipulation * dm, 
                                            DQLBase<QuerySQLPair>::ResObjType & resObj, int startIndex)
{
  int i = 0;

  dm->GetValue(startIndex + i++, resObj.strSQL);

  return i;
}

bool QueryCreateTableStmt::ColumnIsExist(const std::string& _tblName,const std::string& _columnName,const std::string /*_newSql*/)
{
    ecs::ecsdata::QuerySQLPair argObj;
    std::vector<ecs::ecsdata::QuerySQLPair> resCtn;

    argObj.strTableName = _tblName;
    Execute(argObj, resCtn);

    std::string res;
    if (resCtn.size() > 0)
    {
        res = resCtn[0].strSQL;
    }
  
    std::string strIndex = _columnName;
    if(res.find(strIndex) != std::string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
 }
} // namespace history
}
}
