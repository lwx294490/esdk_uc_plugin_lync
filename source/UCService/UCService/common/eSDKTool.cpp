#include "StdAfx.h"
#include "objbase.h"
#include "eSDKTool.h"
#include <io.h>
#include "Log.h"
#include "UCConfigMgr.h"


eSDKTool::eSDKTool(void)
{
}

eSDKTool::~eSDKTool(void)
{
}

void eSDKTool::getCurrentPath(std::string& strPath)
{
	HMODULE hModule = GetModuleHandle(L"UCService.dll");
	char path[MAX_PATH+1] = {0};
	::GetModuleFileNameA(hModule, path, MAX_PATH);
	std::string strModulePath = path;
	unsigned int loc = strModulePath.find_last_of("\\");
	if( loc != string::npos )
	{
		strPath = strModulePath.substr(0,loc);
	}
}

void eSDKTool::GetStartTime(historydata::Date& startdate,historydata::Time& starttime,unsigned int duration)
{
	_tzset();
	CTime times =  CTime::GetCurrentTime();
	times -= (long long)duration;
	startdate.year = times.GetYear();
	startdate.month = times.GetMonth();
	startdate.day = times.GetDay();
	starttime.hour = times.GetHour();
	starttime.minute = times.GetMinute();
	starttime.second = times.GetSecond();
}
bool eSDKTool::IsValidUri(const std::string& uri)
{
	size_t nSip = uri.find("sip:");
	if (nSip != 0) //必须以sip:开头
	{
		return false;
	}
	return true;
}
bool eSDKTool::IsVirtualUri(const std::string& uri)
{
	//模拟的没有绑定任何号码的用户uri
	if (0 == uri.find("sip:index"))
	{
		return true;
	}
	return false;
}
std::string eSDKTool::GetNoFromUri(const std::string & uri)
{
	size_t nSip = uri.find("sip:");

	if (nSip != 0) //必须以sip:开头
	{
		return "";
	}

	if (IsVirtualUri(uri))
	{
		return "";
	}

	size_t nAt = uri.find('@');
	if (std::string::npos == nAt) //必须含有@字符
	{
		return "";
	}
	//取sip:与@之间的字符串，注意要除去长度为4的"sip:"
	std::string strNum = uri.substr(/*nSip +*/ 4, (nAt /*- nSip*/) - 4); //程序执行到此行时，nSip==0

	if (strNum.find('+') != std::string::npos)
	{
		strNum = strNum.substr(1);
	}

	return strNum;
}

std::string eSDKTool::MergeString(const std::vector<std::string>& strList)
{
	unsigned int iSize = strList.size();
	std::string outStr("");
	if(iSize == 0)
	{
		return outStr;
	}
	if(iSize == 1)
	{
		outStr.append(strList.at(0));
		return outStr;
	}
	for(unsigned int i=0;i<(iSize-1);++i)
	{
		outStr.append(strList.at(i));
		outStr.append(",");
	}
	outStr.append(strList.at(iSize-1));
	return outStr;
}
void eSDKTool::SplitString(const std::string& inputstr,std::vector<std::string>& stroutputList)
{
	stroutputList.clear();

	std::string instr = inputstr;
	int pos = -1;
	do{
		pos = (int)instr.find(',');
		stroutputList.push_back(instr.substr(0,(unsigned int)pos));
		instr = instr.substr((unsigned int)(pos+1));
	}while(-1 != pos && instr!="");
	return;
}
void eSDKTool::GetIPPort(const std::string& serverURL,std::string& ip,int& port)
{
	ip.clear();
	std::string instr = serverURL;
	string::size_type pos = instr.find(':');
	if( pos != string::npos )
	{
		ip = instr.substr(0,pos);
		std::string outPort = instr.substr(pos+1);
		port =  atoi(outPort.c_str());
	}
	else
	{
		ip = "";
		port = 0;
	}


	return;
}
std::string eSDKTool::CreateGuidStr()
{
	GUID guid;
	(void)::CoCreateGuid(&guid);

	char buf[64];
	(void)::sprintf_s(buf, 
		"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", 
		(unsigned int)guid.Data1, guid.Data2, guid.Data3, 
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], 
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	return buf;
}
//UTF8转化为unicode
std::wstring eSDKTool::utf82unicode(const std::string& str)
{
	int nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *pUnicode =  new  wchar_t[nLen+1];  
	memset(pUnicode,0,(nLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_UTF8,0,str.c_str(),-1,(LPWSTR)pUnicode,nLen );  
	std::wstring  rt;  
	rt = ( wchar_t* )pUnicode;
	std::wstring cstr = rt.c_str();
	delete  pUnicode; 
	return cstr;
}

std::string eSDKTool::utf8str2unicodestr(const std::string& utf_str)
{
	std::wstring strOut = utf82unicode(utf_str);

	int len= WideCharToMultiByte(CP_ACP,0,strOut.c_str(),(int)wcslen(strOut.c_str()),NULL,0,NULL,NULL); 
	char* pChar=new char[(unsigned int)len+1]; 
	WideCharToMultiByte(CP_ACP,0,strOut.c_str(),(int)wcslen(strOut.c_str()),pChar,len,NULL,NULL); 
	pChar[len]='\0';

	std::string str(pChar);
	delete[] pChar;
	return  str;
}
std::wstring eSDKTool::ansiToUnicode(const std::string _ansic)
{
	int len = ::MultiByteToWideChar(CP_ACP, 0, _ansic.c_str(), -1, NULL, 0);  
	wchar_t *pUnicode = new wchar_t[len + 1]; 
	memset(pUnicode,0,(len +1)*sizeof(wchar_t));  
    ::MultiByteToWideChar(CP_ACP, 0, _ansic.c_str(), -1, (LPWSTR)pUnicode, len);  
	std::wstring  rt;  
	rt = ( wchar_t* )pUnicode;
	std::wstring cstr = rt.c_str();
	delete  pUnicode; 
	return cstr; 

}
std::string eSDKTool::unicodestr2utf8(const std::string& utf_str)
{
	std::wstring  strOut = ansiToUnicode(utf_str);
	std::string  m_desc = unicode2utf8(strOut);
	return m_desc;
}

std::string eSDKTool::unicode2utf8(const std::wstring & wstr)
{
	char* pElementText;
	int   iTextLen = WideCharToMultiByte(CP_UTF8,0,wstr.c_str(),-1,NULL,0,NULL,NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char)*(iTextLen+1));
	::WideCharToMultiByte(CP_UTF8,0,wstr.c_str(),-1,pElementText,iTextLen,NULL,NULL);
	std::string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

void eSDKTool::GetNumStringFromCmd(const std::string& _spker, std::string& _spkeNum0, std::string& _spkeNum1)
{
	std::string spker = _spker;
	std::string::size_type pos = spker.find("#");
	if ( pos != std::string::npos )
	{
		_spkeNum0 = spker.substr(0,pos);
		spker = spker.substr(pos+1);
		pos = spker.find("#");
		if ( pos != std::string::npos )
		{
			_spkeNum1 = spker.substr(0,pos);       
		}
	}
	else if ( !spker.empty() )
	{
		_spkeNum0 = spker;
	}
	else
	{
	}
}

bool eSDKTool::CheckString(const std::string strNum1,const std::string& strNum2,std::string& strNum3)
{
	if(strNum1.empty() || strNum2.empty())
	{
		return false;
	}

	std::string substr = strNum2.substr(0,strNum1.length());
	if(substr != strNum1)
	{
		return false;
	}
	else
	{
		strNum3 = strNum2.substr(strNum1.length());
		return true;
	}
}
void eSDKTool::UTCTime2LocalTime(const std::string& _utcdate, const std::string& _utctime, std::string& localdate_, std::string& localtime_)
{
	int year;
	int month;
	int day;
	(void)::sscanf_s(_utcdate.c_str(), "%d-%d-%d", &year, &month, &day);

	int hour;
	int minute;
	int second;
	(void)::sscanf_s(_utctime.c_str(), "%d:%d:%d", &hour, &minute, &second);

	SYSTEMTIME sysTimeUTC;
	memset(&sysTimeUTC, 0, sizeof(SYSTEMTIME));  
	sysTimeUTC.wYear = (WORD)year;
	sysTimeUTC.wMonth = (WORD)month;
	sysTimeUTC.wDay = (WORD)day;
	sysTimeUTC.wHour = (WORD)hour;
	sysTimeUTC.wMinute = (WORD)minute;
	sysTimeUTC.wSecond = (WORD)second;

	SYSTEMTIME sysTimeLocal;
	memset(&sysTimeLocal, 0, sizeof(SYSTEMTIME));

	TIME_ZONE_INFORMATION *lpTimeZone = new TIME_ZONE_INFORMATION;
	(void)GetTimeZoneInformation(lpTimeZone);

	(void)SystemTimeToTzSpecificLocalTime(lpTimeZone,&sysTimeUTC,&sysTimeLocal);//UTC转本地时间

	delete lpTimeZone;

	char strlocaldate_[16];
	(void)::sprintf_s(strlocaldate_, 16, "%04d-%02d-%02d", sysTimeLocal.wYear, sysTimeLocal.wMonth, sysTimeLocal.wDay);
	localdate_ = strlocaldate_;

	char strlocaltime_[16];
	(void)::sprintf_s(strlocaltime_, 16, "%02d:%02d:%02d", sysTimeLocal.wHour, sysTimeLocal.wMinute, sysTimeLocal.wSecond);
	localtime_ = strlocaltime_;

}

int eSDKTool::MakeDir(const std::string &path)
{
	std::wstring wpath = utf82unicode(path);

	return ::_wmkdir(wpath.c_str());
}

bool eSDKTool::RenameFile(const std::string &filepath, const std::string &newfilepath)
{
	return TRUE == ::MoveFileW(
		utf82unicode(filepath).c_str(), utf82unicode(newfilepath).c_str());
}

void eSDKTool::GetFilesInDir(const std::string& _dirPath,std::list<std::string>& _lstFiles)
{
	_finddata_t fileData;
	std::string searchKey = _dirPath + "*";
	intptr_t hFindFile = ::_findfirst(searchKey.c_str(),&fileData);
	if(hFindFile != -1)
	{
		std::string fileName = fileData.name ;
		if(fileName != "." && fileName != "..")
		{
			_lstFiles.push_back(fileName);
		}
		while(::_findnext(hFindFile,&fileData) == 0)
		{
			fileName = fileData.name ;
			if(fileName != "." && fileName != "..")
			{
				_lstFiles.push_back(fileName);
			}
		}
		(void)::_findclose(hFindFile);
	}
}

bool eSDKTool::Access(const std::string &path, int mode)
{
	std::wstring wpath = utf82unicode(path);
	return Access(wpath, mode);

}
bool eSDKTool::Access(const std::wstring &path, int mode)
{

	return (0 == _waccess(path.c_str(), mode));

}

//static 
std::wstring eSDKTool::s_modulePathW;

//static
std::string eSDKTool::s_modulePath;

std::string eSDKTool::GetProgramDir()
{
	(void)GetProgramDirW();

	return s_modulePath;
}

//static
std::wstring eSDKTool::GetProgramDirW()
{

	if (s_modulePathW.empty())
	{
		HMODULE hModule = GetModuleHandle(L"UCService.dll");
		WCHAR szPath[_MAX_PATH + 1] = {0};
		(void)::GetModuleFileNameW(hModule, szPath, _MAX_PATH);

		s_modulePathW = szPath;
		size_t rightmostBackslash = s_modulePathW.rfind(L'\\');
		s_modulePathW = s_modulePathW.substr(0, rightmostBackslash + 1);

		s_modulePath = unicode2utf8(s_modulePathW);
	}

	return s_modulePathW;
}

//static
bool eSDKTool::DeleteFile(const std::string &filepath)
{

	return TRUE == ::DeleteFileW(utf82unicode(filepath).c_str());

}

std::string eSDKTool::num2str(int i)
{
	char str[STRING_LENGTH]= {0};
	sprintf_s(str,STRING_LENGTH-1,"%d",i);
	return std::string(str);
}

int eSDKTool::str2num(const std::string& str)
{	
	return atoi(str.c_str());
}

TUP_INT64 eSDKTool::GetCurUTCTime()
{
	CTime cur = CTime::GetCurrentTime();
	return cur.GetTime()*1000;
}

bool eSDKTool::GetBestHostip(std::string& ip, const std::string& serverip)
{
	INFO_LOG("Enter GetBestHostip");
	DWORD destAddr = inet_addr(serverip.c_str());

	MIB_IPFORWARDROW bestRoute;
	memset(&bestRoute, 0, sizeof(bestRoute));
	if (NO_ERROR != GetBestRoute((DWORD)destAddr, 0, &bestRoute))
	{
		ERROR_LOG("GetBestRoute Failed");
		return false;
	}

	MIB_IPADDRTABLE buf;
	PMIB_IPADDRTABLE pIPAddrTable = (MIB_IPADDRTABLE*)&buf;
	if ( !pIPAddrTable )
	{
		ERROR_LOG("pIPAddrTable is NULL");
		return false;
	}

	// Make an initial call to GetIpAddrTable to get the
	// necessary size into the dwSize variable
	DWORD dwSize = 0;
	if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER)
	{
		if ( !pIPAddrTable )
		{
			ERROR_LOG("GetIpAddrTable Get pIPAddrTable  Failed");
			return false;
		}
	}

	char* strTable = new char[dwSize];
	pIPAddrTable = (MIB_IPADDRTABLE*)strTable;

	// Make a second call to GetIpAddrTable to get the
	// actual data we want
	DWORD dwRetVal;
	if ( (dwRetVal = GetIpAddrTable( pIPAddrTable, &dwSize, 0 )) != NO_ERROR ) 
	{ 
		ERROR_LOG("GetIpAddrTable Get dwRetVal  Failed");
		return false;
	}

	bool ret = false;
	for (DWORD i=0; i<pIPAddrTable->dwNumEntries; ++i)
	{
		INFO_LOG("dwNumEntries is %d",pIPAddrTable->dwNumEntries);
		const MIB_IPADDRROW& entry = pIPAddrTable->table[i];
		char * ipaddr1 = NULL;
		const unsigned IPLENGTH = 20;//ip 字符串长度
		char addr1[IPLENGTH]={0};
		in_addr inaddr1;
		inaddr1.s_addr=entry.dwAddr;
		ipaddr1 = inet_ntoa(inaddr1);
		strcpy_s(addr1,IPLENGTH,ipaddr1); 
		INFO_LOG("entry.dwAddr is %s",addr1);
		INFO_LOG("entry.dwAddr is %d",entry.dwAddr);
		INFO_LOG("entry.dwIndex is %d",entry.dwIndex);
		INFO_LOG("entry.dwMask is %lu",entry.dwMask);
		INFO_LOG("entry.dwBCastAddr is %d",entry.dwBCastAddr);
		INFO_LOG("entry.dwReasmSize is %d",entry.dwReasmSize);
		INFO_LOG("entry.unused1 is %d",entry.unused1);
		INFO_LOG("entry.wType is %d",entry.wType);
		INFO_LOG("bestRoute.dwForwardIfIndex is %d",bestRoute.dwForwardIfIndex);
		if (entry.dwIndex == bestRoute.dwForwardIfIndex)
		{
			INFO_LOG("entry.dwIndex == bestRoute.dwForwardIfIndex");
			bool found = false;
			INFO_LOG("bestRoute.dwForwardNextHo is %d",bestRoute.dwForwardNextHop);
			if (entry.dwMask <= 0 || entry.dwMask  >= (unsigned long)255*255*255*255)
			{
				//////子网掩码不存在默认此种情况下是拨号方式//////
				found = true;
			} 
			else
			{
				if (0 == bestRoute.dwForwardNextHop)
					found = (entry.dwAddr&bestRoute.dwForwardMask) == (bestRoute.dwForwardDest&bestRoute.dwForwardMask);
				else
					found = (entry.dwAddr&entry.dwMask) == (bestRoute.dwForwardNextHop&entry.dwMask);
			}
			if (found)
			{
				INFO_LOG("found is true");
				char * ipaddr = NULL;
				const unsigned IPLENGTH = 20;//ip 字符串长度
				char addr[IPLENGTH]={0};
				in_addr inaddr;
				inaddr.s_addr=entry.dwAddr;
				ipaddr = inet_ntoa(inaddr);
				strcpy_s(addr,IPLENGTH,ipaddr);  
				if (strcmp(addr,"0.0.0.0") !=0  && strcmp(addr,"127.0.0.1") !=0)
				{
					INFO_LOG("(strcmp !=0  && strcmp !=0)");
					ip = addr;
					ret = true;
				}
			}
		}
	}

	delete[] strTable;
	INFO_LOG("Leave GetBestHostip");
	return ret;
}

bool eSDKTool::IsTextUtf8(const char* str,ULONGLONG length)  
{  
   DWORD nBytes=0;//UFT8可用1-6个字节编码,ASCII用一个字节   
   UCHAR chr;  
   BOOL bAllAscii=TRUE; //如果全部都是ASCII, 说明不是UTF-8   
   for(int i=0; i<length; ++i)  
	    {
		    chr= *(str+i);  
		    if( (chr&0x80) != 0 ) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx   
			 bAllAscii= FALSE;
			if(nBytes==0) //如果不是ASCII码,应该是多字节符,计算字节数   
			  {  
			     if(chr>=0x80)  
				 {  
	                if(chr>=0xFC&&chr<=0xFD)  
		                    nBytes=6;  
	                else if(chr>=0xF8)  
		                    nBytes=5;  
	                else if(chr>=0xF0)  
		                    nBytes=4;  
	                else if(chr>=0xE0)  
		                    nBytes=3;  
	                else if(chr>=0xC0)  
		                    nBytes=2;  
	                else  
		                  return FALSE;  
		                nBytes--;  
					 }  
				}  
			else //多字节符的非首字节,应为 10xxxxxx   
				 {  
		            if( (chr&0xC0) != 0x80 )  
			              return FALSE;  
			            nBytes--;  
			     }  
			 }  
	    if( nBytes > 0 ) //违返规则   
		      return FALSE;  
	    if( bAllAscii ) //如果全部都是ASCII, 说明不是UTF-8   
		      return FALSE;  
		return TRUE;  
}

