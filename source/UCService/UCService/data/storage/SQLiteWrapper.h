#pragma once
#include "sqlite.h"

#include "vos/vos.h"

namespace ecs {
  namespace ecsdata {

class SQLiteDB;
class SQLiteStmt;
class SQLiteException;

class SQLiteDB : public IDataStorage
{
  friend class SQLiteStmt;

public:
  SQLiteDB(const std::string & dbName,const std::string & filename,const std::string & key)
    : dbName_(dbName),dbFile_(filename),key_(key),IsableBackup_(true) {
		instanceLock_ = VOS_CreateMutex();
  }

  virtual ~SQLiteDB();

public:

  //virtual 
  bool IsOpen() const;
  sqlite3* Open(const std::string & filename);  
  void Close();
  bool TestOpen();
  bool IsCanOpen();
  void Key(const std::string & key);
  bool ReKey(const std::string & key, bool thrExcept);
  void Optimize(const std::string &op);
  void ResetKey(const std::string & key);

  bool ExistDBFile(const std::string & filename) const;

  void BackupDataBase(
    const char *zSrcFilename,
    const char *zFilename,      /* Name of file to back up to */
    const std::string & key,
    void(*xProgress)(int, int));

  void EnableBackup(bool IsableBackup);

  // 数据库中是否存在表
  bool ExistTable(const std::string& tabname);

  // 清除表内所有数据
  void ClearTable(const std::string& tabname);

  virtual std::string GetDBName() const { return dbName_; }
  virtual std::string GetDBFileName() const { return dbFile_;};

public:
  virtual void Exec(const std::string & sql);
  virtual IDataManipulation * CreateDataManipulation(const std::string & sql);

public:
  virtual bool GetAutoCommit();
  virtual void BeginTransaction();
  virtual void EndTransaction();
  virtual void Commit();
  virtual void Rollback();

  virtual int GetLastInsertRowId();
  //virtual sqlite3* DBConnection(int threadid);
  sqlite3* getDBConnection();
  sqlite3* getConn();

private:
  sqlite3 * GetDBHandle() { return getDBConnection(); }
    //void setDBHandle(sqlite3& conn) { hDb_=conn; }
  //bool inMemory_;

protected:
  //sqlite3 * hDb_;
  std::string dbName_;
  std::string dbFile_;
  std::string key_;
  std::map<DWORD, sqlite3*>  dbMap;
  //sqlite3* memdbHandler_;
  VOS_Mutex* instanceLock_;
  bool IsableBackup_;

}; // class SQLiteDB

class SQLiteStmt : public IDataManipulation
{
public:
  SQLiteStmt(sqlite3_stmt * stmt, const std::string & dbName)
    : hStmt_(stmt), dbName_(dbName) {}
  ~SQLiteStmt();

  virtual std::string GetDBName() const { return dbName_; }

  virtual void Bind(int index, int nValue);
  virtual void Bind(int index, long long llValue);
  virtual void Bind(int index, const std::string & strValue);

  virtual int Exec(bool reset);
  virtual void Reset();

  virtual bool NextRow();

  virtual void GetValue(int index, int & nValue);
  virtual void GetValue(int index, long long & llValue);
  virtual void GetValue(int index, std::string & strValue);

private:
  sqlite3 * GetDBHandle() { return sqlite3_db_handle(hStmt_); }

private:
  sqlite3_stmt * hStmt_;
  std::string dbName_;

}; // class SQLiteStmt

  } // namespace ecsdata
} // namespace ecs
