#pragma once
#include "data\model\DataModelBase.h"
#include "data\DataType.h"
#define CONTACTRING_TAB "ContactRingTab"

namespace ecs {
  namespace ecsdata {

class   CreateContactRingTabCommand : public DDLBase
{
public:
  CreateContactRingTabCommand() : DDLBase(USERDB_NAME) {}

protected:
  virtual void ComposeSQL(std::string & sql);

}; // class CreateContactRingTabCommand

  } // namespace ecsdata
} // namespace ecs
