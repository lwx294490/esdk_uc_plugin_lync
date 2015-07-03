// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//
#ifndef _STDAFX_HEAD_
#define _STDAFX_HEAD_

#include "targetver.h"

//增加UC API头文件定义--start
#include "tup_def.h"
#include "tup_im_baseapi.h"
#include "tup_im_extendapi.h"
#include "call_interface.h"
#include "call_advanced_interface.h"
//增加UC API头文件定义--end

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>

//#include "vld.h"

// TODO: 在此处引用程序需要的其他头文件
#include "UCSDK.h"
#include "eSDKTool.h"
#include "NotifyCallBack.h"
#include "UnhandledExceptionFilter.h"

#include "sqlite.h"
#include "data/ECSDataException.h"
#include "data/DataType.h"
#include "data/model/history/HistoryDataType.h"
#include "data/model/DataModelBase.h"
#include "data/model/DataModelBase.inl"

#endif



