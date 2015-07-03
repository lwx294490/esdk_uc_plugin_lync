#include "StdAfx.h"
#include "UCIMMgr.h"
#include "UCContactMgr.h"
#include "UCRegMgr.h"
#include "Log.h"

IMRecvNotifyCB UCIMMgr::OnIMEventCB  = NULL;
FileTransNotifyCB UCIMMgr::OnFileEventCB = NULL;

UCIMMgr::UCIMMgr(void)
{
}

UCIMMgr::~UCIMMgr(void)
{
}
void UCIMMgr::Init(void)
{	
}
void UCIMMgr::Uninit(void)
{
}

int UCIMMgr::SendP2PIM(const std::string& _account
						   ,const std::string& _content)
{
	DEBUG_TRACE("");

	IM_S_SENDIM_ARG SendImArg;
	SendImArg.chatType = IM_E_IM_CHAT_TYPE_SINGLE;
	SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_TEXT;
	SendImArg.sourceFlag = IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG;
	memcpy(SendImArg.target,_account.c_str(),IM_D_MAX_ACCOUNT_LENGTH);	
	memcpy(SendImArg.origin,UCRegMgr::Instance().GetSelfAccount().c_str(),IM_D_MAX_ACCOUNT_LENGTH);	
	memcpy(SendImArg.displayname,"",IM_D_MAX_NAME_LENGTH);	
	memcpy(SendImArg.content,_content.c_str(),IM_D_MAX_MESSAGE_LENGTH);
	SendImArg.utcStamp = eSDKTool::GetCurUTCTime();
	SendImArg.regionID = 0;
	TUP_RESULT tRet = tup_im_sendim(&SendImArg);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_im_sendim failed");
		return UC_SDK_Failed;
	}	
	return UC_SDK_Success;
}

int UCIMMgr::SetIMEventCallBack(IMRecvNotifyCB _cb)
{
	OnIMEventCB = _cb;
	return UC_SDK_Success;
}

int UCIMMgr::TransFile(const std::string& _account
						   ,const std::string& _filepath
						   ,std::string& _tranid
						   ,std::string& _convid)
{
	DEBUG_TRACE("");

	IM_S_SENDP2PFILE_ARG arg;
	memset(arg.fileInfo.account,0,IM_D_MAX_ACCOUNT_LENGTH);
	memcpy_s(arg.fileInfo.account,IM_D_MAX_ACCOUNT_LENGTH,_account.c_str(),_account.size());
	memset(arg.fileInfo.filePath,0,IM_D_MAX_FILEPATH_LENGTH);
	memcpy_s(arg.fileInfo.filePath,IM_D_MAX_FILEPATH_LENGTH,_filepath.c_str(),_filepath.size());
	arg.timeoutSeconds = 30;
	arg.isEncrypt = TUP_FALSE;

	TUP_RESULT tRet = tup_im_sendp2pfile(&arg);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_im_sendp2pfile failed");
		return UC_SDK_Failed;
	}

	_convid = _account;
	_tranid = _filepath;

	return UC_SDK_Success;
}

int UCIMMgr::SetFileTransCallBack(FileTransNotifyCB _cb)
{	
	OnFileEventCB = _cb;
	return UC_SDK_Success;
}

int UCIMMgr::AcceptFile(const std::string& convid
							,const std::string& /*tranid*/
							,const std::string& filesavepath)
{
	IM_S_ACCEPTP2PFILE_ARG arg;
	memcpy_s(arg.fileInfo.account,convid.size(),convid.c_str(),IM_D_MAX_ACCOUNT_LENGTH);
	memcpy_s(arg.fileInfo.filePath,filesavepath.size(),filesavepath.c_str(),IM_D_MAX_FILEPATH_LENGTH);
	TUP_RESULT tRet = tup_im_acceptp2pfile(&arg);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_im_acceptp2pfile failed");
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;
}
int UCIMMgr::RejectFile(const std::string& convid,const std::string& tranid)
{
	IM_S_REJECTP2PFILE_ARG arg;
	memcpy_s(arg.fileInfo.account,convid.size(),convid.c_str(),IM_D_MAX_ACCOUNT_LENGTH);
	memcpy_s(arg.fileInfo.filePath,tranid.size(),tranid.c_str(),IM_D_MAX_FILEPATH_LENGTH);

	TUP_RESULT tRet = tup_im_rejectp2pfile(&arg);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_im_rejectp2pfile failed");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}
int UCIMMgr::CancelFile(const std::string& convid,const std::string& tranid)
{
	IM_S_CANCELP2PFILE_ARG arg;
	memcpy_s(arg.fileInfo.account,convid.size(),convid.c_str(),IM_D_MAX_ACCOUNT_LENGTH);
	memcpy_s(arg.fileInfo.filePath,tranid.size(),tranid.c_str(),IM_D_MAX_FILEPATH_LENGTH);
	TUP_RESULT tRet = tup_im_cancelp2pfile(&arg);
	if(TUP_SUCCESS != tRet)
	{
		ERROR_LOG("tup_im_cancelp2pfile failed");
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;
}

int UCIMMgr::NotifyFileTransUI(const STFileTransParam& st)
{
	DEBUG_TRACE("");
	if(NULL == OnFileEventCB)
	{
		ERROR_LOG("----OnFileEventCB is NULL");
		return UC_SDK_Failed;
	}
	INFO_LOG("----Enter OnFileEventCB ");
	OnFileEventCB(st);
	INFO_LOG("----Leave OnFileEventCB ");
	return UC_SDK_Success;
}

int UCIMMgr::NotifyIMUI(const std::string& account,const std::string& content)
{
	DEBUG_TRACE("");
	if(NULL == OnIMEventCB)
	{
		ERROR_LOG("----OnIMEventCB is NULL");
		return UC_SDK_Failed;
	}
	INFO_LOG("----Enter OnIMEventCB ");
	OnIMEventCB(account.c_str(),content.c_str());
	INFO_LOG("----Leave OnIMEventCB");
	return UC_SDK_Success;
}

