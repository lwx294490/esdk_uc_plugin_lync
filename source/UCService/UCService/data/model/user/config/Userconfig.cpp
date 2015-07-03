#include "stdafx.h"
#include "data/model/user/config/Userconfig.h"

#include "Log.h"

using namespace std;

namespace ecs {
  namespace ecsdata {

///////////////////////////////////////////////////////////////////////////
void CreateUserConfigTabCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "CREATE TABLE IF NOT EXISTS "USERCONFIG_TAB
    "( KEY    VARCHAR(20) NOT NULL PRIMARY KEY"
    ", VALUE  VARCHAR(20)"
    ");";
}

///////////////////////////////////////////////////////////////////////////
void AddUserConfigCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "INSERT OR REPLACE INTO "USERCONFIG_TAB
    "( KEY"
    ", VALUE"
    ") VALUES ( ?, ? );";
}

void AddUserConfigCommand::Bind(IDataManipulation * dm, 
  const DMLBase<ConfigPair>::ArgObjType & argObj)
{
  //INFO_PARAM2(argObj.strKey, argObj.strValue);

  int i = 0;
  dm->Bind(++i, argObj.strKey);
  dm->Bind(++i, argObj.strValue);
}

///////////////////////////////////////////////////////////////////////////
void RemoveUserConfigCommand::ComposeSQL(std::string & sql)
{
  const std::string DELETE_USERCONFIG = "DELETE FROM "USERCONFIG_TAB;

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
    WARN_LOG("unknown type : %d" ,type_);
    sql = "";
    return;
  }

  sql = DELETE_USERCONFIG + whereClause + ";";
}

void RemoveUserConfigCommand::Bind(IDataManipulation * dm, 
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
    WARN_LOG("unknown type : %d" ,type_);
    break;
  }
}

//static 
bool RemoveUserConfigCommand::RemoveByConfigKey(const std::string & key)
{
  //TRACE_FUNC1(key);

  ConfigPair argObj;
  argObj.strKey = key;

  RemoveUserConfigCommand cmd;
  cmd.SingleExecute(KEY, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed == 1;
}

///////////////////////////////////////////////////////////////////////////
void UserConfigQuery::ComposeSQL(std::string & sql)
{
  const std::string QUERY_USERCONFIG = "SELECT * FROM "USERCONFIG_TAB;

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
    WARN_LOG("unknown type : %d" ,type_);
    sql = "";
    return;
  }

  sql = QUERY_USERCONFIG + whereClause + ";";
}

void UserConfigQuery::Bind(IDataManipulation * dm, 
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
    WARN_LOG("unknown type : %d" ,type_);
    break;
  }
}

//static 
int UserConfigQuery::ExtractFromUserConfigTab(IDataManipulation * dm, 
  DQLBase<ConfigPair>::ResObjType & resObj, int startIndex)
{
  int i = 0;

  dm->GetValue(startIndex + i++, resObj.strKey);
  dm->GetValue(startIndex + i++, resObj.strValue);

  return i;
}

//static 
int UserConfigQuery::QueryAll(DQLBase<ConfigPair>::ResCtnType & resCtn)
{
  ConfigPair argObj;

  UserConfigQuery qry;
  qry.BatchExecute(ALL, argObj, resCtn);

  DEBUG_LOG("qry.count=%d",qry.count);
  return qry.count;
}

//static 
bool UserConfigQuery::QueryByKey(const std::string & key, 
                                 DQLBase<ConfigPair>::ResObjType & resObj)
{
  ConfigPair argObj;
  argObj.strKey = key;

  UserConfigQuery qry;
  bool ret = qry.SingleExecute(KEY, argObj, resObj);

  DEBUG_LOG("key=%s, resObj.strValue=%s",key.c_str(), resObj.strValue.c_str());
  return ret;
}

///////////////////////////////////////////////////////////////////////////
void CreateOnlineTipTabCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "CREATE TABLE IF NOT EXISTS "ONLINETIP_TAB
    "( ACCOUNT VARCHAR(64) NOT NULL PRIMARY KEY"
    ");";
}

///////////////////////////////////////////////////////////////////////////
void AddOnlineTipCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "INSERT OR REPLACE INTO "ONLINETIP_TAB
    "( ACCOUNT"
    ") VALUES( ? );";
}

void AddOnlineTipCommand::Bind(IDataManipulation * dm, 
  const DMLBase<std::string>::ArgObjType & argObj)
{
  int i = 0;

  //INFO_PARAM1(argObj);
  dm->Bind(++i, argObj);
}

///////////////////////////////////////////////////////////////////////////
void RemoveOnlineTipCommand::ComposeSQL(std::string & sql)
{
  const std::string DELETE_ONLINETIPTAB = "DELETE FROM "ONLINETIP_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case ACCOUNT:
    (void)whereClause.append("ACCOUNT = ?");
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    sql = "";
    return;
  }

  sql = DELETE_ONLINETIPTAB + whereClause + ";";
}

void RemoveOnlineTipCommand
::Bind(IDataManipulation * dm, const ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case ACCOUNT:
    //INFO_PARAM1(argObj);
    dm->Bind(++i, argObj);
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    break;
  }
}

//static 
int RemoveOnlineTipCommand::RemoveAll()
{
  std::string argObj;

  RemoveOnlineTipCommand cmd;
  cmd.SingleExecute(ALL, argObj);

  DEBUG_LOG("cmd.changed=%d",cmd.changed);
  return cmd.changed;
}

//static 
bool RemoveOnlineTipCommand::RemoveByAccount(const std::string & account)
{
  RemoveOnlineTipCommand cmd;
  cmd.SingleExecute(ACCOUNT, account);

  DEBUG_LOG("account=%s, cmd.changed=%d",account.c_str(), cmd.changed);
  return cmd.changed == 1;
}

///////////////////////////////////////////////////////////////////////////
void OnlineTipQuery::ComposeSQL(std::string & sql)
{
  sql = "SELECT * FROM "ONLINETIP_TAB";";
}

void OnlineTipQuery
::Bind(IDataManipulation * /*dm*/, const ArgObjType & /*argObj*/)
{
}

int OnlineTipQuery::ExtractFromOnlineTipTab(IDataManipulation * dm, 
  ResObjType & resObj, int startIndex)
{
  int i = 0;

  dm->GetValue(startIndex + i++, resObj);

  return i;
}

//static 
int OnlineTipQuery::QueryAll(ResCtnType & resCtn)
{
  std::string argObj;

  OnlineTipQuery qry;
  qry.BatchExecute(ALL, argObj, resCtn);

  DEBUG_LOG("qry.count=%d",qry.count);
  return qry.count;
}

///////////////////////////////////////////////////////////////////////////
void CreateSMSSignatureTabCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "CREATE TABLE IF NOT EXISTS "SMSSIGNATURE_TAB
    "( SIGNATURE VARCHAR(1024) NOT NULL PRIMARY KEY"
    ");";
}

///////////////////////////////////////////////////////////////////////////
void AddSMSSignatureCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "INSERT OR REPLACE INTO "SMSSIGNATURE_TAB
    "( SIGNATURE"
    ") VALUES( ? );";
}

void AddSMSSignatureCommand::Bind(IDataManipulation * dm, 
  const DMLBase<std::string>::ArgObjType & argObj)
{
  int i = 0;

  //INFO_PARAM1(argObj);
  dm->Bind(++i, argObj);
}

///////////////////////////////////////////////////////////////////////////
void RemoveSMSSignatureCommand::ComposeSQL(std::string & sql)
{
  const std::string DELETE_SMSSIGNATURETAB = "DELETE FROM "SMSSIGNATURE_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case SIGNATURE:
    (void)whereClause.append("SIGNATURE = ?");
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    sql = "";
    return;
  }

  sql = DELETE_SMSSIGNATURETAB + whereClause + ";";
}

void RemoveSMSSignatureCommand
::Bind(IDataManipulation * dm, const ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case SIGNATURE:
    //INFO_PARAM1(argObj);
    dm->Bind(++i, argObj);
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    break;
  }
}

//static 
int RemoveSMSSignatureCommand::RemoveAll()
{
  std::string argObj;

  RemoveSMSSignatureCommand cmd;
  cmd.SingleExecute(ALL, argObj);

  DEBUG_LOG("cmd.changed=%d",cmd.changed);
  return cmd.changed;
}

//static 
bool RemoveSMSSignatureCommand::RemoveBySignature(const std::string & signature)
{
  RemoveSMSSignatureCommand cmd;
  cmd.SingleExecute(SIGNATURE, signature);

  DEBUG_LOG("signature=%s, cmd.changed=%d",signature.c_str(), cmd.changed);
  return cmd.changed == 1;
}

///////////////////////////////////////////////////////////////////////////
void SMSSignatureQuery::ComposeSQL(std::string & sql)
{
  sql = "SELECT * FROM "SMSSIGNATURE_TAB";";
}

void SMSSignatureQuery
::Bind(IDataManipulation * /*dm*/, const ArgObjType & /*argObj*/)
{
}

int SMSSignatureQuery::ExtractFromSMSSignatureTab(IDataManipulation * dm, 
  ResObjType & resObj, int startIndex)
{
  int i = 0;

  dm->GetValue(startIndex + i++, resObj);

  return i;
}

//static 
int SMSSignatureQuery::QueryAll(ResCtnType & resCtn)
{
  std::string argObj;

  SMSSignatureQuery qry;
  qry.BatchExecute(ALL, argObj, resCtn);

  DEBUG_LOG("qry.count=%d",qry.count);
  return qry.count;
}

  } // namespace ecsdata
} // namespace ecs
