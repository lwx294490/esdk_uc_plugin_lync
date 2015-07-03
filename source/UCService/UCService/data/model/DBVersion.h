#pragma once

#define DBVERSION_TAB "DBVersionTab"


namespace ecs {
  namespace ecsdata {

class   CreateDBVersionTabCommand : public DDLBase
{
public:
  CreateDBVersionTabCommand(const std::string & dbName) : DDLBase(dbName) {}

protected:
  virtual void ComposeSQL(std::string & sql);

};

class   AddDBVersionCommand 
  : public DMLBase<ConfigPair>
{
public:
  AddDBVersionCommand(const std::string & dbName) 
    : DMLBase<ConfigPair>(dbName) {}

public:
  bool AddByKeyValue(const std::string key, const std::string val);

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<ConfigPair>::ArgObjType & argObj);

};

class   RemoveDBVersionCommand 
  : public DMLBase<ConfigPair>
{
public:
  RemoveDBVersionCommand(const std::string & dbName) 
    : DMLBase<ConfigPair>(dbName) {}

public:
  bool RemoveByKey(const std::string & key);

public:
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

class   DBVersionQuery 
  : public DQLBase<ConfigPair>
{
public:
  DBVersionQuery(const std::string & dbName) 
    : DQLBase<ConfigPair>(dbName) {}

public:
  std::string QueryByKey(const std::string & key);

public:
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
  { ExtractFromDBVersionTab(dm, resObj, 0); }

  static int ExtractFromDBVersionTab(IDataManipulation * dm, 
    DQLBase<ConfigPair>::ResObjType & resObj, int startIndex);

};

  } // namespace ecsdata
} // namespace ecs
