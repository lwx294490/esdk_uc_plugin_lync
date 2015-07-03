// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ECSDATA_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
//   函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。

#pragma once


#include <string>
#include <vector>
#include <map>
#include <list>
//#include <assert.h>


namespace ecs {
  namespace ecsdata {

class BackupDataBaseThread;

class BackupDataBaseThread
{
public:
	BackupDataBaseThread():m_pOwner(NULL),count_(),circle_(0){};
	BackupDataBaseThread(void *pOwner);
	~BackupDataBaseThread();

	void onThreadWork();
	void onThreadStop();

	bool start();
	void stop();

	bool isThreadStarted() const;

	void *m_pOwner;
	unsigned long count_;
	int circle_;

protected:

private:
	//typedef ctk::OwnedThread <BackupDataBaseThread> _Thread;
	//typedef ctk::Handle <_Thread>                _ThreadPtr;
	//_ThreadPtr BackUpthread_;
};

class   ECSData
{
public:
  struct TableAlterData
  {
  public:
      std::string TableName;
      std::string IndexName;
      std::string IndexType;
  };

public:
	ECSData();
	~ECSData();

    //singleton
    static ECSData * Instance() {
      if (instance_ == NULL)
	  {
        instance_ = new ECSData();
	  }
      return instance_;
    }

    bool InitializeSysData(const std::string & dbFile) const;
    bool FinalizeSysData() const;

    void Initialize(const std::string & path);
    void Finalize() const;

    bool InitializeUserData(const std::string & dbFile) const;
    bool UpdateUserData(const std::string & dbFile) const;
    void FinalizeUserData() const;
	bool clearUserData(const std::string & dbFile) const;

    void JudgeIsExistNewIndex() const;
    bool InitializeHistoryData(const std::string & dbFile) const;
    bool InitializeHistoryData_BK(const std::string & dbFile) const;
    bool UpdateHistoryData(const std::string & dbFile) const;
    void DecideUseWhichDB(const std::string & dbFile, const std::string & dbFileBak) const;
    void FinalizeHistoryData() const;

    void InitialAllArchive() const;
    bool InitializeArchiveData(const std::string& _dbFile) const;
    bool FinalizeArchiveData(const std::string& _dbFile) const;
    void FinalizeAllArchive()const;
    void GetAllArchiveFiles(std::list<std::string>& _lstDBFiles) const;

    bool InitializeOldHistoryData(const std::string& _dbFilePath) const;
    bool InitializeOldUserData(const std::string& _dbFilePath) const;
    bool InitializeOldSysData(const std::string& _dbFilePath) const;
    void FinalizeOldData(const std::string& _dbFilePath) const;

  //导入历史数据
    bool InitializeImportHistoryData(const std::string& dbPath) const;
    void FinalizeImportHistoryData(const std::string& dbPath) const;

    UserProfile userProfile;
    bool bCallRightGot;

public:
	void SetOldAccount(const std::string & oldAcc) {oldAccount_ = oldAcc;}
	std::string GetOldAccount() const {  return oldAccount_;}

    void SetAccount(const std::string & account) { account_ = account; }
    std::string GetAccount() const { return account_; }

    void SetSipAccount(const std::string & sipaccount) { sipAccount_ = sipaccount; }
    std::string GetSipAccount() const { return sipAccount_; }

    void SetUri(const std::string & uri) { uri_ = uri; }
    std::string GetUri() const { return uri_; }

    void SetBindnoUri(const std::string& _binduri) { binduri_ = _binduri; }
    std::string GetBindnoUri() const { return binduri_; }
  
    void SetName(const std::string & name) { name_ = name; }
    std::string GetName() const { return name_; }

    void SetEntName(const std::string & name) { entname_ = name; }
    std::string GeEntName() const { return entname_; }

    void SetStaffID(const std::string & staffid) { staffid_ = staffid; }
    std::string GetStaffID() const { return staffid_; }

    void SetSipRegOk(const bool bOk) { bSipRegOk_ = bOk; }
    bool GetSipRegOk() const { return bSipRegOk_; }

    void SetOperDNDFlag(const bool bOk) { bOperDNDFlag = bOk; }
    bool GetOperDNDFlag() const { return bOperDNDFlag; }

    std::string GetHeadImageFullPath(
      const std::string& imageid, bool grey = false) const;

    std::string GetDiscussGroupHeadImageFullPath(
        const std::string& groupid) const;

    void GetAllImageNameFromFullPath(std::vector<std::string> &imageNameList) const;
    void DelExistAccountHeadImage(const std::string &account) const;

    bool IsHeadImageExist(const std::string & imageid) const;

    std::string GetDBKey() const;
    std::string GetOldDBKey() const;
	//生成华为UC1.X老im.db和archive.db的密钥
    std::string GetOldHistoryDBKey() const;

    std::string GetImportHistoryDBKey() const;

    void FormatNumToFulluri(std::string &num) const;


    bool IsLinkageNum(const std::string &num) const;
    std::string GetLinkageNum() const;

    void GetSubListCache(std::vector<std::string> &subContactList) { subContactList.assign(subListCache_.begin(),subListCache_.end()); }
    void AddSubListCache(const std::string& _uri) { subListCache_.push_back(_uri); }
    void DelSubListCache(const std::string& _uri) { subListCache_.remove(_uri);}
    bool HasSubContactCache(const std::string& _uri);


private: 
	static ECSData * instance_;
    std::list<std::string> subListCache_;
    ECSData(const ECSData &);
    ECSData & operator=(const ECSData &);

    BackupDataBaseThread *m_pBackupDataBaseThread;

private:
	std::string oldAccount_; 
    std::string account_;
    std::string sipAccount_; //eserver for login
    std::string uri_;
    std::string binduri_; //eServer use for real uri
    std::string name_;

    std::string entname_; // enterprise name
    
    std::string staffid_;//staff id，企业成员ID，对应eServer UserInfo中的staffID；在设置登录用户系统头像时使用

    bool bSipRegOk_;
    bool bOperDNDFlag;//IPT2.2 sip注册成功后，若登记DND，得取消登记；后续再收到DND的notify消息，不做处理，除非有进行sip重注册且注册成功的操作
}; // class ECSData

  } // namespace ecsdata
} // namespace ecs

#define ECSDATA() (ecs::ecsdata::ECSData::Instance())
