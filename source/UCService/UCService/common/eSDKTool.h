#ifndef _ESDKTOOL_H
#define _ESDKTOOL_H

#include <string>
#include <vector>
#include <list>
#include <iosfwd>

#ifdef WIN32
#include <tchar.h>
#include <time.h>
#include <atltime.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Iphlpapi.h>
#endif

#include "UCHistoryMgr.h"

using namespace std;
//#include "Log.h"

#define USER_AGENT				"Huawei SoftCoPCA"

#define SAFE_DELETE(pPoint) 	if(NULL != pPoint)\
{\
	delete pPoint;\
	pPoint = NULL;\
}

#define SAFE_DELETE_ARRAY(pPoint) 	if(NULL != pPoint)\
{\
	delete[] pPoint;\
	pPoint = NULL;\
}

#define CHECK_POINTER(pPoint) if(NULL == pPoint)\
{\
	return;\
}

#define CHECK_POINTER_RETURN(pPoint,ret) if(NULL == pPoint)\
{\
	return ret;\
}

namespace esdkTools
{
	//字符串转化为数，第二个参数指定进制（默认十进制）
	//使用时指定模板参数类型；转换失败抛出runtime_error异常
	template<class T> inline T str2num(
		const std::string & str, std::ios_base &(*f)(std::ios_base&) = std::dec) 
	{ 
		T num;

		std::istringstream iss(str);
		if ((iss >> f >> num).fail()) 
			throw std::runtime_error("invalid conversion : str = " + str);

		return num;
	}

	//数字转化为字符串，第二个参数指定进制（默认十进制）
	//使用时可以不指定模板参数类型；转换失败抛出runtime_error异常
	template<class T> inline std::string num2str(
		const T & num, std::ios_base &(*f)(std::ios_base&) = std::dec)
	{
		std::ostringstream oss;
		if ((oss << f << num).fail())
			throw std::runtime_error("invalid conversion : num = " + num);

		return oss.str();
	}
}

//工具类
class eSDKTool
{
private:
	eSDKTool(void);
	~eSDKTool(void);
public:
	static void GetStartTime(historydata::Date& startdate,historydata::Time& starttime,unsigned int duration);
	static void getCurrentPath(std::string& cstrPath);//获取当前程序可执行路径	
	static bool IsValidUri(const std::string& uri);//判断是否是有效uri
	static bool IsVirtualUri(const std::string& uri);//判断是否是模拟的uri，没有绑定任何号码	
	static std::string GetNoFromUri(const std::string & uri);//从uri中提取号码
	static std::string MergeString(const std::vector<std::string>& strList);// 以','为间隔合并字符串列表
	static void SplitString(const std::string& inputstr,std::vector<std::string>& stroutputList);//按照逗号分解字符串
	static void GetIPPort(const std::string& serverURL,std::string& ip,int& port);//输入“10.10.10.10:10”，解析出“10.10.10.10”和10
	static std::string CreateGuidStr();

	static std::wstring utf82unicode(const std::string& utf_str);
	static std::wstring ansiToUnicode(const std::string _ansic);
	static std::string unicode2utf8(const std::wstring & uni_str);
	static std::string utf8str2unicodestr(const std::string& utf_str);
	static std::string unicodestr2utf8(const std::string& utf_str);  //////界面上传下来的unicode字符//////

	static void GetNumStringFromCmd(const std::string& _spker, std::string& _spkeNum0, std::string& _spkeNum1);
	static bool CheckString(const std::string strNum1,const std::string& strNum2,std::string& strNum3);//查看strNum2的前面的几个字符串是不是strNum1，是则返回true

	static void UTCTime2LocalTime(const std::string& _utcdate, const std::string& _utctime, std::string& localdate_, std::string& localtime_);
	static int MakeDir(const std::string &path);
	static bool RenameFile(const std::string &filepath, const std::string &newfilepath);
	static void GetFilesInDir(const std::string& _dirPath,std::list<std::string>& _lstFiles);

	static bool Access(const std::string & path, int mode);
	static bool Access(const std::wstring & path, int mode);
	static bool Exists(const std::string & path)
	{ return Access(path, 0); }
	static bool Exists(const std::wstring & path)
	{ return Access(path, 0); }
	static std::string GetProgramDir();
	static std::wstring GetProgramDirW();

	static bool DeleteFile(const std::string & filepath);

	static std::string num2str(int);
	static int str2num(const std::string& str);

	static TUP_INT64 GetCurUTCTime();

	static bool GetBestHostip(std::string& ip, const std::string& serverip);
	static bool IsTextUtf8(const char* str,ULONGLONG length);

private:
	static std::wstring s_modulePathW;
	static std::string s_modulePath;
};

#endif


