#include "stdafx.h"
#include "changeAccountRecord.h"

#include "Log.h"

namespace ecs {
  namespace ecsdata {

void CreateChangeAccountRecord::ComposeSQL(std::string & sql)
{
	sql =     "CREATE TABLE IF NOT EXISTS "CHANGE_ACCOUNT_RECORD
    "( ID INTEGER PRIMARY KEY AUTOINCREMENT"
	", NEWACC VARCHAR(64) NOT NULL"
    ", OLDACC VARCHAR(64) NOT NULL"
    ");";
}

bool AddChangeAccountRecord::AddRecord(const std::string & oldAcc, const std::string & newAcc)
{
	changeAccountItem addItem;

	addItem.newAcc = newAcc;
	addItem.oldAcc = oldAcc;

	AddChangeAccountRecord add;
	add.SingleExecute(0,addItem);

	//INFO_PARAM1(add.changed);
    return add.changed == 1;
}
int AddChangeAccountRecord::AddRecords(const std::vector<changeAccountItem> & vecAddInfo)
{
	AddChangeAccountRecord add;
	add.BatchExecute(0,vecAddInfo);
	DEBUG_LOG("add.changed=%d",add.changed);
	return add.changed;
}


void AddChangeAccountRecord::ComposeSQL(std::string & sql)
{
	sql = 
		 "INSERT OR IGNORE INTO "CHANGE_ACCOUNT_RECORD
    "( NEWACC"
	", OLDACC"
    ") VALUES ( ?, ?);";
}

void AddChangeAccountRecord::Bind(IDataManipulation * dm, 
    const DMLBase<changeAccountItem>::ArgObjType & argObj)
{
	int i = 0;
	dm->Bind(++i, argObj.newAcc);
	dm->Bind(++i, argObj.oldAcc);
}


bool QueryChangeAccountRecord::QueryRecord(const std::string & newAcc,DQLBase<changeAccountItem>::ResObjType & resObj)
{
	QueryChangeAccountRecord qry;
	changeAccountItem qryItem;
	qryItem.newAcc = newAcc;

	bool ret = qry.SingleExecute(QUERY_BY_NEW_ACC,qryItem,resObj);
	DEBUG_LOG("newAcc=%s, qry.count=%d",newAcc.c_str(), qry.count);
	return ret;
}

bool QueryChangeAccountRecord::QueryRecordByOldAcc(const std::string & oldAcc, DQLBase<changeAccountItem>::ResObjType & resObj)
{
	QueryChangeAccountRecord qry;
	changeAccountItem qryItem;
	qryItem.oldAcc = oldAcc;

	bool ret = qry.SingleExecute(QUERY_BY_OLD_ACC,qryItem,resObj);
	DEBUG_LOG("oldAcc=%s, qry.count=%d",oldAcc.c_str(), qry.count);
	return ret;
}

int QueryChangeAccountRecord::QueryRecordAll( DQLBase<changeAccountItem>::ResCtnType & resCtn)
{
	QueryChangeAccountRecord qry;
	changeAccountItem argObj;

	qry.BatchExecute(QUERY_ALL,argObj,resCtn);
	DEBUG_LOG("qry.count=%d",qry.count);
	return qry.count;
}

void QueryChangeAccountRecord::ComposeSQL(std::string & sql)
{
	sql = "SELECT * FROM "CHANGE_ACCOUNT_RECORD;
	switch(type_)
	{
	case  QUERY_BY_NEW_ACC:
		(void)sql.append(" WHERE NEWACC = ?");
		break;
	case QUERY_BY_OLD_ACC:
		(void)sql.append(" WHERE OLDACC = ?");
		break;
	case QUERY_ALL:
		break;
    default:
		WARN_LOG("unknown type : %d",type_);
		sql = "";
		return;
	}
}

void QueryChangeAccountRecord::Bind(IDataManipulation * dm, 
    const DMLBase<changeAccountItem>::ArgObjType & argObj)
{
	int i = 0;
	switch (type_)
	{
	case QUERY_BY_NEW_ACC:
		//INFO_PARAM1(argObj.newAcc);
		dm->Bind(++i, argObj.newAcc);
	    break;
	case QUERY_BY_OLD_ACC:
		//INFO_PARAM1(argObj.oldAcc);
		dm->Bind(++i, argObj.oldAcc);
		break;
	case  QUERY_ALL:
		break;
	default:
		WARN_LOG("unknown type : %d",type_);
		break;
	}
}

int QueryChangeAccountRecord::ExtractFromChangeAccTab(IDataManipulation * dm, 
  DQLBase<changeAccountItem>::ResObjType & resObj, int startIndex)
{
  int i = 1;
  dm->GetValue(startIndex + i++, resObj.newAcc);
  dm->GetValue(startIndex + i++, resObj.oldAcc);
  
  return i;
}

bool UpdataChangeAccountRecord::UpdataRecord(const std::string & oldAcc, const std::string & newAcc)
{
	UpdataChangeAccountRecord cmd;
	changeAccountItem updataItem;

	updataItem.newAcc = newAcc;
	updataItem.oldAcc = oldAcc;

	cmd.SingleExecute(0,updataItem);
	int nChanged = cmd.changed;
	//INFO_PARAM1(nChanged);
    return nChanged == 1;
}

void UpdataChangeAccountRecord::ComposeSQL(std::string & sql)
{
	sql = "UPDATE "CHANGE_ACCOUNT_RECORD" SET "
		"OLDACC = ? WHERE NEWACC = ?";
}

void UpdataChangeAccountRecord::Bind(IDataManipulation * dm, 
    const DMLBase<changeAccountItem>::ArgObjType & argObj)
{
	int i = 0;
	dm->Bind(++i, argObj.newAcc);
	dm->Bind(++i, argObj.oldAcc);
}

 } // namespace ecsdata
} // namespace ecs

