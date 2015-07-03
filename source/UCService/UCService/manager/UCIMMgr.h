#pragma once

class UCIMMgr
{
public:
	static inline UCIMMgr& Instance()
	{
		static UCIMMgr inst;
		return inst;
	}
public:
	static IMRecvNotifyCB OnIMEventCB;
	static FileTransNotifyCB OnFileEventCB;
public:
	void Init(void);
	void Uninit(void);
	int SendP2PIM(const std::string& _account,const std::string& _content);
	int SetIMEventCallBack(IMRecvNotifyCB _cb);
	int TransFile(const std::string& _account,const std::string& _filepath,std::string& _tranid,std::string& _convid);
	int AcceptFile(const std::string& _convid,const std::string& _tranid,const std::string& _filesavepath);
	int RejectFile(const std::string& _convid,const std::string& _tranid);
	int CancelFile(const std::string& _convid,const std::string& _tranid);
	int SetFileTransCallBack(FileTransNotifyCB _cb);
	int NotifyFileTransUI(const STFileTransParam& _stPara);
	int NotifyIMUI(const std::string& _account,const std::string& _content);
private:
	UCIMMgr(void);
	~UCIMMgr(void);
};
