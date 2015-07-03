#pragma once

#include "data/storage/DataStorage.h"

#define TRY_EXCEPTIONS \
  try {

#define CATCH_EXCEPTIONS \
  } catch (ecs::ecsdata::SQLiteException &) {} \
    catch (const std::exception & e) { LogStdException(e); } \
    catch (...) { LogUnknownException(); }

namespace ecs {
  namespace ecsdata {

void LogStdException(const std::exception & e);
void LogUnknownException();

inline 
void DDLBase::Execute()
{
  std::string sql;

  ComposeSQL(sql);

  if (sql.empty()) 
    return;

  TRY_EXCEPTIONS

  //assert(ds_ != NULL);
  if (ds_)      
    ds_->Exec(sql);

  CATCH_EXCEPTIONS
}

template<class ArgObjT, class ArgCtnT>
void DMLBase<ArgObjT, ArgCtnT>::Execute(const ArgCtnType & argCtn)
{
  changed = 0;

  std::string sql;
  if (argCtn.size() > 0)
    ComposeSQL(argCtn[0], sql);
  else
    ComposeSQL(sql);
  if (sql.empty()) return;

  if (NULL == DataModelBase::ds_)
  {
    return;
  }

  TRY_EXCEPTIONS

  std::auto_ptr<IDataManipulation> dm(
    DataModelBase::ds_->CreateDataManipulation(sql));
    
  if(!dm.get())
  {
    return;
  }
  
  Transanction t(DataModelBase::ds_, argCtn.size() > 1);

  for (typename ArgCtnType::const_iterator i = argCtn.begin(); 
    i != argCtn.end(); ++i)
  {
    Bind(dm.get(), *i);

    changed += dm->Exec();
    OnExecuted(*i);
  }

  t.Commit();

  CATCH_EXCEPTIONS
}

template<class ArgObjT>
void DMLInsertBase<ArgObjT>::Execute(const ArgObjType & argObj)
{
  DMLBase<ArgObjT, std::vector<ArgObjT> >::changed = 0;

  std::string sql;
  this->ComposeSQL(sql);
  if (sql.empty()) return;

  if (NULL == DataModelBase::ds_)
  {
	return;
  }

  TRY_EXCEPTIONS

  std::auto_ptr<IDataManipulation> dm(
    DataModelBase::ds_->CreateDataManipulation(sql));

  if(!dm.get())
  {
    return;
  }

  this->Bind(dm.get(), argObj);

  if (dm->Exec() == 1)
  {
    ++DMLBase<ArgObjT, std::vector<ArgObjT> >::changed;
    rowid = DataModelBase::ds_->GetLastInsertRowId();
  }

  CATCH_EXCEPTIONS
}

template<class ArgObjT, class ResObjT, class ArgCtnT, class ResCtnT>
void DQLBase<ArgObjT, ResObjT, ArgCtnT, ResCtnT>::Execute(
  const ArgObjType & argObj, ResCtnType & resCtn)
{
  count = 0;

  std::string sql;
  ComposeSQL(argObj, sql);
  if (sql.empty()) return;

  if (NULL == DataModelBase::ds_)
  {
	return;
  }

  TRY_EXCEPTIONS

  std::auto_ptr<IDataManipulation> dm(
    DataModelBase::ds_->CreateDataManipulation(sql));

  if(!dm.get())
  {
    return;
  }
  Bind(dm.get(), argObj);

  ResObjType resObj;
  while (dm->NextRow())
  {
    Extract(dm.get(), resObj);

    ++count;
    resCtn.push_back(resObj);
  }

  CATCH_EXCEPTIONS
}

  } // namespace ecsdata
} // namespace ecs
