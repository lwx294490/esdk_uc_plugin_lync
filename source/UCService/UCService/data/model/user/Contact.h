#pragma once

#ifdef _lint
#define CONTACT_TAB
#else
#define CONTACT_TAB "ContactTab"
#endif


namespace ecs {
  namespace ecsdata {

class CreateContactTabCommand : public DDLBase
{
public:
  CreateContactTabCommand() : DDLBase(USERDB_NAME_CACHED) {}

protected:
  virtual void ComposeSQL(std::string & sql);

};

class AddContactCommand 
  : public DMLBase<ContactInfo>
{
public:
  AddContactCommand() : DMLBase<ContactInfo>(USERDB_NAME_CACHED) {}

  DEFINE_BATCH_SINGLE_ADD_MOTHOD(AddContactCommand)

public:
  static int maxContactID;

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<ContactInfo>::ArgObjType & argObj);
  virtual void OnExecuted(
    const DMLBase<ContactInfo>::ArgObjType & argObj);

};

class   RemoveContactCommand 
  : public DMLBase<ContactInfo>
{
public:
  RemoveContactCommand() : DMLBase<ContactInfo>(USERDB_NAME_CACHED) {}

public:
  static bool RemoveByContactId(const std::string & cid);
  static int  RemoveAll();
protected:
  enum
  {
    INVALID, 
    ALL, 
    URI,
    CID
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DMLBase<ContactInfo>::ArgObjType & argObj);

};

class   ContactQuery 
  : public DQLBase<ContactInfo>
{
  friend class BuddyQuery;
  friend class BuddyCustomTagQuery;

public:
  ContactQuery() : DQLBase<ContactInfo>(USERDB_NAME_MEM) {}

public:
  static int QueryAll(
    DQLBase<ContactInfo>::ResCtnType & resCtn);
  static bool QueryById(const std::string & id, 
    DQLBase<ContactInfo>::ResObjType & resObj);
  static bool QueryByAccount(const std::string & account, 
    DQLBase<ContactInfo>::ResObjType & resObj);
  static bool QueryByUri(const std::string & uri, 
    DQLBase<ContactInfo>::ResObjType & resObj);
  static bool QueryByPhoneNumber(const std::string & phoneNumber, 
    DQLBase<ContactInfo>::ResObjType & resObj);
  static bool QueryByFullUri(const std::string & fullUri, 
      DQLBase<ContactInfo>::ResObjType & resObj);
  static bool QueryExistenceByUri(const std::string & uri);
  static bool QueryByEmail(const std::string & email,
	  DQLBase<ContactInfo>::ResCtnType & resCtn);

protected:
  enum
  {
    INVALID, 
    ALL, 
    CID, 
    URI, 
    CID_URI, 
    ACCOUNT, 
    PHONENUM, 
    FULLURI,
	EMAIL
  };

protected:
  virtual void ComposeSQL(std::string & sql);
  virtual void Bind(IDataManipulation * dm, 
    const DQLBase<ContactInfo>::ArgObjType & argObj);
  virtual void Extract(IDataManipulation * dm, 
    DQLBase<ContactInfo>::ResObjType & resObj)
  {
    (void)ExtractFromContactTab(dm, resObj, 0);
  }

  static int ExtractFromContactTab(IDataManipulation * dm, 
    DQLBase<ContactInfo>::ResObjType & resObj, int startIndex);

};

  } // namespace ecsdata
} // namespace ecs
