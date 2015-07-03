#include "stdafx.h"
#include "data/model/user/config/RingSettings.h"
using namespace std;

namespace ecs {
  namespace ecsdata {

///////////////////////////////////////////////////////////////////////////
void CreateContactRingTabCommand::ComposeSQL(std::string & sql)
{
  const std::string CREATE_CONTACTRINGTAB = 
    "CREATE TABLE IF NOT EXISTS "CONTACTRING_TAB
    "( ID    VARCHAR(64) NOT NULL PRIMARY KEY"
    ", PATH  VARCHAR(128)"
    ");";

  sql = CREATE_CONTACTRINGTAB;
}
  } // namespace ecsdata
} // namespace ecs
