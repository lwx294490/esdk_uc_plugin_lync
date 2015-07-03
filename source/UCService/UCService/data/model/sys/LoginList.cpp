#include "stdafx.h"
#include "data/model/sys/LoginList.h"

#include "Log.h"

using namespace std;

namespace ecs {
  namespace ecsdata {

///////////////////////////////////////////////////////////////////////////
void CreateLoginListTabCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "CREATE TABLE IF NOT EXISTS "LOGINLIST_TAB
    "( ACCOUNT VARCHAR(64) NOT NULL PRIMARY KEY ON CONFLICT REPLACE"
    ", PASSWORD VARCHAR(50) NOT NULL"
    ", REMPWD BOOLEAN NOT NULL DEFAULT(0)"
    ", AUTOLOGIN BOOLEAN NOT NULL DEFAULT(0)"
    ", LOGINMODE INTEGER NOT NULL DEFAULT(0)"
    ", USESVN1 BOOLEAN NOT NULL DEFAULT(0)"
    ", SVNACC1 VARCHAR(64) NOT NULL"
    ", SVNPSW1 VARCHAR(64) NOT NULL"
	", USESVN2 BOOLEAN NOT NULL DEFAULT(0)"
    ", SVNACC2 VARCHAR(64) NOT NULL"
    ", SVNPSW2 VARCHAR(64) NOT NULL"

    ", LOGIN_FLAG INTEGER NOT NULL DEFAULT(0)"
    ", RESERVED_INT1 INTEGER NOT NULL DEFAULT(0)"
    ", RESERVED_INT2 INTEGER NOT NULL DEFAULT(0)"
    ", RESERVED_INT3 INTEGER NOT NULL DEFAULT(0)"
    ", RESERVED_STR1 VARCHAR(1024)"
    ", RESERVED_STR2 VARCHAR(1024)"
    ", RESERVED_STR3 VARCHAR(1024)"

    ");";
}

///////////////////////////////////////////////////////////////////////////
void AddLoginListCommand::ComposeSQL(std::string & sql)
{
  const std::string INSERT_LOGINLIST_TAB = 
    "INSERT OR REPLACE INTO "LOGINLIST_TAB
    "( ACCOUNT "
    ", PASSWORD"
    ", REMPWD"
    ", AUTOLOGIN"
    ", LOGINMODE"
    ", USESVN1"
    ", SVNACC1"
    ", SVNPSW1"
	", USESVN2"
    ", SVNACC2"
    ", SVNPSW2"

    ", LOGIN_FLAG"
    ", RESERVED_INT1"
    ", RESERVED_INT2"
    ", RESERVED_INT3"
    ", RESERVED_STR1"
    ", RESERVED_STR2"
    ", RESERVED_STR3"

    ") VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? );";

  sql = INSERT_LOGINLIST_TAB;
}

void AddLoginListCommand::Bind(IDataManipulation * dm, 
  const DMLBase<LoginListItem>::ArgObjType & argObj)
{
  //INFO_PARAM1(argObj.account);

  int i = 0;
  dm->Bind(++i, argObj.account);
  dm->Bind(++i, argObj.password);
  dm->Bind(++i, argObj.rememberPwd);
  dm->Bind(++i, argObj.autoLogin);
  dm->Bind(++i, argObj.loginMode);
  dm->Bind(++i, argObj.svnacc1);
  dm->Bind(++i, argObj.svnpsw1);
  dm->Bind(++i, argObj.usesvn1);
  dm->Bind(++i, argObj.svnacc2);
  dm->Bind(++i, argObj.svnpsw2);
  dm->Bind(++i, argObj.usesvn2);

  dm->Bind(++i, argObj.loginFlag);
  dm->Bind(++i, argObj.reservedInt1);
  dm->Bind(++i, argObj.reservedInt2);
  dm->Bind(++i, argObj.reservedInt3);
  dm->Bind(++i, argObj.reservedStr1);
  dm->Bind(++i, argObj.reservedStr2);
  dm->Bind(++i, argObj.reservedStr3);
}

///////////////////////////////////////////////////////////////////////////
void UpdateLoginListCommand::ComposeSQL(std::string & sql)
{
  sql = "UPDATE "LOGINLIST_TAB" SET ";

  switch (type_)
  {
  case PWD:
    (void)sql.append("PASSWORD = ? ");
    break;
  case REMPWD:
    (void)sql.append("REMPWD = ? ");
    break;
  case AUTOLOGIN:
    (void)sql.append("AUTOLOGIN = ? ");
    break;
  case LOGINMODE:
    (void)sql.append("LOGINMODE = ? ");
    break;
  case SVNCONFIG:
    (void)sql.append("USESVN1 = ?, SVNACC1 = ?, SVNPSW1 = ?, USESVN2 = ?, SVNACC2 = ?, SVNPSW2 = ? ");
    break;
  case HEADIMG:
    (void)sql.append("RESERVED_STR1 = ? ");
    break;
  case HDDID:
    (void)sql.append("RESERVED_STR2 = ? ");
    break;
  default:
    sql.clear();
    WARN_LOG("unknown type : %d",type_);
    return;
  }

  (void)sql.append("WHERE ACCOUNT = ?");
}

void UpdateLoginListCommand::Bind(IDataManipulation * dm, 
  const DMLBase<LoginListItem>::ArgObjType & argObj)
{
  //INFO_PARAM1(argObj.account);

  int i = 0;
  switch (type_)
  {
  case PWD:
    //INFO_PARAM1(argObj.password);
    dm->Bind(++i, argObj.password);
    break;
  case REMPWD:
    //INFO_PARAM1(argObj.rememberPwd);
    dm->Bind(++i, argObj.rememberPwd);
    break;
  case AUTOLOGIN:
    //INFO_PARAM1(argObj.autoLogin);
    dm->Bind(++i, argObj.autoLogin);
    break;
  case LOGINMODE:
    //INFO_PARAM1(argObj.loginMode);
    dm->Bind(++i, argObj.loginMode);
    break;
  case SVNCONFIG:
    //INFO_PARAM6(argObj.usesvn1, argObj.svnacc1, argObj.svnpsw1, argObj.usesvn2, argObj.svnacc2, argObj.svnpsw2);
	dm->Bind(++i, argObj.usesvn1);
	dm->Bind(++i, argObj.svnacc1);
	dm->Bind(++i, argObj.svnpsw1);
	dm->Bind(++i, argObj.usesvn2);
	dm->Bind(++i, argObj.svnacc2);
	dm->Bind(++i, argObj.svnpsw2);
	break;
  case HEADIMG:
      //INFO_PARAM1(argObj.reservedStr1);
      dm->Bind(++i, argObj.reservedStr1);
      break;
  case HDDID:
      //INFO_PARAM1(argObj.reservedStr2);
      dm->Bind(++i, argObj.reservedStr2);
      break;
  default:
    WARN_LOG("unknown type : %d",type_);
    return;
  }

  dm->Bind(++i, argObj.account);
}

//static 
bool UpdateLoginListCommand::UpdatePasswordByAccount(
  const std::string & account, const std::string & password)
{
  //TRACE_FUNC2(account, password);

  LoginListItem argObj;
  argObj.account = account;
  argObj.password = password;

  int nChanged = UpdateLoginListCommand::UpdatePassword(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged == 1;
}

//static 
bool UpdateLoginListCommand::UpdateRememberPasswordByAccount(
  const std::string & account, bool rememberPwd)
{
  //TRACE_FUNC2(account, rememberPwd);

  LoginListItem argObj;
  argObj.account = account;
  argObj.rememberPwd = rememberPwd;

  int nChanged = UpdateLoginListCommand::UpdateRememberPassword(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged == 1;
}

//static 
bool UpdateLoginListCommand::UpdateAutoLoginByAccount(
  const std::string & account, bool autoLogin)
{
  //TRACE_FUNC2(account, autoLogin);

  LoginListItem argObj;
  argObj.account = account;
  argObj.autoLogin = autoLogin;

  int nChanged = UpdateLoginListCommand::UpdateAutoLogin(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged == 1;
}

//static 
bool UpdateLoginListCommand::UpdateLoginModeByAccount(
  const std::string & account, int loginMode)
{
  //TRACE_FUNC2(account, loginMode);

  LoginListItem argObj;
  argObj.account = account;
  argObj.loginMode = loginMode;

  int nChanged = UpdateLoginListCommand::UpdateLoginMode(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged == 1;
}

//static 
bool UpdateLoginListCommand::UpdateSVNConfigByAccount(
  const std::string & account, bool usesvn1, 
  const std::string & svnacc1, const std::string & svnpsw1,
  bool usesvn2, 
  const std::string & svnacc2, const std::string & svnpsw2
  )
{
  //TRACE_FUNC1(account);
  DEBUG_LOG("usesvn1=%d, svnacc1=%s, svnpsw1=%s, usesvn2=%d, svnacc2=%s, svnpsw2=%s"
	  , usesvn1
	  , svnacc1.c_str()
	  , svnpsw1.c_str()
	  , usesvn2
	  , svnacc2.c_str()
	  , svnpsw2.c_str());

  LoginListItem argObj;
  argObj.account = account;
  argObj.usesvn1 = usesvn1;
  argObj.svnacc1 = svnacc1;
  argObj.svnpsw1 = svnpsw1;
  argObj.usesvn2 = usesvn2;
  argObj.svnacc2 = svnacc2;
  argObj.svnpsw2 = svnpsw2;

  int nChanged = UpdateLoginListCommand::UpdateSVNConfig(argObj);

  //INFO_PARAM1(nChanged);
  return nChanged == 1;
}

//static 
bool UpdateLoginListCommand::UpdateHddIDByAccount(
    const std::string & account, const std::string& id)
{
    //TRACE_FUNC2(account, id);

    LoginListItem argObj;
    argObj.account = account;

    argObj.reservedStr2 = id;
    int nChanged = UpdateLoginListCommand::UpdateHddId(argObj);

    //INFO_PARAM1(nChanged);
    return nChanged == 1;
}

bool UpdateLoginListCommand::UpdatePortraitPathByAccount(
    const std::string & account, const std::string& path)
{
    //TRACE_FUNC2(account, path);

    LoginListItem argObj;
    argObj.account = account;
    argObj.reservedStr1 = path;

    int nChanged = UpdateLoginListCommand::UpdatePortraitPath(argObj);

    //INFO_PARAM1(nChanged);
    return nChanged == 1;
}


///////////////////////////////////////////////////////////////////////////
void RemoveLoginListCommand::ComposeSQL(std::string & sql)
{
  const std::string DELETE_LOGINLIST = "DELETE FROM "LOGINLIST_TAB;

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
    WARN_LOG("unknown type : %d",type_);
    sql = "";
    return;
  }

  sql = DELETE_LOGINLIST + whereClause + ";";
}

void RemoveLoginListCommand::Bind(IDataManipulation * dm, 
  const DMLBase<LoginListItem>::ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case ACCOUNT:
    //INFO_PARAM1(argObj.account);
    dm->Bind(++i, argObj.account);
    break;
  default:
    WARN_LOG("unknown type : %d",type_);
    break;
  }
}

//static 
bool RemoveLoginListCommand::RemoveByAccount(const std::string & account)
{
  //TRACE_FUNC1(account);

  ArgObjType argObj;
  argObj.account = account;

  RemoveLoginListCommand cmd;
  cmd.SingleExecute(ACCOUNT, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed == 1;
}

///////////////////////////////////////////////////////////////////////////
void LoginListQuery::ComposeSQL(std::string & sql)
{
  const std::string QUERY_LOGINLIST = "SELECT * FROM "LOGINLIST_TAB;

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
    WARN_LOG("unknown type : %d",type_);
    sql.clear();
    return;
  }

  sql = QUERY_LOGINLIST + whereClause + " ORDER BY rowid DESC;";
}

void LoginListQuery::Bind(IDataManipulation * dm, 
  const DQLBase<LoginListItem>::ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case ACCOUNT:
    ////INFO_PARAM1(argObj.account);
    dm->Bind(++i, argObj.account);
    break;
  default:
    WARN_LOG("unknown type : %d",type_);
    break;
  }
}

//static 
int LoginListQuery::ExtractFromLoginListTab(IDataManipulation * dm, 
  DQLBase<LoginListItem>::ResObjType & resObj, int startIndex)
{
  int i = 0;

  dm->GetValue(startIndex + i++, resObj.account);
  dm->GetValue(startIndex + i++, resObj.password);
  dm->GetValue(startIndex + i++, resObj.rememberPwd);
  dm->GetValue(startIndex + i++, resObj.autoLogin);
  dm->GetValue(startIndex + i++, resObj.loginMode);
  dm->GetValue(startIndex + i++, resObj.usesvn1);
  dm->GetValue(startIndex + i++, resObj.svnacc1);
  dm->GetValue(startIndex + i++, resObj.svnpsw1);
  dm->GetValue(startIndex + i++, resObj.usesvn2);
  dm->GetValue(startIndex + i++, resObj.svnacc2);
  dm->GetValue(startIndex + i++, resObj.svnpsw2);

  dm->GetValue(startIndex + i++, resObj.loginFlag);
  dm->GetValue(startIndex + i++, resObj.reservedInt1);
  dm->GetValue(startIndex + i++, resObj.reservedInt2);
  dm->GetValue(startIndex + i++, resObj.reservedInt3);
  dm->GetValue(startIndex + i++, resObj.reservedStr1);
  dm->GetValue(startIndex + i++, resObj.reservedStr2);
  dm->GetValue(startIndex + i++, resObj.reservedStr3);

  return i;
}

//static 
int LoginListQuery::QueryAll(DQLBase<LoginListItem>::ResCtnType & resCtn)
{
  LoginListItem argObj;

  LoginListQuery qry;
  qry.BatchExecute(ALL, argObj, resCtn);

  DEBUG_LOG("qry.count=%d",qry.count);
  return qry.count;
}

//static 
bool LoginListQuery::QueryByAccount(const std::string & account, 
  DQLBase<LoginListItem>::ResObjType & resObj)
{
  LoginListItem argObj;
  argObj.account = account;

  LoginListQuery qry;
  bool ret = qry.SingleExecute(ACCOUNT, argObj, resObj);

  DEBUG_LOG("account=%s, qry.count=%d",account.c_str(), qry.count);
  return ret;
}

  }
}
