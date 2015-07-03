#pragma once
#include "data\model\DataModelBase.h"
#include "data\DataType.h"
#define TRANSFERNUMBER_TAB "TransferNumberTab"

namespace ecs {
  namespace ecsdata {

class   CreateTransferNumTabCommand : public DDLBase
{
public:
  CreateTransferNumTabCommand() : DDLBase(USERDB_NAME) {}

protected:
  virtual void ComposeSQL(std::string & sql);

};

class   AddTransferNumCommand 
  : public DMLBase<std::string>
{
public:
  AddTransferNumCommand() : DMLBase<std::string>(USERDB_NAME) {}

  DEFINE_BATCH_SINGLE_ADD_MOTHOD(AddTransferNumCommand)

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<std::string>::ArgObjType & argObj);

};

class   RemoveTransferNumCommand 
  : public DMLBase<std::string>
{
public:
  RemoveTransferNumCommand() : DMLBase(USERDB_NAME) {}

public:
  static int RemoveAll();
  static bool RemoveByNumber(const std::string & number);

protected:
  enum
  {
    ALL, 
    TRANSFERNUMBER,
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, const ArgObjType & argObj);

};

class   TransferNumQuery 
  : public DQLBase<std::string>
{
public:
  TransferNumQuery() : DQLBase<std::string>(USERDB_NAME) {}

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
  { ExtractFromTransferNumTab(dm, resObj, 0); }

  static int ExtractFromTransferNumTab(IDataManipulation * dm, 
    DQLBase<std::string>::ResObjType & resObj, int startIndex);

};

  }
}
