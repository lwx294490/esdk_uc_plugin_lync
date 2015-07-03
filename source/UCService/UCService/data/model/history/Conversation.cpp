#include "stdafx.h"
#include "data/model/history/Conversation.h"

#include "Log.h"

using namespace std;

namespace ecs {
  namespace ecsdata {
    namespace history {

///////////////////////////////////////////////////////////////////////////
void CreateConversationTabCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "CREATE TABLE IF NOT EXISTS "CONVERSATION_TAB
    "( CONVERSATION_ID VARCHAR(128) PRIMARY KEY"
    ", CONVERSATION_TYPE INTEGER NOT NULL"

    ", GROUP_ID VARCHAR(32) NOT NULL"
    ", GROUP_NAME VARCHAR(32) NOT NULL"
    ", ORIGINATOR VARCHAR(128) NOT NULL"
    ", PARTICIPANTS VARCHAR(1024) NOT NULL"
    ", DESC VARCHAR(128) NOT NULL"

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

int AddConversationCommand::BatchInsert(const std::string& _dbName,ArgCtnType _resCtn)
{
	AddConversationCommand cmd(_dbName);
	cmd.BatchExecute(0,_resCtn);
	return cmd.changed;
}

void AddConversationCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "INSERT OR REPLACE INTO "CONVERSATION_TAB
    "( CONVERSATION_ID"
    ", CONVERSATION_TYPE"

    ", GROUP_ID"
    ", GROUP_NAME"
    ", ORIGINATOR"
    ", PARTICIPANTS"
    ", DESC"

    ", FLAG"
    ", RESERVED_INT1"
    ", RESERVED_INT2"
    ", RESERVED_INT3"
    ", RESERVED_STR1"
    ", RESERVED_STR2"
    ", RESERVED_STR3"

    ") VALUES( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? );";
}

void AddConversationCommand::Bind(IDataManipulation * dm, 
  const DMLBase<Cvs>::ArgObjType & argObj)
{
  //INFO_PARAM2(argObj.cvsId, argObj.cvsType);

  int i = 0;

  dm->Bind(++i, argObj.cvsId);
  dm->Bind(++i, argObj.cvsType);
  dm->Bind(++i, argObj.groupId);
  dm->Bind(++i, argObj.groupName);
  dm->Bind(++i, argObj.originator);
  dm->Bind(++i, argObj.participants);
  dm->Bind(++i, argObj.desc);
  dm->Bind(++i, argObj.flag);
  dm->Bind(++i, argObj.reservedInt1);
  dm->Bind(++i, argObj.reservedInt2);
  dm->Bind(++i, argObj.reservedInt3);
  dm->Bind(++i, argObj.reservedStr1);
  dm->Bind(++i, argObj.reservedStr2);
  dm->Bind(++i, argObj.reservedStr3);
}

///////////////////////////////////////////////////////////////////////////
void UpdateConversationCommand::ComposeSQL(std::string & sql)
{
  sql = "UPDATE "CONVERSATION_TAB" SET ";

  switch (type_)
  {
  case PARTICIPANTS:
    (void)sql.append("PARTICIPANTS = ? ");
    break;
  case CONVGROUPNAME:
    (void)sql.append("GROUP_NAME = ? ");
    break;
  case UNREADMSGTOTAL:
    (void)sql.append("RESERVED_INT1 = ? ");
    break;
  case MINMSGID:
    (void)sql.append("RESERVED_STR1 = ? ");
    break;
  default:
    sql.clear();
    WARN_LOG("unknown type : %d" ,type_);
    return;
  }

  (void)sql.append("WHERE CONVERSATION_ID = ?");
}

void UpdateConversationCommand::Bind(IDataManipulation * dm, 
  const DMLBase<Cvs>::ArgObjType & argObj)
{
  //INFO_PARAM1(argObj.cvsId);

  int i = 0;
  switch (type_)
  {
  case PARTICIPANTS:
    //INFO_PARAM1(argObj.participants);
    dm->Bind(++i, argObj.participants);
    break;
  case CONVGROUPNAME:
    //INFO_PARAM1(argObj.groupName);
    dm->Bind(++i, argObj.groupName);
    break;
  case UNREADMSGTOTAL:
    //INFO_PARAM1(argObj.reservedInt1);
    dm->Bind(++i, argObj.reservedInt1);
    break;
  case MINMSGID:
    //INFO_PARAM1(argObj.reservedStr1);
    dm->Bind(++i, argObj.reservedStr1);
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    return;
  }

  dm->Bind(++i, argObj.cvsId);
}

//static 
bool UpdateConversationCommand::UpdateParticipantsByConversationId(
  const std::string & cvsId, const std::string & participants)
{
  Cvs argObj;
  argObj.cvsId = cvsId;
  argObj.participants = participants;

  int nChanged = UpdateConversationCommand::UpdateParticipants(argObj);

  //INFO_PARAM3(cvsId, participants, nChanged);
  return nChanged == 1;
}

bool UpdateConversationCommand::UpdateGroupNameByConversationId(
    const std::string & cvsId, const std::string & newname)
{
    Cvs argObj;
    argObj.cvsId = cvsId;
    argObj.groupName = newname;

    int nChanged = UpdateConversationCommand::UpdateGroupName(argObj);

    //INFO_PARAM3(cvsId, newname, nChanged);
    return nChanged == 1;
}
//更新未读消息总数
bool UpdateConversationCommand::UpdateUnReadMsgTotalByConversationId(
    const std::string & cvsId, const int total)
{
    Cvs argObj;
    argObj.cvsId = cvsId;
    argObj.reservedInt1 = total;

    int nChanged = UpdateConversationCommand::UpdateUnReadMsgTotal(argObj);

    //INFO_PARAM3(cvsId, total, nChanged);
    return nChanged == 1;
}
//更新最早未读消息msgid
bool UpdateConversationCommand::UpdateMinMsgIdByConversationId(
    const std::string & cvsId, const std::string& strMinMsgId)
{
    Cvs argObj;
    argObj.cvsId = cvsId;
    argObj.reservedStr1 = strMinMsgId;

    int nChanged = UpdateConversationCommand::UpdateMinMsgId(argObj);

    //INFO_PARAM3(cvsId, strMinMsgId, nChanged);
    return nChanged == 1;
}

///////////////////////////////////////////////////////////////////////////
void RemoveConversationCommand::ComposeSQL(std::string & sql)
{
  const std::string DELETE_CONVERSATION = "DELETE FROM "CONVERSATION_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case CONVERSATION_ID:
    (void)whereClause.append("CONVERSATION_ID = ?");
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    sql = "";
    return;
  }

  sql = DELETE_CONVERSATION + whereClause + ";";
}

void RemoveConversationCommand::Bind(IDataManipulation * dm, 
  const DMLBase<Cvs>::ArgObjType & argObj)
{
  int i = 0;

  switch (type_)
  {
  case ALL:
    break;
  case CONVERSATION_ID:
    dm->Bind(++i, argObj.cvsId);
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    break;
  }
}

//static 
int RemoveConversationCommand::RemoveAll()
{
  //TRACE_FUNC();

  Cvs argObj;

  RemoveConversationCommand cmd;
  cmd.SingleExecute(ALL, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed;
}

//static 
int RemoveConversationCommand::RemoveByConversationId(
  const std::string & cvsId)
{
  //TRACE_FUNC1(cvsId);

  Cvs argObj;
  argObj.cvsId = cvsId;

  RemoveConversationCommand cmd;
  cmd.SingleExecute(CONVERSATION_ID, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed;
}

///////////////////////////////////////////////////////////////////////////
void ConversationQuery::ComposeSQL(std::string & sql)
{
  const std::string QUERY_CONVERSATION = "SELECT * FROM "CONVERSATION_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case CONVERSATION_ID:
    (void)whereClause.append("CONVERSATION_ID = ?");
    break;
  case CONVERSATION_TYPE:
    (void)whereClause.append("CONVERSATION_TYPE = ?");
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    sql = "";
    return;
  }

  sql = QUERY_CONVERSATION + whereClause + ";";
}

void ConversationQuery::Bind(IDataManipulation * dm, 
                             const DQLBase<Cvs>::ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case CONVERSATION_ID:
    ////INFO_PARAM1(argObj.cvsId);
    dm->Bind(++i, argObj.cvsId);
    break;
  case CONVERSATION_TYPE:
    ////INFO_PARAM1(argObj.cvsType);
    dm->Bind(++i, argObj.cvsType);
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    break;
  }
}

//static 
int ConversationQuery::ExtractFromConversationTab(
  IDataManipulation * dm, DQLBase<Cvs>::ResObjType & resObj, int startIndex)
{
  int i = 0;

  dm->GetValue(startIndex + i++, resObj.cvsId);
  dm->GetValue(startIndex + i++, resObj.cvsType);
  dm->GetValue(startIndex + i++, resObj.groupId);
  dm->GetValue(startIndex + i++, resObj.groupName);
  dm->GetValue(startIndex + i++, resObj.originator);
  dm->GetValue(startIndex + i++, resObj.participants);
  dm->GetValue(startIndex + i++, resObj.desc);
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
bool ConversationQuery::QueryByConversationId(const std::string & cvsId, 
  DQLBase<Cvs>::ResObjType & resObj)
{
  Cvs argObj;
  argObj.cvsId = cvsId;

  ConversationQuery qry;
  bool ret = qry.SingleExecute(CONVERSATION_ID, argObj, resObj);

  DEBUG_LOG("cvsId=%s, ret=%d",cvsId.c_str(), ret);
  return ret;
}

///////////////////////////////////////////////////////////////////////////
void CreateConversationMsgIdTabCommand::ComposeSQL(std::string & sql)
{
    sql =
        "CREATE TABLE IF NOT EXISTS " CONVERSATION_MSGID_TAB
        "( CONVERSATION_ID VARCHAR(128) NOT NULL"
        ", MSG_ID VARCHAR(32) NOT NULL"
        ", MSG_TYPE INTEGER NOT NULL DEFAULT(-1)"
        ", SENDER_URI VARCHAR(32) NOT NULL"
        ", STATE INTEGER NOT NULL DEFAULT(0)"
        ", PRIMARY KEY(CONVERSATION_ID, MSG_ID));";
}

///////////////////////////////////////////////////////////////////////////
void AddConversationMsgIdCommand::ComposeSQL(std::string & sql)
{
    sql =
        "INSERT OR IGNORE INTO " CONVERSATION_MSGID_TAB
        "( CONVERSATION_ID"
        ", MSG_ID"
        ", MSG_TYPE"
        ", SENDER_URI"
        ", STATE"
        ") VALUES( ?, ?, ?, ?, ? );";
}

void AddConversationMsgIdCommand::Bind(IDataManipulation *                    dm,
                                       const DMLBase <CvsMsgId>::ArgObjType & argObj)
{
    //INFO_PARAM2(argObj.cvsId, argObj.msgId);

    int i = 0;

    dm->Bind(++i, argObj.cvsId);
    dm->Bind(++i, argObj.msgId);
    dm->Bind(++i, argObj.msgType);
    dm->Bind(++i, argObj.senderUri);
    dm->Bind(++i, argObj.state);
}

///////////////////////////////////////////////////////////////////////////
void UpdateConversationMsgIdCommand::ComposeSQL(std::string & sql)
{
    sql = "UPDATE " CONVERSATION_MSGID_TAB " SET ";

    switch (type_)
    {
    case STATE_CHANGE:
        (void)sql.append("STATE = ? WHERE STATE = ?");
        break;
    case STATE_CHANGE_BY_CONVERSATION_ID:
        (void)sql.append("STATE = ? WHERE STATE = ? AND CONVERSATION_ID = ?");
        break;
    default:
        sql.clear();
        WARN_LOG("unknown type : %d" ,type_);
        return;
    }
}

void UpdateConversationMsgIdCommand::Bind(IDataManipulation *                    dm,
                                          const DMLBase <CvsMsgId>::ArgObjType & argObj)
{

    int i = 0;

    switch (type_)
    {
    case STATE_CHANGE:
        dm->Bind(++i, argObj.state);
        dm->Bind(++i, argObj.msgType); //msgType field is used as oldState parameter
        break;
    case STATE_CHANGE_BY_CONVERSATION_ID:
        dm->Bind(++i, argObj.state);
        dm->Bind(++i, argObj.msgType); //msgType field is used as oldState parameter
        dm->Bind(++i, argObj.cvsId);
        break;
    default:
        WARN_LOG("unknown type : %d" ,type_);
        return;
    }
}

//static
int UpdateConversationMsgIdCommand::UpdateState(int oldState, int newState)
{
    CvsMsgId argObj;

    argObj.msgType = oldState; //msgType field is used as oldState parameter
    argObj.state = newState;

    int nChanged = UpdateConversationMsgIdCommand::UpdateStateChange(argObj);

    return nChanged;
}

//static
int UpdateConversationMsgIdCommand::UpdateStateByConversationId(const std::string & cvsId, int oldState,
                                                                int newState)
{
    CvsMsgId argObj;

    argObj.cvsId   = cvsId;
    argObj.msgType = oldState; //msgType field is used as oldState parameter
    argObj.state = newState;

    int nChanged = UpdateConversationMsgIdCommand
        ::UpdateStateChangeByConversationId(argObj);

    //INFO_PARAM4(cvsId, oldState, newState, nChanged);
    return nChanged;
}

///////////////////////////////////////////////////////////////////////////
void RemoveConversationMsgIdCommand::ComposeSQL(std::string & sql)
{
    const std::string DELETE_CONVERSATION_MSGID = "DELETE FROM " CONVERSATION_MSGID_TAB;

    std::string whereClause = " WHERE ";

    switch (type_)
    {
    case ALL:
        whereClause.clear();
        break;
    case CONVERSATION_ID_AND_STATE:
        (void)whereClause.append("CONVERSATION_ID = ? AND STATE = ?");
        break;
    case STATE:
        (void)whereClause.append("STATE = ?");
        break;
    case ALLNOTMAX:
        (void)whereClause.append("CONVERSATION_ID = ? AND STATE = ? AND MSG_ID < ?");
        break;
    default:
        WARN_LOG("unknown type : %d" ,type_);
        sql = "";
        return;
    }

    sql = DELETE_CONVERSATION_MSGID + whereClause + ";";
}

void RemoveConversationMsgIdCommand::Bind(IDataManipulation *                    dm,
                                          const DMLBase <CvsMsgId>::ArgObjType & argObj)
{
    int i = 0;

    switch (type_)
    {
    case ALL:
        break;
    case CONVERSATION_ID_AND_STATE:
        //INFO_PARAM2(argObj.cvsId, argObj.state);
        dm->Bind(++i, argObj.cvsId);
        dm->Bind(++i, argObj.state);
        break;
    case STATE:
        //INFO_PARAM1(argObj.state);
        dm->Bind(++i, argObj.state);
        break;
    case ALLNOTMAX:
        dm->Bind(++i, argObj.cvsId);
        dm->Bind(++i, argObj.state);
        dm->Bind(++i, argObj.msgId);
        break;
    default:
        WARN_LOG("unknown type : %d" ,type_);
        break;
    }
}

//static
int RemoveConversationMsgIdCommand::RemoveAll()
{
    //TRACE_FUNC();

    CvsMsgId argObj;

    RemoveConversationMsgIdCommand cmd;
    cmd.SingleExecute(ALL, argObj);

    //INFO_PARAM1(cmd.changed);
    return cmd.changed;
}

//static
int RemoveConversationMsgIdCommand::RemoveByState(int state)
{
    //TRACE_FUNC1(state);

    CvsMsgId argObj;
    argObj.state = state;

    RemoveConversationMsgIdCommand cmd;
    cmd.SingleExecute(STATE, argObj);

    //INFO_PARAM1(cmd.changed);
    return cmd.changed;
}

//static
int RemoveConversationMsgIdCommand::RemoveByConversationIdAndState(const std::string & cvsId, int state)
{
    //TRACE_FUNC2(cvsId, state);

    CvsMsgId argObj;
    argObj.cvsId = cvsId;
    argObj.state = state;

    RemoveConversationMsgIdCommand cmd;
    cmd.SingleExecute(CONVERSATION_ID_AND_STATE, argObj);

    //INFO_PARAM1(cmd.changed);
    return cmd.changed;
}

int RemoveConversationMsgIdCommand::RemoveAllNotMaxByConversationIdAndState(const DMLBase<CvsMsgId>::ArgCtnType& _argCtnObj)
{
    RemoveConversationMsgIdCommand cmd;
    cmd.BatchExecute(ALLNOTMAX, _argCtnObj);

    //INFO_PARAM1(cmd.changed);
    return cmd.changed;
}


///////////////////////////////////////////////////////////////////////////
void ConversationMsgIdQuery::ComposeSQL(std::string & sql)
{
    /*select * from ConversationMsgIdTab where rowid in (select max(rowid) from 
    ConversationMsgIdTab WHERE MSG_TYPE = 1 AND STATE = 0 GROUP BY CONVERSATION_ID);
    */
    const std::string QUERY_CONVERSATION_MSGID = "SELECT * FROM " CONVERSATION_MSGID_TAB;
    const std::string QUERY_LAST_MSGID_PREFIX = " WHERE ROWID IN ( SELECT MAX(ROWID) FROM " CONVERSATION_MSGID_TAB;

    std::string whereClause = " WHERE ";

    switch (type_)
    {
    case ALL_BY_CONVERSATION_ID_AND_STATE:
        (void)whereClause.append("CONVERSATION_ID = ? AND STATE = ?");
        break;
    case LAST_BY_CONVERSATION_ID_AND_STATE:
        (void)whereClause.append("CONVERSATION_ID = ? AND STATE = ? LIMIT 1");
        break;
    case LAST_BY_STATE:
        (void)whereClause.append("STATE = ? GROUP BY CONVERSATION_ID");
        break;
    case ALL_BY_MSGTYPE_AND_STATE:
        (void)whereClause.append("MSG_TYPE = ? AND STATE = ?");
        break;
    case LAST_BY_MSGTYPE_AND_STATE:
        whereClause.clear();
        (void)whereClause.append(QUERY_LAST_MSGID_PREFIX);
        (void)whereClause.append(" WHERE MSG_TYPE = ? AND STATE = ? GROUP BY CONVERSATION_ID)");
        break;
    case CONVERSATION_MAX_MSGID:
        sql = "SELECT CONVERSATION_ID,MAX(MSG_ID),MSG_TYPE,SENDER_URI,STATE FROM " CONVERSATION_MSGID_TAB;
        (void)whereClause.append(" MSG_TYPE = ? AND STATE = ? GROUP BY CONVERSATION_ID");
        (void)sql.append(whereClause);
        return;
    default:
        WARN_LOG("unknown type : %d" ,type_);
        sql = "";
        return;
    }

    sql = QUERY_CONVERSATION_MSGID + whereClause + ";";
}

void ConversationMsgIdQuery::Bind(IDataManipulation *                    dm,
                                  const DQLBase <CvsMsgId>::ArgObjType & argObj)
{
    int i = 0;

    switch (type_)
    {
    case ALL_BY_CONVERSATION_ID_AND_STATE:
    case LAST_BY_CONVERSATION_ID_AND_STATE:
        dm->Bind(++i, argObj.cvsId);
        dm->Bind(++i, argObj.state);
        break;
    case LAST_BY_STATE:
        dm->Bind(++i, argObj.state);
        break;
    case ALL_BY_MSGTYPE_AND_STATE:
        dm->Bind(++i, argObj.msgType);
        dm->Bind(++i, argObj.state);
        break;
    case LAST_BY_MSGTYPE_AND_STATE:
        dm->Bind(++i, argObj.msgType);
        dm->Bind(++i, argObj.state);
        break;
    case CONVERSATION_MAX_MSGID:
        dm->Bind(++i, argObj.msgType);
        dm->Bind(++i, argObj.state);
        break;
    default:
        WARN_LOG("unknown type : %d" ,type_);
        break;
    }
}

//static
int ConversationMsgIdQuery::ExtractFromConversationMsgIdTab(IDataManipulation * dm,
                                                            DQLBase <CvsMsgId>::ResObjType & resObj,
                                                            int startIndex)
{
    int i = 0;

    dm->GetValue(startIndex + i++, resObj.cvsId);
    dm->GetValue(startIndex + i++, resObj.msgId);
    dm->GetValue(startIndex + i++, resObj.msgType);
    dm->GetValue(startIndex + i++, resObj.senderUri);
    dm->GetValue(startIndex + i++, resObj.state);

    return i;
}

//static
int ConversationMsgIdQuery::QueryAllByConversationIdAndState(const std::string & cvsId, int state,
                                                             DQLBase <CvsMsgId>::ResCtnType & resCtn)
{
    CvsMsgId argObj;

    argObj.cvsId = cvsId;
    argObj.state = state;

    ConversationMsgIdQuery qry;
    qry.BatchExecute(ALL_BY_CONVERSATION_ID_AND_STATE, argObj, resCtn);

    DEBUG_LOG("cvsId=%s, state=%d, qry.count=%d",cvsId.c_str(), state, qry.count);
    return qry.count;
}

//static
bool ConversationMsgIdQuery::QueryLastByConversationIdAndState(const std::string & cvsId, int state,
                                                               DQLBase <CvsMsgId>::ResObjType & resObj)
{
    CvsMsgId argObj;

    argObj.cvsId = cvsId;
    argObj.state = state;

    ConversationMsgIdQuery qry;
    bool ret = qry.SingleExecute(LAST_BY_CONVERSATION_ID_AND_STATE, argObj, resObj);

    DEBUG_LOG("cvsId=%s, state=%d, ret=%d",cvsId.c_str(), state, ret);
    return ret;
}

//static
int ConversationMsgIdQuery::QueryLastByState(int state, DQLBase <CvsMsgId>::ResCtnType & resCtn)
{
    CvsMsgId argObj;

    argObj.state = state;

    ConversationMsgIdQuery qry;
    qry.BatchExecute(LAST_BY_STATE, argObj, resCtn);

    DEBUG_LOG("state=%d, qry.count=%d",state, qry.count);
    return qry.count;
}
//static
int ConversationMsgIdQuery::QueryLastByMsgtypeAndState(int msgType, int state, DQLBase <CvsMsgId>::ResCtnType & resCtn)
{
    CvsMsgId argObj;
    argObj.msgType = msgType;
    argObj.state = state;

    ConversationMsgIdQuery qry;
    qry.BatchExecute(LAST_BY_MSGTYPE_AND_STATE, argObj, resCtn);

    DEBUG_LOG("msgType=%d, state=%d, qry.count=%d",msgType, state, qry.count);
    return qry.count;
}

//static
int ConversationMsgIdQuery::QueryALLByMsgtypeAndState(int msgType, int state, DQLBase <CvsMsgId>::ResCtnType & resCtn)
{
    CvsMsgId argObj;
    argObj.msgType = msgType;
    argObj.state = state;

    ConversationMsgIdQuery qry;
    qry.BatchExecute(ALL_BY_MSGTYPE_AND_STATE, argObj, resCtn);

    DEBUG_LOG("msgType=%d, state=%d, qry.count=%d",msgType, state, qry.count);
    return qry.count;
}

int ConversationMsgIdQuery::QueryConversationMaxMsgID(int _type,int _state,DQLBase <CvsMsgId>::ResCtnType & _resObj)
{
    CvsMsgId argObj;
    argObj.msgType = _type;
    argObj.state = _state;

    ConversationMsgIdQuery qry;
    qry.BatchExecute(CONVERSATION_MAX_MSGID, argObj, _resObj);

    DEBUG_LOG("_type=%d, _state=%d, qry.count=%d",_type, _state, qry.count);
    return qry.count;
}

int ConversationQuery::QueryByConversationType(int cvsType, DQLBase<Cvs>::ResCtnType & resCtn,const std::string& _dbName)
{
  Cvs argObj;
  argObj.cvsType = cvsType;

  ConversationQuery qry(_dbName);
  qry.BatchExecute(CONVERSATION_TYPE, argObj, resCtn);

  DEBUG_LOG("cvsType=%d, qry.count=%d",cvsType, qry.count);
  return qry.count;
}

int ConversationQuery::QueryAll(DQLBase<Cvs>::ResCtnType & resCtn)
{
  Cvs argObj;

  ConversationQuery qry;
  qry.BatchExecute(ALL, argObj, resCtn);

  //INFO_PARAM1(qry.count);
  return qry.count;
}

    } // namespace history
  } // namespace ecsdata
} // namespace ecs
