#include "StdAfx.h"
#include "Log.h"
#include "UCIMMgr.h"
#include "UCFileTransEvent.h"

UCFileTransEvent::UCFileTransEvent(void)
{
}

UCFileTransEvent::~UCFileTransEvent(void)
{
}
void UCFileTransEvent::SetPara(IM_E_EVENT_ID eventID, void *body)
{
	m_EventID = eventID;
	m_pBody = body;
}
bool UCFileTransEvent::DoHandle(void)
{
	DEBUG_TRACE("");
	if(NULL == m_pBody)
	{
		ERROR_LOG("----m_pBody is NULL");
		return false;
	}

	STFileTransParam st={0};
	switch (m_EventID)
	{
	case IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY: 		/**< 收到文件传输请求	IM_S_P2PFILECHOOSE_NOTIFY*/
		{
			IM_S_P2PFILECHOOSE_NOTIFY* pInfo = (IM_S_P2PFILECHOOSE_NOTIFY*)m_pBody;

			memcpy_s(st.filename,STRING_LENGTH,pInfo->fileName,strlen(pInfo->fileName));
			memcpy_s(st.sender,STRING_LENGTH,pInfo->targetAccount,strlen(pInfo->targetAccount));
			sprintf_s(st.filesize,STRING_LENGTH,"%d",pInfo->totalSize);
			memset(st.cursize,0,STRING_LENGTH);
			memset(st.errcode,0,STRING_LENGTH);
			memset(st.procent,0,STRING_LENGTH);
			memset(st.reason,0,STRING_LENGTH);
			memset(st.sendername,0,STRING_LENGTH);
			memset(st.transferid,0,STRING_LENGTH);
			memset(st.convid,0,STRING_LENGTH);
			st.notifyType = File_ReceivedNotify;
			INFO_LOG("File_ReceivedNotify");
			SAFE_DELETE(pInfo);
		}
		break;
	case IM_E_EVENT_IM_FILEPROCESS_NOTIFY:			/**< 文件传输进度通知	IM_S_FILEPROCESS_NOTIFY */
		{
			IM_S_FILEPROCESS_NOTIFY* pInfo = (IM_S_FILEPROCESS_NOTIFY*)m_pBody;

			memcpy_s(st.filename,STRING_LENGTH,pInfo->dir,strlen(pInfo->dir));
			memcpy_s(st.sender,STRING_LENGTH,pInfo->account,strlen(pInfo->account));
			sprintf_s(st.filesize,STRING_LENGTH,"%d",pInfo->total);
			sprintf_s(st.cursize,STRING_LENGTH,"%d",pInfo->current);
			memset(st.errcode,0,STRING_LENGTH);
			sprintf_s(st.procent,STRING_LENGTH,"%d",(pInfo->current*100)/pInfo->total);
			memset(st.reason,0,STRING_LENGTH);
			memset(st.sendername,0,STRING_LENGTH);
			memset(st.transferid,0,STRING_LENGTH);
			memset(st.convid,0,STRING_LENGTH);
			st.notifyType = File_TransProcessNotify;
			INFO_LOG("File_TransProcessNotify");
			SAFE_DELETE(pInfo);

		}
		break;
	case IM_E_EVENT_IM_FILESTATISTIC_NOTIFY:			/**< 上报文件信息	    IM_S_P2PFILESTATISTIC_NOTIFY*/
		{
			IM_S_P2PFILESTATISTIC_NOTIFY* pInfo = (IM_S_P2PFILESTATISTIC_NOTIFY*)m_pBody;
			memcpy_s(st.filename,STRING_LENGTH,pInfo->fileName,strlen(pInfo->fileName));
			memcpy_s(st.sender,STRING_LENGTH,pInfo->account,strlen(pInfo->account));
			memset(st.filesize,0,STRING_LENGTH);
			memset(st.cursize,0,STRING_LENGTH);
			memset(st.errcode,0,STRING_LENGTH);
			memset(st.procent,0,STRING_LENGTH);
			sprintf_s(st.reason,STRING_LENGTH,"%d",pInfo->reason);
			memset(st.sendername,0,STRING_LENGTH);
			memset(st.transferid,0,STRING_LENGTH);
			memset(st.convid,0,STRING_LENGTH);
			st.notifyType = File_AcceptedNotify;
			INFO_LOG("File_AcceptedNotify");
			SAFE_DELETE(pInfo);

		}
		break;
	case IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY: 	/**< 文件传输开始结果	IM_S_P2PFILE_RESULT_NOTIFY*/
		{
			IM_S_P2PFILE_RESULT_NOTIFY* pInfo = (IM_S_P2PFILE_RESULT_NOTIFY*)m_pBody;

			memcpy_s(st.filename,STRING_LENGTH,pInfo->fileName,strlen(pInfo->fileName));
			memcpy_s(st.sender,STRING_LENGTH,pInfo->account,strlen(pInfo->account));
			memset(st.filesize,0,STRING_LENGTH);
			memset(st.cursize,0,STRING_LENGTH);
			sprintf_s(st.errcode,STRING_LENGTH,"%d",pInfo->result);
			memset(st.procent,0,STRING_LENGTH);
			memset(st.reason,0,STRING_LENGTH);
			memset(st.sendername,0,STRING_LENGTH);
			memset(st.transferid,0,STRING_LENGTH);
			memset(st.convid,0,STRING_LENGTH);

			switch (pInfo->result)
			{
			case 1:
				st.notifyType = File_SendAckNotify;
				INFO_LOG("File_SendAckNotify");
				break;
			case 0:
				st.notifyType = File_AcceptedNotify;
				INFO_LOG("File_AcceptedNotify");
				break;
			default:
				st.notifyType = File_CancelNotfiy;
				INFO_LOG("File_CancelNotfiy");
				break;

			}
			
			SAFE_DELETE(pInfo);

		}
		break;
	case IM_E_EVENT_IM_P2PFILE_STOPTRESULT_NOTIFY: 	/**< 文件传输停止结果	IM_S_P2PFILE_RESULT_NOTIFY*/
		{
			IM_S_P2PFILE_RESULT_NOTIFY* pInfo = (IM_S_P2PFILE_RESULT_NOTIFY*)m_pBody;

			memcpy_s(st.filename,STRING_LENGTH,pInfo->fileName,strlen(pInfo->fileName));
			memcpy_s(st.sender,STRING_LENGTH,pInfo->account,strlen(pInfo->account));
			memset(st.filesize,0,STRING_LENGTH);
			memset(st.cursize,0,STRING_LENGTH);
			sprintf_s(st.errcode,STRING_LENGTH,"%d",pInfo->result);
			memset(st.procent,0,STRING_LENGTH);
			memset(st.reason,0,STRING_LENGTH);
			memset(st.sendername,0,STRING_LENGTH);
			memset(st.transferid,0,STRING_LENGTH);
			memset(st.convid,0,STRING_LENGTH);
			st.notifyType = File_CancelNotfiy;
			INFO_LOG("File_CancelNotfiy");
			SAFE_DELETE(pInfo);

		}
		break;
	case IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY:			/**<文件传输停止通知	IM_S_P2PFILESTATISTIC_NOTIFY*/
		{
			IM_S_P2PFILESTATISTIC_NOTIFY* pInfo = (IM_S_P2PFILESTATISTIC_NOTIFY*)m_pBody;

			memcpy_s(st.filename,STRING_LENGTH,pInfo->fileName,strlen(pInfo->fileName));
			memcpy_s(st.sender,STRING_LENGTH,pInfo->account,strlen(pInfo->account));
			memset(st.filesize,0,STRING_LENGTH);
			memset(st.cursize,0,STRING_LENGTH);
			sprintf_s(st.reason,STRING_LENGTH,"%d",pInfo->reason);
			memset(st.procent,0,STRING_LENGTH);
			memset(st.errcode,0,STRING_LENGTH);
			memset(st.sendername,0,STRING_LENGTH);
			memset(st.transferid,0,STRING_LENGTH);
			memset(st.convid,0,STRING_LENGTH);
			if (IM_E_FILETRANSFER_P2PFILESTOP_REASON_COMPLETED == pInfo->reason )
			{
				st.notifyType = File_TranceSucess;
				INFO_LOG("File_TranceSucess");
			}
			else
			{
				st.notifyType = File_CancelNotfiy;
				INFO_LOG("File_CancelNotfiy");

			}
			
			SAFE_DELETE(pInfo);

		}
		break;
	}

	UCIMMgr::Instance().NotifyFileTransUI(st);

	return true;
}
