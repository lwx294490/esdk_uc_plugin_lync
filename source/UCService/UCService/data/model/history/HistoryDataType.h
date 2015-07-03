#pragma once

#define HISTORYDB_NAME  "historydb"

namespace ecs {
  namespace ecsdata {
    namespace history {

///////////////////////////////////////////////////////////////////////////
typedef long long DataRecordId;

struct Record
{
  DataRecordId recordId;
  int recordType;

  std::string cvsId;
  std::string oldCvsId;
  // 
  std::string peerId;
  std::string peerName;
  int sent; //1���͵���Ϣ��0���յ�����Ϣ

  // 
  std::string date; // YYYY-MM-DD
  std::string time; // HH:MM:SS
  std::string utcdate; // YYYY-MM-DD
  std::string utctime; // HH:MM:SS 
  int duration;

  // 
  int unread;
  int unreadCall;
  int important;

  std::string body; // with format
  std::string text; // pure text

  int flag;

  int reservedInt1;
  int reservedInt2;
  int reservedInt3;
  std::string reservedStr1;//�ļ����䳡�������ڱ����ļ�����
  std::string reservedStr2;//2013-8-30�գ����ڱ���msgid
  std::string reservedStr3;//���渻ý�峡���µ���չ����
  std::string tmpStr;//��ʱ�ַ������ڸ���msgid

  Record()
    : recordId(-1)
    , recordType(-1)
    , sent(0)
    , duration(-1)
    , unread(0)
	, unreadCall(0)
    , important(0)
    , flag(0)
    , reservedInt1(0)
    , reservedInt2(0)
    , reservedInt3(0)
  {
  }

};

struct Cvs
{
  std::string cvsId;
  int cvsType;

  std::string groupId;
  std::string groupName;
  std::string originator;
  std::string participants;
  std::string desc;

  int flag;
  int reservedInt1;//��ʾδ����Ϣ����
  int reservedInt2;
  int reservedInt3;
  std::string reservedStr1;//��ʾ����δ����Ϣmsgid
  std::string reservedStr2;
  std::string reservedStr3;

  Cvs()
    : cvsType(-1)
    , flag(0)
    , reservedInt1(0)
    , reservedInt2(0)
    , reservedInt3(0)
  {
  }

};

struct CvsMsgId
{
    std::string cvsId;
    std::string msgId;
    int         msgType;
    std::string senderUri;
    int         state;

    CvsMsgId() : msgType(0), state(0)
    {
    }
};

enum CvsMsgState
{
    UNREAD,
    READ,
    DELETING,
};

struct RecentCvs
{
  std::string cvsId;
  int cvsType;

  DataRecordId lastRecordId;

  int hided;
  int flag;

  int reservedInt1;
  int reservedInt2;
  int reservedInt3;
  std::string reservedStr1;
  std::string reservedStr2;
  std::string reservedStr3;

  RecentCvs() 
    : cvsType(-1)
    , lastRecordId(-1)
    , hided(0)
    , flag(0)
    , reservedInt1(0)
    , reservedInt2(0)
    , reservedInt3(0)
  {
  }

};

///////////////////////////////////////////////////////////////////////////
struct CvsWithRecord : public Cvs
{
  int limit; // just used for query parameter

  int hided;
  Record lastRecord;

  CvsWithRecord() : limit(0), hided(0)
  {
  }

};

struct OldHistoryAnalyzeData
{
	std::string key_;
	std::string name_;
	std::string mobile_;
	int			totalCount_;
	OldHistoryAnalyzeData():totalCount_(0)
	{
	}
	bool operator<(const OldHistoryAnalyzeData& _data) const
	{
		return key_ < _data.key_;
	}
};

struct PeerInfo
{
	std::string peerAccount;
	std::string peerName_;
};

struct PeerAllInfo
{
	enum
	{
		kFixGroup = 1,
		kTempGroup,
		kDiscussGroup
	};
	PeerInfo    peerInfo_;
	std::string callNo_;
	std::string passWord_;   //����ȡ��½�б�ʱʹ��
	std::string groupID_;    //���ΪȺ���Աʱ,����Ⱥ��ID
	std::string groupName_;  //���ΪȺ���Աʱ,����Ⱥ����
	std::string groupOwner_; //���ΪȺ���Աʱ,����Ⱥ�鴴�����ʺ�
	int			groupType_;  //1�̶�Ⱥ,2��ʱȺ,3������
	PeerAllInfo():groupType_(kFixGroup){
	}
};

struct GroupInfo
{
	std::string groupID_;   //Ⱥ��ID
	std::string groupName_; //Ⱥ����
	std::string groupOwner_;//Ⱥ�鴴����

	GroupInfo()
	{
	}
};
struct OldHistoryRecord
{
	enum
	{
		SEND_MSG = 1, //������Ϣ
		RECV_MSG,     //���յ�����Ϣ
		SYS_MSG,      //ϵͳ��Ϣ
	};
	enum
	{
		RECV_CALL = 1,    //�ѽ�
		NOT_RECV_CALL,//δ��
		DIALED_CALL   //�Ѳ�
	};
	enum
	{
		FIXED_GROUP_CONV = 1,   //�̶�Ⱥ�Ự
		DISCUSS_GROUP_CONV  //������Ự
	};
	enum
	{
		FRIEND_CONV = 1,  //���ѻỰ
		STRANGE_CONV  //�Ǻ��ѻỰ
	};
	enum
	{
		READED_MSG = 0,   //Ⱥ����Ϣ���Ѷ�
		UN_READED_MSG //Ⱥ����Ϣ��δ��
	};
	GroupInfo	groupInfo_;
	int			unRead_;    //Ⱥ����Ϣ:0�Ѷ�,1δ��
	PeerInfo	peerInfo_;
	std::string format_;
	std::string content_;
	std::string datetime_;
	int			flag_;      //1���͵���Ϣ.2���յ���Ϣ.3ϵͳ��Ϣ;  1�ѽ�2δ��3�Ѳ�
	int			type_;      //Ⱥ��(1�̶�Ⱥ�Ự.2������Ự). ����(1���ѻỰ,2�Ǻ��ѻỰ)
	std::string mobile_;
	std::string duration_;  //ͨ��ʱ��
	std::string uctDatetime_;
	OldHistoryRecord():unRead_(0),flag_(1),type_(1)
	{
	}
};

struct OldHistoryProgress
{
	std::string  keyName_;
	std::string	 value_;
};


    } // namespace history
  } // namespace ecsdata
} // namespace ecs
