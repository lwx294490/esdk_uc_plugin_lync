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
  int sent; //1发送的消息。0接收到的消息

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
  std::string reservedStr1;//文件传输场景，用于保存文件名称
  std::string reservedStr2;//2013-8-30日，用于保存msgid
  std::string reservedStr3;//保存富媒体场景下的扩展参数
  std::string tmpStr;//临时字符串用于更新msgid

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
  int reservedInt1;//表示未读消息总数
  int reservedInt2;
  int reservedInt3;
  std::string reservedStr1;//表示最早未读消息msgid
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
	std::string passWord_;   //供读取登陆列表时使用
	std::string groupID_;    //如果为群组成员时,所属群组ID
	std::string groupName_;  //如果为群组成员时,所属群组名
	std::string groupOwner_; //如果为群组成员时,所属群组创建者帐号
	int			groupType_;  //1固定群,2临时群,3讨论组
	PeerAllInfo():groupType_(kFixGroup){
	}
};

struct GroupInfo
{
	std::string groupID_;   //群组ID
	std::string groupName_; //群组名
	std::string groupOwner_;//群组创建者

	GroupInfo()
	{
	}
};
struct OldHistoryRecord
{
	enum
	{
		SEND_MSG = 1, //发送消息
		RECV_MSG,     //接收到的消息
		SYS_MSG,      //系统消息
	};
	enum
	{
		RECV_CALL = 1,    //已接
		NOT_RECV_CALL,//未接
		DIALED_CALL   //已拨
	};
	enum
	{
		FIXED_GROUP_CONV = 1,   //固定群会话
		DISCUSS_GROUP_CONV  //讨论组会话
	};
	enum
	{
		FRIEND_CONV = 1,  //好友会话
		STRANGE_CONV  //非好友会话
	};
	enum
	{
		READED_MSG = 0,   //群组消息：已读
		UN_READED_MSG //群组消息：未读
	};
	GroupInfo	groupInfo_;
	int			unRead_;    //群组消息:0已读,1未读
	PeerInfo	peerInfo_;
	std::string format_;
	std::string content_;
	std::string datetime_;
	int			flag_;      //1发送的消息.2接收的消息.3系统消息;  1已接2未拨3已拨
	int			type_;      //群组(1固定群会话.2讨论组会话). 单人(1好友会话,2非好友会话)
	std::string mobile_;
	std::string duration_;  //通话时长
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
