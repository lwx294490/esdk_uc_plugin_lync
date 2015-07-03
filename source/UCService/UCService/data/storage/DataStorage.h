#pragma once

#include <map>
struct sqlite3;
namespace ecs {
  namespace ecsdata {

class IDataStorage;
class IDataManipulation;


class DataStorageMgr
{
    typedef std::map<std::string, IDataStorage *> DataStorageMap;

public:
  void Init() const;

  void Uninit();

  IDataStorage * GetDataStorage(const std::string & name)
  { return storages_[name]; }

  IDataStorage * AddDataStorage(
    const std::string & name, const std::string & filename,/* bool memdb,*/
    const std::string & key = "");

  void DecideUseWhichDB(const std::string & name, const std::string & srcfilename, 
    const std::string &bakfilename,
    const std::string & key) ;

  void BackupDB(const std::string & name, const std::string & srcfilename, const std::string &bakfilename,
    const std::string & key, void(*xProgress)(int, int)) ;
  void EnableBackup(const std::string & name, bool IsableBackup) ;

  IDataStorage * AddCachedDataStorage(
    const std::string & name, const std::string & filename, 
    const std::string & key = "");

  bool RemoveDataStorage(const std::string & name);
  bool RemoveCachedDataStorage(const std::string & name);
private:
  DataStorageMap storages_;

  //singleton
public:
  static DataStorageMgr * Instance() {
    if (instance_ == NULL) 
      instance_ = new DataStorageMgr();
    return instance_;
  }
private:
  static DataStorageMgr * instance_;

}; // class DataStorageMgr

class IDataStorage
{
public:
  virtual ~IDataStorage() {}

  virtual bool IsOpen() const = 0;
  virtual sqlite3 *Open(const std::string & filename) = 0;
  virtual void Close() = 0;
  virtual bool TestOpen() = 0;
  virtual bool IsCanOpen() = 0;

  virtual void Key(const std::string & key) = 0;
  virtual bool ReKey(const std::string & key, bool thrExcept) = 0;
  virtual void Optimize(const std::string &op) = 0;
  virtual void ResetKey(const std::string & key) = 0;
  virtual void BackupDataBase(
    const char *zSrcFilename,
    const char *zFilename,      /* Name of file to back up to */
    const std::string & key,
    void(*xProgress)(int, int)) = 0;

  virtual void EnableBackup(bool IsableBackup) = 0;

public:
  virtual int GetLastInsertRowId() = 0;
  virtual std::string GetDBName() const = 0;
  virtual std::string GetDBFileName() const = 0;

public:
  virtual void Exec(const std::string & sql) = 0;
  virtual IDataManipulation * 
    CreateDataManipulation(const std::string & sql) = 0;

public:
  virtual bool GetAutoCommit() = 0;
  virtual void BeginTransaction() = 0;
  virtual void EndTransaction() = 0;
  virtual void Commit() = 0;
  virtual void Rollback() = 0;

}; // class IDataStorage

class IDataManipulation
{
public:
  virtual ~IDataManipulation() {}

  virtual void Bind(int index, int nValue) = 0;
  virtual void Bind(int index, long long llValue) = 0;
  virtual void Bind(int index, const std::string & strValue) = 0;

  virtual int Exec(bool reset = true) = 0;
  virtual void Reset() = 0;

  virtual bool NextRow() = 0;

  virtual void GetValue(int index, int & nValue) = 0;
  virtual void GetValue(int index, long long & llValue) = 0;
  virtual void GetValue(int index, std::string & strValue) = 0;

}; // class IDataManipulation

  } // namespace ecsdata
} // namespace ecs

#define DATASTORAGE_MGR() (ecs::ecsdata::DataStorageMgr::Instance())
