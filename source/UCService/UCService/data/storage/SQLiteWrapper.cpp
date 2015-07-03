#include "stdafx.h"

#include "data/storage/DataStorage.h"
#include "data/storage/SQLiteWrapper.h"

#include "Log.h"
#include "data/ECSDataException.h"

using namespace std;

#define LOG_SQLITE_EXCEPTION(resCode, errMsg) \
  ERROR_LOG("[ %s ] sqlite exception : ( %d ) %s",dbName_.c_str(),resCode,errMsg) //for PClint_No.1506 : (Warning -- Call to virtual function 'ecs::ecsdata::SQLiteStmt::GetDBName(void) const' within a constructor or destructor)
  //(ERROR_LOG("[" << GetDBName() << "] sqlite exception : (" << resCode << ") " << errMsg)

#define THROW_LAST_SQLITEEXCEPTION2(resCode, hDb) \
    const char * errMsg = sqlite3_errmsg(hDb); if(errMsg){\
  LOG_SQLITE_EXCEPTION(resCode, errMsg); \
  throw SQLiteException(resCode, errMsg);}

#define THROW_LAST_SQLITEEXCEPTION1(resCode) \
  THROW_LAST_SQLITEEXCEPTION2(resCode, GetDBHandle())

//#define THROW_LAST_SQLITEEXCEPTION0(hDb)
//  THROW_LAST_SQLITEEXCEPTION1(sqlite3_errcode(hDb), hDb)

namespace ecs {
  namespace ecsdata {

SQLiteDB::~SQLiteDB()
{
  try
  {
    SQLiteDB::Close();
    //memdbHandler_ = NULL;
	VOS_DestroyMutex(instanceLock_);
	instanceLock_ = NULL;
  }
  catch(...)
  {
  }

  //hDb_ = NULL;
}


bool SQLiteDB::ExistDBFile(const std::string & filename) const
{
  sqlite3* hDb = NULL;
  
  int resCode = sqlite3_open_v2(filename.c_str(), &hDb, 
    SQLITE_OPEN_READONLY, NULL);

  if (hDb) {
    resCode = sqlite3_close(hDb);
  }

  if (resCode != SQLITE_OK) {
    return false;
  }

  return true;

}

void SQLiteDB::EnableBackup(bool IsableBackup)
{
    IsableBackup_ = IsableBackup;
}

void SQLiteDB::BackupDataBase(
                              const char *zSrcFilename,
                              const char *zFilename,      /* Name of file to back up to */
                              const std::string & key,
                              void(*xProgress)(int, int))
{
  INFO_LOG("[ %s ] BackupDataBase( %s )",zSrcFilename,zFilename);

  std::string strKey = key;
  strKey = strKey;

  int rc;
  sqlite3 *pFile = NULL;  
  sqlite3_backup *pBackup; 

  sqlite3 *pSrcFile = getDBConnection();

  /* Open the database file identified by zFilename. */
  rc = sqlite3_open_v2(zFilename, &pFile, 
                                  //SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, NULL);  
                                  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_URI, NULL);

  if ((!key_.empty()) && (NULL != pFile))
  {
    #ifdef NDEBUG
    char * errMsg = NULL;

    sqlite3_key(pFile, key.data(), (int)key.length());
    int resCode = sqlite3_exec(
        pFile, "DROP TABLE IF EXISTS TestOpenTab;", NULL, NULL, &errMsg);

    if (SQLITE_OK != resCode)
    {
      (void)sqlite3_close(pFile);
      bool bRet = eSDKTool::DeleteFile(zFilename);
      WARN_LOG("Bak.db file damaged, Need use history.db.bak as history.db: %s Delete Return %d",zFilename,bRet);

      return;
    }

    sqlite3_free(errMsg);
    #endif
  }

  if( (NULL != pSrcFile) && (rc==SQLITE_OK) && (NULL != pFile))
  {
    /* Open the sqlite3_backup object used to accomplish the transfer */
    pBackup = sqlite3_backup_init(pFile, "main", pSrcFile, "main");
    rc = sqlite3_errcode(pFile);
    INFO_LOG("sqlite3_backup_init return %d",rc);

    if( pBackup )
    {
      /* Each iteration of this loop copies 10 database pages from database
      ** pDb to the backup database. If the return value of backup_step()
      ** indicates that there are still further pages to copy, sleep for
      ** 10 ms before repeating. */
      do {
        rc = sqlite3_backup_step(pBackup, 10);

        if(xProgress)
        {
          xProgress(
            sqlite3_backup_remaining(pBackup),
            sqlite3_backup_pagecount(pBackup));
        }
        
        if(( rc==SQLITE_OK || rc==SQLITE_BUSY || rc==SQLITE_LOCKED )&& (IsableBackup_))
        {
          (void)sqlite3_sleep(10); 
        }
      } while( (rc==SQLITE_OK || rc==SQLITE_BUSY || rc==SQLITE_LOCKED)
                  && (IsableBackup_));
      
      /* Release resources allocated by backup_init(). */
      (void)sqlite3_backup_finish(pBackup);
    }
  }

  /* Close the database connection opened on database file zFilename
   ** and return the result of this function. */
  (void)sqlite3_close(pFile);

  INFO_LOG("BackupDataBase End~~~~~~~~~~~~~");
}

bool SQLiteDB::IsOpen() const
{
    DWORD threadID = GetCurrentThreadId();

    
    INFO_LOG("GetCurrentThreadId in IsOpen():%u",threadID);
    std::map<DWORD, sqlite3*>::const_iterator itor = dbMap.find(threadID);

    if (itor != dbMap.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

sqlite3* SQLiteDB::getConn()
{

    DWORD threadID = GetCurrentThreadId();

    
    std::map<DWORD, sqlite3*>::iterator itor = dbMap.find(threadID);

    if (itor != dbMap.end())
    {
        return itor->second;
    }
    else
    {
        return NULL;
    }
}



sqlite3* SQLiteDB::getDBConnection()
{

	VOS_MutexLock(instanceLock_);


    DWORD threadID = GetCurrentThreadId();

    std::map<DWORD, sqlite3*>::iterator itor = dbMap.find(threadID);

    sqlite3* conn;
    if (itor == dbMap.end() /*|| (inMemory_ && NULL == memdbHandler_)*/)
    {
        conn = Open(dbFile_);

        (void)dbMap.insert(std::make_pair(threadID, conn));

        INFO_LOG("opened a connection for thread:%d",threadID);
        INFO_LOG("getDBConnection() conn: %x",conn);
        //encrypt db
        if (!key_.empty())
        {
            #ifdef NDEBUG
            Key(key_);

            if (TestOpen())
            {
              INFO_LOG("db file is not corrupted.");
            }
            else
            {
              Close();
              bool bRet = eSDKTool::DeleteFile(dbFile_);

              DWORD dwErrCode = ::GetLastError();

              WARN_LOG("db file damaged : %s Delete Return %d last error %d" ,dbFile_.c_str() , bRet,dwErrCode);

              std::map<DWORD, sqlite3*>::iterator itorNew = dbMap.find(threadID);
              if (itorNew != dbMap.end())
              {
                  dbMap.erase(itorNew);
                  conn = Open(dbFile_);
				  //if(!inMemory_)
				  //{
                  	dbMap.insert(std::make_pair(threadID, conn));
				  //}
              }

              Key(key_);
            }
            #endif
        }

        {
            Optimize("PRAGMA synchronous = OFF;");             
        }

    }
    else
    {
        conn=itor->second;
    }

	VOS_MutexUnlock(instanceLock_);

    return conn;
}

sqlite3* SQLiteDB::Open(const std::string & filename)
{
    sqlite3* conn=NULL;

  if (!IsOpen()) {

	  //db属性-只读改为读写
	  std::wstring wFilename = eSDKTool::utf82unicode(filename.c_str());
	  WIN32_FILE_ATTRIBUTE_DATA fileAttr;
	  memset(&fileAttr,0,sizeof(WIN32_FILE_ATTRIBUTE_DATA));
	  BOOL bRetGet = ::GetFileAttributesEx(wFilename.c_str(), GetFileExInfoStandard, &fileAttr);
 
	  if (bRetGet)
	  {
		  if (fileAttr.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
		  {
			  BOOL bRetSet = ::SetFileAttributes(wFilename.c_str(), fileAttr.dwFileAttributes & ~FILE_ATTRIBUTE_READONLY);
			  if (!bRetSet)
			  {
				  WARN_LOG("SetFileAttributes failure !");
			  }
		  }
	  }
	  else
	  {
		  WARN_LOG("GetFileAttributesEx failure !");
	  }

    //内存数据库要支持多连接需要加上SQLITE_OPEN_URI配置
    //加上SQLITE_OPEN_FULLMUTEX可以确保是serialized(串行)
    int resCode = sqlite3_open_v2(filename.c_str(), &conn, 
      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_URI , NULL);

    INFO_LOG("[ %s ] sqlite3_open_v2( %s ) return %d",dbName_.c_str(),dbFile_.c_str(),resCode);

    if (resCode != SQLITE_OK) {
      THROW_LAST_SQLITEEXCEPTION1(resCode);
    }

    resCode = sqlite3_busy_timeout(conn, 60000);
    //resCode = sqlite3_busy_handler(conn, mysqliteBusyCallback, conn);
    if (resCode != SQLITE_OK) {
      THROW_LAST_SQLITEEXCEPTION1(resCode);
    }

    //dbFile_ = filename;
  } else {
    WARN_LOG("SQLiteDB is already opened !");
  }

  return conn;
}



void SQLiteDB::Close()
{
  if (IsOpen()) {
    INFO_LOG("[ %s] sqlite3_close()",dbName_.c_str() );

   std::map<DWORD, sqlite3*>::iterator itor = dbMap.begin();

    while (itor != dbMap.end())
    {
        sqlite3* conn=itor->second;
        int resCode = sqlite3_close(conn);
        if (resCode != SQLITE_OK) {
            THROW_LAST_SQLITEEXCEPTION1(resCode);
        }
        ++itor;
    }

    dbMap.clear();

  } else {
    WARN_LOG("SQLiteDB is not opened yet !");
  }
}

bool SQLiteDB::TestOpen()
{
  bool ret = false;

  if (IsOpen()) {
    char * errMsg = NULL;

    int resCode = sqlite3_exec(
      getDBConnection(), "DROP TABLE IF EXISTS TestOpenTab;", NULL, NULL, &errMsg);

    if (resCode != SQLITE_OK) {
		WARN_LOG("db test damaged : %d:%s",resCode, errMsg);
      ret = false;
    } else {
      INFO_LOG("db test ok.");
      ret = true;
    }

    sqlite3_free(errMsg);
  }

  return ret;
}

bool SQLiteDB::IsCanOpen()
{
    VOS_MutexLock(instanceLock_);
    //TRACE_FUNC_DEBUG1(lock.acquired());

    bool ret = false;
#ifdef __APPLE__
    DWORD threadID = (DWORD)ctk::ThreadControl().id().id_;
#else
    DWORD threadID = GetCurrentThreadId();
#endif

    std::map<DWORD, sqlite3*>::iterator itor = dbMap.find(threadID);
    sqlite3* conn = NULL;
    if (itor == dbMap.end() )
    {
        conn = Open(dbFile_);

        (void)dbMap.insert(std::make_pair(threadID, conn));
        INFO_LOG("opened conn thread: %d  getDBConnection() conn: %x",threadID,conn);

        itor = dbMap.find(threadID);
        //encrypt db
        if (!key_.empty())
        {
#ifdef NDEBUG
            Key(key_);
            ret = TestOpen();
#else
			ret = true;
#endif
        }

        if (itor != dbMap.end()) 
        {
            sqlite3* innerConn =itor->second;
            int resCode = sqlite3_close(innerConn);
            if (resCode != SQLITE_OK) 
			{
                THROW_LAST_SQLITEEXCEPTION1(resCode);
            }
            (void)dbMap.erase(itor);
        }
    }
	else
    {
        ret = true;
    }
	VOS_MutexUnlock(instanceLock_);
    return ret;
}

void SQLiteDB::ResetKey(const std::string & key)
{
	key_ = key;
}

void SQLiteDB::Key(const std::string & key)
{
    
    if (IsOpen()) {

        sqlite3* conn = getConn();
        if(!conn)
        {
            return;
        }
        int resCode = sqlite3_key(conn, key.data(), static_cast<int>(key.length()));
    
        INFO_LOG("[%s ] sqlite3_key() return %d",dbName_.c_str(),resCode);

        if (resCode != SQLITE_OK) {
            THROW_LAST_SQLITEEXCEPTION1(resCode);
        }
    } 
	else
	{
        WARN_LOG("SQLiteDB is not opened yet !");
    }
}

void SQLiteDB::Optimize(const std::string &op)
{
    if (IsOpen()) {
        INFO_LOG("[ %s ] sqlite3_exec( %s )",dbName_.c_str(),op.c_str());
        sqlite3* conn = getConn();
        if(!conn)
        {
            return;
        }
        int ret = sqlite3_exec(conn, op.c_str(), 0,0,0);
        if(ret != SQLITE_OK)
        {
            INFO_LOG("Optimize %s error : %d",op.c_str(), ret);
        }
    } else {
        WARN_LOG("SQLiteDB is not opened yet !");
    }
}


bool SQLiteDB::ReKey(const std::string & key, bool thrExcept)
{
    VOS_MutexLock(instanceLock_);
    //TRACE_FUNC_DEBUG3(key, lock.acquired(), thrExcept);

    bool ret = false;
    DWORD threadID = GetCurrentThreadId();

    std::map<DWORD, sqlite3*>::iterator itor = dbMap.find(threadID);
    sqlite3* conn;
    if (itor == dbMap.end() )
    {
        conn = Open(dbFile_);

        (void)dbMap.insert(std::make_pair(threadID, conn));
        INFO_LOG("opened conn thread: %d getDBConnection() conn:%x",threadID,conn);

        itor = dbMap.find(threadID);
        //encrypt db
        if (!key_.empty())
        {
#ifdef NDEBUG
            Key(key_);
            ret = TestOpen();
            if(ret)
            {
                sqlite3* conn = itor->second;
                if(conn)
                {
                    int resCode = sqlite3_rekey(conn, key.data(), static_cast<int>(key.length()));
                    INFO_LOG("[ %s ] sqlite3_rekey() return %d",dbName_.c_str(),resCode);
                    if (thrExcept && resCode != SQLITE_OK) 
                    {
                        THROW_LAST_SQLITEEXCEPTION1(resCode);
                    }
                    ret = resCode == SQLITE_OK;
                    resCode = sqlite3_close(conn);
                    if (resCode != SQLITE_OK)
                    {
						VOS_MutexUnlock(instanceLock_);
                        THROW_LAST_SQLITEEXCEPTION1(resCode);
                    }
                }
                
            }            
#endif
        }
    }
    if (itor != dbMap.end()) 
    {
        (void)dbMap.erase(itor);
    }
	VOS_MutexUnlock(instanceLock_);
    return ret;
}

void SQLiteDB::Exec(const std::string & sql)
{
  char * errMsg = NULL;

  int resCode = sqlite3_exec(getDBConnection(), sql.c_str(), NULL, NULL, &errMsg);

  if (resCode != SQLITE_OK) {
    INFO_LOG("[ %s ] sqlite3_exec( %s )",dbName_.c_str(),sql.c_str());

    if (errMsg)
    {
        LOG_SQLITE_EXCEPTION(resCode, errMsg);//errMsg为NULL崩溃了，所以加上上面这个判断
        SQLiteException ex(resCode, errMsg);
        sqlite3_free(errMsg);
        throw ex;
    }
    else
    {
        //
    }
  }
}


bool SQLiteDB::ExistTable(const std::string& tabname)
{
  int val = 0;

  sqlite3_stmt* hStmt = NULL;
  const char * pzTail = NULL;

  std::string sql = "select count(*) as CNT from sqlite_master where type='table' and name = '";
  sql += tabname;
  sql += "'";

  int resCode = sqlite3_prepare_v2(getDBConnection(), sql.c_str(), -1, &hStmt, &pzTail);
  if (resCode != SQLITE_OK) {
    //INFO_PARAM1(sql);
    return false;
  }

  resCode = sqlite3_step(hStmt);
  while (resCode == SQLITE_ROW){
      val = sqlite3_column_int(hStmt,0);
	  resCode = sqlite3_step(hStmt);
  }

  resCode = sqlite3_finalize(hStmt);
  if (resCode != SQLITE_OK){
	  //INFO_PARAM1(resCode);
      return false;
  }
 
  return (val != 0);
}

void SQLiteDB::ClearTable(const std::string& tabname)
{

  std::string sql = "TRUNCATE TABLE '";
  sql += tabname;
  sql += "'";

  try {
	  this->Exec(sql);
  }
  catch (const SQLiteException& e)
  {
	  ERROR_LOG("%s %s",e.GetErrorName(),sql.c_str());
  }

}

int SQLiteDB::GetLastInsertRowId()
{
    sqlite3_int64 id = sqlite3_last_insert_rowid(getDBConnection());
    return (int)id;
}


IDataManipulation * SQLiteDB::CreateDataManipulation(const std::string & sql)
{
  sqlite3_stmt* hStmt = NULL;
  const char * pzTail = NULL;

  int resCode = sqlite3_prepare_v2(getDBConnection(), sql.c_str(), -1, &hStmt, &pzTail);

  if (resCode != SQLITE_OK) {
    INFO_LOG("[%s] sqlite3_prepare_v2(%s)",dbName_.c_str(),sql.c_str());
    THROW_LAST_SQLITEEXCEPTION1(resCode);
  }

  return new SQLiteStmt(hStmt, dbName_);
}

bool SQLiteDB::GetAutoCommit()
{
  return sqlite3_get_autocommit(getDBConnection()) == TRUE;
}

void SQLiteDB::BeginTransaction()
{
  const char * SQL_BEGIN_TRANSACTION = "BEGIN EXCLUSIVE TRANSACTION;";
  Exec(SQL_BEGIN_TRANSACTION);
}

void SQLiteDB::EndTransaction()
{
  const char * SQL_END_TRANSACTION = "END TRANSACTION;";
  Exec(SQL_END_TRANSACTION);
}

void SQLiteDB::Commit()
{
  const char * SQL_COMMIT_TRANSACTION = "COMMIT TRANSACTION;";
  Exec(SQL_COMMIT_TRANSACTION);
}

void SQLiteDB::Rollback()
{
  const char * SQL_ROLLBACK_TRANSACTION = "ROLLBACK TRANSACTION;";
  Exec(SQL_ROLLBACK_TRANSACTION);
}

///////////////////////////////////////////////////////////////////////////
SQLiteStmt::~SQLiteStmt()
{
  if (hStmt_ != NULL)
  {
    try
    {
      int resCode = sqlite3_finalize(hStmt_);

      if (resCode != SQLITE_OK)
      {
        //PLT -e1506
        THROW_LAST_SQLITEEXCEPTION1(resCode);
      }
    }
    catch(...)
    {
    }

    hStmt_ = NULL;
  }
}

void SQLiteStmt::Bind(int index, int nValue)
{
  int resCode = sqlite3_bind_int(hStmt_, index, nValue);

  if (resCode != SQLITE_OK) {
    THROW_LAST_SQLITEEXCEPTION1(resCode);
  }
}

void SQLiteStmt::Bind(int index, long long llValue)
{
  int resCode = sqlite3_bind_int64(hStmt_, index, llValue);

  if (resCode != SQLITE_OK) {
    THROW_LAST_SQLITEEXCEPTION1(resCode);
  }
}

void SQLiteStmt::Bind(int index, const std::string & strValue)
{
  int resCode = sqlite3_bind_text(hStmt_, 
    index, strValue.c_str(), -1, SQLITE_TRANSIENT);

  if (resCode != SQLITE_OK) {
    THROW_LAST_SQLITEEXCEPTION1(resCode);
  }
}

int SQLiteStmt::Exec(bool reset)
{
  int resCode = sqlite3_step(hStmt_);

  // SQLITE_ROW 没有处理/*chenghaisheng*/
  if (resCode != SQLITE_DONE && resCode != 19) {
    THROW_LAST_SQLITEEXCEPTION1(resCode);
  }

  sqlite3* handle = GetDBHandle();
  if(!handle)
  {
    return -1;
  }
  int changes = sqlite3_changes(handle);

  if (reset)
  {
    Reset();
  }

  return changes;
}

void SQLiteStmt::Reset()
{
  int resCode = sqlite3_reset(hStmt_);

  if (resCode != SQLITE_OK) {
    THROW_LAST_SQLITEEXCEPTION1(resCode);
  }
}

bool SQLiteStmt::NextRow()
{
  int resCode = sqlite3_step(hStmt_);

  if (resCode != SQLITE_DONE && resCode != SQLITE_ROW) {
    THROW_LAST_SQLITEEXCEPTION1(resCode);
  }

  return resCode == SQLITE_ROW;
}

void SQLiteStmt::GetValue(int index, int & nValue)
{
  nValue = sqlite3_column_int(hStmt_, index);
}

void SQLiteStmt::GetValue(int index, long long & llValue)
{
  llValue = sqlite3_column_int64(hStmt_, index);
}

void SQLiteStmt::GetValue(int index, std::string & strValue)
{
  const unsigned char * pChar = sqlite3_column_text(hStmt_, index);
  if (pChar != NULL)
  {
    strValue = reinterpret_cast<const char *>(pChar);
  }
}

//sqlite3 * SQLiteStmt::GetDBHandle()
//{
//  return sqlite3_db_handle(hStmt_);
//}

///////////////////////////////////////////////////////////////////////////
#define ERRORMSG2(code, msg) \
  case code : errMsg = msg; break

#define ERRORMSG(code) ERRORMSG2(code, #code)

//static   
const char * SQLiteException::GetErrorMsgFromErrorCode(int errCode)
{
  const char * errMsg = NULL;
  switch (errCode)
  {
    ERRORMSG(SQLITE_ERROR);
    ERRORMSG(SQLITE_INTERNAL);
    ERRORMSG(SQLITE_PERM);
    ERRORMSG(SQLITE_ABORT);
    ERRORMSG(SQLITE_BUSY);
    ERRORMSG(SQLITE_LOCKED);
    ERRORMSG(SQLITE_NOMEM);
    ERRORMSG(SQLITE_READONLY);
    ERRORMSG(SQLITE_INTERRUPT);
    ERRORMSG(SQLITE_IOERR);
    ERRORMSG(SQLITE_CORRUPT);
    ERRORMSG(SQLITE_NOTFOUND);
    ERRORMSG(SQLITE_FULL);
    ERRORMSG(SQLITE_CANTOPEN);
    ERRORMSG(SQLITE_PROTOCOL);
    ERRORMSG(SQLITE_EMPTY);
    ERRORMSG(SQLITE_SCHEMA);
    ERRORMSG(SQLITE_TOOBIG);
    ERRORMSG(SQLITE_CONSTRAINT);
    ERRORMSG(SQLITE_MISMATCH);
    ERRORMSG(SQLITE_MISUSE);
    ERRORMSG(SQLITE_NOLFS);
    ERRORMSG(SQLITE_AUTH);
    ERRORMSG(SQLITE_FORMAT);
    ERRORMSG(SQLITE_RANGE);
    ERRORMSG(SQLITE_NOTADB);
    ERRORMSG(SQLITE_ROW);
    ERRORMSG(SQLITE_DONE);
    // 
    ERRORMSG(SQLITE_IOERR_READ);
    ERRORMSG(SQLITE_IOERR_SHORT_READ);
    ERRORMSG(SQLITE_IOERR_WRITE);
    ERRORMSG(SQLITE_IOERR_FSYNC);
    ERRORMSG(SQLITE_IOERR_DIR_FSYNC);
    ERRORMSG(SQLITE_IOERR_TRUNCATE);
    ERRORMSG(SQLITE_IOERR_FSTAT);
    ERRORMSG(SQLITE_IOERR_UNLOCK);
    ERRORMSG(SQLITE_IOERR_RDLOCK);
    ERRORMSG(SQLITE_IOERR_DELETE);
    ERRORMSG(SQLITE_IOERR_BLOCKED);
    ERRORMSG(SQLITE_IOERR_NOMEM);
  default: 
    errMsg = ""; break;
  }
  return errMsg;
}

  } // namespace ecsdata
} // namespace ecs
