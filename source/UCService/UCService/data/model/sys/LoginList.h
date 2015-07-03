#pragma once

#define LOGINLIST_TAB "LoginListTab"

namespace ecs {
  namespace ecsdata {

class   CreateLoginListTabCommand : public DDLBase
{
public:
  CreateLoginListTabCommand() : DDLBase(SYSDB_NAME) {}

protected:
  virtual void ComposeSQL(std::string & sql);

};

class   AddLoginListCommand 
  : public DMLBase<LoginListItem>
{
public:
  AddLoginListCommand() : DMLBase<LoginListItem>(SYSDB_NAME) {}

  DEFINE_BATCH_SINGLE_ADD_MOTHOD(AddLoginListCommand)

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<LoginListItem>::ArgObjType & argObj);

};
class   UpdateLoginListCommand 
  : public DMLBase<LoginListItem>
{
public:
  UpdateLoginListCommand() : DMLBase<LoginListItem>(SYSDB_NAME) {}

public:
  static bool UpdatePasswordByAccount(
    const std::string & account, const std::string & password);
  static bool UpdateRememberPasswordByAccount(
    const std::string & account, bool rememberPwd);
  static bool UpdateAutoLoginByAccount(
    const std::string & account, bool autoLogin);
  static bool UpdateLoginModeByAccount(
    const std::string & account, int loginMode);
  static bool UpdateSVNConfigByAccount(const std::string & account, 
    bool usesvn1, const std::string & svnacc1, const std::string & svnpsw1,
	bool usesvn2, const std::string & svnacc2, const std::string & svnpsw2);
  static bool UpdatePortraitPathByAccount(const std::string & account, const std::string& path);
  static bool UpdateHddIDByAccount(const std::string & account, const std::string& id);

protected:
  enum
  {
    INVALID, 
    PWD, 
    REMPWD, 
    AUTOLOGIN, 
    LOGINMODE, 
    SVNCONFIG,
    HEADIMG,
    HDDID,
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(
    IDataManipulation * dm, const DMLBase<LoginListItem>::ArgObjType & argObj);

  DEFINE_SINGLE_EXECUTE_MOTHOD(
    UpdateLoginListCommand, UpdatePassword, PWD)
  DEFINE_SINGLE_EXECUTE_MOTHOD(
    UpdateLoginListCommand, UpdateRememberPassword, REMPWD)
  DEFINE_SINGLE_EXECUTE_MOTHOD(
    UpdateLoginListCommand, UpdateAutoLogin, AUTOLOGIN)
  DEFINE_SINGLE_EXECUTE_MOTHOD(
    UpdateLoginListCommand, UpdateLoginMode, LOGINMODE)
  DEFINE_SINGLE_EXECUTE_MOTHOD(
    UpdateLoginListCommand, UpdateSVNConfig, SVNCONFIG)
  DEFINE_SINGLE_EXECUTE_MOTHOD(
    UpdateLoginListCommand, UpdatePortraitPath, HEADIMG)
  DEFINE_SINGLE_EXECUTE_MOTHOD(
    UpdateLoginListCommand, UpdateHddId, HDDID)

};

class   RemoveLoginListCommand 
  : public DMLBase<LoginListItem>
{
public:
  RemoveLoginListCommand() : DMLBase<LoginListItem>(SYSDB_NAME) {}

public:
  static bool RemoveByAccount(const std::string & account);

protected:
  enum
  {
    ALL, 
    ACCOUNT, 
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<LoginListItem>::ArgObjType & argObj);

};

class   LoginListQuery 
  : public DQLBase<LoginListItem>
{
public:
  LoginListQuery() : DQLBase<LoginListItem>(SYSDB_NAME) {}

public:
  static int QueryAll(
    DQLBase<LoginListItem>::ResCtnType & resCtn);
  static bool QueryByAccount(const std::string & account, 
    DQLBase<LoginListItem>::ResObjType & resObj);

protected:
  enum
  {
    ALL, 
    ACCOUNT, 
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DQLBase<LoginListItem>::ArgObjType & argObj);
  virtual void Extract(IDataManipulation * dm, 
    DQLBase<LoginListItem>::ResObjType & resObj)
  { ExtractFromLoginListTab(dm, resObj, 0); }

  static int ExtractFromLoginListTab(IDataManipulation * dm, 
    DQLBase<LoginListItem>::ResObjType & resObj, int startIndex);

};

  }
}
