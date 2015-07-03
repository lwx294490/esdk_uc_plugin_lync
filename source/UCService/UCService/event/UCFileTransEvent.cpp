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
	case IM_E_EVENT_IM_P2PFILE_INCOMING_NOTIFY: 		/**< �յ��ļ���������	IM_S_P2PFILECHOOSE_NOTIFY*/
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
			SAFE_DELETE(pInfo);
		}
		break;
	case IM_E_EVENT_IM_FILEPROCESS_NOTIFY:			/**< �ļ��������֪ͨ	IM_S_FILEPROCESS_NOTIFY */
		{
			IM_S_FILEPROCESS_NOTIFY* pInfo = (IM_S_FILEPROCESS_NOTIFY*)m_pBody;

			memcpy_s(st.filename,STRING_LENGTH,pInfo->fileName,strlen(pInfo->fileName));
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
			SAFE_DELETE(pInfo);

		}
		break;
	case IM_E_EVENT_IM_FILESTATISTIC_NOTIFY:			/**< �ϱ��ļ���Ϣ	    IM_S_P2PFILESTATISTIC_NOTIFY*/
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
			SAFE_DELETE(pInfo);

		}
		break;
	case IM_E_EVENT_IM_P2PFILE_STARTRESULT_NOTIFY: 	/**< �ļ����俪ʼ���	IM_S_P2PFILE_RESULT_NOTIFY*/
		{
			IM_S_P2PFILE_RESULT_NOTIFY* pInfo = (IM_S_P2PFILE_RESULT_NOTIFY*)m_pBody;

			memcpy_s(st.filename,STRING_LENGTH,pInfo->fileName,strlen(pInfo->fileName));
			memcpy_s(st.sender,STRING_LENGTH,pInfo->account,strlen(pInfo->fileName));
			memset(st.filesize,0,STRING_LENGTH);
			memset(st.cursize,0,STRING_LENGTH);
			sprintf_s(st.errcode,STRING_LENGTH,"%d",pInfo->result);
			memset(st.procent,0,STRING_LENGTH);
			memset(st.reason,0,STRING_LENGTH);
			memset(st.sendername,0,STRING_LENGTH);
			memset(st.transferid,0,STRING_LENGTH);
			memset(st.convid,0,STRING_LENGTH);
			st.notifyType = File_SendAckNotify;
			SAFE_DELETE(pInfo);

		}
		break;
	case IM_E_EVENT_IM_P2PFILE_STOPTRESULT_NOTIFY: 	/**< �ļ�����ֹͣ���	IM_S_P2PFILE_RESULT_NOTIFY*/
		{
			IM_S_P2PFILE_RESULT_NOTIFY* pInfo = (IM_S_P2PFILE_RESULT_NOTIFY*)m_pBody;

			memcpy_s(st.filename,STRING_LENGTH,pInfo->fileName,strlen(pInfo->fileName));
			memcpy_s(st.sender,STRING_LENGTH,pInfo->account,strlen(pInfo->fileName));
			memset(st.filesize,0,STRING_LENGTH);
			memset(st.cursize,0,STRING_LENGTH);
			sprintf_s(st.errcode,STRING_LENGTH,"%d",pInfo->result);
			memset(st.procent,0,STRING_LENGTH);
			memset(st.reason,0,STRING_LENGTH);
			memset(st.sendername,0,STRING_LENGTH);
			memset(st.transferid,0,STRING_LENGTH);
			memset(st.convid,0,STRING_LENGTH);
			st.notifyType = File_CancelNotfiy;
			SAFE_DELETE(pInfo);

		}
		break;
	case IM_E_EVENT_IM_P2PFILE_STOP_NOTIFY:			/**<�ļ�����ֹ֪ͣͨ	IM_S_P2PFILESTATISTIC_NOTIFY*/
		{
			IM_S_P2PFILESTATISTIC_NOTIFY* pInfo = (IM_S_P2PFILESTATISTIC_NOTIFY*)m_pBody;

			memcpy_s(st.filename,STRING_LENGTH,pInfo->fileName,strlen(pInfo->fileName));
			memcpy_s(st.sender,STRING_LENGTH,pInfo->account,strlen(pInfo->fileName));
			memset(st.filesize,0,STRING_LENGTH);
			memset(st.cursize,0,STRING_LENGTH);
			sprintf_s(st.reason,STRING_LENGTH,"%d",pInfo->reason);
			memset(st.procent,0,STRING_LENGTH);
			memset(st.errcode,0,STRING_LENGTH);
			memset(st.sendername,0,STRING_LENGTH);
			memset(st.transferid,0,STRING_LENGTH);
			memset(st.convid,0,STRING_LENGTH);
			st.notifyType = File_CancelNotfiy;
			SAFE_DELETE(pInfo);

		}
		break;
	}

	UCIMMgr::Instance().NotifyFileTransUI(st);

	return true;
}
