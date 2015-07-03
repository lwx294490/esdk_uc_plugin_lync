#include "stdafx.h"
#include "data/model/user/Contact.h"

#include "Log.h"

using namespace std;

namespace ecs {
  namespace ecsdata {

///////////////////////////////////////////////////////////////////////////
void CreateContactTabCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "DROP TABLE IF EXISTS "CONTACT_TAB";"
    "CREATE TABLE IF NOT EXISTS "CONTACT_TAB
    "( CID VARCHAR(32) NOT NULL PRIMARY KEY"
    ", URI VARCHAR(128) NOT NULL"
    ", FULLURI VARCHAR(128) NOT NULL"
    ", ACCOUNT VARCHAR(64) NOT NULL"
    ", STAFFNO VARCHAR(32) NOT NULL"
    ", NAME VARCHAR(32) NOT NULL"
    ", NICKNAME VARCHAR(32) NOT NULL"
    ", GENDER INTEGER NOT NULL"
    ", MOBILEPHONE VARCHAR(32) NOT NULL"
    ", OFFICEPHONE VARCHAR(32) NOT NULL"
    ", OTHERPHONE VARCHAR(32) NOT NULL"
    ", FAX VARCHAR(128) NOT NULL"
    ", EMAIL VARCHAR(128) NOT NULL"
    ", ZIP VARCHAR(512) NOT NULL"
    ", ADDRESS VARCHAR(512) NOT NULL"
    ", TITLE VARCHAR(512) NOT NULL"
    ", DESC VARCHAR(512) NOT NULL"
    ", CORPNAME VARCHAR(512) NOT NULL"
    ", DEPTNAME VARCHAR(512) NOT NULL"
    ", WEBSITE VARCHAR(512) NOT NULL"
	", TERMINALTYPE VARCHAR(8) NOT NULL"
	", QPINYIN VARCHAR(32) NOT NULL"  
	", OFFICEPHONE2 VARCHAR(128) NOT NULL"
    ", OFFICEPHONE3 VARCHAR(128) NOT NULL"
    ", OFFICEPHONE4 VARCHAR(128) NOT NULL"
    ", OFFICEPHONE5 VARCHAR(128) NOT NULL"
    ", OFFICEPHONE6 VARCHAR(128) NOT NULL"
	", HOMEPHONE VARCHAR(128) NOT NULL"
    ", DUMMY VARCHAR(128) NOT NULL"
    ");";
}

///////////////////////////////////////////////////////////////////////////
//static 
int AddContactCommand::maxContactID = 0;

void AddContactCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "INSERT OR REPLACE INTO "CONTACT_TAB
    "( CID"
    ", URI"
    ", FULLURI"
    ", ACCOUNT"
    ", STAFFNO"
    ", NAME"
    ", NICKNAME"
    ", GENDER"
    ", MOBILEPHONE"
    ", OFFICEPHONE"
    ", OTHERPHONE"
    ", FAX"
    ", EMAIL"
    ", ZIP"
    ", ADDRESS"
    ", TITLE"
    ", DESC"
    ", CORPNAME"
    ", DEPTNAME"
    ", WEBSITE"
	", TERMINALTYPE"
	", QPINYIN"
	", OFFICEPHONE2"
    ", OFFICEPHONE3"
    ", OFFICEPHONE4"
    ", OFFICEPHONE5"
    ", OFFICEPHONE6"
	", HOMEPHONE"
    ", DUMMY"
    ") VALUES( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
}

void AddContactCommand::Bind(IDataManipulation * dm, 
  const DMLBase<ContactInfo>::ArgObjType & argObj)
{
  //INFO_PARAM3(argObj.cid, argObj.uri, argObj.name);

  int i = 0;
  dm->Bind(++i, argObj.cid);
  dm->Bind(++i, argObj.uri);
  dm->Bind(++i, argObj.fullUri);
  dm->Bind(++i, argObj.account);
  dm->Bind(++i, argObj.staffNo);
  dm->Bind(++i, argObj.name);
  dm->Bind(++i, argObj.nickName);
  dm->Bind(++i, argObj.gender);
  dm->Bind(++i, argObj.mobilePhone);
  dm->Bind(++i, argObj.officePhone);
  dm->Bind(++i, argObj.otherPhone);
  dm->Bind(++i, argObj.fax);
  dm->Bind(++i, argObj.email);
  dm->Bind(++i, argObj.zip);
  dm->Bind(++i, argObj.addr);
  dm->Bind(++i, argObj.title);
  dm->Bind(++i, argObj.desc);
  dm->Bind(++i, argObj.corpName);
  dm->Bind(++i, argObj.deptName);
  dm->Bind(++i, argObj.website);
  dm->Bind(++i, argObj.terminalType);
  dm->Bind(++i, argObj.qPinyin);//custom contact's pinyin
  dm->Bind(++i, argObj.officePhone2);
  dm->Bind(++i, argObj.officePhone3);
  dm->Bind(++i, argObj.officePhone4);
  dm->Bind(++i, argObj.officePhone5);
  dm->Bind(++i, argObj.officePhone6);
  dm->Bind(++i, argObj.homePhone);
  dm->Bind(++i, argObj.dummy);
}

void AddContactCommand::OnExecuted(
  const DMLBase<ContactInfo>::ArgObjType & argObj)
{
  int cid = 0;

  std::string strCid = argObj.cid;
  if(std::string::npos != strCid.find("cid"))
  {
      strCid = strCid.substr(3, strCid.size() - 3);
  }

  try {
    cid = atoi(strCid.c_str());
  }
  catch (...) {
    WARN_LOG("exception in parsing cid : %s",argObj.cid.c_str());
    return;
  }

  if (cid > maxContactID)
  {
    //DEBUG_LOG(cid);
    maxContactID = cid;
  }
}

///////////////////////////////////////////////////////////////////////////
void RemoveContactCommand::ComposeSQL(std::string & sql)
{
  const std::string DELETE_CONTACT = "DELETE FROM "CONTACT_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case URI:
    (void)whereClause.append("URI = ?");
    break;
  case CID:
    (void)whereClause.append("CID = ?");
    break;
  default:
    WARN_LOG("unknown type : %d",type_);
    sql = "";
    return;
  }

  sql = DELETE_CONTACT + whereClause + ";";
}

void RemoveContactCommand::Bind(IDataManipulation * dm, 
  const DMLBase<ContactInfo>::ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case URI:
    //INFO_PARAM1(argObj.uri);
    dm->Bind(++i, argObj.uri);
    break;
  case CID:
    //INFO_PARAM1(argObj.cid);
    dm->Bind(++i, argObj.cid);
    break;    
  default:
    WARN_LOG("unknown type : %d",type_);
    break;
  }
}

//static 
bool RemoveContactCommand::RemoveByContactId(const std::string & cid)
{
  ContactInfo argObj;
  argObj.cid = cid;

  RemoveContactCommand cmd;
  cmd.SingleExecute(CID, argObj);

  //DEBUG_LOG(cid, cmd.changed);
  return cmd.changed == 1;
}

int RemoveContactCommand::RemoveAll()
{
    ContactInfo argObj;

    RemoveContactCommand cmd;
    cmd.SingleExecute(ALL, argObj);

    //INFO_PARAM1(cmd.changed);
    return cmd.changed;
}

///////////////////////////////////////////////////////////////////////////
void ContactQuery::ComposeSQL(std::string & sql)
{
  const std::string QUERY_CONTACT = "SELECT * FROM "CONTACT_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case CID:
    (void)whereClause.append("CID = ?");
    break;
  case URI:
    (void)whereClause.append("URI = ?");
    break;
  case CID_URI:
    (void)whereClause.append("CID = ? AND URI = ?");
    break;
  case ACCOUNT:
    (void)whereClause.append("ACCOUNT = ?");
    break;
  case PHONENUM:
    (void)whereClause.append(
      "MOBILEPHONE = ? OR OFFICEPHONE = ? OR OTHERPHONE = ? OR OFFICEPHONE2 = ? OR OFFICEPHONE3 = ? OR OFFICEPHONE4 = ? OR OFFICEPHONE5 = ? OR OFFICEPHONE6 = ? OR HOMEPHONE = ?");
    break;
  case FULLURI:
    (void)whereClause.append("FULLURI = ?");
    break;
  case EMAIL:
    (void)whereClause.append("EMAIL = ?");
	break;
  default:
    sql = "";
    WARN_LOG("unknown type : %d",type_);

    return;
  }

  sql = QUERY_CONTACT + whereClause + ";";
}

void ContactQuery::Bind(IDataManipulation * dm, 
                        const DQLBase<ContactInfo>::ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case CID:
    ////INFO_PARAM1(argObj.cid);
    dm->Bind(++i, argObj.cid);
    break;
  case URI:
    ////INFO_PARAM1(argObj.uri);
    dm->Bind(++i, argObj.uri);
    break;
  case CID_URI:
    ////INFO_PARAM2(argObj.cid, argObj.uri);
    dm->Bind(++i, argObj.cid);
    dm->Bind(++i, argObj.uri);
    break;
  case ACCOUNT:
    ////INFO_PARAM1(argObj.account);
    dm->Bind(++i, argObj.account);
    break;
  case PHONENUM:
    ////INFO_PARAM1(argObj.mobilePhone);
    dm->Bind(++i, argObj.mobilePhone);
    dm->Bind(++i, argObj.mobilePhone);
    dm->Bind(++i, argObj.mobilePhone);
	dm->Bind(++i, argObj.mobilePhone);
	dm->Bind(++i, argObj.mobilePhone);
    dm->Bind(++i, argObj.mobilePhone);
    dm->Bind(++i, argObj.mobilePhone);
    dm->Bind(++i, argObj.mobilePhone);
    dm->Bind(++i, argObj.mobilePhone);
    break;
  case FULLURI:
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
int ContactQuery::ExtractFromContactTab(IDataManipulation * dm, 
  DQLBase<ContactInfo>::ResObjType & resObj, int startIndex)
{
  int i = 0;

  dm->GetValue(startIndex + i++, resObj.cid);
  dm->GetValue(startIndex + i++, resObj.uri);
  dm->GetValue(startIndex + i++, resObj.fullUri);
  dm->GetValue(startIndex + i++, resObj.account);
  dm->GetValue(startIndex + i++, resObj.staffNo);
  dm->GetValue(startIndex + i++, resObj.name);
  dm->GetValue(startIndex + i++, resObj.nickName);
  dm->GetValue(startIndex + i++, resObj.gender);
  dm->GetValue(startIndex + i++, resObj.mobilePhone);
  dm->GetValue(startIndex + i++, resObj.officePhone);
  dm->GetValue(startIndex + i++, resObj.otherPhone);
  dm->GetValue(startIndex + i++, resObj.fax);
  dm->GetValue(startIndex + i++, resObj.email);
  dm->GetValue(startIndex + i++, resObj.zip);
  dm->GetValue(startIndex + i++, resObj.addr);
  dm->GetValue(startIndex + i++, resObj.title);
  dm->GetValue(startIndex + i++, resObj.desc);
  dm->GetValue(startIndex + i++, resObj.corpName);
  dm->GetValue(startIndex + i++, resObj.deptName);
  dm->GetValue(startIndex + i++, resObj.website);
  dm->GetValue(startIndex + i++, resObj.terminalType);
  dm->GetValue(startIndex + i++, resObj.qPinyin);
  dm->GetValue(startIndex + i++, resObj.officePhone2);
  dm->GetValue(startIndex + i++, resObj.officePhone3);
  dm->GetValue(startIndex + i++, resObj.officePhone4);
  dm->GetValue(startIndex + i++, resObj.officePhone5);
  dm->GetValue(startIndex + i++, resObj.officePhone6);
  dm->GetValue(startIndex + i++, resObj.homePhone);
  dm->GetValue(startIndex + i++, resObj.dummy);

  return i;
}

//static 
int ContactQuery::QueryAll(DQLBase<ContactInfo>::ResCtnType & resCtn)
{
  ContactInfo argObj;

  ContactQuery qry;
  qry.BatchExecute(ALL, argObj, resCtn);

  //DEBUG_LOG(qry.count);
  return qry.count;
}

//static 
bool ContactQuery::QueryById(const std::string & id, 
                             DQLBase<ContactInfo>::ResObjType & resObj)
{
  ContactInfo argObj;
  argObj.cid = id;

  ContactQuery qry;
  bool ret = qry.SingleExecute(CID, argObj, resObj);

  //DEBUG_LOG(id, qry.count);
  return ret;
}

//static 
bool ContactQuery::QueryByAccount(const std::string & account, 
  DQLBase<ContactInfo>::ResObjType & resObj)
{
  ContactInfo argObj;
  argObj.account = account;

  ContactQuery qry;
  bool ret = qry.SingleExecute(ACCOUNT, argObj, resObj);

  //DEBUG_LOG(account, qry.count);
  return ret;
}

//static 
bool ContactQuery::QueryByUri(const std::string & uri, 
  DQLBase<ContactInfo>::ResObjType & resObj)
{
  ContactInfo argObj;
  argObj.uri = uri;

  ContactQuery qry;
  bool ret = qry.SingleExecute(URI, argObj, resObj);

  //DEBUG_LOG(uri, qry.count);
  return ret;
}

//static 
bool ContactQuery::QueryByPhoneNumber(const std::string & phoneNumber, 
  DQLBase<ContactInfo>::ResObjType & resObj)
{
  ContactInfo argObj;
  argObj.mobilePhone = phoneNumber;

  ContactQuery qry;
  bool ret = qry.SingleExecute(PHONENUM, argObj, resObj);

  //DEBUG_LOG(phoneNumber, qry.count);
  return ret;
}

//static 
bool ContactQuery::QueryByFullUri(const std::string & fullUri, 
                                      DQLBase<ContactInfo>::ResObjType & resObj)
{
    ContactInfo argObj;
    argObj.fullUri = fullUri;

    ContactQuery qry;
    bool ret = qry.SingleExecute(FULLURI, argObj, resObj);

    //DEBUG_LOG(fullUri, qry.count);
    return ret;
}

//static 
bool ContactQuery::QueryExistenceByUri(const std::string & uri)
{
  ContactInfo argObj;
  argObj.uri = uri;

  std::vector<ContactInfo> resObjs;

  ContactQuery qry;
  qry.BatchExecute(URI, argObj, resObjs);

  //DEBUG_LOG(uri, qry.count);
  return qry.count > 0;
}

//static
bool ContactQuery::QueryByEmail(const std::string & email, 
								DQLBase<ContactInfo>::ResCtnType & resCtn)
{
	ContactInfo argObj;
	argObj.email = email;

	ContactQuery qry;
	qry.BatchExecute(EMAIL, argObj, resCtn);

	//DEBUG_LOG(EMAIL, qry.count);
	return qry.count > 0;
}

  } // namespace ecsdata
} // namespace ecs
