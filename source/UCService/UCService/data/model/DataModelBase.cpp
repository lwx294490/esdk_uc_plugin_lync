#include "stdafx.h"

#include <algorithm>

#include "data/storage/DataStorage.h"
#include "data/model/user/Contact.h"
#include "data/model/user/Staff.h"
#include "data/model/user/config/UserConfig.h"
#include "data/model/user/config/RingSettings.h"
#include "data/model/user/config/TransferNumber.h"
#include "data/model/sys/LoginList.h"
#include "data/model/sys/SysConfig.h"
#include "data/model/history/Record.h"
#include "data/model/history/Conversation.h"
#include "data/model/user/changeAccountRecord.h"

#include "Log.h"

namespace ecs {
  namespace ecsdata {

void LogStdException(const std::exception & e)
{
	ERROR_LOG("std exception : %s",e.what());
}

void LogUnknownException()
{
	ERROR_LOG("unknown exception !");
}

///////////////////////////////////////////////////////////////////////////
//static 
DataModel * DataModel::instance_ = NULL;

void DataModel::Init() const
{
}

void DataModel::Uninit() const
{
    delete instance_;
    instance_ = NULL;
}

void DataModel::CreateSysTables() const
{
  CreateLoginListTabCommand createLoginListTabCmd;
  createLoginListTabCmd.Execute();
  INFO_LOG("LoginListTab created.");

  CreateSysConfigTabCommand createSysConfigTabCmd;
  createSysConfigTabCmd.Execute();
  INFO_LOG("SysConfigTab created.");
}

void DataModel::CreateUserTables() const
{
	CreateContactTabCommand createContactTabCmd;
	createContactTabCmd.Execute();
	INFO_LOG("ContactTab created.");


	CreateStaffTabCommand createStaffTabCmd;
	createStaffTabCmd.Execute();
	INFO_LOG("StaffTab created.");


	CreateUserConfigTabCommand createUserConfigCmd;
	createUserConfigCmd.Execute();
	INFO_LOG("UserConfigTab created.");

	CreateOnlineTipTabCommand createOnlinetipCmd;
	createOnlinetipCmd.Execute();
	INFO_LOG("OnlineTipTab created.");

    CreateSMSSignatureTabCommand createSMSSignatureCmd;
    createSMSSignatureCmd.Execute();
    INFO_LOG("SMSSignatureTab created.");

    CreateTransferNumTabCommand createTransferNumCmd;
    createTransferNumCmd.Execute();
    INFO_LOG("TransferNumTab created.");

	CreateContactRingTabCommand createRingtabCmd;
	createRingtabCmd.Execute();
	INFO_LOG("ContactRingTab created.");


	CreateChangeAccountRecord createChangeAccountRecordTabComand;
	createChangeAccountRecordTabComand.Execute();
	INFO_LOG("ChangeAccountRecordTab created.");
}

static const std::string CONTACT_TAB_STR = "ContactTab";
static const std::string CONTACTTAG_TAB_STR = "CustomTagTab";
static const std::string CONTACTCUSTOMTAG_TAB_STR = "ContactCustomTagTab";
static const std::string STAFF_TAB_STR = "StaffTab";
static const std::string FIXEDGROUP_TAB_STR = "FixedGroupTab";
static const std::string FIXEDGROUPMEM_TAB_STR = "FixedGroupMemberTab";
static const std::string FIXEDGROUPCONFIG_TAB_STR = "FixedGroupConfigTab";
static const std::string DISCUSSGROUP_TAB_STR = "DiscussGroupTab";
static const std::string DISCUSSGROUPMEM_TAB_STR = "DiscussGroupMemberTab";
static const std::string CHANGEACCOUNTRECORD_TAB_STR = "ChangeAccountRecordTab";

static const std::string OLD_UC_CONTACTGROUP_TAB_STR = "ContactGroupTab";

bool DataModel::CheckUserTables() const
{
    INFO_LOG(" Start");
    std::vector<std::string> lstTables;
    lstTables.reserve(30);
    (void)UserTabQueryCommand::QueryTab(lstTables);
    std::vector<std::string>::iterator itBegin = lstTables.begin();
    std::vector<std::string>::iterator itEnd = lstTables.end();
	
    if(std::find(itBegin, itEnd,OLD_UC_CONTACTGROUP_TAB_STR) != itEnd)
	{
		INFO_LOG(" user.db Is From UC1.X");
		return false;
	}

	const std::string staffColFunc= "FUNC";
	if(JudgeColumnIsExist(STAFF_TAB_STR,staffColFunc,"",USERDB_NAME))
	{
		INFO_LOG(" user.db Is From UC2.2");
		return false;
	}
	
    if(std::find(itBegin,itEnd,CONTACT_TAB_STR) == itEnd)
    {
	    CreateContactTabCommand createContactTabCmd;
	    createContactTabCmd.Execute();
	    INFO_LOG("ContactTab created.");
    }
    else
    {
        INFO_LOG("ContactTab exist.");
    }


    if(std::find(itBegin, itEnd,STAFF_TAB_STR) == itEnd)
    {
        CreateStaffTabCommand createStaffTabCmd;
        createStaffTabCmd.Execute();
        INFO_LOG("StaffTab created.");
    }
    else
    {
        INFO_LOG("StaffTab exist.");
    }

	if(std::find(itBegin, itEnd,CHANGEACCOUNTRECORD_TAB_STR) == itEnd)
	{
	    CreateChangeAccountRecord createChangeAccountRecordTabComand;
	    createChangeAccountRecordTabComand.Execute();
	    INFO_LOG("ChangeAccountRecordTab created.");
	}
	else
	{
	    INFO_LOG("ChangeAccountRecordTab exist.");
	}
	return true;
}

void DataModel::CreateHistoryTables() const
{
  history::CreateRecordTabCommand cmdRecord;
  cmdRecord.Execute();
  INFO_LOG("RecordTab created.");

  history::CreateRecordTabConversationIDIndexCommand cmdRecordMakeConversationIDIndex;
  cmdRecordMakeConversationIDIndex.Execute();
  INFO_LOG("RecordTab ConversationIDIndex created.");

  history::CreateRecordTabRecordTypeIndexCommand cmdRecordMakeRecordTypeIndex;
  cmdRecordMakeRecordTypeIndex.Execute();
  INFO_LOG("RecordTab RecordTypeIndex created.");

  history::CreateRecordTabMsgIdIndexCommand cmdRecordMakeMsgIdIndex;
  cmdRecordMakeMsgIdIndex.Execute();
  INFO_LOG("RecordTab MsgIdIndex created.");

  history::DeleteRecordTabUniqueIndexCommand cmdDeleteRecordUniqueIndex;
  cmdDeleteRecordUniqueIndex.Execute();
  INFO_LOG("RecordTab UniqueIndex delete.");

  history::CreateRecordTabUniqueIndexCommand cmdRecordUniqueIndex;
  cmdRecordUniqueIndex.Execute();
  INFO_LOG("RecordTab UniqueIndex created.");

  history::CreateConversationTabCommand cmdConv;
  cmdConv.Execute();
  INFO_LOG("ConversationTab created.");

  history::CreateConversationMsgIdTabCommand cmdConvMsgId;
  cmdConvMsgId.Execute();
  INFO_LOG("ConversationMsgIdTab created.");

  int nRecordRemoved = history::RemoveRecordCommand
    ::RemoveByConversationId("");
  int nConversationRemoved = history::RemoveConversationCommand
    ::RemoveByConversationId("");

  DEBUG_LOG("nRecordRemoved=%d,nConversationRemoved=%d.",nRecordRemoved,nConversationRemoved);

}

bool DataModel::JudgeColumnIsExist(const std::string& _tblName, const std::string& _columnName,
     const std::string _newSql, const std::string& _dbName) const
{
    //INFO_PARAM4(_tblName,_columnName,_newSql,_dbName);
    history::QueryCreateTableStmt qry(_dbName);
    return qry.ColumnIsExist(_tblName,_columnName,_newSql);
}

void DataModel::AlterHistoryTables(const std::string& _tblName, const std::string& _columnName,
     const std::string _newSql, const std::string& _dbName) const
{
    //INFO_PARAM4(_tblName,_columnName,_newSql,_dbName);
    history::AlterHistoryTabCommand cmdAlterTable(_tblName,_columnName,_newSql,_dbName);
    cmdAlterTable.Execute();
}

void DataModel::CreateArchiveTables(const std::string& _dbName) const
{
  history::CreateRecordTabCommand cmdRecord(_dbName);
  cmdRecord.Execute();
  INFO_LOG("RecordTab created.");

  history::CreateRecordTabConversationIDIndexCommand cmdRecordMakeConversationIDIndex(_dbName);
  cmdRecordMakeConversationIDIndex.Execute();
  INFO_LOG("RecordTab ConversationIDIndex created.");

  history::CreateRecordTabRecordTypeIndexCommand cmdRecordMakeRecordTypeIndex(_dbName);
  cmdRecordMakeRecordTypeIndex.Execute();
  INFO_LOG("RecordTab RecordTypeIndex created.");

  history::CreateRecordTabUniqueIndexCommand cmdRecordUniqueIndex(_dbName);
  cmdRecordUniqueIndex.Execute();
  INFO_LOG("RecordTab UniqueIndex created.");

  history::CreateConversationTabCommand cmdConv(_dbName);
  cmdConv.Execute();
  INFO_LOG("ConversationTab created.");

}


void DataModel::ClearUserTables() const
{
    (void)RemoveContactCommand::RemoveAll();
    INFO_LOG("ContactTab Cleared.");

    (void)RemoveStaffCommand::RemoveAll();
    INFO_LOG("removeStaffCmd Cleared.");


}
///////////////////////////////////////////////////////////////////////////
Transanction::Transanction(IDataStorage * ds, bool active)
: ds_(ds), active_(active), nested_(false), commited_(false)
{
  if (!active_)
  {
    return;
  }

  nested_ = !(ds_->GetAutoCommit());
  //DEBUG_LOG(nested_);

  if (!nested_)
  {
    DEBUG_LOG("[ %s ] transaction begin.",ds_->GetDBName().c_str());
    ds_->BeginTransaction();
  }
}

Transanction::~Transanction()
{
  if (!active_)
  {
    return;
  }

  if (!nested_ && !commited_)
  {
    //DEBUG_LOG() << "[" << ds_->GetDBName() << "] transaction rollback.";
    try
    {
      ds_->Rollback();
    }
    catch(...)
    {
    }
  }

  ds_ = NULL;
}

void Transanction::Commit()
{
  if (!active_)
  {
    return;
  }

  if (!nested_)
  {
    DEBUG_LOG("[ %s ] transaction commit.",ds_->GetDBName().c_str());
    ds_->Commit();
    commited_ = true;
  }
}

///////////////////////////////////////////////////////////////////////////
DataModelBase::DataModelBase(const std::string & dsName, int type /*= 0*/) 
: ds_(NULL)
, type_(type)
{
  ds_ = DATASTORAGE_MGR()->GetDataStorage(dsName);
}

  } // namespace ecsdata
} // namespace ecs
