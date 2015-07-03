#ifndef _UC_EVENT_
#define _UC_EVENT_

//下层向上层抛的事件类型，不包含上层调用
enum EventType
{
	REG_EVENT=0,			//注册结果通知
	CALL_CONNECT_EVENT,		//呼叫接通事件
	CALL_CLOSE_EVENT,		//呼叫结束事件
	CALL_INCOMING_EVENT,	//新来电事件
	CONV_EVENT,				//会议中的事件
	VIDEO_EVENT,			//视频呼叫的事件
	PJ_NOTIFY_EVENT,		//话机联动设置结果通知事件
	RejectNewCall_EVENT,	//来电后自动拒绝新来电事件
	PUB_PJ_EVENT,			//发布话机联动状态事件
	CONTACT_STATUS_EVENT,	//状态事件
	CALL_RESERVED_EVENT,	//转移事件
	IM_EVENT,				//IM事件
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

