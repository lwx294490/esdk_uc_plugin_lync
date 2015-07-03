#pragma once
#include "data\model\DataModelBase.h"
#include "data\DataType.h"

#ifdef _lint
#define STAFF_TAB
#else
#define STAFF_TAB "StaffTab"
#endif

namespace ecs {
  namespace ecsdata {

struct StaffInfo;

class   CreateStaffTabCommand : public DDLBase
{
public:
  CreateStaffTabCommand() : DDLBase(USERDB_NAME_CACHED) {}

protected:
  virtual void ComposeSQL(std::string & sql);

};

class   AddStaffCommand 
  : public DMLBase<StaffInfo>
{
public:
  AddStaffCommand() : DMLBase<StaffInfo>(USERDB_NAME_CACHED) {}

  DEFINE_BATCH_EXECUTE_MOTHOD(
    AddStaffCommand, BatchAddNotReplace, ADD_OR_REPLACE)
  DEFINE_SINGLE_EXECUTE_MOTHOD(
    AddStaffCommand, SingleAddNotReplace, ADD_OR_REPLACE)

  DEFINE_BATCH_SINGLE_ADD_MOTHOD(AddStaffCommand)

protected:
  enum
  {
    ADD_OR_REPLACE = 0, 
    ADD_NOT_REPLACE 
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<StaffInfo>::ArgObjType & argObj);

};

class   RemoveStaffCommand 
  : public DMLBase<StaffInfo>
{
public:
  RemoveStaffCommand() : DMLBase(USERDB_NAME_CACHED) {}

public:
  static bool RemoveByUri(const std::string & uri);
  static int  RemoveAll();

protected:
  enum
  {
    INVALID, 
    ALL, 
    ACCOUNT,
    URI
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<StaffInfo>::ArgObjType & argObj);

};

class   StaffQuery 
  : public DQLBase<StaffInfo>
{
  friend class StaffFixedGroupQuery;
  friend class BuddyQuery;
  friend class StaffDiscussGroupQuery;

public:
  StaffQuery() : DQLBase(USERDB_NAME_MEM) {}

public:
  static bool QueryByUri(const std::string & uri, 
    DQLBase<StaffInfo>::ResObjType & resObj);
  static bool QueryByAccount(const std::string & account, 
    DQLBase<StaffInfo>::ResObjType & resObj);
  static bool QueryByPhoneNumber(const std::string & phoneNumber, 
    DQLBase<StaffInfo>::ResCtnType & resObj);
  static bool QueryByFullUri(const std::string & fulluri, 
      DQLBase<StaffInfo>::ResCtnType & resObj);
  static bool QueryByEmail(const std::string & email,
	  DQLBase<StaffInfo>::ResCtnType & resObj);
  static bool QueryByDummy(const std::string & dummy, 
      DQLBase<StaffInfo>::ResObjType & resObj);
  static int QueryAll(DQLBase<StaffInfo>::ResCtnType & resObj);
protected:
  enum
  {
    INVALID, 
    ALL, 
    URI,
    PHONENUM,
    ACCOUNT, 
    DUMMY,
    FULLURI,
	EMAIL
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DQLBase<StaffInfo>::ArgObjType & argObj);
  virtual void Extract(IDataManipulation * dm, 
    DQLBase<StaffInfo>::ResObjType & resObj)
  {
    (void)ExtractFromStaffTab(dm, resObj, 0);
  }

  static int ExtractFromStaffTab(IDataManipulation * dm, 
    DQLBase<StaffInfo>::ResObjType & resObj, int startIndex);

};


class   UserTabQueryCommand 
    : public DQLBase<std::string>
{
public:
  UserTabQueryCommand() : DQLBase(USERDB_NAME) {}

public:
  static bool QueryTab(DQLBase<std::string>::ResCtnType & resObj);

protected:
  enum
  {
    TABLE_TYPE
  };

  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DQLBase<std::string>::ArgObjType & argObj);
  virtual void Extract(IDataManipulation * dm, 
    DQLBase<std::string>::ResObjType & resObj);
};

  } // namespace ecsdata
} // namespace ecs
