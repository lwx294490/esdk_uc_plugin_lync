#pragma once

//去掉缺省构造函数未定义的pclint1712 报告
//lint -e1712
//lint -e1713
//lint -e1942

#include "data/storage/DataStorage.h"
#include <vector>

namespace ecs {
  namespace ecsdata {

class IDataStorage;
class IDataManipulation;

///////////////////////////////////////////////////////////////////////////
class DataModel
{
public:
  void Init() const;
  void Uninit() const;

public:
  void CreateSysTables() const;
  void CreateUserTables() const;
  bool CheckUserTables() const;
  void CreateHistoryTables() const;
  bool JudgeColumnIsExist(const std::string& _tblName, const std::string& _columnName, 
      const std::string _newSql, const std::string& _dbName) const;
  void AlterHistoryTables(const std::string& _tblName, const std::string& _columnName, 
      const std::string _newSql, const std::string& _dbName) const;
  void CreateArchiveTables(const std::string& _dbName) const;
  void ClearUserTables() const;

  //singleton
public:
  static DataModel * Instance() {
    if (instance_ == NULL) 
      instance_ = new DataModel();
    return instance_;
  }
private:
  static DataModel * instance_;

}; // class DataModel

#define DATA_MODEL() (ecs::ecsdata::DataModel::Instance())

///////////////////////////////////////////////////////////////////////////
class Transanction
{
public:
  Transanction(IDataStorage * ds, bool active = true);
  ~Transanction();

  void Commit();

private:
  IDataStorage * ds_;
  const bool active_;
  bool nested_;
  bool commited_;

private:
  Transanction & operator=(const Transanction &);

}; // class Transanction

///////////////////////////////////////////////////////////////////////////
class DataModelBase
{
public:
  DataModelBase(const std::string & dsName, int type = 0);
  virtual ~DataModelBase() { ds_ = NULL; }

  virtual void SetType(int type) { type_ = type; }

protected:
  virtual void ComposeSQL(std::string & sql) = 0;

protected:
  IDataStorage * ds_;
  int type_;

}; // class DataModelBase

///////////////////////////////////////////////////////////////////////////
class DDLBase : public DataModelBase
{
public:
  DDLBase(const std::string & dsName) : DataModelBase(dsName) {}
  virtual ~DDLBase() {}

public:
  inline void Execute();

}; // class DDLBase

///////////////////////////////////////////////////////////////////////////
template<class ArgObjT, class ArgCtnT = std::vector<ArgObjT> >
class DMLBase : public DataModelBase
{
public:
  typedef ArgCtnT ArgCtnType;
  typedef ArgObjT ArgObjType;

public:
  DMLBase(const std::string & dsName, int type = 0) 
    : DataModelBase(dsName, type), changed(0) {}
  virtual ~DMLBase() {}

public:
  int changed;

protected:
  // one-step call (with type)
  void SingleExecute(int type, const ArgObjType & argObj)
  {
    std::vector<ArgObjType> argCtn;
    argCtn.push_back(argObj);
    BatchExecute(type, argCtn);
  }

  void BatchExecute(int type, const ArgCtnType & argCtn)
  {
    DataModelBase::SetType(type);
    Execute(argCtn);
  }

  // two-step call (must call SetType first)
  virtual void Execute(const ArgCtnType & argCtn);

protected:
  virtual void ComposeSQL(const ArgObjType & /*argObj*/, std::string & sql)
  { ComposeSQL(sql); }
  virtual void ComposeSQL(std::string & sql) = 0;
  virtual void Bind(IDataManipulation * dm, const ArgObjType & argObj) = 0;
  virtual void OnExecuted(const ArgObjType & /*argObj*/) {}

}; // class DMLBase

#define DEFINE_BATCH_EXECUTE_MOTHOD(cls, method, type) \
  public: static int method(const ArgCtnType & argCtn) \
    { cls cmd; cmd.BatchExecute(type, argCtn); return cmd.changed; }

#define DEFINE_SINGLE_EXECUTE_MOTHOD(cls, method, type) \
  public: static int method(const ArgObjType & argObj) \
    { cls cmd; cmd.SingleExecute(type, argObj); return cmd.changed; }

#define DEFINE_BATCH_SINGLE_ADD_MOTHOD(cls) \
  DEFINE_BATCH_EXECUTE_MOTHOD(cls, BatchAdd, 0) \
  DEFINE_SINGLE_EXECUTE_MOTHOD(cls, SingleAdd, 0) \

///////////////////////////////////////////////////////////////////////////
template<class ArgObjT>
class DMLInsertBase : public DMLBase<ArgObjT>
{
public:
  typedef ArgObjT ArgObjType;

  DMLInsertBase(const std::string & dsName, const std::string & tableName) 
    : DMLBase<ArgObjT>(dsName, 0), tableName_(tableName), rowid(0) {}
  virtual ~DMLInsertBase() {}

public:
  long long rowid;

protected:
  virtual void Execute(const ArgObjType & argObj);

protected:
  std::string tableName_;

}; // class DMLInsertBase

#define DEFINE_SINGLE_INSERT_MOTHOD(cls) \
  public: static long long SingleInsert(const ArgObjType & argObj) \
    { cls cmd; cmd.Execute(argObj); return cmd.rowid; }

///////////////////////////////////////////////////////////////////////////
template<
  class ArgObjT, class ResObjT = ArgObjT, 
  class ArgCtnT = std::vector<ArgObjT>, class ResCtnT = std::vector<ResObjT> >
class DQLBase : public DataModelBase
{
public:
  typedef ArgObjT ArgObjType;

  typedef ResCtnT ResCtnType;
  typedef ResObjT ResObjType;

public:
  DQLBase(const std::string & dsName, int type = 0) 
    : DataModelBase(dsName, type), count(0) {}
  virtual ~DQLBase() {}

public:
  int count;

protected: 
  // one-step call (with type)
  bool SingleExecute(int type, 
    const ArgObjType & argObj, ResObjType & resObj)
  {
    ResCtnType resCtn;
    BatchExecute(type, argObj, resCtn);
    if (resCtn.size() >= 1) {
      // in DQLBase<>::Execute
      // ++count is always accompanied with resCtn.push_back() 
      //assert(count >= 1);
      resObj = resCtn[0];
      return true;
    }
    else 
      return false;
  }

  void BatchExecute(int type, 
    const ArgObjType & argObj, ResCtnType & resCtn)
  {
    DataModelBase::SetType(type);
    Execute(argObj, resCtn);
  }

  // two-step call (must call SetType first)
  virtual void Execute(const ArgObjType & argObj, ResCtnType & resCtn);

protected:
  virtual void ComposeSQL(const ArgObjType & /*argObj*/, std::string & sql)
  { ComposeSQL(sql); }
  virtual void ComposeSQL(std::string & sql) = 0;
  virtual void Bind(IDataManipulation * dm, const ArgObjType & argObj) = 0;
  virtual void Extract(IDataManipulation * dm, ResObjType & resObj) = 0;

}; // class DQLBase

  } // namespace ecsdata
} // namespace ecs
#ifdef __APPLE__
#include "DataModelBase.inl"
#endif

