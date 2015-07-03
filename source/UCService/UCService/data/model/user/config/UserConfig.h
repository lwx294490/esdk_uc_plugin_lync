#pragma once
#include "data\model\DataModelBase.h"
#include "data\DataType.h"
#define USERCONFIG_TAB "UserConfigTab"
#define ONLINETIP_TAB "OnlineTipTab"
#define SMSSIGNATURE_TAB "SMSSignatureTab"

namespace ecs {
  namespace ecsdata {

class   CreateUserConfigTabCommand : public DDLBase
{
public:
  CreateUserConfigTabCommand() : DDLBase(USERDB_NAME) {}

protected:
  virtual void ComposeSQL(std::string & sql);

};

class   AddUserConfigCommand 
  : public DMLBase<ConfigPair>
{
public:
  AddUserConfigCommand() : DMLBase<ConfigPair>(USERDB_NAME) {}

  DEFINE_BATCH_SINGLE_ADD_MOTHOD(AddUserConfigCommand)

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<ConfigPair>::ArgObjType & argObj);

};

class   RemoveUserConfigCommand 
  : public DMLBase<ConfigPair>
{
public:
  RemoveUserConfigCommand() : DMLBase<ConfigPair>(USERDB_NAME) {}

public:
  static bool RemoveByConfigKey(const std::string & key);

protected:
  enum
  {
    KEY, 
    ALL, 
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<ConfigPair>::ArgObjType & argObj);

};

class   UserConfigQuery 
  : public DQLBase<ConfigPair>
{
public:
  UserConfigQuery() : DQLBase<ConfigPair>(USERDB_NAME) {}

public:
  static int QueryAll(ResCtnType & resCtn);
  static bool QueryByKey(const std::string & key, 
    DQLBase<ConfigPair>::ResObjType & resObj);

protected:
  enum
  {
    KEY, 
    ALL, 
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DQLBase<ConfigPair>::ArgObjType & argObj);
  virtual void Extract(IDataManipulation * dm, 
    DQLBase<ConfigPair>::ResObjType & resObj)
  { ExtractFromUserConfigTab(dm, resObj, 0); }

  static int ExtractFromUserConfigTab(IDataManipulation * dm, 
    DQLBase<ConfigPair>::ResObjType & resObj, int startIndex);

};

///////////////////////////////////////////////////////////////////////////
class   CreateOnlineTipTabCommand : public DDLBase
{
public:
  CreateOnlineTipTabCommand() : DDLBase(USERDB_NAME) {}

protected:
  virtual void ComposeSQL(std::string & sql);

};

class   AddOnlineTipCommand 
  : public DMLBase<std::string>
{
public:
  AddOnlineTipCommand() : DMLBase<std::string>(USERDB_NAME) {}

  DEFINE_BATCH_SINGLE_ADD_MOTHOD(AddOnlineTipCommand)

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<std::string>::ArgObjType & argObj);

};

class   RemoveOnlineTipCommand 
  : public DMLBase<std::string>
{
public:
  RemoveOnlineTipCommand() : DMLBase(USERDB_NAME) {}

public:
  static int RemoveAll();
  static bool RemoveByAccount(const std::string & account);

protected:
  enum
  {
    ALL, 
    ACCOUNT,
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, const ArgObjType & argObj);

};

class   OnlineTipQuery 
  : public DQLBase<std::string>
{
public:
  OnlineTipQuery() : DQLBase<std::string>(USERDB_NAME) {}

public:
  static int QueryAll(DQLBase<std::string>::ResCtnType & resCtn);

protected:
  enum
  {
    ALL, 
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DQLBase<std::string>::ArgObjType & argObj);
  virtual void Extract(IDataManipulation * dm, 
    DQLBase<std::string>::ResObjType & resObj)
  { ExtractFromOnlineTipTab(dm, resObj, 0); }

  static int ExtractFromOnlineTipTab(IDataManipulation * dm, 
    DQLBase<std::string>::ResObjType & resObj, int startIndex);

};

///////////////////////////////////////////////////////////////////////////
class   CreateSMSSignatureTabCommand : public DDLBase
{
public:
  CreateSMSSignatureTabCommand() : DDLBase(USERDB_NAME) {}

protected:
  virtual void ComposeSQL(std::string & sql);

};

class   AddSMSSignatureCommand 
  : public DMLBase<std::string>
{
public:
  AddSMSSignatureCommand() : DMLBase<std::string>(USERDB_NAME) {}

  DEFINE_BATCH_SINGLE_ADD_MOTHOD(AddSMSSignatureCommand)

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<std::string>::ArgObjType & argObj);

};

class   RemoveSMSSignatureCommand 
  : public DMLBase<std::string>
{
public:
  RemoveSMSSignatureCommand() : DMLBase(USERDB_NAME) {}

public:
  static int RemoveAll();
  static bool RemoveBySignature(const std::string & signature);

protected:
  enum
  {
    ALL, 
    SIGNATURE,
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, const ArgObjType & argObj);

};

class   SMSSignatureQuery 
  : public DQLBase<std::string>
{
public:
  SMSSignatureQuery() : DQLBase<std::string>(USERDB_NAME) {}

public:
  static int QueryAll(DQLBase<std::string>::ResCtnType & resCtn);

protected:
  enum
  {
    ALL, 
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DQLBase<std::string>::ArgObjType & argObj);
  virtual void Extract(IDataManipulation * dm, 
    DQLBase<std::string>::ResObjType & resObj)
  { ExtractFromSMSSignatureTab(dm, resObj, 0); }

  static int ExtractFromSMSSignatureTab(IDataManipulation * dm, 
    DQLBase<std::string>::ResObjType & resObj, int startIndex);

};

  } // namespace ecsdata
} // namespace ecs
