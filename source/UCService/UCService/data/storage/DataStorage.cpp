#include "stdafx.h"
#include "data/storage/DataStorage.h"
#include "data/storage/CachedDataStorage.h"
#include "data/storage/SQLiteWrapper.h"

#include "Log.h"

namespace ecs {
  namespace ecsdata {

using namespace std;

DataStorageMgr * DataStorageMgr::instance_ = NULL;


void CachedDataStorage::BackupDataBase(const char * /*zSrcFilename*/, /* Name of file to back up to */
                            const char * /*zFilename*/,      
                            const std::string & /*key*/,
                            void(* /*xProgress*/)(int, int))
{
    //TRACE_FUNC4(zSrcFilename, zFilename, key, xProgress);
}

void CachedDataStorage::EnableBackup(bool /*IsableBackup*/)
{

}

void DataStorageMgr::Init() const
{
  int res = sqlite3_threadsafe();
  INFO_LOG(" sqlite3_threadsafe : %d", res);
}

void DataStorageMgr::Uninit()
{
  //TRACE_FUNC();

  std::list<IDataStorage *> valueList;
  //storages_.getValueList(valueList);这里要修改一下
  storages_.clear();

  for (std::list<IDataStorage *>::iterator i = valueList.begin();
       i != valueList.end(); ++i) {
      delete *i;
  }

  delete instance_;
  instance_ = NULL;
}

void DataStorageMgr::BackupDB(const std::string & name, const std::string & srcfilename, const std::string &bakfilename,
                                    const std::string & key, void(*xProgress)(int, int))
{
  IDataStorage * pDs = GetDataStorage(name);
  if (NULL == pDs) // return existed storage
  {
    INFO_LOG("return existed storage!");

    return;
  }

  pDs->BackupDataBase(srcfilename.c_str(), bakfilename.c_str(), key, xProgress);

}

void DataStorageMgr::EnableBackup(const std::string & name, bool IsableBackup) 
{
  IDataStorage * pDs = GetDataStorage(name);
  if (NULL == pDs) // return existed storage
  {
    INFO_LOG("return existed storage!");

    return;
  }

  pDs->EnableBackup(IsableBackup);
}

void DataStorageMgr
::DecideUseWhichDB(const std::string & name, const std::string & srcfilename, const std::string &bakfilename,
                 const std::string & key)
{
    //TRACE_FUNC3(name, srcfilename, bakfilename);
	IDataStorage * pDs = GetDataStorage(name);
    if (NULL != pDs) // return existed storage
    {
      INFO_LOG("return existed storage : %s" , pDs->GetDBFileName().c_str());
      return;
    }

    bool isUseBakDataBase = false; //if Need use history.db.bak as history.db
    IDataStorage* const ds(new SQLiteDB(name, srcfilename, key/*, false*/));

    //check if use history.db.bak
	if(eSDKTool::Exists(srcfilename))
    {
        //encrypt db
        if (!key.empty())
        {
#ifdef NDEBUG
			if(!ds->IsCanOpen())
			{
				bool bRet = eSDKTool::DeleteFile(srcfilename);
				WARN_LOG("db file damaged, Need use history.db.bak as history.db: %s Delete Return %d",srcfilename.c_str(),bRet);
				isUseBakDataBase = true;
			}
			else
			{
				INFO_LOG("Need Backup history.db.bak.");
			}
#endif
        }
    }
    else
    {
        INFO_LOG("history.db not exist");
        isUseBakDataBase = true;
    }

    //check if use bakfile again
    if(isUseBakDataBase && eSDKTool::Exists(bakfilename))
    {
       bool bRet = eSDKTool::RenameFile(bakfilename, srcfilename);
       INFO_LOG("rename db file , return = %d" , bRet);
    }

    delete ds;
}

IDataStorage * DataStorageMgr
::AddDataStorage(const std::string & name, const std::string & filename, /*bool memdb,*/
                 const std::string & key)
{
  //TRACE_FUNC2(name, filename);

  IDataStorage * pDs = storages_[name];
  if (NULL != pDs) // return existed storage
  {
    INFO_LOG("return existed storage : %s",pDs->GetDBFileName().c_str());
    return pDs;
  }

  IDataStorage* const ds(new SQLiteDB(name,filename,key/*, memdb*/));
  //ds->Open(filename);
  storages_[ds->GetDBName()]= ds;
  
  return ds;
}

IDataStorage * DataStorageMgr
::AddCachedDataStorage(const std::string & name, const std::string & filename, 
                       const std::string & key)
{
  //TRACE_FUNC2(name, filename);

  IDataStorage * pDs = storages_[name + "_cached"];
  if (NULL != pDs) // return existed storage
  {
    INFO_LOG("return existed storage : %s" , pDs->GetDBFileName().c_str());
    return pDs;
  }

  IDataStorage * persistDs = AddDataStorage(name, filename, /*false, */key);
  IDataStorage * memoryDs = AddDataStorage(name + "_mem", filename/*"file::memory:?cache=shared"*//*, true*/);
  IDataStorage * cachedDs = new CachedDataStorage(persistDs, memoryDs);
  storages_[cachedDs->GetDBName()] = cachedDs;
  return cachedDs;
}

bool DataStorageMgr::RemoveDataStorage(const std::string & name)
{
  //TRACE_FUNC1(name);

 // std::auto_ptr<IDataStorage> ds(storages_.at(name));
  return 1 == storages_.erase(name);
}

bool DataStorageMgr::RemoveCachedDataStorage(const std::string & name)
{
  //TRACE_FUNC1(name);

  return RemoveDataStorage(name) 
      && RemoveDataStorage(name + "_mem") 
      && RemoveDataStorage(name + "_cached");
}

  } // namespace ecsdata
} // namespace ecs
