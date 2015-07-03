#ifndef _UC_EVENT_
#define _UC_EVENT_

//�²����ϲ��׵��¼����ͣ��������ϲ����
enum EventType
{
	REG_EVENT=0,			//ע����֪ͨ
	CALL_CONNECT_EVENT,		//���н�ͨ�¼�
	CALL_CLOSE_EVENT,		//���н����¼�
	CALL_INCOMING_EVENT,	//�������¼�
	CONV_EVENT,				//�����е��¼�
	VIDEO_EVENT,			//��Ƶ���е��¼�
	PJ_NOTIFY_EVENT,		//�����������ý��֪ͨ�¼�
	RejectNewCall_EVENT,	//������Զ��ܾ��������¼�
	PUB_PJ_EVENT,			//������������״̬�¼�
	CONTACT_STATUS_EVENT,	//״̬�¼�
	CALL_RESERVED_EVENT,	//ת���¼�
	IM_EVENT,				//IM�¼�
};

class UCEvent
{
public:
	UCEvent();
	virtual ~UCEvent();
public:
	virtual bool DoHandle(void)=0;
	EventType GetEventType(void);
private:
	EventType m_EventType;
};


#endif

