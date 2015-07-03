#include "stdafx.h"
#include "data/model/user/config/TransferNumber.h"

#include "Log.h"

using namespace std;

namespace ecs {
  namespace ecsdata {

///////////////////////////////////////////////////////////////////////////
void CreateTransferNumTabCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "CREATE TABLE IF NOT EXISTS "TRANSFERNUMBER_TAB
    "( TRANSFERNUMBER VARCHAR(32) NOT NULL PRIMARY KEY"
    ");";
}

///////////////////////////////////////////////////////////////////////////
void AddTransferNumCommand::ComposeSQL(std::string & sql)
{
  sql = 
    "INSERT OR REPLACE INTO "TRANSFERNUMBER_TAB
    "( TRANSFERNUMBER"
    ") VALUES( ? );";
}

void AddTransferNumCommand::Bind(IDataManipulation * dm, 
  const DMLBase<std::string>::ArgObjType & argObj)
{
  int i = 0;

  //INFO_PARAM1(argObj);
  dm->Bind(++i, argObj);
}

///////////////////////////////////////////////////////////////////////////
void RemoveTransferNumCommand::ComposeSQL(std::string & sql)
{
  const std::string DELETE_TRANSFERNUMBER_TAB = "DELETE FROM "TRANSFERNUMBER_TAB;

  std::string whereClause = " WHERE ";
  switch (type_)
  {
  case ALL:
    whereClause.clear();
    break;
  case TRANSFERNUMBER:
    (void)whereClause.append("TRANSFERNUMBER = ?");
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    sql = "";
    return;
  }

  sql = DELETE_TRANSFERNUMBER_TAB + whereClause + ";";
}

void RemoveTransferNumCommand::Bind(IDataManipulation * dm, 
                                    const ArgObjType & argObj)
{
  int i = 0;
  switch (type_)
  {
  case ALL:
    break;
  case TRANSFERNUMBER:
    //INFO_PARAM1(argObj);
    dm->Bind(++i, argObj);
    break;
  default:
    WARN_LOG("unknown type : %d" ,type_);
    break;
  }
}

//static 
int RemoveTransferNumCommand::RemoveAll()
{
  //TRACE_FUNC();

  std::string argObj;

  RemoveTransferNumCommand cmd;
  cmd.SingleExecute(ALL, argObj);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed;
}

//static 
bool RemoveTransferNumCommand::RemoveByNumber(const std::string & number)
{
  //TRACE_FUNC1(number);

  RemoveTransferNumCommand cmd;
  cmd.SingleExecute(TRANSFERNUMBER, number);

  //INFO_PARAM1(cmd.changed);
  return cmd.changed == 1;
}

///////////////////////////////////////////////////////////////////////////
void TransferNumQuery::ComposeSQL(std::string & sql)
{
  sql = "SELECT * FROM "TRANSFERNUMBER_TAB";";
}

void TransferNumQuery::Bind(IDataManipulation * /*dm*/, const ArgObjType & /*argObj*/)
{
}

//static 
int TransferNumQuery::ExtractFromTransferNumTab(IDataManipulation * dm, 
  ResObjType & resObj, int startIndex)
{
  int i = 0;

  dm->GetValue(startIndex + i++, resObj);

  return i;
}

//static 
int TransferNumQuery::QueryAll(ResCtnType & resCtn)
{
  std::string argObj;

  TransferNumQuery qry;
  qry.BatchExecute(ALL, argObj, resCtn);

  DEBUG_LOG("qry.count=%d",qry.count);
  return qry.count;
}

  }
}
