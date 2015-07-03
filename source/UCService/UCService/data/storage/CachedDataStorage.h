#pragma once

#include <string>
#include <cassert>
#include "sqlite.h"

namespace ecs {
  namespace ecsdata {

class CachedDataStorage;
class CachedDataManipulation;

class CachedDataStorage : public IDataStorage
{
public:
  CachedDataStorage(IDataStorage * persist, IDataStorage * memory)
    : persist_(persist), memory_(memory) {}
  virtual ~CachedDataStorage() {
    persist_ = memory_ = NULL;
  }

public:

  virtual bool IsOpen() const {
    return persist_->IsOpen() && memory_->IsOpen();
  }
  virtual sqlite3* Open(const std::string & /*filename*/) {return NULL;}
  virtual void Close() {}
  virtual bool TestOpen() {
    return persist_->TestOpen();
  }
  virtual bool IsCanOpen(){
      return persist_->IsCanOpen();
  }

  virtual void Key(const std::string & key) {
    return persist_->Key(key);
  }

  virtual bool ReKey(const std::string & key, bool thrExcept) {
    return persist_->ReKey(key, thrExcept);
  }

  virtual void Optimize(const std::string &op)
  {
      memory_->Optimize(op);
    persist_->Optimize(op);
  }
  virtual void ResetKey(const std::string & key)
  {
	  persist_->ResetKey(key);
  }
  virtual int GetLastInsertRowId() { return 0;};

  virtual std::string GetDBName() const {
    return persist_->GetDBName() + "_cached";
  }

  virtual std::string GetDBFileName() const{
	  return persist_->GetDBFileName();
  };

  virtual void BackupDataBase(
    const char *zSrcFilename,
    const char *zFilename,      /* Name of file to back up to */
    const std::string & key,
    void(*xProgress)(int, int));
    
  virtual void EnableBackup(bool IsableBackup);

public:

  virtual void Exec(const std::string & sql) {
    persist_->Exec(sql);
    memory_->Exec(sql);
  }
  inline virtual IDataManipulation * CreateDataManipulation(
    const std::string & sql);

public:

  virtual bool GetAutoCommit()
  {
    bool memoryAutoCommit = memory_->GetAutoCommit();
    assert(memoryAutoCommit == persist_->GetAutoCommit());

    return memoryAutoCommit;
  }

  virtual void BeginTransaction() {
    persist_->BeginTransaction();
    memory_->BeginTransaction();
  }
  virtual void EndTransaction() {
    persist_->EndTransaction();
    memory_->EndTransaction();
  }
  virtual void Commit() {
    persist_->Commit();
    memory_->Commit();
  }
  virtual void Rollback() {
    persist_->Rollback();
    memory_->Rollback();
  }

private:
  IDataStorage * persist_;
  IDataStorage * memory_;

}; // class CachedDataStorage

class CachedDataManipulation : public IDataManipulation
{
public:
  CachedDataManipulation(IDataManipulation * persist, IDataManipulation * memory)
    : persist_(persist), memory_(memory) {}
  virtual ~CachedDataManipulation() {
    delete persist_;
    delete memory_;
    persist_ = memory_ = NULL;
  }

public:
  virtual void Bind(int index, int nValue) {
    persist_->Bind(index, nValue);
    memory_->Bind(index, nValue);
  }
  virtual void Bind(int index, long long llValue) {
    persist_->Bind(index, llValue);
    memory_->Bind(index, llValue);
  }
  virtual void Bind(int index, const std::string & strValue) {
    persist_->Bind(index, strValue);
    memory_->Bind(index, strValue);
  }

  virtual int Exec(bool reset) 
  {
    int changesPer = persist_->Exec(reset);
#ifdef _DEBUG
    int changesMem = memory_->Exec(reset);
    assert(changesPer == changesMem);
#else
	memory_->Exec(reset);
#endif
    return changesPer;
  }

  virtual void Reset() {
    persist_->Reset();
    memory_->Reset();
  }

  virtual bool NextRow() {
    return memory_->NextRow();
  }

  virtual void GetValue(int index, int & nValue) {
    memory_->GetValue(index, nValue);
  }
  virtual void GetValue(int index, long long & llValue) {
    memory_->GetValue(index, llValue);
  }
  virtual void GetValue(int index, std::string & strValue) {
    memory_->GetValue(index, strValue);
  }

private:
  IDataManipulation * persist_;
  IDataManipulation * memory_;

}; // class CachedDataManipulation

inline IDataManipulation * CachedDataStorage
::CreateDataManipulation(const std::string & sql)
{
  return new CachedDataManipulation(
    persist_->CreateDataManipulation(sql), 
    memory_->CreateDataManipulation(sql));
}

  } // namespace ecsdata
} // namespace ecs
