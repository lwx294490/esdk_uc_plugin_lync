#include "stdafx.h"
#include "data/model/sys/SysConfig.h"
#include "Log.h"

using namespace std;

namespace ecs {
  namespace ecsdata {

///////////////////////////////////////////////////////////////////////////
void CreateSysConfigTabCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "CREATE TABLE IF NOT EXISTS "SYSCONFIG_TAB
    "( KEY    VARCHAR(20) NOT NULL PRIMARY KEY"
    ", VALUE  VARCHAR(20)"
    ");";
}

///////////////////////////////////////////////////////////////////////////
void AddSysConfigCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "INSERT OR REPLACE INTO "SYSCONFIG_TAB
    "( KEY"
    ", VALUE"
    ") VALUES ( ?, ? );";
}

void AddSysConfigCommand::Bind(IDataManipulation * dm, 
  const DMLBase<ConfigPair>::ArgObjType & argObj)
{
  //INFO_PARAM2(argObj.strKey, argObj.strValue);

  int i = 0;
  dm->Bind(++i, argObj.strKey);
  dm->Bind(++i, argObj.strValue);
}

///////////////////////////////////////////////////////////////////////////
void RemoveSysConfigCommand::ComposeSQL(std::string & sql)
{
  const std::string DELETE_SYSCONFIG = "DELETE FROM "SYSCONFIG_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case KEY:
    (void)whereClause.append("KEY = ?");
    break;
  default:
    WARN_LOG("unknown type : %d",type_);
    sql = "";
    return;
  }

  sql = DELETE_SYSCONFIG + whereClause + ";";
}

void RemoveSysConfigCommand::Bind(IDataManipulation * dm, 
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

//static 
bool RemoveSysConfigCommand::RemoveByConfigKey(const std::string & key)
{
  //TRACE_FUNC1(key);

  ConfigPair argObj;
  argObj.strKey = key;

  RemoveSysConfigCommand cmd;
  cmd.SingleExecute(KEY, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed == 1;
}

///////////////////////////////////////////////////////////////////////////
void SysConfigQuery::ComposeSQL(std::string & sql)
{
  const std::string QUERY_SYSCONFIG = "SELECT * FROM "SYSCONFIG_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case KEY:
    (void)whereClause.append("KEY = ?");
    break;
  default:
    WARN_LOG("unknown type : %d",type_);
    sql = "";
    return;
  }

  sql = QUERY_SYSCONFIG + whereClause + ";";
}

void SysConfigQuery::Bind(IDataManipulation * dm, 
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
int SysConfigQuery::ExtractFromSysConfigTab(IDataManipulation * dm, 
  DQLBase<ConfigPair>::ResObjType & resObj, int startIndex)
{
  int i = 0;

  dm->GetValue(startIndex + i++, resObj.strKey);
  dm->GetValue(startIndex + i++, resObj.strValue);

  return i;
}

//static 
int SysConfigQuery::QueryAll(DQLBase<ConfigPair>::ResCtnType & resCtn)
{
  ConfigPair argObj;

  SysConfigQuery qry;
  qry.BatchExecute(ALL, argObj, resCtn);

  DEBUG_LOG("qry.count=%d",qry.count);
  return qry.count;
}

//static 
bool SysConfigQuery::QueryByKey(const std::string & key, 
  DQLBase<ConfigPair>::ResObjType & resObj)
{
  ConfigPair argObj;
  argObj.strKey = key;

  SysConfigQuery qry;
  bool ret = qry.SingleExecute(KEY, argObj, resObj);

  DEBUG_LOG("key=%s, resObj.strValue=%s",key.c_str(), resObj.strValue.c_str());
  return ret;
}

  }
}
