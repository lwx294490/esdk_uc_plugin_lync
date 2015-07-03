#pragma once



#include <map>

#define USERDB_NAME "userdb"


#ifdef _DEBUG
//#define USERDB_NAME_CACHED "userdb_mem"
#define USERDB_NAME_CACHED "userdb"
#else
#define USERDB_NAME_CACHED "userdb"
#endif

#define USERDB_NAME_MEM "userdb"

#define SYSDB_NAME "sysdb"


//lint -e1790

namespace ecs {
  namespace ecsdata {

///////////////////////////////////////////////////////////////////////////
// non-storage data types
    
struct   UserProfile
{
  std::string profilepath_;        //!< 用户数据存储位置
  std::string headimagepath_;      //!< 头像数据缓存路径
  std::string imagefilepath_;      //!< IM图片缓存路径
  std::string receivefilepath_;    //!< 文件传输缓存路径
  std::string recordfilepath_;     //!< 录音文件缓存路径

  std::string uapaddr;             //!< UAP address
  std::string portaladdr;          //!< 个人PORTAL地址
  std::string portaladdrback;      //!< 备个人PORTAL地址
  std::string confportal;          //!< 主会议PORTAL地址
  std::string confportalback;      //!< 备会议PORTAL地址
  std::string confaccesscodelist;  //!< 会议接入码列表
  std::string cscfdomain;          //!< cscf domain
  std::string contrycode;          //!< contry code
  std::string token;               //!< token
  std::string eConsoleAddr;        //!< eConsole地址
  std::string dialRuleUrl;         //!< 拨号规则地址
  std::string loginfailedaddr;     //!< 登陆失败链接地址
  std::string userhelpaddr;        //!< 用户帮助链接地址
  std::string forgetpwdaddr;       //!< 忘记密码链接地址
  std::string newaccountaddr;      //!< 创建新账户链接地址
  std::string vpnNames;            //!< 服务器配置VPN名称

  std::string route_num_;          //!< 路由号码,用于服务器证书刷新连接服务器使用

  int selfcalllimittype;
  int curcenter;                  //!< 用户所属中心: 0 南 1 北
  int retrytimes;                 //!< 客户端还可以重新登录次数
  int maxretrytimes;              //!< 客户端密码允许输错总数
  int maxcontact;                 //!< 最大允许的联系人数量

  std::string zone;               //!< 用户所在区域
  std::string netLocation;        //!< 用户登录网络类型，1：内网 2：外网

  int sensitivefunc;              //!< 指示敏感词过滤功能是否开启
  int firstlogin;                 //!< 是否为第一次登陆标识

  std::map<std::string, std::string> pluginconfigs_;  //plugin params fetched from the server
  std::map<std::string, std::string> configList_;     //获取config参数

  std::string funclist;           //!< 如果已订阅，且此功能已开通，则其标识为“1”，否则为“0”。功能位含义参考Centrix基线版本的功能位定义
  bool bIsDNDRingOffMode;         //!< 是否开启免打扰无铃音模式
  std::string featurelist;        //!< 特性位,表明某些特性是否开启
  std::string corpId;

  std::string sensewordver;       //!< 敏感词当前版本号
  std::string prilisttimestamp;   //!< 私人列表时间戳
  std::string lastLoginIP;        //!< 上次登入IP
  std::string lastLoginTime;      //!< 上次登录时间
  std::string lastLocation;       //!< 上次登录位置信息
  std::string mailboxnum;
  std::vector<std::string> senseWordList;
  std::map<std::string, std::string> callexCodeList;
  std::map<int, std::string> webCCInfo;  //!< WebCCInfo配置信息 <ID, 详细信息> 

  int acblinenum; //!< ACB按钮个数
  int reservert1; //!< ACB服务器保留时长
  int ringt2;//!< 收到refer的振铃时长
  std::string Linkagednum;
  bool bPhoneUser; //是否联动用户
  bool bPhoneJoint; //是否开启联动
  int callmode; 
  std::string voicemailaccesscode;
  int voiceMailFlg;

  bool bInputStatus; //!< 是否开启输入状态通知
  unsigned int userId;  //!< 服务器为每个用户生成的ID， 用于数据会议
  int corenetdeploymodel; //!< 核心网模式
  int holdtimeout;        //!< 呼叫保持提醒时长
  std::string snrnum;

  std::string IMGroupNumLimit;
  std::string IMGroupUserLimit;
  std::string faxresponseurl;
  std::string ControlCFU;
  std::string FwdUnconNum;
  std::string FwdBusyNum;
  std::string FwdNoAnsNum;
  std::string FwdOfflineNum;
  std::string cscfDomainName;//eServer sip注册服务器域名
  std::string ipphone_;
  std::string sipPassward;
  std::string sipOutgoingAccCode_;
  std::string exportType_;  //add by chenqinglin cWX230515 2014/7/24 增加一个成员参数用于存储导出联系人时的导出类型 [all，account] all代表全部导出，account代表只导出账号
  std::string autoUpdatetime_;	//自动升级-定时时间
  std::string fecenable_;   //是否支持抗丢包
  int dtmfMode_; //二次拨号模式 ;1:use 2833 mode to redial 0:use dtmf mode to redial

  UserProfile()
  {
      curcenter=0;               //!< 用户所属中心: 0 南 1 北
      retrytimes=0;		           //!< 客户端还可以重新登录次数
      maxretrytimes=0;             //!< 客户端密码允许输错总数
      maxcontact=0;              //!< 最大允许的联系人数量
      selfcalllimittype = 0;
      sensitivefunc=0;           //!< 指示敏感词过滤功能是否开启
      firstlogin=0;              //!< 是否为第一次登陆标识
      bIsDNDRingOffMode=false;

      acblinenum=0; //!< ACB按钮个数
      reservert1=0; //!< ACB服务器保留时长
      ringt2=0;  //!< 收到refer的振铃时长
      bPhoneUser = false;
      bPhoneJoint=false;
      callmode=0; 
      voiceMailFlg=0;
      corenetdeploymodel = 1;
      holdtimeout = 0;

      bInputStatus=false; //!< 是否开启输入状态通知
      userId = 0;
	  exportType_ = "account";            //add by chenqinglin cWX230515 2014/7/24 导出联系人的类型，默认只导出账号
	  autoUpdatetime_ = "3:00";			//自动升级 - 定时时间，默认3：00

      dtmfMode_ = 1;
  }
  ~UserProfile() {}
};

///////////////////////////////////////////////////////////////////////////
// storage data types
struct   StaffInfo
{
  std::string uri;
  std::string fullUri;

  std::string account;
  std::string name;
  std::string staffNo;
  std::string qPinyin;
  std::string sPinyin;
  std::string gender;
  std::string desc;
  std::string title;
  std::string corpName;
  std::string deptName;

  std::string homePhone;
  std::string officePhone;
  std::string officePhone2;
  std::string officePhone3;
  std::string officePhone4;
  std::string officePhone5;
  std::string officePhone6;
  std::string mobilePhone;
  std::string otherPhone;
  std::string otherPhone2;
  std::string fax;
  std::string email;
  std::string website;
  std::string zip;
  std::string addr;

  std::string location;
  std::string position;
  std::string tzone;
  std::string avtool;
  std::string device;

  std::string birthday;
  std::string age;

  std::string signature;
  std::string deptID;
  std::string imageID;

  std::string ipphone1;
  std::string ipphone2;
  std::string ipphone3;
  std::string ipphone4;
  std::string ipphone5;
  std::string ipphone6;

  std::string dummy;
  std::string modifytime;//企业通讯录用户信息时间戳
  std::string state;
  std::string oldAcc_;

  int flow;
  int flag;
public:
    StaffInfo():flow(0), flag(0){}
	virtual ~StaffInfo(){}
}; // struct StaffInfo

struct   ContactInfo : public StaffInfo
{
  ContactInfo() {}
  ContactInfo(const StaffInfo & staffInfo) : StaffInfo(staffInfo) {}
  std::string cid;
  std::string nickName;
  std::string terminalType;

};

struct   QuerySQLPair
{
	std::string strTableName;
	std::string strSQL;

}; // struct QuerySQLPair

struct   ConfigPair
{
	std::string strKey;
	std::string strValue;

}; // struct ConfigPair

struct   LoginListItem
{
  std::string account;
  std::string password;
  int rememberPwd;
  int autoLogin;
  int loginMode;

  int usesvn1;
  std::string svnacc1;
  std::string svnpsw1;
  int usesvn2;
  std::string svnacc2;
  std::string svnpsw2;

  int loginFlag;
  int reservedInt1;
  int reservedInt2;
  int reservedInt3;
  std::string reservedStr1; //保存头像
  std::string reservedStr2; //保存登陆安全码
  std::string reservedStr3;

  LoginListItem() 
    : rememberPwd(0), autoLogin(0), loginMode(0), usesvn1(0), usesvn2(0)
    , loginFlag(0), reservedInt1(0), reservedInt2(0), reservedInt3(0)
  {}

}; // struct LoginListItem

struct   changeAccountItem
{
	std::string oldAcc;
	std::string newAcc;
};

  } // namespace ecsdata
} // namespace ecs
