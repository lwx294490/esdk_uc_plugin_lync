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
  std::string profilepath_;        //!< �û����ݴ洢λ��
  std::string headimagepath_;      //!< ͷ�����ݻ���·��
  std::string imagefilepath_;      //!< IMͼƬ����·��
  std::string receivefilepath_;    //!< �ļ����仺��·��
  std::string recordfilepath_;     //!< ¼���ļ�����·��

  std::string uapaddr;             //!< UAP address
  std::string portaladdr;          //!< ����PORTAL��ַ
  std::string portaladdrback;      //!< ������PORTAL��ַ
  std::string confportal;          //!< ������PORTAL��ַ
  std::string confportalback;      //!< ������PORTAL��ַ
  std::string confaccesscodelist;  //!< ����������б�
  std::string cscfdomain;          //!< cscf domain
  std::string contrycode;          //!< contry code
  std::string token;               //!< token
  std::string eConsoleAddr;        //!< eConsole��ַ
  std::string dialRuleUrl;         //!< ���Ź����ַ
  std::string loginfailedaddr;     //!< ��½ʧ�����ӵ�ַ
  std::string userhelpaddr;        //!< �û��������ӵ�ַ
  std::string forgetpwdaddr;       //!< �����������ӵ�ַ
  std::string newaccountaddr;      //!< �������˻����ӵ�ַ
  std::string vpnNames;            //!< ����������VPN����

  std::string route_num_;          //!< ·�ɺ���,���ڷ�����֤��ˢ�����ӷ�����ʹ��

  int selfcalllimittype;
  int curcenter;                  //!< �û���������: 0 �� 1 ��
  int retrytimes;                 //!< �ͻ��˻��������µ�¼����
  int maxretrytimes;              //!< �ͻ������������������
  int maxcontact;                 //!< ����������ϵ������

  std::string zone;               //!< �û���������
  std::string netLocation;        //!< �û���¼�������ͣ�1������ 2������

  int sensitivefunc;              //!< ָʾ���дʹ��˹����Ƿ���
  int firstlogin;                 //!< �Ƿ�Ϊ��һ�ε�½��ʶ

  std::map<std::string, std::string> pluginconfigs_;  //plugin params fetched from the server
  std::map<std::string, std::string> configList_;     //��ȡconfig����

  std::string funclist;           //!< ����Ѷ��ģ��Ҵ˹����ѿ�ͨ�������ʶΪ��1��������Ϊ��0��������λ����ο�Centrix���߰汾�Ĺ���λ����
  bool bIsDNDRingOffMode;         //!< �Ƿ��������������ģʽ
  std::string featurelist;        //!< ����λ,����ĳЩ�����Ƿ���
  std::string corpId;

  std::string sensewordver;       //!< ���дʵ�ǰ�汾��
  std::string prilisttimestamp;   //!< ˽���б�ʱ���
  std::string lastLoginIP;        //!< �ϴε���IP
  std::string lastLoginTime;      //!< �ϴε�¼ʱ��
  std::string lastLocation;       //!< �ϴε�¼λ����Ϣ
  std::string mailboxnum;
  std::vector<std::string> senseWordList;
  std::map<std::string, std::string> callexCodeList;
  std::map<int, std::string> webCCInfo;  //!< WebCCInfo������Ϣ <ID, ��ϸ��Ϣ> 

  int acblinenum; //!< ACB��ť����
  int reservert1; //!< ACB����������ʱ��
  int ringt2;//!< �յ�refer������ʱ��
  std::string Linkagednum;
  bool bPhoneUser; //�Ƿ������û�
  bool bPhoneJoint; //�Ƿ�������
  int callmode; 
  std::string voicemailaccesscode;
  int voiceMailFlg;

  bool bInputStatus; //!< �Ƿ�������״̬֪ͨ
  unsigned int userId;  //!< ������Ϊÿ���û����ɵ�ID�� �������ݻ���
  int corenetdeploymodel; //!< ������ģʽ
  int holdtimeout;        //!< ���б�������ʱ��
  std::string snrnum;

  std::string IMGroupNumLimit;
  std::string IMGroupUserLimit;
  std::string faxresponseurl;
  std::string ControlCFU;
  std::string FwdUnconNum;
  std::string FwdBusyNum;
  std::string FwdNoAnsNum;
  std::string FwdOfflineNum;
  std::string cscfDomainName;//eServer sipע�����������
  std::string ipphone_;
  std::string sipPassward;
  std::string sipOutgoingAccCode_;
  std::string exportType_;  //add by chenqinglin cWX230515 2014/7/24 ����һ����Ա�������ڴ洢������ϵ��ʱ�ĵ������� [all��account] all����ȫ��������account����ֻ�����˺�
  std::string autoUpdatetime_;	//�Զ�����-��ʱʱ��
  std::string fecenable_;   //�Ƿ�֧�ֿ�����
  int dtmfMode_; //���β���ģʽ ;1:use 2833 mode to redial 0:use dtmf mode to redial

  UserProfile()
  {
      curcenter=0;               //!< �û���������: 0 �� 1 ��
      retrytimes=0;		           //!< �ͻ��˻��������µ�¼����
      maxretrytimes=0;             //!< �ͻ������������������
      maxcontact=0;              //!< ����������ϵ������
      selfcalllimittype = 0;
      sensitivefunc=0;           //!< ָʾ���дʹ��˹����Ƿ���
      firstlogin=0;              //!< �Ƿ�Ϊ��һ�ε�½��ʶ
      bIsDNDRingOffMode=false;

      acblinenum=0; //!< ACB��ť����
      reservert1=0; //!< ACB����������ʱ��
      ringt2=0;  //!< �յ�refer������ʱ��
      bPhoneUser = false;
      bPhoneJoint=false;
      callmode=0; 
      voiceMailFlg=0;
      corenetdeploymodel = 1;
      holdtimeout = 0;

      bInputStatus=false; //!< �Ƿ�������״̬֪ͨ
      userId = 0;
	  exportType_ = "account";            //add by chenqinglin cWX230515 2014/7/24 ������ϵ�˵����ͣ�Ĭ��ֻ�����˺�
	  autoUpdatetime_ = "3:00";			//�Զ����� - ��ʱʱ�䣬Ĭ��3��00

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
  std::string modifytime;//��ҵͨѶ¼�û���Ϣʱ���
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
  std::string reservedStr1; //����ͷ��
  std::string reservedStr2; //�����½��ȫ��
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
