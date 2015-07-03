#pragma once

// includes & warning suppress
#pragma warning(push)
#include "sqlite3.h"
#pragma warning(pop)

// auto-link
#ifdef _DEBUG
# define SQLITE_LIB_NAME "sqlited.lib"
#else
# define SQLITE_LIB_NAME "sqlite.lib"
#endif

#pragma message("sqlite : Auto Linking to "SQLITE_LIB_NAME)
#pragma comment(lib, SQLITE_LIB_NAME)
