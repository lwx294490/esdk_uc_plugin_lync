#pragma once
#include "data\model\DataModelBase.h"
#include "data\DataType.h"
#ifdef _lint
#define CHANGE_ACCOUNT_RECORD
#else
#define CHANGE_ACCOUNT_RECORD "ChangeAccountRecordTab"
#endif

namespace ecs {
  namespace ecsdata {

struct changeAccountItem;

class   CreateChangeAccountRecord : public DDLBase
{
public:
  CreateChangeAccountRecord() : DDLBase(USERDB_NAME_CACHED) {}

protected:
  virtual void ComposeSQL(std::string & sql);

};


class   AddChangeAccountRecord : public DMLBase<changeAccountItem>
{
public:
    AddChangeAccountRecord() : DMLBase(USERDB_NAME_CACHED) {}

public:
    static bool AddRecord(const std::string & oldAcc, const std::string & newAcc);
	static int AddRecords(const std::vector<changeAccountItem> & vecAddInfo);
protected:
	
    virtual void ComposeSQL(std::string & sql);
    virtual void Bind(IDataManipulation * dm, 
    const DMLBase<changeAccountItem>::ArgObjType & argObj);

};


class   QueryChangeAccountRecord :public DQLBase<changeAccountItem>
{
public:
    QueryChangeAccountRecord() : DQLBase(USERDB_NAME_MEM) {}

public:
    static bool QueryRecord(const std::string & newAcc, DQLBase<changeAccountItem>::ResObjType & resObj);
	static bool QueryRecordByOldAcc(const std::string & oldAcc, DQLBase<changeAccountItem>::ResObjType & resObj);
	static int QueryRecordAll( DQLBase<changeAccountItem>::ResCtnType & resCtn);
protected:
	enum
	{
	    QUERY_BY_NEW_ACC,
		QUERY_BY_OLD_ACC,
		QUERY_ALL
	};
    virtual void ComposeSQL(std::string & sql);
    virtual void Bind(IDataManipulation * dm, 
    const DQLBase<changeAccountItem>::ArgObjType & argObj);
	virtual void Extract(IDataManipulation * dm, 
    DQLBase<changeAccountItem>::ResObjType & resObj)
    {
        (void)ExtractFromChangeAccTab(dm, resObj, 0);
    }
	static int ExtractFromChangeAccTab(IDataManipulation * dm, 
    DQLBase<changeAccountItem>::ResObjType & resObj, int startIndex);
};

class   UpdataChangeAccountRecord :public DMLBase<changeAccountItem>
{
public:
    UpdataChangeAccountRecord() : DMLBase(USERDB_NAME_CACHED) {}
public:
    static bool UpdataRecord(const std::string & oldAcc, const std::string & newAcc);

protected:
    virtual void ComposeSQL(std::string & sql);
    virtual void Bind(IDataManipulation * dm, 
    const DMLBase<changeAccountItem>::ArgObjType & argObj);
};

  } // namespace ecsdata
} // namespace ecs
