#pragma once

#define SYSCONFIG_TAB "SysConfigTab"

namespace ecs {
  namespace ecsdata {

class   CreateSysConfigTabCommand : public DDLBase
{
public:
  CreateSysConfigTabCommand() : DDLBase(SYSDB_NAME) {}

protected:
  virtual void ComposeSQL(std::string & sql);

};

class   AddSysConfigCommand 
  : public DMLBase<ConfigPair>
{
public:
  AddSysConfigCommand() : DMLBase<ConfigPair>(SYSDB_NAME) {}

  DEFINE_BATCH_SINGLE_ADD_MOTHOD(AddSysConfigCommand)

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<ConfigPair>::ArgObjType & argObj);

};

class   RemoveSysConfigCommand 
  : public DMLBase<ConfigPair>
{
public:
  RemoveSysConfigCommand() : DMLBase<ConfigPair>(SYSDB_NAME) {}

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

class   SysConfigQuery 
  : public DQLBase<ConfigPair>
{
public:
  SysConfigQuery() : DQLBase<ConfigPair>(SYSDB_NAME) {}

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
  { ExtractFromSysConfigTab(dm, resObj, 0); }

  static int ExtractFromSysConfigTab(IDataManipulation * dm, 
    DQLBase<ConfigPair>::ResObjType & resObj, int startIndex);

};

  }
}
