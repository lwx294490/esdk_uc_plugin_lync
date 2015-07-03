#include "stdafx.h"
#include "data/model/user/Staff.h"

#include "Log.h"

using namespace std;

static const std::string TABLE_TYPE_STR = "table";

namespace ecs {
  namespace ecsdata {

void CreateStaffTabCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "DROP TABLE IF EXISTS "STAFF_TAB";"
    "CREATE TABLE IF NOT EXISTS "STAFF_TAB
    "( URI VARCHAR(128) NOT NULL PRIMARY KEY"
    ", ACCOUNT VARCHAR(64) NOT NULL"
    ", STAFFNO VARCHAR(32) NOT NULL"
    ", NAME VARCHAR(32) NOT NULL"
    ", QPINYIN VARCHAR(32) NOT NULL"
    ", SPINYIN VARCHAR(32) NOT NULL"
    ", GENDER INTEGER NOT NULL"
    ", MOBILEPHONE VARCHAR(32) NOT NULL"
    ", OFFICEPHONE VARCHAR(32) NOT NULL"
    ", OTHERPHONE VARCHAR(32) NOT NULL"
    ", FAX VARCHAR(128) NOT NULL"
    ", EMAIL VARCHAR(128) NOT NULL"
    ", ZIP VARCHAR(512) NOT NULL"
    ", ADDRESS VARCHAR(512) NOT NULL"
    ", TITLE VARCHAR(512) NOT NULL"
    ", DEPTNAME VARCHAR(1024) NOT NULL"
    ", IMAGEID VARCHAR(64) NOT NULL"
    ", SIGNATURE VARCHAR(512) NOT NULL"
    ", POSITION VARCHAR(1024) NOT NULL"
    ", LOCATION VARCHAR(1024) NOT NULL"
    ", TZONE VARCHAR(1024) NOT NULL"
    ", AVTOOL VARCHAR(32) NOT NULL"
    ", DEVICETYPE VARCHAR(32) NOT NULL"
    ", WEBSITE VARCHAR(512) NOT NULL"
	", IPPHONE1 VARCHAR(128) NOT NULL"
	", IPPHONE2 VARCHAR(128) NOT NULL"
    ", IPPHONE3 VARCHAR(128) NOT NULL"
    ", IPPHONE4 VARCHAR(128) NOT NULL"
    ", IPPHONE5 VARCHAR(128) NOT NULL"
    ", IPPHONE6 VARCHAR(128) NOT NULL"
	", OFFICEPHONE2 VARCHAR(128) NOT NULL"
    ", OFFICEPHONE3 VARCHAR(128) NOT NULL"
    ", OFFICEPHONE4 VARCHAR(128) NOT NULL"
    ", OFFICEPHONE5 VARCHAR(128) NOT NULL"
    ", OFFICEPHONE6 VARCHAR(128) NOT NULL"
	", HOMEPHONE VARCHAR(128) NOT NULL"
	", OTHERPHONE2 VARCHAR(32) NOT NULL"
	", FULLURI VARCHAR(128) NOT NULL"
    ", DUMMY VARCHAR(128) NOT NULL"
    ", MODIFYTIME VARCHAR(128) NOT NULL"
    ");";
}

///////////////////////////////////////////////////////////////////////////
void AddStaffCommand::ComposeSQL(std::string & sql)
{

  std::string onConfictClause = "OR ";
  switch (type_)
  {
  case ADD_OR_REPLACE:
    (void)onConfictClause.append("REPLACE");
    break;
  case ADD_NOT_REPLACE:
    (void)onConfictClause.append("IGNORE");
    break;
  default:
    break;
  }

  std::string INSERT_STAFF = 
    "INSERT " + onConfictClause + " INTO "STAFF_TAB
    "( URI"
    ", ACCOUNT"
    ", STAFFNO"
    ", NAME"
    ", QPINYIN"
    ", SPINYIN"
    ", GENDER"
    ", MOBILEPHONE"
    ", OFFICEPHONE"
    ", OTHERPHONE"
    ", FAX"
    ", EMAIL"
    ", ZIP"
    ", ADDRESS"
    ", TITLE"
    ", DEPTNAME"
    ", IMAGEID"
    ", SIGNATURE"
    ", POSITION"
    ", LOCATION"
    ", TZONE"
    ", AVTOOL"
    ", DEVICETYPE"
    ", WEBSITE"
	", IPPHONE1"
	", IPPHONE2"
    ", IPPHONE3"
    ", IPPHONE4"
    ", IPPHONE5"
    ", IPPHONE6"
	", OFFICEPHONE2"
    ", OFFICEPHONE3"
    ", OFFICEPHONE4"
    ", OFFICEPHONE5"
    ", OFFICEPHONE6"
	", HOMEPHONE"
	", OTHERPHONE2"
	", FULLURI"
    ", DUMMY"
    ", MODIFYTIME"
    ") VALUES( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

  sql = INSERT_STAFF;
}

void AddStaffCommand::Bind(IDataManipulation * dm, 
                           const DMLBase<StaffInfo>::ArgObjType & argObj)
{
	DEBUG_LOG("type_=%d, argObj.uri=%s, argObj.account=%s, argObj.name=%s"
		, type_
		, argObj.uri.c_str()
		, argObj.account.c_str()
		, argObj.name.c_str());

	int i = 0;
	dm->Bind(++i, argObj.uri);
	dm->Bind(++i, argObj.account);
	dm->Bind(++i, argObj.staffNo);
	dm->Bind(++i, argObj.name);
	dm->Bind(++i, argObj.qPinyin);
	dm->Bind(++i, argObj.sPinyin);
	dm->Bind(++i, argObj.gender);
	dm->Bind(++i, argObj.mobilePhone);
	dm->Bind(++i, argObj.officePhone);
	dm->Bind(++i, argObj.otherPhone);
	dm->Bind(++i, argObj.fax);
	dm->Bind(++i, argObj.email);
	dm->Bind(++i, argObj.zip);
	dm->Bind(++i, argObj.addr);
	dm->Bind(++i, argObj.title);
	dm->Bind(++i, argObj.deptName);

	dm->Bind(++i, argObj.imageID);
	dm->Bind(++i, argObj.signature);
	dm->Bind(++i, argObj.position);
	dm->Bind(++i, argObj.location);
	dm->Bind(++i, argObj.tzone);
	dm->Bind(++i, argObj.avtool);
	dm->Bind(++i, argObj.device);
	dm->Bind(++i, argObj.website);
	dm->Bind(++i, argObj.ipphone1);
	dm->Bind(++i, argObj.ipphone2);
	dm->Bind(++i, argObj.ipphone3);
	dm->Bind(++i, argObj.ipphone4);
	dm->Bind(++i, argObj.ipphone5);
	dm->Bind(++i, argObj.ipphone6);
	dm->Bind(++i, argObj.officePhone2);
	dm->Bind(++i, argObj.officePhone3);
	dm->Bind(++i, argObj.officePhone4);
	dm->Bind(++i, argObj.officePhone5);
	dm->Bind(++i, argObj.officePhone6);
	dm->Bind(++i, argObj.homePhone);
	dm->Bind(++i, argObj.otherPhone2);
	dm->Bind(++i, argObj.fullUri);
	dm->Bind(++i, argObj.dummy);
	dm->Bind(++i, argObj.modifytime);
}

///////////////////////////////////////////////////////////////////////////
void RemoveStaffCommand::ComposeSQL(std::string & sql)
{
  const std::string DELETE_STAFF = "DELETE FROM "STAFF_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case ACCOUNT:
    (void)whereClause.append("ACCOUNT = ?");
    break;
  case URI:
    (void)whereClause.append("URI = ?");
    break;
  default:
    WARN_LOG("unknown type : %d",type_);
    sql = "";
    return;
  }

  sql = DELETE_STAFF + whereClause + ";";
}

void RemoveStaffCommand::Bind(IDataManipulation * dm, 
  const DMLBase<StaffInfo>::ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case ACCOUNT:
    //INFO_PARAM1(argObj.account);
    dm->Bind(++i, argObj.account);
    break;
  case URI:
    //INFO_PARAM1(argObj.uri);
    dm->Bind(++i, argObj.uri);
    break;
  default:
    WARN_LOG("unknown type : %d",type_);
    break;
  }
}

//static 
bool RemoveStaffCommand::RemoveByUri(const std::string & uri)
{
  //TRACE_FUNC1(uri);

  StaffInfo argObj;
  argObj.uri = uri;

  RemoveStaffCommand cmd;
  cmd.SingleExecute(URI, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed == 1;
}

int  RemoveStaffCommand::RemoveAll()
{
    ContactInfo argObj;

    RemoveStaffCommand cmd;
    cmd.SingleExecute(ALL, argObj);

    //INFO_PARAM1(cmd.changed);
    return cmd.changed;
}

///////////////////////////////////////////////////////////////////////////
void StaffQuery::ComposeSQL(std::string & sql)
{
  const std::string QUERY_STAFF = "SELECT * FROM "STAFF_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case URI:
    (void)whereClause.append("URI  = ?");
    break;
  case PHONENUM:
    (void)whereClause.append(
      "MOBILEPHONE LIKE ? OR OFFICEPHONE = ? OR OTHERPHONE = ? OR OFFICEPHONE2 = ? OR OFFICEPHONE3 = ? OR OFFICEPHONE4 = ?  OR OFFICEPHONE5 = ?  OR OFFICEPHONE6 = ? OR HOMEPHONE = ? OR OTHERPHONE2 = ? OR FULLURI LIKE ? OR URI LIKE ? OR IPPHONE1 LIKE ? OR IPPHONE2 LIKE ? OR IPPHONE3 LIKE ? OR IPPHONE4 LIKE ? OR IPPHONE5 LIKE ? OR IPPHONE6 LIKE ?");
    break;
  case ACCOUNT:
    (void)whereClause.append("ACCOUNT = ?");
    break;
  case DUMMY:
      (void)whereClause.append("DUMMY = ?");
      break;
  case FULLURI:
    (void)whereClause.append("FULLURI = ?");
    break;
  case EMAIL:
	(void)whereClause.append("EMAIL = ?");
	break;
  default:
    WARN_LOG("unknown type : %d",type_);
    sql = "";
    return;
  }

  sql = QUERY_STAFF + whereClause + ";";
}

void StaffQuery::Bind(IDataManipulation * dm, 
                      const DQLBase<StaffInfo>::ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case URI:
    ////INFO_PARAM1(argObj.uri);
    dm->Bind(++i, argObj.uri);
    break;
  case PHONENUM:
    {
      ////INFO_PARAM1(argObj.mobilePhone);
	  string strMobilePhone = "%" + argObj.mobilePhone;
      dm->Bind(++i, strMobilePhone);
      dm->Bind(++i, argObj.mobilePhone);
      dm->Bind(++i, argObj.mobilePhone);
	  dm->Bind(++i, argObj.mobilePhone);
	  dm->Bind(++i, argObj.mobilePhone);
	  dm->Bind(++i, argObj.mobilePhone);
	  dm->Bind(++i, argObj.mobilePhone);
      dm->Bind(++i, argObj.mobilePhone);
      dm->Bind(++i, argObj.mobilePhone);
      dm->Bind(++i, argObj.mobilePhone);
      dm->Bind(++i, "sip:" + argObj.mobilePhone + "@%");
      dm->Bind(++i, "sip:" + argObj.mobilePhone + "@%");
	  dm->Bind(++i, "sip:" + argObj.mobilePhone + "@%");
	  dm->Bind(++i, "sip:" + argObj.mobilePhone + "@%");
      dm->Bind(++i, "sip:" + argObj.mobilePhone + "@%");
      dm->Bind(++i, "sip:" + argObj.mobilePhone + "@%");
      dm->Bind(++i, "sip:" + argObj.mobilePhone + "@%");
      dm->Bind(++i, "sip:" + argObj.mobilePhone + "@%");
    }
    break;
  case ACCOUNT:
    ////INFO_PARAM1(argObj.account);
    dm->Bind(++i, argObj.account);
  	break;
  case DUMMY:
      dm->Bind(++i, argObj.dummy);
      break;
  case FULLURI:
  	////INFO_PARAM1(argObj.account);
  	dm->Bind(++i, argObj.fullUri);
    break;
  case EMAIL:
    dm->Bind(++i, argObj.email);
	break;
  default:
    WARN_LOG("unknown type : %d",type_);
    break;
  }
}

//static 
int StaffQuery::ExtractFromStaffTab(IDataManipulation * dm, 
  DQLBase<StaffInfo>::ResObjType & resObj, int startIndex)
{
  int i = 0;
  dm->GetValue(startIndex + i++, resObj.uri);
  dm->GetValue(startIndex + i++, resObj.account);
  dm->GetValue(startIndex + i++, resObj.staffNo);
  dm->GetValue(startIndex + i++, resObj.name);
  dm->GetValue(startIndex + i++, resObj.qPinyin);
  dm->GetValue(startIndex + i++, resObj.sPinyin);
  dm->GetValue(startIndex + i++, resObj.gender);
  dm->GetValue(startIndex + i++, resObj.mobilePhone);
  dm->GetValue(startIndex + i++, resObj.officePhone);
  dm->GetValue(startIndex + i++, resObj.otherPhone);
  dm->GetValue(startIndex + i++, resObj.fax);
  dm->GetValue(startIndex + i++, resObj.email);
  dm->GetValue(startIndex + i++, resObj.zip);
  dm->GetValue(startIndex + i++, resObj.addr);
  dm->GetValue(startIndex + i++, resObj.title);
  dm->GetValue(startIndex + i++, resObj.deptName);
  dm->GetValue(startIndex + i++, resObj.imageID);
  dm->GetValue(startIndex + i++, resObj.signature);
  dm->GetValue(startIndex + i++, resObj.position);
  dm->GetValue(startIndex + i++, resObj.location);
  dm->GetValue(startIndex + i++, resObj.tzone);
  dm->GetValue(startIndex + i++, resObj.avtool);
  dm->GetValue(startIndex + i++, resObj.device);
  dm->GetValue(startIndex + i++, resObj.website);
  dm->GetValue(startIndex + i++, resObj.ipphone1);
  dm->GetValue(startIndex + i++, resObj.ipphone2);
  dm->GetValue(startIndex + i++, resObj.ipphone3);
  dm->GetValue(startIndex + i++, resObj.ipphone4);
  dm->GetValue(startIndex + i++, resObj.ipphone5);
  dm->GetValue(startIndex + i++, resObj.ipphone6);
  dm->GetValue(startIndex + i++, resObj.officePhone2);
  dm->GetValue(startIndex + i++, resObj.officePhone3);
  dm->GetValue(startIndex + i++, resObj.officePhone4);
  dm->GetValue(startIndex + i++, resObj.officePhone5);
  dm->GetValue(startIndex + i++, resObj.officePhone6);
  dm->GetValue(startIndex + i++, resObj.homePhone);
  dm->GetValue(startIndex + i++, resObj.otherPhone2);
  dm->GetValue(startIndex + i++, resObj.fullUri);
  dm->GetValue(startIndex + i++, resObj.dummy);
  dm->GetValue(startIndex + i++, resObj.modifytime);
  return i;
}

//static 
bool StaffQuery::QueryByUri(const std::string & uri, 
                            DQLBase<StaffInfo>::ResObjType & resObj)
{
  if (uri.empty())
  {
    return false;
  }

  StaffInfo argObj;
  argObj.uri = uri;

  StaffQuery qry;
  bool ret = qry.SingleExecute(URI, argObj, resObj);

  DEBUG_LOG("uri=%s, qry.count=%d",uri.c_str(), qry.count);
  return ret;
}

//static 
bool StaffQuery::QueryByAccount(const std::string & account, 
                                DQLBase<StaffInfo>::ResObjType & resObj)
{
  if (account.empty())
  {
    return false;
  }

  StaffInfo argObj;
  argObj.account = account;

  StaffQuery qry;
  bool ret = qry.SingleExecute(ACCOUNT, argObj, resObj);

  DEBUG_LOG("account=%s, qry.count=%d",account.c_str(), qry.count);
  return ret;
}

//static 
bool StaffQuery::QueryByPhoneNumber(const std::string & phoneNumber, 
                                    DQLBase<StaffInfo>::ResCtnType & resObj)
{
  if (phoneNumber.empty())
  {
    return false;
  }

  StaffInfo argObj;
  argObj.mobilePhone = phoneNumber;

  StaffQuery qry;
  qry.BatchExecute(PHONENUM, argObj, resObj);

  DEBUG_LOG("phoneNumber=%s, qry.count=%d",phoneNumber.c_str(), qry.count);

  if(resObj.size() == 0)
  {
      return false;
  }
  return true;
}

bool StaffQuery::QueryByDummy(const std::string & dummy, 
                         DQLBase<StaffInfo>::ResObjType & resObj)
{
    if (dummy.empty())
    {
        return false;
    }

    StaffInfo argObj;
    argObj.dummy = dummy;

    StaffQuery qry;
    bool ret = qry.SingleExecute(DUMMY, argObj, resObj);

    DEBUG_LOG("dummy=%s, qry.count=%d",dummy.c_str(), qry.count);
    return ret;
}

int StaffQuery::QueryAll(DQLBase<StaffInfo>::ResCtnType & resObj)
{
    StaffQuery qry;
	StaffInfo argObj;
    qry.BatchExecute(ALL, argObj, resObj);
    DEBUG_LOG("qry.count=%d", qry.count);
    return qry.count;
}

//static 
bool StaffQuery::QueryByFullUri(const std::string & fulluri, 
                                    DQLBase<StaffInfo>::ResCtnType & resObj)
{
    if (fulluri.empty())
    {
        return false;
    }

    StaffInfo argObj;
    argObj.fullUri = fulluri;

    StaffQuery qry;
    qry.BatchExecute(FULLURI, argObj, resObj);

    DEBUG_LOG("fulluri=%s, qry.count=%d",fulluri.c_str(), qry.count);

    if(resObj.size() == 0)
    {
        return false;
    }
    return true;
}

bool StaffQuery::QueryByEmail(const std::string & email, 
							      DQLBase<StaffInfo>::ResCtnType & resObj)
{
	if (email.empty())
	{
		return false;
	}

	StaffInfo argObj;
	argObj.email = email;

	StaffQuery qry;
	qry.BatchExecute(EMAIL, argObj, resObj);

	if (resObj.size() == 0)
	{
		return false;
	}

	return true;
}


bool UserTabQueryCommand::QueryTab(DQLBase<std::string>::ResCtnType & resObj)
{
    UserTabQueryCommand qry;
    qry.BatchExecute(TABLE_TYPE, TABLE_TYPE_STR, resObj);

    //INFO_PARAM1(qry.count);

    if(resObj.empty())
    {
        return false;
    }
    return true;
}

void UserTabQueryCommand::ComposeSQL(std::string & sql)
{
    if(type_ == TABLE_TYPE)
    {
        sql = "select name from sqlite_master where type = ?";
    }
    return;
}

void UserTabQueryCommand::Bind(IDataManipulation * dm, const DQLBase<std::string>::ArgObjType & argObj)
{
    int i = 0;
    if (type_ == TABLE_TYPE)
    {
        //INFO_PARAM1(argObj);
        dm->Bind(++i, argObj);
    }
    return;
}

void UserTabQueryCommand::Extract(IDataManipulation * dm, DQLBase<std::string>::ResObjType & resObj)
{
    int i = 0;
    dm->GetValue(i++, resObj);
}

  } // namespace ecsdata
} // namespace ecs


