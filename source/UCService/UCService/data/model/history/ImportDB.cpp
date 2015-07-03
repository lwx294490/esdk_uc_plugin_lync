
#include "stdafx.h"
#include "ImportDB.h"
#include "Log.h"
#include "data\model\history\HistoryDataType.h"
namespace ecs {
    namespace ecsdata {
        namespace history {

//////////////////////////////////////////////////////////////////////////
//static 
bool ImportConvQuery::QuerySingleConvByConvId(const std::string& dbPath, 
        const std::string & cvsId, DQLBase<Cvs>::ResObjType & resObj)
{
    Cvs argObj;
    argObj.cvsId = cvsId;

    ImportConvQuery qry(dbPath);
    bool ret = qry.SingleExecute(SINGLE_CONV_BY_ID, argObj, resObj);

    DEBUG_LOG("cvsId=%s, ret=%d",cvsId.c_str(), ret);
    return ret;
}

//static 
int ImportConvQuery::QueryAllConv(const std::string& dbPath, 
        DQLBase<Cvs>::ResCtnType& resCtn)
{
    Cvs argObj;
    ImportConvQuery qry(dbPath);

    qry.BatchExecute(ALL_CONV, argObj, resCtn);

    //INFO_PARAM1(qry.count);

    return qry.count;
}
//static 
int ImportConvQuery::QueryAllConvByConvType(const std::string& dbPath, 
       int cvsType, DQLBase<Cvs>::ResCtnType& resCtn)
{
    Cvs argObj;
    argObj.cvsType = cvsType;

    ImportConvQuery qry(dbPath);
    qry.BatchExecute(ALL_CONV_BY_CONVTYPE, argObj, resCtn);

    DEBUG_LOG("cvsType=%d, qry.count=%d",cvsType, qry.count);
    return qry.count;
}

//static 
int ImportConvQuery::QueryAllConvByOffsetAndPage(const std::string& dbPath, 
       const std::size_t offset, const std::size_t page, DQLBase<Cvs>::ResCtnType & resCtn)
{
    Cvs argObj;
    argObj.reservedInt1 = (int)page;
    argObj.reservedInt2 = (int)offset;

    ImportConvQuery qry(dbPath);
    qry.BatchExecute(ALL_CONV_BY_OFFSET_AND_PAGE, argObj, resCtn);

    DEBUG_LOG("page=%d, offset=%d, qry.count=%d",page, offset, qry.count);
    return qry.count;
}

//static 
int ImportConvQuery::QueryConvs(const std::string& dbPath, 
       DQLBase<Cvs>::ResCtnType& resCtn, int enumType )
{
    Cvs argObj;

    ImportConvQuery qry(dbPath);
    qry.BatchExecute(enumType, argObj, resCtn);

    DEBUG_LOG("enumType=%d, qry.count=%d",enumType, qry.count);
    return qry.count;
}

void ImportConvQuery::ComposeSQL(std::string & sql)
{
  const std::string QUERY_CONV = "SELECT * FROM "CONVERSATION_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case SINGLE_CONV_BY_ID:
      (void)whereClause.append("CONVERSATION_ID = ?");
      break;
  case SINGLE_CONV_BY_OFFSET:
      break;
  case ALL_CONV:
      whereClause.clear();
      break;
  case ALL_CONV_BY_CONVTYPE:
      (void)whereClause.append("CONVERSATION_TYPE = ?");
      break;
  case ALL_CONV_BY_OFFSET_AND_PAGE:
      (void)whereClause.append(" limit ? offset ?");
      break;
  default:
      WARN_LOG("unknown type : %d" ,type_);
      sql = "";
      return;
  }

  sql = QUERY_CONV + whereClause + ";";
}

void ImportConvQuery::Bind(IDataManipulation * dm, 
         const DQLBase<Cvs>::ArgObjType & argObj)
{
    int i = 0;
    switch (type_)
    {
    case ALL_CONV:
        break;
    case SINGLE_CONV_BY_ID:
        dm->Bind(++i, argObj.cvsId);
        break;
    case ALL_CONV_BY_CONVTYPE:
        dm->Bind(++i, argObj.cvsType);
        break;
    case ALL_CONV_BY_OFFSET_AND_PAGE:
        dm->Bind(++i, argObj.reservedInt1);
        dm->Bind(++i, argObj.reservedInt2);
        break;
    default:
        WARN_LOG("unknown type : %d" ,type_);
        break;
    }
}

int ImportConvQuery::ExtractFromTab(IDataManipulation* dm, 
     DQLBase<Cvs>::ResObjType& resObj, int startIndex) const
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


//////////////////////////////////////////////////////////////////////////
//static 
int ImportRecordQuery::QueryAllRecordCount(const std::string & dbPath)
{
    Record argObj;
    Record resObj;

    ImportRecordQuery qry(dbPath);
    (void)qry.SingleExecute(RECORD_CNT, argObj, resObj);

    DEBUG_LOG("qry.count=%d",qry.count);

    return resObj.reservedInt1;
}

//static 
int ImportRecordQuery::QueryAllRecord(const std::string & dbPath,
      DQLBase<Record>::ResCtnType & resCtn)
{
   return QueryRecords(dbPath, resCtn, ALL_RECORD);
}

//static 
int ImportRecordQuery::QueryAllRecordByRecordType(const std::string& dbPath, 
      int recordType, DQLBase<Record>::ResCtnType& resCtn)
{
    Record argObj;
    argObj.recordType = recordType;

    ImportRecordQuery qry(dbPath);
    qry.BatchExecute(ALL_RECORD_BY_TYPE, argObj, resCtn);

    DEBUG_LOG("recordType=%d, qry.count=%d",recordType, qry.count);
    return qry.count;
}

//static 
int ImportRecordQuery::QueryAllRecordByConvId(const std::string& dbPath, 
      const std::string& cvsId, DQLBase<Record>::ResCtnType& resCtn)
{
    Record argObj;
    argObj.cvsId = cvsId;

    ImportRecordQuery qry(dbPath);
    qry.BatchExecute(ALL_RECORD_BY_CONVID, argObj, resCtn);

    DEBUG_LOG("cvsId=%s, qry.count=%d",cvsId.c_str(), qry.count);
    return qry.count;
}

//static 
int ImportRecordQuery::QueryAllRecordByOffsetAndPage(const std::string& dbPath, 
      const std::size_t offset, const std::size_t page, DQLBase<Record>::ResCtnType & resCtn)
{
    Record argObj;
    argObj.reservedInt1 = (int)page;
    argObj.reservedInt2 = (int)offset;
    ImportRecordQuery qry(dbPath);
    qry.BatchExecute(ALL_RECORD_BY_OFFSET_AND_PAGE, argObj, resCtn);

    DEBUG_LOG("page=%d, offset=%d, qry.count=%d",page, offset, qry.count);

    return qry.count;
}

//static 
int ImportRecordQuery::QueryAllRecordByBetweenDate(const std::string & dbPath,
       const std::string& begindate, const std::string& enddate, DQLBase<Record>::ResCtnType& resCtn)
{
    Record argObj;
    argObj.date = begindate;
    argObj.reservedStr1 = enddate;
    ImportRecordQuery qry(dbPath);
    qry.BatchExecute(ALL_RECORD_BY_BETWEEN_DATE, argObj, resCtn);

    DEBUG_LOG("begindate=%s, enddate=%s, qry.count=%d",begindate.c_str(), enddate.c_str(), qry.count);

    return qry.count;
}

//static 
bool ImportRecordQuery::QuerySingleRecordByRecordId(const std::string& dbPath,
      const DataRecordId& recordId, DQLBase<Record>::ResObjType& resObj)
{
    Record argObj;
    argObj.recordId = recordId;

    ImportRecordQuery qry(dbPath);
    bool ret = qry.SingleExecute(SINGLE_RECORD_BY_ID, argObj, resObj);

    DEBUG_LOG("recordId=%d, qry.count=%d",recordId, qry.count);
    return ret;
}

int ImportRecordQuery::QueryRecords(const std::string& dbPath, 
       DQLBase<Record>::ResCtnType & resCtn, int _enumType)
{
    ArgObjType argObj;
    ImportRecordQuery qry(dbPath);
    qry.BatchExecute(_enumType, argObj, resCtn);

    DEBUG_LOG("dbPath=%s,qry.count=%d",dbPath.c_str(),qry.count);
    return qry.count;
}

void ImportRecordQuery::ComposeSQL(std::string & sql)
{
    const std::string QUERY_RECORD = "SELECT RECORD_ID,RECORD_TYPE,CONVERSATION_ID,PEER_ID,PEER_NAME,SENT,BEGINDATE,BEGINTIME,UTCDATE,UTCTIME,DURATION,UNREAD,IMPORTANT,BODY,TEXT\
	,FLAG,RESERVED_INT1,RESERVED_INT2,RESERVED_INT3,RESERVED_STR1,RESERVED_STR2,RESERVED_STR3 FROM "RECORD_TAB;
    const std::string QUERY_RECORD_COUNT = "SELECT COUNT(*) FROM "RECORD_TAB;
    sql = QUERY_RECORD;
    std::string whereClause = " WHERE ";

    switch (type_)
    {
    case ALL_RECORD:
        whereClause.clear();
        break;
    case ALL_RECORD_BY_TYPE:
        (void)whereClause.append("RECORD_TYPE = ?");
        break;
    case ALL_RECORD_BY_CONVID:
        (void)whereClause.append("CONVERSATION_ID = ?");
        break;
    case ALL_RECORD_BY_OFFSET_AND_PAGE:
        whereClause = " ORDER BY BEGINDATE, BEGINTIME limit ? OFFSET ?";
        break;
    case ALL_RECORD_BY_BETWEEN_DATE:
        (void)whereClause.append(" BEGINDATE between ? and ? ");
        break;
    case SINGLE_RECORD_BY_ID:
        (void)whereClause.append("RECORD_ID = ?");
        break;
    case RECORD_CNT:
        sql = QUERY_RECORD_COUNT;
        whereClause.clear();
        break;
    default:
        WARN_LOG("unknown type : %d" ,type_);
        sql = "";
        return;
    }

    (void)sql.append(whereClause).append(";");
}

void ImportRecordQuery::Bind(IDataManipulation * dm, 
        const DQLBase<Record>::ArgObjType & argObj)
{
    int i = 0;
    switch(type_)
    {
    case ALL_RECORD:
        break;
    case ALL_RECORD_BY_TYPE:
        dm->Bind(++i, argObj.recordType);
        break;
    case ALL_RECORD_BY_CONVID:
        dm->Bind(++i, argObj.cvsId);
        break;
    case ALL_RECORD_BY_OFFSET_AND_PAGE:
        dm->Bind(++i,argObj.reservedInt1);
        dm->Bind(++i,argObj.reservedInt2);
        break;
    case ALL_RECORD_BY_BETWEEN_DATE:
        dm->Bind(++i, argObj.date);
        dm->Bind(++i, argObj.reservedStr1);
        break;
    case SINGLE_RECORD_BY_ID:
        dm->Bind(++i, argObj.recordId);
        break;
    case RECORD_CNT:
        break;
    default:
        WARN_LOG("unknown type : %d" ,type_);
        break;
    }
}

void ImportRecordQuery::Extract(IDataManipulation * dm, 
        DQLBase<Record>::ResObjType & resObj)
{
    switch (type_)
    {
    case SINGLE_RECORD_BY_ID:                //单条记录通过id
    case ALL_RECORD:                         //批量查询所有的记录
    case ALL_RECORD_BY_TYPE:                 //批量查询所有记录通过类型
    case ALL_RECORD_BY_CONVID:               //批量查询所有的记录通过会话id
    case ALL_RECORD_BY_OFFSET_AND_PAGE:      //批量查询所有的记录通过偏移和页数
    case ALL_RECORD_BY_BETWEEN_DATE:         //批量查询所有的记录通过时间
        (void)ExtractFromRecordTab(dm, resObj, 0);
        break;
    case RECORD_CNT:
        dm->GetValue(0, resObj.reservedInt1);
        break;
    case INVALID:                            //无效的查询
        break;
    default:
        break;
    }
}

int ImportRecordQuery::ExtractFromRecordTab(IDataManipulation* dm, 
                           DQLBase<Record>::ResObjType& resObj, int startIndex) const
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
        } // namespace history
    } // namespace ecsdata
} // namespace ecs
