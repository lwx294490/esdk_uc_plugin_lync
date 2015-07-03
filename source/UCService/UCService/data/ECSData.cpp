// ecsdata.cpp : 定义 DLL 应用程序的导出函数。
//


#include "stdafx.h"
#include "tchar.h"
#include "errno.h"
#include "io.h"
#include <algorithm>
#include "data/ECSData.h"
#include "data/storage/DataStorage.h"
#include "data/model/DBVersion.h"
#include "data/model/sys/LoginList.h"
#include "data/model/history/HistoryDataType.h"

#include "eSDKTool.h"



#ifdef __APPLE__
#else
#include "strsafe.h"    //遍历头像文件时用到
#endif

#include "Log.h"
#include "eSDKTool.h"

//默认日志级别
#ifdef _DEBUG
# define DEFAULT_LOG_PRIORITY  (TRACE_DEBUG)
#else
# define DEFAULT_LOG_PRIORITY  (TRACE_INFO)
#endif

static const std::string DBVERSION_KEY = "DBVersion";
static const std::string DBVERSION_VAL = "3.0";

const int def_backupCircle_interval = 1000; //通知线程周期为1s

static const std::string CHECK_DB_TABLES_COLUMN[][4] = {
	{HISTORYDB_NAME, "RecordTab", "UTCDATE", "DATE"},
	{HISTORYDB_NAME, "RecordTab","UTCTIME","TIME"}
};

namespace ecs
{
namespace ecsdata
{

// static
ECSData *ECSData::instance_ = NULL;

ECSData::ECSData()
    : userProfile()
    , subListCache_()
   // , m_pBackupDataBaseThread(NULL)
    , oldAccount_("")
    , account_("")
    , sipAccount_("")
    , uri_("")
    , binduri_("")
    , name_("")
    , entname_("")
    , staffid_("")
	, bSipRegOk_(false)
	, bOperDNDFlag(false)    
    , bCallRightGot(false)
{
    try
    {
        //m_pBackupDataBaseThread = new BackupDataBaseThread((void *)this);

	    INFO_LOG("");
        INFO_LOG(" ************************************");
        INFO_LOG(" ******* ECSData Log Start !! *******");
        INFO_LOG(" ************************************");
        INFO_LOG("");
        INFO_LOG(" log priority : %d",(int)DEFAULT_LOG_PRIORITY);

    }
    catch (const std::bad_alloc &e)
    {
        ERROR_LOG(e.what());
    }
}

ECSData::~ECSData()
{
    try
    {       

        //delete m_pBackupDataBaseThread;
        //m_pBackupDataBaseThread = NULL;

    }
    catch (...)
    {
        //ERROR_LOG("exception!");
    }
}

void ECSData::Initialize(const std::string &path)
{
    //TRACE_FUNC1(path);

    // set user profile path
    userProfile.profilepath_ = path;

    // make sub-dirs
    int mkdirRet = eSDKTool::MakeDir(userProfile.profilepath_);
    INFO_LOG("profile dir created: %d", mkdirRet);

    userProfile.headimagepath_ = userProfile.profilepath_ + "headimage";
    mkdirRet = eSDKTool::MakeDir(userProfile.headimagepath_);
    INFO_LOG("headimage dir created: %d",mkdirRet);

    userProfile.imagefilepath_ = userProfile.profilepath_ + "imagefiles";
    mkdirRet = eSDKTool::MakeDir(userProfile.imagefilepath_);
    INFO_LOG("imagefiles dir created: %d",mkdirRet);

    userProfile.receivefilepath_ = userProfile.profilepath_ + "ReceiveFile";
    mkdirRet = eSDKTool::MakeDir(userProfile.receivefilepath_);
    INFO_LOG("ReceiveFile dir created: %d",mkdirRet);

    userProfile.recordfilepath_ = userProfile.profilepath_ + "RecordFile";
    mkdirRet = eSDKTool::MakeDir(userProfile.recordfilepath_);
    INFO_LOG("RecordFile dir created: %d",mkdirRet);

    DATASTORAGE_MGR()->Init();
    INFO_LOG("data storage initialized.");

    DATA_MODEL()->Init();
    INFO_LOG("data model initialized.");
}

void ECSData::Finalize() const
{
    //TRACE_FUNC();

    //m_pBackupDataBaseThread->stop();

    DATA_MODEL()->Uninit();
    INFO_LOG("data model uninitialized.");

    DATASTORAGE_MGR()->Uninit();
    INFO_LOG("data storage uninitialized.");

    delete instance_;
    instance_ = NULL;
}

bool ECSData::InitializeSysData(const std::string &dbFile) const
{
    //TRACE_FUNC1(dbFile);

    if (NULL == DATASTORAGE_MGR()->AddDataStorage(
                SYSDB_NAME, dbFile, /*false,*/ "{34E1C562-AE8B-4079-B78B-283B708EEA40}"))
    {
        ERROR_LOG("can not open (or create) sysdb.");
        return false;
    }

    DATA_MODEL()->CreateSysTables();

    //版本检测，老版本数据库需要将帐号密码加密
    ecs::ecsdata::CreateDBVersionTabCommand createDBVersionCmd(SYSDB_NAME);
    createDBVersionCmd.Execute();

    ecs::ecsdata::DBVersionQuery dbVersionQry(SYSDB_NAME);
    std::string ver = dbVersionQry.QueryByKey(DBVERSION_KEY);
    INFO_LOG("sys db version : %s",ver.c_str());

    if (ver.empty() || std::string::npos != ver.find("2.0"))
    {
        INFO_LOG("old sys db version : %s",ver.c_str());
        ecs::ecsdata::AddDBVersionCommand addDBVersionCmd(SYSDB_NAME);
        (void)addDBVersionCmd.AddByKeyValue(DBVERSION_KEY, DBVERSION_VAL);

        std::vector<ecs::ecsdata::LoginListItem> dataItems;
        (void)ecs::ecsdata::LoginListQuery::QueryAll(dataItems);

        std::vector<ecs::ecsdata::LoginListItem>::iterator itor = dataItems.begin();
        while (dataItems.end() != itor)
        {
            ecs::ecsdata::LoginListItem dataItem;
            dataItem.account = itor->account;

            dataItem.password = "";

            dataItem.rememberPwd = itor->rememberPwd;
            dataItem.autoLogin = itor->autoLogin;

            (void)ecs::ecsdata::AddLoginListCommand::SingleAdd(dataItem);
            itor++;
        }

    }

    return true;
}

bool ECSData::FinalizeSysData() const
{
    //TRACE_FUNC();

    (void)DATASTORAGE_MGR()->RemoveDataStorage(SYSDB_NAME);
    return true;
}

bool ECSData::InitializeUserData(const std::string &dbFile) const
{
    //TRACE_FUNC1(dbFile);
	IDataStorage *pDs = DATASTORAGE_MGR()->AddDataStorage(
		USERDB_NAME, userProfile.profilepath_ + dbFile,/*false,*/ GetDBKey());
    if (NULL == pDs)
    {
		ERROR_LOG("can not open (or create) userdb.");
        return false;
    }
	if(!pDs->IsCanOpen())
    {
		pDs->ResetKey(GetOldDBKey());
		
		if(!pDs->IsCanOpen())
		{
		    ERROR_LOG("open userdb failed");
			return false;
		}
		if(!pDs->ReKey(GetDBKey(),false))
		{
		    ERROR_LOG("can not change key userdb.");
		}
        
        pDs->ResetKey(GetDBKey());
        if(!pDs->IsCanOpen())
        {
            ERROR_LOG("open userdb failed");
            return false;
        }
    }

    DATA_MODEL()->CreateUserTables();

    return true;
}

bool ECSData::UpdateUserData(const std::string &dbFile) const
{
    //TRACE_FUNC1(dbFile);
	IDataStorage *pDs = DATASTORAGE_MGR()->AddDataStorage(
		USERDB_NAME, userProfile.profilepath_ + dbFile,/*false,*/ GetDBKey());
    if (NULL == pDs)
    {
        ERROR_LOG("can not open (or create) userdb.");
        return false;
    }
	if(!pDs->IsCanOpen())
    {
		pDs->ResetKey(GetOldDBKey());
		
		if(!pDs->IsCanOpen())
		{
		    ERROR_LOG("open userdb failed");
			return false;
		}
		if(!pDs->ReKey(GetDBKey(),false))
		{
		    ERROR_LOG("can not change key userdb.");
		}
        pDs->ResetKey(GetDBKey());
        if(!pDs->IsCanOpen())
        {
            ERROR_LOG("open userdb failed");
            return false;
        }
    }
    return DATA_MODEL()->CheckUserTables();
}

void ECSData::FinalizeUserData() const
{
    //TRACE_FUNC();
	IDataStorage *pDs = DATASTORAGE_MGR()->GetDataStorage(USERDB_NAME);
	if(pDs)
	{
		pDs->Close();
	}
	(void)DATASTORAGE_MGR()->RemoveDataStorage(USERDB_NAME);
}

bool ECSData::clearUserData(const std::string & dbFile) const
{
	IDataStorage *pDs = DATASTORAGE_MGR()->AddDataStorage(
        USERDB_NAME, userProfile.profilepath_ + dbFile,/*false,*/ GetDBKey());
    if (NULL == pDs)
    {
        ERROR_LOG("can not open (or create) userdb.");
        return false;
    }

	if(!pDs->IsCanOpen())
    {
		pDs->ResetKey(GetOldDBKey());

		if(!pDs->IsCanOpen())
		{
		    ERROR_LOG("open userdb failed");
			return false;
		}
		if(!pDs->ReKey(GetDBKey(),false))
		{
		    ERROR_LOG("can not change key userdb.");
		}
        pDs->ResetKey(GetDBKey());
        if(!pDs->IsCanOpen())
        {
            ERROR_LOG("open userdb failed");
            return false;
        }
    }
    DATA_MODEL()->ClearUserTables();
    return true;
}

void ECSData::DecideUseWhichDB(const std::string &dbFile, const std::string &dbFileBak) const
{
    //TRACE_FUNC2(dbFile, dbFileBak);

    DATASTORAGE_MGR()->DecideUseWhichDB(
        HISTORYDB_NAME, userProfile.profilepath_ + dbFile,
        userProfile.profilepath_ + dbFileBak,  GetDBKey());
}

bool ECSData::UpdateHistoryData(const std::string &dbFile) const
{
    //TRACE_FUNC1(dbFile);
	IDataStorage *pDs = DATASTORAGE_MGR()->AddDataStorage(
                HISTORYDB_NAME, userProfile.profilepath_ + dbFile, /*false,*/  GetDBKey());
    if (NULL == pDs)
    {
        ERROR_LOG("can not open (or create) historydb.");
        return false;
		
    }

	if(!pDs->IsCanOpen())
    {
		pDs->ResetKey(GetOldDBKey());
		
		if(!pDs->IsCanOpen())
		{
		    ERROR_LOG("open historydb failed");
			return false;
		}
		if(!pDs->ReKey(GetDBKey(),false))
		{
		    ERROR_LOG("can not change key historydb.");
		}
        pDs->ResetKey(GetDBKey());
        if(!pDs->IsCanOpen())
        {
            ERROR_LOG("open historydb failed");
            return false;
        }
    }
    //check db version
    ecs::ecsdata::CreateDBVersionTabCommand createDBVersionCmd(HISTORYDB_NAME);
    createDBVersionCmd.Execute();

    ecs::ecsdata::DBVersionQuery dbVersionQry(HISTORYDB_NAME);
    std::string ver = dbVersionQry.QueryByKey(DBVERSION_KEY);
    INFO_LOG("history db version : %s",ver.c_str());
	pDs->Close();
    (void)DATASTORAGE_MGR()->RemoveDataStorage(HISTORYDB_NAME);

    if (ver.empty() || std::string::npos != ver.find("2.0"))
    {
        INFO_LOG("old history db version : %s", ver.c_str());
        if (!eSDKTool::RenameFile(userProfile.profilepath_ + dbFile, userProfile.profilepath_ + dbFile + ver))
        {
            ERROR_LOG("move history db failed");
            return false;
        }
    }
    return true;
}


bool ECSData::InitializeHistoryData(const std::string &dbFile) const
{
    //TRACE_FUNC1(dbFile);
	IDataStorage *pDs = DATASTORAGE_MGR()->AddDataStorage(
                HISTORYDB_NAME, userProfile.profilepath_ + dbFile, /*false,*/  GetDBKey());
    if (NULL == pDs)
    {
		ERROR_LOG("can not open (or create) historydb.");
        return false;
    }
	
	if(!pDs->IsCanOpen())
    {
		pDs->ResetKey(GetOldDBKey());

		if(!pDs->IsCanOpen())
		{
		    ERROR_LOG("open historydb failed");
			return false;
		}
		if(!pDs->ReKey(GetDBKey(),false))
		{
		    ERROR_LOG("can not change key historydb.");
		}
        pDs->ResetKey(GetDBKey());
        if(!pDs->IsCanOpen())
        {
            ERROR_LOG("open historydb failed");
            return false;
        }
    }

    //check db version
    ecs::ecsdata::CreateDBVersionTabCommand createDBVersionCmd(HISTORYDB_NAME);
    createDBVersionCmd.Execute();

    ecs::ecsdata::DBVersionQuery dbVersionQry(HISTORYDB_NAME);
    std::string ver = dbVersionQry.QueryByKey(DBVERSION_KEY);
    INFO_LOG("history db version : %s",ver.c_str());

    if (ver.empty())
    {
        ecs::ecsdata::AddDBVersionCommand addDBVersionCmd(HISTORYDB_NAME);
        (void)addDBVersionCmd.AddByKeyValue(DBVERSION_KEY, DBVERSION_VAL);
    }
    else if (ver != DBVERSION_VAL)
    {
        ERROR_LOG("wrong history db version : %s",ver.c_str());
        return false;
    }
    else
    {
        //do nothing
    }

    DATA_MODEL()->CreateHistoryTables();

    //判断是否有新字段
    JudgeIsExistNewIndex();
    return true;
}
void ECSData::JudgeIsExistNewIndex() const
{
    int len=sizeof(CHECK_DB_TABLES_COLUMN)/sizeof(std::string);
    int n=sizeof(CHECK_DB_TABLES_COLUMN[0])/sizeof(std::string);
    int nColumn=len/n;

    for(int i = 0;i < nColumn; ++i)
    {
		std::string _dbName = CHECK_DB_TABLES_COLUMN[i][0];
        std::string _tableName = CHECK_DB_TABLES_COLUMN[i][1];
        std::string _indexName = CHECK_DB_TABLES_COLUMN[i][2];
        std::string _indexType = CHECK_DB_TABLES_COLUMN[i][3];

        //判断表中是否存在指定类型的字段
        if(!(DATA_MODEL()->JudgeColumnIsExist(_tableName,_indexName,_indexType,_dbName)))
        {
            //不存在则新增
            DATA_MODEL()->AlterHistoryTables(_tableName,_indexName,_indexType,_dbName);
        }

		if(_dbName == HISTORYDB_NAME)
		{
			std::list<std::string> lstArchiveDB;
			ECSDATA()->GetAllArchiveFiles(lstArchiveDB);
			std::list<std::string>::iterator itor = lstArchiveDB.begin();
			while(itor != lstArchiveDB.end())
			{
				if(!(DATA_MODEL()->JudgeColumnIsExist(_tableName,_indexName,_indexType,_dbName)))
				{
					//不存在则新增
					DATA_MODEL()->AlterHistoryTables(_tableName,_indexName,_indexType,_dbName);
				}
				++itor;
			}
		}

    }

}

BackupDataBaseThread::BackupDataBaseThread(void *pOwner)
    :count_(0)
    ,circle_(0)

{
    m_pOwner = pOwner;
    circle_ = def_backupCircle_interval;
}

void BackupDataBaseThread::onThreadStop()
{
    ECSData *pEcsData = (ECSData *)m_pOwner;

    if (pEcsData)
    {
        INFO_LOG("Exit BackupDataBase Thread");
        DATASTORAGE_MGR()->EnableBackup(HISTORYDB_NAME, false);
    }
}

void BackupDataBaseThread::onThreadWork()
{

    //登录后20min备份一次，后面每4小时备份一次
    if ((20 * 60 == count_)
            || ((0 == count_ % (4 * 3600)) && (0 != count_)))
    {

        ECSData *pEcsData = (ECSData *)m_pOwner;
        if (pEcsData)
        {
            DATASTORAGE_MGR()->BackupDB(
                HISTORYDB_NAME, pEcsData->userProfile.profilepath_ + "history.db",
                pEcsData->userProfile.profilepath_ + "history.db.bak",
                pEcsData->GetDBKey(), NULL);
            //HISTORYDB_NAME, "main", "main", NULL);
        }
    }

    count_++;
    Sleep((unsigned int)circle_*1000);
}

BackupDataBaseThread::~BackupDataBaseThread()
{
    m_pOwner = NULL;
}

bool BackupDataBaseThread::start()
{
    //if (!BackUpthread_.get())
    //{
    //    INFO_LOG("[historydb] backup Thread run");
    //    BackUpthread_ = new _Thread(this, ("BackupDataBaseThread"));
    //}

    //BackUpthread_->set_on_work(&BackupDataBaseThread::onThreadWork);
    //BackUpthread_->set_on_stop(&BackupDataBaseThread::onThreadStop);

    //BackUpthread_->startAndWait();

    return true;
}

bool BackupDataBaseThread::isThreadStarted() const
{
    //if (BackUpthread_.get())
    //{
    //    return true;
    //}

    return false;
}

void BackupDataBaseThread::stop()
{
    //TRACE_FUNC();
    //if (BackUpthread_.get())
    //{
    //    //InfoMsgRead();
    //    (void)ctk::stopThread(BackUpthread_);
    //}
}

bool ECSData::InitializeHistoryData_BK(const std::string &dbFile) const
{
    INFO_LOG(dbFile.c_str());

    //if (!m_pBackupDataBaseThread->isThreadStarted())
    //{
    //    (void)m_pBackupDataBaseThread->start();
    //}

    return true;
}

void ECSData::FinalizeHistoryData() const
{
    //TRACE_FUNC();

    (void)DATASTORAGE_MGR()->RemoveDataStorage(HISTORYDB_NAME);
}

void ECSData::FinalizeAllArchive() const
{
	std::list<std::string> lstArchiveFiles;
	GetAllArchiveFiles(lstArchiveFiles);
	std::list<std::string>::iterator itor = lstArchiveFiles.begin();
	std::string strDir = ECSDATA()->userProfile.profilepath_ + "ArchiveFiles\\";
	while(itor != lstArchiveFiles.end())
	{
		std::string strFullName = strDir + *itor;
		(void)FinalizeArchiveData(strFullName);
		++itor;
	}
}

void ECSData::InitialAllArchive() const
{
	std::list<std::string> lstArchiveFiles;
	GetAllArchiveFiles(lstArchiveFiles);
	std::list<std::string>::iterator itor = lstArchiveFiles.begin();
	std::string strDir = ECSDATA()->userProfile.profilepath_ + "ArchiveFiles\\";
	while(itor != lstArchiveFiles.end())
	{
		std::string strFullName = strDir + *itor;
		(void)InitializeArchiveData(strFullName);
		++itor;
	}
}

void ECSData::GetAllArchiveFiles(std::list<std::string>& _lstDBFiles) const
{
	std::string archiveDir = ECSDATA()->userProfile.profilepath_ + "ArchiveFiles";
	std::list<std::string> lstArchiveFiles;
	eSDKTool::GetFilesInDir(archiveDir,lstArchiveFiles);
	std::list<std::string>::iterator itor = lstArchiveFiles.begin();
	while(itor != lstArchiveFiles.end())
	{
		if(itor->find("Archive") != std::string::npos 
			&& itor->find(".db") != std::string::npos 
			&& itor->find(".db.bak") == std::string::npos 
			&& itor->find("-") == std::string::npos)
		{
			_lstDBFiles.push_back(*itor);
		}
		++itor;
	}
}

bool ECSData::InitializeArchiveData(const std::string& _dbFile) const
{
    //TRACE_FUNC1(_dbFile);

	IDataStorage *pDs = DATASTORAGE_MGR()->AddDataStorage(
                _dbFile, _dbFile, /*false,*/  GetDBKey());
    if (NULL == pDs)
    {
		ERROR_LOG("can not open (or create) Archivedb.");
        return false;
    }

	if(!pDs->IsCanOpen())
    {
		pDs->ResetKey(GetOldDBKey());

		if(!pDs->IsCanOpen())
		{
		    ERROR_LOG("open Archivedb failed");
			return false;
		}
		if(!pDs->ReKey(GetDBKey(),false))
		{
		    ERROR_LOG("can not change key Archivedb.");
		}
        pDs->ResetKey(GetDBKey());
        if(!pDs->IsCanOpen())
        {
            ERROR_LOG("open Archivedb failed");
            return false;
        }
    }

    //check db version
    ecs::ecsdata::CreateDBVersionTabCommand createDBVersionCmd(_dbFile);
    createDBVersionCmd.Execute();

    ecs::ecsdata::DBVersionQuery dbVersionQry(_dbFile);
    std::string ver = dbVersionQry.QueryByKey(DBVERSION_KEY);
    INFO_LOG("history db version : %s",ver.c_str());

    if (ver.empty())
    {
        ecs::ecsdata::AddDBVersionCommand addDBVersionCmd(_dbFile);
        (void)addDBVersionCmd.AddByKeyValue(DBVERSION_KEY, DBVERSION_VAL);
    }
    else if (ver != DBVERSION_VAL)
    {
        ERROR_LOG("wrong history db version : %s",ver.c_str());
        return false;
    }
    else
    {
        //do nothing
    }

	DATA_MODEL()->CreateArchiveTables(_dbFile);
    return true;
}

bool ECSData::FinalizeArchiveData(const std::string& _dbFile) const
{
    //TRACE_FUNC();

    (void)DATASTORAGE_MGR()->RemoveDataStorage(_dbFile);
	return true;
}

bool ECSData::IsHeadImageExist(const std::string &imageid) const
{
    if (imageid.length() < 4)
    {
        //system image, no need to download
        return true;
    }

    return eSDKTool::Exists(GetHeadImageFullPath(imageid));
}

bool ECSData::IsLinkageNum(const std::string &num) const
{
    return (std::string::npos != userProfile.Linkagednum.find(num) ||
            std::string::npos != num.find(userProfile.Linkagednum));
}

std::string ECSData::GetLinkageNum() const
{
    std::string linkagenum = userProfile.Linkagednum;
    if (linkagenum.rfind("@"))
    {
        //has domain
        return linkagenum;
    }
    std::string::size_type pos = uri_.rfind("@");
    if (std::string::npos != pos && pos != uri_.length() - 1)
    {
        return "sip:" + linkagenum + uri_.substr(pos + 1);
    }
    return linkagenum;
}

std::string ECSData::GetHeadImageFullPath(
    const std::string &imageid, bool grey/* = false*/) const
{
    const std::string SYSTEM_IMAGE_DIR = "Image/face";
    std::string imagedir = imageid.length() < 4
                           ? eSDKTool::GetProgramDir() + SYSTEM_IMAGE_DIR
                           : userProfile.headimagepath_;

    std::string imagefile = imageid.empty() ? "0" : imageid;

    std::string suffix = grey ? "_g.png" : ".png";

    return imagedir + "\\" + imagefile + suffix;
}

std::string ECSData::GetDiscussGroupHeadImageFullPath(const std::string &groupid) const
{
    std::string imagePath = userProfile.headimagepath_ + "\\";
    imagePath += groupid + ".png";
    return imagePath;
}

void c2w(wchar_t *pwstr, size_t len, const char *str)
{
#ifndef __APPLE__
    if (str)
    {
        size_t nu = strlen(str);
        size_t n = (size_t)MultiByteToWideChar(CP_ACP, 0, (const char *)str, (int)nu, NULL, 0);
        if (n >= len)
        {
            n = len - 1;
        }
        (void)MultiByteToWideChar(CP_ACP, 0, (const char *)str, (int)nu, pwstr, (int)n);
        pwstr[n] = 0;
    }
#endif
}

char *w2c(char *pcstr, const wchar_t *pwstr, size_t len)
{
#ifndef __APPLE__
    int nlength = static_cast<int>(wcslen(pwstr));
    //获取转换后的长度
    int nbytes = WideCharToMultiByte( 0, 0, pwstr, nlength, NULL, 0, NULL, NULL );
    if (nbytes > static_cast<int>(len))
    {
        nbytes = static_cast<int>(len);
    }

    // 通过以上得到的结果，转换unicode 字符为ascii 字符
    (void)WideCharToMultiByte( 0, 0, pwstr, nlength,   pcstr, nbytes, NULL,   NULL );

    return pcstr ;
#endif
}

//获取headimage存放路径下的所有头像
void ECSData::GetAllImageNameFromFullPath(std::vector<std::string> &imageNameList) const
{
#ifndef __APPLE__
    _wfinddata_t findFileData;
    wchar_t srcPath[MAX_PATH];
    wchar_t dirPath[MAX_PATH];

    memset(srcPath, 0, (MAX_PATH)*sizeof(wchar_t));

    c2w(srcPath, MAX_PATH, userProfile.headimagepath_.c_str());
    (void)StringCchCopy(dirPath, MAX_PATH, srcPath);   //定义要遍历的文件夹的完整路径\*
    (void)StringCchCat(dirPath, MAX_PATH, TEXT("\\*"));
    intptr_t hFind = _tfindfirst(dirPath, &findFileData);          //找到文件夹中的第一个文件

    if (hFind == EINVAL || -1 == hFind) //如果hFind句柄创建失败，输出错误信息
    {
        (void)_findclose(hFind);
    }
    else
    {
        while (_tfindnext(hFind, &findFileData) == 0)  //当文件或者文件夹存在时
        {
            //判断是文件夹&&表示为"."||表示为"."
            if ((findFileData.attrib & FILE_ATTRIBUTE_DIRECTORY) != 0
                    && (wcscmp(findFileData.name, L".") == 0 || wcscmp(findFileData.name, L"..") == 0))
            {
                continue;
            }

            if ((findFileData.attrib & FILE_ATTRIBUTE_DIRECTORY) == 0) //如果不是文件夹
            {
                char *fname = (char *)malloc(sizeof(char) * (2 * wcslen(findFileData.name) + 1));
                if (fname)
                {
                    memset(fname, 0, 2 * wcslen(findFileData.name) + 1);
                    (void)w2c(fname, findFileData.name, 2 * wcslen(findFileData.name) + 1); // 获取文件名
                    std::string imageName(fname);
                    imageNameList.push_back(imageName);
                    free(fname);
                    //fname = NULL;
                }
            }
        }

        (void)_findclose(hFind);
    }
#endif
}

//删除指定帐号对应的头像
void ECSData::DelExistAccountHeadImage(const std::string &account) const
{
    std::vector<std::string> imageNameList;
    GetAllImageNameFromFullPath(imageNameList);
    std::vector<std::string>::iterator iterImage = imageNameList.begin();
    while (iterImage != imageNameList.end())
    {
        if (std::string::npos != (*iterImage).find(account.c_str()))//找到，删除
        {
            std::string filePath = userProfile.headimagepath_ + "\\" + *iterImage;
            if (!eSDKTool::DeleteFile(filePath))
            {
                ERROR_LOG("Del head image %s fail",filePath.c_str());
            }
        }
        iterImage++;
    }
}

bool ECSData::HasSubContactCache(const std::string &_uri)
{
    std::list<std::string>::iterator itor =
        std::find(subListCache_.begin(), subListCache_.end(), _uri);
    if (itor != subListCache_.end())
    {
        return true;
    }

    return false;
};

std::string ECSData::GetOldDBKey() const
{
	//INFO_PARAM1(oldAccount_);

    if (oldAccount_.empty())
    {
        return "";
    }

    // encrypt from account
    //ctk::istr inStr(oldAccount_);

    // des3 encryption
    //ctk::Bytes outBuff;
    //(void)ctk::des3::encode(inStr, outBuff, "9F-673D");
    //ctk::istr outStr(outBuff);

    // base64 encryption
    std::string outTxt;
    //ctk::Base64::encode(outStr, outTxt);

    return outTxt;
}
std::string ECSData::GetDBKey() const
{
    //INFO_PARAM1(account_);

    if (account_.empty())
    {
		return "{22DA0650-A738-4073-9725-F474948E938A}";
    }

    // encrypt from account
    //ctk::istr inStr(account_);

    // des3 encryption
    //ctk::Bytes outBuff;
    //(void)ctk::des3::encode(inStr, outBuff, "9F-673D");
    //ctk::istr outStr(outBuff);

    // base64 encryption
    std::string outTxt;
    //ctk::Base64::encode(outStr, outTxt);

    return outTxt;
}

void ECSData::FormatNumToFulluri(std::string &num) const
{
    if (num.empty())
    {
        ERROR_LOG("num is empty.");
    }
    else if (num.find("sip:") != std::string::npos)
    {
        WARN_LOG("num doesn't need format.%s",num.c_str());
    }
    else
    {
        num = "sip:" + num + "@" + userProfile.cscfDomainName;
        INFO_LOG("After format, num is %s",num.c_str());
    }
    return;
}

std::string ECSData::GetOldHistoryDBKey() const
{
	return std::string("{34E1C562-AE8B-4079-B78B-283B708EEA40}");
}


bool ECSData::InitializeOldHistoryData(const std::string& _dbFilePath) const
{
	//TRACE_FUNC1(_dbFilePath);
	IDataStorage*  ds = DATASTORAGE_MGR()->AddDataStorage(
		_dbFilePath, _dbFilePath,GetOldHistoryDBKey());
	if (NULL == ds)
	{
		ERROR_LOG("can not open (or create) %s",_dbFilePath.c_str());
		return false;
	}
	if(!ds->IsCanOpen())
    {
		ERROR_LOG("open oldhistorydb %s failed",_dbFilePath.c_str());
		return false;
	}
	return true;
}

bool ECSData::InitializeOldUserData(const std::string& _dbFilePath) const
{
	//TRACE_FUNC1(_dbFilePath);
	IDataStorage*  ds = DATASTORAGE_MGR()->AddDataStorage(
		_dbFilePath, _dbFilePath, GetDBKey());
	if (NULL == ds)
	{
		ERROR_LOG("can not open (or create) oldUserdb.");
        return false;
	}

	if(!ds->IsCanOpen())
    {
		ds->ResetKey( GetOldDBKey());
		
		if(!ds->IsCanOpen())
		{
		    ERROR_LOG("open oldUserdb failed");
			return false;
		}
		if(!ds->ReKey(GetDBKey(),false))
		{
		    ERROR_LOG("can not change key oldUserdb.");
		}
        ds->ResetKey(GetDBKey());
        if(!ds->IsCanOpen())
        {
            ERROR_LOG("open olduserdb failed");
            return false;
        }
    }

	return true;
}

bool ECSData::InitializeOldSysData(const std::string& _dbFilePath) const
{
	//TRACE_FUNC1(_dbFilePath);

	if (NULL == DATASTORAGE_MGR()->AddDataStorage(
		_dbFilePath, _dbFilePath,GetOldHistoryDBKey()))
	{
		ERROR_LOG("can not open (or create) %s",_dbFilePath.c_str());
		return false;
	}
	return true;
}
void ECSData::FinalizeOldData(const std::string& _dbFilePath) const
{
	(void)DATASTORAGE_MGR()->RemoveDataStorage(_dbFilePath);
}

bool ECSData::InitializeImportHistoryData(const std::string& dbPath) const
{
    //TRACE_FUNC1(dbPath);

    IDataStorage*  ds = DATASTORAGE_MGR()->AddDataStorage(
        dbPath, dbPath,  GetDBKey());
    if (NULL == ds)
    {
        ERROR_LOG("can not open (or create) importHistorydb.");
        return false;
    }

    if(!ds->IsCanOpen())
    {
		ds->ResetKey(GetOldDBKey());
		
		if(!ds->IsCanOpen())
		{
		    ERROR_LOG("open db failed: %s",dbPath.c_str());
			return false;
		}
		if(!ds->ReKey(GetDBKey(),false))
		{
		    ERROR_LOG("can not change key importHistorydb.");
		}
        ds->ResetKey(GetDBKey());
        if(!ds->IsCanOpen())
        {
            ERROR_LOG("open importHistorydb failed");
            return false;
        }
    }

    return true;
}

std::string ECSData::GetImportHistoryDBKey() const
{
    return std::string("{96A21D9C-5886-437F-B5E6-39C666061547}");
}

void ECSData::FinalizeImportHistoryData(const std::string& dbPath) const
{
	IDataStorage*  ds = DATASTORAGE_MGR()->GetDataStorage(dbPath);
	if(ds)
	{
		ds->Close();
	}
	(void)DATASTORAGE_MGR()->RemoveDataStorage(dbPath);
}


} // namespace ecsdata
} // namespace ecs
