#include "stdafx.h"
#include "data/model/DBVersion.h"

#include "Log.h"

using namespace std;

namespace ecs {
  namespace ecsdata {

///////////////////////////////////////////////////////////////////////////
void CreateDBVersionTabCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "CREATE TABLE IF NOT EXISTS "DBVERSION_TAB
    "( VERSION_KEY    VARCHAR(20) NOT NULL PRIMARY KEY"
    ", VERSION_VALUE  VARCHAR(20)"
    ");";
}

///////////////////////////////////////////////////////////////////////////
void AddDBVersionCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "INSERT OR REPLACE INTO "DBVERSION_TAB
    "( VERSION_KEY"
    ", VERSION_VALUE"
    ") VALUES ( ?, ? );";
}

void AddDBVersionCommand::Bind(IDataManipulation * dm, 
                               const DMLBase<ConfigPair>::ArgObjType & argObj)
{
  //INFO_PARAM2(argObj.strKey, argObj.strValue);

  int i = 0;
  dm->Bind(++i, argObj.strKey);
  dm->Bind(++i, argObj.strValue);
}

bool AddDBVersionCommand::AddByKeyValue(
  const std::string key, const std::string val)
{
  ecs::ecsdata::ConfigPair argObj;
  argObj.strKey = key;
  argObj.strValue = val;

  SingleExecute(0, argObj);

  DEBUG_LOG("key=%s, val=%s, changed=%d",key.c_str(), val.c_str(), changed);
  return changed == 1;
}

///////////////////////////////////////////////////////////////////////////
void RemoveDBVersionCommand::ComposeSQL(std::string & sql)
{
  const std::string DELETE_USERCONFIG = "DELETE FROM "DBVERSION_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case KEY:
    (void)whereClause.append("VERSION_KEY = ?");
    break;
  default:
    WARN_LOG("unknown type : %d",type_);
    sql = "";
    return;
  }

  sql = DELETE_USERCONFIG + whereClause + ";";
}

void RemoveDBVersionCommand::Bind(IDataManipulation * dm, 
                                  const DMLBase<ConfigPair>::ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case KEY:
    //INFO_PARAM1(argObj.strKey);
    dm->Bind(++i, argObj.strKey);
    break;
  default:
    WARN_LOG("unknown type : %d",type_);
    break;
  }
}

bool RemoveDBVersionCommand::RemoveByKey(const std::string & key)
{
  ecs::ecsdata::ConfigPair argObj;
  argObj.strKey = key;

  SingleExecute(KEY, argObj);

  DEBUG_LOG("key=%s, changed=%d",key.c_str(), changed);
  return changed == 1;
}

///////////////////////////////////////////////////////////////////////////
void DBVersionQuery::ComposeSQL(std::string & sql)
{
  const std::string QUERY_DBVERSION = "SELECT * FROM "DBVERSION_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case KEY:
    (void)whereClause.append("VERSION_KEY = ?");
    break;
  default:
    WARN_LOG("unknown type : %d",type_);
    sql = "";
    return;
  }

  sql = QUERY_DBVERSION + whereClause + ";";
}

void DBVersionQuery::Bind(IDataManipulation * dm, 
                          const DQLBase<ConfigPair>::ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case KEY:
    ////INFO_PARAM1(argObj.strKey);
    dm->Bind(++i, argObj.strKey);
    break;
  default:
    WARN_LOG("unknown type : %d",type_);
    break;
  }
}

//static 
int DBVersionQuery::ExtractFromDBVersionTab(IDataManipulation * dm, 
                                            DQLBase<ConfigPair>::ResObjType & resObj, int startIndex)
{
  int i = 0;

  dm->GetValue(startIndex + i++, resObj.strKey);
  dm->GetValue(startIndex + i++, resObj.strValue);

  return i;
}

std::string DBVersionQuery::QueryByKey(const std::string & key)
{
  SetType(KEY);

  ecs::ecsdata::ConfigPair argObj;
  std::vector<ecs::ecsdata::ConfigPair> resCtn;

  argObj.strKey = key;
  Execute(argObj, resCtn);

  std::string res;
  if (resCtn.size() > 0)
  {
    res = resCtn[0].strValue;
  }

  DEBUG_LOG("key=%s, res=%d",key.c_str(), res);

  return res;
}

  }
}
